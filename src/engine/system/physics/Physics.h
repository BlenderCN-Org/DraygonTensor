#pragma once

#include "engine/system/ISystem.h"
#include "engine/system/physics/PhysicsComponentManager.h"
#include "engine/system/scene/TransformComponentManager.h"
#include "engine/system/physics/PhysicsWorld.h"

namespace ds
{
class Physics : public ISystem
{
public:
    Physics();

    virtual bool Initialize(const Config &config);

    virtual void Update(float deltaTime);

    virtual void Shutdown();

    virtual void PostMessages(const ds_msg::MessageStream &messages);

    virtual ds_msg::MessageStream CollectMessages();

    virtual const char *GetName() const;

    virtual ScriptBindingSet GetScriptBindings() const;

    void AddForceGenerator(Entity entity);

    void SetGravity(const ds_math::Vector3 &gravity);

private:
    void ProcessEvents(ds_msg::MessageStream *messages);

    void CreateTransformComponent(Entity entity, const Config &componentData);

    void CreatePhysicsComponent(Entity entity, const Config &componentData);

    void UpdateComponents();

    /** Messaging */
    ds_msg::MessageStream m_messagesGenerated, m_messagesReceived;

    // /** Transform component manager */
    TransformComponentManager m_transformComponentManager;
    // /** Physics component manager */
    PhysicsComponentManager m_physicsComponentManager;

    ds_phys::PhysicsWorld m_physicsWorld;

    std::shared_ptr<ds_phys::Gravity> m_gravityFg;
    // ds_phys::ImpulseGenerator *m_impulseFg;
    ds_phys::RigidBody m_body;
};
}
