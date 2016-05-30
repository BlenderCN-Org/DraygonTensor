#include "engine/system/render/Material.h"

namespace ds_render
{
ProgramHandle Material::GetProgram() const
{
    return m_program;
}

void Material::SetProgram(ProgramHandle program)
{
    m_program = program;
}

void Material::AddTexture(const std::string &samplerName,
                          TextureHandle textureHandle)
{
    // Construct shader texture
    ShaderTexture shaderTexture;
    shaderTexture.samplerName = samplerName;
    shaderTexture.textureHandle = textureHandle;

    // Add it
    m_textures.push_back(shaderTexture);
}

const std::vector<Material::ShaderTexture> &Material::GetTextures() const
{
    return m_textures;
}

void Material::AddConstantBuffer(const std::string &constantBufferName,
                                 const ConstantBuffer &constantBuffer)
{
    m_constantBuffers.push_back(std::pair<std::string, ConstantBuffer>(
        constantBufferName, constantBuffer));
}

ds::MaterialResourceHandle Material::GetMaterialResourceHandle() const
{
    return m_materialResourceHandle;
}

void Material::SetMaterialResourceHandle(
    ds::MaterialResourceHandle materialResourceHandle)
{
    m_materialResourceHandle = materialResourceHandle;
}
}
