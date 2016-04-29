#pragma once

#include <vector>

#include "btBulletDynamicsCommon.h"

#include "engine/resource/ResourceFactory.h"
#include "engine/resource/TerrainResource.h"
#include "engine/system/ISystem.h"
#include "engine/system/physics/PhysicsComponentManager.h"
#include "engine/system/scene/TransformComponentManager.h"

namespace ds
{
class Physics : public ISystem
{

public:
    virtual bool Initialize(const Config &config);
    virtual void Update(float deltaTime);
    virtual void Shutdown();
    virtual void PostMessages(const ds_msg::MessageStream &messages);
    virtual ds_msg::MessageStream CollectMessages();

private:
    void ProcessEvents(ds_msg::MessageStream *messages);
    ds_msg::MessageStream m_messagesGenerated, m_messagesReceived;

    /**
     * Create a bullet rigid body from the given parameters.
     *
     * btRigidBody should be freed by user.
     *
     * @param   origin  const ds_math::Vector3 &, origin of rigid body.
     * @param   shape   StringIntern::StringId, interned string that will give
     * string representing collision shape of rigidbody.
     * @param   scale   const ds_math::Vector3 &, scale of rigid body.
     * @param   mass    float, mass of the rigid body. 0 for a static rigid
     * body.
     */
    btRigidBody *CreateRigidBody(const ds_math::Vector3 &origin,
                                 StringIntern::StringId shape,
                                 const ds_math::Vector3 &scale,
                                 float mass);

    /**
     * Create a bullet rigid body for a height map from the given parameters.
     *
     * btRigidBody should be freed by user.
     *
     * @param   origin             const ds_math::Vector3 &, origin of rigid
     *                             body.
     * @param   heightmapFilePath  const std::string &, path to heightmap file.
     * @param   heightScale        float, factor to scale terrain height by.
     */
    btRigidBody *CreateHeightMapRigidBody(const ds_math::Vector3 &origin,
                                          const std::string &heightmapFilePath,
                                          float heightScale);

    btDiscreteDynamicsWorld *m_dynamicsWorld;
    btSequentialImpulseConstraintSolver *m_solver;
    btBroadphaseInterface *m_overlappingPairCache;
    btCollisionDispatcher *m_dispatcher;
    btDefaultCollisionConfiguration *m_collisionConfiguration;
    btAlignedObjectArray<btCollisionShape *> m_collisionShapes;

    /** Transform component manager */
    TransformComponentManager m_transformComponentManager;
    /** Physics component manager */
    PhysicsComponentManager m_physicsComponentManager;

    /** Resource factory */
    ResourceFactory m_factory;

    /** Heightmap data */
    std::vector<std::vector<float>> m_heightmapData;
};
}
