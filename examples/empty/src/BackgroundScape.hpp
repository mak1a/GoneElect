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
    Texture mTexture;
public:
    BackgroundScape(Texture &_mTexture);
    
    void draw() const;
};
