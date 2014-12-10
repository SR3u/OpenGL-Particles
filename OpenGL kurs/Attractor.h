//
//  Attractor.h
//  OpenGL kurs
//
//  Created by SR3u on 10.12.14.
//  Copyright (c) 2014 SR3u. All rights reserved.
//

#ifndef __OpenGL_kurs__Attractor__
#define __OpenGL_kurs__Attractor__

#include <GLUT/glut.h>
#include "Vector3D.h"

class Attractor
{
public:
    Vector3D p;
    Vector3D c;
    Vector3D C[4];
    double size;
    double force;
    void Draw();
    void Init(Vector3D _p,double _size,double _force);
};

#endif /* defined(__OpenGL_kurs__Attractor__) */
