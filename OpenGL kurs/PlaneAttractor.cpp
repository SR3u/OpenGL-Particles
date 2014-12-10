//
//  PlaneAttractor.cpp
//  OpenGL kurs
//
//  Created by SR3u on 10.12.14.
//  Copyright (c) 2014 SR3u. All rights reserved.
//

#include "Particles.h"
#include "Primitives.h"

void PlaneAttractor::Init(Vector3D _p,double _size,double _mass)
{
    p=_p;
    size=_size;
    Vector3D c;
    c.X=p.X+size/2;
    c.Y=p.Y+size/2;
    c.Z=p.Z+size/2;
    
    C[0]=Vector3D(0,0,0);
    C[1]=Vector3D(0,0 + size, 0);
    C[2]=Vector3D(0,0 + size, 0 + size);
    C[3]=Vector3D(0,0,0 + size);

    
    C[0]+=p;
    C[1]+=p;
    C[2]+=p;
    C[3]+=p;
    p=c;
    m=_mass;
    alphadistance=25;
}
bool Col(Vector3D &p, Vector3D &o, Vector3D v[4],double s)
{
    if (((p.X-v[0].X)*(o.X-v[0].X))<0)
    {
        if ((p.Y>=v[0].Y&&p.Y<=v[2].Y))
            if((p.Z>=v[0].Z&&p.Z<=v[2].Z))
                return true;
    }
    return false;
}
void PlaneAttractor::UpdateParticle(Particle &P,long delay_millis)
{
    double distance=(P.p-p).getLen();
    double delay=delay_millis/1000.0;
    P.alpha=distance/alphadistance;
    Vector3D Pos,Dir,oldPos=P.p;
    Pos=P.p+P.d*delay;
    Dir=(p-P.p)*delay*(m*GRAVITY_CONST)/(distance*distance)+P.d;
    if (((P.p-p)*(oldPos-p)==-1)||distance<size||distance>P.maxdistance)
    {
        P.dead=true;
    }
    P.p=Pos;P.d=Dir;
}

/* void Particle::Collide(double distance,double delay)
 {
 if (distance>maxdistance*2)
 dead=true;
 if (Col((Vector3D*)attr->C, attr->size))
 dead=true;
 }
 */

void PlaneAttractor::Draw()
{
    glPushMatrix();
    glTranslated(C[0].X, C[0].Y, C[0].Z);
    glScaled(size, size, size);
    glColor4d(1, 1, 1, 1);
    Plane(1, GL_QUADS);
    glPopMatrix();
}