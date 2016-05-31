//
//  CCDirector.cpp
//  gl02
//
//  Created by lewis on 16/4/17.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#include "CCDirector.h"
#include "LCommon.h"
#include "matrix_transform.h"
#include "mglMatrix.h"
#include <math.h>



 static CCDirector *s_SharedDirector = NULL;

//获得CCDirector实例
CCDirector* CCDirector::sharedDirector(){
    if (!s_SharedDirector) {
        s_SharedDirector = new CCDirector();
        s_SharedDirector->init();
    }
    
    return s_SharedDirector;
}

bool CCDirector::init(void){
//    setDefaultValues();
    
    // scenes
    m_pRunningScene = NULL;
//    m_pNextScene = NULL;
//    
//    m_pNotificationNode = NULL;
    
    // FPS
//    m_fAccumDt = 0.0f;
//    m_fFrameRate = 0.0f;
//    m_pFPSLabel = NULL;
//    m_pSPFLabel = NULL;
//    m_pDrawsLabel = NULL;
//    m_uTotalFrames = m_uFrames = 0;
//    m_pszFPS = new char[10];
    m_fLastUpdateTime = 1.0f * clock() / CLOCKS_PER_SEC;
    m_bNextDeltaTimeZero = false;
    
    // paused ?
//    m_bPaused = false;
    
    m_obWinSizeInPoints = CCSizeZero;
    
    // scheduler
    m_pScheduler = new CCScheduler();
    // action manager
    m_pActionManager = new CCActionManager();
//    m_pScheduler->scheduleUpdateForTarget(m_pActionManager, INT32_MIN, false);//优先级越小，越先处理
    m_pScheduler->scheduleUpdateForTarget(m_pActionManager, 0, false);//优先级越小，越先处理
    
    
    return true;
}

//循环入口
void CCDirector::mainLoop(){
    //如果游戏结束就退出
    
    //游戏没有退出就绘制场景
    drawScene();
}

//绘制场景 每帧被调用
void CCDirector::drawScene(){
    //    calculate global delta time m_fDeltaTime
    calculateDeltaTime();
    
    //执行调度，更新每个节点注册的调度动作 CCMoveTo CCScaleTo and so on
    m_pScheduler->update(m_fDeltaTime);
    
    //clear buffers to preset values
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //    如果有要进入下个场景  就设置当前场景为下个场景 nice
    //    if (m_pNextScene)
    //    {
    //        setNextScene();
    //    }
    
    //draw the scene
    if (m_pRunningScene)
    {
        m_pRunningScene->visit();
    }

    //
    //    // draw the notifications node
    //    Useful to hook a notification node
    //    通知节点 游戏只有一个此节点 在最后渲染 所以渲染跟zorder无关的(需要注意)
    //    if (m_pNotificationNode)
    //    {
    //        m_pNotificationNode->visit();
    //    }
    
    //    显示FPS(frame rate) SPF(每帧秒数) numberOfDraws
    //    if (m_bDisplayStats)
    //    {
    //        showStats();
    //    }
    
    
    //    // swap buffers
    //    if (m_pobOpenGLView)
    //    {
    //        m_pobOpenGLView->swapBuffers();
    //    }
    //
    
    //    计算MPF
    //    if (m_bDisplayStats)
    //    {
    //        calculateMPF();
    //    }
}

void CCDirector::runWithScene(CCScene *pScene){
    m_pRunningScene = pScene;
}

void CCDirector::setOpenGLView(GLView *pobOpenGLView){
    m_pobOpenGLView = pobOpenGLView;
    
    //设置设计窗口大小
    m_obWinSizeInPoints = m_pobOpenGLView->getDesignResolutionSize();
    
//    createStatsLabel();

    setGLDefaultValues();

//    CHECK_GL_ERROR_DEBUG();
//    m_pobOpenGLView->setTouchDelegate(m_pTouchDispatcher);
//    m_pTouchDispatcher->setDispatchEvents(true);
}

void CCDirector::setGLDefaultValues()
{
    // This method SHOULD be called only after openGLView_ was initialized
//    CCAssert(m_pobOpenGLView, "opengl view should not be null");
    
//    setAlphaBlending(true);
    // XXX: Fix me, should enable/disable depth test according the depth format as cocos2d-iphone did
    // [self setDepthTest: view_.depthFormat];
//    setDepthTest(false);
//    setProjection(m_eProjection);
    setMVP();
    
    // set other opengl default values
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

//设置视图与透视投影矩阵
void CCDirector::setMVP(){
    setViewport();
    
    CCSize size = m_obWinSizeInPoints;
    
    //获得眼睛位置
    //float zeye = this->getZEye();
    float zeye = m_obWinSizeInPoints.height / 1.1566f;
//    float zeye = 480.0f / 1.1566f;//算出来是1.1547 不知道哪里算错了
    
    Matrix44 matrixPerspective, matrixLookup;
    
    //设置当前矩阵为投影矩阵，对投影矩阵进行操作
    mglMatrixMode(KM_GL_PROJECTION);
    mglLoadIdentity();
//    matrixPerspective = mgluPerspective(60.0f/180.0f*M_PI, 640/480.0f, 0.1f, 2*zeye);
    matrixPerspective = mgluPerspective(60.0f/180.0f*M_PI, size.width/size.height, 0.1f, 2*zeye);
    mglMultMatrix(&matrixPerspective);
    
    //设置观察矩阵
    mglMatrixMode(KM_GL_MODELVIEW);
    mglLoadIdentity();
//    matrixLookup = mglLookAt(640.0f/2, 480.0f/2, zeye, 640.0f/2, 480.0f/2, 0.0f, 0, 1, 0.0f);
    matrixLookup = mglLookAt(size.width/2, size.height/2, zeye, size.width/2, size.height/2, 0.0f, 0.0f, 1.0f, 0.0f);
    mglMultMatrix(&matrixLookup);

}

//设置视口变换矩阵
void CCDirector::setViewport(){
    if (m_pobOpenGLView)
    {
        m_pobOpenGLView->setViewPortInPoints(0, 0, m_obWinSizeInPoints.width, m_obWinSizeInPoints.height);
    }

}

CCSize CCDirector::getWinSize(void)
{
    return m_obWinSizeInPoints;
}

void CCDirector::calculateDeltaTime(void)
{
    float currentTime = 1.0f * clock() / CLOCKS_PER_SEC;
    m_fDeltaTime = currentTime - m_fLastUpdateTime;
    m_fLastUpdateTime = currentTime;
    
    if (m_bNextDeltaTimeZero) {
        m_fDeltaTime = 0.0f;
        m_bNextDeltaTimeZero = false;
    }
}

CCActionManager* CCDirector::getActionManager()
{
    return m_pActionManager;
}