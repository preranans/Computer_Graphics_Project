#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PI 3.14159
void display();
float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle = 0.0;
float cRadius = 10.0f; // our radius distance from our character
float lastx, lasty;
float positionz[10];
float positionx[10];
int df = 10;
void output(char *string)
{
    int len, i;
    glRasterPos3d(0, -0.6, 60); // sets the current raster position in 3D space using double-precision coordinates.Used to specify where the text should be displayed on the screen.
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]); // 24 pixels
}

void cube()
{
    glPushMatrix();
    glColor3f(1, 1, 1); // white
    glutSolidCube(1);   // each side 1 unit
    glPopMatrix();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); // set the viewportto the current window specifications
    glMatrixMode(GL_PROJECTION);              // set the matrix to projection
    glLoadIdentity();
    gluPerspective(87, (GLfloat)w / (GLfloat)h, 1, 5000.0); // set the perspective (angle of sight, width, near,far))
    glMatrixMode(GL_MODELVIEW);                             // set the matrix back to model which is default mode used for defining transformations on objects.
}

void mouseMovement(int x, int y) // takes current position of x and y
{
    int diffx = x - lastx; // check and store the difference between the current x and the last x position
    int diffy = y - lasty; // check and store the difference between the current y and the last y position
    lastx = x;             // set lastx to the current x position
    lasty = y;             // set lasty to the current y position
    xrot += (float)diffy;  // when the mouse is moved up or down (diffy positive or negative), the value of xrot will increase or decrease respectively. This can be used to control the rotation of objects around the x-axis.
    if (xrot > 140)
        xrot -= 140;
    if (xrot < -90)
        xrot += 90;       // set the xrot to xrot with the addition of the difference in the y position
    yrot += (float)diffx; // set the xrot to yrot with the addition of the difference in the x position, when the mouse is moved left or right (diffx positive or negative), the value of yrot will increase or decrease respectively.
}

void keyboard(unsigned char key, int x, int y)
{

    if (key == 'z') // upward movement
    {
        xrot += 1;
        if (xrot > 90)
            xrot -= 90;
    }

    if (key == 'q') // downward movement
    {
        xrot -= 1;
        if (xrot < -90)
            xrot += 90;
    }

    if (key == 'w') // forward
    {
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f); // radians conversion
        xrotrad = (xrot / 180 * 3.141592654f); ////radians conversion
        xpos += (float)(sin(yrotrad));         // The xpos is incremented by the sine of yrotrad, representing movement along the x-axis in the direction determined by the y-rotation.
        zpos -= (float)(cos(yrotrad));         // representing movement along the z-axis in the direction opposite to the y-rotation.
        ypos -= (float)(sin(xrotrad));         //,representing movement along the y-axis in the opposite direction to the x-rotation.
    }

    if (key == 's')
    {
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        xpos -= (float)(sin(yrotrad));
        zpos += (float)(cos(yrotrad));
        ypos += (float)(sin(xrotrad));
    }

    if (key == 'd')
    {
        float yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xpos += (float)(cos(yrotrad));
        zpos += (float)(sin(yrotrad));
    }

    if (key == 'a')
    {
        float yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xpos -= (float)(cos(yrotrad));
        zpos -= (float)(sin(yrotrad));
    }
}

void stripes()
{
    glPushMatrix();
    glTranslated(0, 0.2, 0);
    glRotated(0, 0, 0, 0);
    glColor3f(0.95, 0.95, 0.95); // light grey
    glScalef(12, 0.28, 0.8);     // length,height,width
    glutSolidCube(1);
    glPopMatrix();
}

void crossing()
{
    glPushMatrix();
    glTranslated(0, 0.2, 0);
    glRotated(0, 0, 0, 0);
    glColor3f(0.95, 0.95, 0.95);
    glScalef(10, 0.28, 3);
    glutSolidCube(1);
    glPopMatrix();
}

void parking()
{
    glPushMatrix();
    glColor3f(0.65, 0.65, 0.65); // light grey
    glScaled(180, 0.5, 12);
    glutSolidCube(1);
    glPopMatrix();
}

