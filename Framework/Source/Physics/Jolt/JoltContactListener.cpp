#include "JoltContactListener.h"
#include "Jolt/Physics/Body/Body.h"
namespace fw
{
    JoltContactListener::JoltContactListener(EventManager* pEventManager) :
        m_pEventManager(pEventManager)
    {
    }

    JoltContactListener::~JoltContactListener()
    {

    }

    JPH::ValidateResult JoltContactListener::OnContactValidate(const JPH::Body& inBody1, const JPH::Body& inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult& inCollisionResult)
    {
        //cout << "Contact validate callback" << endl;

        // Allows you to ignore a contact before it is created (using layers to not make objects collide is cheaper!)
        return JPH::ValidateResult::AcceptAllContactsForThisBodyPair;
    }

    void JoltContactListener::OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
    {
        //cout << "A contact was added" << endl;
        fw::CollisionEvent* pEvent = new fw::CollisionEvent(inBody1.GetObjectLayer(), inBody2.GetObjectLayer());
        m_pEventManager->AddEvent(pEvent);
    }

    void JoltContactListener::OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
    {
        //cout << "A contact was persisted" << endl;
    }

    void JoltContactListener::OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair)
    {
        //cout << "A contact was removed" << endl;
    }

}
