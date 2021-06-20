#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std;

// class type stores the x,y and z coordinates of vertex
class Vertex{
    public:
        float x,y,z;
};

// class type stores the vertixes forming the face
class Face{
    public:
        int a,b,c;
};

vector<Vertex> vertex; // Global vector storing the vertices
vector<Face> faces; // Global vector storing the faces

bool mouseDown = false; //tells if left mouse button is pressed  or not
float x_angle = 0.0f; //stores the angle of rotation about x-axis
float y_angle = 0.0f; //stores the angle of rotation about y-axis
float xcenter = 0.0f; //point wrt to which the angle of rotation about y-axis has to be measured
float ycenter = 0.0f; //point wrt to which the angle of rotation about x-axis has to be measured
float scale = 1.0f; //zoom factor

void display(){
    glClear(GL_COLOR_BUFFER_BIT); // Clears the display area
    glLoadIdentity(); //Load Identity matrix wothout any transformation

    glTranslatef(0.0, -0.5, 0); // Translate image to the centre of the screen
    glScalef(scale,scale,scale); // scales up the image size by 4.5
    glRotatef(x_angle,1.0f,0.0f,0.0f); //set angle of rotation about x-axis
    glRotatef(y_angle,0.0f,1.0f,0.0f); //set angle of rotation about y-axis
    
    // Join the vertices forming each face by lines to display wireframe
    for(int i=0;i<faces.size();i++){
        // Get the vertices forming the face
        Vertex v1 = vertex[faces[i].a-1];
        Vertex v2 = vertex[faces[i].b-1];
        Vertex v3 = vertex[faces[i].c-1];
        // Join vertices by lines forming a triangle
        glBegin(GL_LINE_LOOP);
        // normalise the scale along x axis. Since if the width > height of window
        // the image will be distorted along x-axis.In other words unit distance on
        // x-axis will be greater than unit distance on y axis.
        glVertex3f(v1.x,v1.y,v1.z); 
        glVertex3f(v2.x,v2.y,v2.z);
        glVertex3f(v3.x,v3.y,v3.z);
        glEnd();
    }
    glFlush(); // Output the image to the window
}

void mouseMotion(int x, int y) {
    //If Left mouse button is down, change the angle
    //of rotation about x-axis and y-axis
    if (mouseDown) {
        //Rotation about y-axis is defined in terms of distance along 
        //x-axis from the center point to the current mouse locations
        y_angle = x - xcenter;

        //Rotation about x-axis is defined in terms of distance along  
        //y-axis from the center point to the current mouse locations
        x_angle = y + ycenter;
        glutPostRedisplay(); //call display function again to incorporate the rotation change
    }
}

void mouse(int button, int state, int x, int y) {
    //If left mouse button is pressed
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseDown = true; //set mouse pressed to true
        //calculate the center wrt to the current location and current angle rotated
        xcenter = x - y_angle; 
        ycenter = -y + x_angle;
        return;
    }
    //If mouse is not pressed
    mouseDown = false; //set mouse pressed to false

    if (button == 3){ //If scroll up
        scale += 0.06; //increase zoom factor by 0.06
    } else if (button == 4) {//If scroll down
        scale -= 0.06; //decrease zoom factor by 0.06
    }
    scale = max(scale, 0.0f); //set minimum zoom factor to 0
    glutPostRedisplay(); //call display function to incorporate the zoom canges
}

int main(int argc,char** argv){
    // Open input file
    FILE *fp = fopen("lowpolybunny.obj","r");
    // Throw error if failed to open file
    if(fp==NULL){
        cout<<"lowpolybunny.obj not found\n";
        return 0;
    }
    // Read the .obj file and get list of vertices and faces
    while(1){
        // type stores if current line has 'v' or 'f'
        char type;
        // stop reading if EOF is encountered
        if(fscanf(fp,"%c ",&type)==EOF){
            break;
        }
        switch(type){
            // Store the vertex in vector 'vertex'
            case 'v': Vertex v;
                      // read x,y and z coordinates of the vertex
                      fscanf(fp,"%f %f %f\n",&v.x,&v.y,&v.z);
                      vertex.push_back(v);
                      break;
            // Store the face in vector 'faces'
            case 'f': Face f;
                      // read the vertex number forming the face
                      fscanf(fp,"%d %d %d\n",&f.a,&f.b,&f.c);
                      faces.push_back(f);
                      break;
        }
    }
    fclose(fp); // close the file after reading
    
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0); // Window position
    glutInitWindowSize(1000,1000); // Window Size
    glutCreateWindow("lowpolybunny"); // Create window with a name
    glutMouseFunc(mouse); //Set mouse function
    glutMotionFunc(mouseMotion); //Set mouse motion function
    glutDisplayFunc(display); // Sets the display function
    glutMainLoop(); // Prevents window from closing unless user closes it manually
}