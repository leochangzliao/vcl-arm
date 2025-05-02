#include "../Vec2q.h"
#include <iostream>
#include <cassert>

using namespace VCL_NAMESPACE;
void test_default_constructor() {
    // Test case 1: constructor initializes to zero
    Vec2q v;
    for(int i = 0; i < 2; i++) {
        assert(v[i] == 0);
    }
    
    //Test case 2:  multiple instances
    Vec2q v2;
    Vec2q v3;
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == 0);
        assert(v3[i] == 0);
    }

    // Test case 3:  value changes after default construction
    Vec2q v4;
    v4 = Vec2q(1,2);               
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == i+1);
    }

    // Test case 4: negative values after default construction
    Vec2q v5;
    v5 = Vec2q(-1,-2);
    for(int i = 0; i < 2; i++) {
        assert(v5[i] == -(i+1));
    }
    std::cout << "test_default_constructor passed!\n";
}
void test_broadcast_constructor() {
    // Test case 1: Broadcast zero
    Vec2q v1(0);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Broadcast maximum value
    Vec2q v2(INT64_MAX);
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == INT64_MAX);
    }

    // Test case 3: Broadcast arbitrary value
    Vec2q v3(0x1234);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == 0x1234);
    }

    // Test case 4: Multiple instances with different values
    Vec2q v4(0x2AAA);
    Vec2q v5(0x1555);
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == 0x2AAA);
        assert(v5[i] == 0x1555);
    }
    std::cout << "test_broadcast_constructor passed!\n";
}
void test_element_constructor() {
    // Test case 1: Ascending positive values
    Vec2q v1(1, 2);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == i+1);
    }

    // Test case 2: Descending positive values 
    Vec2q v2(2, 1);
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == 2-i);
    }

    // Test case 3: Negative values
    Vec2q v3(-1, -2);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == -(i+1));
    }

    // Test case 4: Mixed positive and negative values
    Vec2q v4(-2, 1);
    int32_t expected[] = {-2, 1};
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == expected[i]);
    }

    // Test case 5: All zeros
    Vec2q v5(0, 0);
    for(int i = 0; i < 2; i++) {
        assert(v5[i] == 0);
    }
    std::cout << "test_element_constructor passed!\n";
}
void test_int64x2t_constructor() {
    // Test case 1: Create int64x2_t with zeros and construct Vec2q from it
    int64_t data1[2] = {0, 0};
    int64x2_t x1 = vld1q_s64(data1);
    Vec2q v1(x1);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Create int64x2_t with sequential values
    int64_t data2[2] = {1, 2}; 
    int64x2_t x2 = vld1q_s64(data2);
    Vec2q v2(x2);
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Create int64x2_t with maximum values
    int64_t data3[2] = {0x7FFFFFFFFFFFFFFF, 0x7FFFFFFFFFFFFFFF};
    int64x2_t x3 = vld1q_s64(data3);
    Vec2q v3(x3);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == 0x7FFFFFFFFFFFFFFF);
    }

    // Test case 4: Create int64x2_t with mixed values
    int64_t data4[2] = {0x123456789ABCDEF0, 0x7FFFFFFFFFFFFFFF};
    int64x2_t x4 = vld1q_s64(data4);
    Vec2q v4(x4);
    assert(v4[0] == 0x123456789ABCDEF0);
    assert(v4[1] == 0x7FFFFFFFFFFFFFFF);
    std::cout << "test_int64x2t_constructor passed!\n";
}
void test_copy_constructor() {
    // Test case 1: Copy basic values
    Vec2q original1(1, 2);
    Vec2q copy1(original1);
    for(int i = 0; i < 2; i++) {
        assert(copy1[i] == original1[i]);
    }

    // Test case 2: Copy zeros
    Vec2q original2(0);
    Vec2q copy2(original2);
    for(int i = 0; i < 2; i++) {
        assert(copy2[i] == 0);
    }

    // Test case 3: Copy negative values 
    Vec2q original3(-1, -2);
    Vec2q copy3(original3);
    for(int i = 0; i < 2; i++) {
        assert(copy3[i] == original3[i]);
    }

    // Test case 4: Copy min/max values
    Vec2q original4(INT64_MIN, INT64_MAX);
    Vec2q copy4(original4);
    for(int i = 0; i < 2; i++) {
        assert(copy4[i] == original4[i]);
    }

    // Test case 5: Modify copy should not affect original
    Vec2q original5(1, 2);
    Vec2q copy5(original5);
    copy5 = Vec2q(-1, -2);
    for(int i = 0; i < 2; i++) {
        assert(original5[i] == i+1);
        assert(copy5[i] == -(i+1));
    }
    std::cout << "test_copy_constructor passed!\n";
}
void test_assignment_operator() {
    // Test case 1: Assign basic values from int64x2_t
    int64_t data1[2] = {1, 2};
    int64x2_t raw1 = vld1q_s64(data1);
    Vec2q v1;
    v1 = raw1;
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == data1[i]);
    }

    // Test case 2: Assign zeros
    int64_t data2[2] = {0};
    int64x2_t raw2 = vld1q_s64(data2);
    Vec2q v2;
    v2 = raw2;
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: Assign negative values
    int64_t data3[2] = {-1, -2};
    int64x2_t raw3 = vld1q_s64(data3);
    Vec2q v3;
    v3 = raw3;
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == data3[i]);
    }

    // Test case 4: Assign min/max values 
    int64_t data4[2] = {INT64_MIN, INT64_MAX};
    int64x2_t raw4 = vld1q_s64(data4);
    Vec2q v4;
    v4 = raw4;
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == data4[i]);
    }

    // Test case 5: Chain assignments
    int64_t data5[2] = {10, 20};
    int64x2_t raw5 = vld1q_s64(data5);
    Vec2q v5, v6;
    v6 = v5 = raw5;
    for(int i = 0; i < 2; i++) {
        assert(v5[i] == data5[i]);
        assert(v6[i] == data5[i]);
    }
    std::cout << "test_assignment_operator passed!\n";
}
void test_type_cast_operator() {
    // Test case 1: Convert basic values to int64x2_t
    Vec2q v1(1, 2);
    int64x2_t raw1 = v1;
    int64_t data1[2];
    vst1q_s64(data1, raw1);
    for(int i = 0; i < 2; i++) {
        assert(data1[i] == i+1);
    }

    // Test case 2: Convert zeros to int64x2_t
    Vec2q v2(0);
    int64x2_t raw2 = v2;
    int64_t data2[2];
    vst1q_s64(data2, raw2);
    for(int i = 0; i < 2; i++) {
        assert(data2[i] == 0);
    }

    // Test case 3: Convert negative values to int64x2_t
    Vec2q v3(-1, -2);
    int64x2_t raw3 = v3;
    int64_t data3[2];
    vst1q_s64(data3, raw3);
    for(int i = 0; i < 2; i++) {
        assert(data3[i] == -(i+1));
    }

    // Test case 4: Convert min/max values to int64x2_t
    Vec2q v4(INT64_MIN, INT64_MAX);
    int64x2_t raw4 = v4;
    int64_t data4[2];
    vst1q_s64(data4, raw4);
    int64_t expected4[] = {INT64_MIN, INT64_MAX};
    for(int i = 0; i < 2; i++) {
        assert(data4[i] == expected4[i]);
    }

    // Test case 5: Convert alternating values to int64x2_t
    Vec2q v5(-100, 100);
    int64x2_t raw5 = v5;
    int64_t data5[2];
    vst1q_s64(data5, raw5);
    int64_t expected5[] = {-100, 100};
    for(int i = 0; i < 2; i++) {
        assert(data5[i] == expected5[i]);
    }
    std::cout << "test_type_cast_operator passed!\n";
}

