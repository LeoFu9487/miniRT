remember to abandon in parsing when orientaion = (0,0,0)

todo : new to redefine for apple

usage :

1.

./miniRt <scene.rt> --save 

will save the picture as a bmp file

2.

./miniRT <scene.rt> 
will open a window
press space to start or change a camera


TEST : 
R 1000 1000
A 1.0 255 255 255
c -50.0,0,20 0,0.1,1 70
l 100,50,50 1  255,0,0
l 500,0,0 0.8 0,0,255
sq -50,0,800 0,0,1 700 255,0,255
tr -50,0,800 -550,0,800 -50,500,800 100,100,100
