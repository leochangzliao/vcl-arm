#ifndef VEC128_2Q_ARM_H
#define VEC128_2Q_ARM_H
#include <arm_neon.h>
#include "Vec2uq.h"
namespace VCL_NAMESPACE {
/*****************************************************************************
*
*     // // Vector of 2 64-bit signed integers
*
*****************************************************************************/
class Vec2q {
private:
    int64x2_t xmm;
public:
    // Default constructor
    Vec2q() {
        xmm = vdupq_n_s64(0);
    }
    // Broadcast constructor
    Vec2q(int64_t i) {
        xmm = vdupq_n_s64(i);
    }
    // Constructor to build from all elements
    Vec2q(int64_t i0, int64_t i1) {
        int64_t tmp[4] = {i0, i1};
        xmm = vld1q_s64(tmp);
    }
    // Constructor to convert from int64x2_t
    Vec2q(int64x2_t const x) {
        xmm = x;
    }
    // Copy constructor
    Vec2q(const Vec2q& other) {
        xmm = other.xmm;
    }
    // Assignment operator to convert from type int8x16_t used in intrinsics:
    Vec2q & operator = (int64x2_t const x) {
        xmm = x;
        return *this;
    }
    // Type cast operator to convert to int64x2_t
    operator int64x2_t() const {
        return xmm;
    }
    // Member functions to load from array
    Vec2q & load(void const * p) {
        xmm = vld1q_s64((int64_t const*)p);
        return *this;
    }
// Member function to load from array (aligned)
    Vec2q & load_a(void const * p) {
        //https://stackoverflow.com/questions/45714535/performance-of-unaligned-simd-load-store-on-aarch64
        int64_t *ap = (int64_t*)__builtin_assume_aligned(p, 16);
        xmm = vld1q_s64(ap);
        return *this;
    }
    // Member function to store into array (unaligned)
    void store(void * p) const {
        vst1q_s64((int64_t *)p, xmm);
    }
    // Member function to store into array,aligned by 8
    void store_a(void * p) const {
        vst1q_s64((int64_t *)p, xmm);
    }
    // Overload the &= operator
    Vec2q& operator&=(const Vec2q& rhs) {
        xmm = vandq_s64(xmm, rhs.xmm);
        return *this;
    }

    // Partial load. Load n elements and set the rest to 0
    Vec2q & load_partial(int n, void const * p) {
        if (n >= 2) load(p);
        else if (n <= 0) *this = 0;
        else if (((int)(intptr_t)p & 0xFFF) < 0xFF0) {
            // p is at least 16 bytes from a page boundary. OK to read 16 bytes
            load(p);// 1<=n<=15,should call cutoff
        }
        else {
            // worst case. read 1 byte at a time and suffer store forwarding penalty
            // unless the compiler can optimize this
            int64_t x[2] = {0};
            for (int i = 0; i < n; i++) x[i] = ((int64_t const *)p)[i];
            load(x);
        }
        cutoff(n);// used to padding zero, when n is less than 16
        return *this;
    }

    // Partial store. Store n elements
    void store_partial(int n, void * p) const {
        // storing in bigger blocks may be unsafe unless compiler option -fno-strict-aliasing is specified,
        // therefore we have to rely on the compiler to optimize this
        int64_t s[2];
        store(s);
        if (uint64_t(n) > 2) n = 2;
        for (int i = 0; i < n; i++) {
            ((int64_t*)p)[i] = s[i];
        }
    }
    // cut off vector to n elements. The last 8-n elements are set to zero
    Vec2q& cutoff(int n) {
        if (uint64_t(n) >= 2) return *this;
        const uint64_t mask[4] = {0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 
                                 0, 0};
        *this &= Vec2q().load(mask + 2 - n);
        return *this;
    }