void test_load() {
    // Test case 1: Load basic values
    int64_t data1[2] = {1, 2};
    Vec2q v1;
    v1.load(data1);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == data1[i]);
    }

    // Test case 2: Load zeros 
    int64_t data2[2] = {0};
    Vec2q v2;
    v2.load(data2);
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: Load negative values
    int64_t data3[2] = {-1, -2};
    Vec2q v3;
    v3.load(data3);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == data3[i]); 
    }

    // Test case 4: Load min/max values
    int64_t data4[2] = {INT64_MIN, INT64_MAX};
    Vec2q v4;
    v4.load(data4);
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == data4[i]);
    }

    // Test case 5: Load values then modify array
    int64_t data5[2] = {1, 2};
    Vec2q v5;
    v5.load(data5);
    data5[0] = 100; // Modify original array
    assert(v5[0] == 1); // Vector should keep original value
    std::cout << "test_load passed!\n";
}
void test_load_a() {
    // Test case 1: Load aligned basic values
    alignas(16) int64_t data1[2] = {1, 2};
    Vec2q v1;
    v1.load_a(data1);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == data1[i]);
    }

    // Test case 2: Load aligned zeros
    alignas(16) int64_t data2[2] = {0};
    Vec2q v2;
    v2.load_a(data2);
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: Load aligned negative values
    alignas(16) int64_t data3[2] = {-1, -2};
    Vec2q v3;
    v3.load_a(data3);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == data3[i]);
    }

    // Test case 4: Load aligned min/max values
    alignas(16) int64_t data4[2] = {INT64_MIN, INT64_MAX};
    Vec2q v4;
    v4.load_a(data4);
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == data4[i]);
    }

    // Test case 5: Load aligned values then modify array
    alignas(16) int64_t data5[2] = {1, 2};
    Vec2q v5;
    v5.load_a(data5);
    data5[0] = 100; // Modify original array
    assert(v5[0] == 1); // Vector should keep original value
    std::cout << "test_load_a passed!\n";
}
void test_store() {
    // Test case 1: Store basic values
    int64_t data1[2];
    Vec2q v1(1, 2);
    v1.store(data1);
    for(int i = 0; i < 2; i++) {
        assert(data1[i] == i+1);
    }

    // Test case 2: Store zeros
    int64_t data2[2];
    Vec2q v2(0);
    v2.store(data2);
    for(int i = 0; i < 2; i++) {
        assert(data2[i] == 0);
    }

    // Test case 3: Store negative values
    int64_t data3[2];
    Vec2q v3(-1, -2);
    v3.store(data3);
    for(int i = 0; i < 2; i++) {
        assert(data3[i] == -(i+1));
    }

    // Test case 4: Store min/max values
    int64_t data4[2];
    Vec2q v4(INT64_MIN, INT64_MAX);
    v4.store(data4);
    int64_t expected4[] = {INT64_MIN, INT64_MAX};
    for(int i = 0; i < 2; i++) {
        assert(data4[i] == expected4[i]);
    }

    // Test case 5: Store multiple times to same array
    int64_t data5[2];
    Vec2q v5(1, 2);
    v5.store(data5);
    Vec2q v6(-1, -2);
    v6.store(data5); // Overwrite previous values
    for(int i = 0; i < 2; i++) {
        assert(data5[i] == -(i+1));
    }
    std::cout << "test_store passed!\n";
}
void test_store_a() {
    // Test case 1: Store aligned basic values
    alignas(16) int64_t data1[2];
    Vec2q v1(1, 2);
    v1.store_a(data1);
    for(int i = 0; i < 2; i++) {
        assert(data1[i] == i+1);
    }

    // Test case 2: Store aligned zeros
    alignas(16) int64_t data2[2];
    Vec2q v2(0);
    v2.store_a(data2);
    for(int i = 0; i < 2; i++) {
        assert(data2[i] == 0);
    }

    // Test case 3: Store aligned negative values
    alignas(16) int64_t data3[2];
    Vec2q v3(-1, -2);
    v3.store_a(data3);
    for(int i = 0; i < 2; i++) {
        assert(data3[i] == -(i+1));
    }

    // Test case 4: Store aligned min/max values
    alignas(16) int64_t data4[2];
    Vec2q v4(INT64_MIN, INT64_MAX);
    v4.store_a(data4);
    int64_t expected4[] = {INT64_MIN, INT64_MAX};
    for(int i = 0; i < 2; i++) {
        assert(data4[i] == expected4[i]);
    }

    // Test case 5: Store aligned multiple times to same array
    alignas(16) int64_t data5[2];
    Vec2q v5(1, 2);
    v5.store_a(data5);
    Vec2q v6(-1, -2);
    v6.store_a(data5); // Overwrite previous values
    for(int i = 0; i < 2; i++) {
        assert(data5[i] == -(i+1));
    }
    std::cout << "test_store_a passed!\n";
}
void test_load_partial() {
    // Test case 1: Load partial with n = 0 (should set all elements to 0)
    int64_t data1[2] = {1, 2};
    Vec2q v1;
    v1.load_partial(0, data1);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Load partial with n = 1 (should load first element and set rest to 0)
    int64_t data2[2] = {1, 2};
    Vec2q v2;
    v2.load_partial(1, data2);
    assert(v2[0] == data2[0]);
    assert(v2[1] == 0);

    // Test case 3: Load partial with n = 2 (should load all elements)
    int64_t data3[2] = {1, 2};
    Vec2q v3;
    v3.load_partial(2, data3);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == data3[i]);
    }

    // Test case 4: Load partial with n = -1 (should set all elements to 0)
    int64_t data4[2] = {1, 2};
    Vec2q v4;
    v4.load_partial(-1, data4);
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == 0);
    }

    // Test case 5: Load partial with n = 1 with negative values
    int64_t data5[2] = {-1, -2};
    Vec2q v5;
    v5.load_partial(1, data5);
    assert(v5[0] == data5[0]);
    assert(v5[1] == 0);

    std::cout << "test_load_partial passed!\n";
}
void test_store_partial() {
    // Test case 1: Store partial with n = 0 (should store nothing)
    int64_t data1[2] = {0};
    Vec2q v1(1, 2);
    v1.store_partial(0, data1);
    for(int i = 0; i < 2; i++) {
        assert(data1[i] == 0);
    }

    // Test case 2: Store partial with n = 1 (should store first element)
    int64_t data2[2] = {0};
    Vec2q v2(1, 2);
    v2.store_partial(1, data2);
    assert(data2[0] == 1);
    assert(data2[1] == 0);

    // Test case 3: Store partial with n = 2 (should store all elements)
    int64_t data3[2] = {0};
    Vec2q v3(1, 2);
    v3.store_partial(2, data3);
    for(int i = 0; i < 2; i++) {
        assert(data3[i] == i+1);
    }

    // Test case 4: Store partial with n > 2 (should store only 2 elements)
    int64_t data4[3] = {0};
    Vec2q v4(1, 2);
    v4.store_partial(3, data4);
    for(int i = 0; i < 2; i++) {
        assert(data4[i] == i+1);
    }
    assert(data4[2] == 0);

    // Test case 5: Store partial with negative values
    int64_t data5[2] = {0};
    Vec2q v5(-1, -2);
    v5.store_partial(1, data5);
    assert(data5[0] == -1);
    assert(data5[1] == 0);

    std::cout << "test_store_partial passed!\n";
}
void test_cutoff() {
    // Test case 1: n = 0 (should set all elements to 0)
    Vec2q v1(1, 2);
    v1.cutoff(0);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: n = 1 (should keep first element, set rest to 0)
    Vec2q v2(1, 2);
    v2.cutoff(1);
    assert(v2[0] == 1);
    assert(v2[1] == 0);

    // Test case 3: n = 2 (should keep all elements)
    Vec2q v3(1, 2);
    v3.cutoff(2);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == i+1);
    }

    // Test case 4: n > 2 (should keep all elements)
    Vec2q v4(1, 2);
    v4.cutoff(3);
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == i+1);
    }

    // Test case 5: Test with negative values
    Vec2q v5(-1, -2);
    v5.cutoff(1);
    assert(v5[0] == -1);
    assert(v5[1] == 0);

    // Test case 6: chain operation test
    Vec2q v6(1, 2);
    v6.cutoff(2).cutoff(1);
    assert(v6[0] == 1);
    assert(v6[1] == 0);

    std::cout << "test_cutoff passed!\n";
}
void test_and_assign_operator() {
    // Test case 1: AND with all 1s (should keep original values)
    Vec2q v1(1, 2);
    Vec2q all_ones(0xFFFFFFFFFFFFFFFF);
    v1 &= all_ones;
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == i+1);
    }

    // Test case 2: AND with all 0s (should set all to 0)
    Vec2q v2(1, 2);
    Vec2q all_zeros(0);
    v2 &= all_zeros;
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: AND with alternating bits
    Vec2q v3(0xFFFFFFFFFFFFFFFF);
    Vec2q alternating(0x5555555555555555);
    v3 &= alternating;
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == 0x5555555555555555);
    }

    // Test case 4: AND with negative values
    Vec2q v4(-1, -2);
    Vec2q mask(0x7FFFFFFFFFFFFFFF);  // Clear sign bit
    v4 &= mask;
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == ((-(i+1)) & 0x7FFFFFFFFFFFFFFF));
    }

    // Test case 5: Chain operations with different masks
    Vec2q v5(0x7FFFFFFFFFFFFFFF);  // Maximum positive value for int64_t
    v5 &= Vec2q(0x7070707070707070);  // First mask
    v5 &= Vec2q(0x7F007F007F007F00);  // Second mask
    for(int i = 0; i < 2; i++) {
        assert(v5[i] == 0x7000700070007000); // Should be 7000700070007000 after both masks
    }

    std::cout << "test_and_assign_operator passed!\n";
}
void test_insert() {
    // Test case 1: Insert at beginning
    Vec2q v1(1, 2);
    v1.insert(0, 100);
    assert(v1[0] == 100);
    assert(v1[1] == 2);

    // Test case 2: Insert at end
    Vec2q v2(1, 2);
    v2.insert(1, 100);
    assert(v2[0] == 1);
    assert(v2[1] == 100);

    // Test case 3: Insert negative value
    Vec2q v3(1, 2);
    v3.insert(1, -100);
    assert(v3[0] == 1);
    assert(v3[1] == -100);

    // Test case 4: Test index wrapping (index & 0x01)
    Vec2q v4(1, 2);
    v4.insert(2, 100);  // 2 & 0x01 = 0
    assert(v4[0] == 100);
    assert(v4[1] == 2);

    // Test case 5: Multiple inserts
    Vec2q v5(1, 2);
    v5.insert(0, 100);
    v5.insert(1, 200);
    assert(v5[0] == 100);
    assert(v5[1] == 200);

    std::cout << "test_insert passed!\n";
}
void test_extract() {
    // Test case 1: Extract elements in order
    Vec2q v1(1, 2);
    for(int i = 0; i < 2; i++) {
        assert(v1.extract(i) == i+1);
    }

    // Test case 2: Extract from vector of zeros
    Vec2q v2(0);
    for(int i = 0; i < 2; i++) {
        assert(v2.extract(i) == 0);
    }

    // Test case 3: Extract from vector with negative values
    Vec2q v3(-1, -2);
    for(int i = 0; i < 2; i++) {
        assert(v3.extract(i) == -(i+1));
    }

    // Test case 4: Test index wrapping (index & 0x01)
    Vec2q v4(1, 2);
    assert(v4.extract(2) == 1);  // 2 & 0x01 = 0
    assert(v4.extract(3) == 2);  // 3 & 0x01 = 1

    // Test case 5: Extract from vector with min/max values
    Vec2q v5(INT64_MIN, INT64_MAX);
    assert(v5.extract(0) == INT64_MIN);
    assert(v5.extract(1) == INT64_MAX);

    std::cout << "test_extract passed!\n";
}
void test_array_subscript_operator() {
    // Test case 1: Access elements in order
    Vec2q v1(1, 2);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == i+1);
    }

    // Test case 2: Access from vector of zeros
    Vec2q v2(0);
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: Access from vector with negative values
    Vec2q v3(-1, -2);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == -(i+1));
    }

    // Test case 4: Test index wrapping (index & 0x01)
    Vec2q v4(1, 2);
    assert(v4[2] == 1);  // 2 & 0x01 = 0
    assert(v4[3] == 2);  // 3 & 0x01 = 1

    // Test case 5: Access from vector with min/max values
    Vec2q v5(INT64_MIN, INT64_MAX);
    assert(v5[0] == INT64_MIN);
    assert(v5[1] == INT64_MAX);

    std::cout << "test_array_subscript_operator passed!\n";
}

