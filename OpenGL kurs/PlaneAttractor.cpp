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
    C[0]=Vector3D(0,-size/2.0,-size/2.0);
    C[1]=Vector3D(0,+size/2.0,-size/2.0);
    C[2]=Vector3D(0,+size/2.0,+size/2.0);
    C[3]=Vector3D(0,-size/2.0,+size/2.0);

    
    C[0]+=p;
    C[1]+=p;
    C[2]+=p;
    C[3]+=p;
    m=_mass;
    maxSpeed=0;
}
bool Col(Vector3D &p, Vector3D &o, Vector3D v[4])
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
void bound(Vector3D &p, Vector3D v[4])
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
void PlaneAttractor::UpdateParticle(Particle &P,long delay_millis)
{
    Vector3D nPos(p);
    bound(nPos, C);
    double distance=(P.p-nPos).getLen();
    double delay=delay_millis/1000.0;
    double speed=P.d.getLen();
    if (speed>maxSpeed){maxSpeed=speed;}
#if ALPHA_CHANGE
    if(speed>P.alphaspeed){P.alphaspeed=speed;}
    P.alpha=P.d.getLen()/P.alphaspeed;
#endif
    Vector3D Pos,Dir;
    Pos=P.p+P.d*delay;
    Dir=(nPos-P.p)*delay*(m*GRAVITY_CONST)/(distance*distance)+P.d;
    if (distance>P.maxdistance||Col(Pos, P.p, C))
    {
        P.dead=true;
    }
    P.oldP=P.p;
    P.p=Pos;P.d=Dir;
}
void PlaneAttractor::Draw()
{
    glPushMatrix();
    glTranslated(C[0].X, C[0].Y, C[0].Z);
    glScaled(size, size, size);
    glColor4d(1, 1, 1, 1);
    Plane(1, GL_QUADS);
    glPopMatrix();
}