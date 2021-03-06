MAKEFILE_PATH:=$(abspath $(lastword $(MAKEFILE_LIST)))
ROOT_DIR:=$(realpath $(dir $(MAKEFILE_PATH)))
ifeq ($(OS),Windows_NT)
platform=windows
else
architecture=$(shell uname -m)
os=$(shell uname -s)
ifeq ($(os),Linux)
platform=linux
else ifeq ($(os),Darwin)
platform=macos
endif

endif
ifeq ($(platform),emscripten)
CC=emcc
CXX=em++
AR=emar
endif
CXXFLAGS=-c -std=c++11 -Wall \
	-I"$(ROOT_DIR)/../ouzel" \
	-I"$(ROOT_DIR)/../shaders" \
	-I"$(ROOT_DIR)/../external/khronos" \
	-I"$(ROOT_DIR)/../external/smbPitchShift" \
	-I"$(ROOT_DIR)/../external/stb"
CFLAGS=-c -Wall \
	-I"$(ROOT_DIR)/../ouzel"
SOURCES=$(ROOT_DIR)/../ouzel/animators/Animator.cpp \
	$(ROOT_DIR)/../ouzel/animators/Ease.cpp \
	$(ROOT_DIR)/../ouzel/animators/Fade.cpp \
	$(ROOT_DIR)/../ouzel/animators/Move.cpp \
	$(ROOT_DIR)/../ouzel/animators/Parallel.cpp \
	$(ROOT_DIR)/../ouzel/animators/Repeat.cpp \
	$(ROOT_DIR)/../ouzel/animators/Rotate.cpp \
	$(ROOT_DIR)/../ouzel/animators/Scale.cpp \
	$(ROOT_DIR)/../ouzel/animators/Sequence.cpp \
	$(ROOT_DIR)/../ouzel/animators/Shake.cpp \
	$(ROOT_DIR)/../ouzel/assets/BmfLoader.cpp \
	$(ROOT_DIR)/../ouzel/assets/Bundle.cpp \
	$(ROOT_DIR)/../ouzel/assets/Cache.cpp \
	$(ROOT_DIR)/../ouzel/assets/ColladaLoader.cpp \
	$(ROOT_DIR)/../ouzel/assets/GltfLoader.cpp \
	$(ROOT_DIR)/../ouzel/assets/ImageLoader.cpp \
	$(ROOT_DIR)/../ouzel/assets/Loader.cpp \
	$(ROOT_DIR)/../ouzel/assets/MtlLoader.cpp \
	$(ROOT_DIR)/../ouzel/assets/ObjLoader.cpp \
	$(ROOT_DIR)/../ouzel/assets/ParticleSystemLoader.cpp \
	$(ROOT_DIR)/../ouzel/assets/SpriteLoader.cpp \
	$(ROOT_DIR)/../ouzel/assets/TtfLoader.cpp \
	$(ROOT_DIR)/../ouzel/assets/VorbisLoader.cpp \
	$(ROOT_DIR)/../ouzel/assets/WaveLoader.cpp \
	$(ROOT_DIR)/../ouzel/audio/empty/EmptyAudioDevice.cpp \
	$(ROOT_DIR)/../ouzel/audio/mixer/Bus.cpp \
	$(ROOT_DIR)/../ouzel/audio/mixer/Mixer.cpp \
	$(ROOT_DIR)/../ouzel/audio/mixer/Processor.cpp \
	$(ROOT_DIR)/../ouzel/audio/mixer/Source.cpp \
	$(ROOT_DIR)/../ouzel/audio/mixer/SourceData.cpp \
	$(ROOT_DIR)/../ouzel/audio/Audio.cpp \
	$(ROOT_DIR)/../ouzel/audio/AudioDevice.cpp \
	$(ROOT_DIR)/../ouzel/audio/Containers.cpp \
	$(ROOT_DIR)/../ouzel/audio/Filter.cpp \
	$(ROOT_DIR)/../ouzel/audio/Filters.cpp \
	$(ROOT_DIR)/../ouzel/audio/Listener.cpp \
	$(ROOT_DIR)/../ouzel/audio/Mix.cpp \
	$(ROOT_DIR)/../ouzel/audio/OscillatorSound.cpp \
	$(ROOT_DIR)/../ouzel/audio/PCMSound.cpp \
	$(ROOT_DIR)/../ouzel/audio/SilenceSound.cpp \
	$(ROOT_DIR)/../ouzel/audio/Sound.cpp \
	$(ROOT_DIR)/../ouzel/audio/SoundCue.cpp \
	$(ROOT_DIR)/../ouzel/audio/Source.cpp \
	$(ROOT_DIR)/../ouzel/audio/Submix.cpp \
	$(ROOT_DIR)/../ouzel/audio/Voice.cpp \
	$(ROOT_DIR)/../ouzel/audio/VorbisSound.cpp \
	$(ROOT_DIR)/../ouzel/core/Engine.cpp \
	$(ROOT_DIR)/../ouzel/core/System.cpp \
	$(ROOT_DIR)/../ouzel/core/NativeWindow.cpp \
	$(ROOT_DIR)/../ouzel/core/Timer.cpp \
	$(ROOT_DIR)/../ouzel/core/Window.cpp \
	$(ROOT_DIR)/../ouzel/events/EventDispatcher.cpp \
	$(ROOT_DIR)/../ouzel/events/EventHandler.cpp \
	$(ROOT_DIR)/../ouzel/files/Archive.cpp \
	$(ROOT_DIR)/../ouzel/files/File.cpp \
	$(ROOT_DIR)/../ouzel/files/FileSystem.cpp \
	$(ROOT_DIR)/../ouzel/graphics/empty/EmptyRenderDevice.cpp \
	$(ROOT_DIR)/../ouzel/graphics/opengl/OGLBlendState.cpp \
	$(ROOT_DIR)/../ouzel/graphics/opengl/OGLBuffer.cpp \
	$(ROOT_DIR)/../ouzel/graphics/opengl/OGLDepthStencilState.cpp \
	$(ROOT_DIR)/../ouzel/graphics/opengl/OGLRenderDevice.cpp \
	$(ROOT_DIR)/../ouzel/graphics/opengl/OGLRenderTarget.cpp \
	$(ROOT_DIR)/../ouzel/graphics/opengl/OGLShader.cpp \
	$(ROOT_DIR)/../ouzel/graphics/opengl/OGLTexture.cpp \
	$(ROOT_DIR)/../ouzel/graphics/BlendState.cpp \
	$(ROOT_DIR)/../ouzel/graphics/Buffer.cpp \
	$(ROOT_DIR)/../ouzel/graphics/DepthStencilState.cpp \
	$(ROOT_DIR)/../ouzel/graphics/ImageData.cpp \
	$(ROOT_DIR)/../ouzel/graphics/Material.cpp \
	$(ROOT_DIR)/../ouzel/graphics/Renderer.cpp \
	$(ROOT_DIR)/../ouzel/graphics/RenderDevice.cpp \
	$(ROOT_DIR)/../ouzel/graphics/RenderTarget.cpp \
	$(ROOT_DIR)/../ouzel/graphics/Shader.cpp \
	$(ROOT_DIR)/../ouzel/graphics/Texture.cpp \
	$(ROOT_DIR)/../ouzel/graphics/Vertex.cpp \
	$(ROOT_DIR)/../ouzel/gui/BMFont.cpp \
	$(ROOT_DIR)/../ouzel/gui/Button.cpp \
	$(ROOT_DIR)/../ouzel/gui/CheckBox.cpp \
	$(ROOT_DIR)/../ouzel/gui/ComboBox.cpp \
	$(ROOT_DIR)/../ouzel/gui/EditBox.cpp \
	$(ROOT_DIR)/../ouzel/gui/Font.cpp \
	$(ROOT_DIR)/../ouzel/gui/Label.cpp \
	$(ROOT_DIR)/../ouzel/gui/Menu.cpp \
	$(ROOT_DIR)/../ouzel/gui/RadioButton.cpp \
	$(ROOT_DIR)/../ouzel/gui/RadioButtonGroup.cpp \
	$(ROOT_DIR)/../ouzel/gui/ScrollArea.cpp \
	$(ROOT_DIR)/../ouzel/gui/ScrollBar.cpp \
	$(ROOT_DIR)/../ouzel/gui/SlideBar.cpp \
	$(ROOT_DIR)/../ouzel/gui/TTFont.cpp \
	$(ROOT_DIR)/../ouzel/gui/Widget.cpp \
	$(ROOT_DIR)/../ouzel/input/Cursor.cpp \
	$(ROOT_DIR)/../ouzel/input/Gamepad.cpp \
	$(ROOT_DIR)/../ouzel/input/GamepadDevice.cpp \
	$(ROOT_DIR)/../ouzel/input/InputDevice.cpp \
	$(ROOT_DIR)/../ouzel/input/InputManager.cpp \
	$(ROOT_DIR)/../ouzel/input/InputSystem.cpp \
	$(ROOT_DIR)/../ouzel/input/Keyboard.cpp \
	$(ROOT_DIR)/../ouzel/input/KeyboardDevice.cpp \
	$(ROOT_DIR)/../ouzel/input/Mouse.cpp \
	$(ROOT_DIR)/../ouzel/input/MouseDevice.cpp \
	$(ROOT_DIR)/../ouzel/input/Touchpad.cpp \
	$(ROOT_DIR)/../ouzel/input/TouchpadDevice.cpp \
	$(ROOT_DIR)/../ouzel/localization/Language.cpp \
	$(ROOT_DIR)/../ouzel/localization/Localization.cpp \
	$(ROOT_DIR)/../ouzel/math/Box2.cpp \
	$(ROOT_DIR)/../ouzel/math/Box3.cpp \
	$(ROOT_DIR)/../ouzel/math/Color.cpp \
	$(ROOT_DIR)/../ouzel/math/MathUtils.cpp \
	$(ROOT_DIR)/../ouzel/math/Matrix4.cpp \
	$(ROOT_DIR)/../ouzel/math/Size2.cpp \
	$(ROOT_DIR)/../ouzel/math/Size3.cpp \
	$(ROOT_DIR)/../ouzel/math/Vector2.cpp \
	$(ROOT_DIR)/../ouzel/math/Vector3.cpp \
	$(ROOT_DIR)/../ouzel/math/Vector4.cpp \
	$(ROOT_DIR)/../ouzel/network/Client.cpp \
	$(ROOT_DIR)/../ouzel/network/Network.cpp \
	$(ROOT_DIR)/../ouzel/network/Socket.cpp \
	$(ROOT_DIR)/../ouzel/scene/Actor.cpp \
	$(ROOT_DIR)/../ouzel/scene/ActorContainer.cpp \
	$(ROOT_DIR)/../ouzel/scene/Camera.cpp \
	$(ROOT_DIR)/../ouzel/scene/Component.cpp \
	$(ROOT_DIR)/../ouzel/scene/Layer.cpp \
	$(ROOT_DIR)/../ouzel/scene/Light.cpp \
	$(ROOT_DIR)/../ouzel/scene/ParticleSystem.cpp \
	$(ROOT_DIR)/../ouzel/scene/ParticleSystemData.cpp \
	$(ROOT_DIR)/../ouzel/scene/Scene.cpp \
	$(ROOT_DIR)/../ouzel/scene/SceneManager.cpp \
	$(ROOT_DIR)/../ouzel/scene/ShapeRenderer.cpp \
	$(ROOT_DIR)/../ouzel/scene/SkinnedMeshData.cpp \
	$(ROOT_DIR)/../ouzel/scene/SkinnedMeshRenderer.cpp \
	$(ROOT_DIR)/../ouzel/scene/Sprite.cpp \
	$(ROOT_DIR)/../ouzel/scene/SpriteData.cpp \
	$(ROOT_DIR)/../ouzel/scene/StaticMeshData.cpp \
	$(ROOT_DIR)/../ouzel/scene/StaticMeshRenderer.cpp \
	$(ROOT_DIR)/../ouzel/scene/TextRenderer.cpp \
	$(ROOT_DIR)/../ouzel/utils/Log.cpp \
	$(ROOT_DIR)/../ouzel/utils/OBF.cpp \
	$(ROOT_DIR)/../ouzel/utils/Utils.cpp \
	$(ROOT_DIR)/../ouzel/utils/XML.cpp
