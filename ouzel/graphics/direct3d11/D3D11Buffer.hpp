// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_GRAPHICS_D3D11BUFFER_HPP
#define OUZEL_GRAPHICS_D3D11BUFFER_HPP

#include "core/Setup.h"

#if OUZEL_COMPILE_DIRECT3D11

#include <d3d11.h>
#include "graphics/direct3d11/D3D11RenderResource.hpp"
#include "graphics/Buffer.hpp"

namespace ouzel
{
    namespace graphics
    {
        class D3D11RenderDevice;

        class D3D11Buffer final: public D3D11RenderResource
        {
        public:
            D3D11Buffer(D3D11RenderDevice& renderDeviceD3D11,
                        Buffer::Usage newUsage, uint32_t newFlags,
                        const std::vector<uint8_t>& data,
                        uint32_t newSize);
            ~D3D11Buffer();

            void setData(const std::vector<uint8_t>& data);

            inline uint32_t getFlags() const { return flags; }
            inline Buffer::Usage getUsage() const { return usage; }
            inline UINT getSize() const { return size; }

            ID3D11Buffer* getBuffer() const { return buffer; }

        private:
            void createBuffer(UINT newSize, const std::vector<uint8_t>& data);

            Buffer::Usage usage;
            uint32_t flags = 0;

            ID3D11Buffer* buffer = nullptr;
            UINT size = 0;
        };
    } // namespace graphics
} // namespace ouzel

#endif

#endif // OUZEL_GRAPHICS_D3D11BUFFER_HPP
