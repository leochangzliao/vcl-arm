#ifndef VEC128_8US_ARM_H
#define VEC128_8US_ARM_H
#include <arm_neon.h>
namespace VCL_NAMESPACE {
/*****************************************************************************
*
*     // vector of 8 16-bit unsigned integers
*
*****************************************************************************/
class Vec8us {
private:
    uint16x8_t xmm;
public:
    // Default constructor:
    Vec8us() {
        xmm = vdupq_n_u16(0);
    }
    // Constructor to broadcast same value:
    Vec8us(uint16_t i) {
        xmm = vdupq_n_u16(i);
    }
    // Constructor to build from all elements:
    Vec8us(uint16_t i0, uint16_t i1, uint16_t i2, uint16_t i3, 
           uint16_t i4, uint16_t i5, uint16_t i6, uint16_t i7) {
        uint16_t _data[8] = {i0, i1, i2, i3, i4, i5, i6, i7};
        xmm = vld1q_u16(_data);
    }
    // Constructor to convert from uint16x8_t:
    Vec8us(uint16x8_t const x) {
        xmm = x;
    }
    // Copy constructor:
    Vec8us(const Vec8us& other) {
        xmm = other.xmm;
    }
    // Assignment operator:
    Vec8us & operator = (uint16x8_t const x) {
        xmm = x;
        return *this;
    }
    // Type cast operator:
    operator uint16x8_t() const {
        return xmm;
    }
    // Load functions:
    Vec8us & load(void const * p) {
        xmm = vld1q_u16((uint16_t const*)p);
        return *this;
    }
    Vec8us & load_a(void const * p) {
        uint16_t *ap = (uint16_t*)__builtin_assume_aligned(p, 16);
        xmm = vld1q_u16(ap);
        return *this;
    }
    // Store functions:
    void store(void * p) const {
        vst1q_u16((uint16_t*)p, xmm);
    }
    void store_a(void * p) const {
        vst1q_u16((uint16_t*)p, xmm);
    }
    // Partial load/store:
    Vec8us & load_partial(int n, void const * p) {
        if (n >= 8) load(p);
        else if (n <= 0) *this = 0;
        else if (((int)(intptr_t)p & 0xFFF) < 0xFF0) {
            load(p);
        }
        else {
            uint16_t x[8] = {0};
            for (int i = 0; i < n; i++) x[i] = ((uint16_t const *)p)[i];
            load(x);
        }
        cutoff(n);
        return *this;
    }
    void store_partial(int n, void * p) const {
        if (n <= 0) return;  // Exit if n is negative or zero
        uint16_t s[8];
        store(s);
        if (uint32_t(n) > 8) n = 8;
        for (int i = 0; i < n; i++) {
            ((uint16_t*)p)[i] = s[i];
        }
    }
    // Cutoff vector:
    Vec8us & cutoff(int n) {
        if (n <= 0) // Exit if n is negative or zero
        {
            *this = 0;
            return *this;  
        }
        if (uint32_t(n) >= 8) return *this;
        const uint16_t mask[16] = {0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
                                  0,0,0,0,0,0,0,0};
        *this &= Vec8us().load(mask + 8 - n);
        return *this;
    }