void ground()
{
    glPushMatrix(); // green ground
    glColor3f(0.180392, 0.545098, 0.341176);
    glTranslated(0, -0.79, 0);
    glScaled(640, 0.2, 640);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix(); // road
    glTranslated(0, 0.1, 0);
    glRotated(0, 0, 0, 0);
    glColor3f(0.35, 0.35, 0.35); // grey
    glScalef(40, 0.2, 640);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix(); // another road
    glTranslated(0, 0.1, 0);
    glRotated(90, 0, 1, 0);
    glColor3f(0.35, 0.35, 0.35);
    glScalef(40, 0.2, 640);
    glutSolidCube(1);
    glPopMatrix();

    // sides white
    glPushMatrix();
    glTranslated(-18, 0.2, -170);
    glRotated(0, 0, 0, 0);
    glColor3f(0.95, 0.95, 0.95);
    glScalef(0.5, 0.28, 300);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-18, 0.2, 170);
    glRotated(0, 0, 0, 0);
    glColor3f(0.95, 0.95, 0.95);
    glScalef(0.5, 0.28, 300);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(18, 0.2, -170);
    glRotated(0, 0, 0, 0);
    glColor3f(0.95, 0.95, 0.95);
    glScalef(0.5, 0.28, 300);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(18, 0.2, 170);
    glRotated(0, 0, 0, 0);
    glColor3f(0.95, 0.95, 0.95);
    glScalef(0.5, 0.28, 300);
    glutSolidCube(1);
    glPopMatrix();

    // sides rotated white
    glPushMatrix();
    glTranslated(-170, 0.2, -18);
    glColor3f(0.95, 0.95, 0.95);
    glScalef(300, 0.28, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslated(170, 0.2, -18);
    glColor3f(0.95, 0.95, 0.95);
    glScalef(300, 0.28, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-170, 0.2, 18);
    glColor3f(0.95, 0.95, 0.95);
    glScalef(300, 0.28, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(170, 0.2, 18);
    glColor3f(0.95, 0.95, 0.95);
    glScalef(300, 0.28, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // stripes
    glPushMatrix();
    glTranslated(45, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(65, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(85, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(105, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(125, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(145, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(165, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(185, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(205, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(225, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(245, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(265, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(285, 0, 0);
    stripes();
    glPopMatrix();

    // stripes2
    glPushMatrix();
    glTranslated(-45, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-65, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-85, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-105, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-125, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-145, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-165, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-185, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-205, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-225, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-245, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-265, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-285, 0, 0);
    stripes();
    glPopMatrix();

    // stripes rotated
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(45, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(65, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(85, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(105, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(125, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(145, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(165, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(185, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(205, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(225, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(245, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(265, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(285, 0, 0);
    stripes();
    glPopMatrix();

    // stripes rotated 2
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(-45, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(-65, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(-85, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(-105, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(-125, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(-145, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(-165, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(-185, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(-205, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(-225, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(-245, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(-265, 0, 0);
    stripes();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslated(-285, 0, 0);
    stripes();
    glPopMatrix();

    // crossing1
    glPushMatrix();
    glTranslated(30, 0, 0);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glTranslated(30, 0, 5);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glTranslated(30, 0, 10);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glTranslated(30, 0, 15);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glTranslated(30, 0, -5);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glTranslated(30, 0, -10);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glTranslated(30, 0, -15);
    crossing();
    glPopMatrix();

    // crossing2
    glPushMatrix();
    glTranslated(-30, 0, 0);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-30, 0, 5);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-30, 0, 10);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-30, 0, 15);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-30, 0, -5);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-30, 0, -10);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-30, 0, -15);
    crossing();
    glPopMatrix();

    // crossing3(rotated)
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(30, 0, 0);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(30, 0, 5);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(30, 0, 10);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(30, 0, 15);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(30, 0, -5);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(30, 0, -10);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(30, 0, -15);
    crossing();
    glPopMatrix();

    // crossing4(rotated)
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(-30, 0, 0);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(-30, 0, 5);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(-30, 0, 10);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(-30, 0, 15);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(-30, 0, -5);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(-30, 0, -10);
    crossing();
    glPopMatrix();

    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(-30, 0, -15);
    crossing();
    glPopMatrix();

    // green pitch
    glPushMatrix();
    glTranslated(-120, 0, -120);
    glColor3f(0.137, 0.556, 0.137);
    glScalef(150, 0.2, 150);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(120, 0, -120);
    glColor3f(0.137, 0.556, 0.137);
    glScalef(150, 0.2, 150);
    glutSolidCube(1);
    glPopMatrix();
}
void house1()
{
    // front
    glPushMatrix();
    glColor3f(0.94, 0.81, 0.99); // light purple

    glTranslated(0, 0, 0);
    glScaled(80, 70, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // back
    glPushMatrix();
    glColor3f(0.94, 0.81, 0.99);

    glTranslated(0, 0, 60);
    glScaled(80, 70, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // left
    glPushMatrix();
    glColor3f(0.94, 0.81, 0.99);
    glTranslated(-40, 0, 30);
    glScaled(0.5, 70, 60);
    glutSolidCube(1);
    glPopMatrix();
    // right
    glPushMatrix();
    glColor3f(0.94, 0.81, 0.99);
    glTranslated(40, 0, 30);
    glScaled(0.5, 70, 60);
    glutSolidCube(1);
    glPopMatrix();

    // top1
    glPushMatrix();
    glColor3f(0.5, 0.184314, 0.184314); // reddish brown
    glRotated(30, 1, 0, 0);
    glTranslated(0, 60, 20);
    glScaled(80, 0.5, 42);
    glutSolidCube(1);
    glPopMatrix();
    // top2
    glPushMatrix();
    glColor3f(0.5, 0.184314, 0.184314);
    glRotated(-30, 1, 0, 0);
    glTranslated(0, 30, 30);
    glScaled(80, 0.5, 42);
    glutSolidCube(1);
    glPopMatrix();
    // door
    glPushMatrix();
    glColor3f(0.36, 0.25, 0.2); // brown
    glTranslated(20, -25, -0.3);
    glScaled(12, 20, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // windows
    // window1
    glPushMatrix();
    glColor3f(1, 1, 0); // yellow
    glTranslated(0, 20, -0.3);
    glScaled(5, 10, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // window2
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(-6, 20, -0.3);
    glScaled(5, 10, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // window3
    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotated(0, 0, 0, 0);
    glTranslated(-25, 20, -0.3);
    glScaled(5, 10, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // window4
    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotated(0, 0, 0, 0);
    glTranslated(-19, 20, -0.3);
    glScaled(5, 10, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // windows down
    // window1
    glPushMatrix();
    glTranslated(0, -30, 0);
    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotated(0, 0, 0, 0);
    glTranslated(0, 20, -0.3);
    glScaled(5, 10, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // window2
    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotated(0, 0, 0, 0);
    glTranslated(-6, 20, -0.3);
    glScaled(5, 10, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // window3
    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotated(0, 0, 0, 0);
    glTranslated(-25, 20, -0.3);
    glScaled(5, 10, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    // window4
    glPushMatrix();
    glColor3f(1, 1, 0);
    glRotated(0, 0, 0, 0);
    glTranslated(-19, 20, -0.3);
    glScaled(5, 10, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();

    // seperation
    glPushMatrix();
    glTranslated(0, 0, 30);
    glColor3f(0.5, 0.184314, 0.184314);
    glScalef(90, 0.2, 70);
    glutSolidCube(1);
    glPopMatrix();
}

void camera_man()
{
    // camera and man
    glTranslatef(0.0f, -5.0f, (-cRadius / 2)); // camera position
    glRotatef(xrot, 1.0, 0.0, 0.0);            // camera rotation angle in x axis

    glPushMatrix();
    glTranslatef(0.0f, -2.0f, -cRadius);
    glColor3f(1, 1, 0);
    glScalef(0.9, 1.8, 1);
    glutSolidSphere(1, 16, 16); // chest (radius,longitude,latitude)
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.7f, -cRadius);
    // glColor3f(0.870588,0.721569,0.529412);
    glColor3f(0, 0, 0); // black
    glScalef(0.8, 1.3, 0.8);
    glutSolidSphere(1, 16, 16); // head
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2f, -1.3f, -cRadius);
    glRotatef(-30, 0, 0, 1);
    glColor3f(1, 1, 0);
    glScalef(0.3, 1, 0.3);
    glutSolidSphere(1, 16, 16); // left upper arm
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.5f, -2.9f, -cRadius - 0.2);
    glRotatef(20, 1, 0, 0);
    glColor3f(0.870588, 0.721569, 0.529412);
    glScalef(0.3, 1, 0.3);
    glutSolidSphere(1, 16, 16); // left lower arm
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.2f, -1.3f, -cRadius);
    glRotatef(30, 0, 0, 1);
    glColor3f(1, 1, 0);
    glScalef(0.3, 1, 0.3);
    glutSolidSphere(1, 16, 16); // right upper arm
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5f, -2.9f, -cRadius - 0.2);
    glRotatef(20, 1, 0, 0);
    glColor3f(0.870588, 0.721569, 0.529412);
    glScalef(0.3, 1, 0.3);
    glutSolidSphere(1, 16, 16); // right lower arm
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.6f, -4.7f, -cRadius);
    glRotatef(5, 0, 0, 1);
    glColor3f(0, 0, 1);
    glScalef(0.4, 1.3, 0.3);
    glutSolidSphere(1, 16, 16); // right upper leg
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.7f, -6.7f, -cRadius);
    glRotatef(3, 0, 0, 1);
    glColor3f(0, 0, 1);
    glScalef(0.3, 1.2, 0.27);
    glutSolidSphere(1, 16, 16); // right lower leg
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6f, -4.7f, -cRadius);
    glRotatef(-5, 0, 0, 1);
    glColor3f(0, 0, 1);
    glScalef(0.4, 1.3, 0.3);
    glutSolidSphere(1, 16, 16); // left upper leg
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.7f, -6.7f, -cRadius);
    glRotatef(-3, 0, 0, 1);
    glColor3f(0, 0, 1);
    glScalef(0.3, 1.2, 0.27);
    glutSolidSphere(1, 16, 16); // left lower leg
    glPopMatrix();
    glRotatef(yrot, 0.0, 1.0, 0.0);    // rotate our camera on the y-axis (up and down)
    glTranslated(-xpos, -8.0f, -zpos); // translate the screen to the position of our camera(lower body)
}

void stars()
{
    // moon
    glPushMatrix();
    glColor3f(0.9, 0.9, 0.9);
    glTranslatef(500, 700, -500);
    glutSolidSphere(50, 16, 16);
    glPopMatrix();
    glTranslated(0, 500, 0);
    { // stars
        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 400, 330);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4200, 600, 3100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1400, 300, 4150);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2600, 200, 4440);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3800, 700, 4450);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3000, 400, 4170);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1200, 500, 4420);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1400, 300, 4200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1600, 900, 4100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1800, 1000, 440);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-2000, 600, 4450);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(40, 300, -4100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4200, 300, -4420);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4400, 300, -4200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4600, 300, -4450);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4800, 300, -4175);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4000, 300, -4150);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4200, 300, -4480);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4400, 300, -4490);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4600, 300, -140);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4800, 300, 4440);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4000, 300, -4100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(5000, 400, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2200, 600, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4400, 300, -4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 200, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4800, 700, -4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4000, 400, -4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3200, 450, -4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3400, 300, -4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4600, 900, -100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4800, 1000, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4000, 600, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2400, 300, -1200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4200, 300, -1400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4400, 300, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4600, 300, -1300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3800, 300, -1900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(5000, 300, -1800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4200, 300, -1500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4400, 300, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4600, 300, -1200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3800, 300, -1800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3000, 300, -400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3330, 400, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3200, 600, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3400, 300, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3600, 200, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3800, 700, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3000, 400, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3200, 500, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3400, 300, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3600, 900, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3800, 1000, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3000, 600, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3000, 300, -4200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3200, 300, -4400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3400, 300, -4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3600, 300, -4300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3800, 300, -4900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3000, 300, -4800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3200, 300, -4500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3400, 300, -4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3600, 300, -4200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3800, 300, -4800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3000, 300, -4400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(330, 400, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3200, 600, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3400, 300, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3600, 200, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3800, 700, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3000, 400, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3200, 500, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3400, 300, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3600, 900, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3800, 1000, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3000, 600, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3330, 300, -3200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3200, 300, -3400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3400, 300, -3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3600, 300, -3300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3800, 300, -3900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3000, 300, -3800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3200, 300, -3500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3400, 300, -3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3600, 300, -3200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4800, 300, -3800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-5000, 300, -3400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4440, 400, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4200, 600, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4400, 300, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4600, 200, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4800, 700, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4000, 400, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4200, 500, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4400, 300, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4600, 900, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4800, 1000, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-5000, 600, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4300, 300, 2200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3200, 300, 2400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4400, 300, 2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4600, 300, 2300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4800, 300, 2900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(5000, 300, 2800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1200, 300, 2500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-2400, 300, 2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-2600, 300, 2200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-2800, 300, 2800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3000, 300, 2400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(5000, 400, 0);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4200, 600, 100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2400, 300, 150);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3600, 200, 0);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3800, 700, 50);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(5000, 400, 170);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4200, 500, 20);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4400, 300, 200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4600, 900, 100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3800, 1000, 0);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-5000, 600, 50);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4330, 300, -100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2200, 300, -20);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4400, 300, -200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4600, 300, -50);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2800, 300, -175);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2000, 300, -150);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3200, 300, -80);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3400, 300, -90);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3600, 300, -10);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3800, 300, 0);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3000, 300, -100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3330, 400, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3200, 600, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3400, 300, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3600, 200, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3800, 700, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3000, 400, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3200, 500, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3400, 300, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3600, 900, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3800, 1000, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3000, 600, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4440, 300, -1200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4200, 300, -1400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4400, 300, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4600, 300, -1300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4800, 300, -1900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4000, 300, -1800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4200, 300, -1500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4400, 300, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4600, 300, -1200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4800, 300, -1800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-5000, 300, -1400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4440, 400, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4200, 600, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4400, 300, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4600, 200, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4800, 700, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(5000, 400, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4200, 500, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4400, 300, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4600, 900, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4800, 1000, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4000, 600, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4440, 300, 1200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1200, 300, 1400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1400, 300, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2600, 300, 1300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2800, 300, 1900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 300, 4800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-2200, 300, 1500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3400, 300, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3600, 300, 1200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4800, 300, 1800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4000, 300, 1400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(40, 400, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2200, 600, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2400, 300, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2600, 200, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2800, 700, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3000, 400, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4200, 500, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4400, 300, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4600, 900, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4800, 1000, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3000, 600, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3330, 300, -200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3200, 300, -400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3400, 300, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3600, 300, -300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3800, 300, -900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(5000, 300, -800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3200, 300, -500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4400, 300, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3600, 300, -200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4800, 300, -800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4000, 300, -400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4440, 400, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(5000, 600, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(40, 300, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1600, 200, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2800, 700, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3000, 400, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4200, 500, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1400, 300, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-2600, 900, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4800, 1000, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-5000, 600, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(30, 300, 200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2200, 300, 400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4400, 300, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4600, 300, 300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1800, 300, 900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 300, 20);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1200, 300, 500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4400, 300, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4600, 300, 200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4800, 300, 800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4000, 300, 400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 400, 0);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4200, 600, 100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1400, 300, 150);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2600, 200, 0);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3800, 700, 50);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3000, 400, 170);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1200, 500, 20);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1400, 300, 200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1600, 900, 100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1800, 1000, 0);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-2000, 600, 50);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(40, 300, -100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4200, 300, -20);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4400, 300, -200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4600, 300, -50);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4800, 300, -175);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4000, 300, -150);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4200, 300, -80);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4400, 300, -90);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4600, 300, -10);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4800, 300, 0);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-4000, 300, -100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(30, 400, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3200, 600, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3400, 300, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3600, 200, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(3800, 700, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(4000, 400, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3200, 500, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3400, 300, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3600, 900, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3800, 1000, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-3000, 600, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(20, 300, -1200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2200, 300, -1400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2400, 300, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2600, 300, -1300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2800, 300, -1900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(2000, 300, -1800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-2200, 300, -1500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-2400, 300, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-2600, 300, -1200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-2800, 300, -1800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-2000, 300, -400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 400, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 600, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 200, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 700, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 400, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 500, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 900, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 1000, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 600, 4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 300, -4200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 300, -4400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, -4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 300, -4300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 300, -4900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 300, -4800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 300, -4500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, -4600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 300, -4200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 300, -4800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 300, -4400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 400, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 600, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 200, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 700, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 400, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 500, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 900, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 1000, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 600, 3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 300, -3200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 300, -3400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, -3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 300, -3300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 300, -3900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 300, -3800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 300, -3500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, -3600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 300, -3200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 300, -3800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 300, -3400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 400, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 600, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 200, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 700, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 400, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 500, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 900, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 1000, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 600, -2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 300, 2200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 300, 2400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, 2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 300, 2300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 300, 2900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 300, 2800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 300, 2500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, 2600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 300, 2200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 300, 2800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 300, 2400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 400, 0);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 600, 100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, 150);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 200, 0);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 700, 50);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 400, 170);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 500, 20);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, 200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 900, 100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 1000, 0);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 600, 50);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 300, -100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 300, -20);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, -200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 300, -50);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 300, -175);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 300, -150);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 300, -80);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, -90);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 300, -10);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 300, 0);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 300, -100);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 400, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 600, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 200, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 700, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 400, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 500, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 900, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 1000, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 600, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 300, -1200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 300, -1400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 300, -1300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 300, -1900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 300, -1800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 300, -1500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, -1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 300, -1200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 300, -1800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 300, -1400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 400, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 600, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 200, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 700, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 400, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 500, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 900, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 1000, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 600, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 300, 1200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 300, 1400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 300, 1300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 300, 1900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 300, 1800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 300, 1500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, 1600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 300, 1200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 300, 1800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 300, 1400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 400, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 600, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 200, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 700, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 400, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 500, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 900, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 1000, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 600, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 300, -200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 300, -400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 300, -300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 300, -900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 300, -800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 300, -500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, -600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 300, -200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 300, -800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 300, -400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 400, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 600, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 200, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 700, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 400, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 500, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 900, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 1000, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 600, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(0, 300, 200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(200, 300, 400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(400, 300, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(600, 300, 300);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(800, 300, 900);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(1000, 300, 800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-200, 300, 500);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-400, 300, 600);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-600, 300, 200);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-800, 300, 800);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.91, 0.98);
        glTranslatef(-1000, 300, 400);
        glutSolidSphere(4, 16, 16);
        glPopMatrix();
    }
}

