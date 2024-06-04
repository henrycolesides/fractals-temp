#include <complex.h>
#include <stdbool.h>
#include "FPToolkit.c"

double clamp_coord(double v, double i_start, double i_end);
complex complex_coord(double v, double i_start, double i_end, double o_start, double o_end);
bool do_i_diverge(complex p, int iterations);
int main(int argc, char * argv[])
{
    double swidth = 1000.0;
    double sheight = 1000.0;
    double x_translate = 100.0;
    double y_translate = 0.0;
    int iterations = 0;
    if(argc < 2) return 0;
	else iterations = atoi(argv[1]);
	if(iterations > 200) 
	{
		fprintf(stderr, "%d is too large!\nLimit 15\n", iterations);
		return 0;
	}

    G_init_graphics(swidth, sheight);
    G_rgb(0.0, 0.0, 0.0);
    G_clear();

    complex c, p;
    double r;
    double m;

    for(int i = -(swidth); i < (swidth); ++i)
    {
        for(int j = -(swidth); j < (sheight); ++j)
        {
            c = i + j*I;
            r = complex_coord(creal(c), -750.0, 750.0, -2.0, 2.0);
            m = complex_coord(cimag(c), -750.0, 750.0, -2.0, 2.0);
            p = r + m*I;

//            printf("%lf + %lfi\n", r, m);
            if(do_i_diverge(p, iterations))
            {
                G_rgb(0.0, 0.0, 0.8);
            }
            else
            {
                G_rgb(0.0, 0.0, 0.0);
            }
            G_point(clamp_coord(i + (swidth / 2) + x_translate, 0.0, swidth), clamp_coord(j + (sheight / 2) + y_translate, 0.0, sheight));
        }
    }

    G_wait_key();
}

double clamp_coord(double v, double i_start, double i_end)
{
    if(v > i_end) return i_end;
    if(v < i_start) return i_start;
    return v;
}
complex complex_coord(double v, double i_start, double i_end, double o_start, double o_end)
{
    return ((v - i_start) / (i_end - i_start)) * (o_end - o_start) + o_start;
}
bool do_i_diverge(complex p, int iterations)
{    
    // Mandelbrot
    //complex z = 0;
    //complex c = p;
    
    // Julia
    complex z = p;
//    complex c = -0.624 + 0.435*I;
    complex c = -1.037 + 0.17*I;
//    complex c = -0.52 + 0.57*I;
//    complex c = 0.295 + 0.55*I;
    int i = 0;
    bool diverges = false;

    z = z*z + c;
    while(!diverges && i < iterations)
    {
        z = z*z + c;
        if(cabs(z) > 2) diverges = true;
        ++i;
    }

    return diverges;
}
