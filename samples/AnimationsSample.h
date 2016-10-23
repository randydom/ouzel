// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "Samples.h"

class AnimationsSample: public ouzel::scene::Scene
{
public:
    AnimationsSample(Samples& aSamples);

private:
    bool handleUI(ouzel::Event::Type type, const ouzel::UIEvent& event) const;
    bool handleKeyboard(ouzel::Event::Type type, const ouzel::KeyboardEvent& event) const;

    Samples& samples;

    std::unique_ptr<ouzel::scene::Layer> layer;
    std::unique_ptr<ouzel::scene::Camera> camera;

    std::unique_ptr<ouzel::scene::ShapeDrawable> shapeDrawable;
    std::unique_ptr<ouzel::scene::Node> drawNode;

    std::unique_ptr<ouzel::scene::Shake> shake;

    std::unique_ptr<ouzel::scene::Sprite> witchSprite;
    std::unique_ptr<ouzel::scene::Node> witch;

    std::unique_ptr<ouzel::scene::Animator> witchScale;
    std::unique_ptr<ouzel::scene::Animator> witchFade;
    std::unique_ptr<ouzel::scene::Animator> witchRotate;
    std::unique_ptr<ouzel::scene::Animator> witchRepeat;
    std::unique_ptr<ouzel::scene::Animator> witchParallel;
    std::unique_ptr<ouzel::scene::Animator> witchSequence;

    std::unique_ptr<ouzel::scene::Sprite> ballSprite;
    std::unique_ptr<ouzel::scene::Node> ball;

    std::unique_ptr<ouzel::scene::Animator> ballDelay;
    std::unique_ptr<ouzel::scene::Animator> ballEase;
    std::unique_ptr<ouzel::scene::Animator> ballMove;
    std::unique_ptr<ouzel::scene::Animator> ballSequence;
    
    ouzel::EventHandler eventHandler;

    std::unique_ptr<ouzel::scene::Layer> guiLayer;
    std::unique_ptr<ouzel::scene::Camera> guiCamera;
    std::unique_ptr<ouzel::gui::Menu> menu;
    std::unique_ptr<ouzel::gui::Button> backButton;
};
