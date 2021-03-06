// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GRAPHICS_RENDERTARGET_HPP
#define OUZEL_GRAPHICS_RENDERTARGET_HPP

#include <memory>
#include "math/Color.hpp"
#include "math/Size2.hpp"

namespace ouzel
{
    namespace graphics
    {
        class Renderer;

        class RenderTarget final
        {
        public:
            enum Flags
            {
                COLOR_BUFFER = 0x01,
                DEPTH_BUFFER = 0x02,
                BINDABLE_COLOR_BUFFER = 0x04,
                BINDABLE_DEPTH_BUFFER = 0x08,
            };

            explicit RenderTarget(Renderer& initRenderer);
            ~RenderTarget();

            inline uintptr_t getResource() const { return resource; }
            inline uintptr_t getColorTextureResource() const { return colorTexture; }
            inline uintptr_t getDepthTextureResource() const { return depthTexture; }

            inline const Size2<float>& getSize() const { return size; }

            inline bool getClearColorBuffer() const { return clearColorBuffer; }
            void setClearColorBuffer(bool clear);

            inline bool getClearDepthBuffer() const { return clearDepthBuffer; }
            void setClearDepthBuffer(bool clear);

            inline Color getClearColor() const { return clearColor; }
            void setClearColor(Color color);

            inline float getClearDepth() const { return clearDepth; }
            void setClearDepth(float clear);

        private:
            Renderer& renderer;
            uintptr_t resource = 0;
            uintptr_t colorTexture = 0;
            uintptr_t depthTexture = 0;

            Size2<float> size;
            bool clearColorBuffer = true;
            bool clearDepthBuffer = false;
            Color clearColor;
            float clearDepth = 1.0F;
        };
    } // namespace graphics
} // namespace ouzel

#endif // OUZEL_GRAPHICS_RENDERTARGET_HPP
