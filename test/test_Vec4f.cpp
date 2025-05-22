#include "../Vec4f.h"
#include <iostream>
#include <cassert>
#include <cfloat>
#include <cmath>
#include <cstring>
using namespace VCL_NAMESPACE;
const float EPSILON = 1e-6f;  // Define small value for float comparison
void test_default_constructor() {
    // Test case 1: constructor initializes to zero
    Vec4f v;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v[i] - 0.0f) < EPSILON);
    }
    
    //Test case 2:  multiple instances
    Vec4f v2;
    Vec4f v3;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v2[i] - 0.0f) < EPSILON);
        assert(std::abs(v3[i] - 0.0f) < EPSILON);
    }

    // Test case 3:  value changes after default construction
    Vec4f v4;
    v4 = Vec4f(1,2,3,4); 
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v4[i] - (float)(i+1)) < EPSILON);
    }

    // Test case 4: negative values after default construction
    Vec4f v5;
    v5 = Vec4f(-1,-2,-3,-4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v5[i] - (float)(-(i+1))) < EPSILON);
    }
    std::cout << "test_default_constructor passed!\n";
}
void test_broadcast_constructor() {
    // Test case 1: Broadcast zero
    Vec4f v1(0.0f);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - 0.0f) < EPSILON);
    }

    // Test case 2: Broadcast maximum value
    Vec4f v2(32767.0f);  // 0x7FFF as float
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v2[i] - 32767.0f) < EPSILON);
    }

    // Test case 3: Broadcast arbitrary value
    Vec4f v3(4660.0f);  // 0x1234 as float
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3[i] - 4660.0f) < EPSILON);
    }

    // Test case 4: Multiple instances with different values
    Vec4f v4(10922.0f);  // 0x2AAA as float
    Vec4f v5(5461.0f);   // 0x1555 as float
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v4[i] - 10922.0f) < EPSILON);
        assert(std::abs(v5[i] - 5461.0f) < EPSILON);
    }
    std::cout << "test_broadcast_constructor passed!\n";
}
void test_element_constructor() {
    // Test case 1: Ascending positive values
    Vec4f v1(1, 2, 3, 4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - (i+1)) < EPSILON);
    }

    // Test case 2: Descending positive values 
    Vec4f v2(4, 3, 2, 1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v2[i] - (4-i)) < EPSILON);
    }

    // Test case 3: Negative values
    Vec4f v3(-1, -2, -3, -4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3[i] - (-(i+1))) < EPSILON);
    }

    // Test case 4: Mixed positive and negative values
    Vec4f v4(-2, -1, 1, 2);
    float expected[] = {-2.0f, -1.0f, 1.0f, 2.0f};
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v4[i] - expected[i]) < EPSILON);
    }

    // Test case 5: All zeros
    Vec4f v5(0, 0, 0, 0);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v5[i]) < EPSILON);
    }
    std::cout << "test_element_constructor passed!\n";
}
void test_floatx4t_constructor() {
    // Test case 1: Create float32x4_t with zeros and construct Vec4f from it
    float data1[4] = {0, 0, 0, 0};
    float32x4_t x1 = vld1q_f32(data1);
    Vec4f v1(x1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - 0.0f) < EPSILON);
    }

    // Test case 2: Create float32x4_t with sequential values
    float data2[4] = {1, 2, 3, 4}; 
    float32x4_t x2 = vld1q_f32(data2);
    Vec4f v2(x2);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v2[i] - (i + 1.0f)) < EPSILON);
    }

    // Test case 3: Create float32x4_t with maximum float values
    float data3[4] = {FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX};
    float32x4_t x3 = vld1q_f32(data3);
    Vec4f v3(x3);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3[i] - FLT_MAX) < EPSILON);
    }

    // Test case 4: Create float32x4_t with mixed values
    float data4[4] = {1.234f, -5.678f, 0.0f, 9.876f};
    float32x4_t x4 = vld1q_f32(data4);
    Vec4f v4(x4);
    assert(std::abs(v4[0] - 1.234f) < EPSILON);
    assert(std::abs(v4[1] - (-5.678f)) < EPSILON);
    assert(std::abs(v4[2] - 0.0f) < EPSILON);
    assert(std::abs(v4[3] - 9.876f) < EPSILON);

    std::cout << "test_floatx4t_constructor passed!\n";
}
void test_copy_constructor() {
    // Test case 1: Copy basic values
    Vec4f original1(1, 2, 3, 4);
    Vec4f copy1(original1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(copy1[i] - original1[i]) < EPSILON);
    }

    // Test case 2: Copy zeros
    Vec4f original2(0);
    Vec4f copy2(original2);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(copy2[i]) < EPSILON);
    }

    // Test case 3: Copy negative values 
    Vec4f original3(-1, -2, -3, -4);
    Vec4f copy3(original3);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(copy3[i] - original3[i]) < EPSILON);
    }

    // Test case 4: Copy min/max values
    Vec4f original4(FLT_MIN, -1.0f, FLT_MAX, -FLT_MAX);
    Vec4f copy4(original4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(copy4[i] - original4[i]) < EPSILON);
    }

    // Test case 5: Modify copy should not affect original
    Vec4f original5(1, 2, 3, 4);
    Vec4f copy5(original5);
    copy5 = Vec4f(-1, -2, -3, -4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(original5[i] - (i+1)) < EPSILON);
        assert(std::abs(copy5[i] - (-(i+1))) < EPSILON);
    }
    std::cout << "test_copy_constructor passed!\n";
}
void test_assignment_operator() {
    // Test case 1: Assign basic values from float32x4_t
    float data1[4] = {1, 2, 3, 4};
    float32x4_t raw1 = vld1q_f32(data1);
    Vec4f v1;
    v1 = raw1;
    for(int i = 0; i < 4; i++) {
        assert(v1[i] == data1[i]);
    }

    // Test case 2: Assign zeros
    float data2[4] = {0};
    float32x4_t raw2 = vld1q_f32(data2);
    Vec4f v2;
    v2 = raw2;
    for(int i = 0; i < 4; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: Assign negative values
    float data3[4] = {-1, -2, -3, -4};
    float32x4_t raw3 = vld1q_f32(data3);
    Vec4f v3;
    v3 = raw3;
    for(int i = 0; i < 4; i++) {
        assert(v3[i] == data3[i]);
    }

    // Test case 4: Assign min/max values 
    float data4[4] = {FLT_MIN, -1, 0, FLT_MAX};
    float32x4_t raw4 = vld1q_f32(data4);
    Vec4f v4;
    v4 = raw4;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v4[i] - data4[i]) < EPSILON);
    }

    // Test case 5: Chain assignments
    float data5[4] = {10, 20, 30, 40};
    float32x4_t raw5 = vld1q_f32(data5);
    Vec4f v5, v6;
    v6 = v5 = raw5;
    for(int i = 0; i < 4; i++) {
        assert(v5[i] == data5[i]);
        assert(v6[i] == data5[i]);
    }
    std::cout << "test_assignment_operator passed!\n";
}
void test_type_cast_operator() {
    // Test case 1: Convert basic values to float32x4_t
    Vec4f v1(1, 2, 3, 4);
    float32x4_t raw1 = v1;
    float data1[4];
    vst1q_f32(data1, raw1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data1[i] - (i+1)) < EPSILON);
    }

    // Test case 2: Convert zeros to float32x4_t
    Vec4f v2(0);
    float32x4_t raw2 = v2;
    float data2[4];
    vst1q_f32(data2, raw2);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data2[i]) < EPSILON);
    }

    // Test case 3: Convert negative values to float32x4_t
    Vec4f v3(-1, -2, -3, -4);
    float32x4_t raw3 = v3;
    float data3[4];
    vst1q_f32(data3, raw3);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data3[i] - (-(i+1))) < EPSILON);
    }

    // Test case 4: Convert min/max values to float32x4_t
    Vec4f v4(FLT_MIN, -1.0f, 0.0f, FLT_MAX);
    float32x4_t raw4 = v4;
    float data4[4];
    vst1q_f32(data4, raw4);
    float expected4[] = {FLT_MIN, -1.0f, 0.0f, FLT_MAX};
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data4[i] - expected4[i]) < EPSILON);
    }

    // Test case 5: Convert alternating values to float32x4_t
    Vec4f v5(-100, 100, -200, 200);
    float32x4_t raw5 = v5;
    float data5[4];
    vst1q_f32(data5, raw5);
    float expected5[] = {-100, 100, -200, 200};
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data5[i] - expected5[i]) < EPSILON);
    }
    std::cout << "test_type_cast_operator passed!\n";
}

