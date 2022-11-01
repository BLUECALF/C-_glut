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
/// info function
void RenderString(float x, float y, void *font, const char* string);
///loop function
void timer(int);
/// Function to callback after key press
void keyboardPress(unsigned char key, int x, int y);

/// function to join char* and char
char* appendCharToCharArray(char* array, char a);
/// Draw a Cube
void drawCube();

/// a list to hold screen vewport info.
float swidth = 800;
float sheight = 500;


/// Details used in Rotation...
char* mode = "DEFAULT";

/// variables used in translation
int xtranslate = 0;
int ytranslate = 0;
/// variables used in ROTATE
int rotate_angle = 0;
char rotation_axis = 'z';

/// variables used in scale
float xscale = 1;
float yscale = 1;


/// Clears the current window and draws a shape.
void display() {
  /// reset the backgroud color.
  glClearColor(.7,.7,.7,1);
  ///enable depth testing
  glEnable(GL_DEPTH_TEST);
  /// Set every pixel in the frame buffer to the current clear color.  ALSO CLear depth buffer bit
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /// reset all transformation
    glLoadIdentity();
  /// Drawing is done by specifying a sequence of vertices.  The way these
  /// vertices are connected (or not connected) depends on the argument to
  /// glBegin.  GL_POLYGON constructs a filled polygon.

  /// increase points size
  glPointSize(10.0);
  glLineWidth(2);
  glTranslatef(0,0,-15);
  /// show string message
  RenderString(-8,8, GLUT_BITMAP_HELVETICA_12,"A display of a Cube");
  RenderString(-8,7, GLUT_BITMAP_HELVETICA_12,mode);
  RenderString(-8,6, GLUT_BITMAP_HELVETICA_12,"press R for rotation,S for scale or T for translation,D for default");


  /// TRANSATION AND rotation are done before drawing

    if(mode == "ROTATION")
    {
        RenderString(-6,7, GLUT_BITMAP_HELVETICA_12,appendCharToCharArray("AXIS::",rotation_axis));
        RenderString(-8,5, GLUT_BITMAP_HELVETICA_12," Press X,Y or Z to switch between axis your rotating on");
        RenderString(-8,4, GLUT_BITMAP_HELVETICA_12,"press (I)adds rotation angle ,(K) reduces rotation angle ");
        std::cout<<"\nThe rotation angle is "<<rotate_angle;
        switch (rotation_axis)
        {
            case 'x': glRotatef(rotate_angle,1,0,0); break;
            case 'y': glRotatef(rotate_angle,0,1,0); break;
            case 'z': glRotatef(rotate_angle,0,0,1); break;
        }
        glScalef(xscale,yscale,1);
    }
    if(mode == "TRANSLATION")
    {
        RenderString(-8,5, GLUT_BITMAP_HELVETICA_12,"press (I)adds y ,(K) reduces y,(J)reduces x,(L) adds x ");
        glTranslatef(xtranslate,ytranslate,0);
        glScalef(xscale,yscale,1);
    }
    if(mode == "SCALE")
    {
        RenderString(-8,5, GLUT_BITMAP_HELVETICA_12,"press (I)adds y ,(K) reduces y,(J)reduces x,(L) adds x ");
        glScalef(xscale,yscale,1);
        glTranslatef(xtranslate,ytranslate,0);
    }
  /// draw selected points
      drawCube();

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
    /// we are setting up 3D projection
    /// perspective takes FOV angle,aspect ratio of width to height,Z near distance, Z far distance.
    gluPerspective(60,1,2,50.0);

    ///switch back to model view matrix
    glMatrixMode(GL_MODELVIEW);
}


void timer(int)
{
    //std::cout<<"Timer was called \n";
    glutPostRedisplay();
    glutTimerFunc(1000/60,timer,0);
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
            /// X Y Z changes rotation axis.
            case 'x': rotation_axis =  'x'; rotate_angle = 0;  break;
            case 'y': rotation_axis =  'y'; rotate_angle = 0; break;
            case 'z': rotation_axis =  'z'; rotate_angle = 0; break;
        }
    }
    if(mode=="TRANSLATION")
    {
        switch(key)
        {
            case 'l': xtranslate+=2;break;
            case 'j': xtranslate-=2;break;
            case 'i': ytranslate+=2;break;
            case 'k': ytranslate-=2;break;
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
        if(xscale<0)
            xscale = 0.1;
        if(yscale< 0)
            yscale = 0.1;
    }
    if(mode=="DEFAULT")
    {
        xscale = 1;
        yscale = 1;
        rotate_angle = 0;
        xtranslate = 0;
        ytranslate = 0;
    }

}

void RenderString(float x, float y, void *font, const char* string)
{
  char *c;

  glColor3f(0, 0,0);
  glRasterPos3f(x, y, 0);
  for(int i=0;i<strlen(string);i++)
  {
      glRasterPos2f(x+=.2, y);
      glutBitmapCharacter(font, string[i]);
  }
}

void drawCube()
{
    glBegin(GL_QUADS);
    //top
    glColor3f(1.0,0.0,0.0);
    glVertex3f(-1.0,1.0,1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glVertex3f(1.0,-1.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    //back
    glColor3f(0.0,1.0,0.0);
    glVertex3f(1.0,1.0,-1.0);
    glVertex3f(1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,1.0,-1.0);
    //right
    glColor3f(0.0,0.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,-1.0,1.0);
    glVertex3f(1.0,-1.0,-1.0);
    glVertex3f(1.0,1.0,-1.0);
    //left
    glColor3f(1.0,1.0,0.0);
    glVertex3f(-1.0,1.0,-1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glVertex3f(-1.0,1.0,1.0);
    //top
    glColor3f(0.0,1.0,1.0);
    glVertex3f(-1.0,1.0,-1.0);
    glVertex3f(-1.0,1.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,1.0,-1.0);
    //bottom
    glColor3f(1.0,0.0,1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glVertex3f(1.0,-1.0,1.0);
    glVertex3f(1.0,-1.0,-1.0);
  glEnd();
  glLoadIdentity();
}
char* appendCharToCharArray(char* array, char a)
{
    size_t len = strlen(array);

    char* ret = new char[len+2];

    strcpy(ret, array);
    ret[len] = a;
    ret[len+1] = '\0';

    return ret;
}

/// Initializes GLUT, the display mode, and main window; registers callbacks;
/// enters the main event loop.
int main(int argc, char** argv) {

  /// Use a single buffered window in RGB mode (as opposed to a double-buffered
  /// window or color-index mode).
  glutInit(&argc, argv);
  /// made depth testing available in display mode
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(80, 80);
  glutInitWindowSize(800, 500);
  glutCreateWindow("An interactive graphics,Rotation Scale and translation");
  glutKeyboardFunc(keyboardPress);
  glutDisplayFunc(display);
  /// a reshape function ,callback for resizing window , to edit veiwport and projection.
  glutReshapeFunc(reshape);

  /// Loop function
  glutTimerFunc(0,timer,0);
  glutMainLoop();
}
