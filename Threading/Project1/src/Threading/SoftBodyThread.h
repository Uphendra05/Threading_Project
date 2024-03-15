#pragma once
#include "ThreadStruct.h"

extern SoftBodyThread* sbInfo = new SoftBodyThread();
extern EntityThread* enInfo = new EntityThread();


DWORD WINAPI UpdateSoftBodyThread(LPVOID lpParameter)
{

	

	SoftBodyThread* sbInfor = (SoftBodyThread*)lpParameter;

	double lastFrameTime = glfwGetTime();
	double totalElapsedFrameTime = 0.0;
	DWORD sleepTime_ms = 1;

	sbInfor->phyThread->Initialize();

	while (sbInfor->bIsAlive)
	{
		if (sbInfor->bRun)
		{
			double currentTime = glfwGetTime();
			double deltaTime = currentTime - lastFrameTime;
			lastFrameTime = currentTime;

			totalElapsedFrameTime += deltaTime;



			if (totalElapsedFrameTime >= sbInfor->desiredUpdateTime)
			{
				totalElapsedFrameTime = 0;

				sbInfor->eneityManager->Update(deltaTime);
				//sbInfor->engine->Update(deltaTime);

			}


			Sleep(sbInfor->sleepTime);
		}

	}


	return 0;
}

DWORD WINAPI UpdateEntityThread(LPVOID lpParameter)
{

	EntityThread* enInfor = (EntityThread*)lpParameter;

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

				//sbInfor->eneityManager->Update(deltaTime);
				//sbInfor->engine->Update(deltaTime);
				//enInfor->entityManager->Update(deltaTime);

			}


			Sleep(enInfor->sleepTime);
		}

	}


	return 0;

}

void StartThreadForSoftBody(float time)
{
	
	sbInfo->desiredUpdateTime = time;
	sbInfo->engine = &PhysicsEngine::GetInstance();
	sbInfo->manager = &ThreadManager::Getinstance();
	sbInfo->eneityManager = &EntityManager::GetInstance();
	sbInfo->panelmanager = &PanelManager::GetInstance();
	sbInfo->bIsAlive = true;
	sbInfo->sleepTime = 1;

	sbInfo->threadHandle = CreateThread(
		NULL,						
		0,							
		UpdateSoftBodyThread,		
		(void*)sbInfo,			
		0,						
		&sbInfo->ThreadId);		

	// SoftBody Thread
}

void StartEntityThread(float time)
{

	enInfo->desiredUpdateTime = time;
	enInfo->entityManager = &EntityManager::GetInstance();
	enInfo->bIsAlive = true;
	enInfo->sleepTime = 1;
	enInfo->threadHandle = CreateThread(
		NULL,
		0,
		UpdateEntityThread,
		(void*)sbInfo,
		0,
		&sbInfo->ThreadId);


}
