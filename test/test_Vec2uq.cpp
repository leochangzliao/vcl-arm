#include "../Vec2uq.h"
#include <iostream>
#include <cassert>

using namespace VCL_NAMESPACE;

void test_default_constructor() {
    // Test default constructor initializes to zero
    Vec2uq v;
    for(int i = 0; i < 2; i++) {
        assert(v[i] == 0);
    }
    
    // Test multiple instances
    Vec2uq v2;
    Vec2uq v3;
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == 0);
        assert(v3[i] == 0);
    }

    // Test value changes after default construction
    Vec2uq v4;
    v4 = Vec2uq(1,2); 
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == i+1);
    }
    std::cout << "test_default_constructor passed!\n";
}
void test_broadcast_constructor() {
    // Test case 1: Broadcast zero
    Vec2uq v1(0);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Broadcast maximum value
    Vec2uq v2(0xFFFFFFFFFFFFFFFFULL);
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == 0xFFFFFFFFFFFFFFFFULL);
    }

    // Test case 3: Broadcast arbitrary value
    Vec2uq v3(0x12345678);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == 0x12345678);
    }

    // Test case 4: Multiple instances with different values
    Vec2uq v4(0xAAAAAAAA);
    Vec2uq v5(0x55555555);
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == 0xAAAAAAAA);
        assert(v5[i] == 0x55555555);
    }
    std::cout << "test_broadcast_constructor passed!\n";
}
void test_element_constructor() {
    // Test case 1: Sequential values
    Vec2uq v1(0, 1);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == i);
    }

    // Test case 2: All same values
    Vec2uq v2(5, 5);
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == 5);
    }

    // Test case 3: Maximum values
    Vec2uq v3(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == 0xFFFFFFFFFFFFFFFFULL);
    }

    // Test case 4: Mixed values
    Vec2uq v4(0x12345678ABCDEF00ULL, 0xFFFFFFFF00000000ULL);
    assert(v4[0] == 0x12345678ABCDEF00ULL);
    assert(v4[1] == 0xFFFFFFFF00000000ULL);

    std::cout << "test_element_constructor passed!\n";
}
void test_uint64x2t_constructor() {
    // Test case 1: Create uint64x2_t with zeros and construct Vec2uq from it
    uint64_t data1[2] = {0, 0};
    uint64x2_t x1 = vld1q_u64(data1);
    Vec2uq v1(x1);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Create uint64x2_t with sequential values
    uint64_t data2[2] = {1, 2}; 
    uint64x2_t x2 = vld1q_u64(data2);
    Vec2uq v2(x2);
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Create uint64x2_t with maximum values
    uint64_t data3[2] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
    uint64x2_t x3 = vld1q_u64(data3);
    Vec2uq v3(x3);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == 0xFFFFFFFFFFFFFFFF);
    }

    // Test case 4: Create uint64x2_t with mixed values
    uint64_t data4[2] = {0x12345678ABCDEF00, 0xFFFFFFFF00000000};
    uint64x2_t x4 = vld1q_u64(data4);
    Vec2uq v4(x4);
    assert(v4[0] == 0x12345678ABCDEF00);
    assert(v4[1] == 0xFFFFFFFF00000000);
    std::cout << "test_uint64x2t_constructor passed!\n";
}
void test_copy_constructor() {
    // Test case 1: Copy constructor with zeros
    Vec2uq original1(0);
    Vec2uq copy1(original1);
    for(int i = 0; i < 2; i++) {
        assert(copy1[i] == 0);
    }

    // Test case 2: Copy constructor with sequential values
    Vec2uq original2(1, 2);
    Vec2uq copy2(original2);
    for(int i = 0; i < 2; i++) {
        assert(copy2[i] == i + 1);
    }

    // Test case 3: Copy constructor with maximum values
    Vec2uq original3(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
    Vec2uq copy3(original3);
    for(int i = 0; i < 2; i++) {
        assert(copy3[i] == 0xFFFFFFFFFFFFFFFF);
    }

    // Test case 4: Copy constructor with mixed values
    Vec2uq original4(0x12345678ABCDEF00, 0xFFFFFFFF00000000);
    Vec2uq copy4(original4);
    assert(copy4[0] == 0x12345678ABCDEF00);
    assert(copy4[1] == 0xFFFFFFFF00000000);
    std::cout << "test_copy_constructor passed!\n";
}
void test_assignment_operator() {
    // Test case 1: Assign zeros
    uint64_t data1[2] = {0, 0};
    uint64x2_t x1 = vld1q_u64(data1);
    Vec2uq v1;
    v1 = x1;
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Assign sequential values
    uint64_t data2[2] = {1, 2};
    uint64x2_t x2 = vld1q_u64(data2);
    Vec2uq v2;
    v2 = x2;
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Assign maximum values
    uint64_t data3[2] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
    uint64x2_t x3 = vld1q_u64(data3);
    Vec2uq v3;
    v3 = x3;
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == 0xFFFFFFFFFFFFFFFF);
    }

    // Test case 4: Assign mixed values
    uint64_t data4[2] = {0x12345678ABCDEF00, 0xFFFFFFFF00000000};
    uint64x2_t x4 = vld1q_u64(data4);
    Vec2uq v4;
    v4 = x4;
    assert(v4[0] == 0x12345678ABCDEF00);
    assert(v4[1] == 0xFFFFFFFF00000000);
    std::cout << "test_assignment_operator passed!\n";
}
void test_type_cast_operator() {
    // Test case 1: Cast zero values
    Vec2uq v1(0);
    uint64x2_t x1 = v1;
    uint64_t data1[2];
    vst1q_u64(data1, x1);
    for(int i = 0; i < 2; i++) {
        assert(data1[i] == 0);
    }

    // Test case 2: Cast sequential values
    Vec2uq v2(1, 2);
    uint64x2_t x2 = v2;
    uint64_t data2[2];
    vst1q_u64(data2, x2);
    for(int i = 0; i < 2; i++) {
        assert(data2[i] == i + 1);
    }

    // Test case 3: Cast maximum values
    Vec2uq v3(0xFFFFFFFFFFFFFFFFULL);
    uint64x2_t x3 = v3;
    uint64_t data3[2];
    vst1q_u64(data3, x3);
    for(int i = 0; i < 2; i++) {
        assert(data3[i] == 0xFFFFFFFFFFFFFFFFULL);
    }

    // Test case 4: Cast mixed values
    Vec2uq v4(0x12345678ABCDEF00ULL, 0xFFFFFFFF00000000ULL);
    uint64x2_t x4 = v4;
    uint64_t data4[2];
    vst1q_u64(data4, x4);
    assert(data4[0] == 0x12345678ABCDEF00ULL);
    assert(data4[1] == 0xFFFFFFFF00000000ULL);

    std::cout << "test_type_cast_operator passed!\n";
}

