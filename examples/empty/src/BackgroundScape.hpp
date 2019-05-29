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
    Texture m_tCourt, m_tReporter, m_tCloud, m_tCar;
    
    RectF m_rLoad;
    
    Array<Vec2> m_ReporterPos;
public:
    BackgroundScape(Texture &court, Texture &reporter,
                    Texture &cloud, Texture &car);
    
    void draw() const;
};
