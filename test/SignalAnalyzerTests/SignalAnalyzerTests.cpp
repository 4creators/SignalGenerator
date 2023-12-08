//
// Copyright © 2023 Jacek Błaszczyński
//
// SPDX-License-Identifier: MIT
//

#include <iostream>
#include <gtest/gtest.h>
#include "types.h"
#include "SignalGenerator.h"
#include "FftAnalysis.h"

using namespace DevnetZone;

namespace DevnetZone
{
}

int main(int argc, wchar_t** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