void test_add_operator() {
    // Test case 1: Basic addition
    Vec2q v1(1, 2);
    Vec2q v2(1, 1);
    Vec2q result1 = v1 + v2;
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == (i + 2));
    }

    // Test case 2: Adding zeros (identity operation)
    Vec2q v3(1, 2);
    Vec2q zeros(0);
    Vec2q result2 = v3 + zeros;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == v3[i]);
    }

    // Test case 3: Adding negative numbers
    Vec2q v4(1, 2);
    Vec2q v5(-1, -2);
    Vec2q result3 = v4 + v5;
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == 0);
    }

    // Test case 4: Testing saturation (overflow protection)
    Vec2q v6(INT64_MAX, INT64_MAX);
    Vec2q v7(1, INT64_MAX);
    Vec2q result4 = v6 + v7;
    assert(result4[0] == INT64_MAX);  // Saturated addition
    assert(result4[1] == INT64_MAX);  // Saturated addition

    // Test case 5: Chained additions
    Vec2q v8(1, 1);
    Vec2q result5 = v8 + v8 + v8;  // Should be (3,3)
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 3);
    }

    std::cout << "test_add_operator passed!\n";
}
void test_add_assign_operator() {
    // Test case 1: Basic addition assignment
    Vec2q v1(1, 2);
    Vec2q v2(1, 1);
    v1 += v2;
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == i + 2);
    }

    // Test case 2: Adding zeros (identity operation)
    Vec2q v3(1, 2);
    Vec2q zeros(0);
    v3 += zeros;
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == i + 1);
    }

    // Test case 3: Adding negative numbers 
    Vec2q v4(1, 2);
    Vec2q v5(-1, -2);
    v4 += v5;
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == 0);
    }

    // Test case 4: Testing saturation (overflow protection)
    Vec2q v6(INT64_MAX, INT64_MAX);
    Vec2q v7(1, INT64_MAX);
    v6 += v7;
    assert(v6[0] == INT64_MAX);  // Saturated addition
    assert(v6[1] == INT64_MAX);  // Saturated addition 

    // Test case 5: Chained additions
    Vec2q v8(1, 1);
    Vec2q v9(1, 1);
    v8 += v9 += v9;  // v9 becomes (2,2), then v8 becomes (3,3)
    for(int i = 0; i < 2; i++) {
        assert(v8[i] == 3);
        assert(v9[i] == 2);
    }

    std::cout << "test_add_assign_operator passed!\n";
}
void test_postfix_increment_operator() {
    // Test case 1: Basic increment
    Vec2q v1(1, 2);
    Vec2q result1 = v1++;
    // Check that result holds original values
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == i + 1);
    }
    // Check that original vector was incremented
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == i + 2);
    }

    // Test case 2: Increment zeros
    Vec2q v2(0);
    Vec2q result2 = v2++;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0);
        assert(v2[i] == 1);
    }

    // Test case 3: Increment negative values
    Vec2q v3(-2, -1);
    Vec2q result3 = v3++;
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == -2 + i);
        assert(v3[i] == -1 + i);
    }

    // Test case 4: Test saturation at maximum value
    Vec2q v4(INT64_MAX, INT64_MAX-1);
    Vec2q result4 = v4++;
    assert(result4[0] == INT64_MAX);
    assert(result4[1] == INT64_MAX-1);
    
    assert(v4[0] == INT64_MAX);     // Saturated
    assert(v4[1] == INT64_MAX);     // Saturated

    // Test case 5: Multiple increments
    Vec2q v5(1, 1);
    Vec2q result5 = v5++;
    result5 = v5++;
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 2);
        assert(v5[i] == 3);
    }

    std::cout << "test_postfix_increment_operator passed!\n";
}
void test_prefix_increment_operator() {
    // Test case 1: Basic increment
    Vec2q v1(1, 2);
    Vec2q& result1 = ++v1;
    // Check incremented values
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == i + 2);
    }
    // Check that result references the incremented vector
    assert(&result1 == &v1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == i + 2);
    }

    // Test case 2: Increment zeros
    Vec2q v2(0);
    Vec2q& result2 = ++v2;
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == 1);
        assert(result2[i] == 1);
    }
    assert(&result2 == &v2);

    // Test case 3: Increment negative values
    Vec2q v3(-2, -1);
    Vec2q& result3 = ++v3;
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == -1 + i);
        assert(result3[i] == -1 + i);
    }
    assert(&result3 == &v3);

    // Test case 4: Test saturation at maximum value
    Vec2q v4(INT64_MAX, INT64_MAX-1);
    Vec2q& result4 = ++v4;
    assert(v4[0] == INT64_MAX);     // Saturated
    assert(v4[1] == INT64_MAX);     // Saturated
    
    // Check reference
    assert(&result4 == &v4);
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == v4[i]);
    }

    // Test case 5: Multiple increments
    Vec2q v5(1, 1);
    Vec2q& result5 = ++v5;
    ++v5;
    for(int i = 0; i < 2; i++) {
        assert(v5[i] == 3);
        assert(result5[i] == 3);
    }
    assert(&result5 == &v5);

    std::cout << "test_prefix_increment_operator passed!\n";
}