void test_load() {
    // Test case 1: Load zeros
    uint64_t data1[2] = {0, 0};
    Vec2uq v1;
    v1.load(data1);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Load sequential values 
    uint64_t data2[2] = {1, 2};
    Vec2uq v2;
    v2.load(data2);
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Load maximum values
    uint64_t data3[2] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
    Vec2uq v3;
    v3.load(data3);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == 0xFFFFFFFFFFFFFFFF);
    }

    // Test case 4: Load mixed values
    uint64_t data4[2] = {0x12345678ABCDEF00, 0xFFFFFFFF00000000};
    Vec2uq v4;
    v4.load(data4);
    assert(v4[0] == 0x12345678ABCDEF00);
    assert(v4[1] == 0xFFFFFFFF00000000);

    std::cout << "test_load passed!\n";
}
void test_load_a() {
    // Test case 1: Load aligned zeros
    alignas(16) uint64_t data1[2] = {0, 0};
    Vec2uq v1;
    v1.load_a(data1);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == 0);
    }

    // Test case 2: Load aligned sequential values
    alignas(16) uint64_t data2[2] = {1, 2};
    Vec2uq v2;
    v2.load_a(data2);
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == i + 1);
    }

    // Test case 3: Load aligned maximum values
    alignas(16) uint64_t data3[2] = {0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL};
    Vec2uq v3;
    v3.load_a(data3);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == 0xFFFFFFFFFFFFFFFFULL);
    }

    // Test case 4: Load aligned mixed values
    alignas(16) uint64_t data4[2] = {0x12345678ABCDEF00ULL, 0xFFFFFFFF00000000ULL};
    Vec2uq v4;
    v4.load_a(data4);
    assert(v4[0] == 0x12345678ABCDEF00ULL);
    assert(v4[1] == 0xFFFFFFFF00000000ULL);

    std::cout << "test_load_a passed!\n";
}
void test_store() {
    // Test case 1: Store zeros
    uint64_t data1[2];
    Vec2uq v1(0);
    v1.store(data1);
    for(int i = 0; i < 2; i++) {
        assert(data1[i] == 0);
    }

    // Test case 2: Store sequential values
    uint64_t data2[2];
    Vec2uq v2(1, 2);
    v2.store(data2);
    for(int i = 0; i < 2; i++) {
        assert(data2[i] == i + 1);
    }

    // Test case 3: Store maximum values
    uint64_t data3[2];
    Vec2uq v3(0xFFFFFFFFFFFFFFFFULL);
    v3.store(data3);
    for(int i = 0; i < 2; i++) {
        assert(data3[i] == 0xFFFFFFFFFFFFFFFFULL);
    }

    // Test case 4: Store mixed values
    uint64_t data4[2];
    Vec2uq v4(0x12345678ABCDEF00ULL, 0xFFFFFFFF00000000ULL);
    v4.store(data4);
    assert(data4[0] == 0x12345678ABCDEF00ULL);
    assert(data4[1] == 0xFFFFFFFF00000000ULL);

    std::cout << "test_store passed!\n";
}
void test_store_a() {
    // Test case 1: Store aligned zeros
    alignas(16) uint64_t data1[2];
    Vec2uq v1(0);
    v1.store_a(data1);
    for(int i = 0; i < 2; i++) {
        assert(data1[i] == 0);
    }

    // Test case 2: Store aligned sequential values 
    alignas(16) uint64_t data2[2];
    Vec2uq v2(1, 2);
    v2.store_a(data2);
    for(int i = 0; i < 2; i++) {
        assert(data2[i] == i + 1);
    }

    // Test case 3: Store aligned maximum values
    alignas(16) uint64_t data3[2];
    Vec2uq v3(0xFFFFFFFFFFFFFFFFULL);
    v3.store_a(data3);
    for(int i = 0; i < 2; i++) {
        assert(data3[i] == 0xFFFFFFFFFFFFFFFFULL);
    }

    // Test case 4: Store aligned mixed values
    alignas(16) uint64_t data4[2];
    Vec2uq v4(0x12345678ABCDEF00ULL, 0xFFFFFFFF00000000ULL);
    v4.store_a(data4);
    assert(data4[0] == 0x12345678ABCDEF00ULL);
    assert(data4[1] == 0xFFFFFFFF00000000ULL);

    std::cout << "test_store_a passed!\n";
}
void test_load_partial() {
    // Test case 1: Load full vector (n = 2)
    uint64_t data1[2] = {1, 2};
    Vec2uq v1;
    v1.load_partial(2, data1);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == i + 1);
    }

    // Test case 2: Load zero elements (n = 0)
    uint64_t data2[2] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
    Vec2uq v2;
    v2.load_partial(0, data2);
    for(int i = 0; i < 2; i++) {
        assert(v2[i] == 0);
    }

    // Test case 3: Load partial data (n = 1)
    uint64_t data3[2] = {0x12345678ABCDEF00, 0xFFFFFFFFFFFFFFFF};
    Vec2uq v3;
    v3.load_partial(1, data3);
    assert(v3[0] == 0x12345678ABCDEF00);
    assert(v3[1] == 0);

    // Test case 4: Load with negative n
    uint64_t data4[2] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
    Vec2uq v4;
    v4.load_partial(-1, data4);
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == 0);
    }

    std::cout << "test_load_partial passed!\n";
}
void test_store_partial() {
    // Test case 1: Store full vector (n = 2)
    uint64_t data1[2] = {0};
    Vec2uq v1(1, 2);
    v1.store_partial(2, data1);
    for(int i = 0; i < 2; i++) {
        assert(data1[i] == i + 1);
    }

    // Test case 2: Store zero elements (n = 0)
    uint64_t data2[2] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
    Vec2uq v2(1, 2);
    v2.store_partial(0, data2);
    for(int i = 0; i < 2; i++) {
        assert(data2[i] == 0xFFFFFFFFFFFFFFFF);
    }

    // Test case 3: Store partial data (n = 1)
    uint64_t data3[2] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
    Vec2uq v3(0x12345678ABCDEF00, 0xFFFFFFFF00000000);
    v3.store_partial(1, data3);
    assert(data3[0] == 0x12345678ABCDEF00);
    assert(data3[1] == 0xFFFFFFFFFFFFFFFF);

    // Test case 4: Store with negative n
    uint64_t data4[2] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF};
    Vec2uq v4(1, 2);
    v4.store_partial(-1, data4);
    for(int i = 0; i < 2; i++) {
        assert(data4[i] == 0xFFFFFFFFFFFFFFFF);
    }

    std::cout << "test_store_partial passed!\n";
}
void test_cutoff() {
    // Test case 1: n >= 2 (no cutoff)
    Vec2uq v1(1, 2);
    v1.cutoff(2);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == i + 1);
    }
    
    v1.cutoff(3);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == i + 1);
    }

    // Test case 2: n = 1 (cutoff half)
    Vec2uq v2(1, 2);
    v2.cutoff(1);
    assert(v2[0] == 1);
    assert(v2[1] == 0);

    // Test case 3: n = 0 (all zeros)
    Vec2uq v3(0xFFFF, 0xFFFF);
    v3.cutoff(0);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == 0);
    }

    // Test case 4: n < 0 (should zero all elements)
    Vec2uq v4(0xFFFF, 0xFFFF);
    v4.cutoff(-1);
    for(int i = 0; i < 2; i++) {
        assert(v4[i] == 0);
    }

    // Test case 5: Multiple cutoff operations
    Vec2uq v5(1, 2);
    v5.cutoff(2);
    v5.cutoff(1);  // Should reduce to 1 element
    assert(v5[0] == 1);
    assert(v5[1] == 0);

    std::cout << "test_cutoff passed!\n";
}
void test_and_assign_operator() {
    // Test case 1: AND with all bits set
    Vec2uq a(0xFFFF);
    Vec2uq b(0x5555);
    a &= b;
    for(int i = 0; i < 2; i++) {
        assert(a[i] == 0x5555);
    }

    // Test case 2: AND with zero
    Vec2uq c(0xFFFF);
    Vec2uq d(0);
    c &= d;
    for(int i = 0; i < 2; i++) {
        assert(c[i] == 0);
    }

    // Test case 3: AND with alternating patterns
    Vec2uq e(0xAAAA, 0x5555);
    Vec2uq f(0x5555, 0xAAAA);
    e &= f;
    assert(e[0] == 0x0000); // 0xAAAA & 0x5555
    assert(e[1] == 0x0000); // 0x5555 & 0xAAAA

    // Test case 4: AND with same value
    Vec2uq g(0xAAAA);
    Vec2uq h(0xAAAA);
    g &= h;
    for(int i = 0; i < 2; i++) {
        assert(g[i] == 0xAAAA);
    }

    std::cout << "test_and_equals_operator passed!\n";
}
void test_insert() {
    // Test case 1: Insert at each valid index
    Vec2uq v1(0);
    for(int i = 0; i < 2; i++) {
        v1 = v1.insert(i, i + 1);
        assert(v1[i] == i + 1);
    }

    // Test case 2: Insert with index wrapping (index & 0x01)
    Vec2uq v2(0);
    v2 = v2.insert(2, 1);  // Should wrap to index 0
    assert(v2[0] == 1);
    v2 = v2.insert(3, 2);  // Should wrap to index 1
    assert(v2[1] == 2);

    // Test case 3: Insert maximum values
    Vec2uq v3(0);
    for(int i = 0; i < 2; i++) {
        v3 = v3.insert(i, 0xFFFFFFFFFFFFFFFF);
        assert(v3[i] == 0xFFFFFFFFFFFFFFFF);
    }

    // Test case 4: Insert with negative indices (should wrap)
    Vec2uq v4(0);
    v4 = v4.insert(-1, 1);  // Should wrap to index 1
    assert(v4[1] == 1);
    v4 = v4.insert(-2, 2);  // Should wrap to index 0
    assert(v4[0] == 2);

    std::cout << "test_insert passed!\n";
}
void test_extract() {
    // Test case 1: Extract from sequence
    Vec2uq v1(1, 2);
    for(int i = 0; i < 2; i++) {
        assert(v1.extract(i) == i + 1);
    }

    // Test case 2: Extract with index wrapping (index & 0x01)
    Vec2uq v2(1, 2);
    assert(v2.extract(2) == 1);   // Should wrap to index 0
    assert(v2.extract(3) == 2);   // Should wrap to index 1
    assert(v2.extract(5) == 2);   // Should wrap to index 1

    // Test case 3: Extract maximum values
    Vec2uq v3(0xFFFFFFFFFFFFFFFF);
    for(int i = 0; i < 2; i++) {
        assert(v3.extract(i) == 0xFFFFFFFFFFFFFFFF);
    }

    // Test case 4: Extract with negative indices (should wrap)
    Vec2uq v4(1, 2);
    assert(v4.extract(-1) == 2);  // Should wrap to index 1
    assert(v4.extract(-2) == 1);  // Should wrap to index 0
    assert(v4.extract(-4) == 1);  // Should wrap to index 0

    // Test case 5: Extract from mixed values
    Vec2uq v5(0x12345678ABCDEF00, 0xFFFFFFFF00000000);
    assert(v5.extract(0) == 0x12345678ABCDEF00);
    assert(v5.extract(1) == 0xFFFFFFFF00000000);
    assert(v5.extract(2) == 0x12345678ABCDEF00);  // Wraps to index 0
    assert(v5.extract(3) == 0xFFFFFFFF00000000);  // Wraps to index 1

    std::cout << "test_extract passed!\n";
}
void test_array_subscript_operator() {
    // Test case 1: Access sequential values
    Vec2uq v1(1, 2);
    for(int i = 0; i < 2; i++) {
        assert(v1[i] == i + 1);
    }

    // Test case 2: Access with index wrapping (index & 0x01)
    Vec2uq v2(1, 2);
    assert(v2[2] == 1);   // Should wrap to index 0
    assert(v2[3] == 2);   // Should wrap to index 1

    // Test case 3: Access maximum values
    Vec2uq v3(0xFFFFFFFFFFFFFFFF);
    for(int i = 0; i < 2; i++) {
        assert(v3[i] == 0xFFFFFFFFFFFFFFFF);
    }

    // Test case 4: Access with negative indices (should wrap)
    Vec2uq v4(1, 2);
    assert(v4[-1] == 2);  // Should wrap to index 1
    assert(v4[-2] == 1);  // Should wrap to index 0

    // Test case 5: Access mixed values
    Vec2uq v5(0x12345678ABCDEF00, 0xFFFFFFFF00000000);
    assert(v5[0] == 0x12345678ABCDEF00);
    assert(v5[1] == 0xFFFFFFFF00000000);

    std::cout << "test_array_subscript_operator passed!\n";
}

