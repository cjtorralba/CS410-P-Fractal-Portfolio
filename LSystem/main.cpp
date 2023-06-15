/**
 * PythagorasTree.c
 */
#include "../FPToolkit/FPToolkit.c"
#include <stack>

#define WIDTH 800.0
#define HEIGHT 800.0
#define DEGREE_TO_RAD(x) ((x * M_PI) / 180)



void drawPlant(char *string, double distance, double angle, double *points);

void stringBuilderPlant(char *source, int depth);

void stringBuilderDragon(char *source, int depth);

void drawDragon(char *string, double distance, double angle, double *points);

int main() {

    double swidth, sheight;
    // must do this before you do 'almost' any other graphical tasks
    swidth = 800.0;
    sheight = 800.0;
    G_init_graphics(swidth, sheight);  // interactive graphics
    // clear the screen with white
    G_rgb(.3, .3, .3);
    G_clear();
    // =================================================================




    // Drawing the sky
    for (int i = 0; i < HEIGHT; ++i) {
        G_rgb(.8 - ((double) i / 300), .5 - ((double) i / 100), .2 * i / 100);
        G_line(0, i, WIDTH, i);
    }

    // Creating grass
    G_rgb(.086, .271, 0.055);
    G_fill_circle(WIDTH / 2.0, -900, 1000);


    char str[1000000] = {'F'};
    char drag[1000000] = {'F', 'X'};
    stringBuilderDragon(drag, 10);
    stringBuilderPlant(str, 4);


    // Drawing clouds
    double points[2] = {WIDTH / 6.0, HEIGHT - (HEIGHT / 8.0)};
    G_rgb(.5, .5, .5);
    drawDragon(drag, 2.0, 0.0, points);

    points[0] += WIDTH / 6.0;
    points[1] -= 40.0;
    drawDragon(drag, 2.0, 30.0, points);

    points[0] += WIDTH / 6.0;
    points[1] += 90.0;
    drawDragon(drag, 2.0, -30.0, points);


    // Drawing lonely plant
    points[0] = WIDTH / 2.0;
    points[1] = 100.0;
    G_rgb(.84, .5, .05);
    drawPlant(str, 3.0, 90.0, points);


    int key;
    key = G_wait_key(); // pause so user can see results

    G_save_to_bmp_file("turtle.bmp");
}


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

    double p2[2] = {listOfPoints[0] + xLength, listOfPoints[1] + yLength};

    if (!transparent) {
        G_line(listOfPoints[0], listOfPoints[1], listOfPoints[0] + xLength, listOfPoints[1] + yLength);
    }

    if (increment) {
        listOfPoints[0] += xLength;
        listOfPoints[1] += yLength;
    }
}


/**
 * This function draws a plant at a given location, it uses a make-shift stack to keep track of previously saved locations and angle so we create a
 * nice in depth photo
 * @param string Grammmar to draw from
 * @param distance Line length between each connecting piece
 * @param angle Angle between lines
 * @param points Starting point
 */
void drawPlant(char *string, double distance, double angle, double *points) {

    int arrSize = 0;
    double *storedX = nullptr;
    double *storedY = nullptr;
    double *storedAngle = nullptr;

    for (int i = 0; i < strlen(string); ++i) {
        if (string[i] == '[') {
            ++arrSize;
        }
    }

    storedX = new double[arrSize];
    storedY = new double[arrSize];
    storedAngle = new double[arrSize];
    int currentIndex = 0;


    for (int i = 0; i < strlen(string); ++i) {

        switch (string[i]) {
            case 'F':
                drawLineAtAngle(points, distance, angle, true, false);
                break;

            case 'X':
                drawLineAtAngle(points, distance, angle, true, false);
                break;
            case 'Z':
                drawLineAtAngle(points, distance, angle, true, false);
                break;

            case '[':
                storedX[currentIndex] = points[0];
                storedY[currentIndex] = points[1];
                storedAngle[currentIndex] = angle;
                ++currentIndex;
                break;

            case ']':
                --currentIndex;
                points[0] = storedX[currentIndex];
                points[1] = storedY[currentIndex];
                angle = storedAngle[currentIndex];

                break;
            case '+':
                angle -= 22.5;
                break;
            case '-':
                angle += 22.5;
                break;
        }
    }
}


/** function which creates a grammar rule in a char array of:
* Rules:
 *   F -> FX[FX[+XF]]
 *   X -> FF{+XZ++X-F[+ZX]][-X++F-X]
 *   Z -> [+F-X-F][++ZX]
 *   + -> Increase angle
 *   - -> Decrease angle
 *   [ -> Store location and angle
 *   ] -> Go back to last location and angle
 * @param source Starting string
 * @param depth Number of iterations to do
 **/
void stringBuilderPlant(char *source, int depth) {

    char temp[1000000] = {'\0'};

    for (int i = 0; i < depth; ++i) {
        for (int j = 0; j < strlen(source); ++j) {
            switch (source[j]) {

                case 'F':
                    strcat(temp, "FX[FX[+XF]]");
                    break;

                case 'X':
                    strcat(temp, "FF[+XZ++X-F[+ZX]][-X++F-X]");
                    break;
                case 'Z':
                    strcat(temp, "[+F-X-F][++ZX]");
                    break;

                case '+':
                    strcat(temp, "+");
                    break;
                case '-':
                    strcat(temp, "-");
                    break;
                case '[':
                    strcat(temp, "[");
                    break;
                case ']':
                    strcat(temp, "]");
                    break;

                default:
                    break;
            }
        }
        strcpy(source, temp);
        memset(temp, '\0', sizeof(temp));
    }

}


void stringBuilderDragon(char *source, int depth) {

    char temp[1000000] = {'\0'};

    for (int i = 0; i < depth; ++i) {
        for (int j = 0; j < strlen(source); ++j) {
            switch (source[j]) {

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
        strcpy(source, temp);
        memset(temp, '\0', sizeof(temp));
    }

}


void drawDragon(char *string, double distance, double angle, double *points) {
    for (int i = 0; i < strlen(string) - 1; ++i) {
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



