#include <string>
#include "math/Vector3.h"
#include <btBulletDynamicsCommon.h>


namespace ds
{
	class PhysicsHandler
	{
	public:
		PhysicsHandler();
		~PhysicsHandler();
		void ConstructEntity(int entityID, std::string modelPath, bool staticObject);
		void SetEntityPosition(int entityID, ds_math::Vector3 pos);
		ds_math::Vector3 GetEntityPosition(int entityID);
		void ApplyRotationToEntity(int entityID, ds_math::Vector3 axis, float angle);
		void SetWorldGravity(float yAmount);
		void SetWorldGravity(ds_math::Vector3 gravVec);
		void SetEntityMesh(int entityID, float mass);
		void SetEntityGravity(int entityID, ds_math::Vector3 grav);
		void SetEntityAngDampening(int entityId, float damp);
		void SetEntityFriction(int entityID, float fric);
		void RemoveEntity(int entityID);
		bool DoesEntityExist(int entityID);
		void SetPhysicsWorldIntertia(float inert);
		


	private:
		btDiscreteDynamicsWorld * m_physicalWorld;
		btBroadphaseInterface * m_broadphaseAlgo;
		btDefaultCollisionConfiguration * m_collisionConfig;
		btCollisionDispatcher * m_dispatcher;
		btSequentialImpulseConstraintSolver * m_worldLogic;
	};
}