    // Member function to change a single element in vector
    Vec2q& insert(int index, int64_t value) {
        xmm[index & 0x01] = value;
        return *this;
    }
    /* Note: The extract(), insert(), size(), [], etc. all use int index for consistency.
    An unsigned type for index might cause problems in case of underflow, for example:
    for (i = 0; i < a.size() - 4; i++) a[i] = ...
    This would go nuts if a.size() is 2.
    */
    // Member function extract a single element from vector
    int64_t extract(int index) const {
        int64_t x[2];
        store(x);
        return x[index & 0x01];
    }
    // Extract a single element. Use store function if extracting more than one element.
    // Operator [] can only read an element, not write.
    int64_t operator [] (int index) const {
        return extract(index);
    }
    static constexpr int size() {
        return 2;
    }
    static constexpr int elementtype() {
        return 11;
    };
};
// vector operator + : add element by element
static inline Vec2q operator + (Vec2q const a, Vec2q const b) {
    return vqaddq_s64(a, b);
}
// vector operator += : add
static inline Vec2q & operator += (Vec2q & a, Vec2q const b) {
    a = a + b;
    return a;
}
// postfix operator ++
static inline Vec2q operator ++ (Vec2q & a, int) {
    Vec2q a0 = a;
    a = a + 1;
    return a0;
}
// prefix operator ++
static inline Vec2q & operator ++ (Vec2q & a) {
    a = a + 1;
    return a;
}
// vector operator - : subtract element by element
static inline Vec2q operator - (Vec2q const a, Vec2q const b) {
    return vqsubq_s64(a, b);
}
// vector operator - : unary minus
static inline Vec2q operator - (Vec2q const a) {
    return vnegq_s64(a);
}
// vector operator -= : subtract
static inline Vec2q & operator -= (Vec2q & a, Vec2q const b) {
    a = a - b;
    return a;
}
// postfix operator --
static inline Vec2q operator -- (Vec2q & a, int) {
    Vec2q a0 = a;
    a = a - 1;
    return a0;
}
// prefix operator --
static inline Vec2q & operator -- (Vec2q & a) {
    a = a - 1;
    return a;
}
// vector operator * : multiply element by element
static inline Vec2q operator * (Vec2q const a, Vec2q const b) {
    int64_t a0 = vgetq_lane_s64(a, 0);
    int64_t a1 = vgetq_lane_s64(a, 1);
    int64_t b0 = vgetq_lane_s64(b, 0);
    int64_t b1 = vgetq_lane_s64(b, 1);
    return Vec2q(a0 * b0, a1 * b1);
}
// vector operator *= : multiply
static inline Vec2q & operator *= (Vec2q & a, Vec2q const b) {
    a = a * b;
    return a;
}
// vector operator << : shift left all elements
static inline Vec2q operator << (Vec2q const a, int b) {
    return vshlq_n_s64(a, b);
}
// vector operator <<= : shift left
static inline Vec2q & operator <<= (Vec2q & a, int b) {
    a = a << b;
    return a;
}
// vector operator >> : shift right arithmetic all elements
static inline Vec2q operator >> (Vec2q const a, int b) {
    return vshrq_n_s64(a, b);
}
// vector operator >>= : shift right arithmetic
static inline Vec2q & operator >>= (Vec2q & a, int b) {
    a = a >> b;
    return a;
}
// vector operator == : returns true for elements for which a == b
static inline Vec2uq operator == (Vec2q const a, Vec2q const b) {
    return vceqq_s64(a, b);
}
// vector operator != : returns true for elements for which a != b
static inline Vec2uq operator != (Vec2q const a, Vec2q const b) {
    return veorq_u64(vceqq_s64(a, b),  vdupq_n_u64(0xFFFFFFFFFFFFFFFF));
}
// vector operator > : returns true for elements for which a > b (signed)
static inline Vec2uq operator > (Vec2q const a, Vec2q const b) {
    return vcgtq_s64(a, b);
}
// vector operator < : returns true for elements for which a < b (signed)
static inline Vec2uq operator < (Vec2q const a, Vec2q const b) {
    return b > a;
}
// vector operator >= : returns true for elements for which a >= b (signed)
static inline Vec2uq operator >= (Vec2q const a, Vec2q const b) {
    return vcgeq_s64(a, b);
}
// vector operator <= : returns true for elements for which a <= b (signed)
static inline Vec2uq operator <= (Vec2q const a, Vec2q const b) {
    return b >= a;
}
// vector operator & : bitwise and
static inline Vec2q operator & (Vec2q const a, Vec2q const b) {
    return vandq_s64(a, b);
}
// vector operator | : bitwise or
static inline Vec2q operator | (Vec2q const a, Vec2q const b) {
    return vorrq_s64(a, b);
}
// vector operator ^ : bitwise xor
static inline Vec2q operator ^ (Vec2q const a, Vec2q const b) {
    return veorq_s64(a, b);
}
// vector operator ~ : bitwise not
static inline Vec2q operator ~ (Vec2q const a) {
    return Vec2q(veorq_s64(a, vdupq_n_s64(-1)));
}
// // vector operator &= : bitwise and equal
// static inline Vec2q & operator &= (Vec2q & a, Vec2q const b) {
//     a = a & b;
//     return a;
// }

// Select between two operands
static inline Vec2q select(Vec2uq const s, Vec2q const a, Vec2q const b) {
    return vbslq_s64(s, a, b);
}
// Conditional add
static inline Vec2q if_add(Vec2uq const f, Vec2q const a, Vec2q const b) {
    return a + (Vec2q(vreinterpretq_s64_u64(f)) & b);
}
// Conditional sub
static inline Vec2q if_sub(Vec2uq const f, Vec2q const a, Vec2q const b) {
    return a - (Vec2q(vreinterpretq_s64_u64(f)) & b);
}
// Conditional mul
static inline Vec2q if_mul(Vec2uq const f, Vec2q const a, Vec2q const b) {
    return select(f, a * b, a);
}
// Horizontal add
static inline int64_t horizontal_add(Vec2q const a) {
     return vgetq_lane_s64(a, 0) + vgetq_lane_s64(a, 1);
}
// function max
static inline Vec2q max(Vec2q const a, Vec2q const b) {
    return select(a > b, a, b);
}
// function min
static inline Vec2q min(Vec2q const a, Vec2q const b) {
    return select(a <= b, a, b);
}
// function abs
static inline Vec2q abs(Vec2q const a) {
    return vabsq_s64(a);
}
// Rotate functions
static inline Vec2q rotate_left(Vec2q const a, int b) {
    return vshlq_n_s64(a, b);
}
static inline Vec2q rotate_right(Vec2q const a, int b) {
    return vshrq_n_s64(a, b);
}
} // namespace VCL_NAMESPACE

#endif // VEC128_2Q_ARM_H