ifeq ($(platform),windows)
SOURCES+=$(ROOT_DIR)/../ouzel/audio/dsound/DSAudioDevice.cpp \
	$(ROOT_DIR)/../ouzel/core/windows/EngineWin.cpp \
	$(ROOT_DIR)/../ouzel/core/windows/main.cpp \
	$(ROOT_DIR)/../ouzel/core/windows/NativeWindowWin.cpp \
	$(ROOT_DIR)/../ouzel/core/windows/SystemWin.cpp \
	$(ROOT_DIR)/../ouzel/graphics/direct3d11/D3D11BlendState.cpp \
	$(ROOT_DIR)/../ouzel/graphics/direct3d11/D3D11Buffer.cpp \
	$(ROOT_DIR)/../ouzel/graphics/direct3d11/D3D11DepthStencilState.cpp \
	$(ROOT_DIR)/../ouzel/graphics/direct3d11/D3D11RenderDevice.cpp \
	$(ROOT_DIR)/../ouzel/graphics/direct3d11/D3D11Shader.cpp \
	$(ROOT_DIR)/../ouzel/graphics/direct3d11/D3D11Texture.cpp \
	$(ROOT_DIR)/../ouzel/graphics/opengl/windows/OGLRenderDeviceWin.cpp \
	$(ROOT_DIR)/../ouzel/input/windows/GamepadDeviceDI.cpp \
	$(ROOT_DIR)/../ouzel/input/windows/GamepadDeviceXI.cpp \
	$(ROOT_DIR)/../ouzel/input/windows/InputSystemWin.cpp \
	$(ROOT_DIR)/../ouzel/input/windows/KeyboardDeviceWin.cpp \
	$(ROOT_DIR)/../ouzel/input/windows/MouseDeviceWin.cpp \
	$(ROOT_DIR)/../ouzel/input/windows/CursorWin.cpp
