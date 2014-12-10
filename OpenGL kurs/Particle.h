//
//  Particle.h
//  OpenGL kurs
//
//  Created by SR3u on 10.12.14.
//  Copyright (c) 2014 SR3u. All rights reserved.
//

#ifndef __OpenGL_kurs__Particle__
#define __OpenGL_kurs__Particle__

#include "Attractor.h"
#include <GLUT/glut.h>

class Particle
{
    double alpha;
    double maxdistance;
    const Attractor *attr;
    void Collide(double distance,double delay);
    bool Col(Vector3D v[4],double s);
    double speed;
public:
    Vector3D p,d;
    Vector3D oldP;
    bool dead;
    void Draw();
    void Update(long delay_millis);
    void Init(Vector3D _p,Vector3D _d,
              const Attractor *_attr,
              double _maxdistance);
    Particle operator=(const Particle& p);
};

#endif /* defined(__OpenGL_kurs__Particle__) */
