#pragma once
#include "PhysicsThreadingStruct.h"

extern PhysicsThreadingStruct* sbInfo = new PhysicsThreadingStruct();


DWORD WINAPI UpdateThread(LPVOID lpParameter)
{

	PhysicsThreadingStruct* sbInfor = (PhysicsThreadingStruct*)lpParameter;

	double lastFrameTime = glfwGetTime();
	double totalElapsedFrameTime = 0.0;
	DWORD sleepTime_ms = 1;

	sbInfor->phyThread->Initialize();

	
	return 0;
}


void StartThread(float time)
{
	
	sbInfo->desiredUpdateTime = time;
	sbInfo->bIsAlive = true;
	sbInfo->sleepTime = 1;

	sbInfo->threadHandle = CreateThread(
		NULL,						
		0,							
		UpdateThread,		
		(void*)sbInfo,			
		0,						
		&sbInfo->ThreadId);		

	
}


