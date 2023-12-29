#include "Resources/MultiLanguage.h"

void MultiLanguage::Deserialize()
{
	BinaryReader binaryReader = BinaryReader(GetResourceData(), GetResourceDataSize());
	localizationCategory = binaryReader.Read<char>();
	const unsigned int count = (GetResourceDataSize() - 1) >> 3;
	const char* data = static_cast<const char*>(GetResourceData());

	for (unsigned int i = 0; i < count; ++i)
	{
		const int index = *reinterpret_cast<const int*>(&data[8 * i + 5]);
		const std::string locale = &data[8 * i + 1];

		indices.push_back(index);
		locales.push_back(locale);
	}

	isResourceDeserialized = true;
}

char MultiLanguage::GetLocalizationCategory()
{
	return localizationCategory;
}

std::vector<int>& MultiLanguage::GetIndices()
{
	return indices;
}

std::vector<std::string>& MultiLanguage::GetLocales()
{
	return locales;
}
