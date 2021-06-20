#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

enum {SPHERE_PLASTIC = 1, SPHERE_TEXTURE, SPHERE_GLOSSY, LIGHT, LEFTWALL, FLOOR};
GLuint texture_sphere;
GLfloat shadow_matrix_left[4][4];
GLfloat shadow_matrix_floor[4][4];
GLfloat light_position[] = {50.f, 50.f, -320.f, 1.f};
GLfloat mat[] = {0.f, 0.f, 0.f, 0.f};
GLfloat Amat[] = {0.f, 0.f, 0.f, 0.f};

// Draw the texture for the sphere
void make_tex(void){
    unsigned char data[256][256][3];
    for (int y = 0; y < 255; y++) {
		for (int x = 0; x < 255; x++) {
	    	unsigned char *p = data[y][x];
			// changing the function changes the texture pattern
	    	p[0] = p[1] = p[2] = (x+y) & 8 ? 255 : 0;
		}
    }
    glGenTextures(1, &texture_sphere);
    glBindTexture(GL_TEXTURE_2D, texture_sphere);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, (const GLvoid *) data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

// create a matrix that will project the desired shadow 
void shadowmatrix(GLfloat shadow_matrix[4][4],GLfloat plane[4],GLfloat light_position[4]){
  GLfloat dot_product;
  // find dot_product product between light position vector and ground plane normal
  dot_product = plane[0] * light_position[0] + plane[1] * light_position[1] + plane[2] * light_position[2] +plane[3] * light_position[3];
  shadow_matrix[0][0] = dot_product - light_position[0] * plane[0];
  shadow_matrix[1][0] = 0.f - light_position[0] * plane[1];
  shadow_matrix[2][0] = 0.f - light_position[0] * plane[2];
  shadow_matrix[3][0] = 0.f - light_position[0] * plane[3];
  shadow_matrix[0][1] = 0.f - light_position[1] * plane[0];
  shadow_matrix[1][1] = dot_product - light_position[1] * plane[1];
  shadow_matrix[2][1] = 0.f - light_position[1] * plane[2];
  shadow_matrix[3][1] = 0.f - light_position[1] * plane[3];
  shadow_matrix[0][2] = 0.f - light_position[2] * plane[0];
  shadow_matrix[1][2] = 0.f - light_position[2] * plane[1];
  shadow_matrix[2][2] = dot_product - light_position[2] * plane[2];
  shadow_matrix[3][2] = 0.f - light_position[2] * plane[3];
  shadow_matrix[0][3] = 0.f - light_position[3] * plane[0];
  shadow_matrix[1][3] = 0.f - light_position[3] * plane[1];
  shadow_matrix[2][3] = 0.f - light_position[3] * plane[2];
  shadow_matrix[3][3] = dot_product - light_position[3] * plane[3];
}

// find the plane equation given 3 points
void findplane(GLfloat plane[4],GLfloat vertex0[3], GLfloat vertex1[3], GLfloat vertex2[3]){
  GLfloat vector1[3], vector2[3];
  // compute the two vectors lying in the plane
  // vertex0->vertex1  and vertex0->vertex2
  vector1[0] = vertex1[0] - vertex0[0];
  vector1[1] = vertex1[1] - vertex0[1];
  vector1[2] = vertex1[2] - vertex0[2];
  vector2[0] = vertex2[0] - vertex0[0];
  vector2[1] = vertex2[1] - vertex0[1];
  vector2[2] = vertex2[2] - vertex0[2];
  // find cross product to get the normal to the plane
  // the normal along with one point in the plane forms the equation the plane
  plane[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
  plane[1] = -(vector1[0] * vector2[2] - vector1[2] * vector2[0]);
  plane[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
  plane[3] = -(plane[0] * vertex0[0] + plane[1] * vertex0[1] + plane[2] * vertex0[2]);
}

// Render plastic sphere
void spherePlastic(){
    glPushMatrix();
    // set position of plastic sphere
    glTranslatef(0.0f, -75.f, -360.f);
    glCallList(SPHERE_PLASTIC);
    glPopMatrix();
}

// Render textured sphere
void sphereTexture(){
    glPushMatrix();
    // set position of texture sphere
    glTranslatef(-40.f, -40.f, -400.f);
	glCallList(SPHERE_TEXTURE);
    glPopMatrix();
}

// Render Glossy sphere
void sphereGlossy(){
    glPushMatrix();
    // set position of glossy sphere
    glTranslatef(40.f, -40.f, -400.f);
	glCallList(SPHERE_GLOSSY);
    glPopMatrix();
}

void draw(){
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
	// Set wall material properties
	static GLfloat wall_material[] = {1.f, 1.f, 1.f, 1.f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wall_material);
    
    glBegin(GL_QUADS);
    // Render Floor
	glNormal3f(0.f, 1.f, 0.f);
    glVertex3f(-100.f, -100.f, -320.f);
    glVertex3f( 100.f, -100.f, -320.f);
    glVertex3f( 100.f, -100.f, -520.f);
    glVertex3f(-100.f, -100.f, -520.f);
    glEnd();

	// disable lighting
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
	// set shadow color to black
    glColor3f(0.f, 0.f, 0.f);
    // compute shadow of texture sphere on ground  
	glPushMatrix();
    glMultMatrixf((GLfloat *)shadow_matrix_floor);
    sphereTexture();
    glPopMatrix();
	// compute shadow of plastic sphere on floor
    glPushMatrix();
    glMultMatrixf((GLfloat *)shadow_matrix_floor);
    spherePlastic();
    glPopMatrix();
	// compute shadow of glossy sphere on floor
	glPushMatrix();
    glMultMatrixf((GLfloat *)shadow_matrix_floor);
    sphereGlossy();
    glPopMatrix();
    // enable lighting again
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_ALWAYS, 1, 0);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    
	glBegin(GL_QUADS);
    // Render left wall
    glNormal3f(1.f, 0.f, 0.f);
    glVertex3f(-100.f, -100.f, -320.f);
    glVertex3f(-100.f, -100.f, -520.f);
    glVertex3f(-100.f,  100.f, -520.f);
    glVertex3f(-100.f,  100.f, -320.f);
    glEnd();

    glStencilFunc(GL_EQUAL, 1, 1);
	// Disable lighting so that shadow is rendered as black
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
	// Set shadow color to black
    glColor3f(0.f, 0.f, 0.f);
    glDisable(GL_DEPTH_TEST);
	// Compute the shadow of texture sphere on left wall
    glPushMatrix();
    glMultMatrixf((GLfloat *)shadow_matrix_left);
    sphereTexture();
    glPopMatrix();
	// Compute the shadow of plastic sphere on left wall
	glPushMatrix();
    glMultMatrixf((GLfloat *)shadow_matrix_left);
    spherePlastic();
    glPopMatrix();
	// compute the shadow of glossy sphere on left wall
	glPushMatrix();
    glMultMatrixf((GLfloat *)shadow_matrix_left);
    sphereGlossy();
    glPopMatrix();
	// Enable lighting
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_STENCIL_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
    glBegin(GL_QUADS);
    // Render right wall
    glNormal3f(-1.f, 0.f, 0.f);
    glVertex3f( 100.f, -100.f, -320.f);
    glVertex3f( 100.f,  100.f, -320.f);
    glVertex3f( 100.f,  100.f, -520.f);
    glVertex3f( 100.f, -100.f, -520.f);
    // Render ceiling
    glNormal3f(0.f, -1.f, 0.f);
    glVertex3f(-100.f,  100.f, -320.f);
    glVertex3f(-100.f,  100.f, -520.f);
    glVertex3f( 100.f,  100.f, -520.f);
    glVertex3f( 100.f,  100.f, -320.f);
    // Render back wall
    glNormal3f(0.f, 0.f, 1.f);
    glVertex3f(-100.f, -100.f, -520.f);
    glVertex3f( 100.f, -100.f, -520.f);
    glVertex3f( 100.f,  100.f, -520.f);
    glVertex3f(-100.f,  100.f, -520.f);
    glEnd();
    glPushMatrix();
    glTranslatef(light_position[0], light_position[1], light_position[2]);
    glDisable(GL_LIGHTING);
    glColor3f(1.f, 1.f, .7f);
    glCallList(LIGHT);
    glEnable(GL_LIGHTING);
    glPopMatrix();

	// Display the textured sphere
	sphereTexture();
	// set material properties for glossy sphere
	Amat[0] = 0.19225;
  	Amat[1] = 0.19225;
  	Amat[2] = 0.19225;
	Amat[3] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, Amat);
	mat[0] = 0.50754;
	mat[1] = 0.50754;
	mat[2] = 0.50754;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	mat[0] = 0.508273;
	mat[1] = 0.508273;
	mat[2] = 0.508273;
  	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
  	glMaterialf(GL_FRONT, GL_SHININESS, 0.4 * 128.0);
	  // display glossy sphere
    sphereGlossy();
	// set material properties for plastic sphere
	Amat[0] = 0.0;
  	Amat[1] = 0.0;
  	Amat[2] = 0.0;
	Amat[3] = 1.0;
	glMaterialfv(GL_FRONT, GL_AMBIENT, Amat);
	mat[0] = 0.1;
	mat[1] = 0.35;
	mat[2] = 0.1;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	mat[0] = 0.45;
	mat[1] = 0.55;
	mat[2] = 0.45;
  	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);
  	glMaterialf(GL_FRONT, GL_SHININESS, 0.25 * 128.0);
	  // display plastic sphere
	spherePlastic();
    glutSwapBuffers();
}
// Press Esc to exit the code
void key(unsigned char key, int x, int y){	if(key == '\033')	exit(0);}

