//
//  BackgroundScape.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/28.
//

#include "BackgroundScape.hpp"

BackgroundScape::BackgroundScape(Texture &_mTextureCourt, Texture &_mTextureReporter, Texture &_mTextureCloud) :
    mTextureCourt(_mTextureCourt), mTextureReporter(_mTextureReporter), mRectLoad(Vec2(0, 400), 1280, 320),
    mTextureCloud(_mTextureCloud){
        for (size_t i = 0; i < 5; i++) {
            mReporterPositions.emplace_back(Window::Center().moveBy(-200 - 200 * Cos(ToRadians(90 * i / 5)), static_cast<int>(i * 30 - 50)));
        }
        for (size_t i = 5; i < 10; i++) {
            mReporterPositions.emplace_back(Window::Center().moveBy(0 + 200 * Cos(ToRadians(90 * (i - 5) / 5)), static_cast<int>((i - 5) * 30 - 50)));
        }
    }

void BackgroundScape::draw() const {
    mTextureCloud.resized(1280, 400).draw();
    mTextureCourt.resized(700, 400).draw(290, 20);
    mRectLoad.draw(Palette::Sandybrown);
    
    for (auto reporterPosition : mReporterPositions) {
        mTextureReporter.scaled(0.7)
        .draw(reporterPosition);
    }
}