void test_add_operator() {
    // Test case 1: Basic addition
    Vec2uq a1(1, 2);
    Vec2uq b1(1, 1);
    Vec2uq c1 = a1 + b1;
    for(int i = 0; i < 2; i++) {
        assert(c1[i] == i + 2);
    }

    // Test case 2: Addition with zeros
    Vec2uq a2(1, 2);
    Vec2uq b2(0);
    Vec2uq c2 = a2 + b2;
    for(int i = 0; i < 2; i++) {
        assert(c2[i] == i + 1);
    }

    // Test case 3: Addition with saturation
    Vec2uq a3(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL);
    Vec2uq b3(1, 1);
    Vec2uq c3 = a3 + b3;
    for(int i = 0; i < 2; i++) {
        assert(c3[i] == 0xFFFFFFFFFFFFFFFFULL); // Should saturate at maximum value
    }

    // Test case 4: Mixed value addition
    Vec2uq a4(0x1000000000000000ULL, 0x2000000000000000ULL);
    Vec2uq b4(0x0100000000000000ULL, 0x0200000000000000ULL);
    Vec2uq c4 = a4 + b4;
    assert(c4[0] == 0x1100000000000000ULL);
    assert(c4[1] == 0x2200000000000000ULL);

    std::cout << "test_add_operator passed!\n";
}
void test_add_assign_operator() {
    // Test case 1: Basic addition
    Vec2uq a1(1, 2);
    Vec2uq b1(1);
    a1 += b1;
    for(int i = 0; i < 2; i++) {
        assert(a1[i] == i + 2);
    }

    // Test case 2: Addition with zeros 
    Vec2uq a2(1, 2);
    Vec2uq b2(0);
    a2 += b2;
    for(int i = 0; i < 2; i++) {
        assert(a2[i] == i + 1);
    }

    // Test case 3: Addition with saturation
    Vec2uq a3(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL);
    Vec2uq b3(1);
    a3 += b3;
    for(int i = 0; i < 2; i++) {
        assert(a3[i] == 0xFFFFFFFFFFFFFFFFULL); // Should saturate at maximum value
    }

    // Test case 4: Mixed value addition
    Vec2uq a4(0x1000000000000000ULL, 0x2000000000000000ULL);
    Vec2uq b4(0x0100000000000000ULL, 0x0200000000000000ULL);
    a4 += b4;
    assert(a4[0] == 0x1100000000000000ULL);
    assert(a4[1] == 0x2200000000000000ULL);

    std::cout << "test_add_equals_operator passed!\n";
}
void test_postfix_increment_operator() {
    // Test case 1: Basic increment
    Vec2uq a1(1, 2);
    Vec2uq b1 = a1++;
    // Check original values were returned
    for(int i = 0; i < 2; i++) {
        assert(b1[i] == i + 1);
    }
    // Check values were incremented
    for(int i = 0; i < 2; i++) {
        assert(a1[i] == i + 2);
    }

    // Test case 2: Increment from zero
    Vec2uq a2(0);
    Vec2uq b2 = a2++;
    // Check original values were returned
    for(int i = 0; i < 2; i++) {
        assert(b2[i] == 0);
    }
    // Check values were incremented
    for(int i = 0; i < 2; i++) {
        assert(a2[i] == 1);
    }

    // Test case 3: Increment with saturation
    Vec2uq a3(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq b3 = a3++;
    // Check original values were returned
    for(int i = 0; i < 2; i++) {
        assert(b3[i] == 0xFFFFFFFFFFFFFFFFULL);
    }
    // Check values remained at maximum
    for(int i = 0; i < 2; i++) {
        assert(a3[i] == 0xFFFFFFFFFFFFFFFFULL);  // Should saturate at maximum value
    }

    // Test case 4: Multiple increments
    Vec2uq a4(0x1000);
    Vec2uq b4 = a4++;
    Vec2uq c4 = a4++;
    // Check original values were returned
    for(int i = 0; i < 2; i++) {
        assert(b4[i] == 0x1000);
        assert(c4[i] == 0x1001);
    }
    // Check final values after both increments
    for(int i = 0; i < 2; i++) {
        assert(a4[i] == 0x1002);
    }

    std::cout << "test_postfix_increment_operator passed!\n";
}
void test_prefix_increment_operator() {
    // Test case 1: Basic increment
    Vec2uq a1(1, 2);
    Vec2uq& b1 = ++a1;
    // Check values were incremented
    for(int i = 0; i < 2; i++) {
        assert(a1[i] == i + 2);
        assert(b1[i] == i + 2); // Reference should point to incremented value
    }
    // Verify b1 is reference to a1
    assert(&b1 == &a1);

    // Test case 2: Increment from zero
    Vec2uq a2(0);
    Vec2uq& b2 = ++a2;
    // Check values were incremented
    for(int i = 0; i < 2; i++) {
        assert(a2[i] == 1);
        assert(b2[i] == 1); // Reference should point to incremented value
    }
    // Verify b2 is reference to a2  
    assert(&b2 == &a2);

    // Test case 3: Increment with saturation
    Vec2uq a3(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq& b3 = ++a3;
    // Check values remained at maximum
    for(int i = 0; i < 2; i++) {
        assert(a3[i] == 0xFFFFFFFFFFFFFFFFULL); // Should saturate at maximum value
        assert(b3[i] == 0xFFFFFFFFFFFFFFFFULL);
    }
    // Verify b3 is reference to a3
    assert(&b3 == &a3);

    // Test case 4: Multiple increments
    Vec2uq a4(0x1000);
    Vec2uq& b4 = ++(++a4);
    // Check values after both increments
    for(int i = 0; i < 2; i++) {
        assert(a4[i] == 0x1002);
        assert(b4[i] == 0x1002);
    }
    // Verify b4 is reference to a4
    assert(&b4 == &a4);

    std::cout << "test_prefix_increment_operator passed!\n";
}

void test_subtract_operator() {
    // Test case 1: Basic subtraction
    Vec2uq a1(10, 11);
    Vec2uq b1(1, 1);
    Vec2uq c1 = a1 - b1;
    for(int i = 0; i < 2; i++) {
        assert(c1[i] == 9 + i);
    }

    // Test case 2: Subtraction with zeros
    Vec2uq a2(1, 2);
    Vec2uq b2(0);
    Vec2uq c2 = a2 - b2;
    for(int i = 0; i < 2; i++) {
        assert(c2[i] == i + 1);
    }

    // Test case 3: Subtraction with saturation (prevent underflow)
    Vec2uq a3(0, 0);
    Vec2uq b3(1, 1);
    Vec2uq c3 = a3 - b3;
    for(int i = 0; i < 2; i++) {
        assert(c3[i] == 0); // Should saturate at minimum value
    }

    // Test case 4: Mixed value subtraction
    Vec2uq a4(0x1100, 0x2200);
    Vec2uq b4(0x0100, 0x0200);
    Vec2uq c4 = a4 - b4;
    assert(c4[0] == 0x1000);
    assert(c4[1] == 0x2000);

    std::cout << "test_subtract_operator passed!\n";
}
void test_subtract_equals_operator() {
    // Test case 1: Basic subtraction
    Vec2uq a1(10, 11);
    Vec2uq b1(1, 1);
    a1 -= b1;
    for(int i = 0; i < 2; i++) {
        assert(a1[i] == 9 + i);
    }

    // Test case 2: Subtraction with zeros
    Vec2uq a2(1, 2);
    Vec2uq b2(0);
    a2 -= b2;
    for(int i = 0; i < 2; i++) {
        assert(a2[i] == i + 1);
    }

    // Test case 3: Subtraction with saturation
    Vec2uq a3(0, 0);
    Vec2uq b3(1, 1);
    a3 -= b3;
    for(int i = 0; i < 2; i++) {
        assert(a3[i] == 0); // Should saturate at minimum value
    }

    // Test case 4: Mixed value subtraction
    Vec2uq a4(0x1100, 0x2200);
    Vec2uq b4(0x0100, 0x0200);
    a4 -= b4;
    assert(a4[0] == 0x1000);
    assert(a4[1] == 0x2000);

    std::cout << "test_subtract_equals_operator passed!\n";
}
void test_postfix_decrement_operator() {
    // Test case 1: Basic decrement
    Vec2uq a1(2, 3);
    Vec2uq b1 = a1--;
    // Check original values were returned
    for(int i = 0; i < 2; i++) {
        assert(b1[i] == i + 2);
    }
    // Check values were decremented
    for(int i = 0; i < 2; i++) {
        assert(a1[i] == i + 1);
    }

    // Test case 2: Decrement towards zero
    Vec2uq a2(1, 1);
    Vec2uq b2 = a2--;
    // Check original values were returned
    for(int i = 0; i < 2; i++) {
        assert(b2[i] == 1);
    }
    // Check values were decremented to zero
    for(int i = 0; i < 2; i++) {
        assert(a2[i] == 0);
    }

    // Test case 3: Decrement with saturation
    Vec2uq a3(0);
    Vec2uq b3 = a3--;
    // Check original values were returned
    for(int i = 0; i < 2; i++) {
        assert(b3[i] == 0);
    }
    // Check values remained at minimum
    for(int i = 0; i < 2; i++) {
        assert(a3[i] == 0); // Should saturate at minimum value
    }

    std::cout << "test_postfix_decrement_operator passed!\n";
}
void test_prefix_decrement_operator() {
    // Test case 1: Basic decrement
    Vec2uq a1(2, 3);
    Vec2uq& b1 = --a1;
    // Check values were decremented
    for(int i = 0; i < 2; i++) {
        assert(a1[i] == i + 1);
        assert(b1[i] == i + 1); // Reference should point to decremented value
    }
    // Verify b1 is reference to a1
    assert(&b1 == &a1);

    // Test case 2: Decrement towards zero
    Vec2uq a2(1, 1);
    Vec2uq& b2 = --a2;
    // Check values were decremented to zero
    for(int i = 0; i < 2; i++) {
        assert(a2[i] == 0);
        assert(b2[i] == 0);
    }
    // Verify b2 is reference to a2
    assert(&b2 == &a2);

    // Test case 3: Decrement with saturation
    Vec2uq a3(0);
    Vec2uq& b3 = --a3;
    // Check values remained at minimum
    for(int i = 0; i < 2; i++) {
        assert(a3[i] == 0); // Should saturate at minimum value
        assert(b3[i] == 0);
    }
    // Verify b3 is reference to a3
    assert(&b3 == &a3);

    std::cout << "test_prefix_decrement_operator passed!\n";
}

void test_multiply_operator() {
    // Test case 1: Basic multiplication
    Vec2uq a1(1, 2);
    Vec2uq b1(2);
    Vec2uq c1 = a1 * b1;
    for(int i = 0; i < 2; i++) {
        assert(c1[i] == (i + 1) * 2);
    }

    // Test case 2: Multiplication with zero
    Vec2uq a2(1, 2);
    Vec2uq b2(0);
    Vec2uq c2 = a2 * b2;
    for(int i = 0; i < 2; i++) {
        assert(c2[i] == 0);
    }

    // Test case 3: Multiplication with ones (identity)
    Vec2uq a3(1, 2);
    Vec2uq b3(1);
    Vec2uq c3 = a3 * b3;
    for(int i = 0; i < 2; i++) {
        assert(c3[i] == i + 1);
    }

    // Test case 4: Test with larger numbers
    Vec2uq a4(100, 200);
    Vec2uq b4(3);
    Vec2uq c4 = a4 * b4;
    assert(c4[0] == 300);
    assert(c4[1] == 600);

    // Test case 5: Test multiplication with large values
    Vec2uq a5(0xFFFFFFFFULL, 0x8000000000000000ULL);
    Vec2uq b5(2);
    Vec2uq c5 = a5 * b5;
    assert(c5[0] == 0x1FFFFFFFEULL);
    assert(c5[1] == 0); // 0x8000000000000000 * 2 overflows to 0

    std::cout << "test_multiply_operator passed!\n";
}
void test_multiply_equals_operator() {
    // Test case 1: Basic multiplication
    Vec2uq a1(1, 2);
    Vec2uq b1(2);
    a1 *= b1;
    for(int i = 0; i < 2; i++) {
        assert(a1[i] == (i + 1) * 2);
    }

    // Test case 2: Multiplication with zero
    Vec2uq a2(1, 2);
    Vec2uq b2(0);
    a2 *= b2;
    for(int i = 0; i < 2; i++) {
        assert(a2[i] == 0);
    }

    // Test case 3: Multiplication with ones (identity)
    Vec2uq a3(1, 2);
    Vec2uq b3(1);
    a3 *= b3;
    for(int i = 0; i < 2; i++) {
        assert(a3[i] == i + 1);
    }

    // Test case 4: Test with larger numbers
    Vec2uq a4(100, 200);
    Vec2uq b4(3);
    a4 *= b4;
    assert(a4[0] == 300);
    assert(a4[1] == 600);

    // Test case 5: Test multiplication near maximum values
    Vec2uq a5(0x7FFFFFFFFFFFFFFFULL, 0x4000000000000000ULL);
    Vec2uq b5(2);
    a5 *= b5;
    // Check multiplication results
    assert(a5[0] == 0xFFFFFFFFFFFFFFFEULL);  // 0x7FFFFFFFFFFFFFFF * 2
    assert(a5[1] == 0x8000000000000000ULL);  // 0x4000000000000000 * 2

    std::cout << "test_multiply_equals_operator passed!\n";
}
void test_shift_left_operator() {
    // Test case 1: Basic left shift by 1
    Vec2uq a1(1, 2);
    Vec2uq b1 = a1 << 1;
    for(int i = 0; i < 2; i++) {
        assert(b1[i] == (a1[i] << 1));
    }

    // Test case 2: Left shift by 4
    Vec2uq a2(0x1111, 0x2222);
    Vec2uq b2 = a2 << 4;
    for(int i = 0; i < 2; i++) {
        assert(b2[i] == (a2[i] << 4));
    }

    // Test case 3: Left shift by 8 (half the bits)
    Vec2uq a3(0x00FF, 0xFF00);
    Vec2uq b3 = a3 << 8;
    for(int i = 0; i < 2; i++) {
        assert(b3[i] == (a3[i] << 8));
    }

    // Test case 4: Left shift that clears all bits
    Vec2uq a4(0xFFFFFFFFFFFFFFFF);
    Vec2uq b4 = a4 << 64;
    for(int i = 0; i < 2; i++) {
        assert(b4[i] == 0);
    }

    std::cout << "test_shift_left_operator passed!\n";
}
void test_shift_left_equals_operator() {
    // Test case 1: Basic left shift by 1
    Vec2uq a1(1, 2);
    Vec2uq expected1 = a1 << 1;
    a1 <<= 1;
    for(int i = 0; i < 2; i++) {
        assert(a1[i] == expected1[i]);
    }

    // Test case 2: Left shift by 4
    Vec2uq a2(0x1111, 0x2222);
    Vec2uq expected2 = a2 << 4;
    a2 <<= 4;
    for(int i = 0; i < 2; i++) {
        assert(a2[i] == expected2[i]);
    }

    // Test case 3: Left shift by 8
    Vec2uq a3(0x00FF, 0xFF00);
    Vec2uq expected3 = a3 << 8;
    a3 <<= 8;
    for(int i = 0; i < 2; i++) {
        assert(a3[i] == expected3[i]);
    }

    // Test case 4: Left shift that clears all bits
    Vec2uq a4(0xFFFF);
    a4 <<= 64;
    for(int i = 0; i < 2; i++) {
        assert(a4[i] == 0);
    }

    std::cout << "test_shift_left_equals_operator passed!\n";
}
void test_shift_right_operator() {
    // Test case 1: Basic right shift by 1
    Vec2uq a1(2, 4);
    Vec2uq b1 = a1 >> 1;
    for(int i = 0; i < 2; i++) {
        assert(b1[i] == (a1[i] >> 1));
    }

    // Test case 2: Right shift by 4
    Vec2uq a2(0x1110, 0x2220);
    Vec2uq b2 = a2 >> 4;
    for(int i = 0; i < 2; i++) {
        assert(b2[i] == (a2[i] >> 4));
    }

    // Test case 3: Right shift by 8 (half the bits)
    Vec2uq a3(0xFF00, 0x00FF);
    Vec2uq b3 = a3 >> 8;
    for(int i = 0; i < 2; i++) {
        assert(b3[i] == (a3[i] >> 8));
    }

    // Test case 4: Right shift that clears all bits
    Vec2uq a4(0xFFFF);
    Vec2uq b4 = a4 >> 16;
    for(int i = 0; i < 2; i++) {
        assert(b4[i] == 0);
    }

    std::cout << "test_shift_right_operator passed!\n";
}
void test_shift_right_equals_operator() {
    // Test case 1: Basic right shift by 1
    Vec2uq a1(2, 4);
    Vec2uq expected1 = a1 >> 1;
    a1 >>= 1;
    for(int i = 0; i < 2; i++) {
        assert(a1[i] == expected1[i]);
    }

    // Test case 2: Right shift by 4
    Vec2uq a2(0x1110, 0x2220);
    Vec2uq expected2 = a2 >> 4;
    a2 >>= 4;
    for(int i = 0; i < 2; i++) {
        assert(a2[i] == expected2[i]);
    }

    // Test case 3: Right shift by 8
    Vec2uq a3(0xFF00, 0x00FF);
    Vec2uq expected3 = a3 >> 8;
    a3 >>= 8;
    for(int i = 0; i < 2; i++) {
        assert(a3[i] == expected3[i]);
    }

    // Test case 4: Right shift that clears all bits
    Vec2uq a4(0xFFFF);
    a4 >>= 32;
    for(int i = 0; i < 2; i++) {
        assert(a4[i] == 0);
    }

    std::cout << "test_shift_right_equals_operator passed!\n";
}

// // Comparison Operation Tests
void test_operator_equal() {
    // Test case 1: Equal values
    Vec2uq a1(1, 1);
    Vec2uq b1(1, 1);
    Vec2uq result1 = (a1 == b1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == 0xFFFFFFFFFFFFFFFFULL); // All bits set indicates true
    }

    // Test case 2: Unequal values
    Vec2uq a2(1, 2);
    Vec2uq b2(2, 1);
    Vec2uq result2 = (a2 == b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0); // All bits clear indicates false
    }

    // Test case 3: Mix of equal and unequal values
    Vec2uq a3(1, 2);
    Vec2uq b3(1, 1);
    Vec2uq result3 = (a3 == b3);
    assert(result3[0] == 0xFFFFFFFFFFFFFFFFULL); // Equal
    assert(result3[1] == 0);                      // Unequal

    // Test case 4: Compare with zero
    Vec2uq a4(0, 1);
    Vec2uq b4(0);
    Vec2uq result4 = (a4 == b4);
    assert(result4[0] == 0xFFFFFFFFFFFFFFFFULL); // Equal to zero
    assert(result4[1] == 0);                      // Not equal to zero

    std::cout << "test_operator_equal passed!\n";
}
void test_operator_not_equal() {
    // Test case 1: All values equal (should return all false)
    Vec2uq a1(1, 1);
    Vec2uq b1(1, 1);
    Vec2uq result1 = (a1 != b1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == 0); // All bits clear indicates false (values are equal)
    }

    // Test case 2: All values unequal (should return all true)
    Vec2uq a2(1, 2);
    Vec2uq b2(2, 1);
    Vec2uq result2 = (a2 != b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0xFFFFFFFFFFFFFFFFULL); // All bits set indicates true (values are unequal)
    }

    // Test case 3: Mix of equal and unequal values
    Vec2uq a3(1, 2);
    Vec2uq b3(1, 1);
    Vec2uq result3 = (a3 != b3);
    assert(result3[0] == 0);                      // Equal
    assert(result3[1] == 0xFFFFFFFFFFFFFFFFULL); // Unequal

    // Test case 4: Compare with zero
    Vec2uq a4(0, 1);
    Vec2uq b4(0);
    Vec2uq result4 = (a4 != b4);
    assert(result4[0] == 0);                      // Equal to zero
    assert(result4[1] == 0xFFFFFFFFFFFFFFFFULL); // Not equal to zero

    // Test case 5: Compare maximum values
    Vec2uq a5(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq b5(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq result5 = (a5 != b5);
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 0); // All elements are equal
    }

    // Test case 6: Compare with mixed maximum values
    Vec2uq a6(0xFFFFFFFFFFFFFFFFULL, 0);
    Vec2uq b6(0, 0xFFFFFFFFFFFFFFFFULL);
    Vec2uq result6 = (a6 != b6);
    for(int i = 0; i < 2; i++) {
        assert(result6[i] == 0xFFFFFFFFFFFFFFFFULL); // All elements are unequal
    }

    std::cout << "test_operator_not_equal passed!\n";
}
void test_greater_than_operator() {
    // Test case 1: Basic greater than comparison
    Vec2uq a1(2, 3);
    Vec2uq b1(1, 2);
    Vec2uq result1 = (a1 > b1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == 0xFFFFFFFFFFFFFFFFULL); // All elements in a1 are greater than b1
    }

    // Test case 2: Basic less than comparison
    Vec2uq a2(1, 2);
    Vec2uq b2(2, 3);
    Vec2uq result2 = (a2 > b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0); // All elements in a2 are less than b2
    }

    // Test case 3: Equal values comparison
    Vec2uq a3(1, 1);
    Vec2uq b3(1, 1);
    Vec2uq result3 = (a3 > b3);
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == 0); // Equal elements should return false
    }

    // Test case 4: Mixed comparisons
    Vec2uq a4(5, 2);
    Vec2uq b4(3, 4);
    Vec2uq result4 = (a4 > b4);
    assert(result4[0] == 0xFFFFFFFFFFFFFFFFULL); // 5 > 3
    assert(result4[1] == 0);          // 2 < 4

    // Test case 5: Compare with zero
    Vec2uq a5(1, 0);
    Vec2uq b5(0, 0);
    Vec2uq result5 = (a5 > b5);
    assert(result5[0] == 0xFFFFFFFFFFFFFFFFULL); // 1 > 0
    assert(result5[1] == 0);          // 0 = 0

    // Test case 6: Compare with maximum values
    Vec2uq a6(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFEULL);
    Vec2uq b6(0xFFFFFFFFFFFFFFFEULL, 0xFFFFFFFFFFFFFFFFULL);
    Vec2uq result6 = (a6 > b6);
    assert(result6[0] == 0xFFFFFFFFFFFFFFFFULL);   // max > max-1
    assert(result6[1] == 0);          // max-1 < max

    std::cout << "test_greater_than_operator passed!\n";
}
void test_less_than_operator() {
    // Test case 1: Basic less than comparison
    Vec2uq a1(1, 2);
    Vec2uq b1(2, 3);
    Vec2uq result1 = (a1 < b1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == 0xFFFFFFFFFFFFFFFFULL); // All elements in a1 are less than b1
    }

    // Test case 2: Basic greater than comparison
    Vec2uq a2(2, 3);
    Vec2uq b2(1, 2);
    Vec2uq result2 = (a2 < b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0); // All elements in a2 are greater than b2
    }

    // Test case 3: Equal values comparison
    Vec2uq a3(1, 1);
    Vec2uq b3(1, 1);
    Vec2uq result3 = (a3 < b3);
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == 0); // Equal elements should return false
    }

    // Test case 4: Mixed comparisons
    Vec2uq a4(3, 4);
    Vec2uq b4(5, 2);
    Vec2uq result4 = (a4 < b4);
    assert(result4[0] == 0xFFFFFFFFFFFFFFFFULL); // 3 < 5
    assert(result4[1] == 0);                      // 4 > 2

    // Test case 5: Compare with zero
    Vec2uq a5(0, 1);
    Vec2uq b5(1, 0);
    Vec2uq result5 = (a5 < b5);
    assert(result5[0] == 0xFFFFFFFFFFFFFFFFULL); // 0 < 1
    assert(result5[1] == 0);                      // 1 > 0

    // Test case 6: Compare with maximum values
    Vec2uq a6(0xFFFFFFFFFFFFFFFEULL, 0xFFFFFFFFFFFFFFFFULL);
    Vec2uq b6(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFEULL);
    Vec2uq result6 = (a6 < b6);
    assert(result6[0] == 0xFFFFFFFFFFFFFFFFULL);   // 0xFFFFFFFE < 0xFFFFFFFF
    assert(result6[1] == 0);                        // 0xFFFFFFFF > 0xFFFFFFFE

    std::cout << "test_less_than_operator passed!\n";
}
void test_greater_than_or_equal_operator() {
    // Test case 1: Greater than comparison
    Vec2uq a1(2, 3);
    Vec2uq b1(1, 2);
    Vec2uq result1 = (a1 >= b1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == 0xFFFFFFFFFFFFFFFFULL); // All elements in a1 are greater than b1
    }

    // Test case 2: Equal values comparison
    Vec2uq a2(1, 1);
    Vec2uq b2(1, 1);
    Vec2uq result2 = (a2 >= b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0xFFFFFFFFFFFFFFFFULL); // Equal elements should return true
    }

    // Test case 3: Less than comparison
    Vec2uq a3(1, 2);
    Vec2uq b3(2, 3);
    Vec2uq result3 = (a3 >= b3);
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == 0); // All elements in a3 are less than b3
    }

    // Test case 4: Mixed comparisons
    Vec2uq a4(5, 2);
    Vec2uq b4(5, 4);
    Vec2uq result4 = (a4 >= b4);
    assert(result4[0] == 0xFFFFFFFFFFFFFFFFULL); // 5 = 5
    assert(result4[1] == 0);                      // 2 < 4

    // Test case 5: Compare with zero
    Vec2uq a5(1, 0);
    Vec2uq b5(0);
    Vec2uq result5 = (a5 >= b5);
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 0xFFFFFFFFFFFFFFFFULL); // Greater or equal to zero
    }

    // Test case 6: Compare with maximum values
    Vec2uq a6(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFEULL);
    Vec2uq b6(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFEULL);
    Vec2uq result6 = (a6 >= b6);
    assert(result6[0] == 0xFFFFFFFFFFFFFFFFULL); // Equal
    assert(result6[1] == 0xFFFFFFFFFFFFFFFFULL); // Equal

    std::cout << "test_greater_than_or_equal_operator passed!\n";
}
void test_less_than_or_equal_operator() {
    // Test case 1: Less than comparison
    Vec2uq a1(1, 2);
    Vec2uq b1(2, 3);
    Vec2uq result1 = (a1 <= b1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == 0xFFFFFFFFFFFFFFFFULL); // All elements in a1 are less than b1
    }

    // Test case 2: Equal values comparison
    Vec2uq a2(1, 1);
    Vec2uq b2(1, 1);
    Vec2uq result2 = (a2 <= b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0xFFFFFFFFFFFFFFFFULL); // Equal elements should return true
    }

    // Test case 3: Greater than comparison
    Vec2uq a3(2, 3);
    Vec2uq b3(1, 2);
    Vec2uq result3 = (a3 <= b3);
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == 0); // All elements in a3 are greater than b3
    }

    // Test case 4: Mixed comparisons
    Vec2uq a4(5, 2);
    Vec2uq b4(5, 4);
    Vec2uq result4 = (a4 <= b4);
    assert(result4[0] == 0xFFFFFFFFFFFFFFFFULL); // 5 = 5
    assert(result4[1] == 0xFFFFFFFFFFFFFFFFULL); // 2 < 4

    // Test case 5: Compare with zero
    Vec2uq a5(0, 1);
    Vec2uq b5(0);
    Vec2uq result5 = (a5 <= b5);
    for(int i = 0; i < 2; i++) {
        if(a5[i] == 0) {
            assert(result5[i] == 0xFFFFFFFFFFFFFFFFULL); // Equal to zero
        } else {
            assert(result5[i] == 0); // Greater than zero
        }
    }

    // Test case 6: Compare with maximum values
    Vec2uq a6(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL);
    Vec2uq b6(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFEULL);
    Vec2uq result6 = (a6 <= b6);
    assert(result6[0] == 0xFFFFFFFFFFFFFFFFULL); // Equal
    assert(result6[1] == 0);                      // Greater

    std::cout << "test_less_than_or_equal_operator passed!\n";
}

