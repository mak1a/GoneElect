//
//  Score.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/28.
//

#include "Score.hpp"
Score::Score(const InitData& init)
: IScene(init) {
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
    
    for (auto i : step(m_highScores.size()))
    {
        const Rect rect = Rect(520, 100).setCenter(Window::Center().x, static_cast<int>(120 + i * 120));
        
        rect.draw(ColorF(1.0, 0.2));
        
        FontAsset(U"ScoreList")(m_highScores[i].score)
        .draw(rect.pos + Point(42, (rect.h - h) / 2 + 2), Palette::Gray);
        
        FontAsset(U"ScoreList")(m_highScores[i].score)
        .draw(rect.pos + Point(40, (rect.h - h) / 2));
        
        const Size dateSize = FontAsset(U"ScoreListDate")(m_highScores[i].date).region().size;
        
        FontAsset(U"ScoreListDate")(m_highScores[i].date)
        .draw(rect.br().x - dateSize.x - 40, rect.center().y - dateSize.y / 2);
        
        for (auto k : step(5 - i))
        {
            const Point left(rect.center().movedBy(-rect.w / 2 - 40 - k * 50, 0).asPoint());
            const Point right(rect.center().movedBy(rect.w / 2 + 40 + k * 50, 0).asPoint());
            
            Rect(40).setCenter(left).rotated(45_deg).draw(AlphaF(1.0 - i * 0.1));
            Rect(40).setCenter(right).rotated(45_deg).draw(AlphaF(1.0 - i * 0.1));
        }
    }
}
