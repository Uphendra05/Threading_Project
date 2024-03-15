#pragma once
#include "EntityThreadingStruct.h"

extern EntityThreadingStruct* enInfo = new EntityThreadingStruct();


DWORD WINAPI UpdateSoftBodyThread(LPVOID lpParameter)
{

	EntityThreadingStruct* enInfor = (EntityThreadingStruct*)lpParameter;

	double lastFrameTime = glfwGetTime();
	double totalElapsedFrameTime = 0.0;
	DWORD sleepTime_ms = 1;


	while (enInfor->bIsAlive)
	{
		if (enInfor->bRun)
		{
			double currentTime = glfwGetTime();
			double deltaTime = currentTime - lastFrameTime;
			lastFrameTime = currentTime;

			totalElapsedFrameTime += deltaTime;



			if (totalElapsedFrameTime >= enInfor->desiredUpdateTime)
			{
				totalElapsedFrameTime = 0;

				
				enInfor->eneityManager->Update(deltaTime);
				
			}


			Sleep(enInfor->sleepTime);
		}

	}


	return 0;

}

void StartThreadForEntity(float time)
{
	
	enInfo->desiredUpdateTime = time;
	enInfo->engine = &PhysicsEngine::GetInstance();
	enInfo->manager = &ThreadManager::Getinstance();
	enInfo->eneityManager = &EntityManager::GetInstance();
	enInfo->panelmanager = &PanelManager::GetInstance();
	enInfo->bIsAlive = true;
	enInfo->sleepTime = 1;

	enInfo->threadHandle = CreateThread(
		NULL,						
		0,							
		UpdateSoftBodyThread,		
		(void*)enInfo,
		0,						
		&enInfo->ThreadId);

	// SoftBody Thread
}
