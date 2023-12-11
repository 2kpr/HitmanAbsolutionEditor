#pragma once

#undef min
#undef max

#include <string>

#include "Physics/NxSphereShapeDesc.h"
#include "Physics/NxCapsuleShapeDesc.h"
#include "Physics/NxBoxShapeDesc.h"

#include "Glacier/Physics/ZPhysicsResourceData.h"
#include "Glacier/Physics/ECollidableLayer.h"

#include "IO/BinaryReader.h"

class Physics
{
public:
	Physics() = default;
	const ZCollisionShape& GetCollisionShape() const;
	void Deserialize(const std::string& filePath);
	void Deserialize(void* data, const unsigned int dataSize);
	void Deserialize(BinaryReader& binaryReader);
	bool DeserializeHeader(BinaryReader& binaryReader);
	bool DeserializeCollisionShape(BinaryReader& binaryReader);
	bool DeserializeConvexMesh(BinaryReader& binaryReader);
	bool DeserializeTriangleMesh(BinaryReader& binaryReader);
	bool DeserializeImplicitPrimitives(std::vector<G2NxShapeDesc*>& shapeDescriptors, BinaryReader& binaryReader);
	void DeserializeSphereShape(NxSphereShapeDesc* sphereShapeDescriptor, BinaryReader& binaryReader);
	void DeserializeCapsuleShape(NxCapsuleShapeDesc* capsuleShapeDescriptor, BinaryReader& binaryReader);
	void DeserializeBoxShape(NxBoxShapeDesc* boxShapeDescriptor, BinaryReader& binaryReader);
	bool DeserializeShatterData(BinaryReader& binaryReader);
	bool DeserializeKinematicLinkedData(BinaryReader& binaryReader);
	NxMat34 DeserializeNxMat34(BinaryReader& binaryReader);
	bool IsCollisionLayerOpaque(const ECollidableLayer collidableLayer);
	void SerializeToJson(const std::string& outputFilePath);

private:
	const float skinWidth = 0.00999999978f;
	NxPhysicsSDK* physicsSDK;
	unsigned int id;
	ZPhysicsResourceData::SHeaderData headerData;
	ZCollisionShape collisionShape;
	ZPhysicsResourceData::SShatterData shatterData;
	SKinematicLinkedPrimResourceData linkedPrimData;
};
