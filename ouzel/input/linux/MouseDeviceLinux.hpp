// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_INPUT_MOUSEDEVICELINUX_HPP
#define OUZEL_INPUT_MOUSEDEVICELINUX_HPP

#include "input/MouseDevice.hpp"

namespace ouzel
{
    namespace input
    {
        class CursorLinux;

        class MouseDeviceLinux final: public MouseDevice
        {
        public:
            MouseDeviceLinux(InputSystem& initInputSystem,
                             uint32_t initId):
                MouseDevice(initInputSystem, initId)
            {
            }

            void setPosition(const Vector2<float>& position);
            bool isCursorVisible() const { return cursorVisible; }
            void setCursorVisible(bool visible);
            void setCursorLocked(bool locked);

            CursorLinux* getCursor() const { return cursor; }
            void setCursor(CursorLinux* newCursor);

        private:
            CursorLinux* cursor = nullptr;
            bool cursorVisible = true;
        };
    } // namespace input
} // namespace ouzel

#endif // OUZEL_INPUT_MOUSEDEVICELINUX_HPP
