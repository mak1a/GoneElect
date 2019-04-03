//
//  Game.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/27.
//

#include "Game.hpp"

Game::Game(const InitData& init)
    : IScene(init), mTextureCourt(Resource(U"texture/saibanjo.png")), mTextureLawer(Resource(U"texture/stand_sagyouin_man.png")),
      mTextureGone(Resource(U"texture/stand_sagyouin_gone.png")), mTextureReporter(Resource(U"texture/job_shinbun_kisya.png")),
      mTextureCloud(Resource(U"texture/bg_aozora.png")), mTextureCar(Resource(U"texture/car_side.png")),
    bgs(mTextureCourt, mTextureReporter, mTextureCloud, mTextureCar) {
    getData().lastScore = 0;
}

void Game::update() {
    if (!onGame() && !m_countDownTimer.isRunning())
    {
        m_countDownTimer.start();
    }
    
    if (!onGame() && m_countDownTimer >= 3000ms)
    {
        m_gameTimer.start();
        
        for (size_t i = 0; i < 5; i++) {
            mTextureHuman.emplace_back(generateTexture());
        }
    }
    
    if (!onGame())
    {
        return;
    }
    
    if (m_gameTimer.ms() >= gameTimeMillisec)
    {
        getData().lastScore = mScore;
        getData().wrongGone = mScoreWrongGone;
        getData().wrongLawer = mScoreWrongLawer;
        
        changeScene(U"Result", 2000);
    }
    
    if (KeyG.down()) {
        if (mTextureHuman[4] == mTextureGone){
            ++mScore;
        }
        else {
            mScoreWrongGone++;
            --mScore;
        }
        
        flyingHumansPosition.emplace_back(Window::Center().moveBy(25, 25), 0);
        flyingHumansTexture.emplace_back(mTextureHuman[4]);
        mTextureHuman.pop_back();
        mTextureHuman.push_front(generateTexture());
        
    }
    else if (KeyL.down()) {
        if (mTextureHuman[4] == mTextureLawer){
            ++mScore;
        }
        else {
            mScoreWrongLawer++;
            --mScore;
        }
        
        ridingHumansPosition.emplace_back(Window::Center().moveBy(25, 25));
        ridingHumansTexture.emplace_back(mTextureHuman[4]);
        mTextureHuman.pop_back();
        mTextureHuman.push_front(generateTexture());
        
    }
    
    for (size_t i = 0; i < flyingHumansPosition.size(); i++) {
        flyingHumansPosition[i].y -= 20;
        flyingHumansPosition[i].z += 10;
        
        if (flyingHumansPosition[i].y < -100) {
            flyingHumansTexture.remove_at(i);
            flyingHumansPosition.remove_at(i);
        }
    }
    
    for (size_t i = 0; i < ridingHumansPosition.size(); i++) {
        ridingHumansPosition[i].x += 50;
        
        if (ridingHumansPosition[i].x > 1400) {
            ridingHumansTexture.remove_at(i);
            ridingHumansPosition.remove_at(i);
        }
    }
    
    if ((MouseL | KeyEscape).down()) {
        changeScene(U"Result");
    }
}

void Game::draw() const {
    bgs.draw();
    
    if (onCountDown())
    {
        const int32 timeMillisec = Max((3999 - m_countDownTimer.ms()), 0);
        const int32 countDown = timeMillisec / 1000;
        const double e = EaseIn(Easing::Expo, (timeMillisec % 1000) / 1000.0);
        
        if (countDown > 0)
        {
            Transformer2D t(Mat3x2::Scale(1.0 + e * 2, Window::Center()));
            FontAsset(U"CountDown")(countDown).drawAt(Window::Center());
        }
        else
        {
            Transformer2D t(Mat3x2::Scale(1.0 + (1.0 - e) * 2, Window::Center()));
            FontAsset(U"CountDown")(U"START").drawAt(Window::Center(), AlphaF(e));
        }
    }
    
    if (!onGame())
    {
        return;
    }
    
    for(size_t i = 0; i < mTextureHuman.size(); i++) {
        mTextureHuman[i].scaled(0.7)
        .drawAt(Window::Center().moveBy(static_cast<int>(i * 5), static_cast<int>(i * 5)));
    }
    
    for (size_t i = 0; i < flyingHumansPosition.size(); i++) {
        flyingHumansTexture[i].scaled(0.7)
        .rotated(ToRadians(flyingHumansPosition[i].z))
        .drawAt(flyingHumansPosition[i].xy());
    }
    
    for (size_t i = 0; i < ridingHumansPosition.size(); i++) {
        ridingHumansTexture[i].scaled(0.7)
        .drawAt(ridingHumansPosition[i].xy());
    }
    
    const int32 timeLeftMillisec = Max(gameTimeMillisec - m_gameTimer.ms(), 0);
    
    FontAsset(U"GameTime")(U"TIME: {:0>2}'{:0>2}"_fmt(timeLeftMillisec / 1000, timeLeftMillisec % 1000 / 10)).draw(60, 60, Palette::Black);
}
