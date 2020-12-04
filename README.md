# CPP_GlutApps
Apps built with GLUT for CSE 165 Intro to OO programming at UCMerced. Includes, Custom Game Called: Fruit Catch, MS Paint, Watered Down Space Invader, and more!




To run these apps, go to linux shell and run the following commands:

Update your apt repositories: sudo apt update

Install freeglut: sudo apt install freeglut3-dev

Install xming (https://sourceforge.net/projects/xming/)

Set display environment variable: echo "export DISPLAY=localhost:0.0" >> ~/.bashrc

Once done, make sure you open xming, and then open linux terminal and run:

make
./glutapp