    // Overload the &= operator
    Vec8us& operator&=(const Vec8us& rhs) {
        xmm = vandq_u16(xmm, rhs.xmm);
        return *this;
    }
    // Element access:
    Vec8us & insert(int index, uint16_t value) {
        xmm[index & 0x07] = value;
        return *this;
    }
    uint16_t extract(int index) const {
        uint16_t x[8];
        store(x);
        return x[index & 0x07];
    }
    uint16_t operator [] (int index) const {
        return extract(index);
    }
    static constexpr int size() {
        return 8;
    }
    static constexpr int elementtype() {
        return 7;
    }
};

// vector operator + : add element by element
static inline Vec8us operator + (Vec8us const a, Vec8us const b) {
    return vqaddq_u16(a, b);
}

// vector operator += : add
static inline Vec8us & operator += (Vec8us & a, Vec8us const b) {
    a = a + b;
    return a;
}
// postfix operator ++
static inline Vec8us operator ++ (Vec8us & a, int) {
    Vec8us a0 = a;
    a = a + 1;
    return a0;
}
// prefix operator ++
static inline Vec8us & operator ++ (Vec8us & a) {
    a = a + 1;
    return a;
}

// vector operator - : subtract element by element
static inline Vec8us operator - (Vec8us const a, Vec8us const b) {
    return vqsubq_u16(a, b);
}

// vector operator -= : subtract
static inline Vec8us & operator -= (Vec8us & a, Vec8us const b) {
    a = a - b;
    return a;
}

// postfix operator --
static inline Vec8us & operator -- (Vec8us & a) {
    a = a - 1;
    return a;
}
// prefix operator --
static inline Vec8us operator -- (Vec8us & a, int) {
    Vec8us a0 = a;
    a = a - 1;
    return a0;
}
// vector operator * : multiply element by element
// Proper multiplication for Vec8us, handling overflow
static inline Vec8us operator * (Vec8us const a, Vec8us const b) {
    uint32x4_t low = vmull_u16(vget_low_u16(a), vget_low_u16(b));
    uint32x4_t high = vmull_u16(vget_high_u16(a), vget_high_u16(b));
    return vcombine_u16(vmovn_u32(low), vmovn_u32(high));
}

// vector operator *= : multiply
static inline Vec8us & operator *= (Vec8us & a, Vec8us const b) {
    a = a * b;
    return a;
}
// vector operator << : shift left all elements
static inline Vec8us operator << (Vec8us const a, int b) {
    return vshlq_n_u16(a, b);
}
// vector operator <<= : shift left
static inline Vec8us & operator <<= (Vec8us & a, int b) {
    a = a << b;
    return a;
}
// vector operator >> : shift right arithmetic all elements
static inline Vec8us operator >> (Vec8us const a, int b) {
    return vshrq_n_u16(a, b);
}
// vector operator >>= : shift right arithmetic
static inline Vec8us & operator >>= (Vec8us & a, int b) {
    a = a >> b;
    return a;
}
// vector operator == : returns true for elements for which a == b
static inline Vec8us operator == (Vec8us const a, Vec8us const b) {
    return vceqq_u16(a, b);
}
// vector operator != : returns true for elements for which a != b
static inline Vec8us operator != (Vec8us const a, Vec8us const b) {
    return vmvnq_u16(vceqq_u16(a, b));
}
// vector operator > : returns true for elements for which a > b
static inline Vec8us operator > (Vec8us const a, Vec8us const b) {
    return vcgtq_u16(a, b);
}
// vector operator < : returns true for elements for which a < b
static inline Vec8us operator < (Vec8us const a, Vec8us const b) {
    return vcltq_u16(a, b);
}
// vector operator >= : returns true for elements for which a >= b
static inline Vec8us operator >= (Vec8us const a, Vec8us const b) {
    return vcgeq_u16(a, b);
}
// vector operator <= : returns true for elements for which a <= b
static inline Vec8us operator <= (Vec8us const a, Vec8us const b) {
    return vcleq_u16(a, b);
}

// vector operator & : bitwise and
static inline Vec8us operator & (Vec8us const a, Vec8us const b) {
    return vandq_u16(a, b);
}

// vector operator | : bitwise or
static inline Vec8us operator | (Vec8us const a, Vec8us const b) {
    return vorrq_u16(a, b);
}

// vector operator ^ : bitwise xor
static inline Vec8us operator ^ (Vec8us const a, Vec8us const b) {
    return veorq_u16(a, b);
}

// vector operator ~ : bitwise not
static inline Vec8us operator ~ (Vec8us const a) {
    return vmvnq_u16(a);
}
// vector operator &= : bitwise and equal
// static inline Vec8us & operator &= (Vec8us & a, Vec8us const b) {
//     a = a & b;
//     return a;
// }

// Select between two operands
static inline Vec8us select(Vec8us const s, Vec8us const a, Vec8us const b) {
    return vbslq_u16(s, a, b);
}

// Conditional add
static inline Vec8us if_add(Vec8us const f, Vec8us const a, Vec8us const b) {
    return a + (f & b);
}

// Conditional sub
static inline Vec8us if_sub(Vec8us const f, Vec8us const a, Vec8us const b) {
    return a - (f & b);
}

// Conditional mul
static inline Vec8us if_mul(Vec8us const f, Vec8us const a, Vec8us const b) {
    return select(f, a * b, a);
}

// Horizontal add
static inline uint32_t horizontal_add(Vec8us const a) {
    uint32x4_t sum32 = vpaddlq_u16(a);
    uint64x2_t sum64 = vpaddlq_u32(sum32);
    return vgetq_lane_u64(sum64, 0) + vgetq_lane_u64(sum64, 1);
}

// function max
static inline Vec8us max(Vec8us const a, Vec8us const b) {
    return vmaxq_u16(a, b);
}
// function min
static inline Vec8us min(Vec8us const a, Vec8us const b) {
    return vminq_u16(a, b);
}

// Rotate functions
static inline Vec8us rotate_left(Vec8us const a, int b) {
    return vshlq_n_u16(a, b);
}
static inline Vec8us rotate_right(Vec8us const a, int b) {
    return vshrq_n_u16(a, b);
}

} // namespace VCL_NAMESPACE
#endif // VEC128_8US_ARM_H