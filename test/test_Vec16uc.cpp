#ifndef TEST_VEC16UC_H
#define TEST_VEC16UC_H

#include "../Vec16uc.h"
#include <iostream>
#include <cassert>
using namespace VCL_NAMESPACE;
void test_default_constructor() {
    Vec16uc vec;
    uint8_t expected[16] = {0};
    uint8_t result[16];
    vec.store(result);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == expected[i]);
    }
    std::cout << "test_default_constructor passed!" << std::endl;
}

void test_broadcast_constructor() {
    Vec16uc vec(5);
    for (int i = 0; i < 16; i++) {
        assert(vec[i] == 5);
    }
    std::cout << "test_broadcast_constructor passed!" << std::endl;
}

void test_element_constructor() {
    Vec16uc vec(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    for (int i = 0; i < 16; i++) {
        assert(vec[i] == i);
    }
    std::cout << "test_element_constructor passed!" << std::endl;
}

void test_intrinsics_constructor() {
    uint8_t data[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint8x16_t intrinsic_data = vld1q_u8(data);
    Vec16uc vec(intrinsic_data);
    for (int i = 0; i < 16; i++) {
        assert(vec[i] == i);
    }
    std::cout << "test_intrinsics_constructor passed!" << std::endl;
}

void test_copy_constructor() {
    Vec16uc vec1(1);
    Vec16uc vec2(vec1);
    for (int i = 0; i < 16; i++) {
        assert(vec2[i] == 1);
    }
    std::cout << "test_copy_constructor passed!" << std::endl;
}

void test_assignment_operator() {
    uint8_t data[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint8x16_t intrinsic_data = vld1q_u8(data);
    Vec16uc vec;
    vec = intrinsic_data;
    for (int i = 0; i < 16; i++) {
        assert(vec[i] == i);
    }
    std::cout << "test_assignment_operator passed!" << std::endl;
}

void test_load_store() {
    uint8_t data[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    Vec16uc vec;
    vec.load(data);
    uint8_t result[16];
    vec.store(result);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == i);
    }
    std::cout << "test_load_store passed!" << std::endl;
}

void test_partial_load_store() {
    uint8_t data[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    Vec16uc vec;
    vec.load_partial(8, data);
    uint8_t result[16] = {0};
    vec.store_partial(8, result);
    for (int i = 0; i < 8; i++) {
        assert(result[i] == i );
    }
    for (int i = 8; i < 16; i++) {
        assert(result[i] == 0);
    }
    std::cout << "test_partial_load_store passed!" << std::endl;
}

void test_cutoff() {
    Vec16uc vec(1);
    vec.cutoff(8);
    for (int i = 0; i < 8; i++) {
        assert(vec[i] == 1);
    }
    for (int i = 8; i < 16; i++) {
        assert(vec[i] == 0);
    }
    std::cout << "test_cutoff passed!" << std::endl;
}

void test_type_cast_operator_uint8x16_t() {
    Vec16uc vec1;
    uint8x16_t result1 = static_cast<uint8x16_t>(vec1);
    uint8_t expected1[16] = {0};
    uint8_t actual1[16];
    vst1q_u8(actual1, result1);
    for (int i = 0; i < 16; ++i) {
        assert(actual1[i] == expected1[i]);
    }
    std::cout << "test_type_cast_operator_uint8x16_t passed!" << std::endl;
}

void test_store_partial() {
    // Test case 1: Store partial with n = 0
    Vec16uc vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    uint8_t result1[16] = {0};
    vec1.store_partial(0, result1);
    for (int i = 0; i < 16; i++) {
        assert(result1[i] == 0);
    }

    // Test case 2: Store partial with n = 8
    Vec16uc vec2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    uint8_t result2[16] = {0};
    vec2.store_partial(8, result2);
    for (int i = 0; i < 8; i++) {
        assert(result2[i] == i + 1);
    }
    for (int i = 8; i < 16; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: Store partial with n = 16
    Vec16uc vec3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    uint8_t result3[16] = {0};
    vec3.store_partial(16, result3);
    for (int i = 0; i < 16; i++) {
        assert(result3[i] == i + 1);
    }

    // Test case 4: Store partial with n > 16
    Vec16uc vec4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    uint8_t result4[16] = {0};
    vec4.store_partial(20, result4);
    for (int i = 0; i < 16; i++) {
        assert(result4[i] == i + 1);
    }

    std::cout << "test_store_partial passed!" << std::endl;
}

void test_extract() {
    // Test case 1: Extract element at index 0
    Vec16uc vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    assert(vec1.extract(0) == 1);

    // Test case 2: Extract element at index 15
    assert(vec1.extract(15) == 16);

    // Test case 3: Extract element at index 16 (wrap around)
    assert(vec1.extract(16) == 1);

    // Test case 4: Extract element at index -1 (wrap around)
    assert(vec1.extract(-1) == 16);

    std::cout << "test_extract passed!" << std::endl;
}

void test_operator_and_equals() {
    // Test case 1: &= operator with all elements set to 255
    Vec16uc vec1(255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255);
    Vec16uc vec2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    vec1 &= vec2;
    for (int i = 0; i < 16; i++) {
        assert(vec1[i] == vec2[i]);
    }

    // Test case 2: &= operator with all elements set to 0
    Vec16uc vec3(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Vec16uc vec4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    vec3 &= vec4;
    for (int i = 0; i < 16; i++) {
        assert(vec3[i] == 0);
    }

    std::cout << "test_operator_and_equals passed!" << std::endl;
}

void test_insert() {
    // Test case 1: Insert value at index 0
    Vec16uc vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    vec1.insert(0, 99);
    assert(vec1[0] == 99);

    // Test case 2: Insert value at index 15
    Vec16uc vec2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    vec2.insert(15, 99);
    assert(vec2[15] == 99);

    // Test case 3: Insert value at index greater than 15 (should wrap around)
    Vec16uc vec3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    vec3.insert(16, 99);
    assert(vec3[0] == 99);

    std::cout << "test_insert passed!" << std::endl;
}

void test_operator_brackets() {
    // Test case 1: Accessing elements within bounds
    Vec16uc vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    for (int i = 0; i < 16; i++) {
        assert(vec1[i] == i + 1);
    }

    // Test case 2: Accessing elements with negative index (should wrap around)
    Vec16uc vec2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    assert(vec2[-1] == 16);
    assert(vec2[-2] == 15);

    // Test case 3: Accessing elements with index greater than 15 (should wrap around)
    Vec16uc vec3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    assert(vec3[16] == 1);
    assert(vec3[17] == 2);

    std::cout << "test_operator_brackets passed!" << std::endl;
}

void test_operator_add() {
    // Test case 1: Add two vectors
    Vec16uc vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc vec2(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    Vec16uc result = vec1 + vec2;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 17);
    }

    std::cout << "test_operator_add passed!" << std::endl;
}

void test_operator_add_assign() {
    // Test case 1: Add and assign two vectors
    Vec16uc vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc vec2(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    vec1 += vec2;
    for (int i = 0; i < 16; i++) {
        assert(vec1[i] == 17);
    }

    std::cout << "test_operator_add_assign passed!" << std::endl;
}

void test_operator_postfix_increment() {
    // Test case 1: Postfix increment
    Vec16uc vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc vec2 = vec1++;
    for (int i = 0; i < 16; i++) {
        assert(vec1[i] == i + 2);
        assert(vec2[i] == i + 1);
    }

    std::cout << "test_operator_postfix_increment passed!" << std::endl;
}

void test_operator_prefix_increment() {
    // Test case 1: Prefix increment
    Vec16uc vec3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc vec4 = ++vec3;
    for (int i = 0; i < 16; i++) {
        assert(vec3[i] == i + 2);
        assert(vec4[i] == i + 2);
    }

    std::cout << "test_operator_prefix_increment passed!" << std::endl;
}

void test_operator_subtract() {
    // Test case 1: Subtract two vectors
    Vec16uc vec1(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    Vec16uc vec2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc result = vec1 - vec2;
    for (int i = 0; i < 16; i++) {
        // if (result[i] > vec1[i]) { // This indicates an underflow
        //     result[i] = 0; //FIXME should be allowed!
        // }
        // std::cout << static_cast<int>(result[i]) << std::max(0, 15 - i) << std::endl;
        assert(result[i] == std::max(0, 16 - (2*i+1)));
    }

    std::cout << "test_operator_subtract passed!" << std::endl;
}

void test_operator_subtract_assign() {
    // Test case 1: Subtract and assign two vectors
    Vec16uc vec1(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    Vec16uc vec2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    vec1 -= vec2;
    for (int i = 0; i < 16; i++) {
        assert(vec1[i] == std::max(0, 16 - (2*i+1)));
    }

    std::cout << "test_operator_subtract_assign passed!" << std::endl;
}

void test_operator_postfix_decrement() {
    // Test case 1: Postfix decrement
    Vec16uc vec(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc result = vec--;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == i + 1);
        assert(vec[i] == i);
    }

    std::cout << "test_operator_postfix_decrement passed!" << std::endl;
}

void test_operator_prefix_decrement() {
    // Test case 1: Prefix decrement
    Vec16uc vec(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc result = --vec;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == i);
        assert(vec[i] == i);
    }

    std::cout << "test_operator_prefix_decrement passed!" << std::endl;
}

void test_operator_multiply() {
    // Test case 1: Multiply two vectors
    Vec16uc vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc vec2(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2);
    Vec16uc result = vec1 * vec2;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == vec1[i] * 2);
    }

    std::cout << "test_operator_multiply passed!" << std::endl;
}

void test_operator_multiply_assign() {
    // Test case 1: Multiply and assign two vectors
    Vec16uc vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc vec2(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2);
    vec1 *= vec2;
    for (int i = 0; i < 16; i++) {
        assert(vec1[i] == (i + 1) * 2);
    }

    std::cout << "test_operator_multiply_assign passed!" << std::endl;
}

void test_operator_shift_left() {
    // Test case 1: Shift left all elements
    Vec16uc vec(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc result = vec << 1;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == vec[i] << 1);
    }

    std::cout << "test_operator_shift_left passed!" << std::endl;
}

void test_operator_shift_left_assign() {
    // Test case 1: Shift left by 1
    Vec16uc vec(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    vec <<= 1;
    for (int i = 0; i < 16; i++) {
        assert(vec[i] == (i + 1) << 1);
    }

    // Test case 2: Shift left by 2
    vec = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    vec <<= 2;
    for (int i = 0; i < 16; i++) {
        assert(vec[i] == (i + 1) << 2);
    }

    std::cout << "test_operator_shift_left_assign passed!" << std::endl;
}

void test_operator_shift_right() {
    // Test case 1: Shift right by 1
    Vec16uc vec(2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32);
    Vec16uc result = vec >> 1;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == (i + 1));
    }

    // Test case 2: Shift right by 2
    vec = Vec16uc(4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64);
    result = vec >> 2;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == (i + 1));
    }

    std::cout << "test_operator_shift_right passed!" << std::endl;
}
void test_operator_shift_right_assign() {
    // Test case 1: Shift right by 1
    Vec16uc vec(2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32);
    vec >>= 1;
    for (int i = 0; i < 16; i++) {
        assert(vec[i] == (i + 1));
    }

    // Test case 2: Shift right by 2
    vec = Vec16uc(4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64);
    vec >>= 2;
    for (int i = 0; i < 16; i++) {
        assert(vec[i] == (i + 1));
    }

    std::cout << "test_operator_shift_right_assign passed!" << std::endl;
}

