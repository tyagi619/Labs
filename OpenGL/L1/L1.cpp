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

void display(){
    glClear(GL_COLOR_BUFFER_BIT); // Clears the display area
    int w = glutGet(GLUT_WINDOW_WIDTH); // get window width
    int h = glutGet(GLUT_WINDOW_HEIGHT); // get window height
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
        glVertex3f(h*(v1.x/w),v1.y,v1.z); 
        glVertex3f(h*(v2.x/w),v2.y,v2.z);
        glVertex3f(h*(v3.x/w),v3.y,v3.z);
        glEnd();
    }
    glFlush(); // Output the image to the window
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
    
    glTranslatef(0.2, -1.3, 0); // Translate image to the centre of the screen
    glScalef(6,6,6); // scales up the image size by 4.5

    glutDisplayFunc(display); // Sets the display function
    glutMainLoop(); // Prevents window from closing unless user closes it manually
}