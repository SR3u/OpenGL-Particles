//
//  Emitter.h
//  OpenGL kurs
//
//  Created by SR3u on 10.12.14.
//  Copyright (c) 2014 SR3u. All rights reserved.
//

#ifndef __OpenGL_kurs__Emitter__
#define __OpenGL_kurs__Emitter__

#include <GLUT/glut.h>

#include "Attractor.h"
#include "Particle.h"
#include <list>
typedef std::list<Particle> particles_t;

class Emitter
{
    const Attractor *attr;
    long curdelay;
    particles_t *q;
    double spread;
    size_t maxParticles;
public:
    Vector3D p,d;
    long delay;
    double speed;
    void Draw();
    void Update(long delay_millis);
    void Init(Vector3D _p,Vector3D _d,long _delay,double _speed,double _spread,
              const Attractor*_attr,particles_t *_q,size_t _maxParticles);
    void Emit();
};

#endif /* defined(__OpenGL_kurs__Emitter__) */
