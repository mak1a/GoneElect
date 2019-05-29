//
//  Game.hpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/27.
//
#pragma once

#include"GameInfo.hpp"
#include"BackgroundScape.hpp"

///////////////////////////////////////////////////////////////////////
//
//  ゲーム
//
class Game : public MyApp::Scene
{
private:
    Texture m_tCourt, m_tLawer, m_tGone, m_tReporter, m_tCloud, m_tCar;
    
    static constexpr int32 gameTimeMillisec = 20 * 1000;
    
    Stopwatch m_sCountDownTimer;
    
    Stopwatch m_sGameTimer;
    
    Array<Texture> m_TextureHuman, m_TextureFlyingHuman, m_TextureRidingHuman;
    Array<Vec3> m_FlyingHumanPos;
    Array<Vec2> m_RidingHumanPos;
    
    int32 m_iScore = 0;
    int32 m_iScoreWrongGone = 0;
    int32 m_iScoreWrongLawer = 0;
    
    BackgroundScape m_BackGroundScape;
    
    Texture generateTexture() const
    {
        bool randomSetTexture = RandomBool(0.3);
        
        if (randomSetTexture) {
            return Texture(m_tGone);
        }
        
        return Texture(m_tLawer);
    }
    
    bool onCountDown() const
    {
        return m_sCountDownTimer.isRunning() && m_sCountDownTimer < 4000ms;
    }
    
    bool onGame() const
    {
        return m_sGameTimer.isRunning();
    }
    
    
public:
    
    Game(const InitData& init);
    
    void update() override;
    
    void draw() const override;
};
