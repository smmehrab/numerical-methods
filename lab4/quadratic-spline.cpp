/*
Submitted By:

S.M.Mehrabul Islam
Roll: 01
Batch: 24 (3rd Year 2nd Semester)
Email: mehrab.24csedu.001@gmail.com

# Lab Assignment 2

x       |   -350.0  -175.0  0       175.0   350.0
f(x)    |   -300.0  -72.67  62.7    217.33  403.67

Write fx program in C/C++ to make fx curve using above points. 

*/

#include <GL/glut.h>
#define WIDTH 1200
#define HEIGHT 1000
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define n 4

double x[] = {-350.00, -175.00, 0.00, 175.00, 350.00};
double fx[] = {-300.00, -72.67, 62.70, 217.33, 403.67};
double c[n], b[n], d[n];

/*
Util Functions
*/

void takeInput() {
    for(int i=0; i<n+1; ++i){ 
        printf("Enter x[%d] : ", i);
        scanf("%lf", &x[i]);
        printf("Enter y[%d] : ", i);
        scanf("%lf", &fx[i]);
    }
}

static void reShape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH/2, WIDTH/2 - 1, -HEIGHT/2, HEIGHT/2 - 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void display(void) {
    float X, Y;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // plotting the curve
    glPushMatrix();
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3ub(255, 100, 255);
    for(int i=0; i<=n; i++)
       glVertex2f(x[i], fx[i]);
    glEnd();

    glPointSize(1);

    glPushMatrix();
    glColor3ub(128, 128, 128);
    glBegin(GL_LINES);
    glVertex2i(-WIDTH/2, 0);
    glVertex2i(WIDTH/2, 0);
    glVertex2i(0, -HEIGHT/2);
    glVertex2i(0, HEIGHT/2);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POINTS);
    for(int i=0; i<n; i++){
        glColor3ub(255-i*52, i*52, 0);
        X = x[i];
        for(int j=0; j<1000; j++){
            X += (x[i+1]-x[i])/1000.0;
            Y = fx[i] + b[i]*(X - x[i]) + c[i]*pow((X - x[i]),2.0) + d[i]*pow((X - x[i]),3.0);
            glVertex2f(X, Y);
        }
    }
    glEnd();
    glPopMatrix();
    glFlush();
}

static void idle(void) {
    glutPostRedisplay();
}

static void myinit(void) {
    glClearColor(0, 0, 0, 1);
    glEnable(GL_COLOR_MATERIAL);
}

/*
Algorithm Function
*/

void algorithm(void){
    int i, j;
    float h[n], A[n+1], u[n+1], z[n+1];

    // takeInput();
    // To take input for other set of values, uncomment the above line

    /** Step 1 */
    for(j = 0; j < n; ++j) 
        h[j] = x[j + 1] - x[j];

    /** Step 2 */
    A[0] = A[n] = 0;
    for(j = 1; j < n; ++j)
        A[j] = 3 * (fx[j+1] - fx[j]) / h[j] - 3 * (fx[j] - fx[j-1]) / h[j-1];

    /** Step 3 */
    u[0] = 0;
    z[0] = 0;

    /** Step 4 */
    for (i = 1; i < n; ++i) {
        u[i] = h[i] / (2 * (x[i + 1] - x[i - 1]) - h[i - 1] * u[i - 1]);
        z[i] = (A[i] - h[i - 1] * z[i - 1]) / (2 * (x[i + 1] - x[i - 1]) - h[i - 1] * u[i - 1]);
    }

    /** Step 5 */
    z[n] = 0;
    c[n] = 0;

    /** Step 6 */
    for(j = n-1; j >= 0; --j) {
        c[j] = z[j] - u[j] * c[j + 1];
        b[j] = (fx[j+1] - fx[j]) / h[j] - h[j] * (c[j+1] + 2 * c[j]) / 3;
        d[j] = (c[j+1] - c[j]) / (3 * h[j]);
    }

    /** Step 7 */
    printf("%2s %8s %8s %8s %8s\n", "i", "ai", "bi", "ci", "di");
    for(i = 0; i < n; ++i)
        printf("%2d %8.2f %8.2f %8.2f %8.2f\n", i, fx[i], b[i], c[i], d[i]);
}

/*
Driver Function
*/

int main(int argc, char* argv[]) {

    algorithm();
    
    // Showing Output
    float X, Y;
    for(int i=0; i<n; i++){
        glColor3ub(255-i*52, i*52, 0);
        X = x[i];
        for(int j=0; j<10; j++){
            X += (x[i+1]-x[i])/10.0;
            Y = fx[i] + b[i]*(X - x[i]) + c[i]*pow((X - x[i]),2.0) + d[i]*pow((X - x[i]),3.0);
            printf("%0.4f  %0.4f\n", X, Y);
        }
    }

    // Displaying Graph
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("Lab Assignment 2");
    myinit();
    glutReshapeFunc(reShape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();
    
    return EXIT_SUCCESS;
}