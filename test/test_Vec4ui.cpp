#include "../Vec4ui.h"
#include <iostream>
#include <cassert>

using namespace VCL_NAMESPACE;

void test_default_constructor() {
    // Test default constructor initializes to zero
    Vec4ui v;
    for(int i = 0; i < 4; i++) {
        assert(v[i] == 0);
    }
    
    // Test multiple instances
    Vec4ui v2;
    Vec4ui v3;
    for(int i = 0; i < 4; i++) {
        assert(v2[i] == 0);
        assert(v3[i] == 0);
    }

    // Test value changes after default construction
    Vec4ui v4;
    v4 = Vec4ui(1,2,3,4); 
    for(int i = 0; i < 4; i++) {
        assert(v4[i] == i+1);
    }
    std::cout << "test_default_constructor passed!\n";
}
void test_broadcast_constructor() {
    // Test case 1: Broadcast zero
    Vec4ui v1(0);
    for(int i = 0; i < 4; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Broadcast maximum value
    Vec4ui v2(0xFFFFFFFF);
    for(int i = 0; i < 4; i++) {
        assert(v2[i] == 0xFFFFFFFF);
    }

    // Test case 3: Broadcast arbitrary value
    Vec4ui v3(0x12345678);
    for(int i = 0; i < 4; i++) {
        assert(v3[i] == 0x12345678);
    }

    // Test case 4: Multiple instances with different values
    Vec4ui v4(0xAAAAAAAA);
    Vec4ui v5(0x55555555);
    for(int i = 0; i < 4; i++) {
        assert(v4[i] == 0xAAAAAAAA);
        assert(v5[i] == 0x55555555);
    }
    std::cout << "test_broadcast_constructor passed!\n";
}
void test_element_constructor() {
    // Test case 1: Sequential values
    Vec4ui v1(0, 1, 2, 3);
    for(int i = 0; i < 4; i++) {
        assert(v1[i] == i);
    }

    // Test case 2: All same values
    Vec4ui v2(5, 5, 5, 5);
    for(int i = 0; i < 4; i++) {
        assert(v2[i] == 5);
    }

    // Test case 3: Maximum values
    Vec4ui v3(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
    for(int i = 0; i < 4; i++) {
        assert(v3[i] == 0xFFFFFFFF);
    }

    // Test case 4: Mixed values
    Vec4ui v4(0x12345678, 0xABCDEF00, 0, 0xFFFFFFFF);
    assert(v4[0] == 0x12345678);
    assert(v4[1] == 0xABCDEF00);
    assert(v4[2] == 0);
    assert(v4[3] == 0xFFFFFFFF);

    std::cout << "test_element_constructor passed!\n";
}
void test_uint32x4t_constructor() {
    // Test case 1: Create uint32x4_t with zeros and construct Vec4ui from it
    uint32_t data1[4] = {0, 0, 0, 0};
    uint32x4_t x1 = vld1q_u32(data1);
    Vec4ui v1(x1);
    for(int i = 0; i < 4; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Create uint32x4_t with sequential values
    uint32_t data2[4] = {1, 2, 3, 4}; 
    uint32x4_t x2 = vld1q_u32(data2);
    Vec4ui v2(x2);
    for(int i = 0; i < 4; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Create uint32x4_t with maximum values
    uint32_t data3[4] = {0xFFFFFFFF, 0xFFFFFFFF, 
                         0xFFFFFFFF, 0xFFFFFFFF};
    uint32x4_t x3 = vld1q_u32(data3);
    Vec4ui v3(x3);
    for(int i = 0; i < 4; i++) {
        assert(v3[i] == 0xFFFFFFFF);
    }

    // Test case 4: Create uint32x4_t with mixed values
    uint32_t data4[4] = {0x12345678, 0xABCDEF00,
                         0, 0xFFFFFFFF};
    uint32x4_t x4 = vld1q_u32(data4);
    Vec4ui v4(x4);
    assert(v4[0] == 0x12345678);
    assert(v4[1] == 0xABCDEF00);
    assert(v4[2] == 0);
    assert(v4[3] == 0xFFFFFFFF);
    std::cout << "test_uint32x4t_constructor passed!\n";
}
void test_copy_constructor() {
    // Test case 1: Copy constructor with zeros
    Vec4ui original1(0);
    Vec4ui copy1(original1);
    for(int i = 0; i < 4; i++) {
        assert(copy1[i] == 0);
    }

    // Test case 2: Copy constructor with sequential values
    Vec4ui original2(1, 2, 3, 4);
    Vec4ui copy2(original2);
    for(int i = 0; i < 4; i++) {
        assert(copy2[i] == i + 1);
    }

    // Test case 3: Copy constructor with maximum values
    Vec4ui original3(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
    Vec4ui copy3(original3);
    for(int i = 0; i < 4; i++) {
        assert(copy3[i] == 0xFFFFFFFF);
    }

    // Test case 4: Copy constructor with mixed values
    Vec4ui original4(0x12345678, 0xABCDEF00, 0, 0xFFFFFFFF);
    Vec4ui copy4(original4);
    assert(copy4[0] == 0x12345678);
    assert(copy4[1] == 0xABCDEF00);
    assert(copy4[2] == 0);
    assert(copy4[3] == 0xFFFFFFFF);
    std::cout << "test_copy_constructor passed!\n";
}
void test_assignment_operator() {
    // Test case 1: Assign zeros
    uint32_t data1[4] = {0, 0, 0, 0};
    uint32x4_t x1 = vld1q_u32(data1);
    Vec4ui v1;
    v1 = x1;
    for(int i = 0; i < 4; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Assign sequential values
    uint32_t data2[4] = {1, 2, 3, 4};
    uint32x4_t x2 = vld1q_u32(data2);
    Vec4ui v2;
    v2 = x2;
    for(int i = 0; i < 4; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Assign maximum values
    uint32_t data3[4] = {0xFFFFFFFF, 0xFFFFFFFF, 
                         0xFFFFFFFF, 0xFFFFFFFF};
    uint32x4_t x3 = vld1q_u32(data3);
    Vec4ui v3;
    v3 = x3;
    for(int i = 0; i < 4; i++) {
        assert(v3[i] == 0xFFFFFFFF);
    }

    // Test case 4: Assign mixed values
    uint32_t data4[4] = {0x12345678, 0xABCDEF00,
                         0, 0xFFFFFFFF};
    uint32x4_t x4 = vld1q_u32(data4);
    Vec4ui v4;
    v4 = x4;
    assert(v4[0] == 0x12345678);
    assert(v4[1] == 0xABCDEF00);
    assert(v4[2] == 0);
    assert(v4[3] == 0xFFFFFFFF);
    std::cout << "test_assignment_operator passed!\n";
}
void test_type_cast_operator() {
    // Test case 1: Cast zero values
    Vec4ui v1(0);
    uint32x4_t x1 = v1;
    uint32_t data1[4];
    vst1q_u32(data1, x1);
    for(int i = 0; i < 4; i++) {
        assert(data1[i] == 0);
    }

    // Test case 2: Cast sequential values
    Vec4ui v2(1, 2, 3, 4);
    uint32x4_t x2 = v2;
    uint32_t data2[4];
    vst1q_u32(data2, x2);
    for(int i = 0; i < 4; i++) {
        assert(data2[i] == i + 1);
    }

    // Test case 3: Cast maximum values
    Vec4ui v3(0xFFFFFFFF);
    uint32x4_t x3 = v3;
    uint32_t data3[4];
    vst1q_u32(data3, x3);
    for(int i = 0; i < 4; i++) {
        assert(data3[i] == 0xFFFFFFFF);
    }

    // Test case 4: Cast mixed values
    Vec4ui v4(0x12345678, 0xABCDEF00, 0, 0xFFFFFFFF);
    uint32x4_t x4 = v4;
    uint32_t data4[4];
    vst1q_u32(data4, x4);
    assert(data4[0] == 0x12345678);
    assert(data4[1] == 0xABCDEF00);
    assert(data4[2] == 0);
    assert(data4[3] == 0xFFFFFFFF);

    std::cout << "test_type_cast_operator passed!\n";
}

void test_load() {
    // Test case 1: Load zeros
    uint32_t data1[4] = {0, 0, 0, 0};
    Vec4ui v1;
    v1.load(data1);
    for(int i = 0; i < 4; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Load sequential values 
    uint32_t data2[4] = {1, 2, 3, 4};
    Vec4ui v2;
    v2.load(data2);
    for(int i = 0; i < 4; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Load maximum values
    uint32_t data3[4] = {0xFFFFFFFF, 0xFFFFFFFF,
                         0xFFFFFFFF, 0xFFFFFFFF};
    Vec4ui v3;
    v3.load(data3);
    for(int i = 0; i < 4; i++) {
        assert(v3[i] == 0xFFFFFFFF);
    }

    // Test case 4: Load mixed values
    uint32_t data4[4] = {0x12345678, 0xABCDEF00,
                         0, 0xFFFFFFFF};
    Vec4ui v4;
    v4.load(data4);
    assert(v4[0] == 0x12345678);
    assert(v4[1] == 0xABCDEF00);
    assert(v4[2] == 0);
    assert(v4[3] == 0xFFFFFFFF);

    std::cout << "test_load passed!\n";
}
void test_load_a() {
    // Test case 1: Load aligned zeros
    alignas(16) uint32_t data1[4] = {0, 0, 0, 0};
    Vec4ui v1;
    v1.load_a(data1);
    for(int i = 0; i < 4; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Load aligned sequential values
    alignas(16) uint32_t data2[4] = {1, 2, 3, 4};
    Vec4ui v2;
    v2.load_a(data2);
    for(int i = 0; i < 4; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Load aligned maximum values
    alignas(16) uint32_t data3[4] = {0xFFFFFFFF, 0xFFFFFFFF,
                                    0xFFFFFFFF, 0xFFFFFFFF};
    Vec4ui v3;
    v3.load_a(data3);
    for(int i = 0; i < 4; i++) {
        assert(v3[i] == 0xFFFFFFFF);
    }

    // Test case 4: Load aligned mixed values
    alignas(16) uint32_t data4[4] = {0x12345678, 0xABCDEF00,
                                    0, 0xFFFFFFFF};
    Vec4ui v4;
    v4.load_a(data4);
    assert(v4[0] == 0x12345678);
    assert(v4[1] == 0xABCDEF00); 
    assert(v4[2] == 0);
    assert(v4[3] == 0xFFFFFFFF);

    std::cout << "test_load_a passed!\n";
}

void test_store() {
    // Test case 1: Store zeros
    uint32_t data1[4];
    Vec4ui v1(0);
    v1.store(data1);
    for(int i = 0; i < 4; i++) {
        assert(data1[i] == 0);
    }

    // Test case 2: Store sequential values
    uint32_t data2[4];
    Vec4ui v2(1, 2, 3, 4);
    v2.store(data2);
    for(int i = 0; i < 4; i++) {
        assert(data2[i] == i + 1);
    }

    // Test case 3: Store maximum values
    uint32_t data3[4];
    Vec4ui v3(0xFFFFFFFF);
    v3.store(data3);
    for(int i = 0; i < 4; i++) {
        assert(data3[i] == 0xFFFFFFFF);
    }

    // Test case 4: Store mixed values
    uint32_t data4[4];
    Vec4ui v4(0x12345678, 0xABCDEF00, 0, 0xFFFFFFFF);
    v4.store(data4);
    assert(data4[0] == 0x12345678);
    assert(data4[1] == 0xABCDEF00);
    assert(data4[2] == 0);
    assert(data4[3] == 0xFFFFFFFF);

    std::cout << "test_store passed!\n";
}
void test_store_a() {
    // Test case 1: Store aligned zeros
    alignas(16) uint32_t data1[4];
    Vec4ui v1(0);
    v1.store_a(data1);
    for(int i = 0; i < 4; i++) {
        assert(data1[i] == 0);
    }

    // Test case 2: Store aligned sequential values 
    alignas(16) uint32_t data2[4];
    Vec4ui v2(1, 2, 3, 4);
    v2.store_a(data2);
    for(int i = 0; i < 4; i++) {
        assert(data2[i] == i + 1);
    }

    // Test case 3: Store aligned maximum values
    alignas(16) uint32_t data3[4];
    Vec4ui v3(0xFFFFFFFF);
    v3.store_a(data3);
    for(int i = 0; i < 4; i++) {
        assert(data3[i] == 0xFFFFFFFF);
    }

    // Test case 4: Store aligned mixed values
    alignas(16) uint32_t data4[4];
    Vec4ui v4(0x12345678, 0xABCDEF00, 0, 0xFFFFFFFF);
    v4.store_a(data4);
    assert(data4[0] == 0x12345678);
    assert(data4[1] == 0xABCDEF00);
    assert(data4[2] == 0);
    assert(data4[3] == 0xFFFFFFFF);

    std::cout << "test_store_a passed!\n";
}
void test_load_partial() {
    // Test case 1: Load full vector (n = 4)
    uint32_t data1[4] = {1, 2, 3, 4};
    Vec4ui v1;
    v1.load_partial(4, data1);
    for(int i = 0; i < 4; i++) {
        assert(v1[i] == i + 1);
    }

    // Test case 2: Load zero elements (n = 0)
    uint32_t data2[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    Vec4ui v2;
    v2.load_partial(0, data2);
    for(int i = 0; i < 4; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: Load partial data (n = 2)
    uint32_t data3[4] = {0x12345678, 0xABCDEF00, 0xFFFFFFFF, 0xFFFFFFFF};
    Vec4ui v3;
    v3.load_partial(2, data3);
    assert(v3[0] == 0x12345678);
    assert(v3[1] == 0xABCDEF00);
    for(int i = 2; i < 4; i++) {
        assert(v3[i] == 0);
    }

    // Test case 4: Load with negative n
    uint32_t data4[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    Vec4ui v4;
    v4.load_partial(-1, data4);
    for(int i = 0; i < 4; i++) {
        assert(v4[i] == 0);
    }

    std::cout << "test_load_partial passed!\n";
}
void test_store_partial() {
    // Test case 1: Store full vector (n = 4)
    uint32_t data1[4] = {0};
    Vec4ui v1(1, 2, 3, 4);
    v1.store_partial(4, data1);
    for(int i = 0; i < 4; i++) {
        assert(data1[i] == i + 1);
    }

    // Test case 2: Store zero elements (n = 0)
    uint32_t data2[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    Vec4ui v2(1, 2, 3, 4);
    v2.store_partial(0, data2);
    for(int i = 0; i < 4; i++) {
        assert(data2[i] == 0xFFFFFFFF);
    }

    // Test case 3: Store partial data (n = 2)
    uint32_t data3[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    Vec4ui v3(0x12345678, 0xABCDEF00, 0, 0);
    v3.store_partial(2, data3);
    assert(data3[0] == 0x12345678);
    assert(data3[1] == 0xABCDEF00);
    assert(data3[2] == 0xFFFFFFFF);
    assert(data3[3] == 0xFFFFFFFF);

    // Test case 4: Store with negative n
    uint32_t data4[4] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
    Vec4ui v4(1, 2, 3, 4);
    v4.store_partial(-1, data4);
    for(int i = 0; i < 4; i++) {
        assert(data4[i] == 0xFFFFFFFF);
    }

    std::cout << "test_store_partial passed!\n";
}
void test_cutoff() {
    // Test case 1: n >= 4 (no cutoff)
    Vec4ui v1(1, 2, 3, 4);
    v1.cutoff(4);
    for(int i = 0; i < 4; i++) {
        assert(v1[i] == i + 1);
    }
    
    v1.cutoff(5);
    for(int i = 0; i < 4; i++) {
        assert(v1[i] == i + 1);
    }

    // Test case 2: n = 2 (cutoff half)
    Vec4ui v2(1, 2, 3, 4);
    v2.cutoff(2);
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == i + 1);
    }
    for(int i = 2; i < 4; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: n = 0 (all zeros)
    Vec4ui v3(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
    v3.cutoff(0);
    for(int i = 0; i < 4; i++) {
        assert(v3[i] == 0);
    }

    // Test case 4: n = 1 (keep only first element)
    Vec4ui v4(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
    v4.cutoff(1);
    assert(v4[0] == 0xFFFF);
    for(int i = 1; i < 4; i++) {
        assert(v4[i] == 0);
    }

    // Test case 5: n < 0 (should zero all elements)
    Vec4ui v5(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
    v5.cutoff(-1);
    for(int i = 0; i < 4; i++) {
        assert(v5[i] == 0);
    }

    // Test case 6: n = 3 (keep all but last element)
    Vec4ui v6(1, 2, 3, 4);
    v6.cutoff(3);
    for(int i = 0; i < 3; i++) {
        assert(v6[i] == i + 1);
    }
    assert(v6[3] == 0);

    // Test case 7: Multiple cutoff operations
    Vec4ui v7(1, 2, 3, 4);
    v7.cutoff(3);
    v7.cutoff(2);  // Should further reduce to 2 elements
    for(int i = 0; i < 2; i++) {
        assert(v7[i] == i + 1);
    }
    for(int i = 2; i < 4; i++) {
        assert(v7[i] == 0);
    }

    std::cout << "test_cutoff passed!\n";
}
void test_and_assign_operator() {
    // Test case 1: AND with all bits set
    Vec4ui a(0xFFFF);
    Vec4ui b(0x5555);
    a &= b;
    for(int i = 0; i < 4; i++) {
        assert(a[i] == 0x5555);
    }

    // Test case 2: AND with zero
    Vec4ui c(0xFFFF);
    Vec4ui d(0);
    c &= d;
    for(int i = 0; i < 4; i++) {
        assert(c[i] == 0);
    }

    // Test case 3: AND with alternating patterns
    Vec4ui e(0xAAAA, 0x5555, 0xFFFF, 0x0000);
    Vec4ui f(0x5555, 0xAAAA, 0xFFFF, 0xFFFF);
    e &= f;
    assert(e[0] == 0x0000); // 0xAAAA & 0x5555
    assert(e[1] == 0x0000); // 0x5555 & 0xAAAA
    assert(e[2] == 0xFFFF); // 0xFFFF & 0xFFFF
    assert(e[3] == 0x0000); // 0x0000 & 0xFFFF

    // Test case 4: AND with same value
    Vec4ui g(0xAAAA);
    Vec4ui h(0xAAAA);
    g &= h;
    for(int i = 0; i < 4; i++) {
        assert(g[i] == 0xAAAA);
    }

    std::cout << "test_and_equals_operator passed!\n";
}
void test_insert() {
    // Test case 1: Insert at each valid index
    Vec4ui v1(0);
    for(int i = 0; i < 4; i++) {
        v1 = v1.insert(i, i + 1);
        assert(v1[i] == i + 1);
    }

    // Test case 2: Insert with index wrapping (index & 0x03)
    Vec4ui v2(0);
    v2 = v2.insert(4, 1);  // Should wrap to index 0
    assert(v2[0] == 1);
    v2 = v2.insert(5, 2);  // Should wrap to index 1
    assert(v2[1] == 2);
    v2 = v2.insert(7, 3); // Should wrap to index 3
    assert(v2[3] == 3);

    // Test case 3: Insert maximum values
    Vec4ui v3(0);
    for(int i = 0; i < 4; i++) {
        v3 = v3.insert(i, 0xFFFFFFFF);
        assert(v3[i] == 0xFFFFFFFF);
    }

    // Test case 4: Insert with negative indices (should wrap)
    Vec4ui v4(0);
    v4 = v4.insert(-1, 1);  // Should wrap to index 3
    assert(v4[3] == 1);
    v4 = v4.insert(-2, 2);  // Should wrap to index 2
    assert(v4[2] == 2);
    v4 = v4.insert(-4, 4);  // Should wrap to index 0
    assert(v4[0] == 4);

    std::cout << "test_insert passed!\n";
}
void test_extract() {
    // Test case 1: Extract from sequence
    Vec4ui v1(1, 2, 3, 4);
    for(int i = 0; i < 4; i++) {
        assert(v1.extract(i) == i + 1);
    }

    // Test case 2: Extract with index wrapping (index & 0x03)
    Vec4ui v2(1, 2, 3, 4);
    assert(v2.extract(4) == 1);   // Should wrap to index 0
    assert(v2.extract(5) == 2);   // Should wrap to index 1
    assert(v2.extract(7) == 4);   // Should wrap to index 3

    // Test case 3: Extract maximum values
    Vec4ui v3(0xFFFFFFFF);
    for(int i = 0; i < 4; i++) {
        assert(v3.extract(i) == 0xFFFFFFFF);
    }

    // Test case 4: Extract with negative indices (should wrap)
    Vec4ui v4(1, 2, 3, 4);
    assert(v4.extract(-1) == 4);  // Should wrap to index 3
    assert(v4.extract(-2) == 3);  // Should wrap to index 2
    assert(v4.extract(-4) == 1);  // Should wrap to index 0

    // Test case 5: Extract from mixed values
    Vec4ui v5(0x12345678, 0xABCDEF00, 0, 0xFFFFFFFF);
    assert(v5.extract(0) == 0x12345678);
    assert(v5.extract(1) == 0xABCDEF00);
    assert(v5.extract(2) == 0);
    assert(v5.extract(3) == 0xFFFFFFFF);
    assert(v5.extract(4) == 0x12345678);  // Wraps to index 0
    assert(v5.extract(5) == 0xABCDEF00);  // Wraps to index 1
    assert(v5.extract(6) == 0);           // Wraps to index 2
    assert(v5.extract(7) == 0xFFFFFFFF);  // Wraps to index 3

    std::cout << "test_extract passed!\n";
}
void test_array_subscript_operator() {
    // Test case 1: Access sequential values
    Vec4ui v1(1, 2, 3, 4);
    for(int i = 0; i < 4; i++) {
        assert(v1[i] == i + 1);
    }

    // Test case 2: Access with index wrapping (index & 0x03)
    Vec4ui v2(1, 2, 3, 4);
    assert(v2[4] == 1);   // Should wrap to index 0
    assert(v2[5] == 2);   // Should wrap to index 1
    assert(v2[7] == 4);   // Should wrap to index 3

    // Test case 3: Access maximum values
    Vec4ui v3(0xFFFFFFFF);
    for(int i = 0; i < 4; i++) {
        assert(v3[i] == 0xFFFFFFFF);
    }

    // Test case 4: Access with negative indices (should wrap)
    Vec4ui v4(1, 2, 3, 4);
    assert(v4[-1] == 4);  // Should wrap to index 3
    assert(v4[-2] == 3);  // Should wrap to index 2
    assert(v4[-4] == 1);  // Should wrap to index 0

    // Test case 5: Access mixed values
    Vec4ui v5(0x12345678, 0xABCDEF00, 0, 0xFFFFFFFF);
    assert(v5[0] == 0x12345678);
    assert(v5[1] == 0xABCDEF00);
    assert(v5[2] == 0);
    assert(v5[3] == 0xFFFFFFFF);

    std::cout << "test_array_subscript_operator passed!\n";
}

void test_add_operator() {
    // Test case 1: Basic addition
    Vec4ui a1(1, 2, 3, 4);
    Vec4ui b1(1, 1, 1, 1);
    Vec4ui c1 = a1 + b1;
    for(int i = 0; i < 4; i++) {
        assert(c1[i] == i + 2);
    }

    // Test case 2: Addition with zeros
    Vec4ui a2(1, 2, 3, 4);
    Vec4ui b2(0);
    Vec4ui c2 = a2 + b2;
    for(int i = 0; i < 4; i++) {
        assert(c2[i] == i + 1);
    }

    // Test case 3: Addition with saturation
    Vec4ui a3(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
    Vec4ui b3(1, 1, 1, 1);
    Vec4ui c3 = a3 + b3;
    for(int i = 0; i < 4; i++) {
        assert(c3[i] == 0xFFFFFFFF); // Should saturate at maximum value
    }

    // Test case 4: Mixed value addition
    Vec4ui a4(0x10000000, 0x20000000, 0x30000000, 0x40000000);
    Vec4ui b4(0x01000000, 0x02000000, 0x03000000, 0x04000000);
    Vec4ui c4 = a4 + b4;
    assert(c4[0] == 0x11000000);
    assert(c4[1] == 0x22000000);
    assert(c4[2] == 0x33000000);
    assert(c4[3] == 0x44000000);

    std::cout << "test_add_operator passed!\n";
}
void test_add_assign_operator() {
    // Test case 1: Basic addition
    Vec4ui a1(1, 2, 3, 4);
    Vec4ui b1(1, 1, 1, 1);
    a1 += b1;
    for(int i = 0; i < 4; i++) {
        assert(a1[i] == i + 2);
    }

    // Test case 2: Addition with zeros 
    Vec4ui a2(1, 2, 3, 4);
    Vec4ui b2(0);
    a2 += b2;
    for(int i = 0; i < 4; i++) {
        assert(a2[i] == i + 1);
    }

    // Test case 3: Addition with saturation
    Vec4ui a3(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
    Vec4ui b3(1, 1, 1, 1);
    a3 += b3;
    for(int i = 0; i < 4; i++) {
        assert(a3[i] == 0xFFFFFFFF); // Should saturate at maximum value
    }

    // Test case 4: Mixed value addition
    Vec4ui a4(0x10000000, 0x20000000, 0x30000000, 0x40000000);
    Vec4ui b4(0x01000000, 0x02000000, 0x03000000, 0x04000000);
    a4 += b4;
    assert(a4[0] == 0x11000000);
    assert(a4[1] == 0x22000000);
    assert(a4[2] == 0x33000000);
    assert(a4[3] == 0x44000000);

    std::cout << "test_add_equals_operator passed!\n";
}
void test_postfix_increment_operator() {
    // Test case 1: Basic increment
    Vec4ui a1(1, 2, 3, 4);
    Vec4ui b1 = a1++;
    // Check original values were returned
    for(int i = 0; i < 4; i++) {
        assert(b1[i] == i + 1);
    }
    // Check values were incremented
    for(int i = 0; i < 4; i++) {
        assert(a1[i] == i + 2);
    }

    // Test case 2: Increment from zero
    Vec4ui a2(0);
    Vec4ui b2 = a2++;
    // Check original values were returned
    for(int i = 0; i < 4; i++) {
        assert(b2[i] == 0);
    }
    // Check values were incremented
    for(int i = 0; i < 4; i++) {
        assert(a2[i] == 1);
    }

    // Test case 3: Increment with saturation
    Vec4ui a3(0xFFFFFFFF);
    Vec4ui b3 = a3++;
    // Check original values were returned
    for(int i = 0; i < 4; i++) {
        assert(b3[i] == 0xFFFFFFFF);
    }
    // Check values remained at maximum
    for(int i = 0; i < 4; i++) {
        assert(a3[i] == 0xFFFFFFFF);  // Should saturate at maximum value
    }

    // Test case 4: Multiple increments
    Vec4ui a4(0x1000);
    Vec4ui b4 = a4++;
    Vec4ui c4 = a4++;
    // Check original values were returned
    for(int i = 0; i < 4; i++) {
        assert(b4[i] == 0x1000);
        assert(c4[i] == 0x1001);
    }
    // Check final values after both increments
    for(int i = 0; i < 4; i++) {
        assert(a4[i] == 0x1002);
    }

    std::cout << "test_postfix_increment_operator passed!\n";
}
void test_prefix_increment_operator() {
    // Test case 1: Basic increment
    Vec4ui a1(1, 2, 3, 4);
    Vec4ui& b1 = ++a1;
    // Check values were incremented
    for(int i = 0; i < 4; i++) {
        assert(a1[i] == i + 2);
        assert(b1[i] == i + 2); // Reference should point to incremented value
    }
    // Verify b1 is reference to a1
    assert(&b1 == &a1);

    // Test case 2: Increment from zero
    Vec4ui a2(0);
    Vec4ui& b2 = ++a2;
    // Check values were incremented
    for(int i = 0; i < 4; i++) {
        assert(a2[i] == 1);
        assert(b2[i] == 1); // Reference should point to incremented value
    }
    // Verify b2 is reference to a2  
    assert(&b2 == &a2);

    // Test case 3: Increment with saturation
    Vec4ui a3(0xFFFFFFFF);
    Vec4ui& b3 = ++a3;
    // Check values remained at maximum
    for(int i = 0; i < 4; i++) {
        assert(a3[i] == 0xFFFFFFFF); // Should saturate at maximum value
        assert(b3[i] == 0xFFFFFFFF);
    }
    // Verify b3 is reference to a3
    assert(&b3 == &a3);

    // Test case 4: Multiple increments
    Vec4ui a4(0x1000);
    Vec4ui& b4 = ++(++a4);
    // Check values after both increments
    for(int i = 0; i < 4; i++) {
        assert(a4[i] == 0x1002);
        assert(b4[i] == 0x1002);
    }
    // Verify b4 is reference to a4
    assert(&b4 == &a4);

    std::cout << "test_prefix_increment_operator passed!\n";
}

void test_subtract_operator() {
    // Test case 1: Basic subtraction
    Vec4ui a1(10, 11, 12, 13);
    Vec4ui b1(1, 1, 1, 1);
    Vec4ui c1 = a1 - b1;
    for(int i = 0; i < 4; i++) {
        assert(c1[i] == 9 + i);
    }

    // Test case 2: Subtraction with zeros
    Vec4ui a2(1, 2, 3, 4);
    Vec4ui b2(0);
    Vec4ui c2 = a2 - b2;
    for(int i = 0; i < 4; i++) {
        assert(c2[i] == i + 1);
    }

    // Test case 3: Subtraction with saturation (prevent underflow)
    Vec4ui a3(0, 0, 0, 0);
    Vec4ui b3(1, 1, 1, 1);
    Vec4ui c3 = a3 - b3;
    for(int i = 0; i < 4; i++) {
        assert(c3[i] == 0); // Should saturate at minimum value
    }

    // Test case 4: Mixed value subtraction
    Vec4ui a4(0x1100, 0x2200, 0x3300, 0x4400);
    Vec4ui b4(0x0100, 0x0200, 0x0300, 0x0400);
    Vec4ui c4 = a4 - b4;
    assert(c4[0] == 0x1000);
    assert(c4[1] == 0x2000);
    assert(c4[2] == 0x3000);
    assert(c4[3] == 0x4000);

    std::cout << "test_subtract_operator passed!\n";
}
void test_subtract_equals_operator() {
    // Test case 1: Basic subtraction
    Vec4ui a1(10, 11, 12, 13);
    Vec4ui b1(1, 1, 1, 1);
    a1 -= b1;
    for(int i = 0; i < 4; i++) {
        assert(a1[i] == 9 + i);
    }

    // Test case 2: Subtraction with zeros
    Vec4ui a2(1, 2, 3, 4);
    Vec4ui b2(0);
    a2 -= b2;
    for(int i = 0; i < 4; i++) {
        assert(a2[i] == i + 1);
    }

    // Test case 3: Subtraction with saturation
    Vec4ui a3(0, 0, 0, 0);
    Vec4ui b3(1, 1, 1, 1);
    a3 -= b3;
    for(int i = 0; i < 4; i++) {
        assert(a3[i] == 0); // Should saturate at minimum value
    }

    // Test case 4: Mixed value subtraction
    Vec4ui a4(0x1100, 0x2200, 0x3300, 0x4400);
    Vec4ui b4(0x0100, 0x0200, 0x0300, 0x0400);
    a4 -= b4;
    assert(a4[0] == 0x1000);
    assert(a4[1] == 0x2000);
    assert(a4[2] == 0x3000);
    assert(a4[3] == 0x4000);

    std::cout << "test_subtract_equals_operator passed!\n";
}
void test_postfix_decrement_operator() {
    // Test case 1: Basic decrement
    Vec4ui a1(2, 3, 4, 5);
    Vec4ui b1 = a1--;
    // Check original values were returned
    for(int i = 0; i < 4; i++) {
        assert(b1[i] == i + 2);
    }
    // Check values were decremented
    for(int i = 0; i < 4; i++) {
        assert(a1[i] == i + 1);
    }

    // Test case 2: Decrement towards zero
    Vec4ui a2(1, 1, 1, 1);
    Vec4ui b2 = a2--;
    // Check original values were returned
    for(int i = 0; i < 4; i++) {
        assert(b2[i] == 1);
    }
    // Check values were decremented to zero
    for(int i = 0; i < 4; i++) {
        assert(a2[i] == 0);
    }

    // Test case 3: Decrement with saturation
    Vec4ui a3(0);
    Vec4ui b3 = a3--;
    // Check original values were returned
    for(int i = 0; i < 4; i++) {
        assert(b3[i] == 0);
    }
    // Check values remained at minimum
    for(int i = 0; i < 4; i++) {
        assert(a3[i] == 0); // Should saturate at minimum value
    }

    std::cout << "test_postfix_decrement_operator passed!\n";
}
void test_prefix_decrement_operator() {
    // Test case 1: Basic decrement
    Vec4ui a1(2, 3, 4, 5);
    Vec4ui& b1 = --a1;
    // Check values were decremented
    for(int i = 0; i < 4; i++) {
        assert(a1[i] == i + 1);
        assert(b1[i] == i + 1); // Reference should point to decremented value
    }
    // Verify b1 is reference to a1
    assert(&b1 == &a1);

    // Test case 2: Decrement towards zero
    Vec4ui a2(1, 1, 1, 1);
    Vec4ui& b2 = --a2;
    // Check values were decremented to zero
    for(int i = 0; i < 4; i++) {
        assert(a2[i] == 0);
        assert(b2[i] == 0);
    }
    // Verify b2 is reference to a2
    assert(&b2 == &a2);

    // Test case 3: Decrement with saturation
    Vec4ui a3(0);
    Vec4ui& b3 = --a3;
    // Check values remained at minimum
    for(int i = 0; i < 4; i++) {
        assert(a3[i] == 0); // Should saturate at minimum value
        assert(b3[i] == 0);
    }
    // Verify b3 is reference to a3
    assert(&b3 == &a3);

    std::cout << "test_prefix_decrement_operator passed!\n";
}

void test_multiply_operator() {
    // Test case 1: Basic multiplication
    Vec4ui a1(1, 2, 3, 4);
    Vec4ui b1(2);
    Vec4ui c1 = a1 * b1;
    for(int i = 0; i < 4; i++) {
        assert(c1[i] == (i + 1) * 2);
    }

    // Test case 2: Multiplication with zero
    Vec4ui a2(1, 2, 3, 4);
    Vec4ui b2(0);
    Vec4ui c2 = a2 * b2;
    for(int i = 0; i < 4; i++) {
        assert(c2[i] == 0);
    }

    // Test case 3: Multiplication with ones (identity)
    Vec4ui a3(1, 2, 3, 4);
    Vec4ui b3(1);
    Vec4ui c3 = a3 * b3;
    for(int i = 0; i < 4; i++) {
        assert(c3[i] == i + 1);
    }

    // Test case 4: Test with larger numbers
    Vec4ui a4(100, 200, 300, 400);
    Vec4ui b4(3);
    Vec4ui c4 = a4 * b4;
    assert(c4[0] == 300);
    assert(c4[1] == 600);
    assert(c4[2] == 900);
    assert(c4[3] == 1200);

    // Test case 5: Test multiplication with large values
    Vec4ui a5(0xFFFFFFFF, 0x80000000, 0x40000000, 0x20000000);
    Vec4ui b5(2);
    Vec4ui c5 = a5 * b5;
    assert(c5[0] == 0xFFFFFFFE);
    assert(c5[1] == 0x00000000); // 0x80000000 * 2 overflows to 0
    assert(c5[2] == 0x80000000);
    assert(c5[3] == 0x40000000);

    std::cout << "test_multiply_operator passed!\n";
}
void test_multiply_equals_operator() {
    // Test case 1: Basic multiplication
    Vec4ui a1(1, 2, 3, 4);
    Vec4ui b1(2);
    a1 *= b1;
    for(int i = 0; i < 4; i++) {
        assert(a1[i] == (i + 1) * 2);
    }

    // Test case 2: Multiplication with zero
    Vec4ui a2(1, 2, 3, 4);
    Vec4ui b2(0);
    a2 *= b2;
    for(int i = 0; i < 4; i++) {
        assert(a2[i] == 0);
    }

    // Test case 3: Multiplication with ones (identity)
    Vec4ui a3(1, 2, 3, 4);
    Vec4ui b3(1);
    a3 *= b3;
    for(int i = 0; i < 4; i++) {
        assert(a3[i] == i + 1);
    }

    // Test case 4: Test with larger numbers
    Vec4ui a4(100, 200, 300, 400);
    Vec4ui b4(3);
    a4 *= b4;
    assert(a4[0] == 300);
    assert(a4[1] == 600);
    assert(a4[2] == 900);
    assert(a4[3] == 1200);

    // Test case 5: Test multiplication near maximum values
    Vec4ui a5(0xFFFFFFFF, 0x80000000, 0x40000000, 0x20000000);
    Vec4ui b5(2);
    a5 *= b5;
    // Check multiplication results
    assert(a5[0] == 0xFFFFFFFE);  // 0xFFFFFFFF * 2 = 0x1FFFFFFFE truncated
    assert(a5[1] == 0x00000000);  // 0x80000000 * 2 = 0x100000000 truncated
    assert(a5[2] == 0x80000000);  // 0x40000000 * 2 = 0x80000000
    assert(a5[3] == 0x40000000);  // 0x20000000 * 2 = 0x40000000

    std::cout << "test_multiply_equals_operator passed!\n";
}
void test_shift_left_operator() {
    // Test case 1: Basic left shift by 1
    Vec4ui a1(1, 2, 4, 8);
    Vec4ui b1 = a1 << 1;
    for(int i = 0; i < 4; i++) {
        assert(b1[i] == (a1[i] << 1));
    }

    // Test case 2: Left shift by 4
    Vec4ui a2(0x1111, 0x2222, 0x3333, 0x4444);
    Vec4ui b2 = a2 << 4;
    for(int i = 0; i < 4; i++) {
        assert(b2[i] == (a2[i] << 4));
    }

    // Test case 3: Left shift by 8 (half the bits)
    Vec4ui a3(0x00FF, 0xFF00, 0x0F0F, 0xF0F0);
    Vec4ui b3 = a3 << 8;
    for(int i = 0; i < 4; i++) {
        assert(b3[i] == (a3[i] << 8));
    }

    // Test case 4: Left shift that clears all bits
    Vec4ui a4(0xFFFFFFFF);
    Vec4ui b4 = a4 << 32;
    for(int i = 0; i < 4; i++) {
        assert(b4[i] == 0);
    }

    std::cout << "test_shift_left_operator passed!\n";
}
void test_shift_left_equals_operator() {
    // Test case 1: Basic left shift by 1
    Vec4ui a1(1, 2, 4, 8);
    Vec4ui expected1 = a1 << 1;
    a1 <<= 1;
    for(int i = 0; i < 4; i++) {
        assert(a1[i] == expected1[i]);
    }

    // Test case 2: Left shift by 4
    Vec4ui a2(0x1111, 0x2222, 0x3333, 0x4444);
    Vec4ui expected2 = a2 << 4;
    a2 <<= 4;
    for(int i = 0; i < 4; i++) {
        assert(a2[i] == expected2[i]);
    }

    // Test case 3: Left shift by 8
    Vec4ui a3(0x00FF, 0xFF00, 0x0F0F, 0xF0F0);
    Vec4ui expected3 = a3 << 8;
    a3 <<= 8;
    for(int i = 0; i < 4; i++) {
        assert(a3[i] == expected3[i]);
    }

    // Test case 4: Left shift that clears all bits
    Vec4ui a4(0xFFFF);
    a4 <<= 32;
    for(int i = 0; i < 4; i++) {
        assert(a4[i] == 0);
    }

    std::cout << "test_shift_left_equals_operator passed!\n";
}
void test_shift_right_operator() {
    // Test case 1: Basic right shift by 1
    Vec4ui a1(2, 4, 8, 16);
    Vec4ui b1 = a1 >> 1;
    for(int i = 0; i < 4; i++) {
        assert(b1[i] == (a1[i] >> 1));
    }

    // Test case 2: Right shift by 4
    Vec4ui a2(0x1110, 0x2220, 0x3330, 0x4440);
    Vec4ui b2 = a2 >> 4;
    for(int i = 0; i < 4; i++) {
        assert(b2[i] == (a2[i] >> 4));
    }

    // Test case 3: Right shift by 8 (half the bits)
    Vec4ui a3(0xFF00, 0x00FF, 0xF0F0, 0x0F0F);
    Vec4ui b3 = a3 >> 8;
    for(int i = 0; i < 4; i++) {
        assert(b3[i] == (a3[i] >> 8));
    }

    // Test case 4: Right shift that clears all bits
    Vec4ui a4(0xFFFF);
    Vec4ui b4 = a4 >> 16;
    for(int i = 0; i < 4; i++) {
        assert(b4[i] == 0);
    }

    std::cout << "test_shift_right_operator passed!\n";
}
void test_shift_right_equals_operator() {
    // Test case 1: Basic right shift by 1
    Vec4ui a1(2, 4, 8, 16);
    Vec4ui expected1 = a1 >> 1;
    a1 >>= 1;
    for(int i = 0; i < 4; i++) {
        assert(a1[i] == expected1[i]);
    }

    // Test case 2: Right shift by 4
    Vec4ui a2(0x1110, 0x2220, 0x3330, 0x4440);
    Vec4ui expected2 = a2 >> 4;
    a2 >>= 4;
    for(int i = 0; i < 4; i++) {
        assert(a2[i] == expected2[i]);
    }

    // Test case 3: Right shift by 8
    Vec4ui a3(0xFF00, 0x00FF, 0xF0F0, 0x0F0F);
    Vec4ui expected3 = a3 >> 8;
    a3 >>= 8;
    for(int i = 0; i < 4; i++) {
        assert(a3[i] == expected3[i]);
    }

    // Test case 4: Right shift that clears all bits
    Vec4ui a4(0xFFFF);
    a4 >>= 32;
    for(int i = 0; i < 4; i++) {
        assert(a4[i] == 0);
    }

    std::cout << "test_shift_right_equals_operator passed!\n";
}

// Comparison Operation Tests
void test_operator_equal() {
    // Test case 1: Equal values
    Vec4ui a1(1, 1, 1, 1);
    Vec4ui b1(1, 1, 1, 1);
    Vec4ui result1 = (a1 == b1);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == 0xFFFFFFFF); // All bits set indicates true
    }

    // Test case 2: Unequal values
    Vec4ui a2(1, 2, 3, 4);
    Vec4ui b2(4, 3, 2, 1);
    Vec4ui result2 = (a2 == b2);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0); // All bits clear indicates false
    }

    // Test case 3: Mix of equal and unequal values
    Vec4ui a3(1, 2, 1, 2);
    Vec4ui b3(1, 1, 1, 1);
    Vec4ui result3 = (a3 == b3);
    assert(result3[0] == 0xFFFFFFFF); // Equal
    assert(result3[1] == 0);          // Unequal
    assert(result3[2] == 0xFFFFFFFF); // Equal
    assert(result3[3] == 0);          // Unequal

    // Test case 4: Compare with zero
    Vec4ui a4(0, 0, 1, 1);
    Vec4ui b4(0);
    Vec4ui result4 = (a4 == b4);
    assert(result4[0] == 0xFFFFFFFF); // Equal to zero
    assert(result4[1] == 0xFFFFFFFF); // Equal to zero
    assert(result4[2] == 0);          // Not equal to zero
    assert(result4[3] == 0);          // Not equal to zero

    std::cout << "test_operator_equal passed!\n";
}
void test_operator_not_equal() {
    // Test case 1: All values equal (should return all false)
    Vec4ui a1(1, 1, 1, 1);
    Vec4ui b1(1, 1, 1, 1);
    Vec4ui result1 = (a1 != b1);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == 0); // All bits clear indicates false (values are equal)
    }

    // Test case 2: All values unequal (should return all true)
    Vec4ui a2(1, 2, 3, 4);
    Vec4ui b2(4, 3, 2, 1);
    Vec4ui result2 = (a2 != b2);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0xFFFFFFFF); // All bits set indicates true (values are unequal)
    }

    // Test case 3: Mix of equal and unequal values
    Vec4ui a3(1, 2, 1, 2);
    Vec4ui b3(1, 1, 1, 1);
    Vec4ui result3 = (a3 != b3);
    assert(result3[0] == 0);          // Equal
    assert(result3[1] == 0xFFFFFFFF); // Unequal
    assert(result3[2] == 0);          // Equal
    assert(result3[3] == 0xFFFFFFFF); // Unequal

    // Test case 4: Compare with zero
    Vec4ui a4(0, 0, 1, 1);
    Vec4ui b4(0);
    Vec4ui result4 = (a4 != b4);
    assert(result4[0] == 0);          // Equal to zero
    assert(result4[1] == 0);          // Equal to zero
    assert(result4[2] == 0xFFFFFFFF); // Not equal to zero
    assert(result4[3] == 0xFFFFFFFF); // Not equal to zero

    // Test case 5: Compare maximum values
    Vec4ui a5(0xFFFFFFFF);
    Vec4ui b5(0xFFFFFFFF);
    Vec4ui result5 = (a5 != b5);
    for(int i = 0; i < 4; i++) {
        assert(result5[i] == 0); // All elements are equal
    }

    // Test case 6: Compare with mixed maximum values
    Vec4ui a6(0xFFFFFFFF, 0, 0xFFFFFFFF, 0);
    Vec4ui b6(0, 0xFFFFFFFF, 0, 0xFFFFFFFF);
    Vec4ui result6 = (a6 != b6);
    for(int i = 0; i < 4; i++) {
        assert(result6[i] == 0xFFFFFFFF); // All elements are unequal
    }

    std::cout << "test_operator_not_equal passed!\n";
}
void test_greater_than_operator() {
    // Test case 1: Basic greater than comparison
    Vec4ui a1(2, 3, 4, 5);
    Vec4ui b1(1, 2, 3, 4);
    Vec4ui result1 = (a1 > b1);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == 0xFFFFFFFF); // All elements in a1 are greater than b1
    }

    // Test case 2: Basic less than comparison
    Vec4ui a2(1, 2, 3, 4);
    Vec4ui b2(2, 3, 4, 5);
    Vec4ui result2 = (a2 > b2);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0); // All elements in a2 are less than b2
    }

    // Test case 3: Equal values comparison
    Vec4ui a3(1, 1, 1, 1);
    Vec4ui b3(1, 1, 1, 1);
    Vec4ui result3 = (a3 > b3);
    for(int i = 0; i < 4; i++) {
        assert(result3[i] == 0); // Equal elements should return false
    }

    // Test case 4: Mixed comparisons
    Vec4ui a4(5, 2, 7, 4);
    Vec4ui b4(3, 4, 5, 6);
    Vec4ui result4 = (a4 > b4);
    assert(result4[0] == 0xFFFFFFFF); // 5 > 3
    assert(result4[1] == 0);          // 2 < 4
    assert(result4[2] == 0xFFFFFFFF); // 7 > 5
    assert(result4[3] == 0);          // 4 < 6

    // Test case 5: Compare with zero
    Vec4ui a5(1, 2, 0, 4);
    Vec4ui b5(0);
    Vec4ui result5 = (a5 > b5);
    assert(result5[0] == 0xFFFFFFFF); // 1 > 0
    assert(result5[1] == 0xFFFFFFFF); // 2 > 0
    assert(result5[2] == 0);          // 0 = 0
    assert(result5[3] == 0xFFFFFFFF); // 4 > 0

    // Test case 6: Compare with maximum values
    Vec4ui a6(0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFE);
    Vec4ui b6(0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFF);
    Vec4ui result6 = (a6 > b6);
    for(int i = 0; i < 4; i += 2) {
        assert(result6[i] == 0xFFFFFFFF);   // 0xFFFFFFFF > 0xFFFFFFFE
        assert(result6[i+1] == 0);          // 0xFFFFFFFE < 0xFFFFFFFF
    }

    std::cout << "test_greater_than_operator passed!\n";
}
void test_less_than_operator() {
    // Test case 1: Basic less than comparison
    Vec4ui a1(1, 2, 3, 4);
    Vec4ui b1(2, 3, 4, 5);
    Vec4ui result1 = (a1 < b1);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == 0xFFFFFFFF); // All elements in a1 are less than b1
    }

    // Test case 2: Basic greater than comparison
    Vec4ui a2(2, 3, 4, 5);
    Vec4ui b2(1, 2, 3, 4);
    Vec4ui result2 = (a2 < b2);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0); // All elements in a2 are greater than b2
    }

    // Test case 3: Equal values comparison
    Vec4ui a3(1, 1, 1, 1);
    Vec4ui b3(1, 1, 1, 1);
    Vec4ui result3 = (a3 < b3);
    for(int i = 0; i < 4; i++) {
        assert(result3[i] == 0); // Equal elements should return false
    }

    // Test case 4: Mixed comparisons
    Vec4ui a4(3, 4, 5, 6);
    Vec4ui b4(5, 2, 7, 4);
    Vec4ui result4 = (a4 < b4);
    assert(result4[0] == 0xFFFFFFFF); // 3 < 5
    assert(result4[1] == 0);          // 4 > 2
    assert(result4[2] == 0xFFFFFFFF); // 5 < 7
    assert(result4[3] == 0);          // 6 > 4

    // Test case 5: Compare with zero
    Vec4ui a5(0, 1, 0, 2);
    Vec4ui b5(1, 0, 2, 0);
    Vec4ui result5 = (a5 < b5);
    assert(result5[0] == 0xFFFFFFFF); // 0 < 1
    assert(result5[1] == 0);          // 1 > 0
    assert(result5[2] == 0xFFFFFFFF); // 0 < 2
    assert(result5[3] == 0);          // 2 > 0

    // Test case 6: Compare with maximum values
    Vec4ui a6(0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFF);
    Vec4ui b6(0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFE);
    Vec4ui result6 = (a6 < b6);
    for(int i = 0; i < 4; i += 2) {
        assert(result6[i] == 0xFFFFFFFF);   // 0xFFFFFFFE < 0xFFFFFFFF
        assert(result6[i+1] == 0);          // 0xFFFFFFFF > 0xFFFFFFFE
    }

    std::cout << "test_less_than_operator passed!\n";
}
void test_greater_than_or_equal_operator() {
    // Test case 1: Greater than comparison
    Vec4ui a1(2, 3, 4, 5);
    Vec4ui b1(1, 2, 3, 4);
    Vec4ui result1 = (a1 >= b1);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == 0xFFFFFFFF); // All elements in a1 are greater than b1
    }

    // Test case 2: Equal values comparison
    Vec4ui a2(1, 1, 1, 1);
    Vec4ui b2(1, 1, 1, 1);
    Vec4ui result2 = (a2 >= b2);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0xFFFFFFFF); // Equal elements should return true
    }

    // Test case 3: Less than comparison
    Vec4ui a3(1, 2, 3, 4);
    Vec4ui b3(2, 3, 4, 5);
    Vec4ui result3 = (a3 >= b3);
    for(int i = 0; i < 4; i++) {
        assert(result3[i] == 0); // All elements in a3 are less than b3
    }

    // Test case 4: Mixed comparisons
    Vec4ui a4(5, 2, 7, 4);
    Vec4ui b4(5, 4, 5, 6);
    Vec4ui result4 = (a4 >= b4);
    assert(result4[0] == 0xFFFFFFFF); // 5 = 5
    assert(result4[1] == 0);          // 2 < 4
    assert(result4[2] == 0xFFFFFFFF); // 7 > 5
    assert(result4[3] == 0);          // 4 < 6

    // Test case 5: Compare with zero
    Vec4ui a5(1, 0, 2, 0);
    Vec4ui b5(0);
    Vec4ui result5 = (a5 >= b5);
    for(int i = 0; i < 4; i++) {
        if(a5[i] == 0) {
            assert(result5[i] == 0xFFFFFFFF); // Equal to zero
        } else {
            assert(result5[i] == 0xFFFFFFFF); // Greater than zero
        }
    }

    // Test case 6: Compare with maximum values
    Vec4ui a6(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFE);
    Vec4ui b6(0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFE);
    Vec4ui result6 = (a6 >= b6);
    assert(result6[0] == 0xFFFFFFFF); // Equal
    assert(result6[1] == 0xFFFFFFFF); // Greater
    assert(result6[2] == 0);          // Less
    assert(result6[3] == 0xFFFFFFFF); // Equal

    std::cout << "test_greater_than_or_equal_operator passed!\n";
}
void test_less_than_or_equal_operator() {
    // Test case 1: Less than comparison
    Vec4ui a1(1, 2, 3, 4);
    Vec4ui b1(2, 3, 4, 5);
    Vec4ui result1 = (a1 <= b1);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == 0xFFFFFFFF); // All elements in a1 are less than b1
    }

    // Test case 2: Equal values comparison
    Vec4ui a2(1, 1, 1, 1);
    Vec4ui b2(1, 1, 1, 1);
    Vec4ui result2 = (a2 <= b2);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0xFFFFFFFF); // Equal elements should return true
    }

    // Test case 3: Greater than comparison
    Vec4ui a3(2, 3, 4, 5);
    Vec4ui b3(1, 2, 3, 4);
    Vec4ui result3 = (a3 <= b3);
    for(int i = 0; i < 4; i++) {
        assert(result3[i] == 0); // All elements in a3 are greater than b3
    }

    // Test case 4: Mixed comparisons
    Vec4ui a4(5, 2, 7, 4);
    Vec4ui b4(5, 4, 5, 6);
    Vec4ui result4 = (a4 <= b4);
    assert(result4[0] == 0xFFFFFFFF); // 5 = 5
    assert(result4[1] == 0xFFFFFFFF); // 2 < 4
    assert(result4[2] == 0);          // 7 > 5
    assert(result4[3] == 0xFFFFFFFF); // 4 < 6

    // Test case 5: Compare with zero
    Vec4ui a5(0, 1, 0, 2);
    Vec4ui b5(0);
    Vec4ui result5 = (a5 <= b5);
    for(int i = 0; i < 4; i++) {
        if(a5[i] == 0) {
            assert(result5[i] == 0xFFFFFFFF); // Equal to zero
        } else {
            assert(result5[i] == 0); // Greater than zero
        }
    }

    // Test case 6: Compare with maximum values
    Vec4ui a6(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFE);
    Vec4ui b6(0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFE);
    Vec4ui result6 = (a6 <= b6);
    assert(result6[0] == 0xFFFFFFFF); // Equal
    assert(result6[1] == 0);          // Greater
    assert(result6[2] == 0xFFFFFFFF); // Less
    assert(result6[3] == 0xFFFFFFFF); // Equal

    std::cout << "test_less_than_or_equal_operator passed!\n";
}