void test_operator_equal() {
    // Test case 1: Equal vectors
    Vec16uc vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc vec2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc result = (vec1 == vec2);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0xFF);
    }

    // Test case 2: Different vectors
    vec2 = Vec16uc(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    result = (vec1 == vec2);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0);
    }

    std::cout << "test_operator_equal passed!" << std::endl;
}
void test_operator_not_equal() {
    // Test case 1: Vectors are not equal
    Vec16uc vec1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc vec2(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    Vec16uc result = vec1 != vec2;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0xFF);
    }

    // Test case 2: Vectors are equal
    vec2 = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    result = vec1 != vec2;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0x00);
    }

    std::cout << "test_operator_not_equal passed!" << std::endl;
}
void test_operator_greater_than() {
    // Test case 1: a > b
    Vec16uc a(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    Vec16uc b(5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105, 115, 125, 135, 145, 155);
    Vec16uc result = a > b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0xFF);
    }

    // Test case 2: a <= b
    a = Vec16uc(5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105, 115, 125, 135, 145, 155);
    b = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    result = a > b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0x00);
    }

    std::cout << "test_operator_greater_than passed!" << std::endl;
}
void test_operator_less_than() {
    // Test case 1: a < b
    Vec16uc a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc b(2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17);
    Vec16uc result = a < b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0xFF);
    }

    // Test case 2: a >= b
    a = Vec16uc(2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17);
    b = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    result = a < b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0x00);
    }

    std::cout << "test_operator_less_than passed!" << std::endl;
}
void test_operator_greater_equal() {
    // Test case 1: All elements of a are greater than or equal to b
    Vec16uc a(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    Vec16uc b(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc result = a >= b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0xFF);
    }

    // Test case 2: All elements of a are less than b
    a = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    b = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    result = a >= b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0x00);
    }

    // Test case 3: Identical elements
    a = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    b = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    result = a >= b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0xFF);
    }

    // Test case 4: Mixed elements
    a = Vec16uc(10, 5, 30, 25, 50, 45, 70, 65, 90, 85, 110, 105, 130, 125, 150, 145);
    b = Vec16uc(5, 10, 25, 30, 45, 50, 65, 70, 85, 90, 105, 110, 125, 130, 145, 150);
    result = a >= b;
    for (int i = 0; i < 16; i++) {
        if (a[i] >= b[i]) {
            assert(result[i] == 0xFF);
        } else {
            assert(result[i] == 0x00);
        }
    }

    std::cout << "test_operator_greater_equal passed!" << std::endl;
}
void test_operator_less_equal() {
    // Test case 1: All elements of a are less than or equal to b
    Vec16uc a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc b(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    Vec16uc result = a <= b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0xFF);
    }

    // Test case 2: All elements of a are greater than b
    a = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    b = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    result = a <= b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0x00);
    }

    // Test case 3: Identical elements
    a = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    b = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    result = a <= b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0xFF);
    }

    // Test case 4: Mixed elements
    a = Vec16uc(10, 5, 30, 25, 50, 45, 70, 65, 90, 85, 110, 105, 130, 125, 150, 145);
    b = Vec16uc(5, 10, 25, 30, 45, 50, 65, 70, 85, 90, 105, 110, 125, 130, 145, 150);
    result = a <= b;
    for (int i = 0; i < 16; i++) {
        if (a[i] <= b[i]) {
            assert(result[i] == 0xFF);
        } else {
            assert(result[i] == 0x00);
        }
    }

    std::cout << "test_operator_less_equal passed!" << std::endl;
}
void test_operator_bitwise_and() {
    // Test case 1: All elements of a and b are the same
    Vec16uc a(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    Vec16uc b(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    Vec16uc result = a & b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0xFF);
    }

    // Test case 2: All elements of a are 0
    a = Vec16uc(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    b = Vec16uc(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    result = a & b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0x00);
    }

    // Test case 3: Mixed elements
    a = Vec16uc(0x0F, 0xF0, 0xAA, 0x55, 0x33, 0xCC, 0x99, 0x66, 0x0F, 0xF0, 0xAA, 0x55, 0x33, 0xCC, 0x99, 0x66);
    b = Vec16uc(0xF0, 0x0F, 0x55, 0xAA, 0xCC, 0x33, 0x66, 0x99, 0xF0, 0x0F, 0x55, 0xAA, 0xCC, 0x33, 0x66, 0x99);
    result = a & b;
    Vec16uc expected(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == expected[i]);
    }

    std::cout << "test_operator_bitwise_and passed!" << std::endl;
}
void test_operator_bitwise_and_assign() {
    // Test case 1: General case
    Vec16uc a(0xFF, 0x0F, 0xF0, 0xAA, 0x55, 0x33, 0xCC, 0x99, 0x66, 0x77, 0x88, 0x11, 0x22, 0x44, 0xEE, 0xDD);
    Vec16uc b(0x0F, 0xFF, 0x0F, 0x55, 0xAA, 0xCC, 0x33, 0x66, 0x99, 0x88, 0x77, 0x22, 0x11, 0xEE, 0x44, 0xBB);
    a &= b;
    Vec16uc expected(0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x44, 0x44, 0x99);
    for (int i = 0; i < 16; i++) {
        assert(a[i] == expected[i]);
    }

    // Test case 2: All elements are zero
    a = Vec16uc(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    b = Vec16uc(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    a &= b;
    expected = Vec16uc(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    for (int i = 0; i < 16; i++) {
        assert(a[i] == expected[i]);
    }

    // Test case 3: All elements are 0xFF
    a = Vec16uc(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    b = Vec16uc(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    a &= b;
    expected = Vec16uc(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    for (int i = 0; i < 16; i++) {
        assert(a[i] == expected[i]);
    }

    // Test case 4: Mixed elements
    a = Vec16uc(0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55);
    b = Vec16uc(0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA);
    a &= b;
    expected = Vec16uc(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    for (int i = 0; i < 16; i++) {
        assert(a[i] == expected[i]);
    }

    std::cout << "test_operator_bitwise_and_assign passed!" << std::endl;
}
void test_operator_bitwise_or() {
    // Test case 1: All elements of a and b are different
    Vec16uc a(0x0F, 0x1F, 0x2F, 0x3F, 0x4F, 0x5F, 0x6F, 0x7F, 0x8F, 0x9F, 0xAF, 0xBF, 0xCF, 0xDF, 0xEF, 0xFF);
    Vec16uc b(0xF0, 0xE0, 0xD0, 0xC0, 0xB0, 0xA0, 0x90, 0x80, 0x70, 0x60, 0x50, 0x40, 0x30, 0x20, 0x10, 0x00);
    Vec16uc result = a | b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0xFF);
    }

    // Test case 2: All elements of a and b are the same
    a = Vec16uc(0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA);
    b = Vec16uc(0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55);
    result = a | b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0xFF);
    }

    // Test case 3: Mixed elements
    a = Vec16uc(0x0F, 0x1E, 0x2D, 0x3C, 0x4B, 0x5A, 0x69, 0x78, 0x87, 0x96, 0xA5, 0xB4, 0xC3, 0xD2, 0xE1, 0xF0);
    b = Vec16uc(0xF0, 0xE1, 0xD2, 0xC3, 0xB4, 0xA5, 0x96, 0x87, 0x78, 0x69, 0x5A, 0x4B, 0x3C, 0x2D, 0x1E, 0x0F);
    result = a | b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0xFF);
    }

    std::cout << "test_operator_bitwise_or passed!" << std::endl;
}
void test_operator_or_assign() {
    // Test case 1: Basic OR operation
    Vec16uc a(0x0F, 0xF0, 0xAA, 0x55, 0x00, 0xFF, 0x33, 0xCC, 0x0F, 0xF0, 0xAA, 0x55, 0x00, 0xFF, 0x33, 0xCC);
    Vec16uc b(0xF0, 0x0F, 0x55, 0xAA, 0xFF, 0x00, 0xCC, 0x33, 0xF0, 0x0F, 0x55, 0xAA, 0xFF, 0x00, 0xCC, 0x33);
    a |= b;
    Vec16uc expected(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    for (int i = 0; i < 16; i++) {
        assert(a[i] == expected[i]);
    }

    // Test case 2: OR with zero
    a = Vec16uc(0x0F, 0xF0, 0xAA, 0x55, 0x00, 0xFF, 0x33, 0xCC, 0x0F, 0xF0, 0xAA, 0x55, 0x00, 0xFF, 0x33, 0xCC);
    b = Vec16uc(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    a |= b;
    expected = Vec16uc(0x0F, 0xF0, 0xAA, 0x55, 0x00, 0xFF, 0x33, 0xCC, 0x0F, 0xF0, 0xAA, 0x55, 0x00, 0xFF, 0x33, 0xCC);
    for (int i = 0; i < 16; i++) {
        assert(a[i] == expected[i]);
    }

    // Test case 3: OR with itself
    a = Vec16uc(0x0F, 0xF0, 0xAA, 0x55, 0x00, 0xFF, 0x33, 0xCC, 0x0F, 0xF0, 0xAA, 0x55, 0x00, 0xFF, 0x33, 0xCC);
    a |= a;
    expected = Vec16uc(0x0F, 0xF0, 0xAA, 0x55, 0x00, 0xFF, 0x33, 0xCC, 0x0F, 0xF0, 0xAA, 0x55, 0x00, 0xFF, 0x33, 0xCC);
    for (int i = 0; i < 16; i++) {
        assert(a[i] == expected[i]);
    }

    std::cout << "test_operator_or_assign passed!" << std::endl;
}
void test_operator_bitwise_xor() {
    // Test case 1: All elements are different
    Vec16uc a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc b(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    Vec16uc result = a ^ b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == (a[i] ^ b[i]));
    }

    // Test case 2: All elements are the same
    a = Vec16uc(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    b = Vec16uc(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    result = a ^ b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0);
    }

    // Test case 3: Mixed elements
    a = Vec16uc(1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0);
    b = Vec16uc(0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1);
    result = a ^ b;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 1);
    }

    std::cout << "test_operator_bitwise_xor passed!" << std::endl;
}

