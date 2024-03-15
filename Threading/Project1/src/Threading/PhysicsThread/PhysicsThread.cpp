#include "PhysicsThread.h"
#include "../../GraphicsRender.h"
#include "../../Physics/PhysicsEngine.h"
#include <random>

PhysicsThread::PhysicsThread()
{
	InitializeCriticalSection(&ball_CS);

	ballPhysicsObj = new PhysicsObject();
	ballPhysicsObj->LoadModel("Models/DefaultSphere/DefaultSphere.fbx");
	GraphicsRender::GetInstance().AddModelAndShader(ballPhysicsObj, GraphicsRender::GetInstance().defaultShader);
	ballPhysicsObj->Initialize(SPHERE, true, DYNAMIC);

	floorModel = new PhysicsObject();
	floorModel->LoadModel("Models/DefaultQuad/DefaultQuad.fbx");

	floorModel->transform.SetPosition(glm::vec3(1, -2, 1));
	floorModel->transform.SetRotation(glm::vec3(90,0,0));

	floorModel->transform.SetScale(glm::vec3(100));

	GraphicsRender::GetInstance().AddModelAndShader(floorModel, GraphicsRender::GetInstance().defaultShader);
	floorModel->Initialize(AABB, true, STATIC);

}

PhysicsThread::~PhysicsThread()
{

	DeleteCriticalSection(&ball_CS);

}

void PhysicsThread::Initialize()
{

	SpawnBalls();


}

void PhysicsThread::SpawnBalls()
{
	EnterCriticalSection(&ball_CS);

	InterLock::Increment(&objectsSpawned);

	PhysicsObject* copyBall = new PhysicsObject();
	copyBall->LoadModel(*ballPhysicsObj);

	copyBall->transform.SetPosition(glm::vec3( GetRandomIntNumber(2,5) * (InterLock::Increment(&i)), 10, GetRandomIntNumber(2, 5)));

	GraphicsRender::GetInstance().AddModelAndShader(copyBall, GraphicsRender::GetInstance().defaultShader);
	copyBall->Initialize(SPHERE, true, DYNAMIC);

	std::cout << " Counter : " << objectsSpawned << std::endl;

	LeaveCriticalSection(&ball_CS);


}

int PhysicsThread::GetRandomIntNumber(int minValue, int maxValue)
{
	
		EnterCriticalSection(&ball_CS);
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(minValue, maxValue);
		LeaveCriticalSection(&ball_CS);
		return distribution(gen);

	
}

