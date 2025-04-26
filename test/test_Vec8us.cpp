#include "../Vec8us.h"
#include <iostream>
#include <cassert>

using namespace VCL_NAMESPACE;

void test_default_constructor() {
    // Test default constructor initializes to zero
    Vec8us v;
    for(int i = 0; i < 8; i++) {
        assert(v[i] == 0);
    }
    
    // Test multiple instances
    Vec8us v2;
    Vec8us v3;
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == 0);
        assert(v3[i] == 0);
    }

    // Test value changes after default construction
    Vec8us v4;
    v4 = Vec8us(1,2,3,4,5,6,7,8); 
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == i+1);
    }
    std::cout << "test_default_constructor passed!\n";
}
void test_broadcast_constructor() {
    // Test case 1: Broadcast zero
    Vec8us v1(0);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Broadcast maximum value
    Vec8us v2(0xFFFF);
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == 0xFFFF);
    }

    // Test case 3: Broadcast arbitrary value
    Vec8us v3(0x1234);
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == 0x1234);
    }

    // Test case 4: Multiple instances with different values
    Vec8us v4(0xAAAA);
    Vec8us v5(0x5555);
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == 0xAAAA);
        assert(v5[i] == 0x5555);
    }
    std::cout << "test_broadcast_constructor passed!\n";
}
void test_element_constructor() {
    // Test case 1: Sequential values
    Vec8us v1(0, 1, 2, 3, 4, 5, 6, 7);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == i);
    }

    // Test case 2: All same values
    Vec8us v2(5, 5, 5, 5, 5, 5, 5, 5);
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == 5);
    }

    // Test case 3: Maximum values
    Vec8us v3(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 
              0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == 0xFFFF);
    }

    // Test case 4: Mixed values
    Vec8us v4(0x1234, 0xABCD, 0, 0xFFFF, 
              0x8000, 0x4000, 0x2000, 0x1000);
    assert(v4[0] == 0x1234);
    assert(v4[1] == 0xABCD);
    assert(v4[2] == 0);
    assert(v4[3] == 0xFFFF);
    assert(v4[4] == 0x8000);
    assert(v4[5] == 0x4000);
    assert(v4[6] == 0x2000);
    assert(v4[7] == 0x1000);

    std::cout << "test_element_constructor passed!\n";
}
void test_uint16x8t_constructor() {
    // Test case 1: Create uint16x8_t with zeros and construct Vec8us from it
    uint16_t data1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint16x8_t x1 = vld1q_u16(data1);
    Vec8us v1(x1);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Create uint16x8_t with sequential values
    uint16_t data2[8] = {1, 2, 3, 4, 5, 6, 7, 8}; 
    uint16x8_t x2 = vld1q_u16(data2);
    Vec8us v2(x2);
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Create uint16x8_t with maximum values
    uint16_t data3[8] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
                         0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    uint16x8_t x3 = vld1q_u16(data3);
    Vec8us v3(x3);
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == 0xFFFF);
    }

    // Test case 4: Create uint16x8_t with mixed values
    uint16_t data4[8] = {0x1234, 0xABCD, 0, 0xFFFF,
                         0x8000, 0x4000, 0x2000, 0x1000};
    uint16x8_t x4 = vld1q_u16(data4);
    Vec8us v4(x4);
    assert(v4[0] == 0x1234);
    assert(v4[1] == 0xABCD);
    assert(v4[2] == 0);
    assert(v4[3] == 0xFFFF); 
    assert(v4[4] == 0x8000);
    assert(v4[5] == 0x4000);
    assert(v4[6] == 0x2000);
    assert(v4[7] == 0x1000);
    std::cout << "test_uint16x8t_constructor passed!\n";
}
void test_copy_constructor() {
    // Test case 1: Copy constructor with zeros
    Vec8us original1(0);
    Vec8us copy1(original1);
    for(int i = 0; i < 8; i++) {
        assert(copy1[i] == 0);
    }

    // Test case 2: Copy constructor with sequential values
    Vec8us original2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us copy2(original2);
    for(int i = 0; i < 8; i++) {
        assert(copy2[i] == i + 1);
    }

    // Test case 3: Copy constructor with maximum values
    Vec8us original3(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
                     0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
    Vec8us copy3(original3);
    for(int i = 0; i < 8; i++) {
        assert(copy3[i] == 0xFFFF);
    }

    // Test case 4: Copy constructor with mixed values
    Vec8us original4(0x1234, 0xABCD, 0, 0xFFFF,
                     0x8000, 0x4000, 0x2000, 0x1000);
    Vec8us copy4(original4);
    assert(copy4[0] == 0x1234);
    assert(copy4[1] == 0xABCD);
    assert(copy4[2] == 0);
    assert(copy4[3] == 0xFFFF);
    assert(copy4[4] == 0x8000);
    assert(copy4[5] == 0x4000);
    assert(copy4[6] == 0x2000);
    assert(copy4[7] == 0x1000);
    std::cout << "test_copy_constructor passed!\n";
}

void test_assignment_operator() {
    // Test case 1: Assign zeros
    uint16_t data1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    uint16x8_t x1 = vld1q_u16(data1);
    Vec8us v1;
    v1 = x1;
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Assign sequential values
    uint16_t data2[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    uint16x8_t x2 = vld1q_u16(data2);
    Vec8us v2;
    v2 = x2;
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Assign maximum values
    uint16_t data3[8] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
                         0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    uint16x8_t x3 = vld1q_u16(data3);
    Vec8us v3;
    v3 = x3;
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == 0xFFFF);
    }

    // Test case 4: Assign mixed values
    uint16_t data4[8] = {0x1234, 0xABCD, 0, 0xFFFF,
                         0x8000, 0x4000, 0x2000, 0x1000};
    uint16x8_t x4 = vld1q_u16(data4);
    Vec8us v4;
    v4 = x4;
    assert(v4[0] == 0x1234);
    assert(v4[1] == 0xABCD);
    assert(v4[2] == 0);
    assert(v4[3] == 0xFFFF);
    assert(v4[4] == 0x8000);
    assert(v4[5] == 0x4000);
    assert(v4[6] == 0x2000);
    assert(v4[7] == 0x1000);
    std::cout << "test_assignment_operator passed!\n";
}

void test_type_cast_operator() {
    // Test case 1: Cast zero values
    Vec8us v1(0);
    uint16x8_t x1 = v1;
    uint16_t data1[8];
    vst1q_u16(data1, x1);
    for(int i = 0; i < 8; i++) {
        assert(data1[i] == 0);
    }

    // Test case 2: Cast sequential values
    Vec8us v2(1, 2, 3, 4, 5, 6, 7, 8);
    uint16x8_t x2 = v2;
    uint16_t data2[8];
    vst1q_u16(data2, x2);
    for(int i = 0; i < 8; i++) {
        assert(data2[i] == i + 1);
    }

    // Test case 3: Cast maximum values
    Vec8us v3(0xFFFF);
    uint16x8_t x3 = v3;
    uint16_t data3[8];
    vst1q_u16(data3, x3);
    for(int i = 0; i < 8; i++) {
        assert(data3[i] == 0xFFFF);
    }

    // Test case 4: Cast mixed values
    Vec8us v4(0x1234, 0xABCD, 0, 0xFFFF, 0x8000, 0x4000, 0x2000, 0x1000);
    uint16x8_t x4 = v4;
    uint16_t data4[8];
    vst1q_u16(data4, x4);
    assert(data4[0] == 0x1234);
    assert(data4[1] == 0xABCD);
    assert(data4[2] == 0);
    assert(data4[3] == 0xFFFF);
    assert(data4[4] == 0x8000);
    assert(data4[5] == 0x4000);
    assert(data4[6] == 0x2000);
    assert(data4[7] == 0x1000);

    std::cout << "test_type_cast_operator passed!\n";
}

void test_load() {
    // Test case 1: Load zeros
    uint16_t data1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    Vec8us v1;
    v1.load(data1);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Load sequential values 
    uint16_t data2[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Vec8us v2;
    v2.load(data2);
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Load maximum values
    uint16_t data3[8] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
                         0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    Vec8us v3;
    v3.load(data3);
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == 0xFFFF);
    }

    // Test case 4: Load mixed values
    uint16_t data4[8] = {0x1234, 0xABCD, 0, 0xFFFF,
                         0x8000, 0x4000, 0x2000, 0x1000};
    Vec8us v4;
    v4.load(data4);
    assert(v4[0] == 0x1234);
    assert(v4[1] == 0xABCD);
    assert(v4[2] == 0);
    assert(v4[3] == 0xFFFF);
    assert(v4[4] == 0x8000);
    assert(v4[5] == 0x4000);
    assert(v4[6] == 0x2000);
    assert(v4[7] == 0x1000);

    std::cout << "test_load passed!\n";
}

void test_load_a() {
    // Test case 1: Load aligned zeros
    alignas(16) uint16_t data1[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    Vec8us v1;
    v1.load_a(data1);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Load aligned sequential values
    alignas(16) uint16_t data2[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Vec8us v2;
    v2.load_a(data2);
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Load aligned maximum values
    alignas(16) uint16_t data3[8] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
                                    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    Vec8us v3;
    v3.load_a(data3);
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == 0xFFFF);
    }

    // Test case 4: Load aligned mixed values
    alignas(16) uint16_t data4[8] = {0x1234, 0xABCD, 0, 0xFFFF,
                                    0x8000, 0x4000, 0x2000, 0x1000};
    Vec8us v4;
    v4.load_a(data4);
    assert(v4[0] == 0x1234);
    assert(v4[1] == 0xABCD); 
    assert(v4[2] == 0);
    assert(v4[3] == 0xFFFF);
    assert(v4[4] == 0x8000);
    assert(v4[5] == 0x4000);
    assert(v4[6] == 0x2000);
    assert(v4[7] == 0x1000);

    std::cout << "test_load_a passed!\n";
}

void test_store() {
    // Test case 1: Store zeros
    uint16_t data1[8];
    Vec8us v1(0);
    v1.store(data1);
    for(int i = 0; i < 8; i++) {
        assert(data1[i] == 0);
    }

    // Test case 2: Store sequential values
    uint16_t data2[8];
    Vec8us v2(1, 2, 3, 4, 5, 6, 7, 8);
    v2.store(data2);
    for(int i = 0; i < 8; i++) {
        assert(data2[i] == i + 1);
    }

    // Test case 3: Store maximum values
    uint16_t data3[8];
    Vec8us v3(0xFFFF);
    v3.store(data3);
    for(int i = 0; i < 8; i++) {
        assert(data3[i] == 0xFFFF);
    }

    // Test case 4: Store mixed values
    uint16_t data4[8];
    Vec8us v4(0x1234, 0xABCD, 0, 0xFFFF, 0x8000, 0x4000, 0x2000, 0x1000);
    v4.store(data4);
    assert(data4[0] == 0x1234);
    assert(data4[1] == 0xABCD);
    assert(data4[2] == 0);
    assert(data4[3] == 0xFFFF);
    assert(data4[4] == 0x8000);
    assert(data4[5] == 0x4000);
    assert(data4[6] == 0x2000);
    assert(data4[7] == 0x1000);

    std::cout << "test_store passed!\n";
}

