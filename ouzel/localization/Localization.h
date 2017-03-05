// Copyright (C) 2017 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include <unordered_map>
#include <string>
#include "utils/Types.h"

namespace ouzel
{
    class Language;

    class Localization
    {
    public:
        void addLanguage(const std::string& name, const std::string& filename);
        void setLanguage(const std::string& language);
        std::string getString(const std::string& str);

    protected:
        std::unordered_map<std::string, std::shared_ptr<Language>> languages;
        std::shared_ptr<Language> currentLanguage;
    };
}
