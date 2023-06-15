#include "../FPToolkit/FPToolkit.c"

#define WIDTH 800.0
#define HEIGHT 800.0
#define MAX_SNOWFLAKES 3

using namespace std;


/**
 * Draws a Pythagoreas Tree, starting at a current location up until a certain amount of iterations.
 * @param p0 Bottom left point of the tree
 * @param p1 Bottom right point of the tree
 * @param curr_iteration Current iteration of function
 * @param depth How many layers deep are we iterating into the tree
 * @param f Angle of triangle, ranges from 0.0 - .99
 */
void draw_tree(double *p0, double *p1, int curr_iteration, int depth, double f) {

    if(curr_iteration > depth)
        return;

    double p2[] = {0.0, 0.0};
    double p3[] = {0.0, 0.0};

    double x2 = p1[0] - (p1[1] - p0[1]);
    double y2 = p1[1] + (p1[0] - p0[0]);

    double x3 = p0[0] - (p1[1] - p0[1]);
    double y3 = p0[1] + (p1[0] - p0[0]);

    double xm = x3 + f * (x2-x3);
    double ym = y3 + f * (y2 - y3);

    double g = sqrt(f * (1-f));
    double xq = xm - g * (y2-y3);
    double yq = ym + g * (x2 - x3);

    G_rgb(.4 - ((double) curr_iteration / 50), .2 + ((double) curr_iteration / 10), 0.1);


    G_line(p0[0], p0[1], p1[0], p1[1]);
    G_line(p1[0], p1[1], x2, y2);
    G_line(x2, y2, x3, y3);
    G_line(p0[0], p0[1], x3, y3);

    // fill
    double x[] = {p0[0], p1[0], x2, x3};
    double y[] = {p0[1], p1[1], y2, y3};
    G_fill_polygon(x, y, 4);

    p2[0] = x2;
    p2[1] = y2;

    p3[0] = x3;
    p3[1] = y3;

    double q[] = {xq, yq};

    draw_tree(q, p2, curr_iteration + 1, depth, f);
    draw_tree(p3, q, curr_iteration + 1, depth, f);
}



/**
 *
 * @param p0
 * @param p1
 * @param depth
 */
void drawKochCurve(double p0[2], double p1[2], int depth) {
    if (depth <= 0) {
        return;
    }
    depth--;

    // pick a random color
    G_rgb(1.0, 1.0, 1.0);

    // calculate the 2 new points which are 1/3 of the way from the original points
    double p2[2], p3[2];
    p2[0] = p0[0] + (p1[0] - p0[0]) / 3;
    p2[1] = p0[1] + (p1[1] - p0[1]) / 3;
    p3[0] = p0[0] + (p1[0] - p0[0]) * 2 / 3;
    p3[1] = p0[1] + (p1[1] - p0[1]) * 2 / 3;

    // calculate the 3rd point of the triangle which is 60 degrees from the line
    double p4[2];
    p4[0] = p2[0] + (p3[0] - p2[0]) / 2 - (p3[1] - p2[1]) * sqrt(3) / 2;
    p4[1] = p2[1] + (p3[1] - p2[1]) / 2 + (p3[0] - p2[0]) * sqrt(3) / 2;

    // draw the 3 lines of the triangle
    G_line(p0[0], p0[1], p2[0], p2[1]);
    G_line(p2[0], p2[1], p4[0], p4[1]);
    G_line(p4[0], p4[1], p3[0], p3[1]);
    G_line(p3[0], p3[1], p1[0], p1[1]);

    // draw the other 3 lines of the triangle recursively
    drawKochCurve(p0, p2, depth);
    drawKochCurve(p2, p4, depth);
    drawKochCurve(p4, p3, depth);
    drawKochCurve(p3, p1, depth);
}



/**
 * This function takes a point on the screen and a radius essentially, then draws three koch curves around that point to create
 * a snowflake.
 * @param point Location on the screen to draw the KochCurve
 * @param sideLength Radius of the snowflake.
 */
void draw_koch_at_point(double point[2], double sideLength) {


    double p0[2], p1[2], p2[2];

    p0[0] = point[0] - (sideLength / 2.0);
    p0[1] = point[1] - (sideLength * sqrt(3.0) / 4.0);

    p1[0] = point[0];
    p1[1] =  point[1] + ((sideLength * sqrt(3.0)) / 4.0);

    p2[0] = point[0] + (sideLength / 2.0);
    p2[1] = point[1] - (sideLength * sqrt(3.0) / 4.0);

    drawKochCurve(p0, p1, 3);
    drawKochCurve(p1, p2, 3);
    drawKochCurve(p2, p0, 3);

}


/**
 * Draws a cloud at a location (x, y)
 * @param x X location to place cloud
 * @param y Y location to place cloud
 */
void draw_cloud(double x, double y) {
    G_rgb(.839, .839, .839);
    G_fill_circle(x, y, 25);
    G_fill_circle(x - 20, y, 20);
    G_fill_circle(x + 20, y, 20);
    G_fill_circle(x - 40, y, 15);
    G_fill_circle(x + 40, y, 15);
}


int main(int argc, char **argv) {
    int swidth, sheight;


    // must do this before you do 'almost' any other graphical tasks
    swidth = WIDTH;
    sheight = HEIGHT;
    G_init_graphics(swidth, sheight);  // interactive graphics

    G_rgb(0.3, 0.3, 0.3); // dark gray
    G_clear();

    // Night sky gradiaent
    for(int i = 0; i < HEIGHT; i++) {
        G_rgb(0.0, 0.0, 0.0 + (double) i / 1000);
        G_line(0, 800 - i, 800, 800 - i);
    }


    // Star specs throughout whole screen
    G_rgb(.949, .937, .286);
    for(int i = 0; i < 1000; i++) {
        G_point(drand48() * WIDTH, drand48() * HEIGHT);
    }

    // Snow lines
    G_rgb(.94, .94, .916);
    for(int i = 0; i < HEIGHT / 8.0; ++i) {
        G_line(0, i, WIDTH, i);
    }


    // Drawing clouds around the top fo the screen
    draw_cloud(100, 740);
    draw_cloud(220, 730);
    draw_cloud(346, 745);
    draw_cloud(471, 737);
    draw_cloud(602, 730);
    draw_cloud(718, 747);



    // Place tree
    double p0[] = { WIDTH / 1.5, HEIGHT / 8.0};
    double p1[] = { (WIDTH / 1.5) + 80, HEIGHT / 8.0};
    draw_tree(p0, p1, 0, 10, .66);


    // Drawing the snow covering the ground
    G_rgb(.94, .94, .916);
    for(int i = 0; i < 500; ++i) {
            G_fill_circle(drand48() * WIDTH, HEIGHT / 8.0 - 5, 10 * drand48());
    }


    // Having user draw snowflakes
    double click[] = {0.0, 0.0};
    for (int i = 0; i < MAX_SNOWFLAKES; i++) {
        G_wait_click(click);
        draw_koch_at_point(click, 80);
    }


    int key;
    key = G_wait_key(); // pause so user can see results
    G_save_to_bmp_file("recursive.bmp");

    exit(EXIT_SUCCESS);
}

