//
//  AttractorTest.m
//  OpenGL kurs
//
//  Created by Sergey Rump (SPHERE) on 23.05.2016.
//  Copyright © 2016 SR3u. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "Particles.h"

@interface ParticlesTests : XCTestCase
@end

@implementation ParticlesTests
Attractor<double> attractor;

- (void)setUp
{
    [super setUp];
    attractor.Init(*(new Vector3D(0,0,0)),10,10);
    attractor.Init(*(new Vector3D(0,0,0)),10,10);
}

- (void)tearDown
{
    [super tearDown];
}

-(void) testDistanceDestruction
{
    Particle<double> pCollide,pNear,pFar;
    pCollide.Init(Vector3D(0.1,0.1,0.1), Vector3D(1,1,1), 1, 100, 1);
    pNear.Init(Vector3D(30,30,30), Vector3D(1,1,1), 1, 100, 1);
    pFar.Init(Vector3D(100,100,100), Vector3D(1,1,1), 1, 100, 1);
    attractor.UpdateParticle(pCollide, 1.0);
    attractor.UpdateParticle(pFar, 1.0);
    attractor.UpdateParticle(pNear, 1.0);
    XCTAssert(pFar.dead,"Particle pCollide should be dead due to collision with attractor distance < attractor.radius");
    XCTAssert(pFar.dead,"Particle pFar should be dead due to distance > maxdistance");
    XCTAssert(pNear.dead == false,"Particle pNear should be not dead due to distance < maxdistance");
}
-(void) testSpeedDestruction
{
    Particle<double> pSlow,pFast;
    pSlow.Init(Vector3D(30,30,30), Vector3D(1,1,1), 1, 100, 10);
    pFast.Init(Vector3D(30,30,30), Vector3D(10,10,10), 1, 100, 10);
    attractor.UpdateParticle(pSlow, 1.0);
    attractor.UpdateParticle(pFast, 1.0);
    XCTAssert(pFast.dead == false,"Particle pFast should be not dead due speed > minspeed");
    XCTAssert(pSlow.dead,"Particle pSlow should be dead due to spwwd < minspeed");
}

@end
