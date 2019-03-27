//
//  BackgroundScape.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/28.
//

#include "BackgroundScape.hpp"

BackgroundScape::BackgroundScape(Texture &_mTexture) :
    mTexture(_mTexture) {
        
    }

void BackgroundScape::draw() const {
    mTexture.resized(1280, 720).draw();
}
