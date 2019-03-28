//
//  Credit.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/28.
//

#include "Credit.hpp"

Credit::Credit(const InitData& init)
: IScene(init) {
    double y = 0;
    
    for (const auto& credit : GameInfo::Credits)
    {
        m_credits.emplace_back(credit.first, y, true);
        y += 70;
        
        for (const auto& name : credit.second)
        {
            m_credits.emplace_back(name, y, false);
            y += 60;
        }
        
        y += 60;
    }
    
    m_height = y;
}

void Credit::update() {
    if ((MouseL | KeyEscape).down())
    {
        changeScene(U"Title");
    }
    
    if ((m_height + yOffset()) < 0)
    {
        m_stopwatch.restart();
    }
}

void Credit::draw() const {
    const double offset = yOffset();
    
    for (const auto& credit : m_credits)
    {
        FontAsset(std::get<bool>(credit) ? U"CreditBig" : U"CreditSmall")(std::get<String>(credit))
        .drawAt(Window::Center().x, std::get<double>(credit) + offset);
    }
}
