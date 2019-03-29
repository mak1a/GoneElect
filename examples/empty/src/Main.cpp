#include"GameInfo.hpp"
#include"Title.hpp"
#include"Game.hpp"
#include"Result.hpp"
#include"Score.hpp"
#include"Credit.hpp"

///////////////////////////////////////////////////////////////////////
//
//  メイン関数
//
void Main()
{
    //////////////////////////////////////////////////////////////
    //
    //  使用するシーン
    //
    MyApp manager;
    manager.setFadeColor(GameInfo::FadeInColor);
    manager.add<Title>(U"Title");
    manager.add<Game>(U"Game");
    manager.add<Result>(U"Result");
    manager.add<Score>(U"Score");
    manager.add<Credit>(U"Credit");
    
    //////////////////////////////////////////////////////////////
    //
    //  使用するフォント
    //
    FontAsset::Register(U"Title", GameInfo::TitleFontSize, Typeface::Heavy);
    FontAsset::Register(U"Menu", GameInfo::MenuFontSize, Typeface::Bold);
    FontAsset::Register(U"Version", 14, Typeface::Regular);
    FontAsset::Register(U"CountDown", 72, Typeface::Bold);
    FontAsset::Register(U"Result", 80, Typeface::Bold);
    FontAsset::Register(U"ResultButton", 32, Typeface::Regular);
    FontAsset::Register(U"GameTime", 40, Typeface::Light);
    FontAsset::Register(U"ScoreList", 50, Typeface::Heavy);
    FontAsset::Register(U"ScoreListDate", 25, Typeface::Regular, FontStyle::Italic);
    FontAsset::Register(U"CreditBig", 32, Typeface::Bold);
    FontAsset::Register(U"CreditSmall", 28, Typeface::Regular);
    
    //////////////////////////////////////////////////////////////
    //
    //  メインループ
    //
    while (System::Update())
    {
        if (!manager.update())
        {
            break;
        }
    }
}
