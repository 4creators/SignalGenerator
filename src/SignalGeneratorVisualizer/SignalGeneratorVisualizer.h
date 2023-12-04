//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#pragma once

void PlotWaveformSpectrogramFftw(DevnetZone::SignalGenerator& gen, double* buffer);

static void PlotFftComplexOutput(DevnetZone::SignalGenerator& gen, fftw_complex* fftBuffer);

void PrintScaleFrequencyRange();

static void PrintNotes();

static fftw_complex* GetDftFromReal(int64_t size, double* buffer);

static void PlotWaveformSpectrogramKissfft(DevnetZone::SignalGenerator& gen, double* buffer);
