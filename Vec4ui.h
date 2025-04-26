#ifndef VEC128_4UI_ARM_H
#define VEC128_4UI_ARM_H
#include <arm_neon.h>
namespace VCL_NAMESPACE {
/*****************************************************************************
*
*     // vector of 4 32-bit unsigned integers
*
*****************************************************************************/
class Vec4ui {
private:
    uint32x4_t xmm;
public:
    // Default constructor:
    Vec4ui() {
        xmm = vdupq_n_u32(0);
    }
    // Constructor to broadcast same value:
    Vec4ui(uint32_t i) {
        xmm = vdupq_n_u32(i);
    }
    // Constructor to build from all elements:
    Vec4ui(uint32_t i0, uint32_t i1, uint32_t i2, uint32_t i3) {
        uint32_t _data[4] = {i0, i1, i2, i3};
        xmm = vld1q_u32(_data);
    }
    // Constructor to convert from uint16x8_t:
    Vec4ui(uint32x4_t const x) {
        xmm = x;
    }
    // Copy constructor:
    Vec4ui(const Vec4ui& other) {
        xmm = other.xmm;
    }
    // Assignment operator:
    Vec4ui& operator = (uint32x4_t const x) {
        xmm = x;
        return *this;
    }
    // Type cast operator:
    operator uint32x4_t() const {
        return xmm;
    }
    // Load functions:
    Vec4ui& load(void const * p) {
        xmm = vld1q_u32((uint32_t const*)p);
        return *this;
    }
    Vec4ui& load_a(void const * p) {
        uint32_t *ap = (uint32_t*)__builtin_assume_aligned(p, 16);
        xmm = vld1q_u32(ap);
        return *this;
    }
    // Store functions:
    void store(void * p) const {
        vst1q_u32((uint32_t*)p, xmm);
    }
    void store_a(void * p) const {
        vst1q_u32((uint32_t*)p, xmm);
    }
    // Partial load/store:
    Vec4ui& load_partial(int n, void const * p) {
        if (n >= 4) load(p);
        else if (n <= 0) *this = 0;
        else if (((int)(intptr_t)p & 0xFFF) < 0xFF0) {
            load(p);
        }
        else {
            uint32_t x[4] = {0};
            for (int i = 0; i < n; i++) x[i] = ((uint32_t const *)p)[i];
            load(x);
        }
        cutoff(n);
        return *this;
    }
    void store_partial(int n, void * p) const {
        if (n <= 0) return;  // Exit if n is negative or zero
        uint32_t s[4];
        store(s);
        if (uint32_t(n) > 4) n = 4;
        for (int i = 0; i < n; i++) {
            ((uint32_t*)p)[i] = s[i];
        }
    }
    // Cutoff vector:
    Vec4ui& cutoff(int n) {
        if (n <= 0) // Exit if n is negative or zero
        {
            *this = 0;
            return *this;  
        }
        if (uint32_t(n) >= 4) return *this;
        const uint32_t mask[8] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 
                                  0, 0, 0, 0};
        *this &= Vec4ui().load(mask + 4 - n);
        return *this;
    }

    // Overload the &= operator
    Vec4ui& operator&=(const Vec4ui& rhs) {
        xmm = vandq_u32(xmm, rhs.xmm);
        return *this;
    }
    // Element access:
    Vec4ui& insert(int index, uint32_t value) {
        xmm[index & 0x03] = value;
        return *this;
    }
    uint32_t extract(int index) const {
        uint32_t x[4];
        store(x);
        return x[index & 0x03];
    }
    uint32_t operator [] (int index) const {
        return extract(index);
    }
    static constexpr int size() {
        return 4;
    }
    static constexpr int elementtype() {
        return 8;
    }
};

// vector operator + : add element by element
static inline Vec4ui operator + (Vec4ui const a, Vec4ui const b) {
    return vqaddq_u32(a, b);
}

// vector operator += : add
static inline Vec4ui & operator += (Vec4ui & a, Vec4ui const b) {
    a = a + b;
    return a;
}
// postfix operator ++
static inline Vec4ui operator ++ (Vec4ui & a, int) {
    Vec4ui a0 = a;
    a = a + 1;
    return a0;
}
// prefix operator ++
static inline Vec4ui & operator ++ (Vec4ui & a) {
    a = a + 1;
    return a;
}

// vector operator - : subtract element by element
static inline Vec4ui operator - (Vec4ui const a, Vec4ui const b) {
    return vqsubq_u32(a, b);
}

// vector operator -= : subtract
static inline Vec4ui & operator -= (Vec4ui & a, Vec4ui const b) {
    a = a - b;
    return a;
}

