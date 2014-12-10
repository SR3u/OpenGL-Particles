//
//  Particle.cpp
//  OpenGL kurs
//
//  Created by SR3u on 10.12.14.
//  Copyright (c) 2014 SR3u. All rights reserved.
//

#include "Particle.h"
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
void Particle::Init(Vector3D _p,Vector3D _d,
                    const Attractor *_attr,double _maxdistance)
{
    oldP=p;
    attr=_attr;
    p=_p;
    d=_d;
    dead=false;
    alpha=1.0;
    maxdistance=_maxdistance;
    return;
}
bool Particle::Col(Vector3D v[4],double s)
{
    Vector3D &o=oldP;
    if (((p.X-v[0].X)*(o.X-v[0].X))<0)
    {
        if ((p.Y>=v[0].Y&&p.Y<=v[2].Y))
            if((p.Z>=v[0].Z&&p.Z<=v[2].Z))
            return true;
    }
    return false;
}
void Particle::Collide(double distance,double delay)
{
    if (distance>maxdistance*2)
        dead=true;
    if (Col((Vector3D*)attr->C, attr->size))
        dead=true;
}
void Particle::Update(long delay_millis)
{
    double distance=(p-attr->c).getLen();
    double delay=delay_millis/1000.0;
    Collide(distance,delay);
    alpha=distance/maxdistance;
    Vector3D P,D;
    P=p+d*delay;
    D=(attr->c-p)*delay*attr->force/(distance*distance) +d;
    bool DEAD=dead;
    Init(P, D, attr,maxdistance);
    dead=DEAD;
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



Particle Particle::operator=(const Particle& P)
{
    Init(P.p, P.d,P.attr,P.maxdistance);
    return *this;
}
