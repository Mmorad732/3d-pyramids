#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <string>
#include <math.h>
#include <iostream>

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------

int rotate=0;
float anglez=0,angley=0,anglex=0,x=0,y=0 , pAX=0,pAY=0,pAZ=0 ,pYpos=0  ,sAX=0 , sAY=0,sAZ=0 , sRadius=0 ,red=0,green=0,black = 0;

// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------

void printSomething(char *str,float x, float y ,float z);
void polygon(float *x , float *y,float *z );
void triangle(float *x , float *y,float *z );

// ----------------------------------------------------------
// reshape function
// ----------------------------------------------------------

void reshapeFunc (int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (70.0, (GLdouble)w / (GLdouble)h, 0.5, 130.0);
    glMatrixMode(GL_MODELVIEW);
}

// ----------------------------------------------------------
// pyramid drawing function
// ----------------------------------------------------------
void pyramid(float posx , float  posy ,float posz, float width ,float height ){
    float w = width/2;
    // X , Y , Z array decleration to be passed to the object making function
    float xarr[3]={0.0f ,w,-w} ,yarr[3]={height ,0.0f,0.0f },zarr[3]={0.0f,w,w} ;
    glPushMatrix();
    glTranslatef(0.0f+posx, 0.0f+posy, -15.0f + posz);
    glRotatef(pAZ, 0.0, 0.0, 1.0);
    glRotatef(pAY, 0.0, 1.0, 0.0);
    glRotatef(pAX, 1.0, 0.0, 0.0);
  
    // Begin drawing the pyramid with 4 triangles
    
    glColor3f(0.8f, 0.5f, 0.0f);
  
    //front side
    triangle(xarr , yarr , zarr );
    
    //right side
    
    xarr[1]=w;
    xarr[2] = w;
    zarr[1]=w;
    zarr[2]=-w;
    triangle(xarr , yarr , zarr);
   
    //left side
    xarr[1]=-w;
    xarr[2] = -w;
    zarr[1]=-w;
    zarr[2]=w;
    triangle(xarr , yarr , zarr);
    
    //back side
    xarr[1]=-w;
    xarr[2] = w;
    zarr[1]=-w;
    zarr[2]=-w;
    triangle(xarr , yarr , zarr);
    
     glEnd();
    //base
    glColor3f(0.9f, 0.6f, 0.0f);
    float xarr1[4]={w,w,-w,-w} ,yarr1[4]={0.0f,0.0f,0.0f,0.0f},zarr1[4]={w,-w,-w,w} ;
    polygon(xarr1, yarr1, zarr1);
    
    glPopMatrix();
    
}

// ----------------------------------------------------------
// polygon drawing function
// ----------------------------------------------------------

void polygon(float *x , float *y,float *z ){
    //drawing 4 sided polygon
    glBegin(GL_POLYGON);
    glVertex3f(x[0], y[0], z[0]);
    glVertex3f(x[1], y[1], z[1]);
    glVertex3f(x[2], y[2], z[2]);
    glVertex3f(x[3], y[3], z[3]);
    glEnd();
}

// ----------------------------------------------------------
// 3 sided polygon drawing function
// ----------------------------------------------------------

void triangle(float *x , float *y,float *z ){
    //drawing 3 sided polygon
    glBegin(GL_POLYGON);
    glVertex3f(x[0], y[0], z[0]);
    glVertex3f(x[1], y[1], z[1]);
    glVertex3f(x[2], y[2], z[2]);
    glEnd();
}

// ----------------------------------------------------------
// floor drawing function
// ----------------------------------------------------------

void floor(){
    glPushMatrix();
    //floor coloring
    glColor3f(0.8f, 0.6f, 0.0f);
     // X , Y , Z array decleration to be passed to the object making function
    float xarr[4]={30.0f,-30.0f,-30.0f,30.0f} ,yarr[4]={-0.1f,-0.1f,-0.1f,-0.1},zarr[4]={-35,-35,35,35} ;
    polygon(xarr, yarr, zarr);
    glPopMatrix();
}

// ----------------------------------------------------------
// sun drawing function
// ----------------------------------------------------------

