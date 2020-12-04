# CPP_GlutApps
Apps built with FreeGlu (http://freeglut.sourceforge.net/) for CSE 165 Intro to OO programming at UCMerced.

Includes: 
  - Shiv's Fruit Catch: Custom Game built by Shivneel Chand
  - Simple Clone of MS Paint
  - Watered Down Space Invader (An object controlled by the player that can shoot projectiles at an enemy)

# Installation Instructions

## Windows Users

This project can only run in your Linux subsystem (Ubuntu Shell), not natively in Windows.

- Update your apt repositories: `sudo apt update`
- Install freeglut: `sudo apt install freeglut3-dev`
- Install xming (https://sourceforge.net/projects/xming/)
- Set display environment variable: `echo "export DISPLAY=localhost:0.0" >> ~/.bashrc`
- Relaunch your VS Code

## Linux Users

If you are running Linux natively (not the Ubuntu Shell under Windows)

- Update your apt repositories: `sudo apt update`
- Install freeglut: `sudo apt install freeglut3-dev`

## Mac Users

On a Mac, the project just works

# Running the App

After all dependencies above have been installed, navigate to the project folder and:

- Compile: `make`

- Run: `./glutapp`
