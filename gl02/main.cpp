//
//  main.c
//  gl02
//
//  Created by 鲁飞 on 15/8/7.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//
#include "LCommon.h"
#include "CCSprite.h"
#include "CCDirector.h"

void mouse(int button, int state, int x, int y){
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
        }
    }
    
}

void keyboard(unsigned char keyValue, int x, int y){
    switch (keyValue) {
        case 'q':
            printf("EXIT");
            exit(-1);
            break;
            
        default:
            break;
    }
}

void redraw(){}

// 空闲回调
void idleCallback(){
    static clock_t pre = clock();
    
//    t=0.1进行一次重绘
    if (clock() - pre > 0.1 * CLOCKS_PER_SEC) {
        pre = clock();
        
        // 绘制每帧场景
//        drawScene();
        CCDirector::sharedDirector()->mainLoop();
        glFlush();
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize (640, 480);
    glutInitWindowPosition (1000, 100);
    glutCreateWindow ("GLO2 2D Game Enginer");
    
    glEnable(GL_TEXTURE_2D);      // 启用纹理映射

    CCSprite *scene = CCSprite::create("/Users/lewis/Desktop/gl02/asset/Icon-72@2x.png");
    CCDirector::sharedDirector()->runWithScene(scene);

    glutDisplayFunc(redraw);
   
    glutIdleFunc(idleCallback);
    
    glutMouseFunc(mouse);
    
    glutKeyboardFunc(keyboard);
    
    glutMainLoop();
    
    return 0;
}
