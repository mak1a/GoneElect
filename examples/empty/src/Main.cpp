#include"GameInfo.hpp"
#include"title.hpp"
#include"Game.hpp"
#include"Result.hpp"

///////////////////////////////////////////////////////////////////////
//
//  ハイスコア一覧
//
class Score : public MyApp::Scene
{
private:
    
    std::array<ScoreData, 5> m_highScores = defaultHighScores;
    
public:
    
    Score(const InitData& init)
    : IScene(init)
    {
        if (FileSystem::Exists(GameInfo::SaveFilePath))
        {
            Deserializer<BinaryReader>{GameInfo::SaveFilePath}(m_highScores);
        }
        else
        {
            Serializer<BinaryWriter>{GameInfo::SaveFilePath}(m_highScores);
        }
    }
    
    void update() override
    {
        if ((MouseL | KeyEscape).down())
        {
            changeScene(U"Title");
        }
    }
    
    void draw() const override
    {
        const int32 h = FontAsset(U"ScoreList").height();
        
        for (auto i : step(m_highScores.size()))
        {
            const Rect rect = Rect(520, 100).setCenter(Window::Center().x, 120 + i * 120);
            
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
};

///////////////////////////////////////////////////////////////////////
//
//  スタッフクレジット
//
class Credit : public MyApp::Scene
{
private:
    
    Array<std::tuple<String, double, bool>> m_credits;
    
    double m_height = 0.0;
    
    Stopwatch m_stopwatch{ true };
    
    double yOffset() const
    {
        return Window::Height() + 60 - m_stopwatch.ms() / 20.0;
    }
    
public:
    
    Credit(const InitData& init)
    : IScene(init)
    {
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
    
    void update() override
    {
        if ((MouseL | KeyEscape).down())
        {
            changeScene(U"Title");
        }
        
        if ((m_height + yOffset()) < 0)
        {
            m_stopwatch.restart();
        }
    }
    
    void draw() const override
    {
        const double offset = yOffset();
        
        for (const auto& credit : m_credits)
        {
            FontAsset(std::get<bool>(credit) ? U"CreditBig" : U"CreditSmall")(std::get<String>(credit))
            .drawAt(Window::Center().x, std::get<double>(credit) + offset);
        }
    }
};

///////////////////////////////////////////////////////////////////////
//
//  メイン関数
//
void Main()
{
    Window::Resize(1280, 720);
    Window::SetTitle(GameInfo::title);
    Graphics::SetBackground(GameInfo::BackgroundColor);
    System::SetExitEvent(WindowEvent::CloseButton);
    
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