void test_bitwise_and_operator() {
    // Test case 1: Basic AND operation
    Vec4ui a1(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
    Vec4ui b1(0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF);
    Vec4ui result1 = a1 & b1;
    assert(result1[0] == 0x00000000);
    assert(result1[1] == 0xFFFFFFFF);
    assert(result1[2] == 0x00000000);
    assert(result1[3] == 0xFFFFFFFF);

    // Test case 2: AND with zero
    Vec4ui a2(0xFFFFFFFF, 0xAAAAAAAA, 0x55555555, 0xF0F0F0F0);
    Vec4ui b2(0);
    Vec4ui result2 = a2 & b2;
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: AND with patterns
    Vec4ui a3(0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA);
    Vec4ui b3(0x55555555, 0x55555555, 0x55555555, 0x55555555);
    Vec4ui result3 = a3 & b3;
    for(int i = 0; i < 4; i++) {
        assert(result3[i] == 0);
    }

    // Test case 4: Self AND
    Vec4ui a4(0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0, 0xF0F0F0F0);
    Vec4ui result4 = a4 & a4;
    for(int i = 0; i < 4; i++) {
        assert(result4[i] == 0xF0F0F0F0);
    }

    // Test case 5: Mixed patterns
    Vec4ui a5(0xFFFFFFFF, 0xF0F0F0F0, 0xAAAAAAAA, 0x55555555);
    Vec4ui b5(0xFF00FF00, 0x0F0F0F0F, 0x55555555, 0xAAAAAAAA);
    Vec4ui result5 = a5 & b5;
    assert(result5[0] == 0xFF00FF00);
    assert(result5[1] == 0x00000000);
    assert(result5[2] == 0x00000000);
    assert(result5[3] == 0x00000000);

    std::cout << "test_bitwise_and_operator passed!\n";
}
void test_bitwise_or_operator() {
    // Test case 1: Basic OR operation
    Vec4ui a1(0x0000);
    Vec4ui b1(0xFFFF, 0x0000, 0xFFFF, 0x0000);
    Vec4ui result1 = a1 | b1;
    assert(result1[0] == 0xFFFF);
    assert(result1[1] == 0x0000);
    assert(result1[2] == 0xFFFF);
    assert(result1[3] == 0x0000);

    // Test case 2: OR with all bits set
    Vec4ui a2(0xAAAA, 0x5555, 0xF0F0, 0x0F0F);
    Vec4ui b2(0xFFFFFFFF);
    Vec4ui result2 = a2 | b2;
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0xFFFFFFFF);
    }

    // Test case 3: OR with alternating patterns
    Vec4ui a3(0xAAAAAAAA);
    Vec4ui b3(0x55555555);
    Vec4ui result3 = a3 | b3;
    for(int i = 0; i < 4; i++) {
        assert(result3[i] == 0xFFFFFFFF);
    }

    // Test case 4: OR with self
    Vec4ui a4(0xF0F0F0F0);
    Vec4ui result4 = a4 | a4;
    for(int i = 0; i < 4; i++) {
        assert(result4[i] == 0xF0F0F0F0);
    }

    // Test case 5: OR with zero
    Vec4ui a5(0xFFFFFFFF, 0xF0F0F0F0, 0xAAAAAAAA, 0x55555555);
    Vec4ui b5(0);
    Vec4ui result5 = a5 | b5;
    assert(result5[0] == 0xFFFFFFFF);
    assert(result5[1] == 0xF0F0F0F0);
    assert(result5[2] == 0xAAAAAAAA);
    assert(result5[3] == 0x55555555);

    std::cout << "test_bitwise_or_operator passed!\n";
}
void test_bitwise_xor_operator() {
    // Test case 1: XOR with zero (identity)
    Vec4ui a1(0xFFFFFFFF, 0xAAAAAAAA, 0x55555555, 0xF0F0F0F0);
    Vec4ui b1(0);
    Vec4ui result1 = a1 ^ b1;
    assert(result1[0] == 0xFFFFFFFF);
    assert(result1[1] == 0xAAAAAAAA); 
    assert(result1[2] == 0x55555555);
    assert(result1[3] == 0xF0F0F0F0);

    // Test case 2: XOR with same value (should be zero)
    Vec4ui a2(0xFFFFFFFF, 0xAAAAAAAA, 0x55555555, 0xF0F0F0F0);
    Vec4ui result2 = a2 ^ a2;
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: XOR with alternating patterns
    Vec4ui a3(0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA);
    Vec4ui b3(0x55555555, 0x55555555, 0x55555555, 0x55555555);
    Vec4ui result3 = a3 ^ b3;
    for(int i = 0; i < 4; i++) {
        assert(result3[i] == 0xFFFFFFFF);
    }

    // Test case 4: XOR with all bits set
    Vec4ui a4(0xFFFFFFFF, 0xAAAAAAAA, 0x55555555, 0xF0F0F0F0);
    Vec4ui b4(0xFFFFFFFF);
    Vec4ui result4 = a4 ^ b4;
    assert(result4[0] == 0x00000000);
    assert(result4[1] == 0x55555555);
    assert(result4[2] == 0xAAAAAAAA);
    assert(result4[3] == 0x0F0F0F0F);

    // Test case 5: XOR with mixed patterns
    Vec4ui a5(0xFF00FF00, 0x00FF00FF, 0xF0F0F0F0, 0x0F0F0F0F);
    Vec4ui b5(0x00FF00FF, 0xFF00FF00, 0x0F0F0F0F, 0xF0F0F0F0);
    Vec4ui result5 = a5 ^ b5;
    for(int i = 0; i < 4; i++) {
        assert(result5[i] == 0xFFFFFFFF);
    }

    std::cout << "test_bitwise_xor_operator passed!\n";
}
void test_bitwise_not_operator() {
    // Test case 1: NOT of zero gives all bits set
    Vec4ui a1(0);
    Vec4ui result1 = ~a1;
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == 0xFFFFFFFF);
    }

    // Test case 2: NOT of all bits set gives zero
    Vec4ui a2(0xFFFFFFFF);
    Vec4ui result2 = ~a2;
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: NOT of alternating bits
    Vec4ui a3(0xAAAAAAAA, 0x55555555, 0xF0F0F0F0, 0x0F0F0F0F);
    Vec4ui result3 = ~a3;
    assert(result3[0] == 0x55555555); // NOT of 0xAAAAAAAA
    assert(result3[1] == 0xAAAAAAAA); // NOT of 0x55555555
    assert(result3[2] == 0x0F0F0F0F); // NOT of 0xF0F0F0F0
    assert(result3[3] == 0xF0F0F0F0); // NOT of 0x0F0F0F0F

    // Test case 4: Double NOT should give original value
    Vec4ui a4(0x12345678, 0x9ABCDEF0, 0x24680135, 0x7ACEF024);
    Vec4ui result4 = ~~a4;
    for(int i = 0; i < 4; i++) {
        assert(result4[i] == a4[i]);
    }

    std::cout << "test_bitwise_not_operator passed!\n";
}