void test_bitwise_and_operator() {
    // Test case 1: Basic AND operation
    Vec2uq a1(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
    Vec2uq b1(0x0000000000000000, 0xFFFFFFFFFFFFFFFF);
    Vec2uq result1 = a1 & b1;
    assert(result1[0] == 0x0000000000000000);
    assert(result1[1] == 0xFFFFFFFFFFFFFFFF);

    // Test case 2: AND with zero
    Vec2uq a2(0xFFFFFFFFFFFFFFFF, 0xAAAAAAAAAAAAAAAA);
    Vec2uq b2(0);
    Vec2uq result2 = a2 & b2;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: AND with patterns
    Vec2uq a3(0xAAAAAAAAAAAAAAAA, 0xAAAAAAAAAAAAAAAA);
    Vec2uq b3(0x5555555555555555, 0x5555555555555555);
    Vec2uq result3 = a3 & b3;
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == 0);
    }

    // Test case 4: Self AND
    Vec2uq a4(0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0);
    Vec2uq result4 = a4 & a4;
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == 0xF0F0F0F0F0F0F0F0);
    }

    // Test case 5: Mixed patterns
    Vec2uq a5(0xFFFFFFFFFFFFFFFF, 0xF0F0F0F0F0F0F0F0);
    Vec2uq b5(0xFF00FF00FF00FF00, 0x0F0F0F0F0F0F0F0F);
    Vec2uq result5 = a5 & b5;
    assert(result5[0] == 0xFF00FF00FF00FF00);
    assert(result5[1] == 0x0000000000000000);

    std::cout << "test_bitwise_and_operator passed!\n";
}
void test_bitwise_or_operator() {
    // Test case 1: Basic OR operation
    Vec2uq a1(0x0000ULL);
    Vec2uq b1(0xFFFFULL, 0x0000ULL);
    Vec2uq result1 = a1 | b1;
    assert(result1[0] == 0xFFFFULL);
    assert(result1[1] == 0x0000ULL);

    // Test case 2: OR with all bits set
    Vec2uq a2(0xAAAAAAAAAAAAAAAAULL, 0x5555555555555555ULL);
    Vec2uq b2(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq result2 = a2 | b2;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0xFFFFFFFFFFFFFFFFULL);
    }

    // Test case 3: OR with alternating patterns
    Vec2uq a3(0xAAAAAAAAAAAAAAAAULL);
    Vec2uq b3(0x5555555555555555ULL);
    Vec2uq result3 = a3 | b3;
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == 0xFFFFFFFFFFFFFFFFULL);
    }

    // Test case 4: OR with self
    Vec2uq a4(0xF0F0F0F0F0F0F0F0ULL);
    Vec2uq result4 = a4 | a4;
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == 0xF0F0F0F0F0F0F0F0ULL);
    }

    // Test case 5: OR with zero
    Vec2uq a5(0xFFFFFFFFFFFFFFFFULL, 0xF0F0F0F0F0F0F0F0ULL);
    Vec2uq b5(0);
    Vec2uq result5 = a5 | b5;
    assert(result5[0] == 0xFFFFFFFFFFFFFFFFULL);
    assert(result5[1] == 0xF0F0F0F0F0F0F0F0ULL);

    std::cout << "test_bitwise_or_operator passed!\n";
}
void test_bitwise_xor_operator() {
    // Test case 1: XOR with zero (identity)
    Vec2uq a1(0xFFFFFFFFFFFFFFFFULL, 0xAAAAAAAAAAAAAAAAULL);
    Vec2uq b1(0);
    Vec2uq result1 = a1 ^ b1;
    assert(result1[0] == 0xFFFFFFFFFFFFFFFFULL);
    assert(result1[1] == 0xAAAAAAAAAAAAAAAAULL);

    // Test case 2: XOR with same value (should be zero)
    Vec2uq a2(0xFFFFFFFFFFFFFFFFULL, 0xAAAAAAAAAAAAAAAAULL);
    Vec2uq result2 = a2 ^ a2;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: XOR with alternating patterns
    Vec2uq a3(0xAAAAAAAAAAAAAAAAULL, 0xAAAAAAAAAAAAAAAAULL);
    Vec2uq b3(0x5555555555555555ULL, 0x5555555555555555ULL);
    Vec2uq result3 = a3 ^ b3;
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == 0xFFFFFFFFFFFFFFFFULL);
    }

    // Test case 4: XOR with all bits set
    Vec2uq a4(0xFFFFFFFFFFFFFFFFULL, 0xAAAAAAAAAAAAAAAAULL);
    Vec2uq b4(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq result4 = a4 ^ b4;
    assert(result4[0] == 0x0000000000000000ULL);
    assert(result4[1] == 0x5555555555555555ULL);

    // Test case 5: XOR with mixed patterns
    Vec2uq a5(0xFF00FF00FF00FF00ULL, 0x00FF00FF00FF00FFULL);
    Vec2uq b5(0x00FF00FF00FF00FFULL, 0xFF00FF00FF00FF00ULL);
    Vec2uq result5 = a5 ^ b5;
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 0xFFFFFFFFFFFFFFFFULL);
    }

    std::cout << "test_bitwise_xor_operator passed!\n";
}
void test_bitwise_not_operator() {
    // Test case 1: NOT of zero gives all bits set
    Vec2uq a1(0);
    Vec2uq result1 = ~a1;
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == 0xFFFFFFFFFFFFFFFFULL);
    }

    // Test case 2: NOT of all bits set gives zero
    Vec2uq a2(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq result2 = ~a2;
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 0);
    }

    // Test case 3: NOT of alternating bits
    Vec2uq a3(0xAAAAAAAAAAAAAAAAULL, 0x5555555555555555ULL);
    Vec2uq result3 = ~a3;
    assert(result3[0] == 0x5555555555555555ULL); // NOT of 0xAAAAAAAAAAAAAAAA
    assert(result3[1] == 0xAAAAAAAAAAAAAAAAULL); // NOT of 0x5555555555555555

    // Test case 4: Double NOT should give original value
    Vec2uq a4(0x123456789ABCDEF0ULL, 0xFEDCBA9876543210ULL);
    Vec2uq result4 = ~~a4;
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == a4[i]);
    }

    std::cout << "test_bitwise_not_operator passed!\n";
}

