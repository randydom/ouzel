// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#include "core/Setup.h"

#if OUZEL_COMPILE_OPENGL

#include "OGLTexture.hpp"
#include "OGLRenderDevice.hpp"

namespace ouzel
{
    namespace graphics
    {
        static GLenum getOGLInternalPixelFormat(PixelFormat pixelFormat, uint32_t openGLVersion)
        {
#if OUZEL_SUPPORTS_OPENGLES
            if (openGLVersion >= 3)
            {
                switch (pixelFormat)
                {
                    case PixelFormat::A8_UNORM: return GL_ALPHA8_OES;
                    case PixelFormat::R8_UNORM: return GL_R8;
                    case PixelFormat::R8_SNORM: return GL_R8_SNORM;
                    case PixelFormat::R8_UINT: return GL_R8UI;
                    case PixelFormat::R8_SINT: return GL_R8I;

                    case PixelFormat::R16_UNORM: return GL_NONE;
                    case PixelFormat::R16_SNORM: return GL_NONE;
                    case PixelFormat::R16_UINT: return GL_R16UI;
                    case PixelFormat::R16_SINT: return GL_R16I;
                    case PixelFormat::R16_FLOAT: return GL_R16F;
                    case PixelFormat::R32_UINT: return GL_R32UI;
                    case PixelFormat::R32_SINT: return GL_R32I;
                    case PixelFormat::R32_FLOAT: return GL_R32F;
                    case PixelFormat::RG8_UNORM: return GL_RG8;
                    case PixelFormat::RG8_SNORM: return GL_RG8_SNORM;
                    case PixelFormat::RG8_UINT: return GL_RG8UI;
                    case PixelFormat::RG8_SINT: return GL_RG8I;
                    case PixelFormat::RGBA8_UNORM: return GL_RGBA8;
                    case PixelFormat::RGBA8_SNORM: return GL_RGBA8_SNORM;
                    case PixelFormat::RGBA8_UINT: return GL_RGBA8UI;
                    case PixelFormat::RGBA8_SINT: return GL_RGBA8I;

                    case PixelFormat::RGBA16_UNORM: return GL_NONE;
                    case PixelFormat::RGBA16_SNORM: return GL_NONE;
                    case PixelFormat::RGBA16_UINT: return GL_RGBA16UI;
                    case PixelFormat::RGBA16_SINT: return GL_RGBA16I;
                    case PixelFormat::RGBA16_FLOAT: return GL_RGBA16F;
                    case PixelFormat::RGBA32_UINT: return GL_RGBA32UI;
                    case PixelFormat::RGBA32_SINT: return GL_RGBA32I;
                    case PixelFormat::RGBA32_FLOAT: return GL_RGBA32F;
                    default: return GL_NONE;
                }
            }
            else
            {
                switch (pixelFormat)
                {
                    case PixelFormat::A8_UNORM: return GL_ALPHA;
                    case PixelFormat::RGBA8_UNORM: return GL_RGBA;
                    default: return GL_NONE;
                }
            }
#else
            (void)openGLVersion;

            switch (pixelFormat)
            {
                case PixelFormat::A8_UNORM: return GL_ALPHA8_EXT;

                case PixelFormat::R8_UNORM: return GL_R8;
                case PixelFormat::R8_SNORM: return GL_R8_SNORM;
                case PixelFormat::R8_UINT: return GL_R8UI;
                case PixelFormat::R8_SINT: return GL_R8I;

                case PixelFormat::R16_UNORM: return GL_R16;
                case PixelFormat::R16_SNORM: return GL_R16_SNORM;
                case PixelFormat::R16_UINT: return GL_R16UI;
                case PixelFormat::R16_SINT: return GL_R16I;
                case PixelFormat::R16_FLOAT: return GL_R16F;
                case PixelFormat::R32_UINT: return GL_R32UI;
                case PixelFormat::R32_SINT: return GL_R32I;
                case PixelFormat::R32_FLOAT: return GL_R32F;
                case PixelFormat::RG8_UNORM: return GL_RG8;
                case PixelFormat::RG8_SNORM: return GL_RG8_SNORM;
                case PixelFormat::RG8_UINT: return GL_RG8UI;
                case PixelFormat::RG8_SINT: return GL_RG8I;
                case PixelFormat::RGBA8_UNORM: return GL_RGBA8;
                case PixelFormat::RGBA8_SNORM: return GL_RGBA8_SNORM;
                case PixelFormat::RGBA8_UINT: return GL_RGBA8UI;
                case PixelFormat::RGBA8_SINT: return GL_RGBA8I;

                case PixelFormat::RGBA16_UNORM: return GL_RGBA16;
                case PixelFormat::RGBA16_SNORM: return GL_RGBA16_SNORM;
                case PixelFormat::RGBA16_UINT: return GL_RGBA16UI;
                case PixelFormat::RGBA16_SINT: return GL_RGBA16I;
                case PixelFormat::RGBA16_FLOAT: return GL_RGBA16F;
                case PixelFormat::RGBA32_UINT: return GL_RGBA32UI;
                case PixelFormat::RGBA32_SINT: return GL_RGBA32I;
                case PixelFormat::RGBA32_FLOAT: return GL_RGBA32F;
                default: return GL_NONE;
            }
#endif
        }

