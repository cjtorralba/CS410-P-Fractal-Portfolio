
#include "../FPToolkit/FPToolkit.c"

#define WIDTH 800.0
#define HEIGHT 800.0

using namespace std;

// TODO: this isn't an L-System, this is just to visualize
void fern(double p[2]) {
	double r;

    for (int i = 0; i < 100000 / 2; i++) {
        r = drand48();

        double x = p[0];
        double y = p[1];

		std::cout << "(" << x << ", " << y << ")\n)";

        if (r < 0.01) {
            // change color to purple
            G_rgb(0.5, 0, 0.5);

            p[0] = 0;
            p[1] = 0.16 * y;
        } else if (r < 0.86) {
            // change color to green
            G_rgb(0, 0.5, 0);

            p[0] = 0.85 * x + 0.04 * y;
            p[1] = -0.04 * x + 0.85 * y + 1.6;
        } else if (r < 0.93) {
            // change color to red
            G_rgb(0.5, 0, 0);

            p[0] = 0.2 * x - 0.26 * y;
            p[1] = 0.23 * x + 0.22 * y + 1.6;
        } else {
            // change color to yellow
            G_rgb(0.5, 0.5, 0);

            p[0] = -0.15 * x + 0.28 * y;
            p[1] = 0.26 * x + 0.24 * y + 0.44;
        }

        // draw p
        G_point(p[0] * (swidth / 15) + swidth/2, p[1] * (sheight / 15));
    }
}

// TODO: this isn't an L-System, this is just to visualize
void drawSierpinskiTriangle(double p0[2], double p1[2], double p2[2], int depth) {
	if (depth <= 0) {
		return;
	}
	depth--;

	// "sandy" color
	G_rgb(1.0 - depth / 10.0, 1.0 - depth / 10.0, 0.0);

	// draw the triangle
	G_fill_triangle(p0[0], p0[1], p1[0], p1[1], p2[0], p2[1]);

	// calculate the other 3 points
	double p3[2], p4[2], p5[2];
	p3[0] = p0[0] + (p1[0] - p0[0]) / 2;
	p3[1] = p0[1] + (p1[1] - p0[1]) / 2;
	p4[0] = p1[0] + (p2[0] - p1[0]) / 2;
	p4[1] = p1[1] + (p2[1] - p1[1]) / 2;
	p5[0] = p2[0] + (p0[0] - p2[0]) / 2;
	p5[1] = p2[1] + (p0[1] - p2[1]) / 2;

	// draw the other 3 triangles
	drawSierpinskiTriangle(p0, p3, p5, depth);
	drawSierpinskiTriangle(p3, p1, p4, depth);
	drawSierpinskiTriangle(p5, p4, p2, depth);
}

int main(int argc, char **argv) {


    int swidth, sheight;


    // must do this before you do 'almost' any other graphical tasks
    swidth = WIDTH;
    sheight = HEIGHT;
    G_init_graphics(swidth, sheight);  // interactive graphics

    G_rgb(0.3, 0.3, 0.3); // dark gray
    G_clear();


	G_rgb(1, 0, 0);

	// Light blue sky gradient
	for(int i = 0; i < HEIGHT; i++) {
		double r = 0.5 + (double) i / 2000;
		double g = 0.7 + (double) i / 2000;
		double b = 1.0;
		G_rgb(r, g, b);
		G_line(0, 800 - i, 800, 800 - i);
	}



	// calculate the 3 points of the triangle
	double p0[2], p1[2], p2[2];
	p0[0] = swidth / 2 - (sheight - 400) / sqrt(3);
	p0[1] = 300;
	p1[0] = swidth / 2 + (sheight - 400) / sqrt(3);
	p1[1] = 300;
	p2[0] = swidth / 2;
	p2[1] = sheight / 2 + (swidth * sqrt(3) / 6);

	

	
	// draw the triangle
	drawSierpinskiTriangle(p0, p1, p2, 7);


	G_rgb(0, 0, 0);

	p[0] = 0;
	p[1] = 0;
	fern(p0);

	// // draw a circle on each p0, p1, p2
	// // red color
	// G_rgb(1, 0, 0);
	// G_fill_circle(p0[0], p0[1], 5);
	// // green color
	// G_rgb(0, 1, 0);
	// G_fill_circle(p1[0], p1[1], 5);
	// // blue color
	// G_rgb(0, 0, 1);
	// G_fill_circle(p2[0], p2[1], 5);



    int key;
    key = G_wait_key(); // pause so user can see results

    G_save_to_bmp_file("l-system.bmp");


    exit(EXIT_SUCCESS);
}