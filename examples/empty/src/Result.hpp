//
//  Result.hpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/27.
//
#pragma once

#include"GameInfo.hpp"

///////////////////////////////////////////////////////////////////////
//
//  結果画面
//
class Result : public MyApp::Scene
{
private:
    
public:
    
    Result(const InitData& init);
    
    void update() override;
    
    void draw() const override;
};
