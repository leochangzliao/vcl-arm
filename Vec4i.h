#ifndef VEC128_4I_ARM_H
#define VEC128_4I_ARM_H
#include <arm_neon.h>
#include "Vec4ui.h"
namespace VCL_NAMESPACE {
/*****************************************************************************
*
*     // vector of 4 32-bit signed integers
*
*****************************************************************************/
class Vec4i {
private:
    int32x4_t xmm;
public:
    // Default constructor
    Vec4i() {
        xmm = vdupq_n_s32(0);
    }
    // Broadcast constructor
    Vec4i(int32_t i) {
        xmm = vdupq_n_s32(i);
    }
    // Constructor to build from all elements
    Vec4i(int32_t i0, int32_t i1, int32_t i2, int32_t i3) {
        int32_t tmp[4] = {i0, i1, i2, i3};
        xmm = vld1q_s32(tmp);
    }
    // Constructor to convert from int32x4_t
    Vec4i(int32x4_t const x) {
        xmm = x;
    }
    // Copy constructor
    Vec4i(const Vec4i& other) {
        xmm = other.xmm;
    }
    // Assignment operator to convert from type int8x16_t used in intrinsics:
    Vec4i & operator = (int32x4_t const x) {
        xmm = x;
        return *this;
    }
    // Type cast operator to convert to int32x4_t
    operator int32x4_t() const {
        return xmm;
    }
    // Member functions to load from array
    Vec4i & load(void const * p) {
        xmm = vld1q_s32((int32_t const*)p);
        return *this;
    }
// Member function to load from array (aligned)
    Vec4i & load_a(void const * p) {
        //https://stackoverflow.com/questions/45714535/performance-of-unaligned-simd-load-store-on-aarch64
        int32_t *ap = (int32_t*)__builtin_assume_aligned(p, 16);
        xmm = vld1q_s32(ap);
        return *this;
    }
    // Member function to store into array (unaligned)
    void store(void * p) const {
        vst1q_s32((int32_t *)p, xmm);
    }
    // Member function to store into array,aligned by 8
    void store_a(void * p) const {
        vst1q_s32((int32_t *)p, xmm);
    }
    // Overload the &= operator
    Vec4i& operator&=(const Vec4i& rhs) {
        xmm = vandq_s32(xmm, rhs.xmm);
        return *this;
    }

    // Partial load. Load n elements and set the rest to 0
    Vec4i & load_partial(int n, void const * p) {
        if (n >= 4) load(p);
        else if (n <= 0) *this = 0;
        else if (((int)(intptr_t)p & 0xFFF) < 0xFF0) {
            // p is at least 16 bytes from a page boundary. OK to read 16 bytes
            load(p);// 1<=n<=15,should call cutoff
        }
        else {
            // worst case. read 1 byte at a time and suffer store forwarding penalty
            // unless the compiler can optimize this
            int32_t x[4] = {0};
            for (int i = 0; i < n; i++) x[i] = ((int32_t const *)p)[i];
            load(x);
        }
        cutoff(n);// used to padding zero, when n is less than 16
        return *this;
    }

    // Partial store. Store n elements
    void store_partial(int n, void * p) const {
        // storing in bigger blocks may be unsafe unless compiler option -fno-strict-aliasing is specified,
        // therefore we have to rely on the compiler to optimize this
        int32_t s[4];
        store(s);
        if (uint32_t(n) > 4) n = 4;
        for (int i = 0; i < n; i++) {
            ((int32_t*)p)[i] = s[i];
        }
    }
    // cut off vector to n elements. The last 8-n elements are set to zero
    Vec4i& cutoff(int n) {
        if (uint32_t(n) >= 4) return *this;
        const uint32_t mask[8] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 
                                  0, 0, 0, 0};
        *this &= Vec4i().load(mask + 4 - n);
        return *this;
    }

