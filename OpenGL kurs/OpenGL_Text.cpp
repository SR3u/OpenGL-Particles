//
//  OpenGL_Text.cpp
//  OpenGL kurs
//
//  Created by Sergey Rump on 10.12.14.
//  Copyright (c) 2014 Sergey Rump. All rights reserved.
//

#include "OpenGL_Text.h"
#include <string>

void OutTextXY(const std::string&text,double x,double y,double size)
{
    OutTextXYZ(text, x, y, 0, size);
}
void OutTextXYZ(const std::string&text,double x,double y,double z,double size)
{
    glPushMatrix();
    glTranslated(x,y,z);
    glScaled(size, size, size);
    int i=0;
    for (std::string::const_iterator itr=text.begin();itr!=text.end();itr++,i++)
    {
        glTranslated(1, 0, 0);
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *itr);
    }
    glPopMatrix();
}