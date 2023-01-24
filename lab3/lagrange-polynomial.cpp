#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

/**************************************************************************************/

#include <GL/glut.h>
#define WIDTH 3000
#define HEIGHT 1200
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/**************************************************************************************/

void reshape(int width, int height);
void display(void);
void idle(void);
void myInit(void);

/**************************************************************************************/

double l(int i, double x);
double f(double x);
void lagrange_polynomial();

/**************************************************************************************/

struct Point {
    int x;
    int y;
};

struct Color {
    int r;
    int g;
    int b;
};

Color colors[] = { 
    {254, 0, 255}, 
    {92, 127, 179}, 
    {143, 176, 48}, 
    {2, 70, 254}, 
    {100, 76, 49}, 
    {225, 156, 35}, 
    {235, 97, 51}, 
    {252, 254, 49}, 
    {0, 0, 0}
};
Color color;
int colorIndex = 0;
int colorCount = 9;

int n;
vector<Point> points;
Point point;

double xLow;
double xHigh;
double xOffset = 100;
double yOffset = 50;
double h = 0.001;

/**************************************************************************************/

bool compareX(const Point &a, const Point &b) {
    return a.x < b.x;
}

double f(double x) {
    double fx = 0.00;
    for(int i=0; i<n; i++) {
        fx += (l(i, x) * points[i].y);
    }
    return fx;
}

double l(int i, double x) {
    double li = 1.00;
    for (int j=0; j<n; j++) {
        if (j!=i) {
            li *= ((x - points[j].x)/(double(points[i].x - points[j].x)));
        }
    }
    return li;
}

void lagrange_polynomial() {
    freopen("input.txt", "r+", stdin);
    freopen("output.txt", "w+", stdout);

    cin >> n;

    for(int i=0; i<n; i++) {
        cin >> point.x >> point.y;
        points.push_back(point);
    }

    sort(points.begin(), points.end(), compareX);
    
    xLow = points[0].x;
    xHigh = points[n-1].x;

    cout << "Input:" << endl;
    for(Point p : points) {
        cout << p.x << " " << p.y << endl;
    }
    cout << endl;

    // cout << "Output:" << endl;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Coordinate Axis
    glColor3ub(0,0,0);
    glPointSize(1);
    glPushMatrix();
    glBegin(GL_LINES);
    // x axis
    glVertex2i(-WIDTH/2,0);
    glVertex2i(WIDTH/2,0);
    // y axis
    glVertex2i(0,-HEIGHT/2);
    glVertex2i(0,HEIGHT/2);
    glEnd();
    glPopMatrix();

    double xScale = 60;
    double yScale = 60;

    /*
    Langrange Li()
    i = 0 ... n-1
    x = (xLow - xOffset) ... (xHigh+xOffset) [0.001]
    */
    for(int i=0; i<n; i++) {
        color = colors[i%colorCount];
        glColor3ub(color.r, color.g, color.b);
        glPointSize(1);
        glPushMatrix();
        glBegin(GL_POINTS);
            for(double x=xLow-xOffset; x<=xHigh+xOffset; x+=h) {
                glVertex2d(xScale * x, yScale * l(i, x));
            }
        glEnd();
        glPopMatrix();
    }

    // x axis points
    glColor3ub(0, 0, 0);
    glPointSize(4);
    glPushMatrix();
    glBegin(GL_POINTS);
        for(double x=-xOffset; x<=xOffset; x+=1.0) {
            glVertex2d(xScale * x, 0.0);
        }
    glEnd();
    glPopMatrix();

    // y axis points
    glColor3ub(0, 0, 0);
    glPointSize(4);
    glPushMatrix();
    glBegin(GL_POINTS);
        for(double y=-yOffset; y<=yOffset; y+=1.0) {
            glVertex2d(0.0, yScale*y);
        }
    glEnd();
    glPopMatrix();

    /*
    Langrange Fx()
    x = (xLow - xOffset) ... (xHigh+xOffset) [0.001]
    */
    glColor3ub(255, 255, 0);
    glPointSize(2);
    glPushMatrix();
    glBegin(GL_POINTS);
        for(double x=xLow-xOffset; x<=xHigh+xOffset; x+=h) {
            glVertex2d(xScale * x, yScale * f(x));
        }
    glEnd();
    glPopMatrix();


    /*
    Points
    */
    glColor3ub(208, 0, 0);
    glPointSize(4);
    glPushMatrix();
    glBegin(GL_POINTS);
    for(Point point : points) {
        glVertex2d(xScale * point.x, yScale * point.y);
    }
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(500, 200);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("86-Lagrange-Polynomial");

    glutReshapeFunc(reshape);
    myInit();
    
    lagrange_polynomial();

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}

/**************************************************************************************/

void reshape(int width, int height) {
    // specify viewport
    glViewport(0, 0, width, height);
    // select projection matrix
    glMatrixMode(GL_PROJECTION);
    // reset projection matrix
    glLoadIdentity();
    // specify projection
    glOrtho(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2, -1, 1);
    // switch back to modelview matrix
    // where we draw stuff
    glMatrixMode(GL_MODELVIEW);
    // reset modelview matrix
    glLoadIdentity();
}

void idle(void) {
    glutPostRedisplay();
}

void myInit(void) {
    glClearColor(212,223,158, 0);
    glEnable(GL_COLOR_MATERIAL);
}