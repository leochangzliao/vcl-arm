#include "../Vec8s.h"
#include <iostream>
#include <cassert>

using namespace VCL_NAMESPACE;
void test_default_constructor() {
    // Test case 1: constructor initializes to zero
    Vec8s v;
    for(int i = 0; i < 8; i++) {
        assert(v[i] == 0);
    }
    
    //Test case 2:  multiple instances
    Vec8s v2;
    Vec8s v3;
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == 0);
        assert(v3[i] == 0);
    }

    // Test case 3:  value changes after default construction
    Vec8s v4;
    v4 = Vec8s(1,2,3,4,5,6,7,8); 
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == i+1);
    }

    // Test case 4: negative values after default construction
    Vec8s v5;
    v5 = Vec8s(-1,-2,-3,-4,-5,-6,-7,-8);
    for(int i = 0; i < 8; i++) {
        assert(v5[i] == -(i+1));
    }
    std::cout << "test_default_constructor passed!\n";
}
void test_broadcast_constructor() {
    // Test case 1: Broadcast zero
    Vec8s v1(0);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Broadcast maximum value
    Vec8s v2(0x7FFF);
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == 0x7FFF);
    }

    // Test case 3: Broadcast arbitrary value
    Vec8s v3(0x1234);
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == 0x1234);
    }

    // Test case 4: Multiple instances with different values
    Vec8s v4(0x2AAA);
    Vec8s v5(0x1555);
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == 0x2AAA);
        assert(v5[i] == 0x1555);
    }
    std::cout << "test_broadcast_constructor passed!\n";
}
void test_element_constructor() {
    // Test case 1: Ascending positive values
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == i+1);
    }

    // Test case 2: Descending positive values 
    Vec8s v2(8, 7, 6, 5, 4, 3, 2, 1);
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == 8-i);
    }

    // Test case 3: Negative values
    Vec8s v3(-1, -2, -3, -4, -5, -6, -7, -8);
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == -(i+1));
    }

    // Test case 4: Mixed positive and negative values
    Vec8s v4(-4, -3, -2, -1, 1, 2, 3, 4);
    int16_t expected[] = {-4, -3, -2, -1, 1, 2, 3, 4};
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == expected[i]);
    }

    // Test case 5: All zeros
    Vec8s v5(0, 0, 0, 0, 0, 0, 0, 0);
    for(int i = 0; i < 8; i++) {
        assert(v5[i] == 0);
    }
    std::cout << "test_element_constructor passed!\n";
}
void test_int16x8t_constructor() {
    // Test case 1: Convert from int16x8_t with basic values
    int16_t data1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int16x8_t raw1 = vld1q_s16(data1);
    Vec8s result1(raw1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == data1[i]);
    }

    // Test case 2: Convert from int16x8_t with zeros
    int16_t data2[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    int16x8_t raw2 = vld1q_s16(data2);
    Vec8s result2(raw2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: Convert from int16x8_t with negative values
    int16_t data3[8] = {-1, -2, -3, -4, -5, -6, -7, -8};
    int16x8_t raw3 = vld1q_s16(data3);
    Vec8s result3(raw3);
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == data3[i]);
    }

    // Test case 4: Convert from int16x8_t with min/max values
    int16_t data4[8] = {INT16_MIN, -1, 0, 1, INT16_MAX, INT16_MAX-1, INT16_MIN+1, 0};
    int16x8_t raw4 = vld1q_s16(data4);
    Vec8s result4(raw4);
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == data4[i]);
    }

    // Test case 5: Convert from int16x8_t with alternating values
    int16_t data5[8] = {-100, 100, -200, 200, -300, 300, -400, 400};
    int16x8_t raw5 = vld1q_s16(data5);
    Vec8s result5(raw5);
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == data5[i]);
    }
    std::cout << "test_int16x8t_constructor passed!\n";
}
void test_copy_constructor() {
    // Test case 1: Copy basic values
    Vec8s original1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s copy1(original1);
    for(int i = 0; i < 8; i++) {
        assert(copy1[i] == original1[i]);
    }

    // Test case 2: Copy zeros
    Vec8s original2(0);
    Vec8s copy2(original2);
    for(int i = 0; i < 8; i++) {
        assert(copy2[i] == 0);
    }

    // Test case 3: Copy negative values 
    Vec8s original3(-1, -2, -3, -4, -5, -6, -7, -8);
    Vec8s copy3(original3);
    for(int i = 0; i < 8; i++) {
        assert(copy3[i] == original3[i]);
    }

    // Test case 4: Copy min/max values
    Vec8s original4(INT16_MIN, -1, 0, 1, INT16_MAX, INT16_MAX-1, INT16_MIN+1, 0);
    Vec8s copy4(original4);
    for(int i = 0; i < 8; i++) {
        assert(copy4[i] == original4[i]);
    }

    // Test case 5: Modify copy should not affect original
    Vec8s original5(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s copy5(original5);
    copy5 = Vec8s(-1, -2, -3, -4, -5, -6, -7, -8);
    for(int i = 0; i < 8; i++) {
        assert(original5[i] == i+1);
        assert(copy5[i] == -(i+1));
    }
    std::cout << "test_copy_constructor passed!\n";
}
void test_assignment_operator() {
    // Test case 1: Assign basic values from int16x8_t
    int16_t data1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int16x8_t raw1 = vld1q_s16(data1);
    Vec8s v1;
    v1 = raw1;
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == data1[i]);
    }

    // Test case 2: Assign zeros
    int16_t data2[8] = {0};
    int16x8_t raw2 = vld1q_s16(data2);
    Vec8s v2;
    v2 = raw2;
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: Assign negative values
    int16_t data3[8] = {-1, -2, -3, -4, -5, -6, -7, -8};
    int16x8_t raw3 = vld1q_s16(data3);
    Vec8s v3;
    v3 = raw3;
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == data3[i]);
    }

    // Test case 4: Assign min/max values 
    int16_t data4[8] = {INT16_MIN, -1, 0, 1, INT16_MAX, INT16_MAX-1, INT16_MIN+1, 0};
    int16x8_t raw4 = vld1q_s16(data4);
    Vec8s v4;
    v4 = raw4;
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == data4[i]);
    }

    // Test case 5: Chain assignments
    int16_t data5[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    int16x8_t raw5 = vld1q_s16(data5);
    Vec8s v5, v6;
    v6 = v5 = raw5;
    for(int i = 0; i < 8; i++) {
        assert(v5[i] == data5[i]);
        assert(v6[i] == data5[i]);
    }
    std::cout << "test_assignment_operator passed!\n";
}
void test_type_cast_operator() {
    // Test case 1: Convert basic values to int16x8_t
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    int16x8_t raw1 = v1;
    int16_t data1[8];
    vst1q_s16(data1, raw1);
    for(int i = 0; i < 8; i++) {
        assert(data1[i] == i+1);
    }

    // Test case 2: Convert zeros to int16x8_t
    Vec8s v2(0);
    int16x8_t raw2 = v2;
    int16_t data2[8];
    vst1q_s16(data2, raw2);
    for(int i = 0; i < 8; i++) {
        assert(data2[i] == 0);
    }

    // Test case 3: Convert negative values to int16x8_t
    Vec8s v3(-1, -2, -3, -4, -5, -6, -7, -8);
    int16x8_t raw3 = v3;
    int16_t data3[8];
    vst1q_s16(data3, raw3);
    for(int i = 0; i < 8; i++) {
        assert(data3[i] == -(i+1));
    }

    // Test case 4: Convert min/max values to int16x8_t
    Vec8s v4(INT16_MIN, -1, 0, 1, INT16_MAX, INT16_MAX-1, INT16_MIN+1, 0);
    int16x8_t raw4 = v4;
    int16_t data4[8];
    vst1q_s16(data4, raw4);
    int16_t expected4[] = {INT16_MIN, -1, 0, 1, INT16_MAX, INT16_MAX-1, INT16_MIN+1, 0};
    for(int i = 0; i < 8; i++) {
        assert(data4[i] == expected4[i]);
    }

    // Test case 5: Convert alternating values to int16x8_t
    Vec8s v5(-100, 100, -200, 200, -300, 300, -400, 400);
    int16x8_t raw5 = v5;
    int16_t data5[8];
    vst1q_s16(data5, raw5);
    int16_t expected5[] = {-100, 100, -200, 200, -300, 300, -400, 400};
    for(int i = 0; i < 8; i++) {
        assert(data5[i] == expected5[i]);
    }
    std::cout << "test_type_cast_operator passed!\n";
}

