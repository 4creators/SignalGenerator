//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#pragma once

#include <iostream>
#include <fftw3.h>
#include "SignalFunctions.h"
#include "SignalGenerator.h"
#include "Scale.h"
#include "FftAnalysis.h"
#include "SignalGeneratorVisualizer.h"

using namespace DevnetZone;

int main() 
{
    //PrintScaleFrequencyRange();

    //PrintNotes();

    SignalGenerator gen;
    std::function<double(double)> func{ SignalFunctions::SawToothRev };
    gen.SetDefaultWaveFunction(func);
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