void test_load() {
    // Test case 1: Load basic values
    alignas(16) float data1[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    Vec4f v1;
    v1.load(data1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - data1[i]) < EPSILON);
    }

    // Test case 2: Load zeros 
    alignas(16) float data2[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    Vec4f v2;
    v2.load(data2);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v2[i]) < EPSILON);
    }

    // Test case 3: Load negative values
    alignas(16) float data3[4] = {-1.0f, -2.0f, -3.0f, -4.0f};
    Vec4f v3;
    v3.load(data3);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3[i] - data3[i]) < EPSILON);
    }

    // Test case 4: Load min/max values
    alignas(16) float data4[4] = {FLT_MIN, -1.0f, 0.0f, FLT_MAX};
    Vec4f v4;
    v4.load(data4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v4[i] - data4[i]) < EPSILON);
    }

    // Test case 5: Load values then modify array
    alignas(16) float data5[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    Vec4f v5;
    v5.load(data5);
    data5[0] = 100.0f; // Modify original array
    assert(std::abs(v5[0] - 1.0f) < EPSILON); // Vector should keep original value
    std::cout << "test_load passed!\n";
}
void test_load_a() {
    // Test case 1: Load aligned basic values
    alignas(16) float data1[4] = {1, 2, 3, 4};
    Vec4f v1;
    v1.load_a(data1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - data1[i]) < EPSILON);
    }

    // Test case 2: Load aligned zeros
    alignas(16) float data2[4] = {0};
    Vec4f v2;
    v2.load_a(data2);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v2[i]) < EPSILON);
    }

    // Test case 3: Load aligned negative values
    alignas(16) float data3[4] = {-1, -2, -3, -4};
    Vec4f v3;
    v3.load_a(data3);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3[i] - data3[i]) < EPSILON);
    }

    // Test case 4: Load aligned min/max values
    alignas(16) float data4[4] = {FLT_MIN, -1, 0, FLT_MAX};
    Vec4f v4;
    v4.load_a(data4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v4[i] - data4[i]) < EPSILON);
    }

    // Test case 5: Load aligned values then modify array
    alignas(16) float data5[4] = {1, 2, 3, 4};
    Vec4f v5;
    v5.load_a(data5);
    data5[0] = 100; // Modify original array
    assert(std::abs(v5[0] - 1.0f) < EPSILON); // Vector should keep original value
    std::cout << "test_load_a passed!\n";
}
void test_store() {
    // Test case 1: Store basic values
     float data1[4];
    Vec4f v1(1, 2, 3, 4);
    v1.store(data1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data1[i] - (i+1)) < EPSILON);
    }

    // Test case 2: Store zeros
    float data2[4];
    Vec4f v2(0);
    v2.store(data2);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data2[i]) < EPSILON);
    }

    // Test case 3: Store negative values
    float data3[4];
    Vec4f v3(-1, -2, -3, -4);
    v3.store(data3);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data3[i] - (-(i+1))) < EPSILON);
    }

    // Test case 4: Store min/max values
    float data4[4];
    Vec4f v4(FLT_MIN, -1, 0, FLT_MAX);
    v4.store(data4);
    float expected4[] = {FLT_MIN, -1, 0, FLT_MAX};
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data4[i] - expected4[i]) < EPSILON);
    }

    // Test case 5: Store multiple times to same array
    float data5[4];
    Vec4f v5(1, 2, 3, 4);
    v5.store(data5);
    Vec4f v6(-1, -2, -3, -4);
    v6.store(data5); // Overwrite previous values
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data5[i] - (-(i+1))) < EPSILON);
    }
    std::cout << "test_store passed!\n";
}
void test_store_a() {
    // Test case 1: Store aligned basic values
    alignas(16) float data1[4];
    Vec4f v1(1, 2, 3, 4);
    v1.store_a(data1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data1[i] - (i+1)) < EPSILON);
    }

    // Test case 2: Store aligned zeros
    alignas(16) float data2[4];
    Vec4f v2(0);
    v2.store_a(data2);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data2[i]) < EPSILON);
    }

    // Test case 3: Store aligned negative values
    alignas(16) float data3[4];
    Vec4f v3(-1, -2, -3, -4);
    v3.store_a(data3);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data3[i] - (-(i+1))) < EPSILON);
    }

    // Test case 4: Store aligned min/max values
    alignas(16) float data4[4];
    Vec4f v4(FLT_MIN, -1, 0, FLT_MAX);
    v4.store_a(data4);
    float expected4[] = {FLT_MIN, -1, 0, FLT_MAX};
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data4[i] - expected4[i]) < EPSILON);
    }

    // Test case 5: Store aligned multiple times to same array
    alignas(16) float data5[4];
    Vec4f v5(1, 2, 3, 4);
    v5.store_a(data5);
    Vec4f v6(-1, -2, -3, -4);
    v6.store_a(data5); // Overwrite previous values
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data5[i] - (-(i+1))) < EPSILON);
    }
    std::cout << "test_store_a passed!\n";
}
void test_load_partial() {
    // Test case 1: Load partial with n = 0 (should set all elements to 0)
    float data1[4] = {1, 2, 3, 4};
    Vec4f v1;
    v1.load_partial(0, data1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i]) < EPSILON);
    }

    // Test case 2: Load partial with n = 2 (should load first 2 elements and set rest to 0)
    float data2[4] = {1, 2, 3, 4};
    Vec4f v2;
    v2.load_partial(2, data2);
    for(int i = 0; i < 2; i++) {
        assert(std::abs(v2[i] - data2[i]) < EPSILON);
    }
    for(int i = 2; i < 4; i++) {
        assert(std::abs(v2[i]) < EPSILON);
    }

    // Test case 3: Load partial with n = 4 (should load all elements)
    float data3[4] = {1, 2, 3, 4};
    Vec4f v3;
    v3.load_partial(4, data3);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3[i] - data3[i]) < EPSILON);
    }

    // Test case 4: Load partial with n = -1 (should set all elements to 0)
    float data4[4] = {1, 2, 3, 4};
    Vec4f v4;
    v4.load_partial(-1, data4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v4[i]) < EPSILON);
    }

    // Test case 5: Load partial with n = 3 with negative values
    float data5[4] = {-1, -2, -3, -4};
    Vec4f v5;
    v5.load_partial(3, data5);
    for(int i = 0; i < 3; i++) {
        assert(std::abs(v5[i] - data5[i]) < EPSILON);
    }
    for(int i = 3; i < 4; i++) {
        assert(std::abs(v5[i]) < EPSILON);
    }

    std::cout << "test_load_partial passed!\n";
}
void test_store_partial() {
    // Test case 1: Store partial with n = 0 (should store nothing)
    float data1[4] = {0};
    Vec4f v1(1, 2, 3, 4);
    v1.store_partial(0, data1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data1[i]) < EPSILON);
    }

    // Test case 2: Store partial with n = 2 (should store first 2 elements)
    float data2[4] = {0};
    Vec4f v2(1, 2, 3, 4);
    v2.store_partial(2, data2);
    for(int i = 0; i < 2; i++) {
        assert(std::abs(data2[i] - (i+1)) < EPSILON);
    }
    for(int i = 2; i < 4; i++) {
        assert(std::abs(data2[i]) < EPSILON);
    }

    // Test case 3: Store partial with n = 4 (should store all elements)
    float data3[4] = {0};
    Vec4f v3(1, 2, 3, 4);
    v3.store_partial(4, data3);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data3[i] - (i+1)) < EPSILON);
    }

    // Test case 4: Store partial with n > 4 (should store only 4 elements)
    float data4[6] = {0};
    Vec4f v4(1, 2, 3, 4);
    v4.store_partial(6, data4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(data4[i] - (i+1)) < EPSILON);
    }
    for(int i = 4; i < 6; i++) {
        assert(std::abs(data4[i]) < EPSILON);
    }

    // Test case 5: Store partial with negative values
    float data5[4] = {0};
    Vec4f v5(-1, -2, -3, -4);
    v5.store_partial(2, data5);
    for(int i = 0; i < 2; i++) {
        assert(std::abs(data5[i] - (-(i+1))) < EPSILON);
    }
    for(int i = 2; i < 4; i++) {
        assert(std::abs(data5[i]) < EPSILON);
    }

    std::cout << "test_store_partial passed!\n";
}
void test_cutoff() {
    // Test case 1: n = 0 (should set all elements to 0)
    Vec4f v1(1, 2, 3, 4);
    v1.cutoff(0);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i]) < EPSILON);
    }

    // Test case 2: n = 2 (should keep first 2 elements, set rest to 0)
    Vec4f v2(1, 2, 3, 4);
    v2.cutoff(2);
    for(int i = 0; i < 2; i++) {
        assert(std::abs(v2[i] - (i+1)) < EPSILON);
    }
    for(int i = 2; i < 4; i++) {
        assert(std::abs(v2[i]) < EPSILON);
    }

    // Test case 3: n = 4 (should keep all elements)
    Vec4f v3(1, 2, 3, 4);
    v3.cutoff(4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3[i] - (i+1)) < EPSILON);
    }

    // Test case 4: n > 4 (should keep all elements)
    Vec4f v4(1, 2, 3, 4);
    v4.cutoff(6);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v4[i] - (i+1)) < EPSILON);
    }

    // Test case 5: n = 3 with negative values
    Vec4f v5(-1, -2, -3, -4);
    v5.cutoff(3);
    for(int i = 0; i < 3; i++) {
        assert(std::abs(v5[i] - (-(i+1))) < EPSILON);
    }
    assert(std::abs(v5[3]) < EPSILON);

    // Test case 6: chain operation test
    Vec4f v6(1, 2, 3, 4);
    v6.cutoff(3).cutoff(2);
    for(int i = 0; i < 2; i++) {
        assert(std::abs(v6[i] - (i+1)) < EPSILON);
    }
    for(int i = 2; i < 4; i++) {
        assert(std::abs(v6[i]) < EPSILON);
    }

    std::cout << "test_cutoff passed!\n";
}
void test_and_assign_operator() {
    // Test case 1: AND with all 1s (should keep original values)
    Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    uint32_t ones = 0xFFFFFFFF;
    float32x4_t all_ones = vreinterpretq_f32_u32(vdupq_n_u32(ones));
    v1 &= Vec4f(all_ones);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - (float)(i+1)) < EPSILON);
    }

    // Test case 2: AND with all 0s (should set all to 0)
    Vec4f v2(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f all_zeros(0.0f);
    v2 &= all_zeros;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v2[i]) < EPSILON);
    }

    // Test case 3: Test bitwise AND with specific bit patterns
    float pattern1 = 3.14159f;  // Arbitrary float value
    float pattern2 = 2.71828f;  // Another arbitrary float value
    Vec4f v3(pattern1);
    Vec4f v4(pattern2);
    v3 &= v4;
    
    // Convert to integer representation for bitwise comparison
    uint32_t expected = *(uint32_t*)&pattern1 & *(uint32_t*)&pattern2;
    float expected_float = *(float*)&expected;
    
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3[i] - expected_float) < EPSILON);
    }

    // Test case 4: Self AND operation
    Vec4f v5(1.0f, 2.0f, 3.0f, 4.0f);
    v5 &= v5;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v5[i] - (float)(i+1)) < EPSILON);
    }

    // Test case 5: AND with bit patterns
    Vec4f v6;
    uint32_t val = 0x55555555;
    v6 = Vec4f(*(float*)&val);
    Vec4f special;
    uint32_t vals[4] = {0xAAAAAAAA, 0x33333333, 0xF0F0F0F0, 0x00FF00FF};
    special.load((float*)vals);
    v6 &= special;
    
    for(int i = 0; i < 4; i++) {
        expected = 0x55555555 & vals[i];
        float temp = v6[i];
        assert(*(uint32_t*)&temp == expected);
    }

    std::cout << "test_and_assign_operator passed!\n";
}
void test_insert() {
    // Test case 1: Insert at beginning
    Vec4f v1(1, 2, 3, 4);
    v1.insert(0, 100);
    assert(std::abs(v1[0] - 100.0f) < EPSILON);
    for(int i = 1; i < 4; i++) {
        assert(std::abs(v1[i] - (i+1)) < EPSILON);
    }

    // Test case 2: Insert at end
    Vec4f v2(1, 2, 3, 4);
    v2.insert(3, 100);
    for(int i = 0; i < 3; i++) {
        assert(std::abs(v2[i] - (i+1)) < EPSILON);
    }
    assert(std::abs(v2[3] - 100.0f) < EPSILON);

    // Test case 3: Insert in middle
    Vec4f v3(1, 2, 3, 4);
    v3.insert(2, 100);
    for(int i = 0; i < 2; i++) {
        assert(std::abs(v3[i] - (i+1)) < EPSILON);
    }
    assert(std::abs(v3[2] - 100.0f) < EPSILON);
    assert(std::abs(v3[3] - 4.0f) < EPSILON);

    // Test case 4: Insert negative value
    Vec4f v4(1, 2, 3, 4);
    v4.insert(1, -100);
    assert(std::abs(v4[0] - 1.0f) < EPSILON);
    assert(std::abs(v4[1] - (-100.0f)) < EPSILON);
    assert(std::abs(v4[2] - 3.0f) < EPSILON);
    assert(std::abs(v4[3] - 4.0f) < EPSILON);

    // Test case 5: Test index wrapping (index & 0x03)
    Vec4f v5(1, 2, 3, 4);
    v5.insert(4, 100);  // 4 & 0x03 = 0
    assert(std::abs(v5[0] - 100.0f) < EPSILON);
    for(int i = 1; i < 4; i++) {
        assert(std::abs(v5[i] - (i+1)) < EPSILON);
    }

    // Test case 6: Multiple inserts
    Vec4f v6(1, 2, 3, 4);
    v6.insert(0, 100);
    v6.insert(1, 200); 
    v6.insert(2, 300);
    assert(std::abs(v6[0] - 100.0f) < EPSILON);
    assert(std::abs(v6[1] - 200.0f) < EPSILON);
    assert(std::abs(v6[2] - 300.0f) < EPSILON);
    assert(std::abs(v6[3] - 4.0f) < EPSILON);

    std::cout << "test_insert passed!\n";
}
void test_extract() {
    // Test case 1: Extract elements in order
    Vec4f v1(1, 2, 3, 4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1.extract(i) - (i+1)) < EPSILON);
    }

    // Test case 2: Extract from vector of zeros
    Vec4f v2(0);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v2.extract(i)) < EPSILON);
    }

    // Test case 3: Extract from vector with negative values
    Vec4f v3(-1, -2, -3, -4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3.extract(i) - (-(i+1))) < EPSILON);
    }

    // Test case 4: Test index wrapping (index & 0x03)
    Vec4f v4(1, 2, 3, 4);
    assert(std::abs(v4.extract(4) - 1) < EPSILON);  // 4 & 0x03 = 0
    assert(std::abs(v4.extract(5) - 2) < EPSILON);  // 5 & 0x03 = 1
    assert(std::abs(v4.extract(7) - 4) < EPSILON);  // 7 & 0x03 = 3

    // Test case 5: Extract from vector with min/max values
    Vec4f v5(INT32_MIN, -1, 0, INT32_MAX);
    assert(std::abs(v5.extract(0) - INT32_MIN) < EPSILON);
    assert(std::abs(v5.extract(1) - (-1)) < EPSILON);
    assert(std::abs(v5.extract(2)) < EPSILON);
    assert(std::abs(v5.extract(3) - INT32_MAX) < EPSILON);

    std::cout << "test_extract passed!\n";
}
void test_array_subscript_operator() {
    // Test case 1: Access elements in order
    Vec4f v1(1, 2, 3, 4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - (i+1)) < EPSILON);
    }

    // Test case 2: Access from vector of zeros
    Vec4f v2(0);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v2[i]) < EPSILON);
    }

    // Test case 3: Access from vector with negative values
    Vec4f v3(-1, -2, -3, -4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3[i] - (-(i+1))) < EPSILON);
    }

    // Test case 4: Test index wrapping (index & 0x03)
    Vec4f v4(1, 2, 3, 4);
    assert(std::abs(v4[4] - 1) < EPSILON);  // 4 & 0x03 = 0
    assert(std::abs(v4[5] - 2) < EPSILON);  // 5 & 0x03 = 1
    assert(std::abs(v4[7] - 4) < EPSILON);  // 7 & 0x03 = 3

    // Test case 5: Access from vector with FLT_MAX/MIN values
    Vec4f v5(FLT_MIN, -1, 0, FLT_MAX);
    assert(std::abs(v5[0] - FLT_MIN) < EPSILON);
    assert(std::abs(v5[1] - (-1)) < EPSILON);
    assert(std::abs(v5[2]) < EPSILON);
    assert(std::abs(v5[3] - FLT_MAX) < EPSILON);

    std::cout << "test_array_subscript_operator passed!\n";
}

