usage :

1.

./miniRt <scene.rt> --save 

will save the picture as a bmp file in the repository images

2.

./miniRT <scene.rt> 
will open a window
press space to start or change a camera

press s for stereoecopy (red green glasses)

press w for wave effect

press r,g,b to turn on or turn off the red,green,blue filter respectively

features : the invalid negative number will possibly be treated as a positive number to assure that the program will be applicable

bonus objets :

Cube :

cu -50,0,800	500	255,255,255

identifier : cu
x,y,z coordinate for the center point : -50,0,500
side size : 500
R,G,B colors in range [0,255] : 255,255,255

Cone :

co ... the rest is like cylinder

identifier : co

Pyramid :

py -50,0,800	0,0,1	300	700	255,0,255

identifier : py

x,y,z coordinate for the center point of the bottom square : -50,0,800

3d normalized orientation vector. In range [-1,1] for each x,y,z axis : 0,0,1

side size : 300

height : 700

R,G,B colors in range [0,255] : 255,0,255

flashlight (parallel light)

fl 0,500,-100 0,0,1 1.0 50 255,255,255

identifier : fl

coordinate : 0,500,-100

orientation (x,y,z) in range [0,1] : 0,0,1

brightness in range [0,1] : 1.0

diameter : 50

color (r,g,b) in range [0,255] : 255,255,255
