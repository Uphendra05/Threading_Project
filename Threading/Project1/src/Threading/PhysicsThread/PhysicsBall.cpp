#include "PhysicsBall.h"
#include "../../GraphicsRender.h"
#include "../../Physics/PhysicsEngine.h"
#include <random>

PhysicsBall::PhysicsBall()
{
	InitializeCriticalSection(&ball_CS);

	ballPhysicsObj = new PhysicsObject();
	ballPhysicsObj->LoadModel("Models/DefaultSphere/DefaultSphere.fbx");
	
	floorModel = new PhysicsObject();
	floorModel->LoadModel("Models/DefaultQuad/DefaultQuad.fbx");

	floorModel->transform.SetPosition(glm::vec3(1, -2, 1));
	floorModel->transform.SetRotation(glm::vec3(90,0,0));

	floorModel->transform.SetScale(glm::vec3(100));

	GraphicsRender::GetInstance().AddModelAndShader(floorModel, GraphicsRender::GetInstance().defaultShader);
	floorModel->Initialize(AABB, true, STATIC);

}

PhysicsBall::~PhysicsBall()
{

	DeleteCriticalSection(&ball_CS);

}

void PhysicsBall::Initialize()
{

	SpawnBalls();


}

void PhysicsBall::SpawnBalls()
{
	EnterCriticalSection(&ball_CS);

	InterLock::Increment(&objectsSpawned);

	PhysicsObject* copyBall = new PhysicsObject();
	copyBall->LoadModel(*ballPhysicsObj);

	copyBall->transform.SetPosition(glm::vec3( GetRandomIntNumber(-2,2) * (InterLock::Increment(&i)), 10, GetRandomIntNumber(-2, 2) * (InterLock::Increment(&i))));

	GraphicsRender::GetInstance().AddModelAndShader(copyBall, GraphicsRender::GetInstance().defaultShader);
	copyBall->Initialize(SPHERE, true, DYNAMIC);

	std::cout << " Counter : " << objectsSpawned << std::endl;

	LeaveCriticalSection(&ball_CS);


}

int PhysicsBall::GetRandomIntNumber(int minValue, int maxValue)
{
	
		EnterCriticalSection(&ball_CS);
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(minValue, maxValue);
		LeaveCriticalSection(&ball_CS);
		return distribution(gen);

	
}

