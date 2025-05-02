#ifndef VEC128_2UQ_ARM_H
#define VEC128_2UQ_ARM_H
#include <arm_neon.h>
namespace VCL_NAMESPACE {
/*****************************************************************************
*
*     // Vector of 2 64-bit unsigned integers
*
*****************************************************************************/
class Vec2uq {
private:
    uint64x2_t xmm;
public:
    // Default constructor:
    Vec2uq() {
        xmm = vdupq_n_u64(0);
    }
    // Constructor to broadcast same value:
    Vec2uq(uint64_t i) {
        xmm = vdupq_n_u64(i);
    }
    // Constructor to build from all elements:
    Vec2uq(uint64_t i0, uint64_t i1) {
        uint64_t _data[2] = {i0, i1};
        xmm = vld1q_u64(_data);
    }
    // Constructor to convert from uint16x8_t:
    Vec2uq(uint64x2_t const x) {
        xmm = x;
    }
    // Copy constructor:
    Vec2uq(const Vec2uq& other) {
        xmm = other.xmm;
    }
    // Assignment operator:
    Vec2uq& operator = (uint64x2_t const x) {
        xmm = x;
        return *this;
    }
    // Type cast operator:
    operator uint64x2_t() const {
        return xmm;
    }
    // Load functions:
    Vec2uq& load(void const * p) {
        xmm = vld1q_u64((uint64_t const*)p);
        return *this;
    }
    Vec2uq& load_a(void const * p) {
        uint64_t *ap = (uint64_t*)__builtin_assume_aligned(p, 16);
        xmm = vld1q_u64(ap);
        return *this;
    }
    // Store functions:
    void store(void * p) const {
        vst1q_u64((uint64_t*)p, xmm);
    }
    void store_a(void * p) const {
        vst1q_u64((uint64_t*)p, xmm);
    }
    // Partial load/store:
    Vec2uq& load_partial(int n, void const * p) {
        if (n >= 2) load(p);
        else if (n <= 0) *this = 0;
        else if (((int)(intptr_t)p & 0xFFF) < 0xFF0) {
            load(p);
        }
        else {
            uint64_t x[2] = {0};
            for (int i = 0; i < n; i++) x[i] = ((uint64_t const *)p)[i];
            load(x);
        }
        cutoff(n);
        return *this;
    }
    void store_partial(int n, void * p) const {
        if (n <= 0) return;  // Exit if n is negative or zero
        uint64_t s[2];
        store(s);
        if (uint64_t(n) > 2) n = 2;
        for (int i = 0; i < n; i++) {
            ((uint64_t*)p)[i] = s[i];
        }
    }
    // Cutoff vector:
    Vec2uq& cutoff(int n) {
        if (n <= 0) // Exit if n is negative or zero
        {
            *this = 0;
            return *this;  
        }
        if (uint64_t(n) >= 2) return *this;
        const uint64_t mask[4] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 
                                 0, 0};
        *this &= Vec2uq().load(mask + 2 - n);
        return *this;
    }

    // Overload the &= operator
    Vec2uq& operator&=(const Vec2uq& rhs) {
        xmm = vandq_u64(xmm, rhs.xmm);
        return *this;
    }
    // Element access:
    Vec2uq& insert(int index, uint64_t value) {
        xmm[index & 0x01] = value;
        return *this;
    }
    uint64_t extract(int index) const {
        uint64_t x[2];
        store(x);
        return x[index & 0x01];
    }
    uint64_t operator [] (int index) const {
        return extract(index);
    }
    static constexpr int size() {
        return 4;
    }
    static constexpr int elementtype() {
        return 10;
    }
};

// vector operator + : add element by element
static inline Vec2uq operator + (Vec2uq const a, Vec2uq const b) {
    return vqaddq_u64(a, b);
}

// vector operator += : add
static inline Vec2uq & operator += (Vec2uq & a, Vec2uq const b) {
    a = a + b;
    return a;
}
// postfix operator ++
static inline Vec2uq operator ++ (Vec2uq & a, int) {
    Vec2uq a0 = a;
    a = a + 1;
    return a0;
}
// prefix operator ++
static inline Vec2uq & operator ++ (Vec2uq & a) {
    a = a + 1;
    return a;
}

// vector operator - : subtract element by element
static inline Vec2uq operator - (Vec2uq const a, Vec2uq const b) {
    return vqsubq_u64(a, b);
}

// vector operator -= : subtract
static inline Vec2uq & operator -= (Vec2uq & a, Vec2uq const b) {
    a = a - b;
    return a;
}

