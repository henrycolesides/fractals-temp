#include "FPToolkit.c"

// Basic point struct
struct point_s 
{
    double x;
    double y;
} typedef point;


struct color_s
{
    double r;
    double g;
    double b;
    double a;
} typedef color;


// Affine transformations
void scale(point * p, double sx, double sy)
{
  p->x *= sx;
  p->y *= sy;
}

void translate(point * p, double sx, double sy)
{
  p->x += sx;
  p->y += sy;
}

void rotate(point * p, double t)
{
  double temp;
  temp  = (p->x * cos(t)) - (p->y * sin(t));
  p->y  = (p->x * sin(t)) + (p->y * cos(t));
  p->x  = temp;
}


// Non-linears
point identity(point * p)
{
    // p->x = p->x
    // p->y = p->y
    return *p;
}

point sinusoidal(point * p)
{
    point r = {sin(p->x), sin(p->y)};
    return r;
}

point spherical(point * p)
{
    point r;
    double x = p->x;
    double y = p->y;
    r.x = x / ((x * x) + (y * y));
    r.y = y / ((x * x) + (y * y));
    return r;
}

point swirl(point * p)
{
    point r;
    double x = p->x;
    double y = p->y;
    double t = (x * x) + (y * y);
    r.x = (x * sin(t)) - (y * cos(t));
    r.y = (x * cos(t)) + (y * sin(t));
    return r;
}

point fisheye(point * p)
{
    point r;
    double s = 2.0 / (sqrt((p->x * p->x) + (p->y * p->y)) + 1);
    r.x = s * p->y;
    r.y = s * p->x;
    return r;
}



static double swidth   = 1000.0;
static double sheight  = 1000.0;


// Point helpers

point add(point p1, point p2)
{
    point p;
    p.x = p1.x + p2.x;
    p.y = p1.y + p2.y;
    return p;
}

void average_color(color * c1, color * c2)
{
    c1->r = (c1->r + c2->r) / 2;
    c1->g = (c1->g + c2->g) / 2;
    c1->b = (c1->b + c2->b) / 2;
}

void accumulate_color(color * c1, color * c2)
{
    c1->r += c2->r;
    c1->g += c2->g;
    c1->b += c2->b;
    ++(c1->a);
}

int main()
{
    size_t elements = swidth * sheight;
    color * pixels = (color *)malloc(elements * sizeof(color));
    for(size_t i = 0; i < elements; ++i)
    {
        pixels[i].r = 0.0;
        pixels[i].g = 0.0;
        pixels[i].b = 0.0;
        pixels[i].a = 0.0;
    }


    G_init_graphics(swidth, sheight);
    G_rgb(1.0, 1.0, 1.0);
    G_clear();
    
    point p = {0.0, 0.0};
    color c = {0.0, 0.0, 0.0, 0.0};
    
    color r1 = {1.0, 0.0, 0.0, 0.0};
    color r2 = {0.0, 0.5, 0.0, 0.0};
    color r3 = {0.0, 0.0, 1.0, 0.0};
    color r4 = {0.5, 0.0, 0.5, 0.0};
    
    int final_x = 0;
    int final_y = 0;
    float min[2] = {swidth, sheight};
    float max[2] = {0, 0};
    double r;

    for(int k = 0; k < 100000000; k++) {
        r = drand48();
        if(r < 0.34)
        {
            scale(&p, 0.33, 0.33);
            p = add(swirl(&p), p);
            average_color(&c, &r2);
        }
        else if(r < 0.67)
        {
            scale(&p, 0.33, 0.33);
            translate(&p, 0.0, 0.5);
            p = add(swirl(&p), p);
            average_color(&c, &r4);
        }
        else
        {
            scale(&p, 0.33, 0.33);
            translate(&p, 0.5, 0.0);
            p = add(swirl(&p), p);
            average_color(&c, &r3);
        }
 //       rotate(&p, 3.14);
//        translate(&p, 0.1, -0.1);
       // if(r < 0.33) {
       //     //rule 1
       //     scale(&p, 0.01 , 0.5) ;
       //     translate(&p, 0 , 0.01) ;
       //     //p = add(swirl(&p), sinusoidal(&p));
       //     p = add(swirl(&p), spherical(&p));
       //     translate(&p, 0.0, 0.0);
       //     average_color(&c, &r2);
       // }
       // else if(r < 0.66) {
       //     //rule 2
       //     rotate(&p, 3.14);
       //     scale(&p, 0.0125 , 0.0125) ;
       //     translate(&p, 0.01 , 0) ;
       //     p = add(p, sinusoidal(&p));
       //     translate(&p, 0.5, 0.7);
       //     average_color(&c, &r1);
       // }
       // else if(r < 1.0) {
       //     //rule 3
       //     scale(&p, 0.01 , 0.1) ;
//     //       p = add(swirl(&p), spherical(&p));
//     //       p = add(p, fisheye(&p));
       //     p = add(spherical(&p), fisheye(&p));
       //     translate(&p, 0.75, 0);
       //     average_color(&c, &r3);
       // }
//      else {
//          //rule 4
//          scale(&p, 0.5 , 0.5) ;
//          translate(&p, 0.25 , 0.25) ;
//          p = add(swirl(&p), spherical(&p));
//          average_color(&c, &r4);
//      }
    //  G_rgb(0,1,0) ;
        final_x = p.x * swidth;
        final_y = p.y * sheight;
        
        if(final_x > max[0]) max[0] = final_x;
        if(final_x < min[0]) min[0] = final_x;
        if(final_y > max[1]) max[1] = final_y;
        if(final_y < min[1]) min[1] = final_y;

        if(final_x < 0)         final_x = 0;
        if(final_x >= swidth)    final_x = swidth - 1;
        if(final_y < 0)         final_y = 0;
        if(final_y >= sheight)    final_y = sheight - 1;
        accumulate_color(pixels + ((final_y * (int)swidth) + final_x), &c);
    }
   
    
    // Auto placer
   // if(max[0] > swidth)
   // {
   //     
   //     
   // }
   
    color current;
    color final;
    for(int j = 0; j < sheight; ++j)
    {
        for(int i = 0; i < swidth; ++i)
        {
            current = pixels[(j * (int)swidth) + i];
            current.r = current.r * (log(current.a) / current.a);// / current.a);
            current.g = current.g * (log(current.a) / current.a);// / current.a);
            current.b = current.b * (log(current.a) / current.a);// / current.a);

            G_rgb(pow(current.r, 1/2.2), pow(current.g, 1/2.2), pow(current.b, 1/2.2));
            //G_rgb(current.r, current.g, current.b);
            G_point(i, j);
        }
    }

    G_wait_key() ;
}
