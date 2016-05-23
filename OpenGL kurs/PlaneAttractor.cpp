//
//  PlaneAttractor.cpp
//  OpenGL kurs
//
//  Created by Sergey Rump on 10.12.14.
//  Copyright (c) 2014 Sergey Rump. All rights reserved.
//

#ifndef OpenGL_kurs_Particles_h_PlaneAttractor
#define OpenGL_kurs_Particles_h_PlaneAttractor

#include "Particles.h"

template<typename real_t>
bool ColPlane(vector3d<real_t> &p, vector3d<real_t> &o, vector3d<real_t> v[4])
{
    if (((p.X-v[0].X)*(o.X-v[0].X))<0)
    {
        /*if ((p.Y>=v[0].Y&&p.Y<=v[2].Y))
            if((p.Z>=v[0].Z&&p.Z<=v[2].Z))
                return true;*/
        if (p.Y<v[0].Y)
            return false;
        if(p.Y>v[2].Y)
            return false;
        if(p.Z<v[0].Z)
            return false;
        if(p.Z>v[2].Z)
            return false;
        return true;
    }
    return false;
}
template<typename real_t>
void boundPlane(vector3d<real_t> &p, vector3d<real_t> v[4])
{
    if (p.X<=v[0].X)
    {
        if (p.Y<v[0].Y)
            p.Y=v[0].Y;
        if(p.Y>v[2].Y)
            p.Y=v[2].Y;
        if(p.Z>=v[0].Z)
            p.Z=v[0].Z;
        if(p.Z<=v[2].Z)
            p.Z=v[2].Z;
    }
}
template<typename real_t>
void PlaneAttractor<real_t>::UpdateParticle(Particle<real_t> &P,long delay_millis)
{
    vector3d<real_t> nPos(this->p);
    boundPlane(nPos, this->C);
    real_t distance=(P.p-nPos).getLen();
    real_t delay=delay_millis/1000.0;
    real_t speed=P.d.getLen();
    if (speed>this->maxSpeed){this->maxSpeed=speed;}
    if (speed<P.minspeed){P.dead=true;return;}
#if ALPHA_CHANGE
    if(speed>P.alphaspeed){P.alphaspeed=speed;}
    P.alpha=P.d.getLen()/P.alphaspeed;
#endif
    vector3d<real_t> Pos,Dir;
    Pos=P.p+P.d*delay;
    Dir=(nPos-P.p)*delay*(this->m*GRAVITY_CONST)/(distance*distance)+P.d;
    if (distance>P.maxdistance||ColPlane(Pos, P.p, this->C))
    {
        P.dead=true;
    }
    P.oldP=P.p;
    P.p=Pos;P.d=Dir;
}
template<typename real_t>
void PlaneAttractor<real_t>::Draw()
{
    glPushMatrix();
    glTranslated(this->C[0].X,this->C[0].Y,this->C[0].Z);
    glScaled(this->size, this->size, this->size);
    glColor4d(1, 1, 1, 1);
    Plane(1, GL_QUADS);
    glPopMatrix();
}
#endif