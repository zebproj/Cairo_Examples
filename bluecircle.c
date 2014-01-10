#include <cairo/cairo.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define HEIGHT	500
#define WIDTH	500

void drawCircle(cairo_t *cr, float x, float y, float size, float color[3]);

void drawCircleGrid(cairo_t *cr, float scale, float d_x, float d_y, float color[3], int its);

void randomizeColor(float *color);

void bananaColor(float *color);

int 
main (int argc, char *argv[])
{
	srand(time(NULL));
	cairo_surface_t *surface;
	cairo_t *cr;
	float color[] = {114/255.0, 160/255.0, 193/255.0};
	float color_alt[3];
	int its = 8;
	int i, j;
	int state;
	int b;
	surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, HEIGHT, WIDTH);
	cr = cairo_create (surface);
	cairo_scale (cr, HEIGHT, WIDTH);

	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
	cairo_paint(cr);
	for(j = 0; j < its; j++){
		for(i = 0; i < its; i++){
			color[0] = 114/255.0;
			color[1] = 160/255.0;
			color[2] = 193/255.0;
			randomizeColor(color);
			//printf("%g %g %g\n", color[0], color[1], color[2]);
			drawCircleGrid(cr, 1.0/its, 1.0 * i/its, 1.0 * j/its, color, 8);	
		}
	}

	cairo_surface_write_to_png (surface, "bluecircle.png");
	cairo_destroy (cr);
	cairo_surface_destroy (surface);

	return 0;
}

void drawCircle(cairo_t *cr, float x, float y, float size, float color[3])
{
	bananaColor(color);
	cairo_arc(cr, x, y, size, 0, 2 * M_PI);
	cairo_set_source_rgb (cr, color[0], color[1], color[2]);
	cairo_fill(cr);
}

void drawCircleGrid(cairo_t *cr, float scale, float d_x, float d_y, float color[3], int its)
{
	int i, j, state;
	for(j = 0; j < its; j++){
		for(i = 0; i < its; i++){
			state = rand() % 2;
			if(state)
			{
				drawCircle(cr, 
						((i + 1)/(its + 1.0) * scale) + d_x,
						((j + 1)/(its + 1.0) * scale) + d_y, 
						1/(its * 4.0) * scale, 
						color);
			}
		}
	}
}

void randomizeColor(float *color)
{
	int i;
	int seed = rand() % 40;
	float r = seed/255.0;
	float tmp;
	for (i = 0; i < 3; i++){
		tmp = *(color + i);
		*(color + i) = tmp + r;		
	}
}
void bananaColor(float *color){
	int s = random() % 128;
	//int s = 0;
	if(s == 0){
		*(color) = 250/255.0;
		*(color + 1) = 231/255.0;
		*(color + 2) = 181/255.0;
	}
}