void test_store_a() {
    // Test case 1: Store aligned zeros
    alignas(8) uint16_t data1[8];
    Vec8us v1(0);
    v1.store_a(data1);
    for(int i = 0; i < 8; i++) {
        assert(data1[i] == 0);
    }

    // Test case 2: Store aligned sequential values 
    alignas(8) uint16_t data2[8];
    Vec8us v2(1, 2, 3, 4, 5, 6, 7, 8);
    v2.store_a(data2);
    for(int i = 0; i < 8; i++) {
        assert(data2[i] == i + 1);
    }

    // Test case 3: Store aligned maximum values
    alignas(8) uint16_t data3[8];
    Vec8us v3(0xFFFF);
    v3.store_a(data3);
    for(int i = 0; i < 8; i++) {
        assert(data3[i] == 0xFFFF);
    }

    // Test case 4: Store aligned mixed values
    alignas(8) uint16_t data4[8];
    Vec8us v4(0x1234, 0xABCD, 0, 0xFFFF, 0x8000, 0x4000, 0x2000, 0x1000);
    v4.store_a(data4);
    assert(data4[0] == 0x1234);
    assert(data4[1] == 0xABCD);
    assert(data4[2] == 0);
    assert(data4[3] == 0xFFFF);
    assert(data4[4] == 0x8000);
    assert(data4[5] == 0x4000);
    assert(data4[6] == 0x2000);
    assert(data4[7] == 0x1000);

    std::cout << "test_store_a passed!\n";
}

void test_load_partial() {
    // Test case 1: Load when n >= 8 (full load)
    uint16_t data1[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    Vec8us v1;
    v1.load_partial(8, data1);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == i + 1);
    }

    // Test case 2: Load when n <= 0 (zero)
    uint16_t data2[8] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 
                         0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    Vec8us v2;
    v2.load_partial(0, data2);
    for(int i = 0; i < 8; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: Load partial data (n = 4)
    uint16_t data3[8] = {1, 2, 3, 4, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    Vec8us v3;
    v3.load_partial(4, data3);
    for(int i = 0; i < 4; i++) {
        assert(v3[i] == i + 1);
    }
    for(int i = 4; i < 8; i++) {
        assert(v3[i] == 0);
    }

    // Test case 4: Load with negative n
    uint16_t data4[8] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
                         0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    Vec8us v4;
    v4.load_partial(-1, data4);
    for(int i = 0; i < 8; i++) {
        assert(v4[i] == 0);
    }

    std::cout << "test_load_partial passed!\n";
}

void test_store_partial() {
    // Test case 1: Store when n > 8 (should store only 8 elements)
    uint16_t data1[10] = {0};
    Vec8us v1(1, 2, 3, 4, 5, 6, 7, 8);
    v1.store_partial(10, data1);
    for(int i = 0; i < 8; i++) {
        assert(data1[i] == i + 1);
    }
    // Elements beyond 8 should remain unchanged
    assert(data1[8] == 0);
    assert(data1[9] == 0);

    // Test case 2: Store when n = 4 (partial store)
    uint16_t data2[8] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 
                         0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    Vec8us v2(1, 2, 3, 4, 5, 6, 7, 8);
    v2.store_partial(4, data2);
    // First 4 elements should be stored
    for(int i = 0; i < 4; i++) {
        assert(data2[i] == i + 1);
    }
    // Remaining elements should be unchanged
    for(int i = 4; i < 8; i++) {
        assert(data2[i] == 0xFFFF);
    }

    // Test case 3: Store when n = 0 (no store)
    uint16_t data3[8] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
                         0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    Vec8us v3(1, 2, 3, 4, 5, 6, 7, 8);
    v3.store_partial(0, data3);
    // All elements should remain unchanged
    for(int i = 0; i < 8; i++) {
        assert(data3[i] == 0xFFFF);
    }

    // Test case 4: Store when n < 0 (no store)
    uint16_t data4[8] = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
                         0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF};
    Vec8us v4(1, 2, 3, 4, 5, 6, 7, 8);
    v4.store_partial(-1, data4);
    // All elements should remain unchanged
    for(int i = 0; i < 8; i++) {
        assert(data4[i] == 0xFFFF);
    }

    std::cout << "test_store_partial passed!\n";
}

