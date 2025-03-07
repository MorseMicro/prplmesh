#!/bin/bash
###############################################################
# SPDX-License-Identifier: BSD-2-Clause-Patent
# SPDX-FileCopyrightText: 2019-2020 the prplMesh contributors (see AUTHORS.md)
# This code is subject to the terms of the BSD+Patent license.
# See LICENSE file for more details.
###############################################################

scriptdir=$(dirname "$(readlink -f "$0")")
rootdir=$(realpath "$scriptdir/../..")
# shellcheck disable=SC2034
installdir="${rootdir:?}/build/install"

# shellcheck source=functions.sh
. "${rootdir}/tools/functions.sh"

usage() {
    echo "usage: $(basename "$0") [-hvd] [-n name] [-N network]"
    echo "  options:"
    echo "      -h|--help - show this help menu"
    echo "      -v|--verbose - verbosity on"
    echo "      -d|--detach - run in background"
    echo "      -f|--force - if the container is already running, kill it and restart"
    echo "      -n|--name - container name (for later easy attach)"
    echo "      -p|--port - port to expose on the container"
    echo "      -P|--publish - publish all exposed ports to the host"
    echo "      -N|--network - docker network to which to attach the container"
    echo "      -u|--unique-id - unique id to add as suffix to container and network names"
    echo "      --entrypoint - use a different entrypoint for the container"
}

main() {
    if ! OPTS=$(getopt -o 'hvdfn:N:o:t:e:p:u:' --long verbose,help,detach,force,name:,network:,entrypoint:,tag:,expose:,publish:,options:,unique-id: -n 'parse-options' -- "$@"); then
        err "Failed parsing options." >&2; usage; exit 1
    fi

    eval set -- "$OPTS"

    while true; do
        case "$1" in
            -v | --verbose)     VERBOSE=true; shift ;;
            -h | --help)        usage; exit 0; shift ;;
            -d | --detach)      DETACH=true; shift ;;
            -f | --force)       FORCE=true; shift ;;
            -n | --name)        NAME="$2"; shift; shift ;;
            -u | --unique-id)   UNIQUE_ID="$2"; shift; shift ;;
            -t | --tag)         TAG=":$2"; shift; shift ;;
            -e | --expose)      PORT+=(--expose "$2"); shift; shift ;;
            -p | --publish)     PUBLISH+=(-p "$2"); shift; shift ;;
            -N | --network)     NETWORK="$2"; shift; shift ;;
            --entrypoint)       ENTRYPOINT="$2"; shift; shift ;;
            -- ) shift; break ;;
            * ) err "unsupported argument $1"; usage; exit 1 ;;
        esac
    done

    image=${PRPLMESH_RUNNER_IMAGE-"${DOCKER_REGISTRY}prplmesh-builder-ubuntu-bionic$TAG"}
    dbg "VERBOSE=${VERBOSE}"
    dbg "DETACH=${DETACH}"
    dbg "NETWORK=${NETWORK}"
    dbg "IMAGE=${image}"
    dbg "PORT=${PORT[*]}"
    dbg "PUBLISH=${PUBLISH[*]}"
    dbg "NAME=${NAME}"
    dbg "FORCE=${FORCE}"
    dbg "UNIQUE_ID=${UNIQUE_ID}"

    NETWORK="${NETWORK:-prplMesh-net-${UNIQUE_ID}}"
    # Interface names seems to be assigned based on the alphabetical order of the docker networks.
    # We need the ucc to always be eth0, so we prepend a low number to the network name.
    # TODO: remove once docker has another way to have deterministic interface names.
    NETWORK_UCC="1-$NETWORK-ucc"
    for _network in "$NETWORK" "$NETWORK_UCC" ; do
            docker network inspect "${_network}" >/dev/null 2>&1 || {
                echo "Network ${_network} does not exist, creating..."
                run docker network create --label prplmesh --label prplmesh-id="${UNIQUE_ID}" "${_network}" || {
                    echo "Network creation failed!"
                    exit 1
                }
            }
    done

    DOCKEROPTS=(
        -e "USER=${SUDO_USER:-${USER}}"
        -e "INSTALL_DIR=${installdir}"
        --label prplmesh
        --label "prplmesh-id=${UNIQUE_ID}"
        --privileged
        --network "${NETWORK}"
        "${PORT[@]}"
        "${PUBLISH[@]}"
        -v "${installdir}:${installdir}"
        -v "${rootdir}:${rootdir}"
        -v "${rootdir}/logs/${NAME}:/tmp/beerocks/logs"
        -v "/lib/modules:/lib/modules:ro"
        --name "${NAME}"
    )

    [ -n "$ENTRYPOINT" ] && DOCKEROPTS+=(--entrypoint "$ENTRYPOINT")
    if [ "$DETACH" = "false" ]; then
        DOCKER_RUN_OPTS+=(-a)
    fi
    if docker ps -a --format '{{ .Names }}' --filter name="${NAME}" | grep -q -x "${NAME}"; then
        info "Container ${NAME} is already running"
        if [ "$FORCE" = "true" ]; then
            run docker container rm -f "$NAME"
        else
            exit 1
        fi
    fi

    mkdir -p "${rootdir}/logs/${NAME}"

    # Save the container name so that it can easily be stopped/removed later
    run docker container create "${DOCKEROPTS[@]}" --entrypoint /root/start-prplmesh.sh "${image}" "$@"
    # Connect the container to the ucc network:
    run docker network connect "$NETWORK_UCC" "$NAME"
    run docker container start "${DOCKER_RUN_OPTS[@]}" "$NAME"
}

VERBOSE=false
DETACH=false
FORCE=false
UNIQUE_ID=${SUDO_USER:-${USER}}
NAME=prplMesh
ENTRYPOINT=
PORT=(--expose 5000)

main "$@"
