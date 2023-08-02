/*
    SlimeVR Code is placed under the MIT license
    Copyright (c) 2023 SlimeVR Contributors

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef SLIMEVR_SENSOR_FEATURE_FLAGS_H_
#define SLIMEVR_SENSOR_FEATURE_FLAGS_H_

#include <cstring>
#include <algorithm>

/**
 * Bit packed flags, enum values start with 0 and indicate which bit it is.
 * 
 * Change the enums and `flagsEnabled` inside to extend.
*/
class SensorFeatures {
public:
    enum ESensorFeatureFlags: uint32_t {
        // The sensor sends rotation data
        ROTATION_DATA,
        // The sensor sends position data
        POSITION_DATA,
        
        // Add new flags here
        
        BITS_TOTAL,
    };

    // Flags to send
    static constexpr const std::initializer_list<ESensorFeatureFlags> flagsEnabled = {
        ROTATION_DATA,

        // Add enabled flags here
    };

    static constexpr auto flags = []{
        constexpr uint32_t flagsLength = ESensorFeatureFlags::BITS_TOTAL / 8 + 1;
        std::array<uint8_t, flagsLength> packed{};
        
        for (uint32_t bit : flagsEnabled) {
            packed[bit / 8] |= 1 << (bit % 8);
        }

        return packed;
    }();
};

#endif