CXXFLAGS+=-DWINVER=0x0601 -D_WIN32_WINNT=0x0601
else ifeq ($(platform),linux)
SOURCES+=$(ROOT_DIR)/../ouzel/audio/alsa/ALSAAudioDevice.cpp \
	$(ROOT_DIR)/../ouzel/audio/openal/OALAudioDevice.cpp \
	$(ROOT_DIR)/../ouzel/core/linux/EngineLinux.cpp \
	$(ROOT_DIR)/../ouzel/core/linux/main.cpp \
	$(ROOT_DIR)/../ouzel/core/linux/NativeWindowLinux.cpp \
	$(ROOT_DIR)/../ouzel/core/linux/SystemLinux.cpp \
	$(ROOT_DIR)/../ouzel/graphics/opengl/linux/OGLRenderDeviceLinux.cpp \
	$(ROOT_DIR)/../ouzel/input/linux/EventDevice.cpp \
	$(ROOT_DIR)/../ouzel/input/linux/InputSystemLinux.cpp \
	$(ROOT_DIR)/../ouzel/input/linux/KeyboardDeviceLinux.cpp \
	$(ROOT_DIR)/../ouzel/input/linux/MouseDeviceLinux.cpp \
	$(ROOT_DIR)/../ouzel/input/linux/CursorLinux.cpp
