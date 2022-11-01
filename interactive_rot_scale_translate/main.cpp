#include <windows.h>
#include <iostream>
#ifdef __APPLE_CC__
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
/// Function to callback after key press
void keyboardPress(unsigned char key, int x, int y);

/// draw points
void drawPoints();
void drawPolygon();

/// a list to hold selected vertices.
POINT pointList[20];
int currentClickNo = 0;
float swidth = 800;
float sheight = 500;
bool drawShape = false;


/// Details used in Rotation...
char* mode = "DEFAULT";

/// variables used in translation
int xtranslate = 0;
int ytranslate = 0;
/// variables used in ROTATE
int rotate_angle = 0;

/// variables used in scale
float xscale = 1;
float yscale = 1;


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
  RenderString(0,430, GLUT_BITMAP_HELVETICA_12,"Middle mouse to clear...");
  RenderString(0,400, GLUT_BITMAP_HELVETICA_12,mode);
  RenderString(0,370, GLUT_BITMAP_HELVETICA_12,"press R for rotation,S for scale or T for translation,D for default");
  RenderString(0,350, GLUT_BITMAP_HELVETICA_12,"press (I)adds y ,(K) reduces y,(J)reduces x,(L) adds x ");

  /// TRANSATION AND rotation are done before drawing
    if(mode == "ROTATION")
    {
        std::cout<<"\nThe rotation angle is "<<rotate_angle;
        glRotatef(rotate_angle,0,0,1);
    }
    if(mode == "TRANSLATION")
    {
        glTranslatef(xtranslate,ytranslate,0);
    }
    if(mode == "SCALE")
    {
        glScalef(xscale,yscale,1);
    }
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
       /// ALSO RESETS ALL TRANSLATION OR ROTAYION
       glLoadIdentity();
    }


}
void keyboardPress(unsigned char key, int x, int y)
{
    /// case to change codes
    switch (key)
    {
        case 't': mode = "TRANSLATION";break;
        case 'r': mode = "ROTATION";break;
        case 's': mode = "SCALE";break;
        case 'd': mode = "DEFAULT";break;
    }
    std::cout<<"\nThe key pressed is :::"<<key;
    if(mode=="ROTATION")
    {
        if(rotate_angle>360 || rotate_angle <0)
        {
            rotate_angle = 0;
        }
        switch(key)
        {
            case 'i': rotate_angle+=1;break;
            case 'k': rotate_angle -=1;break;
        }
    }
    if(mode=="TRANSLATION")
    {
        switch(key)
        {
            case 'l': xtranslate+=5;break;
            case 'j': xtranslate-=5;break;
            case 'i': ytranslate+=5;break;
            case 'k': ytranslate-=5;break;
        }
    }
    if(mode=="SCALE")
    {
        switch(key)
        {
            case 'l': xscale+=.1;break;
            case 'j': xscale -=.1;break;
            case 'i': yscale+=.1;break;
            case 'k': yscale-=.1;break;
        }
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
  glLoadIdentity();
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
  glutCreateWindow("An interactive graphics,Rotation Scale and translation");
  glutMouseFunc(mouseOnClick);
  glutKeyboardFunc(keyboardPress);
  glutDisplayFunc(display);
  /// a reshape function ,callback for resizing window , to edit veiwport and projection.
  glutReshapeFunc(reshape);

  /// Loop function
  glutTimerFunc(0,timer,0);
  glutMainLoop();
}
