//
//  Texture.cpp
//  OpenGL 3
//
//  Created by Sergey Rump on 28.11.14.
//  Copyright (c) 2014 Sergey Rump. All rights reserved.
//

#include "Texture.h"
#include "Tga.h"
#include <cstdlib>
#include <GLUT/GLUT.h>

bool LoadTGATexture(Texture * texture, char * filename)
{
    if (!LoadTGA(texture, filename))
    {
        return false;
    }
    glGenTextures(1, &texture->texID);				// Create The Texture ( CHANGE )
    glBindTexture(GL_TEXTURE_2D, texture->texID);
    glTexImage2D(GL_TEXTURE_2D, 0, texture->bpp / 8, texture->width, texture->height, 0, texture->type, GL_UNSIGNED_BYTE, texture->imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST_MIPMAP_LINEAR);
    if (texture->imageData)						// If Texture Image Exists ( CHANGE )
    {
        free(texture->imageData);					// Free The Texture Image Memory ( CHANGE )
    }
    return true;
}

