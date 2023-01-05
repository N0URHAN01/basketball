#include<stdlib.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<string.h>
#include<process.h>

int balls_caught = 0, missed_balls = 0, level_count = 1, points = 0;
int p = 0;                // To increment the points based on color
int d = 0;                // For color selection
int ball_x, ball_y = 10;   // To compute the x and y co ordinates of ball
int basket_x , basket_y;  // To compute the x and y co ordinates of basket
int a = 500, b = 500;        // To set the default screen size
int s = 0;                // To display menu options
int dropped_balls = 0;    // To calculate the number of balls dropped
float speed_1 = 0.5, speed_2 = 1, speed_3 = 1.4, speed_4 = 1.7;    // To increment speeds based on the level
int red_ball = 0, white_ball = 0;
int blue_ball = 0, yellow_ball = 0, green_ball = 0;
int w = 48, h = 48, t = 10, e = 9, g = 12;

void myinit();
void start_screen(int, int);
void ball();
void basket(int, int);
void print_score();
void ball_start();
void color();
void score();
void display(void);
void basket_set(int, int);
void myReshape(int, int);
void keys(unsigned char, int, int);
void menu(int);
int main(int, char**);

void myinit()
{
    glViewport(0, 0, a, b);
    gluOrtho2D(0, (GLdouble)a, 0, (GLdouble)b);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();  
}

// Drawing the initial screen with with the title
void start_screen(int i, int j)
{
    int k;
    char cat[70] = "BASKETBALL STARS";

    glColor3f(1, 1, 0);      //color of BASKETBALL STARS
    glRasterPos2i(120, 190);

    for (k = 0; k < 50; k++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, cat[k]);   // view the cat 

    glFlush();
    

    glColor3f(1, 1, 1);
   ball_x = 375;
    ball_y = 370;

   ball();
    basket(330, 0);
}
// Drawing an ball
void ball()
{
    float x, y;
    float t;
    glBegin(GL_POLYGON);
    for (t = 0; t <= 360; t += 1)
    {
        x = ball_x + 16 * (cos(t));
        y = ball_y + 16 * (sin(t));

        glVertex2f(x,y );
    }
    glEnd();

}

// Drawing the basket
void basket(int i, int j)
{
    j = 10;
   if (i >= a - 60) i = a - 60;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(0.0+i , 50.0 + j);
    glVertex2f(10.0+i, 10.0 + j);
    glColor3f(1.0, 0.0, 1.0);
    glVertex2f(50.0+i , 10.0 + j);
    glVertex2f(60.0+i , 50.0 + j);
    glEnd();
}

//Displaying the score. This function is called when the game is over
void print_score()
{
    printf("\nLevel reached: %d\n\n", level_count);
    printf("\nNo. of balls dropped     = %d \n", dropped_balls);
    printf("\nNo. of balls caught      = %d\n", balls_caught);
    printf("\nNo. of balls missed      = %d\n", missed_balls);
    printf("\nWhite balls   = %d\tpoints gained   = %d\n", white_ball, white_ball);
    printf("\nRed balls  = %d\tpoints gained   = %d\n", red_ball, red_ball * 5);
    printf("\nGreen balls   = %d\tpoints gained   = %d\n", green_ball, green_ball * 10);
    printf("\nBlue balls    = %d\tpoints gained   = %d\n", blue_ball, blue_ball * 15);
    printf("\nYellow balls  = %d\tpoints gained   = %d\n\n", yellow_ball, yellow_ball * 100);

    printf("\n\n\nYour score = %d\n\n", points);

}
//init_score initialises score counters after a game is over.
void init_score()
{
    balls_caught = 0, missed_balls = 0, level_count = 1;
    dropped_balls = 0;
    missed_balls = 0;
    white_ball = 0;
    red_ball = 0;
    green_ball = 0;
    blue_ball = 0;
    yellow_ball = 0;
    points = 0;
   s = 0;
}


// All the three ball generators start dropping the balls
void ball_start()
{
    ball_y = 800;
    if (missed_balls < 10)
    {
        dropped_balls++;
        switch (rand() % 9)
        {
        case 0:ball_x = 105; d = rand() % 5; break;
        case 1:ball_x = 245; d = rand() % 5; break;
        case 2:ball_x = 480; d = rand() % 5; break;
        case 5:ball_x = 105; d = rand() % 5; break;
        case 3:ball_x = 245; d = rand() % 5; break;
        case 4:ball_x = 380; d = rand() % 5; break;
        case 7:ball_x = 105; d = rand() % 5; break;
        case 6:ball_x = 245; d = rand() % 5; break;
        case 8:ball_x = 380; d = rand() % 5; break;
        }
    }
    else
    {
        printf("\n\n\t\t\t\tGAME OVER\n\n");
        print_score();
        init_score();
    }

}
//colours for the balls
void color()
{
    switch (d)
    {
    case 0:glColor3f(0, 0, 1); p = 15; break;     //blue
    case 1:glColor3f(1, 1, 0); p = 100; break;    //yellow
    case 2:glColor3f(0, 1, 0); p = 10; break;     //green
   case 3:glColor3f(1, 0, 0); p = 5; break;      //red
    case 5:glColor3f(1, 1, 1); p = 1; break;      //white
    }
    glFlush();
}

