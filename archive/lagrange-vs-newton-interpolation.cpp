/*
Submitted By:

S.M.Mehrabul Islam
Roll: 01
Batch: 24 (3rd Year 2nd Semester)
Email: mehrab.24csedu.001@gmail.com

# Assignment

Write a program in C to display a 3rd order
    (i) Lagrange Interpolation Polynomial
    (ii) Newton Divided Difference Interpolation Polynomial
using Divided-Difference Method on the same screen with same data points.

Suppose, the data points are (-400,-120),(-200,200),(200, -170),(400,250) and N=4

We will represent our polynomials as such:
    (i) Lagrange Polynomial - Yellow
    (ii) Newton Divided Difference Interpolation Polynomial - Green
Points are represented as little red squares.

And also, as both polynomials are almost entirely overlapping each other (from observation),
we are going to vertically shift the Newton Divided Difference Polynomial for 10 units.
(Thus, displaying y+10)

*/

// #include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 1000
#define HEIGHT 700
#define N 4

struct DataPoint {
    int x, y;
};

DataPoint dataPoints[] =  {{-400,-120}, {-200, 200}, {200, -170}, {400, 250}};

/*
Interpolation Functions
*/

double lagrange_interpolate(DataPoint dataPoints[], double x, int n) {
    double y = 0;
    for(int i=0; i<n; i++) {
        double l = (double) dataPoints[i].y;
        for(int j=0; j<n; j++) {
            if(j!=i) {
                l *= (x-dataPoints[j].x)/double(dataPoints[i].x-dataPoints[j].x);
            }
        }
        y += l;
    }
    return y;
}

double newton_divided_difference_interpolate(DataPoint dataPoints[], double x, int n) {
    double dividedDifferenceTable[n+1][n+1];
    for(int i=0; i<n; i++) {
        dividedDifferenceTable[i][0] = dataPoints[i].y;
    }

    double y = dividedDifferenceTable[0][0];
    for(int i=1; i<n; i++) {
        for (int j=0; j<n-1; j++) {
            dividedDifferenceTable[j][i] = ((dividedDifferenceTable[j+1][i-1]-dividedDifferenceTable[j][i-1])/double(dataPoints[i+j].x-dataPoints[j].x));
        }
        int p = 1;
        for(int j=0; j<i; j++) {
            p *= (x-dataPoints[j].x);
        }
        y += (dividedDifferenceTable[0][i]*p);
    }
    return y;
}

/*
GLUT Callback
*/

static void display(void) {
    // Setting Up
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Displaying Contents
    glPushMatrix();

        // Coordinate Axis
        glColor3ub(255, 255, 255);
        glPointSize(1);
        glBegin(GL_LINES);
            glVertex2f(0, -HEIGHT/2.0);
            glVertex2f(0, HEIGHT/2.0);
            glVertex2f(-WIDTH/2.0, 0);
            glVertex2f(WIDTH/2.0, 0);
        glEnd();

        // Points
        glColor3ub(255, 0, 0);
        glPointSize(7);
        glBegin(GL_POINTS);
            for(int i=0; i<N; i++) {
                glVertex2d(dataPoints[i].x, dataPoints[i].y);
            }
        glEnd();
        // Shifted Points
        glColor3ub(255, 0, 0);
        glPointSize(7);
        glBegin(GL_POINTS);
            for(int i=0; i<N; i++) {
                glVertex2d(dataPoints[i].x, dataPoints[i].y+50);
            }
        glEnd();

        /*
        Polynomials
        */

        glPointSize(2);
        glColor3ub(255, 255, 0);
        glBegin(GL_POINTS);
            // Displaying Lagrange Interpolation Polynomial
            for(double x=-(WIDTH/2.00); x<(WIDTH/2.00); x+=0.2) {
                double y = lagrange_interpolate(dataPoints, x, N);
                glVertex2d(x, y);
            }
        glEnd();

        glPointSize(2);
        glColor3ub(0, 255, 0);
        glBegin(GL_POINTS);
            // Displaying Newton Divided Difference Polynomial
            for(double x=-(WIDTH/2.00); x<(WIDTH/2.00); x+=0.2) {
                double y = newton_divided_difference_interpolate(dataPoints, x, N);
                glVertex2d(x, y+50);
            }
        glEnd();

    glPopMatrix();
    glFlush();
}

/*
GLUT Callback Handlers
*/

// Projection Setting
static void reshape(int width, int height) {
    GLfloat aspectRatio = (GLfloat) width / (GLfloat) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

// Lighting Setting
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_COLOR_MATERIAL);
}

/*
GLUT Key Press Handler
*/

static void key(unsigned char key, int x, int y) {
    switch (key) {
        case 27 :
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

/* Entry Point */
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 10);
    glutInitDisplayMode(GLUT_RGB);

    glutCreateWindow("Lagrange Interpolation Polynomial (Yellow) & Newton Divided Difference Polynomial (Green)");

    init(); // Lighting
    glutReshapeFunc(reshape); // Projection
    glutDisplayFunc(display); // Callback
    glutKeyboardFunc(key);
    glutMainLoop();

    return EXIT_SUCCESS;
}
