#include "OrbitCamera.h"

fw::OrbitCamera::OrbitCamera(Scene* pScene, vec3 eye, vec3 up, vec3 at) : fw::Camera(pScene, eye, up, at)
{
}

fw::OrbitCamera::~OrbitCamera()
{
}

void fw::OrbitCamera::Update(float32 deltaTime)
{
}

void fw::OrbitCamera::ExecuteEvent(Event* pEvent)
{
	Super::ExecuteEvent(pEvent);
}

void fw::OrbitCamera::Enable(int viewID)
{
	Super::Enable(viewID);
}
