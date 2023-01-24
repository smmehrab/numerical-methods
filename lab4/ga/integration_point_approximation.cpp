#include <GL/glut.h>
#define WIDTH 512
#define HEIGHT 512

#include <bits/stdc++.h>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
using namespace std;

// g++ main.cpp -o opengl -lGL -lGLU -lglut
// ./opengl

/*
    f(x) = (x*x)
    range 0 to 1
    n = 10
*/

/**************************************************************************************/

void reshape(int width, int height);
void display(void);
void idle(void);
void myInit(void);

double f(double x);
double Ln(double a, double b, double delX);
void numerical_integration();

/**************************************************************************************/

struct Point {
    double x;
    double y;

    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }
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

double xLow;
double xHigh;
double xOffset = 100;
double yOffset = 50;
double h = 0.001;

double xScale = 300;
double yScale = 300;

/**************************************************************************************/

int a, b, n;
double delX;
vector<Point> leftPoints;
vector<Point> rightPoints;
vector<Point> midPoints;

double leftPointApproximation(double a, double b, double delX, int n) {
    double sumFx = 0;
    double fx;
    double x=a;
    for(int i=0; i<n; i++, x+=delX) {
        fx = f(x);
        leftPoints.push_back(Point(x, fx));
        sumFx += fx;
    }

    cout << "Left Points" << endl;
    for(Point point: leftPoints) {
        cout << point.x << " " << point.y << endl;
    }
    return (sumFx*delX);
}

double rightPointApproximation(double a, double b, double delX, int n) {
    double sumFx = 0;
    double fx;
    double x=a;
    for(int i=0; i<n; i++, x+=delX) {
        fx = f(x+delX);
        rightPoints.push_back(Point(x+delX, fx));
        sumFx += fx;
    }

    cout << "Right Points" << endl;
    for(Point point: rightPoints) {
        cout << point.x << " " << point.y << endl;
    }
    return (sumFx*delX);
}

double midPointApproximation(double a, double b, double delX, int n) {
    double sumFx = 0;
    double fx;
    double x=a;
    for(int i=0; i<n; i++, x+=delX) {
        fx = f(x+(delX/2.00));
        midPoints.push_back(Point(x+(delX/2.00), fx));
        sumFx += fx;
    }
    cout << "Mid Points" << endl;
    for(Point point: midPoints) {
        cout << point.x << " " << point.y << endl;
    }
    return (sumFx*delX);
}

double f(double x) {
    return (x*x);
}

double integrate(double a, double b) {
    return ((b*b*b)/3.00) - ((a*a*a)/3.00);
}

void numerical_integration() {
    freopen("input.txt", "r+", stdin);
    freopen("output.txt", "w+", stdout);

    cin >> a >> b;
    cin >> n;

    xLow = a;
    xHigh = b;
    delX = (b-a)/(n*1.00);
    cout << "Input: " << a << " " << b << endl;
    cout << "delX: " << delX << endl;

    double ln = leftPointApproximation(a, b, delX, n);
    double rn = rightPointApproximation(a, b, delX, n);
    double mn = midPointApproximation(a, b, delX, n);
    double actual = integrate(a, b);

    cout << "Ln: " << ln << endl;


    cout << "Rn: " << rn << endl;

    cout << "Mn: " << mn << endl;

    cout << endl;
    cout << "Ln Error: " << (actual-ln)/(actual*1.00)*100 << endl;
    cout << "Rn Error: " << (-1)*(actual-rn)/(actual*1.00)*100 << endl;
    cout << "Mn Error: " << (actual-mn)/(actual*1.00)*100 << endl;

}

void reshape(int width, int height) {
    // specify viewport
    glViewport(0, 0, width, height);
    // select projection matrix
    glMatrixMode(GL_PROJECTION);
    // reset projection matrix
    glLoadIdentity();
    // specify projection
    glOrtho(-12, 500, -12, 500, -1, 1);
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

    numerical_integration();
}

