2D Particle Flocling system\
Class particle has a .h and a .cpp file. There is a points.cpp file which has the main functions. In the makefile, $program_name should have particle.o and points.o ($(PROGRAM_NAME): particle.o points.o).\
Additional Implemented Features:
1. Inertia only for left mouse button.
2. When 'l'(Small L) is pressed, the points life starts. Life spans are randomized and they will die depending on their life span. A new particle will be created after a particle dies. Inertia does not exist when points are alive :D.
3. Passive mouse mode which changes the partcles colour to red whenever the mouse hits a particle.
4. When 's' is pressed, x and y positions of particles close to mouse will be swaped.

**Instructions on how to operate the program:**\
Whenever mouse hits a particle, its color changes to red.\
Left mouse button attracts particles\
Right mouse button repels particle\
Key = a -> Adds a new particle at the current cursor location.\
Key = d -> Removes the particle close to the cursor\
Key = +/- -> Increases/decrease the range\
Key = up/down -> increase/decrease the speed\
Key = space bar -> Stops/runs the animation\
Key = r -> reset\
Key = q or Escape -> exit\
Key = l -> starts particle life span\
key = s -> Swaps x and y of a particle close to the cursor.\
Refrence for text on the screen:\
https://www.youtube.com/watch?v=elE__Nouv54
 