void test_load() {
    // Test case 1: Load basic values
    int16_t data1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Vec8s v1;
    v1.load(data1);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == data1[i]);
    }

    // Test case 2: Load zeros 
    int16_t data2[8] = {0};
    Vec8s v2;
    v2.load(data2);
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: Load negative values
    int16_t data3[8] = {-1, -2, -3, -4, -5, -6, -7, -8};
    Vec8s v3;
    v3.load(data3);
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == data3[i]); 
    }

    // Test case 4: Load min/max values
    int16_t data4[8] = {INT16_MIN, -1, 0, 1, INT16_MAX, INT16_MAX-1, INT16_MIN+1, 0};
    Vec8s v4;
    v4.load(data4);
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == data4[i]);
    }

    // Test case 5: Load values then modify array
    int16_t data5[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Vec8s v5;
    v5.load(data5);
    data5[0] = 100; // Modify original array
    assert(v5[0] == 1); // Vector should keep original value
    std::cout << "test_load passed!\n";
}
void test_load_a() {
    // Test case 1: Load aligned basic values
    alignas(8) int16_t data1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Vec8s v1;
    v1.load_a(data1);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == data1[i]);
    }

    // Test case 2: Load aligned zeros
    alignas(8) int16_t data2[8] = {0};
    Vec8s v2;
    v2.load_a(data2);
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: Load aligned negative values
    alignas(8) int16_t data3[8] = {-1, -2, -3, -4, -5, -6, -7, -8};
    Vec8s v3;
    v3.load_a(data3);
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == data3[i]);
    }

    // Test case 4: Load aligned min/max values
    alignas(8) int16_t data4[8] = {INT16_MIN, -1, 0, 1, INT16_MAX, INT16_MAX-1, INT16_MIN+1, 0};
    Vec8s v4;
    v4.load_a(data4);
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == data4[i]);
    }

    // Test case 5: Load aligned values then modify array
    alignas(8) int16_t data5[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Vec8s v5;
    v5.load_a(data5);
    data5[0] = 100; // Modify original array
    assert(v5[0] == 1); // Vector should keep original value
    std::cout << "test_load_a passed!\n";
}
void test_store() {
    // Test case 1: Store basic values
    int16_t data1[8];
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    v1.store(data1);
    for(int i = 0; i < 8; i++) {
        assert(data1[i] == i+1);
    }

    // Test case 2: Store zeros
    int16_t data2[8];
    Vec8s v2(0);
    v2.store(data2);
    for(int i = 0; i < 8; i++) {
        assert(data2[i] == 0);
    }

    // Test case 3: Store negative values
    int16_t data3[8];
    Vec8s v3(-1, -2, -3, -4, -5, -6, -7, -8);
    v3.store(data3);
    for(int i = 0; i < 8; i++) {
        assert(data3[i] == -(i+1));
    }

    // Test case 4: Store min/max values
    int16_t data4[8];
    Vec8s v4(INT16_MIN, -1, 0, 1, INT16_MAX, INT16_MAX-1, INT16_MIN+1, 0);
    v4.store(data4);
    int16_t expected4[] = {INT16_MIN, -1, 0, 1, INT16_MAX, INT16_MAX-1, INT16_MIN+1, 0};
    for(int i = 0; i < 8; i++) {
        assert(data4[i] == expected4[i]);
    }

    // Test case 5: Store multiple times to same array
    int16_t data5[8];
    Vec8s v5(1, 2, 3, 4, 5, 6, 7, 8);
    v5.store(data5);
    Vec8s v6(-1, -2, -3, -4, -5, -6, -7, -8);
    v6.store(data5); // Overwrite previous values
    for(int i = 0; i < 8; i++) {
        assert(data5[i] == -(i+1));
    }
    std::cout << "test_store passed!\n";
}
void test_store_a() {
    // Test case 1: Store aligned basic values
    alignas(8) int16_t data1[8];
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    v1.store_a(data1);
    for(int i = 0; i < 8; i++) {
        assert(data1[i] == i+1);
    }

    // Test case 2: Store aligned zeros
    alignas(8) int16_t data2[8];
    Vec8s v2(0);
    v2.store_a(data2);
    for(int i = 0; i < 8; i++) {
        assert(data2[i] == 0);
    }

    // Test case 3: Store aligned negative values
    alignas(8) int16_t data3[8];
    Vec8s v3(-1, -2, -3, -4, -5, -6, -7, -8);
    v3.store_a(data3);
    for(int i = 0; i < 8; i++) {
        assert(data3[i] == -(i+1));
    }

    // Test case 4: Store aligned min/max values
    alignas(8) int16_t data4[8];
    Vec8s v4(INT16_MIN, -1, 0, 1, INT16_MAX, INT16_MAX-1, INT16_MIN+1, 0);
    v4.store_a(data4);
    int16_t expected4[] = {INT16_MIN, -1, 0, 1, INT16_MAX, INT16_MAX-1, INT16_MIN+1, 0};
    for(int i = 0; i < 8; i++) {
        assert(data4[i] == expected4[i]);
    }

    // Test case 5: Store aligned multiple times to same array
    alignas(8) int16_t data5[8];
    Vec8s v5(1, 2, 3, 4, 5, 6, 7, 8);
    v5.store_a(data5);
    Vec8s v6(-1, -2, -3, -4, -5, -6, -7, -8);
    v6.store_a(data5); // Overwrite previous values
    for(int i = 0; i < 8; i++) {
        assert(data5[i] == -(i+1));
    }
    std::cout << "test_store_a passed!\n";
}
void test_load_partial() {
    // Test case 1: Load partial with n = 0 (should set all elements to 0)
    int16_t data1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Vec8s v1;
    v1.load_partial(0, data1);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Load partial with n = 4 (should load first 4 elements and set rest to 0)
    int16_t data2[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Vec8s v2;
    v2.load_partial(4, data2);
    for(int i = 0; i < 4; i++) {
        assert(v2[i] == data2[i]);
    }
    for(int i = 4; i < 8; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: Load partial with n = 8 (should load all elements)
    int16_t data3[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Vec8s v3;
    v3.load_partial(8, data3);
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == data3[i]);
    }

    // Test case 4: Load partial with n = -1 (should set all elements to 0)
    int16_t data4[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Vec8s v4;
    v4.load_partial(-1, data4);
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == 0);
    }

    // Test case 5: Load partial with n = 3 with negative values
    int16_t data5[8] = {-1, -2, -3, -4, -5, -6, -7, -8};
    Vec8s v5;
    v5.load_partial(3, data5);
    for(int i = 0; i < 3; i++) {
        assert(v5[i] == data5[i]);
    }
    for(int i = 3; i < 8; i++) {
        assert(v5[i] == 0);
    }

    std::cout << "test_load_partial passed!\n";
}
void test_store_partial() {
    // Test case 1: Store partial with n = 0 (should store nothing)
    int16_t data1[8] = {0};
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    v1.store_partial(0, data1);
    for(int i = 0; i < 8; i++) {
        assert(data1[i] == 0);
    }

    // Test case 2: Store partial with n = 4 (should store first 4 elements)
    int16_t data2[8] = {0};
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8);
    v2.store_partial(4, data2);
    for(int i = 0; i < 4; i++) {
        assert(data2[i] == i+1);
    }
    for(int i = 4; i < 8; i++) {
        assert(data2[i] == 0);
    }

    // Test case 3: Store partial with n = 8 (should store all elements)
    int16_t data3[8] = {0};
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    v3.store_partial(8, data3);
    for(int i = 0; i < 8; i++) {
        assert(data3[i] == i+1);
    }

    // Test case 4: Store partial with n > 8 (should store only 8 elements)
    int16_t data4[12] = {0};
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    v4.store_partial(12, data4);
    for(int i = 0; i < 8; i++) {
        assert(data4[i] == i+1);
    }
    for(int i = 8; i < 12; i++) {
        assert(data4[i] == 0);
    }

    // Test case 5: Store partial with negative values
    int16_t data5[8] = {0};
    Vec8s v5(-1, -2, -3, -4, -5, -6, -7, -8);
    v5.store_partial(4, data5);
    for(int i = 0; i < 4; i++) {
        assert(data5[i] == -(i+1));
    }
    for(int i = 4; i < 8; i++) {
        assert(data5[i] == 0);
    }

    std::cout << "test_store_partial passed!\n";
}
void test_cutoff() {
    // Test case 1: n = 0 (should set all elements to 0)
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    v1.cutoff(0);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: n = 4 (should keep first 4 elements, set rest to 0)
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8);
    v2.cutoff(4);
    for(int i = 0; i < 4; i++) {
        assert(v2[i] == i+1);
    }
    for(int i = 4; i < 8; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: n = 8 (should keep all elements)
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    v3.cutoff(8);
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == i+1);
    }

    // Test case 4: n > 8 (should keep all elements)
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    v4.cutoff(10);
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == i+1);
    }

    // Test case 5: n = 3 with negative values
    Vec8s v5(-1, -2, -3, -4, -5, -6, -7, -8);
    v5.cutoff(3);
    for(int i = 0; i < 3; i++) {
        assert(v5[i] == -(i+1));
    }
    for(int i = 3; i < 8; i++) {
        assert(v5[i] == 0);
    }

    // Test case 6: chain operation test
    Vec8s v6(1, 2, 3, 4, 5, 6, 7, 8);
    v6.cutoff(4).cutoff(2);
    for(int i = 0; i < 2; i++) {
        assert(v6[i] == i+1);
    }
    for(int i = 2; i < 8; i++) {
        assert(v6[i] == 0);
    }

    std::cout << "test_cutoff passed!\n";
}
void test_and_assign_operator() {
    // Test case 1: AND with all 1s (should keep original values)
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s all_ones(0xFFFF);
    v1 &= all_ones;
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == i+1);
    }

    // Test case 2: AND with all 0s (should set all to 0)
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s all_zeros(0);
    v2 &= all_zeros;
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: AND with alternating bits
    Vec8s v3(0xFFFF);
    Vec8s alternating(0x5555);
    v3 &= alternating;
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == 0x5555);
    }

    // Test case 4: AND with negative values
    Vec8s v4(-1, -2, -3, -4, -5, -6, -7, -8);
    Vec8s mask(0x7FFF);  // Clear sign bit
    v4 &= mask;
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == ((-(i+1)) & 0x7FFF));
    }

    // Test case 5: Chain operations with different masks
    Vec8s v5(0x7FFF);  // Maximum positive value for int16_t
    v5 &= Vec8s(0x7070);  // First mask
    v5 &= Vec8s(0x7F00);  // Second mask
    for(int i = 0; i < 8; i++) {
        assert(v5[i] == 0x7000); // Should be 7000 after both masks
    }

    // Test case 6: Chain operations with all elements different
    Vec8s v6(0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888);
    Vec8s mask1(0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0);
    Vec8s mask2(0x0F0F, 0x0F0F, 0x0F0F, 0x0F0F, 0x0F0F, 0x0F0F, 0x0F0F, 0x0F0F);
    v6 &= mask1;
    v6 &= mask2;
    for(int i = 0; i < 8; i++) {
        assert(v6[i] == 0x0000); // Should be 0 after both masks
    }

    // Test case 7: Chain operations preserving certain bits (using values within INT16_MAX range)
    Vec8s v7(0x1234, 0x2345, 0x3456, 0x4567, 0x2468, 0x1357, 0x7654, 0x6543);
    v7 &= Vec8s(0x7F00); // Keep upper byte (within signed 16-bit range)
    v7 &= Vec8s(0x7000); // Keep only upper nibble
    int16_t expected[] = {0x1000, 0x2000, 0x3000, 0x4000, 0x2000, 0x1000, 0x7000, 0x6000};
    for(int i = 0; i < 8; i++) {
        assert(v7[i] == expected[i]);
    }

    std::cout << "test_and_assign_operator passed!\n";
}
void test_insert() {
    // Test case 1: Insert at beginning
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    v1.insert(0, 100);
    assert(v1[0] == 100);
    for(int i = 1; i < 8; i++) {
        assert(v1[i] == i+1);
    }

    // Test case 2: Insert at end
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8);
    v2.insert(7, 100);
    for(int i = 0; i < 7; i++) {
        assert(v2[i] == i+1);
    }
    assert(v2[7] == 100);

    // Test case 3: Insert in middle
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    v3.insert(3, 100);
    for(int i = 0; i < 3; i++) {
        assert(v3[i] == i+1);
    }
    assert(v3[3] == 100);
    for(int i = 4; i < 8; i++) {
        assert(v3[i] == i+1);
    }

    // Test case 4: Insert negative value
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    v4.insert(4, -100);
    for(int i = 0; i < 4; i++) {
        assert(v4[i] == i+1);
    }
    assert(v4[4] == -100);
    for(int i = 5; i < 8; i++) {
        assert(v4[i] == i+1);
    }

    // Test case 5: Test index wrapping (index & 0x07)
    Vec8s v5(1, 2, 3, 4, 5, 6, 7, 8);
    v5.insert(8, 100);  // 8 & 0x07 = 0
    assert(v5[0] == 100);
    for(int i = 1; i < 8; i++) {
        assert(v5[i] == i+1);
    }

    // Test case 6: Multiple inserts (without chaining)
    Vec8s v6(1, 2, 3, 4, 5, 6, 7, 8);
    v6.insert(0, 100);
    v6.insert(1, 200); 
    v6.insert(2, 300);
    assert(v6[0] == 100);
    assert(v6[1] == 200);
    assert(v6[2] == 300);
    for(int i = 3; i < 8; i++) {
        assert(v6[i] == i+1);
    }

    std::cout << "test_insert passed!\n";
}
void test_extract() {
    // Test case 1: Extract elements in order
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    for(int i = 0; i < 8; i++) {
        assert(v1.extract(i) == i+1);
    }

    // Test case 2: Extract from vector of zeros
    Vec8s v2(0);
    for(int i = 0; i < 8; i++) {
        assert(v2.extract(i) == 0);
    }

    // Test case 3: Extract from vector with negative values
    Vec8s v3(-1, -2, -3, -4, -5, -6, -7, -8);
    for(int i = 0; i < 8; i++) {
        assert(v3.extract(i) == -(i+1));
    }

    // Test case 4: Test index wrapping (index & 0x07)
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    assert(v4.extract(8) == 1);  // 8 & 0x07 = 0
    assert(v4.extract(9) == 2);  // 9 & 0x07 = 1
    assert(v4.extract(15) == 8); // 15 & 0x07 = 7

    // Test case 5: Extract from vector with min/max values
    Vec8s v5(INT16_MIN, -1, 0, 1, INT16_MAX, INT16_MAX-1, INT16_MIN+1, 0);
    assert(v5.extract(0) == INT16_MIN);
    assert(v5.extract(1) == -1);
    assert(v5.extract(2) == 0);
    assert(v5.extract(3) == 1);
    assert(v5.extract(4) == INT16_MAX);
    assert(v5.extract(5) == INT16_MAX-1);
    assert(v5.extract(6) == INT16_MIN+1);
    assert(v5.extract(7) == 0);

    std::cout << "test_extract passed!\n";
}
void test_array_subscript_operator() {
    // Test case 1: Access elements in order
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == i+1);
    }

    // Test case 2: Access from vector of zeros
    Vec8s v2(0);
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: Access from vector with negative values
    Vec8s v3(-1, -2, -3, -4, -5, -6, -7, -8);
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == -(i+1));
    }

    // Test case 4: Test index wrapping (index & 0x07)
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    assert(v4[8] == 1);  // 8 & 0x07 = 0
    assert(v4[9] == 2);  // 9 & 0x07 = 1
    assert(v4[15] == 8); // 15 & 0x07 = 7

    // Test case 5: Access from vector with min/max values
    Vec8s v5(INT16_MIN, -1, 0, 1, INT16_MAX, INT16_MAX-1, INT16_MIN+1, 0);
    assert(v5[0] == INT16_MIN);
    assert(v5[1] == -1);
    assert(v5[2] == 0);
    assert(v5[3] == 1);
    assert(v5[4] == INT16_MAX);
    assert(v5[5] == INT16_MAX-1);
    assert(v5[6] == INT16_MIN+1);
    assert(v5[7] == 0);

    std::cout << "test_subscript_operator passed!\n";
}