void test_select() {
    // Test case 1: Basic selection with all true condition
    Vec2uq mask1(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq a1(1, 2);
    Vec2uq b1(9, 10);
    Vec2uq result1 = select(mask1, a1, b1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == a1[i]); // Should select all from a1
    }

    // Test case 2: Basic selection with all false condition
    Vec2uq mask2(0);
    Vec2uq a2(1, 2);
    Vec2uq b2(9, 10);
    Vec2uq result2 = select(mask2, a2, b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == b2[i]); // Should select all from b2
    }

    // Test case 3: Alternating selection pattern
    Vec2uq mask3(0xFFFFFFFFFFFFFFFFULL, 0);
    Vec2uq a3(1, 2);
    Vec2uq b3(9, 10);
    Vec2uq result3 = select(mask3, a3, b3);
    assert(result3[0] == 1);  // From a3
    assert(result3[1] == 10); // From b3

    // Test case 4: Selection with maximum values
    Vec2uq mask4(0xFFFFFFFFFFFFFFFFULL, 0);
    Vec2uq a4(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq b4(0);
    Vec2uq result4 = select(mask4, a4, b4);
    assert(result4[0] == 0xFFFFFFFFFFFFFFFFULL);
    assert(result4[1] == 0);

    // Test case 5: Selection with mixed patterns
    Vec2uq mask5(0xAAAAAAAAAAAAAAAAULL, 0x5555555555555555ULL);
    Vec2uq a5(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq b5(0);
    Vec2uq result5 = select(mask5, a5, b5);
    assert(result5[0] == 0xAAAAAAAAAAAAAAAAULL);
    assert(result5[1] == 0x5555555555555555ULL);

    std::cout << "test_select passed!\n";
}
void test_if_add() {
    // Test case 1: Add with all true conditions
    Vec2uq mask1(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq a1(1, 2);
    Vec2uq b1(1);
    Vec2uq result1 = if_add(mask1, a1, b1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == a1[i] + b1[i]); // Should add all values
    }

    // Test case 2: Add with all false conditions
    Vec2uq mask2(0);
    Vec2uq a2(1, 2);
    Vec2uq b2(1);
    Vec2uq result2 = if_add(mask2, a2, b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == a2[i]); // Should not add anything
    }

    // Test case 3: Alternating conditions
    Vec2uq mask3(0xFFFFFFFFFFFFFFFFULL, 0);
    Vec2uq a3(1, 2);
    Vec2uq b3(1);
    Vec2uq result3 = if_add(mask3, a3, b3);
    assert(result3[0] == 2);  // 1 + 1
    assert(result3[1] == 2);  // 2 + 0

    // Test case 4: Add with saturation
    Vec2uq mask4(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq a4(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq b4(1);
    Vec2uq result4 = if_add(mask4, a4, b4);
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == 0xFFFFFFFFFFFFFFFFULL); // Should saturate at maximum value
    }

    // Test case 5: Add with mixed values
    Vec2uq mask5(0xFFFFFFFFFFFFFFFFULL, 0);
    Vec2uq a5(0x1000, 0x2000);
    Vec2uq b5(0x0100, 0x0200);
    Vec2uq result5 = if_add(mask5, a5, b5);
    assert(result5[0] == 0x1100); // 0x1000 + 0x0100
    assert(result5[1] == 0x2000); // 0x2000 + 0

    std::cout << "test_if_add passed!\n";
}
void test_if_sub() {
    // Test case 1: Subtract with all true conditions
    Vec2uq mask1(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq a1(10, 11);
    Vec2uq b1(1);
    Vec2uq result1 = if_sub(mask1, a1, b1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == a1[i] - b1[i]); // Should subtract all values
    }

    // Test case 2: Subtract with all false conditions
    Vec2uq mask2(0);
    Vec2uq a2(10, 11);
    Vec2uq b2(1);
    Vec2uq result2 = if_sub(mask2, a2, b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == a2[i]); // Should not subtract anything
    }

    // Test case 3: Alternating conditions
    Vec2uq mask3(0xFFFFFFFFFFFFFFFFULL, 0);
    Vec2uq a3(10, 11);
    Vec2uq b3(1);
    Vec2uq result3 = if_sub(mask3, a3, b3);
    assert(result3[0] == 9);   // 10 - 1
    assert(result3[1] == 11);  // 11 - 0

    // Test case 4: Subtract with saturation prevention
    Vec2uq mask4(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq a4(1, 2);
    Vec2uq b4(2, 3);
    Vec2uq result4 = if_sub(mask4, a4, b4);
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == 0); // Should saturate at minimum value
    }

    // Test case 5: Subtract with mixed values
    Vec2uq mask5(0xFFFFFFFFFFFFFFFFULL, 0);
    Vec2uq a5(0x1100, 0x2200);
    Vec2uq b5(0x0100, 0x0200);
    Vec2uq result5 = if_sub(mask5, a5, b5);
    assert(result5[0] == 0x1000); // 0x1100 - 0x0100
    assert(result5[1] == 0x2200); // 0x2200 - 0

    std::cout << "test_if_sub passed!\n";
}
void test_if_mul() {
    // Test case 1: Multiply with all true conditions
    Vec2uq mask1(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq a1(1, 2);
    Vec2uq b1(2);
    Vec2uq result1 = if_mul(mask1, a1, b1);
    for(int i = 0; i < 2; i++) {
        assert(result1[i] == a1[i] * b1[i]); // Should multiply all values
    }

    // Test case 2: Multiply with all false conditions
    Vec2uq mask2(0);
    Vec2uq a2(1, 2);
    Vec2uq b2(2);
    Vec2uq result2 = if_mul(mask2, a2, b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == a2[i]); // Should not multiply anything
    }

    // Test case 3: Alternating conditions
    Vec2uq mask3(0xFFFFFFFFFFFFFFFFULL, 0);
    Vec2uq a3(1, 2);
    Vec2uq b3(2);
    Vec2uq result3 = if_mul(mask3, a3, b3);
    assert(result3[0] == 2);  // 1 * 2
    assert(result3[1] == 2);  // 2 (unchanged)

    // Test case 4: Multiply with larger values
    Vec2uq mask4(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq a4(100, 200);
    Vec2uq b4(3);
    Vec2uq result4 = if_mul(mask4, a4, b4);
    assert(result4[0] == 300);
    assert(result4[1] == 600);

    // Test case 5: Multiply near maximum values
    Vec2uq mask5(0xFFFFFFFFFFFFFFFFULL);  
    Vec2uq a5(0x8000000000000000ULL, 0x4000000000000000ULL);
    Vec2uq b5(2);
    Vec2uq result5 = if_mul(mask5, a5, b5);
    assert(result5[0] == 0x0000000000000000ULL);  // 0x8000000000000000 * 2 overflows to 0
    assert(result5[1] == 0x8000000000000000ULL);  // 0x4000000000000000 * 2 = 0x8000000000000000

    // Test case 6: Multiply at maximum values
    Vec2uq mask6(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq a6(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq b6(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq result6 = if_mul(mask6, a6, b6);
    for(int i = 0; i < 2; i++) {
        assert(result6[i] == 1); // 0xFFFFFFFFFFFFFFFF * 0xFFFFFFFFFFFFFFFF = 1 due to overflow
    }

    // Test case 7: Mixed multiplications near maximum  
    Vec2uq mask7(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq a7(0xFFFFFFFFFFFFFFFFULL, 0x7FFFFFFFFFFFFFFFULL);
    Vec2uq b7(2, 3); 
    Vec2uq result7 = if_mul(mask7, a7, b7);
    assert(result7[0] == 0xFFFFFFFFFFFFFFFEULL);  // 0xFFFFFFFFFFFFFFFF * 2
    assert(result7[1] == 0x7FFFFFFFFFFFFFFDULL);  // 0x7FFFFFFFFFFFFFFF * 3

    std::cout << "test_if_mul passed!\n";
}

void test_horizontal_add() {
    // Test case 1: Basic addition of all ones
    Vec2uq a1(1, 1);
    uint64_t result1 = horizontal_add(a1);
    assert(result1 == 2); // Sum should be 2

    // Test case 2: Addition of sequential numbers
    Vec2uq a2(1, 2); 
    uint64_t result2 = horizontal_add(a2);
    assert(result2 == 3); // Sum should be 3

    // Test case 3: Addition with zeros
    Vec2uq a3(0, 0);
    uint64_t result3 = horizontal_add(a3);
    assert(result3 == 0); // Sum should be 0

    // Test case 4: Addition of mixed values
    Vec2uq a4(0xFFFF, 0x0001);
    uint64_t result4 = horizontal_add(a4);
    assert(result4 == 0x10000); // Sum of values

    // Test case 5: Addition of maximum values
    Vec2uq a5(0xFFFFFFFFFFFFFFFFULL, 0xFFFFFFFFFFFFFFFFULL);
    uint64_t result5 = horizontal_add(a5);
    assert(result5 == 0xFFFFFFFFFFFFFFFEULL); // Sum of two max values

    std::cout << "test_horizontal_add passed!\n";
}

void test_max() {
    // Test case 1: Basic max comparison
    Vec2uq a1(1, 2);
    Vec2uq b1(8, 7);
    Vec2uq result1 = max(a1, b1);
    assert(result1[0] == 8);
    assert(result1[1] == 7);

    // Test case 2: Max with equal values
    Vec2uq a2(5, 5);
    Vec2uq b2(5, 5);
    Vec2uq result2 = max(a2, b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 5);
    }

    // Test case 3: Max with zeros 
    Vec2uq a3(0, 0);
    Vec2uq b3(1, 1);
    Vec2uq result3 = max(a3, b3);
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == 1);
    }

    // Test case 4: Max with maximum values
    Vec2uq a4(0xFFFF);
    Vec2uq b4(0x7FFF, 0x8FFF);
    Vec2uq result4 = max(a4, b4);
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == 0xFFFF);
    }

    // Test case 5: Max with mixed values
    Vec2uq a5(0x1234, 0x5678);
    Vec2uq b5(0x4321, 0x1234);
    Vec2uq result5 = max(a5, b5);
    assert(result5[0] == 0x4321);
    assert(result5[1] == 0x5678);

    std::cout << "test_max passed!\n";
}
void test_min() {
    // Test case 1: Basic min comparison
    Vec2uq a1(1, 2);
    Vec2uq b1(8, 7);
    Vec2uq result1 = min(a1, b1);
    assert(result1[0] == 1);
    assert(result1[1] == 2);

    // Test case 2: Min with equal values
    Vec2uq a2(5, 5);
    Vec2uq b2(5, 5);
    Vec2uq result2 = min(a2, b2);
    for(int i = 0; i < 2; i++) {
        assert(result2[i] == 5);
    }

    // Test case 3: Min with zeros
    Vec2uq a3(1, 1);
    Vec2uq b3(0, 0);
    Vec2uq result3 = min(a3, b3);
    for(int i = 0; i < 2; i++) {
        assert(result3[i] == 0);
    }

    // Test case 4: Min with maximum values
    Vec2uq a4(0xFFFF);
    Vec2uq b4(0x7FFF, 0x8FFF);
    Vec2uq result4 = min(a4, b4);
    assert(result4[0] == 0x7FFF);
    assert(result4[1] == 0x8FFF);

    // Test case 5: Min with mixed values
    Vec2uq a5(0x1234, 0x5678);
    Vec2uq b5(0x4321, 0x1234);
    Vec2uq result5 = min(a5, b5);
    assert(result5[0] == 0x1234);
    assert(result5[1] == 0x1234);

    std::cout << "test_min passed!\n";
}