void test_add_operator() {
    // Test case 1: Basic addition
    Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v2(1.0f, 1.0f, 1.0f, 1.0f);
    Vec4f result1 = v1 + v2;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result1[i] - (i + 2.0f)) < EPSILON);
    }

    // Test case 2: Adding zeros (identity operation)
    Vec4f v3(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f zeros(0.0f);
    Vec4f result2 = v3 + zeros;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result2[i] - v3[i]) < EPSILON);
    }

    // Test case 3: Adding negative numbers
    Vec4f v4(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v5(-1.0f, -2.0f, -3.0f, -4.0f);
    Vec4f result3 = v4 + v5;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result3[i]) < EPSILON);
    }

    // Test case 4: Testing saturation (overflow protection)
    Vec4f v6(FLT_MAX, FLT_MAX, 1.0f, 0.0f);
    Vec4f v7(1.0f, FLT_MAX, FLT_MAX, 0.0f);
    Vec4f result4 = v6 + v7;
    assert(std::abs(result4[0] - FLT_MAX) < EPSILON);  // Saturated addition
    assert(std::abs(std::isinf(result4[1])));  // Saturated addition
    assert(std::abs(result4[2] - FLT_MAX) < EPSILON);  // Saturated addition
    assert(std::abs(result4[3]) < EPSILON);            // Normal addition

    // Test case 5: Chained additions
    Vec4f v8(1.0f, 1.0f, 1.0f, 1.0f);
    Vec4f result5 = v8 + v8 + v8;  // Should be (3,3,3,3)
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result5[i] - 3.0f) < EPSILON);
    }

    std::cout << "test_add_operator passed!\n";
}
void test_add_assign_operator() {
    // Test case 1: Basic addition assignment
    Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v2(1.0f, 1.0f, 1.0f, 1.0f);
    v1 += v2;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - (float)(i + 2)) < EPSILON);
    }

    // Test case 2: Adding zeros (identity operation)
    Vec4f v3(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f zeros(0.0f);
    v3 += zeros;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3[i] - (float)(i + 1)) < EPSILON);
    }

    // Test case 3: Adding negative numbers 
    Vec4f v4(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v5(-1.0f, -2.0f, -3.0f, -4.0f);
    v4 += v5;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v4[i]) < EPSILON);
    }

    // Test case 4: Testing saturation (overflow protection)
    Vec4f v6(FLT_MAX, FLT_MAX, 1.0f, 0.0f);
    Vec4f v7(1.0f, FLT_MAX, FLT_MAX, 0.0f);
    v6 += v7;
    assert(std::abs(v6[0] - FLT_MAX) < EPSILON);  // Saturated addition
    assert(std::isinf(v6[1]));  // Saturated addition 
    assert(std::abs(v6[2] - FLT_MAX) < EPSILON);  // Saturated addition
    assert(std::abs(v6[3]) < EPSILON);     // Normal addition

    // Test case 5: Chained additions
    Vec4f v8(1.0f, 1.0f, 1.0f, 1.0f);
    Vec4f v9(1.0f, 1.0f, 1.0f, 1.0f);
    v8 += v9 += v9;  // v9 becomes (2,2,2,2), then v8 becomes (3,3,3,3)
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v8[i] - 3.0f) < EPSILON);
        assert(std::abs(v9[i] - 2.0f) < EPSILON);
    }

    std::cout << "test_add_assign_operator passed!\n";
}
void test_postfix_increment_operator() {
    // Test case 1: Basic increment
    Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f result1 = v1++;
    // Check that result holds original values
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result1[i] - (float)(i + 1)) < EPSILON);
    }
    // Check that original vector was incremented
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - (float)(i + 2)) < EPSILON);
    }

    // Test case 2: Increment zeros
    Vec4f v2(0.0f);
    Vec4f result2 = v2++;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result2[i]) < EPSILON);
        assert(std::abs(v2[i] - 1.0f) < EPSILON);
    }

    // Test case 3: Increment negative values
    Vec4f v3(-4.0f, -3.0f, -2.0f, -1.0f);
    Vec4f result3 = v3++;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result3[i] - (float)(-4 + i)) < EPSILON);
        assert(std::abs(v3[i] - (float)(-3 + i)) < EPSILON);
    }

    // Test case 4: Test saturation at maximum value
    Vec4f v4(FLT_MAX, FLT_MAX-1.0f, FLT_MAX-2.0f, 0.0f);
    Vec4f result4 = v4++;
    assert(std::abs(result4[0] - FLT_MAX) < EPSILON);
    assert(std::abs(result4[1] - (FLT_MAX-1.0f)) < EPSILON);
    assert(std::abs(result4[2] - (FLT_MAX-2.0f)) < EPSILON);
    assert(std::abs(result4[3]) < EPSILON);
    
    assert(std::abs(v4[0] - FLT_MAX) < EPSILON);     // Saturated
    assert(std::abs(v4[1] - FLT_MAX) < EPSILON);     // Saturated
    assert(std::abs(v4[2] - (FLT_MAX-1.0f)) < EPSILON);
    assert(std::abs(v4[3] - 1.0f) < EPSILON);

    // Test case 5: Multiple increments
    Vec4f v5(1.0f);
    Vec4f result5 = v5++;
    result5 = v5++;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result5[i] - 2.0f) < EPSILON);
        assert(std::abs(v5[i] - 3.0f) < EPSILON);
    }

    std::cout << "test_postfix_increment_operator passed!\n";
}
void test_prefix_increment_operator() {
    // Test case 1: Basic increment
    Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f& result1 = ++v1;
    // Check incremented values
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - (float)(i + 2)) < EPSILON);
    }
    // Check that result references the incremented vector
    assert(&result1 == &v1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result1[i] - (float)(i + 2)) < EPSILON);
    }

    // Test case 2: Increment zeros
    Vec4f v2(0.0f);
    Vec4f& result2 = ++v2;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v2[i] - 1.0f) < EPSILON);
        assert(std::abs(result2[i] - 1.0f) < EPSILON);
    }
    assert(&result2 == &v2);

    // Test case 3: Increment negative values
    Vec4f v3(-4.0f, -3.0f, -2.0f, -1.0f);
    Vec4f& result3 = ++v3;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3[i] - (float)(-3 + i)) < EPSILON);
        assert(std::abs(result3[i] - (float)(-3 + i)) < EPSILON);
    }
    assert(&result3 == &v3);

    // Test case 4: Test saturation at maximum value
    Vec4f v4(FLT_MAX, FLT_MAX-1.0f, FLT_MAX-2.0f, 0.0f);
    Vec4f& result4 = ++v4;
    assert(std::abs(v4[0] - FLT_MAX) < EPSILON);     // Saturated
    assert(std::abs(v4[1] - FLT_MAX) < EPSILON);     // Saturated
    assert(std::abs(v4[2] - (FLT_MAX-1.0f)) < EPSILON);
    assert(std::abs(v4[3] - 1.0f) < EPSILON);
    
    // Check reference
    assert(&result4 == &v4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result4[i] - v4[i]) < EPSILON);
    }

    // Test case 5: Multiple increments
    Vec4f v5(1.0f, 1.0f, 1.0f, 1.0f);
    Vec4f& result5 = ++v5;
    ++v5;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v5[i] - 3.0f) < EPSILON);
        assert(std::abs(result5[i] - 3.0f) < EPSILON);
    }
    assert(&result5 == &v5);

    std::cout << "test_prefix_increment_operator passed!\n";
}

void test_subtract_operator() {
    // Test case 1: Basic subtraction
    Vec4f v1(2, 3, 4, 5);
    Vec4f v2(1, 1, 1, 1);
    Vec4f result1 = v1 - v2;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result1[i] - (float)(i + 1)) < EPSILON);
    }

    // Test case 2: Subtracting zeros (identity operation)
    Vec4f v3(1, 2, 3, 4);
    Vec4f zeros(0);
    Vec4f result2 = v3 - zeros;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result2[i] - v3[i]) < EPSILON);
    }

    // Test case 3: Subtracting from zeros
    Vec4f v4(1, 2, 3, 4);
    Vec4f result3 = zeros - v4;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result3[i] - (-(float)(i + 1))) < EPSILON);
    }

    // Test case 4: Testing saturation (underflow protection)
    Vec4f v5(-FLT_MAX, -FLT_MAX/2, 0.0f, 1.0f);
    Vec4f v6(1.0f, FLT_MAX, 0.0f, -1.0f); 
    Vec4f result4 = v5 - v6;
    assert(std::abs(result4[0] - (-FLT_MAX)) < EPSILON);  // Saturated subtraction
    assert(std::isinf(result4[1]));  // Saturated subtraction  
    assert(std::abs(result4[2]) < EPSILON);               // Normal subtraction
    assert(std::abs(result4[3] - 2.0f) < EPSILON);        // Normal subtraction

    // Test case 5: Chained subtractions
    Vec4f v7(9.0f, 9.0f, 9.0f, 9.0f);
    Vec4f v8(3.0f, 3.0f, 3.0f, 3.0f);
    Vec4f result5 = v7 - v8 - v8;  // Should be (3,3,3,3)
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result5[i] - 3.0f) < EPSILON);
    }

    std::cout << "test_subtract_operator passed!\n";
}
void test_unary_minus_operator() {
    // Test case 1: Negate positive values
    Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f result1 = -v1;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result1[i] - (-(float)(i + 1))) < EPSILON);
    }

    // Test case 2: Negate zero
    Vec4f v2(0.0f);
    Vec4f result2 = -v2;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result2[i]) < EPSILON);
    }

    // Test case 3: Negate negative values
    Vec4f v3(-1.0f, -2.0f, -3.0f, -4.0f);
    Vec4f result3 = -v3;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result3[i] - (float)(i + 1)) < EPSILON);
    }

    // Test case 4: Test with minimum/maximum values
    Vec4f v4(-FLT_MAX, FLT_MAX, -1.0f, 1.0f);
    Vec4f result4 = -v4;
    assert(std::abs(result4[0] - FLT_MAX) < EPSILON);
    assert(std::abs(result4[1] + FLT_MAX) < EPSILON);
    assert(std::abs(result4[2] - 1.0f) < EPSILON);
    assert(std::abs(result4[3] - (-1.0f)) < EPSILON);

    // Test case 5: Double negation should return to original value
    Vec4f v5(1.0f, -2.0f, 3.0f, -4.0f);
    Vec4f result5 = -(-v5);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result5[i] - v5[i]) < EPSILON);
    }

    std::cout << "test_unary_minus_operator passed!\n";
}
void test_subtract_assign_operator() {
    // Test case 1: Basic subtraction assignment
    Vec4f v1(2.0f, 3.0f, 4.0f, 5.0f);
    Vec4f v2(1.0f, 1.0f, 1.0f, 1.0f);
    v1 -= v2;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - (float)(i + 1)) < EPSILON);
    }

    // Test case 2: Subtracting zeros (identity operation)
    Vec4f v3(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f zeros(0.0f);
    v3 -= zeros;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3[i] - (float)(i + 1)) < EPSILON);
    }

    // Test case 3: Subtracting to get zeros
    Vec4f v4(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v5(1.0f, 2.0f, 3.0f, 4.0f);
    v4 -= v5;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v4[i]) < EPSILON);
    }

    // Test case 4: Testing saturation (underflow protection)
    Vec4f v6(-FLT_MAX, -FLT_MAX/2, 0.0f, 1.0f);
    Vec4f v7(1.0f, FLT_MAX, 0.0f, -1.0f);
    v6 -= v7;
    assert(std::abs(v6[0] - (-FLT_MAX)) < EPSILON);  // Saturated subtraction
    assert(std::isinf(v6[1]));  // Saturated subtraction
    assert(std::abs(v6[2]) < EPSILON);               // Normal subtraction
    assert(std::abs(v6[3] - 2.0f) < EPSILON);        // Normal subtraction

    // Test case 5: Chained subtractions
    Vec4f v8(9.0f, 9.0f, 9.0f, 9.0f);
    Vec4f v9(3.0f, 3.0f, 3.0f, 3.0f);
    v8 -= v9 -= v9;  // v9 becomes (0,0,0,0), then v8 becomes (9,9,9,9)
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v8[i] - 9.0f) < EPSILON);
        assert(std::abs(v9[i]) < EPSILON);
    }

    std::cout << "test_subtract_assign_operator passed!\n";
}
void test_postfix_decrement_operator() {
    // Test case 1: Basic decrement
    Vec4f v1(2, 3, 4, 5);
    Vec4f result1 = v1--;
    // Check that result holds original values
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result1[i] - (i + 2.0f)) < EPSILON);
    }
    // Check that original vector was decremented
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - (i + 1.0f)) < EPSILON);
    }

    // Test case 2: Decrement zeros
    Vec4f v2(0);
    Vec4f result2 = v2--;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result2[i]) < EPSILON);
        assert(std::abs(v2[i] - (-1.0f)) < EPSILON);
    }

    // Test case 3: Decrement positive values to negative
    Vec4f v3(8, 7, 6, 5);
    Vec4f result3 = v3--;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result3[i] - (8.0f - i)) < EPSILON);
        assert(std::abs(v3[i] - (7.0f - i)) < EPSILON);
    }

    // Test case 4: Test saturation at negative maximum magnitude
    Vec4f v4(-FLT_MAX, -FLT_MAX, -FLT_MAX+1, 0);
    Vec4f result4 = v4--;
    assert(std::abs(result4[0] - (-FLT_MAX)) < EPSILON);
    assert(std::abs(result4[1] - (-FLT_MAX)) < EPSILON); 
    assert(std::abs(result4[2] - (-FLT_MAX+1)) < EPSILON);
    assert(std::abs(result4[3]) < EPSILON);
    
    assert(std::abs(v4[0] - (-FLT_MAX)) < EPSILON);     // Saturated
    assert(std::abs(v4[1] - (-FLT_MAX)) < EPSILON);     // Saturated
    assert(std::abs(v4[2] - (-FLT_MAX)) < EPSILON);     
    assert(std::abs(v4[3] - (-1.0f)) < EPSILON);

    // Test case 5: Multiple decrements
    Vec4f v5(3, 3, 3, 3);
    Vec4f result5 = v5--;
    result5 = v5--;
    for(int i = 0; i < 4; i++) {
        assert(result5[i] == 2);
        assert(v5[i] == 1);
    }

    std::cout << "test_postfix_decrement_operator passed!\n";
}
void test_prefix_decrement_operator() {
    // Test case 1: Basic decrement
    Vec4f v1(2, 3, 4, 5);
    Vec4f& result1 = --v1;
    // Check decremented values
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - (float)(i + 1)) < EPSILON);
    }
    // Check that result references the decremented vector
    assert(&result1 == &v1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result1[i] - (float)(i + 1)) < EPSILON);
    }

    // Test case 2: Decrement zeros
    Vec4f v2(0);
    Vec4f& result2 = --v2;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v2[i] - (-1.0f)) < EPSILON);
        assert(std::abs(result2[i] - (-1.0f)) < EPSILON);
    }
    assert(&result2 == &v2);

    // Test case 3: Decrement positive values to negative
    Vec4f v3(8, 7, 6, 5);
    Vec4f& result3 = --v3;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3[i] - (float)(7 - i)) < EPSILON);
        assert(std::abs(result3[i] - (float)(7 - i)) < EPSILON);
    }
    assert(&result3 == &v3);

    // Test case 4: Test saturation at minimum value
    Vec4f v4(-FLT_MAX, -FLT_MAX, FLT_MAX, FLT_MAX-1);
    Vec4f& result4 = --v4;
    assert(std::abs(v4[0] + FLT_MAX) < EPSILON);     // Saturated
    assert(std::abs(v4[1] + FLT_MAX) < EPSILON);     // Saturated
    assert(std::abs(v4[2] - (FLT_MAX-1)) < EPSILON);   // Normal decrement
    assert(std::abs(v4[3] - (FLT_MAX-2)) < EPSILON);   // Normal decrement
    
    // Check reference
    assert(&result4 == &v4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result4[i] - v4[i]) < EPSILON);
    }

    // Test case 5: Multiple decrements
    Vec4f v5(3, 3, 3, 3);
    Vec4f& result5 = --v5;
    --v5;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v5[i] - 1.0f) < EPSILON);
        assert(std::abs(result5[i] - 1.0f) < EPSILON);
    }
    assert(&result5 == &v5);

    std::cout << "test_prefix_decrement_operator passed!\n";
}

