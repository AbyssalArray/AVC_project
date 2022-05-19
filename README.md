# AVC

Autonomous Vehicle Challenge project

## Team Members and Contact Information
- Alex Fausett - fausetalex@myvuw.ac.nz
- Anthony Kendrew - kendreanth@myvuw.ac.nz
- Evgeny Zhilkin - zhilkievge@myvuw.ac.nz

# Role Descriptions
## Software Architect : Ev
- Description : The Software Architect's role is to develop the main functionality of the program. They are responsible for building the skeleton of the program, requesting specific functions of the Project Designer to be developed, and generally the bulk of the working code.

## Project Designer : Alex
- Description : The Project Designer's role is to ensure the program runs as expected and is legible. They will comment and format code, find the best values to use for different functions and constants, test the program, and designing the project specifications. 

## Project Manager : Anthony
- Description : The Project Manager's role is to maintain the project's timeline and ensure that segments of the project are completed on time. They will approve merge requests, chase up any aspects of the plan that are lagging behind the alloted time, ensure communication and delivery of the project, and help in places when required.

## Software Engineer : Alex, Anthony and Ev
- Description : The Software Engineers' role is to develop programmatic aspects of the project. This includes developing sub-programs and functions called by the main program and testing when required.

# Project Design
The main project is split into three sections: Core, Completion, Challenge. Each section will have its own method and the program will switch to the next method once the first one meets the designated colour (red, green or blue) which marks the end of the section (and the start of the next one). Each section will have its own way of navigating through the maze, and will use some universal methods such as turning, moving forward, what to do in the case of 'getting lost' (losing the black line of the maze), etc.

# Planning

## Core
| **Start Date** | **Task Description**                                                      | **Responsible Team Member** | **End Date** | **Outcome**      |
| -------------- | ------------------------------------------------------------------------- | --------------------------- | ------------ | ---------------- |
| 13/5           | Construct skeleton code for the main() method                             | Ev                          | 15/5         | Completed 15/5   |
| 13/5           | Create UML Class diagrams                                                 | Anthony                     | 15/5         | Completed 19/5   |
| 14/5           | Set up classes for Hardware etc. using diagrams                           | Anthony                     | 15/5         | Completed 19/5   |
| 14/5           | Create constants                                                          | Alex                        | 15/5         | Add as we go     |
| 13/5           | Develop code for basic movements (forward, backward, turn left and right) | Ev                          | 18/5         | Completed\* 17/5 |
| 16/5           | Develop method to detect line using the robot camera                      | Anthony                     | 18/5         |                  |
| 16/5           | Detect offset (error) or how far from centre the line is                  | Alex                        | 18/5         |                  |
| 19/5           | Code the main function for core                                           | Ev                          | 20/5         | Skeleton 17/5    |
| 19/5           | Tune basic movements in relation to the offset                            | Alex                        | 20/5         |                  |
| 21/5           | Create the recovery system (when the line is lost)                        | Ev                          | 22/5         | Skeleton 17/5    |
| 21/5           | Tune and test recovery system                                             | Alex                        | 23/5         |                  |
| 24/5           | Test the core method                                                      | Alex                        | 25/5         |                  |
| 23/5           | Add red colour detection and switch to completion method                  | Anthony                     | 25/5         |                  |


## Completion
| **Start Date** | **Task Description**                                                   | **Responsible Team Member** | **End Date** | **Outcome** |
| -------------- | ---------------------------------------------------------------------- | --------------------------- | ------------ | ----------- |
| 23/5           | Create a method to detect an intersection                              | Ev                          | 25/5         |             |
| 25/5           | Develop response to an intersection being detected (turning movements) | Ev                          | 27/5         |             |
| 26/5           | Code the main function for completion                                  | Ev                          | 27/5         |             |
| 25/5           | Tune and test intersection method                                      | Alex                        | 26/5         |             |
| 26/5           | Test the completion method                                             | Alex                        | 27/5         |             |
| 27/5           | Add blue colour detection and switch to challenge method               | Anthony                     | 29/5         |             |

## Challenge
| **Start Date** | **Task Description**                                        | **Responsible Team Member** | **End Date** | **Outcome** |
| -------------- | ----------------------------------------------------------- | --------------------------- | ------------ | ----------- |
| 27/5           | Develop a turn counter and methodology for turning          | Ev                          | 31/5         |             |
| 30/5           | Add green colour detection for the end of challenge         | Anthony                     | 1/6          |             |
| 31/5           | Tune any further movements as required                      | Alex                        | 2/6          |             |
| 31/5           | Extensive testing from beginning to end (core to challenge) | Alex                        | 2/6          |             |
| 31/5           | Fix any bugs from testing                                   | Alex                        | 2/6          |             |


# Default

## Getting started

To make it easy for you to get started with GitLab, here's a list of recommended next steps.