void test_add_operator() {
    // Test case 1: Basic addition
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v2(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8s result1 = v1 + v2;
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == (i + 2));
    }

    // Test case 2: Adding zeros (identity operation)
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s zeros(0);
    Vec8s result2 = v3 + zeros;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == v3[i]);
    }

    // Test case 3: Adding negative numbers
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v5(-1, -2, -3, -4, -5, -6, -7, -8);
    Vec8s result3 = v4 + v5;
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == 0);
    }

    // Test case 4: Testing saturation (overflow protection)
    Vec8s v6(INT16_MAX, INT16_MAX, 1, 0, INT16_MIN, INT16_MIN, -1, 0);
    Vec8s v7(1, INT16_MAX, INT16_MAX, 0, -1, INT16_MIN, INT16_MIN, 0);
    Vec8s result4 = v6 + v7;
    assert(result4[0] == INT16_MAX);  // Saturated addition
    assert(result4[1] == INT16_MAX);  // Saturated addition
    assert(result4[2] == INT16_MAX);  // Saturated addition
    assert(result4[3] == 0);          // Normal addition
    assert(result4[4] == INT16_MIN);  // Saturated addition
    assert(result4[5] == INT16_MIN);  // Saturated addition
    assert(result4[6] == INT16_MIN);  // Saturated addition
    assert(result4[7] == 0);          // Normal addition

    // Test case 5: Chained additions
    Vec8s v8(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8s result5 = v8 + v8 + v8;  // Should be (3,3,3,3,3,3,3,3)
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == 3);
    }

    std::cout << "test_add_operator passed!\n";
}
void test_add_assign_operator() {
    // Test case 1: Basic addition assignment
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v2(1, 1, 1, 1, 1, 1, 1, 1);
    v1 += v2;
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == i + 2);
    }

    // Test case 2: Adding zeros (identity operation)
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s zeros(0);
    v3 += zeros;
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == i + 1);
    }

    // Test case 3: Adding negative numbers 
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v5(-1, -2, -3, -4, -5, -6, -7, -8);
    v4 += v5;
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == 0);
    }

    // Test case 4: Testing saturation (overflow protection)
    Vec8s v6(INT16_MAX, INT16_MAX, 1, 0, INT16_MIN, INT16_MIN, -1, 0);
    Vec8s v7(1, INT16_MAX, INT16_MAX, 0, -1, INT16_MIN, INT16_MIN, 0);
    v6 += v7;
    assert(v6[0] == INT16_MAX);  // Saturated addition
    assert(v6[1] == INT16_MAX);  // Saturated addition 
    assert(v6[2] == INT16_MAX);  // Saturated addition
    assert(v6[3] == 0);          // Normal addition
    assert(v6[4] == INT16_MIN);  // Saturated addition
    assert(v6[5] == INT16_MIN);  // Saturated addition
    assert(v6[6] == INT16_MIN);  // Saturated addition
    assert(v6[7] == 0);          // Normal addition

    // Test case 5: Chained additions
    Vec8s v8(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8s v9(1, 1, 1, 1, 1, 1, 1, 1);
    v8 += v9 += v9;  // v9 becomes (2,2,2,2,2,2,2,2), then v8 becomes (3,3,3,3,3,3,3,3)
    for(int i = 0; i < 8; i++) {
        assert(v8[i] == 3);
        assert(v9[i] == 2);
    }

    std::cout << "test_add_assign_operator passed!\n";
}
void test_postfix_increment_operator() {
    // Test case 1: Basic increment
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result1 = v1++;
    // Check that result holds original values
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == i + 1);
    }
    // Check that original vector was incremented
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == i + 2);
    }

    // Test case 2: Increment zeros
    Vec8s v2(0);
    Vec8s result2 = v2++;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0);
        assert(v2[i] == 1);
    }

    // Test case 3: Increment negative values
    Vec8s v3(-8, -7, -6, -5, -4, -3, -2, -1);
    Vec8s result3 = v3++;
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == -8 + i);
        assert(v3[i] == -7 + i);
    }

    // Test case 4: Test saturation at maximum value
    Vec8s v4(INT16_MAX, INT16_MAX-1, INT16_MAX-2, 0, INT16_MIN, INT16_MIN+1, INT16_MIN+2, -1);
    Vec8s result4 = v4++;
    assert(result4[0] == INT16_MAX);
    assert(result4[1] == INT16_MAX-1);
    assert(result4[2] == INT16_MAX-2);
    assert(result4[3] == 0);
    assert(result4[4] == INT16_MIN);
    assert(result4[5] == INT16_MIN+1);
    assert(result4[6] == INT16_MIN+2);
    assert(result4[7] == -1);
    
    assert(v4[0] == INT16_MAX);     // Saturated
    assert(v4[1] == INT16_MAX);     // Saturated
    assert(v4[2] == INT16_MAX-1);
    assert(v4[3] == 1);
    assert(v4[4] == INT16_MIN+1);
    assert(v4[5] == INT16_MIN+2);
    assert(v4[6] == INT16_MIN+3);
    assert(v4[7] == 0);

    // Test case 5: Multiple increments
    Vec8s v5(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8s result5 = v5++;
    result5 = v5++;
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == 2);
        assert(v5[i] == 3);
    }

    std::cout << "test_postfix_increment_operator passed!\n";
}
void test_prefix_increment_operator() {
    // Test case 1: Basic increment
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s& result1 = ++v1;
    // Check incremented values
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == i + 2);
    }
    // Check that result references the incremented vector
    assert(&result1 == &v1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == i + 2);
    }

    // Test case 2: Increment zeros
    Vec8s v2(0);
    Vec8s& result2 = ++v2;
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == 1);
        assert(result2[i] == 1);
    }
    assert(&result2 == &v2);

    // Test case 3: Increment negative values
    Vec8s v3(-8, -7, -6, -5, -4, -3, -2, -1);
    Vec8s& result3 = ++v3;
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == -7 + i);
        assert(result3[i] == -7 + i);
    }
    assert(&result3 == &v3);

    // Test case 4: Test saturation at maximum value
    Vec8s v4(INT16_MAX, INT16_MAX-1, INT16_MAX-2, 0, INT16_MIN, INT16_MIN+1, INT16_MIN+2, -1);
    Vec8s& result4 = ++v4;
    assert(v4[0] == INT16_MAX);     // Saturated
    assert(v4[1] == INT16_MAX);     // Saturated
    assert(v4[2] == INT16_MAX-1);
    assert(v4[3] == 1);
    assert(v4[4] == INT16_MIN+1);
    assert(v4[5] == INT16_MIN+2);
    assert(v4[6] == INT16_MIN+3);
    assert(v4[7] == 0);
    
    // Check reference
    assert(&result4 == &v4);
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == v4[i]);
    }

    // Test case 5: Multiple increments
    Vec8s v5(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8s& result5 = ++v5;
    ++v5;
    for(int i = 0; i < 8; i++) {
        assert(v5[i] == 3);
        assert(result5[i] == 3);
    }
    assert(&result5 == &v5);

    std::cout << "test_prefix_increment_operator passed!\n";
}
void test_subtract_operator() {
    // Test case 1: Basic subtraction
    Vec8s v1(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8s v2(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8s result1 = v1 - v2;
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == i + 1);
    }

    // Test case 2: Subtracting zeros (identity operation)
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s zeros(0);
    Vec8s result2 = v3 - zeros;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == v3[i]);
    }

    // Test case 3: Subtracting from zeros
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result3 = zeros - v4;
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == -(i + 1));
    }

    // Test case 4: Testing saturation (underflow protection)
    Vec8s v5(INT16_MIN, INT16_MIN, 0, 1, INT16_MAX, INT16_MAX, -1, 0);
    Vec8s v6(1, INT16_MAX, 0, -1, -1, INT16_MIN, INT16_MAX, 0);
    Vec8s result4 = v5 - v6;
    assert(result4[0] == INT16_MIN);  // Saturated subtraction
    assert(result4[1] == INT16_MIN);  // Saturated subtraction
    assert(result4[2] == 0);          // Normal subtraction
    assert(result4[3] == 2);          // Normal subtraction
    assert(result4[4] == INT16_MAX);  // Saturated subtraction
    assert(result4[5] == INT16_MAX);  // Saturated subtraction
    assert(result4[6] == INT16_MIN);  // Saturated subtraction
    assert(result4[7] == 0);          // Normal subtraction

    // Test case 5: Chained subtractions
    Vec8s v7(9, 9, 9, 9, 9, 9, 9, 9);
    Vec8s v8(3, 3, 3, 3, 3, 3, 3, 3);
    Vec8s result5 = v7 - v8 - v8;  // Should be (3,3,3,3,3,3,3,3)
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == 3);
    }

    std::cout << "test_subtract_operator passed!\n";
}
void test_unary_minus_operator() {
    // Test case 1: Negate positive values
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result1 = -v1;
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == -(i + 1));
    }

    // Test case 2: Negate zero
    Vec8s v2(0);
    Vec8s result2 = -v2;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: Negate negative values
    Vec8s v3(-1, -2, -3, -4, -5, -6, -7, -8);
    Vec8s result3 = -v3;
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == i + 1);
    }

    // Test case 4: Test with minimum/maximum values
    Vec8s v4(INT16_MIN, INT16_MAX, -1, 1, INT16_MIN + 1, INT16_MAX - 1, 0, -32768);
    Vec8s result4 = -v4;
    assert(result4[0] == INT16_MIN);  // Negating INT16_MIN stays INT16_MIN due to 2's complement
    assert(result4[1] == -INT16_MAX);
    assert(result4[2] == 1);
    assert(result4[3] == -1);
    assert(result4[4] == -(INT16_MIN + 1));
    assert(result4[5] == -(INT16_MAX - 1));
    assert(result4[6] == 0);
    assert(result4[7] == INT16_MIN);

    // Test case 5: Double negation should return to original value
    Vec8s v5(1, -2, 3, -4, 5, -6, 7, -8);
    Vec8s result5 = -(-v5);
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == v5[i]);
    }

    std::cout << "test_unary_minus_operator passed!\n";
}
void test_subtract_assign_operator() {
    // Test case 1: Basic subtraction assignment
    Vec8s v1(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8s v2(1, 1, 1, 1, 1, 1, 1, 1);
    v1 -= v2;
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == i + 1);
    }

    // Test case 2: Subtracting zeros (identity operation)
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s zeros(0);
    v3 -= zeros;
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == i + 1);
    }

    // Test case 3: Subtracting to get zeros
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v5(1, 2, 3, 4, 5, 6, 7, 8);
    v4 -= v5;
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == 0);
    }

    // Test case 4: Testing saturation (underflow protection)
    Vec8s v6(INT16_MIN, INT16_MIN, 0, 1, INT16_MAX, INT16_MAX, -1, 0);
    Vec8s v7(1, INT16_MAX, 0, -1, -1, INT16_MIN, INT16_MAX, 0);
    v6 -= v7;
    assert(v6[0] == INT16_MIN);  // Saturated subtraction
    assert(v6[1] == INT16_MIN);  // Saturated subtraction
    assert(v6[2] == 0);          // Normal subtraction
    assert(v6[3] == 2);          // Normal subtraction
    assert(v6[4] == INT16_MAX);  // Saturated subtraction
    assert(v6[5] == INT16_MAX);  // Saturated subtraction
    assert(v6[6] == INT16_MIN);  // Saturated subtraction
    assert(v6[7] == 0);          // Normal subtraction

    // Test case 5: Chained subtractions
    Vec8s v8(9, 9, 9, 9, 9, 9, 9, 9);
    Vec8s v9(3, 3, 3, 3, 3, 3, 3, 3);
    v8 -= v9 -= v9;  // v9 becomes (0,0,0,0,0,0,0,0), then v8 becomes (9,9,9,9,9,9,9,9)
    for(int i = 0; i < 8; i++) {
        assert(v8[i] == 9);
        assert(v9[i] == 0);
    }

    std::cout << "test_subtract_assign_operator passed!\n";
}
void test_postfix_decrement_operator() {
    // Test case 1: Basic decrement
    Vec8s v1(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8s result1 = v1--;
    // Check that result holds original values
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == i + 2);
    }
    // Check that original vector was decremented
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == i + 1);
    }

    // Test case 2: Decrement zeros
    Vec8s v2(0);
    Vec8s result2 = v2--;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0);
        assert(v2[i] == -1);
    }

    // Test case 3: Decrement positive values to negative
    Vec8s v3(8, 7, 6, 5, 4, 3, 2, 1);
    Vec8s result3 = v3--;
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == 8 - i);
        assert(v3[i] == 7 - i);
    }

    // Test case 4: Test saturation at minimum value
    Vec8s v4(INT16_MIN, INT16_MIN+1, INT16_MIN+2, 0, INT16_MAX, INT16_MAX-1, INT16_MAX-2, 1);
    Vec8s result4 = v4--;
    assert(result4[0] == INT16_MIN);
    assert(result4[1] == INT16_MIN+1);
    assert(result4[2] == INT16_MIN+2);
    assert(result4[3] == 0);
    assert(result4[4] == INT16_MAX);
    assert(result4[5] == INT16_MAX-1);
    assert(result4[6] == INT16_MAX-2);
    assert(result4[7] == 1);
    
    assert(v4[0] == INT16_MIN);     // Saturated
    assert(v4[1] == INT16_MIN);     // Saturated
    assert(v4[2] == INT16_MIN+1);
    assert(v4[3] == -1);
    assert(v4[4] == INT16_MAX-1);
    assert(v4[5] == INT16_MAX-2);
    assert(v4[6] == INT16_MAX-3);
    assert(v4[7] == 0);

    // Test case 5: Multiple decrements
    Vec8s v5(3, 3, 3, 3, 3, 3, 3, 3);
    Vec8s result5 = v5--;
    result5 = v5--;
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == 2);
        assert(v5[i] == 1);
    }

    std::cout << "test_postfix_decrement_operator passed!\n";
}
void test_prefix_decrement_operator() {
    // Test case 1: Basic decrement
    Vec8s v1(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8s& result1 = --v1;
    // Check decremented values
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == i + 1);
    }
    // Check that result references the decremented vector
    assert(&result1 == &v1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == i + 1);
    }

    // Test case 2: Decrement zeros
    Vec8s v2(0);
    Vec8s& result2 = --v2;
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == -1);
        assert(result2[i] == -1);
    }
    assert(&result2 == &v2);

    // Test case 3: Decrement positive values to negative
    Vec8s v3(8, 7, 6, 5, 4, 3, 2, 1);
    Vec8s& result3 = --v3;
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == 7 - i);
        assert(result3[i] == 7 - i);
    }
    assert(&result3 == &v3);

    // Test case 4: Test saturation at minimum value
    Vec8s v4(INT16_MIN, INT16_MIN+1, INT16_MIN+2, 0, INT16_MAX, INT16_MAX-1, INT16_MAX-2, 1);
    Vec8s& result4 = --v4;
    assert(v4[0] == INT16_MIN);     // Saturated
    assert(v4[1] == INT16_MIN);     // Saturated
    assert(v4[2] == INT16_MIN+1);
    assert(v4[3] == -1);
    assert(v4[4] == INT16_MAX-1);
    assert(v4[5] == INT16_MAX-2);
    assert(v4[6] == INT16_MAX-3);
    assert(v4[7] == 0);
    
    // Check reference
    assert(&result4 == &v4);
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == v4[i]);
    }

    // Test case 5: Multiple decrements
    Vec8s v5(3, 3, 3, 3, 3, 3, 3, 3);
    Vec8s& result5 = --v5;
    --v5;
    for(int i = 0; i < 8; i++) {
        assert(v5[i] == 1);
        assert(result5[i] == 1);
    }
    assert(&result5 == &v5);

    std::cout << "test_prefix_decrement_operator passed!\n";
}