void test_operator_xor_assign() {
    // Test case 1: Basic XOR operation
    Vec16uc a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc b(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    a ^= b;
    Vec16uc expected(17, 13, 13, 9, 9, 13, 13, 1, 1, 13, 13, 9, 9, 13, 13, 17);
    for (int i = 0; i < 16; i++) {
        assert(a[i] == expected[i]);
    }

    // Test case 2: XOR with zero
    a = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    b = Vec16uc(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    a ^= b;
    expected = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    for (int i = 0; i < 16; i++) {
        assert(a[i] == expected[i]);
    }

    // Test case 3: XOR with itself
    a = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    b = a;
    a ^= b;
    expected = Vec16uc(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    for (int i = 0; i < 16; i++) {
        assert(a[i] == expected[i]);
    }

    std::cout << "test_operator_xor_equal passed!" << std::endl;
}
void test_operator_bitwise_not() {
    // Test case 1: All elements are zero
    Vec16uc a(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Vec16uc result = ~a;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0xFF);
    }

    // Test case 2: All elements are 0xFF
    a = Vec16uc(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    result = ~a;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0x00);
    }

    // Test case 3: Mixed elements
    a = Vec16uc(0x0F, 0xF0, 0x55, 0xAA, 0x33, 0xCC, 0x99, 0x66, 0x77, 0x88, 0x11, 0xEE, 0x22, 0xDD, 0x44, 0xBB);
    result = ~a;
    uint8_t expected[16] = {0xF0, 0x0F, 0xAA, 0x55, 0xCC, 0x33, 0x66, 0x99, 0x88, 0x77, 0xEE, 0x11, 0xDD, 0x22, 0xBB, 0x44};
    for (int i = 0; i < 16; i++) {
        assert(result[i] == expected[i]);
    }

    std::cout << "test_operator_bitwise_not passed!" << std::endl;
}
void test_operator_logical_not() {
    // Test case 1: All elements are zero
    Vec16uc a(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    Vec16uc result = !a;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0xFF);
    }

    // Test case 2: No elements are zero
    a = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    result = !a;
    for (int i = 0; i < 16; i++) {
        assert(result[i] == 0x00);
    }

    // Test case 3: Mixed elements
    a = Vec16uc(0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8);
    result = !a;
    for (int i = 0; i < 16; i++) {
        if (a[i] == 0) {
            assert(result[i] == 0xFF);
        } else {
            assert(result[i] == 0x00);
        }
    }

    std::cout << "test_operator_logical_not passed!" << std::endl;
}