void test_subtract_operator() {
    // Test case 1: Basic subtraction
    Vec2q v1(2, 3);
    Vec2q v2(1, 1);
    Vec2q result1 = v1 - v2;
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == i + 1);
    }

    // Test case 2: Subtracting zeros (identity operation)
    Vec2q v3(1, 2);
    Vec2q zeros(0);
    Vec2q result2 = v3 - zeros;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == v3[i]);
    }

    // Test case 3: Subtracting from zeros
    Vec2q v4(1, 2);
    Vec2q result3 = zeros - v4;
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == -(i + 1));
    }

    // Test case 4: Testing saturation (underflow protection)
    Vec2q v5(INT64_MIN, INT64_MIN);
    Vec2q v6(1, INT64_MAX);
    Vec2q result4 = v5 - v6;
    assert(result4[0] == INT64_MIN);  // Saturated subtraction
    assert(result4[1] == INT64_MIN);  // Saturated subtraction

    // Test case 5: Chained subtractions
    Vec2q v7(9, 9);
    Vec2q v8(3, 3);
    Vec2q result5 = v7 - v8 - v8;  // Should be (3,3)
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 3);
    }

    std::cout << "test_subtract_operator passed!\n";
}
void test_unary_minus_operator() {
    // Test case 1: Negate positive values
    Vec2q v1(1, 2);
    Vec2q result1 = -v1;
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == -(i + 1));
    }

    // Test case 2: Negate zero
    Vec2q v2(0);
    Vec2q result2 = -v2;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: Negate negative values
    Vec2q v3(-1, -2);
    Vec2q result3 = -v3;
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == i + 1);
    }

    // Test case 4: Test with minimum/maximum values
    Vec2q v4(INT64_MIN, INT64_MAX);
    Vec2q result4 = -v4;
    assert(result4[0] == INT64_MIN);  // Negating INT64_MIN stays INT64_MIN due to 2's complement
    assert(result4[1] == -INT64_MAX);

    // Test case 5: Double negation should return to original value
    Vec2q v5(1, -2);
    Vec2q result5 = -(-v5);
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == v5[i]);
    }

    std::cout << "test_unary_minus_operator passed!\n";
}
void test_subtract_assign_operator() {
    // Test case 1: Basic subtraction assignment
    Vec2q v1(2, 3);
    Vec2q v2(1, 1);
    v1 -= v2;
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == i + 1);
    }

    // Test case 2: Subtracting zeros (identity operation)
    Vec2q v3(1, 2);
    Vec2q zeros(0);
    v3 -= zeros;
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == i + 1);
    }

    // Test case 3: Subtracting to get zeros
    Vec2q v4(1, 2);
    Vec2q v5(1, 2);
    v4 -= v5;
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == 0);
    }

    // Test case 4: Testing saturation (underflow protection)
    Vec2q v6(INT64_MIN, INT64_MIN);
    Vec2q v7(1, INT64_MAX);
    v6 -= v7;
    assert(v6[0] == INT64_MIN);  // Saturated subtraction
    assert(v6[1] == INT64_MIN);  // Saturated subtraction

    // Test case 5: Chained subtractions
    Vec2q v8(9, 9);
    Vec2q v9(3, 3);
    v8 -= v9 -= v9;  // v9 becomes (0,0), then v8 becomes (9,9)
    for(int i = 0; i < 2; i++) {
        assert(v8[i] == 9);
        assert(v9[i] == 0);
    }

    std::cout << "test_subtract_assign_operator passed!\n";
}
void test_postfix_decrement_operator() {
    // Test case 1: Basic decrement
    Vec2q v1(2, 3);
    Vec2q result1 = v1--;
    // Check that result holds original values
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == i + 2);
    }
    // Check that original vector was decremented
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == i + 1);
    }

    // Test case 2: Decrement zeros
    Vec2q v2(0);
    Vec2q result2 = v2--;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0);
        assert(v2[i] == -1);
    }

    // Test case 3: Decrement positive values to negative
    Vec2q v3(8, 7);
    Vec2q result3 = v3--;
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == 8 - i);
        assert(v3[i] == 7 - i);
    }

    // Test case 4: Test saturation at minimum value
    Vec2q v4(INT64_MIN, INT64_MIN+1);
    Vec2q result4 = v4--;
    assert(result4[0] == INT64_MIN);
    assert(result4[1] == INT64_MIN+1);
    
    assert(v4[0] == INT64_MIN);     // Saturated
    assert(v4[1] == INT64_MIN);     // Saturated

    // Test case 5: Multiple decrements
    Vec2q v5(3, 3);
    Vec2q result5 = v5--;
    result5 = v5--;
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 2);
        assert(v5[i] == 1);
    }

    std::cout << "test_postfix_decrement_operator passed!\n";
}
void test_prefix_decrement_operator() {
    // Test case 1: Basic decrement
    Vec2q v1(2, 3);
    Vec2q& result1 = --v1;
    // Check decremented values
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == i + 1);
    }
    // Check that result references the decremented vector
    assert(&result1 == &v1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == i + 1);
    }

    // Test case 2: Decrement zeros
    Vec2q v2(0);
    Vec2q& result2 = --v2;
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == -1);
        assert(result2[i] == -1);
    }
    assert(&result2 == &v2);

    // Test case 3: Decrement positive values to negative
    Vec2q v3(8, 7);
    Vec2q& result3 = --v3;
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == 7 - i);
        assert(result3[i] == 7 - i);
    }
    assert(&result3 == &v3);

    // Test case 4: Test saturation at minimum value
    Vec2q v4(INT64_MIN, INT64_MIN + 1);
    Vec2q& result4 = --v4;
    assert(v4[0] == INT64_MIN);     // Saturated
    assert(v4[1] == INT64_MIN);     // Saturated
    
    // Check reference
    assert(&result4 == &v4);
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == v4[i]);
    }

    // Test case 5: Multiple decrements
    Vec2q v5(3, 3);
    Vec2q& result5 = --v5;
    --v5;
    for(int i = 0; i < 2; i++) {
        assert(v5[i] == 1);
        assert(result5[i] == 1);
    }
    assert(&result5 == &v5);

    std::cout << "test_prefix_decrement_operator passed!\n";
}

