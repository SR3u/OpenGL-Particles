//
//  Primitives.cpp
//  OpenGL kurs
//
//  Created by SR3u on 10.12.14.
//  Copyright (c) 2014 SR3u. All rights reserved.
//

#include "Primitives.h"

void Plane(int quadCount,GLenum mode)
{
    double quadSize=1.0/quadCount;
    glBegin(mode);
    for (int x = 0; x < quadCount; ++x)
    {
        double xPos =x * quadSize;
        for (int y = 0; y < quadCount; ++y)
        {
            double yPos = y * quadSize;
            glNormal3d(1, 0, 0);
            glVertex3d(0,xPos,            yPos);glTexCoord2d(1,1);
            glVertex3d(0,xPos + quadSize, yPos);glTexCoord2d(0,1);
            glVertex3d(0,xPos + quadSize, yPos + quadSize);glTexCoord2d(0,0);
            glVertex3d(0,xPos,            yPos + quadSize);glTexCoord2d(1,0);
        }
    }
    glEnd();
}