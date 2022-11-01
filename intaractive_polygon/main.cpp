#include <windows.h>
#include <iostream>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <math.h>
#endif


/// USED FUNCTIONS
void display();
void reshape(int,int);
/// info fuction
void RenderString(float x, float y, void *font, const char* string);
///loop function
void timer(int);
/// Function to callback after click
void mouseOnClick(int button, int state, int x, int y);

/// draw points
void drawPoints();
void drawPolygon();

/// a list to hold selected vertices.
POINT pointList[20];
int currentClickNo = 0;
float swidth = 800;
float sheight = 500;
bool drawShape = false;

/// Clears the current window and draws a shape.
void display() {
  /// reset the backgroud color.
  glClearColor(.7,.7,.7,1);
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

  /// show string message
  RenderString(0,450, GLUT_BITMAP_HELVETICA_12,"hello, Left click to mark Points, Right click to make polygon from the points");
  RenderString(0,400, GLUT_BITMAP_HELVETICA_12,"Middle mouse to clear...");

  /// draw selected points
  drawPoints();
  if(drawShape)
    drawPolygon();

  // Flush drawing command buffer to make drawing happen as soon as possible.
  //glFlush();

  /// swap buffers in dbl buffer
  glutSwapBuffers();
}


void reshape(int w,int h)
{
    swidth = w;
    sheight =h;
    /// resets veiwport,
    glViewport(0,0,w,h);

    /// resets projection


    /// change matrix mode
    glMatrixMode(GL_PROJECTION);
    /// reset rotation & all trnasformations
    glLoadIdentity();
    /// we are seting up 2d projection
    gluOrtho2D(0,w,0,h);

    ///switch back to model view matrix
    glMatrixMode(GL_MODELVIEW);
}


void timer(int)
{
    //std::cout<<"Timer was called \n";
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
}

void mouseOnClick(int button, int state, int x, int y)
{
     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        std::cout<<"\nLeft mouse was clicked \n at "<<x<<" , "<<y;

        /// add the clicked point to the list of points
        if(currentClickNo < 20)
        {
            pointList[currentClickNo] =  tagPOINT{x,sheight-y};
            currentClickNo ++;
            std::cout<<"\n mouse point \n at "<<x<<" , "<<y;
            std::cout<<"\n vertex point \n at "<<x<<" , "<<sheight-y;
        }

    } else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
       drawShape = !drawShape;
    }
    else if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
        /// this provides a=n ilusiopn of like clearing array
       currentClickNo = 0;
    }


}

void RenderString(float x, float y, void *font, const char* string)
{
  char *c;

  glColor3f(0, 0,0);
  glRasterPos2f(x, y);
  for(int i=0;i<strlen(string);i++)
  {
      glRasterPos2f(x+=10, y);
      glutBitmapCharacter(font, string[i]);
  }
}

void drawPoints()
{
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    for(int i=0; i<currentClickNo;i++)
    {
        glVertex2f(pointList[i].x,pointList[i].y);
    }
  glEnd();
}
void drawPolygon()
{
    glBegin(GL_POLYGON);
    glColor3f(0,0,1);
    for(int i=0; i<currentClickNo;i++)
    {
        glVertex2f(pointList[i].x,pointList[i].y);
    }
  glEnd();
}

/// Initializes GLUT, the display mode, and main window; registers callbacks;
/// enters the main event loop.
int main(int argc, char** argv) {

  /// Use a single buffered window in RGB mode (as opposed to a double-buffered
  /// window or color-index mode).
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);


  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 500);
  glutCreateWindow("An interactive graphics");
  glutMouseFunc(mouseOnClick);
  glutDisplayFunc(display);
  /// a reshape function ,callback for resizing window , to edit veiwport and projection.
  glutReshapeFunc(reshape);

  /// Loop function
  glutTimerFunc(0,timer,0);
  glutMainLoop();
}