ifneq ($(filter arm%,$(architecture)),) # ARM Linux
CXXFLAGS+=-I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host/linux
endif
else ifeq ($(platform),macos)
SOURCES+=$(ROOT_DIR)/../ouzel/audio/coreaudio/CAAudioDevice.cpp \
	$(ROOT_DIR)/../ouzel/audio/openal/OALAudioDevice.cpp \
	$(ROOT_DIR)/../ouzel/core/macos/EngineMacOS.mm \
	$(ROOT_DIR)/../ouzel/core/macos/main.cpp \
	$(ROOT_DIR)/../ouzel/core/macos/NativeWindowMacOS.mm \
	$(ROOT_DIR)/../ouzel/core/macos/SystemMacOS.mm \
	$(ROOT_DIR)/../ouzel/core/macos/ViewMacOS.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/macos/MetalView.m \
	$(ROOT_DIR)/../ouzel/graphics/metal/macos/MetalRenderDeviceMacOS.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalBlendState.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalBuffer.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalDepthStencilState.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalRenderDevice.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalRenderTarget.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalShader.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalTexture.mm \
	$(ROOT_DIR)/../ouzel/graphics/opengl/macos/OGLRenderDeviceMacOS.mm \
	$(ROOT_DIR)/../ouzel/graphics/opengl/macos/OpenGLView.m \
	$(ROOT_DIR)/../ouzel/input/macos/GamepadDeviceGC.mm \
	$(ROOT_DIR)/../ouzel/input/macos/GamepadDeviceIOKit.cpp \
	$(ROOT_DIR)/../ouzel/input/macos/InputSystemMacOS.mm \
	$(ROOT_DIR)/../ouzel/input/macos/MouseDeviceMacOS.mm \
	$(ROOT_DIR)/../ouzel/input/macos/CursorMacOS.cpp
