#pragma once
#include <Windows.h>
#include "../Physics/PhysicsEngine.h"
#include "Threading/ThreadManager.h"
#include "../EntityManager/EntityManager.h"
#include "../ImGui/PanelManager.h"
#include "PhysicsThread/PhysicsThread.h"


struct SoftBodyThread 
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

struct EntityThread
{

    EntityManager* entityManager;
   
    double desiredUpdateTime = 0.0;
    bool bRun = false;
    bool bIsAlive = true;
    DWORD sleepTime;

    DWORD ThreadId = 0;
    HANDLE threadHandle = 0;

};