int main(int argc, char *argv[]){
    
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 1000);
    glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL|GLUT_DOUBLE);
    glutCreateWindow("Sphere");
    glutDisplayFunc(draw);

    glutKeyboardFunc(key);
    // draw a perspective scene
    glMatrixMode(GL_PROJECTION);
    glFrustum(-100., 100., -100., 100., 320., 640.); 
    glMatrixMode(GL_MODELVIEW);
    // turn on lighting 
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
	// make shadow matricies
    GLfloat vertex0[3], vertex1[3], vertex2[3];
	GLfloat plane[4];
	// 3 points on floor
    vertex0[0] = -100.f; vertex0[1] = -100.f; vertex0[2] = -320.f;
    vertex1[0] =  100.f; vertex1[1] = -100.f; vertex1[2] = -320.f;
    vertex2[0] =  100.f; vertex2[1] = -100.f; vertex2[2] = -520.f;
    // FInd equation of plane of the floor  
    findplane(plane, vertex0, vertex1, vertex2);
	// Find shadow matrix for the floor
    shadowmatrix(shadow_matrix_floor, plane, light_position);
    // Choose 3 points on left wall to get equation of plane
    vertex0[0] = -100.f; vertex0[1] = -100.f; vertex0[2] = -320.f;
    vertex1[0] = -100.f; vertex1[1] = -100.f; vertex1[2] = -520.f;
    vertex2[0] = -100.f; vertex2[1] =  100.f; vertex2[2] = -520.f;
	// Find the equation of plane of left wall
    findplane(plane, vertex0, vertex1, vertex2);
	// compute the shadow matrix for left wall
    shadowmatrix(shadow_matrix_left, plane, light_position);
    /* place light 0 in the right place */
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	// get texture for sphere
    make_tex();

	GLUquadricObj *sphere;

	//Add different types of spheres to list. This saves time
	//when rendering the spheres since it does not have to create 
	//a new sphere every time the draw function is called

	//TEXTURED
	glNewList(SPHERE_TEXTURE, GL_COMPILE);
    sphere = gluNewQuadric();
	glEnable(GL_TEXTURE_2D);
	gluQuadricDrawStyle(sphere, GLU_FILL);
	glBindTexture(GL_TEXTURE_2D, texture_sphere);
	gluQuadricTexture(sphere, GL_TRUE);
    gluSphere(sphere, 20.f, 20, 20);
	glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(sphere);
    glEndList();
	// PLASTIC
	glNewList(SPHERE_PLASTIC, GL_COMPILE);
    sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
    gluSphere(sphere, 20.f, 20, 20);
    gluDeleteQuadric(sphere);
    glEndList();
	//GLOSSY
	glNewList(SPHERE_GLOSSY, GL_COMPILE);
    sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
    gluSphere(sphere, 20.f, 20, 20);
    gluDeleteQuadric(sphere);
    glEndList();
	// LIGHT BULB
	glNewList(LIGHT, GL_COMPILE);
    sphere = gluNewQuadric();
    gluSphere(sphere, 5.f, 20, 20);
    gluDeleteQuadric(sphere);
    glEndList();
	// FLOOR
	glNewList(FLOOR, GL_COMPILE);
    glEndList();
	//LEFTWALL
    glNewList(LEFTWALL, GL_COMPILE);
    glEndList();

    glutMainLoop();
}