        static GLenum getOGLPixelFormat(PixelFormat pixelFormat)
        {
            switch (pixelFormat)
            {
                case PixelFormat::A8_UNORM:
                    return GL_ALPHA;
                case PixelFormat::R8_UNORM:
                case PixelFormat::R8_SNORM:
                case PixelFormat::R16_UNORM:
                case PixelFormat::R16_SNORM:
                case PixelFormat::R16_FLOAT:
                case PixelFormat::R32_FLOAT:
                    return GL_RED;
                case PixelFormat::R8_UINT:
                case PixelFormat::R8_SINT:
                case PixelFormat::R16_UINT:
                case PixelFormat::R16_SINT:
                case PixelFormat::R32_UINT:
                case PixelFormat::R32_SINT:
                    return GL_RED_INTEGER;
                case PixelFormat::RG8_UNORM:
                case PixelFormat::RG8_SNORM:
                    return GL_RG;
                case PixelFormat::RG8_UINT:
                case PixelFormat::RG8_SINT:
                    return GL_RG_INTEGER;
                case PixelFormat::RGBA8_UNORM:
                case PixelFormat::RGBA8_SNORM:
                case PixelFormat::RGBA16_UNORM:
                case PixelFormat::RGBA16_SNORM:
                case PixelFormat::RGBA16_FLOAT:
                case PixelFormat::RGBA32_FLOAT:
                    return GL_RGBA;
                case PixelFormat::RGBA8_UINT:
                case PixelFormat::RGBA8_SINT:
                case PixelFormat::RGBA16_UINT:
                case PixelFormat::RGBA16_SINT:
                case PixelFormat::RGBA32_UINT:
                case PixelFormat::RGBA32_SINT:
                    return GL_RGBA_INTEGER;
                default:
                    return 0;
            }
        }

        static GLenum getOGLPixelType(PixelFormat pixelFormat)
        {
            switch (pixelFormat)
            {
                case PixelFormat::A8_UNORM:
                case PixelFormat::R8_UNORM:
                case PixelFormat::R16_UNORM:
                case PixelFormat::RG8_UNORM:
                case PixelFormat::RGBA8_UNORM:
                case PixelFormat::RGBA16_UNORM:
                    return GL_UNSIGNED_BYTE;
                case PixelFormat::R8_SNORM:
                case PixelFormat::R16_SNORM:
                case PixelFormat::RG8_SNORM:
                case PixelFormat::RGBA8_SNORM:
                case PixelFormat::RGBA16_SNORM:
                    return GL_BYTE;
                case PixelFormat::R8_UINT:
                case PixelFormat::R16_UINT:
                case PixelFormat::R32_UINT:
                case PixelFormat::RG8_UINT:
                case PixelFormat::RGBA8_UINT:
                case PixelFormat::RGBA16_UINT:
                case PixelFormat::RGBA32_UINT:
                    return GL_UNSIGNED_INT;
                case PixelFormat::R8_SINT:
                case PixelFormat::R16_SINT:
                case PixelFormat::R32_SINT:
                case PixelFormat::RG8_SINT:
                case PixelFormat::RGBA8_SINT:
                case PixelFormat::RGBA16_SINT:
                case PixelFormat::RGBA32_SINT:
                    return GL_INT;
                case PixelFormat::R16_FLOAT:
                case PixelFormat::R32_FLOAT:
                case PixelFormat::RGBA16_FLOAT:
                case PixelFormat::RGBA32_FLOAT:
                    return GL_FLOAT;
                default:
                    return 0;
            }
        }