void test_select() {
    // Test case 1: All elements of s are true
    Vec16uc s(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    Vec16uc a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc b(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    Vec16uc result = select(s, a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == a[i]);
    }

    // Test case 2: All elements of s are false
    s = Vec16uc(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    result = select(s, a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == b[i]);
    }

    // Test case 3: Mixed elements
    s = Vec16uc(0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00);
    result = select(s, a, b);
    for (int i = 0; i < 16; i++) {
        if (s[i] == 0xFF) {
            assert(result[i] == a[i]);
        } else {
            assert(result[i] == b[i]);
        }
    }

    std::cout << "test_select passed!" << std::endl;
}
void test_if_add() {
    // Test case 1: All elements of f are true
    Vec16uc f(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    Vec16uc a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc b(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    Vec16uc result = if_add(f, a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == a[i] + b[i]);
    }

    // Test case 2: All elements of f are false
    f = Vec16uc(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    result = if_add(f, a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == a[i]);
    }

    // Test case 3: Mixed elements
    f = Vec16uc(0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00);
    result = if_add(f, a, b);
    for (int i = 0; i < 16; i++) {
        if (f[i] == 0xFF) {
            assert(result[i] == a[i] + b[i]);
        } else {
            assert(result[i] == a[i]);
        }
    }

    std::cout << "test_if_add passed!" << std::endl;
}

void test_if_sub() {
    // Test case 1: All elements of f are true
    Vec16uc f(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    Vec16uc a(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    Vec16uc b(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc result = if_sub(f, a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == (a[i] - b[i]));
    }

    // Test case 2: All elements of f are false
    f = Vec16uc(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    result = if_sub(f, a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == a[i]);
    }

    // Test case 3: Mixed elements
    f = Vec16uc(0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00);
    result = if_sub(f, a, b);
    for (int i = 0; i < 16; i++) {
        if (f[i] == 0xFF) {
            assert(result[i] == (a[i] - b[i]));
        } else {
            assert(result[i] == a[i]);
        }
    }

    std::cout << "test_if_sub passed!" << std::endl;
}

void test_if_mul() {
    // Test case 1: All elements of f are true
    Vec16uc f(0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF);
    Vec16uc a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc b(2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2);
    Vec16uc result = if_mul(f, a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == a[i] * b[i]);
    }

    // Test case 2: All elements of f are false
    f = Vec16uc(0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
    result = if_mul(f, a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == a[i]);
    }

    // Test case 3: Mixed elements
    f = Vec16uc(0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00);
    result = if_mul(f, a, b);
    for (int i = 0; i < 16; i++) {
        if (f[i] == 0xFF) {
            assert(result[i] == a[i] * b[i]);
        } else {
            assert(result[i] == a[i]);
        }
    }

    std::cout << "test_if_mul passed!" << std::endl;
}

void test_horizontal_add() {
    // Test case 1: All elements are zero
    Vec16uc a(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    uint32_t result = horizontal_add(a);
    assert(result == 0);

    // Test case 2: All elements are one
    a = Vec16uc(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    result = horizontal_add(a);
    assert(result == 16);

    // Test case 3: Sequential elements
    a = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    result = horizontal_add(a);
    assert(result == 136);

    // Test case 4: Mixed elements
    a = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    result = horizontal_add(a);
    assert(result == 1360);

    std::cout << "test_horizontal_add passed!" << std::endl;
}

void test_max() {
    // Test case 1: General case
    Vec16uc a(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    Vec16uc b(5, 25, 15, 35, 45, 55, 65, 75, 85, 95, 105, 115, 125, 135, 145, 155);
    Vec16uc result = max(a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == (a[i] > b[i] ? a[i] : b[i]));
    }

    // Test case 2: All elements of a are greater than b
    a = Vec16uc(20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170);
    b = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    result = max(a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == a[i]);
    }

    // Test case 3: All elements of b are greater than a
    a = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    b = Vec16uc(20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170);
    result = max(a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == b[i]);
    }

    // Test case 4: Identical elements
    a = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    b = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    result = max(a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == a[i]);
    }

    // Test case 5: Mixed elements
    a = Vec16uc(10, 5, 30, 25, 50, 45, 70, 65, 90, 85, 110, 105, 130, 125, 150, 145);
    b = Vec16uc(5, 10, 25, 30, 45, 50, 65, 70, 85, 90, 105, 110, 125, 130, 145, 150);
    result = max(a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == (a[i] > b[i] ? a[i] : b[i]));
    }

    std::cout << "test_max passed!" << std::endl;
}

void test_min() {
    // Test case 1: General case
    Vec16uc a(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    Vec16uc b(5, 25, 15, 35, 45, 55, 65, 75, 85, 95, 105, 115, 125, 135, 145, 155);
    Vec16uc result = min(a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == (a[i] < b[i] ? a[i] : b[i]));
    }

    // Test case 2: All elements of a are less than b
    a = Vec16uc(5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105, 115, 125, 135, 145, 155);
    b = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    result = min(a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == a[i]);
    }

    // Test case 3: All elements of b are less than a
    a = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    b = Vec16uc(5, 15, 25, 35, 45, 55, 65, 75, 85, 95, 105, 115, 125, 135, 145, 155);
    result = min(a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == b[i]);
    }

    // Test case 4: Identical elements
    a = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    b = Vec16uc(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
    result = min(a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == a[i]);
    }

    // Test case 5: Mixed elements
    a = Vec16uc(10, 5, 30, 25, 50, 45, 70, 65, 90, 85, 110, 105, 130, 125, 150, 145);
    b = Vec16uc(5, 10, 25, 30, 45, 50, 65, 70, 85, 90, 105, 110, 125, 130, 145, 150);
    result = min(a, b);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == (a[i] < b[i] ? a[i] : b[i]));
    }

    std::cout << "test_min passed!" << std::endl;
}

