#pragma once

#include <vector>

#include "BasePanel.h"
#include "Resources/Resource.h"

class HexViewerPanel : public BasePanel
{
public:
	HexViewerPanel(const char* name, const char* icon, const bool showResourceData);
	void Render() override;
	void SetResource(std::shared_ptr<Resource> resource);
	void GetHexBytes(const unsigned char* data, const size_t dataSize);

private:
	bool showResourceData;
	std::shared_ptr<Resource> resource;
	std::string offsets;
	std::string bytes;
	std::string decodedText;
};
