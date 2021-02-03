#include <stdio.h>
typedef enum
{
	a,
	b,
	c
}type;

int my_int_func(int x)
{
    printf( "%d\n", x );
    return (1);
}

int haha(int x)
{
	printf("!! %d\n", x);
	return (1);
}

void	assigned(void **f)
{
	f[0] = &my_int_func;
	f[1] = &haha;
}
 
int main()
{

	int	(*func[10])(int);
	assigned((void**)func);
	func[0](123);
	func[1](c);
    /* call my_int_func (note that you do not need to write (*foo)(2) ) */
    //foo( 2 );
    /* but if you want to, you may */
    //(*foo)( 2 );
 
    return 0;
}