void test_cutoff() {
    // Test case 1: n >= 8 (no cutoff)
    Vec8us v1(1, 2, 3, 4, 5, 6, 7, 8);
    v1.cutoff(8);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == i + 1);
    }
    
    v1.cutoff(9);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == i + 1);
    }

    // Test case 2: n = 4 (cutoff half)
    Vec8us v2(1, 2, 3, 4, 5, 6, 7, 8);
    v2.cutoff(4);
    for(int i = 0; i < 4; i++) {
        assert(v2[i] == i + 1);
    }
    for(int i = 4; i < 8; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: n = 0 (all zeros)
    Vec8us v3(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
    v3.cutoff(0);
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == 0);
    }

    // Test case 4: n = 1 (keep only first element)
    Vec8us v4(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
    v4.cutoff(1);
    assert(v4[0] == 0xFFFF);
    for(int i = 1; i < 8; i++) {
        assert(v4[i] == 0);
    }

    // Test case 5: n < 0 (should zero all elements)
    Vec8us v5(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
    v5.cutoff(-1);
    for(int i = 0; i < 8; i++) {
        assert(v5[i] == 0);
    }

    // Test case 6: n = 7 (keep all but last element)
    Vec8us v6(1, 2, 3, 4, 5, 6, 7, 8);
    v6.cutoff(7);
    for(int i = 0; i < 7; i++) {
        assert(v6[i] == i + 1);
    }
    assert(v6[7] == 0);

    // Test case 7: Multiple cutoff operations
    Vec8us v7(1, 2, 3, 4, 5, 6, 7, 8);
    v7.cutoff(6);
    v7.cutoff(4);  // Should further reduce to 4 elements
    for(int i = 0; i < 4; i++) {
        assert(v7[i] == i + 1);
    }
    for(int i = 4; i < 8; i++) {
        assert(v7[i] == 0);
    }

    std::cout << "test_cutoff passed!\n";
}

void test_and_assign_operator() {
    // Test case 1: AND with all bits set
    Vec8us a(0xFFFF);
    Vec8us b(0x5555);
    a &= b;
    for(int i = 0; i < 8; i++) {
        assert(a[i] == 0x5555);
    }

    // Test case 2: AND with zero
    Vec8us c(0xFFFF);
    Vec8us d(0);
    c &= d;
    for(int i = 0; i < 8; i++) {
        assert(c[i] == 0);
    }

    // Test case 3: AND with alternating patterns
    Vec8us e(0xAAAA, 0x5555, 0xFFFF, 0x0000, 
             0xAAAA, 0x5555, 0xFFFF, 0x0000);
    Vec8us f(0x5555, 0xAAAA, 0xFFFF, 0xFFFF,
             0x5555, 0xAAAA, 0xFFFF, 0xFFFF);
    e &= f;
    assert(e[0] == 0x0000); // 0xAAAA & 0x5555
    assert(e[1] == 0x0000); // 0x5555 & 0xAAAA
    assert(e[2] == 0xFFFF); // 0xFFFF & 0xFFFF
    assert(e[3] == 0x0000); // 0x0000 & 0xFFFF
    assert(e[4] == 0x0000); // 0xAAAA & 0x5555
    assert(e[5] == 0x0000); // 0x5555 & 0xAAAA
    assert(e[6] == 0xFFFF); // 0xFFFF & 0xFFFF
    assert(e[7] == 0x0000); // 0x0000 & 0xFFFF

    // Test case 4: AND with same value
    Vec8us g(0xAAAA);
    Vec8us h(0xAAAA);
    g &= h;
    for(int i = 0; i < 8; i++) {
        assert(g[i] == 0xAAAA);
    }

    std::cout << "test_and_equals_operator passed!\n";
}

void test_insert() {
    // Test case 1: Insert at each valid index
    Vec8us v1(0);
    for(int i = 0; i < 8; i++) {
        v1 = v1.insert(i, i + 1);
        assert(v1[i] == i + 1);
    }

    // Test case 2: Insert with index wrapping (index & 0x07)
    Vec8us v2(0);
    v2 = v2.insert(8, 1);  // Should wrap to index 0
    assert(v2[0] == 1);
    v2 = v2.insert(9, 2);  // Should wrap to index 1
    assert(v2[1] == 2);
    v2 = v2.insert(15, 7); // Should wrap to index 7
    assert(v2[7] == 7);

    // Test case 3: Insert maximum values
    Vec8us v3(0);
    for(int i = 0; i < 8; i++) {
        v3 = v3.insert(i, 0xFFFF);
        assert(v3[i] == 0xFFFF);
    }

    // Test case 4: Insert with negative indices (should wrap)
    Vec8us v4(0);
    v4 = v4.insert(-1, 1);  // Should wrap to index 7
    assert(v4[7] == 1);
    v4 = v4.insert(-2, 2);  // Should wrap to index 6
    assert(v4[6] == 2);
    v4 = v4.insert(-8, 8);  // Should wrap to index 0
    assert(v4[0] == 8);

    std::cout << "test_insert passed!\n";
}

void test_extract() {
    // Test case 1: Extract from sequence
    Vec8us v1(1, 2, 3, 4, 5, 6, 7, 8);
    for(int i = 0; i < 8; i++) {
        assert(v1.extract(i) == i + 1);
    }

    // Test case 2: Extract with index wrapping (index & 0x07)
    Vec8us v2(1, 2, 3, 4, 5, 6, 7, 8);
    assert(v2.extract(8) == 1);   // Should wrap to index 0
    assert(v2.extract(9) == 2);   // Should wrap to index 1
    assert(v2.extract(15) == 8);  // Should wrap to index 7

    // Test case 3: Extract maximum values
    Vec8us v3(0xFFFF);
    for(int i = 0; i < 8; i++) {
        assert(v3.extract(i) == 0xFFFF);
    }

    // Test case 4: Extract with negative indices (should wrap)
    Vec8us v4(1, 2, 3, 4, 5, 6, 7, 8);
    assert(v4.extract(-1) == 8);  // Should wrap to index 7
    assert(v4.extract(-2) == 7);  // Should wrap to index 6
    assert(v4.extract(-8) == 1);  // Should wrap to index 0

    // Test case 5: Extract from mixed values
    Vec8us v5(0x1234, 0xABCD, 0, 0xFFFF, 0x8000, 0x4000, 0x2000, 0x1000);
    assert(v5.extract(0) == 0x1234);
    assert(v5.extract(1) == 0xABCD);
    assert(v5.extract(2) == 0);
    assert(v5.extract(3) == 0xFFFF);
    assert(v5.extract(4) == 0x8000);
    assert(v5.extract(5) == 0x4000);
    assert(v5.extract(6) == 0x2000);
    assert(v5.extract(7) == 0x1000);

    std::cout << "test_extract passed!\n";
}

void test_array_subscript_operator() {
    // Test case 1: Access sequential values
    Vec8us v1(1, 2, 3, 4, 5, 6, 7, 8);
    for(int i = 0; i < 8; i++) {
        assert(v1[i] == i + 1);
    }

    // Test case 2: Access with index wrapping (index & 0x07)
    Vec8us v2(1, 2, 3, 4, 5, 6, 7, 8);
    assert(v2[8] == 1);   // Should wrap to index 0
    assert(v2[9] == 2);   // Should wrap to index 1
    assert(v2[15] == 8);  // Should wrap to index 7

    // Test case 3: Access maximum values
    Vec8us v3(0xFFFF);
    for(int i = 0; i < 8; i++) {
        assert(v3[i] == 0xFFFF);
    }

    // Test case 4: Access with negative indices (should wrap)
    Vec8us v4(1, 2, 3, 4, 5, 6, 7, 8);
    assert(v4[-1] == 8);  // Should wrap to index 7
    assert(v4[-2] == 7);  // Should wrap to index 6
    assert(v4[-8] == 1);  // Should wrap to index 0

    // Test case 5: Access mixed values
    Vec8us v5(0x1234, 0xABCD, 0, 0xFFFF, 0x8000, 0x4000, 0x2000, 0x1000);
    assert(v5[0] == 0x1234);
    assert(v5[1] == 0xABCD);
    assert(v5[2] == 0);
    assert(v5[3] == 0xFFFF);
    assert(v5[4] == 0x8000);
    assert(v5[5] == 0x4000);
    assert(v5[6] == 0x2000);
    assert(v5[7] == 0x1000);

    std::cout << "test_array_subscript_operator passed!\n";
}

void test_add_operator() {
    // Test case 1: Basic addition
    Vec8us a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b1(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us c1 = a1 + b1;
    for(int i = 0; i < 8; i++) {
        assert(c1[i] == i + 2);
    }

    // Test case 2: Addition with zeros
    Vec8us a2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b2(0);
    Vec8us c2 = a2 + b2;
    for(int i = 0; i < 8; i++) {
        assert(c2[i] == i + 1);
    }

    // Test case 3: Addition with saturation
    Vec8us a3(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
    Vec8us b3(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us c3 = a3 + b3;
    for(int i = 0; i < 8; i++) {
        assert(c3[i] == 0xFFFF); // Should saturate at maximum value
    }

    // Test case 4: Mixed value addition
    Vec8us a4(0x1000, 0x2000, 0x3000, 0x4000, 0x5000, 0x6000, 0x7000, 0x8000);
    Vec8us b4(0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600, 0x0700, 0x0800);
    Vec8us c4 = a4 + b4;
    assert(c4[0] == 0x1100);
    assert(c4[1] == 0x2200);
    assert(c4[2] == 0x3300);
    assert(c4[3] == 0x4400);
    assert(c4[4] == 0x5500);
    assert(c4[5] == 0x6600);
    assert(c4[6] == 0x7700);
    assert(c4[7] == 0x8800);

    std::cout << "test_add_operator passed!\n";
}
void test_add_assign_operator() {
    // Test case 1: Basic addition
    Vec8us a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b1(1, 1, 1, 1, 1, 1, 1, 1);
    a1 += b1;
    for(int i = 0; i < 8; i++) {
        assert(a1[i] == i + 2);
    }

    // Test case 2: Addition with zeros 
    Vec8us a2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b2(0);
    a2 += b2;
    for(int i = 0; i < 8; i++) {
        assert(a2[i] == i + 1);
    }

    // Test case 3: Addition with saturation
    Vec8us a3(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
    Vec8us b3(1, 1, 1, 1, 1, 1, 1, 1);
    a3 += b3;
    for(int i = 0; i < 8; i++) {
        assert(a3[i] == 0xFFFF); // Should saturate at maximum value
    }

    // Test case 4: Mixed value addition
    Vec8us a4(0x1000, 0x2000, 0x3000, 0x4000, 0x5000, 0x6000, 0x7000, 0x8000);
    Vec8us b4(0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600, 0x0700, 0x0800);
    a4 += b4;
    assert(a4[0] == 0x1100);
    assert(a4[1] == 0x2200);
    assert(a4[2] == 0x3300);
    assert(a4[3] == 0x4400);
    assert(a4[4] == 0x5500);
    assert(a4[5] == 0x6600);
    assert(a4[6] == 0x7700);
    assert(a4[7] == 0x8800);

    std::cout << "test_add_equals_operator passed!\n";
}
void test_postfix_increment_operator() {
    // Test case 1: Basic increment
    Vec8us a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b1 = a1++;
    // Check original values were returned
    for(int i = 0; i < 8; i++) {
        assert(b1[i] == i + 1);
    }
    // Check values were incremented
    for(int i = 0; i < 8; i++) {
        assert(a1[i] == i + 2);
    }

    // Test case 2: Increment from zero
    Vec8us a2(0);
    Vec8us b2 = a2++;
    // Check original values were returned
    for(int i = 0; i < 8; i++) {
        assert(b2[i] == 0);
    }
    // Check values were incremented
    for(int i = 0; i < 8; i++) {
        assert(a2[i] == 1);
    }

    // Test case 3: Increment with saturation
    Vec8us a3(0xFFFF);
    Vec8us b3 = a3++;
    // Check original values were returned
    for(int i = 0; i < 8; i++) {
        assert(b3[i] == 0xFFFF);
    }
    // Check values remained at maximum
    for(int i = 0; i < 8; i++) {
        assert(a3[i] == 0xFFFF);  // Should saturate at maximum value
    }

    // Test case 4: Multiple increments
    Vec8us a4(0x1000);
    Vec8us b4 = a4++;
    Vec8us c4 = a4++;
    // Check original values were returned
    for(int i = 0; i < 8; i++) {
        assert(b4[i] == 0x1000);
        assert(c4[i] == 0x1001);
    }
    // Check final values after both increments
    for(int i = 0; i < 8; i++) {
        assert(a4[i] == 0x1002);
    }

    std::cout << "test_postfix_increment_operator passed!\n";
}
void test_prefix_increment_operator() {
    // Test case 1: Basic increment
    Vec8us a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us& b1 = ++a1;
    // Check values were incremented
    for(int i = 0; i < 8; i++) {
        assert(a1[i] == i + 2);
        assert(b1[i] == i + 2); // Reference should point to incremented value
    }
    // Verify b1 is reference to a1
    assert(&b1 == &a1);

    // Test case 2: Increment from zero
    Vec8us a2(0);
    Vec8us& b2 = ++a2;
    // Check values were incremented
    for(int i = 0; i < 8; i++) {
        assert(a2[i] == 1);
        assert(b2[i] == 1); // Reference should point to incremented value
    }
    // Verify b2 is reference to a2  
    assert(&b2 == &a2);

    // Test case 3: Increment with saturation
    Vec8us a3(0xFFFF);
    Vec8us& b3 = ++a3;
    // Check values remained at maximum
    for(int i = 0; i < 8; i++) {
        assert(a3[i] == 0xFFFF); // Should saturate at maximum value
        assert(b3[i] == 0xFFFF);
    }
    // Verify b3 is reference to a3
    assert(&b3 == &a3);

    // Test case 4: Multiple increments
    Vec8us a4(0x1000);
    Vec8us& b4 = ++(++a4);
    // Check values after both increments
    for(int i = 0; i < 8; i++) {
        assert(a4[i] == 0x1002);
        assert(b4[i] == 0x1002);
    }
    // Verify b4 is reference to a4
    assert(&b4 == &a4);

    std::cout << "test_prefix_increment_operator passed!\n";
}

void test_subtract_operator() {
    // Test case 1: Basic subtraction
    Vec8us a1(10, 11, 12, 13, 14, 15, 16, 17);
    Vec8us b1(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us c1 = a1 - b1;
    for(int i = 0; i < 8; i++) {
        assert(c1[i] == 9 + i);
    }

    // Test case 2: Subtraction with zeros
    Vec8us a2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b2(0);
    Vec8us c2 = a2 - b2;
    for(int i = 0; i < 8; i++) {
        assert(c2[i] == i + 1);
    }

    // Test case 3: Subtraction with saturation (prevent underflow)
    Vec8us a3(0, 0, 0, 0, 0, 0, 0, 0);
    Vec8us b3(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us c3 = a3 - b3;
    for(int i = 0; i < 8; i++) {
        assert(c3[i] == 0); // Should saturate at minimum value
    }

    // Test case 4: Mixed value subtraction
    Vec8us a4(0x1100, 0x2200, 0x3300, 0x4400, 0x5500, 0x6600, 0x7700, 0x8800);
    Vec8us b4(0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600, 0x0700, 0x0800);
    Vec8us c4 = a4 - b4;
    assert(c4[0] == 0x1000);
    assert(c4[1] == 0x2000);
    assert(c4[2] == 0x3000);
    assert(c4[3] == 0x4000);
    assert(c4[4] == 0x5000);
    assert(c4[5] == 0x6000);
    assert(c4[6] == 0x7000);
    assert(c4[7] == 0x8000);

    std::cout << "test_subtract_operator passed!\n";
}
void test_subtract_equals_operator() {
    // Test case 1: Basic subtraction
    Vec8us a1(10, 11, 12, 13, 14, 15, 16, 17);
    Vec8us b1(1, 1, 1, 1, 1, 1, 1, 1);
    a1 -= b1;
    for(int i = 0; i < 8; i++) {
        assert(a1[i] == 9 + i);
    }

    // Test case 2: Subtraction with zeros
    Vec8us a2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b2(0);
    a2 -= b2;
    for(int i = 0; i < 8; i++) {
        assert(a2[i] == i + 1);
    }

    // Test case 3: Subtraction with saturation
    Vec8us a3(0, 0, 0, 0, 0, 0, 0, 0);
    Vec8us b3(1, 1, 1, 1, 1, 1, 1, 1);
    a3 -= b3;
    for(int i = 0; i < 8; i++) {
        assert(a3[i] == 0); // Should saturate at minimum value
    }

    // Test case 4: Mixed value subtraction
    Vec8us a4(0x1100, 0x2200, 0x3300, 0x4400, 0x5500, 0x6600, 0x7700, 0x8800);
    Vec8us b4(0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600, 0x0700, 0x0800);
    a4 -= b4;
    assert(a4[0] == 0x1000);
    assert(a4[1] == 0x2000);
    assert(a4[2] == 0x3000);
    assert(a4[3] == 0x4000);
    assert(a4[4] == 0x5000);
    assert(a4[5] == 0x6000);
    assert(a4[6] == 0x7000);
    assert(a4[7] == 0x8000);

    std::cout << "test_subtract_equals_operator passed!\n";
}

void test_postfix_decrement_operator() {
    // Test case 1: Basic decrement
    Vec8us a1(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8us b1 = a1--;
    // Check original values were returned
    for(int i = 0; i < 8; i++) {
        assert(b1[i] == i + 2);
    }
    // Check values were decremented
    for(int i = 0; i < 8; i++) {
        assert(a1[i] == i + 1);
    }

    // Test case 2: Decrement towards zero
    Vec8us a2(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us b2 = a2--;
    // Check original values were returned
    for(int i = 0; i < 8; i++) {
        assert(b2[i] == 1);
    }
    // Check values were decremented to zero
    for(int i = 0; i < 8; i++) {
        assert(a2[i] == 0);
    }

    // Test case 3: Decrement with saturation
    Vec8us a3(0);
    Vec8us b3 = a3--;
    // Check original values were returned
    for(int i = 0; i < 8; i++) {
        assert(b3[i] == 0);
    }
    // Check values remained at minimum
    for(int i = 0; i < 8; i++) {
        assert(a3[i] == 0); // Should saturate at minimum value
    }

    std::cout << "test_postfix_decrement_operator passed!\n";
}
void test_prefix_decrement_operator() {
    // Test case 1: Basic decrement
    Vec8us a1(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8us& b1 = --a1;
    // Check values were decremented
    for(int i = 0; i < 8; i++) {
        assert(a1[i] == i + 1);
        assert(b1[i] == i + 1); // Reference should point to decremented value
    }
    // Verify b1 is reference to a1
    assert(&b1 == &a1);

    // Test case 2: Decrement towards zero
    Vec8us a2(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us& b2 = --a2;
    // Check values were decremented to zero
    for(int i = 0; i < 8; i++) {
        assert(a2[i] == 0);
        assert(b2[i] == 0);
    }
    // Verify b2 is reference to a2
    assert(&b2 == &a2);

    // Test case 3: Decrement with saturation
    Vec8us a3(0);
    Vec8us& b3 = --a3;
    // Check values remained at minimum
    for(int i = 0; i < 8; i++) {
        assert(a3[i] == 0); // Should saturate at minimum value
        assert(b3[i] == 0);
    }
    // Verify b3 is reference to a3
    assert(&b3 == &a3);

    std::cout << "test_prefix_decrement_operator passed!\n";
}

void test_multiply_operator() {
    // Test case 1: Basic multiplication
    Vec8us a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b1(2, 2, 2, 2, 2, 2, 2, 2);
    Vec8us c1 = a1 * b1;
    for(int i = 0; i < 8; i++) {
        assert(c1[i] == (i + 1) * 2);
    }

    // Test case 2: Multiplication with zero
    Vec8us a2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b2(0);
    Vec8us c2 = a2 * b2;
    for(int i = 0; i < 8; i++) {
        assert(c2[i] == 0);
    }

    // Test case 3: Multiplication with ones (identity)
    Vec8us a3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b3(1);
    Vec8us c3 = a3 * b3;
    for(int i = 0; i < 8; i++) {
        assert(c3[i] == i + 1);
    }

    // Test case 4: Test with larger numbers
    Vec8us a4(100, 200, 300, 400, 500, 600, 700, 800);
    Vec8us b4(3, 3, 3, 3, 3, 3, 3, 3);
    Vec8us c4 = a4 * b4;
    assert(c4[0] == 300);
    assert(c4[1] == 600);
    assert(c4[2] == 900);
    assert(c4[3] == 1200);
    assert(c4[4] == 1500);
    assert(c4[5] == 1800);
    assert(c4[6] == 2100);
    assert(c4[7] == 2400);

    // Test case 5: Test multiplication near maximum values
    Vec8us a5(0xFFFF, 0x8000, 0x4000, 0x2000, 
              0x1000, 0x0800, 0x0400, 0x0200);
    Vec8us b5(2, 2, 2, 2, 2, 2, 2, 2);
    Vec8us c5 = a5 * b5;
    // Values that would overflow are truncated to 16 bits
    assert(c5[0] == 0xFFFE);
    assert(c5[1] == 0x0000); // 0x8000 * 2 = 0x10000 truncated to 16 bits = 0
    assert(c5[2] == 0x8000);
    assert(c5[3] == 0x4000);
    assert(c5[4] == 0x2000);
    assert(c5[5] == 0x1000);
    assert(c5[6] == 0x0800);
    assert(c5[7] == 0x0400);

    std::cout << "test_multiply_operator passed!\n";
}
void test_multiply_equals_operator() {
    // Test case 1: Basic multiplication
    Vec8us a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b1(2, 2, 2, 2, 2, 2, 2, 2);
    a1 *= b1;
    for(int i = 0; i < 8; i++) {
        assert(a1[i] == (i + 1) * 2);
    }

    // Test case 2: Multiplication with zero
    Vec8us a2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b2(0);
    a2 *= b2;
    for(int i = 0; i < 8; i++) {
        assert(a2[i] == 0);
    }

    // Test case 3: Multiplication with ones (identity)
    Vec8us a3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b3(1);
    a3 *= b3;
    for(int i = 0; i < 8; i++) {
        assert(a3[i] == i + 1);
    }

    // Test case 4: Test with larger numbers
    Vec8us a4(100, 200, 300, 400, 500, 600, 700, 800);
    Vec8us b4(3, 3, 3, 3, 3, 3, 3, 3);
    a4 *= b4;
    assert(a4[0] == 300);
    assert(a4[1] == 600);
    assert(a4[2] == 900);
    assert(a4[3] == 1200);
    assert(a4[4] == 1500);
    assert(a4[5] == 1800);
    assert(a4[6] == 2100);
    assert(a4[7] == 2400);

    // Test case 5: Test multiplication near maximum values
    Vec8us a5(0xFFFF, 0x8000, 0x4000, 0x2000, 
              0x1000, 0x0800, 0x0400, 0x0200);
    Vec8us b5(2, 2, 2, 2, 2, 2, 2, 2);
    a5 *= b5;
    // Values that would overflow are truncated to 16 bits
    assert(a5[0] == 0xFFFE);
    assert(a5[1] == 0x0000); // 0x8000 * 2 = 0x10000 truncated to 16 bits = 0
    assert(a5[2] == 0x8000);
    assert(a5[3] == 0x4000);
    assert(a5[4] == 0x2000);
    assert(a5[5] == 0x1000);
    assert(a5[6] == 0x0800);
    assert(a5[7] == 0x0400);

    std::cout << "test_multiply_equals_operator passed!\n";
}

void test_shift_left_operator() {
    // Test case 1: Basic left shift by 1
    Vec8us a1(1, 2, 4, 8, 16, 32, 64, 128);
    Vec8us b1 = a1 << 1;
    for(int i = 0; i < 8; i++) {
        assert(b1[i] == (a1[i] << 1));
    }

    // Test case 2: Left shift by 4
    Vec8us a2(0x1111, 0x2222, 0x3333, 0x4444, 
              0x5555, 0x6666, 0x7777, 0x8888);
    Vec8us b2 = a2 << 4;
    for(int i = 0; i < 8; i++) {
        assert(b2[i] == static_cast<uint16_t>((a2[i]) << 4));
    }

    // Test case 3: Left shift by 8 (half the bits)
    Vec8us a3(0x00FF, 0xFF00, 0x0F0F, 0xF0F0,
              0x5555, 0xAAAA, 0x3333, 0xCCCC);
    Vec8us b3 = a3 << 8;
    for(int i = 0; i < 8; i++) {
        assert(b3[i] == static_cast<uint16_t>((a3[i]) << 8));
    }

    // Test case 4: Left shift that clears all bits
    Vec8us a4(0xFFFF);
    Vec8us b4 = a4 << 16;
    for(int i = 0; i < 8; i++) {
        assert(b4[i] == 0);
    }

    std::cout << "test_shift_left_operator passed!\n";
}
void test_shift_left_equals_operator() {
    // Test case 1: Basic left shift by 1
    Vec8us a1(1, 2, 4, 8, 16, 32, 64, 128);
    Vec8us expected1 = a1 << 1;
    a1 <<= 1;
    for(int i = 0; i < 8; i++) {
        assert(a1[i] == expected1[i]);
    }

    // Test case 2: Left shift by 4
    Vec8us a2(0x1111, 0x2222, 0x3333, 0x4444,
              0x5555, 0x6666, 0x7777, 0x8888);
    Vec8us expected2 = a2 << 4;
    a2 <<= 4;
    for(int i = 0; i < 8; i++) {
        assert(a2[i] == expected2[i]);
    }

    // Test case 3: Left shift by 8
    Vec8us a3(0x00FF, 0xFF00, 0x0F0F, 0xF0F0,
              0x5555, 0xAAAA, 0x3333, 0xCCCC);
    Vec8us expected3 = a3 << 8;
    a3 <<= 8;
    for(int i = 0; i < 8; i++) {
        assert(a3[i] == expected3[i]);
    }

    // Test case 4: Left shift that clears all bits
    Vec8us a4(0xFFFF);
    a4 <<= 16;
    for(int i = 0; i < 8; i++) {
        assert(a4[i] == 0);
    }

    std::cout << "test_shift_left_equals_operator passed!\n";
}
void test_shift_right_operator() {
    // Test case 1: Basic right shift by 1
    Vec8us a1(2, 4, 8, 16, 32, 64, 128, 256);
    Vec8us b1 = a1 >> 1;
    for(int i = 0; i < 8; i++) {
        assert(b1[i] == (a1[i] >> 1));
    }

    // Test case 2: Right shift by 4
    Vec8us a2(0x1110, 0x2220, 0x3330, 0x4440,
              0x5550, 0x6660, 0x7770, 0x8880);
    Vec8us b2 = a2 >> 4;
    for(int i = 0; i < 8; i++) {
        assert(b2[i] == (a2[i] >> 4));
    }

    // Test case 3: Right shift by 8 (half the bits)
    Vec8us a3(0xFF00, 0x00FF, 0xF0F0, 0x0F0F,
              0x5555, 0xAAAA, 0x3333, 0xCCCC);
    Vec8us b3 = a3 >> 8;
    for(int i = 0; i < 8; i++) {
        assert(b3[i] == (a3[i] >> 8));
    }

    // Test case 4: Right shift that clears all bits
    Vec8us a4(0xFFFF);
    Vec8us b4 = a4 >> 16;
    for(int i = 0; i < 8; i++) {
        assert(b4[i] == 0);
    }

    std::cout << "test_shift_right_operator passed!\n";
}
void test_shift_right_equals_operator() {
    // Test case 1: Basic right shift by 1
    Vec8us a1(2, 4, 8, 16, 32, 64, 128, 256);
    Vec8us expected1 = a1 >> 1;
    a1 >>= 1;
    for(int i = 0; i < 8; i++) {
        assert(a1[i] == expected1[i]);
    }

    // Test case 2: Right shift by 4
    Vec8us a2(0x1110, 0x2220, 0x3330, 0x4440,
              0x5550, 0x6660, 0x7770, 0x8880);
    Vec8us expected2 = a2 >> 4;
    a2 >>= 4;
    for(int i = 0; i < 8; i++) {
        assert(a2[i] == expected2[i]);
    }

    // Test case 3: Right shift by 8
    Vec8us a3(0xFF00, 0x00FF, 0xF0F0, 0x0F0F,
              0x5555, 0xAAAA, 0x3333, 0xCCCC);
    Vec8us expected3 = a3 >> 8;
    a3 >>= 8;
    for(int i = 0; i < 8; i++) {
        assert(a3[i] == expected3[i]);
    }

    // Test case 4: Right shift that clears all bits
    Vec8us a4(0xFFFF);
    a4 >>= 16;
    for(int i = 0; i < 8; i++) {
        assert(a4[i] == 0);
    }

    std::cout << "test_shift_right_equals_operator passed!\n";
}

// Comparison Operation Tests
void test_operator_equal() {
    // Test case 1: Equal values
    Vec8us a1(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us b1(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result1 = (a1 == b1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0xFFFF); // All bits set indicates true
    }

    // Test case 2: Unequal values
    Vec8us a2(1, 2, 3, 4, 5, 6, 7, 8);  
    Vec8us b2(8, 7, 6, 5, 4, 3, 2, 1);
    Vec8us result2 = (a2 == b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0); // All bits clear indicates false
    }

    // Test case 3: Mix of equal and unequal values
    Vec8us a3(1, 2, 1, 2, 1, 2, 1, 2);
    Vec8us b3(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result3 = (a3 == b3);
    assert(result3[0] == 0xFFFF); // Equal
    assert(result3[1] == 0);      // Unequal
    assert(result3[2] == 0xFFFF); // Equal
    assert(result3[3] == 0);      // Unequal
    assert(result3[4] == 0xFFFF); // Equal
    assert(result3[5] == 0);      // Unequal
    assert(result3[6] == 0xFFFF); // Equal
    assert(result3[7] == 0);      // Unequal

    // Test case 4: Compare with zero
    Vec8us a4(0, 0, 0, 0, 1, 1, 1, 1);
    Vec8us b4(0);
    Vec8us result4 = (a4 == b4);
    for(int i = 0; i < 4; i++) {
        assert(result4[i] == 0xFFFF); // First 4 elements equal to zero
    }
    for(int i = 4; i < 8; i++) {
        assert(result4[i] == 0); // Last 4 elements not equal to zero
    }

    std::cout << "test_operator_equal passed!\n";
}
void test_operator_not_equal() {
    // Test case 1: All values equal (should return all false)
    Vec8us a1(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us b1(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result1 = (a1 != b1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0); // All bits clear indicates false (values are equal)
    }

    // Test case 2: All values unequal (should return all true)
    Vec8us a2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b2(8, 7, 6, 5, 4, 3, 2, 1);
    Vec8us result2 = (a2 != b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0xFFFF); // All bits set indicates true (values are unequal)
    }

    // Test case 3: Mix of equal and unequal values
    Vec8us a3(1, 2, 1, 2, 1, 2, 1, 2);
    Vec8us b3(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result3 = (a3 != b3);
    assert(result3[0] == 0);      // Equal
    assert(result3[1] == 0xFFFF); // Unequal
    assert(result3[2] == 0);      // Equal
    assert(result3[3] == 0xFFFF); // Unequal
    assert(result3[4] == 0);      // Equal
    assert(result3[5] == 0xFFFF); // Unequal
    assert(result3[6] == 0);      // Equal
    assert(result3[7] == 0xFFFF); // Unequal

    // Test case 4: Compare with zero
    Vec8us a4(0, 0, 0, 0, 1, 1, 1, 1);
    Vec8us b4(0);
    Vec8us result4 = (a4 != b4);
    for(int i = 0; i < 4; i++) {
        assert(result4[i] == 0); // First 4 elements equal to zero
    }
    for(int i = 4; i < 8; i++) {
        assert(result4[i] == 0xFFFF); // Last 4 elements not equal to zero
    }

    // Test case 5: Compare maximum values
    Vec8us a5(0xFFFF);
    Vec8us b5(0xFFFF);
    Vec8us result5 = (a5 != b5);
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == 0); // All elements are equal
    }

    // Test case 6: Compare with mixed maximum values
    Vec8us a6(0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0);
    Vec8us b6(0, 0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0, 0xFFFF);
    Vec8us result6 = (a6 != b6);
    for(int i = 0; i < 8; i++) {
        assert(result6[i] == 0xFFFF); // All elements are unequal
    }
    std::cout << "test_operator_not_equal passed!\n";
}
void test_greater_than_operator() {
    // Test case 1: Basic greater than comparison
    Vec8us a1(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8us b1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us result1 = (a1 > b1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0xFFFF); // All elements in a1 are greater than b1
    }

    // Test case 2: Basic less than comparison
    Vec8us a2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b2(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8us result2 = (a2 > b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0); // All elements in a2 are less than b2
    }

    // Test case 3: Equal values comparison
    Vec8us a3(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us b3(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result3 = (a3 > b3);
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == 0); // Equal elements should return false
    }

    // Test case 4: Mixed comparisons
    Vec8us a4(5, 2, 7, 4, 9, 6, 3, 8);
    Vec8us b4(3, 4, 5, 6, 7, 8, 9, 2);
    Vec8us result4 = (a4 > b4);
    assert(result4[0] == 0xFFFF); // 5 > 3
    assert(result4[1] == 0);      // 2 < 4
    assert(result4[2] == 0xFFFF); // 7 > 5
    assert(result4[3] == 0);      // 4 < 6
    assert(result4[4] == 0xFFFF); // 9 > 7
    assert(result4[5] == 0);      // 6 < 8
    assert(result4[6] == 0);      // 3 < 9
    assert(result4[7] == 0xFFFF); // 8 > 2

    // Test case 5: Compare with zero
    Vec8us a5(1, 2, 0, 4, 0, 6, 0, 8);
    Vec8us b5(0);
    Vec8us result5 = (a5 > b5);
    assert(result5[0] == 0xFFFF); // 1 > 0
    assert(result5[1] == 0xFFFF); // 2 > 0
    assert(result5[2] == 0);      // 0 = 0
    assert(result5[3] == 0xFFFF); // 4 > 0
    assert(result5[4] == 0);      // 0 = 0
    assert(result5[5] == 0xFFFF); // 6 > 0
    assert(result5[6] == 0);      // 0 = 0
    assert(result5[7] == 0xFFFF); // 8 > 0

    // Test case 6: Compare with maximum values
    Vec8us a6(0xFFFF, 0xFFFE, 0xFFFF, 0xFFFE, 0xFFFF, 0xFFFE, 0xFFFF, 0xFFFE);
    Vec8us b6(0xFFFE, 0xFFFF, 0xFFFE, 0xFFFF, 0xFFFE, 0xFFFF, 0xFFFE, 0xFFFF);
    Vec8us result6 = (a6 > b6);
    for(int i = 0; i < 8; i += 2) {
        assert(result6[i] == 0xFFFF);   // 0xFFFF > 0xFFFE
        assert(result6[i+1] == 0);      // 0xFFFE < 0xFFFF
    }

    std::cout << "test_greater_than_operator passed!\n";
}
void test_less_than_operator() {
    // Test case 1: Basic less than comparison
    Vec8us a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b1(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8us result1 = (a1 < b1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0xFFFF); // All elements in a1 are less than b1
    }

    // Test case 2: Basic greater than comparison
    Vec8us a2(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8us b2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us result2 = (a2 < b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0); // All elements in a2 are greater than b2
    }

    // Test case 3: Equal values comparison
    Vec8us a3(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us b3(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result3 = (a3 < b3);
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == 0); // Equal elements should return false
    }

    // Test case 4: Mixed comparisons
    Vec8us a4(3, 4, 5, 6, 7, 8, 9, 2);
    Vec8us b4(5, 2, 7, 4, 9, 6, 3, 8);
    Vec8us result4 = (a4 < b4);
    assert(result4[0] == 0xFFFF); // 3 < 5
    assert(result4[1] == 0);      // 4 > 2
    assert(result4[2] == 0xFFFF); // 5 < 7
    assert(result4[3] == 0);      // 6 > 4
    assert(result4[4] == 0xFFFF); // 7 < 9
    assert(result4[5] == 0);      // 8 > 6
    assert(result4[6] == 0);      // 9 > 3
    assert(result4[7] == 0xFFFF); // 2 < 8

    // Test case 5: Compare with zero
    Vec8us a5(0, 1, 0, 2, 0, 3, 0, 4);
    Vec8us b5(1, 0, 2, 0, 3, 0, 4, 0);
    Vec8us result5 = (a5 < b5);
    assert(result5[0] == 0xFFFF); // 0 < 1
    assert(result5[1] == 0);      // 1 > 0
    assert(result5[2] == 0xFFFF); // 0 < 2
    assert(result5[3] == 0);      // 2 > 0
    assert(result5[4] == 0xFFFF); // 0 < 3
    assert(result5[5] == 0);      // 3 > 0
    assert(result5[6] == 0xFFFF); // 0 < 4
    assert(result5[7] == 0);      // 4 > 0

    // Test case 6: Compare with maximum values
    Vec8us a6(0xFFFE, 0xFFFF, 0xFFFE, 0xFFFF, 0xFFFE, 0xFFFF, 0xFFFE, 0xFFFF);
    Vec8us b6(0xFFFF, 0xFFFE, 0xFFFF, 0xFFFE, 0xFFFF, 0xFFFE, 0xFFFF, 0xFFFE);
    Vec8us result6 = (a6 < b6);
    for(int i = 0; i < 8; i += 2) {
        assert(result6[i] == 0xFFFF);   // 0xFFFE < 0xFFFF
        assert(result6[i+1] == 0);      // 0xFFFF > 0xFFFE
    }

    std::cout << "test_less_than_operator passed!\n";
}
void test_greater_than_or_equal_operator() {
    // Test case 1: Greater than comparison
    Vec8us a1(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8us b1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us result1 = (a1 >= b1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0xFFFF); // All elements in a1 are greater than b1
    }

    // Test case 2: Equal values comparison
    Vec8us a2(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us b2(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result2 = (a2 >= b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0xFFFF); // Equal elements should return true
    }

    // Test case 3: Less than comparison
    Vec8us a3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b3(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8us result3 = (a3 >= b3);
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == 0); // All elements in a3 are less than b3
    }

    // Test case 4: Mixed comparisons
    Vec8us a4(5, 2, 7, 4, 9, 6, 3, 8);
    Vec8us b4(5, 4, 5, 6, 7, 6, 9, 2);
    Vec8us result4 = (a4 >= b4);
    assert(result4[0] == 0xFFFF); // 5 = 5
    assert(result4[1] == 0);      // 2 < 4
    assert(result4[2] == 0xFFFF); // 7 > 5
    assert(result4[3] == 0);      // 4 < 6
    assert(result4[4] == 0xFFFF); // 9 > 7
    assert(result4[5] == 0xFFFF); // 6 = 6
    assert(result4[6] == 0);      // 3 < 9
    assert(result4[7] == 0xFFFF); // 8 > 2

    // Test case 5: Compare with zero
    Vec8us a5(1, 0, 2, 0, 3, 0, 4, 0);
    Vec8us b5(0);
    Vec8us result5 = (a5 >= b5);
    for(int i = 0; i < 8; i++) {
        if(a5[i] == 0) {
            assert(result5[i] == 0xFFFF); // Equal to zero
        } else {
            assert(result5[i] == 0xFFFF); // Greater than zero
        }
    }

    // Test case 6: Compare with maximum values
    Vec8us a6(0xFFFF, 0xFFFF, 0xFFFE, 0xFFFE, 0xFFFF, 0xFFFE, 0xFFFF, 0xFFFE);
    Vec8us b6(0xFFFF, 0xFFFE, 0xFFFF, 0xFFFE, 0xFFFE, 0xFFFF, 0xFFFF, 0xFFFF);
    Vec8us result6 = (a6 >= b6);
    assert(result6[0] == 0xFFFF); // Equal
    assert(result6[1] == 0xFFFF); // Greater
    assert(result6[2] == 0);      // Less
    assert(result6[3] == 0xFFFF); // Equal
    assert(result6[4] == 0xFFFF); // Greater
    assert(result6[5] == 0);      // Less
    assert(result6[6] == 0xFFFF); // Equal
    assert(result6[7] == 0);      // Less

    std::cout << "test_greater_than_or_equal_operator passed!\n";
}
void test_less_than_or_equal_operator() {
    // Test case 1: Less than comparison
    Vec8us a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b1(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8us result1 = (a1 <= b1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0xFFFF); // All elements in a1 are less than b1
    }

    // Test case 2: Equal values comparison
    Vec8us a2(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us b2(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result2 = (a2 <= b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0xFFFF); // Equal elements should return true
    }

    // Test case 3: Greater than comparison
    Vec8us a3(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8us b3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us result3 = (a3 <= b3);
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == 0); // All elements in a3 are greater than b3
    }

    // Test case 4: Mixed comparisons
    Vec8us a4(5, 2, 7, 4, 9, 6, 3, 8);
    Vec8us b4(5, 4, 5, 6, 7, 6, 9, 2);
    Vec8us result4 = (a4 <= b4);
    assert(result4[0] == 0xFFFF); // 5 = 5
    assert(result4[1] == 0xFFFF); // 2 < 4
    assert(result4[2] == 0);      // 7 > 5
    assert(result4[3] == 0xFFFF); // 4 < 6
    assert(result4[4] == 0);      // 9 > 7
    assert(result4[5] == 0xFFFF); // 6 = 6
    assert(result4[6] == 0xFFFF); // 3 < 9
    assert(result4[7] == 0);      // 8 > 2

    // Test case 5: Compare with zero
    Vec8us a5(0, 1, 0, 2, 0, 3, 0, 4);
    Vec8us b5(0);
    Vec8us result5 = (a5 <= b5);
    for(int i = 0; i < 8; i++) {
        if(a5[i] == 0) {
            assert(result5[i] == 0xFFFF); // Equal to zero
        } else {
            assert(result5[i] == 0); // Greater than zero
        }
    }

    // Test case 6: Compare with maximum values
    Vec8us a6(0xFFFF, 0xFFFF, 0xFFFE, 0xFFFE, 0xFFFF, 0xFFFE, 0xFFFF, 0xFFFE);
    Vec8us b6(0xFFFF, 0xFFFE, 0xFFFF, 0xFFFE, 0xFFFE, 0xFFFF, 0xFFFF, 0xFFFF);
    Vec8us result6 = (a6 <= b6);
    assert(result6[0] == 0xFFFF); // Equal
    assert(result6[1] == 0);      // Greater
    assert(result6[2] == 0xFFFF); // Less
    assert(result6[3] == 0xFFFF); // Equal
    assert(result6[4] == 0);      // Greater
    assert(result6[5] == 0xFFFF); // Less
    assert(result6[6] == 0xFFFF); // Equal
    assert(result6[7] == 0xFFFF); // Less

    std::cout << "test_less_than_or_equal_operator passed!\n";
}

void test_bitwise_and_operator() {
    // Test case 1: Basic AND operation
    Vec8us a1(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
    Vec8us b1(0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF);
    Vec8us result1 = a1 & b1;
    assert(result1[0] == 0x0000);
    assert(result1[1] == 0xFFFF);
    assert(result1[2] == 0x0000);
    assert(result1[3] == 0xFFFF);
    assert(result1[4] == 0x0000);
    assert(result1[5] == 0xFFFF);
    assert(result1[6] == 0x0000);
    assert(result1[7] == 0xFFFF);

    // Test case 2: AND with zero
    Vec8us a2(0xFFFF, 0xAAAA, 0x5555, 0xF0F0, 0x0F0F, 0xCCCC, 0x3333, 0xFFFF);
    Vec8us b2(0);
    Vec8us result2 = a2 & b2;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: AND with patterns
    Vec8us a3(0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA);
    Vec8us b3(0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555);
    Vec8us result3 = a3 & b3;
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == 0);
    }

    // Test case 4: Self AND
    Vec8us a4(0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0);
    Vec8us result4 = a4 & a4;
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == 0xF0F0);
    }

    // Test case 5: Mixed patterns
    Vec8us a5(0xFFFF, 0xF0F0, 0xAAAA, 0x5555, 0x3333, 0xCCCC, 0x0F0F, 0xFF00);
    Vec8us b5(0xFF00, 0x0F0F, 0x5555, 0xAAAA, 0xCCCC, 0x3333, 0xF0F0, 0xFFFF);
    Vec8us result5 = a5 & b5;
    assert(result5[0] == 0xFF00);
    assert(result5[1] == 0x0000);
    assert(result5[2] == 0x0000);
    assert(result5[3] == 0x0000);
    assert(result5[4] == 0x0000);
    assert(result5[5] == 0x0000);
    assert(result5[6] == 0x0000);
    assert(result5[7] == 0xFF00);

    std::cout << "test_bitwise_and_operator passed!\n";
}
void test_bitwise_or_operator() {
    // Test case 1: Basic OR operation
    Vec8us a1(0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000);
    Vec8us b1(0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000);
    Vec8us result1 = a1 | b1;
    assert(result1[0] == 0xFFFF);
    assert(result1[1] == 0x0000);
    assert(result1[2] == 0xFFFF);
    assert(result1[3] == 0x0000);
    assert(result1[4] == 0xFFFF);
    assert(result1[5] == 0x0000);
    assert(result1[6] == 0xFFFF);
    assert(result1[7] == 0x0000);

    // Test case 2: OR with all bits set
    Vec8us a2(0xAAAA, 0x5555, 0xF0F0, 0x0F0F, 0xCCCC, 0x3333, 0xFF00, 0x00FF);
    Vec8us b2(0xFFFF);
    Vec8us result2 = a2 | b2;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0xFFFF);
    }

    // Test case 3: OR with alternating patterns
    Vec8us a3(0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA);
    Vec8us b3(0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555);
    Vec8us result3 = a3 | b3;
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == 0xFFFF);
    }

    // Test case 4: OR with self
    Vec8us a4(0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0, 0xF0F0);
    Vec8us result4 = a4 | a4;
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == 0xF0F0);
    }

    // Test case 5: OR with zero
    Vec8us a5(0xFFFF, 0xF0F0, 0xAAAA, 0x5555, 0x3333, 0xCCCC, 0x0F0F, 0xFF00);
    Vec8us b5(0);
    Vec8us result5 = a5 | b5;
    assert(result5[0] == 0xFFFF);
    assert(result5[1] == 0xF0F0);
    assert(result5[2] == 0xAAAA);
    assert(result5[3] == 0x5555);
    assert(result5[4] == 0x3333);
    assert(result5[5] == 0xCCCC);
    assert(result5[6] == 0x0F0F);
    assert(result5[7] == 0xFF00);

    std::cout << "test_bitwise_or_operator passed!\n";
}
void test_bitwise_xor_operator() {
    // Test case 1: XOR with zero (identity)
    Vec8us a1(0xFFFF, 0xAAAA, 0x5555, 0xF0F0, 0x0F0F, 0xCCCC, 0x3333, 0xFF00);
    Vec8us b1(0);
    Vec8us result1 = a1 ^ b1;
    assert(result1[0] == 0xFFFF);
    assert(result1[1] == 0xAAAA); 
    assert(result1[2] == 0x5555);
    assert(result1[3] == 0xF0F0);
    assert(result1[4] == 0x0F0F);
    assert(result1[5] == 0xCCCC);
    assert(result1[6] == 0x3333);
    assert(result1[7] == 0xFF00);

    // Test case 2: XOR with same value (should be zero)
    Vec8us a2(0xFFFF, 0xAAAA, 0x5555, 0xF0F0, 0x0F0F, 0xCCCC, 0x3333, 0xFF00);
    Vec8us result2 = a2 ^ a2;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: XOR with alternating patterns
    Vec8us a3(0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA, 0xAAAA);
    Vec8us b3(0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555, 0x5555);
    Vec8us result3 = a3 ^ b3;
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == 0xFFFF);
    }

    // Test case 4: XOR with all bits set
    Vec8us a4(0xFFFF, 0xAAAA, 0x5555, 0xF0F0, 0x0F0F, 0xCCCC, 0x3333, 0xFF00);
    Vec8us b4(0xFFFF);
    Vec8us result4 = a4 ^ b4;
    assert(result4[0] == 0x0000);
    assert(result4[1] == 0x5555);
    assert(result4[2] == 0xAAAA);
    assert(result4[3] == 0x0F0F);
    assert(result4[4] == 0xF0F0);
    assert(result4[5] == 0x3333);
    assert(result4[6] == 0xCCCC);
    assert(result4[7] == 0x00FF);

    // Test case 5: XOR with mixed patterns
    Vec8us a5(0xFF00, 0x00FF, 0xF0F0, 0x0F0F, 0xCCCC, 0x3333, 0xAAAA, 0x5555);
    Vec8us b5(0x00FF, 0xFF00, 0x0F0F, 0xF0F0, 0x3333, 0xCCCC, 0x5555, 0xAAAA);
    Vec8us result5 = a5 ^ b5;
    assert(result5[0] == 0xFFFF);
    assert(result5[1] == 0xFFFF);
    assert(result5[2] == 0xFFFF);
    assert(result5[3] == 0xFFFF);
    assert(result5[4] == 0xFFFF);
    assert(result5[5] == 0xFFFF);
    assert(result5[6] == 0xFFFF);
    assert(result5[7] == 0xFFFF);

    std::cout << "test_bitwise_xor_operator passed!\n";
}
void test_bitwise_not_operator() {
    // Test case 1: NOT of zero gives all bits set
    Vec8us a1(0);
    Vec8us result1 = ~a1;
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == 0xFFFF);
    }

    // Test case 2: NOT of all bits set gives zero
    Vec8us a2(0xFFFF);
    Vec8us result2 = ~a2;
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: NOT of alternating bits
    Vec8us a3(0xAAAA, 0x5555, 0xF0F0, 0x0F0F, 0xCCCC, 0x3333, 0xFF00, 0x00FF);
    Vec8us result3 = ~a3;
    assert(result3[0] == 0x5555); // NOT of 0xAAAA
    assert(result3[1] == 0xAAAA); // NOT of 0x5555
    assert(result3[2] == 0x0F0F); // NOT of 0xF0F0
    assert(result3[3] == 0xF0F0); // NOT of 0x0F0F
    assert(result3[4] == 0x3333); // NOT of 0xCCCC
    assert(result3[5] == 0xCCCC); // NOT of 0x3333
    assert(result3[6] == 0x00FF); // NOT of 0xFF00
    assert(result3[7] == 0xFF00); // NOT of 0x00FF

    // Test case 4: Double NOT should give original value
    Vec8us a4(0x1234, 0x5678, 0x9ABC, 0xDEF0, 0x2468, 0xACE0, 0x1357, 0x9BDF);
    Vec8us result4 = ~~a4;
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == a4[i]);
    }

    std::cout << "test_bitwise_not_operator passed!\n";
}