void test_multiply_operator() {
    // Test case 1: Basic multiplication
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v2(2, 2, 2, 2, 2, 2, 2, 2);
    Vec8s result1 = v1 * v2;
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 2 * (i + 1));
    }

    // Test case 2: Multiply by zero
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s zeros(0);
    Vec8s result2 = v3 * zeros;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: Multiply by one (identity)
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s ones(1);
    Vec8s result3 = v4 * ones;
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == i + 1);
    }

    // Test case 4: Multiply negative numbers
    Vec8s v5(-1, -2, -3, -4, 2, 3, 4, 5);
    Vec8s v6(2, 3, 4, 5, -1, -2, -3, -4);
    Vec8s result4 = v5 * v6;
    int16_t expected4[] = {-2, -6, -12, -20, -2, -6, -12, -20};
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == expected4[i]);
    }

    // Test case 5: Test saturation (overflow protection)
    Vec8s v7(INT16_MAX, INT16_MAX, INT16_MIN, INT16_MIN, 32767, -32768, 16384, -16384);
    Vec8s v8(2, INT16_MAX, 2, INT16_MIN, 2, 2, 2, 2);
    Vec8s result5 = v7 * v8;
    assert(result5[0] == INT16_MAX);  // Saturated multiplication
    assert(result5[1] == INT16_MAX);  // Saturated multiplication
    assert(result5[2] == INT16_MIN);  // Saturated multiplication
    assert(result5[3] == INT16_MAX);  // Saturated multiplication
    assert(result5[4] == INT16_MAX);  // Saturated multiplication
    assert(result5[5] == INT16_MIN);  // Saturated multiplication
    assert(result5[6] == 32767);      // 
    assert(result5[7] == -32768);     // -16384 * 2

    // Test case 6: Chained multiplications
    Vec8s v9(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8s v10(2, 2, 2, 2, 2, 2, 2, 2);
    Vec8s result6 = v9 * v10 * v10;  // Should be (4,4,4,4,4,4,4,4)
    for(int i = 0; i < 8; i++) {
        assert(result6[i] == 4);
    }

    std::cout << "test_multiply_operator passed!\n";
}
void test_multiply_assign_operator() {
    // Test case 1: Basic multiplication assignment
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v2(2, 2, 2, 2, 2, 2, 2, 2);
    v1 *= v2;
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == 2 * (i + 1));
    }

    // Test case 2: Multiply by zero
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s zeros(0);
    v3 *= zeros;
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == 0);
    }

    // Test case 3: Multiply by one (identity)
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s ones(1);
    v4 *= ones;
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == i + 1);
    }

    // Test case 4: Multiply negative numbers
    Vec8s v5(-1, -2, -3, -4, 2, 3, 4, 5);
    Vec8s v6(2, 3, 4, 5, -1, -2, -3, -4);
    v5 *= v6;
    int16_t expected[] = {-2, -6, -12, -20, -2, -6, -12, -20};
    for(int i = 0; i < 8; i++) {
        assert(v5[i] == expected[i]);
    }

    // Test case 5: Test saturation (overflow protection)
    Vec8s v7(INT16_MAX, INT16_MAX, INT16_MIN, INT16_MIN, 32767, -32768, 16384, -16384);
    Vec8s v8(2, INT16_MAX, 2, INT16_MIN, 2, 2, 2, 2);
    v7 *= v8;
    assert(v7[0] == INT16_MAX);  // Saturated multiplication
    assert(v7[1] == INT16_MAX);  // Saturated multiplication
    assert(v7[2] == INT16_MIN);  // Saturated multiplication
    assert(v7[3] == INT16_MAX);  // Saturated multiplication
    assert(v7[4] == INT16_MAX);  // Saturated multiplication
    assert(v7[5] == INT16_MIN);  // Saturated multiplication
    assert(v7[6] == 32767);      // 
    assert(v7[7] == -32768);     // -16384 * 2

    // Test case 6: Chained multiplications
    Vec8s v9(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8s v10(2, 2, 2, 2, 2, 2, 2, 2);
    v9 *= v10 *= v10;  // v10 becomes (4,4,4,4,4,4,4,4), then v9 becomes (4,4,4,4,4,4,4,4)
    for(int i = 0; i < 8; i++) {
        assert(v9[i] == 4);
        assert(v10[i] == 4);
    }

    std::cout << "test_multiply_assign_operator passed!\n";
}

void test_shift_left_operator() {
    // Test case 1: Basic shift left by 1
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result1 = v1 << 1;
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == (i + 1) * 2);
    }

    // Test case 2: Shift left by 0 (no change)
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result2 = v2 << 0;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == i + 1);
    }

    // Test case 3: Shift left by multiple positions
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result3 = v3 << 3;  // Multiply by 8
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == (i + 1) * 8);
    }

    // Test case 4: Shift left with negative numbers
    Vec8s v4(-8, -7, -6, -5, -4, -3, -2, -1);
    Vec8s result4 = v4 << 2;  // Multiply by 4
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == (-8 + i) * 4);
    }

    // Test case 5: Test overflow and saturation behavior
    Vec8s v5(16384, -16384, 32767, -32768, 1024, -1024, 8192, -8192);
    Vec8s result5 = v5 << 1;
    assert(result5[0] == -32768);    // 16384 * 2 Saturated overflows to -32768
    assert(result5[1] == -32768);   // -16384 * 2
    assert(result5[2] == -2);  // 32767 * 2 overflows to -2
    assert(result5[3] == 0);   // -32768 * 2 overflows to 0
    assert(result5[4] == 2048);     // 1024 * 2
    assert(result5[5] == -2048);    // -1024 * 2
    assert(result5[6] == 16384);    // 8192 * 2
    assert(result5[7] == -16384);   // -8192 * 2

    // Test case 6: Shift by larger values
    Vec8s v6(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result6 = v6 << 14;  // Large shift
    for(int i = 0; i < 8; i++) {
        if(i == 0 || i == 4) assert(result6[i] == 16384);      // 1,5 shift to 16384
        else if(i == 1 || i == 5) assert(result6[i] == -32768); // 2,6 shift to -32768
        else if(i == 2 || i == 6) assert(result6[i] == -16384); // 3,7 shift to -16384
        else assert(result6[i] == 0);                           // 4,8 shift to 0
    }

    // Test case 7: Chain multiple shifts
    Vec8s v7(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8s result7 = (v7 << 1) << 2;  // Shift left by 3 total
    for(int i = 0; i < 8; i++) {
        assert(result7[i] == 8);    // 1 * 2^3
    }

    // Test case 8: Shift that clears all bits
    Vec8s v8(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result8 = v8 >> 16;  // Shift beyond number of bits
    for(int i = 0; i < 8; i++) {
        assert(result8[i] == 0); // All bits should be cleared
    }
    std::cout << "test_shift_left_operator passed!\n";
}
void test_shift_left_assign_operator() {
    // Test case 1: Basic shift left assign by 1
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    v1 <<= 1;
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == (i + 1) * 2);
    }

    // Test case 2: Shift left assign by 0 (no change)
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8);
    v2 <<= 0;
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Shift left assign by multiple positions
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    v3 <<= 3;  // Multiply by 8
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == (i + 1) * 8);
    }

    // Test case 4: Shift left assign with negative numbers
    Vec8s v4(-8, -7, -6, -5, -4, -3, -2, -1);
    v4 <<= 2;  // Multiply by 4
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == (-8 + i) * 4);
    }

    // Test case 5: Test overflow behavior
    Vec8s v5(16384, -16384, 32767, -32768, 1024, -1024, 8192, -8192);
    v5 <<= 1;
    assert(v5[0] == -32768);    // 16384 * 2 Saturated overflows to -32768
    assert(v5[1] == -32768);   // -16384 * 2
    assert(v5[2] == -2);  // 32767 * 2 overflows to -2
    assert(v5[3] == 0);   // -32768 * 2 overflows to 0
    assert(v5[4] == 2048);     // 1024 * 2
    assert(v5[5] == -2048);    // -1024 * 2
    assert(v5[6] == 16384);    // 8192 * 2
    assert(v5[7] == -16384);   // -8192 * 2

    // Test case 6: Chain multiple shift assignments
    Vec8s v6(1, 1, 1, 1, 1, 1, 1, 1);
    (v6 <<= 1) <<= 2;  // Shift left by 3 total
    for(int i = 0; i < 8; i++) {
        assert(v6[i] == 8);    // 1 * 2^3
    }

    // Test case 7: Shift assign by larger values
    Vec8s v7(1, 2, 3, 4, 5, 6, 7, 8);
    v7 <<= 14;  // Large shift
    for(int i = 0; i < 8; i++) {
        if(i == 0 || i == 4) assert(v7[i] == 16384);      // 1,5 shift to 16384
        else if(i == 1 || i == 5) assert(v7[i] == -32768); // 2,6 shift to -32768
        else if(i == 2 || i == 6) assert(v7[i] == -16384); // 3,7 shift to -16384
        else assert(v7[i] == 0);                           // 4,8 shift to 0
    }

    // Test case 8: Shift that clears all bits
    Vec8s v8(1, 2, 3, 4, 5, 6, 7, 8);
    v8 >>= 16;  // Shift beyond number of bits
    for(int i = 0; i < 8; i++) {
        assert(v8[i] == 0); // All bits should be cleared
    }
    std::cout << "test_shift_left_assign_operator passed!\n";
}
void test_shift_right_operator() {
    // Test case 1: Basic shift right by 1
    Vec8s v1(2, 4, 6, 8, 10, 12, 14, 16);
    Vec8s result1 = v1 >> 1;
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == (i + 1) * 2 / 2);
    }

    // Test case 2: Shift right by 0 (no change)
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result2 = v2 >> 0;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == i + 1);
    }

    // Test case 3: Shift right by multiple positions
    Vec8s v3(8, 16, 24, 32, 40, 48, 56, 64);
    Vec8s result3 = v3 >> 3;  // Divide by 8
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == (i + 1));
    }

    // Test case 4: Shift right with negative numbers (arithmetic shift)
    Vec8s v4(-8, -16, -24, -32, -40, -48, -56, -64);
    Vec8s result4 = v4 >> 2;  // Divide by 4, preserving sign
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == (-8 - i * 8) / 4);
    }

    // Test case 5: Test sign preservation behavior
    Vec8s v5(-32768, -16384, -8192, -4096, 32767, 16384, 8192, 4096);
    Vec8s result5 = v5 >> 1;
    assert(result5[0] == -16384);  // -32768 / 2
    assert(result5[1] == -8192);   // -16384 / 2
    assert(result5[2] == -4096);   // -8192 / 2
    assert(result5[3] == -2048);   // -4096 / 2
    assert(result5[4] == 16383);   // 32767 / 2
    assert(result5[5] == 8192);    // 16384 / 2
    assert(result5[6] == 4096);    // 8192 / 2
    assert(result5[7] == 2048);    // 4096 / 2

    // Test case 6: Shift by larger values
    Vec8s v6(-32768, -16384, -8192, -4096, 32767, 16384, 8192, 4096);
    Vec8s result6 = v6 >> 14;  // Large shift
    assert(result6[0] == -2);  // Sign preserved
    assert(result6[1] == -1);  // Sign preserved
    assert(result6[2] == -1);  // Sign preserved
    assert(result6[3] == -1);  // Sign preserved
    assert(result6[4] == 1);   // Positive numbers
    assert(result6[5] == 1);
    assert(result6[6] == 0);
    assert(result6[7] == 0);

    // Test case 7: Chain multiple shifts
    Vec8s v7(64, 64, 64, 64, 64, 64, 64, 64);
    Vec8s result7 = (v7 >> 1) >> 2;  // Shift right by 3 total
    for(int i = 0; i < 8; i++) {
        assert(result7[i] == 8);    // 64 / 2^3
    }
    // Test case 8: Shift that clears all bits
    Vec8s v8(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result8 = v8 >> 16;  // Shift beyond number of bits
    for(int i = 0; i < 8; i++) {
        assert(result8[i] == 0); // All bits should be cleared
    }
    std::cout << "test_shift_right_operator passed!\n";
}
void test_shift_right_assign_operator() {
    // Test case 1: Basic shift right assign by 1
    Vec8s v1(2, 4, 6, 8, 10, 12, 14, 16);
    v1 >>= 1;
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == (i + 1) * 2 / 2);
    }

    // Test case 2: Shift right assign by 0 (no change)
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8);
    v2 >>= 0;
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Shift right assign by multiple positions
    Vec8s v3(8, 16, 24, 32, 40, 48, 56, 64);
    v3 >>= 3;  // Divide by 8
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == (i + 1));
    }

    // Test case 4: Shift right assign with negative numbers (arithmetic shift)
    Vec8s v4(-8, -16, -24, -32, -40, -48, -56, -64);
    v4 >>= 2;  // Divide by 4, preserving sign
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == (-8 - i * 8) / 4);
    }

    // Test case 5: Test sign preservation behavior
    Vec8s v5(-32768, -16384, -8192, -4096, 32767, 16384, 8192, 4096);
    v5 >>= 1;
    assert(v5[0] == -16384);  // -32768 / 2
    assert(v5[1] == -8192);   // -16384 / 2
    assert(v5[2] == -4096);   // -8192 / 2
    assert(v5[3] == -2048);   // -4096 / 2
    assert(v5[4] == 16383);   // 32767 / 2
    assert(v5[5] == 8192);    // 16384 / 2
    assert(v5[6] == 4096);    // 8192 / 2
    assert(v5[7] == 2048);    // 4096 / 2

    // Test case 6: Chain multiple shift assignments
    Vec8s v6(64, 64, 64, 64, 64, 64, 64, 64);
    (v6 >>= 1) >>= 2;  // Shift right by 3 total
    for(int i = 0; i < 8; i++) {
        assert(v6[i] == 8);    // 64 / 2^3
    }

    // Test case 7: Shift assign by larger values
    Vec8s v7(-32768, -16384, -8192, -4096, 32767, 16384, 8192, 4096);
    v7 >>= 14;  // Large shift
    assert(v7[0] == -2);  // Sign preserved
    assert(v7[1] == -1);  // Sign preserved
    assert(v7[2] == -1);  // Sign preserved
    assert(v7[3] == -1);  // Sign preserved
    assert(v7[4] == 1);   // Positive numbers
    assert(v7[5] == 1);
    assert(v7[6] == 0);
    assert(v7[7] == 0);

    // Test case 8: Shift that clears all bits
    Vec8s v8(1, 2, 3, 4, 5, 6, 7, 8);
    v8 >>= 16;  // Shift beyond number of bits
    for(int i = 0; i < 8; i++) {
        assert(v8[i] == 0);  // All bits should be cleared
    }

    std::cout << "test_shift_right_assign_operator passed!\n";
}

