#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include <vector>
#include<bits/stdc++.h>
#include "BmpLoader.h"
#include<time.h>

using namespace std;

const double PI = 3.14159265389;


/* GLUT callback Handlers */


int anglex= 0, angley = 0, anglez = 0;          //rotation angles
int window;
int wired=0;
int shcpt=1;
int animat = 0;


double Txval=0,Tyval=0,Tzval=0,ex=7, ey=2, ez=108,cx=10,cy=5,cz =10;
double tx = -5, ty= -2, tz= -2, rotAngle=0.0, rotAngle1=0.0,rotAngle2=0.0,trns = 45.0,x=10,y=-35,z=0,w=0;
double windowHeight=1200, windowWidth=700;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;
bool flagScale = false, rotFlag = false,l1=true,l2=true,l3=true,l1a=true,l1d=true,l1s=true,l2a=true,l2d=true,l2s=true,l3a=true,l3d=true,l3s=true;
float angle = 0.0f;
bool rotflag1=false,rotflag2=false,rotflag3=false,rotflag4=false,rotflag5=false,rotflag6=false;
float angle1 = 0.0f,ang = 0.0f,ang1 = 0.0f,ang2 = 0.0f,ang3 = 0.0f;
unsigned int ID[]={};

const int L=12;
const int dgre=3;
int ncpt=L+1;
int clikd=0;
const int nt1 = 40;				//number of slices along x-direction
const int ntheta1 = 40;
const int nt = 60;				//number of slices along x-direction
const int ntheta = 60;
GLint viewport[4]; //var to hold the viewport info
GLdouble modelview[16]; //var to hold the modelview info
GLdouble projection[16];
void matColor(float kdr, float kdg, float kdb,  float shiny, int frnt_Back=0, float ambFactor=1.0, float specFactor=1.0);
GLfloat ctrlpoints[L+1][3] =
{
  {-1.0815,3.25404,0},{-0.306167,3.23054,0},
  {0.328194,3.20705,0},{1.24449,3.18355,0},
  {1.15051,2.66667,0},{0.539648,2.59618,0},
  {-0.212188,2.57269,0},{-0.917034,2.57269,0},
  {-1.43392,2.57269,0},{-1.83333,2.73715,0},
  {-2.02129,2.99559,0},{-1.45,3.15,0},
  {-1.075,3.25,0}

};
GLfloat ctrlpoints1[L+1][3] =
{
    {-0.3, .075, 0.0},{-0.25,.6,0},{-0.15,1.1,0},
    { 0.2, 1.6, 0.0},{ 0.5, 1.9, 0.0},
    {1.0, 2.1, 0.0}, {1.4, 2.28, 0.0},
    {1.8, 2.2, 0.0},{2.2, 2.1, 0.0},
    {2.55, 2, 0.0},{3.0, 1.35, 0.0},
    {3.3, .75, 0.0},
    {3.45, .3, 0.0}

};

//double ex=0, ey=0, ez=15, lx=0,ly=0,lz=0, hx=0,hy=1,hz=0;

