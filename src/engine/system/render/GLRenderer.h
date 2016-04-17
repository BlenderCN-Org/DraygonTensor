#pragma once

#include <vector>

#include <GL/glew.h>

#include "engine/common/HandleManager.h"
#include "engine/system/render/IRenderer.h"

namespace ds_render
{
/**
 * Modern OpenGL renderer.
 */
class GLRenderer : public IRenderer
{
public:
    /**
     * Allows renderer to perform any necessary initialization.
     *
     * Should be called before any other renderer methods.
     *
     * @param   viewportWidth   unsigned int, width of the viewport in pixels.
     * @param   viewportHeight  unsigned int, width of the viewport in pixels.
     * @return                  bool, TRUE if renderer initialized successfully,
     * FALSE otherwise.
     */
    virtual bool Init(unsigned int viewportWidth, unsigned int viewportHeight);

    /**
     * Set the clear colour of the colour buffer.
     *
     * @param r float, red value (0 - 1).
     * @param g float, green value (0 - 1).
     * @param b float, blue value (0 - 1).
     * @param a float, alpha value (0 - 1).
     */
    virtual void SetClearColour(float r, float g, float b, float a);

    /**
     * Clear the colour, depth and/or stencil buffers of the renderer.
     *
     * Buffers passed a value of TRUE are cleared, buffers passed a value OF
     * FALSE are not.
     *
     * @param colour bool, TRUE to clear colour buffer, FALSE otherwise.
     * @param depth bool, TRUE to clear depth buffer, FALSE otherwise.
     * @param stencil bool, TRUE to clear stencil buffer, FALSE otherwise.
     */
    virtual void
    ClearBuffers(bool colour = true, bool depth = true, bool stencil = true);

    /**
     * Resize the viewport the renderer renders to.
     *
     * @param  newViewportWidth   unsigned int, new viewport width in pixels.
     * @param  newViewportHeight  unsigned int, new viewport height in pixels.
     */
    virtual void ResizeViewport(unsigned int newViewportWidth,
                                unsigned int newViewportHeight);

    /**
     * Create a vertex buffer.
     *
     * A vertex buffer is a collection of vertex data (eg. position, normal,
     * texCoords)
     *
     * @param   usage        BufferUsageType, how the buffer will be used. See
     * BufferUsageType.
     * @param   description  VertexBufferDescription, description of the vertex
     * buffer and it's attributes. See VertexBufferDescription
     * @param   numBytes     size_t, number of bytes of data in vertex buffer.
     * @param   data         const void *, vertex buffer data to construct
     * vertex buffer with.
     * @return               VertexBufferHandle, handle to vertex buffer
     * created.
     */
    virtual VertexBufferHandle
    CreateVertexBuffer(BufferUsageType usage,
                       const VertexBufferDescription &description,
                       size_t numBytes,
                       const void *data);

    /**
     * Create an index buffer.
     *
     * A index buffer is a collection of indices which are used to determine the
     * order in which the vertices in a vertes buffer are drawn.
     *
     * @param   usage     BufferUsageType, how the buffer will be used. See
     * BufferUsageType.
     * @param   numBytes  size_t, number of bytes if data in the index buffer.
     * @param   data      const void *, index buffer data.
     * @return            IndexBufferHandle, handle to index buffer created.
     */
    virtual IndexBufferHandle
    CreateIndexBuffer(BufferUsageType usage, size_t numBytes, const void *data);

    /**
     * Compile the given shader source int a shader object of the given type.
     *
     * @param   shaderType        ShaderType, type of the shader (Vertex,
     * Fragment, etc.)
     * @param   shaderSourceSize  size_t, size of the shader source data (in
     * bytes).
     * @param   shaderSource      const char *, pointer to shader source data.
     * @return                    ShaderHandle, handle to compiled to shader
     * object.
     */
    virtual ShaderHandle CreateShaderObject(ShaderType shaderType,
                                            size_t shaderSourceSize,
                                            const char *shaderSource);

    /**
     * Create a shader program from a list of shaders.
     *
     * @param  shaders  const vector<ShaderHandle> &, list of shaders to create
     * shader program from.
     * @return          ProgramHandle, handle to created program.
     */
    virtual ProgramHandle
    CreateProgram(const std::vector<ShaderHandle> &shaders);

    /**
     * Set a shader program as the current shader program
     *
     * @param  programHandle  ProgramHandle, handle to program to set as the
     * current shader.
     * TODO: Unset program
     */
    virtual void SetProgram(ProgramHandle programHandle);

    /**
     * Draw a number of vertices in a vertex buffer.
     *
     * The vertices are drawn one-by-one from the given starting vertex.
     *
     * @param  buffer          VertexBufferHandle, vertex buffer to draw from.
     * @param  primitiveType   PrimitiveType, primitives to draw with vertices.
     * @param  startingVertex  size_t, index of vertex in vertex buffer to begin
     * drawing from.
     * @param  numVertices     size_t, number of vertices to draw from vertex
     * buffer.
     */
    virtual void DrawVertices(VertexBufferHandle buffer,
                              PrimitiveType primitiveType,
                              size_t startingVertex,
                              size_t numVertices);

