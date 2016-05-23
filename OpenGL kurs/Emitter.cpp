//
//  Emitter.cpp
//  OpenGL kurs
//
//  Created by Sergey Rump on 10.12.14.
//  Copyright (c) 2014 Sergey Rump. All rights reserved.
//
#ifndef OpenGL_kurs_Particles_h_Emitter
#define OpenGL_kurs_Particles_h_Emitter
#include "Particles.h"
#include <cstdlib>

template<typename real_t>
real_t dRand(real_t fMin, real_t fMax)
{
    real_t f=(double)rand()/RAND_MAX;
    return fMin+f*(fMax - fMin);
}
template<typename real_t>
void Emitter<real_t>::Init(vector3d<real_t> _p,vector3d<real_t> _d,long _delay,real_t _speed,
                   real_t _spread,real_t _mass,real_t _maxDistance,particles_t<real_t> *_q,
                   size_t _maxParticles,real_t _minspeed)
{
    speed=_speed;
    p=_p;d=_d;
    delay=_delay;
    curdelay=0;
    spread=_spread;
    q=_q;
    curdelay=0;
    d=d*(1.0/d.getLen());
    m=_mass;
    maxParticles=_maxParticles;
    maxDistance=_maxDistance;
}
template<typename real_t>
void Emitter<real_t>::Emit()
{
    if (q->size()>=maxParticles)
        return;
    Particle<real_t> np;
    vector3d<real_t> D(d.X+dRand(-spread, spread),
               d.Y+dRand(-spread, spread),
               d.Z+dRand(-spread, spread));
    D=D*(1.0/D.getLen())*speed;
    np.Init(p,D,m,maxDistance,minspeed);
    q->push_back(np);
}
template<typename real_t>
void Emitter<real_t>::Update(long delay_millis)
{
    if (delay_millis>1000000)
        return;
    curdelay+=delay_millis;
    if ((curdelay>=delay))
    {   if(delay==0){Emit();return;}
        for (int i=0; i<curdelay/delay; i++)
        {
            Emit();
        }
        curdelay=0;
        curdelay=delay_millis%delay;
    }
}
template<typename real_t>
void Emitter<real_t>::Draw()
{
    glPushMatrix();
    glTranslated(p.X, p.Y, p.Z);
    glColor4d(0, 1, 0, 1);
    glutSolidSphere(1, 10, 10);
    glPopMatrix();
    /*glPushMatrix();
    glBegin(GL_LINES);
    glVertex3d(p.X, p.Y, p.Z);
    glVertex3d(d.X, d.Y, d.Z);
    glEnd();
    glPopMatrix();*/
}
#endif