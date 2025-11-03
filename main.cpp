/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Author: Damiano Vitulli
 *
 * This program is released under the BSD licence
 * By using this program you agree to licence terms on spacesimulator.net copyright page
 *
 *
 * Tutorial 5: Vectors and OpenGL lighting
 * 
 * 
 *
 * To compile this project you must include the following libraries:
 * opengl32.lib,glu32.lib,glut32.lib
 * You need also the header file glut.h in your compiler directory.
 *  
 */

/*
 * Spaceships credits:
 * fighter1.3ds - created by: Dario Vitulli 
 */

#ifdef __WIN32__
#include <windows.h>
#endif

#include <iostream>
#include <GL/glut.h>
#include "load_bmp.h"
#include "load_3ds.h"
#include "object.h"
#include "matrix_func.h"
#include "vector_func.h"

using namespace std;

/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

// The width and height of your window, change them as you like
int screen_width=640;
int screen_height=480;

// Absolute rotation values (0-359 degrees) and rotation increments for each frame
double rotation_x=0, rotation_x_increment=0.1;
double rotation_y=0, rotation_y_increment=0.05;
double rotation_z=0, rotation_z_increment=0.03;
 
double position_x = 0;
double position_y = 0;
double position_z = 0;

// Flag for rendering as lines or filled polygons
int filling=1; //0=OFF 1=ON

//Lights settings
GLfloat light_ambient[]= { 0.1f, 0.1f, 0.1f, 0.1f };
GLfloat light_diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_position[]= { 100.0f, 0.0f, -10.0f, 1.0f };

//Materials settings
GLfloat mat_ambient[]= { 0.1f, 0.1f, 0.1f, 0.0f };
GLfloat mat_diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat mat_specular[]= { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat mat_shininess[]= { 1.0f };



/**********************************************************
 *
 * SUBROUTINE init(void)
 *
 * Used to initialize OpenGL and to setup our world
 *
 *********************************************************/

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // Clear background color to black

    // Viewport transformation
    glViewport(0,0,screen_width,screen_height);  

    // Projection transformation
    glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations 
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,5.0f,10000.0f); // We define the "viewing volume"
   
	//Lights initialization and activation
    glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv (GL_LIGHT1, GL_POSITION, light_position);    
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);

    //Materials initialization and activation
	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);    

	//Other initializations
    glShadeModel(GL_SMOOTH); // Type of shading for the polygons
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Texture mapping perspective correction (OpenGL... thank you so much!)
    glEnable(GL_TEXTURE_2D); // Texture mapping ON
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
	glEnable(GL_CULL_FACE); // Enable the back face culling
    glEnable(GL_DEPTH_TEST); // Enable the depth test (also called z buffer)

	//Objects loading
	ObjLoad ("fighter1.3ds","skull.bmp");

    v4d p = { 1,1,1,1 }, q = { 2,2,2,1 };
    v4d plus_ans = vector_plus(p, q);
    printf("vector plus ans:%f,%f,%f,%f\n", plus_ans.x, plus_ans.y, plus_ans.z, plus_ans.w);
    v4d minus_ans = vector_minus(p, q);
    printf("vector minus ans:%f,%f,%f,%f\n", minus_ans.x, minus_ans.y, minus_ans.z, minus_ans.w);
    float length_ans = length(p);
    printf("vector length ans:%f\n", length_ans);
    v4d normal_ans = normalization(p);
    printf("vector normalization ans:%f,%f,%f,%f\n", normal_ans.x, normal_ans.y, normal_ans.z, normal_ans.w);
    float dot_ans = dot(p, q);
    printf("vector dot ans:%f\n", dot_ans);
    v4d proj_ans = ProjPQ(p, q);
    printf("vector projection ans:%f,%f,%f,%f\n", proj_ans.x, proj_ans.y, proj_ans.z, proj_ans.w);
    v4d cross_ans = cross(p, q);
    printf("vector cross ans:%f,%f,%f,%f\n", cross_ans.x, cross_ans.y, cross_ans.z, cross_ans.w);
    v4d perp_ans = PerpPQ(p, q);
    printf("vector perp ans:%f,%f,%f,%f\n", perp_ans.x, perp_ans.y, perp_ans.z, perp_ans.w);

    float m1[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
    float m2[16] = { 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2 };
    float* add_ans = matrix_add(m1, m2);
    cout << "matrix add ans:";
    for (int i = 0; i < 16; i++) {
        cout << add_ans[i] << " ";
    }
    cout << endl;
    delete[] add_ans;
    float* sub_ans = matrix_substract(m1, m2);
    cout << "matrix substract ans:";
    for (int i = 0; i < 16; i++) {
        cout << sub_ans[i] << " ";
    }
    cout << endl;
    delete[] sub_ans;
    float* multi_ans = multiplication(m1, m2);
    cout << "matrix multiplication ans:";
    for (int i = 0; i < 16; i++) {
        cout << multi_ans[i] << " ";
    }
    cout << endl;
    delete[] multi_ans;
    float* transpose_ans = transpose(m1);
    cout << "matrix transpose ans:";
    for (int i = 0; i < 16; i++) {
        cout << transpose_ans[i] << " ";
    }
    cout << endl;
    delete[] transpose_ans;
    float deter_ans = deteminant(m1);
    cout << "matrix deteminant ans:";
    cout << deter_ans << endl;
    float* invert_ans = invertible(m1);
    cout << "matrix invertible ans:";
    for (int i = 0; i < 16; i++) {
        cout << invert_ans[i] << " ";
    }
    cout << endl;
    delete[] invert_ans;

}



