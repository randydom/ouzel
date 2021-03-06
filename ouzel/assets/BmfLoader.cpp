// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#include "BmfLoader.hpp"
#include "Bundle.hpp"
#include "gui/BMFont.hpp"

namespace ouzel
{
    namespace assets
    {
        BmfLoader::BmfLoader(Cache& initCache):
            Loader(initCache, TYPE)
        {
        }

        bool BmfLoader::loadAsset(Bundle& bundle, const std::string& filename, const std::vector<uint8_t>& data, bool)
        {
            try
            {
                // TODO: move the loader here
                std::shared_ptr<BMFont> font = std::make_shared<BMFont>(data);
                bundle.setFont(filename, font);
            }
            catch (const std::exception&)
            {
                return false;
            }

            return true;
        }
    } // namespace assets
} // namespace ouzel
