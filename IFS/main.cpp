
#include "../FPToolkit/FPToolkit.c"

#define WIDTH 800.0
#define HEIGHT 800.0
#define DEGREE_TO_RAD(x) ((x * M_PI) / 180)

using namespace std;




// TODO: this isn't an L-System, this is just to visualize
void fern(double p[2]) {
    double r;

    G_rgb(1, .773, 0.314);
    for (int i = 0; i < 100000 / 2; i++) {
        r = drand48();

        double x = p[0];
        double y = p[1];

        //cout << "(" << x << ", " << y << ")\n)";

        if (r < 0.01) {
            // change color to purple

            p[0] = 0;
            p[1] = 0.16 * y;
        } else if (r < 0.86) {
            // change color to green

            p[0] = 0.85 * x + 0.04 * y;
            p[1] = -0.04 * x + 0.85 * y + 1.6;
        } else if (r < 0.93) {
            // change color to red

            p[0] = 0.2 * x - 0.26 * y;
            p[1] = 0.23 * x + 0.22 * y + 1.6;
        } else {
            // change color to yellow

            p[0] = -0.15 * x + 0.28 * y;
            p[1] = 0.26 * x + 0.24 * y + 0.44;
        }

        p[0] *= .8;
        p[1] *= .8;
        G_point(p[0] * (WIDTH / 15) + 50, p[1] * (HEIGHT / 15) + 30);

    }
}

// TODO: this isn't an L-System, this is just to visualize
void drawSierpinskiTriangle(double p0[2], double p1[2], double p2[2], int depth, bool color) {
    if (depth <= 0) {
        return;
    }
    depth--;

    // "sandy" color
    if(color)
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
    drawSierpinskiTriangle(p0, p3, p5, depth, color);
    drawSierpinskiTriangle(p3, p1, p4, depth, color);
    drawSierpinskiTriangle(p5, p4, p2, depth, color);
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

    // Drawing sun dark orange/red
    G_rgb(1, .2, 0.0);

    //G_fill_circle(150, 200, 100.0);
    G_fill_circle(WIDTH / 2.0, 150, 300.0);

    // Draw sand gradient
    /*
    for(int i = 0; i < HEIGHT / 4.0; ++i) {
        double r = 0.6 + (double) i * drand48();
        double g = 0.3 + (double) i / 2000;
        double b = .01 + (double) i / 2000;
        G_rgb(r, g, b);
        G_line(0, i, WIDTH, i);

    }
     */

    // Draw sand
    double r = 1.0;
    double g = 0.5;
    double b = 0.1;
    for(int i = 0; i < 10000000; ++i) {
        double randomX = drand48();
        double randomY = drand48();
        G_rgb(r, g * randomX, b * randomY);
        G_point(WIDTH * randomX, (HEIGHT  / 4.0) * randomY);
    }



    // calculate the 3 points of the triangle
    double p0[2], p1[2], p2[2];
    p0[0] = WIDTH / 4.0;
    p0[1] = 150;
    p1[0] = WIDTH / 2.0;
    p1[1] = 500;
    p2[0] = WIDTH /  2.0 ;
    p2[1] = 100;


    double q0[2], q1[2], q2[2];

    q0[0] = WIDTH / 2.0;
    q0[1] = 100;

    q1[0] = WIDTH / 2.0;
    q1[1] = 500;

    q2[0] = (WIDTH / 4.0) * 3.0;
    q2[1] = 150;


    double z[2] = { WIDTH / 2.0, 0.0 };


    G_rgb(0.0, 0.0, 0.0);
    drawSierpinskiTriangle(p0, z, q2, 7, false);
    // draw the triangle
    drawSierpinskiTriangle(p0, p1, p2, 7, true);
    drawSierpinskiTriangle(q0, q1, q2, 7, true);

    // Draw shadow

    // Borders
    G_rgb(0.3, 0.2, 0.4);

    // Draw border lines
    for (double i = 0; i < 0.5; i += 0.1) {
        // Left side border
        G_line(p0[0] - i, p0[1], p1[0] - i, p1[1]);

        // Right side border
        G_line(p1[0] - i, p1[1], q2[0] - i, q2[1]);

        // Center border
        G_line(p2[0] - i, p2[1], p1[0] - i, p1[1]);
    }


    G_rgb(0, 0, 0);

    p0[0] = 0.0;
    p0[1] = 0.0;
    fern(p0);



    int key;
    key = G_wait_key(); // pause so user can see results

    G_save_to_bmp_file("l-system.bmp");


    exit(EXIT_SUCCESS);
}