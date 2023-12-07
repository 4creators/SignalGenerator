//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#pragma once

#include <matplot/matplot.h>
#include "dependencies.h"
#include "FftAnalysis.h"


using namespace matplot;
using namespace DevnetZone;

fftw_complex* DevnetZone::GetDftFromReal(uint64_t size, double* buffer)
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

void DevnetZone::GetDftXAxisFrequencies(DevnetZone::SignalGenerator& gen, uint64_t samplesCount, std::vector<double>& xAxisValues)
{
    double sampleFrequency = gen.SampleRate().convert_to<double>();
    for (uint64_t k = 0; k < samplesCount; k++)
        xAxisValues[k] = ((double)k) / samplesCount * sampleFrequency / 2;
}

void DevnetZone::PlotWaveformSpectrogramFftw(DevnetZone::SignalGenerator& gen, double* buffer)
{
    fftw_complex* fftBuffer = GetDftFromReal(gen.SamplesCount(), buffer);

    PlotFftComplexOutput(gen, fftBuffer);

    fftw_free(fftBuffer);
}

void DevnetZone::PlotFftComplexOutput(DevnetZone::SignalGenerator& gen, fftw_complex* fftBuffer)
{
    uint64_t fftSize = gen.SamplesCount() / 2 + 1;

    double* plotBuffer = (double*)malloc(fftSize * sizeof(double));

    if (plotBuffer)
    {
        for (int i = 0; i < fftSize; i++)
        {
            double real = fftBuffer[i][0];
            double img = fftBuffer[i][1];
            plotBuffer[i] = 2 * sqrt(pow(real, 2) + pow(img, 2)) / gen.SamplesCount(); // normalize + magnitude
        }

        double* endPlotBuff = plotBuffer + fftSize;

        std::vector<double> x(fftSize);
        std::vector<double> ticksX =
        {
            0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 100000,
            //11000, 12000, 13000, 14000, 15000, 16000, 17000, 18000, 19000, 200000,
        };

        GetDftXAxisFrequencies(gen, fftSize, x);

        std::vector<double> y(plotBuffer, endPlotBuff);

        plot(x, y);
        axis(tight);
        xticks(ticksX);

        show();

        free(plotBuffer);
    }
}