void test_multiply_operator() {
    // Test case 1: Basic multiplication
    Vec4f v1(1, 2, 3, 4);
    Vec4f v2(2, 2, 2, 2);
    Vec4f result1 = v1 * v2;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result1[i] - 2.0f * (i + 1)) < EPSILON);
    }

    // Test case 2: Multiply by zero
    Vec4f v3(1, 2, 3, 4);
    Vec4f zeros(0);
    Vec4f result2 = v3 * zeros;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result2[i]) < EPSILON);
    }

    // Test case 3: Multiply by one (identity)
    Vec4f v4(1, 2, 3, 4);
    Vec4f ones(1);
    Vec4f result3 = v4 * ones;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result3[i] - (float)(i + 1)) < EPSILON);
    }

    // Test case 4: Multiply negative numbers
    Vec4f v5(-1, -2, -3, -4);
    Vec4f v6(2, 3, 4, 5);
    Vec4f result4 = v5 * v6;
    float expected4[] = {-2.0f, -6.0f, -12.0f, -20.0f};
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result4[i] - expected4[i]) < EPSILON);
    }

    // Test case 5: Test with large values and saturation
    Vec4f v7(FLT_MAX/2, FLT_MAX/3, -FLT_MAX/2, -FLT_MAX/3);
    Vec4f v8(2.0f, 3.0f, 2.0f, 3.0f);
    Vec4f result5 = v7 * v8;
    assert(std::abs(result5[0] - FLT_MAX) < EPSILON);  // Saturates to FLT_MAX
    assert(std::abs(result5[1] - FLT_MAX) < EPSILON);  // Saturates to FLT_MAX
    assert(std::abs(result5[2] + FLT_MAX) < EPSILON);  // Saturates to -FLT_MAX
    assert(std::abs(result5[3] + FLT_MAX) < EPSILON);  // Saturates to -FLT_MAX

    // Test case 6: Chained multiplications
    Vec4f v9(1.0f, 1.0f, 1.0f, 1.0f);
    Vec4f v10(2.0f, 2.0f, 2.0f, 2.0f);
    Vec4f result6 = v9 * v10 * v10;  // Should be (4,4,4,4)
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result6[i] - 4.0f) < EPSILON);
    }

    std::cout << "test_multiply_operator passed!\n";
}
void test_multiply_assign_operator() {
    // Test case 1: Basic multiplication assignment
    Vec4f v1(1, 2, 3, 4);
    Vec4f v2(2, 2, 2, 2);
    v1 *= v2;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - (2.0f * (i + 1))) < EPSILON);
    }

    // Test case 2: Multiply by zero
    Vec4f v3(1, 2, 3, 4);
    Vec4f zeros(0);
    v3 *= zeros;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v3[i]) < EPSILON);
    }

    // Test case 3: Multiply by one (identity)
    Vec4f v4(1, 2, 3, 4);
    Vec4f ones(1);
    v4 *= ones;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v4[i] - (float)(i + 1)) < EPSILON);
    }

    // Test case 4: Multiply negative numbers
    Vec4f v5(-1, -2, -3, -4);
    Vec4f v6(2, 3, 4, 5);
    v5 *= v6;
    float expected[] = {-2, -6, -12, -20};
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v5[i] - expected[i]) < EPSILON);
    }

    // Test case 5: Test overflow behavior
    Vec4f v7(FLT_MAX/2, FLT_MAX/2, -FLT_MAX/2, -FLT_MAX/2);
    Vec4f v8(3.0f, 3.0f, 3.0f, 3.0f);
    v7 *= v8;
    assert(std::isinf(v7[0]));  // Should overflow to infinity
    assert(std::isinf(v7[1]));  // Should overflow to infinity
    assert(std::isinf(v7[2]));  // Should overflow to -infinity
    assert(std::isinf(v7[3]));  // Should overflow to -infinity

    // Test case 6: Chained multiplications
    Vec4f v9(1, 1, 1, 1);
    Vec4f v10(2, 2, 2, 2);
    v9 *= v10 *= v10;  // v10 becomes (4,4,4,4), then v9 becomes (4,4,4,4)
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v9[i] - 4.0f) < EPSILON);
        assert(std::abs(v10[i] - 4.0f) < EPSILON);
    }

    std::cout << "test_multiply_assign_operator passed!\n";
}

void test_vec4f_division_by_scalar() {
    // Test case 1: Basic division by positive scalar
    Vec4f v1(8.0f, 16.0f, 24.0f, 32.0f);
    float scalar1 = 2.0f;
    Vec4f result1 = v1 / scalar1;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result1[i] - (float)(4*(i+1))) < EPSILON);
    }

    // Test case 2: Division by negative scalar
    Vec4f v2(8.0f, -16.0f, 24.0f, -32.0f);
    float scalar2 = -2.0f;
    Vec4f result2 = v2 / scalar2;
    float expected2[] = {-4.0f, 8.0f, -12.0f, 16.0f};
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result2[i] - expected2[i]) < EPSILON);
    }

    // Test case 3: Division by small number (near zero)
    Vec4f v3(1.0f, 2.0f, 3.0f, 4.0f);
    float scalar3 = 0.1f;
    Vec4f result3 = v3 / scalar3;
    float expected3[] = {10.0f, 20.0f, 30.0f, 40.0f};
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result3[i] - expected3[i]) < EPSILON);
    }

    // Test case 4: Division by very small number (test large value handling)
    Vec4f v4(10.0f, -10.0f, FLT_MAX/2, -FLT_MAX/2);
    float scalar4 = 1e-38f;
    Vec4f result4 = v4 / scalar4;
    assert(std::isinf(result4[0]));  // Should overflow to infinity
    assert(std::isinf(result4[1]));  // Should overflow to -infinity
    assert(std::isinf(result4[2]));  // Should overflow to infinity
    assert(std::isinf(result4[3]));  // Should overflow to -infinity

    // Test case 5: Division of zero vector
    Vec4f v5(0.0f);
    float scalar5 = 2.0f;
    Vec4f result5 = v5 / scalar5;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result5[i]) < EPSILON);
    }

    // Test case 6: Division by one (identity operation)
    Vec4f v6(1.0f, 2.0f, 3.0f, 4.0f);
    float scalar6 = 1.0f;
    Vec4f result6 = v6 / scalar6;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result6[i] - (float)(i + 1)) < EPSILON);
    }

    // Test case 7: Division with min/max values
    Vec4f v7(FLT_MIN, FLT_MAX, -FLT_MIN, -FLT_MAX);
    float scalar7 = 2.0f;
    Vec4f result7 = v7 / scalar7;
    assert(std::abs(result7[0] - FLT_MIN/2) < EPSILON);
    assert(std::abs(result7[1] - FLT_MAX/2) < EPSILON);
    assert(std::abs(result7[2] + FLT_MIN/2) < EPSILON);
    assert(std::abs(result7[3] + FLT_MAX/2) < EPSILON);

    std::cout << "test_vec4f_division_by_scalar passed!\n";
}

