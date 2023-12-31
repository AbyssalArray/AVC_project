# Project Analysis

## What went according to plan? What did not?
Something that went to plan was that everyone so far has chipped in and completed a significant chunk of their designated work. This has allowed us as a group to progress at a rate that is on track with how we planned it. Although specific aspects of the plan have been completed ahead or behind schedule, the time taken on tasks has balanced itself over the progression of the project.

Something that was unexpected was that our Software Architect completed most of his allocated tasks well ahead of schedule. This could be attributed to the Project Manager assigning tasks too conservatively, or the Software Architect working extremely quickly. Either way, the bulk of the code was written in a small amount of time. Therefore, an improvement we could have made in the planning process could have been to allocate more tasks to each individual, or give them less time to ensure the project finishes on time.

Something else that was not according to plan was that we did not expect the code to not compile for so long. This made our Project Designer's role difficult, as he could not test the code easily if it would not run. The reason for this problem was that the nature of the project meant that the code was difficult to get started, as there were a lot of constants and methods that needed to be set up and working before the robot could even move, or travel along the black line. To remedy this, we could have had more detailed planning, including some more pseudocode or flow charts in the design process to make the code compile quicker.
## What are the bottlenecks? What is slowing development?
The main bottleneck was the fact that the code could not be compiled. This is because there were missing methods that needed developing that were included in some of the code. We could get around this by commenting some of them out, or setting a variable to an initial arbitrary value, but this was not always possible. This was particularly problematic for the Project Designer, who needed this to progress with testing.

Our Software Architect was also assigned not enough work in the beginning, which meant he had finished most of the tasks that he was responsible for before other essential aspects of the program were completed. This was a significant bottleneck as he felt like he could do more work, but there was none assigned for him to do. He was also unsure if any of his code would work, as it was difficult to test when the program did not compile.

## Team recommendations on how to advance the project
The recommendation from the team is to ensure more detailed planning for future methods. This would make it easier to develop the code and have a clearer idea of what is required of each team member. So far, sometimes team members have been unsure about what to progress with as the plan was not specific enough, or they got confused as to what method they were developing. This lead to aspects of the project lagging behind. To avoid this, we need to advance the project keeping in mind this plan and potentially extending it when required.

There has also been discussion about the decision of whether to use classes and separate files. This would help to chunk the code up and make it easier to work with. Whether there are enough methods to separate into multiple classes, however, could mean there is no need to do so.

Finally, an important thing for each team member to advance the project is sticking to deadlines. If one cannot be met due to something unexpected occuring, communication is key to the success of the project. With this is mind, although we are on track according to our plan, we believe we are slightly behind schedule, since the tasks were allocated conservatively time-wise. But, we should be able to make this time up quickly over the coming days as we traverse deeper into the plan, and get on to completion and challenge as soon as possible.

# Planning

## Core
| **Start Date** | **Task Description**                                                      | **Responsible Team Member** | **End Date** | **Outcome as of 22/5** |
| -------------- | ------------------------------------------------------------------------- | --------------------------- | ------------ | ---------------------- |
| 13/5           | Construct skeleton code for the main() method                             | Ev                          | 15/5         | Completed 15/5         |
| 13/5           | Create UML Class diagrams                                                 | Anthony                     | 15/5         | Completed\* 19/5       |
| 14/5           | Set up classes for Hardware etc. using diagrams                           | Anthony                     | 15/5         | Completed\* 19/5       |
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

\* - Finished late
