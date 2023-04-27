#include "sl_channel.h"

#include <assert.h>

#ifndef _BV
    #define _BV(b) (1u << (b))
#endif
#ifndef __CHAR_BIT__
    #define __CHAR_BIT__ 8u
#endif

namespace sl_channel
{
    //Private API
    unsigned int parity_counter = 0;

    void reset_channel()
    {
        set_bit_0(true);
        set_bit_1(true);
    }
    void write_start()
    {
        write_bit(false);
    }
    void write_stop()
    {
        reset_channel();
        set_bit_0(false);
        set_bit_1(false);
        parity_counter = 0;
    }
    void write_bit(bool v)
    {
        reset_channel();
        set_bit_0(!v);
        set_bit_1(v);
        if (v) parity_counter++;
    }

    //Public API
    void send(const void* p, size_t bits, bool use_start = false)
    {
        assert((bits + use_start ? 1 : 0) % 2 == 0);

        const uint8_t* buf = reinterpret_cast<const uint8_t*>(p);
        size_t bytes = bits / __CHAR_BIT__;
        size_t remainder = bits % __CHAR_BIT__;

        if (use_start) write_start();
        for (size_t i = 0; i < bytes; i++)
        {
            for (size_t j = 0; j < __CHAR_BIT__; j++)
            {
                write_bit(buf[i] & _BV(j));
            }
        }
        for (size_t i = 0; i < remainder; i++)
        {
            write_bit(buf[bytes] & _BV(i));
        }
        
        write_bit(parity_counter % 2 == 0);
        write_stop();
    }
} // namespace sl_channel