void test_scalar_vec4f_division() {
    // Test case 1: Basic scalar/vector division with positive numbers
    float scalar1 = 24.0f;
    Vec4f v1(2.0f, 4.0f, 3.0f, 6.0f);
    Vec4f result1 = scalar1 / v1;
    assert(std::abs(result1[0] - 12.0f) < EPSILON); // 24/2
    assert(std::abs(result1[1] - 6.0f) < EPSILON);  // 24/4
    assert(std::abs(result1[2] - 8.0f) < EPSILON);  // 24/3
    assert(std::abs(result1[3] - 4.0f) < EPSILON);  // 24/6

    // Test case 2: Division with negative numbers
    float scalar2 = -24.0f;
    Vec4f v2(2.0f, -4.0f, 3.0f, -6.0f);
    Vec4f result2 = scalar2 / v2;
    assert(std::abs(result2[0] - (-12.0f)) < EPSILON);  // -24/2
    assert(std::abs(result2[1] - 6.0f) < EPSILON);      // -24/-4
    assert(std::abs(result2[2] - (-8.0f)) < EPSILON);   // -24/3
    assert(std::abs(result2[3] - 4.0f) < EPSILON);      // -24/-6

    // Test case 3: Division with very small numbers
    float scalar3 = 1.0f;
    Vec4f v3(0.1f, 0.2f, 0.4f, 0.5f);
    Vec4f result3 = scalar3 / v3;
    assert(std::abs(result3[0] - 10.0f) < EPSILON);  // 1/0.1
    assert(std::abs(result3[1] - 5.0f) < EPSILON);   // 1/0.2
    assert(std::abs(result3[2] - 2.5f) < EPSILON);   // 1/0.4
    assert(std::abs(result3[3] - 2.0f) < EPSILON);   // 1/0.5

    // Test case 4: Division with very large numbers (testing overflow protection)
    float scalar4 = 1.0f;
    Vec4f v4(FLT_MIN, -FLT_MIN, FLT_MAX, -FLT_MAX);
    Vec4f result4 = scalar4 / v4;
    assert(std::abs(result4[0] - (1.0f/FLT_MIN)) < EPSILON);
    assert(std::abs(result4[1] - (-1.0f/FLT_MIN)) < EPSILON);
    assert(std::abs(result4[2] - (1.0f/FLT_MAX)) < EPSILON);
    assert(std::abs(result4[3] - (-1.0f/FLT_MAX)) < EPSILON);

    // Test case 5: Division by very small numbers (near zero)
    float scalar5 = 10.0f;
    Vec4f v5(1e-38f, -1e-38f, 1e-38f, -1e-38f);
    Vec4f result5 = scalar5 / v5;
    assert(std::isinf(result5[0]));  // Should overflow to infinity
    assert(std::isinf(result5[1]));  // Should overflow to -infinity
    assert(std::isinf(result5[2]));  // Should overflow to infinity
    assert(std::isinf(result5[3]));  // Should overflow to -infinity

    // Test case 6: Division with 1.0 (reciprocal)
    float scalar6 = 1.0f;
    Vec4f v6(2.0f, 4.0f, 5.0f, 10.0f);
    Vec4f result6 = scalar6 / v6;
    assert(std::abs(result6[0] - 0.5f) < EPSILON);    // 1/2
    assert(std::abs(result6[1] - 0.25f) < EPSILON);   // 1/4
    assert(std::abs(result6[2] - 0.2f) < EPSILON);    // 1/5
    assert(std::abs(result6[3] - 0.1f) < EPSILON);    // 1/10

    std::cout << "test_scalar_vec4f_division passed!\n";
}

void test_vec4f_division() {
    // Test case 1: Basic division with positive numbers
    Vec4f v1(24.0f, 16.0f, 12.0f, 8.0f);
    Vec4f v2(2.0f, 4.0f, 3.0f, 2.0f);
    Vec4f result1 = v1 / v2;
    assert(std::abs(result1[0] - 12.0f) < EPSILON); // 24/2
    assert(std::abs(result1[1] - 4.0f) < EPSILON);  // 16/4
    assert(std::abs(result1[2] - 4.0f) < EPSILON);  // 12/3
    assert(std::abs(result1[3] - 4.0f) < EPSILON);  // 8/2

    // Test case 2: Division with negative numbers
    Vec4f v3(-24.0f, 16.0f, -12.0f, 8.0f);
    Vec4f v4(2.0f, -4.0f, 3.0f, -2.0f);
    Vec4f result2 = v3 / v4;
    assert(std::abs(result2[0] - (-12.0f)) < EPSILON); // -24/2
    assert(std::abs(result2[1] - (-4.0f)) < EPSILON);  // 16/-4
    assert(std::abs(result2[2] - (-4.0f)) < EPSILON);  // -12/3
    assert(std::abs(result2[3] - (-4.0f)) < EPSILON);  // 8/-2

    // Test case 3: Division with very small numbers
    Vec4f v5(0.0001f, 0.0002f, 0.0003f, 0.0004f);
    Vec4f v6(0.0002f, 0.0001f, 0.0003f, 0.0002f);
    Vec4f result3 = v5 / v6;
    assert(std::abs(result3[0] - 0.5f) < EPSILON);    // 0.0001/0.0002
    assert(std::abs(result3[1] - 2.0f) < EPSILON);    // 0.0002/0.0001
    assert(std::abs(result3[2] - 1.0f) < EPSILON);    // 0.0003/0.0003
    assert(std::abs(result3[3] - 2.0f) < EPSILON);    // 0.0004/0.0002

    // Test case 4: Division with large numbers (near FLT_MAX)
    Vec4f v7(FLT_MAX/2, FLT_MAX/3, -FLT_MAX/2, -FLT_MAX/3);
    Vec4f v8(2.0f, 3.0f, 2.0f, 3.0f);
    Vec4f result4 = v7 / v8;
    assert(std::abs(result4[0] - FLT_MAX/4) < EPSILON);
    assert(std::abs(result4[1] - FLT_MAX/9) < EPSILON);
    assert(std::abs(result4[2] - (-FLT_MAX/4)) < EPSILON);
    assert(std::abs(result4[3] - (-FLT_MAX/9)) < EPSILON);

    // Test case 5: Division by ones (identity division)
    Vec4f v9(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f ones(1.0f);
    Vec4f result5 = v9 / ones;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result5[i] - (float)(i + 1)) < EPSILON);
    }

    // Test case 6: Division of zeros
    Vec4f zeros(0.0f);
    Vec4f v10(2.0f, 3.0f, 4.0f, 5.0f);
    Vec4f result6 = zeros / v10;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result6[i]) < EPSILON);
    }

    // Test case 7: Test with min/max float values
    Vec4f v11(FLT_MIN, -FLT_MIN, FLT_MAX, -FLT_MAX);
    Vec4f v12(2.0f, 2.0f, 2.0f, 2.0f);
    Vec4f result7 = v11 / v12;
    assert(std::abs(result7[0] - FLT_MIN/2) < EPSILON);
    assert(std::abs(result7[1] - (-FLT_MIN/2)) < EPSILON);
    assert(std::abs(result7[2] - FLT_MAX/2) < EPSILON);
    assert(std::abs(result7[3] - (-FLT_MAX/2)) < EPSILON);

    // Test case 8: Division with mixed signs and values
    Vec4f v13(1.0f, -2.0f, FLT_MAX/2, -FLT_MIN);
    Vec4f v14(-1.0f, 2.0f, 2.0f, -2.0f);
    Vec4f result8 = v13 / v14;
    assert(std::abs(result8[0] - (-1.0f)) < EPSILON);
    assert(std::abs(result8[1] - (-1.0f)) < EPSILON);
    assert(std::abs(result8[2] - FLT_MAX/4) < EPSILON);
    assert(std::abs(result8[3] - FLT_MIN/2) < EPSILON);

    std::cout << "test_vec4f_division passed!\n";
}

void test_vec4f_division_assignment() {
    // Test case 1: Basic division assignment with positive numbers
    Vec4f v1(8.0f, 16.0f, 24.0f, 32.0f);
    Vec4f v2(2.0f, 4.0f, 6.0f, 8.0f);
    v1 /= v2;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v1[i] - 4.0f) < EPSILON);  // All should be 4
    }

    // Test case 2: Division assignment with negative numbers
    Vec4f v3(-24.0f, 16.0f, -12.0f, 8.0f);
    Vec4f v4(2.0f, -4.0f, 3.0f, -2.0f);
    v3 /= v4;
    assert(std::abs(v3[0] - (-12.0f)) < EPSILON); // -24/2
    assert(std::abs(v3[1] - (-4.0f)) < EPSILON);  // 16/-4
    assert(std::abs(v3[2] - (-4.0f)) < EPSILON);  // -12/3
    assert(std::abs(v3[3] - (-4.0f)) < EPSILON);  // 8/-2

    // Test case 3: Division assignment with very small numbers
    Vec4f v5(0.0001f, 0.0002f, 0.0003f, 0.0004f);
    Vec4f v6(0.0002f, 0.0001f, 0.0003f, 0.0002f);
    v5 /= v6;
    assert(std::abs(v5[0] - 0.5f) < EPSILON);    // 0.0001/0.0002
    assert(std::abs(v5[1] - 2.0f) < EPSILON);    // 0.0002/0.0001
    assert(std::abs(v5[2] - 1.0f) < EPSILON);    // 0.0003/0.0003
    assert(std::abs(v5[3] - 2.0f) < EPSILON);    // 0.0004/0.0002

    // Test case 4: Division assignment with large numbers (near FLT_MAX)
    Vec4f v7(FLT_MAX/2, FLT_MAX/3, -FLT_MAX/2, -FLT_MAX/3);
    Vec4f v8(2.0f, 3.0f, 2.0f, 3.0f);
    v7 /= v8;
    assert(std::abs(v7[0] - FLT_MAX/4) < EPSILON);
    assert(std::abs(v7[1] - FLT_MAX/9) < EPSILON);
    assert(std::abs(v7[2] - (-FLT_MAX/4)) < EPSILON);
    assert(std::abs(v7[3] - (-FLT_MAX/9)) < EPSILON);

    // Test case 5: Division assignment by ones (identity division)
    Vec4f v9(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f ones(1.0f);
    v9 /= ones;
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v9[i] - (float)(i + 1)) < EPSILON);
    }

    // Test case 6: Division assignment with min/max float values
    Vec4f v10(FLT_MIN, -FLT_MIN, FLT_MAX, -FLT_MAX);
    Vec4f v11(2.0f, 2.0f, 2.0f, 2.0f);
    v10 /= v11;
    assert(std::abs(v10[0] - FLT_MIN/2) < EPSILON);
    assert(std::abs(v10[1] - (-FLT_MIN/2)) < EPSILON);
    assert(std::abs(v10[2] - FLT_MAX/2) < EPSILON);
    assert(std::abs(v10[3] - (-FLT_MAX/2)) < EPSILON);

    // Test case 7: Sequential division assignments
    Vec4f v12(64.0f, 64.0f, 64.0f, 64.0f);
    Vec4f v13(2.0f, 2.0f, 2.0f, 2.0f);
    v12 /= v13;  // v12 becomes (32,32,32,32)
    v13 /= v12;  // v13 becomes (0.0625,0.0625,0.0625,0.0625)
    for(int i = 0; i < 4; i++) {
        assert(std::abs(v12[i] - 32.0f) < EPSILON);
        assert(std::abs(v13[i] - 0.0625f) < EPSILON);
    }

    // Test case 8: Mixed signs and values division assignment
    Vec4f v14(1.0f, -2.0f, FLT_MAX/2, -FLT_MIN);
    Vec4f v15(-1.0f, 2.0f, 2.0f, -2.0f);
    v14 /= v15;
    assert(std::abs(v14[0] - (-1.0f)) < EPSILON);
    assert(std::abs(v14[1] - (-1.0f)) < EPSILON);
    assert(std::abs(v14[2] - FLT_MAX/4) < EPSILON);
    assert(std::abs(v14[3] - FLT_MIN/2) < EPSILON);

    std::cout << "test_vec4f_division_assignment passed!\n";
}
void test_operator_equal() {
    // Test case 1: Equal vectors
    Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v2(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4ui result1 = (v1 == v2);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result1[i] == 0xFFFFFFFF)); // Equal
    }

    // Test case 2: Different vectors
    Vec4f v3(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v4(4.0f, 3.0f, 2.0f, 1.0f);
    Vec4ui result2 = (v3 == v4);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0); // All bits clear when not equal
    }

    // Test case 3: Partially equal vectors
    Vec4f v5(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v6(1.0f, 2.0f, 0.0f, 4.0f);
    Vec4ui result3 = (v5 == v6);
    assert(result3[0] == 0XFFFFFFFF); // Equal
    assert(result3[1] == 0XFFFFFFFF); // Equal
    assert(result3[2] == 0);  // Not equal
    assert(result3[3] == 0XFFFFFFFF); // Equal

    // Test case 4: Compare with zeros
    Vec4f v7(0.0f);
    Vec4f v8(0.0f);
    Vec4ui result4 = (v7 == v8);
    for(int i = 0; i < 4; i++) {
        assert(result4[i] == 0XFFFFFFFF); // All equal to zero
    }

    // Test case 5: Compare with maximum values
    Vec4f v9(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX);
    Vec4f v10(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX);
    Vec4ui result5 = (v9 == v10);
    for(int i = 0; i < 4; i++) {
        assert(result5[i] == 0xFFFFFFFF); // All equal to FLT_MAX
    }

    std::cout << "test_operator_equal passed!\n";
}
void test_operator_not_equal() {
    // Test case 1: Equal vectors should return false
    Vec4f v1(1, 2, 3, 4);
    Vec4f v2(1, 2, 3, 4);
    Vec4ui result1 = (v1 != v2);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == 0); // All bits clear when equal
    }

    // Test case 2: Different vectors should return true
    Vec4f v3(1, 2, 3, 4);
    Vec4f v4(4, 3, 2, 1);
    Vec4ui result2 = (v3 != v4);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0xFFFFFFFF); // All bits set when not equal
    }

    // Test case 3: Partially equal vectors
    Vec4f v5(1, 2, 3, 4);
    Vec4f v6(1, 2, 0, 4);
    Vec4ui result3 = (v5 != v6);
    assert(result3[0] == 0);         // Equal
    assert(result3[1] == 0);         // Equal
    assert(result3[2] == 0xFFFFFFFF); // Not equal
    assert(result3[3] == 0);         // Equal

    // Test case 4: Compare with zeros
    Vec4f v7(0);
    Vec4f v8(0);
    Vec4ui result4 = (v7 != v8);
    for(int i = 0; i < 4; i++) {
        assert(result4[i] == 0); // None not equal to zero
    }

    // Test case 5: Compare with maximum values
    Vec4f v9(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX);
    Vec4f v10(INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX);
    Vec4ui result5 = (v9 != v10);
    for(int i = 0; i < 4; i++) {
        assert(result5[i] == 0); // None not equal to INT32_MAX
    }

    std::cout << "test_operator_not_equal passed!\n";
}
void test_greater_than_operator() {
    // Test case 1: Basic greater than comparison
    Vec4f v1(2.0f, 3.0f, 4.0f, 5.0f);
    Vec4f v2(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4ui result1 = (v1 > v2);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == 0xFFFFFFFF); // All should be greater
    }

    // Test case 2: Equal values should return false
    Vec4f v3(1.0f, 2.0f, 3.0f, 4.0f); 
    Vec4f v4(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4ui result2 = (v3 > v4);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0); // None should be greater
    }

    // Test case 3: Mixed comparisons
    Vec4f v5(1.0f, 3.0f, 5.0f, 7.0f);
    Vec4f v6(2.0f, 2.0f, 6.0f, 6.0f);
    Vec4ui result3 = (v5 > v6);
    assert(result3[0] == 0);         // 1.0 < 2.0
    assert(result3[1] == 0xFFFFFFFF);// 3.0 > 2.0
    assert(result3[2] == 0);         // 5.0 < 6.0
    assert(result3[3] == 0xFFFFFFFF);// 7.0 > 6.0

    // Test case 4: Compare with large and small values
    Vec4f v7(FLT_MAX/2, FLT_MAX, 0.0f, -FLT_MAX/2);
    Vec4f v8(FLT_MAX, FLT_MAX/2, -1.0f, 0.0f);
    Vec4ui result4 = (v7 > v8);
    assert(result4[0] == 0);         // FLT_MAX/2 < FLT_MAX
    assert(result4[1] == 0xFFFFFFFF);// FLT_MAX > FLT_MAX/2
    assert(result4[2] == 0xFFFFFFFF);// 0.0 > -1.0
    assert(result4[3] == 0);         // -FLT_MAX/2 < 0.0

    // Test case 5: Compare with zeros
    Vec4f v9(1.0f, -1.0f, 0.0f, FLT_MAX);
    Vec4f zeros(0.0f);
    Vec4ui result5 = (v9 > zeros);
    assert(result5[0] == 0xFFFFFFFF);// 1.0 > 0.0
    assert(result5[1] == 0);         // -1.0 < 0.0
    assert(result5[2] == 0);         // 0.0 == 0.0
    assert(result5[3] == 0xFFFFFFFF);// FLT_MAX > 0.0

    std::cout << "test_greater_than_operator passed!\n";
}

