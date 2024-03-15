#pragma once
#include <Windows.h>
#include "../../Physics/PhysicsEngine.h"
#include "../../Threading/ThreadManager.h"
#include "../../EntityManager/EntityManager.h"
#include "../../ImGui/PanelManager.h"
#include "PhysicsBall.h"


struct PhysicsThreadingStruct 
{
	
    PhysicsBall* phyThread;

    double desiredUpdateTime = 0.0;  
    bool bRun = false;	
    bool bIsAlive = true;
    DWORD sleepTime;	

    DWORD ThreadId = 0;
    HANDLE threadHandle = 0;

};