void test_select() {
    // Test case 1: Basic selection with all true condition
    Vec4ui mask1(0xFFFFFFFF);
    Vec4ui a1(1, 2, 3, 4);
    Vec4ui b1(9, 10, 11, 12);
    Vec4ui result1 = select(mask1, a1, b1);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == a1[i]); // Should select all from a1
    }

    // Test case 2: Basic selection with all false condition
    Vec4ui mask2(0);
    Vec4ui a2(1, 2, 3, 4);
    Vec4ui b2(9, 10, 11, 12);
    Vec4ui result2 = select(mask2, a2, b2);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == b2[i]); // Should select all from b2
    }

    // Test case 3: Alternating selection pattern
    Vec4ui mask3(0xFFFFFFFF, 0, 0xFFFFFFFF, 0);
    Vec4ui a3(1, 2, 3, 4);
    Vec4ui b3(9, 10, 11, 12);
    Vec4ui result3 = select(mask3, a3, b3);
    assert(result3[0] == 1);  // From a3
    assert(result3[1] == 10); // From b3
    assert(result3[2] == 3);  // From a3
    assert(result3[3] == 12); // From b3

    // Test case 4: Selection with maximum values
    Vec4ui mask4(0xFFFFFFFF, 0xFFFFFFFF, 0, 0);
    Vec4ui a4(0xFFFFFFFF);
    Vec4ui b4(0);
    Vec4ui result4 = select(mask4, a4, b4);
    assert(result4[0] == 0xFFFFFFFF);
    assert(result4[1] == 0xFFFFFFFF);
    assert(result4[2] == 0);
    assert(result4[3] == 0);

    // Test case 5: Selection with mixed patterns
    Vec4ui mask5(0xAAAAAAAA, 0x55555555, 0xF0F0F0F0, 0x0F0F0F0F);
    Vec4ui a5(0xFFFFFFFF);
    Vec4ui b5(0);
    Vec4ui result5 = select(mask5, a5, b5);
    assert(result5[0] == 0xAAAAAAAA);
    assert(result5[1] == 0x55555555);
    assert(result5[2] == 0xF0F0F0F0);
    assert(result5[3] == 0x0F0F0F0F);

    std::cout << "test_select passed!\n";
}
void test_if_add() {
    // Test case 1: Add with all true conditions
    Vec4ui mask1(0xFFFFFFFF);
    Vec4ui a1(1, 2, 3, 4);
    Vec4ui b1(1, 1, 1, 1);
    Vec4ui result1 = if_add(mask1, a1, b1);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == a1[i] + b1[i]); // Should add all values
    }

    // Test case 2: Add with all false conditions
    Vec4ui mask2(0);
    Vec4ui a2(1, 2, 3, 4);
    Vec4ui b2(1, 1, 1, 1);
    Vec4ui result2 = if_add(mask2, a2, b2);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == a2[i]); // Should not add anything
    }

    // Test case 3: Alternating conditions
    Vec4ui mask3(0xFFFFFFFF, 0, 0xFFFFFFFF, 0);
    Vec4ui a3(1, 2, 3, 4);
    Vec4ui b3(1, 1, 1, 1);
    Vec4ui result3 = if_add(mask3, a3, b3);
    assert(result3[0] == 2);  // 1 + 1
    assert(result3[1] == 2);  // 2 + 0
    assert(result3[2] == 4);  // 3 + 1
    assert(result3[3] == 4);  // 4 + 0

    // Test case 4: Add with saturation
    Vec4ui mask4(0xFFFFFFFF);
    Vec4ui a4(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
    Vec4ui b4(1, 1, 1, 1);
    Vec4ui result4 = if_add(mask4, a4, b4);
    for(int i = 0; i < 4; i++) {
        assert(result4[i] == 0xFFFFFFFF); // Should saturate at maximum value
    }

    // Test case 5: Add with mixed values
    Vec4ui mask5(0xFFFFFFFF, 0xFFFFFFFF, 0, 0);
    Vec4ui a5(0x1000, 0x2000, 0x3000, 0x4000);
    Vec4ui b5(0x0100, 0x0200, 0x0300, 0x0400);
    Vec4ui result5 = if_add(mask5, a5, b5);
    assert(result5[0] == 0x1100); // 0x1000 + 0x0100
    assert(result5[1] == 0x2200); // 0x2000 + 0x0200
    assert(result5[2] == 0x3000); // 0x3000 + 0
    assert(result5[3] == 0x4000); // 0x4000 + 0

    std::cout << "test_if_add passed!\n";
}
void test_if_sub() {
    // Test case 1: Subtract with all true conditions
    Vec4ui mask1(0xFFFFFFFF);
    Vec4ui a1(10, 11, 12, 13);
    Vec4ui b1(1, 1, 1, 1);
    Vec4ui result1 = if_sub(mask1, a1, b1);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == a1[i] - b1[i]); // Should subtract all values
    }

    // Test case 2: Subtract with all false conditions
    Vec4ui mask2(0);
    Vec4ui a2(10, 11, 12, 13);
    Vec4ui b2(1, 1, 1, 1);
    Vec4ui result2 = if_sub(mask2, a2, b2);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == a2[i]); // Should not subtract anything
    }

    // Test case 3: Alternating conditions
    Vec4ui mask3(0xFFFFFFFF, 0, 0xFFFFFFFF, 0);
    Vec4ui a3(10, 11, 12, 13);
    Vec4ui b3(1, 1, 1, 1);
    Vec4ui result3 = if_sub(mask3, a3, b3);
    assert(result3[0] == 9);   // 10 - 1
    assert(result3[1] == 11);  // 11 - 0
    assert(result3[2] == 11);  // 12 - 1
    assert(result3[3] == 13);  // 13 - 0

    // Test case 4: Subtract with saturation prevention
    Vec4ui mask4(0xFFFFFFFF);
    Vec4ui a4(1, 2, 3, 4);
    Vec4ui b4(2, 3, 4, 5);
    Vec4ui result4 = if_sub(mask4, a4, b4);
    for(int i = 0; i < 4; i++) {
        assert(result4[i] == 0); // Should saturate at minimum value
    }

    // Test case 5: Subtract with mixed values
    Vec4ui mask5(0xFFFFFFFF, 0xFFFFFFFF, 0, 0);
    Vec4ui a5(0x1100, 0x2200, 0x3300, 0x4400);
    Vec4ui b5(0x0100, 0x0200, 0x0300, 0x0400);
    Vec4ui result5 = if_sub(mask5, a5, b5);
    assert(result5[0] == 0x1000); // 0x1100 - 0x0100
    assert(result5[1] == 0x2000); // 0x2200 - 0x0200
    assert(result5[2] == 0x3300); // 0x3300 - 0
    assert(result5[3] == 0x4400); // 0x4400 - 0

    std::cout << "test_if_sub passed!\n";
}
void test_if_mul() {
    // Test case 1: Multiply with all true conditions
    Vec4ui mask1(0xFFFFFFFF);
    Vec4ui a1(1, 2, 3, 4);
    Vec4ui b1(2, 2, 2, 2);
    Vec4ui result1 = if_mul(mask1, a1, b1);
    for(int i = 0; i < 4; i++) {
        assert(result1[i] == a1[i] * b1[i]); // Should multiply all values
    }

    // Test case 2: Multiply with all false conditions
    Vec4ui mask2(0);
    Vec4ui a2(1, 2, 3, 4);
    Vec4ui b2(2, 2, 2, 2);
    Vec4ui result2 = if_mul(mask2, a2, b2);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == a2[i]); // Should not multiply anything
    }

    // Test case 3: Alternating conditions
    Vec4ui mask3(0xFFFFFFFF, 0, 0xFFFFFFFF, 0);
    Vec4ui a3(1, 2, 3, 4);
    Vec4ui b3(2, 2, 2, 2);
    Vec4ui result3 = if_mul(mask3, a3, b3);
    assert(result3[0] == 2);  // 1 * 2
    assert(result3[1] == 2);  // 2 (unchanged)
    assert(result3[2] == 6);  // 3 * 2
    assert(result3[3] == 4);  // 4 (unchanged)

    // Test case 4: Multiply with larger values
    Vec4ui mask4(0xFFFFFFFF);
    Vec4ui a4(100, 200, 300, 400);
    Vec4ui b4(3, 3, 3, 3);
    Vec4ui result4 = if_mul(mask4, a4, b4);
    assert(result4[0] == 300);
    assert(result4[1] == 600);
    assert(result4[2] == 900);
    assert(result4[3] == 1200);

    // Test case 6: Multiply near maximum values
    Vec4ui mask6(0xFFFFFFFF);  
    Vec4ui a6(0x80000000, 0x40000000, 0x20000000, 0x10000000);
    Vec4ui b6(2);
    Vec4ui result6 = if_mul(mask6, a6, b6);
    assert(result6[0] == 0x00000000);  // 0x80000000 * 2 overflows to 0
    assert(result6[1] == 0x80000000);  // 0x40000000 * 2 = 0x80000000
    assert(result6[2] == 0x40000000);  // 0x20000000 * 2 = 0x40000000
    assert(result6[3] == 0x20000000);  // 0x10000000 * 2 = 0x20000000

    // Test case 7: Multiply at maximum values
    Vec4ui mask7(0xFFFFFFFF);
    Vec4ui a7(0xFFFFFFFF);
    Vec4ui b7(0xFFFFFFFF);
    Vec4ui result7 = if_mul(mask7, a7, b7);
    for(int i = 0; i < 4; i++) {
        assert(result7[i] == 1); // 0xFFFFFFFF * 0xFFFFFFFF = 1 due to overflow
    }

    // Test case 8: Mixed multiplications near maximum  
    Vec4ui mask8(0xFFFFFFFF);
    Vec4ui a8(0xFFFFFFFF, 0x7FFFFFFF, 0x3FFFFFFF, 0x1FFFFFFF);
    Vec4ui b8(2, 3, 4, 5); 
    Vec4ui result8 = if_mul(mask8, a8, b8);
    assert(result8[0] == 0xFFFFFFFE);  // 0xFFFFFFFF * 2
    assert(result8[1] == 0x7FFFFFFD);  // 0x7FFFFFFF * 3
    assert(result8[2] == 0xFFFFFFFC);  // 0x3FFFFFFF * 4
    assert(result8[3] == 0x9FFFFFFB);  // 0x1FFFFFFF * 5

    std::cout << "test_if_mul passed!\n";
}

