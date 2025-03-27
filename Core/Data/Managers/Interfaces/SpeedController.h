// Created by AwallencePC on 27.03.2025.
//

#ifndef SPEEDCONTROLLER_H
#define SPEEDCONTROLLER_H

class SpeedController
{
public:
    virtual ~SpeedController() = default;
    virtual void resetAcceleration() = 0;
};

#endif //SPEEDCONTROLLER_H