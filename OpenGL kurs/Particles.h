//
//  Particles.h
//  OpenGL kurs
//
//  Created by SR3u on 10.12.14.
//  Copyright (c) 2014 SR3u. All rights reserved.
//

#ifndef OpenGL_kurs_Particles_h
#define OpenGL_kurs_Particles_h

#include <GLUT/glut.h>
#include "Vector3D.h"
#include <list>

const double GRAVITY_CONSTS[]={0.000000000066742,0.00000000066742, //1,2
                               0.0000000066742,0.000000066742,0.00000066742, //3,4,5
                               0.0000066742,0.000066742,0.00066742,0.0066742,//6,7,8,9
                               0.066742,0.66742,6.674,66.74,667.4,6674.0,//10,11,12,13,14,15
                               0.00133484};//16
#define REAL_GRAVITY_CONST GRAVITY_CONSTS[0]
#define GRAVITY_CONST GRAVITY_CONSTS[15]

#define ALPHA_CHANGE 1

template<typename real_t >
class Particle
{
public:
    real_t m;//mass
    real_t alphaspeed;//maxspeed achieved
    vector3d<real_t > p,d;
    vector3d<real_t > oldP;//Position in previous frame
    real_t maxdistance;
    real_t minspeed;//minimum particle speed (if speed is smaller, particle will be removed)
    real_t alpha;//Alpha channel
    bool dead;//if true, particle will be removed
    //Drawing
    void Draw();
    //Drawing
    void Init(vector3d<real_t > _p,//position
              vector3d<real_t > _d,//speed
              real_t _mass,//particle mass
              real_t _maxdistance,//max distance between attractor and particle
                            //if distance is greater, particle will be removed
              real_t _minspeed/*minimum particle speed (if speed is smaller, particle will be removed)*/);
    Particle operator=(const Particle& p);
};

//Particles container
template<typename real_t >
class particles_t: public std::list<Particle<real_t >>{};

template<typename real_t >
class Attractor//Point attractor
{
public:
    bool slowcol;
    real_t maxSpeed;
    vector3d<real_t > p;
    vector3d<real_t > C[4];
    real_t size;
    real_t m;//mass
    //Drawing
    virtual void Draw();
    ///Initialisation, should be called before all oher things
    virtual void Init(vector3d<real_t > _p,//position
                      real_t _size,//size (radius)
                      real_t _mass/*attractor's mass*/);
    //Update single particle state
    /*'delay_millis' is a delay between previous
       and current frame in milliseconds*/
    virtual void UpdateParticle(Particle<real_t > &p,long delay_millis);
    //Update state of all particles in container 'p'
    virtual void UpdateParticles(particles_t<real_t > &p,long delay_millis);
    //Update state of all particles in container 'p' and draws them
    virtual void UpdateAndDrawParticles(particles_t<real_t > &p,long delay_millis);
};

template<typename real_t >
class PlaneAttractor:public Attractor<real_t>
{
public:
    virtual void Draw();
    virtual void UpdateParticle(Particle<real_t > &p,long delay_millis);
};

template<typename real_t >
class Emitter
{
    long curdelay;
    particles_t<real_t > *q;
public:
    real_t maxDistance;
    real_t minspeed;
    size_t maxParticles;
    real_t spread,m;
    vector3d<real_t > p,d;
    long delay;
    real_t speed;
    //Drawing
    void Draw();
    //Update Emitter state
    void Update(long delay_millis);
    void Init(vector3d<real_t > _p,//position
              vector3d<real_t > _d,//emission direction
              long _delay,//emission delay
              real_t _speed,//particle's speed at emission
              real_t _spread,//particle emission spread
              real_t _mass,//particle mass
              real_t _maxDistance,//Maximum distance between particle and emitter
              particles_t<real_t > *_q,//pointer to particles container
              size_t _maxParticles,
              real_t _minspeed/*minimum particle speed (if speed is smaller, particle will be removed)*/);
    //Emit single particle
    void Emit();
};
template<typename real_t>
real_t Max(real_t a,real_t b,real_t c)
{
    if(a>=b&&a>=c)
        return a;
    if (b>=a&&b>=c)
        return b;
    if (c>=b&&c>=a)
        return c;
    return c;
}
template<typename real_t>
real_t Min(real_t a,real_t b,real_t c)
{
    if(a<=b&&a<=c)
        return a;
    if (b<=a&&b<=c)
        return b;
    if (c<=b&&c<=a)
        return c;
    return c;
}
#include "Particle.cpp"
#include "Attractor.cpp"
#include "Emitter.cpp"
#include "PlaneAttractor.cpp"
#endif
