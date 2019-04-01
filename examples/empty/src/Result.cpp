//
//  Result.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/27.
//

#include "Result.hpp"

Result::Result(const InitData& init)
: IScene(init), mTextureCourt(U"texture/saibanjo.png"), mTextureCloud(U"texture/bg_aozora.png"),
mRectLoad(Vec2(0, 400), 1280, 320) {
    if (FileSystem::Exists(GameInfo::SaveFilePath))
    {
        Deserializer<BinaryReader>{GameInfo::SaveFilePath}(m_highScores);
    }
    else
    {
        Serializer<BinaryWriter>{GameInfo::SaveFilePath}(m_highScores);
    }
    
    if (m_highScores.back().score <= getData().lastScore)
    {
        m_highScores.back() = { getData().lastScore, Date::Today() };
        
        std::sort(m_highScores.begin(), m_highScores.end(), [](const ScoreData& a, const ScoreData& b)
                  {
                      return a.score > b.score ? true : a.score == b.score ? a.date > b.date : false;
                  });
        
        Serializer<BinaryWriter>{GameInfo::SaveFilePath}(m_highScores);
    }
}

void Result::update() {
    
    
    if ((MouseL | KeyEscape).down()) {
        changeScene(U"Title");
    }
}

void Result::draw() const {
    mTextureCloud.resized(1280, 400).draw();
    // mTextureCourt.resized(700, 400).draw(290, 20);
    mRectLoad.draw(Palette::Sandybrown);
    const double resultHeight = FontAsset(U"Result")(U"スコア：", getData().lastScore).region().h;
    
    FontAsset(U"Result")(U"スコア").draw(Window::Center().x - 100, Window::Height() * 0.4 - resultHeight / 2, Palette::Black);
    FontAsset(U"Result")(U":", getData().lastScore).draw(Window::Center().x + 200, Window::Height() * 0.4 - resultHeight / 2, Palette::Black);
    
    FontAsset(U"ResultSupplement")(U"(弁護士を会長と間違えた数").draw(Window::Center().x - 200, Window::Height() * 0.4 + resultHeight * 2, Palette::Red);
    FontAsset(U"ResultSupplement")(U":", getData().wrongGone, U")").draw(Window::Center().x + 200, Window::Height() * 0.4 + resultHeight * 2, Palette::Red);
    
    FontAsset(U"ResultSupplement")(U"(会長を弁護士と間違えた数").draw(Window::Center().x - 200, Window::Height() * 0.4 + resultHeight * 3, Palette::Red);
    FontAsset(U"ResultSupplement")(U":", getData().wrongLawer, U")").draw(Window::Center().x + 200, Window::Height() * 0.4 + resultHeight * 3, Palette::Red);
}
