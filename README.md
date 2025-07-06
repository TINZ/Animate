INTRODUCTION

In 1999, I completed a university project on the Emergent Properties of Multi-Agent Systems. This repository is all of the code for a Windows C++ multi-agent simulation system that I delivered for that project which you are free to use. I have selected the CCO attribution so you don't have to attribute me, but I would always be delighted to know if this code has been used anywhere, as it was once a great passion of mine.

The project won the Addison Wesley Longman Prize for the best undergraduate project in all of the computer sciences at Essex University in 1999. It also enabled me to obtain a 1st class degree in Computer Science (Artificial Intelligence) from Essex, as it was part of my undergraduate degree work.

The main reason why I supply the code is because the simulator may have been one of the first of its kind to use a form of vector field pathfinding to allow agents to navigate their dynamic shared environment within a "gamified" simulator. The solution that I created avoids the limitation of heuristics, so it always knows whether a path exists or not. The pathfinding solution never gets stuck and it is very fast at generating paths because it uses some crafty techniques to post potential gradient field values to follow up on onto a memory stack using address arithmetic to reduce the number of CPU cycles.

THE CODE

The "Resources" folder includes images for the application. All files that I originally used to compile this application using Visual Studio in 1999 are included. However, these files have never been used to generate a Visual Studio project since 1999, so some work is required to get them into a modern project structure.

The "Release" folder includes a compiled version, together with the two .dll files that are required to be present within the same folder as the .exe application when the application is executed. I do not have time to provide full instructions on the operation, but within this README I have provided a sample execution of some scenarios you can run and some other tips to get you started.

The "Documents" folder includes my original report, which includes discussion on the experiemnts I ran and my findings. It also includes other materials related to the project. Please note that whilst I reference A* search in my report, I do not actually implement A* search, but something different. I wasn't even sure what to call it at the time as I was a student and inexperienced. However, it is a very fascinating implementation of a vector field style pathfinding solution which avoids the calamities when paths are not possible.

** Work in progress - more text to follow **