else ifeq ($(platform),ios)
SOURCES+=$(ROOT_DIR)/../ouzel/audio/coreaudio/CAAudioDevice.cpp \
	$(ROOT_DIR)/../ouzel/audio/openal/OALAudioDevice.cpp \
	$(ROOT_DIR)/../ouzel/core/ios/DisplayLink.mm \
	$(ROOT_DIR)/../ouzel/core/ios/EngineIOS.mm \
	$(ROOT_DIR)/../ouzel/core/ios/main.cpp \
	$(ROOT_DIR)/../ouzel/core/ios/NativeWindowIOS.mm \
	$(ROOT_DIR)/../ouzel/core/ios/SystemIOS.mm \
	$(ROOT_DIR)/../ouzel/core/ios/ViewIOS.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/ios/MetalView.m \
	$(ROOT_DIR)/../ouzel/graphics/metal/ios/MetalRenderDeviceIOS.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalBlendState.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalBuffer.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalDepthStencilState.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalRenderDevice.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalRenderTarget.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalShader.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalTexture.mm \
	$(ROOT_DIR)/../ouzel/graphics/opengl/ios/OGLRenderDeviceIOS.mm \
	$(ROOT_DIR)/../ouzel/graphics/opengl/ios/OpenGLView.m \
	$(ROOT_DIR)/../ouzel/input/ios/GamepadDeviceIOS.mm \
	$(ROOT_DIR)/../ouzel/input/ios/InputSystemIOS.mm
CFLAGS+=-arch arm64 -isysroot $(shell xcrun --sdk iphoneos --show-sdk-path) -miphoneos-version-min=8.0
CXXFLAGS+=-arch arm64 -isysroot $(shell xcrun --sdk iphoneos --show-sdk-path) -miphoneos-version-min=8.0
else ifeq ($(platform),tvos)
SOURCES+=$(ROOT_DIR)/../ouzel/audio/coreaudio/CAAudioDevice.cpp \
	$(ROOT_DIR)/../ouzel/audio/openal/OALAudioDevice.cpp \
	$(ROOT_DIR)/../ouzel/core/tvos/DisplayLink.mm \
	$(ROOT_DIR)/../ouzel/core/tvos/EngineTVOS.mm \
	$(ROOT_DIR)/../ouzel/core/tvos/main.cpp \
	$(ROOT_DIR)/../ouzel/core/tvos/NativeWindowTVOS.mm \
	$(ROOT_DIR)/../ouzel/core/tvos/SystemTVOS.mm \
	$(ROOT_DIR)/../ouzel/core/tvos/ViewTVOS.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/tvos/MetalView.m \
	$(ROOT_DIR)/../ouzel/graphics/metal/tvos/MetalRenderDeviceTVOS.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalBlendState.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalBuffer.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalDepthStencilState.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalRenderDevice.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalRenderTarget.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalShader.mm \
	$(ROOT_DIR)/../ouzel/graphics/metal/MetalTexture.mm \
	$(ROOT_DIR)/../ouzel/graphics/opengl/tvos/OGLRenderDeviceTVOS.mm \
	$(ROOT_DIR)/../ouzel/graphics/opengl/tvos/OpenGLView.m \
	$(ROOT_DIR)/../ouzel/input/tvos/GamepadDeviceTVOS.mm \
	$(ROOT_DIR)/../ouzel/input/tvos/InputSystemTVOS.mm
