#include <assimp/Importer.hpp>

#include "engine/resource/MeshResource.h"

namespace ds
{
std::unique_ptr<IResource> MeshResource::CreateFromFile(std::string filePath)
{
    std::unique_ptr<IResource> meshResource(nullptr);

    // TODO: Parse file
    Assimp::Importer importer;

    // TODO: Create mesh resource

    // Return resource (if any)
    return meshResource;
}

// TODO: other methods (e.g. GetVertices...)
const std::string &MeshResource::GetResourceFilePath() const
{
    return m_filePath;
}

void MeshResource::SetResourceFilePath(const std::string &filePath)
{
    m_filePath = filePath;
}
}
