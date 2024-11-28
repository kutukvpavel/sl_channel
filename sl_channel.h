/**
 * @file sl_channel.h
 * @author Kutukov Pavel (kutukovps@my.msu.ru)
 * @brief A library to communicate with SL-channel bus (used by NPO Fizika)
 * @version 1.1
 * @date 2023-04-27
 * 
 *  @copyright This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 */

#pragma once

#include <inttypes.h>
#include <stddef.h>

namespace sl_channel
{
    //Implementation-defined
    void set_bit_0(bool v);
    void set_bit_1(bool v);
    void delay();

    //Public API
    void init();
    void send(const void* p, size_t bits, bool use_start = false);
} // namespace sl_channel
