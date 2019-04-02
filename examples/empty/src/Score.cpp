//
//  Score.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/28.
//

#include "Score.hpp"
Score::Score(const InitData& init)
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
}

void Score::update() {
    if ((MouseL | KeyEscape).down())
    {
        changeScene(U"Title");
    }
}

void Score::draw() const {
    const int32 h = FontAsset(U"ScoreList").height();
    
    mTextureCloud.resized(1280, 400).draw();
    // mTextureCourt.resized(700, 400).draw(290, 20);
    mRectLoad.draw(Palette::Sandybrown);
    
    for (auto i : step(m_highScores.size()))
    {
        const Rect rect = Rect(520, 100).setCenter(Window::Center().x + 100, static_cast<int>(120 + i * 120));
        
        rect.draw(ColorF(1.0, 0.2));
        
        FontAsset(U"ScoreList")(i + 1, U"位").draw(252, rect.pos.y + (rect.h - h) / 2 + 2, Palette::Gray);
        FontAsset(U"ScoreList")(i + 1, U"位").draw(250, rect.pos.y + (rect.h - h) / 2, Palette::Black);
        
        FontAsset(U"ScoreList")(m_highScores[i].score)
        .draw(rect.pos + Point(42, (rect.h - h) / 2 + 2), Palette::Gray);
        
        FontAsset(U"ScoreList")(m_highScores[i].score)
        .draw(rect.pos + Point(40, (rect.h - h) / 2), Palette::Black);
        
        const Size dateSize = FontAsset(U"ScoreListDate")(m_highScores[i].date).region().size;
        
        FontAsset(U"ScoreListDate")(m_highScores[i].date)
        .draw(rect.br().x - dateSize.x - 40, rect.center().y - dateSize.y / 2, Palette::Black);
    }
}
