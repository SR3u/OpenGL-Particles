//
//  Attractor.cpp
//  OpenGL kurs
//
//  Created by SR3u on 10.12.14.
//  Copyright (c) 2014 SR3u. All rights reserved.
//

#include "Particles.h"
#include "Primitives.h"

void Attractor::Init(Vector3D _p,double _size,double _mass)
{
    p=_p;
    size=_size;
    Vector3D c;
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
    
    
    p=c;
    m=_mass;
}

void Attractor::UpdateParticles(particles_t &P,long delay_millis)
{
    for (particles_t::iterator i=P.begin(); i!=P.end(); i++)
    {
        this->UpdateParticle(*i, delay_millis);
        if (i->dead)
        {
            P.erase(i);
        }
    }
}
void Attractor::UpdateParticle(Particle &P,long delay_millis)
{
    double distance=(P.p-p).getLen();
    double delay=delay_millis/1000.0;
    //P.alpha=distance/maxdistance;
    Vector3D Pos,Dir,oldPos=P.p;
    Pos=P.p+P.d*delay;
    Dir=(p-P.p)*delay*(m*GRAVITY_CONST)/(distance*distance)+P.d;
    if (((P.p-p)*(oldPos-p)==-1)||distance<size||distance>P.maxdistance)
    {
        P.dead=true;
    }
    P.p=Pos;P.d=Dir;
}

void Attractor::Draw()
{
    glPushMatrix();
    glTranslated(C[0].X, C[0].Y, C[0].Z);
    glScaled(size, size, size);
    glColor4d(1, 0, 0, 1);
    glutSolidSphere(1, 10, 10);
    //Plane(1, GL_QUADS);
    glPopMatrix();
}