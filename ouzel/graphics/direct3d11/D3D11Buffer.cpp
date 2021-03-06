// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#include "core/Setup.h"

#if OUZEL_COMPILE_DIRECT3D11

#include "D3D11Buffer.hpp"
#include "D3D11RenderDevice.hpp"

namespace ouzel
{
    namespace graphics
    {
        D3D11Buffer::D3D11Buffer(D3D11RenderDevice& renderDeviceD3D11,
                                 Buffer::Usage newUsage, uint32_t newFlags,
                                 const std::vector<uint8_t>& data,
                                 uint32_t newSize):
            D3D11RenderResource(renderDeviceD3D11),
            usage(newUsage),
            flags(newFlags),
            size(static_cast<UINT>(newSize))
        {
            createBuffer(newSize, data);
        }

        D3D11Buffer::~D3D11Buffer()
        {
            if (buffer) buffer->Release();
        }

        void D3D11Buffer::setData(const std::vector<uint8_t>& data)
        {
            if (!(flags & Buffer::DYNAMIC))
                throw std::runtime_error("Buffer is not dynamic");

            if (data.empty())
                throw std::runtime_error("Data is empty");

            if (!buffer || data.size() > size)
                createBuffer(static_cast<UINT>(data.size()), data);
            else
            {
                if (!data.empty())
                {
                    D3D11_MAPPED_SUBRESOURCE mappedSubresource;
                    mappedSubresource.pData = nullptr;
                    mappedSubresource.RowPitch = 0;
                    mappedSubresource.DepthPitch = 0;

                    HRESULT hr;
                    if (FAILED(hr = renderDevice.getContext()->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubresource)))
                        throw std::system_error(hr, direct3D11ErrorCategory, "Failed to lock Direct3D 11 buffer");

                    std::copy(data.begin(), data.end(), static_cast<uint8_t*>(mappedSubresource.pData));

                    renderDevice.getContext()->Unmap(buffer, 0);
                }
            }
        }

        void D3D11Buffer::createBuffer(UINT newSize, const std::vector<uint8_t>& data)
        {
            if (buffer)
            {
                buffer->Release();
                buffer = nullptr;
            }

            if (newSize)
            {
                size = newSize;

                D3D11_BUFFER_DESC bufferDesc;
                bufferDesc.ByteWidth = size;
                bufferDesc.Usage = (flags & Texture::DYNAMIC) ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_IMMUTABLE;

                switch (usage)
                {
                    case Buffer::Usage::INDEX:
                        bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
                        break;
                    case Buffer::Usage::VERTEX:
                        bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                        break;
                    default:
                        throw std::runtime_error("Unsupported buffer type");
                }

                bufferDesc.CPUAccessFlags = (flags & Texture::DYNAMIC) ? D3D11_CPU_ACCESS_WRITE : 0;
                bufferDesc.MiscFlags = 0;
                bufferDesc.StructureByteStride = 0;

                HRESULT hr;

                if (data.empty())
                {
                    if (FAILED(hr = renderDevice.getDevice()->CreateBuffer(&bufferDesc, nullptr, &buffer)))
                        throw std::system_error(hr, direct3D11ErrorCategory, "Failed to create Direct3D 11 buffer");
                }
                else
                {
                    D3D11_SUBRESOURCE_DATA bufferResourceData;
                    bufferResourceData.pSysMem = data.data();
                    bufferResourceData.SysMemPitch = 0;
                    bufferResourceData.SysMemSlicePitch = 0;

                    if (FAILED(hr = renderDevice.getDevice()->CreateBuffer(&bufferDesc, &bufferResourceData, &buffer)))
                        throw std::system_error(hr, direct3D11ErrorCategory, "Failed to create Direct3D 11 buffer");
                }
            }
        }
    } // namespace graphics
} // namespace ouzel

#endif
