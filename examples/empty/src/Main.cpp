#include"GameInfo.hpp"
#include"Title.hpp"
#include"Game.hpp"
#include"Result.hpp"
#include"Score.hpp"


/**
 メイン関数

 */
void Main()
{
    // 使用するシーン一覧
    MyApp manager;
    manager.setFadeColor(GameInfo::FadeInColor);
    manager.add<Title>(U"Title");
    manager.add<Game>(U"Game");
    manager.add<Result>(U"Result");
    manager.add<Score>(U"Score");
    
    
    // 使用するフォント
    FontAsset::Register(U"Title", GameInfo::TitleFontSize, Typeface::Heavy);
    FontAsset::Register(U"Menu", GameInfo::MenuFontSize, Typeface::Bold);
    FontAsset::Register(U"Version", 14, Typeface::Regular);
    FontAsset::Register(U"CountDown", 72, Typeface::Bold);
    FontAsset::Register(U"Result", 50, Typeface::Bold);
    FontAsset::Register(U"ResultSupplement", 30, Typeface::Regular);
    FontAsset::Register(U"GameTime", 40, Typeface::Light);
    FontAsset::Register(U"ScoreList", 50, Typeface::Heavy);
    FontAsset::Register(U"ScoreListDate", 25, Typeface::Regular, FontStyle::Italic);
    
    
    // メインループ
    while (System::Update())
    {
        if (!manager.update())
        {
            break;
        }
    }
}
