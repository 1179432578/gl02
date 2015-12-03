//
//  world window and screen view.cpp
//  gl02
//
//  Created by 鲁飞 on 15/8/7.
//  Copyright (c) 2015年 鲁飞. All rights reserved.
//

#include "world window and screen view.h"

void WindowToView::setWorldWindow(float left, float right, float bottom, float top)
{
    m_window.left = left;
    m_window.right = right;
    m_window.bottom = bottom;
    m_window.top = top;
}

void WindowToView::setScreenView(float left, float right, float bottom, float top)
{
    m_view.left = left;
    m_view.right = right;
    m_view.bottom = bottom;
    m_view.top = top;
}

LPoint2f WindowToView::convertWindowToView(LPoint2f point)
{
    return LPoint2f(m_A*point.x+m_B, m_C*point.y+m_D);
}

void WindowToView::createWindowToView()
{
    m_A = (m_view.right - m_view.left) / (m_window.right - m_window.left);
    m_B = m_view.left - (m_view.right - m_view.left) /
        (m_window.right - m_window.left) *  m_window.left;
    m_C = (m_view.top - m_view.bottom) / (m_window.top - m_window.bottom);
    m_D = m_view.bottom - (m_view.top - m_view.bottom) /
        (m_window.top - m_window.bottom) * m_window.bottom;
}


