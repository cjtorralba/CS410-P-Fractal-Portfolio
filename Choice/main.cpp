/**
 * Choice piece
 */
#include "../FPToolkit/FPToolkit.c"

#define WIDTH 800.0
#define HEIGHT 800.0
#define DEGREE_TO_RAD(x) ((x * M_PI) / 180)



/**
 * Draws a line a certain length at a given angle
 * @param listOfPoints Location to draw from
 * @param lineLength Length of the line
 * @param angle     Angle to draw at
 * @param increment If you want the function to increase the value of listOfPoints by lineLength
 * @param transparent True if you wish the drawing not to be seen
 */
void drawLineAtAngle(double *listOfPoints, double lineLength, double angle, bool increment, bool transparent) {
    double radians = DEGREE_TO_RAD(angle);
    double yLength = lineLength * sin(radians);
    double xLength = lineLength * cos(radians);


    if (!transparent) {
        G_line(listOfPoints[0], listOfPoints[1], listOfPoints[0] + xLength, listOfPoints[1] + yLength);
    }

    if (increment) {
        listOfPoints[0] += xLength;
        listOfPoints[1] += yLength;
    }
}


/**
 * Draws a Heighway Dragon fractal on the screen
 * @param string Langauge to draw from
 * @param distance Line length
 * @param angle Current angle
 * @param points Starting position
 */
void drawCoral(char *string, double distance, double angle, double *points) {
    for (int i = 0; i < strlen(string); ++i) {
        switch (string[i]) {
            case 'F':
                drawLineAtAngle(points, distance, angle, true, false);
                break;

            case 'X':
                drawLineAtAngle(points, distance, angle, true, false);
                break;
            case 'Y':
                drawLineAtAngle(points, distance, angle, true, false);
                break;

            case '+':
                angle -= 45.0;
                break;
            case '-':
                angle += 45.0;
                break;


        }
    }
}


/**
 * Builds a grammar for the Heighway Dragon fractal
 * Rules:
 *      F -> Z \n
 *      X -> +FX--FY+ \n
 *      Y -> -FX++FY- \n
 *      + -> Increase angle by 45 degrees \n
 *      - -> Decrease angle by 45 degrees \n
 * Axiom: "FX"
 * @param string String to write into
 * @param depth Number of iterations
 */
void coralStringBuilder(char *string, int depth) {

    char temp[1000000] = {'\0'};

    for (int i = 0; i < depth; ++i) {
        for (int j = 0; j < strlen(string); ++j) {
            switch (string[j]) {
                case 'F':
                    strcat(temp, "Z");
                    break;

                case 'X':
                    strcat(temp, "+FX--FY+");
                    break;
                case 'Y':
                    strcat(temp, "-FX++FY-");
                    break;
                case '+':
                    strcat(temp, "+");
                    break;
                case '-':
                    strcat(temp, "-");
                    break;

                default:
                    break;
            }
        }
        strcpy(string, temp);
        memset(temp, '\0', sizeof(temp));
    }
}


/**
 * Draws a McWorter fractal to the screen. \n
 * @param string Grammar to draw
 * @param distance Distance of lines
 * @param angle  Angle difference
 * @param points Starting position
 */
void drawMcworter(char *string, double distance, double angle, double *points) {

    for (int i = 0; i < strlen(string); ++i) {
        switch (string[i]) {
            case 'F':
                drawLineAtAngle(points, distance, angle, true, false);
                break;

            case '+':
                angle -= 36.0;
                break;
            case '-':
                angle += 36.0;
                break;
        }
        //G_wait_key();
    }
}

/**
 * Creates Creates a string containing necessary grammar to draw a McWorter Pentigree \n
 * Rules: \n
 *      F -> +F++F----F--F++F++F-  \n
 *      + -> Increase angle 36.0 degrees  \n
 *      - -> Decrease angle 36.0 degrees  \n
 * Axiom: \n
 *      F \n
 * @param str String to write into
 * @param depth Number of iterations
 */
void buildMcworter(char *str, int depth) {
    char temp[1000000] = {'\0'};

    for (int i = 0; i < depth; ++i) {
        for (int j = 0; j < strlen(str); ++j) {

            switch (str[j]) {
                case 'F':
                    strcat(temp, "+F++F----F--F++F++F-");
                    break;

                case '+':
                    strcat(temp, "+");
                    break;
                case '-':
                    strcat(temp, "-");
                    break;

                default:
                    break;
            }
        }
        strcpy(str, temp);
        memset(temp, '\0', sizeof(temp));
    }

}


int main() {
    double swidth, sheight;

    // must do this before you do 'almost' any other graphical tasks
    swidth = 800.0;
    sheight = 800.0;
    G_init_graphics(swidth, sheight);  // interactive graphics

    // clear the screen with white
    G_rgb(.3, .3, .3);

    G_clear();

    // Dark ocean gradient
    for (int i = 0; i < HEIGHT; ++i) {
        double r = 0.1059 - (double) i / 2000;
        double g = 0.3020 - (double) i / 2000;
        double b = 0.4471 - (double) i / 2000;
        G_rgb(r, g, b);
        G_line(0, HEIGHT - i, WIDTH, HEIGHT - i);
    }

    // Draw sand

    for(int i = 0; i < HEIGHT / 5.0; ++i) {
        G_rgb(.91, .7 + (i / 1000.0), .3 + (i / 1000.0));
        G_line(0.0, i, WIDTH, i);

    }


    double coralPosition[2] = {300.0, 200.0};
    char coral[1000000] = {'F', 'X'};
    coralStringBuilder(coral, 11);
    G_rgb(1.0, 0.0, 0.0);
    drawCoral(coral, 3.0, 180.0, coralPosition);

    G_rgb(255.0 / 255.0, 127.0 / 255.0, 80.0 / 255.0);
    double worterPosition[2] = {500.0, 250.0};
    char worter[100000] = {'F'};
    buildMcworter(worter, 4);
    drawMcworter(worter, 5.0, 0.0, worterPosition);


    G_rgb(.467, .337, .651);
    coralPosition[0] = WIDTH / 2.0;
    coralPosition[1] = HEIGHT / 2.0;
    drawCoral(coral, 3.5, 130.0, coralPosition);


    int key;
    key = G_wait_key(); // pause so user can see results

    G_save_to_bmp_file("turtle.bmp");
}

