//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#ifndef SIGNALGENERATOR_H
#define SIGNALGENERATOR_H

#pragma once

#include <math.h>
#include <functional>

#include "dependencies.h"
#include "types.h"

using namespace boost::multiprecision;

namespace DevnetZone
{

    SIGNALGENERATOR_API class SignalGenerator {

    public:
        SignalGenerator() = default;
        ~SignalGenerator() = default;

        // GenerateWaveformSamples function fills buffer returned from function with sampled waveform data points.
        // Generated waveform is defined in the parameter "waveFunction" with other function parameters controlling generation
        // It is generally assumed that waveforms are periodic, however, some parameters combinations allow nonperiodic output generation
        // The assumption for the purpose of phase calculations in multi call continous data generation is that 
        // passed in wave function has a period of Tau ( Tau = 2 * Pi ), otherwise, in the case of single call use it has no effect.
        // Returned double* buffer will contain values adjusted by normalized "gain" parameter 
        // "frequency" is expressed in Hz and range is expected to be more than 0 up to a maximum double value
        // "duration" is in seconds and is expected to be more than 0.0 and up to a maximum double value 
        // "sampleRate" is in samples/second and has to be grater than 0.0 and up to a maximum double value
        // "gain" is linear and enforced to be in the range from 0.0 to 1.0.
        // "waveFunction" parameter is used to pass function used to generate waveform data points, in case nullptr is passed default wave function is used
        // Consecutive channels data are returned in linearly allocated parts of return buffer starting with channel 1
        // Function may return nullptr in the case of data contract violation or OOM error during buffer allocation
        // Function allocates return buffer which has to be freed by caller
        SIGNALGENERATOR_API double* GenerateWaveformSamples(
            uint32_t numberOfChannels = 2,
            double frequency = (double) Constants::A4TuningFrequency,
            double duration = 0.01, 
            double sampleRate = 409600, 
            double gain = 1.0,
            std::function<double(double)> waveFunction = nullptr);

        SIGNALGENERATOR_API double* GenerateWaveformSamples(
            double* buffer,
            uint32_t numberOfChannels = 2,
            double frequency = (double) Constants::A4TuningFrequency,
            double duration = 0.01,
            double sampleRate = 409600,
            double gain = 1.0,
            std::function<double(double)> waveFunction = nullptr);

        SIGNALGENERATOR_API double* GenerateNextWaveformSamples();

        SIGNALGENERATOR_API float128 LastWaveFunctionInput() const
        {
            return m_lastWaveFunctionInput;
        }

        // Returns phase in radians
        SIGNALGENERATOR_API float128 LastWaveFunctionInputPhase() const
        {
            return fmod( m_lastWaveFunctionInput, Constants::Tau );
        }
        
        SIGNALGENERATOR_API uint64_t SamplesCount() const
        {
            return m_samplesCount;
        }

        SIGNALGENERATOR_API float128 SampleInterval() const
        {
            return m_sampleInterval;
        }

        SIGNALGENERATOR_API float128 SampleRate()
        {
            return m_sampleRate;
        }

        SIGNALGENERATOR_API const std::function<double(double)>& WaveFunction() const
        {
            return m_waveFunction;
        }

        SIGNALGENERATOR_API void SetWaveFunction(std::function<double(double)>& waveFunction)
        {
            auto* functionPtr = waveFunction.target<double(*)(double)>();
            if (functionPtr && *functionPtr)
            {
                auto* defaultPtr = m_waveFunction.target<double(*)(double)>();
                if (!defaultPtr || *functionPtr != *defaultPtr)
                    m_waveFunction = waveFunction;
            }
        }

        SIGNALGENERATOR_API const std::function<double(double)>& DefaultWaveFunction() const
        {
            return m_defaultFunction;
        }

        SIGNALGENERATOR_API void SetDefaultWaveFunction(std::function<double(double)>& waveFunction)
        {
            auto* functionPtr = waveFunction.target<double(*)(double)>();
            if (functionPtr && *functionPtr)
            {
                auto* defaultPtr = m_defaultFunction.target<double(*)(double)>();
                if (*functionPtr != *defaultPtr)
                    m_defaultFunction = waveFunction;
            }
        }

        enum ReturnCode : int64_t
        {
            Success = 0,
            Failed = 0x8000000000000000,
            OutOfMemoryError = Failed | (1 << 0),
            FrequencyOutOfRange = Failed | (1 << 1),
            DurationOutOfRange = Failed | (1 << 2),
            SampleRateOutOfRange = Failed | (1 << 3),
            GainOutOfRange = Failed | (1 << 4),
            NumberOfChannelsOutOfRange = Failed | (1 << 5)
        };

        SIGNALGENERATOR_API ReturnCode LastGeneratorCallResult() const
        {
            return m_lastGeneratorCallResult;
        }

        SIGNALGENERATOR_API bool LastGeneratorCallSuccess() const
        {
            return !((uint64_t)m_lastGeneratorCallResult & (uint64_t)ReturnCode::Failed);
        }

        SIGNALGENERATOR_API bool IsError(uint64_t errorCode)
        {
            return (bool)((uint64_t)m_lastGeneratorCallResult & (errorCode & 0x7fffffffffffff));
        };

    protected:
        // If we want to preserve continuity while generating signal in consecutive
        // calls to GenerateWaveformSamples we need to preserve some additionl context
        // to determine phase of last generated sample
        float128 m_sampleRate = 0.0;
        float128 m_signalFrequency = 0.0;
        float128 m_signalDuration = 0.0;
        float128 m_signalGain = 0.0;
        uint32_t m_numberOfChannels = 0;
        float128 m_maxInputValue = 0.0;
        float128 m_samplesCountDouble = 0.0;
        float128 m_sampleInterval = 0.0;
        uint64_t m_samplesCount = 0;
        float128 m_lastWaveFunctionInput = 0.0;
        float128 m_phaseCorrection = 0.0;

        std::function<double(double)> m_defaultFunction =  (double(*)(double)) std::sin;
        std::function<double(double)> m_waveFunction = nullptr;

        ReturnCode m_lastGeneratorCallResult = ReturnCode::Failed;

    } Generator;

} // namespace DevnetZone

#endif // #ifndef SIGNALGENERATOR_H