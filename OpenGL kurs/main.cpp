//
//  main.cpp
//  OpenGL_test
//
//  Created by SR3u on 05.09.14.
//  Copyright (c) 2014 SR3u. All rights reserved.
//
/*
 Задание 7.
 1. Эмиттер – точка с заданным направлением, которое варьируется случайным образом в определенных пределах.
 2. Обязательные параметры: присутствует ускорение, прозрачность изменяется в зависимости от скорости частицы
 ​Остальные параметры устанавливаются и изменяются по вашему выбору.
 3. След: присутствует, длина от 5 до 10
 4. Аттрактор: плоскость
 */

#include <iostream>
#include <GLUT/glut.h>
#include "Texture.h"
#include <cmath>
#include "Particles.h"
#include <sys/time.h>
#include "OpenGL_Text.h"
#include <sstream>
#include "MemUsage.h"

bool second_attr;
Attractor<double> secondAttr;

GLfloat aspect;
GLint Width,Height;
GLdouble simStep=0.0;
long delay_millis;

Attractor<double> attr_point,attr_point1,*attr[255];
PlaneAttractor<double> attr_plane,attr_plane1;
int curAttr=3,max_attr=3;
double spread[]={0.0,0.2,0.5,1,10};
int curS=1,max_s=4;
size_t max_particles[]={0,1,2,4,8,16,32,48,64,96,128,192
                       ,256,384,512,768,1024,1536,3072,2048
                       ,6144,4096,8192,12288,16384,24576};
int curP=16,max_p=25;
Emitter<double> em;
particles_t<double> pq;
Texture tex[255];
bool axis=false;

int cam=0,max_cam=5;

void InitParticles(void)
{
    //init attractor
    secondAttr.Init(Vector3D(75,0,0), 3, 500000);
    attr_plane.Init(Vector3D(-25, 0, 0),//position
              25,//size
              500000);//mass
    attr_point.Init(Vector3D(-25, 0, 0),//position
                    2,//size
                    500000);//mass
    attr_plane1.Init(Vector3D(-25, 0, 0),//position
                    50,//size
                    2000000);//mass
    attr_point1.Init(Vector3D(-25, 0, 0),//position
                    4,//size
                    2000000);//mass
    attr[0]=&attr_point;
    attr[1]=&attr_plane;
    attr[2]=&attr_point1;
    attr[3]=&attr_plane1;
    //init emitter
    em.Init(Vector3D(25,0,0),//pos
            Vector3D(-1,1,1),//dir
            20,//delay
            10,//speed
            spread[curS],//spread
            10,//particle mass
            1000, &pq,//attractor and particles container
            max_particles[curP],//Max particles
            0);
}

double CalculateFrameRate(bool use_stdout,long delay)//returns last calculated FPS
{//PARAMS: use_stdout: print fps to stdout; delay: max delay between FPS calculations
    static long oldTime=0;
    static long frames=0;
    static double framesPerSecond=0.0;       // This will store our fps
    timeval time;
    gettimeofday(&time, NULL);
    long millis = (time.tv_sec*1000)+(time.tv_usec/1000);
    frames++;
    delay_millis=millis - oldTime;
    if( delay_millis >delay)
    {
        double realDelay=(millis-oldTime)/1000.0;
        framesPerSecond=frames/realDelay;
        oldTime = millis;
        if (use_stdout)
        {std::cout<<"FPS: "<<framesPerSecond<<" ("<<frames<<"/"<<realDelay<<")"<<"\n";}
        frames=0;
    }
    return framesPerSecond;
}
void init(void)
{
    //glClearColor (0.5, 0.5, 0.5, 0.0);
    glClearColor (0, 0, 0, 0);
    glShadeModel (GL_FLAT);
}
void SetCam(void)
{
    //gluLookAt(25, 25, 25, 0, 0, 0, 0, 1, 0);
    Vector3D p,d;
    p.X=25*sin(simStep);
    p.Y=25;
    p.Z=25*cos(simStep);
    d.X=0;
    d.Y=0;
    d.Z=0;
    switch (cam) {
        case 0:
            p=p*5;
            break;
        case 1:
            p+=em.p;
            d+=em.p;
            break;
        case 2:
            p+=attr[curAttr]->p;
            d+=attr[curAttr]->p;
            break;
        case 3:
            p+=pq.begin()->p;
            d+=pq.begin()->p;
            break;
        case 4:
            p=p*3;
            break;
        case 5:
            break;
        default:
            break;
    }
    gluLookAt(p.X,p.Y,p.Z,d.X,d.Y,d.Z,0,1,0);
    //glRotated(morphStep*5, 0, 1, 0);
}
void DrawAxis(void)
{
    if(!axis){return;}
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glLineWidth(5);
    glPushMatrix();
    glColor3d(1, 0, 0);//OX
    glBegin(GL_LINES);
    glVertex4d(0, 0, 0,1);
    glVertex4d(10, 0, 0,0);
    glEnd();
    glColor3d(0, 1, 0);//OY
    glBegin(GL_LINES);
    glVertex4d(0, 0, 0,1);
    glVertex4d(0, 10, 0,0);
    glEnd();
    glColor3d(0, 0, 1);//OZ
    glBegin(GL_LINES);
    glVertex4d(0, 0, 0,1);
    glVertex4d(0, 0, 10,0);
    glEnd();
    glPopMatrix();
    glPopAttrib();
}
void DisplayFunc(void)
{
    std::stringstream ss;
    double fps=CalculateFrameRate(false, 0);
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(90.0f, aspect, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    SetCam();
    DrawAxis();
    if (second_attr)
    {
        secondAttr.Draw();
        secondAttr.UpdateParticles(pq, delay_millis);
    }
    attr[curAttr]->UpdateAndDrawParticles(pq, delay_millis);
    em.Draw();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex[0].texID);
    attr[curAttr]->Draw();
    glDisable(GL_TEXTURE_2D);
    
    simStep+=0.01;
    glPopMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, Width,0,Height);
    glColor4d(1, 1, 1, 1);
    ss<<"FPS: "<<(int)fps<<" Particles: "<<pq.size()<<"/"<<em.maxParticles;
    OutTextXY(ss.str(), 5, Height-15, 0.1);
    ss.str("");
    ss<<"Max particle speed: "<<attr[curAttr]->maxSpeed;
    OutTextXY(ss.str(), 5, Height-30, 0.1);
    ss.str("");
    ss<<"Attractor mass: "<<attr[curAttr]->m;
    OutTextXY(ss.str(), 5, Height-45, 0.1);
    ss.str("");
    ss<<"Emitter spread: "<<em.spread;
    OutTextXY(ss.str(), 5, Height-60, 0.1);
    ss.str("");
    ss<<"Emitter delay: "<<em.delay;
    OutTextXY(ss.str(), 5, Height-75, 0.1);
    ss.str("");
    ss<<"Particle emission speed: "<<em.speed;
    OutTextXY(ss.str(), 5, Height-90, 0.1);
    ss.str("");
    ss<<"Minimum particle speed: "<<em.minspeed;
    OutTextXY(ss.str(), 5, Height-105, 0.1);
    glPopAttrib();
    glutSwapBuffers();
    em.Update(delay_millis);
}

