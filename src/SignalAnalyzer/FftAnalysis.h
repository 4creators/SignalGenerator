//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#ifndef FFTANALYSIS_H
#define FFTANALYSIS_H

#pragma once

#include <vector>
#include <fftw3.h>
#include "dependencies.h"
#include "types.h"
#include "SignalGenerator.h"

#ifdef __cplusplus
namespace DevnetZone
{
    extern "C" {
#   endif

        SIGNALANALYZER_API fftw_complex * GetDftFromReal(uint64_t size, double* buffer);

        SIGNALANALYZER_API void PlotWaveformSpectrogramFftw(DevnetZone::SignalGenerator & gen, double* buffer);

        SIGNALANALYZER_API void PlotFftComplexOutput(DevnetZone::SignalGenerator & gen, fftw_complex * fftBuffer);

        SIGNALANALYZER_API void GetDftXAxisFrequencies(DevnetZone::SignalGenerator & gen, uint64_t samplesCount, std::vector<double>&xAxisValues);

#   ifdef __cplusplus
    } // extern "C"
}
#endif // __cplusplus

#endif // FFTANALYSIS_H
