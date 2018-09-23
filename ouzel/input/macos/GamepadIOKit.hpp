// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#pragma once

#include <unordered_map>
#include <IOKit/hid/IOHIDManager.h>

#include "input/macos/GamepadMacOS.hpp"
#include "input/Gamepad.hpp"

namespace ouzel
{
    namespace input
    {
        class GamepadIOKit: public GamepadMacOS
        {
        public:
            explicit GamepadIOKit(InputSystemMacOS& initInputSystemMacOS,
                                  uint32_t initDeviceId,
                                  IOHIDDeviceRef initDevice);

            inline IOHIDDeviceRef getDevice() const { return device; }

            void handleInput(IOHIDValueRef value);

        private:
            void handleThumbAxisChange(int64_t oldValue, int64_t newValue,
                                       int64_t min, int64_t max,
                                       Gamepad::Button negativeButton, Gamepad::Button positiveButton);

            int32_t vendorId = 0;
            int32_t productId = 0;

            IOHIDDeviceRef device = nullptr;

            struct Element
            {
                IOHIDElementRef element = nullptr;
                uint32_t type = 0;
                uint32_t usagePage = 0;
                uint32_t usage = 0;
                int64_t min = 0;
                int64_t max = 0;
                int64_t value = 0;
                Gamepad::Button button = Gamepad::Button::NONE;
            };

            std::unordered_map<IOHIDElementRef, Element> elements;

            IOHIDElementRef leftThumbX = nullptr;
            IOHIDElementRef leftThumbY = nullptr;
            IOHIDElementRef leftTrigger = nullptr;
            IOHIDElementRef rightThumbX = nullptr;
            IOHIDElementRef rightThumbY = nullptr;
            IOHIDElementRef rightTrigger = nullptr;
        };
    } // namespace input
} // namespace ouzel
