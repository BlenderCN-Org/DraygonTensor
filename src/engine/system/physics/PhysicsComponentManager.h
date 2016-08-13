#pragma once

#include "engine/entity/ComponentManager.h"
#include "engine/system/physics/PhysicsComponent.h"

namespace ds
{
/**
 * Physics component manager.
 *
 * Associates an entity with some physics properties. The memory of each Bullet
 * collisionObject is managed by the Physics system. The Physics system is
 * responsible for deleting PhysicsComponent instances when their rigidbodies
 * are deleted.
 */
class PhysicsComponentManager : public ComponentManager<PhysicsComponent>
{
public:
    /**
     * Get the rigid body of the given component instance.
     *
     * @param   i  Instance, component instance to get rigid body of.
     * @return     btCollisionObject *, physics rigid body.
     */
    btCollisionObject *GetCollisionObject(Instance i) const;

    /**
     * Set the rigid body of the given component instance.
     *
     * @param  i          Instance, component instance to set rigid body of.
     * @param  collisionObject  btCollisionObject *, rigid body to set.
     */
    void SetCollisionObject(Instance i, btCollisionObject *collisionObject);

    /**
     * Get the collision shape of the given component instance.
     *
     * @param   i  Instance, component instance to get rigid body of.
     * @return     btCollisionShape *, collision shape.
     */
    btCollisionShape *GetCollisionShape(Instance i) const;

    /**
     * Set the collision shape of the given component instance.
     *
     * @param  i               Instance, component instance to set collision
     * shape of.
     * @param  collisionShape  btCollisionShape *, collision shape to set.
     */
    void SetCollisionShape(Instance i, btCollisionShape *collisionShape);

    /**
     * Get the collision shape type of the given component instance.
     *
     * @param   i  Instance, component instance to get collision shape type of.
     * @return     StringIntern::StringId, interned string that will give the
     * collision shape type as a string.
     */
    StringIntern::StringId GetShape(Instance i) const;

    /**
     * Set the collision shape type of the given component instance.
     *
     * @param  i      Instance, component instance to set collision shape type
     *                of.
     * @param  shape  StringIntern::StringId, interned string that will give the
     *                collision shape type as a string.
     */
    void SetShape(Instance i, StringIntern::StringId shape);

    /**
     * Get the scale of the given physics component instance.
     *
     * @param   i  Instance, component instance to get scale of.
     * @return     const ds_math::Vector3 &, scale of the given component
     *             instance.
     */
    const ds_math::Vector3 &GetScale(Instance i) const;

    /**
     * Set the scale of the given physics component instance.
     *
     * @param  i      Instance, component instance to set scale of.
     * @param  scale  const ds_math::Vector3 &, scale to set given physics
     *                component instance.
     */
    void SetScale(Instance i, const ds_math::Vector3 &scale);

    /**
     * Get the mass of the given physics component instance.
     *
     * @param   i  Instance, component instance to get mass of.
     * @return     float, mass of given component instance.
     */
    float GetMass(Instance i) const;

    /**
     * Set the mass of the given physics component instance.
     *
     * @param  i     Instance, component instance to set mass of.
     * @param  mass  float, mass to give given physics component instance.
     */
    void SetMass(Instance i, float mass);

    /**
     * Get the component instance with the given collision object.
     *
     * Returns invalid instance if no physics component instance has the given
     * collision object.
     *
     * @param   collisionObject  const btCollisionObject *, collision object to
     * find component instance for.
     * @return                   Instance, component instance with the given
     * collisionObject.
     */
    Instance
    GetInstanceForCollisionObject(const btCollisionObject *collisionObject);
};
}