void test_operator_equal() {
    // Test case 1: Equal vectors
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us result1 = (v1 == v2);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0xFFFF); // All bits set when equal
    }

    // Test case 2: Different vectors
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v4(8, 7, 6, 5, 4, 3, 2, 1);
    Vec8us result2 = (v3 == v4);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0x0000); // All bits clear when not equal
    }

    // Test case 3: Partially equal vectors
    Vec8s v5(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v6(1, 2, 0, 4, 0, 6, 0, 8);
    Vec8us result3 = (v5 == v6);
    assert(result3[0] == 0xFFFF); // Equal
    assert(result3[1] == 0xFFFF); // Equal
    assert(result3[2] == 0x0000); // Not equal
    assert(result3[3] == 0xFFFF); // Equal
    assert(result3[4] == 0x0000); // Not equal
    assert(result3[5] == 0xFFFF); // Equal
    assert(result3[6] == 0x0000); // Not equal
    assert(result3[7] == 0xFFFF); // Equal

    // Test case 4: Compare with zeros
    Vec8s v7(0);
    Vec8s v8(0);
    Vec8us result4 = (v7 == v8);
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == 0xFFFF); // All equal to zero
    }

    // Test case 5: Compare with maximum values
    Vec8s v9(INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX);
    Vec8s v10(INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX);
    Vec8us result5 = (v9 == v10);
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == 0xFFFF); // All equal to INT16_MAX
    }

    std::cout << "test_equality_operator passed!\n";
}
void test_operator_not_equal() {
    // Test case 1: Equal vectors should return false
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us result1 = (v1 != v2);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0x0000); // All bits clear when equal
    }

    // Test case 2: Different vectors should return true
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v4(8, 7, 6, 5, 4, 3, 2, 1);
    Vec8us result2 = (v3 != v4);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0xFFFF); // All bits set when not equal
    }

    // Test case 3: Partially equal vectors
    Vec8s v5(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v6(1, 2, 0, 4, 0, 6, 0, 8);
    Vec8us result3 = (v5 != v6);
    assert(result3[0] == 0x0000); // Equal
    assert(result3[1] == 0x0000); // Equal
    assert(result3[2] == 0xFFFF); // Not equal
    assert(result3[3] == 0x0000); // Equal
    assert(result3[4] == 0xFFFF); // Not equal
    assert(result3[5] == 0x0000); // Equal
    assert(result3[6] == 0xFFFF); // Not equal
    assert(result3[7] == 0x0000); // Equal

    // Test case 4: Compare with zeros
    Vec8s v7(0);
    Vec8s v8(0);
    Vec8us result4 = (v7 != v8);
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == 0x0000); // None not equal to zero
    }

    // Test case 5: Compare with maximum values
    Vec8s v9(INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX);
    Vec8s v10(INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX, INT16_MAX);
    Vec8us result5 = (v9 != v10);
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == 0x0000); // None not equal to INT16_MAX
    }

    std::cout << "test_not_equal_operator passed!\n";
}
void test_greater_than_operator() {
    // Test case 1: Basic greater than comparison
    Vec8s v1(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us result1 = (v1 > v2);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0xFFFF); // All should be greater
    }

    // Test case 2: Equal values should return false
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us result2 = (v3 > v4);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0x0000); // None should be greater
    }

    // Test case 3: Mixed comparisons
    Vec8s v5(1, 3, 5, 7, 9, 11, 13, 15);
    Vec8s v6(2, 2, 6, 6, 10, 10, 14, 14);
    Vec8us result3 = (v5 > v6);
    assert(result3[0] == 0x0000); // 1 > 2
    assert(result3[1] == 0xFFFF); // 3 > 2
    assert(result3[2] == 0x0000); // 5 > 6
    assert(result3[3] == 0xFFFF); // 7 > 6
    assert(result3[4] == 0x0000); // 9 > 10
    assert(result3[5] == 0xFFFF); // 11 > 10
    assert(result3[6] == 0x0000); // 13 > 14
    assert(result3[7] == 0xFFFF); // 15 > 14

    // Test case 4: Compare with maximum and minimum values
    Vec8s v7(INT16_MAX, INT16_MAX-1, 0, -1, INT16_MIN+1, INT16_MIN, 1, -2);
    Vec8s v8(INT16_MAX-1, INT16_MAX, -1, 0, INT16_MIN, INT16_MIN+1, -2, 1);
    Vec8us result4 = (v7 > v8);
    assert(result4[0] == 0xFFFF);  // INT16_MAX > INT16_MAX-1
    assert(result4[1] == 0x0000);  // INT16_MAX-1 > INT16_MAX
    assert(result4[2] == 0xFFFF);  // 0 > -1
    assert(result4[3] == 0x0000);  // -1 > 0
    assert(result4[4] == 0xFFFF);  // INT16_MIN+1 > INT16_MIN
    assert(result4[5] == 0x0000);  // INT16_MIN > INT16_MIN+1
    assert(result4[6] == 0xFFFF);  // 1 > -2
    assert(result4[7] == 0x0000);  // -2 > 1

    // Test case 5: Compare with zeros
    Vec8s v9(1, -1, 0, 0, INT16_MAX, INT16_MIN, 500, -500);
    Vec8s zeros(0);
    Vec8us result5 = (v9 > zeros);
    assert(result5[0] == 0xFFFF);  // 1 > 0
    assert(result5[1] == 0x0000);  // -1 > 0
    assert(result5[2] == 0x0000);  // 0 > 0
    assert(result5[3] == 0x0000);  // 0 > 0
    assert(result5[4] == 0xFFFF);  // INT16_MAX > 0
    assert(result5[5] == 0x0000);  // INT16_MIN > 0
    assert(result5[6] == 0xFFFF);  // 500 > 0
    assert(result5[7] == 0x0000);  // -500 > 0

    std::cout << "test_greater_than_operator passed!\n";
}
void test_less_than_operator() {
    // Test case 1: Basic less than comparison
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v2(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8us result1 = (v1 < v2);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0xFFFF); // All should be less
    }

    // Test case 2: Equal values should return false
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us result2 = (v3 < v4);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0x0000); // None should be less
    }

    // Test case 3: Mixed comparisons
    Vec8s v5(2, 2, 6, 6, 10, 10, 14, 14);
    Vec8s v6(1, 3, 5, 7, 9, 11, 13, 15);
    Vec8us result3 = (v5 < v6);
    assert(result3[0] == 0x0000); // 2 < 1
    assert(result3[1] == 0xFFFF); // 2 < 3
    assert(result3[2] == 0x0000); // 6 < 5
    assert(result3[3] == 0xFFFF); // 6 < 7
    assert(result3[4] == 0x0000); // 10 < 9
    assert(result3[5] == 0xFFFF); // 10 < 11
    assert(result3[6] == 0x0000); // 14 < 13
    assert(result3[7] == 0xFFFF); // 14 < 15

    // Test case 4: Compare with maximum and minimum values
    Vec8s v7(INT16_MAX-1, INT16_MAX, -1, 0, INT16_MIN, INT16_MIN+1, -2, 1);
    Vec8s v8(INT16_MAX, INT16_MAX-1, 0, -1, INT16_MIN+1, INT16_MIN, 1, -2);
    Vec8us result4 = (v7 < v8);
    assert(result4[0] == 0xFFFF);  // INT16_MAX-1 < INT16_MAX
    assert(result4[1] == 0x0000);  // INT16_MAX < INT16_MAX-1
    assert(result4[2] == 0xFFFF);  // -1 < 0
    assert(result4[3] == 0x0000);  // 0 < -1
    assert(result4[4] == 0xFFFF);  // INT16_MIN < INT16_MIN+1
    assert(result4[5] == 0x0000);  // INT16_MIN+1 < INT16_MIN
    assert(result4[6] == 0xFFFF);  // -2 < 1
    assert(result4[7] == 0x0000);  // 1 < -2

    // Test case 5: Compare with zeros
    Vec8s v9(1, -1, 0, 0, INT16_MAX, INT16_MIN, 500, -500);
    Vec8s zeros(0);
    Vec8us result5 = (v9 < zeros);
    assert(result5[0] == 0x0000);  // 1 < 0
    assert(result5[1] == 0xFFFF);  // -1 < 0
    assert(result5[2] == 0x0000);  // 0 < 0
    assert(result5[3] == 0x0000);  // 0 < 0
    assert(result5[4] == 0x0000);  // INT16_MAX < 0
    assert(result5[5] == 0xFFFF);  // INT16_MIN < 0
    assert(result5[6] == 0x0000);  // 500 < 0
    assert(result5[7] == 0xFFFF);  // -500 < 0

    std::cout << "test_less_than_operator passed!\n";
}
void test_greater_than_or_equal_operator() {
    // Test case 1: Basic greater than or equal comparison
    Vec8s v1(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us result1 = (v1 >= v2);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0xFFFF); // All should be greater or equal
    }

    // Test case 2: Equal values should return true
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us result2 = (v3 >= v4);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0xFFFF); // All should be equal
    }

    // Test case 3: Mixed comparisons
    Vec8s v5(1, 3, 5, 7, 9, 11, 13, 15);
    Vec8s v6(2, 2, 6, 6, 10, 10, 14, 14);
    Vec8us result3 = (v5 >= v6);
    assert(result3[0] == 0x0000); // 1 >= 2
    assert(result3[1] == 0xFFFF); // 3 >= 2
    assert(result3[2] == 0x0000); // 5 >= 6
    assert(result3[3] == 0xFFFF); // 7 >= 6
    assert(result3[4] == 0x0000); // 9 >= 10
    assert(result3[5] == 0xFFFF); // 11 >= 10
    assert(result3[6] == 0x0000); // 13 >= 14
    assert(result3[7] == 0xFFFF); // 15 >= 14

    // Test case 4: Compare with maximum and minimum values
    Vec8s v7(INT16_MAX, INT16_MAX-1, 0, -1, INT16_MIN+1, INT16_MIN, 1, -2);
    Vec8s v8(INT16_MAX, INT16_MAX, -1, 0, INT16_MIN, INT16_MIN+1, -2, 1);
    Vec8us result4 = (v7 >= v8);
    assert(result4[0] == 0xFFFF);  // INT16_MAX >= INT16_MAX
    assert(result4[1] == 0x0000);  // INT16_MAX-1 >= INT16_MAX
    assert(result4[2] == 0xFFFF);  // 0 >= -1
    assert(result4[3] == 0x0000);  // -1 >= 0
    assert(result4[4] == 0xFFFF);  // INT16_MIN+1 >= INT16_MIN
    assert(result4[5] == 0x0000);  // INT16_MIN >= INT16_MIN+1
    assert(result4[6] == 0xFFFF);  // 1 >= -2
    assert(result4[7] == 0x0000);  // -2 >= 1

    // Test case 5: Compare with zeros
    Vec8s v9(1, -1, 0, 0, INT16_MAX, INT16_MIN, 500, -500);
    Vec8s zeros(0);
    Vec8us result5 = (v9 >= zeros);
    assert(result5[0] == 0xFFFF);  // 1 >= 0
    assert(result5[1] == 0x0000);  // -1 >= 0
    assert(result5[2] == 0xFFFF);  // 0 >= 0
    assert(result5[3] == 0xFFFF);  // 0 >= 0
    assert(result5[4] == 0xFFFF);  // INT16_MAX >= 0
    assert(result5[5] == 0x0000);  // INT16_MIN >= 0
    assert(result5[6] == 0xFFFF);  // 500 >= 0
    assert(result5[7] == 0x0000);  // -500 >= 0

    std::cout << "test_greater_than_equal_operator passed!\n";
}
void test_less_than_or_equal_operator() {
    // Test case 1: Basic less than or equal comparison
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v2(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8us result1 = (v1 <= v2);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0xFFFF); // All should be less or equal
    }

    // Test case 2: Equal values should return true
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us result2 = (v3 <= v4);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0xFFFF); // All should be equal
    }

    // Test case 3: Mixed comparisons
    Vec8s v5(2, 2, 6, 6, 10, 10, 14, 14);
    Vec8s v6(1, 3, 5, 7, 9, 11, 13, 15);
    Vec8us result3 = (v5 <= v6);
    assert(result3[0] == 0x0000); // 2 <= 1
    assert(result3[1] == 0xFFFF); // 2 <= 3
    assert(result3[2] == 0x0000); // 6 <= 5
    assert(result3[3] == 0xFFFF); // 6 <= 7
    assert(result3[4] == 0x0000); // 10 <= 9
    assert(result3[5] == 0xFFFF); // 10 <= 11
    assert(result3[6] == 0x0000); // 14 <= 13
    assert(result3[7] == 0xFFFF); // 14 <= 15

    // Test case 4: Compare with maximum and minimum values
    Vec8s v7(INT16_MAX-1, INT16_MAX, -1, 0, INT16_MIN, INT16_MIN+1, -2, 1);
    Vec8s v8(INT16_MAX, INT16_MAX-1, 0, -1, INT16_MIN+1, INT16_MIN, 1, -2);
    Vec8us result4 = (v7 <= v8);
    assert(result4[0] == 0xFFFF);  // INT16_MAX-1 <= INT16_MAX
    assert(result4[1] == 0x0000);  // INT16_MAX <= INT16_MAX-1
    assert(result4[2] == 0xFFFF);  // -1 <= 0
    assert(result4[3] == 0x0000);  // 0 <= -1
    assert(result4[4] == 0xFFFF);  // INT16_MIN <= INT16_MIN+1
    assert(result4[5] == 0x0000);  // INT16_MIN+1 <= INT16_MIN
    assert(result4[6] == 0xFFFF);  // -2 <= 1
    assert(result4[7] == 0x0000);  // 1 <= -2

    // Test case 5: Compare with zeros
    Vec8s v9(1, -1, 0, 0, INT16_MAX, INT16_MIN, 500, -500);
    Vec8s zeros(0);
    Vec8us result5 = (v9 <= zeros);
    assert(result5[0] == 0x0000);  // 1 <= 0
    assert(result5[1] == 0xFFFF);  // -1 <= 0
    assert(result5[2] == 0xFFFF);  // 0 <= 0
    assert(result5[3] == 0xFFFF);  // 0 <= 0
    assert(result5[4] == 0x0000);  // INT16_MAX <= 0
    assert(result5[5] == 0xFFFF);  // INT16_MIN <= 0
    assert(result5[6] == 0x0000);  // 500 <= 0
    assert(result5[7] == 0xFFFF);  // -500 <= 0

    std::cout << "test_less_than_equal_operator passed!\n";
}

