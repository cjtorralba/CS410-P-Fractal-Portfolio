#include "../FPToolkit/FPToolkit.c"

#define WIDTH 800.0
#define HEIGHT 800.0

using namespace std;



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

    p2[0] = x2;
    p2[1] = y2;

    p3[0] = x3;
    p3[1] = y3;

    double q[] = {xq, yq};

    draw_tree(q, p2, curr_iteration + 1, depth, f);
    draw_tree(p3, q, curr_iteration + 1, depth, f);


}






int main(int argc, char **argv) {


    int swidth, sheight;


    // must do this before you do 'almost' any other graphical tasks
    swidth = WIDTH;
    sheight = HEIGHT;
    G_init_graphics(swidth, sheight);  // interactive graphics

    G_rgb(0.3, 0.3, 0.3); // dark gray
    G_clear();

    int key;
    key = G_wait_key(); // pause so user can see results

    //   G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("Demo.bmp");


    exit(EXIT_SUCCESS);
}

