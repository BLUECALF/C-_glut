#include <windows.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <math.h>
#endif


/// USED FUNCTIONS
void display();
void reshape(int,int);
/// shape functions.
void drawXAxis();
void drawYAxis();
void drawTriangle();
void drawSquare();
void drawCircle();
void drawTear();
void drawPentagon();
void drawDottedLine();
void drawPoints();


/// Clears the current window and draws a shape.
void display() {
  /// reset the backgroud color.
  glClearColor(1,1,1,1);
  /// Set every pixel in the frame buffer to the current clear color.
  glClear(GL_COLOR_BUFFER_BIT);
    /// reset all transformation
    glLoadIdentity();
  /// Drawing is done by specifying a sequence of vertices.  The way these
  /// vertices are connected (or not connected) depends on the argument to
  /// glBegin.  GL_POLYGON constructs a filled polygon.

  /// increase points size
  glPointSize(10.0);
  glLineWidth(2);

  drawXAxis();
  drawYAxis();
  drawTriangle();
  drawSquare();
  drawCircle();
  drawTear();
  drawPentagon();
  drawDottedLine();
  drawPoints();

  // Flush drawing command buffer to make drawing happen as soon as possible.
  glFlush();
}

void drawXAxis()
{
    glBegin(GL_LINES);
    glColor3f(0,1,0);
    glVertex2f(10,0);
    glVertex2f(-10,0);
  glEnd();
}
void drawYAxis()
{
    glBegin(GL_LINES);
    glColor3f(0,0,1);
    glVertex2f(0,10);
    glVertex2f(0,-10);
  glEnd();
}
void drawTriangle()
{
    glBegin(GL_POLYGON);
    glColor3f(1,1,0);
    glVertex2f(0,1);
    glVertex2f(4,1);
    glVertex2f(2,5);
  glEnd();
}
void drawSquare()
{
    glBegin(GL_POLYGON);
    glColor3f(0.5,0.5,4);
    glVertex2f(2,2);
    glVertex2f(6,2);
    glVertex2f(6,6);
    glVertex2f(2,6);
  glEnd();
}
void drawCircle()
{
    glColor3f(.7,.1,.4);
    float x,y;
   for(double i =0; i <= 360;){
    glBegin(GL_TRIANGLES);
    x=1*cos(i);
    y=1*sin(i);
    glVertex2d(x-5, y+5);
    i=i+.5;
    x=1*cos(i);
    y=1*sin(i);
    glVertex2d(x-5, y+5);
    glVertex2d(0-5, 0+5);
    glEnd();
    i=i+.5;
}
}
void drawTear()
{
    glColor3f(.4,.5,.4);
    float x,y;
   for(double i =0; i <= 360;){
    glBegin(GL_TRIANGLES);
    x=1*cos(i);
    y=1*sin(i);
    glColor3f(1,.5,.4);
    glVertex2d(x-5, y-5);
    i=i+.5;
    x=1*cos(i);
    y=1*sin(i);
    glColor3f(0,1,.4);
    glVertex2d(x-5, y-5);
    glColor3f(0,0,0);
    glVertex2d(-2,-2);
    glEnd();
    i=i+.5;
}
}void drawPentagon()
{
glBegin(GL_TRIANGLES);

    glVertex2f(-0.7, -1.0);
    glVertex2f(-1.0, 0.3);
    glVertex2f(0.0, 1.0); // that's one triangle

    glVertex2f(-0.7, -1.0);
    glVertex2f(0.0, 1.0);
    glVertex2f(1.0, 0.3); // that's another

    glVertex2f(-0.7, -1.0);
    glVertex2f(1.0, 0.3);
    glVertex2f(0.7,-1.0); // and a third
    glEnd();
}

void drawDottedLine()
{
    glLineStipple(30, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glColor3f(0,1,.5);
    glVertex2f(10,-10);
    glVertex2f(2,-2);
  glEnd();
}
void drawPoints()
{
    glBegin(GL_POINTS);
    glColor3f(0,1,0);
    glVertex2f(8,-6);
    glColor3f(0,0,1);
    glVertex2f(6,-4);
  glEnd();
}

void reshape(int w,int h)
{
    /// resets veiwport,
    glViewport(0,0,w,h);

    /// resets projection


    /// change matrix mode
    glMatrixMode(GL_PROJECTION);
    /// reset rotation & all trnasformations
    glLoadIdentity();
    /// we are seting up 2d projection
    gluOrtho2D(-10,10,-10,10 );

    ///switch back to model view matrix
    glMatrixMode(GL_MODELVIEW);
}
/// Initializes GLUT, the display mode, and main window; registers callbacks;
/// enters the main event loop.
int main(int argc, char** argv) {

  /// Use a single buffered window in RGB mode (as opposed to a double-buffered
  /// window or color-index mode).
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);


  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 500);
  glutCreateWindow("A Drawing ");
  glutDisplayFunc(display);
  /// a reshape function ,callback for resizing window , to edit veiwport and projection.
  glutReshapeFunc(reshape);
  glutMainLoop();
}
