//
//  Title.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/27.
//

#include "Title.hpp"

Title::Title(const InitData& init)
    : IScene(init), mTextureCourt(U"texture/saibanjo.png"), mTextureCloud(U"texture/bg_aozora.png"),
      mRectLoad(Vec2(0, 400), 1280, 320)
{
    m_menuBoxes.resize(m_menuTexts.size());
    
    int32 boxWidth = 0;
    
    for (const auto& text : m_menuTexts)
    {
        boxWidth = Max(boxWidth, FontAsset(U"Menu")(text).region().w);
    }
    
    for (auto i : step(m_menuBoxes.size()))
    {
        m_menuBoxes[i].set(390, static_cast<int>(450 + i * 80), boxWidth + 180, 60);
    }
}

void Title::update() {
    bool handCursor = false;
    
    for (auto i : step(m_menuBoxes.size()))
    {
        const Quad item = m_menuBoxes[i].shearedX(20);
        
        handCursor |= item.mouseOver();
        
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
            else
            {
                System::Exit();
            }
            
            break;
        }
    }
    /*
    if (m_effectBackgroundStopwatch.elapsed() > 50ms)
    {
        m_effect.add<TitleBackGroundEffect>();
        
        m_effectBackgroundStopwatch.restart();
    }
    */
    Cursor::RequestStyle(handCursor ? CursorStyle::Hand : CursorStyle::Default);
}

void Title::draw() const {
    Window::Resize(1280, 720);
    Window::SetTitle(GameInfo::title);
    Graphics::SetBackground(GameInfo::BackgroundColor);
    System::SetExitEvent(WindowEvent::CloseButton);
    
    mTextureCloud.resized(1280, 400).draw();
    mTextureCourt.resized(700, 400).draw(290, 20);
    mRectLoad.draw(Palette::Sandybrown);
    
    Graphics2D::SetBlendState(BlendState::Default);
    
    const double titleHeight = FontAsset(U"Title")(GameInfo::title).region().h;
    
    FontAsset(U"Title")(GameInfo::title).drawAt(Window::Center().x, titleHeight, Palette::Black);
    
    for (auto i : step(m_menuBoxes.size()))
    {
        //m_menuBoxes[i].shearedX(20).draw();
        
        FontAsset(U"Menu")(m_menuTexts[i]).drawAt(m_menuBoxes[i].center(), Color(40));
    }
    
    const Size versionSize = FontAsset(U"Version")(GameInfo::version).region().size;
    
    FontAsset(U"Version")(GameInfo::version).drawAt(Window::Size().moveBy(-versionSize));
}
