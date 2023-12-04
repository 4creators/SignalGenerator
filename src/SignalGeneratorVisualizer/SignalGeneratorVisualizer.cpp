//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#pragma once

#include <iostream>
#include <matplot/matplot.h>
#include "fftw3.h"
#include "SignalFunctions.h"
#include "SignalGenerator.h"
#include "Scale.h"
#include "SignalGeneratorVisualizer.h"


using namespace matplot;
using namespace DevnetZone;

int main() 
{
    PrintScaleFrequencyRange();

    PrintNotes();

    SignalGenerator gen;
    gen.SetDefaultWaveFunction(&SignalFunctions::SawToothRev);
    double* buffer = gen.GenerateWaveformSamples(1, 880, 0.1, 20480, 1.0);

    PlotWaveformSpectrogramFftw(gen, buffer);

    free(buffer);

    return 0;
}

static void PrintScaleFrequencyRange()
{
    DevnetZone::float128 minFreq = Constants::MinScaleFrequencyC_7;
    DevnetZone::float128 maxFreq = Constants::MaxScaleFrequencyB12;

    std::cout << std::setprecision(64) << "Min frequency: " << minFreq << "\n";
    std::cout << "Max frequency: " << maxFreq << "\n";
}

static void PrintNotes()
{
    Scale scale;
    auto& u = scale.NoteFrequencyMap();

    std::cout << "\nNoteFrequencyMap.size: " << u.size() << "\n";

    auto print_key_value = [](const auto& key, const auto& value)
        {
            std::cout << "Key:[" << key << "] Value:[" << value << "]\n";
        };

    for (const auto& [key, value] : u)
        print_key_value(key, value);
}

static fftw_complex* GetDftFromReal(int64_t size, double* buffer)
{
    if (buffer)
    {
        double* inputBuffer = fftw_alloc_real(size);
        fftw_complex* outputBuffer = fftw_alloc_complex(size);
        if (outputBuffer)
            memset(outputBuffer, 0, sizeof(fftw_complex) * size);
        fftw_plan plan = fftw_plan_dft_r2c_1d((int)size, inputBuffer, outputBuffer, FFTW_ESTIMATE);

        memcpy(inputBuffer, buffer, sizeof(double) * size);

        fftw_execute(plan);

        fftw_destroy_plan(plan);
        fftw_free(inputBuffer);

        return outputBuffer;
    }

    return nullptr;
}

static void PlotWaveformSpectrogramFftw(DevnetZone::SignalGenerator& gen, double* buffer)
{
    fftw_complex* fftBuffer = GetDftFromReal(gen.SamplesCount(), buffer);

    PlotFftComplexOutput(gen, fftBuffer);

    fftw_free(fftBuffer);
}

void PlotFftComplexOutput(DevnetZone::SignalGenerator& gen, fftw_complex* fftBuffer)
{
    // Copy real fft part to input buffer - correct for 
    // complex double size difference
    int64_t fftSize = gen.SamplesCount() / 2 + 1;

    double* plotBuffer = (double*)malloc(fftSize * sizeof(double));

    if (plotBuffer)
    {
        double* fftBuffDouble = (double*)fftBuffer;
        for (int i = 3, j = 0; j < fftSize - 2; i += 2, j++)
            plotBuffer[j] = abs(fftBuffDouble[i]) / fftSize; // copy real part and normalize

        int64_t dataPoints = fftSize - 2;

        double* endPlotBuff = plotBuffer + dataPoints;

        std::vector<double> x = linspace(0, dataPoints, dataPoints);
        std::vector<double> y(plotBuffer, endPlotBuff);

        plot(x, y);
        show();

        free(plotBuffer);
    }
}