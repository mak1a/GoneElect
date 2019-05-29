//
//  Game.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/27.
//

#include "Game.hpp"


/**
 ゲームクラスの引数付きコンストラクタ

 @param init シーン遷移用の引数
 */
Game::Game(const InitData& init)
    : IScene(init), m_tCourt(Resource(U"texture/saibanjo.png")), m_tLawer(Resource(U"texture/stand_sagyouin_man.png")),
      m_tGone(Resource(U"texture/stand_sagyouin_gone.png")), m_tReporter(Resource(U"texture/job_shinbun_kisya.png")),
      m_tCloud(Resource(U"texture/bg_aozora.png")), m_tCar(Resource(U"texture/car_side.png")),
    m_BackGroundScape(m_tCourt, m_tReporter, m_tCloud, m_tCar) {
    getData().lastScore = 0;
}


/**
 毎フレーム呼び出される関数
 */
void Game::update() {
    // ゲームスタートとカウントダウンをしていない場合カウントダウンを始める
    if (!onGame() && !m_sCountDownTimer.isRunning())
    {
        m_sCountDownTimer.start();
    }
    
    // ゲームスタートをしていなくて、カウントダウン3秒過ぎたらゲームスタート
    if (!onGame() && m_sCountDownTimer >= 3000ms)
    {
        m_sGameTimer.start();
        for (size_t i = 0; i < 5; i++) {
            m_TextureHuman.emplace_back(generateTexture());
        }
    }
    
    if (!onGame())
    {
        return;
    }
    
    // ゲーム終了後、
    if (m_sGameTimer.ms() >= gameTimeMillisec)
    {
        getData().lastScore = m_iScore;
        getData().wrongGone = m_iScoreWrongGone;
        getData().wrongLawer = m_iScoreWrongLawer;
        
        changeScene(U"Result", 2000);
    }
    
    // Gボタンを押したら人間を空に飛ばす
    if (KeyG.down()) {
        if (m_TextureHuman[4] == m_tGone){
            ++m_iScore;
        }
        else {
            ++m_iScoreWrongGone;
            --m_iScore;
        }
        
        m_FlyingHumanPos.emplace_back(Window::Center().moveBy(25, 25), 0);
        m_TextureFlyingHuman.emplace_back(m_TextureHuman[4]);
        m_TextureHuman.pop_back();
        m_TextureHuman.push_front(generateTexture());
        
    }
    // Lボタンを押したら人を車に乗せる
    else if (KeyL.down()) {
        if (m_TextureHuman[4] == m_tLawer){
            ++m_iScore;
        }
        else {
            m_iScoreWrongLawer++;
            --m_iScore;
        }
        
        m_RidingHumanPos.emplace_back(Window::Center().moveBy(25, 25));
        m_TextureRidingHuman.emplace_back(m_TextureHuman[4]);
        m_TextureHuman.pop_back();
        m_TextureHuman.push_front(generateTexture());
        
    }
    // 人間を空に飛ばす処理
    for (size_t i = 0; i < m_FlyingHumanPos.size(); i++) {
        m_FlyingHumanPos[i].y -= 20;
        m_FlyingHumanPos[i].z += 10;
        
        if (m_FlyingHumanPos[i].y < -100) {
            m_TextureFlyingHuman.remove_at(i);
            m_FlyingHumanPos.remove_at(i);
        }
    }
    // 人間を車に乗せる処理
    for (size_t i = 0; i < m_RidingHumanPos.size(); i++) {
        m_RidingHumanPos[i].x += 50;
        
        if (m_RidingHumanPos[i].x > 1400) {
            m_TextureRidingHuman.remove_at(i);
            m_RidingHumanPos.remove_at(i);
        }
    }
    
    if ((MouseL | KeyEscape).down()) {
        changeScene(U"Result");
    }
}

void Game::draw() const {
    m_BackGroundScape.draw();
    
    if (onCountDown())
    {
        const int32 timeMillisec = Max((3999 - m_sCountDownTimer.ms()), 0);
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
    
    for(size_t i = 0; i < m_TextureHuman.size(); i++) {
        m_TextureHuman[i].scaled(0.7)
        .drawAt(Window::Center().moveBy(static_cast<int>(i * 5), static_cast<int>(i * 5)));
    }
    
    for (size_t i = 0; i < m_FlyingHumanPos.size(); i++) {
        m_TextureFlyingHuman[i].scaled(0.7)
        .rotated(ToRadians(m_FlyingHumanPos[i].z))
        .drawAt(m_FlyingHumanPos[i].xy());
    }
    
    for (size_t i = 0; i < m_RidingHumanPos.size(); i++) {
        m_TextureRidingHuman[i].scaled(0.7)
        .drawAt(m_RidingHumanPos[i].xy());
    }
    
    const int32 timeLeftMillisec = Max(gameTimeMillisec - m_sGameTimer.ms(), 0);
    
    FontAsset(U"GameTime")(U"TIME: {:0>2}'{:0>2}"_fmt(timeLeftMillisec / 1000, timeLeftMillisec % 1000 / 10)).draw(60, 60, Palette::Black);
}