        static GLint getWrapMode(Texture::Address address)
        {
            switch (address)
            {
                case Texture::Address::CLAMP:
                    return GL_CLAMP_TO_EDGE;
                case Texture::Address::REPEAT:
                    return GL_REPEAT;
                case Texture::Address::MIRROR_REPEAT:
                    return GL_MIRRORED_REPEAT;
                default:
                    throw std::runtime_error("Invalid texture address mode");
            }
        }

        static GLenum getTextureType(Texture::Dimensions dimensions)
        {
            switch (dimensions)
            {
#if !OUZEL_SUPPORTS_OPENGLES
                case Texture::Dimensions::ONE: return GL_TEXTURE_1D;
#endif
                case Texture::Dimensions::TWO: return GL_TEXTURE_2D;
                case Texture::Dimensions::THREE: return GL_TEXTURE_3D;
                case Texture::Dimensions::CUBE: return GL_TEXTURE_CUBE_MAP;
                default: throw std::runtime_error("Invalid texture type");
            }
        }

        OGLTexture::OGLTexture(OGLRenderDevice& renderDeviceOGL,
                               const std::vector<Texture::Level>& newLevels,
                               uint32_t newFlags,
                               uint32_t newSampleCount,
                               PixelFormat newPixelFormat):
            OGLRenderResource(renderDeviceOGL),
            levels(newLevels),
            flags(newFlags),
            mipmaps(static_cast<uint32_t>(newLevels.size())),
            sampleCount(newSampleCount),
            pixelFormat(newPixelFormat)
        {
            if ((flags & Texture::RENDER_TARGET) && (mipmaps == 0 || mipmaps > 1))
                throw std::runtime_error("Invalid mip map count");

            createTexture();

            renderDevice.bindTexture(textureId, 0);

            if (flags & Texture::RENDER_TARGET)
            {
                clearMask = 0;
                if (clearColorBuffer) clearMask |= GL_COLOR_BUFFER_BIT;
                if (clearDepthBuffer) clearMask |= GL_DEPTH_BUFFER_BIT;

                frameBufferClearColor[0] = clearColor.normR();
                frameBufferClearColor[1] = clearColor.normG();
                frameBufferClearColor[2] = clearColor.normB();
                frameBufferClearColor[3] = clearColor.normA();
            }
            else
            {
                if (!levels.empty())
                {
                    if (renderDevice.isTextureBaseLevelSupported()) glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
                    if (renderDevice.isTextureMaxLevelSupported()) glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLsizei>(levels.size()) - 1);

                    GLenum error;

                    if ((error = glGetErrorProc()) != GL_NO_ERROR)
                        throw std::system_error(makeErrorCode(error), "Failed to set texture base and max levels");
                }

                for (size_t level = 0; level < levels.size(); ++level)
                {
                    if (!levels[level].data.empty())
                    {
                        glTexImage2DProc(GL_TEXTURE_2D, static_cast<GLint>(level), static_cast<GLint>(oglInternalPixelFormat),
                                         static_cast<GLsizei>(levels[level].size.v[0]),
                                         static_cast<GLsizei>(levels[level].size.v[1]), 0,
                                         oglPixelFormat, oglPixelType, levels[level].data.data());
                    }
                    else
                    {
                        glTexImage2DProc(GL_TEXTURE_2D, static_cast<GLint>(level), static_cast<GLint>(oglInternalPixelFormat),
                                         static_cast<GLsizei>(levels[level].size.v[0]),
                                         static_cast<GLsizei>(levels[level].size.v[1]), 0,
                                         oglPixelFormat, oglPixelType, nullptr);
                    }
                }

                GLenum error;

                if ((error = glGetErrorProc()) != GL_NO_ERROR)
                    throw std::system_error(makeErrorCode(error), "Failed to upload texture data");
            }

