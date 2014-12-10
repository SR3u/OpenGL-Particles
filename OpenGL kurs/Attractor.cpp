//
//  Attractor.cpp
//  OpenGL kurs
//
//  Created by SR3u on 10.12.14.
//  Copyright (c) 2014 SR3u. All rights reserved.
//

#include "Attractor.h"
#include "Primitives.h"

void Attractor::Init(Vector3D _p,double _size,double _force)
{
    p=_p;
    size=_size;
    c.X=p.X+size/2;
    c.Y=p.Y+size/2;
    c.Z=p.Y+size/2;
    
    C[0]=Vector3D(0,0,0);
    C[1]=Vector3D(0,0 + size, 0);
    C[2]=Vector3D(0,0 + size, 0 + size);
    C[3]=Vector3D(0,0,0 + size);

    
    C[0]+=p;
    C[1]+=p;
    C[2]+=p;
    C[3]+=p;
    force=_force;
}
void Attractor::Draw()
{
    glPushMatrix();
    glTranslated(p.X, p.Y, p.Z);
    glScaled(size, size, size);
    glColor4d(1, 1, 1, 1);
    Plane(1, GL_QUADS);
    glPopMatrix();
}