void test_less_than_operator() {
    // Test case 1: Basic less than comparison
    Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v2(2.0f, 3.0f, 4.0f, 5.0f);
    Vec4ui result1 = (v1 < v2);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == 0xFFFFFFFF); // All should be less
    }

    // Test case 2: Equal values should return false
    Vec4f v3(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v4(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4ui result2 = (v3 < v4);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0); // None should be less
    }

    // Test case 3: Mixed comparisons
    Vec4f v5(2.0f, 2.0f, 6.0f, 6.0f);
    Vec4f v6(1.0f, 3.0f, 5.0f, 7.0f);
    Vec4ui result3 = (v5 < v6);
    assert(result3[0] == 0);         // 2 > 1
    assert(result3[1] == 0xFFFFFFFF);// 2 < 3
    assert(result3[2] == 0);         // 6 > 5
    assert(result3[3] == 0xFFFFFFFF);// 6 < 7

    // Test case 4: Compare with maximum and minimum values
    Vec4f v7(FLT_MAX/2, FLT_MAX, -1.0f, 0.0f);
    Vec4f v8(FLT_MAX, FLT_MAX/2, 0.0f, -1.0f);
    Vec4ui result4 = (v7 < v8);
    assert(result4[0] == 0xFFFFFFFF);// FLT_MAX/2 < FLT_MAX
    assert(result4[1] == 0);         // FLT_MAX > FLT_MAX/2
    assert(result4[2] == 0xFFFFFFFF);// -1 < 0
    assert(result4[3] == 0);         // 0 > -1

    // Test case 5: Compare with zeros
    Vec4f v9(1.0f, -1.0f, 0.0f, -FLT_MAX);
    Vec4f zeros(0.0f);
    Vec4ui result5 = (v9 < zeros);
    assert(result5[0] == 0);         // 1 < 0
    assert(result5[1] == 0xFFFFFFFF);// -1 < 0
    assert(result5[2] == 0);         // 0 < 0
    assert(result5[3] == 0xFFFFFFFF);// -FLT_MAX < 0

    std::cout << "test_less_than_operator passed!\n";
}
void test_greater_than_or_equal_operator() {
    // Test case 1: Basic greater than or equal comparison
    Vec4f v1(2.0f, 3.0f, 4.0f, 5.0f);
    Vec4f v2(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4ui result1 = (v1 >= v2);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == 0xFFFFFFFF); // All should be greater or equal
    }

    // Test case 2: Equal values should return true
    Vec4f v3(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v4(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4ui result2 = (v3 >= v4);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0xFFFFFFFF); // All should be equal (all bits set)
    }

    // Test case 3: Mixed comparisons
    Vec4f v5(1.0f, 3.0f, 5.0f, 7.0f);
    Vec4f v6(2.0f, 2.0f, 6.0f, 6.0f);
    Vec4ui result3 = (v5 >= v6);
    assert(result3[0] == 0);          // 1 <= 2
    assert(result3[1] == 0xFFFFFFFF); // 3 >= 2
    assert(result3[2] == 0);          // 5 <= 6
    assert(result3[3] == 0xFFFFFFFF); // 7 >= 6

    // Test case 4: Compare with maximum and minimum values
    Vec4f v7(FLT_MAX, FLT_MAX/2.0f, 0.0f, -1.0f);
    Vec4f v8(FLT_MAX, FLT_MAX, -1.0f, 0.0f);
    Vec4ui result4 = (v7 >= v8);
    assert(result4[0] == 0xFFFFFFFF); // FLT_MAX >= FLT_MAX
    assert(result4[1] == 0);          // FLT_MAX/2 <= FLT_MAX
    assert(result4[2] == 0xFFFFFFFF); // 0 >= -1
    assert(result4[3] == 0);          // -1 <= 0

    // Test case 5: Compare with zeros
    Vec4f v9(1.0f, -1.0f, 0.0f, FLT_MAX);
    Vec4f zeros(0.0f);
    Vec4ui result5 = (v9 >= zeros);
    assert(result5[0] == 0xFFFFFFFF); // 1 >= 0
    assert(result5[1] == 0);          // -1 <= 0
    assert(result5[2] == 0xFFFFFFFF); // 0 >= 0
    assert(result5[3] == 0xFFFFFFFF); // FLT_MAX >= 0

    std::cout << "test_greater_than_or_equal_operator passed!\n";
}
void test_less_than_or_equal_operator() {
    // Test case 1: Basic less than or equal comparison
    Vec4f v1(1, 2, 3, 4);
    Vec4f v2(2, 3, 4, 5);
    Vec4ui result1 = (v1 <= v2);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == 0xFFFFFFFF); // All should be less or equal
    }

    // Test case 2: Equal values should return true
    Vec4f v3(1, 2, 3, 4);
    Vec4f v4(1, 2, 3, 4);
    Vec4ui result2 = (v3 <= v4);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0xFFFFFFFF); // All should be equal
    }

    // Test case 3: Mixed comparisons
    Vec4f v5(2, 2, 6, 6);
    Vec4f v6(1, 3, 5, 7);
    Vec4ui result3 = (v5 <= v6);
    assert(result3[0] == 0);          // 2 <= 1
    assert(result3[1] == 0xFFFFFFFF); // 2 <= 3
    assert(result3[2] == 0);          // 6 <= 5
    assert(result3[3] == 0xFFFFFFFF); // 6 <= 7

    // Test case 4: Compare with maximum and minimum values
    Vec4f v7(FLT_MAX/2, FLT_MAX, -1.0f, 0.0f);
    Vec4f v8(FLT_MAX, FLT_MAX/2, 0.0f, -1.0f);
    Vec4ui result4 = (v7 <= v8);
    assert(result4[0] == 0xFFFFFFFF); // FLT_MAX/2 <= FLT_MAX
    assert(result4[1] == 0);          // FLT_MAX <= FLT_MAX/2
    assert(result4[2] == 0xFFFFFFFF); // -1 <= 0
    assert(result4[3] == 0);          // 0 <= -1

    // Test case 5: Compare with zeros
    Vec4f v9(1.0f, -1.0f, 0.0f, -FLT_MAX);
    Vec4f zeros(0.0f);
    Vec4ui result5 = (v9 <= zeros);
    assert(result5[0] == 0);          // 1 <= 0
    assert(result5[1] == 0xFFFFFFFF); // -1 <= 0
    assert(result5[2] == 0xFFFFFFFF); // 0 <= 0
    assert(result5[3] == 0xFFFFFFFF); // INT32_MIN <= 0

    std::cout << "test_less_than_or_equal_operator passed!\n";
}

