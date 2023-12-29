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
| **Start Date** | **Task Description**                                                      | **Responsible Team Member** | **End Date** | **Outcome as of 22/5** |
| -------------- | ------------------------------------------------------------------------- | --------------------------- | ------------ | ---------------------- |
| 13/5           | Construct skeleton code for the main() method                             | Ev                          | 15/5         | Completed 15/5         |
| 13/5           | Create UML Class diagrams                                                 | Anthony                     | 15/5         | Completed 19/5         |
| 14/5           | Set up classes for Hardware etc. using diagrams                           | Anthony                     | 15/5         | Completed 19/5         |
| 14/5           | Create constants                                                          | Alex                        | 15/5         | Add as we go           |
| 13/5           | Develop code for basic movements (forward, backward, turn left and right) | Ev                          | 18/5         | Completed 17/5         |
| 16/5           | Develop method to detect line using the robot camera                      | Alex                        | 18/5         | Completed\* 22/5       |
| 16/5           | Detect offset (error) or how far from centre the line is                  | Alex                        | 18/5         | Completed\* 22/5       |
| 19/5           | Code the main function for core                                           | Ev                          | 20/5         | Skeleton 17/5          |
| 19/5           | Tune basic movements in relation to the offset                            | Alex                        | 20/5         | \*                     |
| 21/5           | Create the recovery system (when the line is lost)                        | Ev                          | 22/5         | Skeleton 17/5          |
| 21/5           | Tune and test recovery system                                             | Alex                        | 23/5         | \*                     |
| 24/5           | Test the core method                                                      | Alex                        | 25/5         |                        |
| 23/5           | Add red colour detection and switch to completion method                  | Anthony                     | 25/5         | Completed 22/5         |


## Completion
| **Start Date** | **Task Description**                                                   | **Responsible Team Member** | **End Date** | **Outcome as of 22/5** |
| -------------- | ---------------------------------------------------------------------- | --------------------------- | ------------ | ---------------------- |
| 23/5           | Create a method to detect an intersection                              | Ev                          | 25/5         |                        |
| 25/5           | Develop response to an intersection being detected (turning movements) | Ev                          | 27/5         |                        |
| 26/5           | Code the main function for completion                                  | Ev                          | 27/5         |                        |
| 25/5           | Tune and test intersection method                                      | Alex                        | 26/5         |                        |
| 26/5           | Test the completion method                                             | Alex                        | 27/5         |                        |
| 27/5           | Add blue colour detection and switch to challenge method               | Anthony                     | 29/5         | Completed 22/5         |

## Challenge
| **Start Date** | **Task Description**                                        | **Responsible Team Member** | **End Date** | **Outcome as of 22/5** |
| -------------- | ----------------------------------------------------------- | --------------------------- | ------------ | ---------------------- |
| 27/5           | Develop a turn counter and methodology for turning          | Ev                          | 31/5         |                        |
| 30/5           | Add green colour detection for the end of challenge         | Anthony                     | 1/6          | Completed 22/5         |
| 31/5           | Tune any further movements as required                      | Alex                        | 2/6          |                        |
| 31/5           | Extensive testing from beginning to end (core to challenge) | Alex                        | 2/6          |                        |
| 31/5           | Fix any bugs from testing                                   | Alex                        | 2/6          |                        |


