#include "../../ModuleATest.h"

// Button控件测试类
class GUI_Widget_ButtonTest : public WidgetTest {
protected:
    void SetUp() override {
        WidgetTest::SetUp();
        // Button特定设置
    }
};

// 点击事件测试
TEST_F(GUI_Widget_ButtonTest, ClickEvent) {
    // 测试按钮点击事件
}

// 双击事件测试
TEST_F(GUI_Widget_ButtonTest, DoubleClickEvent) {
    // 测试按钮双击事件
} 