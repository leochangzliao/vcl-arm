#ifndef VEC128_8S_ARM_H
#define VEC128_8S_ARM_H
#include <arm_neon.h>
#include "Vec8us.h"
namespace VCL_NAMESPACE {
/*****************************************************************************
*
*     // vector of 8 16-bit signed integers
*
*****************************************************************************/
class Vec8s {
private:
    int16x8_t xmm;
public:
    // Default constructor
    Vec8s() {
        xmm = vdupq_n_s16(0);
    }
    // Broadcast constructor
    Vec8s(int16_t i) {
        xmm = vdupq_n_s16(i);
    }
    // Constructor to build from all elements
    Vec8s(int16_t i0, int16_t i1, int16_t i2, int16_t i3, 
          int16_t i4, int16_t i5, int16_t i6, int16_t i7) {
        int16_t tmp[8] = {i0, i1, i2, i3, i4, i5, i6, i7};
        xmm = vld1q_s16(tmp);
    }
    // Constructor to convert from int16x8_t
    Vec8s(int16x8_t const x) {
        xmm = x;
    }
    // Copy constructor
    Vec8s(const Vec8s& other) {
        xmm = other.xmm;
    }
    // Assignment operator to convert from type int8x16_t used in intrinsics:
    Vec8s & operator = (int16x8_t const x) {
        xmm = x;
        return *this;
    }
    // Type cast operator to convert to int16x8_t
    operator int16x8_t() const {
        return xmm;
    }
    // Member functions to load from array
    Vec8s & load(void const * p) {
        xmm = vld1q_s16((int16_t const*)p);
        return *this;
    }
// Member function to load from array (aligned)
    Vec8s & load_a(void const * p) {
        //https://stackoverflow.com/questions/45714535/performance-of-unaligned-simd-load-store-on-aarch64
        int16_t *ap = (int16_t*)__builtin_assume_aligned(p, 16);
        xmm = vld1q_s16(ap);
        return *this;
    }
    // Member function to store into array (unaligned)
    void store(void * p) const {
        vst1q_s16((int16_t *)p, xmm);
    }
    // Member function to store into array,aligned by 8
    void store_a(void * p) const {
        vst1q_s16((int16_t *)p, xmm);
    }
    // Overload the &= operator
    Vec8s& operator&=(const Vec8s& rhs) {
        xmm = vandq_s16(xmm, rhs.xmm);
        return *this;
    }

    // Partial load. Load n elements and set the rest to 0
    Vec8s & load_partial(int n, void const * p) {
        if (n >= 8) load(p);
        else if (n <= 0) *this = 0;
        else if (((int)(intptr_t)p & 0xFFF) < 0xFF0) {
            // p is at least 16 bytes from a page boundary. OK to read 16 bytes
            load(p);// 1<=n<=15,should call cutoff
        }
        else {
            // worst case. read 1 byte at a time and suffer store forwarding penalty
            // unless the compiler can optimize this
            int16_t x[8] = {0};
            for (int i = 0; i < n; i++) x[i] = ((int16_t const *)p)[i];
            load(x);
        }
        cutoff(n);// used to padding zero, when n is less than 16
        return *this;
    }

    // Partial store. Store n elements
    void store_partial(int n, void * p) const {
        // storing in bigger blocks may be unsafe unless compiler option -fno-strict-aliasing is specified,
        // therefore we have to rely on the compiler to optimize this
        int16_t s[8];
        store(s);
        if (uint32_t(n) > 8) n = 8;
        for (int i = 0; i < n; i++) {
            ((int16_t*)p)[i] = s[i];
        }
    }
    // cut off vector to n elements. The last 8-n elements are set to zero
    Vec8s& cutoff(int n) {
        if (uint32_t(n) >= 8) return *this;
        // Define a mask array of 16 uint16_t elements where the first 8 are set to 0xFFFF (all bits 1)
        // and the remaining 8 are set to 0. This mask will be used to clear elements beyond position n.
        const uint16_t mask[16] = { 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
                                   0, 0, 0, 0, 0, 0, 0, 0 };
        *this &= Vec8s().load(mask + 8 - n);
        return *this;
    }