void test_horizontal_add() {
    // Test case 1: Basic addition of all ones
    Vec4ui a1(1, 1, 1, 1);
    uint32_t result1 = horizontal_add(a1);
    assert(result1 == 4); // Sum should be 4

    // Test case 2: Addition of sequential numbers
    Vec4ui a2(1, 2, 3, 4); 
    uint32_t result2 = horizontal_add(a2);
    assert(result2 == 10); // Sum should be 10

    // Test case 3: Addition with zeros
    Vec4ui a3(0, 0, 0, 0);
    uint32_t result3 = horizontal_add(a3);
    assert(result3 == 0); // Sum should be 0

    // Test case 4: Addition of mixed values
    Vec4ui a4(0xFFFF, 0x0001, 0x1000, 0x0100);
    uint32_t result4 = horizontal_add(a4);
    assert(result4 == 0x11100); // Sum of all values

    // Test case 5: Addition of maximum values
    Vec4ui a5(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF);
    uint32_t result5 = horizontal_add(a5);
    assert(result5 == 0xFFFFFFFC); // Sum of four 0xFFFFFFFF values

    std::cout << "test_horizontal_add passed!\n";
}

void test_max() {
    // Test case 1: Basic max comparison
    Vec4ui a1(1, 2, 3, 4);
    Vec4ui b1(8, 7, 6, 5);
    Vec4ui result1 = max(a1, b1);
    assert(result1[0] == 8);
    assert(result1[1] == 7);
    assert(result1[2] == 6);
    assert(result1[3] == 5);

    // Test case 2: Max with equal values
    Vec4ui a2(5, 5, 5, 5);
    Vec4ui b2(5, 5, 5, 5);
    Vec4ui result2 = max(a2, b2);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 5);
    }

    // Test case 3: Max with zeros 
    Vec4ui a3(0, 0, 0, 0);
    Vec4ui b3(1, 1, 1, 1);
    Vec4ui result3 = max(a3, b3);
    for(int i = 0; i < 4; i++) {
        assert(result3[i] == 1);
    }

    // Test case 4: Max with maximum values
    Vec4ui a4(0xFFFF);
    Vec4ui b4(0x7FFF, 0x8FFF, 0x9FFF, 0xAFFF);
    Vec4ui result4 = max(a4, b4);
    for(int i = 0; i < 4; i++) {
        assert(result4[i] == 0xFFFF);
    }

    // Test case 5: Max with mixed values
    Vec4ui a5(0x1234, 0x5678, 0xABCD, 0x4321);
    Vec4ui b5(0x4321, 0x1234, 0xDCBA, 0xABCD);
    Vec4ui result5 = max(a5, b5);
    assert(result5[0] == 0x4321);
    assert(result5[1] == 0x5678);
    assert(result5[2] == 0xDCBA);
    assert(result5[3] == 0xABCD);

    std::cout << "test_max passed!\n";
}
void test_min() {
    // Test case 1: Basic min comparison
    Vec4ui a1(1, 2, 3, 4);
    Vec4ui b1(8, 7, 6, 5);
    Vec4ui result1 = min(a1, b1);
    assert(result1[0] == 1);
    assert(result1[1] == 2);
    assert(result1[2] == 3);
    assert(result1[3] == 4);

    // Test case 2: Min with equal values
    Vec4ui a2(5, 5, 5, 5);
    Vec4ui b2(5, 5, 5, 5);
    Vec4ui result2 = min(a2, b2);
    for(int i = 0; i < 4; i++) {
        assert(result2[i] == 5);
    }

    // Test case 3: Min with zeros
    Vec4ui a3(1, 1, 1, 1);
    Vec4ui b3(0, 0, 0, 0);
    Vec4ui result3 = min(a3, b3);
    for(int i = 0; i < 4; i++) {
        assert(result3[i] == 0);
    }

    // Test case 4: Min with maximum values
    Vec4ui a4(0xFFFF);
    Vec4ui b4(0x7FFF, 0x8FFF, 0x9FFF, 0xAFFF);
    Vec4ui result4 = min(a4, b4);
    assert(result4[0] == 0x7FFF);
    assert(result4[1] == 0x8FFF);
    assert(result4[2] == 0x9FFF);
    assert(result4[3] == 0xAFFF);

    // Test case 5: Min with mixed values
    Vec4ui a5(0x1234, 0x5678, 0xABCD, 0x4321);
    Vec4ui b5(0x4321, 0x1234, 0xDCBA, 0xABCD);
    Vec4ui result5 = min(a5, b5);
    assert(result5[0] == 0x1234);
    assert(result5[1] == 0x1234); 
    assert(result5[2] == 0xABCD);
    assert(result5[3] == 0x4321);

    std::cout << "test_min passed!\n";
}

