#include <GL/glut.h>
#define Width 800
#define Height 600
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

double x_l = 0;
double x_u = 1;
double h = 0.001;
int n = 1000;
double x;
double table[1110][5];

// g++ main.cpp -o opengl -lGL -lGLU -lglut
// ./opengl

/*  
    f(x)    = x^3 - 7x _1 
    f'(x)   = 3x^2 - 7 
    g1(x)   = x
    g2(x)   = (x^3 + 1)/7
*/

static void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Width/2, Width/2, -Height/2, Height/2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(255,255,255);
    glPushMatrix();
    glBegin(GL_LINES);
    glVertex2i(-Width/2,0);
    glVertex2i(Width/2,0);
    glVertex2i(0,-Height/2);
    glVertex2i(0,Height/2);
    glEnd();
    glPopMatrix();

    double xScale = 800;
    double yScale = 800;

    // f(x)
    glColor3ub(255,0,0);
    glPointSize(1);
    glPushMatrix();
    glBegin(GL_POINTS);
    for (int i = 0; i < n; i++) {
        glVertex2d(xScale * (i/1000.00), yScale * table[i][1]);
    }
    glEnd();
    glPopMatrix();
    
    // g1(x)
    glColor3ub(255,255,0);
    glPointSize(1);
    glPushMatrix();
    glBegin(GL_POINTS);
    for (int i = 0; i < n; i++) {
        glVertex2d(xScale * (i/1000.00), yScale * table[i][2]);
    }
    glEnd();
    glPopMatrix();
    

    // g2(x)
    glColor3ub(0,255,0);
    glPointSize(1);
    glPushMatrix();
    glBegin(GL_POINTS);
    for (int i = 0; i < n; i++) {
        glVertex2d(xScale * (i/1000.00), yScale * table[i][3]);
    }
    glEnd();
    glPopMatrix();
    

    glutSwapBuffers();
}

static void idle(void) {
    glutPostRedisplay();
}

void myInit(void) {
    glClearColor(0,0,0,1);
    glEnable(GL_COLOR_MATERIAL);

}
const GLfloat high_shininess[] = { 100.0f };

double calculateFx(double x) {
    return (x*x*x) - (7*x) +1;
}

double calculateG1x(double x) {
    return x;
}

double calculateG2x(double x) {
    return ((x*x*x) + 1)/7.00;
}

void populateTable() {
    x = x_l;
    for(int i = 0; i<n; i++) {
        table[i][1] = calculateFx(x);
        x += h;
    }

    x = x_l;
    for(int i = 0; i<n; i++) {
        table[i][2] = calculateG1x(x);
        x += h;
    }

    x = x_l;
    for(int i = 0; i<n; i++) {
        table[i][3] = calculateG2x(x);
        x += h;
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(10, 50);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("Newton-Raphson");

    glutReshapeFunc(reshape);
    myInit();
    populateTable();
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}