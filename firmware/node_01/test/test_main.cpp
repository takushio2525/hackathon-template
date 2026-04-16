// test_main.cpp — PlatformIO Unity テストのサンプル
//
// テストの実行方法:
//   cd firmware/node_01
//   pio test
//
// 参考: https://docs.platformio.org/en/latest/advanced/unit-testing/index.html

#include <unity.h>
#include <Arduino.h>

// テスト対象の関数（実際には src/ や lib/ から #include する）
int32_t add(int32_t a, int32_t b) {
    return a + b;
}

// テストケース: 正常系
void test_add_positive_numbers(void) {
    TEST_ASSERT_EQUAL(5, add(2, 3));
}

// テストケース: ゼロを含む
void test_add_with_zero(void) {
    TEST_ASSERT_EQUAL(3, add(3, 0));
    TEST_ASSERT_EQUAL(0, add(0, 0));
}

// テストケース: 負の数
void test_add_negative_numbers(void) {
    TEST_ASSERT_EQUAL(-1, add(2, -3));
}

void setup() {
    delay(2000); // ボードのシリアル接続待ち
    UNITY_BEGIN();

    RUN_TEST(test_add_positive_numbers);
    RUN_TEST(test_add_with_zero);
    RUN_TEST(test_add_negative_numbers);

    UNITY_END();
}

void loop() {
    // テストモードでは何もしない
}
