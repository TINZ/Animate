INTRODUCTION

In 1999, I completed a university project on the Emergent Properties of Multi-Agent Systems. This repository is all of the code for a Windows C++ multi-agent simulation system that I delivered for that project which you are free to use. I have selected the CCO attribution so you don't have to attribute me, but I would always be delighted to know if this code has been used anywhere, as it was once a great passion of mine.

The project won the Addison Wesley Longman Prize for the best undergraduate project in all of the computer sciences at Essex University in 1999. It also enabled me to obtain a 1st class degree in Computer Science (Artificial Intelligence) from Essex, as it was part of my undergraduate degree work.

The main reason why I supply the code is because the simulator may have been one of the first of its kind to use a form of vector field pathfinding to allow agents to navigate their dynamic shared environment within a "gamified" graphical simulator. That is not a claim, so please focus on the "may be" of that statement. I state this as I have gathered that vector fields did not enter the gaming world until the early 2000s and my project completed in 1999. The solution that I created avoids the limitation of heuristics, so it always knows whether a path exists or not. The pathfinding solution never gets stuck and it is very fast at generating paths because it uses some crafty techniques to post potential "gradient field" values to follow up on onto a memory stack using address arithmetic to reduce the number of CPU cycles.

THE CODE

The "Resources" folder includes images for the application. All files that I originally used to compile this application using Visual Studio in 1999 are included. However, these files have never been used to generate a Visual Studio project since 1999, so some work is required to get them into a modern project structure.

The "Release" folder includes a compiled version, together with the two .dll files that are required to be present within the same folder as the .exe application when the application is executed. I do not have time to provide full instructions on the operation, but within this README I have provided a sample execution of some scenarios you can run and some other tips to get you started.

DOCUMENTATION

The "Documents" folder includes my original report, which includes discussion on the experiemnts I ran and my findings. It also includes other materials related to the project.

Please note that whilst I reference A* search in my report, I do not actually implement A* search, but something different. I wasn't even sure what to call it at the time as I was a student and inexperienced. However, it is a very fascinating implementation of a vector field style pathfinding solution (I only found out about vector fields in 2025, as I don't work in coding) which avoids the calamities when paths are not possible. You cannot include spaces in the environment that might be accessible if an obstacle is removed. You can only work with accessible space and obstacles, not accessible space that is not accessible within obstacles. These limitations were necessary to simplify the simulation, but could be altered for more broader applications with further coding. Thus, if the search space is accesible, the agents will always find optimal paths and never get stuck looking for a path.

EXAMPLE USAGE

This example is to run a simulation scenario for basic mining.

1. Run Animate.exe in Windows within a folder that also includes the two DLL files, all of which are included in the "Release" folder.
2. Click on the button at the bottom which is a pencil over a grid to open the Map Editor dialog window.
3. Select the "Mineral" option in Map Objects and Functions, then click anywhere in the blue space to drop a mineral.
4. Select the "Set Mineral / Ore value" option and then click the button with a di on it to randomise the mineral value.
6. Now click "Home" and click on a free space to set the home base, some distance apart from the mineral.
7. Now click the save map button indicated by an arrow pointing to a floppy disk, give the map a name and select the "Save" button, then close the Map Editor window or select the "OK" button.
8. Ensure "Scenario Type" is set to "Basic Mining".
9. Click the button which has an arrow above a rectangle with three other rectangles inside it to start the simulation. Select "Ok" to proceed when asked.
10. The agent will slowly move towards the mineral, collect ore and deposit ore at the home base. The simulation will end after 100 turns.
11. You can speed up and slow down the simulation by dragging the slider and you can end the simulation by clicking the button that looks like the start simulation button but the arrow head is a square.

There are many other settings that you can experiment with and also different scenarios. You should read the documents to understand what sort of setup is required for other experiments. Don't just disregard the capabilities of the simulator with random tries, as setup is important in some situations.

HELP

I cannot provide help or instruction on this code to compile it or modify it, but feel free to get in contact if you have questions and I will do my best to help. Please remember though that I left this field 26 years ago (2025), so my memory will be rather fuzzy. I was also unable to find work in C++, so I don't remember it that well today.

ABOUT ME

My name is Paul Tinsley and I live on the island of Guernsey in the British Channel Islands. I had a career partly in software engineering, mostly creating thin-client intranets and some web facing sites too, but I have also spent many years in lots of other fields. I currently consult occasionally as a business anaylst. I have posted my project code here to ensure it isn't lost, as I was very proud of it at the time I created it and it is a fascinating little simulator.
