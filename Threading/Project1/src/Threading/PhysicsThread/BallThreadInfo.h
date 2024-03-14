#pragma once
#include <Windows.h>
#include "../../Physics/PhysicsEngine.h"
class PhysicsBall;



class BallThreadInfo
{
public:

	PhysicsBall* ball = nullptr;
    PhysicsEngine* phyEngine;


    double desiredUpdateTime = 0.0;
    bool bRun = false;
    bool bIsAlive = true;
    DWORD sleepTime;

    DWORD ThreadId = 0;
    HANDLE threadHandle = 0;

    CRITICAL_SECTION* ball_CS = nullptr;


};