void test_bitwise_and_operator() {
    // Test case 1: Basic AND operation with all bits set
    Vec8s v1(32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767);
    Vec8s v2(0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555);
    Vec8s result1 = v1 & v2;
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0x5555);
    }

    // Test case 2: AND with zero
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s zeros(0);
    Vec8s result2 = v3 & zeros;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: AND with alternating bits
    Vec8s v4(0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555);
    Vec8s v5(0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555);
    Vec8s result3 = v4 & v5;
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == 0x5555);
    }

    // Test case 4: AND with negative numbers
    Vec8s v6(-1, -2, -3, -4, -5, -6, -7, -8);
    Vec8s v7(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result4 = v6 & v7;
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == ((-1-i) & (i+1)));
    }

    // Test case 5: AND with maximum values
    Vec8s v8(32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767);
    Vec8s v9(0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF);
    Vec8s result5 = v8 & v9;
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == 0x7FFF);
    }

    std::cout << "test_bitwise_and_operator passed!\n";
}
void test_bitwise_or_operator() {
    // Test case 1: Basic OR operation with bits
    Vec8s v1(0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555);
    Vec8s v2(0x2AAA, 0x2AAA, 0x2AAA, 0x2AAA, 0x2AAA, 0x2AAA, 0x2AAA, 0x2AAA);
    Vec8s result1 = v1 | v2;
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0x7FFF); // Maximum positive value
    }

    // Test case 2: OR with zero (identity operation)
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s zeros(0);
    Vec8s result2 = v3 | zeros;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == i + 1);
    }

    // Test case 3: OR with all bits set
    Vec8s v4(0x1234, 0x5678, 0x3ABC, 0x5EF0, 0x1122, 0x3344, 0x5566, 0x7788);
    Vec8s all_ones(0x7FFF);
    Vec8s result3 = v4 | all_ones;
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == 0x7FFF); // All results should be max positive value
    }

    // Test case 4: OR with negative numbers
    Vec8s v5(-1, -2, -3, -4, -5, -6, -7, -8);
    Vec8s v6(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result4 = v5 | v6;
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == ((-1-i) | (i+1)));
    }

    // Test case 5: OR with maximum/minimum values
    Vec8s v7(32767, -32768, 0x7FFF, 0x4000, 0x3333, 0x4CCC, 0x0F0F, 0x70F0);
    Vec8s v8(0x5555, 0x2AAA, 0x3333, 0x4CCC, 0x0F0F, 0x70F0, 0x00FF, 0x7F00);
    Vec8s result5 = v7 | v8;
    assert(result5[0] == (32767 | 0x5555));
    assert(result5[1] == (-32768 | 0x2AAA));
    assert(result5[2] == (0x7FFF | 0x3333));
    assert(result5[3] == (0x4000 | 0x4CCC));
    assert(result5[4] == (0x3333 | 0x0F0F));
    assert(result5[5] == (0x4CCC | 0x70F0));
    assert(result5[6] == (0x0F0F | 0x00FF));
    assert(result5[7] == (0x70F0 | 0x7F00));

    std::cout << "test_bitwise_or_operator passed!\n";
}
void test_bitwise_xor_operator() {
    // Test case 1: Basic XOR operation with alternating bits
    Vec8s v1(0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555);
    Vec8s v2(0x2AAA, 0x2AAA, 0x2AAA, 0x2AAA, 0x2AAA, 0x2AAA, 0x2AAA, 0x2AAA);
    Vec8s result1 = v1 ^ v2;
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0x7FFF); // All bits set up to max signed value
    }

    // Test case 2: XOR with zero (identity operation)
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8); 
    Vec8s zeros(0);
    Vec8s result2 = v3 ^ zeros;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == i + 1);
    }

    // Test case 3: XOR with self (should be zero)
    Vec8s v4(0x1234, 0x5678, 0x3ABC, 0x5EF0, 0x1122, 0x3344, 0x5566, 0x7788);
    Vec8s result3 = v4 ^ v4;
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == 0); // XOR with self gives 0
    }

    // Test case 4: XOR with negative numbers
    Vec8s v5(-1, -2, -3, -4, -5, -6, -7, -8);
    Vec8s v6(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result4 = v5 ^ v6;
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == ((-1-i) ^ (i+1)));
    }

    // Test case 5: XOR with maximum/minimum values
    Vec8s v7(32767, -32768, 0x7FFF, 0x4000, 0x3333, 0x4CCC, 0x0F0F, 0x70F0);
    Vec8s v8(0x5555, 0x2AAA, 0x3333, 0x4CCC, 0x0F0F, 0x70F0, 0x00FF, 0x7F00);
    Vec8s result5 = v7 ^ v8;
    assert(result5[0] == (32767 ^ 0x5555));
    assert(result5[1] == (-32768 ^ 0x2AAA));
    assert(result5[2] == (0x7FFF ^ 0x3333));
    assert(result5[3] == (0x4000 ^ 0x4CCC));
    assert(result5[4] == (0x3333 ^ 0x0F0F));
    assert(result5[5] == (0x4CCC ^ 0x70F0));
    assert(result5[6] == (0x0F0F ^ 0x00FF));
    assert(result5[7] == (0x70F0 ^ 0x7F00));

    std::cout << "test_bitwise_xor_operator passed!\n";
}
void test_bitwise_not_operator() {
    // Test case 1: NOT on zeros (should give all ones)
    Vec8s v1(0);
    Vec8s result1 = ~v1;
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == -1); // All bits set (-1 in two's complement)
    }

    // Test case 2: NOT on all ones (should give zeros) 
    Vec8s v2(-1);  // All bits set
    Vec8s result2 = ~v2;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: NOT on alternating bits
    Vec8s v3(0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555);
    Vec8s result3 = ~v3;
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == (int16_t)0xAAAA); // Cast to signed for proper comparison
    }

    // Test case 4: NOT on positive numbers
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result4 = ~v4;
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == ~(int16_t)(i + 1));
    }

    // Test case 5: NOT on max/min values
    Vec8s v5(INT16_MAX, INT16_MIN, 0x7FFF, 0x8000, 0x3333, 0xCCCC, 0x0F0F, 0xF0F0);
    Vec8s result5 = ~v5;
    assert(result5[0] == ~INT16_MAX);     // NOT on maximum positive value
    assert(result5[1] == ~INT16_MIN);     // NOT on minimum negative value
    assert(result5[2] == (int16_t)0x8000); // NOT on 0x7FFF
    assert(result5[3] == (int16_t)0x7FFF); // NOT on 0x8000
    assert(result5[4] == (int16_t)0xCCCC); // NOT on 0x3333
    assert(result5[5] == (int16_t)0x3333); // NOT on 0xCCCC
    assert(result5[6] == (int16_t)0xF0F0); // NOT on 0x0F0F
    assert(result5[7] == (int16_t)0x0F0F); // NOT on 0xF0F0

    std::cout << "test_bitwise_not_operator passed!\n";
}

