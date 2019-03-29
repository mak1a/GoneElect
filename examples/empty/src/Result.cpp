//
//  Result.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/27.
//

#include "Result.hpp"

Result::Result(const InitData& init)
: IScene(init) {
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
    const double resultHeight = FontAsset(U"Result")(U"x", getData().lastScore).region().h;
    
    FontAsset(U"Result")(U"x", getData().lastScore).draw(Window::Center().x + 50, Window::Height() * 0.4 - resultHeight / 2, Palette::Black);
}
