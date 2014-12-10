//
//  Emitter.cpp
//  OpenGL kurs
//
//  Created by SR3u on 10.12.14.
//  Copyright (c) 2014 SR3u. All rights reserved.
//

#include "Particles.h"
#include <cstdlib>

double dRand(double fMin, double fMax)
{
    double f=(double)rand()/RAND_MAX;
    return fMin+f*(fMax - fMin);
}

void Emitter::Init(Vector3D _p,Vector3D _d,long _delay,double _speed,double _spread,double _mass,const Attractor *_attr,particles_t *_q,size_t _maxParticles)
{
    attr=_attr;
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
}
void Emitter::Emit()
{
    if (q->size()>=maxParticles)
        return;
    Particle np;
    Vector3D D(d.X+dRand(-spread, spread),
               d.Y+dRand(-spread, spread),
               d.Z+dRand(-spread, spread));
    D=D*(1.0/D.getLen())*speed;
    np.Init(p,D,m,(p-attr->p).getLen()*10);
    q->push_back(np);
}
void Emitter::Update(long delay_millis)
{
    if (delay_millis>1000000)
        return;
    curdelay+=delay_millis;
    if ((curdelay>=delay))
    {
        for (int i=0; i<curdelay/delay; i++)
        {
            Emit();
        }
        curdelay=0;
    }
}
void Emitter::Draw()
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