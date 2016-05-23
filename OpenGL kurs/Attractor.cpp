//
//  Attractor.cpp
//  OpenGL kurs
//
//  Created by Sergey Rump on 10.12.14.
//  Copyright (c) 2014 Sergey Rump. All rights reserved.
//

#include "Particles.h"
#include "Primitives.h"

#ifndef OpenGL_kurs_Particles_h_Attractor
#define OpenGL_kurs_Particles_h_Attractor

template<typename real_t >
void Attractor<real_t>::Init(vector3d<real_t> _p,real_t _size,real_t _mass)
{
    p=_p;
    size=_size;
    
    C[0]=vector3d<real_t>(-size/2.0,-size/2.0,-size/2.0);
    C[1]=vector3d<real_t>(-size/2.0,+size/2.0,-size/2.0);
    C[2]=vector3d<real_t>(-size/2.0,+size/2.0,+size/2.0);
    C[3]=vector3d<real_t>(-size/2.0,-size/2.0,+size/2.0);

    C[0]+=p;
    C[1]+=p;
    C[2]+=p;
    C[3]+=p;
    m=_mass;
    maxSpeed=0;
    slowcol=false;
}
template<typename real_t >
void Attractor<real_t>::UpdateParticles(particles_t<real_t> &P,long delay_millis)
{
    for (typename particles_t<real_t>::iterator i=P.begin(); i!=P.end(); i++)
    {
        this->UpdateParticle(*i, delay_millis);
        if (i->dead)
        {
            typename particles_t<real_t>::iterator prev = i;
            i++;
            P.erase(prev);
        }
        else
        {
            i++;
        }
    }
}
template<typename real_t >
void Attractor<real_t>::UpdateAndDrawParticles(particles_t<real_t> &P,long delay_millis)
{
    for (typename particles_t<real_t>::iterator i=P.begin(); i!=P.end(); )
    {
        this->UpdateParticle(*i, delay_millis);
        i->Draw();
        if (i->dead)
        {
            typename particles_t<real_t>::iterator prev = i;
            i++;
            P.erase(prev);
        }
        else
        {
            i++;
        }
    }
}
template<typename real_t >
bool SphereCol(vector3d<real_t> &p, vector3d<real_t> &o, vector3d<real_t> &s,real_t r)
{
    vector3d<real_t> dir=(p-o);
    real_t pr=(s-o)*dir;
    if (pr>dir.getLen()+r||pr<-r)
        return false;
    vector3d<real_t> prV=o+dir*pr;
    if((prV-s).getLen()>r*r)
        return false;
    return true;
}
template<typename real_t >
void Attractor<real_t>::UpdateParticle(Particle<real_t> &P,long delay_millis)
{
    real_t distance=(P.p-p).getLen();
    real_t delay=delay_millis/1000.0;
    real_t speed=P.d.getLen();
    if (speed>maxSpeed){maxSpeed=speed;}
    if (speed<P.minspeed){P.dead=true;return;}
#if ALPHA_CHANGE
    if(speed>P.alphaspeed){P.alphaspeed=speed;}
    P.alpha=P.d.getLen()/P.alphaspeed;
#endif
    vector3d<real_t> Pos,Dir,oldPos=P.p;
    Pos=P.p+P.d*delay;
    Dir=(p-P.p)*delay*(m*GRAVITY_CONST)/(distance*distance)+P.d;
    if (((P.p-p)*(oldPos-p)==-1)||distance<size
        ||distance>P.maxdistance)
    {
        P.dead=true;
        return;
    }
    if (slowcol)
    {
        if(SphereCol(Pos, P.p, p,size))
        {P.dead=true;return;}
    }
    P.oldP=P.p;
    P.p=Pos;P.d=Dir;
}
template<typename real_t >
void Attractor<real_t>::Draw()
{
    glPushMatrix();
    glTranslated(p.X, p.Y, p.Z);
    glScaled(size, size, size);
    glColor4d(1, 0, 0, 1);
    glutSolidSphere(1, 10, 10);
    //Plane(1, GL_QUADS);
    glPopMatrix();
}
#endif