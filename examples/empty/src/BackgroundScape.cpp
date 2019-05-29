//
//  BackgroundScape.cpp
//  empty
//
//  Created by 山口隼矢 on 2019/03/28.
//

#include "BackgroundScape.hpp"

BackgroundScape::BackgroundScape(Texture &court, Texture &reporter,
                                 Texture &cloud, Texture &car) :
    m_tCourt(court), m_tReporter(reporter), m_tCar(car),
    m_rLoad(Vec2(0, 400), 1280, 320),m_tCloud(cloud){
        for (size_t i = 0; i < 5; i++) {
            m_ReporterPos.emplace_back(Window::Center().moveBy(-200 - 200 * Cos(ToRadians(90 * i / 5)), static_cast<int>(i * 30 - 50)));
        }
        for (size_t i = 5; i < 10; i++) {
            m_ReporterPos.emplace_back(Window::Center().moveBy(0 + 200 * Cos(ToRadians(90 * (i - 5) / 5)), static_cast<int>((i - 5) * 30 - 50)));
        }
    }

void BackgroundScape::draw() const {
    m_tCloud.resized(1280, 400).draw();
    m_tCourt.resized(700, 400).draw(290, 20);
    m_rLoad.draw(Palette::Sandybrown);
    
    for (auto reporterPosition : m_ReporterPos) {
        m_tReporter.scaled(0.7)
        .draw(reporterPosition);
    }
    
    m_tCar.scaled(1.2).drawAt(1280, 400);
}