void test_rotate_left() {
    // Test case 1: Rotate left by 1
    Vec16uc a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    Vec16uc result = rotate_left(a, 1);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == (a[i] << 1));
    }

    // Test case 2: Rotate left by 2
    a = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    result = rotate_left(a, 2);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == (a[i] << 2));
    }

    // Test case 3: Rotate left by 0 (no change)
    a = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    result = rotate_left(a, 0);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == a[i]);
    }

    // Test case 4: Rotate left by 8 (wrap around)
    a = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    result = rotate_left(a, 8);
    for (int i = 0; i < 16; i++) {
        // FIXME 
        uint16_t ushited = static_cast<uint16_t>(a[i]) << 8;
        // std::cout << ushited << " 1 " <<((int)static_cast<uint8_t>(ushited)) << " 2 " << static_cast<uint>(result[i])<< std::endl;
        assert(result[i] == static_cast<uint8_t>(ushited));
    }

    std::cout << "test_rotate_left passed!" << std::endl;
}

void test_rotate_right() {
    // Test case 1: Rotate right by 1
    Vec16uc a(2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32);
    Vec16uc result = rotate_right(a, 1);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == (a[i] >> 1));
    }

    // Test case 2: Rotate right by 2
    a = Vec16uc(4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64);
    result = rotate_right(a, 2);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == (a[i] >> 2));
    }

    // Test case 3: Rotate right by 0 (no change)
    a = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    result = rotate_right(a, 0);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == a[i]);
    }

    // Test case 4: Rotate right by 8 (wrap around)
    a = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    result = rotate_right(a, 8);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == (a[i] >> 8));
    }

    // Test case 5: Rotate right by 15 (wrap around)
    a = Vec16uc(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    result = rotate_right(a, 15);
    for (int i = 0; i < 16; i++) {
        assert(result[i] == (a[i] >> 15));
    }
    std::cout << "test_rotate_right passed!" << std::endl;
}