// score function increments the score counters
void score()
{
    if (ball_y <= 50 && (ball_x >= basket_x && ball_x <= basket_x + 60))
    {
        printf("\a");

        balls_caught++;

        switch (d)
        {
        case 0: blue_ball++; break;
        case 1: yellow_ball++; break;
        case 2: green_ball++; break;
        case 3: red_ball++; break;
        case 5: white_ball++; break;
        }
        points += p;
        ball_y = -10;

    }
    missed_balls = dropped_balls - balls_caught;

}


void display(void)
{

    char level1[12] = "LEVEL 1";
    char level2[12] = "LEVEL 2";
    char level3[12] = "LEVEL 3";
    char level4[12] = "LEVEL 4";

    glClear(GL_COLOR_BUFFER_BIT);


    if (s >= 1)
    {
        //Diplaying the level
        if (level_count == 1)
        {
            glColor3f(1, 1, 1);
            glRasterPos2i(400, 300);
            int i;
            for (i = 0; i < 12; i++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, level1[i]);
        }
        else if (level_count == 2)
        {
            glColor3f(1, 1, 1);
            glRasterPos2i(400, 300);
            int i;
            for (i = 0; i < 12; i++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, level2[i]);
        }
        else if (level_count == 3)
        {
            glColor3f(1, 1, 1);
            glRasterPos2i(400, 300);
            int i;
            for (i = 0; i < 12; i++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, level3[i]);
        }
        if (level_count == 4)
        {
            glColor3f(1, 1, 1);
            glRasterPos2i(400, 300);
            int i;
            for (i = 0; i < 12; i++)
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, level4[i]);
        }

        if (ball_y <= 10)
        {
            ball_start();  //ball_start() is the balls dropping function
        }
        color();
        ball();
        basket(basket_x, basket_y);


        //changing the level based on the balls caught

        if (balls_caught >= 5)
        {

            ball_y -= speed_2;
            level_count = 2;
        }
        if (balls_caught >= 10)
        {

            ball_y -= speed_3;
            level_count = 3;
        }
        if (balls_caught >= 15)
        {

            ball_y -= speed_4;
            level_count = 4;
        }

        else
            ball_y -= speed_1;
        score();
    }

    else
        //No game start event. Display initial screen
        start_screen(40, 300);
    glFlush();
    glutSwapBuffers();

}


void basket_set(int a, int b)
{
    basket_x = a;
    basket_y = b;
    glutPostRedisplay();
    glFlush();
}

void myReshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    a = w;
    b = h;
}


void keys(unsigned char key, int x, int y)
{

    if (key == 'q' || key == 'Q')
    {
        printf("\n\n\n\t\tQUIT BY PLAYER\n\n");
        print_score();
        exit(0);
    }
    if (key == 's' || key == 'S')
        s += 1;

}


void menu(int id)
{
    switch (id)
    {
    case 1: s += 1;
        break;


    case 2: printf("\n\n\n\t\tPLAYER HAS QUIT\n");
        print_score();
        exit(0);
    }
    glutPostRedisplay();

}


int main(int argc, char** argv)
{
    printf("**********");
    printf("\n\t\t\t\t  BALL IN THE BASKET \n\n");
    printf("**********");
    printf("\nInstructions\n\n   <1> The objective of the game is to catch the ball in the basket.\n\t To move Basket use the mouse.\n");
    printf("\n   <2> To Start, press key 's' or 'S' or \n\tClick Right mouse button then click 'Start Game'.\n");


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(a, b);
    glutCreateWindow("BASKETBALL STARS");
    myinit();
    glutCreateMenu(menu);
    glutAddMenuEntry("Start game", 1);

    glutAddMenuEntry("Quit", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutDisplayFunc(display);
    glutKeyboardFunc(keys);
    glutPassiveMotionFunc(basket_set);
    glutIdleFunc(display);
    glutReshapeFunc(myReshape);
    glutMainLoop();

}
