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

class Particle
{
public:
    double m;//mass
    Vector3D p,d;
    Vector3D oldP;//Position in previous frame
    double maxdistance;
    double alpha;//Alpha channel
    bool dead;//if true, particle will be removed
    //Drawing
    void Draw();
    //Drawing
    void Init(Vector3D _p,//position
              Vector3D _d,//speed
              double _mass,//particle mass
              double _maxdistance/*max distance between attractor and particle
                                   if distance is greater^ particle will be removed*/);
    Particle operator=(const Particle& p);
};

//Particles container
typedef std::list<Particle> particles_t;


class Attractor//Point attractor
{
public:
    double alphadistance;
    Vector3D p;
    Vector3D C[4];
    double size;
    double m;//mass
    //Drawing
    virtual void Draw();
    ///Initialisation, should be called before all oher things
    virtual void Init(Vector3D _p,//position
                      double _size,//size (radius)
                      double _mass/*attractor's mass*/);
    //Update single particle state
    /*'delay_millis' is a delay between previous
       and current frame in milliseconds*/
    virtual void UpdateParticle(Particle &p,long delay_millis);
    //Update state of all particles in container 'p'
    virtual void UpdateParticles(particles_t &p,long delay_millis);
};

class PlaneAttractor:public Attractor
{
public:
    virtual void Draw();
    virtual void Init(Vector3D _p,double _size,double _mass);
    virtual void UpdateParticle(Particle &p,long delay_millis);
};

class Emitter
{
    const Attractor *attr;
    long curdelay;
    particles_t *q;
public:
    size_t maxParticles;
    double spread,m;
    Vector3D p,d;
    long delay;
    double speed;
    //Drawing
    void Draw();
    //Update Emitter state
    void Update(long delay_millis);
    void Init(Vector3D _p,//position
              Vector3D _d,//emission direction
              long _delay,//emission delay
              double _speed,//particle's speed at emission
              double _spread,//particle emission spread
              double _mass,//particle mass
              const Attractor *_attr,//pointer to attractor
              particles_t *_q,//pointer to particles container
              size_t _maxParticles);
    //Emit single particle
    void Emit();
};

#endif
