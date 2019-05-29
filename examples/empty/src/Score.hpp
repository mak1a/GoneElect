//
//  Score.hpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/28.
//

#pragma once
#include"GameInfo.hpp"

///////////////////////////////////////////////////////////////////////
//
//  ハイスコア一覧
//
class Score : public MyApp::Scene
{
private:
    
    std::array<ScoreData, 5> m_highScores = defaultHighScores;
    
    Texture m_tCourt, m_tCloud;
    
    RectF m_rLoad;
    
public:
    
    Score(const InitData& init);
    
    void update() override;
    
    void draw() const override;
};