void test_select() {
    // Test case 1: Basic selection with all true condition
    Vec8us mask1(0xFFFF);
    Vec8us a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b1(9, 10, 11, 12, 13, 14, 15, 16);
    Vec8us result1 = select(mask1, a1, b1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == a1[i]); // Should select all from a1
    }

    // Test case 2: Basic selection with all false condition
    Vec8us mask2(0);
    Vec8us a2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b2(9, 10, 11, 12, 13, 14, 15, 16);
    Vec8us result2 = select(mask2, a2, b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == b2[i]); // Should select all from b2
    }

    // Test case 3: Alternating selection pattern
    Vec8us mask3(0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0);
    Vec8us a3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b3(9, 10, 11, 12, 13, 14, 15, 16);
    Vec8us result3 = select(mask3, a3, b3);
    assert(result3[0] == 1);  // From a3
    assert(result3[1] == 10); // From b3
    assert(result3[2] == 3);  // From a3
    assert(result3[3] == 12); // From b3
    assert(result3[4] == 5);  // From a3
    assert(result3[5] == 14); // From b3
    assert(result3[6] == 7);  // From a3
    assert(result3[7] == 16); // From b3

    // Test case 4: Selection with maximum values
    Vec8us mask4(0xFFFF, 0xFFFF, 0, 0, 0xFFFF, 0xFFFF, 0, 0);
    Vec8us a4(0xFFFF);
    Vec8us b4(0);
    Vec8us result4 = select(mask4, a4, b4);
    assert(result4[0] == 0xFFFF);
    assert(result4[1] == 0xFFFF);
    assert(result4[2] == 0);
    assert(result4[3] == 0);
    assert(result4[4] == 0xFFFF);
    assert(result4[5] == 0xFFFF);
    assert(result4[6] == 0);
    assert(result4[7] == 0);

    // Test case 5: Selection with mixed patterns
    Vec8us mask5(0xAAAA, 0x5555, 0xF0F0, 0x0F0F, 0xCCCC, 0x3333, 0xFF00, 0x00FF);
    Vec8us a5(0xFFFF);
    Vec8us b5(0);
    Vec8us result5 = select(mask5, a5, b5);
    assert(result5[0] == 0xAAAA);
    assert(result5[1] == 0x5555);
    assert(result5[2] == 0xF0F0);
    assert(result5[3] == 0x0F0F);
    assert(result5[4] == 0xCCCC);
    assert(result5[5] == 0x3333);
    assert(result5[6] == 0xFF00);
    assert(result5[7] == 0x00FF);

    std::cout << "test_select passed!\n";
}
void test_if_add() {
    // Test case 1: Add with all true conditions
    Vec8us mask1(0xFFFF);
    Vec8us a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b1(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result1 = if_add(mask1, a1, b1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == a1[i] + b1[i]); // Should add all values
    }

    // Test case 2: Add with all false conditions
    Vec8us mask2(0);
    Vec8us a2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b2(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result2 = if_add(mask2, a2, b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == a2[i]); // Should not add anything
    }

    // Test case 3: Alternating conditions
    Vec8us mask3(0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0);
    Vec8us a3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b3(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result3 = if_add(mask3, a3, b3);
    assert(result3[0] == 2);  // 1 + 1
    assert(result3[1] == 2);  // 2 + 0
    assert(result3[2] == 4);  // 3 + 1
    assert(result3[3] == 4);  // 4 + 0
    assert(result3[4] == 6);  // 5 + 1
    assert(result3[5] == 6);  // 6 + 0
    assert(result3[6] == 8);  // 7 + 1
    assert(result3[7] == 8);  // 8 + 0

    // Test case 4: Add with saturation
    Vec8us mask4(0xFFFF);
    Vec8us a4(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
    Vec8us b4(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result4 = if_add(mask4, a4, b4);
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == 0xFFFF); // Should saturate at maximum value
    }

    // Test case 5: Add with mixed values
    Vec8us mask5(0xFFFF, 0xFFFF, 0, 0, 0xFFFF, 0xFFFF, 0, 0);
    Vec8us a5(0x1000, 0x2000, 0x3000, 0x4000, 0x5000, 0x6000, 0x7000, 0x8000);
    Vec8us b5(0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600, 0x0700, 0x0800);
    Vec8us result5 = if_add(mask5, a5, b5);
    assert(result5[0] == 0x1100); // 0x1000 + 0x0100
    assert(result5[1] == 0x2200); // 0x2000 + 0x0200
    assert(result5[2] == 0x3000); // 0x3000 + 0
    assert(result5[3] == 0x4000); // 0x4000 + 0
    assert(result5[4] == 0x5500); // 0x5000 + 0x0500
    assert(result5[5] == 0x6600); // 0x6000 + 0x0600
    assert(result5[6] == 0x7000); // 0x7000 + 0
    assert(result5[7] == 0x8000); // 0x8000 + 0

    std::cout << "test_if_add passed!\n";
}
void test_if_sub() {
    // Test case 1: Subtract with all true conditions
    Vec8us mask1(0xFFFF);
    Vec8us a1(10, 11, 12, 13, 14, 15, 16, 17);
    Vec8us b1(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result1 = if_sub(mask1, a1, b1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == a1[i] - b1[i]); // Should subtract all values
    }

    // Test case 2: Subtract with all false conditions
    Vec8us mask2(0);
    Vec8us a2(10, 11, 12, 13, 14, 15, 16, 17);
    Vec8us b2(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result2 = if_sub(mask2, a2, b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == a2[i]); // Should not subtract anything
    }

    // Test case 3: Alternating conditions
    Vec8us mask3(0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0);
    Vec8us a3(10, 11, 12, 13, 14, 15, 16, 17);
    Vec8us b3(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result3 = if_sub(mask3, a3, b3);
    assert(result3[0] == 9);   // 10 - 1
    assert(result3[1] == 11);  // 11 - 0
    assert(result3[2] == 11);  // 12 - 1
    assert(result3[3] == 13);  // 13 - 0
    assert(result3[4] == 13);  // 14 - 1
    assert(result3[5] == 15);  // 15 - 0
    assert(result3[6] == 15);  // 16 - 1
    assert(result3[7] == 17);  // 17 - 0

    // Test case 4: Subtract with saturation prevention
    Vec8us mask4(0xFFFF);
    Vec8us a4(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b4(2, 3, 4, 5, 6, 7, 8, 9);
    Vec8us result4 = if_sub(mask4, a4, b4);
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == 0); // Should saturate at minimum value
    }

    // Test case 5: Subtract with mixed values
    Vec8us mask5(0xFFFF, 0xFFFF, 0, 0, 0xFFFF, 0xFFFF, 0, 0);
    Vec8us a5(0x1100, 0x2200, 0x3300, 0x4400, 0x5500, 0x6600, 0x7700, 0x8800);
    Vec8us b5(0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600, 0x0700, 0x0800);
    Vec8us result5 = if_sub(mask5, a5, b5);
    assert(result5[0] == 0x1000); // 0x1100 - 0x0100
    assert(result5[1] == 0x2000); // 0x2200 - 0x0200
    assert(result5[2] == 0x3300); // 0x3300 - 0
    assert(result5[3] == 0x4400); // 0x4400 - 0
    assert(result5[4] == 0x5000); // 0x5500 - 0x0500
    assert(result5[5] == 0x6000); // 0x6600 - 0x0600
    assert(result5[6] == 0x7700); // 0x7700 - 0
    assert(result5[7] == 0x8800); // 0x8800 - 0

    std::cout << "test_if_sub passed!\n";
}
void test_if_mul() {
    // Test case 1: Multiply with all true conditions
    Vec8us mask1(0xFFFF);
    Vec8us a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b1(2, 2, 2, 2, 2, 2, 2, 2);
    Vec8us result1 = if_mul(mask1, a1, b1);
    for(int i = 0; i < 8; i++) {
        assert(result1[i] == a1[i] * b1[i]); // Should multiply all values
    }

    // Test case 2: Multiply with all false conditions
    Vec8us mask2(0);
    Vec8us a2(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b2(2, 2, 2, 2, 2, 2, 2, 2);
    Vec8us result2 = if_mul(mask2, a2, b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == a2[i]); // Should not multiply anything
    }

    // Test case 3: Alternating conditions
    Vec8us mask3(0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0, 0xFFFF, 0);
    Vec8us a3(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b3(2, 2, 2, 2, 2, 2, 2, 2);
    Vec8us result3 = if_mul(mask3, a3, b3);
    assert(result3[0] == 2);  // 1 * 2
    assert(result3[1] == 2);  // 2 (unchanged)
    assert(result3[2] == 6);  // 3 * 2
    assert(result3[3] == 4);  // 4 (unchanged)
    assert(result3[4] == 10); // 5 * 2
    assert(result3[5] == 6);  // 6 (unchanged)
    assert(result3[6] == 14); // 7 * 2
    assert(result3[7] == 8);  // 8 (unchanged)

    // Test case 4: Multiply with larger values
    Vec8us mask4(0xFFFF);
    Vec8us a4(100, 200, 300, 400, 500, 600, 700, 800);
    Vec8us b4(3, 3, 3, 3, 3, 3, 3, 3);
    Vec8us result4 = if_mul(mask4, a4, b4);
    assert(result4[0] == 300);
    assert(result4[1] == 600);
    assert(result4[2] == 900);
    assert(result4[3] == 1200);
    assert(result4[4] == 1500);
    assert(result4[5] == 1800);
    assert(result4[6] == 2100);
    assert(result4[7] == 2400);

    // Test case 5: Multiply near maximum values
    Vec8us mask5(0xFFFF, 0xFFFF, 0, 0, 0xFFFF, 0xFFFF, 0, 0);
    Vec8us a5(0x1000, 0x2000, 0x3000, 0x4000, 0x5000, 0x6000, 0x7000, 0x8000);
    Vec8us b5(0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002);
    Vec8us result5 = if_mul(mask5, a5, b5);
    assert(result5[0] == 0x2000); // 0x1000 * 2
    assert(result5[1] == 0x4000); // 0x2000 * 2
    assert(result5[2] == 0x3000); // unchanged
    assert(result5[3] == 0x4000); // unchanged
    assert(result5[4] == 0xA000); // 0x5000 * 2
    assert(result5[5] == 0xC000); // 0x6000 * 2
    assert(result5[6] == 0x7000); // unchanged
    assert(result5[7] == 0x8000); // unchanged

    std::cout << "test_if_mul passed!\n";
}

void test_horizontal_add() {
    // Test case 1: Basic addition of all ones
    Vec8us a1(1, 1, 1, 1, 1, 1, 1, 1);
    uint32_t result1 = horizontal_add(a1);
    assert(result1 == 8); // Sum should be 8

    // Test case 2: Addition of sequential numbers
    Vec8us a2(1, 2, 3, 4, 5, 6, 7, 8); 
    uint32_t result2 = horizontal_add(a2);
    assert(result2 == 36); // Sum should be 36

    // Test case 3: Addition with zeros
    Vec8us a3(0, 0, 0, 0, 0, 0, 0, 0);
    uint32_t result3 = horizontal_add(a3);
    assert(result3 == 0); // Sum should be 0

    // Test case 4: Addition of mixed values
    Vec8us a4(0xFFFF, 0x0001, 0x1000, 0x0100, 0x0010, 0x2000, 0x0200, 0x0020);
    uint32_t result4 = horizontal_add(a4);
    assert(result4 == 0x13330); // Sum of all values

    // Test case 5: Addition of maximum values
    Vec8us a5(0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF);
    uint32_t result5 = horizontal_add(a5);
    assert(result5 == 0x7FFF8); // Sum of eight 0xFFFF values

    std::cout << "test_horizontal_add passed!\n";
}

void test_max() {
    // Test case 1: Basic max comparison
    Vec8us a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b1(8, 7, 6, 5, 4, 3, 2, 1);
    Vec8us result1 = max(a1, b1);
    assert(result1[0] == 8);
    assert(result1[1] == 7);
    assert(result1[2] == 6);
    assert(result1[3] == 5); 
    assert(result1[4] == 5);
    assert(result1[5] == 6);
    assert(result1[6] == 7);
    assert(result1[7] == 8);

    // Test case 2: Max with equal values
    Vec8us a2(5, 5, 5, 5, 5, 5, 5, 5);
    Vec8us b2(5, 5, 5, 5, 5, 5, 5, 5);
    Vec8us result2 = max(a2, b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 5);
    }

    // Test case 3: Max with zeros 
    Vec8us a3(0, 0, 0, 0, 0, 0, 0, 0);
    Vec8us b3(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us result3 = max(a3, b3);
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == 1);
    }

    // Test case 4: Max with maximum values
    Vec8us a4(0xFFFF);
    Vec8us b4(0x7FFF, 0x8FFF, 0x9FFF, 0xAFFF, 0xBFFF, 0xCFFF, 0xDFFF, 0xEFFF);
    Vec8us result4 = max(a4, b4);
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == 0xFFFF);
    }

    // Test case 5: Max with mixed values
    Vec8us a5(0x1234, 0x5678, 0xABCD, 0x4321, 0x8765, 0xDCBA, 0x1111, 0xFFFF);
    Vec8us b5(0x4321, 0x1234, 0xDCBA, 0xABCD, 0x5678, 0x8765, 0xFFFF, 0x1111);
    Vec8us result5 = max(a5, b5);
    assert(result5[0] == 0x4321);
    assert(result5[1] == 0x5678);
    assert(result5[2] == 0xDCBA);
    assert(result5[3] == 0xABCD);
    assert(result5[4] == 0x8765);
    assert(result5[5] == 0xDCBA);
    assert(result5[6] == 0xFFFF);
    assert(result5[7] == 0xFFFF);

    std::cout << "test_max passed!\n";
}
void test_min() {
    // Test case 1: Basic min comparison
    Vec8us a1(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us b1(8, 7, 6, 5, 4, 3, 2, 1);
    Vec8us result1 = min(a1, b1);
    assert(result1[0] == 1);
    assert(result1[1] == 2);
    assert(result1[2] == 3);
    assert(result1[3] == 4);
    assert(result1[4] == 4);
    assert(result1[5] == 3);
    assert(result1[6] == 2);
    assert(result1[7] == 1);

    // Test case 2: Min with equal values
    Vec8us a2(5, 5, 5, 5, 5, 5, 5, 5);
    Vec8us b2(5, 5, 5, 5, 5, 5, 5, 5);
    Vec8us result2 = min(a2, b2);
    for(int i = 0; i < 8; i++) {
        assert(result2[i] == 5);
    }

    // Test case 3: Min with zeros
    Vec8us a3(1, 1, 1, 1, 1, 1, 1, 1);
    Vec8us b3(0, 0, 0, 0, 0, 0, 0, 0);
    Vec8us result3 = min(a3, b3);
    for(int i = 0; i < 8; i++) {
        assert(result3[i] == 0);
    }

    // Test case 4: Min with maximum values
    Vec8us a4(0xFFFF);
    Vec8us b4(0x7FFF, 0x8FFF, 0x9FFF, 0xAFFF, 0xBFFF, 0xCFFF, 0xDFFF, 0xEFFF);
    Vec8us result4 = min(a4, b4);
    assert(result4[0] == 0x7FFF);
    assert(result4[1] == 0x8FFF);
    assert(result4[2] == 0x9FFF);
    assert(result4[3] == 0xAFFF);
    assert(result4[4] == 0xBFFF);
    assert(result4[5] == 0xCFFF);
    assert(result4[6] == 0xDFFF);
    assert(result4[7] == 0xEFFF);

    // Test case 5: Min with mixed values
    Vec8us a5(0x1234, 0x5678, 0xABCD, 0x4321, 0x8765, 0xDCBA, 0x1111, 0xFFFF);
    Vec8us b5(0x4321, 0x1234, 0xDCBA, 0xABCD, 0x5678, 0x8765, 0xFFFF, 0x1111);
    Vec8us result5 = min(a5, b5);
    assert(result5[0] == 0x1234);
    assert(result5[1] == 0x1234); 
    assert(result5[2] == 0xABCD);
    assert(result5[3] == 0x4321);
    assert(result5[4] == 0x5678);
    assert(result5[5] == 0x8765);
    assert(result5[6] == 0x1111);
    assert(result5[7] == 0x1111);

    std::cout << "test_min passed!\n";
}

void test_rotate_left() {
    // Test case 1: Rotate left by 1
    Vec8us a(1, 2, 3, 4, 5, 6, 7, 8);
    Vec8us res1 = rotate_left(a, 1);
    for(int i = 0; i < 8; i++) {
        assert(res1[i] == (a[i] << 1));
    }

    // Test case 2: Rotate left by 4 
    Vec8us b(0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888);
    Vec8us res2 = rotate_left(b, 4);
    for(int i = 0; i < 8; i++) {
        uint16_t expected = (static_cast<uint16_t>(b[i]) << 4);
        assert(res2[i] == expected);
    }

    // Test case 3: Rotate left by 8
    Vec8us c(0x00FF, 0xFF00, 0x0F0F, 0xF0F0, 0x5555, 0xAAAA, 0x3333, 0xCCCC);
    Vec8us res3 = rotate_left(c, 8);
    for(int i = 0; i < 8; i++) {
        uint16_t expected = (static_cast<uint16_t>(c[i]) << 8);
        assert(res3[i] == expected);
    }

    // Test case 4: Rotate by 1
    Vec8us a1(0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080);
    Vec8us result1 = rotate_left(a1, 1);
    assert(result1[0] == 0x0002);
    assert(result1[1] == 0x0004);
    assert(result1[2] == 0x0008);
    assert(result1[3] == 0x0010);
    assert(result1[4] == 0x0020);
    assert(result1[5] == 0x0040);
    assert(result1[6] == 0x0080);
    assert(result1[7] == 0x0100);

    // Test case 5: Rotate by 4
    Vec8us a2(0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888);
    Vec8us result2 = rotate_left(a2, 4);
    assert(result2[0] == 0x1110);
    assert(result2[1] == 0x2220);
    assert(result2[2] == 0x3330);
    assert(result2[3] == 0x4440);
    assert(result2[4] == 0x5550);
    assert(result2[5] == 0x6660);
    assert(result2[6] == 0x7770);
    assert(result2[7] == 0x8880);

    // Test case 6: Rotate by 8 (half word)
    Vec8us a3(0x00FF, 0xFF00, 0x0F0F, 0xF0F0, 0x5555, 0xAAAA, 0x3333, 0xCCCC);
    Vec8us result3 = rotate_left(a3, 8);
    assert(result3[0] == 0xFF00);
    assert(result3[1] == 0x0000);
    assert(result3[2] == 0x0F00);
    assert(result3[3] == 0xF000);
    assert(result3[4] == 0x5500);
    assert(result3[5] == 0xAA00);
    assert(result3[6] == 0x3300);
    assert(result3[7] == 0xCC00);

    // Test case 7: Rotate zeros (should remain zero)
    Vec8us a4(0);
    Vec8us result4 = rotate_left(a4, 4);
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == 0);
    }

    // Test case 8: Rotate maximum value
    Vec8us a5(0xFFFF);
    Vec8us result5 = rotate_left(a5, 4);
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == 0xFFF0);
    }
}

