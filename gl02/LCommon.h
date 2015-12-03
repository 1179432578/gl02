//
//  LGUI.h
//  gl02
//
//  Created by 鲁飞 on 15/8/10.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#ifndef gl02_LGUI_h
#define gl02_LGUI_h

// opengl
#include "GLUT/glut.h"


// c
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>


// L
#include "world window and screen view.h"
#include "LDeviceContext.h"
#include "LPoint2f.h"
#include "LMatrix.h"
#include "cyrus-beck.h"
#include "LMath.h"
#include "LTool.h"
#include "LScene.h"
#include "LMesh.h"

// 
#define PT(a,b) LPoint2f((float)a,(float)b)
#define LMATRIX3X3(m11, m12, m13, m21, m22, m23) \
        LMatrix3x3((float)m11,(float)m12,(float)m13, \
                (float)m21,(float)m22,(float)m23)

#endif
