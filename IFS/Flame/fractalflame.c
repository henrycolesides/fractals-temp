#include <math.h>
#include "FPToolkit.c"
//#include "transformations.c"

double[2] scale(double p[2], double * args)
{
  double p2[2] = {p[0] * args[0], p[1] * args[1]};
  return p2;
}

double[2] translate(double p[2], double * args)
{
  double p2[2] = {p[0] + args[0], p[1] + args[1]};
  return p2;
}

double[2] rotate(double p[2], double * args)
{
  double p2[2];
  double temp;

  temp  = p[0]*cos(args[0]) - p[1]*sin(args[0]);
  p2[1] = p[0]*sin(args[0]) + p[1]*cos(args[0]);
  p2[0] = temp;

  return p2;
}


// Non-linears
double[2] identity(double p[2], double * args)
{
    return p;
}



static double swidth = 1000.0;
static double sheight = 1000.0;



// Color struct
// RGB normalized to [0 - 1] 
// alpha is used as a density counter, but can be exported as alpha for formats supporting it
struct color_s {
    double r;
    double g;
    double b;
    double a;
} typedef color_t;

// Color array
static color_t[swidth * sheight] = {{ 0 }};


// Maps r, g, b for PPM format
// [0 - 1] -> [0 - 255]
double denormalize(double v)
{
    int temp = 255 * v;
    if(temp > 255) temp = 255;
    else if(temp < 0) temp = 0;
    return temp;
}


// Scales some color channel based on its density (alpha)
// Logarithmically due to density's power like trend
double log_scale(double v, double alpha)
{
    return v * (log(alpha) / alpha);
}

typedef double[2] (*func_ptr)(double p[2], double * args);

struct function_s
{
    func_ptr * variations;
    func_ptr * pre_transform;
    func_ptr * post_transform;
    double * coefficients;
    int num_variations;
    color_t color;
   
} typedef function_t;


int main(int argc, char * argv[])
{
    std::fstream output;
    char fname[200]; 
    
    if(argc > 2) fname = argv[2];
    else 
    {
        fprintf(stderr, "error: no output name provided!\n");
    }
    
    // First:
    function_t first;
    first.variations = malloc(1 * sizeof(functype));
    first.variations[0] = identity; 

    first.pre_transform = malloc(1 * sizeof(functype));
    first.pre_transform[0] = scale;
    first.color = {1.0, 0.0, 0.0, 0.0};

    // Second:
    function_t second;
    second.variations = malloc(1 * sizeof(functype));
    second.variations[1] = identity; 
    
    second.pre_transform = malloc(2 * sizeof(functype));
    second.pre_transform[0] = scale;
    second.pre_transform[1] = translate;
    second.color = {0.0, 1.0, 0.0, 0.0};

    // Third:
    function_t third;
    third.variations = malloc(1 * sizeof(functype));
    third.variations[1] = identity; 

    third.pre_transform = malloc(2 * sizeof(functype));
    third.pre_transform[0] = scale;
    third.pre_transform[1] = rotate;
    third.color = {0.0, 0.0, 1.0, 0.0};

    // Fourth:
    function_t fourth;
    fourth.variations = malloc(1 * sizeof(functype));
    fourth.variations[1] = identity; 

    fourth.pre_transform = malloc(2 * sizeof(functype));
    fourth.pre_transform[0] = scale;
    fourth.pre_transform[1] = rotate;
    fourth.color = {1.0, 0.0, 1.0, 0.0};

    double scale_args[2] = {0.5, 0.5};

    G_init_graphics(swidth,sheight) ;

    double p[2] = {0.0, 0.0};
    
    int k ;
    double r ;

    for(k=0;k<200000;k++) {

        r = drand48() ;

        if(r < 0.25) {
            //rule 1
            p = first.pre_transform[0](p, scale_args);
            p = first.variations[0](p, NULL);
            G_rgb(first.color.r, first.color.g, first.color.b);
        }
        else if(r < 0.5) {
            //rule 2
            double args[2] = {0.5, 0};

            p = first.pre_transform[0](p, scale_args);
            p = first.pre_transform[1](p, args);
            p = first.variations[0](p, NULL); 
            G_rgb(second.color.r, second.color.g, second.color.b);
        }
        else if(r < 0.75) {
            //rule 3
            double args[2] = {0.0, 0.5};

            p = first.pre_transform[0](p, scale_args);
            p = first.pre_transform[1](p, args);
            p = first.variations[0](p, NULL); 
            G_rgb(third.color.r, third.color.g, third.color.b);
        }
        else {
            //rule 4
            //
            double args[2] = {0.0, 0.5};

            p = first.pre_transform[0](p, scale_args);
            p = first.pre_transform[1](p, args);
            p = first.variations[0](p, NULL); 
            G_rgb(fourth.color.b, fourth.color.g, fourth.color.b);
        }

        //    G_rgb(0,1,0) ;
        G_point(p[0]*swidth , p[1]*sheight) ;
    }

    G_wait_key() ;
    
 //   // Final PPM creation
 //   output.open(fname, std::fstream::out | std::fstream::trunc);    
 //   output << "P3\n" << swidth << ' ' << sheight << "\n255\n";
 //   
 //   for (int j = sheight - 1; j >= 0; --j)
 //   {
 //       for (int i = 0; i < swidth; ++i)
 //       {
 //            
 //       }
 //   }
 //
 //   std::cout << f << "flame done!\n";
 //   output.close();

    if(first.variations) free(first.variations);
    if(first.pre_transform) free(first.pre_transform);
    
    if(second.variations) free(second.variations);
    if(second.pre_transform) free(second.pre_transform);
    
    if(third.variations) free(third.variations);
    if(third.pre_transform) free(third.pre_transform);

    if(fourth.variations) free(fourth.variations);
    if(fourth.pre_transform) free(fourth.pre_transform);
}
