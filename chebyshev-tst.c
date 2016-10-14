/*
 * Adapted from OpenGLSamples (openglsamples.sf.net) Examples.
 *
 * Test of Chebyshev interpolation.
 *
 */

#include <stdio.h>
//#include <windows.h>	   // Standard header for MS Windows applications
#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header

#include "chebyshev.h"
#include "bmp.h"

#define KEY_ESCAPE 27



typedef struct {
    int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

glutWindow win;

float sample_points_x[] =
{30,
46,
93,
170,
248,
347,
413,
495,
560,
624,
675,
705,
698,
637,
540,
435,
344,
244,
168,
109,
70,
39,
30};

float sample_points_y[] =
{261,
218,
161,
107,
82,
80,
80,
112,
151,
194,
250,
311,
353,
382,
397,
398,
398,
388,
372,
351,
326,
298,
274};

const int n_sample_points = sizeof(sample_points_x)/sizeof(sample_points_x[0]);
	
float cheby_coeff_x[n_sample_points];
float cheby_coeff_y[n_sample_points];

const int n_points_to_evaluate=300;
const int n_coeffs_to_use = 10;

bmp_file img;

GLuint texName;

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     // Clear Screen and Depth Buffer
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-2.5f);			
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texName);
	/*
	 * Triangle code starts here
	 * 3 verteces, 3 colors.
	 */
	/*
       glBegin(GL_TRIANGLES);					
		glColor3f(0.0f,0.0f,1.0f);			
		glVertex3f( 0.0f, 1.0f, 0.0f);		
		glColor3f(0.0f,1.0f,0.0f);			
		glVertex3f(-1.0f,-1.0f, 0.0f);		
		glColor3f(1.0f,0.0f,0.0f);			
		glVertex3f( 1.0f,-1.0f, 0.0f);		
	glEnd();				
 */
	float xvals[] = {-1.0, 1.0, 1.0, -1.0};
        float yvals[] = {1.0, 1.0, -1.0, -1.0};

	float svals[] = {1, 1, 0, 0};
	float tvals[] = {1, 0, 0, 1};

	glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
	glBegin(GL_POLYGON);
	for (int i=0; i < 4; i++)
        {
             glVertex2f(xvals[i], yvals[i]);
             glTexCoord2f(svals[i], tvals[i]);
        }
        glEnd();

	glutSwapBuffers();
}

float getCoordinate(float index, float array[])
{
	// round to nearest
	int nearestIdx = (int)(index + 0.5);
	return array[nearestIdx];
}

float getYCoordinate(float index)
{
	return getCoordinate(index, sample_points_y);
}

float getXCoordinate(float index)
{
	return getCoordinate(index, sample_points_x);
}

void drawChebyshevApprox()
{
	// x points
	chebyshevFit(0.0f, n_sample_points-1, cheby_coeff_x, n_sample_points, getXCoordinate);
	// y points
	chebyshevFit(0.0f, n_sample_points-1, cheby_coeff_y, n_sample_points, getYCoordinate);

	// write pixels
	float step_size = ((float)n_sample_points-1)/(n_points_to_evaluate-1);
	float cur_val = 0.0f;
	for (int i=0; i < n_points_to_evaluate; i++)
	{
		// round to nearest
		int xcoord = (int)(chebyshevEv(0.0f, n_sample_points-1,
				cheby_coeff_x,n_coeffs_to_use, cur_val) + 0.5);

		int ycoord = (int)(chebyshevEv(0.0f, n_sample_points-1,
				cheby_coeff_y,n_coeffs_to_use, cur_val) + 0.5);
		//printf("i: %d, x: %d, y: %d\n", i, xcoord, ycoord);
		// set pixel to red
		// NOTE: the y coordinates are "upside down", i.e. img corner
		// is bottom left, not top left, but we used top-left ordering
		// to define the coordinates
		int pixelStart = 3*(img.width*img.height - img.width*ycoord + xcoord);
		img.data[pixelStart] = 255;  // red
		img.data[pixelStart + 1] = 0;
		img.data[pixelStart + 2] = 0;
		cur_val += step_size;
	}
}

void initialize () 
{
    glMatrixMode(GL_PROJECTION);												// select projection matrix
    glViewport(0, 0, win.width, win.height);									// set the viewport
    glMatrixMode(GL_PROJECTION);												// set matrix mode
    glLoadIdentity();															// reset projection matrix
    GLfloat aspect = (GLfloat) win.width / win.height;
	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);		// set up a perspective projection matrix
    glMatrixMode(GL_MODELVIEW);													// specify which matrix is the current matrix
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );														// specify the clear value for the depth buffer
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						// specify implementation-specific hints
	glClearColor(0.0, 0.0, 0.0, 1.0);											// specify clear values for the color buffers							
    // read bmp image 

    img = readBMP("tst.bmp");
    drawChebyshevApprox();
    //printf("img width: %d, img height: %d\n", img.width, img.height);
    glGenTextures(1, &texName);
    glBindTexture(GL_TEXTURE_2D, texName);

    glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
    glPixelStorei(GL_UNPACK_LSB_FIRST,  GL_TRUE);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
		  img.width, img.height, 0,
		 GL_RGB, GL_UNSIGNED_BYTE, img.data);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		            
    glBindTexture(GL_TEXTURE_2D, 0);
}


void keyboard ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
  switch ( key ) 
  {
    case KEY_ESCAPE:        
      exit ( 0 );   
      break;      

    default:      
      break;
  }
}

int main(int argc, char **argv) 
{
	// set window values
	win.width = 640;
	win.height = 480;
	win.title = "OpenGL/GLUT Example. Visit http://openglsamples.sf.net ";
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 500.0f;

	// initialize and run program
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
	glutInitWindowSize(win.width,win.height);					// set window size
	glutCreateWindow(win.title);								// create Window
	glutDisplayFunc(display);									// register Display Function
	glutIdleFunc( display );									// register Idle Function
    glutKeyboardFunc( keyboard );								// register Keyboard Handler
	initialize();
	glutMainLoop();												// run GLUT mainloop
	return 0;
}

