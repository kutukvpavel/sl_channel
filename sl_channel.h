#pragma once

#include <inttypes.h>
#include <stddef.h>

namespace sl_channel
{
    //Implementation-defined
    void set_bit_0(bool v);
    void set_bit_1(bool v);

    //Public API
    void send(const void* p, size_t bits, bool use_start = false);
} // namespace sl_channel
