//
//  CCDirector.hpp
//  gl02
//
//  Created by lewis on 16/4/17.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef CCDirector_hpp
#define CCDirector_hpp
#include "CCScene.h"
#include "CCSprite.h"
#include "CCScheduler.h"
#include "CCActionManager.h"
#include "GLView.h"

typedef enum {
    /// sets a 2D projection (orthogonal projection)
    kCCDirectorProjection2D,
    
    /// sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500.
    kCCDirectorProjection3D,//默认用这个
    
    /// it calls "updateProjection" on the projection delegate.
    kCCDirectorProjectionCustom,
    
    /// Default projection is 3D projection
    kCCDirectorProjectionDefault = kCCDirectorProjection3D,
} ccDirectorProjection;


class CCDirector {
public:
    //获得CCDirector实例
    static CCDirector* sharedDirector();
    
    //初始化函数
    virtual bool init(void);
    
    //循环入口
    void mainLoop();
    
    //绘制场景 每帧被调用
    void drawScene();
    
    void runWithScene(CCScene *pScene);
    
//    void setProjection(ccDirectorProjection kProjection);
    //设置观察与透视投影矩阵
    void setMVP();
    
    //设置视口变换矩阵
    void setViewport();

//    void setOpenGLView(CCEGLView *pobOpenGLView);
    //设置opengl视图
    void setOpenGLView(GLView *pobOpenGLView);
    
    /** sets the OpenGL default values */
    void setGLDefaultValues(void);
    
    CCSize m_obWinSizeInPoints;//设计窗口大小
    
    CCSize getWinSize(void);//返回窗口大小
   
    void calculateDeltaTime();
    
    CCActionManager* getActionManager();
private:
    CCScene *m_pRunningScene;
    
    CCScheduler *m_pScheduler;
    CCActionManager *m_pActionManager;
    
    float m_fDeltaTime;//帧间隔
    
    float m_fLastUpdateTime;
    
    bool m_bNextDeltaTimeZero;
    
    GLView *m_pobOpenGLView;
};

#endif /* CCDirector_hpp */
