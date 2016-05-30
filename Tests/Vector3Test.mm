//
//  Vector3Test.m
//  OpenGL kurs
//
//  Created by Sergey Rump on 30.05.16.
//  Copyright © 2016 SR3u. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "Particles.h"
using namespace std;

@interface Vector3Tests : XCTestCase

@end

@implementation Vector3Tests

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testLen
{
    Vector3D vec(1,2,3);
    XCTAssert(vec.getSqrLen() == 14, "Invalid vector length");
}

-(void)testEq
{
    Vector3D vec1(1,2,3);
    Vector3D vec2(1,2,3);
    Vector3D vec3(4,5,6);
    
    XCTAssert(vec1 == vec2, "vec1 should be equal to vec2");
    XCTAssert(vec1 != vec3, "vec1 should not be equal to vec3");
}

-(void)testScalarMultiplication
{
    Vector3D vec(1,2,3);
    XCTAssert((vec*3) == Vector3D(3,6,9),"failed to multiply vec");
}

-(void)testAddSub
{
    Vector3D vec1(1,2,3);
    Vector3D vec2(4,5,6);
    XCTAssert(vec1+vec2 == Vector3D(5,7,9), "Strange result of vec1 + vec2");
    XCTAssert(vec2-vec1 == Vector3D(3,3,3), "Strange result of vec2 - vec1");
}

@end
