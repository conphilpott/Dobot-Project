#pragma once
#ifndef DOBOT_H
#define DOBOT_H

#include "Arduino.h"
class Dobot
{
    public:
        Dobot();
        void printPose();
        void begin();
        void commandFrame(byte comFrame[]);
        void jogXp(); //not yet implemented
        void jogXm(); //not yet implemented
        void jogYp(); //not yet implemented
        void jogYm(); //not yet implemented
        void jogZp(); //not yet implemented
        void jogZm(); //not yet implemented
};

#endif