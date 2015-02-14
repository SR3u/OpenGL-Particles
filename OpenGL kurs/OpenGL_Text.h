//
//  OpenGL_Text.h
//  OpenGL kurs
//
//  Created by SR3u on 10.12.14.
//  Copyright (c) 2014 SR3u. All rights reserved.
//

#ifndef __OpenGL_kurs__OpenGL_Text__
#define __OpenGL_kurs__OpenGL_Text__

#include <GLUT/glut.h>
#include <string>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

void OutTextXYZ(const std::string&text,double x,double y,double z,double size);
void OutTextXY(const std::string&text,double x,double y,double size);

#endif /* defined(__OpenGL_kurs__OpenGL_Text__) */