float wcsClkDn[3],wcsClkUp[3];
class point1
{
public:
    point1()
    {
        x;
        y;
    }
    int x;
    int y;
} clkpt[2];
int flag=0;
long long nCr(int n, int r)
{
    if(r > n / 2) r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for(i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

//polynomial interpretation for N points
void BezierCurve ( double t,  float xy[2])
{
    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0; i<=L; i++)
    {
        int ncr=nCr(L,i);
        double oneMinusTpow=pow(1-t,double(L-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints[i][0];
        y+=coef*ctrlpoints[i][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //return y;
}
void BezierCurve1 ( double t,  float xy[2])
{
    double y=0;
    double x=0;
    t=t>1.0?1.0:t;
    for(int i=0; i<=L; i++)
    {
        int ncr=nCr(L,i);
        double oneMinusTpow=pow(1-t,double(L-i));
        double tPow=pow(t,double(i));
        double coef=oneMinusTpow*tPow*ncr;
        x+=coef*ctrlpoints1[i][0];
        y+=coef*ctrlpoints1[i][1];

    }
    xy[0] = float(x);
    xy[1] = float(y);

    //return y;
}
void setNormal(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(-Nx,-Ny,-Nz);
}
void bottleBezier()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = ctrlpoints[L][0];
    //number of angular slices
    const float dx = (endx - startx) / nt;	//x step size
    const float dtheta = 2*PI / ntheta;		//angular step size

    float t=0;
    float dt=1.0/nt;
    float xy[2];
    BezierCurve( t,  xy);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt; ++i ) //nt 			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve( t,  xy);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= ntheta; ++j )//ntheta
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}
void ballBezier()
{
    int i, j;
    float x, y, z, r;				//current coordinates
    float x1, y1, z1, r1;			//next coordinates
    float theta;

    const float startx = 0, endx = ctrlpoints1[L][0];
    //number of angular slices
    const float dx = (endx - startx) / nt1;	//x step size
    const float dtheta = 2*PI / ntheta1;		//angular step size

    float t=0;
    float dt=1.0/nt1;
    float xy[2];
    BezierCurve1( t,  xy);
    x = xy[0];
    r = xy[1];
    //rotate about z-axis
    float p1x,p1y,p1z,p2x,p2y,p2z;
    for ( i = 0; i < nt1; ++i )  			//step through x
    {
        theta = 0;
        t+=dt;
        BezierCurve1( t,  xy);
        x1 = xy[0];
        r1 = xy[1];

        //draw the surface composed of quadrilaterals by sweeping theta
        glBegin( GL_QUAD_STRIP );
        for ( j = 0; j <= ntheta1; ++j )
        {
            theta += dtheta;
            double cosa = cos( theta );
            double sina = sin ( theta );
            y = r * cosa;
            y1 = r1 * cosa;	//current and next y
            z = r * sina;
            z1 = r1 * sina;	//current and next z

            //edge from point at x to point at next x
            glVertex3f (x, y, z);

            if(j>0)
            {
                setNormal(p1x,p1y,p1z,p2x,p2y,p2z,x, y, z);
            }
            else
            {
                p1x=x;
                p1y=y;
                p1z=z;
                p2x=x1;
                p2y=y1;
                p2z=z1;

            }
            glVertex3f (x1, y1, z1);

            //forms quad with next pair of points with incremented theta value
        }
        glEnd();
        x = x1;
        r = r1;
    } //for i

}


static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0
    {0.0, 0.0, 1.0}, //1
    {1.0, 0.0, 1.0}, //2
    {1.0, 0.0, 0.0}, //3
    {0.0, 1.0, 0.0}, //4
    {0.0, 1.0, 1.0}, //5
    {1.0, 1.0, 1.0}, //6
    {1.0, 1.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};
static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte quadIndices1[1][4] =
{
    {0, 3, 2, 1}
};
static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void drawCube(float x, float y,float z,float a, float b, float c,float p, float q, float r)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { x, y, z, 1.0 };
    GLfloat mat_specular[] = { a,b,c, 1.0 };
    GLfloat mat_diffuse[] = { p, q, r, 1.0 };
    GLfloat mat_shininess[] = {100};
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {

        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);

        glVertex3fv(&v_cube[quadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);glTexCoord2f(0,1);
    }
    glEnd();
}

void drawpyramid(float x, float y,float z,float a, float b, float c,float p, float q, float r)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { x, y, z, 1.0 };
    GLfloat mat_specular[] = { a,b,c, 1.0 };
    GLfloat mat_diffuse[] = { p, q, r, 1.0 };
    GLfloat mat_shininess[] = {100};
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);

        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);glTexCoord2f(0,0);
    }
    glEnd();

}
void light()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {1,1,1, 1.0};
    GLfloat light_diffuse[]  = { 1,1,1, 1.0 };
    GLfloat light_specular[] = { 0.961,0.961,0.761, 1.0 };
    GLfloat light_position[] = { -20,40,15, 1.0 };
    if(l1 == true)
    {
        glEnable( GL_LIGHT0);
        if(l1a == true)
        {
            glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
        }
        else
        {
            glLightfv( GL_LIGHT0, GL_AMBIENT, no_light);
        }

        if(l1d ==true)
        {
            glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
        }
        else
        {
            glLightfv( GL_LIGHT0, GL_DIFFUSE, no_light);
        }
        if(l1s == true)
        {
            glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
        }
        else
        {
            glLightfv( GL_LIGHT0, GL_SPECULAR, no_light);
        }
    }
    else
    {
        glDisable(GL_LIGHT0);
    }


    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();
}
void light1()
{
    glPushMatrix();
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {1.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat light_position[] = {8,18,45, 1.0 };

    if(l3 == true)
    {
        glEnable( GL_LIGHT2);
        if(l3a == true)
        {
            glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
        }
        else
        {
            glLightfv( GL_LIGHT2, GL_AMBIENT, no_light);
        }

        if(l3d ==true)
        {
            glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
        }
        else
        {
            glLightfv( GL_LIGHT2, GL_DIFFUSE, no_light);
        }
        if(l3s == true)
        {
            glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
        }
        else
        {
            glLightfv( GL_LIGHT2, GL_SPECULAR, no_light);
        }
    }
    else
    {
        glDisable(GL_LIGHT2);
    }
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);

    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf( GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
    glPopMatrix();
}
void update()
{

    if (flagScale == true)
    {
        angle += 1;
        if (angle > 60)
        {
            angle = 60;
        }


    }
    if (flagScale == false)
    {
        angle -= 1;
        if (angle < 0)
        {
            angle = 0;
        }
    }
    if (flagScale == true)
    {
        angle1 += 1;
        if (angle1 > 90)
        {
            angle1 = 90;
        }


    }
    if (flagScale == false)
    {
        angle1 -= 1;
        if (angle1 < 0)
        {
            angle1 = 0;
        }
    }
    if (rotFlag == true)
    {
        trns -=0.1;
        if (trns < 10)
        {
            trns = 60;
        }
    }
    if (rotflag1 == true)
    {
        z +=0.1;
        if(z>15){
            ang=90;
            rotflag1 = false;
            z=13-6;
            x+=20;
        }
    }
     if(rotflag3 == true){
                x-=0.1;
                if(x<-21){
                    ang1=90;
                    rotflag3 = false;
                    z-=18;
                    x-=12;
                }
            }
    if (rotflag2 == true)
    {
        z +=0.1;
    }
    if (rotflag4 == true)
    {
        w +=0.1;
        if(w>17){
            ang2=90;
            rotflag4 = false;
            w=10;
            y+=24;
        }
    }
    if(rotflag6 == true){
                y+=0.1;
                if(y>41){
                    ang3=90;
                    rotflag6 = false;
                    w-=32;
                }
            }
    if (rotflag5 == true){
        w +=0.1;
    }
    rotAngle1+= 2;
    if(rotAngle1 > 360 )
        rotAngle1 -= 360;
    rotAngle2+= 0.5;
    if(rotAngle2 > 360 )
        rotAngle2 -= 360;
    glutPostRedisplay();


}


void clockss()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    //printf("%i \n",ltm->tm_hour);
    //printf("%i \n",ltm->tm_min);

    int hour=(ltm->tm_hour%12);
    int minute=ltm->tm_min;
    int second=ltm->tm_sec;
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-7+8,5+5+8,7+2+3);
    glScalef(3,4,0.5);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(-7+8,5+5+8,7+2+3+0.05);
    glScalef(0.3,4,1);
    drawCube(0,0,0,0,0,0,0,0,0);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(-7+8+3-0.3,5+5+8,7+2+3+0.05);
    glScalef(0.3,4,1);
    drawCube(0,0,0,0,0,0,0,0,0);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(-7+8,5+5+8,7+2+3+0.05);
    glScalef(3,0.3,1);
    drawCube(0,0,0,0,0,0,0,0,0);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(-7+8,5+5+8+4,7+2+3+0.05);
    glScalef(3,0.3,1);
    drawCube(0,0,0,0,0,0,0,0,0);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(-7+8+1.5,5+5+8+2,7+2+3+0.5);
    glRotatef(-second*6,0,0,1);
    glScalef(1,0.05,1);
    drawCube(0,0,0,0,0,0,0,0,0);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(-7+8+1.5,5+5+8+2,7+2+3+0.5);
    glRotatef(-minute*6,0,0,1);
    glScalef(0.8,0.05,1);
    drawCube(0,0,0,0,0,0,0,0,0);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(-7+8+1.5,5+5+8+2,7+2+3+0.5);
    glRotatef(-90,0,0,1);
    glRotatef(hour*30,0,0,1);
    glScalef(0.6,0.05,1);
    drawCube(0,0,0,0,0,0,0,0,0);
    glPopMatrix();
}
void wheels()
{
    ///front
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslated(14+0.5,10-0.5,5+2+0.5);
    glRotatef( 90, 0.0, 0.0, 1.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview inf
    glScalef(0.5,0.5,0.5);
    bottleBezier();
    glPopMatrix();
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslated(14-0.5,10-0.5,5+2+0.5+3);
    glRotatef( 90, 0.0, 0.0, 1.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview inf
    glScalef(0.5,0.5,0.5);
    bottleBezier();
    glPopMatrix();
    ///back
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslated(14+4+2,10-0.5,5+2+0.5);
    glRotatef( 90, 0.0, 0.0, 1.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview inf
    glScalef(0.5,0.5,0.5);
    bottleBezier();
    glPopMatrix();
    glPushMatrix();
    glColor3f(0,0,0);
    glTranslated(14+4+2,10-0.5,5+2+0.5+3);
    glRotatef( 90, 0.0, 0.0, 1.0);
    glRotatef(90, 0.0, 1.0, 0.0);
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview inf
    glScalef(0.5,0.5,0.5);
    bottleBezier();
    glPopMatrix();

}
void car()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[10]);
    glPushMatrix();
    glTranslatef(10+2,5+5,7+1);
    glScalef(10,6,3);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,1,0);
    glTranslatef(10+2+0.3,5+5+1,7+1+0.05);
    glScalef(1.5,4,3);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,1,0);
    glTranslatef(10+2+0.3+2,5+5+1+2,7+1+0.05-0.1);
    glScalef(2,2,3.1);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,1,0);
    glTranslatef(10+2+0.3+2+2.75,5+5+1+2,7+1+0.05-0.1);
    glScalef(2,2,3.1);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,1,0);
    glTranslatef(10+2+0.3+2+2.75+2.75,5+5+1+2,7+1+0.05-0.1);
    glScalef(2,2,3.1);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[9]);
    wheels();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void upper_part()
{
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-7,5+5+9,7+2);
    glScalef(18,0.1,4);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-7,5+5+10+1,7+2);
    glScalef(18,0.1,4);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-7+2,5+5+9,7+2);
    glScalef(0.1,2,4);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-7+4,5+5+9,7+2);
    glScalef(0.1,2,4);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-7+6,5+5+9,7+2);
    glScalef(0.2,2,4);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-7+11,5+5+9,7+2);
    glScalef(0.1,2,4);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-7+13,5+5+9,7+2);
    glScalef(0.1,2,4);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-7+15,5+5+9,7+2);
    glScalef(0.05,2,4);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
}
void pyramids()
{
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(10,5+5+7+5,7);
    glScalef(1.5,3,1.5);
    drawpyramid(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(10,5+5+7+5,7+3);
    glScalef(1.5,3,1.5);
    drawpyramid(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-10,5+5+7+5,7);
    glScalef(1.5,3,1.5);
    drawpyramid(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-10,5+5+7+5,7+3);
    glScalef(1.5,3,1.5);
    drawpyramid(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
}
void tower()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[0]);
    ///right tower

    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(10,5,7);
    glScalef(3,5+7+5,1);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(10,5,7+5);
    glScalef(3,5+7+5,1);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(10,5+5+7+4,7);
    glScalef(3,1,5);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();

    ///left tower
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-10,5,7);
    glScalef(3,5+7+5,1);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-10,5,7+5);
    glScalef(3,5+7+5,1);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-10,5+5+7+4,7);
    glScalef(3,1,5);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    ///pyramids
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[8]);
    pyramids();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    ///upper part front
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[7]);
    glPushMatrix();
    glTranslatef(0,0,10);
    glScalef(1,1,0.2);
    upper_part();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,5.5);
    glScalef(1,1,0.2);
    upper_part();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}
