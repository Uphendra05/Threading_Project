#pragma once
#include "../../Physics/PhysicsObject.h"
#include "../../model.h"

#include <iostream>
#include <functional>
#include "ThreadHelper.h"




class PhysicsThread : public Model
{
public:

	PhysicsThread();
	~PhysicsThread();


	void Initialize();

	void SpawnBalls();


	LONG objectsSpawned;
	LONG i;

	CRITICAL_SECTION ball_CS;

	int GetRandomIntNumber(int minValue, int maxValue);
	

private:

	PhysicsObject* ballPhysicsObj;
	PhysicsObject* floorModel;

};

