// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_AUDIO_AUDIODEVICEALSA_HPP
#define OUZEL_AUDIO_AUDIODEVICEALSA_HPP

#include "core/Setup.h"

#if OUZEL_COMPILE_ALSA

#include <atomic>
#include <thread>
#include <alsa/asoundlib.h>

#include "audio/AudioDevice.hpp"

namespace ouzel
{
    namespace audio
    {
        class ALSAAudioDevice final: public AudioDevice
        {
        public:
            explicit ALSAAudioDevice(mixer::Mixer& initMixer);
            ~ALSAAudioDevice();

        private:
            void run();

            snd_pcm_t* playbackHandle = nullptr;
            snd_pcm_hw_params_t* hwParams = nullptr;
            snd_pcm_sw_params_t* swParams = nullptr;

            unsigned int periods = 4;
            snd_pcm_uframes_t periodSize = 1024;

            std::vector<uint8_t> data;

            std::atomic_bool running{false};
            std::thread audioThread;
        };
    } // namespace audio
} // namespace ouzel

#endif

#endif // OUZEL_AUDIO_AUDIODEVICEALSA_HPP