void test_rotate_left() {
    // Test case 1: Rotate left by 1
    Vec2uq a(1, 2);
    Vec2uq res1 = rotate_left(a, 1);
    for(int i = 0; i < 2; i++) {
        assert(res1[i] == (a[i] << 1));
    }

    // Test case 2: Rotate left by 4 
    Vec2uq b(0x1111, 0x2222);
    Vec2uq res2 = rotate_left(b, 4);
    for(int i = 0; i < 2; i++) {
        uint64_t expected = (b[i] << 4);
        assert(res2[i] == expected);
    }

    // Test case 3: Rotate left by 8
    Vec2uq c(0x00FF, 0xFF00);
    Vec2uq res3 = rotate_left(c, 8);
    for(int i = 0; i < 2; i++) {
        uint64_t expected = (c[i] << 8);
        assert(res3[i] == expected);
    }

    // Test case 4: Rotate zeros (should remain zero)
    Vec2uq a4(0);
    Vec2uq result4 = rotate_left(a4, 4);
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == 0);
    }

    // Test case 5: Rotate maximum values
    Vec2uq a5(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq result5 = rotate_left(a5, 4);
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 0xFFFFFFFFFFFFFFF0ULL);
    }

    std::cout << "test_rotate_left passed!\n";
}

void test_rotate_right() {
    // Test case 1: Rotate right by 1
    Vec2uq a(2, 4);
    Vec2uq res1 = rotate_right(a, 1);
    for(int i = 0; i < 2; i++) {
        assert(res1[i] == (a[i] >> 1));
    }

    // Test case 2: Rotate right by 4
    Vec2uq b(0x1111, 0x2222);
    Vec2uq res2 = rotate_right(b, 4);
    for(int i = 0; i < 2; i++) {
        uint64_t expected = (b[i] >> 4);
        assert(res2[i] == expected);
    }

    // Test case 3: Rotate right by 8
    Vec2uq c(0xFF00, 0x00FF);
    Vec2uq res3 = rotate_right(c, 8);
    for(int i = 0; i < 2; i++) {
        uint64_t expected = (c[i] >> 8);
        assert(res3[i] == expected);
    }

    // Test case 4: Rotate zeros (should remain zero)
    Vec2uq a4(0);
    Vec2uq result4 = rotate_right(a4, 4);
    for(int i = 0; i < 2; i++) {
        assert(result4[i] == 0);
    }

    // Test case 5: Rotate maximum value
    Vec2uq a5(0xFFFFFFFFFFFFFFFFULL);
    Vec2uq result5 = rotate_right(a5, 4);
    for(int i = 0; i < 2; i++) {
        assert(result5[i] == 0x0FFFFFFFFFFFFFFFULL);
    }
    std::cout << "test_rotate_right passed!\n";
}

int main() 
{
    test_default_constructor();
    test_broadcast_constructor();
    test_element_constructor();
    test_uint64x2t_constructor();
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