// postfix operator --
static inline Vec2uq & operator -- (Vec2uq & a) {
    a = a - 1;
    return a;
}
// prefix operator --
static inline Vec2uq operator -- (Vec2uq & a, int) {
    Vec2uq a0 = a;
    a = a - 1;
    return a0;
}
// vector operator * : multiply element by element
// Proper multiplication for Vec2uq, handling overflow
static inline Vec2uq operator * (Vec2uq const a, Vec2uq const b) {
    uint64_t a0 = vgetq_lane_u64(a, 0);
    uint64_t a1 = vgetq_lane_u64(a, 1);
    uint64_t b0 = vgetq_lane_u64(b, 0);
    uint64_t b1 = vgetq_lane_u64(b, 1);
    return Vec2uq(a0 * b0, a1 * b1);
}

// vector operator *= : multiply
static inline Vec2uq & operator *= (Vec2uq & a, Vec2uq const b) {
    a = a * b;
    return a;
}
// vector operator << : shift left all elements
static inline Vec2uq operator << (Vec2uq const a, int b) {
    return vshlq_n_u64(a, b);
}
// vector operator <<= : shift left
static inline Vec2uq & operator <<= (Vec2uq & a, int b) {
    a = a << b;
    return a;
}
// vector operator >> : shift right arithmetic all elements
static inline Vec2uq operator >> (Vec2uq const a, int b) {
    return vshrq_n_u64(a, b);
}
// vector operator >>= : shift right arithmetic
static inline Vec2uq & operator >>= (Vec2uq & a, int b) {
    a = a >> b;
    return a;
}
// vector operator == : returns true for elements for which a == b
static inline Vec2uq operator == (Vec2uq const a, Vec2uq const b) {
    return vceqq_u64(a, b);
}
// vector operator != : returns true for elements for which a != b
static inline Vec2uq operator != (Vec2uq const a, Vec2uq const b) {
    return veorq_u64(vceqq_u64(a, b), vdupq_n_u64(0xFFFFFFFFFFFFFFFF));
}
// vector operator > : returns true for elements for which a > b
static inline Vec2uq operator > (Vec2uq const a, Vec2uq const b) {
    return vcgtq_u64(a, b);
}
// vector operator < : returns true for elements for which a < b
static inline Vec2uq operator < (Vec2uq const a, Vec2uq const b) {
    return vcltq_u64(a, b);
}
// vector operator >= : returns true for elements for which a >= b
static inline Vec2uq operator >= (Vec2uq const a, Vec2uq const b) {
    return vcgeq_u64(a, b);
}
// vector operator <= : returns true for elements for which a <= b
static inline Vec2uq operator <= (Vec2uq const a, Vec2uq const b) {
    return vcleq_u64(a, b);
}

// vector operator & : bitwise and
static inline Vec2uq operator & (Vec2uq const a, Vec2uq const b) {
    return vandq_u64(a, b);
}

// vector operator | : bitwise or
static inline Vec2uq operator | (Vec2uq const a, Vec2uq const b) {
    return vorrq_u64(a, b);
}

// vector operator ^ : bitwise xor
static inline Vec2uq operator ^ (Vec2uq const a, Vec2uq const b) {
    return veorq_u64(a, b);
}

// vector operator ~ : bitwise not
static inline Vec2uq operator ~ (Vec2uq const a) {
    return Vec2uq(veorq_u64(a, vdupq_n_u64(0xFFFFFFFFFFFFFFFF)));
}
// vector operator &= : bitwise and equal
// static inline Vec2uq & operator &= (Vec2uq & a, Vec2uq const b) {
//     a = a & b;
//     return a;
// }

// Select between two operands
static inline Vec2uq select(Vec2uq const s, Vec2uq const a, Vec2uq const b) {
    return vbslq_u64(s, a, b);
}

// Conditional add
static inline Vec2uq if_add(Vec2uq const f, Vec2uq const a, Vec2uq const b) {
    return a + (f & b);
}

// Conditional sub
static inline Vec2uq if_sub(Vec2uq const f, Vec2uq const a, Vec2uq const b) {
    return a - (f & b);
}

// Conditional mul
static inline Vec2uq if_mul(Vec2uq const f, Vec2uq const a, Vec2uq const b) {
    return select(f, a * b, a);
}

// Horizontal add
static inline uint64_t horizontal_add(Vec2uq const a) {
    return vgetq_lane_u64(a, 0) + vgetq_lane_u64(a, 1);
}

// function max
static inline Vec2uq max(Vec2uq const a, Vec2uq const b) {
    return select(a > b, a, b);
}
// function min
static inline Vec2uq min(Vec2uq const a, Vec2uq const b) {
    return select(a < b, a, b);
}

// Rotate functions
static inline Vec2uq rotate_left(Vec2uq const a, int b) {
    return vshlq_n_u64(a, b);
}
static inline Vec2uq rotate_right(Vec2uq const a, int b) {
    return vshrq_n_u64(a, b);
}

} // namespace VCL_NAMESPACE
#endif // VEC128_2UQ_ARM_H