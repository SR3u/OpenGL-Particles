//
//  Particle.cpp
//  OpenGL kurs
//
//  Created by SR3u on 10.12.14.
//  Copyright (c) 2014 SR3u. All rights reserved.
//

#include "Particles.h"
#include "Primitives.h"

double Max(double a,double b,double c)
{
    if(a>=b&&a>=c)
        return a;
    if (b>=a&&b>=c)
        return b;
    if (c>=b&&c>=a)
        return c;
    return c;
}
double Min(double a,double b,double c)
{
    if(a<=b&&a<=c)
        return a;
    if (b<=a&&b<=c)
        return b;
    if (c<=b&&c<=a)
        return c;
    return c;
}
void Particle::Draw()
{
    glPushMatrix();
    glTranslated(p.X, p.Y, p.Z);
    glScaled(0.2, 0.2, 0.2);
    glColor4d(1, 1, 0, alpha);
    glutSolidSphere(1, 3, 3);
    glPopMatrix();
}
void Particle::Init(Vector3D _p, Vector3D _d,double _speed,double _mass, double _maxdistance)
{
    p=_p;
    maxdistance=_maxdistance;
    d=_d;
    speed=_speed;
    alpha=1;
    m=_mass;
    dead=false;
}

Particle Particle::operator=(const Particle& P)
{
    Init(P.p, P.d,P.speed,P.m,P.maxdistance);
    return *this;
}