void test_select() {
    // Test case 1: Basic selection with all true mask
    Vec8us mask1(0xFFFF);  // All bits set (true)
    Vec8s a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s b1(-1, -2, -3, -4, -5, -6, -7, -8);
    Vec8s result1 = select(mask1, a1, b1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == i + 1);  // Should select all from a1
    }

    // Test case 2: Basic selection with all false mask
    Vec8us mask2(0);  // All bits clear (false)
    Vec8s a2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s b2(-1, -2, -3, -4, -5, -6, -7, -8);
    Vec8s result2 = select(mask2, a2, b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == -(i + 1));  // Should select all from b2
    }

    // Test case 3: Alternating selection
    Vec8us mask3(0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0);
    Vec8s a3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s b3(-1, -2, -3, -4, -5, -6, -7, -8);
    Vec8s result3 = select(mask3, a3, b3);
    assert(result3[0] == 1);   // From a3
    assert(result3[1] == -2);  // From b3
    assert(result3[2] == 3);   // From a3
    assert(result3[3] == -4);  // From b3
    assert(result3[4] == 5);   // From a3
    assert(result3[5] == -6);  // From b3
    assert(result3[6] == 7);   // From a3
    assert(result3[7] == -8);  // From b3

    // Test case 4: Selection with special values
    Vec8us mask4(0xFFFF, 0xFFFF, 0, 0, 0xFFFF, 0, 0xFFFF, 0);
    Vec8s a4(INT16_MAX, INT16_MIN, 0x7FFF, 0x8000, -1, 32767, -32768, 0);
    Vec8s b4(-32768, 32767, -1, 0, INT16_MIN, INT16_MAX, 0, 1);
    Vec8s result4 = select(mask4, a4, b4);
    assert(result4[0] == INT16_MAX);  // From a4
    assert(result4[1] == INT16_MIN);  // From a4
    assert(result4[2] == -1);         // From b4
    assert(result4[3] == 0);          // From b4
    assert(result4[4] == -1);         // From a4
    assert(result4[5] == INT16_MAX);  // From b4
    assert(result4[6] == -32768);     // From a4
    assert(result4[7] == 1);          // From b4

    // Test case 5: Selection with zeros and ones
    Vec8us mask5(0xFFFF);  // All bits set
    Vec8s a5(0);          // All zeros
    Vec8s b5(1);          // All ones
    Vec8s result5 = select(mask5, a5, b5);
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == 0);  // Should select all zeros from a5
    }

    std::cout << "test_select passed!\n";
}
void test_if_add() {
    // Test case 1: Basic conditional add with all true mask
    Vec8us mask1(0xFFFF);  // All bits set (true)
    Vec8s a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s b1(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8s result1 = if_add(mask1, a1, b1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == i + 2);  // Should add all elements
    }

    // Test case 2: Conditional add with all false mask
    Vec8us mask2(0);  // All bits clear (false)
    Vec8s a2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s b2(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8s result2 = if_add(mask2, a2, b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == i + 1);  // Should not add anything
    }

    // Test case 3: Alternating conditional add
    Vec8us mask3(0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0);
    Vec8s a3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s b3(10, 20, 30, 40, 50, 60, 70, 80);
    Vec8s result3 = if_add(mask3, a3, b3);
    assert(result3[0] == 11);  // 1 + 10
    assert(result3[1] == 2);   // 2 + 0
    assert(result3[2] == 33);  // 3 + 30
    assert(result3[3] == 4);   // 4 + 0
    assert(result3[4] == 55);  // 5 + 50
    assert(result3[5] == 6);   // 6 + 0
    assert(result3[6] == 77);  // 7 + 70
    assert(result3[7] == 8);   // 8 + 0

    // Test case 4: Test saturation behavior
    Vec8us mask4(0xFFFF);
    Vec8s a4(INT16_MAX, INT16_MAX-1, INT16_MIN, INT16_MIN+1, 0, -1, 32767, -32768);
    Vec8s b4(1, 2, -1, -2, INT16_MAX, INT16_MIN, 1, -1);
    Vec8s result4 = if_add(mask4, a4, b4);
    assert(result4[0] == INT16_MAX);      // Saturated addition
    assert(result4[1] == INT16_MAX);      // Saturated addition
    assert(result4[2] == INT16_MIN);      // Saturated addition
    assert(result4[3] == INT16_MIN);      // Saturated addition
    assert(result4[4] == INT16_MAX);      // 0 + INT16_MAX
    assert(result4[5] == INT16_MIN);      // -1 + INT16_MIN
    assert(result4[6] == INT16_MAX);      // Saturated addition
    assert(result4[7] == INT16_MIN);      // Saturated addition

    // Test case 5: Test with zero operands
    Vec8us mask5(0xFFFF);
    Vec8s a5(0);
    Vec8s b5(0);
    Vec8s result5 = if_add(mask5, a5, b5);
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == 0);  // 0 + 0 should be 0
    }

    std::cout << "test_if_add passed!\n";
}
void test_if_sub() {
    // Test case 1: Basic conditional subtract with all true mask
    Vec8us mask1(0xFFFF);  // All bits set (true)
    Vec8s a1(10, 20, 30, 40, 50, 60, 70, 80);
    Vec8s b1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result1 = if_sub(mask1, a1, b1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 10*(i+1) - (i+1));  // Should subtract all elements
    }

    // Test case 2: Conditional subtract with all false mask
    Vec8us mask2(0);  // All bits clear (false)
    Vec8s a2(10, 20, 30, 40, 50, 60, 70, 80);
    Vec8s b2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result2 = if_sub(mask2, a2, b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 10*(i+1));  // Should not subtract anything
    }

    // Test case 3: Alternating conditional subtract
    Vec8us mask3(0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0);
    Vec8s a3(10, 20, 30, 40, 50, 60, 70, 80);
    Vec8s b3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result3 = if_sub(mask3, a3, b3);
    assert(result3[0] == 9);   // 10 - 1
    assert(result3[1] == 20);  // 20 - 0
    assert(result3[2] == 27);  // 30 - 3
    assert(result3[3] == 40);  // 40 - 0
    assert(result3[4] == 45);  // 50 - 5
    assert(result3[5] == 60);  // 60 - 0
    assert(result3[6] == 63);  // 70 - 7
    assert(result3[7] == 80);  // 80 - 0

    // Test case 4: Test saturation behavior
    Vec8us mask4(0xFFFF);
    Vec8s a4(INT16_MIN, INT16_MIN+1, INT16_MAX, INT16_MAX-1, 0, -1, 32767, -32768);
    Vec8s b4(1, 2, -1, -2, INT16_MAX, INT16_MIN, 1, -1);
    Vec8s result4 = if_sub(mask4, a4, b4);
    assert(result4[0] == INT16_MIN);      // Saturated subtraction
    assert(result4[1] == INT16_MIN);      // Saturated subtraction
    assert(result4[2] == INT16_MAX);      // INT16_MAX - (-1)
    assert(result4[3] == INT16_MAX);      // INT16_MAX-1 - (-2)
    assert(result4[4] == -INT16_MAX);     // 0 - INT16_MAX
    assert(result4[5] == INT16_MAX);      // -1 - INT16_MIN
    assert(result4[6] == 32766);          // 32767 - 1
    assert(result4[7] == -32767);         // -32768 - (-1)

    // Test case 5: Test with zero operands
    Vec8us mask5(0xFFFF);
    Vec8s a5(0);
    Vec8s b5(0);
    Vec8s result5 = if_sub(mask5, a5, b5);
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == 0);  // 0 - 0 should be 0
    }

    std::cout << "test_if_sub passed!\n";
}
void test_if_mul() {
    // Test case 1: Basic conditional multiply with all true mask
    Vec8us mask1(0xFFFF);  // All bits set (true)
    Vec8s a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s b1(2, 2, 2, 2, 2, 2, 2, 2);
    Vec8s result1 = if_mul(mask1, a1, b1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == (i + 1) * 2);  // Should multiply all elements
    }

    // Test case 2: Conditional multiply with all false mask
    Vec8us mask2(0);  // All bits clear (false)
    Vec8s a2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s b2(2, 2, 2, 2, 2, 2, 2, 2);
    Vec8s result2 = if_mul(mask2, a2, b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == i + 1);  // Should return original a values
    }

    // Test case 3: Alternating conditional multiply
    Vec8us mask3(0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0);
    Vec8s a3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s b3(10, 20, 30, 40, 50, 60, 70, 80);
    
    Vec8s result3 = if_mul(mask3, a3, b3);
    assert(result3[0] == 10);  // 1 * 10
    assert(result3[1] == 2);   // 2 (original)
    assert(result3[2] == 90);  // 3 * 30
    assert(result3[3] == 4);   // 4 (original)
    assert(result3[4] == 250); // 5 * 50
    assert(result3[5] == 6);   // 6 (original)
    assert(result3[6] == 490); // 7 * 70
    assert(result3[7] == 8);   // 8 (original)

    // Test case 4: Test saturation behavior
    Vec8us mask4(0xFFFF);
    Vec8s a4(INT16_MAX, INT16_MAX/2, INT16_MIN, INT16_MIN/2, 16384, -16384, 32767, -32768);
    Vec8s b4(2, 3, 2, 3, 2, 2, 2, 2);

    Vec8s c4 = a4 * b4;
    Vec8s result4 = if_mul(mask4, a4, b4);
    assert(result4[0] == INT16_MAX);  // Saturated multiplication
    assert(result4[1] == INT16_MAX);  // Saturated multiplication
    assert(result4[2] == INT16_MIN);  // Saturated multiplication
    assert(result4[3] == INT16_MIN);  // Saturated multiplication
    assert(result4[4] == INT16_MAX);  // 16384 * 2 saturates to INT16_MAX
    assert(result4[5] == INT16_MIN);  // -16384 * 2 saturates to INT16_MIN
    assert(result4[6] == INT16_MAX);  // Saturated multiplication
    assert(result4[7] == INT16_MIN);  // -32768 * 2 saturates to -32768

    // Test case 5: Test with zero operands
    Vec8us mask5(0xFFFF);
    Vec8s a5(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s b5(0);
    Vec8s result5 = if_mul(mask5, a5, b5);
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == 0);  // Multiplication by 0 should give 0
    }

    std::cout << "test_if_mul passed!\n";
}

