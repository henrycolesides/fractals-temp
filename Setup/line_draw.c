// 4/7 Draw line between two points
// (Missed class due to sickness)

#include "FPToolkit.c"

int main()
{
	float width = 600.0;
	float height = 600.0;
	double click1[2], click2[2];
	G_init_graphics(width, height);

	G_rgb(0.8, 0.8, 0.8);
	G_clear();
	
	G_wait_click(click1);

	G_rgb(0.0, 0.0, 0.0);
	G_fill_circle(click1[0], click1[1], 1);

	G_wait_click(click2);
	G_fill_circle(click2[0], click2[1], 1);

	//G_line(click1[0], click1[1], click2[0], click2[1]);
	
	//float start_x, dest_x, start_y, dest_y = 0.0;
        //
	//if(click1[0] < click2[0])
	//{
	//	start_x = click1[0];
	//	start_y = click1[1];
	//	dest_x = click2[0];
	//	dest_y = click2[1];
	//}
	//else
	//{
	//	start_x = click2[0];
	//	start_y = click2[1];
	//	dest_x = click1[0];
	//	dest_y = click1[1];
	//}
        //
	//float slope = (click2[1] - click1[1]) / (click2[0] - click1[0]);
	//printf("%f\n", slope);
        //
	//if(slope >= -1 && slope <= 1)
	//{
	//	for(float i = start_x; i < dest_x; ++i)
	//	{
	//		G_point(i, start_y += slope);
	//	}
	//}
	//else
	//{
	//	if(start_y < dest_y)
	//	{
	//		for(float i = start_y; i < dest_y; ++i)
	//		{
	//			G_point(start_x += (1.0/slope), i);
	//			//printf("%f\n", start_x);
	//		}
	//	}
	//	else	// Doesnt work
	//	{
	//		for(float i = dest_y; i > start_y; --i)
	//		{
	//			G_point(dest_x += (1.0/slope), i);
	//			//printf("%f\n", start_x);
	//		}
	//	}
	//}
        //
	float dx = (click1[0] > click2[0] ? click1[0] - click2[0] : click2[0] - click1[0]);
	float dy = (click1[1] > click2[1] ? click1[1] - click2[1] : click2[1] - click1[1]);
	float hyp = sqrt(pow(dx, 2) + pow(dy, 2));		
	float step = hyp * 0.0001;	
	
	printf("%f: step %f\n", hyp, step);
	G_rgb(0.0, 0.0, 0.0);
	for(float i = 0; i < 1; i+=step)
	{
		G_point(click1[0] + (i * (click2[0] - click1[0])), click1[1] + (i * (click2[1] - click1[1])));
	}
	G_wait_key();
}
