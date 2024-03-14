#include "PhysicsBall.h"
#include "../../GraphicsRender.h"
#include "../../Physics/PhysicsEngine.h"


PhysicsBall::PhysicsBall()
{
    ballPhysicsObj = new PhysicsObject();
    ballPhysicsObj->LoadModel("Models/DefaultSphere/DefaultSphere.fbx");
    GraphicsRender::GetInstance().AddModelAndShader(ballPhysicsObj, GraphicsRender::GetInstance().defaultShader);
    ballPhysicsObj->Initialize(SPHERE, true, DYNAMIC);
}

PhysicsBall::~PhysicsBall()
{
}



void PhysicsBall::MoveBall()
{
    ballPhysicsObj->transform.position.x += 1.0f;
}

void PhysicsBall::DrawProperties()
{
}

void PhysicsBall::SceneDraw()
{
}

void PhysicsBall::Start()
{
}

void PhysicsBall::Update(float deltaTime)
{
}

void PhysicsBall::OnDestroy()
{
}

void PhysicsBall::Render()
{
}


DWORD WINAPI UpdateBallThread(LPVOID lpParameter)
{
    BallThreadInfo* threadInfo = (BallThreadInfo*)lpParameter;

    double currentTime = glfwGetTime();
    double lastTime = currentTime;
    double deltaTime = 0.0f;

    double timeStep = 0.0f;

    while (threadInfo->bIsAlive)
    {
        if (threadInfo->bRun)
        {
            currentTime = glfwGetTime();
            deltaTime = currentTime - lastTime;
            lastTime = currentTime;

            if (deltaTime > threadInfo->desiredUpdateTime) { deltaTime = threadInfo->desiredUpdateTime; }

            timeStep += deltaTime;

            if (timeStep >= threadInfo->desiredUpdateTime)
            {
                timeStep = 0;

                threadInfo->phyEngine->Update(deltaTime);
            }

            Sleep(threadInfo->sleepTime);
        }

    }


    return 0;

}

void PhysicsBall::InitializeBallThread()
{

    threadInfo.desiredUpdateTime = stepTime;
    threadInfo.ball = this;
    threadInfo.phyEngine = &PhysicsEngine::GetInstance();
    threadInfo.bIsAlive = true;
    threadInfo.sleepTime = 100;
    threadInfo.bRun = true;
    threadInfo.threadHandle = CreateThread(
        NULL,							// lpThreadAttributes,
        0,								// dwStackSize,
        UpdateBallThread,				// lpStartAddress,
        (void*)&threadInfo,			//  lpParameter,
        0,								// dwCreationFlags (0 or CREATE_SUSPENDED)
        &threadInfo.ThreadId);			// lpThreadId


}