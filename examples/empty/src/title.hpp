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
//  タイトル画面の背景エフェクト
//
struct TitleBackGroundEffect : IEffect
{
    Line m_line;
    
    TitleBackGroundEffect();
    
    bool update(double timeSec);
};

///////////////////////////////////////////////////////////////////////
//
//  タイトル画面のメニュー選択時のエフェクト
//
struct MenuEffect : IEffect
{
    Rect m_rect;
    
    MenuEffect(const Rect& rect)
    : m_rect(rect) {}
    
    bool update(double timeSec);
};

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
        GameInfo::MenuCredit,
        GameInfo::MenuWebURL,
        GameInfo::MenuExit
    };
    
public:
    
    Title(const InitData& init);
    
    void update() override;
    
    void draw() const override;
};