void sideroad()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[4]);
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(10+10+5+4.5+0.5,3+1,0);
    //glRotatef(-30,0,0,1);
    glScalef(10,7,15);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(-7-10-10-5-5-1,3+0.5+0.5,0);
    //glRotatef(30,0,0,1);
    glScalef(12,7,15);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void road()
{
    ///right road
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(10,5+5,7+1);
    glScalef(10+10,1,4);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    ///left road
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(-7-10-10,5+5,7+1);
    glScalef(10+10,1,4);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    //glColor3f(1,1,1);
    glTranslatef(-7-10-10+13,5+5,7+1+2);
    glScalef(3,.01,0.3);
    drawCube(1,1,1,1,1,1,1,1,1);
    glPopMatrix();
    ///rotation bridge left
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(-7,5+5,7+1);
    glRotatef(angle,0,0,1);
    glScalef(8.5,1,4);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    ///rotation bridge right
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(10,5+5,7+1+4);
    glRotatef(180,0,1,0);
    glRotatef(angle,0,0,1);
    glScalef(8.5,1,4);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    sideroad();
    glPopMatrix();


}
void bridge()
{
    glPushMatrix();
    tower();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1,0,0);
    clockss();
    glPopMatrix();
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[5]);
    road();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void boat()
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[11]);
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(-5,8,24.5);
    glScalef(5,3,8);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(0,1,1);
    glTranslatef(-4.5,8+2,25);
    glScalef(4,2,7);
    drawCube(0,0.5,0.5,0,1,1,0,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(0,0,0);
    glTranslatef(-4.5+0.5,8+2+2,25+0.5);
    glScalef(3,2,6);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,1,1);
    glTranslatef(-4.5+3,8+2+2.5,25+0.5+0.5);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,1,1);
    glTranslatef(-4.5+3,8+2+2.5,25+.5+2.25);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,1,1);
    glTranslatef(-4.5+3,8+2+2.5,25+.5+4);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-4+1,8+2+2+1+1.15,25+0.5+4+0.5);
    glScalef(0.5,3,0.5);
    drawCube(0.5,0,0,1,0,0,1,0,0);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-4+1,8+2+2+1+1.15,25+.5+2.25+0.5);
    glScalef(0.5,4,0.5);
    drawCube(0.5,0,0,1,0,0,1,0,0);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,0,0);
    glTranslatef(-4+1,8+2+2+1+1.15,25.5+0.5+0.5);
    glScalef(0.5,3,0.5);
    drawCube(0.5,0,0,1,0,0,1,0,0);
    glPopMatrix();

}
void base()
{
    glPushMatrix();
    //glColor3f(0,0,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[2]);
    glTranslatef(-15,0,0);
    glScalef(40,1,30);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(0,0,1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[1]);
    glTranslatef(-15,30,0);
    glScalef(40,1,30);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[1]);
    //glColor3f(1,1,1);
    glTranslatef(-15,0,1);
    glScalef(40,30,5);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPushMatrix();
    //glColor3f(1,1,0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[3]);
    glTranslatef(-15,0,0);
    glScalef(1,30,30);
    //drawCube(0.194,0.345,0.449,0.348, 0.29, 0.398,0.348, 0.29, 0.398);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[6]);
    //glColor3f(1,0,0);
    glTranslatef(25,0,0);
    glScalef(1,30,30);
    //drawCube(0.194,0.345,0.449,0.348, 0.39, 0.698,0.348, 0.39, 0.698);
    drawCube(0.5,0.5,0.5,1,1,1,1,1,1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void showControlPoints()
{
    glPointSize(5.0);
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    for (int i = 0; i <=L; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
}
void showControlPoints1()
{
    glPointSize(5.0);
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    for (int i = 0; i <=L; i++)
        glVertex3fv(&ctrlpoints1[i][0]);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glFrustum(-5,5,-5,5, 4, 50);
    gluPerspective(60,1,1,100);
    //glOrtho(-15, 15, -15, 15,-15,15);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(ex,ey,ez, cx,cy,cz, 0,1,0);

    glViewport(0, 0, 1500, 800);

    glEnable(GL_LIGHTING);
    light();
    light1();
    glScalef(.8,1,1);
    glTranslatef(0,-15,10);//-15
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ID[12]);
    glTranslated(-20,45,15);
    glRotatef( 90, 0.0, 0.0, 1.0);
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); //get the modelview info
    ballBezier();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glScalef(2,2,2);
    base();
    glPopMatrix();
    glTranslatef(10,0,0);
    glPushMatrix();
    glTranslatef(3,-5,trns);//-5
    glScalef(0.5,0.8,0.5);
    boat();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,-3,0);
    glScalef(1,1,4);
    bridge();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x+13,0+2+0.5,22+12+6+z);
    glScalef(1,0.75,1);
    glRotatef(90,0,1,0);
    glRotatef(ang,0,1,0);
    glRotatef(ang1,0,1,0);
    glScalef(1,1,1);
    car();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(y-1,0+2,22+8+12+6+w);
    glScalef(0.75,0.75,1.5);
    glRotatef(90,0,1,0);
    glRotatef(ang2,0,1,0);
    glRotatef(ang3,0,1,0);
    car();
    glPopMatrix();
    /*glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(0,0,25);
    glRotatef(90,0,0,1);
    //glRotatef(-90,1,0,0);

    showControlPoints();
    glPopMatrix();
    glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(0,10,25+5);
    glRotatef(90,0,0,1);
    //glRotatef(-90,1,0,0);

    showControlPoints1();
    glPopMatrix();*/
    glDisable(GL_LIGHTING);
    glFlush();
    glutSwapBuffers();
}
void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case '8': //up arrow to move upwards along Y axis
        ey+=0.10;
        break;
    case '5':
        ey-=0.10;
        break;
    case '4':
        ex-=0.10;
        break;
    case '6':
        ex+=0.10;
        break;
    case '-':
        ez+=0.10;////zoom out
        break;
    case '+':
        ez-=0.10;//zoom in
        break;
    case 'a':
        cx+=1.0;
        break;
    case 'b':
        cy+=1.0;
        break;
    case 'c':
        cz+=1.0;
        break;
    case 'e':
        rotFlag = !rotFlag;
        break;
    case 'n':
        rotflag1 = !rotflag1;
        break;
    case 'm':
        rotflag3 = !rotflag3;
        break;
    case 'o':
        rotflag2 = !rotflag2;
        break;
    case 'p':
        rotflag4 = !rotflag4;
        break;
    case 'q':
        rotflag6 = !rotflag6;
        break;
    case 'r':
        rotflag5 = !rotflag5;
        break;
    case '1':
        l1= !l1;//light1 on/off
        break;
    case '2':
        l3 = !l3;//spot light on/off
        break;
    case 'x':
        l1a= !l1a;//light1 ambient on/off
        break;
    case 'y':
        l1d = !l1d;//light1 diffuse on/off
        break;
    case 'z':
        l1s= !l1s;//light1 specular on/off
        break;
    case 'f':
        l3a= !l3a;//spot light ambient on/off
        break;
    case 'g':
        l3d = !l3d;//spot light diffuse on/off
        break;
    case 'h':
        l3s= !l3s;//spot light specular on/off
        break;
    case 's':
       flagScale= !flagScale;
        break;
    case 27:    // Escape key
        exit(1);
    }
    glutPostRedisplay();
}
void LoadTexture(const char*filename, int num)
{
    glGenTextures(1, &ID[num]);
    glBindTexture(GL_TEXTURE_2D, ID[num]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[num]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}
int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    printf("Keyboard options:\n");
    printf(" +    :Zoom in\n");
    printf(" -    :Zoom out\n");
    printf(" 4    :Go Left\n");
    printf(" 6    :Go Right\n");
    printf(" 5    :Go Down\n");
    printf(" 8    :Go UP\n");
    printf(" a    :Camera movement for Left direction\n");
    printf(" b    :Camera movement for Right direction\n");
    printf(" c    :Camera movement for Up direction\n");
    printf(" s    :Bridge rotation up/down\n");
    printf(" e    :Ship movement on\off\n");
    printf(" n    :Car 1 moving forward in z direction on/off before crossing the bridge\n");
    printf(" m    :Car 1 moving forward in x direction on/off\n");
    printf(" o    :Car 1 moving forward in z direction on/off after crossing the bridge\n");
    printf(" p    :Car 2 moving forward in z direction on/off before crossing the bridge\n");
    printf(" q    :Car 2 moving forward in x direction on/off\n");
    printf(" r    :Car 2 moving forward in z direction on/off after crossing the bridge\n");
    printf(" 1    :Light 1 on/off\n");
    printf(" x    :Light 1 Ambient property on/off\n");
    printf(" y    :Light 1 Diffuse property on/off\n");
    printf(" z    :Light 1 Specular property on/off\n");
    printf(" 2    :Spot Light on/off\n");
    printf(" f    :Spot Light Ambient property on/off\n");
    printf(" g    :Spot Light Diffuse property on/off\n");
    printf(" h    :Spot Light Specular property on/off\n");
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(1500, 800);
    glutCreateWindow("Project-1607067: Vertical lift bridge with traffic control simulation");
    LoadTexture("D:\\4th year 2nd trmm\\grapics design\\lab\\Project\\Project\\brick2.bmp",0);
    LoadTexture("D:\\4th year 2nd trmm\\grapics design\\lab\\Project\\Project\\sky.bmp",1);
    LoadTexture("D:\\4th year 2nd trmm\\grapics design\\lab\\Project\\Project\\water.bmp",2);
    LoadTexture("D:\\4th year 2nd trmm\\grapics design\\lab\\Project\\Project\\index.bmp",3);
    LoadTexture("D:\\4th year 2nd trmm\\grapics design\\lab\\Project\\Project\\road1.bmp",4);
    LoadTexture("D:\\4th year 2nd trmm\\grapics design\\lab\\Project\\Project\\road2.bmp",5);
    LoadTexture("D:\\4th year 2nd trmm\\grapics design\\lab\\Project\\Project\\images.bmp",6);
    LoadTexture("D:\\4th year 2nd trmm\\grapics design\\lab\\Project\\Project\\iron.bmp",7);
    LoadTexture("D:\\4th year 2nd trmm\\grapics design\\lab\\Project\\Project\\brick1.bmp",8);
    LoadTexture("D:\\4th year 2nd trmm\\grapics design\\lab\\Project\\Project\\car1.bmp",9);
    LoadTexture("D:\\4th year 2nd trmm\\grapics design\\lab\\Project\\Project\\car2.bmp",10);
    LoadTexture("D:\\4th year 2nd trmm\\grapics design\\lab\\Project\\Project\\ship.bmp",11);
    LoadTexture("D:\\4th year 2nd trmm\\grapics design\\lab\\Project\\Project\\sun.bmp",12);
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(update);

    glClearColor(0,0,0,1);
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);


    glutMainLoop();

    return 0;
}

