// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_SCENE_CAMERA_HPP
#define OUZEL_SCENE_CAMERA_HPP

#include <memory>
#include "scene/Component.hpp"
#include "math/MathUtils.hpp"
#include "math/Rect.hpp"
#include "graphics/DepthStencilState.hpp"
#include "graphics/Texture.hpp"

namespace ouzel
{
    namespace scene
    {
        class Layer;

        class Camera: public Component
        {
            friend Layer;
        public:
            static constexpr uint32_t CLASS = Component::CAMERA;

            enum class ProjectionMode
            {
                CUSTOM,
                ORTHOGRAPHIC,
                PERSPECTIVE
            };

            enum class ScaleMode
            {
                NONE,
                EXACT_FIT,
                NO_BORDER,
                SHOW_ALL
            };

            explicit Camera(const Matrix4<float>& initProjection);
            explicit Camera(const Size2<float>& initTargetContentSize = Size2<float>(), ScaleMode initScaleMode = ScaleMode::NONE);
            explicit Camera(float initFov, float initNearPlane = 1.0F, float initFarPlane = 100.0F);
            virtual ~Camera();

            inline ProjectionMode getProjectionMode() const { return projectionMode; }
            void setProjectionMode(ProjectionMode newProjectionMode) { projectionMode = newProjectionMode; }

            inline float getFOV() const { return fov; }
            void setFOV(float newFOV) { fov = newFOV; }

            inline float getNearPlane() const { return nearPlane; }
            void setNearPlane(float newNearPlane) { nearPlane = newNearPlane; }

            inline float getFarPlane() const { return farPlane; }
            void setFarPlane(float newFarPlane) { farPlane = newFarPlane; }

            const Matrix4<float>& getProjection() const { return projection; }
            void recalculateProjection();

            const Matrix4<float>& getViewProjection() const;
            const Matrix4<float>& getRenderViewProjection() const;
            const Matrix4<float>& getInverseViewProjection() const;

            Vector3<float> convertNormalizedToWorld(const Vector2<float>& normalizedPosition) const;
            Vector2<float> convertWorldToNormalized(const Vector3<float>& worldPosition) const;

            bool checkVisibility(const Matrix4<float>& boxTransform, const Box3<float>& box) const;

            inline const Rect<float>& getViewport() const { return viewport; }
            inline const Rect<float>& getRenderViewport() const { return renderViewport; }
            void setViewport(const Rect<float>& newViewport);

            inline ScaleMode getScaleMode() const { return scaleMode; }
            void setScaleMode(ScaleMode newScaleMode);

            inline const Size2<float>& getTargetContentSize() const { return targetContentSize; }
            void setTargetContentSize(const Size2<float>& newTargetContentSize);

            inline const Size2<float>& getContentSize() const { return contentSize; }
            inline const Vector2<float>& getContentScale() const { return contentScale; }
            inline const Vector2<float>& getContentPosition() const { return contentPosition; }

            inline const std::shared_ptr<graphics::Texture>& getRenderTarget() const { return renderTarget; }
            void setRenderTarget(const std::shared_ptr<graphics::Texture>& newRenderTarget);

            inline bool getDepthTest() const { return depthTest; }
            void setDepthTest(bool newDepthTest);
            inline const std::shared_ptr<graphics::DepthStencilState>& getDepthStencilState() const { return depthStencilState; }

            inline bool getWireframe() const { return wireframe; }
            inline void setWireframe(bool newWireframe) { wireframe = newWireframe; }

        protected:
            void setActor(Actor* newActor) override;
            void setLayer(Layer* newLayer) override;

            void updateTransform() override;
            void calculateViewProjection() const;

            ProjectionMode projectionMode;
            float fov = TAU / 6.0F;
            float nearPlane = 1.0F;
            float farPlane = 100.0F;

            Matrix4<float> projection;

            Rect<float> viewport = Rect<float>(0.0F, 0.0F, 1.0F, 1.0F);
            Rect<float> renderViewport;
            Size2<float> targetContentSize;

            ScaleMode scaleMode = ScaleMode::NONE;
            Size2<float> contentSize;
            Vector2<float> contentScale;
            Vector2<float> contentPosition;

            bool depthTest = false;
            bool wireframe = false;

            mutable bool viewProjectionDirty = true;
            mutable Matrix4<float> viewProjection;
            mutable Matrix4<float> renderViewProjection;

            mutable bool inverseViewProjectionDirty = true;
            mutable Matrix4<float> inverseViewProjection;

            std::shared_ptr<graphics::Texture> renderTarget;
            std::shared_ptr<graphics::DepthStencilState> depthStencilState;
        };
    } // namespace scene
} // namespace ouzel

#endif // OUZEL_SCENE_CAMERA_HPP