void test_bitwise_and_operator() {
    // Test case 1: Basic AND operation
    uint32_t bits1 = 0x40000000;  // 2.0f in IEEE 754
    uint32_t bits2 = 0x40400000;  // 3.0f in IEEE 754
    float val1 = *(float*)&bits1;
    float val2 = *(float*)&bits2;
    Vec4f v1(val1);
    Vec4f v2(val2);
    Vec4f result1 = v1 & v2;
    uint32_t expected = 0x40000000;  // Result of AND operation
    for(int i = 0; i < 4; i++) {
        uint32_t res_bits;
        float temp = result1[i];
        memcpy(&res_bits, &temp, sizeof(float));
        assert(res_bits == expected);
    }

    // Test case 2: AND with zero
    Vec4f v3(val1);
    Vec4f zeros(0.0f);
    Vec4f result2 = v3 & zeros;
    for(int i = 0; i < 4; i++) {
        uint32_t res_bits;
        float temp = result2[i];
        memcpy(&res_bits, &temp, sizeof(float));
        assert(res_bits == 0);
    }

    // Test case 3: AND with identical values
    Vec4f v4(val1);
    Vec4f result3 = v4 & v4;
    for(int i = 0; i < 4; i++) {
        assert(result3[i] == val1);
    }

    std::cout << "test_bitwise_and_operator passed!\n";
}
void test_bitwise_or_operator() {
    // Test case 1: Basic OR operation with bit patterns
    uint32_t pattern1 = 0x3F800000;  // Represents 1.0f in IEEE 754
    uint32_t pattern2 = 0x40000000;  // Represents 2.0f in IEEE 754
    Vec4f v1(*(float*)&pattern1);
    Vec4f v2(*(float*)&pattern2);
    Vec4f result1 = v1 | v2;
    uint32_t expected1 = pattern1 | pattern2;
    for(int i = 0; i < 4; i++) {
        uint32_t res_bits;
        float temp = result1[i];
        memcpy(&res_bits, &temp, sizeof(float));
        assert(res_bits == expected1);
    }

    // Test case 2: OR with zero
    float zero = 0.0f;
    uint32_t zero_pattern;
    memcpy(&zero_pattern, &zero, sizeof(float));
    Vec4f v3(*(float*)&pattern1);
    Vec4f zeros(0.0f);
    Vec4f result2 = v3 | zeros;
    uint32_t expected2 = pattern1 | zero_pattern;
    for(int i = 0; i < 4; i++) {
        uint32_t res_bits;
        float temp = result2[i];
        memcpy(&res_bits, &temp, sizeof(float));
        assert(res_bits == expected2);
    }

    // Test case 3: OR with specific patterns
    uint32_t pattern3 = 0x40800000;  // Represents 4.0f in IEEE 754
    uint32_t pattern4 = 0x40A00000;  // Represents 5.0f in IEEE 754
    Vec4f v4(*(float*)&pattern3);
    Vec4f v5(*(float*)&pattern4);
    Vec4f result3 = v4 | v5;
    uint32_t expected3 = pattern3 | pattern4;
    for(int i = 0; i < 4; i++) {
        uint32_t res_bits;
        float temp = result3[i];
        memcpy(&res_bits, &temp, sizeof(float));
        assert(res_bits == expected3);
    }

    std::cout << "test_bitwise_or_operator passed!\n";
}
void test_bitwise_xor_operator() {
    // Test case 1: Basic XOR operation with specific bit patterns
    uint32_t pattern1 = 0x55555555;
    uint32_t pattern2 = 0x2AAAAAAA;
    Vec4f v1(*(float*)&pattern1);
    Vec4f v2(*(float*)&pattern2);
    Vec4f result1 = v1 ^ v2;
    uint32_t expected1 = pattern1 ^ pattern2;
    for(int i = 0; i < 4; i++) {
        uint32_t res_bits;
        float temp = result1[i];
        memcpy(&res_bits, &temp, sizeof(float));
        assert(res_bits == expected1);
    }

    // Test case 2: XOR with zero
    float zero = 0.0f;
    uint32_t zero_pattern;

    memcpy(&zero_pattern, &zero, sizeof(float));
    Vec4f v3(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f zeros(0.0f);
    Vec4f result2 = v3 ^ zeros;
    for(int i = 0; i < 4; i++) {
        uint32_t original_bits;
        float temp = v3[i];
        memcpy(&original_bits, &temp, sizeof(float));
        uint32_t res_bits;

        temp = result2[i];
        memcpy(&res_bits, &temp, sizeof(float));
        assert(res_bits == (original_bits ^ zero_pattern));
    }

    // Test case 3: XOR with self (should be zero)
    uint32_t pattern3 = 0x12345678;
    Vec4f v4(*(float*)&pattern3);
    Vec4f result3 = v4 ^ v4;
    for(int i = 0; i < 4; i++) {
        uint32_t res_bits;
        float temp = result3[i];
        memcpy(&res_bits, &temp, sizeof(float));
        assert(res_bits == 0);
    }

    // Test case 4: XOR with specific patterns
    uint32_t pattern4 = 0xAABBCCDD;
    uint32_t pattern5 = 0x11223344;
    Vec4f v5(*(float*)&pattern4);
    Vec4f v6(*(float*)&pattern5);
    Vec4f result4 = v5 ^ v6;
    uint32_t expected4 = pattern4 ^ pattern5;
    for(int i = 0; i < 4; i++) {
        uint32_t res_bits;
        float temp = result4[i];
        memcpy(&res_bits, &temp, sizeof(float));
        assert(res_bits == expected4);
    }

    std::cout << "test_bitwise_xor_operator passed!\n";
}
void test_bitwise_not_operator() {
    // Test case 1: Basic bitwise NOT using bit patterns
    uint32_t pattern1 = 0;
    Vec4f v1(*(float*)&pattern1);
    Vec4f result1 = ~v1;
    for(int i = 0; i < 4; i++) {
        uint32_t res_bits;
        float temp = result1[i];
        memcpy(&res_bits, &temp, sizeof(float));
        assert(res_bits == ~pattern1);
    }

    // Test case 2: NOT on specific bit pattern
    uint32_t pattern2 = 0x55555555;
    Vec4f v2(*(float*)&pattern2);
    Vec4f result2 = ~v2;
    for(int i = 0; i < 4; i++) {
        uint32_t res_bits;
        float temp = result2[i];
        memcpy(&res_bits, &temp, sizeof(float));
        assert(res_bits == 0xAAAAAAAA);
    }

    // Test case 3: NOT on alternating bit patterns
    uint32_t pattern3 = 0xFFFFFFFF;
    Vec4f v3(*(float*)&pattern3);
    Vec4f result3 = ~v3;
    for(int i = 0; i < 4; i++) {
        uint32_t res_bits;
        float temp = result3[i];
        memcpy(&res_bits, &temp, sizeof(float));
        assert(res_bits == 0);
    }

    // Test case 4: NOT on IEEE 754 float bit patterns
    float f4 = 1.0f;
    uint32_t pattern4;
    memcpy(&pattern4, &f4, sizeof(float));
    Vec4f v4(f4);
    Vec4f result4 = ~v4;
    for(int i = 0; i < 4; i++) {
        uint32_t res_bits;
        float temp = result4[i];
        memcpy(&res_bits, &temp, sizeof(float));
        assert(res_bits == ~pattern4);
    }

    std::cout << "test_bitwise_not_operator passed!\n";
}

void test_select() {
    // Test case 1: Basic selection with all true mask
    Vec4ui mask1(0xFFFFFFFF);  // All bits set (true)
    Vec4f a1(1, 2, 3, 4);
    Vec4f b1(-1, -2, -3, -4);
    Vec4f result1 = select(mask1, a1, b1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result1[i] - (i + 1)) < EPSILON);  // Should select all from a1
    }

    // Test case 2: Basic selection with all false mask
    Vec4ui mask2(0);  // All bits clear (false) 
    Vec4f a2(1, 2, 3, 4);
    Vec4f b2(-1, -2, -3, -4);
    Vec4f result2 = select(mask2, a2, b2);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result2[i] - (-(i + 1))) < EPSILON);  // Should select all from b2
    }

    // Test case 3: Alternating selection
    Vec4ui mask3(0xFFFFFFFF, 0, 0xFFFFFFFF, 0);
    Vec4f a3(1, 2, 3, 4);
    Vec4f b3(-1, -2, -3, -4);
    Vec4f result3 = select(mask3, a3, b3);
    assert(std::abs(result3[0] - 1) < EPSILON);   // From a3
    assert(std::abs(result3[1] - (-2)) < EPSILON);  // From b3 
    assert(std::abs(result3[2] - 3) < EPSILON);   // From a3
    assert(std::abs(result3[3] - (-4)) < EPSILON);  // From b3

    // Test case 4: Selection with special values
    Vec4ui mask4(0xFFFFFFFF, 0xFFFFFFFF, 0, 0);
    Vec4f a4(FLT_MAX, -FLT_MAX, 1000.0f, -1000.0f);
    Vec4f b4(-FLT_MAX, FLT_MAX, -1.0f, 0.0f);
    Vec4f result4 = select(mask4, a4, b4);
    assert(std::abs(result4[0] - FLT_MAX) < EPSILON);      // From a4
    assert(std::abs(result4[1] - (-FLT_MAX)) < EPSILON);   // From a4
    assert(std::abs(result4[2] - (-1.0f)) < EPSILON);      // From b4
    assert(std::abs(result4[3]) < EPSILON);                // From b4

    // Test case 5: Selection with zeros and ones
    Vec4ui mask5(0xFFFFFFFF);  // All bits set
    Vec4f a5(0);              // All zeros
    Vec4f b5(1);              // All ones
    Vec4f result5 = select(mask5, a5, b5);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result5[i]) < EPSILON);  // Should select all zeros from a5
    }

    std::cout << "test_select passed!\n";
}
void test_if_add() {
    // Test case 1: Basic conditional add with all true mask
    Vec4ui mask1(0xFFFFFFFF);  // All bits set (true)
    Vec4f a1(1, 2, 3, 4);
    Vec4f b1(1, 1, 1, 1);
    Vec4f result1 = if_add(mask1, a1, b1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result1[i] - (i + 2.0f)) < EPSILON);  // Should add all elements
    }

    // Test case 2: Conditional add with all false mask
    Vec4ui mask2(0);  // All bits clear (false)
    Vec4f a2(1, 2, 3, 4);
    Vec4f b2(1, 1, 1, 1);
    Vec4f result2 = if_add(mask2, a2, b2);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result2[i] - (i + 1.0f)) < EPSILON);  // Should not add anything
    }

    // Test case 3: Alternating conditional add
    Vec4ui mask3(0xFFFFFFFF, 0, 0xFFFFFFFF, 0);
    Vec4f a3(1, 2, 3, 4);
    Vec4f b3(10, 20, 30, 40);
    Vec4f result3 = if_add(mask3, a3, b3);
    assert(std::abs(result3[0] - 11.0f) < EPSILON);  // 1 + 10
    assert(std::abs(result3[1] - 2.0f) < EPSILON);   // 2 + 0
    assert(std::abs(result3[2] - 33.0f) < EPSILON);  // 3 + 30
    assert(std::abs(result3[3] - 4.0f) < EPSILON);   // 4 + 0

    // Test case 4: Test saturation behavior
    Vec4ui mask4(0xFFFFFFFF);
    Vec4f a4(FLT_MAX/2, FLT_MAX/3, -FLT_MAX/2, -FLT_MAX/3);
    Vec4f b4(FLT_MAX/2, FLT_MAX/3*2, -FLT_MAX/2, -FLT_MAX/3*2);
    Vec4f result4 = if_add(mask4, a4, b4);
    assert(std::abs(result4[0] - FLT_MAX) < EPSILON);     // Saturated addition
    assert(std::abs(result4[1] - FLT_MAX) < EPSILON);     // Saturated addition
    assert(std::abs(result4[2] + FLT_MAX) < EPSILON);     // Saturated addition
    assert(std::abs(result4[3] + FLT_MAX) < EPSILON);     // Saturated addition

    // Test case 5: Test with zero operands
    Vec4ui mask5(0xFFFFFFFF);
    Vec4f a5(0);
    Vec4f b5(0);
    Vec4f result5 = if_add(mask5, a5, b5);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result5[i]) < EPSILON);  // 0 + 0 should be 0
    }

    std::cout << "test_if_add passed!\n";
}
void test_if_sub() {
    // Test case 1: Basic conditional subtract with all true mask
    Vec4ui mask1(0xFFFFFFFF);  // All bits set (true)
    Vec4f a1(10.0f, 20.0f, 30.0f, 40.0f);
    Vec4f b1(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f result1 = if_sub(mask1, a1, b1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result1[i] - (10.0f*(i+1) - (i+1))) < EPSILON);
    }

    // Test case 2: Conditional subtract with all false mask
    Vec4ui mask2(0);  // All bits clear (false)
    Vec4f a2(10.0f, 20.0f, 30.0f, 40.0f);
    Vec4f b2(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f result2 = if_sub(mask2, a2, b2);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result2[i] - (10.0f*(i+1))) < EPSILON);
    }

    // Test case 3: Alternating conditional subtract
    Vec4ui mask3(0xFFFFFFFF, 0, 0xFFFFFFFF, 0);
    Vec4f a3(10.0f, 20.0f, 30.0f, 40.0f);
    Vec4f b3(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f result3 = if_sub(mask3, a3, b3);
    assert(std::abs(result3[0] - 9.0f) < EPSILON);   // 10 - 1
    assert(std::abs(result3[1] - 20.0f) < EPSILON);  // 20 - 0
    assert(std::abs(result3[2] - 27.0f) < EPSILON);  // 30 - 3
    assert(std::abs(result3[3] - 40.0f) < EPSILON);  // 40 - 0

    // Test case 4: Test with very large numbers
    Vec4ui mask4(0xFFFFFFFF);
    Vec4f a4(FLT_MAX/2, FLT_MAX/3, -FLT_MAX/2, -FLT_MAX/3);
    Vec4f b4(FLT_MAX/3, FLT_MAX/2, -FLT_MAX/3, -FLT_MAX/2);
    Vec4f result4 = if_sub(mask4, a4, b4);
    assert(std::abs(result4[0] - (FLT_MAX/2 - FLT_MAX/3)) < EPSILON);
    assert(std::abs(result4[1] - (FLT_MAX/3 - FLT_MAX/2)) < EPSILON);
    assert(std::abs(result4[2] - (-FLT_MAX/2 + FLT_MAX/3)) < EPSILON);
    assert(std::abs(result4[3] - (-FLT_MAX/3 + FLT_MAX/2)) < EPSILON);

    // Test case 5: Test with zero operands
    Vec4ui mask5(0xFFFFFFFF);
    Vec4f a5(0.0f);
    Vec4f b5(0.0f);
    Vec4f result5 = if_sub(mask5, a5, b5);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result5[i]) < EPSILON);  // 0 - 0 should be 0
    }

    std::cout << "test_if_sub passed!\n";
}

