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
    Texture mTextureCourt, mTextureLawer, mTextureGone, mTextureReporter, mTextureCloud, mTextureCar;
    
    static constexpr int32 gameTimeMillisec = 20 * 1000;
    
    Stopwatch m_countDownTimer;
    
    Stopwatch m_gameTimer;
    
    Array<Texture> mTextureHuman, flyingHumansTexture, ridingHumansTexture;
    Array<Vec3> flyingHumansPosition;
    Array<Vec2> ridingHumansPosition;
    
    int32 m_score = 0;
    
    BackgroundScape bgs;
    
    Texture generateTexture() const
    {
        bool randomSetTexture = RandomBool(0.3);
        
        if (randomSetTexture) {
            return Texture(mTextureGone);
        }
        
        return Texture(mTextureLawer);
    }
    
    bool onCountDown() const
    {
        return m_countDownTimer.isRunning() && m_countDownTimer < 4000ms;
    }
    
    bool onGame() const
    {
        return m_gameTimer.isRunning();
    }
    
    
public:
    
    Game(const InitData& init);
    
    void update() override;
    
    void draw() const override;
};
