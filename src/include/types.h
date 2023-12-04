//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#ifndef TYPES_H
#define TYPES_H

#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

using namespace boost::multiprecision;

namespace DevnetZone
{
    typedef cpp_bin_float_quad float128;

    class Constants
    {
    public:
        static const inline float128 Pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;
        static const inline float128 Tau = 6.283185307179586476925286766559005768394338798750211641949889184615632812572396;
        static const inline float128 Euler = 2.71828182845904523536028747135266249775724709369995957496696762772407663035354759;

        // Equally tempered music scale half tone ratio formula: 2 ^ (1/12)
        // The name of the constant should be HalfToneEquallyTemperedScaleRatio
        static const inline float128 HalfToneRatio = 1.059463094359295264561825294946341700779204317494185628559208431458761646063259;

        // Base A4 standard tuning frequency in Hz
        static const inline float128 A4TuningFrequency = 440.0;

        // Scale spanning 20 octaves from C-7 at 0.1277 Hz to B12 at 126434.1251 -
        // extreme parts below 16 Hz and above 22 kHz cannot be heard by any humans
        static const inline double MinScaleFrequencyC_7 = 0.1277468580569329492657715263703721575438976287841796875;
        static const inline double MaxScaleFrequencyB12 = 126434.125121567849419079720973968505859375;
    };

};

#endif TYPES_H