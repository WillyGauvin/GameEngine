#pragma once

namespace JPH {
    class PhysicsSystem;
    class TempAllocatorImpl;
    class JobSystemThreadPool;
    class Body;
    class ContactListener;
}

namespace fw {

    class EventManager;
    class BPLayerInterfaceImpl;
    class ObjectVsBroadPhaseLayerFilterImpl;
    class ObjectLayerPairFilterImpl;

    class JoltWorldBundle
    {
    public:
        JPH::PhysicsSystem* m_pWorld = nullptr;
        JPH::JobSystemThreadPool* m_pJobSystem = nullptr;
        JPH::TempAllocatorImpl* m_pTempAllocator = nullptr;

        BPLayerInterfaceImpl* m_pBroadPhaseLayerInterface = nullptr;
        ObjectVsBroadPhaseLayerFilterImpl* m_pObjecVsBroadphaseLayerFilter = nullptr;
        ObjectLayerPairFilterImpl* m_pObjectVsObjectLayerFilter = nullptr;
    };

    JoltWorldBundle* CreateJoltWorld(EventManager* pEventManager, JPH::ContactListener* pListener);


    void UpdateJoltWorld(JoltWorldBundle* pBundle, float deltaTime);
    void DestroyJoltWorld(JoltWorldBundle* pBundle);
    
    JPH::Body* CreateJoltBody(JPH::PhysicsSystem* pWorld, vec3 pos, vec3 rot, vec3 scale, bool isDynamic, float density);

    JPH::Body* CreateSphereJoltBody(JPH::PhysicsSystem* pWorld, vec3 pos, float radius, bool isDynamic, float density);
    JPH::Body* CreateCubeJoltBody(JPH::PhysicsSystem* pWorld, vec3 pos, vec3 rot, vec3 scale, bool isDynamic, float density);

    JPH::Body* CreateMeshJoltBody(JPH::PhysicsSystem* pWorld, vec3 pos, vec3 rot, vec3 scale, bool isDynamic, float density, GameObject* pGameObject);
    void DestroyJoltBody(JPH::PhysicsSystem* pWorld, JPH::Body* pBody);

    void SetJoltBodyPositionRotation(JoltWorldBundle* bundle, JPH::Body* body, vec3 position, vec3 rotation);
} // namespace fw