#pragma once
#include "../../Physics/PhysicsObject.h"
#include "../../model.h"
#include "BallThreadInfo.h"

class PhysicsBall : public Model
{
public:

	PhysicsBall();
	~PhysicsBall();


	void MoveBall();
	void DrawProperties() override;
	void SceneDraw() override;

	void Start() override;
	void Update(float deltaTime) override;
	void OnDestroy();
	void Render() override;


	BallThreadInfo threadInfo;
	void InitializeBallThread();


private:

	PhysicsObject* ballPhysicsObj;
	static constexpr float stepTime = 1.0f / 60.f;
};

