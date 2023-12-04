//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#pragma once

#ifndef SIGNALFUNCTIONS_H
#define SIGNALFUNCTIONS_H

#pragma once

#include <numbers>
#include "types.h"

namespace DevnetZone
{
    class SignalFunctions
    {
    public:

        static double Cos(double value)
        {
            return cos(value);
        }

        static double SawTooth(double value)
        {
            return fmod(value, tau) * inv2_tau - 1;
        }

        static double SawToothRev(double value)
        {
            return 1 - fmod(value, tau) * inv2_tau;
        }

        static double Sin(double value)
        {
            return sin(value);
        }

        static double Rectangular(double value)
        {
            double modVal = fmod(value, tau);
            if (modVal > pi)
            {
                return -1;
            }
            else 
            {
                return 1;
            }
        }

    private:
        static const inline double pi = std::numbers::pi;
        static const inline double inv_pi = 1 / pi;
        static const inline double tau = 2 * pi;
        static const inline double inv_tau = 1 / tau;
        static const inline double inv2_tau = 2 / tau;
    };
}

#endif // SIGNALFUNCTIONS_H