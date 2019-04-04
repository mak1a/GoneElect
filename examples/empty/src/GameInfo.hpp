//
//  GameInfo.hpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/27.
//
#pragma once

#include<Siv3D.hpp>
#include<HamFramework.hpp>

namespace GameInfo {
    // ゲームのタイトル
    const String title = U"作業服の会長";
    
    // ゲームのバージョン
    const String version = U"Version 1.0";
    
    // ゲームの背景色
    const ColorF BackgroundColor = Palette::Ghostwhite;
    
    // シーン切り替え時のフェードイン・アウトの色
    const ColorF FadeInColor = Palette::Black;
    
    // タイトルのフォントサイズ
    const int32 TitleFontSize = 150;
    
    // メニューのフォントサイズ
    const int32 MenuFontSize = 40;
    
    // メニュー項目「ゲームスタート」
    const String MenuGameStart = U"ゲームスタート";
    
    // メニュー項目「スコア」
    const String MenuScore = U"スコア";
    
    // メニュー項目「終了」
    const String MenuExit = U"終了";
    
    // セーブデータの保存場所
    const FilePath SaveFilePath = U"Save/Score.dat";
}


// 全てのシーンからアクセスできるデータ
struct GameData
{
    int32 lastScore = 0;
    int32 wrongGone = 0;
    int32 wrongLawer = 0;
};

using MyApp = SceneManager<String, GameData>;


// セーブ用スコアデータ
struct ScoreData
{
    int32 score;
    
    Date date;
    
    template <class Archive>
    void SIV3D_SERIALIZE(Archive& archive)
    {
        archive(score, date);
    }
};

// デフォルトのハイスコア
const std::array<ScoreData, 5> defaultHighScores
{
    ScoreData{ 50, Date(2018,1,1) },
    ScoreData{ 40, Date(2018,1,1) },
    ScoreData{ 30, Date(2018,1,1) },
    ScoreData{ 20, Date(2018,1,1) },
    ScoreData{ 10, Date(2018,1,1) },
};