void test_multiply_operator() {
    // Test case 1: Basic multiplication
    Vec2q v1(1, 2);
    Vec2q v2(2, 2);
    Vec2q result1 = v1 * v2;
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == 2 * (i + 1));
    }

    // Test case 2: Multiply by zero
    Vec2q v3(1, 2);
    Vec2q zeros(0);
    Vec2q result2 = v3 * zeros;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: Multiply by one (identity)
    Vec2q v4(1, 2);
    Vec2q ones(1);
    Vec2q result3 = v4 * ones;
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == i + 1);
    }

    // Test case 4: Multiply negative numbers
    Vec2q v5(-1, -2);
    Vec2q v6(2, 3);
    Vec2q result4 = v5 * v6;
    int64_t expected4[] = {-2, -6};
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == expected4[i]);
    }

    // Test case 5: Test saturation (overflow protection)
    Vec2q v7(INT64_MAX, INT64_MAX);
    Vec2q v8(2, INT64_MAX);
    Vec2q result5 = v7 * v8;
    assert(result5[0] == 0xFFFFFFFFFFFFFFFE);  // Saturated multiplication
    assert(result5[1] == 1);  // Saturated multiplication

    // Test case 6: Chained multiplications
    Vec2q v9(1, 1);
    Vec2q v10(2, 2);
    Vec2q result6 = v9 * v10 * v10;  // Should be (4,4)
    for(int i = 0; i < 2; i++) {
        assert(result6[i] == 4);
    }

    std::cout << "test_multiply_operator passed!\n";
}
void test_multiply_assign_operator() {
    // Test case 1: Basic multiplication assignment
    Vec2q v1(1, 2);
    Vec2q v2(2, 2);
    v1 *= v2;
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == 2 * (i + 1));
    }

    // Test case 2: Multiply by zero
    Vec2q v3(1, 2);
    Vec2q zeros(0);
    v3 *= zeros;
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == 0);
    }

    // Test case 3: Multiply by one (identity)
    Vec2q v4(1, 2);
    Vec2q ones(1);
    v4 *= ones;
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == i + 1);
    }

    // Test case 4: Multiply negative numbers
    Vec2q v5(-1, -2);
    Vec2q v6(2, 3);
    v5 *= v6;
    int64_t expected[] = {-2, -6};
    for(int i = 0; i < 2; i++) {
        assert(v5[i] == expected[i]);
    }

    // Test case 5: Test saturation (overflow protection)
    Vec2q v7(INT64_MAX, INT64_MAX);
    Vec2q v8(2, INT64_MAX);
    v7 *= v8;
    assert(v7[0] == 0xFFFFFFFFFFFFFFFE);  // Saturated multiplication
    assert(v7[1] == 1);  // Saturated multiplication

    // Test case 6: Chained multiplications
    Vec2q v9(1, 1);
    Vec2q v10(2, 2);
    v9 *= v10 *= v10;  // v10 becomes (4,4), then v9 becomes (4,4)
    for(int i = 0; i < 2; i++) {
        assert(v9[i] == 4);
        assert(v10[i] == 4);
    }

    std::cout << "test_multiply_assign_operator passed!\n";
}
void test_shift_left_operator() {
    // Test case 1: Basic shift left by 1
    Vec2q v1(1, 2);
    Vec2q result1 = v1 << 1;
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == (i + 1) * 2);
    }

    // Test case 2: Shift left by 0 (no change)
    Vec2q v2(1, 2);
    Vec2q result2 = v2 << 0;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == i + 1);
    }

    // Test case 3: Shift left by multiple positions
    Vec2q v3(1, 2);
    Vec2q result3 = v3 << 3;  // Multiply by 8
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == (i + 1) * 8);
    }

    // Test case 4: Shift left with negative numbers
    Vec2q v4(-8, -7);
    Vec2q result4 = v4 << 2;  // Multiply by 4
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == (-8 + i) * 4);
    }

    // Test case 5: Test overflow and saturation behavior
    Vec2q v5((int64_t)INT64_MAX>>1, (int64_t)INT64_MIN>>1);
    Vec2q result5 = v5 << 1;
    assert(result5[0] == 0x7FFFFFFFFFFFFFFE);// Saturated to INT64_MAX -1
    assert(result5[1] == INT64_MIN);      // Saturated to INT64_MIN

    // Test case 6: Shift by larger values
    Vec2q v6(1, 2);
    Vec2q result6 = v6 << 14;  // Large shift
    assert(result6[0] == 16384);       // 1 << 14
    assert(result6[1] == 32768);       // 2 << 14

    // Test case 7: Chain multiple shifts
    Vec2q v7(1, 1);
    Vec2q result7 = (v7 << 1) << 2;  // Shift left by 3 total
    for(int i = 0; i < 2; i++) {
        assert(result7[i] == 8);    // 1 * 2^3
    }

    // Test case 8: Shift that clears all bits
    Vec2q v8(1, 2);
    Vec2q result8 = v8 << 64;  // Shift beyond number of useful bits
    for(int i = 0; i < 2; i++) {
        assert(result8[i] == 0); // All bits should be cleared
    }
    std::cout << "test_shift_left_operator passed!\n";
}
void test_shift_left_assign_operator() {
    // Test case 1: Basic shift left assign by 1
    Vec2q v1(1, 2);
    v1 <<= 1;
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == (i + 1) * 2);
    }

    // Test case 2: Shift left assign by 0 (no change)
    Vec2q v2(1, 2);
    v2 <<= 0;
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Shift left assign by multiple positions
    Vec2q v3(1, 2);
    v3 <<= 3;  // Multiply by 8
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == (i + 1) * 8);
    }

    // Test case 4: Shift left assign with negative numbers
    Vec2q v4(-8, -7);
    v4 <<= 2;  // Multiply by 4
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == (-8 + i) * 4);
    }

    // Test case 5: Test shift behavior with large integers
    Vec2q v5(1LL << 60, -(1LL << 60));
    v5 <<= 1;
    assert(v5[0] == (1LL << 61));        // Regular shift left
    assert(v5[1] == (-(1LL << 61)));     // Regular shift left preserving sign

    // Test case 6: Chain multiple shift assignments
    Vec2q v6(1, 1);
    (v6 <<= 1) <<= 2;  // Shift left by 3 total
    for(int i = 0; i < 2; i++) {
        assert(v6[i] == 8);    // 1 * 2^3
    }

    // Test case 7: Shift assign by larger values 
    Vec2q v7(1, 2);
    v7 <<= 30;  // Large shift
    for(int i = 0; i < 2; i++) {
        assert(v7[i] == ((int64_t)(i+1)) << 30); 
    }

    // Test case 8: Shift that clears all bits
    Vec2q v8(1, 2);
    v8 <<= 64;  // Shift beyond number of useful bits
    for(int i = 0; i < 2; i++) {
        assert(v8[i] == 0); // All bits should be cleared
    }
    
    std::cout << "test_shift_left_assign_operator passed!\n";
}
void test_shift_right_operator() {
    // Test case 1: Basic shift right by 1
    Vec2q v1(2, 4);
    Vec2q result1 = v1 >> 1;
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == (i + 1) * 2 / 2);
    }

    // Test case 2: Shift right by 0 (no change)
    Vec2q v2(1, 2);
    Vec2q result2 = v2 >> 0;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == i + 1);
    }

    // Test case 3: Shift right by multiple positions
    Vec2q v3(8, 16);
    Vec2q result3 = v3 >> 3;  // Divide by 8
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == (i + 1));
    }

    // Test case 4: Shift right with negative numbers (arithmetic shift)
    Vec2q v4(-8, -16);
    Vec2q result4 = v4 >> 2;  // Divide by 4, preserving sign
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == (-8 - i * 8) / 4);
    }

    // Test case 5: Test sign preservation behavior
    Vec2q v5(INT64_MIN, -16384);
    Vec2q result5 = v5 >> 1;
    assert(result5[0] == INT64_MIN/2);  // INT64_MIN / 2
    assert(result5[1] == -8192);        // -16384 / 2

    // Test case 6: Shift by larger values
    Vec2q v6(INT64_MIN, -16384);
    Vec2q result6 = v6 >> 14;  // Large shift
    assert(result6[0] == INT64_MIN >> 14);  // Sign preserved
    assert(result6[1] == -1);               // Sign preserved

    // Test case 7: Chain multiple shifts
    Vec2q v7(64, 64);
    Vec2q result7 = (v7 >> 1) >> 2;  // Shift right by 3 total
    for(int i = 0; i < 2; i++) {
        assert(result7[i] == 8);    // 64 / 2^3
    }

    // Test case 8: Shift that clears all bits
    Vec2q v8(1, 2);
    Vec2q result8 = v8 >> 63;  // Shift beyond number of bits
    for(int i = 0; i < 2; i++) {
        assert(result8[i] == 0); // All bits should be cleared
    }
    std::cout << "test_shift_right_operator passed!\n";
}
void test_shift_right_assign_operator() {
    // Test case 1: Basic shift right assign by 1
    Vec2q v1(2, 4);
    v1 >>= 1;
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == (i + 1) * 2 / 2);
    }

    // Test case 2: Shift right assign by 0 (no change)
    Vec2q v2(1, 2);
    v2 >>= 0;
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Shift right assign by multiple positions
    Vec2q v3(8, 16);
    v3 >>= 3;  // Divide by 8
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == (i + 1));
    }

    // Test case 4: Shift right assign with negative numbers (arithmetic shift)
    Vec2q v4(-8, -16);
    v4 >>= 2;  // Divide by 4, preserving sign
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == (-8 - i * 8) / 4);
    }

    // Test case 5: Test sign preservation behavior
    Vec2q v5(-32768, -16384);
    v5 >>= 1;
    assert(v5[0] == -16384);  // -32768 / 2
    assert(v5[1] == -8192);   // -16384 / 2

    // Test case 6: Chain multiple shift assignments
    Vec2q v6(64, 64);
    (v6 >>= 1) >>= 2;  // Shift right by 3 total
    for(int i = 0; i < 2; i++) {
        assert(v6[i] == 8);    // 64 / 2^3
    }

    // Test case 7: Shift assign by larger values
    Vec2q v7(-32768, -16384);
    v7 >>= 14;  // Large shift
    assert(v7[0] == -2);  // Sign preserved
    assert(v7[1] == -1);  // Sign preserved

    // Test case 8: Shift that clears all bits
    Vec2q v8(1, 2);
    v8 >>= 16;  // Shift beyond number of bits
    for(int i = 0; i < 2; i++) {
        assert(v8[i] == 0);  // All bits should be cleared
    }

    std::cout << "test_shift_right_assign_operator passed!\n";
}

