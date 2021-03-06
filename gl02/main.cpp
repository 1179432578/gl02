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
#include <unistd.h>
#include "CCAction.h"
#include "CCActionInterval.h"
#include "GLView.h"

void mouse(int button, int state, int x, int y){
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
        }
    }
    
}

void keyboard(unsigned char keyValue, int x, int y){
    switch (keyValue) {
        case 'q':
            printf("EXIT\n");
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
    
    //每帧间隔t=0.016进行一次重绘
    if (clock() - pre > 0.016 * CLOCKS_PER_SEC) {
        pre = clock();
        
        // 主循环，场景每帧的调用由mainLoop检查，若游戏没结束，就会调用drawScene
        CCDirector::sharedDirector()->mainLoop();
        glFlush();
    }
}


int main(int argc, const char * argv[]) {
//    kResolutionNoBorder,
//    kResolutionShowAll,
//    kResolutionFixedHeight,
//    kResolutionFixedWidth,
    GLView::sharedOpenGLView()->setFrameSize(1024, 768);
    GLView::sharedOpenGLView()->setDesignResolutionSize(1024, 768, kResolutionShowAll);
    CCDirector::sharedDirector()->setOpenGLView(GLView::sharedOpenGLView());
    
    CCScene *scene = CCScene::create();
    CCSprite *c1 = CCSprite::create("Resources/asset/Icon-72@2x.png");
    CCAction *action = CCMoveBy::create(10, ccp(700, 500));
    c1->runAction(action);
    scene->addChild(c1, 20, 0);
    c1->setPosition(ccp(100, 200));
    c1->setScale(2);
    c1->setRotation(-30);

    CCSprite *c2 = CCSprite::create("Resources/asset/9.png");
    scene->addChild(c2, 10, 10);
    c2->setPosition(ccp(340, 240));
    CCAction *action2 = CCMoveBy::create(10, ccp(-200, -500));
    c2->runAction(action2);

    
    CCDirector::sharedDirector()->runWithScene(scene);
    //窗口重绘函数，这里直接提供了一个空函数。创建窗口后、改变窗口大小都会触发重绘。重绘函数为空函数会导致出现白色窗口，
    //我们可以指定绘制一张背景图来消除这个问题。
    glutDisplayFunc(redraw);
    
    //空闲回调，程序空闲时就会调用idleCallback函数，它会进行游戏循环
    glutIdleFunc(idleCallback);
    
    //指定鼠标回调
    glutMouseFunc(mouse);
    
    //指定键盘回调
    glutKeyboardFunc(keyboard);
    
    char path[1024];
    
    getcwd(path, sizeof(path));
    printf("cwd: %s\n", path);
    
    //开启opengl事件循环，如果不调用，程序就会直接结束了
    glutMainLoop();
    
    return 0;
}
