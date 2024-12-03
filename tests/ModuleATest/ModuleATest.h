#pragma once

#include <gtest/gtest.h>
#include "../../src/ModuleA/ModuleA.h"

// 基础测试夹具
class ModuleATest : public ::testing::Test {
protected:
    void SetUp() override;
    void TearDown() override;

    ModuleA::Calculator calc;
};

// GUI测试的基础夹具
class GUITest : public ModuleATest {
protected:
    void SetUp() override {
        ModuleATest::SetUp();
        // GUI测试的通用设置
    }
};

// Widget测试的基础夹具
class WidgetTest : public GUITest {
protected:
    void SetUp() override {
        GUITest::SetUp();
        // Widget测试的通用设置
    }
};
