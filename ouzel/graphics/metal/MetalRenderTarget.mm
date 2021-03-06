// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#include "core/Setup.h"

#if OUZEL_COMPILE_METAL

#include "MetalRenderTarget.hpp"
#include "MetalRenderDevice.hpp"

namespace ouzel
{
    namespace graphics
    {
        MetalRenderTarget::MetalRenderTarget(MetalRenderDevice& renderDeviceMetal):
            MetalRenderResource(renderDeviceMetal)
        {
        }
    } // namespace graphics
} // namespace ouzel

#endif