void test_horizontal_add() {
    // Test case 1: Basic addition of positive numbers
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    int32_t result1 = horizontal_add(v1);
    assert(result1 == 36);  // 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 = 36

    // Test case 2: Addition of negative numbers
    Vec8s v2(-1, -2, -3, -4, -5, -6, -7, -8);
    int32_t result2 = horizontal_add(v2);
    assert(result2 == -36);  // -1 + (-2) + (-3) + (-4) + (-5) + (-6) + (-7) + (-8) = -36

    // Test case 3: Addition of zeros
    Vec8s v3(0);
    int32_t result3 = horizontal_add(v3);
    assert(result3 == 0);  // 0 + 0 + 0 + 0 + 0 + 0 + 0 + 0 = 0

    // Test case 4: Mixed positive and negative numbers
    Vec8s v4(1, -1, 2, -2, 3, -3, 4, -4);
    int32_t result4 = horizontal_add(v4);
    assert(result4 == 0);  // 1 + (-1) + 2 + (-2) + 3 + (-3) + 4 + (-4) = 0

    // Test case 5: Large numbers testing potential overflow
    Vec8s v5(32767, 32767, -32768, -32768, 16384, -16384, 8192, -8192);
    int32_t result5 = horizontal_add(v5);
    assert(result5 == -2);  // Sum should be -2

    // Test case 6: Alternating positive numbers
    Vec8s v6(1, 3, 5, 7, 9, 11, 13, 15);
    int32_t result6 = horizontal_add(v6);
    assert(result6 == 64);  // 1 + 3 + 5 + 7 + 9 + 11 + 13 + 15 = 64

    // Test case 7: Random mix of numbers
    Vec8s v7(100, -50, 75, -25, 30, -15, 10, -5);
    int32_t result7 = horizontal_add(v7);
    assert(result7 == 120);  // 100 + (-50) + 75 + (-25) + 30 + (-15) + 10 + (-5) = 120

    // Test case 8: All maximum positive values
    Vec8s v8(32767, 32767, 32767, 32767, 32767, 32767, 32767, 32767);
    int32_t result8 = horizontal_add(v8);
    assert(result8 == 262136);  // 32767 * 8 = 262136

    // Test case 9: All minimum negative values
    Vec8s v9(INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN, INT16_MIN);
    int32_t result9 = horizontal_add(v9);
    assert(result9 == -262144);  // -32768 * 8 = -262144

    std::cout << "test_horizontal_add passed!\n";

    std::cout << "test_horizontal_add passed!\n";
}
void test_max() {
    // Test case 1: Basic max comparison with positive numbers
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v2(8, 7, 6, 5, 4, 3, 2, 1);
    Vec8s result1 = max(v1, v2);
    assert(result1[0] == 8);
    assert(result1[1] == 7); 
    assert(result1[2] == 6);
    assert(result1[3] == 5);
    assert(result1[4] == 5);
    assert(result1[5] == 6);
    assert(result1[6] == 7);
    assert(result1[7] == 8);

    // Test case 2: Max of equal numbers
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result2 = max(v3, v4);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == i + 1);  // Should return same numbers
    }

    // Test case 3: Max with negative numbers
    Vec8s v5(-8, -7, -6, -5, -4, -3, -2, -1);
    Vec8s v6(-1, -2, -3, -4, -5, -6, -7, -8);
    Vec8s result3 = max(v5, v6);
    assert(result3[0] == -1);
    assert(result3[1] == -2);
    assert(result3[2] == -3);
    assert(result3[3] == -4);
    assert(result3[4] == -4);
    assert(result3[5] == -3);
    assert(result3[6] == -2);
    assert(result3[7] == -1);

    // Test case 4: Max with mix of positive and negative
    Vec8s v7(-1, 2, -3, 4, -5, 6, -7, 8);
    Vec8s v8(1, -2, 3, -4, 5, -6, 7, -8);
    Vec8s result4 = max(v7, v8);
    assert(result4[0] == 1);
    assert(result4[1] == 2);
    assert(result4[2] == 3);
    assert(result4[3] == 4);
    assert(result4[4] == 5);
    assert(result4[5] == 6);
    assert(result4[6] == 7);
    assert(result4[7] == 8);

    // Test case 5: Max with INT16_MAX/MIN values
    Vec8s v9(INT16_MAX, INT16_MIN, 0, INT16_MAX, INT16_MIN, 0, 32767, -32768);
    Vec8s v10(0, 0, INT16_MIN, INT16_MIN, INT16_MAX, INT16_MAX, -32768, 32767);
    Vec8s result5 = max(v9, v10);
    assert(result5[0] == INT16_MAX);  // INT16_MAX vs 0
    assert(result5[1] == 0);          // INT16_MIN vs 0
    assert(result5[2] == 0);          // 0 vs INT16_MIN
    assert(result5[3] == INT16_MAX);  // INT16_MAX vs INT16_MIN
    assert(result5[4] == INT16_MAX);  // INT16_MIN vs INT16_MAX
    assert(result5[5] == INT16_MAX);  // 0 vs INT16_MAX
    assert(result5[6] == 32767);      // 32767 vs -32768
    assert(result5[7] == 32767);      // -32768 vs 32767

    std::cout << "test_max passed!\n";
}
void test_min() {
    // Test case 1: Basic min comparison with positive numbers 
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v2(8, 7, 6, 5, 4, 3, 2, 1);
    Vec8s result1 = min(v1, v2);
    assert(result1[0] == 1);
    assert(result1[1] == 2);
    assert(result1[2] == 3);
    assert(result1[3] == 4);
    assert(result1[4] == 4);
    assert(result1[5] == 3);
    assert(result1[6] == 2);
    assert(result1[7] == 1);

    // Test case 2: Min of equal numbers
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s v4(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result2 = min(v3, v4);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == i + 1);  // Should return same numbers
    }

    // Test case 3: Min with negative numbers
    Vec8s v5(-8, -7, -6, -5, -4, -3, -2, -1);
    Vec8s v6(-1, -2, -3, -4, -5, -6, -7, -8);
    Vec8s result3 = min(v5, v6);
    assert(result3[0] == -8);
    assert(result3[1] == -7);
    assert(result3[2] == -6);
    assert(result3[3] == -5);
    assert(result3[4] == -5);
    assert(result3[5] == -6);
    assert(result3[6] == -7);
    assert(result3[7] == -8);

    // Test case 4: Min with mix of positive and negative
    Vec8s v7(-1, 2, -3, 4, -5, 6, -7, 8);
    Vec8s v8(1, -2, 3, -4, 5, -6, 7, -8);
    Vec8s result4 = min(v7, v8);
    assert(result4[0] == -1);
    assert(result4[1] == -2);
    assert(result4[2] == -3);
    assert(result4[3] == -4);
    assert(result4[4] == -5);
    assert(result4[5] == -6);
    assert(result4[6] == -7);
    assert(result4[7] == -8);

    // Test case 5: Min with INT16_MAX/MIN values 
    Vec8s v9(INT16_MAX, INT16_MIN, 0, INT16_MAX, INT16_MIN, 0, 32767, -32768);
    Vec8s v10(0, 0, INT16_MIN, INT16_MIN, INT16_MAX, INT16_MAX, -32768, 32767);
    Vec8s result5 = min(v9, v10);
    assert(result5[0] == 0);          // INT16_MAX vs 0
    assert(result5[1] == INT16_MIN);  // INT16_MIN vs 0
    assert(result5[2] == INT16_MIN);  // 0 vs INT16_MIN
    assert(result5[3] == INT16_MIN);  // INT16_MAX vs INT16_MIN
    assert(result5[4] == INT16_MIN);  // INT16_MIN vs INT16_MAX
    assert(result5[5] == 0);          // 0 vs INT16_MAX
    assert(result5[6] == -32768);     // 32767 vs -32768
    assert(result5[7] == -32768);     // -32768 vs 32767

    std::cout << "test_min passed!\n";
}
void test_abs() {
    // Test case 1: Basic absolute values of negative numbers
    Vec8s v1(-1, -2, -3, -4, -5, -6, -7, -8);
    Vec8s result1 = abs(v1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == i + 1);  // Should return positive values
    }

    // Test case 2: Absolute values of positive numbers (no change)
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result2 = abs(v2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == i + 1);  // Should return same positive values
    }

    // Test case 3: Mix of positive and negative numbers
    Vec8s v3(-1, 2, -3, 4, -5, 6, -7, 8);
    Vec8s result3 = abs(v3);
    assert(result3[0] == 1);
    assert(result3[1] == 2);
    assert(result3[2] == 3);
    assert(result3[3] == 4);
    assert(result3[4] == 5);
    assert(result3[5] == 6);
    assert(result3[6] == 7);
    assert(result3[7] == 8);

    // Test case 4: Zero values
    Vec8s v4(0);
    Vec8s result4 = abs(v4);
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == 0);  // Absolute value of 0 is 0
    }

    // Test case 5: Test INT16_MIN/MAX values
    Vec8s v5(INT16_MIN, INT16_MAX, -32768, 32767, INT16_MIN, INT16_MAX, -32768, 32767);
    Vec8s result5 = abs(v5);
    assert(result5[0] == INT16_MIN);  // Special case: abs(INT16_MIN) = INT16_MIN due to two's complement
    assert(result5[1] == INT16_MAX);  // abs(INT16_MAX) = INT16_MAX
    assert(result5[2] == INT16_MIN);  // abs(-32768) = -32768 due to two's complement
    assert(result5[3] == INT16_MAX);  // abs(32767) = 32767
    assert(result5[4] == INT16_MIN);
    assert(result5[5] == INT16_MAX);
    assert(result5[6] == INT16_MIN);
    assert(result5[7] == INT16_MAX);

    std::cout << "test_abs passed!\n";
}
void test_rotate_left() {
    // Test case 1: Basic rotate left by 1
    Vec8s v1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result1 = rotate_left(v1, 1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == (i + 1) * 2);  // Each value doubled
    }

    // Test case 2: Rotate left by 0 (no change)
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8); 
    Vec8s result2 = rotate_left(v2, 0);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == i + 1);  // No change
    }

    // Test case 3: Rotate left by multiple positions
    Vec8s v3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result3 = rotate_left(v3, 2); // Multiply by 4
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == (i + 1) * 4);
    }

    // Test case 4: Test rotation with negative numbers
    Vec8s v4(-8, -7, -6, -5, -4, -3, -2, -1);
    Vec8s result4 = rotate_left(v4, 1);
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == (-8 + i) * 2);
    }

    // Test case 5: Test overflow behavior
    Vec8s v5(16384, -16384, 32767, -32768, 1024, -1024, 8192, -8192);
    Vec8s result5 = rotate_left(v5, 1);
    assert(result5[0] == -32768);    // 16384 * 2 overflows to -32768
    assert(result5[1] == -32768);    // -16384 * 2 overflows to -32768 
    assert(result5[2] == -2);        // 32767 * 2 overflows to -2
    assert(result5[3] == 0);         // -32768 * 2 overflows to 0
    assert(result5[4] == 2048);      // 1024 * 2
    assert(result5[5] == -2048);     // -1024 * 2
    assert(result5[6] == 16384);     // 8192 * 2
    assert(result5[7] == -16384);    // -8192 * 2

    // Test case 6: Large rotations
    Vec8s v6(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result6 = rotate_left(v6, 14);
    int16_t expected[] = {16384, -32768, -16384, 0, 16384, -32768, -16384, 0};
    for(int i = 0; i < 8; i++) {
        assert(result6[i] == expected[i]);
    }

    // Test case 7: Chained rotations
    Vec8s v7(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8s result7 = rotate_left(rotate_left(v7, 1), 2); // Left 3 total
    for(int i = 0; i < 8; i++) {
        assert(result7[i] == 8); // 1 << 3 = 8
    }

    std::cout << "test_rotate_left passed!\n";
}
void test_rotate_right() {
    // Test case 1: Basic rotate right by 1
    Vec8s v1(2, 4, 6, 8, 10, 12, 14, 16);
    Vec8s result1 = rotate_right(v1, 1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == (i + 1) * 2 / 2);  // Each value halved
    }

    // Test case 2: Rotate right by 0 (no change)
    Vec8s v2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8s result2 = rotate_right(v2, 0);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == i + 1);  // No change
    }

    // Test case 3: Rotate right by multiple positions
    Vec8s v3(16, 32, 48, 64, 80, 96, 112, 128);
    Vec8s result3 = rotate_right(v3, 2); // Divide by 4
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == (i * 16 + 16) / 4);
    }

    // Test case 4: Test rotation with negative numbers
    Vec8s v4(-16, -14, -12, -10, -8, -6, -4, -2);
    Vec8s result4 = rotate_right(v4, 1);
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == (-16 + i * 2) / 2);
    }

    // Test case 5: Test with maximum and minimum values
    Vec8s v5(INT16_MAX, INT16_MIN, 32767, -32768, 16384, -16384, 8192, -8192);
    Vec8s result5 = rotate_right(v5, 1);
    assert(result5[0] == 16383);     // INT16_MAX / 2
    assert(result5[1] == -16384);    // INT16_MIN / 2
    assert(result5[2] == 16383);     // 32767 / 2
    assert(result5[3] == -16384);    // -32768 / 2
    assert(result5[4] == 8192);      // 16384 / 2
    assert(result5[5] == -8192);     // -16384 / 2
    assert(result5[6] == 4096);      // 8192 / 2
    assert(result5[7] == -4096);     // -8192 / 2

    // Test case 6: Large rotations
    Vec8s v6(32768, 16384, 8192, 4096, 2048, 1024, 512, 256);
    Vec8s result6 = rotate_right(v6, 8);
    for(int i = 0; i < 8; i++) {
        assert(result6[i] == (v6[i] >> 8));  // Right shift by 8
    }

    // Test case 7: Odd numbers
    Vec8s v7(15, 13, 11, 9, 7, 5, 3, 1);
    Vec8s result7 = rotate_right(v7, 1);
    for(int i = 0; i < 8; i++) {
        assert(result7[i] == (15 - 2 * i) / 2);
    }

    // Test case 8: Chained rotations
    Vec8s v8(64, 64, 64, 64, 64, 64, 64, 64);
    Vec8s result8 = rotate_right(rotate_right(v8, 1), 2); // Right 3 total
    for(int i = 0; i < 8; i++) {
        assert(result8[i] == 8); // 64 >> 3 = 8
    }

    std::cout << "test_rotate_right passed!\n";
}

int main() 
{
    test_default_constructor();
    test_broadcast_constructor();
    test_element_constructor();
    test_int16x8t_constructor();
    test_copy_constructor();
    test_assignment_operator();
    test_type_cast_operator();
   
    test_load();
    test_load_a();
    test_store();
    test_store_a();
    test_load_partial();
    test_store_partial();
    test_cutoff();
    test_and_assign_operator();
    test_insert();
    test_extract();
    test_array_subscript_operator();
    
    test_add_operator();
    test_add_assign_operator();
    test_postfix_increment_operator();
    test_prefix_increment_operator();

    test_subtract_operator();
    test_unary_minus_operator();
    test_subtract_assign_operator();
    test_postfix_decrement_operator();
    test_prefix_decrement_operator();

    test_multiply_operator();
    test_multiply_assign_operator();
    test_shift_left_operator();
    test_shift_left_assign_operator();
    test_shift_right_operator();
    test_shift_right_assign_operator();

    test_operator_equal();
    test_operator_not_equal();
    test_greater_than_operator();
    test_less_than_operator();
    test_greater_than_or_equal_operator();
    test_less_than_or_equal_operator();

    test_bitwise_and_operator();
    test_bitwise_or_operator();
    test_bitwise_xor_operator();
    test_bitwise_not_operator();
    
    test_select();
    test_if_add();
    test_if_sub();
    test_if_mul();

    test_horizontal_add();
    test_max();
    test_min();
    test_abs();
    test_rotate_left();
    test_rotate_right();
    std::cout << "All tests passed!\n";
    return 0;
}