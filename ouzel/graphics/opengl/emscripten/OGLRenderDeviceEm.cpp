// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#include "core/Setup.h"

#if defined(__EMSCRIPTEN__) && OUZEL_COMPILE_OPENGL

#include "OGLRenderDeviceEm.hpp"
#include "utils/Utils.hpp"

namespace ouzel
{
    namespace graphics
    {
        OGLRenderDeviceEm::OGLRenderDeviceEm(const std::function<void(const Event&)>& initCallback):
            OGLRenderDevice(initCallback)
        {
        }

        OGLRenderDeviceEm::~OGLRenderDeviceEm()
        {
            if (webGLContext)
                emscripten_webgl_destroy_context(webGLContext);
        }

        void OGLRenderDeviceEm::init(Window* newWindow,
                                     const Size2<uint32_t>& newSize,
                                     uint32_t newSampleCount,
                                     Texture::Filter newTextureFilter,
                                     uint32_t newMaxAnisotropy,
                                     bool newVerticalSync,
                                     bool newDepth,
                                     bool newDebugRenderer)
        {
            apiMajorVersion = 2;
            apiMinorVersion = 0;

            EmscriptenWebGLContextAttributes attrs;
            emscripten_webgl_init_context_attributes(&attrs);

            attrs.alpha = true;
            attrs.depth = newDepth;
            attrs.stencil = false;
            attrs.antialias = newSampleCount > 0;

            webGLContext = emscripten_webgl_create_context(0, &attrs);

            if (!webGLContext)
                throw std::runtime_error("Failed to create WebGL context");

            EMSCRIPTEN_RESULT result = emscripten_webgl_make_context_current(webGLContext);

            if (result != EMSCRIPTEN_RESULT_SUCCESS)
                throw std::runtime_error("Failed to make WebGL context current");

            emscripten_set_main_loop_timing(newVerticalSync ? EM_TIMING_RAF : EM_TIMING_SETTIMEOUT, 1);

            OGLRenderDevice::init(newWindow,
                                  newSize,
                                  newSampleCount,
                                  newTextureFilter,
                                  newMaxAnisotropy,
                                  newVerticalSync,
                                  newDepth,
                                  newDebugRenderer);
        }
    } // namespace graphics
} // namespace ouzel

#endif
