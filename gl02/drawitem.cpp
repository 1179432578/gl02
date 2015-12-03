//
//  drawitem.cpp
//  gl02
//
//  Created by 鲁飞 on 15/8/13.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#include "drawitem.h"

#define RANDOM() (float)(random()%255) / 255.0f
LPolygen* drawHouse(){
    LPoint2f house[] = {PT(0, 4),PT(1, 3),PT(1, 0),PT(-1, 0),PT(-1, 3)};
    LDeviceContext dc;
    dc.moveTo(house[0]);
    for (int i=1; i<=4; i++) {
        dc.lineTo(house[i]);
    }
    dc.lineTo(house[0]);
    
    LPoint2f *ret = new LPoint2f[sizeof(house)/sizeof(LPoint2f)];
    memcpy(ret, house, sizeof(house));
    LPolygen *polygen = new LPolygen();
    polygen->pts = ret;
    polygen->n = sizeof(house)/sizeof(LPoint2f);
    return polygen;
}

void drawCoordinateSystem(){
   // glPointSize(20.0f);
    LDeviceContext dc;
    // x axis
    dc.moveTo(PT(-10, 0));
    dc.lineTo(PT(10, 0));
    dc.moveTo(PT(9.9, 0.1));
    dc.lineTo(PT(10, 0));
    dc.moveTo(PT(9.9, -0.1));
    dc.lineTo(PT(10, 0));
    for (int i=-10; i<=9; i++) {
        dc.moveTo(PT(i, 0.2));
        dc.lineTo(PT(i, 0));
    }
    
    // y axis
    dc.moveTo(PT(0, -10));
    dc.lineTo(PT(0, 10));
    dc.moveTo(PT(0.1, 9.9));
    dc.lineTo(PT(0, 10));
    dc.moveTo(PT(-0.1, 9.9));
    dc.lineTo(PT(0, 10));
    for (int i=-10; i<=9; i++) {
        dc.moveTo(PT(0.2, i));
        dc.lineTo(PT(0, i));
    }
   // glPointSize(2.0f);
}

void drawPolygen(LPolygen *polygen){
    LDeviceContext dc;
    dc.moveTo(polygen->pts[0]);
    for (int i=1; i<polygen->n; i++) {
        dc.lineTo(polygen->pts[i]);
    }
    dc.lineTo(polygen->pts[0]);
}

void drawCircleCorlorPane(){
    LDeviceContext dc;
    float z;
    for (float x=-2.0f; x<=2.0f; x+=0.05) {
        for (float y=-2.0f; y<=2.0f; y+=0.05) {
            if (x*x+y*y<=4.0f) {
                z = lmath.sqrt(x*x+y*y);
                glColor3f((x+2.0f)/4.0f*1.0f, (y+2.0f)/4.0f*1.0f,
                          z/2.0f*1.0f);
                dc.pixel(LPoint2f(x, y));
            }
        }
    }
}














