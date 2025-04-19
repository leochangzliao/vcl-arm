#include "../Vec16c.h"
#include <iostream>
#include <cassert>

using namespace VCL_NAMESPACE;

void test_default_constructor() {
    Vec16c vec;
    for (int i = 0; i < Vec16c::size(); ++i) {
        assert(vec[i] == 0);
    }
    std::cout << "test_default_constructor passed!" << std::endl;
}

void test_broadcast_constructor() {
    Vec16c vec(5);
    for (int i = 0; i < Vec16c::size(); ++i) {
        assert(vec[i] == 5);
    }
    std::cout << "test_broadcast_constructor passed!" << std::endl;
}

void test_element_constructor() {
    Vec16c vec(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    for (int i = 0; i < Vec16c::size(); ++i) {
        assert(vec[i] == i + 1);
    }
    std::cout << "test_element_constructor passed!" << std::endl;
}

void test_constructor_from_int8x16_t() {
    // Create an int8x16_t vector with specific values
    int8_t values[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int8x16_t int8_vector = vld1q_s8(values);

    // Use the constructor to create a Vec16c object
    Vec16c vec(int8_vector);

    // Verify that the values in Vec16c match the original values
    for (int i = 0; i < 16; ++i) {
        assert(vec[i] == values[i]);
    }

    std::cout << "test_constructor_from_int8x16_t passed!" << std::endl;
}

void test_copy_constructor() {
    // Initialize a Vec16c object with specific values
    Vec16c original(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    // Use the copy constructor to create a new Vec16c object
    Vec16c copy(original);

    // Verify that the copied object has the same values as the original
    for (int i = 0; i < 16; ++i) {
        assert(copy[i] == original[i]);
    }

    std::cout << "test_copy_constructor passed!" << std::endl;
}

void test_assignment_operator() {
    // Create an int8x16_t vector with specific values
    int8_t values[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int8x16_t test_vector = vld1q_s8(values);

    // Create a Vec16c object and assign the int8x16_t vector to it
    Vec16c vec;
    vec = test_vector;

    // Verify that the values in Vec16c match the original values
    for (int i = 0; i < 16; ++i) {
        assert(vec[i] == values[i]);
    }

    std::cout << "test_assignment_operator passed!" << std::endl;
}

// Test type cast using static_cast
void test_static_cast_operator_int8x16_t() {
    // Test default constructor
    Vec16c vec1;
    int8x16_t result1 = static_cast<int8x16_t>(vec1);
    int8_t expected1[16] = {0};
    int8_t actual1[16];
    vst1q_s8(actual1, result1);
    for (int i = 0; i < 16; ++i) {
        assert(actual1[i] == expected1[i]);
    }
    std::cout << "test_static_cast_operator_int8x16_t passed!" << std::endl;
}

void test_load_store() {
    int8_t data[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    Vec16c vec;
    vec.load(data);
    int8_t result[16];
    vec.store(result);
    for (int i = 0; i < Vec16c::size(); ++i) {
        assert(result[i] == data[i]);
    }
    std::cout << "test_load_store passed!" << std::endl;
}

void test_load_partial() {
    // Test case 1: Load 16 elements
    int8_t data1[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    Vec16c vec1;
    vec1.load_partial(16, data1);
    for (int i = 0; i < 16; i++) {
        assert(vec1[i] == data1[i]);
    }

    // Test case 2: Load 8 elements, rest should be 0
    int8_t data2[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Vec16c vec2;
    vec2.load_partial(8, data2);
    for (int i = 0; i < 8; i++) {
        assert(vec2[i] == data2[i]);
    }
    for (int i = 8; i < 16; i++) {
        assert(vec2[i] == 0);
    }

    // Test case 3: Load 0 elements, all should be 0
    int8_t data3[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    Vec16c vec3;
    vec3.load_partial(0, data3);
    for (int i = 0; i < 16; i++) {
        assert(vec3[i] == 0);
    }

    // Test case 4: Load 4 elements, rest should be 0
    int8_t data4[4] = {1, 2, 3, 4};
    Vec16c vec4;
    vec4.load_partial(4, data4);
    for (int i = 0; i < 4; i++) {
        assert(vec4[i] == data4[i]);
    }
    for (int i = 4; i < 16; i++) {
        assert(vec4[i] == 0);
    }

    std::cout << "test_load_partial passed!" << std::endl;
}

void test_store_partial() {
    // Test case 1: Store 16 elements
    int8_t data1[16];
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    vec1.store_partial(16, data1);
    for (int i = 0; i < 16; i++) {
        assert(data1[i] == vec1[i]);
    }

    // Test case 2: Store 8 elements, rest should be unchanged
    int8_t data2[16] = {0};
    Vec16c vec2(1, 2, 3, 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0);
    vec2.store_partial(8, data2);
    for (int i = 0; i < 8; i++) {
        assert(data2[i] == vec2[i]);
    }
    for (int i = 8; i < 16; i++) {
        assert(data2[i] == 0);
    }

    // Test case 3: Store 0 elements, all should be unchanged
    int8_t data3[16] = {0};
    Vec16c vec3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    vec3.store_partial(0, data3);
    for (int i = 0; i < 16; i++) {
        assert(data3[i] == 0);
    }

    // Test case 4: Store 4 elements, rest should be unchanged
    int8_t data4[16] = {0};
    Vec16c vec4(1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    vec4.store_partial(4, data4);
    for (int i = 0; i < 4; i++) {
        assert(data4[i] == vec4[i]);
    }
    for (int i = 4; i < 16; i++) {
        assert(data4[i] == 0);
    }

    std::cout << "test_store_partial tests passed!" << std::endl;
}

/*
void test_operator_and_assignment() {

    // Test case 1: Basic AND operation
    Vec16c vec1(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    Vec16c vec2(1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0);
    vec1 &= vec2;

    for (int i = 0; i < Vec16c::size(); ++i) {
        if (vec1[i] != (1 & vec2[i])) {
            std::cerr << "Test case 1 failed at index " << i << std::endl;
            return;
        }
    }

    // Test case 2: AND operation with zero vector
    Vec16c vec3(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Vec16c vec4(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    vec3 &= vec4;

    for (int i = 0; i < Vec16c::size(); ++i) {
        if (vec3[i] != 0) {
            std::cerr << "Test case 2 failed at index " << i << std::endl;
            return;
        }
    }

    // Test case 3: AND operation with itself
    Vec16c vec5(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    vec5 &= vec5;

    for (int i = 0; i < Vec16c::size(); ++i) {
        if (vec5[i] != vec5[i]) {
            std::cerr << "Test case 3 failed at index " << i << std::endl;
            return;
        }
    }
    std::cout << "test_operator_and_assignment passed!" << std::endl;
}
*/
void test_insert_extract() {
    Vec16c vec;
    vec.insert(0, 42);
    assert(vec.extract(0) == 42);
    std::cout << "test_insert_extract passed!" << std::endl;
}

void test_cutoff() {
    Vec16c vec(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    vec.cutoff(8);
    for (int i = 0; i < 8; ++i) {
        assert(vec[i] == i + 1);
    }
    for (int i = 8; i < Vec16c::size(); ++i) {
        assert(vec[i] == 0);
    }
    std::cout << "test_cutoff passed!" << std::endl;
}

void test_operator_brackets() {
    // Test case 1: Accessing elements within bounds
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    for (int i = 0; i < 16; i++) {
        assert(vec1[i] == i + 1);
    }

    // Test case 2: Accessing elements with negative index (should wrap around)
    Vec16c vec2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    assert(vec2[-1] == 16);
    assert(vec2[-2] == 15);

    // Test case 3: Accessing elements with index greater than 15 (should wrap around)
    Vec16c vec3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    assert(vec3[16] == 1);
    assert(vec3[17] == 2);

    std::cout << "test_operator_brackets passed!" << std::endl;
}

void test_add_operator() {
    // Test case 1: Basic addition
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    Vec16c result1 = vec1 + vec2;
    for (int i = 0; i < 16; ++i) {
        assert(result1[i] == (vec1[i] + vec2[i]));
    }

    // Test case 2: Addition with zero vector
    Vec16c vec3(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Vec16c result2 = vec1 + vec3;
    for (int i = 0; i < 16; ++i) {
        assert(result2[i] == vec1[i]);
    }

    // Test case 3: Addition with negative values
    Vec16c vec4(-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16);
    Vec16c result3 = vec1 + vec4;
    for (int i = 0; i < 16; ++i) {
        assert(result3[i] == 0);
    }

    // Test case 4: Addition with mixed positive and negative values
    Vec16c vec5(1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
    Vec16c vec6(-1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -11, 12, -13, 14, -15, 16);
    Vec16c result4 = vec5 + vec6;
    for (int i = 0; i < 16; ++i) {
        assert(result4[i] == 0);
    }

    // Test case 5: Saturated addition
    Vec16c vec7(127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127);
    Vec16c vec8(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    Vec16c result5 = vec7 + vec8;
    for (int i = 0; i < 16; ++i) {
        assert(result5[i] == 127); // Saturated to 127
    }

    // Test case 6: Saturated underflow
    Vec16c vec9(-128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128, -128);
    Vec16c vec10(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
    Vec16c result6 = vec9 + vec10;
    for (int i = 0; i < 16; ++i) {
        assert(result6[i] == -128); // Saturated to -128
    }

    std::cout << "test_add_operator passed!" << std::endl;
}

void test_add_eq_operator() {
    using namespace VCL_NAMESPACE;

    // Initialize two Vec16c objects with specific values
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);

    // Use the += operator to add vec2 to vec1
    vec1 += vec2;

    // Verify that the result is correct
    for (int i = 0; i < 16; ++i) {
        assert(vec1[i] == 17);
    }

    std::cout << "test_add_eq_operator passed!" << std::endl;
}

void test_postfix_increment() {
    Vec16c vec(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec_old = vec++;
    for (int i = 0; i < 16; ++i) {
        assert(vec_old[i] == i + 1);
        assert(vec[i] == i + 2);
    }
    std::cout << "test_postfix_increment passed!" << std::endl;
}

void test_prefix_increment() {
    Vec16c vec(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    ++vec;
    for (int i = 0; i < 16; ++i) {
        assert(vec[i] == i + 2);
    }
    std::cout << "test_prefix_increment passed!" << std::endl;
}

void test_subtract_element_by_element() {
    Vec16c a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c b(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    Vec16c result = a - b;
    for (int i = 0; i < 16; ++i) {
        assert(result[i] == (a[i] - b[i]));
    }
    std::cout << "test_subtract_element_by_element passed!" << std::endl;
}

void test_unary_minus() {
    Vec16c a(1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16);
    Vec16c result = -a;
    for (int i = 0; i < 16; ++i) {
        assert(result[i] == -a[i]);
    }
    std::cout << "test_unary_minus passed!" << std::endl;
}

void test_subtract_and_assign() {
    Vec16c a(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    Vec16c b(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c c = a - b;
    a -= b;
    for (int i = 0; i < 16; ++i) {
        assert(a[i] == c[i]);
    }
    std::cout << "test_subtract_and_assign passed!" << std::endl;
}

void test_postfix_decrement() {
    Vec16c a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c a0 = a--;
    for (int i = 0; i < 16; ++i) {
        assert(a0[i] == (i + 1));
        assert(a[i] == (i));
    }
    std::cout << "test_postfix_decrement passed!" << std::endl;
}

void test_prefix_decrement() {
    Vec16c a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    --a;
    for (int i = 0; i < 16; ++i) {
        assert(a[i] == (i));
    }
    std::cout << "test_prefix_decrement passed!" << std::endl;
}

void test_multiplication() {
    // Test element-wise multiplication
    // Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    // Vec16c vec2(2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17);

    Vec16c vec1(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 127, -128, -100, -50 );
    Vec16c vec2( 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 2, 2, 2, 2 );
    Vec16c result = vec1 * vec2;

    Vec16c realResult(20, 60, 120, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, -128, -128, -100);
    for (int i = 0; i < Vec16c::size(); ++i) {
        assert(realResult[i] == result[i]);
    }

    std::cout << "test_multiplication passed!" << std::endl;
}

void test_multiplication_assignment() {
    // Test element-wise multiplication assignment
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17);
    vec1 *= vec2;

    Vec16c realResult(2, 6, 12, 20, 30, 42, 56, 72, 90, 110, 127, 127, 127, 127, 127, 127);
    for (int i = 0; i < Vec16c::size(); ++i) {
        assert(vec1[i] == realResult[i]);
    }

    std::cout << "test_multiplication_assignment passed!" << std::endl;
}
void test_shift_left() {
    // Test shift left operator
    Vec16c vec(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result = vec << 1;

    for (int i = 0; i < Vec16c::size(); ++i) {
        assert(result[i] == (vec[i] >> 1));
    }

    std::cout << "test_shift_left passed!" << std::endl;
}

void test_shift_left_assignment() {
    // Test shift left assignment operator
    Vec16c vec(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    vec <<= 1;

    for (int i = 0; i < Vec16c::size(); ++i) {
        assert(vec[i] == (i + 1) >> 1);
    }

    std::cout << "test_shift_left_assignment passed!" << std::endl;
}
void test_shift_right() {
    // Test shift right arithmetic
    Vec16c vec(16, 32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240, 255);
    Vec16c result = vec >> 1;

    for (int i = 0; i < Vec16c::size(); ++i) {
        assert(result[i] == vec[i] >> 1);
    }

    std::cout << "test_shift_right passed!" << std::endl;
}

void test_shift_right_assignment() {
    // Test shift right arithmetic assignment
    Vec16c vec(16, 32, 48, 64, 80, 96, 112, 127, 14, 16, 17, 19, 20, 22, 24, 25);
    vec >>= 1;
    Vec16c result(8, 16, 24, 32, 40, 48, 56, 63, 7, 8, 8, 9, 10, 11, 12, 12);
    for (int i = 0; i < Vec16c::size(); ++i) {
        assert(vec[i] == result[i]);
    }
    std::cout << "test_shift_right_assignment passed!" << std::endl;
}

void test_equality_operator() {
    // Test equality operator
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec3(2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17);

    Vec16uc result1 = (vec1 == vec2);
    Vec16uc result2 = (vec1 == vec3);

    for (int i = 0; i < Vec16c::size(); ++i) {
        assert(result1[i] == 0xFF); // All elements should be equal
        assert(result2[i] == 0x00); // All elements should be different
    }

    std::cout << "test_equality_operator passed!" << std::endl;
}

void test_inequality_operator() {
    // Test inequality operator
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 17);
    Vec16uc result = vec1 != vec2;

    for (int i = 0; i < Vec16c::size(); ++i) {
        if (i == 15) {
            assert(result[i] == 0xFF); // Only the last element should be different
        } else {
            assert(result[i] == 0x00); // All other elements should be equal
        }
    }

    std::cout << "test_inequality_operator passed!" << std::endl;
}

void test_operator_greater_than() {
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    Vec16uc result = vec1 > vec2;

    for (int i = 0; i < 16; ++i) {
        assert(result[i] == 0xFF);
    }
    std::cout << "test_operator_greater_than passed!" << std::endl;
}

void test_operator_less_than() {
    Vec16c vec1(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    Vec16c vec2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc result = vec1 < vec2;

    for (int i = 0; i < 16; ++i) {
        assert(result[i] == 0xFF);
    }
    std::cout << "test_operator_less_than passed!" << std::endl;
}

void test_operator_greater_equal() {
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15);
    Vec16uc result = vec1 >= vec2;
    uint8_t actual[16];
    result.store(actual);
    uint8_t expected[16] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    for (int i = 0; i < 16; ++i) {
        assert(actual[i] == expected[i]);
    }
    std::cout << "test_operator_greater_equal passed!" << std::endl;
}

void test_operator_less_equal() {
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15);
    Vec16uc result = vec1 <= vec2;
    uint8_t actual[16];
    result.store(actual);
    uint8_t expected[16] = {0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0};
    for (int i = 0; i < 16; ++i) {
        assert(actual[i] == expected[i]);
    }
    std::cout << "test_operator_less_equal passed!" << std::endl;
}

void test_operator_and() {
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15);
    Vec16c result = vec1 & vec2;
    int8_t actual[16];
    result.store(actual);
    int8_t expected[16] = {1, 0, 3, 0, 5, 4, 7, 0, 9, 8, 11, 8, 13, 12, 15, 0};
    for (int i = 0; i < 16; ++i) {
        assert(actual[i] == expected[i]);
    }
    std::cout << "test_operator_and passed!" << std::endl;
}

void test_operator_logical_and() {
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15);
    Vec16c result = vec1 && vec2;
    int8_t actual[16];
    result.store(actual);
    int8_t expected[16] = {1, 0, 3, 0, 5, 4, 7, 0, 9, 8, 11, 8, 13, 12, 15, 0};
    for (int i = 0; i < 16; ++i) {
        assert(actual[i] == expected[i]);
    }
    std::cout << "test_operator_logical_and passed!" << std::endl;
}

void test_operator_and_assign() {
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15);
    vec1 &= vec2;
    int8_t actual[16];
    vec1.store(actual);
    int8_t expected[16] = {1, 0, 3, 0, 5, 4, 7, 0, 9, 8, 11, 8, 13, 12, 15, 0};
    for (int i = 0; i < 16; ++i) {
        assert(actual[i] == expected[i]);
    }
    std::cout << "test_operator_and_assign passed!" << std::endl;
}

void test_operator_or() {
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15);
               
    Vec16c result = vec1 | vec2;
    int8_t actual[16];
    result.store(actual);
    int8_t expected[16] = {1, 3, 3, 7, 5, 7, 7, 15, 9, 11, 11, 15, 13, 15, 15, 31};
    for (int i = 0; i < 16; ++i) {
        assert(actual[i] == expected[i]);
    }
    std::cout << "test_operator_or passed!" << std::endl;
}

void test_operator_logical_or() {
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15);
               
    Vec16c result = vec1 || vec2;
    int8_t actual[16];
    result.store(actual);
    int8_t expected[16] = {1, 3, 3, 7, 5, 7, 7, 15, 9, 11, 11, 15, 13, 15, 15, 31};
    for (int i = 0; i < 16; ++i) {
        assert(actual[i] == expected[i]);
    }
    std::cout << "test_operator_logical_or passed!" << std::endl;
}

void test_operator_or_assign() {
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(1, 1, 3, 3, 5, 5, 7, 7, 9, 9, 11, 11, 13, 13, 15, 15);
    vec1 |= vec2;
    int8_t actual[16];
    vec1.store(actual);
    int8_t expected[16] = {1, 3, 3, 7, 5, 7, 7, 15, 9, 11, 11, 15, 13, 15, 15, 31};
    for (int i = 0; i < 16; ++i) {
        assert(actual[i] == expected[i]);
    }   
    std::cout << "test_operator_or_assign passed!" << std::endl;
}

void test_operator_xor() {
    // Test data
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    int8_t expected_result[16] = {17, 13, 13, 9, 9, 13, 13, 1, 1, 13, 13, 9, 9, 13, 13, 17};

    // Perform bitwise XOR
    Vec16c result = vec1 ^ vec2;

    // Store result
    int8_t result_data[16];
    result.store(result_data);

    // Verify result
    bool success = true;
    for (int i = 0; i < 16; ++i) {
        assert(result_data[i] == expected_result[i]);
    }
    std::cout << "test_operator_xor passed!" << std::endl;
}

void test_operator_xor_assignment() {
    // Test data
    Vec16c vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c vec2(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    int8_t expected_result[16] = {17, 13, 13, 9, 9, 13, 13, 1, 1, 13, 13, 9, 9, 13, 13, 17};
    // Perform bitwise XOR assignment
    vec1 ^= vec2;

    // Store result
    int8_t result_data[16];
    vec1.store(result_data);

    // Verify result
    bool success = true;
    for (int i = 0; i < 16; ++i) {
        assert(result_data[i] == expected_result[i]); 
    }
    std::cout << "test_operator_xor_assignment passed!" << std::endl;
}

void test_operator_not() {
    // Test case 1: All elements are zero
    Vec16c vec1(0);
    Vec16c result1 = ~vec1;
    for (int i = 0; i < Vec16c::size(); ++i) {
        assert(result1[i] == static_cast<int8_t>(~0));
    }

    // Test case 2: All elements are one
    Vec16c vec2(1);
    Vec16c result2 = ~vec2;
    for (int i = 0; i < Vec16c::size(); ++i) {
        assert(result2[i] == static_cast<int8_t>(~1));
    }

    // Test case 3: Mixed elements
    Vec16c vec3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result3 = ~vec3;
    for (int i = 0; i < Vec16c::size(); ++i) {
        assert(result3[i] == static_cast<int8_t>(~vec3[i]));
    }

    std::cout << "test_operator_not passed!" << std::endl;
}

void test_operator_logical_not() {
    // Test case 1: All elements are zero
    Vec16c vec1(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Vec16uc result1 = !vec1;
    for (int i = 0; i < 16; i++) {
        assert(result1[i] == 0xFF);
    }
    // Test case 2: All elements are non-zero
    Vec16c vec2(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    Vec16uc result2 = !vec2;
    for (int i = 0; i < 16; i++) {
        assert(result2[i] == 0x0);
    }
    // // Test case 3: Mixed elements
    Vec16c vec3(0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1);
    Vec16uc result3 = !vec3;
    for (int i = 0; i < 16; i++) {
        uint8_t expected = (i % 2 == 0) ? 0xFF : 0x0;
        assert(result3[i] == expected);
    }

    std::cout << "test_operator_logical_not passed!" << std::endl;
}

void test_select() {
    // Test case 1: All elements in s are true (-1)
    Vec16uc s1(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    Vec16c a1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c b1(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
    Vec16c result1 = select(s1, a1, b1);
    for (int i = 0; i < 16; ++i) {
        assert(result1[i] == a1[i]);
    }

    // Test case 2: All elements in s are false (0)
    Vec16uc s2(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Vec16c a2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c b2(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
    Vec16c result2 = select(s2, a2, b2);
    for (int i = 0; i < 16; ++i) {
        assert(result2[i] == b2[i]);
    }

    // Test case 3: Mixed elements in s
    Vec16uc s3(0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0);
    Vec16c a3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c b3(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
    Vec16c result3 = select(s3, a3, b3);
    for (int i = 0; i < 16; ++i) {
        if (i % 2 == 0) {
            assert(result3[i] == a3[i]);
        } else {
            assert(result3[i] == b3[i]);
        }
    }

    std::cout << "test_select passed!" << std::endl;
}

void test_if_add() {
    // Test case 1: All elements in f are true (-1)
    Vec16uc f1(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    Vec16c a1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c b1(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    Vec16c result1 = if_add(f1, a1, b1);
    for (int i = 0; i < 16; ++i) {
        assert(result1[i] == a1[i] + b1[i]);
    }

    // Test case 2: All elements in f are false (0)
    Vec16uc f2(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Vec16c a2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c b2(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    Vec16c result2 = if_add(f2, a2, b2);
    for (int i = 0; i < 16; ++i) {
        assert(result2[i] == a2[i]);
    }

    // Test case 3: Mixed elements in f
    Vec16uc f3(0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0);
    Vec16c a3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c b3(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    Vec16c result3 = if_add(f3, a3, b3);
    for (int i = 0; i < 16; ++i) {
        if (i % 2 == 0) {
            assert(result3[i] == a3[i] + b3[i]);
        } else {
            assert(result3[i] == a3[i]);
        }
    }

    std::cout << "test_if_add passed!" << std::endl;
}

void test_if_sub() {
    // Test case 1: All elements in f are true (-1)
    Vec16uc f1(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    Vec16c a1(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    Vec16c b1(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    Vec16c result1 = if_sub(f1, a1, b1);
    for (int i = 0; i < 16; ++i) {
        assert(result1[i] == a1[i] - b1[i]);
    }

    // Test case 2: All elements in f are false (0)
    Vec16uc f2(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Vec16c a2(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    Vec16c b2(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    Vec16c result2 = if_sub(f2, a2, b2);
    for (int i = 0; i < 16; ++i) {
        assert(result2[i] == a2[i]);
    }

    // Test case 3: Mixed elements in f
    Vec16uc f3(0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0);
    Vec16c a3(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    Vec16c b3(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    Vec16c result3 = if_sub(f3, a3, b3);
    for (int i = 0; i < 16; ++i) {
        if (i % 2 == 0) {
            assert(result3[i] == a3[i] - b3[i]);
        } else {
            assert(result3[i] == a3[i]);
        }
    }

    std::cout << "test_if_sub passed!" << std::endl;
}

void test_if_mul() {
    // Test case 1: All elements in f are true (-1)
    Vec16uc f1(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    Vec16c a1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c b1(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2);
    Vec16c result1 = if_mul(f1, a1, b1);
    for (int i = 0; i < 16; ++i) {
        assert(result1[i] == a1[i] * b1[i]);
    }

    // Test case 2: All elements in f are false (0)
    Vec16uc f2(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Vec16c a2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c b2(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2);
    Vec16c result2 = if_mul(f2, a2, b2);
    for (int i = 0; i < 16; ++i) {
        assert(result2[i] == a2[i]);
    }

    // Test case 3: Mixed elements in f
    Vec16uc f3(0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0, 0xFF, 0);
    Vec16c a3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c b3(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2);
    Vec16c result3 = if_mul(f3, a3, b3);
    for (int i = 0; i < 16; ++i) {
        if (i % 2 == 0) {
            assert(result3[i] == a3[i] * b3[i]);
        } else {
            assert(result3[i] == a3[i]);
        }
    }

    std::cout << "test_if_mul passed!" << std::endl;
}

void test_horizontal_add() {
    // Test case 1: Simple addition
    Vec16c a1(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    int32_t result1 = horizontal_add(a1);
    assert(result1 == 16);

    // Test case 2: Mixed positive and negative values
    Vec16c a2(1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8);
    int32_t result2 = horizontal_add(a2);
    assert(result2 == 0);

    // Test case 3: Larger positive values
    Vec16c a3(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 127, 127, 127, 127);
    int32_t result3 = horizontal_add(a3);
    assert(result3 == 1288);

    std::cout << "test_horizontal_add passed!" << std::endl;
}

void test_max() {
    // Test case 1: a < b
    Vec16c a1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c b1(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
    Vec16c result1 = max(a1, b1);
    for (int i = 0; i < 16; ++i) {
        assert(result1[i] == b1[i]);
    }

    // Test case 2: a > b
    Vec16c a2(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
    Vec16c b2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result2 = max(a2, b2);
    for (int i = 0; i < 16; ++i) {
        assert(result2[i] == a2[i]);
    }

    // Test case 3: a == b
    Vec16c a3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c b3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result3 = max(a3, b3);
    for (int i = 0; i < 16; ++i) {
        assert(result3[i] == a3[i]);
    }

    // Test case 4: Mixed a > b and a < b
    Vec16c a4(1, 18, 3, 20, 5, 22, 7, 24, 9, 26, 11, 28, 13, 30, 15, 32);
    Vec16c b4(17, 2, 19, 4, 21, 6, 23, 8, 25, 10, 27, 12, 29, 14, 31, 16);
    Vec16c result4 = max(a4, b4);
    for (int i = 0; i < 16; ++i) {
        assert(result4[i] == std::max(a4[i], b4[i]));
    }

    std::cout << "test_max passed!" << std::endl;
}

void test_min() {
    // Test case 1: a < b
    Vec16c a1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c b1(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
    Vec16c result1 = min(a1, b1);
    for (int i = 0; i < 16; ++i) {
        assert(result1[i] == a1[i]);
    }

    // Test case 2: a > b
    Vec16c a2(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
    Vec16c b2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result2 = min(a2, b2);
    for (int i = 0; i < 16; ++i) {
        assert(result2[i] == b2[i]);
    }

    // Test case 3: a == b
    Vec16c a3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c b3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result3 = min(a3, b3);
    for (int i = 0; i < 16; ++i) {
        assert(result3[i] == a3[i]);
    }

    // Test case 4: Mixed a > b and a < b
    Vec16c a4(1, 18, 3, 20, 5, 22, 7, 24, 9, 26, 11, 28, 13, 30, 15, 32);
    Vec16c b4(17, 2, 19, 4, 21, 6, 23, 8, 25, 10, 27, 12, 29, 14, 31, 16);
    Vec16c result4 = min(a4, b4);
    for (int i = 0; i < 16; ++i) {
        assert(result4[i] == std::min(a4[i], b4[i]));
    }

    std::cout << "test_min passed!" << std::endl;
}

void test_abs() {
    // Test case 1: All positive elements
    Vec16c a1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result1 = abs(a1);
    for (int i = 0; i < 16; ++i) {
        assert(result1[i] == a1[i]);
    }

    // Test case 2: All negative elements
    Vec16c a2(-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16);
    Vec16c result2 = abs(a2);
    for (int i = 0; i < 16; ++i) {
        assert(result2[i] == -a2[i]);
    }

    // Test case 3: Mixed positive and negative elements
    Vec16c a3(-1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -11, 12, -13, 14, -15, 16);
    Vec16c result3 = abs(a3);
    for (int i = 0; i < 16; ++i) {
        assert(result3[i] == (a3[i] >= 0 ? a3[i] : -a3[i]));
    }

    // Test case 4: Corner cases with 127 and -128
    Vec16c a4(127, -128, 0, 1, -1, 127, -128, 0, 1, -1, 127, -128, 0, 1, -1, 127);
    Vec16c result4 = abs(a4);
    for (int i = 0; i < 16; ++i) {
        assert(result4[i] == (a4[i] == -128 ? -128 : (a4[i] >= 0 ? a4[i] : -a4[i])));
    }

    std::cout << "test_abs passed!" << std::endl;
}

void test_abs_saturate() {
    // Test case 1: All positive elements
    int8x16_t a1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int8x16_t result1 = abs_saturate(a1);
    for (int i = 0; i < 16; ++i) {
        assert(result1[i] == a1[i]);
    }

    // Test case 2: All negative elements
    int8x16_t a2 = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16};
    int8x16_t result2 = abs_saturate(a2);
    for (int i = 0; i < 16; ++i) {
        assert(result2[i] == -a2[i]);
    }

    // Test case 3: Mixed positive and negative elements
    int8x16_t a3 = {-1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -11, 12, -13, 14, -15, 16};
    int8x16_t result3 = abs_saturate(a3);
    for (int i = 0; i < 16; ++i) {
        assert(result3[i] == (a3[i] >= 0 ? a3[i] : -a3[i]));
    }

    // Test case 4: Corner cases with 127 and -128
    int8x16_t a4 = {127, -128, 0, 1, -1, 127, -128, 0, 1, -1, 127, -128, 0, 1, -1, 127};
    int8x16_t result4 = abs_saturate(a4);
    for (int i = 0; i < 16; ++i) {
        assert(result4[i] == (a4[i] == -128 ? 127 : (a4[i] >= 0 ? a4[i] : -a4[i])));
    }

    std::cout << "test_abs_saturate passed!" << std::endl;
}

void test_rotate_left() {
    // Test case 1: Rotate left by 1 bit
    Vec16c a1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result1 = rotate_left(a1, 1);
    for (int i = 0; i < 16; ++i) {
        assert(result1[i] == (a1[i] << 1));
    }

    // Test case 2: Rotate left by 2 bits
    Vec16c a2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result2 = rotate_left(a2, 2);
    for (int i = 0; i < 16; ++i) {
        assert(result2[i] == (a2[i] << 2));
    }

    // Test case 3: Rotate left by 7 bits (corner case)
    Vec16c a3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result3 = rotate_left(a3, 7);
    for (int i = 0; i < 16; ++i) {
        int8_t expected = (static_cast<int8_t>(a3[i]) << 7);
        assert(result3[i] == expected);
    }

    // Test case 4: Rotate left by 8 bits (full rotation)
    Vec16c a4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result4 = rotate_left(a4, 8);
    for (int i = 0; i < 16; ++i) {
        int8_t expected = (static_cast<int8_t>(a3[i]) << 8);
        assert(result4[i] == expected);
    }

    // Test case 5: Rotate left by 0 bits (no rotation)
    Vec16c a5(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result5 = rotate_left(a5, 0);
    for (int i = 0; i < 16; ++i) {
        assert(result5[i] == a5[i]);
    }

    // Test case 6: Rotate left by 15 bits (corner case)
    Vec16c a6(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result6 = rotate_left(a6, 15);
    for (int i = 0; i < 16; ++i) {
        int8_t expected = (static_cast<int8_t>(a3[i]) << 15);
        assert(result6[i] == expected);
    }

    std::cout << "test_rotate_left passed!" << std::endl;
}

void test_rotate_right() {
    // Test case 1: Rotate right by 1 bit
    Vec16c a1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result1 = rotate_right(a1, 1);
    for (int i = 0; i < 16; ++i) {
        assert(result1[i] == (a1[i] >> 1));
    }

    // Test case 2: Rotate right by 2 bits
    Vec16c a2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result2 = rotate_right(a2, 2);
    for (int i = 0; i < 16; ++i) {
        assert(result2[i] == (a2[i] >> 2));
    }

    // Test case 3: Rotate right by 7 bits (corner case)
    Vec16c a3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result3 = rotate_right(a3, 7);
    for (int i = 0; i < 16; ++i) {
        assert(result3[i] == (a3[i] >> 7));
    }

    // Test case 4: Rotate right by 8 bits (full rotation)
    Vec16c a4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result4 = rotate_right(a4, 8);
    for (int i = 0; i < 16; ++i) {
        int8_t expected = (static_cast<int8_t>(a3[i]) >>8);
        assert(result4[i] == expected);
    }

    // Test case 5: Rotate right by 0 bits (no rotation)
    Vec16c a5(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result5 = rotate_right(a5, 0);
    for (int i = 0; i < 16; ++i) {
        assert(result5[i] == a5[i]);
    }

    // Test case 6: Rotate right by 15 bits (corner case)
    Vec16c a6(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16c result6 = rotate_right(a6, 15);
    for (int i = 0; i < 16; ++i) {
        int8_t expected = (static_cast<int8_t>(a3[i]) >>15);
        assert(result6[i] == expected);
    }

    std::cout << "test_rotate_right passed!" << std::endl;
}


int main() {
    test_default_constructor();
    test_broadcast_constructor();
    test_element_constructor();
    test_constructor_from_int8x16_t();
    test_copy_constructor();
    test_assignment_operator();
    test_static_cast_operator_int8x16_t();
    test_load_store();
    test_load_partial();
    test_store_partial();
    test_insert_extract();
    test_cutoff();
    //test_operator_and_assignment();
    test_operator_brackets();
    test_add_operator();
    test_add_eq_operator();
    test_postfix_increment();
    test_prefix_increment();
    test_subtract_element_by_element();
    test_unary_minus();
    test_subtract_and_assign();
    test_postfix_decrement();
    test_prefix_decrement();
    test_multiplication();
    test_multiplication_assignment();
    test_shift_left();
    test_shift_left_assignment();
    test_shift_right();
    test_shift_right_assignment();
    test_equality_operator();
    test_inequality_operator();
    test_operator_greater_than();
    test_operator_less_than();
    test_operator_greater_equal();
    test_operator_less_equal();
    test_operator_and();
    test_operator_logical_and();
    test_operator_and_assign();
    test_operator_or();
    test_operator_or_assign();
    test_operator_logical_or();
    test_operator_xor();
    test_operator_xor_assignment();
    test_operator_not();
    test_operator_logical_not();
    test_select();
    test_if_add();
    test_if_sub();
    test_if_mul();
    test_horizontal_add();
    test_max();
    test_min();
    test_abs();
    test_abs_saturate();
    test_rotate_left();
    test_rotate_right();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}