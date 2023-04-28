#include "sl_channel.h"

#include <assert.h>
#include <cstdio>

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
        delay();
    }
    void write_bit(bool v)
    {
        reset_channel();
        set_bit_0(!v);
        set_bit_1(v);
        if (v) parity_counter++;
        delay();
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
        delay();
        reset_channel();
    }

    //Public API
    void init()
    {
        reset_channel();
    }
    void send(const void* p, size_t bits, bool use_start)
    {
        size_t total_bits = bits + (use_start ? 1 : 0);
        if (total_bits % 2 != 0)
        {
            printf("SL Channel WARNING: total number of bits is not even (%u).\n", total_bits);
        }

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
