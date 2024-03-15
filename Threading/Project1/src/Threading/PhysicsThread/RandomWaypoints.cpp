#include "RandomWaypoints.h"
#include "../../Utilities/Lerp.h"
#include "../../GraphicsRender.h"
#include <random>

RandomWaypoints::RandomWaypoints()
{
	LoadModel("Models/DefaultCube/DefaultCube.fbx");
	name = "AI Agent";
	meshes[0]->meshMaterial->material()->SetBaseColor(glm::vec4(1, 0, 0, 1));
	GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().defaultShader);

}

RandomWaypoints::RandomWaypoints(float patrolSpeed, float waitTime, float alertDistance, Camera* target)
{
	InitializeCriticalSection(&agent_CS);
	this->patrolSpeed = patrolSpeed;
	this->waitTime = waitTime;
	this->alertDistance = alertDistance;
	this->sceneCam = target;

	LoadModel("Models/DefaultCube/DefaultCube.fbx");
	
	name = "AI Agent";
	GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().defaultShader);

	alertDistanceModel = new Model("Models/DefaultSphere/DefaultSphere.fbx");
	alertDistanceModel->meshes[0]->isWireFrame = true;
	GraphicsRender::GetInstance().AddModelAndShader(alertDistanceModel, GraphicsRender::GetInstance().defaultShader);

	
	 //RenderWaypoints();
}

RandomWaypoints::~RandomWaypoints()
{
	DeleteCriticalSection(&agent_CS);
}

void RandomWaypoints::MoveAgent(const glm::vec3& targetPosition, const glm::vec3& targetRotation, float deltaTime)
{

	transform.position = Lerp(transform.position, targetPosition, deltaTime);
}

void RandomWaypoints::CalculateNextWaypoint(float deltaTime)
{
	EnterCriticalSection(&agent_CS);

	if (waypointIndex < listOfWaypoints.size())
	{
		const Waypoint& CurWaypoint = listOfWaypoints[waypointIndex];

		MoveAgent(CurWaypoint.position, transform.rotation, deltaTime * patrolSpeed);

		glm::vec3 currentPosition = transform.position;

		if (glm::distance(currentPosition, CurWaypoint.position) < 1.5f)
		{

			if (waitTime > 0)
			{
				waitTime -= deltaTime;
			}
			else
			{
				waypointIndex = GetRandomIntNumber(0,listOfWaypoints.size() - 1);

				waitTime = 2.0f;
			}

			
		}

	}

	LeaveCriticalSection(&agent_CS);
}

void RandomWaypoints::DrawProperties()
{
	Model::DrawProperties();
}

void RandomWaypoints::SceneDraw()
{
	Model::SceneDraw();
}

void RandomWaypoints::Start()
{
}

void RandomWaypoints::Update(float deltaTime)
{
	RenderAlertDistance();
	CalculateNextWaypoint(deltaTime);
}

void RandomWaypoints::Render()
{
}

void RandomWaypoints::OnDestroy()
{
}

void RandomWaypoints::RenderAlertDistance()
{
	alertDistanceModel->transform.SetPosition(transform.position);
	alertDistanceModel->transform.SetScale(glm::vec3(alertDistance));

	float distance = CalculateDistance(this->transform.position, sceneCam->transform.position);

	if (distance < alertDistance)
	{
		InterLock::Increment(&cameraDetected);
		std::cout << " Detected Camera Times :" << cameraDetected <<std::endl;

	}

}

float RandomWaypoints::CalculateDistance(glm::vec3& transform, glm::vec3& targetTransform)
{
	float dx = targetTransform.x - transform.x;
	float dy = targetTransform.y - transform.y;
	float dz = targetTransform.z - transform.z;

	return std::sqrt(dx * dx + dy * dy + dz * dz);


}

void RandomWaypoints::RenderWaypoints()
{
	for (size_t i = 0; i < listOfWaypoints.size(); i++)
	{
		waypointModel = new Model("Models/DefaultSphere/DefaultSphere.fbx");
		waypointModel->name = " Waypoints";
		waypointModel->transform.SetPosition(listOfWaypoints[i].position);
		waypointModel->transform.SetScale(glm::vec3(0.4f));
		GraphicsRender::GetInstance().AddModelAndShader(waypointModel, GraphicsRender::GetInstance().defaultShader);
	}

}

int RandomWaypoints::GetRandomIntNumber(int minValue, int maxValue)
{
	

		EnterCriticalSection(&agent_CS);
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(minValue, maxValue);
		LeaveCriticalSection(&agent_CS);
		return distribution(gen);


	
}



