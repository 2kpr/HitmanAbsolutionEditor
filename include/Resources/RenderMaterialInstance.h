#pragma once

#include <vector>
#include <string>

#include "DirectXTex.h"

#include "Glacier/Material/SProperty.h"
#include "Glacier/Material/SRMaterialPropertyList.h"
#include "Glacier/Material/PROPERTY_TYPE.h"

#include "IO/BinaryReader.h"
#include "Resource.h"

class RenderMaterialInstance
{
public:
	struct Property
	{
		SProperty propertyInfo;
		std::vector<Property> childProperties;
		unsigned int uint32Value;
		float floatValue;
		std::string stringValue;
	};

	struct Texture
	{
		enum class Type
		{
			Unknown,
			Diffuse,
			Normal,
			Specular,
			Emissive
		};

		Type type;
		DirectX::Blob* blob = nullptr;
		int textureReferenceIndex = -1;
		std::string name;
	};

	void Deserialize(const std::string& filePath);
	void Deserialize(void* buffer, const unsigned int dataSize);
	void Deserialize(BinaryReader& binaryReader);
	void ReadProperty(Property& property, BinaryReader& binaryReader, const unsigned int propertyOffset);
	void GetTextures(std::shared_ptr<Resource> matiResource, std::vector<RenderMaterialInstance::Texture>& textures);
	void GetTextures(const Property& property, std::shared_ptr<Resource> matiResource, std::vector<Texture>& textures, bool& foundNormalTexture, bool& foundDiffuseTexture, bool& foundSpecularTexture);

private:
	SRMaterialPropertyList materialPropertyList;
	Property instanceProperty;
};