    // Member function to change a single element in vector
    Vec8s& insert(int index, int16_t value) {
        // const int8_t maskl[32] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        //     -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
        // int8x16_t broad = vdupq_n_s8(value);  // broadcast value into all elements
        // int8x16_t mask  = _mm_loadu_si128((__m128i const*)(maskl + 16 - (index & 0x0F))); // mask with FF at index position
        // xmm = selectb(mask, broad, xmm);

        // xmm = vsetq_lane_s16(value, xmm, index & 0x07);
        xmm[index & 0x07] = value;
        return *this;
    }
    /* Note: The extract(), insert(), size(), [], etc. all use int index for consistency.
    An unsigned type for index might cause problems in case of underflow, for example:
    for (i = 0; i < a.size() - 4; i++) a[i] = ...
    This would go nuts if a.size() is 2.
    */
    // Member function extract a single element from vector
    int16_t extract(int index) const {
        int16_t x[8];
        store(x);
        return x[index & 0x07];
    }
    // Extract a single element. Use store function if extracting more than one element.
    // Operator [] can only read an element, not write.
    int16_t operator [] (int index) const {
        return extract(index);
    }
    static constexpr int size() {
        return 8;
    }
    static constexpr int elementtype() {
        return 6;
    };
};
// vector operator + : add element by element
static inline Vec8s operator + (Vec8s const a, Vec8s const b) {
    return vqaddq_s16(a, b);
}
// vector operator += : add
static inline Vec8s & operator += (Vec8s & a, Vec8s const b) {
    a = a + b;
    return a;
}
// postfix operator ++
static inline Vec8s operator ++ (Vec8s & a, int) {
    Vec8s a0 = a;
    a = a + 1;
    return a0;
}
// prefix operator ++
static inline Vec8s & operator ++ (Vec8s & a) {
    a = a + 1;
    return a;
}
// vector operator - : subtract element by element
static inline Vec8s operator - (Vec8s const a, Vec8s const b) {
    return vqsubq_s16(a, b);
}
// vector operator - : unary minus
static inline Vec8s operator - (Vec8s const a) {
    return vnegq_s16(a);
}
// vector operator -= : subtract
static inline Vec8s & operator -= (Vec8s & a, Vec8s const b) {
    a = a - b;
    return a;
}
// postfix operator --
static inline Vec8s operator -- (Vec8s & a, int) {
    Vec8s a0 = a;
    a = a - 1;
    return a0;
}
// prefix operator --
static inline Vec8s & operator -- (Vec8s & a) {
    a = a - 1;
    return a;
}
// vector operator * : multiply element by element
static inline Vec8s operator * (Vec8s const a, Vec8s const b) {
    int32x4_t temp_low = vmull_s16(vget_low_s16(a), vget_low_s16(b));
    int32x4_t temp_high = vmull_s16(vget_high_s16(a), vget_high_s16(b));

    int16x4_t result_low = vqmovn_s32(temp_low);
    int16x4_t result_high = vqmovn_s32(temp_high);

    return vcombine_s16(result_low, result_high);
}
// vector operator *= : multiply
static inline Vec8s & operator *= (Vec8s & a, Vec8s const b) {
    a = a * b;
    return a;
}
// vector operator << : shift left all elements
static inline Vec8s operator << (Vec8s const a, int b) {
    return vshlq_n_s16(a, b);
}
// vector operator <<= : shift left
static inline Vec8s & operator <<= (Vec8s & a, int b) {
    a = a << b;
    return a;
}
// vector operator >> : shift right arithmetic all elements
static inline Vec8s operator >> (Vec8s const a, int b) {
    return vshrq_n_s16(a, b);
}
// vector operator >>= : shift right arithmetic
static inline Vec8s & operator >>= (Vec8s & a, int b) {
    a = a >> b;
    return a;
}
// vector operator == : returns true for elements for which a == b
static inline Vec8us operator == (Vec8s const a, Vec8s const b) {
    return vceqq_s16(a, b);
}
// vector operator != : returns true for elements for which a != b
static inline Vec8us operator != (Vec8s const a, Vec8s const b) {
    return vmvnq_u16(a == b);
}
// vector operator > : returns true for elements for which a > b (signed)
static inline Vec8us operator > (Vec8s const a, Vec8s const b) {
    return vcgtq_s16(a, b);
}
// vector operator < : returns true for elements for which a < b (signed)
static inline Vec8us operator < (Vec8s const a, Vec8s const b) {
    return b > a;
}
// vector operator >= : returns true for elements for which a >= b (signed)
static inline Vec8us operator >= (Vec8s const a, Vec8s const b) {
    return vcgeq_s16(a, b);
}
// vector operator <= : returns true for elements for which a <= b (signed)
static inline Vec8us operator <= (Vec8s const a, Vec8s const b) {
    return b >= a;
}
// vector operator & : bitwise and
static inline Vec8s operator & (Vec8s const a, Vec8s const b) {
    return vandq_s16(a, b);
}
// vector operator | : bitwise or
static inline Vec8s operator | (Vec8s const a, Vec8s const b) {
    return vorrq_s16(a, b);
}
// vector operator ^ : bitwise xor
static inline Vec8s operator ^ (Vec8s const a, Vec8s const b) {
    return veorq_s16(a, b);
}
// vector operator ~ : bitwise not
static inline Vec8s operator ~ (Vec8s const a) {
    return vmvnq_s16(a);
}
// // vector operator &= : bitwise and equal
// static inline Vec8s & operator &= (Vec8s & a, Vec8s const b) {
//     a = a & b;
//     return a;
// }

// Select between two operands
static inline Vec8s select(Vec8us const s, Vec8s const a, Vec8s const b) {
    return vbslq_s16(s, a, b);
}
// Conditional add
static inline Vec8s if_add(Vec8us const f, Vec8s const a, Vec8s const b) {
    return a + (Vec8s(vreinterpretq_s16_u16(f)) & b);
}
// Conditional sub
static inline Vec8s if_sub(Vec8us const f, Vec8s const a, Vec8s const b) {
    return a - (Vec8s(vreinterpretq_s16_u16(f)) & b);
}
// Conditional mul
static inline Vec8s if_mul(Vec8us const f, Vec8s const a, Vec8s const b) {
    return select(f, a * b, a);
}
// Horizontal add
static inline int32_t horizontal_add(Vec8s const a) {
    int32x4_t pairwise_sum = vpaddlq_s16(a);
    int64x2_t pairwise_sum_64 = vpaddlq_s32(pairwise_sum);
    int64_t sum = vgetq_lane_s64(pairwise_sum_64, 0) + vgetq_lane_s64(pairwise_sum_64, 1);
    return static_cast<int32_t>(sum);
}
// function max
static inline Vec8s max(Vec8s const a, Vec8s const b) {
    return vmaxq_s16(a, b);
}
// function min
static inline Vec8s min(Vec8s const a, Vec8s const b) {
    return vminq_s16(a, b);
}
// function abs
static inline Vec8s abs(Vec8s const a) {
    return vabsq_s16(a);
}
// Rotate functions
static inline Vec8s rotate_left(Vec8s const a, int b) {
    return vshlq_n_s16(a, b);
}
static inline Vec8s rotate_right(Vec8s const a, int b) {
    return vshrq_n_s16(a, b);
}
} // namespace VCL_NAMESPACE

#endif // VEC128_8S_ARM_H