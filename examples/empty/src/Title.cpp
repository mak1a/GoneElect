//
//  Title.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/27.
//

#include "Title.hpp"


/**
 タイトルクラスのこ引数付きコンストラクタ

 @param init シーン遷移用の引数
 */
Title::Title(const InitData& init)
    : IScene(init), m_tCourt(Resource(U"texture/saibanjo.png")), m_tCloud(Resource(U"texture/bg_aozora.png")),
      m_rLoad(Vec2(0, 400), 1280, 320) {
    m_MenuBoxes.resize(m_MenuTexts.size());
    
    int32 boxWidth = 0;
    
    // メニューボックスの最大の幅を取得する
    for (const auto& text : m_MenuTexts)
    {
        boxWidth = Max(boxWidth, FontAsset(U"Menu")(text).region().w);
    }
    
    // メニューボックスの設置
    for (auto i : step(m_MenuBoxes.size()))
    {
        m_MenuBoxes[i].set(390, static_cast<int>(450 + i * 80), boxWidth + 180, 60);
    }
}


/**
 毎フレーム呼び出す関数
 */
void Title::update() {
    bool handCursor = false;
    
    for (auto i : step(m_MenuBoxes.size()))
    {
        const Rect item = m_MenuBoxes[i];
        
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
    // メニューボックスにカーソルが当たったらカーソルを手の形にする
    Cursor::RequestStyle(handCursor ? CursorStyle::Hand : CursorStyle::Default);
}


/**
 描画の関数（update関数の後に呼び出される）
 */
void Title::draw() const {
    // ウィンドウのサイズを (1280, 720) に設定する
    Window::Resize(1280, 720);
    Window::SetTitle(GameInfo::title);
    // 背景色を設定する
    Graphics::SetBackground(GameInfo::BackgroundColor);
    System::SetExitEvent(WindowEvent::CloseButton);
    
    // 雲の描画
    m_tCloud.resized(1280, 400).draw();
    // 裁判所の描画
    m_tCourt.resized(700, 400).draw(290, 20);
    // 道の描画
    m_rLoad.draw(Palette::Sandybrown);
    
    Graphics2D::SetBlendState(BlendState::Default);
    
    const double titleHeight = FontAsset(U"Title")(GameInfo::title).region().h;
    
    // タイトルの文字
    FontAsset(U"Title")(GameInfo::title).drawAt(Window::Center().x, titleHeight, Palette::Black);
    
    // メニューボックスに文字を描画する
    // 「ゲームスタート」「スコア」「終了する」の３種類
    for (auto i : step(m_MenuBoxes.size()))
    {
        FontAsset(U"Menu")(m_MenuTexts[i]).drawAt(m_MenuBoxes[i].center(), Color(40));
    }
    
    const Size versionSize = FontAsset(U"Version")(GameInfo::version).region().size;
    
    // ゲームのバージョンを画面左下に表示する
    FontAsset(U"Version")(GameInfo::version).drawAt(Window::Size().moveBy(-versionSize));
}
