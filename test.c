// Test for graphics setup

#include "FPToolkit.c"

int main()
{
	G_init_graphics(1280, 720);	// Setup window w,h

	G_rgb(0.0, 0.0, 0.0);		// Change color to rgb normalized 0, 0, 0 (black)
	G_clear();			// Draw entire window to set color
	
	G_wait_key();
}