void test_if_mul() {
    // Test case 1: Basic conditional multiply with all true mask
    Vec4ui mask1(0xFFFFFFFF);  // All bits set (true)
    Vec4f a1(1, 2, 3, 4);
    Vec4f b1(2, 2, 2, 2);
    Vec4f result1 = if_mul(mask1, a1, b1);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == (i + 1) * 2);  // Should multiply all elements
    }

    // Test case 2: Conditional multiply with all false mask
    Vec4ui mask2(0);  // All bits clear (false)
    Vec4f a2(1, 2, 3, 4);
    Vec4f b2(2, 2, 2, 2);
    Vec4f result2 = if_mul(mask2, a2, b2);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == i + 1);  // Should return original a values
    }

    // Test case 3: Alternating conditional multiply
    Vec4ui mask3(0xFFFFFFFF, 0, 0xFFFFFFFF, 0);
    Vec4f a3(1, 2, 3, 4);
    Vec4f b3(10, 20, 30, 40);
    
    Vec4f result3 = if_mul(mask3, a3, b3);
    assert(result3[0] == 10);  // 1 * 10
    assert(result3[1] == 2);   // 2 (original)
    assert(result3[2] == 90);  // 3 * 30
    assert(result3[3] == 4);   // 4 (original)

    // Test case 4: Test saturation behavior
    Vec4ui mask4(0xFFFFFFFF);
    Vec4f a4(FLT_MAX/2, FLT_MAX/3, -FLT_MAX/2, -FLT_MAX/3);
    Vec4f b4(2.0f, 3.0f, 2.0f, 3.0f);

    Vec4f result4 = if_mul(mask4, a4, b4);
    assert(std::abs(result4[0] - FLT_MAX) < EPSILON);  // Should be very large positive
    assert(std::abs(result4[1] - FLT_MAX) < EPSILON);  // Should be very large positive
    assert(std::abs(result4[2] + FLT_MAX) < EPSILON);  // Should be very large negative
    assert(std::abs(result4[3] + FLT_MAX) < EPSILON);  // Should be very large negative

    // Test case 5: Test with zero operands
    Vec4ui mask5(0xFFFFFFFF);
    Vec4f a5(1, 2, 3, 4);
    Vec4f b5(0);
    Vec4f result5 = if_mul(mask5, a5, b5);
    for(int i = 0; i < 4; i++) {
        assert(result5[i] == 0);  // Multiplication by 0 should give 0
    }

    std::cout << "test_if_mul passed!\n";
}

void test_horizontal_add() {
    // Test case 1: Basic addition of positive numbers
    Vec4f v1(1, 2, 3, 4);
    float result1 = horizontal_add(v1);
    assert(std::abs(result1 - 10.0f) < EPSILON);  // 1 + 2 + 3 + 4 = 10

    // Test case 2: Addition of negative numbers 
    Vec4f v2(-1, -2, -3, -4);
    float result2 = horizontal_add(v2);
    assert(std::abs(result2 - (-10.0f)) < EPSILON);  // -1 + (-2) + (-3) + (-4) = -10

    // Test case 3: Addition of zeros
    Vec4f v3(0);
    float result3 = horizontal_add(v3);
    assert(std::abs(result3) < EPSILON);  // 0 + 0 + 0 + 0 = 0

    // Test case 4: Mixed positive and negative numbers
    Vec4f v4(1, -1, 2, -2);
    float result4 = horizontal_add(v4);
    assert(std::abs(result4) < EPSILON);  // 1 + (-1) + 2 + (-2) = 0

    // Test case 5: Large numbers testing potential overflow
    Vec4f v5(FLT_MAX/4, FLT_MAX/4, -FLT_MAX/4, -FLT_MAX/4);
    float result5 = horizontal_add(v5);
    assert(std::abs(result5) < EPSILON);  // Sum should be 0

    // Test case 6: Alternating positive numbers
    Vec4f v6(1, 3, 5, 7);
    float result6 = horizontal_add(v6);
    assert(std::abs(result6 - 16.0f) < EPSILON);  // 1 + 3 + 5 + 7 = 16

    // Test case 7: Random mix of numbers
    Vec4f v7(100, -50, 75, -25);
    float result7 = horizontal_add(v7);
    assert(std::abs(result7 - 100.0f) < EPSILON);  // 100 + (-50) + 75 + (-25) = 100

    std::cout << "test_horizontal_add passed!\n";
}
void test_max() {
    // Test case 1: Basic max comparison with positive numbers
    Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v2(4.0f, 3.0f, 2.0f, 1.0f);
    Vec4f result1 = max(v1, v2);
    assert(std::abs(result1[0] - 4.0f) < EPSILON);
    assert(std::abs(result1[1] - 3.0f) < EPSILON);
    assert(std::abs(result1[2] - 3.0f) < EPSILON);
    assert(std::abs(result1[3] - 4.0f) < EPSILON);

    // Test case 2: Max of equal numbers
    Vec4f v3(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v4(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f result2 = max(v3, v4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result2[i] - (float)(i + 1)) < EPSILON);  // Should return same numbers
    }

    // Test case 3: Max with negative numbers
    Vec4f v5(-4.0f, -3.0f, -2.0f, -1.0f);
    Vec4f v6(-1.0f, -2.0f, -3.0f, -4.0f);
    Vec4f result3 = max(v5, v6);
    assert(std::abs(result3[0] - (-1.0f)) < EPSILON);
    assert(std::abs(result3[1] - (-2.0f)) < EPSILON);
    assert(std::abs(result3[2] - (-2.0f)) < EPSILON);
    assert(std::abs(result3[3] - (-1.0f)) < EPSILON);

    // Test case 4: Max with mix of positive and negative
    Vec4f v7(-1.0f, 2.0f, -3.0f, 4.0f);
    Vec4f v8(1.0f, -2.0f, 3.0f, -4.0f);
    Vec4f result4 = max(v7, v8);
    assert(std::abs(result4[0] - 1.0f) < EPSILON);
    assert(std::abs(result4[1] - 2.0f) < EPSILON);
    assert(std::abs(result4[2] - 3.0f) < EPSILON);
    assert(std::abs(result4[3] - 4.0f) < EPSILON);

    // Test case 5: Max with maximum/minimum values
    Vec4f v9(FLT_MAX, -FLT_MAX, 0.0f, FLT_MAX);
    Vec4f v10(0.0f, 0.0f, -FLT_MAX, -FLT_MAX);
    Vec4f result5 = max(v9, v10);
    assert(std::abs(result5[0] - FLT_MAX) < EPSILON);  // FLT_MAX vs 0
    assert(std::abs(result5[1]) < EPSILON);            // -FLT_MAX vs 0
    assert(std::abs(result5[2]) < EPSILON);            // 0 vs -FLT_MAX
    assert(std::abs(result5[3] - FLT_MAX) < EPSILON);  // FLT_MAX vs -FLT_MAX

    std::cout << "test_max passed!\n";
}
void test_min() {
    // Test case 1: Basic min comparison with positive numbers
    Vec4f v1(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v2(4.0f, 3.0f, 2.0f, 1.0f);
    Vec4f result1 = min(v1, v2);
    assert(std::abs(result1[0] - 1.0f) < EPSILON);
    assert(std::abs(result1[1] - 2.0f) < EPSILON);
    assert(std::abs(result1[2] - 2.0f) < EPSILON);
    assert(std::abs(result1[3] - 1.0f) < EPSILON);

    // Test case 2: Min of equal numbers
    Vec4f v3(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f v4(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f result2 = min(v3, v4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result2[i] - (float)(i + 1)) < EPSILON);  // Should return same numbers
    }

    // Test case 3: Min with negative numbers
    Vec4f v5(-8.0f, -7.0f, -6.0f, -5.0f);
    Vec4f v6(-1.0f, -2.0f, -3.0f, -4.0f);
    Vec4f result3 = min(v5, v6);
    assert(std::abs(result3[0] - (-8.0f)) < EPSILON);
    assert(std::abs(result3[1] - (-7.0f)) < EPSILON);
    assert(std::abs(result3[2] - (-6.0f)) < EPSILON);
    assert(std::abs(result3[3] - (-5.0f)) < EPSILON);

    // Test case 4: Min with mix of positive and negative
    Vec4f v7(-1.0f, 2.0f, -3.0f, 4.0f);
    Vec4f v8(1.0f, -2.0f, 3.0f, -4.0f);
    Vec4f result4 = min(v7, v8);
    assert(std::abs(result4[0] - (-1.0f)) < EPSILON);
    assert(std::abs(result4[1] - (-2.0f)) < EPSILON);
    assert(std::abs(result4[2] - (-3.0f)) < EPSILON);
    assert(std::abs(result4[3] - (-4.0f)) < EPSILON);

    // Test case 5: Min with large values
    Vec4f v9(FLT_MAX, -FLT_MAX, 0.0f, FLT_MAX);
    Vec4f v10(0.0f, 0.0f, -FLT_MAX, -FLT_MAX);
    Vec4f result5 = min(v9, v10);
    assert(std::abs(result5[0]) < EPSILON);            // FLT_MAX vs 0
    assert(std::abs(result5[1] - (-FLT_MAX)) < EPSILON);  // -FLT_MAX vs 0
    assert(std::abs(result5[2] - (-FLT_MAX)) < EPSILON);  // 0 vs -FLT_MAX
    assert(std::abs(result5[3] - (-FLT_MAX)) < EPSILON);  // FLT_MAX vs -FLT_MAX

    std::cout << "test_min passed!\n";
}
void test_abs() {
    // Test case 1: Basic absolute values of negative numbers
    Vec4f v1(-1.0f, -2.0f, -3.0f, -4.0f);
    Vec4f result1 = abs(v1);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result1[i] - (float)(i + 1)) < EPSILON);  // Should return positive values
    }

    // Test case 2: Absolute values of positive numbers (no change)
    Vec4f v2(1.0f, 2.0f, 3.0f, 4.0f);
    Vec4f result2 = abs(v2);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result2[i] - (float)(i + 1)) < EPSILON);  // Should return same positive values
    }

    // Test case 3: Mix of positive and negative numbers
    Vec4f v3(-1.0f, 2.0f, -3.0f, 4.0f);
    Vec4f result3 = abs(v3);
    assert(std::abs(result3[0] - 1.0f) < EPSILON);
    assert(std::abs(result3[1] - 2.0f) < EPSILON);
    assert(std::abs(result3[2] - 3.0f) < EPSILON);
    assert(std::abs(result3[3] - 4.0f) < EPSILON);

    // Test case 4: Zero values
    Vec4f v4(0.0f);
    Vec4f result4 = abs(v4);
    for(int i = 0; i < 4; i++) {
        assert(std::abs(result4[i]) < EPSILON);  // Absolute value of 0 is 0
    }

    // Test case 5: Test with large float values
    Vec4f v5(-FLT_MAX, FLT_MAX, -FLT_MAX/2, FLT_MAX/2);
    Vec4f result5 = abs(v5);
    assert(std::abs(result5[0] - FLT_MAX) < EPSILON);  // abs(-FLT_MAX) = FLT_MAX
    assert(std::abs(result5[1] - FLT_MAX) < EPSILON);  // abs(FLT_MAX) = FLT_MAX
    assert(std::abs(result5[2] - FLT_MAX/2) < EPSILON);  // abs(-FLT_MAX/2) = FLT_MAX/2
    assert(std::abs(result5[3] - FLT_MAX/2) < EPSILON);  // abs(FLT_MAX/2) = FLT_MAX/2

    std::cout << "test_abs passed!\n";
}
int main() 
{
    test_default_constructor();
    test_broadcast_constructor();
    test_element_constructor();
    test_floatx4t_constructor();
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
    test_vec4f_division_by_scalar();
    test_scalar_vec4f_division();
    test_vec4f_division();
    test_vec4f_division_assignment();

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
    std::cout << "All tests passed!\n";
    return 0;
}