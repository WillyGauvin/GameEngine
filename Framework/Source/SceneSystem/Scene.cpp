#include "Scene.h"
#include "Component/ComponentManager.h"
#include "EventSystem/EventManager.h"
#include "Objects/Camera.h"
#include "Objects/GameObject.h"
#include "MyContactListener.h"

namespace fw
{
	Scene::Scene(GameCore* pGameCore) :
		m_pGameCore(pGameCore)
	{
		b2Vec2 gravity = b2Vec2(0, -10);
		m_pWorld = new b2World(gravity);

		m_pComponentManager = new ComponentManager();
		m_pEventManager = new EventManager(m_pGameCore);
		m_pCamera = new Camera(this, vec3(0, 0, 0), vec3(0, 1, 0), vec3(0, 0, 3));
		m_pContactListener = new MyContactListener(m_pEventManager);
		m_pWorld->SetContactListener(m_pContactListener);
	}

	Scene::~Scene()
	{
		delete m_pEventManager;
		delete m_pCamera;

		for (fw::GameObject* pObject : m_Objects)
		{
			delete pObject;
		}

		delete m_pComponentManager;
		delete m_pWorld;
		delete m_pContactListener;
	}

	void Scene::ExecuteEvent(fw::Event* pEvent)
	{
	}

	void Scene::StartFrame(float deltaTime)
	{
	}

	void Scene::Update(float deltaTime)
	{
	}

	void Scene::Draw()
	{
	}

	void Scene::CreateRevoluteJoint(b2Body* ObjA, b2Body* ObjB, vec2 pos)
	{
		// Declare a joint definition object
		b2RevoluteJointDef jointdef;

		// Select a world space anchor point
		b2Vec2 anchorpos(pos.x, pos.y);


		// Initialize the motor on the joint
		jointdef.enableMotor = true;
		jointdef.motorSpeed = 20; // positive values will go counter-clockwise, negative clockwise
		jointdef.maxMotorTorque = 50;

		// Initialize the joint�s angle limits, in radians
	/*	jointdef.enableLimit = true;
		jointdef.lowerAngle = -60 * PI / 180;
		jointdef.upperAngle = 60 * PI / 180;*/


		// Initialize the joint definition with the 2 bodies and the world space anchor
		jointdef.Initialize(ObjA, ObjB, anchorpos);

		// Create the actual joint in the world
		m_pWorld->CreateJoint(&jointdef);


	}


	void Scene::CreatePrismaticJoint(b2Body* ObjA, b2Body* ObjB, vec2 pos, vec2 axis)
	{
		// Declare a joint definition object
		b2PrismaticJointDef jointdef;

		// Select a world space anchor point
		b2Vec2 anchorpos(pos.x, pos.y);

		b2Vec2 newaxis(axis.x, axis.y);

		// Initialize the motor on the joint
		jointdef.enableMotor = true;
		jointdef.motorSpeed = -20; // positive values will go counter-clockwise, negative clockwise
		jointdef.maxMotorForce = 20;

		// Initialize the joint�s angle limits, in radians
	/*	jointdef.enableLimit = true;
		jointdef.lowerAngle = -60 * PI / 180;
		jointdef.upperAngle = 60 * PI / 180;*/


		// Initialize the joint definition with the 2 bodies and the world space anchor
		jointdef.Initialize(ObjA, ObjB, anchorpos, newaxis);

		// Create the actual joint in the world
		m_pWorld->CreateJoint(&jointdef);


	}

}
