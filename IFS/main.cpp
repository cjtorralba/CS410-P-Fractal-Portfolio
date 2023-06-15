
#include "../FPToolkit/FPToolkit.c"

#define WIDTH 800.0
#define HEIGHT 800.0
#define DEGREE_TO_RAD(x) ((x * M_PI) / 180)

using namespace std;

double points[2] = {0.0, 0.0};


/**
 * Scales our global value points by both scale factors.
 * @param scaleFactorX
 * @param scaleFactorY
 */
void scale(double scaleFactorX, double scaleFactorY) {
    points[0] *= scaleFactorX;
    points[1] *= scaleFactorY;
}

/**
 * Translates our global value points by translation factors
 * @param transFactorX
 * @param transFactorY
 */
void translate(double transFactorX, double transFactorY) {
    points[0] += transFactorX;
    points[1] += transFactorY;
}



/**
 * Draws a Sierpinsky triangle on the screen restricted to a certain area with a certain scale factor.
 * @param min_x Restricts minimum location for triangle along X axis
 * @param min_y Restricts minimum location for triangle along Y axis
 * @param iterations Amount of points to place
 * @param scaleAmt Scale factor
 */
void drawTriangleIFS(double min_x, double min_y, int iterations, double scaleAmt) {

    for (int i = 0; i < iterations; ++i) {

        double random = drand48();

        if (random < .333) { // Draw bottom left quadrant
            translate(0.0, 0.0);

            G_rgb(1.0, 0.0, 0.0);
        } else if (random > .333 && random < .666) { // Top Left Quadrant


            translate(0.5, 0.0);

            G_rgb(0.0, 1.0, 0.0);

        } else {
            translate(.25, .5);

            G_rgb(0.0, 0.0, 1.0);
        }

        G_rgb(points[0] - points[1], points[1], points[0]);
        G_point((scaleAmt * points[0]) + min_x , (scaleAmt * points[1]) + min_y );
        scale(.5, .5);
    }

}

/**
 * Draws a Sierpinsky carpet across the entire screen
 * @param iterations Number of points to palce.
 */
void drawCarpet(int iterations) {
    for (int i = 0; i < iterations; ++i) {
        double random = drand48();
        if (random < (1.0 / 8.0)) { // Bottom left
            G_rgb(points[0], points[1], points[0] - points[1]);
        } else if (random < (2.0 / 8.0)) {
            G_rgb(1, 1, 0);
            translate(0.0, (1.0 / 3.0));
        } else if (random < (3.0 / 8.0)) {
            G_rgb(1, 0, 1);
            translate(0.0, (2.0 / 3.0));
        } else if (random < (4.0 / 8.0)) {
            G_rgb(0, 1, 1);
            translate((1.0 / 3.0), 0.0);
        } else if (random < (5.0 / 8.0)) {
            G_rgb(1, 0, 0);
            translate((1.0 / 3.0), (2.0 / 3.0));
        } else if (random < (6.0 / 8.0)) {
            G_rgb(0, 1, 0);
            translate((2.0 / 3.0), 0.0);
        } else if (random < (7.0 / 8.0)) {
            G_rgb(0, 0, 1);
            translate((2.0 / 3.0), (1.0 / 3.0));
        } else {
            G_rgb(0.5, 0, 1);
            translate((2.0 / 3.0), (2.0 / 3.0));
        }
        G_rgb(points[0], points[1], points[0]);
        G_point(WIDTH * points[0], HEIGHT * points[1]);
        scale((1.0 / 3.0), (1.0 / 3.0));
    }

}


int main(int argc, char **argv) {
    int swidth, sheight;

    // must do this before you do 'almost' any other graphical tasks
    swidth = WIDTH;
    sheight = HEIGHT;
    G_init_graphics(swidth, sheight);  // interactive graphics

    G_rgb(0.3, 0.3, 0.3); // dark gray
    G_clear();




    // Draw carpet across whole screen
    drawCarpet(10000000);

    for(int x = 1; x <= 9; x+=3) {
        for(int y = 1; y <= 9; y+=3) {
            // Skip the center square
            if (x == 4 && y == 4) {
                drawTriangleIFS(WIDTH / 3.0, HEIGHT / 3.0, 1000000, WIDTH / 3.0);
                continue;
            }
            double minX = (WIDTH / 9) * x;
            double minY = (HEIGHT / 9) * y;

            drawTriangleIFS(minX, minY, 1000000, WIDTH / 9.0);

            points[0] = 0.0;
            points[1] = 0.0;
        }
    }

    int key;
    key = G_wait_key(); // pause so user can see results

    G_save_to_bmp_file("l-system.bmp");


    exit(EXIT_SUCCESS);
}