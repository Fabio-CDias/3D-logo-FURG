#include<iostream>
#include<GL/glut.h>
#include<cmath>

void scale(float x, float y, float z){
    double  t [4][4] = {{x,0,0,0},
                        {0,y,0,0},
                        {0,0,z,0},
                        {0,0,0,1}};
    glMultMatrixd((double *) t);
}

void translate(float x,float y, float z){
    double  t [4][4] = {{1,0,0,0},
                        {0,1,0,0},
                        {0,0,1,0},
                        {x,y,z,1}};
    glMultMatrixd((double *) t);
}

void rotate(float angle, int x, int y, int z){
    
    double rad = angle * M_PI / 180;
    double c = cos(rad);
    double s = sin(rad);

    double rotx [4][4]= {{1, 0,0,0},
                         {0, c,s,0},
                         {0,-s,c,0},
                         {0, 0,0,1}};

    double roty [4][4]= {{c, 0,-s,0},
                         {0, 1,0,0},
                         {s, 0,c,0},
                         {0, 0,0,1}};

    double rotz [4][4]= {{ c,s,0,0},
                         {-s,c,0,0},
                         { 0,0,1,0},
                         { 0,0,0,1}};
                         
    if(x == 1){ glMultMatrixd((double *) rotx); }
    if(y == 1){ glMultMatrixd((double *) roty); }
    if(z == 1){ glMultMatrixd((double *) rotz); }
}


void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);  
    glEnable(GL_LIGHT0);    
    glEnable(GL_CULL_FACE); 
    glCullFace(GL_BACK);

    GLfloat light_position[] = {-1.0, 2.0, 2.5, 0.0}; 
    GLfloat ambient[] = {1, 1, 1, 1.0};
    GLfloat diffuse[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess = 100.0;

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    // glLightf(GL_FRONT, GL_SHININESS, shininess);



    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glEnable(GL_NORMALIZE); 
}

void cylinder(GLfloat radius, GLfloat height,GLint n_triangles){ 
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= n_triangles;i++){
        GLfloat x = radius * cos(i * (2.0f * M_PI) / n_triangles);
        GLfloat y = radius * sin(i * (2.0f * M_PI) / n_triangles);

        glNormal3f(x,y,0.0);

        glVertex3f(x,y,-height/2);
        glVertex3f(x,y,height/2);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0,0.0,-1.0);
    glVertex3d(0,0,-height/2);
    for (int i = 0; i <= n_triangles;i++){
        GLfloat x = radius * cos(i * (2.0f * M_PI) / n_triangles);
        GLfloat y = radius * sin(i * (2.0f * M_PI) / n_triangles);
        
        glNormal3f(0,0,-1.0);

        glVertex3f(x,y,-height/2);
    }
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0,0.0,1.0);
    glVertex3d(0,0,height/2);
    for (int i = 0; i <= n_triangles;i++){
        GLfloat x = radius * cos(i * (2.0f * M_PI) / n_triangles);
        GLfloat y = radius * sin(i * (2.0f * M_PI) / n_triangles);

        glNormal3f(0,0,1.0);
        
        glVertex3f(x,y,height/2);
    }
    glEnd();
}

void display(void){
    glClearColor(0.72,0.92,1,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    glColor3f(0.35,0.15,0.0); //Orange
    glLoadIdentity();

    glPushMatrix();
    translate(0, 0, -3);
    rotate(35, 0, 1, 0);  // ROTATE
    cylinder(1, 0.3, 100);

    glPushMatrix();
    translate(0, 0, 0.18);
    scale(0.5,1.4,0.08);

    glColor3f(1,1,1);

    //LEFT
    glPushMatrix();
    translate(-0.8,0,0);
    glutSolidCube(1.0);

    scale(0.4,0.9,1.3);
    translate(0,0.06,0.9);
    glColor3f(0.31,0,0.06);
    glutSolidCube(1.0);
    glPopMatrix();

    // RIGHT
    glPushMatrix();
    glColor3f(1,1,1);
    translate(0.8,0,0);
    glutSolidCube(1.0);

    scale(0.4,0.9,1.3);
    translate(0,0.06,0.9);
    glColor3f(0.31,0,0.06);
    glutSolidCube(1.0);
    glPopMatrix();

    //MIDDLE
    glPushMatrix();
    scale(0.6,0.295,1);
    translate(0,-1.2,0);
    glColor3f(1,1,1);
    glutSolidCube(1.0);

    scale(2,0.4,1.3);
    translate(0,0.12,0.9);
    glColor3f(0.31,0,0.06);
    glutSolidCube(1.0);
    glPopMatrix();

    // UP MIDDLE
    scale(0.6,0.71,2.2);
    translate(0,0.20,0.3);
    glColor3f(0.38,0.25,0);
    glutSolidCube(1.0);
    glFlush ();
    

}


void reshape(int w, int h){
    glViewport(0,0,(GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0,1.0,-1.0,1.0,1.5,20.0);
    // glOrtho(-3.0,3.0,-3.0,3.0,1.5,20.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char* argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400,400);
    glutInitWindowPosition(10,10);
    glutCreateWindow("FURG LOGO !");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}