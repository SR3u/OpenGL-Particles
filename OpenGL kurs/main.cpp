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
#include "Emitter.h"
#include <sys/time.h>

GLdouble simStep=0.0;
long delay_millis;

Attractor attr;
Emitter em;
particles_t pq;

Texture tex[255];

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
    gluLookAt(25*sin(simStep), 25, 25*cos(simStep), 0, 0, 0, 0, 1, 0);
    //glRotated(morphStep*5, 0, 1, 0);
}
void DrawAxis(void)
{
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
    CalculateFrameRate(false, 0);
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    SetCam();
    DrawAxis();
    
    for (particles_t::iterator i=pq.begin(); i!=pq.end(); i++)
    {
        i->Update(delay_millis);
        i->Draw();
        if (i->dead)
        {
            pq.erase(i);
        }
    }
    em.Draw();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex[0].texID);
    attr.Draw();
    glDisable(GL_TEXTURE_2D);
    
    simStep+=0.01;
    glPopMatrix();
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
    // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    
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
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
                break;
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
                break;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}
void KeyboardFunc(unsigned char key,int par1,int par2)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_DOWN:
            break;
        default:
            break;
    }
    glutPostRedisplay();
}
int main(int argc, char** argv)
{
    //fig.Init();
    attr.Init(Vector3D(-25, -12.5, -12.5), 25,500);
    em.Init(Vector3D(25,0,0),//pos
            Vector3D(0,1,1),//dir
            1,//delay
            19,//speed
            0,//spread
            &attr, &pq,//attractor and particles container
            8*2048);
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (700,700);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init();
    glutDisplayFunc(DisplayFunc);
    glutReshapeFunc(ReshapeFunc);
    glutMouseFunc(MouseFunc);
    glutKeyboardFunc(KeyboardFunc);
    glutIdleFunc(IdleFunc);
    LoadTGATexture(&(tex[0]),"/Users/sr3u/Documents/XCode Projects/OpenGL 3/OpenGL 3/Uncompressed.tga");
    glutMainLoop();
    return 0;
}