void test_rotate_right() {
    // Test case 1: Rotate right by 1
    Vec8us a(2, 4, 6, 8, 10, 12, 14, 16);
    Vec8us res1 = rotate_right(a, 1);
    for(int i = 0; i < 8; i++) {
        assert(res1[i] == (a[i] >> 1));
    }

    // Test case 2: Rotate right by 4
    Vec8us b(0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888);
    Vec8us res2 = rotate_right(b, 4);
    for(int i = 0; i < 8; i++) {
        uint16_t expected = (static_cast<uint16_t>(b[i]) >> 4);
        assert(res2[i] == expected);
    }

    // Test case 3: Rotate right by 8
    Vec8us c(0xFF00, 0x00FF, 0xF0F0, 0x0F0F, 0x5555, 0xAAAA, 0xCCCC, 0x3333);
    Vec8us res3 = rotate_right(c, 8);
    for(int i = 0; i < 8; i++) {
        uint16_t expected = (static_cast<uint16_t>(c[i]) >> 8);
        assert(res3[i] == expected);
    }
    // Test case 4: Rotate by 1
    Vec8us a1(0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100);
    Vec8us result1 = rotate_right(a1, 1);
    assert(result1[0] == 0x0001);
    assert(result1[1] == 0x0002);
    assert(result1[2] == 0x0004);
    assert(result1[3] == 0x0008);
    assert(result1[4] == 0x0010);
    assert(result1[5] == 0x0020);
    assert(result1[6] == 0x0040);
    assert(result1[7] == 0x0080);

    // Test case 5: Rotate by 4
    Vec8us a2(0x1111, 0x2222, 0x3333, 0x4444, 0x5555, 0x6666, 0x7777, 0x8888);
    Vec8us result2 = rotate_right(a2, 4);
    assert(result2[0] == 0x0111);
    assert(result2[1] == 0x0222);
    assert(result2[2] == 0x0333);
    assert(result2[3] == 0x0444);
    assert(result2[4] == 0x0555);
    assert(result2[5] == 0x0666);
    assert(result2[6] == 0x0777);
    assert(result2[7] == 0x0888);

    // Test case 6: Rotate by 8 (half word)
    Vec8us a3(0xFF00, 0x00FF, 0xF0F0, 0x0F0F, 0xAAAA, 0x5555, 0xCCCC, 0x3333);
    Vec8us result3 = rotate_right(a3, 8);
    assert(result3[0] == 0x00FF);
    assert(result3[1] == 0x0000);
    assert(result3[2] == 0x00F0);
    assert(result3[3] == 0x000F);
    assert(result3[4] == 0x00AA);
    assert(result3[5] == 0x0055);
    assert(result3[6] == 0x00CC);
    assert(result3[7] == 0x0033);

    // Test case 7: Rotate zeros (should remain zero)
    Vec8us a4(0);
    Vec8us result4 = rotate_right(a4, 4);
    for(int i = 0; i < 8; i++) {
        assert(result4[i] == 0);
    }

    // Test case 8: Rotate maximum value
    Vec8us a5(0xFFFF);
    Vec8us result5 = rotate_right(a5, 4);
    for(int i = 0; i < 8; i++) {
        assert(result5[i] == 0x0FFF);
    }
}

int main() 
{
    test_default_constructor();
    test_broadcast_constructor();
    test_element_constructor();
    test_uint16x8t_constructor();
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