/**********************************************************
 *
 * SUBROUTINE resize(int p_width, int p_height)
 *
 * This routine must be called everytime we resize our window.
 *
 * Input parameters: p_width = width in pixels of our viewport
 *					 p_height = height in pixels of our viewport
 * 
 *********************************************************/

void resize (int p_width, int p_height)
{
	if (screen_width==0 && screen_height==0) exit(0);
    screen_width=p_width; // We obtain the new screen width values and store it
    screen_height=p_height; // Height value

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We clear both the color and the depth buffer so to draw the next frame
    glViewport(0,0,screen_width,screen_height); // Viewport transformation

    glMatrixMode(GL_PROJECTION); // Projection transformation
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,5.0f,10000.0f);

    glutPostRedisplay (); // This command redraw the scene (it calls the same routine of glutDisplayFunc)
}



/**********************************************************
 *
 * SUBROUTINE keyboard(unsigned char p_key, int p_x, int p_y)
 *
 * Used to handle the keyboard input (ASCII Characters)
 *
 * Input parameters: p_key = ascii code of the key pressed
 *					 p_x = not used, keeped to maintain compatibility with glut function
 *                   p_y = not used, keeped to maintain compatibility with glut function
 * 
 *********************************************************/

void keyboard(unsigned char p_key, int p_x, int p_y)
{  
    switch (p_key)
    {
    case 'r': case 'R':
        if (filling == 0)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
            filling = 1;
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Polygon rasterization mode (polygon outlined)
            filling = 0;
        }
        break;
    case 'w': case 'W':
        position_y += 0.1;
        break;
    case 's': case 'S':
        position_y -= 0.1;
        break;
    case 'a': case 'A':
        position_x -= 0.1;
        break;
    case 'd': case 'D':
        position_x += 0.1;
        break;
    case 'z': case 'Z':
        position_z -= 0.1;
        break;
    case 'x': case 'X':
        position_z += 0.1;
        break;
    }
}



/**********************************************************
 *
 * SUBROUTINE keyboard(int p_key, int p_x, int py)
 *
 * Used to handle the keyboard input (not ASCII Characters)
 *
 * Input parameters: p_key = code of the key pressed
 *					 p_x = not used, keeped to maintain compatibility with glut function
 *                   p_y = not used, keeped to maintain compatibility with glut function
 * 
 *********************************************************/