void displayLeft(void) {
    glClearColor(212,223,158, 0);
    glEnable(GL_COLOR_MATERIAL);

    glClear(GL_COLOR_BUFFER_BIT);

    // Coordinate Axis
    glColor3ub(0,0,0);
    glPointSize(1);
    glPushMatrix();
    glBegin(GL_LINES);
    // x axis
    glVertex2i(-12,0);
    glVertex2i(500,0);
    // y axis
    glVertex2i(0,-12);
    glVertex2i(0,500);
    glEnd();
    glPopMatrix();

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
    Boxes
    */
    int i = 0;
    for(Point point : leftPoints) {
        glPushMatrix();
        glColor4ub(255, 0, 0, 128);
        glBegin(GL_QUADS);
            glVertex2d(xScale * point.x, yScale * 0);
            glVertex2d(xScale * point.x, yScale * point.y);
            glVertex2d(xScale * (point.x+delX), yScale * point.y);
            glVertex2d(xScale * (point.x+delX), yScale * 0);

        glEnd();
        glPopMatrix();
        i++;
    }


    /*
    f(x)
    */
    glColor3ub(255, 200, 0);
    glPointSize(1);
    glPushMatrix();
    glBegin(GL_POINTS);
        for(double x=xLow-xOffset; x<=xHigh+xOffset; x+=h) {
            glVertex2d(xScale * x, yScale * f(x));
        }
    glEnd();
    glPopMatrix();

    /*
    Left Points
    */
    color = colors[0];
    glColor3ub(color.r, color.g, color.b);
    glPointSize(4);
    glPushMatrix();
    glBegin(GL_POINTS);
    for(Point point : leftPoints) {
        glVertex2d(xScale * point.x, yScale * point.y);
    }
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void displayRight(void) {
    glClearColor(212,223,158, 0);
    glEnable(GL_COLOR_MATERIAL);

    glClear(GL_COLOR_BUFFER_BIT);

    // Coordinate Axis
    glColor3ub(0,0,0);
    glPointSize(1);
    glPushMatrix();
    glBegin(GL_LINES);
    // x axis
    glVertex2i(-12,0);
    glVertex2i(500,0);
    // y axis
    glVertex2i(0,-12);
    glVertex2i(0,500);
    glEnd();
    glPopMatrix();

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
    Boxes
    */
    int i = 0;
    for(Point point : rightPoints) {
        glPushMatrix();
        glColor4ub(255, 0, 0, 128);
        glBegin(GL_QUADS);
            glVertex2d(xScale * point.x, yScale * 0);
            glVertex2d(xScale * point.x, yScale * point.y);
            glVertex2d(xScale * (point.x-delX), yScale * point.y);
            glVertex2d(xScale * (point.x-delX), yScale * 0);
        glEnd();
        glPopMatrix();
        i++;
    }
    
    /*
    f(x)
    */
    glColor3ub(255, 200, 0);
    glPointSize(1);
    glPushMatrix();
    glBegin(GL_POINTS);
        for(double x=xLow-xOffset; x<=xHigh+xOffset; x+=h) {
            glVertex2d(xScale * x, yScale * f(x));
        }
    glEnd();
    glPopMatrix();


    /*
    Right Points
    */
    color = colors[0];
    glColor3ub(color.r, color.g, color.b);
    glPointSize(4);
    glPushMatrix();
    glBegin(GL_POINTS);
    for(Point point : rightPoints) {
        glVertex2d(xScale * point.x, yScale * point.y);
    }
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void displayMid(void) {
    
    glClearColor(212,223,158, 0);
    glEnable(GL_COLOR_MATERIAL);

    glClear(GL_COLOR_BUFFER_BIT);

    // Coordinate Axis
    glColor3ub(0,0,0);
    glPointSize(1);
    glPushMatrix();
    glBegin(GL_LINES);
    // x axis
    glVertex2i(-12,0);
    glVertex2i(500,0);
    // y axis
    glVertex2i(0,-12);
    glVertex2i(0,500);
    glEnd();
    glPopMatrix();

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
    Boxes
    */
    int i = 0;
    for(Point point : midPoints) {
        glPushMatrix();
        glColor4ub(255, 0, 0, 128);
        glBegin(GL_QUADS);
            glVertex2d(xScale * (point.x-(delX/2.00)), yScale * 0);
            glVertex2d(xScale * (point.x-(delX/2.00)), yScale * point.y);
            glVertex2d(xScale * (point.x+(delX/2.00)), yScale * point.y);
            glVertex2d(xScale * (point.x+(delX/2.00)), yScale * 0);
        glEnd();
        glPopMatrix();
        i++;
    }
    
    /*
    f(x)
    */
    glColor3ub(255, 200, 0);
    glPointSize(1);
    glPushMatrix();
    glBegin(GL_POINTS);
        for(double x=xLow-xOffset; x<=xHigh+xOffset; x+=h) {
            glVertex2d(xScale * x, yScale * f(x));
        }
    glEnd();
    glPopMatrix();


    /*
    Mid Points
    */
    color = colors[0];
    glColor3ub(color.r, color.g, color.b);
    glPointSize(4);
    glPushMatrix();
    glBegin(GL_POINTS);
    for(Point point : midPoints) {
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

    myInit();

    glutCreateWindow("86 - Left");
    glutReshapeFunc(reshape);
    glutDisplayFunc(displayLeft);
    glutIdleFunc(idle);

    glutCreateWindow("86 - Right");
    glutReshapeFunc(reshape);
    glutDisplayFunc(displayRight);
    glutIdleFunc(idle);

    glutCreateWindow("86 - Mid");
    glutReshapeFunc(reshape);
    glutDisplayFunc(displayMid);
    glutIdleFunc(idle);


    glutMainLoop();

    return EXIT_SUCCESS;
}
