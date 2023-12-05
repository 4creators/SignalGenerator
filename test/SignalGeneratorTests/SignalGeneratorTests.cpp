// SignalGeneratorTests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <gtest/gtest.h>
#include "types.h"
#include "SignalGenerator.h"

using namespace DevnetZone;

namespace DevnetZone
{
    class SignalGeneratorTest : public testing::Test 
    {
    protected:
        void SetUp() override 
        {
        }

        void TearDown() override 
        {
        }

        SignalGenerator g0_;
    };

    TEST_F(SignalGeneratorTest, DefaultWaveFunction_IsSetDuringInitialization) 
    {
        EXPECT_NE(g0_.DefaultWaveFunction().target<double(*)(double)>(), nullptr);
    }

    TEST_F(SignalGeneratorTest, DefaultWaveFunction_IsStdSin) 
    {
        auto sinPtr2 = g0_.DefaultWaveFunction().target<double(*)(double)>();
        EXPECT_EQ(*sinPtr2, (double(*)(double)) & std::sin);
    }

    TEST_F(SignalGeneratorTest, SetDefaultWaveFunction_ArgumentCannotBeNullptr) 
    {
        std::function<double(double)> nullFunction{ (double(*)(double)) nullptr };
        g0_.SetDefaultWaveFunction(nullFunction);

        auto* targetFunc = g0_.DefaultWaveFunction().target<double(*)(double)>();
        auto* targetNullFunction = nullFunction.target<double(*)(double)>();
        EXPECT_TRUE(*targetFunc);
        EXPECT_FALSE(targetNullFunction);
    }

    TEST_F(SignalGeneratorTest, SetDefaultWaveFunction_FunctionIsSet)
    {
        std::function<double(double)> cosFunction = (double(*)(double)) & std::cos;
        g0_.SetDefaultWaveFunction(cosFunction);

        auto* targetFunc = g0_.DefaultWaveFunction().target<double(*)(double)>();
        EXPECT_EQ(*targetFunc, (double(*)(double)) & std::cos);
    }

    TEST_F(SignalGeneratorTest, SettWaveFunction_FunctionIsSet)
    {
        // Check precondition
        auto* initialFuncValue = g0_.WaveFunction().target<double(*)(double)>();
        EXPECT_FALSE(initialFuncValue);

        std::function<double(double)> cosFunction = (double(*)(double)) & std::cos;
        g0_.SetWaveFunction(cosFunction);

        auto* targetFunc = g0_.WaveFunction().target<double(*)(double)>();
        EXPECT_EQ(*targetFunc, (double(*)(double)) & std::cos);
    }

    TEST_F(SignalGeneratorTest, SettWaveFunction_ArgumentCannotBeNullptr)
    {
        std::function<double(double)> cosFunction = (double(*)(double)) & std::cos;
        g0_.SetWaveFunction(cosFunction);

        auto* targetFunc = g0_.WaveFunction().target<double(*)(double)>();
        EXPECT_EQ(*targetFunc, (double(*)(double)) & std::cos);

        std::function<double(double)> nullFunction{ (double(*)(double)) nullptr };
        g0_.SetWaveFunction(nullFunction);

        targetFunc = g0_.WaveFunction().target<double(*)(double)>();
        auto* targetNullFunction = nullFunction.target<double(*)(double)>();
        EXPECT_TRUE(*targetFunc);
        EXPECT_FALSE(targetNullFunction);
    }

    TEST_F(SignalGeneratorTest, GenerateWaveformSamples_DataContractErrors)
    {
        double* buffer = g0_.GenerateWaveformSamples(nullptr, 0, -1, -1, -1, -0.5);
        EXPECT_FALSE(buffer);

        EXPECT_FALSE(g0_.LastGeneratorCallSuccess());
        EXPECT_TRUE(g0_.IsError(SignalGenerator::FrequencyOutOfRange));
        EXPECT_TRUE(g0_.IsError(SignalGenerator::NumberOfChannelsOutOfRange));
        EXPECT_TRUE(g0_.IsError(SignalGenerator::DurationOutOfRange));
        EXPECT_TRUE(g0_.IsError(SignalGenerator::SampleRateOutOfRange));
        EXPECT_TRUE(g0_.IsError(SignalGenerator::GainOutOfRange));
        EXPECT_FALSE(g0_.IsError(SignalGenerator::OutOfMemoryError));
    }
}

int main(int argc, wchar_t** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

