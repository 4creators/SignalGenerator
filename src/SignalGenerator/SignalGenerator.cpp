//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#include "SignalGenerator.h"

using namespace std;

namespace DevnetZone {

    double* SignalGenerator::GenerateWaveformSamples(uint32_t numberOfChannels, double frequency, double duration, double sampleRate, double gain, std::function<double(double)> waveFunction)
    {
        return GenerateWaveformSamples(nullptr, numberOfChannels, frequency, duration, sampleRate, gain, waveFunction);
    }

    double* SignalGenerator::GenerateWaveformSamples(double* buffer, uint32_t numberOfChannels, double frequency, double duration, double sampleRate, double gain, std::function<double(double)> waveFunction)
    {
        // TODO: handle fractional frequency and sampleRate

        // Data contract enforcment
        // Do not throw FE_INVALID

        if (waveFunction == nullptr)
            m_waveFunction = m_defaultFunction;

        int64_t result = 0;

        if (isless(frequency, 0.0) && !isnormal(frequency))
            result |= ReturnCode::FrequencyOutOfRange;

        if (isless(duration, 0.0) && !isnormal(duration))
            result |= ReturnCode::DurationOutOfRange;

        if (isless(sampleRate, 0.0) && !isnormal(sampleRate))
            result |= ReturnCode::SampleRateOutOfRange;

        // Rethink using isnormal() check as it eliminates 0.0 gain
        // value what may not be a desired function behaviour
        if (isless(gain, -1.0) || isgreater(gain, 1.0) || !isnormal(gain))
            result |= ReturnCode::GainOutOfRange;

        if (numberOfChannels == 0)
            result |= ReturnCode::NumberOfChannelsOutOfRange;

        m_lastGeneratorCallResult = (ReturnCode)result;

        if (m_lastGeneratorCallResult & ReturnCode::Failed)
            return nullptr;

        m_maxInputValue = float128(frequency) * float128(duration) * Constants::Tau;
        m_samplesCountDouble = float128(sampleRate) * float128(duration);
        m_sampleInterval = m_maxInputValue / m_samplesCountDouble;
        m_samplesCount = floor(m_samplesCountDouble).convert_to<uint64_t>();

        double* retBuffer = buffer;
        if (!retBuffer)
        {
            retBuffer = (double*)malloc(m_samplesCount * numberOfChannels * sizeof(double) + 64);
            if (retBuffer)
                memset(retBuffer, 0, m_samplesCount * numberOfChannels * sizeof(double) + 64);
        }

// Note: this is a workaround for a false-positive warning produced by the Visual C++ 17 compiler
#pragma warning(disable:6386)
        if (retBuffer != nullptr)
        {
            for (uint64_t index = 0; index < m_samplesCount; index++)
            {
                // Multiplicative calculation of input value introduces lower floating point error 
                // in contrast to an additive accumulation done in alternative algorithm for input value 
                m_lastWaveFunctionInput = m_sampleInterval * index + m_phaseCorrection;
                retBuffer[index] = m_waveFunction((double)m_lastWaveFunctionInput) * gain;
            }

            int count = numberOfChannels - 1;
            double* destBuffer = retBuffer + m_samplesCount;

            for (int i = 0; i < count; i++)
            {
                memcpy(destBuffer, retBuffer, m_samplesCount);
                destBuffer = destBuffer + m_samplesCount;
            };

            m_phaseCorrection = m_lastWaveFunctionInput + m_sampleInterval;
        }
#pragma warning(default:6386)
        else
        {
            result |= ReturnCode::OutOfMemoryError;
            m_lastGeneratorCallResult = (ReturnCode)result;
        }

        return retBuffer;
    }

    SIGNALGENERATOR_API double* SignalGenerator::GenerateNextWaveformSamples()
    {
        return nullptr;
    }

} // namespace DevnetZone
