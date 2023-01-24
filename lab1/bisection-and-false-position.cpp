#include <GL/glut.h>
#define Width 1920
#define Height 1080
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

double table[11][3];

// g++ main.cpp -o opengl -lGL -lGLU -lglut
// ./opengl

static void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Width/2, Width/2-1, -Height/2, Height/2-1, -1, 1);
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

    double xScale = 100;
    double yScale = 5;

    // Bisection
    glColor3ub(255,0,0);
    glPointSize(5);
    glPushMatrix();
    glBegin(GL_POINTS);
    for (int i = 1; i < 10; i++) {
        glVertex2d(xScale * i, yScale * table[i][1]);
    }
    glEnd();
    glPopMatrix();
    
    glColor3ub(255,0,0);
    glPointSize(1);
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    for (int i = 1; i < 10; i++) {
        glVertex2d(xScale * i, yScale * table[i][1]);
    }
    glEnd();
    glPopMatrix();

    // False Position
    glColor3ub(255,255,0);
    glPointSize(5);
    glPushMatrix();
    glBegin(GL_POINTS);
    for (int i = 1; i < 10; i++) {
        glVertex2d(xScale * i, yScale * table[i][2]);
    }
    glEnd();
    glPopMatrix();
    
    glColor3ub(255,255,0);
    glPointSize(1);
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    for (int i = 1; i < 10; i++) {
        glVertex2d(xScale * i, yScale * table[i][2]);
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

double mathFunction(double x) {
    return 3 * x + sin(x) - exp(x);
}

void bisection(double x_l, double x_u) {
    double x_r, f_x, x_r_old;
    for (int i = 0; i < 10; i++) {
        table[i][0] = i + 1;
        x_r = (x_l + x_u) / 2;
        f_x = mathFunction(x_r);
        table[i][1] = (abs(x_r - x_r_old) / x_r) * 100;
        if (f_x < 0) {
            x_l = x_r;
        } else {
            x_u = x_r;
        }
        x_r_old = x_r;
    }

    x_l = 0;
    x_u = 1;
    x_r = x_u;
}

void falsePosition(double x_l, double x_u) {
    double x_r, f_x, x_r_old;
    double f_l, f_u;

    x_r = x_u;
    for (int i = 0; i < 10; i++) {
        f_x = mathFunction(x_r);
        f_l = mathFunction(x_l);
        f_u = mathFunction(x_u);
        x_r = (x_l * f_u - x_u * f_l) / (f_u - f_l);
        table[i][2] = (abs(x_r - x_r_old) / x_r) * 100;
        if (f_x < 0) {
            x_l = x_r;
        } else {
            x_u = x_r;
        }
        x_r_old = x_r;
    }
}

void populateTable() {
    double x_l = 0;
    double x_u = 1;
    
    // Bisection
    bisection(x_l, x_u);

    // False Position
    falsePosition(x_l, x_u);


    printf(" i |        erorr - bisection  |        erorr - false position\n", 1);
    printf("---------------------------------------------------------------\n");
    printf("%2d |                     N/A   |                            N/A\n", 1);
    for (int i = 1; i < 10; i++) {
        printf("%2d | %25f | %30lf \n", (int)table[i][0], table[i][1], table[i][2]);
    }

}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(10, 50);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutCreateWindow("Bisection-and-False-Position");

    glutReshapeFunc(reshape);
    myInit();
    populateTable();
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}