void test_operator_equal() {
    // Test case 1: Equal vectors
    Vec2q v1(1, 2);
    Vec2q v2(1, 2);
    Vec2uq result1 = (v1 == v2);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == -1); // All bits set when equal
    }

    // Test case 2: Different vectors
    Vec2q v3(1, 2);
    Vec2q v4(2, 1);
    Vec2uq result2 = (v3 == v4);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0); // All bits clear when not equal
    }

    // Test case 3: Partially equal vectors
    Vec2q v5(1, 2);
    Vec2q v6(1, 0);
    Vec2uq result3 = (v5 == v6);
    assert(result3[0] == -1); // Equal
    assert(result3[1] == 0);  // Not equal

    // Test case 4: Compare with zeros
    Vec2q v7(0);
    Vec2q v8(0);
    Vec2uq result4 = (v7 == v8);
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == -1); // All equal to zero
    }

    // Test case 5: Compare with maximum values
    Vec2q v9(INT64_MAX, INT64_MAX);
    Vec2q v10(INT64_MAX, INT64_MAX);
    Vec2uq result5 = (v9 == v10);
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == -1); // All equal to INT64_MAX
    }

    std::cout << "test_operator_equal passed!\n";
}
void test_operator_not_equal() {
    // Test case 1: Equal vectors should return false
    Vec2q v1(1, 2);
    Vec2q v2(1, 2);
    Vec2uq result1 = (v1 != v2);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == 0); // All bits clear when equal
    }

    // Test case 2: Different vectors should return true
    Vec2q v3(1, 2);
    Vec2q v4(2, 1);
    Vec2uq result2 = (v3 != v4);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == -1); // All bits set when not equal
    }

    // Test case 3: Partially equal vectors
    Vec2q v5(1, 2);
    Vec2q v6(1, 3);
    Vec2uq result3 = (v5 != v6);
    assert(result3[0] == 0);  // Equal
    assert(result3[1] == -1); // Not equal

    // Test case 4: Compare with zeros
    Vec2q v7(0);
    Vec2q v8(0);
    Vec2uq result4 = (v7 != v8);
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == 0); // None not equal to zero
    }

    // Test case 5: Compare with maximum values
    Vec2q v9(INT64_MAX, INT64_MAX);
    Vec2q v10(INT64_MAX, INT64_MAX);
    Vec2uq result5 = (v9 != v10);
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 0); // None not equal to INT64_MAX
    }

    std::cout << "test_operator_not_equal passed!\n";
}
void test_greater_than_operator() {
    // Test case 1: Basic greater than comparison
    Vec2q v1(2, 3);
    Vec2q v2(1, 2);
    Vec2uq result1 = (v1 > v2);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == -1); // All should be greater (-1 = all bits set)
    }

    // Test case 2: Equal values should return false
    Vec2q v3(1, 2);
    Vec2q v4(1, 2);
    Vec2uq result2 = (v3 > v4);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0); // None should be greater
    }

    // Test case 3: Mixed comparisons
    Vec2q v5(1, 3);
    Vec2q v6(2, 2);
    Vec2uq result3 = (v5 > v6);
    assert(result3[0] == 0);         // 1 > 2
    assert(result3[1] == -1);        // 3 > 2

    // Test case 4: Compare with maximum and minimum values
    Vec2q v7(INT64_MAX, INT64_MAX-1);
    Vec2q v8(INT64_MAX-1, INT64_MAX);
    Vec2uq result4 = (v7 > v8);
    assert(result4[0] == -1);        // INT64_MAX > INT64_MAX-1
    assert(result4[1] == 0);         // INT64_MAX-1 > INT64_MAX

    // Test case 5: Compare with zeros
    Vec2q v9(1, -1);
    Vec2q zeros(0);
    Vec2uq result5 = (v9 > zeros);
    assert(result5[0] == -1);        // 1 > 0
    assert(result5[1] == 0);         // -1 > 0

    std::cout << "test_greater_than_operator passed!\n";
}
void test_less_than_operator() {
    // Test case 1: Basic less than comparison
    Vec2q v1(1, 2);
    Vec2q v2(2, 3);
    Vec2uq result1 = (v1 < v2);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == -1); // All should be less (-1 = all bits set)
    }

    // Test case 2: Equal values should return false
    Vec2q v3(1, 2);
    Vec2q v4(1, 2);
    Vec2uq result2 = (v3 < v4);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0); // None should be less
    }

    // Test case 3: Mixed comparisons
    Vec2q v5(2, 2);
    Vec2q v6(1, 3);
    Vec2uq result3 = (v5 < v6);
    assert(result3[0] == 0);      // 2 < 1
    assert(result3[1] == -1);     // 2 < 3

    // Test case 4: Compare with maximum and minimum values
    Vec2q v7(INT64_MAX-1, INT64_MAX);
    Vec2q v8(INT64_MAX, INT64_MAX-1);
    Vec2uq result4 = (v7 < v8);
    assert(result4[0] == -1);     // INT64_MAX-1 < INT64_MAX
    assert(result4[1] == 0);      // INT64_MAX < INT64_MAX-1

    // Test case 5: Compare with zeros
    Vec2q v9(1, -1);
    Vec2q zeros(0);
    Vec2uq result5 = (v9 < zeros);
    assert(result5[0] == 0);      // 1 < 0
    assert(result5[1] == -1);     // -1 < 0

    std::cout << "test_less_than_operator passed!\n";
}
void test_greater_than_or_equal_operator() {
    // Test case 1: Basic greater than or equal comparison
    Vec2q v1(2, 3);
    Vec2q v2(1, 2);
    Vec2uq result1 = (v1 >= v2);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == -1); // All should be greater or equal
    }

    // Test case 2: Equal values should return true
    Vec2q v3(1, 2);
    Vec2q v4(1, 2);
    Vec2uq result2 = (v3 >= v4);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == -1); // All should be equal (all bits set)
    }

    // Test case 3: Mixed comparisons
    Vec2q v5(1, 3);
    Vec2q v6(2, 2);
    Vec2uq result3 = (v5 >= v6);
    assert(result3[0] == 0);    // 1 >= 2
    assert(result3[1] == -1);   // 3 >= 2

    // Test case 4: Compare with maximum and minimum values
    Vec2q v7(INT64_MAX, INT64_MAX-1);
    Vec2q v8(INT64_MAX, INT64_MAX);
    Vec2uq result4 = (v7 >= v8);
    assert(result4[0] == -1);   // INT64_MAX >= INT64_MAX
    assert(result4[1] == 0);    // INT64_MAX-1 >= INT64_MAX

    // Test case 5: Compare with zeros
    Vec2q v9(1, -1);
    Vec2q zeros(0);
    Vec2uq result5 = (v9 >= zeros);
    assert(result5[0] == -1);   // 1 >= 0
    assert(result5[1] == 0);    // -1 >= 0

    std::cout << "test_greater_than_or_equal_operator passed!\n";
}
void test_less_than_or_equal_operator() {
    // Test case 1: Basic less than or equal comparison
    Vec2q v1(1, 2);
    Vec2q v2(2, 3);
    Vec2uq result1 = (v1 <= v2);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == -1); // All should be less or equal (-1 = all bits set)
    }

    // Test case 2: Equal values should return true
    Vec2q v3(1, 2);
    Vec2q v4(1, 2);
    Vec2uq result2 = (v3 <= v4);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == -1); // All should be equal (-1 = all bits set)
    }

    // Test case 3: Mixed comparisons
    Vec2q v5(2, 2);
    Vec2q v6(1, 3);
    Vec2uq result3 = (v5 <= v6);
    assert(result3[0] == 0);     // 2 <= 1
    assert(result3[1] == -1);    // 2 <= 3

    // Test case 4: Compare with maximum and minimum values
    Vec2q v7(INT64_MAX-1, INT64_MAX);
    Vec2q v8(INT64_MAX, INT64_MAX-1);
    Vec2uq result4 = (v7 <= v8);
    assert(result4[0] == -1);    // INT64_MAX-1 <= INT64_MAX
    assert(result4[1] == 0);     // INT64_MAX <= INT64_MAX-1

    // Test case 5: Compare with zeros
    Vec2q v9(1, -1);
    Vec2q zeros(0);
    Vec2uq result5 = (v9 <= zeros);
    assert(result5[0] == 0);     // 1 <= 0
    assert(result5[1] == -1);    // -1 <= 0

    std::cout << "test_less_than_or_equal_operator passed!\n";
}

void test_bitwise_and_operator() {
    // Test case 1: Basic AND operation with all bits set
    Vec2q v1(32767, 32767);
    Vec2q v2(0x5555, 0x5555);
    Vec2q result1 = v1 & v2;
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == 0x5555);
    }

    // Test case 2: AND with zero
    Vec2q v3(1, 2);
    Vec2q zeros(0);
    Vec2q result2 = v3 & zeros;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: AND with alternating bits
    Vec2q v4(0x5555, 0x5555);
    Vec2q v5(0x5555, 0x5555);
    Vec2q result3 = v4 & v5;
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == 0x5555);
    }

    // Test case 4: AND with negative numbers
    Vec2q v6(-1, -2);
    Vec2q v7(1, 2);
    Vec2q result4 = v6 & v7;
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == ((-1-i) & (i+1)));
    }

    // Test case 5: AND with maximum values
    Vec2q v8(INT64_MAX, INT64_MAX);
    Vec2q v9(0x7FFFFFFFFFFFFFFF, 0x7FFFFFFFFFFFFFFF);
    Vec2q result5 = v8 & v9;
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 0x7FFFFFFFFFFFFFFF);
    }

    std::cout << "test_bitwise_and_operator passed!\n";
}
void test_bitwise_or_operator() {
    // Test case 1: Basic OR operation with bits
    Vec2q v1(0x5555, 0x5555);
    Vec2q v2(0x2AAA, 0x2AAA);
    Vec2q result1 = v1 | v2;
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == 0x7FFF); // Maximum positive value
    }

    // Test case 2: OR with zero (identity operation)
    Vec2q v3(1, 2);
    Vec2q zeros(0);
    Vec2q result2 = v3 | zeros;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == i + 1);
    }

    // Test case 3: OR with all bits set
    Vec2q v4(0x1234, 0x5678);
    Vec2q all_ones(0x7FFF);
    Vec2q result3 = v4 | all_ones;
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == 0x7FFF); // All results should be max positive value
    }

    // Test case 4: OR with negative numbers
    Vec2q v5(-1, -2);
    Vec2q v6(1, 2);
    Vec2q result4 = v5 | v6;
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == ((-1-i) | (i+1)));
    }

    // Test case 5: OR with maximum/minimum values
    Vec2q v7(INT64_MAX, INT64_MIN);
    Vec2q v8(0x5555555555555555, 0x2AAAAAAAAAAAAAAA);
    Vec2q result5 = v7 | v8;
    assert(result5[0] == (INT64_MAX | 0x5555555555555555));
    assert(result5[1] == (INT64_MIN | 0x2AAAAAAAAAAAAAAA));

    std::cout << "test_bitwise_or_operator passed!\n";
}
void test_bitwise_xor_operator() {
    // Test case 1: Basic XOR operation with alternating bits
    Vec2q v1(0x5555, 0x5555);
    Vec2q v2(0x2AAA, 0x2AAA);
    Vec2q result1 = v1 ^ v2;
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == 0x7FFF); // All bits set up to max signed value
    }

    // Test case 2: XOR with zero (identity operation)
    Vec2q v3(1, 2);
    Vec2q zeros(0);
    Vec2q result2 = v3 ^ zeros;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == i + 1);
    }

    // Test case 3: XOR with self (should be zero)
    Vec2q v4(0x1234, 0x5678);
    Vec2q result3 = v4 ^ v4;
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == 0); // XOR with self gives 0
    }

    // Test case 4: XOR with negative numbers
    Vec2q v5(-1, -2);
    Vec2q v6(1, 2);
    Vec2q result4 = v5 ^ v6;
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == ((-1-i) ^ (i+1)));
    }

    // Test case 5: XOR with maximum/minimum values
    Vec2q v7(INT64_MAX, INT64_MIN);
    Vec2q v8(0x5555555555555555, 0x2AAAAAAAAAAAAAAA);
    Vec2q result5 = v7 ^ v8;
    assert(result5[0] == (INT64_MAX ^ 0x5555555555555555));
    assert(result5[1] == (INT64_MIN ^ 0x2AAAAAAAAAAAAAAA));

    std::cout << "test_bitwise_xor_operator passed!\n";
}
void test_bitwise_not_operator() {
    // Test case 1: NOT on zeros (should give all ones)
    Vec2q v1(0);
    Vec2q result1 = ~v1;
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == -1); // All bits set (-1 in two's complement)
    }

    // Test case 2: NOT on all ones (should give zeros) 
    Vec2q v2(-1);  // All bits set
    Vec2q result2 = ~v2;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: NOT on alternating bits
    Vec2q v3(0x5555555555555555, 0x5555555555555555);
    Vec2q result3 = ~v3;
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == (int64_t)0xAAAAAAAAAAAAAAAA); // Cast to signed for proper comparison
    }

    // Test case 4: NOT on positive numbers
    Vec2q v4(1, 2);
    Vec2q result4 = ~v4;
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == ~(int64_t)(i + 1));
    }

    // Test case 5: NOT on max/min values
    Vec2q v5(INT64_MAX, INT64_MIN);
    Vec2q result5 = ~v5;
    assert(result5[0] == ~INT64_MAX);      // NOT on maximum positive value
    assert(result5[1] == ~INT64_MIN);      // NOT on minimum negative value

    std::cout << "test_bitwise_not_operator passed!\n";
}

