# Contributing to prplMesh

You can contribute to prplMesh in various ways: reporting bugs, improving documentation, improving the code.

## Getting involved

Part of the conversation takes place directly on gitlab through merge requests, and comments on commits.
But discussions about the design of features or the approach to bug fixes happens in JIRA.
Thus, it is advisable to subscribe to (i.e. watch) the JIRA issues you are interested in.

Daily conversations take place on [Slack](https://prplfoundation.slack.com/).
You can ask for an invite to anyone currently involved, e.g. by sending a message to an active contributer on gitlab.

Some issues are labelled as [good first issue](https://jira.prplfoundation.org/browse/PPM-305?jql=labels%3Dgood_first_issue).
Picking one of these to work on as your first contribution is recommended.

The [prpl Foundation Code of Conduct](https://prplfoundation.org/about/code-of-conduct/) applies to all communication about prplMesh.
If you encounter a problem with someone's conduct, contact the prpl Operations Manager Shelly Coen - Shelly.Coen [at] prplfoundation.org.

## Reporting bugs

To report bugs, use the [JIRA create issue](https://jira.prplfoundation.org/secure/CreateIssue!default.jspa) entry form.
Select Prplmesh as the project, and "Bug" as the issue type (you can use "Task" for feature requests)

## Improving documentation

High-level developer documentation can be found on [Confluence](https://confluence.prplfoundation.org/display/PRPLMESH), which can be edited in-place.

User documentation is still under development.
It currently resides as pptx and docx documents in the [documentation](documentation/) directory.

## Contributing code

Before development is started, a [JIRA task or bug](#working-with-jira) should have been created for the issue.
All development is managed using [merge requests](#merge-requests-workflow).
[Commits](#commits) must be in logical, consistent units and have a good commit message that includes the JIRA key of the corresponding issue.
Every commit must carry a Signed-off-by tag to assert your agreement with the [DCO](#developers-certificate-of-origin).
Merge requests are reviewed and checks are performed on them before they are merged.
Code should adhere to the [coding style](#coding-style).

Note that everybody follows these same guidelines.
Core contributors, occasional contributors and maintainers are all alike.

### Working with JIRA

Every bug or feature needs to have a JIRA task associated with it, so that we can track the progress and see what people are working on.
An exception is made for "hotfixes": small fixes that are uncontroversial, e.g. fixing whitespace in one file. Those don't need an explicit JIRA issue.

To enable automatic tracking between JIRA and git, we ask that all branches (except for hotfixes) contain the JIRA id, and all commits contain it as well.
This is unfortunately necessary for matching up the information between the two systems.
Adding the JIRA key to merge request names is also recommended, but not required.

The JIRA issue should be created before any work is started.
When work is started, the developer should transition the issue to "In progress" and assign his- or herself to the issue.
Please also make sure that any issue you work on is part of the current sprint (even if you don't think it'll be finished in the sprint)
Usage of the time tracking features is also recommended; for this to work, make sure that you add an estimation of how much time the work is going to take before you start, and then remember to log the time it takes you to work on the issue.
Time spent reviewing other issues is not counted, but time spent implementing review feedback is.
When it's time for review, please transition the issue manually to the "In review" state.
We're looking at possibly automating this in the future, but it still needs to be done manually for now.
Make sure the JIRA issue has an informative description; it will form the basis of any discussion of the feature or bug in question, so you want to make sure that the description makes the problem clear.
You can then copy the description to the merge request description (it's OK if they're the same).
You may need to adjust the syntax manually if you do this, though.

JIRA uses a syntax that's different from the markdown used by gitlab. It's described [here](https://jira.prplfoundation.org/secure/WikiRendererHelpAction.jspa)

### Copyright

The copyright over the code is shared between all contributors.
To simplify tracking this information, the [AUTHORS](AUTHORS.md) file list all contributors.
Individual files don't.
Therefore, if you make a significant (i.e. copyrightable) contribution, add yourself to AUTHORS.md (in a separate commit).

Every file must have the following copyright header:
```
SPDX-License-Identifier: BSD-2-Clause-Patent
SPDX-FileCopyrightText: 2020 the prplMesh contributors (see AUTHORS.md)
This code is subject to the terms of the BSD+Patent license.
See LICENSE file for more details.
```

### Commits

The code history is considered a very important aspect of the source code of the project.
It is part of the code's documentation, and allows anyone (including the original author) to find back why something was done in that particular way.
Therefore, we pay attention to how the commits look.

Every commit must stand on its own.
Commits should be split up into atomic units that perform one specific change.
E.g. to add a parameter to a function, there would be one commit to add the parameter and update all callers with the current value for it, and a second commit that changes one caller to use a different value for it.

Normally, a commit shouldn't break anything.
This makes it possible to use `git bisect` to find the commit that introduced a bug.
However, sometimes splitting commits in a way that does break something is much easier (e.g. to review).
Also, it turns out that we don't use bisect much in practice (instead, we manually bisect over merges).
Therefore, commits that break something are allowed, though it is still to be avoided if it's easy to do.
If you do this, make sure to mention in the commit message that it breaks compilation or runtime (and why).
Also in the commit that finally fixes it, mention that.

The commit message is very important, it is part of the documentation.
It is relevant both during review of the contribution, and later to be able to understand why things are the way they are.
A commit message consists of a subject, a message body and a set of tags.

    component: class-or-function: change this and that

    The current situation is this and that. However, it should be that or
    that.

    We can do one or the other. One has this advantage, the other has this
    advantage. We choose one.

    Do this thing and do that thing.

    https://jira.prplfoundation.org/browse/PPM-204

    Signed-off-by: The Author <author.mail@address.com>
    Co-Authored-by: The Other Author <email@address.com>
    Signed-off-by: The Other Author <email@address.com>

The subject must be very short, it appears in the [short log](https://gitlab.com/prpl-foundation/prplmesh/prplMesh/-/network/master).

* Write it in the imperative: "add support for X".
* Start with a prefix that indicates the component: tlvf, common, documentation, bpl, bwl, bcl, bml, transport, topology, master, slave, monitor.
  Often, changes need to be made to multiple components, e.g. because of API change.
  The component that exports the changed API should be the one indicated then.
  If you feel multiple components apply, you should try to split up the commit into separate commits.
  The component does not always correspond to a directory.
  E.g. a change to [this file](CONTRIBUTING.md) would have `documentation` as component, even if it's not in the `documentation` directory.
* If the change is to a specific class or function, add it after the component
* In principle maximum 62 characters (including prefix).
  Because prefixes can be long (e.g. `transport: Ieee1905Transport::update_network_interfaces():`, this limit is often exceeded.
* Describes the "what" succinctly.
* Avoid verbs that don't say anything: "fix", "improve", "update", ...
* Be specific.
* Don't capitalize first word after the prefix.
* Don't write a full stop at the end of the subject line.

After the subject comes an empty line, followed by the extended description.
There is no limit to the length of the description.
It generally describes the "why" and "what" according to the following pattern:

* the context (current situation);
* the problem statement (why the current situation is not good);
* possible solutions with their pros and cons;
* the chosen solution and why it was chosen;
* the (core) change itself - in the imperative (i.e. "add foo()", not ("added foo()");
* additional changes needed to keep things working (e.g. "Update callers with the new argument").
* The JIRA key should ideally be part of every commit. It can be either on its own (PPM-204) or as a link to JIRA (https://jira.prplfoundation.org/browse/PPM-204).

Since commits should be split up, there will be many commits that are not useful on their own, but just prepare for another commit.
In that case, the preparatory commits should refer to what they prepare for.
For example, you could have the preparatory commit:

    tlvf: CmduMessageTx::finalize(): add swap_needed parameter

    Prepare for "tlvf: message_com::send_cmdu(): don't swap internal
    messages".

    PPM-204

    Signed-off-by: Joe Developer <joe@prplfoundation.org>

Followed by the commit that actually makes the change:

    tlvf: message_com::send_cmdu(): don't swap internal messages

    Messages that are sent over UDS should not be swapped, since the
    receiver does not unswap them. Swapping is not needed anyway since the
    sender and receiver are guaranteed to be the same device over UDS.

    This can be detected using the dst_mac of the message, which is empty
    for messages that will be sent over UDS.

    Use the swap_needed parameter of CmduMessageTx::finalize() to avoid
    swapping.

    https://jira.prplfoundation.org/browse/PPM-204

    Signed-off-by: Joe Developer <joe@prplfoundation.org>

The extended description only needs to be added if there is actually something to say.
For example, the commit that added this document only had the subject line "documentation: add CONTRIBUTING.md" and no extended description.

The extended description should be wrapped at 72 columns (because `git log` indents with a tab, so it still fits on an 80-character line).
There are four exceptions:

* Strings found in log files should be copied as is, to simplify searching through the history.
* Similarly, for build failures, compilation output and error messages should be copied as is.
* URLs should never be split, for obvious reasons.
* The tags (Signed-off-by etc.) are never wrapped.

At the end of the commit message there is a block of tags.

The first tag must be a "Signed-off-by:" from the author of the commit.
This is a short way for you to say that you are entitled to contribute the patch under prplMesh's BSD+Patent license.
It is a legal statement that asserts your agreement with the [DCO](#developers-certificate-of-origin).
Therefore, it must have your *real name* (First Last) and a valid e-mail address.
Adding this tag can be done automatically by using `git commit -s`.
If you are editing files and committing through GitLab, you must write your real name in the “Full Name” field in your GitLab profile and the email used in the "Signed-off-by:" must be your "Commit email" address.
You must manually add the "Signed-off-by:" to the commit message that gitlab requests.
If you are editing files and committing on your local PC, set your name and email with:

```bash
git config --global user.name "my name"
git config --global user.email "my@email.address"
```

Then, adding the "Signed-off-by" line is as simple as using `git commit -s` instead of `git commit` (using an alias is recommended, e.g. `git config --global alias.ci='commit -s'`)

### Merge Request workflow

This section describes the workflow followed by core contributors and maintainers.
It is advised to follow a similar workflow for your own contributions.
This section describes the full workflow.
For smaller contributions, you may take shortcuts.

The workflow is explained in detail below. In summary, it consists of these steps.

1. Create a branch
2. Create a "Draft" (work in progress) merge request. This means that the MR title starts with "Draft:", and is treated specially by gitlab (for instance, by preventing it from getting merged while in "Draft" state)
3. Make the changes, commit with amend and rebase
4. Push regularly
5. Clean up the commits, push, and move the MR out of "Draft" state
6. Review starts - reviewer "Requests changes"
7. Author addresses review comments in additional fixup commits.
   * If no more fixes are needed
     * Author rebases with `git rebase -i --autosquash master` to clean up the merge request.
   * If more fixes are needed (suggested by reviewers or by the author himself)
     * Author does rebase-force-push to squash fixup commits and asks for a followup review (this makes the next review iterations simpler)

8. Review is approved by maintainers.
9. Use `git rebase -i --autosquash master` to clean up the branch of the merge request.
10. The merge request will be merged automatically when CI succeeds.

Start by creating a branch.
We give branches a name following `<type>/<subject>`.
Types are `feature` for feature development, `bugfix` for fixing bugs from the issues list, `hotfix` for small fixes without an issue, and `dev/<user>` for personal development branches that are not meant for merging.
Both `bugfix` and `feature` branches should have a JIRA identifier in their branch name (e.g. feature/PPM-204-implement-dynamic-steering)

This branch is immediately pushed, and a "Draft" (Work in progress) merge request is created for it.
This can be done in a number of ways: when using `git push` on the CLI, you will get a link to create a MR; alternatively, you can create a merge request from the gitlab UI, or [add options to git push](https://docs.gitlab.com/ee/user/project/push_options.html#push-options-for-merge-requests) to instruct gitlab to automatically create a MR for it.
This "Draft" merge request signals the others that someone is working on this feature/bugfix.
It allows others to see what you're doing before it is completed, and to give early feedback and suggestions.
For such a "Draft", it is not yet necessary that the commits are nicely split up.

Continue developing the code.
Push your work regularly.
You can make separate commits, or amend a single commit, or rebase and sort it into different commits, at your option.
Every time you push, CI will run on the code and you will be informed of any issues with it.
Also, even if the merge request is still in a "Draft" state, maintainers may start giving comments on it.
The purpose of these comments is to make sure your work is aligned with expectations.
It avoids that after a lot of work, you are asked to still make major changes.

Once your feature is ready, use `git rebase -i` to organise it in clean commits and add a proper commit message to every commit, including a Signed-off-by.
Force-push the branch and take the merge request out of "Draft" state.
Other contributors will start reviewing your change and make suggestions for improvements.
The review has the following goals:

* Make sure maintainers stay aware of all the changes happening in the code.
* Identify opportunities for refactoring, code reuse, optimisation, ...
* Make sure the coding style and patterns stay consistent.
* Make sure the code remains maintainable and easy to understand.
* Brainstorm about better ways to write code or better architectural approaches.
* Identify potential bugs.
* Identify missing tests.

Very often, the review will lead to comments that don't really need to be addressed for the merge request to be accepted.
Many of the review goals are more about having a discussion than about really forcing changes.
Unfortunately, gitlab doesn't have an easy way to make such a distinction, so reviewers have to mention explicitly when a suggestion is optional.
For issues that can be addressed later, it is acceptable to create a new JIRA task for them, then resolve the comment by pointing to the new JIRA task that will address those comments.

If you make more changes after a merge request is moved out of "Draft" state, do not rebase or amend.
This will allow reviewers to easily see the differences compared to their previous review.
Instead, create additional commits with `git commit --fixup <sha1 of commit to fix> -e`.
Do _not_ add a Signed-off-by to these commits.
This will block merging due to the DCO check, but that is intended because the fixup commits need to be applied first (see below).
In the fixup commit message, explain which review comments are addressed by the change - but don't change the subject line, since that is used by autosquash (see below).
If the commit message itself needs to be changed, use `git commit --squash <sha1 of commit to fix> -e`.
Below the subject line, add a second subject line, followed by the complete commit message and the Signed-off-by.
During the autosquash rebase, we'll only retain the second commit message (see below).

In the merge request's web interface, mark the comments that have been addressed as Resolved (this should be automatic for specific code related comments; gitlab automatically detects if the code in question has been changed).
Also mark the comments that are optional as Resolved.
If you don't take the suggestion directly or you disagree or only apply it in part, don't mark it as Resolved.
Regularly push your branch.

There may be several iterations in the review.
Finally, the merge request is marked as Approved by the approvers.
However, it cannot be applied as is because the commits are still "dirty".
The last step is to perform `git rebase -i --autosquash master`.
This will apply the fixup commits automatically.
For the squash commits, it will stop in an editor to allow you to update the commit message.
Just use the last commit message, remove all the rest.
Finally, force-push the branch.
The DCO check will now succeed.
When CI finishes and is successful, the merge request will be merged automatically.

Note that there are a few cases where it is not possible to use fixup commits.
In these cases, use rebase and create a clean series of commits again.
Add a comment in the merge request why this was done.
This is needed at least in the following cases:

* If you need to pull in changes from master or another branch or merge request.
* If you need to reorder the commits.
* If you need to move a subset of the changes from one commit to another commit.

If you are working on a big feature, you often encounter something small that needs to be fixed or improved that is relatively independent of the feature.
Such a change can be included as one of the first commits in the merge request.
However, often it's useful to create a separate merge request for it, so it can be applied more quickly.
The typical workflow for this is:

* Make the fix and commit it with a proper commit message.
* Check out a new branch `hotfix/<description>` based on master.
* Cherry-pick the fix commit.
* Push and create a merge request.
* Check out the development branch and rebase on the hotfix branch. This will automatically remove the fix commit.

If a MR is in "Draft" state and it becomes ready (i.e. you did the necessary fixups and rebased on master), please remember to remove the "Draft" state.
TODO: a good example of a merge request with review, discussion, and several iterations is https://gitlab.com/prpl-foundation/prplmesh/prplMesh/-/merge\_requests/???

### Testing

Some changes are riskier than others, since they may break existing functionality which is not yet covered by prplMesh CI.
Changing the topology handling, channel selection, autoconfig - developers should take extra care when modifying such code areas.
So, it is expected from every developer to use his/hers good judgement, consult with the EasyMesh Test plan, and run real certification tests
with real devices using the prplmesh CI infrastructure which allows triggering a test in the CI testbed for a given branch.
For more information on how to trigger a test, see [Testing in CI](https://confluence.prplfoundation.org/display/PRPLMESH/Testing+in+CI).

### Definition of done

Before a merge request can be merged, it must be considered "Done".
That means the following conditions must hold.

* All commits have a Signed-off-by. Automatic with the DCO check.
* At least one maintainer has reviewed and approvied.
* Code builds on Ubuntu, with `BWL_TYPE=DUMMY`. Automatic with gitlab CI.
* Unit tests run successfully. Automatic with gitlab CI.
* For each new flow being added, `tests/test_flows.py` must be updated accordingly to test the new flow, and the corresponding certification test (if any) must be added to `tests/certification/passing_agent_tests.txt` or to `tests/certification/passing_agent_tests_wifi_bh.txt` if it is a wireless backhaul test.
* Run clang-format.sh. If it fixes lines you did not change, commit that separately.
* Code builds for Turris Omnia, GL.inet B1300, and Axepoint-based devices. Automatic with gitlab CI.
* Test at least one agent test in the CI testbed covering the changes done, if applicable.
* TODO valgrind / klockwork / clang-tidy / etc

### Coding style

See [the separate coding style document](CODINGSTYLE.md).

Formatting of the code is verified automatically in CI with various tools.
C++ code is checked with `clang-format`, which can also update files in-place.
Use `tools/docker/clang-format.sh` to make sure formatting is correct before each commit.
Autogenerated files are excluded by this script.
Python code is checked with `flake8`.
Use the command `docker run -v $PWD:$PWD pipelinecomponents/flake8:f087c4c flake8 $PWD/tests/opts.py` from the top-level directory to check the file `tests/opts.py`.
Do this for every file you modified.
You can use the `autopep8` tool to automatically reformat files to satisfy flake8 checks, but make sure to verify what it does.

<a id="developers-certificate-of-origin"></a>
## Developer's Certificate of Origin 1.1

By making a contribution to this project, I certify that:

* (a) The contribution was created in whole or in part by me and I
  have the right to submit it under the open source license
  indicated in the file; or

* (b) The contribution is based upon previous work that, to the best
  of my knowledge, is covered under an appropriate open source
  license and I have the right under that license to submit that
  work with modifications, whether created in whole or in part
  by me, under the same open source license (unless I am
  permitted to submit under a different license), as indicated
  in the file; or

* (c) The contribution was provided directly to me by some other
  person who certified (a), (b) or (c) and I have not modified
  it.

* (d) I understand and agree that this project and the contribution
  are public and that a record of the contribution (including all
  personal information I submit with it, including my sign-off) is
  maintained indefinitely and may be redistributed consistent with
  this project or the open source license(s) involved.