CFLAGS+=-arch arm64 -isysroot $(shell xcrun --sdk appletvos --show-sdk-path) -mtvos-version-min=9.0
CXXFLAGS+=-arch arm64 -isysroot $(shell xcrun --sdk appletvos --show-sdk-path) -mtvos-version-min=9.0
else ifeq ($(platform),emscripten)
SOURCES+=$(ROOT_DIR)/../ouzel/audio/openal/OALAudioDevice.cpp \
	$(ROOT_DIR)/../ouzel/core/emscripten/EngineEm.cpp \
	$(ROOT_DIR)/../ouzel/core/emscripten/main.cpp \
	$(ROOT_DIR)/../ouzel/core/emscripten/NativeWindowEm.cpp \
	$(ROOT_DIR)/../ouzel/core/emscripten/SystemEm.cpp \
	$(ROOT_DIR)/../ouzel/graphics/opengl/emscripten/OGLRenderDeviceEm.cpp \
	$(ROOT_DIR)/../ouzel/input/emscripten/GamepadDeviceEm.cpp \
	$(ROOT_DIR)/../ouzel/input/emscripten/InputSystemEm.cpp \
	$(ROOT_DIR)/../ouzel/input/emscripten/MouseDeviceEm.cpp
CXXFLAGS+=-s DISABLE_EXCEPTION_CATCHING=0
endif
BASE_NAMES=$(basename $(SOURCES))
OBJECTS=$(BASE_NAMES:=.o)
LIBRARY=libouzel.a
DEPENDENCIES=$(OBJECTS:.o=.d)

.PHONY: all
ifeq ($(debug),1)
all: CXXFLAGS+=-DDEBUG -g
all: CFLAGS+=-DDEBUG -g
else
all: CXXFLAGS+=-O3
all: CFLAGS+=-O3
endif
all: config
all: $(ROOT_DIR)/Prefix.hpp.gch
all: $(ROOT_DIR)/$(LIBRARY)

$(ROOT_DIR)/$(LIBRARY): $(OBJECTS)
	$(AR) rs $@ $^

-include $(DEPENDENCIES)

.PHONY: config
config:
ifeq ($(platform),windows)
	if not exist $(ROOT_DIR)\..\ouzel\Config.h copy $(ROOT_DIR)\..\ouzel\DefaultConfig.h $(ROOT_DIR)\..\ouzel\Config.h
else
	if [ ! -f $(ROOT_DIR)/../ouzel/Config.h ]; then \
		cp $(ROOT_DIR)/../ouzel/DefaultConfig.h $(ROOT_DIR)/../ouzel/Config.h; \
	fi
endif

%.hpp.gch: %.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -include $(ROOT_DIR)/Prefix.hpp -MMD -MP $< -o $@

%.o: %.mm
	$(CXX) -fno-objc-arc $(CXXFLAGS) -MMD -MP $< -o $@

%.o: %.m
	$(CC) -fno-objc-arc $(CFLAGS) -MMD -MP $< -o $@

.PHONY: clean
clean:
ifeq ($(platform),windows)
	-del /f /q "$(ROOT_DIR)\$(LIBRARY)"
	-del /f /q "$(ROOT_DIR)\Prefix.hpp.gch"
	-del /s "$(ROOT_DIR)\..\*.o"
	-del /s "$(ROOT_DIR)\..\*.d"
else
	$(RM) $(ROOT_DIR)/$(LIBRARY)
	$(RM) $(ROOT_DIR)/Prefix.hpp.gch
	find $(ROOT_DIR)/.. -name '*.o' -type f -delete
	find $(ROOT_DIR)/.. -name '*.d' -type f -delete
endif