void test_select() {
    // Test case 1: Basic selection with all true mask
    Vec2uq mask1(0xFFFFFFFFFFFFFFFF);  // All bits set (true)
    Vec2q a1(1, 2);
    Vec2q b1(-1, -2);
    Vec2q result1 = select(mask1, a1, b1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == i + 1);  // Should select all from a1
    }

    // Test case 2: Basic selection with all false mask
    Vec2uq mask2(0);  // All bits clear (false)
    Vec2q a2(1, 2);
    Vec2q b2(-1, -2);
    Vec2q result2 = select(mask2, a2, b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == -(i + 1));  // Should select all from b2
    }

    // Test case 3: Alternating selection
    Vec2uq mask3(0xFFFFFFFFFFFFFFFF, 0);
    Vec2q a3(1, 2);
    Vec2q b3(-1, -2);
    Vec2q result3 = select(mask3, a3, b3);
    assert(result3[0] == 1);   // From a3
    assert(result3[1] == -2);  // From b3

    // Test case 4: Selection with special values
    Vec2uq mask4(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
    Vec2q a4(INT64_MAX, INT64_MIN);
    Vec2q b4(-INT64_MAX, INT64_MAX);
    Vec2q result4 = select(mask4, a4, b4);
    assert(result4[0] == INT64_MAX);    // From a4
    assert(result4[1] == INT64_MIN);    // From a4

    // Test case 5: Selection with zeros and ones
    Vec2uq mask5(0xFFFFFFFFFFFFFFFF);  // All bits set
    Vec2q a5(0);     // All zeros
    Vec2q b5(1);     // All ones
    Vec2q result5 = select(mask5, a5, b5);
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 0);  // Should select all zeros from a5
    }

    std::cout << "test_select passed!\n";
}
void test_if_add() {
    // Test case 1: Basic conditional add with all true mask
    Vec2uq mask1(0xFFFFFFFFFFFFFFFF);  // All bits set (true)
    Vec2q a1(1, 2);
    Vec2q b1(1, 1);
    Vec2q result1 = if_add(mask1, a1, b1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == i + 2);  // Should add all elements
    }

    // Test case 2: Conditional add with all false mask
    Vec2uq mask2(0);  // All bits clear (false)
    Vec2q a2(1, 2);
    Vec2q b2(1, 1);
    Vec2q result2 = if_add(mask2, a2, b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == i + 1);  // Should not add anything
    }

    // Test case 3: Alternating conditional add
    Vec2uq mask3(0xFFFFFFFFFFFFFFFF, 0);
    Vec2q a3(1, 2);
    Vec2q b3(10, 20);
    Vec2q result3 = if_add(mask3, a3, b3);
    assert(result3[0] == 11);  // 1 + 10
    assert(result3[1] == 2);   // 2 + 0

    // Test case 4: Test saturation behavior
    Vec2uq mask4(0xFFFFFFFFFFFFFFFF);
    Vec2q a4(INT64_MAX, INT64_MAX-1);
    Vec2q b4(1, 2);
    Vec2q result4 = if_add(mask4, a4, b4);
    assert(result4[0] == INT64_MAX);      // Saturated addition
    assert(result4[1] == INT64_MAX);      // Saturated addition

    // Test case 5: Test with zero operands
    Vec2uq mask5(0xFFFFFFFFFFFFFFFF);
    Vec2q a5(0);
    Vec2q b5(0);
    Vec2q result5 = if_add(mask5, a5, b5);
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 0);  // 0 + 0 should be 0
    }

    std::cout << "test_if_add passed!\n";
}
void test_if_sub() {
    // Test case 1: Basic conditional subtract with all true mask
    Vec2uq mask1(-1);  // All bits set (true)
    Vec2q a1(10, 20);
    Vec2q b1(1, 2);
    Vec2q result1 = if_sub(mask1, a1, b1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == 10*(i+1) - (i+1));  // Should subtract all elements
    }

    // Test case 2: Conditional subtract with all false mask
    Vec2uq mask2(0);  // All bits clear (false)
    Vec2q a2(10, 20);
    Vec2q b2(1, 2);
    Vec2q result2 = if_sub(mask2, a2, b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 10*(i+1));  // Should not subtract anything
    }

    // Test case 3: Alternating conditional subtract
    Vec2uq mask3(-1, 0);
    Vec2q a3(10, 20);
    Vec2q b3(1, 2);
    Vec2q result3 = if_sub(mask3, a3, b3);
    assert(result3[0] == 9);   // 10 - 1
    assert(result3[1] == 20);  // 20 - 0

    // Test case 4: Test saturation behavior
    Vec2uq mask4(-1);
    Vec2q a4(INT64_MIN, INT64_MIN+1);
    Vec2q b4(1, 2);
    Vec2q result4 = if_sub(mask4, a4, b4);
    assert(result4[0] == INT64_MIN);      // Saturated subtraction
    assert(result4[1] == INT64_MIN);      // Saturated subtraction

    // Test case 5: Test with zero operands
    Vec2uq mask5(-1);
    Vec2q a5(0);
    Vec2q b5(0);
    Vec2q result5 = if_sub(mask5, a5, b5);
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 0);  // 0 - 0 should be 0
    }

    std::cout << "test_if_sub passed!\n";
}

void test_if_mul() {
    // Test case 1: Basic conditional multiply with all true mask
    Vec2uq mask1(0xFFFFFFFFFFFFFFFF);  // All bits set (true)
    Vec2q a1(1, 2);
    Vec2q b1(2, 2);
    Vec2q result1 = if_mul(mask1, a1, b1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == (i + 1) * 2);  // Should multiply all elements
    }

    // Test case 2: Conditional multiply with all false mask
    Vec2uq mask2(0);  // All bits clear (false)
    Vec2q a2(1, 2);
    Vec2q b2(2, 2);
    Vec2q result2 = if_mul(mask2, a2, b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == i + 1);  // Should return original a values
    }

    // Test case 3: Alternating conditional multiply
    Vec2uq mask3(0xFFFFFFFFFFFFFFFF, 0);
    Vec2q a3(1, 2);
    Vec2q b3(10, 20);
    
    Vec2q result3 = if_mul(mask3, a3, b3);
    assert(result3[0] == 10);  // 1 * 10
    assert(result3[1] == 2);   // 2 (original)

    // Test case 4: Test saturation behavior
    Vec2uq mask4(0xFFFFFFFFFFFFFFFF);
    Vec2q a4(INT64_MAX/2, INT64_MIN/2);
    Vec2q b4(2, 2);

    Vec2q result4 = if_mul(mask4, a4, b4);
    assert(result4[0] == 0x7FFFFFFFFFFFFFFE);  // Saturated multiplication
    assert(result4[1] == INT64_MIN);  // Saturated multiplication

    // Test case 5: Test with zero operands
    Vec2uq mask5(0xFFFFFFFFFFFFFFFF);
    Vec2q a5(1, 2);
    Vec2q b5(0);
    Vec2q result5 = if_mul(mask5, a5, b5);
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 0);  // Multiplication by 0 should give 0
    }

    std::cout << "test_if_mul passed!\n";
}

