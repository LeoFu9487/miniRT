remember to abandon in parsing when orientaion = (0,0,0) (reconsider parsing)

todo : need to redefine for apple, bonus, create more tests

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

TEST : 
R 1000 1000
A 1.0 255 255 255
c -50.0,0,20 0,0.1,1 70
l 100,50,50 1  255,0,0
l 500,0,0 0.8 0,0,255
sq -50,0,800 0,0,1 700 255,0,255
tr -50,0,800 -550,0,800 -50,500,800 100,100,100