void test_rotate_left() {
    // Test case 1: Rotate left by 1
    Vec4ui a(1, 2, 3, 4);
    Vec4ui res1 = rotate_left(a, 1);
    for(int i = 0; i < 4; i++) {
        assert(res1[i] == (a[i] << 1));
    }

    // Test case 2: Rotate left by 4 
    Vec4ui b(0x1111, 0x2222, 0x3333, 0x4444);
    Vec4ui res2 = rotate_left(b, 4);
    for(int i = 0; i < 4; i++) {
        uint32_t expected = (b[i] << 4);
        assert(res2[i] == expected);
    }

    // Test case 3: Rotate left by 8
    Vec4ui c(0x00FF, 0xFF00, 0x0F0F, 0xF0F0);
    Vec4ui res3 = rotate_left(c, 8);
    for(int i = 0; i < 4; i++) {
        uint32_t expected = (c[i] << 8);
        assert(res3[i] == expected);
    }

    // Test case 4: Rotate zeros (should remain zero)
    Vec4ui a4(0);
    Vec4ui result4 = rotate_left(a4, 4);
    for(int i = 0; i < 4; i++) {
        assert(result4[i] == 0);
    }

    // Test case 5: Rotate maximum values
    Vec4ui a5(0xFFFFFFFF);
    Vec4ui result5 = rotate_left(a5, 4);
    for(int i = 0; i < 4; i++) {
        assert(result5[i] == 0xFFFFFFF0);
    }

    std::cout << "test_rotate_left passed!\n";
}

