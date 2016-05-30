#pragma once

#include <vector>

#include "engine/system/render/ConstantBuffer.h"
#include "engine/system/render/RenderCommon.h"
#include "engine/system/render/Texture.h"
#include "engine/system/render/RenderCommon.h"
#include "engine/resource/MaterialResourceManager.h"

namespace ds_render
{
class Material
{
public:
    /**
     * A shader texture is composed of the name of the sampler to bind the
     * texture to and the texture to bind to that sampler.
     */
    struct ShaderTexture
    {
        /** Name of sampler to bind texture to */
        std::string samplerName;
        /** Handle to Texture to bind to sampler */
        TextureHandle textureHandle;
    };

    /**
     * Get the shader program this material uses.
     *
     * @return  ProgramHandle, shader program this material uses.
     */
    ProgramHandle GetProgram() const;

    /**
     * Set the shader program this material uses.
     *
     * @param  program  ProgramHandle, shader program to set.
     */
    void SetProgram(ProgramHandle program);

    /**
     * Add a texture to this material.
     *
     * @param  samplerName    const std::string &, name of sampler in shader to
     * bind this texture to.
     * @param  textureHandle  TextureHandle, handle to texture to add to this
     * material.
     */
    void AddTexture(const std::string &samplerName,
                    TextureHandle textureHandle);

    /**
     * Get a list sampler names and their corresponding texture.
     *
     * @return  const std::vector<ShaderTexture> &, list of sampler names and
     * their corresponding textures.
     */
    const std::vector<ShaderTexture> &GetTextures() const;

    /**
     * Add a constant buffer to this material.
     *
     * @param  constantBufferName  const std::string &, name of the constant
     * buffer in shader to bind given constant buffer to.
     * @param  constantBuffer      const ConstantBuffer &, constant buffer to
     * add to material.
     */
    void AddConstantBuffer(const std::string &constantBufferName,
                           const ConstantBuffer &constantBuffer);

    /**
     * Get the handle to the material resource from which this material was
     * created.
     *
     * @return  MaterialResourceHandle, handle to material resource from
     * which this material was created.
     */
    ds::MaterialResourceHandle GetMaterialResourceHandle() const;

    /**
     * Set handle to the material resource from which this material was created.
     *
     * @param  materialResourceHandle  MaterialResourceHandle, handle to
     * material resource from which this material was created.
     */
    void SetMaterialResourceHandle(
        ds::MaterialResourceHandle materialResourceHandle);

private:
    /** Shader program */
    ProgramHandle m_program;
    /** Material textures */
    std::vector<ShaderTexture> m_textures;
    /** Material constant buffer */
    std::vector<std::pair<std::string, ConstantBuffer>> m_constantBuffers;
    /** Handle to the material resource that created this material */
    ds::MaterialResourceHandle m_materialResourceHandle;
};
}
