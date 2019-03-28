//
//  Game.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/27.
//

#include "Game.hpp"

Game::Game(const InitData& init)
    : IScene(init), mTextureCourt(U"texture/saibanjo.png"), bgs(mTextureCourt) {
    getData().lastScore = 0;
}

void Game::update() {
    if ((MouseL | KeyEscape).down()) {
        changeScene(U"Result");
    }
}

void Game::draw() const {
    bgs.draw();
}
