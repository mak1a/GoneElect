//
//  Result.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/27.
//

#include "Result.hpp"

Result::Result(const InitData& init)
    : IScene(init) {
    
}

void Result::update() {
    if ((MouseL | KeyEscape).down()) {
        changeScene(U"Title");
    }
}

void Result::draw() const {
    
}
