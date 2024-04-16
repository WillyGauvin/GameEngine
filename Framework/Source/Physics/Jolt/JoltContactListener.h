
#include "EventSystem/EventManager.h"

#include "Jolt/Jolt.h"

#include "Jolt/Physics/Collision/ContactListener.h"


namespace fw
{
    class JoltContactListener : public JPH::ContactListener
    {
    public:
        JoltContactListener(EventManager* pEventManager);
        virtual	~JoltContactListener() override;
        // See: ContactListener
        virtual JPH::ValidateResult OnContactValidate(const JPH::Body& inBody1, const JPH::Body& inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult& inCollisionResult) override;

        virtual void OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override;

        virtual void OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override;

        virtual void OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair) override;
    protected:
        EventManager* m_pEventManager = nullptr;
    };
}