            setTextureParameters();
        }

        OGLTexture::~OGLTexture()
        {
            if (depthBufferId)
                renderDevice.deleteRenderBuffer(depthBufferId);

            if (colorBufferId)
                renderDevice.deleteRenderBuffer(colorBufferId);

            if (frameBufferId)
                renderDevice.deleteFrameBuffer(frameBufferId);

            if (depthTextureId)
                renderDevice.deleteTexture(depthTextureId);

            if (textureId)
                renderDevice.deleteTexture(textureId);
        }

        void OGLTexture::reload()
        {
            textureId = 0;
            depthTextureId = 0;
            frameBufferId = 0;
            colorBufferId = 0;
            depthBufferId = 0;

            createTexture();

            renderDevice.bindTexture(textureId, 0);

            if (!(flags & Texture::RENDER_TARGET))
            {
                if (!levels.empty())
                {
                    if (renderDevice.isTextureBaseLevelSupported()) glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
                    if (renderDevice.isTextureMaxLevelSupported()) glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLsizei>(levels.size()) - 1);

                    GLenum error;

                    if ((error = glGetErrorProc()) != GL_NO_ERROR)
                        throw std::system_error(makeErrorCode(error), "Failed to set texture base and max levels");
                }

                for (size_t level = 0; level < levels.size(); ++level)
                {
                    if (!levels[level].data.empty())
                    {
                        glTexImage2DProc(GL_TEXTURE_2D, static_cast<GLint>(level), static_cast<GLint>(oglInternalPixelFormat),
                                         static_cast<GLsizei>(levels[level].size.v[0]),
                                         static_cast<GLsizei>(levels[level].size.v[1]), 0,
                                         oglPixelFormat, oglPixelType, levels[level].data.data());
                    }
                    else
                    {
                        glTexImage2DProc(GL_TEXTURE_2D, static_cast<GLint>(level), static_cast<GLint>(oglInternalPixelFormat),
                                         static_cast<GLsizei>(levels[level].size.v[0]),
                                         static_cast<GLsizei>(levels[level].size.v[1]), 0,
                                         oglPixelFormat, oglPixelType, nullptr);
                    }
                }

                GLenum error;

                if ((error = glGetErrorProc()) != GL_NO_ERROR)
                    throw std::system_error(makeErrorCode(error), "Failed to upload texture data");
            }

