//
//  MemUsage.h
//  OpenGL kurs
//
//  Created by Sergey Rump on 10.12.14.
//  Copyright (c) 2014 Sergey Rump. All rights reserved.
//

#ifndef OpenGL_kurs_MemUsage_h
#define OpenGL_kurs_MemUsage_h

#include <sys/time.h>
#include <sys/resource.h>

long getMemoryUsage()
{
    struct rusage usage;
    if(0 == getrusage(RUSAGE_SELF, &usage))
        return usage.ru_maxrss; // bytes
    else
        return 0;
}

#endif
