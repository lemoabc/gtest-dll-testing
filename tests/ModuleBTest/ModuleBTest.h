#pragma once

#include <gtest/gtest.h>
#include "../../src/ModuleB/ModuleB.h"

// Test fixture for ModuleB
class ModuleBTest : public ::testing::Test {
protected:
    void SetUp() override;
    void TearDown() override;

    ModuleB::StringUtil stringUtil;
};
