//
//  BackgroundScape.hpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/28.
//

#pragma once
#include<Siv3D.hpp>

class BackgroundScape {
private:
    Texture mTextureCourt, mTextureReporter, mTextureCloud;
    
    RectF mRectLoad;
    
    Array<Vec2> mReporterPositions;
public:
    BackgroundScape(Texture &_mTextureCourt, Texture &_mTextureReporter, Texture &_mTextureCloud);
    
    void draw() const;
};
