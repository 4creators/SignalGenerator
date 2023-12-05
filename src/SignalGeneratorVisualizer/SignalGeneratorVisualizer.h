//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#ifndef SIGNALGENERATORVISUALIZER_H
#define SIGNALGENERATORVISUALIZER_H

#pragma once

static void PlotWaveformSpectrogramFftw(DevnetZone::SignalGenerator& gen, double* buffer);

static void PlotFftComplexOutput(DevnetZone::SignalGenerator& gen, fftw_complex* fftBuffer);

static void PrintScaleFrequencyRange();

static void PrintNotes();

static fftw_complex* GetDftFromReal(uint64_t size, double* buffer);

static void GetDftXAxisFrequencies(DevnetZone::SignalGenerator& gen, uint64_t samplesCount, std::vector<double>& xAxisValues);

#endif // SIGNALGENERATORVISUALIZER_H