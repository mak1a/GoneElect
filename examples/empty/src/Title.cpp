//
//  Title.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/27.
//

#include "title.hpp"

TitleBackGroundEffect::TitleBackGroundEffect() {
    const Vec2 pos = RandomVec2(Window::ClientRect());
    const Vec2 direction = Circular(Window::Width() + Window::Height(), Random(360_deg));
    m_line.set(pos - direction, pos + direction);
}

bool TitleBackGroundEffect::update(double timeSec) {
    m_line.draw(2, AlphaF((1.0 - Abs(timeSec - 1.0)) * 0.3));
    return timeSec < 2.0;
}

bool MenuEffect::update(double timeSec) {
    const double e = EaseOut(Easing::Quad, timeSec);
    RectF(m_rect).stretched(e * 20).shearedX(20).draw(AlphaF((1.0 - e) * 0.4));
    return timeSec < 1.0;
}

Title::Title(const InitData& init)
    : IScene(init)
{
    if (!GameInfo::WebURL)
    {
        m_menuTexts.erase(m_menuTexts.begin() + 3);
    }
    
    m_menuBoxes.resize(m_menuTexts.size());
    
    int32 boxWidth = 0;
    
    for (const auto& text : m_menuTexts)
    {
        boxWidth = Max(boxWidth, FontAsset(U"Menu")(text).region().w);
    }
    
    for (auto i : step(m_menuBoxes.size()))
    {
        m_menuBoxes[i].set(240, 280 + i * 80, boxWidth + 80, 60);
    }
}

void Title::update() {
    bool handCursor = false;
    
    for (auto i : step(m_menuBoxes.size()))
    {
        const Quad item = m_menuBoxes[i].shearedX(20);
        
        handCursor |= item.mouseOver();
        
        if (item.mouseOver() && m_effectMenuItemStopwatch > 300ms)
        {
            m_effect.add<MenuEffect>(m_menuBoxes[i]);
            
            m_effectMenuItemStopwatch.restart();
        }
        
        if (item.leftClicked())
        {
            if (i == 0)
            {
                changeScene(U"Game");
            }
            else if (i == 1)
            {
                changeScene(U"Score");
            }
            else if (i == 2)
            {
                changeScene(U"Credit");
            }
            else if (GameInfo::WebURL && i == 3)
            {
                System::LaunchBrowser(GameInfo::WebURL);
            }
            else
            {
                System::Exit();
            }
            
            break;
        }
    }
    
    if (m_effectBackgroundStopwatch.elapsed() > 50ms)
    {
        m_effect.add<TitleBackGroundEffect>();
        
        m_effectBackgroundStopwatch.restart();
    }
    
    Cursor::RequestStyle(handCursor ? CursorStyle::Hand : CursorStyle::Default);
}

void Title::draw() const {
    Graphics2D::SetBlendState(BlendState::Additive);
    
    m_effect.update();
    
    Graphics2D::SetBlendState(BlendState::Default);
    
    const double titleHeight = FontAsset(U"Title")(GameInfo::title).region().h;
    
    FontAsset(U"Title")(GameInfo::title).drawAt(Window::Center().x, titleHeight);
    
    for (auto i : step(m_menuBoxes.size()))
    {
        m_menuBoxes[i].shearedX(20).draw();
        
        FontAsset(U"Menu")(m_menuTexts[i]).drawAt(m_menuBoxes[i].center(), Color(40));
    }
    
    const Size versionSize = FontAsset(U"Version")(GameInfo::version).region().size;
    
    FontAsset(U"Version")(GameInfo::version).drawAt(Window::Size().moveBy(-versionSize));
}
