//
//  Credit.hpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/28.
//

#pragma once
#include"GameInfo.hpp"

//////////////////////////////////////////////////////////////////////
//
//  スタッフクレジット
//
class Credit : public MyApp::Scene
{
private:
    
    Array<std::tuple<String, double, bool>> m_credits;
    
    double m_height = 0.0;
    
    Stopwatch m_stopwatch{ true };
    
    double yOffset() const
    {
        return Window::Height() + 60 - m_stopwatch.ms() / 20.0;
    }
    
public:
    
    Credit(const InitData& init);
    
    void update() override;
    
    void draw() const override;
};
