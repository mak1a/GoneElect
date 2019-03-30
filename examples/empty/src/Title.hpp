//
//  Title.hpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/27.
//
#pragma once

#include"GameInfo.hpp"

///////////////////////////////////////////////////////////////////////
//
//  タイトル画面
//
class Title : public MyApp::Scene
{
private:
    
    Effect m_effect;
    
    Stopwatch m_effectBackgroundStopwatch{ true };
    
    Stopwatch m_effectMenuItemStopwatch{ true };
    
    Array<Rect> m_menuBoxes;
    
    Array<String> m_menuTexts =
    {
        GameInfo::MenuGameStart,
        GameInfo::MenuScore,
        GameInfo::MenuExit
    };
    
    Texture mTextureCourt, mTextureCloud;
    
    RectF mRectLoad;
public:
    
    Title(const InitData& init);
    
    void update() override;
    
    void draw() const override;
};
