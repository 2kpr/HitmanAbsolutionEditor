#pragma once

#include <memory>

#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../Shader.h"
#include "Material.h"
#include "Math/BoundingBox.h"
#include "Resources/RenderPrimitive.h"
#include "Component.h"
#include "Rendering/Scene/SceneRenderer.h"

class Mesh : public Component
{
public:
    Mesh(const char* name, const char* icon, std::weak_ptr<Entity> entity);
    void Initialize(RenderPrimitive::Mesh* mesh, std::shared_ptr<Resource> matiResource);

    template <typename T>
    void Initialize(const std::vector<T>& vertices, const SceneRenderer::Shaders vertexShader, const SceneRenderer::Shaders pixelShader, Vector3 color, PrimitiveType primitiveType = PrimitiveType::TriangleList)
    {
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            VertexPosition vertexPosition;

            vertexPosition.position = Vector3(vertices[i].position);

            vertexPositions.push_back(vertexPosition);
        }

        indices = nullptr;
        this->vertexShader = SceneRenderer::GetShader(vertexShader);
        this->pixelShader = SceneRenderer::GetShader(pixelShader);
        this->materialColor = color;
        this->primitiveType = primitiveType;

        CreateGpuBuffers(vertices);
        CreateBoundingBox(vertices);
    }

    template <typename T>
    void Initialize(const std::vector<T>& vertices, const std::vector<unsigned short>& indices, const SceneRenderer::Shaders vertexShader, const SceneRenderer::Shaders pixelShader, Vector3 color, PrimitiveType primitiveType = PrimitiveType::TriangleList)
    {
        for (size_t i = 0; i < vertices.size(); ++i)
        {
            VertexPosition vertexPosition;

            vertexPosition.position = Vector3(vertices[i].position);

            vertexPositions.push_back(vertexPosition);
        }

        this->indices = &indices;
        this->vertexShader = SceneRenderer::GetShader(vertexShader);
        this->pixelShader = SceneRenderer::GetShader(pixelShader);
        this->materialColor = color;
        this->primitiveType = primitiveType;

        CreateGpuBuffers(vertices, indices);
        CreateBoundingBox(vertices);
    }

    const std::vector<VertexPosition>& GetVertexPositions() const;
    const std::vector<unsigned short>& GetIndices() const;
    const VertexBuffer* GetVertexBuffer() const;
    const IndexBuffer* GetIndexBuffer() const;
    Shader* GetVertexShader() const;
    Shader* GetPixelShader() const;
    const BoundingBox& GetAABB();
    const unsigned char GetLODMask() const;
    const float GetBlurRadius() const;
    const float GetBlurSigma() const;
    const Vector4& GetOutlineColor() const;
    const PrimitiveType GetPrimitiveType() const;

    void CreateGpuBuffers(RenderPrimitive::Mesh* mesh);

    template <typename T>
    void CreateGpuBuffers(const std::vector<T>& vertices)
    {
        vertexBuffer = std::make_shared<VertexBuffer>();
        vertexBuffer->Create(vertices);
    }

    template<typename T>
    void CreateGpuBuffers(const std::vector<T>& vertices, const std::vector<unsigned short>& indices)
    {
        vertexBuffer = std::make_shared<VertexBuffer>();
        vertexBuffer->Create(vertices);

        indexBuffer = std::make_shared<IndexBuffer>();
        indexBuffer->Create(indices);
    }

    void CreateBoundingBox(const RenderPrimitive::Mesh* mesh);

    template <typename T>
    void CreateBoundingBox(const std::vector<T>& vertices)
    {
        boundingBox = BoundingBox(vertices);
    }

    void CreateMaterial(const RenderPrimitive::Mesh* mesh, std::shared_ptr<Resource> matiResource);
    void Render() override;
    void RenderProperties() override;
    void SetWireframe(const bool wireframe);
    void SetIsLODInRange(const bool isLODInRange);

private:
    std::vector<VertexPosition> vertexPositions;
    const std::vector<unsigned short>* indices;
    std::shared_ptr<VertexBuffer> vertexBuffer;
    std::shared_ptr<IndexBuffer> indexBuffer;
    std::shared_ptr<Shader> vertexShader;
    std::shared_ptr<Shader> pixelShader;
    Material material;
    Matrix44 lastTransform = Matrix44::Identity;
    BoundingBox boundingBox;
    BoundingBox aabb;
    PrimitiveType primitiveType;

    bool useGlossAlpha;
    bool useSpecularMap;
    bool useNormalMap;
    Vector3 materialColor;
    Vector3 specularColor;
    float specularWeight;
    float specularGloss;
    float normalMapWeight;
    unsigned char lodMask;
    bool isLODInRange;
    bool wireframe;

    float blurRadius;
    float blurSigma;
    Vector4 outlineColor;
};
