#include "Glacier/Entity/SCppEntity.h"

std::string SCppEntity::SerializeToJson()
{
    rapidjson::StringBuffer stringBuffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(stringBuffer);

    writer.StartObject();

    writer.String("blueprintIndexInResourceHeader");
    writer.Int(blueprintIndexInResourceHeader);

    writer.String("propertyValues");
    propertyValues.SerializeToJson(writer);

    writer.EndObject();

    return stringBuffer.GetString();
}

void SCppEntity::SerializeToMemory(ZBinarySerializer& binarySerializer)
{
    unsigned int blueprintIndexInResourceHeaderOffset = offsetof(SCppEntity, blueprintIndexInResourceHeader);
    unsigned int propertyValuesOffset = offsetof(SCppEntity, propertyValues);

    binarySerializer.WriteToMemory(&blueprintIndexInResourceHeader, sizeof(int), blueprintIndexInResourceHeaderOffset);

    propertyValues.SerializeToMemory(binarySerializer, propertyValuesOffset);
}

SCppEntity* SCppEntity::DeserializeFromJson(const rapidjson::Document& document)
{
    SCppEntity* cppEntity = new SCppEntity();

    cppEntity->blueprintIndexInResourceHeader = document["blueprintIndexInResourceHeader"].GetInt();
    cppEntity->propertyValues = *TArray<SEntityTemplateProperty>::DeserializeFromJson(document["propertyValues"].GetArray());

    return cppEntity;
}
