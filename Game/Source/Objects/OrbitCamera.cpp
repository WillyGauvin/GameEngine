#include "Framework.h"

#include "OrbitCamera.h"
#include "Utility/Uniforms.h"


OrbitCamera::OrbitCamera(fw::Scene* pScene, vec3 eye, vec3 up, vec3 at, VirtualController* pController, fw::GameObject* pTarget) :
	fw::Camera(pScene, eye, up, at),
	m_pController(pController),
	m_pTarget(pTarget)
{
	m_pTarget->SetCamera(this);
}

OrbitCamera::~OrbitCamera()
{
}

void OrbitCamera::Update(float32 deltaTime)
{
	vec2 rotationSpeed = vec2(1.0f, 0.4f);

	if (m_pController->isActionHeld(VirtualController::OrbitRight))
		m_Rotation.y += 90 * deltaTime * rotationSpeed.x;

	if (m_pController->isActionHeld(VirtualController::OrbitLeft))
		m_Rotation.y -= 90 * deltaTime * rotationSpeed.x;

	if (m_pController->isActionHeld(VirtualController::OrbitUp))
		m_Rotation.x -= 90 * deltaTime * rotationSpeed.y;

	if (m_pController->isActionHeld(VirtualController::OrbitDown))
		m_Rotation.x += 90 * deltaTime * rotationSpeed.y;

	if (m_pController->isActionHeld(VirtualController::ZoomIn))
		m_Distance -= 10 * deltaTime;

	if (m_pController->isActionHeld(VirtualController::ZoomOut))
		m_Distance += 10 * deltaTime;

	fw::MyClamp(m_Distance, 0.1f, 100.0f);
	fw::MyClamp(m_Rotation.x, -89.9f, 89.9f);

	float sx = sin(m_Rotation.x / 180 * PI);
	float sy = sin(m_Rotation.y / 180 * PI);
	float cx = cos(m_Rotation.x / 180 * PI);
	float cy = cos(m_Rotation.y / 180 * PI);
	vec3 offset = vec3(cx * sy * m_Distance, -sx * m_Distance, -1 * cx * cy * m_Distance);


	m_eye = m_pTarget->GetTransformComponent()->m_position + offset;
	m_at = m_pTarget->GetTransformComponent()->m_position;
	m_up = vec3(0, 1, 0);

	SetEye(m_eye);
	SetAt(m_at);

}

void OrbitCamera::ExecuteEvent(fw::Event* pEvent)
{
	Super::ExecuteEvent(pEvent);
}

void OrbitCamera::Enable(int viewID)
{
	fw::Uniforms* pUniforms = m_pScene->GetGameCore()->GetUniforms();

	mat4 viewMatrix;
	viewMatrix.CreateLookAtView(m_eye, m_up, m_at);
	// viewMatrix.CreateLookAtView(m_eye, m_up, m_eye + m_at);

	bgfx::setUniform(pUniforms->GetUniform("u_MatView"), &viewMatrix, 1);

	mat4 projMatrix;
	projMatrix.CreatePerspectiveVFoV(45, m_AspectRatio, 0.01f, 300.0f);
	bgfx::setUniform(pUniforms->GetUniform("u_MatProj"), &projMatrix);
}