void test_horizontal_add() {
    // Test case 1: Basic addition of positive numbers
    Vec2q v1(1, 2);
    int64_t result1 = horizontal_add(v1);
    assert(result1 == 3);  // 1 + 2 = 3

    // Test case 2: Addition of negative numbers
    Vec2q v2(-1, -2);
    int64_t result2 = horizontal_add(v2);
    assert(result2 == -3);  // -1 + (-2) = -3

    // Test case 3: Addition of zeros
    Vec2q v3(0);
    int64_t result3 = horizontal_add(v3);
    assert(result3 == 0);  // 0 + 0 = 0

    // Test case 4: Mixed positive and negative numbers
    Vec2q v4(1, -1);
    int64_t result4 = horizontal_add(v4);
    assert(result4 == 0);  // 1 + (-1) = 0

    // Test case 5: Large numbers testing potential overflow
    Vec2q v5(INT64_MAX, INT64_MIN);
    int64_t result5 = horizontal_add(v5);
    assert(result5 == -1);  // INT64_MAX + INT64_MIN = -1

    // Test case 6: Alternating positive numbers
    Vec2q v6(1, 3);
    int64_t result6 = horizontal_add(v6);
    assert(result6 == 4);  // 1 + 3 = 4

    // Test case 7: Random mix of numbers
    Vec2q v7(100, -50);
    int64_t result7 = horizontal_add(v7);
    assert(result7 == 50);  // 100 + (-50) = 50

    std::cout << "test_horizontal_add passed!\n";
}
void test_max() {
    // Test case 1: Basic max comparison with positive numbers
    Vec2q v1(1, 2);
    Vec2q v2(4, 1);
    Vec2q result1 = max(v1, v2);
    assert(result1[0] == 4);
    assert(result1[1] == 2);

    // Test case 2: Max of equal numbers
    Vec2q v3(1, 2);
    Vec2q v4(1, 2);
    Vec2q result2 = max(v3, v4);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == i + 1);  // Should return same numbers
    }

    // Test case 3: Max with negative numbers
    Vec2q v5(-4, -3);
    Vec2q v6(-1, -2);
    Vec2q result3 = max(v5, v6);
    assert(result3[0] == -1);
    assert(result3[1] == -2);

    // Test case 4: Max with mix of positive and negative
    Vec2q v7(-1, 2);
    Vec2q v8(1, -2);
    Vec2q result4 = max(v7, v8);
    assert(result4[0] == 1);
    assert(result4[1] == 2);

    // Test case 5: Max with maximum/minimum values
    Vec2q v9(INT64_MAX, INT64_MIN);
    Vec2q v10(0, 0);
    Vec2q result5 = max(v9, v10);
    assert(result5[0] == INT64_MAX);  // INT64_MAX vs 0
    assert(result5[1] == 0);          // INT64_MIN vs 0

    std::cout << "test_max passed!\n";
}
void test_min() {
    // Test case 1: Basic min comparison with positive numbers
    Vec2q v1(1, 2);
    Vec2q v2(4, 1);
    Vec2q result1 = min(v1, v2);
    assert(result1[0] == 1);
    assert(result1[1] == 1);

    // Test case 2: Min of equal numbers
    Vec2q v3(1, 2);
    Vec2q v4(1, 2);
    Vec2q result2 = min(v3, v4);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == i + 1);  // Should return same numbers
    }

    // Test case 3: Min with negative numbers
    Vec2q v5(-8, -7);
    Vec2q v6(-1, -2);
    Vec2q result3 = min(v5, v6);
    assert(result3[0] == -8);
    assert(result3[1] == -7);

    // Test case 4: Min with mix of positive and negative
    Vec2q v7(-1, 2);
    Vec2q v8(1, -2);
    Vec2q result4 = min(v7, v8);
    assert(result4[0] == -1);
    assert(result4[1] == -2);

    // Test case 5: Min with INT64_MAX/MIN values 
    Vec2q v9(INT64_MAX, INT64_MIN);
    Vec2q v10(0, 0);
    Vec2q result5 = min(v9, v10);
    assert(result5[0] == 0);          // INT64_MAX vs 0
    assert(result5[1] == INT64_MIN);  // INT64_MIN vs 0

    std::cout << "test_min passed!\n";
}
void test_abs() {
    // Test case 1: Basic absolute values of negative numbers
    Vec2q v1(-1, -2);
    Vec2q result1 = abs(v1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == i + 1);  // Should return positive values
    }

    // Test case 2: Absolute values of positive numbers (no change)
    Vec2q v2(1, 2);
    Vec2q result2 = abs(v2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == i + 1);  // Should return same positive values
    }

    // Test case 3: Mix of positive and negative numbers
    Vec2q v3(-1, 2);
    Vec2q result3 = abs(v3);
    assert(result3[0] == 1);
    assert(result3[1] == 2);

    // Test case 4: Zero values
    Vec2q v4(0);
    Vec2q result4 = abs(v4);
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == 0);  // Absolute value of 0 is 0
    }

    // Test case 5: Test INT64_MIN/MAX values
    Vec2q v5(INT64_MIN, INT64_MAX);
    Vec2q result5 = abs(v5);
    assert(result5[0] == INT64_MIN);  // Special case: abs(INT64_MIN) = INT64_MIN due to two's complement
    assert(result5[1] == INT64_MAX);  // abs(INT64_MAX) = INT64_MAX

    std::cout << "test_abs passed!\n";
}
void test_rotate_left() {
    // Test case 1: Basic rotate left by 1
    Vec2q v1(1, 2);
    Vec2q result1 = rotate_left(v1, 1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == (i + 1) * 2);  // Each value doubled
    }

    // Test case 2: Rotate left by 0 (no change)
    Vec2q v2(1, 2); 
    Vec2q result2 = rotate_left(v2, 0);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == i + 1);  // No change
    }

    // Test case 3: Rotate left by multiple positions
    Vec2q v3(1, 2);
    Vec2q result3 = rotate_left(v3, 2); // Multiply by 4
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == (i + 1) * 4);
    }

    // Test case 4: Test rotation with negative numbers
    Vec2q v4(-2, -1);
    Vec2q result4 = rotate_left(v4, 1);
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == (-2 + i) * 2);
    }

    // Test case 5: Test bit rotation behavior with large values
    Vec2q v5(0x4000000000000000LL, 0x2000000000000000LL);
    Vec2q result5 = rotate_left(v5, 1);
    assert(result5[0] == 0x8000000000000000LL);  // Shifted left by 1
    assert(result5[1] == 0x4000000000000000LL);  // Shifted left by 1

    // Test case 6: Large rotations
    Vec2q v6(0x1, 0x2);
    Vec2q result6 = rotate_left(v6, 60);
    int64_t expected[] = {0x1000000000000000LL, 0x2000000000000000LL};
    for(int i = 0; i < 2; i++) {
        assert(result6[i] == expected[i]);
    }

    // Test case 7: Chained rotations
    Vec2q v7(1, 1);
    Vec2q result7 = rotate_left(rotate_left(v7, 1), 2); // Left 3 total
    for(int i = 0; i < 2; i++) {
        assert(result7[i] == 8); // 1 << 3 = 8
    }

    std::cout << "test_rotate_left passed!\n";
}
void test_rotate_right() {
    // Test case 1: Basic rotate right by 1
    Vec2q v1(2, 4);
    Vec2q result1 = rotate_right(v1, 1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == (i + 1) * 2 / 2);  // Each value halved
    }

    // Test case 2: Rotate right by 0 (no change)
    Vec2q v2(1, 2);
    Vec2q result2 = rotate_right(v2, 0);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == i + 1);  // No change
    }

    // Test case 3: Rotate right by multiple positions
    Vec2q v3(16, 32);
    Vec2q result3 = rotate_right(v3, 2); // Divide by 4
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == (i * 16 + 16) / 4);
    }

    // Test case 4: Test rotation with negative numbers
    Vec2q v4(-16, -12);
    Vec2q result4 = rotate_right(v4, 1);
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == (-16 + i * 4) / 2);
    }

    // Test case 5: Test with maximum and minimum values
    Vec2q v5(INT64_MAX, INT64_MIN);
    Vec2q result5 = rotate_right(v5, 1);
    assert(result5[0] == INT64_MAX/2);    // INT64_MAX / 2
    assert(result5[1] == INT64_MIN/2);    // INT64_MIN / 2

    // Test case 6: Large rotations
    Vec2q v6(32768, 16384);
    Vec2q result6 = rotate_right(v6, 28);
    for(int i = 0; i < 2; i++) {
        assert(result6[i] == (v6[i] >> 28));  // Right shift by 28
    }

    // Test case 7: Odd numbers
    Vec2q v7(15, 11);
    Vec2q result7 = rotate_right(v7, 1);
    for(int i = 0; i < 2; i++) {
        assert(result7[i] == (15 - 4 * i) / 2);
    }

    // Test case 8: Chained rotations
    Vec2q v8(64, 64);
    Vec2q result8 = rotate_right(rotate_right(v8, 1), 2); // Right 3 total
    for(int i = 0; i < 2; i++) {
        assert(result8[i] == 8); // 64 >> 3 = 8
    }

    std::cout << "test_rotate_right passed!\n";
}

int main() 
{
    test_default_constructor();
    test_broadcast_constructor();
    test_element_constructor();
    test_int64x2t_constructor();
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