            setTextureParameters();
        }

        void OGLTexture::setData(const std::vector<Texture::Level>& newLevels)
        {
            if (!(flags & Texture::DYNAMIC) || flags & Texture::RENDER_TARGET)
                throw std::runtime_error("Texture is not dynamic");

            levels = newLevels;

            if (!textureId)
                throw std::runtime_error("Texture not initialized");

            renderDevice.bindTexture(textureId, 0);

            if (!(flags & Texture::RENDER_TARGET))
            {
                for (size_t level = 0; level < levels.size(); ++level)
                {
                    if (!levels[level].data.empty())
                    {
                        glTexSubImage2DProc(GL_TEXTURE_2D, static_cast<GLint>(level), 0, 0,
                                            static_cast<GLsizei>(levels[level].size.v[0]),
                                            static_cast<GLsizei>(levels[level].size.v[1]),
                                            oglPixelFormat, oglPixelType,
                                            levels[level].data.data());
                    }
                }

                GLenum error;

                if ((error = glGetErrorProc()) != GL_NO_ERROR)
                    throw std::system_error(makeErrorCode(error), "Failed to upload texture data");
            }
        }

        void OGLTexture::setFilter(Texture::Filter newFilter)
        {
            filter = newFilter;

            if (!textureId)
                throw std::runtime_error("Texture not initialized");

            renderDevice.bindTexture(textureId, 0);

            Texture::Filter finalFilter = (filter == Texture::Filter::DEFAULT) ? renderDevice.getTextureFilter() : filter;

            switch (finalFilter)
            {
                case Texture::Filter::DEFAULT:
                case Texture::Filter::POINT:
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (levels.size() > 1) ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST);
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    break;
                case Texture::Filter::LINEAR:
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (levels.size() > 1) ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR);
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    break;
                case Texture::Filter::BILINEAR:
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (levels.size() > 1) ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR);
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    break;
                case Texture::Filter::TRILINEAR:
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (levels.size() > 1) ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    break;
                default:
                    throw std::runtime_error("Invalid texture filter");
            }

            GLenum error;

            if ((error = glGetErrorProc()) != GL_NO_ERROR)
                throw std::system_error(makeErrorCode(error), "Failed to set texture filter");
        }

        void OGLTexture::setAddressX(Texture::Address newAddressX)
        {
            addressX = newAddressX;

            if (!textureId)
                throw std::runtime_error("Texture not initialized");

            renderDevice.bindTexture(textureId, 0);
            glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, getWrapMode(addressX));

            GLenum error;
            if ((error = glGetErrorProc()) != GL_NO_ERROR)
                throw std::system_error(makeErrorCode(error), "Failed to set texture wrap mode");
        }

        void OGLTexture::setAddressY(Texture::Address newAddressY)
        {
            addressY = newAddressY;

            if (!textureId)
                throw std::runtime_error("Texture not initialized");

            renderDevice.bindTexture(textureId, 0);
            glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, getWrapMode(addressY));

            GLenum error;
            if ((error = glGetErrorProc()) != GL_NO_ERROR)
                throw std::system_error(makeErrorCode(error), "Failed to set texture wrap mode");
        }

        void OGLTexture::setMaxAnisotropy(uint32_t newMaxAnisotropy)
        {
            maxAnisotropy = newMaxAnisotropy;

            if (!textureId)
                throw std::runtime_error("Texture not initialized");

            renderDevice.bindTexture(textureId, 0);

            uint32_t finalMaxAnisotropy = (maxAnisotropy == 0) ? renderDevice.getMaxAnisotropy() : maxAnisotropy;

            if (finalMaxAnisotropy > 1 && renderDevice.isAnisotropicFilteringSupported())
            {
                glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<GLint>(finalMaxAnisotropy));

                GLenum error;

                if ((error = glGetErrorProc()) != GL_NO_ERROR)
                    throw std::system_error(makeErrorCode(error), "Failed to set texture max anisotrophy");
            }
        }

        void OGLTexture::setClearColorBuffer(bool clear)
        {
            clearColorBuffer = clear;

            if (clearColorBuffer)
                clearMask |= GL_COLOR_BUFFER_BIT;
            else
                clearMask &= ~static_cast<GLbitfield>(GL_COLOR_BUFFER_BIT);
        }

        void OGLTexture::setClearDepthBuffer(bool clear)
        {
            clearDepthBuffer = clear;

            if (clearDepthBuffer)
                clearMask |= GL_DEPTH_BUFFER_BIT;
            else
                clearMask &= ~static_cast<GLbitfield>(GL_DEPTH_BUFFER_BIT);
        }

        void OGLTexture::setClearColor(Color color)
        {
            clearColor = color;

            frameBufferClearColor[0] = clearColor.normR();
            frameBufferClearColor[1] = clearColor.normG();
            frameBufferClearColor[2] = clearColor.normB();
            frameBufferClearColor[3] = clearColor.normA();
        }

        void OGLTexture::setClearDepth(float newClearDepth)
        {
            clearDepth = newClearDepth;
        }

        void OGLTexture::createTexture()
        {
            if (depthBufferId)
            {
                renderDevice.deleteRenderBuffer(depthBufferId);
                depthBufferId = 0;
            }

            if (colorBufferId)
            {
                renderDevice.deleteRenderBuffer(colorBufferId);
                colorBufferId = 0;
            }

            if (frameBufferId)
            {
                renderDevice.deleteFrameBuffer(frameBufferId);
                frameBufferId = 0;
            }

            if (textureId)
            {
                renderDevice.deleteTexture(textureId);
                textureId = 0;
            }

            if (depthTextureId)
            {
                renderDevice.deleteTexture(depthTextureId);
                depthTextureId = 0;
            }

            glGenTexturesProc(1, &textureId);

            GLenum error;

            if ((error = glGetErrorProc()) != GL_NO_ERROR)
                throw std::system_error(makeErrorCode(error), "Failed to create texture");

            renderDevice.bindTexture(textureId, 0);

            width = static_cast<GLsizei>(levels.front().size.v[0]);
            height = static_cast<GLsizei>(levels.front().size.v[1]);

            oglInternalPixelFormat = getOGLInternalPixelFormat(pixelFormat, renderDevice.getAPIMajorVersion());

            if (oglInternalPixelFormat == GL_NONE)
                throw std::runtime_error("Invalid pixel format");

            oglPixelFormat = getOGLPixelFormat(pixelFormat);

            if (oglPixelFormat == GL_NONE)
                throw std::runtime_error("Invalid pixel format");

            oglPixelType = getOGLPixelType(pixelFormat);

            if (oglPixelType == GL_NONE)
                throw std::runtime_error("Invalid pixel format");

            if ((flags & Texture::RENDER_TARGET) && renderDevice.isRenderTargetsSupported())
            {
                glGenFramebuffersProc(1, &frameBufferId);

                if ((error = glGetErrorProc()) != GL_NO_ERROR)
                    throw std::system_error(makeErrorCode(error), "Failed to create frame buffer");

                renderDevice.bindFrameBuffer(frameBufferId);

                if (flags & Texture::BINDABLE_COLOR_BUFFER)
                {
                    renderDevice.bindTexture(textureId, 0);

                    glTexImage2DProc(GL_TEXTURE_2D, 0, static_cast<GLint>(oglInternalPixelFormat),
                                     width, height, 0,
                                     oglPixelFormat, oglPixelType, nullptr);

                    // TODO: blit multisample render buffer to texture
                    glFramebufferTexture2DProc(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);

                    if ((error = glGetErrorProc()) != GL_NO_ERROR)
                        throw std::system_error(makeErrorCode(error), "Failed to set frame buffer's color texture");
                }
                else
                {
                    glGenRenderbuffersProc(1, &colorBufferId);
                    glBindRenderbufferProc(GL_RENDERBUFFER, colorBufferId);

                    if (sampleCount > 1 && renderDevice.isMultisamplingSupported())
                    {
                        glRenderbufferStorageMultisampleProc(GL_RENDERBUFFER,
                                                             static_cast<GLsizei>(sampleCount),
                                                             oglInternalPixelFormat,
                                                             width, height);

                        if ((error = glGetErrorProc()) != GL_NO_ERROR)
                            throw std::system_error(makeErrorCode(error), "Failed to set color render buffer's multisample storage");
                    }
                    else
                    {
                        glRenderbufferStorageProc(GL_RENDERBUFFER, oglInternalPixelFormat,
                                                  width, height);

                        if ((error = glGetErrorProc()) != GL_NO_ERROR)
                            throw std::system_error(makeErrorCode(error), "Failed to set color render buffer's storage");
                    }

                    glFramebufferRenderbufferProc(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorBufferId);

                    if ((error = glGetErrorProc()) != GL_NO_ERROR)
                        throw std::system_error(makeErrorCode(error), "Failed to set frame buffer's color render buffer");
                }

                if (flags & Texture::DEPTH_BUFFER)
                {
                    if (flags & Texture::BINDABLE_DEPTH_BUFFER)
                    {
                        glGenTexturesProc(1, &depthTextureId);

                        renderDevice.bindTexture(depthTextureId, 0);

                        glTexImage2DProc(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24,
                                         width, height, 0,GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

                        glFramebufferTexture2DProc(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextureId, 0);

                        if ((error = glGetErrorProc()) != GL_NO_ERROR)
                            throw std::system_error(makeErrorCode(error), "Failed to set frame buffer's depth texture");
                    }
                    else
                    {
                        glGenRenderbuffersProc(1, &depthBufferId);
                        glBindRenderbufferProc(GL_RENDERBUFFER, depthBufferId);

                        if (sampleCount > 1 && renderDevice.isMultisamplingSupported())
                        {
                            glRenderbufferStorageMultisampleProc(GL_RENDERBUFFER,
                                                                 static_cast<GLsizei>(sampleCount),
                                                                 GL_DEPTH_COMPONENT24,
                                                                 width, height);

                            if ((error = glGetErrorProc()) != GL_NO_ERROR)
                                throw std::system_error(makeErrorCode(error), "Failed to set depth render buffer's multisample storage");
                        }
                        else
                        {
                            glRenderbufferStorageProc(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24,
                                                      width, height);

                            if ((error = glGetErrorProc()) != GL_NO_ERROR)
                                throw std::system_error(makeErrorCode(error), "Failed to set depth render buffer's storage");
                        }

                        glFramebufferRenderbufferProc(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferId);

                        if ((error = glGetErrorProc()) != GL_NO_ERROR)
                            throw std::system_error(makeErrorCode(error), "Failed to set frame buffer's depth render buffer");
                    }
                }

                GLenum status;
                if ((status = glCheckFramebufferStatusProc(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE)
                    throw std::runtime_error("Failed to create frame buffer, status: " + std::to_string(status));

                if ((error = glGetErrorProc()) != GL_NO_ERROR)
                    throw std::system_error(makeErrorCode(error), "Failed to check frame buffer status");
            }
        }

        void OGLTexture::setTextureParameters()
        {
            renderDevice.bindTexture(textureId, 0);

            Texture::Filter finalFilter = (filter == Texture::Filter::DEFAULT) ? renderDevice.getTextureFilter() : filter;

            switch (finalFilter)
            {
                case Texture::Filter::DEFAULT:
                case Texture::Filter::POINT:
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (levels.size() > 1) ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST);
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    break;
                case Texture::Filter::LINEAR:
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (levels.size() > 1) ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR);
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    break;
                case Texture::Filter::BILINEAR:
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (levels.size() > 1) ? GL_LINEAR_MIPMAP_NEAREST : GL_LINEAR);
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    break;
                case Texture::Filter::TRILINEAR:
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (levels.size() > 1) ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    break;
                default:
                    throw std::runtime_error("Invalid texture filter");
            }

            GLenum error;

            if ((error = glGetErrorProc()) != GL_NO_ERROR)
                throw std::system_error(makeErrorCode(error), "Failed to set texture filter");

            switch (addressX)
            {
                case Texture::Address::CLAMP:
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    break;
                case Texture::Address::REPEAT:
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    break;
                case Texture::Address::MIRROR_REPEAT:
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
                    break;
                default:
                    throw std::runtime_error("Invalid texture address mode");
            }

            if ((error = glGetErrorProc()) != GL_NO_ERROR)
                throw std::system_error(makeErrorCode(error), "Failed to set texture wrap mode");

            switch (addressY)
            {
                case Texture::Address::CLAMP:
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                    break;
                case Texture::Address::REPEAT:
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    break;
                case Texture::Address::MIRROR_REPEAT:
                    glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
                    break;
                default:
                    throw std::runtime_error("Invalid texture address mode");
            }

            if ((error = glGetErrorProc()) != GL_NO_ERROR)
                throw std::system_error(makeErrorCode(error), "Failed to set texture wrap mode");

            uint32_t finalMaxAnisotropy = (maxAnisotropy == 0) ? renderDevice.getMaxAnisotropy() : maxAnisotropy;

            if (finalMaxAnisotropy > 1 && renderDevice.isAnisotropicFilteringSupported())
            {
                glTexParameteriProc(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, static_cast<GLint>(finalMaxAnisotropy));

                if ((error = glGetErrorProc()) != GL_NO_ERROR)
                    throw std::system_error(makeErrorCode(error), "Failed to set texture max anisotrophy");
            }
        }
    } // namespace graphics
} // namespace ouzel

#endif
