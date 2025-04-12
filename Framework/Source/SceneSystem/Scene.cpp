#include "Scene.h"
#include "EventSystem/EventManager.h"
#include "Component/ComponentManager.h"
#include "Objects/Camera.h"
#include "Objects/GameObject.h"
#include "Physics/Box2D/MyContactListener.h"
#include "Component/TransformComponent.h"
#include "Component/LightComponent.h"
#include "Component/RenderComponent.h"
#include "Utility/Uniforms.h"


namespace fw
{
	Scene::Scene(GameCore* pGameCore) :
		m_pGameCore(pGameCore)
	{
		m_pEventManager = new EventManager(m_pGameCore);
		m_pComponentManager = new ComponentManager(m_pEventManager);

		m_pCamera = new Camera(this, vec3(0, 0, 0), vec3(0, 1, 0), vec3(0, 0, 3));
	}

	Scene::~Scene()
	{
		delete m_pEventManager;
		delete m_pCamera;

		for (fw::GameObject* pObject : m_Objects)
		{
			delete pObject;
		}

		m_Objects.clear();
		m_Lights.clear();

		delete m_pComponentManager;
	}

	void Scene::ExecuteEvent(fw::Event* pEvent)
	{
	}

	void Scene::StartFrame(float deltaTime)
	{
		m_pEventManager->ProcessEvents();
	}

	void Scene::Update(float deltaTime)
	{
		m_pComponentManager->Update(deltaTime);

		m_pCamera->Update(deltaTime);
	}

	void Scene::Draw()
	{
		PopulateAllLightArrays();
		Uniforms* pUniforms = GetGameCore()->GetUniforms();

		bgfx::setUniform(pUniforms->GetUniform("u_LightPosition"), &m_LightPos, UINT16_MAX);
		bgfx::setUniform(pUniforms->GetUniform("u_LightColor"), &m_LightColor, UINT16_MAX);
		bgfx::setUniform(pUniforms->GetUniform("u_LightRange"), &m_LightRange, UINT16_MAX);
		bgfx::setUniform(pUniforms->GetUniform("u_AmbientPercentage"), &m_AmbPerc, UINT16_MAX);
		bgfx::setUniform(pUniforms->GetUniform("u_FalloffExponent"), &m_FalloffExp, UINT16_MAX);
		bgfx::setUniform(pUniforms->GetUniform("u_SpecularExponent"), &m_SpecExp, UINT16_MAX);
	}

	GameObject* Scene::GetClosestLight(vec3 position)
	{
		if (m_Lights.size() == 0)
		{
			return nullptr;
		}

		GameObject* closestLight = m_Lights[0];

		for (GameObject* light : m_Lights)
		{
			if (closestLight->GetTransformComponent() == nullptr)
			{
				//closest light has no transform component
				assert(false);
			}
			if (light->GetTransformComponent() == nullptr)
			{
				//light has no transform component
				assert(false);
			}
			float currentDistance = (closestLight->GetTransformComponent()->m_position - position).Length();
			float challengingDistance = (light->GetTransformComponent()->m_position - position).Length();

			if (challengingDistance < currentDistance)
			{
				closestLight = light;
			}
		}
		return closestLight;
	}

	//void Scene::CreateRevoluteJoint(b2Body* ObjA, b2Body* ObjB, vec2 pos)
	//{
	//	// Declare a joint definition object
	//	b2RevoluteJointDef jointdef;

	//	// Select a world space anchor point
	//	b2Vec2 anchorpos(pos.x, pos.y);


	//	// Initialize the motor on the joint
	//	jointdef.enableMotor = true;
	//	jointdef.motorSpeed = 20; // positive values will go counter-clockwise, negative clockwise
	//	jointdef.maxMotorTorque = 50;

	//	// Initialize the joint’s angle limits, in radians
	///*	jointdef.enableLimit = true;
	//	jointdef.lowerAngle = -60 * PI / 180;
	//	jointdef.upperAngle = 60 * PI / 180;*/


	//	// Initialize the joint definition with the 2 bodies and the world space anchor
	//	jointdef.Initialize(ObjA, ObjB, anchorpos);

	//	// Create the actual joint in the world
	//	m_pWorld->CreateJoint(&jointdef);


	//}


	//void Scene::CreatePrismaticJoint(b2Body* ObjA, b2Body* ObjB, vec2 pos, vec2 axis)
	//{
	//	// Declare a joint definition object
	//	b2PrismaticJointDef jointdef;

	//	// Select a world space anchor point
	//	b2Vec2 anchorpos(pos.x, pos.y);

	//	b2Vec2 newaxis(axis.x, axis.y);

	//	// Initialize the motor on the joint
	//	jointdef.enableMotor = true;
	//	jointdef.motorSpeed = -20; // positive values will go counter-clockwise, negative clockwise
	//	jointdef.maxMotorForce = 20;

	//	// Initialize the joint’s angle limits, in radians
	///*	jointdef.enableLimit = true;
	//	jointdef.lowerAngle = -60 * PI / 180;
	//	jointdef.upperAngle = 60 * PI / 180;*/


	//	// Initialize the joint definition with the 2 bodies and the world space anchor
	//	jointdef.Initialize(ObjA, ObjB, anchorpos, newaxis);

	//	// Create the actual joint in the world
	//	m_pWorld->CreateJoint(&jointdef);


	//}

	void Scene::PopulateAllLightArrays()
	{
		for (int i = 0; i < 10; i++)
		{
			if (i < m_Lights.size())
			{
				fw::GameObject* object = m_Lights[i];
				fw::LightComponent* component = object->GetLightComponent();
				m_LightPos[i] = vec4(object->GetTransformComponent()->m_position, 0);

				vec4 color = object->GetRenderComponent()->GetColor();

				m_LightColor[i] = color;
				m_LightRange[i] = vec4(component->m_LightRange, 0.0f, 0.0f, 0.0f);
				m_AmbPerc[i] = vec4(component->m_AmbientPerc, 0.0f, 0.0f ,0.0f);
				m_FalloffExp[i] = vec4(component->m_FalloffExp, 0.0f, 0.0f, 0.0f);
				m_SpecExp[i] = vec4(component->m_SpecularExp, 0.0f, 0.0f, 0.0f);
			}
			else
			{
				m_LightPos[i] = vec4();
				m_LightColor[i] = vec4();
				m_LightRange[i] = vec4();
				m_AmbPerc[i] = vec4();
				m_FalloffExp[i] = vec4();
				m_SpecExp[i] = vec4();
			}

		}

	}
}