int main() {
    test_default_constructor();
    test_broadcast_constructor();
    test_element_constructor();
    test_intrinsics_constructor();
    test_copy_constructor();
    test_assignment_operator();
    test_load_store();
    test_partial_load_store();
    test_cutoff();
    test_type_cast_operator_uint8x16_t();
    test_store_partial();
    test_extract();
    test_operator_and_equals();
    test_insert();
    test_operator_brackets();
    test_operator_add();
    test_operator_add_assign();
    test_operator_prefix_increment();
    test_operator_postfix_increment();
    test_operator_subtract();
    test_operator_subtract_assign();
    test_operator_postfix_decrement();
    test_operator_prefix_decrement();
    test_operator_multiply();
    test_operator_multiply_assign();
    test_operator_shift_left();
    test_operator_shift_left_assign();
    test_operator_shift_right();
    test_operator_shift_right_assign();
    test_operator_equal();
    test_operator_not_equal();
    test_operator_greater_than();
    test_operator_less_than();
    test_operator_greater_equal();
    test_operator_less_equal();
    test_operator_bitwise_and();
    test_operator_bitwise_and_assign();
    test_operator_bitwise_or();
    test_operator_or_assign();
    test_operator_bitwise_xor();
    test_operator_xor_assign();
    test_operator_bitwise_not();
    test_operator_logical_not();
    test_select();
    test_if_add();
    test_if_sub();
    test_if_mul();
    test_horizontal_add();
    test_max();
    test_min();
    test_rotate_left();
    test_rotate_right();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

#endif // TEST_VEC16UC_H