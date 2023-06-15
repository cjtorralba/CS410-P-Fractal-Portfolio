#include "../FPToolkit/FPToolkit.c"

#define WIDTH 800.0
#define HEIGHT 800.0

#include <complex.h>
#include <stdio.h>
#include <math.h>

double swidth = 800, sheight = 800;


void julia(double rad, int mlimit) {
    double delta, x, y, xp, yp;
    complex c = (-0.8) + 0.156 * I;
    complex z;
    int reps;

    int divisions = 4;

    delta = 2 * rad / WIDTH;
    y = -rad;
    for (yp = 0; yp < WIDTH; yp++) {
        x = -rad;
        for (xp = 0; xp < WIDTH; xp++) {
            //the julia iteration:
            z = x + y * I;
            for (reps = 0; reps < mlimit; reps++) {
                if (cabs(z) > 2.0) {
                    break;
                }
                z = z * z + c;
            }

            if (reps == mlimit) {
                G_rgb(0.988 + (xp / WIDTH) * 0.471, 0.275 + (xp / WIDTH) * 0.192, 0.667 + (xp / WIDTH) * 0.020);
                G_point(xp, yp + 100);

            }
            x = x + delta;
        }
        y = y + delta;
    }
}


void generateYValues(double yvals[12], double yOffset) {
    // create 10 y values
    for (int i = 0; i < 11; i++) {
        yvals[i] = rand() % 115 + yOffset;
    }

    // close the polygon
    yvals[10] = 0;
    yvals[11] = 0;
}

void generateXValues(double xvals[12]) {
    // create 10 x values between 0 and swidth,
    xvals[0] = 0;
    for (int i = 1; i < 10; i++) {
        xvals[i] = (swidth / 10) * i + rand() % 20;
    }

    // close the polygon
    xvals[10] = swidth * 2;
    xvals[11] = 0;
}

int main(int argc, char **argv) {

    // seed rand with the current time
    srand(time(NULL));

    int swidth, sheight;


    // must do this before you do 'almost' any other graphical tasks
    swidth = WIDTH;
    sheight = HEIGHT;
    G_init_graphics(swidth, sheight);  // interactive graphics

    G_rgb(0, 0, 0);
    G_clear();




    // draw stars throughout
    for (int i = 0; i < 1000; i++) {
        int x = rand() % (int) swidth;
        int y = rand() % (int) sheight;
        G_rgb(1, 1, 0);
        G_point(x, y);
    }

    // draw a moon at the top right using multiple circles of different sizes to create a gradient
    for (int i = 0; i < 50; i++) {
        // change color based on itteration to create a gradient
        G_rgb(1 - (i / 100.0), 1 - (i / 100.0), 1 - (i / 100.0));

        G_fill_circle(700, 700, 50 - i);
    }

    julia(2, 100);

    // change the color to gray
    G_rgb(0.5, 0.5, 0.5);

    // create 10 y values
    double yvals[12];
    double xvals[12];

    for (int i = 200; i > 0; i -= 50) {
        // create 10 x values between 0 and 800 randomly
        generateXValues(xvals);
        generateYValues(yvals, i);
        G_fill_polygon(xvals, yvals, 12);

        // pick a color based on i
        G_rgb(0.5 + (i / 1000.0), 0.5 + (i / 1000.0), 0.5 + (i / 1000.0));
    }


    int key;
    key = G_wait_key(); // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("Demo.bmp");


    exit(EXIT_SUCCESS);
}

