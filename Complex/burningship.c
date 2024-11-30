#include <complex.h>
#include <stdbool.h>
#include "FPToolkit.c"

double clamp_coord(double v, double i_start, double i_end);
complex complex_coord(double v, double i_start, double i_end, double o_start, double o_end);
bool do_i_diverge(complex p, int iterations, int * num_ptr);
int main(int argc, char * argv[])
{
    double swidth = 1000.0;
    double sheight = 1000.0;

    //double x_translate = 100.0;
    //double y_translate = -100.0;
    
    double x_translate = 0.0;
    double y_translate = -850.0;
   
    int iterations = 0;
    if(argc < 2) return 0;
	else iterations = atoi(argv[1]);
	if(iterations > 2000) 
	{
		fprintf(stderr, "%d is too large!\nLimit 200\n", iterations);
		return 0;
	}

    G_init_graphics(swidth, sheight);
    G_rgb(0.0, 0.0, 0.0);
    G_clear();

    char fname[200];

    double magnification = 1.5;
    double click[2] = {0.0, 0.0};
    
    double cx_range[2] = {-2.0, 2.0};
    double cy_range[2] = {-2.0, 2.0};
    
    //double cx_range[2] = {-1.8, -1.7};
    //double cy_range[2] = {-0.085, 0.0149};

    int count = 0;
    while(1)
    {
        count++;
        sprintf(fname, "ship%02d.ppm", count);

        // Draw loop:
        complex c, p;
        double r;
        double m;

        double min_m = 10000.0;
        double max_m = -10000.0; 
        int num_iterations = 0;

        for(int i = 0; i < (swidth); ++i)
        {
            for(int j = 0; j < (sheight); ++j)
            {
                c = i + j*I;
                //r = complex_coord(creal(c), -750.0, 750.0, -2.0, 2.0);
                //m = complex_coord(cimag(c), -750.0, 750.0, -2.0, 2.0);
                
                //r = complex_coord(creal(c), 0.0, swidth, -2.0, 2.0);
                //m = complex_coord(cimag(c), 0.0, sheight, -2.0, 2.0);

                // Base ship:
                r = complex_coord(creal(c), 0.0, swidth, cx_range[0], cx_range[1]);
                m = complex_coord(cimag(c), 0.0, sheight, cy_range[1], cy_range[0]);

                // Cool ship! 
                //r = complex_coord(creal(c), 0.0, (swidth), -1.8, -1.7);
                //////m = complex_coord(cimag(c) + y_translate, 0.0, (sheight), 0.0, 0.1);
                //m = complex_coord(cimag(c), 0.0, (sheight), 0.0149, -0.085);

                if(m < min_m) min_m = m;
                if(m > max_m) max_m = m;

                p = r + m*I;

//                printf("%lf + %lfi\n", r, m);
//
                num_iterations = 0;
                if(do_i_diverge(p, iterations, &num_iterations))
                {
                    G_rgb(0.0, 0.0, 0.8 * complex_coord(num_iterations, 0.0, iterations, 0.0, 1.0));
                }
                else
                {
                    G_rgb(0.0, 0.0, 0.0);
                }
                //G_point(clamp_coord(i + (swidth / 2) + x_translate, 0.0, swidth), clamp_coord(-j + (sheight / 2) + y_translate, 0.0, sheight));
                //G_point(clamp_coord(i, 0.0, swidth), clamp_coord(-j + sheight, 0.0, sheight));
                G_point(clamp_coord(i, 0.0, swidth), clamp_coord(j, 0.0, sheight));
            }
        }

        G_save_to_bmp_file(fname);
        G_wait_click(click);
        click[0] = complex_coord(click[0], 0.0, swidth, cx_range[0], cx_range[1]);
        click[1] = complex_coord(click[1], 0.0, sheight, cy_range[1], cy_range[0]);

        double range1 = (fabs(cx_range[1] - cx_range[0])) / magnification;
        double range2 = (fabs(cy_range[0] - cy_range[1])) / magnification;
        cx_range[0] = click[0] - (range1 / 2.0);
        cx_range[1] = click[0] + (range1 / 2.0);
        cy_range[0] = click[1] - (range2 / 2.0);
        cy_range[1] = click[1] + (range2 / 2.0);

        //cx_range[0] = click[0] + ((cx_range[0] < 0 ? cx_range[0] : -cx_range[0]) / magnification);
        //cx_range[1] = click[0] + ((cx_range[1] > 0 ? cx_range[1] : -cx_range[1]) / magnification);
        //cy_range[0] = click[1] + ((cy_range[0] < 0 ? cy_range[0] : -cy_range[0]) / magnification);
        //cy_range[1] = click[1] + ((cy_range[1] > 0 ? cy_range[1] : -cy_range[1]) / magnification);
        //printf("Click: %lf, %lf\nCX Range: %lf, %lf\nCY Range %lf, %lf\n", click[0], click[1], cx_range[0], cx_range[1], cy_range[0], cy_range[1]);
        printf("X range: %lf, Y range: %lf\n", range1, range2);
    }
    //printf("Complex y min: %lf, Complex y max: %lf\n", min_m, max_m);
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


bool do_i_diverge(complex p, int iterations, int * num_ptr)
{   
    // Mandelbrot
    complex z = 0;
    complex c = p;
    
    // Julia
    //complex z = p;
//  //  complex c = -0.624 + 0.435*I;
    //complex c = -1.037 + 0.17*I;
//  //  complex c = -0.52 + 0.57*I;
//  //  complex c = 0.295 + 0.55*I;
    int i = 0;
    bool diverges = false;

    //z = z*z + c;
    //while(!diverges && i < iterations)
    //{
    //    z = z*z + c;
    //    if(cabs(z) > 2) diverges = true;
    //    ++i;
    //}
    
    // Burning ship

    z = fabs(creal(z)) + fabs(cimag(z))*I;
    z = z*z + c;
    while(!diverges && i < iterations)
    {
        z = fabs(creal(z)) + fabs(cimag(z))*I;
        z = z*z + c;
        
        ++(*num_ptr);
        if(cabs(z) > 2) diverges = true;
        ++i;
    }

    return diverges;
}
