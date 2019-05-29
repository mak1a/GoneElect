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
    Array<Rect> m_MenuBoxes;
    
    Array<String> m_MenuTexts =
    {
        GameInfo::MenuGameStart,
        GameInfo::MenuScore,
        GameInfo::MenuExit
    };
    
    Texture m_tCourt, m_tCloud;
    
    RectF m_rLoad;
public:
    
    Title(const InitData& init);
    
    void update() override;
    
    void draw() const override;
};