void keyboard_s (int p_key, int p_x, int py)
{
    switch (p_key)
    {
        case GLUT_KEY_UP:
            rotation_x_increment = rotation_x_increment +0.005;
        break;
        case GLUT_KEY_DOWN:
            rotation_x_increment = rotation_x_increment -0.005;
        break;
        case GLUT_KEY_LEFT:
            rotation_y_increment = rotation_y_increment +0.005;
        break;
        case GLUT_KEY_RIGHT:
            rotation_y_increment = rotation_y_increment -0.005;
        break;
    }
}



/**********************************************************
 *
 * SUBROUTINE display(void)
 *
 * This is our main rendering subroutine, called each frame
 * 
 *********************************************************/

    void display(void)
    {
        int j;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue
        glMatrixMode(GL_MODELVIEW); // Modeling transformation
        glLoadIdentity(); // Initialize the model matrix as identity

        glTranslatef(0.0,0.0,-20); // We move the object forward (the model matrix is multiplied by the translation matrix)

        glTranslatef(position_x, position_y, position_z);

	    if (object.id_texture!=-1) 
	    {
		    glBindTexture(GL_TEXTURE_2D, object.id_texture); // We set the active texture 
	        glEnable(GL_TEXTURE_2D); // Texture mapping ON
	    }
	    else
	        glDisable(GL_TEXTURE_2D); // Texture mapping OFF

	    glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
	    for (j=0;j<object.polygons_qty;j++)
	    {
		    //----------------- FIRST VERTEX -----------------
		    //Normal coordinates of the first vertex
		    glNormal3f( object.normal[ object.polygon[j].a ].x,
					    object.normal[ object.polygon[j].a ].y,
					    object.normal[ object.polygon[j].a ].z);
		    // Texture coordinates of the first vertex
		    glTexCoord2f( object.mapcoord[ object.polygon[j].a ].u,
					      object.mapcoord[ object.polygon[j].a ].v);
		    // Coordinates of the first vertex
		    glVertex3f( object.vertex[ object.polygon[j].a ].x,
					    object.vertex[ object.polygon[j].a ].y,
					    object.vertex[ object.polygon[j].a ].z);

		    //----------------- SECOND VERTEX -----------------
		    //Normal coordinates of the second vertex
		    glNormal3f( object.normal[ object.polygon[j].b ].x,
					    object.normal[ object.polygon[j].b ].y,
					    object.normal[ object.polygon[j].b ].z);
		    // Texture coordinates of the second vertex
		    glTexCoord2f( object.mapcoord[ object.polygon[j].b ].u,
					      object.mapcoord[ object.polygon[j].b ].v);
		    // Coordinates of the second vertex
		    glVertex3f( object.vertex[ object.polygon[j].b ].x,
					    object.vertex[ object.polygon[j].b ].y,
					    object.vertex[ object.polygon[j].b ].z);
        
		    //----------------- THIRD VERTEX -----------------
		    //Normal coordinates of the third vertex
		    glNormal3f( object.normal[ object.polygon[j].c ].x,
					    object.normal[ object.polygon[j].c ].y,
					    object.normal[ object.polygon[j].c ].z);
		    // Texture coordinates of the third vertex
		    glTexCoord2f( object.mapcoord[ object.polygon[j].c ].u,
					      object.mapcoord[ object.polygon[j].c ].v);
		    // Coordinates of the Third vertex
		    glVertex3f( object.vertex[ object.polygon[j].c ].x,
					    object.vertex[ object.polygon[j].c ].y,
					    object.vertex[ object.polygon[j].c ].z);
	    }
	    glEnd();
        glFlush(); // This force the execution of OpenGL commands
        glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer
    }



/**********************************************************
 *
 * The main routine
 * 
 *********************************************************/

int main(int argc, char **argv)
{
    // We use the GLUT utility to initialize the window, to handle the input and to interact with the windows system
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("www.spacesimulator.net - 3d engine tutorials - To exit press ESC");    
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc (resize);
    glutKeyboardFunc (keyboard);
    glutSpecialFunc (keyboard_s);
    init();
    glutMainLoop();

    return(0);    
}