    /**
     * Draw a number of vertices in a vertex buffer using the index buffer to
     * choose which vertices to draw and in which order.
     *
     * @param  buffer          VertexBufferHandle, vertex buffer to draw from.
     * @param  indexBuffer     IndexBufferHandle, index buffer to determine
     * which vertices to draw and in what order.
     * @param  primitiveType   PrimitiveType, primitives to draw with vertices.
     * @param  startingVertex  size_t, index of vertex in vertex buffer to begin
     * drawing from.
     * @param  numVertices     size_t, number of vertices to draw from vertex
     * buffer.
     */
    virtual void DrawVerticesIndexed(VertexBufferHandle buffer,
                                     IndexBufferHandle indexBuffer,
                                     PrimitiveType primitiveType,
                                     size_t startingVertex,
                                     size_t numVertices);

private:
    /**
     * A GLuint can represent one of many different OpenGL objects,
     * therefore,
     * use this enum to represent which OpenGL object it is.
     */
    enum class GLObjectType
    {
        ShaderObject,
        ProgramObject,
        VertexArrayObject,
        IndexBufferObject,
        TextureObject
    };

    /** Each OpenGL object is stored with it's handle so that the handles can be
     * updated easily. */
    struct GLObject
    {
        ds::Handle handle;
        GLuint object;
    };

    /**
     * Store an OpenGL object and return a handle to it, allowing us to access
     * that OpenGL object later.
     *
     * An OpenGL object may be a OpenGL handle to a shader, a program, a vertex
     * buffer, etc.
     *
     * @param   glObject  GLuint, OpenGL handle to a OpenGL object.
     * @param   type      GLObjectType, type of the OpenGL object to be stored.
     * @return            ds::Handle, handle to OpenGL object stored.
     */
    ds::Handle StoreOpenGLObject(GLuint glObject, GLObjectType type);

    /**
     * Get the OpenGL object of the given type using the given handle.
     *
     * Method will fail if type of the handle does not match type of
     * OpenGL object given.
     *
     * @param  handle           ds::Handle, handle to OpenGLObject.
     * @param  type             GLObjectType, type of the OpenGLObject
     *                          (VertexBuffer, Shader, etc.).
     * @param  openGLObjectOut  GLuint *, where to store openGLObject if method
     * is successful. If method is unsuccessful, openGLObject is not modified.
     * @return                  bool, TRUE if the method retrieved OpenGLObject
     * successfully, FALSE otherwise.
     */
    bool GetOpenGLObject(ds::Handle handle,
                         GLObjectType type,
                         GLuint *openGLObject) const;

    /**
     * Bind a vertex buffer for drawing.
     *
     * @param  handle  VertexBufferHandle, handle to vertex buffer to draw.
     */
    void BindVertexBuffer(VertexBufferHandle vertexBufferHandle);

    /**
     * Unbind all vertex buffers.
     */
    void UnbindVertexBuffer();

    /**
     * Convert a BufferUsageType to an OpenGL-specific equivalent.
     *
     * @param   usage  BufferUsageType, buffer usage type.
     * @return         GLenum, OpenGL buffer usage type.
     */
    GLenum ToGLBufferUsageType(BufferUsageType usage) const;

    /**
     * Convert a RenderDataType to an OpenGL-specific equivalent.
     *
     * @param   datatype  RenderDataType, data type to convert.
     * @return            GLenum, OpenGL data type.
     */
    GLenum ToGLDataType(RenderDataType dataType) const;

    /**
     * Convert a boolean value to an OpenGL bool.
     *
     * @param   boolean  bool, boolean to convert.
     * @return           GLenum, OpenGL bool.
     */
    GLenum ToGLBool(bool boolean) const;

    /**
     * Convert a ShaderType to an OpenGL-specific equivalent.
     *
     * @param   shaderType  ShaderType, shader type to convert.
     * @return              GLenum, OpenGL shader type.
     */
    GLenum ToGLShaderType(ShaderType shaderType) const;

    /**
     * Convert a PrimitiveType to an OpenGL-specific equivalent.
     *
     * @param   primitiveType  PrimitiveType, primitive type to convert.
     * @return                 GLenum, OpenGL primitive type.
     */
    GLenum ToGLPrimitiveType(PrimitiveType primitiveType) const;

    /**
     * All OpenGL objects that have been created by this renderer and their
     * handles.
     */
    std::vector<GLObject> m_openGLObjects;
    /** Handle manager used to manage the handles of all OpenGL objects we
     * create */
    ds::HandleManager m_handleManager;
};
}
