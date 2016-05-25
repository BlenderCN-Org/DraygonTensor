#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "engine/resource/IResource.h"
#include "engine/system/render/UniformBlock.h"
#include "engine/system/render/RenderCommon.h"

namespace ds
{
class MaterialResource : public IResource
{
public:
    /**
     * Create a material resource from file.
     *
     * @param   filePath  std::string, file path to create material resource
     * from.
     * @return            std::unique_ptr<IResource>, pointer to material
     * resource created.
     */
    static std::unique_ptr<IResource> CreateFromFile(std::string filePath);

    /**
     * Get the file path to the resource.
     *
     * @return  const std::string &, resource file path.
     */
    virtual const std::string &GetResourceFilePath() const;

    /**
     * Set the file path to the resource.
     *
     * @param  filePath  const std::string &, file path of this resource.
     */
    virtual void SetResourceFilePath(const std::string &filePath);

    /**
     * Return the path to the shader resource that this material resource uses.
     *
     * @return  const std::string &, file path to shader resource.
     */
    const std::string &GetShaderResourceFilePath() const;

    /**
     * Set the path to the shader resource that this material resource uses.
     *
     * @param  shaderFilePath  const std::string &, file path to shader
     * resource.
     */
    void SetShaderResourceFilePath(const std::string &shaderFilePath);

    /**
     * Get a list of texture sampler names this material resource contains.
     *
     * Corresponds to the name used in the shader for the texture.
     *
     * @return  std::vector<std::string>, list of texture sampler names.
     */
    std::vector<std::string> GetTextureSamplerNames() const;

    /**
     * Get the type (2D, Cubemap, etc.) of the texture sampler with the given
     * name.
     *
     * @param   samplerName  const std::string &, name of the texture sampler to
     *                       get the type of.
     * @return               ds_render::TextureType, type of the texture
     * sampler.
     */
    ds_render::TextureType
    GetTextureTextureType(const std::string &samplerName) const;

    /**
     * Add a new empty texture sampler to the material resource with no texture
     * file paths. If a texture sampler with that name already exists, it will
     * be erased and a blank sampler entry created.
     *
     * @param  samplerName  const std::string &, new texture sampler name.
     * @param  type         const ds_render::TextureType &, type of the texture
     * sampler.
     */
    void AddTextureSampler(const std::string &samplerName,
                           const ds_render::TextureType &type);

    /**
     * Get the texture resource file paths for the sampler with the given
     * sampler name (corresponding to the name of the texture sampler used in
     * the shader).
     *
     * If no texture sampler with that name, returns empty vector.
     *
     * @param   samplerName  const std::string &, sampler name of the texture.
     * @return               std::vector<std::string>, texture resource file
     *                       paths for the given texture sampler name.
     */
    std::vector<std::string>
    GetTextureSamplerFilePaths(const std::string &samplerName) const;

    /**
     * Add a texture resource file path to the texture sampler with the given
     * name.
     *
     * @pre SamplerEntry for samplerName must exist.
     *
     * @param  samplerName              const std::string &, sampler name of the
     *                                  texture.
     * @param  textureResourceFilePath  const std::string &, path to the texture
     *                                  resource to add to sampler entry.
     */
    void AddTextureSamplerFilePath(const std::string &samplerName,
                                   const std::string &textureResourceFilePath);

    /**
     * Add a uniform block to the material.
     *
     * @param  uniformBlock  const ds_render::UniformBlock &, uniform block.
     */
    void AddUniformBlock(const ds_render::UniformBlock &uniformBlock);

    /**
     * Get all uniform blocks associated with this material.
     *
     * @return const std::vector<ds_render::UniformBlock>
     */
    const std::vector<ds_render::UniformBlock> &GetUniformBlocks() const;

private:
    /**
     * A collection of textures that exist for a given texture type. Texture
     * types might be 2D (1 image, 2D sampler), 3D (1 image, 3D sampler),
     * Cubemap (6 images, 3D sampler) or HDR (1 image, 3D sampler).
     */
    struct SamplerEntry
    {
        /** Type of the texture */
        ds_render::TextureType type;
        /** Collection of texture files that form this texture */
        std::vector<std::string> filePaths;
    };

    /** Path to material shader file */
    std::string m_shaderPath;
    /** Map texture sampler name to SamplerEntry */
    std::map<std::string, SamplerEntry> m_textureSamplers;
    /** Uniform blocks */
    std::vector<ds_render::UniformBlock> m_uniformBlocks;
    /** This resource's file path */
    std::string m_filePath;
};
}
