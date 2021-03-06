// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#include <cstdint>
#include "Size3.hpp"
#include "Size2.hpp"

namespace ouzel
{
    template<class T>
    Size3<T>::Size3(const Size2<T>& s):
        v{s.v[0], s.v[1], 0}
    {
    }

    template class Size3<float>;
    template class Size3<uint32_t>;
}