// postfix operator --
static inline Vec4ui & operator -- (Vec4ui & a) {
    a = a - 1;
    return a;
}
// prefix operator --
static inline Vec4ui operator -- (Vec4ui & a, int) {
    Vec4ui a0 = a;
    a = a - 1;
    return a0;
}
// vector operator * : multiply element by element
// Proper multiplication for Vec4ui, handling overflow
static inline Vec4ui operator * (Vec4ui const a, Vec4ui const b) {
    uint64x2_t low = vmull_u32(vget_low_u32(a), vget_low_u32(b));
    uint64x2_t high = vmull_u32(vget_high_u32(a), vget_high_u32(b));
    return vcombine_u32(vmovn_u64(low), vmovn_u64(high));
}

// vector operator *= : multiply
static inline Vec4ui & operator *= (Vec4ui & a, Vec4ui const b) {
    a = a * b;
    return a;
}
// vector operator << : shift left all elements
static inline Vec4ui operator << (Vec4ui const a, int b) {
    return vshlq_n_u32(a, b);
}
// vector operator <<= : shift left
static inline Vec4ui & operator <<= (Vec4ui & a, int b) {
    a = a << b;
    return a;
}
// vector operator >> : shift right arithmetic all elements
static inline Vec4ui operator >> (Vec4ui const a, int b) {
    return vshrq_n_u32(a, b);
}
// vector operator >>= : shift right arithmetic
static inline Vec4ui & operator >>= (Vec4ui & a, int b) {
    a = a >> b;
    return a;
}
// vector operator == : returns true for elements for which a == b
static inline Vec4ui operator == (Vec4ui const a, Vec4ui const b) {
    return vceqq_u32(a, b);
}
// vector operator != : returns true for elements for which a != b
static inline Vec4ui operator != (Vec4ui const a, Vec4ui const b) {
    return vmvnq_u32(vceqq_u32(a, b));
}
// vector operator > : returns true for elements for which a > b
static inline Vec4ui operator > (Vec4ui const a, Vec4ui const b) {
    return vcgtq_u32(a, b);
}
// vector operator < : returns true for elements for which a < b
static inline Vec4ui operator < (Vec4ui const a, Vec4ui const b) {
    return vcltq_u32(a, b);
}
// vector operator >= : returns true for elements for which a >= b
static inline Vec4ui operator >= (Vec4ui const a, Vec4ui const b) {
    return vcgeq_u32(a, b);
}
// vector operator <= : returns true for elements for which a <= b
static inline Vec4ui operator <= (Vec4ui const a, Vec4ui const b) {
    return vcleq_u32(a, b);
}

// vector operator & : bitwise and
static inline Vec4ui operator & (Vec4ui const a, Vec4ui const b) {
    return vandq_u32(a, b);
}

// vector operator | : bitwise or
static inline Vec4ui operator | (Vec4ui const a, Vec4ui const b) {
    return vorrq_u32(a, b);
}

// vector operator ^ : bitwise xor
static inline Vec4ui operator ^ (Vec4ui const a, Vec4ui const b) {
    return veorq_u32(a, b);
}

// vector operator ~ : bitwise not
static inline Vec4ui operator ~ (Vec4ui const a) {
    return vmvnq_u32(a);
}
// vector operator &= : bitwise and equal
// static inline Vec4ui & operator &= (Vec4ui & a, Vec4ui const b) {
//     a = a & b;
//     return a;
// }

// Select between two operands
static inline Vec4ui select(Vec4ui const s, Vec4ui const a, Vec4ui const b) {
    return vbslq_u32(s, a, b);
}

// Conditional add
static inline Vec4ui if_add(Vec4ui const f, Vec4ui const a, Vec4ui const b) {
    return a + (f & b);
}

// Conditional sub
static inline Vec4ui if_sub(Vec4ui const f, Vec4ui const a, Vec4ui const b) {
    return a - (f & b);
}

// Conditional mul
static inline Vec4ui if_mul(Vec4ui const f, Vec4ui const a, Vec4ui const b) {
    return select(f, a * b, a);
}

// Horizontal add
static inline uint64_t horizontal_add(Vec4ui const a) {
    uint64x2_t sum = vpaddlq_u32(a);
    return vgetq_lane_u64(sum, 0) + vgetq_lane_u64(sum, 1);
}

// function max
static inline Vec4ui max(Vec4ui const a, Vec4ui const b) {
    return vmaxq_u32(a, b);
}
// function min
static inline Vec4ui min(Vec4ui const a, Vec4ui const b) {
    return vminq_u32(a, b);
}

// Rotate functions
static inline Vec4ui rotate_left(Vec4ui const a, int b) {
    return vshlq_n_u32(a, b);
}
static inline Vec4ui rotate_right(Vec4ui const a, int b) {
    return vshrq_n_u32(a, b);
}

} // namespace VCL_NAMESPACE
#endif // VEC128_4UI_ARM_H