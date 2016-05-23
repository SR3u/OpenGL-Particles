//
//  Particle.cpp
//  OpenGL kurs
//
//  Created by Sergey Rump on 10.12.14.
//  Copyright (c) 2014 Sergey Rump. All rights reserved.
//
#ifndef OpenGL_kurs_Particles_h_Particle
#define OpenGL_kurs_Particles_h_Particle
#include "Particles.h"
#include "Primitives.h"
template<typename real_t>
void Particle<real_t>::Draw()
{
    glPushMatrix();
    glTranslated(p.X, p.Y, p.Z);
    glScaled(0.2, 0.2, 0.2);
    glColor4d(1, 1, 0, alpha);
    glutSolidSphere(1, 3, 3);
    glPopMatrix();
}
template<typename real_t>
void Particle<real_t>::Init(vector3d<real_t> _p, vector3d<real_t> _d,real_t _mass, real_t _maxdistance,real_t _minspeed)
{
    p=_p;
    maxdistance=_maxdistance;
    d=_d;
    alpha=1;
    m=_mass;
    alphaspeed=0.01;
    dead=false;
    minspeed=_minspeed;
}

template<typename real_t>
Particle<real_t> Particle<real_t>::operator=(const Particle<real_t>& P)
{
    Init(P.p, P.d,P.m,P.maxdistance,P.minspeed);
    alphaspeed=P.alphaspeed;
    return *this;
}
#endif