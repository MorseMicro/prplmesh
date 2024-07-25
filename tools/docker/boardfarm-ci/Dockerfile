FROM python:3.12.4-slim-bullseye
# Debian dependencies to install docker and docker compose from docker.com
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    apt-transport-https \
    ca-certificates \
    curl \
    gcc \
    gnupg-agent \
    jq \
    libsnmp-dev \
    software-properties-common \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install docker and docker-compose from docker.com repositories
RUN install -m 0755 -d /etc/apt/keyrings && curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc && chmod a+r /etc/apt/keyrings/docker.asc
RUN echo \
    "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian \
    $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
    tee /etc/apt/sources.list.d/docker.list > /dev/null
RUN apt-get update \
    && apt-get install -y \
    docker-ce \
    docker-ce-cli \
    containerd.io \
    docker-buildx-plugin \
    docker-compose-plugin \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Installation of boardfarm
RUN git clone https://github.com/mattsm/boardfarm.git \
    && cd boardfarm \
    && git checkout 100521fde1fb67536682cafecc2f91a6e2e8a6f8 \
    && python3 setup.py install

# Installation of the python packages needed by the tests
COPY requirements.txt /app/requirements.txt
WORKDIR app
# Pin pysnmp package, as an update breaks boardfarm imports
RUN sed -i 's/pysnmp/pysnmp==4.4.12/g' requirements.txt
RUN pip3 install -r requirements.txt && pip3 install pyasyncore

# Installation of Debian dependencies needed by the tests
RUN apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    iperf3 \
    iproute2 \
    iw \
    net-tools \
    tshark \
    wireshark-common \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*
