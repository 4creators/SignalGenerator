//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#include <iostream>
#include <gtest/gtest.h>
#include "types.h"
#include "SignalGenerator.h"
#include "Scale.h"

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
}

int main(int argc, wchar_t** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