    // Member function to change a single element in vector
    Vec4i& insert(int index, int32_t value) {
        xmm[index & 0x03] = value;
        return *this;
    }
    /* Note: The extract(), insert(), size(), [], etc. all use int index for consistency.
    An unsigned type for index might cause problems in case of underflow, for example:
    for (i = 0; i < a.size() - 4; i++) a[i] = ...
    This would go nuts if a.size() is 2.
    */
    // Member function extract a single element from vector
    int32_t extract(int index) const {
        int32_t x[4];
        store(x);
        return x[index & 0x03];
    }
    // Extract a single element. Use store function if extracting more than one element.
    // Operator [] can only read an element, not write.
    int32_t operator [] (int index) const {
        return extract(index);
    }
    static constexpr int size() {
        return 4;
    }
    static constexpr int elementtype() {
        return 9;
    };
};
// vector operator + : add element by element
static inline Vec4i operator + (Vec4i const a, Vec4i const b) {
    return vqaddq_s32(a, b);
}
// vector operator += : add
static inline Vec4i & operator += (Vec4i & a, Vec4i const b) {
    a = a + b;
    return a;
}
// postfix operator ++
static inline Vec4i operator ++ (Vec4i & a, int) {
    Vec4i a0 = a;
    a = a + 1;
    return a0;
}
// prefix operator ++
static inline Vec4i & operator ++ (Vec4i & a) {
    a = a + 1;
    return a;
}
// vector operator - : subtract element by element
static inline Vec4i operator - (Vec4i const a, Vec4i const b) {
    return vqsubq_s32(a, b);
}
// vector operator - : unary minus
static inline Vec4i operator - (Vec4i const a) {
    return vnegq_s32(a);
}
// vector operator -= : subtract
static inline Vec4i & operator -= (Vec4i & a, Vec4i const b) {
    a = a - b;
    return a;
}
// postfix operator --
static inline Vec4i operator -- (Vec4i & a, int) {
    Vec4i a0 = a;
    a = a - 1;
    return a0;
}
// prefix operator --
static inline Vec4i & operator -- (Vec4i & a) {
    a = a - 1;
    return a;
}
// vector operator * : multiply element by element
static inline Vec4i operator * (Vec4i const a, Vec4i const b) {
    int64x2_t temp_low = vmull_s32(vget_low_s32(a), vget_low_s32(b));
    int64x2_t temp_high = vmull_s32(vget_high_s32(a), vget_high_s32(b));

    return vcombine_s32(vqmovn_s64(temp_low), vqmovn_s64(temp_high));
}
// vector operator *= : multiply
static inline Vec4i & operator *= (Vec4i & a, Vec4i const b) {
    a = a * b;
    return a;
}
// vector operator << : shift left all elements
static inline Vec4i operator << (Vec4i const a, int b) {
    return vshlq_n_s32(a, b);
}
// vector operator <<= : shift left
static inline Vec4i & operator <<= (Vec4i & a, int b) {
    a = a << b;
    return a;
}
// vector operator >> : shift right arithmetic all elements
static inline Vec4i operator >> (Vec4i const a, int b) {
    return vshrq_n_s32(a, b);
}
// vector operator >>= : shift right arithmetic
static inline Vec4i & operator >>= (Vec4i & a, int b) {
    a = a >> b;
    return a;
}
// vector operator == : returns true for elements for which a == b
static inline Vec4ui operator == (Vec4i const a, Vec4i const b) {
    return vceqq_s32(a, b);
}
// vector operator != : returns true for elements for which a != b
static inline Vec4ui operator != (Vec4i const a, Vec4i const b) {
    return vmvnq_u32(a == b);
}
// vector operator > : returns true for elements for which a > b (signed)
static inline Vec4ui operator > (Vec4i const a, Vec4i const b) {
    return vcgtq_s32(a, b);
}
// vector operator < : returns true for elements for which a < b (signed)
static inline Vec4ui operator < (Vec4i const a, Vec4i const b) {
    return b > a;
}
// vector operator >= : returns true for elements for which a >= b (signed)
static inline Vec4ui operator >= (Vec4i const a, Vec4i const b) {
    return vcgeq_s32(a, b);
}
// vector operator <= : returns true for elements for which a <= b (signed)
static inline Vec4ui operator <= (Vec4i const a, Vec4i const b) {
    return b >= a;
}
// vector operator & : bitwise and
static inline Vec4i operator & (Vec4i const a, Vec4i const b) {
    return vandq_s32(a, b);
}
// vector operator | : bitwise or
static inline Vec4i operator | (Vec4i const a, Vec4i const b) {
    return vorrq_s32(a, b);
}
// vector operator ^ : bitwise xor
static inline Vec4i operator ^ (Vec4i const a, Vec4i const b) {
    return veorq_s32(a, b);
}
// vector operator ~ : bitwise not
static inline Vec4i operator ~ (Vec4i const a) {
    return vmvnq_s32(a);
}
// // vector operator &= : bitwise and equal
// static inline Vec4i & operator &= (Vec4i & a, Vec4i const b) {
//     a = a & b;
//     return a;
// }

// Select between two operands
static inline Vec4i select(Vec4ui const s, Vec4i const a, Vec4i const b) {
    return vbslq_s32(s, a, b);
}
// Conditional add
static inline Vec4i if_add(Vec4ui const f, Vec4i const a, Vec4i const b) {
    return a + (Vec4i(vreinterpretq_s32_u32(f)) & b);
}
// Conditional sub
static inline Vec4i if_sub(Vec4ui const f, Vec4i const a, Vec4i const b) {
    return a - (Vec4i(vreinterpretq_s32_u32(f)) & b);
}
// Conditional mul
static inline Vec4i if_mul(Vec4ui const f, Vec4i const a, Vec4i const b) {
    return select(f, a * b, a);
}
// Horizontal add
static inline int64_t horizontal_add(Vec4i const a) {
    int64x2_t pairwise_sum = vpaddlq_s32(a);
    return vgetq_lane_s64(pairwise_sum, 0) + vgetq_lane_s64(pairwise_sum, 1);
}
// function max
static inline Vec4i max(Vec4i const a, Vec4i const b) {
    return vmaxq_s32(a, b);
}
// function min
static inline Vec4i min(Vec4i const a, Vec4i const b) {
    return vminq_s32(a, b);
}
// function abs
static inline Vec4i abs(Vec4i const a) {
    return vabsq_s32(a);
}
// Rotate functions
static inline Vec4i rotate_left(Vec4i const a, int b) {
    return vshlq_n_s32(a, b);
}
static inline Vec4i rotate_right(Vec4i const a, int b) {
    return vshrq_n_s32(a, b);
}
} // namespace VCL_NAMESPACE

#endif // VEC128_4I_ARM_H