void test_rotate_right() {
    // Test case 1: Rotate right by 1
    Vec4ui a(2, 4, 6, 8);
    Vec4ui res1 = rotate_right(a, 1);
    for(int i = 0; i < 4; i++) {
        assert(res1[i] == (a[i] >> 1));
    }

    // Test case 2: Rotate right by 4
    Vec4ui b(0x1111, 0x2222, 0x3333, 0x4444);
    Vec4ui res2 = rotate_right(b, 4);
    for(int i = 0; i < 4; i++) {
        uint32_t expected = (b[i] >> 4);
        assert(res2[i] == expected);
    }

    // Test case 3: Rotate right by 8
    Vec4ui c(0xFF00, 0x00FF, 0xF0F0, 0x0F0F);
    Vec4ui res3 = rotate_right(c, 8);
    for(int i = 0; i < 4; i++) {
        uint32_t expected = (c[i] >> 8);
        assert(res3[i] == expected);
    }

    // Test case 4: Rotate zeros (should remain zero)
    Vec4ui a4(0);
    Vec4ui result4 = rotate_right(a4, 4);
    for(int i = 0; i < 4; i++) {
        assert(result4[i] == 0);
    }

    // Test case 5: Rotate maximum value
    Vec4ui a5(0xFFFFFFFF);
    Vec4ui result5 = rotate_right(a5, 4);
    for(int i = 0; i < 4; i++) {
        assert(result5[i] == 0x0FFFFFFF);
    }
    std::cout << "test_rotate_right passed!\n";
}

int main() 
{
    test_default_constructor();
    test_broadcast_constructor();
    test_element_constructor();
    test_uint32x4t_constructor();
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
    test_subtract_equals_operator();
    test_postfix_decrement_operator();
    test_prefix_decrement_operator();

    test_multiply_operator();
    test_multiply_equals_operator();
    test_shift_left_operator();
    test_shift_left_equals_operator();
    test_shift_right_operator();
    test_shift_right_equals_operator();

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
    test_rotate_left();
    test_rotate_right();
    std::cout << "All tests passed!\n";
    return 0;
}