//
//  world window and screen view.h
//  gl02
//
//  Created by 鲁飞 on 15/8/7.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#ifndef __gl02__world_window_and_screen_view__
#define __gl02__world_window_and_screen_view__

#include "LPoint2f.h"

class WindowToView
{
public:
    void setWorldWindow(float left, float right, float top, float bottom);
    void setScreenView(float left, float right, float top, float bottom);
    LPoint2f convertWindowToView(LPoint2f point);
    void createWindowToView();
private:
    float m_A;
    float m_B;
    float m_C;
    float m_D;
    Rect4f m_window;
    Rect4f m_view;
};

#endif /* defined(__gl02__world_window_and_screen_view__) */