void sun(int x , int y ,int z ,float radius ){
    glPushMatrix();
    //adjusting sun rotation around axis
    glRotatef(sAZ, 0.0, 0.0, 1.0);
    glRotatef(sAY, 0.0, 1.0, 0.0);
    glRotatef(sAX-210, 1.0, 0.0, 0.0);
    //adjusting sun starting positiion
    glTranslatef(x+0.0, y+0.0, -15.0+z);
    glColor3f(1.0f, 0.5f, 0.0f);
    //drawing sun and adding variable radius to be changed
    glutSolidSphere(radius +sRadius , 20, 20);
    
    glPopMatrix();
}

// ----------------------------------------------------------
// bazzar drawing function
// ----------------------------------------------------------

void bazzar(float x , float y ,float z ,float base , float height){
    
    // X , Y , Z array decleration to be passed to the object making function
    float xarr[4]={5,-5,-5,5} ,yarr[4]={y-3,y-3,y-1,y-1},zarr[4]={0.0f,0.0f,-1.0f,-0.1f} ;
    glPushMatrix();
    //adjusting position of the name sign
    float signX = x-30.0 , signZ =-13.0+z;
    printSomething("Bazzar", x-35, y+4 , z+0.5f);
    glTranslatef(signX, y, signZ);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glColor3f(0.8f, 0.6f, 0.0f);
    //Drawing name sign
    polygon(xarr, yarr, zarr);
    glPopMatrix();
    
    //Ceiling of bazzar
    glPushMatrix();
    glTranslatef(x+0.0, y+0.0, -15.0+z);
    glRotatef(0, 0.0, 0.0, 1.0);
    glRotatef(0, 0.0, 1.0, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glColor3f(1.0f, 0.5f, 0.0f);
    glutSolidCone(base, height, 20, 20);
    glPopMatrix();
    
    //Bazzar walls
    glPushMatrix();
    glTranslatef(x+0.0, y+0.0-y, -15.0+z);
    glColor3f(0.958824, 0.858824, 0.439216);
    glutSolidCube(base);
    glPopMatrix();
    
    //Entrance
    glPushMatrix();
    glTranslatef(x-30, y-5.5, z-13.5f);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    xarr[0] = 2 ; xarr[1]=-2; xarr[2]=-2 ; xarr[3] = 2;
    yarr[0] = 3 ; yarr[1]=3 ; yarr[2]=-3 ; yarr[3] = -3;
    polygon(xarr, yarr, zarr);
    glPopMatrix();
    
    //Opened door
    glPushMatrix();
    glTranslatef(x-32, y-5.5, z-10.5f);
    glRotatef(-90, 0.0, 1.0, 0.0);
    glColor3f(0.8f, 0.6f, 0.0f);
    xarr[0] = 2 ; xarr[1]=-1; xarr[2]=-1 ; xarr[3] = 2;
    zarr[1] = -4.0f ; zarr[2] = -4.0f ; zarr[3] = 0.0f ;
    polygon(xarr, yarr, zarr);
    glPopMatrix();
    
    
}

// ----------------------------------------------------------
// obelisk drawing function
// ----------------------------------------------------------

void obelisk(float x , float  y ,float z, float size , float height){
    float  w = size/2;
    glPushMatrix();
    
    glTranslatef(x+0.0, y+0.0, -15.0+z);
    //Angle variable to allow rotation
    glRotatef(pAZ+0, 0.0, 0.0, 1.0);
    glRotatef(pAY+0, 0.0, 1.0, 0.0);
    glRotatef(pAX+0, 1.0, 0.0, 0.0);
    
    glColor3f(0.8f, 0.6f, 0.0f);
    
    // X , Y , Z array decleration to be passed to the object making function
    //right side
    float xarr[4]={w,-w,-w,w} ,yarr[4]={height,height,-3.0f,-3.0f},zarr[4]={-w,-w,-w,-w} ;
    polygon(xarr, yarr, zarr);
    
    // X , Y , Z array editing to be passed to the object making function
    //left side
    xarr[0] = -w ; xarr[3] = -w;
    zarr[1] = w ; zarr[2] = w;
    polygon(xarr, yarr, zarr);
    
    // X , Y , Z array editing to be passed to the object making function
    //front side
    xarr[0] = w ; xarr[1] = w ; xarr[2] = w ;xarr[3] = w;
    polygon(xarr, yarr, zarr);
    
    // X , Y , Z array editing to be passed to the object making function
    //back side
    xarr[0] = -w ; xarr[1] = w ; xarr[2] = w ;xarr[3] = -w;
    zarr[0] = w ; zarr[3] = w;
    polygon(xarr, yarr, zarr);
   
    
    //base
    glColor3f(0.8f, 0.8f, 0.0f);
    // X , Y , Z array editing to be passed to the object making function
    xarr[0] = w ; xarr[1] = w; xarr[2]=-w ; xarr[3] = -w;
    yarr[0] = -3.0f ; yarr[1]= -3.0f ;
    zarr[0] = w ; zarr[1] = -w ; zarr[2] = -w ; zarr[3] = w  ;
    polygon(xarr, yarr, zarr);
   
    
    glPushMatrix();
    glColor3f(0.8f, 0.6f, 0.0f);
    //addjusting position to be on the top of the obelisk
    glTranslatef(0.0, height, 0.0f);
    //making solid cubes
    glutSolidCube(size);
    glPopMatrix();
    glPushMatrix();
    //addjusting position to be on the top of the obelisk and bigger cubes
    glTranslatef(0.0f, height+size-1, 0.0f);
    //making second solid cubes
    glutSolidCube(size-1);
    glPopMatrix();
    glPushMatrix();
    //addjusting position to be on the top of the obelisk and bigger cubes
    glTranslatef(0.0f, height+(size*2)-3, 0.0f);
    //making third solid cubes
    glutSolidCube(size-2);
    glPopMatrix();
    glPushMatrix();
    //addjusting position to be on the top of the obelisk and bigger cubes
    glTranslatef(0.0, height+(size*3)-6, 0.0f);
    //making fourth solid cubes
    glutSolidCube(size-3);
    glPopMatrix();
    
    glPopMatrix();
    
}

// ----------------------------------------------------------
// museum drawing function
// ----------------------------------------------------------

void museum(float x , float  y ,float z,float width , float height){
    
    float w= width/2;
    glPushMatrix();
    // Posisitioning object
    glTranslatef(x+0.0, y+0.0, -15.0+z);
    // Printing Museum word
    printSomething("Museum", x+36, y+height-1.0f , z+width+1.5f);
    glColor3f(0.958824, 0.858824, 0.439216);
    // X , Y , Z array decleration to be passed to the object making function
    float xarr[4]={w,-w,-w,w} ,yarr[4]={height,height,-3.0f,-3.0f},zarr[4]={-w,-w,-w,-w} ;
    polygon(xarr, yarr, zarr);
    
    // X , Y , Z array editing to be passed to the object making function
    xarr[0] = -w ; xarr[3] = -w;
    zarr[1] = w ; zarr[2] = w;
    polygon(xarr, yarr, zarr);
    
    // X , Y , Z array editing to be passed to the object making function
    xarr[0] = w ; xarr[1] = w ; xarr[2] = w ;xarr[3] = w;
    polygon(xarr, yarr, zarr);
    
    // X , Y , Z array editing to be passed to the object making function
    xarr[0] = -w ; xarr[1] = w ; xarr[2] = w ;xarr[3] = -w;
    zarr[0] = w ; zarr[3] = w;
    polygon(xarr, yarr, zarr);
    
    
     //Entrance
    glColor3f(0.0f, 0.0f, 0.0f);
    // X , Y , Z array editing to be passed to the object making function
    xarr[0] = w+1 ; xarr[1] = w+1 ; xarr[2] = w+1 ;xarr[3] = w+1;
    yarr[0] = height/2 ; yarr[1] = height/2 ;
    zarr[0] = w/4 ; zarr[1] = -w/4 ; zarr[2]= -w/4 ; zarr[3] = w/4 ;
    polygon(xarr, yarr, zarr);
   
   
    glPopMatrix();
}

// ----------------------------------------------------------
// printSomething function
// ----------------------------------------------------------

void printSomething(char *str,float x, float y , float z)
{
    
    glColor3f(1,1.0,1.0);
    //positioning
    glRasterPos3f(x, y, -15.0f+z);
    //determining array length
    int len = (int)strlen(str);
    for(int i=0;i<len;i++)
    {
        //darwing letters
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
    }
   
    
    glFlush();
}



// ----------------------------------------------------------
// display()
// ----------------------------------------------------------

void display (void)
{
    //  Clear screen and Z-buffer
    glClear        (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformations
    glLoadIdentity ();
    
    
    glPushMatrix();
    // Rotate when user changes rotate_x and rotate_y
    glRotatef(anglez, 0.0, 0.0, 1.0);
    glRotatef(angley, 0.0, 1.0, 0.0);
    glRotatef(anglex, 1.0, 0.0, 0.0);
    glTranslatef(0.0f, -2.0f, 10.0f);
    //Front pyramid(big pyramid)
    pyramid(0,0+pYpos,-13,20,15);
    //Back pyramid(small pyramid)
    pyramid(0,0+pYpos,20 ,10,5);
    //Sun
    sun(15, 0, -25,1);
    //Bazzar
    bazzar(70,8,0,20,19);
    //Obelisk
    obelisk(-30.0f, 0+pYpos, 15, 4,12);
    //Museum
    museum(-30.0f, 0.0f, 5, 10, 4);

    glEnd();
    
    //Floor under all objects
    floor();
    glPopMatrix();
    
    
    
    
    
    
    glFlush();
    glutSwapBuffers();
}

// ----------------------------------------------------------
// idleFunc function
// ----------------------------------------------------------

void idleFunc (void)
{
    //  Changing sun radius as it rotates
    if(sAX <= -359.0f){
        sAX = 0;
        sRadius = 1.1f;
    }else if (sAX >=-270 && sAX <-90) {
        if(sAX <-180){
        sRadius -= 0.007;
        }else{
        sRadius -= 0.0009;
        }
        if( green>-1){
            if(red > -0.6 ){
                red-=0.0005;
            }
            green-=0.0009;
            black-=0.0009;
            
        }
        
    }else{
        
        if(sAX < -270 && sAX > -360 ){
            
        }else{
           sRadius+=0.009;
        }
        if(  green<0){
            if(red < 0){
                red+=0.005;
                
            }
            green+=0.0009;
            black+=0.0009;
        }
    }
    //rotation of objects around it's z-axis and increasing it's y-pos
    if(rotate == 1){
        pYpos = 4;
        pAZ+=1;
        glutPostRedisplay();
        
    }
    //rotation of sun around it's x-axis with certain y-axis angle
    sAY = 135;
    sAX -=0.09;
    //Changin background color
    glClearColor(0.6+red,1.0+green,1.0+black, 0);
    //display function
    display();
    
}

// ----------------------------------------------------------
// keyboard Function
// ----------------------------------------------------------

void keyboard ( int key, int x, int y ) {
    
    //  right arrow - rotates view angle around y-axis
    if (key == GLUT_KEY_RIGHT)
    {
        angley += 5;
        
    }
    //  Left arrow - rotates view angle around y-axis
    else if (key == GLUT_KEY_LEFT)
    {
        
        angley -= 5;
        
    }
    //  x key - rotates objects around y-axis
    else if (key == 'x' ){
        pAY +=5;
    }
    //  a key - rotates objects around y-axis in opposite direction
    else if (key == 'a'){
        pAY -=5;
    }
    //  w key - rotates objects around x-axis
    else if (key == 'w'){
        pYpos = 4;
        pAX -=5;
    }
    //  w key - rotates objects around x-axis in opposite direction
    else if (key == 's'){
        pYpos = 4;
        pAX +=5;
    }
    //  q key - reset rotating objects angles
    else if (key == 'q'){
        pYpos =pAX =pAZ=0;
    }
    //  l key -  resets angles
    else if (key == 'l'){
        angley = anglez = anglex = 0;
    }
    //  r key - start the z-axis rotation
    else if (key == 'r')
    {
        rotate = 1;
        
    }
    //  p key - stop the z-axis rotation
    else if (key == 'p')
    {
        rotate = 0;
        
    }
    
    
    display();
    
}


// ----------------------------------------------------------
// main function
// ----------------------------------------------------------


int main (int argc, char **argv)
{
    //  Initialize GLUT and process user parameters
    glutInit(&argc, argv);
     //  Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    // Set the window's initial width & height
    glutInitWindowSize     (800, 700);
    glutInitWindowPosition (100, 200);
    // Create window
    glutCreateWindow       ("16102736 - 18101617");
    glClearColor(0.6+red,1.0+green,1.0+black, 0);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    
    glutSpecialFunc(keyboard);
    // Callback functions
    glutDisplayFunc (display);
    glutReshapeFunc (reshapeFunc);
    glutIdleFunc    (idleFunc);
    glutFullScreen();
    
    
    
    
    
    
    //  Pass control to GLUT for events
    glutMainLoop();
}

