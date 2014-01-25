#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#define HEIGHT 500
#define WIDTH 500

void hex2float(int color, float *colorSpace); /*converts hex code to color for cairo */
void drawGen(cairo_t *cr, int size, int its, int current);
void set_color(cairo_t *cr, int color);

int
main (int argc, char *argv[])
{
	cairo_surface_t *surface;
	cairo_t *cr;

	surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, HEIGHT, WIDTH);
	cr = cairo_create (surface);
	/* Examples are in 1.0 x 1.0 coordinate space */

	/* Drawing code goes here */
	int c1 = 0x6D9BC3; /*Cerulean Frost */
	int c2 = 0xFFFFFF;
	set_color(cr, c1);
	cairo_paint(cr);
	set_color(cr, c2);
	cairo_set_line_width (cr, 1);
	cairo_move_to(cr, 50, HEIGHT - 140);
	int its = 5;
	int width = 400;
	drawGen(cr, width, its, 1);
	cairo_rotate(cr, (-120 * M_PI)/180.0);
	drawGen(cr, width, its, 1);
	cairo_rotate(cr, (-120 * M_PI)/180.0);
	drawGen(cr, width, its, 1);
	cairo_fill(cr);

	/* Write output and clean up */
	cairo_surface_write_to_png (surface, "koch.png");
	cairo_destroy (cr);
	cairo_surface_destroy (surface);

	return 0;
}
void drawGen(cairo_t *cr, int size, int its, int current)
{
	float length = size / pow(3, current);
	if(its == 1){
	cairo_rel_line_to(cr, length, 0);
	cairo_rotate(cr, (60* M_PI)/180.0);
	cairo_rel_line_to(cr, length, 0);
	cairo_rotate(cr, (-120* M_PI)/180.0);
	cairo_rel_line_to(cr, length, 0);
	cairo_rotate(cr, (60* M_PI)/180.0);
	cairo_rel_line_to(cr, length, 0);
	}else{
	drawGen(cr, size, its - 1, current + 1);
	cairo_rotate(cr, (60* M_PI)/180.0);
	drawGen(cr, size, its - 1, current + 1);
	cairo_rotate(cr, (-120* M_PI)/180.0);
	drawGen(cr, size, its - 1, current + 1);
	cairo_rotate(cr, (60* M_PI)/180.0);
	drawGen(cr, size, its - 1, current + 1);
	}

}

void hex2float(int color, float *colorSpace)
{
	int r = color >> 0x10;
	int g = color - (r << 0x10) >> 0x8;
	int b = color - ((r << 0x10) + (g << 0x8));

	*(colorSpace) = r/255.0;
	*(colorSpace + 1) = g/255.0;
	*(colorSpace + 2) = b/255.0;
}
void set_color(cairo_t *cr, int color)
{
	float cs[3];
	hex2float(color, cs);
	cairo_set_source_rgb (cr, cs[0], cs[1], cs[2]);
}
