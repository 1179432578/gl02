//
//  GLView.hpp
//  gl02
//
//  Created by 鲁飞 on 16/5/31.
//  Copyright © 2016年 鲁飞. All rights reserved.
//

#ifndef GLView_hpp
#define GLView_hpp

#include <stdio.h>
#include "CCGeometry.h"

/*opengl view 负责设置opengl view的大小 gl的一些默认值*/

enum ResolutionPolicy
{
    kResolutionExactFit,
    kResolutionNoBorder,
    kResolutionShowAll,
    kResolutionFixedHeight,
    kResolutionFixedWidth,
    
    kResolutionUnKnown,
};

class GLView{
public:
    GLView();
    ~GLView(){};
    
    static GLView* sharedOpenGLView();
    
//    virtual bool    isOpenGLReady() = 0;
//    virtual void    swapBuffers() = 0;
//    virtual void    setIMEKeyboardState(bool bOpen) = 0;
    
    virtual const CCSize& getFrameSize() const;
    virtual void setFrameSize(float width, float height);
    
    virtual CCSize getVisibleSize() const;
    virtual CCPoint getVisibleOrigin() const;
    

    virtual void setDesignResolutionSize(float width, float height, ResolutionPolicy resolutionPolicy);
    virtual const CCSize&  getDesignResolutionSize() const;
    
    //改变视口
    virtual void setViewPortInPoints(float x , float y , float w , float h);

//    virtual void setScissorInPoints(float x , float y , float w , float h);
//    virtual bool isScissorEnabled();
//    virtual CCRect getScissorRect();
    
    const CCRect& getViewPortRect() const;
    float getScaleX() const;
    float getScaleY() const;

protected:
    // real screen size
    CCSize m_obScreenSize;
    // resolution size, it is the size appropriate for the app resources.
    //设计大小:opengl世界坐标系xoy面中矩形大小,设计方案决定了视口变换
    CCSize m_obDesignResolutionSize;
    // the view port size
    CCRect m_obViewPortRect;
    // the view name
//    char   m_szViewName[50];
    
    float  m_fScaleX;
    float  m_fScaleY;
    ResolutionPolicy m_eResolutionPolicy;
};

#endif /* GLView_hpp */
