// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#include "Listener.hpp"
#include "Audio.hpp"
#include "AudioDevice.hpp"
#include "Submix.hpp"
#include "scene/Actor.hpp"
#include "math/MathUtils.hpp"

namespace ouzel
{
    namespace audio
    {
        Listener::Listener(Audio& initAudio):
            scene::Component(scene::Component::LISTENER),
            audio(initAudio)
        {
        }

        Listener::~Listener()
        {
            if (mix) mix->removeListener(this);
        }

        void Listener::setMix(Mix* newMix)
        {
            if (mix) mix->removeListener(this);
            mix = newMix;
            if (mix) mix->addListener(this);
        }

        void Listener::updateTransform()
        {
            transformDirty = true;
        }
    } // namespace audio
} // namespace ouzel