void IdleFunc(void)
{
    glutPostRedisplay();
}

void ReshapeFunc(int width, int height)
{
    glLoadIdentity();
    Width=width;
    Height=height;
    // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    aspect = (GLfloat)width / (GLfloat)height;
    
    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);
    
    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(90.0f, aspect, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    //SetCam();
    //glLoadIdentity();
}

void MouseFunc(int button, int state, int x, int y)
{
    /*switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                cam++;
                break;
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                cam--;
                break;
            break;
        default:
            break;
    }
    if (cam<0)
        cam=max_cam;
    if (cam>max_cam)
        cam=0;*/
    glutPostRedisplay();
}
void KeyboardFunc(unsigned char key,int par1,int par2)
{
    switch (key)
    {
        case 'w':
        case 'W':
            cam++;
            break;
        case 'S':
        case 's':
            cam--;
            break;
        case 'A':
        case 'a':
            curAttr--;
            break;
        case 'D':
        case 'd':
            curAttr++;
            break;
        case 'Q':
        case 'q':
            curS--;
            break;
        case 'E':
        case 'e':
            curS++;
            break;
        case 'Z':
        case 'z':
            axis=!axis;
            break;
        case 'G':
        case 'g':
            second_attr=!second_attr;
            break;
        case '+':
        case '=':
            curP++;
            break;
        case '<':
        case ',':
            em.delay--;
            break;
        case '>':
        case '.':
            em.delay++;
            break;
        case '1':
        case '!':
            em.minspeed-=0.1;
            break;
        case '2':
        case '@':
            em.minspeed+=0.1;
            break;
        case '3':
        case '#':
            em.speed-=0.1;
            break;
        case '4':
        case '$':
            em.speed+=0.1;
            break;
        case '-':
        case '_':
            curP--;
            break;
        case '0':
        case ')':
            pq.clear();
            break;
        case '9':
        case '(':
            attr[0]->slowcol=!attr[0]->slowcol;
            attr[1]->slowcol=!attr[1]->slowcol;
            attr[2]->slowcol=!attr[2]->slowcol;
            attr[3]->slowcol=!attr[3]->slowcol;
            break;
        default:
            break;
    }
    if (em.delay<0)
        em.delay=0;
    if (em.minspeed<0)
        em.minspeed=0;
    if (em.speed<0)
        em.minspeed=0;
    if (cam<0)
        cam=max_cam;
    if (cam>max_cam)
        cam=0;
    if (curAttr<0)
        curAttr=max_attr;
    if (curAttr>max_attr)
        curAttr=0;
    if (curS<0)
        curS=max_s;
    if (curS>max_s)
        curS=0;
    if (curP<0)
        curP=max_p;
    if (curP>max_p)
        curP=0;
    em.maxParticles=max_particles[curP];
    em.spread=spread[curS];
    glutPostRedisplay();
}
int main(int argc, char** argv)
{
    std::cout<<"/************************************************************/"
    "\n\nСИСТЕМА ЧАСТИЦ\n\n"
    "УПРАВЛЕНИЕ:\n"
    "        0 - стереть все частицы\n"
    "        </> - изменить задержку выброса частиц\n"
    "        +/- изменить макс. количество частиц\n"
    "        W/S -- переключить камеру\n"
    "        A/D - изменить аттрактор\n"
    "        Q/E - изменить разброс\n"
    "        1/2 - изменить минимальную скорость частицы (если частица медленнее данной скорости, то она \"погибает\")\n"
    "        3/4 - изменить скорость частицы\n"
    "        G -  вкл/выкл второй аттрактор\n"
    "        9 - переключить collision’ы\n"
    "        Z - вкл/выкл оси\n\n"
    "/************************************************************/\n";
    InitParticles();
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_ALPHA);
    glutInitWindowSize (700,700);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init();
    glutDisplayFunc(DisplayFunc);
    glutReshapeFunc(ReshapeFunc);
    glutMouseFunc(MouseFunc);
    glutKeyboardFunc(KeyboardFunc);
    glutIdleFunc(IdleFunc);
    LoadTGATexture(&(tex[0]),(char*)"Uncompressed.tga");
    glutMainLoop();
    return 0;
}
