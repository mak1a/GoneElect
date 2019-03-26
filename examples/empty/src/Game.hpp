//
//  Game.hpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/27.
//
#pragma once

#include"GameInfo.hpp"

///////////////////////////////////////////////////////////////////////
//
//  ゲーム
//
class Game : public MyApp::Scene
{
private:
    
public:
    
    Game(const InitData& init);
    
    void update() override;
    
    void draw() const override;
};
