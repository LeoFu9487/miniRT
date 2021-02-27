how to improve : solve linear_equations in polynominal time(right now it's O(n!))

remember to abandon in parsing when orientaion = (0,0,0)
need to do ambient lighting in math/utils.c, intersect_color
need to think get_new_brightness in math/utils.c 
for intersect_objects, deal with every element in t_intersect *
remember not to use have_intersection_* in intersect_*

todo : utils3.c : point_to_line_distance, cyylinder.c


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