void window()//building1,2
{
    glPushMatrix();
    glColor3f(0, 0.255, 0.255);
    glScalef(10, 10, 0.5);
    glutSolidCube(1);
    glPopMatrix();
}

void window2()//building3
{
    glPushMatrix();
    glColor3f(0, 0.255, 0.255);
    glScalef(20, 15, 0.5);
    glutSolidCube(1);
    glPopMatrix();
}

void building1()//3 storey
{
    //first tier
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    glPushMatrix();
    glColor3f(0.81,0.71,0.23);//gold
    glTranslated(0,50,0);
    glScalef(60, 102, 60);
    glutSolidCube(1);
    glPopMatrix();
     //second tier
    glPushMatrix();
    glColor3f(0.81,0.71,0.23);
    glTranslated(0, 130, 0);
    glScalef(40, 60, 40);
    glutSolidCube(1);
    glPopMatrix();
    //third tier
    glPushMatrix();
    glColor3f(0.81,0.71,0.23);
    glTranslated(0, 160, 0);
    glScalef(10, 60, 10);
    glutSolidCube(1);
    glPopMatrix();

    // door
    glPushMatrix();
    glColor3f(0, 0.255, 0.255);//window colour
    glTranslated(10, 10, -30);
    glScalef(10, 20, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    {//placing windows
        // 1strow
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(22, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-22, 35, -30);
        window();
        glPopMatrix();

        // 2ndrow
        glPushMatrix();
        glTranslated(0, 15, 0);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(22, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-22, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // 3rdrow
        glPushMatrix();
        glTranslated(0, 30, 0);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(22, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-22, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // 4throw
        glPushMatrix();
        glTranslated(0, 45, 0);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(22, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-22, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // 5throw
        glPushMatrix();
        glTranslated(0, 60, 0);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(22, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix(); // camera
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-22, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // 2ndstep_1strow
        glPushMatrix();
        glTranslated(0, 75, 10);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // 2ndstep_2strow
        glPushMatrix();
        glTranslated(0, 90, 10);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // 2ndstep_3strow
        glPushMatrix();
        glTranslated(0, 105, 10);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // 2ndstep_4strow
        glPushMatrix();
        glTranslated(0, 119, 10);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // laststep
        glPushMatrix();
        glTranslated(0, 135, 20);
        glPushMatrix();
        glTranslated(0, 35, -30);
        glScaled(8, 15, 0.5);
        glutSolidCube(1);
        glPopMatrix();
        glPopMatrix();
    }
//left side
    {
        glPushMatrix();
        glRotated(90, 0, 1, 0);
        // 1strow
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(22, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-22, 35, -30);
        window();
        glPopMatrix();

        // 2ndrow
        glPushMatrix();
        glTranslated(0, 15, 0);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(22, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-22, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // 3rdrow
        glPushMatrix();
        glTranslated(0, 30, 0);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(22, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-22, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // 4throw
        glPushMatrix();
        glTranslated(0, 45, 0);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(22, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-22, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // 5throw
        glPushMatrix();
        glTranslated(0, 60, 0);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(22, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-22, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // 2ndstep_1strow
        glPushMatrix();
        glTranslated(0, 75, 10);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // 2ndstep_2strow
        glPushMatrix();
        glTranslated(0, 90, 10);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // 2ndstep_3strow
        glPushMatrix();
        glTranslated(0, 105, 10);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // 2ndstep_4strow
        glPushMatrix();
        glTranslated(0, 119, 10);
        glPushMatrix();
        glTranslated(0, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(11, 35, -30);
        window();
        glPopMatrix();
        glPushMatrix();
        glTranslated(-11, 35, -30);
        window();
        glPopMatrix();
        glPopMatrix();

        // laststep
        glPushMatrix();
        glTranslated(0, 135, 20);
        glPushMatrix();
        glTranslated(0, 35, -30);
        glScaled(8, 15, 0.5);
        glutSolidCube(1);
        glPopMatrix();
        glPopMatrix();

        glPopMatrix();
    }
    //right side
    glPushMatrix();
    glRotated(-90, 0, 1, 0);

    // 1strow
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();

    // 2ndrow
    glPushMatrix();
    glTranslated(0, 15, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 3rdrow
    glPushMatrix();
    glTranslated(0, 30, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 4throw
    glPushMatrix();
    glTranslated(0, 45, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 5throw
    glPushMatrix();
    glTranslated(0, 60, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 2ndstep_1strow
    glPushMatrix();
    glTranslated(0, 75, 10);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 2ndstep_2strow
    glPushMatrix();
    glTranslated(0, 90, 10);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 2ndstep_3strow
    glPushMatrix();
    glTranslated(0, 105, 10);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 2ndstep_4strow
    glPushMatrix();
    glTranslated(0, 119, 10);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // laststep
    glPushMatrix();
    glTranslated(0, 135, 20);
    glPushMatrix();
    glTranslated(0, 35, -30);
    glScaled(8, 15, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

void building2()
{

    glPushMatrix();
    glColor3f(1, 1, 0.75);//whitish yellow
    glTranslated(0, 70, 0);
    glScalef(60, 140, 60);
    glutSolidCube(1);
    glPopMatrix();

    // door
    glPushMatrix();
    glColor3f(0, 0.255, 0.255);
    glTranslated(10, 10, -30);
    glScalef(10, 20, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // 1strow
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();

    // 2ndrow
    glPushMatrix();//for row
    glTranslated(0, 15, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 3rdrow
    glPushMatrix();
    glTranslated(0, 30, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 4throw
    glPushMatrix();
    glTranslated(0, 45, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 5throw
    glPushMatrix();
    glTranslated(0, 60, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 6throw
    glPushMatrix();
    glTranslated(0, 75, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 7throw
    glPushMatrix();
    glTranslated(0, 90, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();
    
    //side
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    // 1strow
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();

    // 2ndrow
    glPushMatrix();
    glTranslated(0, 15, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 3rdrow
    glPushMatrix();
    glTranslated(0, 30, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 4throw
    glPushMatrix();
    glTranslated(0, 45, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 5throw
    glPushMatrix();
    glTranslated(0, 60, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 6throw
    glPushMatrix();
    glTranslated(0, 75, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 7throw
    glPushMatrix();
    glTranslated(0, 90, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    
    //side 2
    glPushMatrix();
    glRotated(-90, 0, 1, 0);
    // 1strow
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();

    // 2ndrow
    glPushMatrix();
    glTranslated(0, 15, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 3rdrow
    glPushMatrix();
    glTranslated(0, 30, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 4throw
    glPushMatrix();
    glTranslated(0, 45, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 5throw
    glPushMatrix();
    glTranslated(0, 60, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 6throw
    glPushMatrix();
    glTranslated(0, 75, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();

    // 7throw
    glPushMatrix();
    glTranslated(0, 90, 0);
    glPushMatrix();
    glTranslated(0, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(22, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-11, 35, -30);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-22, 35, -30);
    window();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}
void building3()//like school
{
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glPushMatrix();
    glColor3f(0.91, 0.76, 0.65);
    glTranslated(0, 45, 0);
    glScalef(180, 90, 70);
    glutSolidCube(1);
    glPopMatrix();

    // pillars
    glPushMatrix();
    glColor3f(0.36, 0.25, 0.2);
    glTranslated(90, 45, -36);
    glScalef(4, 90, 2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.36, 0.25, 0.2);
    glTranslated(60, 45, -36);
    glScalef(4, 90, 2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.36, 0.25, 0.2);
    glTranslated(30, 45, -36);
    glScalef(4, 90, 2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.36, 0.25, 0.2);
    glTranslated(-90, 45, -36);
    glScalef(4, 90, 2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.36, 0.25, 0.2);
    glTranslated(-60, 45, -36);
    glScalef(4, 90, 2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.36, 0.25, 0.2);
    glTranslated(-30, 45, -36);
    glScalef(4, 90, 2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.36, 0.25, 0.2);
    glTranslated(90, 45, -36);
    glScalef(4, 90, 2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.36, 0.25, 0.2);
    glTranslated(60, 45, -36);
    glScalef(4, 90, 2);
    glutSolidCube(1);
    glPopMatrix();

    // centre
    glPushMatrix();
    glColor3f(0.91, 0.76, 0.65);
    glTranslated(0, 70, -36);
    glScalef(40, 80, 2);
    glutSolidCube(1);
    glPopMatrix();

    // pillar
    glPushMatrix();
    glColor3f(0.36, 0.25, 0.2);
    glTranslated(20, 70, -36.5);
    glScalef(4, 80, 2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.36, 0.25, 0.2);
    glTranslated(-20, 70, -36.5);
    glScalef(4, 80, 2);
    glutSolidCube(1);
    glPopMatrix();

    // front chapra
    glPushMatrix();
    glColor3f(0.36, 0.25, 0.2);
    glTranslated(0, 30, -45);
    glScalef(42, 3, 40);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.36, 0.25, 0.2);
    glTranslated(20, 15, -65);
    glScalef(3, 30, 3);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.36, 0.25, 0.2);
    glTranslated(-20, 15, -65);
    glScalef(3, 30, 3);
    glutSolidCube(1);
    glPopMatrix();

    // windows
    //first row
    glPushMatrix();
    glTranslated(75, 18, -36);
    window2();
    glPopMatrix();
    glPushMatrix();
    glTranslated(45, 18, -36);
    window2();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-75, 18, -36);
    window2();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-45, 18, -36);
    window2();
    glPopMatrix();
    //second row
    glPushMatrix();
    glTranslated(0, 30, 0);
    glPushMatrix();
    glTranslated(75, 18, -36);
    window2();
    glPopMatrix();
    glPushMatrix();
    glTranslated(45, 18, -36);
    window2();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-75, 18, -36);
    window2();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-45, 18, -36);
    window2();
    glPopMatrix();
    glPopMatrix();
    //third row
    glPushMatrix();
    glTranslated(0, 60, 0);
    glPushMatrix();
    glTranslated(75, 18, -36);
    window2();
    glPopMatrix();
    glPushMatrix();
    glTranslated(45, 18, -36);
    window2();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-75, 18, -36);
    window2();
    glPopMatrix();
    glPushMatrix();
    glTranslated(-45, 18, -36);
    window2();
    glPopMatrix();
    glPopMatrix();
    //door
    glPushMatrix();
    glTranslated(0, 13, -36);
    glColor3f(0, 0.255, 0.255);
    glScaled(14, 25, 2);
    glutSolidCube(1);
    glPopMatrix();

    // centre window
    glPushMatrix();
    glTranslated(0, 50, -38);//lower
    glColor3f(0, 0.255, 0.255);
    glScaled(28, 15, 2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 70, -38);//middle
    glColor3f(0, 0.255, 0.255);
    glScaled(28, 15, 2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 90, -38);//higher
    glColor3f(0, 0.255, 0.255);
    glScaled(28, 15, 2);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void trees()
{
    glPushMatrix();
    glColor3f(1, 1, 0);//cone
    glTranslated(0, -3, 0);
    glRotated(-90, 1, 0, 0);
    glutSolidCone(8, 28, 16, 16);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0, -6, 0);//shoot
    glScaled(3, 10, 3);
    glColor3f(0.803922, 0.521569, 0.247059);//brown
    glutSolidCube(1);
    glPopMatrix();
}

void traffic()
{
    // pole
    glPushMatrix();
    glTranslated(18, 12, 18);
    glScalef(0.7, 24, 0.7);
    glutSolidCube(1);
    glPopMatrix();

    // board
    glPushMatrix();
    glTranslated(10, 24, 18);
    glScalef(10, 3, 1);
    glutSolidCube(1);
    glPopMatrix();

    // support
    glPushMatrix();
    glTranslated(17, 24, 18);
    glScalef(4, 1, 1);
    glutSolidCube(1);
    glPopMatrix();

    // red
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslated(13, 24, 18);
    glutSolidSphere(1, 16, 16);
    glPopMatrix();

    // yellow
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(10, 24, 18);
    glutSolidSphere(1, 16, 16);
    glPopMatrix();

    // green
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslated(7, 24, 18);
    glutSolidSphere(1, 16, 16);
    glPopMatrix();
}

void street_light()
{
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);//grey
    glTranslated(0, 23, 0);
    glScalef(1, 46, 1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-7.5, 46, 0);
    glRotated(0, 0, 1, 0);
    glScalef(16, 1, 1);//support for ligt
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(256, 256, 0);//yellow light
    glTranslated(-10, 45, 0);
    glRotated(0, 0, 1, 0);
    glScalef(10, 1, 1);
    glutSolidCube(1);
    glPopMatrix();
}

void display()
{
    glClearColor(0.0, 0.0,0.0, 1.0);//black background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslated(-30, 500, -60);//on sky
    glColor3d(1, 1, 1);//white
    glScaled(100, 100, 10);
    output("SMART CITY 3D BY PRAJWAL AND PRERANA");
    glPopMatrix();

    traffic();
    // street lights
    {
        glPushMatrix();
        glTranslated(21, 0, -50);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, -150);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, -250);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, 50);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, 150);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, 250);
        street_light();
        glPopMatrix();

        // opposite
        glPushMatrix();
        glRotated(180, 0, 1, 0);
        glPushMatrix();
        glTranslated(21, 0, -100);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, -200);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, -300);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, 100);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, 200);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, 300);
        street_light();
        glPopMatrix();
        glPopMatrix();

        //-x
        glPushMatrix();
        glRotated(90, 0, 1, 0);
        glPushMatrix();
        glTranslated(21, 0, -50);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, -150);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, -250);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, 50);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, 150);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, 250);
        street_light();
        glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glRotated(90, 0, 1, 0);
        glPushMatrix();
        glRotated(180, 0, 1, 0);
        glPushMatrix();
        glTranslated(21, 0, -100);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, -200);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, -300);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, 100);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, 200);
        street_light();
        glPopMatrix();
        glPushMatrix();
        glTranslated(21, 0, 300);
        street_light();
        glPopMatrix();
        glPopMatrix();
        glPopMatrix();
    }

    glPushMatrix();
    glColor3f(1, 1, 1);//white
    glTranslated(-36, 0, 0);
    glRotated(90, 0, 1, 0);
    traffic();
    glPopMatrix();

    ground();

    // building1
    glPushMatrix();
    glTranslated(-80, 0, 220);
    building1();
    glPopMatrix();
    // building1
    glPushMatrix();
    glTranslated(-200, 0, 80);
    building1();
    glPopMatrix();
    // building1
    glPushMatrix();
    glTranslated(-200, 0, 220);
    building1();
    glPopMatrix();

    // building2
    glPushMatrix();
    glTranslated(-100, 0, 80);
    building2();
    glPopMatrix();
      // building2
    /*glPushMatrix();
    glTranslated(100, 0, -80);
    building2();
    glPopMatrix();
*/
    // building3
    glPushMatrix();
    glTranslated(190, 0, -160);
    glRotated(0, 0, 0, 0);
    building3();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-190, 0, -160);
    glRotated(180, 0, 1, 0);
    building3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(160, 0.2, 26);
    parking();
    glPopMatrix();

    // trees
    glPushMatrix();
    glTranslated(155, 10, 50);
    trees();
    glPopMatrix();

    glPushMatrix();
    glTranslated(175, 10, 50);
    trees();
    glPopMatrix();

    glPushMatrix();
    glTranslated(300, 10, 50);
    trees();
    glPopMatrix();

    glPushMatrix();
    glTranslated(50, 10, 50);
    trees();
    glPopMatrix();

    glPushMatrix();
    glTranslated(50, 10, 130);
    trees();
    glPopMatrix();

    glPushMatrix();
    glTranslated(50, 10, 160);
    trees();
    glPopMatrix();

    { // 3houses
        glPushMatrix();
        glTranslated(230, 35, 60);
        house1();
        glPopMatrix();
        glPushMatrix();
        glRotated(0, 0, 0, 0);
        glTranslated(100, 35, 60);
        house1();
        glPopMatrix();
        glPushMatrix();
        glRotated(90, 0, 1, 0);
        glTranslated(-240, 35, 60);
        house1();
        glPopMatrix();
    }

    stars();

    glutPostRedisplay();
    glLoadIdentity();

    camera_man();

    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}

const GLfloat light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};//white
const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};//white
const GLfloat light_position[] = {200.0f, 200.0f, 200.0f, 0.0f};

const GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {100.0f};

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1440, 1220);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("3D CITY");
    glutDisplayFunc(display);
    // glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(mouseMovement);
    glutKeyboardFunc(keyboard);

    glClearColor(1, 1, 1, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();
}
