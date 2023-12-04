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
            // g0_ remains in default state
        }

        void TearDown() override 
        {
            // nothing to do
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

    TEST_F(SignalGeneratorTest, SetDefaultWaveFunction_ArgumentCannotPointToNullptr) 
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
}

int main(int argc, wchar_t** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

