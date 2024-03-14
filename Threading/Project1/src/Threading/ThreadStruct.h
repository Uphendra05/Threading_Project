#pragma once
#include <Windows.h>
#include "../Physics/PhysicsEngine.h"
#include "Threading/ThreadManager.h"
#include "../EntityManager/EntityManager.h"
#include "../ImGui/PanelManager.h"
#include "PhysicsThread/PhysicsThread.h"


struct SoftBodyThread // SoftBody Struct Infor
{
	PhysicsEngine* engine;
    ThreadManager* manager;
    EntityManager* eneityManager;
    PanelManager* panelmanager;
    PhysicsThread* phyThread;

    double desiredUpdateTime = 0.0;  
    bool bRun = false;	
    bool bIsAlive = true;
    DWORD sleepTime;	

    DWORD ThreadId = 0;
    HANDLE threadHandle = 0;

};