Already a pro? Just edit this README.md and make it your own. Want to make it easy? [Use the template at the bottom](#editing-this-readme)!



## Add your files

- [ ] [Create](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#create-a-file) or [upload](https://docs.gitlab.com/ee/user/project/repository/web_editor.html#upload-a-file) files
- [ ] [Add files using the command line](https://docs.gitlab.com/ee/gitlab-basics/add-file.html#add-a-file-using-the-command-line) or push an existing Git repository with the following command:

```
cd existing_repo
git remote add origin https://gitlab.ecs.vuw.ac.nz/Team16/avc.git
git branch -M main
git push -uf origin main
```

## Integrate with your tools

- [ ] [Set up project integrations](https://gitlab.ecs.vuw.ac.nz/Team16/avc/-/settings/integrations)

## Collaborate with your team

- [ ] [Invite team members and collaborators](https://docs.gitlab.com/ee/user/project/members/)
- [ ] [Create a new merge request](https://docs.gitlab.com/ee/user/project/merge_requests/creating_merge_requests.html)
- [ ] [Automatically close issues from merge requests](https://docs.gitlab.com/ee/user/project/issues/managing_issues.html#closing-issues-automatically)
- [ ] [Enable merge request approvals](https://docs.gitlab.com/ee/user/project/merge_requests/approvals/)
- [ ] [Automatically merge when pipeline succeeds](https://docs.gitlab.com/ee/user/project/merge_requests/merge_when_pipeline_succeeds.html)

## Test and Deploy

Use the built-in continuous integration in GitLab.

- [ ] [Get started with GitLab CI/CD](https://docs.gitlab.com/ee/ci/quick_start/index.html)
- [ ] [Analyze your code for known vulnerabilities with Static Application Security Testing(SAST)](https://docs.gitlab.com/ee/user/application_security/sast/)
- [ ] [Deploy to Kubernetes, Amazon EC2, or Amazon ECS using Auto Deploy](https://docs.gitlab.com/ee/topics/autodevops/requirements.html)
- [ ] [Use pull-based deployments for improved Kubernetes management](https://docs.gitlab.com/ee/user/clusters/agent/)
- [ ] [Set up protected environments](https://docs.gitlab.com/ee/ci/environments/protected_environments.html)

***

# Editing this README

When you're ready to make this README your own, just edit this file and use the handy template below (or feel free to structure it however you want - this is just a starting point!).  Thank you to [makeareadme.com](https://www.makeareadme.com/) for this template.

## Suggestions for a good README
Every project is different, so consider which of these sections apply to yours. The sections used in the template are suggestions for most open source projects. Also keep in mind that while a README can be too long and detailed, too long is better than too short. If you think your README is too long, consider utilizing another form of documentation rather than cutting out information.

## Name
Choose a self-explaining name for your project.

## Description
Let people know what your project can do specifically. Provide context and add a link to any reference visitors might be unfamiliar with. A list of Features or a Background subsection can also be added here. If there are alternatives to your project, this is a good place to list differentiating factors.

## Badges
On some READMEs, you may see small images that convey metadata, such as whether or not all the tests are passing for the project. You can use Shields to add some to your README. Many services also have instructions for adding a badge.

## Visuals
Depending on what you are making, it can be a good idea to include screenshots or even a video (you'll frequently see GIFs rather than actual videos). Tools like ttygif can help, but check out Asciinema for a more sophisticated method.

## Installation
Within a particular ecosystem, there may be a common way of installing things, such as using Yarn, NuGet, or Homebrew. However, consider the possibility that whoever is reading your README is a novice and would like more guidance. Listing specific steps helps remove ambiguity and gets people to using your project as quickly as possible. If it only runs in a specific context like a particular programming language version or operating system or has dependencies that have to be installed manually, also add a Requirements subsection.

## Usage
Use examples liberally, and show the expected output if you can. It's helpful to have inline the smallest example of usage that you can demonstrate, while providing links to more sophisticated examples if they are too long to reasonably include in the README.

## Support
Tell people where they can go to for help. It can be any combination of an issue tracker, a chat room, an email address, etc.

## Roadmap
If you have ideas for releases in the future, it is a good idea to list them in the README.

## Contributing
State if you are open to contributions and what your requirements are for accepting them.

For people who want to make changes to your project, it's helpful to have some documentation on how to get started. Perhaps there is a script that they should run or some environment variables that they need to set. Make these steps explicit. These instructions could also be useful to your future self.

You can also document commands to lint the code or run tests. These steps help to ensure high code quality and reduce the likelihood that the changes inadvertently break something. Having instructions for running tests is especially helpful if it requires external setup, such as starting a Selenium server for testing in a browser.

## Authors and acknowledgment
Show your appreciation to those who have contributed to the project.

## License
For open source projects, say how it is licensed.

## Project status
If you have run out of energy or time for your project, put a note at the top of the README saying that development has slowed down or stopped completely. Someone may choose to fork your project or volunteer to step in as a maintainer or owner, allowing your project to keep going. You can also make an explicit request for maintainers.
