#pragma once
#include <Windows.h>
#include "../../EntityManager/EntityManager.h"
class RandomWaypoints;

class waypointThreadinfo
{

public:
    RandomWaypoints* huntl = nullptr;
    EntityManager* entityManager = nullptr;

    double desiredUpdateTime = 0.0;
    bool bRun = false;
    bool bIsAlive = true;
    DWORD sleepTime;

    DWORD ThreadId = 0;
    HANDLE threadHandle = 0;



};
