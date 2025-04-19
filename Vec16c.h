#ifndef VEC128_16C_ARM_H
#define VEC128_16C_ARM_H
#include <arm_neon.h>
#include "Vec16uc.h"
namespace VCL_NAMESPACE {
/*****************************************************************************
*
*     Vector of 16 8-bit signed integers
*
*****************************************************************************/
class Vec16c {
private:
    int8x16_t xmm;
public:
    // Default constructor:
    Vec16c() {
        xmm = vdupq_n_s8(0);
    }
    // Constructor to broadcast the same value into all elements:
    Vec16c(int8_t i) {
        xmm = vdupq_n_s8(i);
    }
    // Constructor to build from all elements:
    Vec16c(int8_t i0, int8_t i1, int8_t i2, int8_t i3, int8_t i4, int8_t i5, int8_t i6, int8_t i7,
        int8_t i8, int8_t i9, int8_t i10, int8_t i11, int8_t i12, int8_t i13, int8_t i14, int8_t i15) {
        int8_t _data[16] = {i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15};
        xmm = vld1q_s8(_data);
    }
    // Constructor to convert from type int8x16_t used in intrinsics:
    Vec16c(int8x16_t const x) {
        xmm = x;
    }
    // Copy constructor
    Vec16c(const Vec16c& other) {
        xmm = other.xmm;
    }
    // Assignment operator to convert from type int8x16_t used in intrinsics:
    Vec16c & operator = (int8x16_t const x) {
        xmm = x;
        return *this;
    }
    // Type cast operator to convert to int8x16_t used in intrinsics
    operator int8x16_t() const {
        return xmm;
    }
    // Member function to load from array (unaligned)
    Vec16c & load(void const * p) {
        xmm = vld1q_s8((int8_t const*)p);
        return *this;
    }
    // Member function to load from array (aligned)
    Vec16c & load_a(void const * p) {
        //https://stackoverflow.com/questions/45714535/performance-of-unaligned-simd-load-store-on-aarch64
        int8_t *ap = (int8_t*)__builtin_assume_aligned(p, 16);
        xmm = vld1q_s8(ap);
        return *this;
    }
    // Member function to store into array (unaligned)
    void store(void * p) const {
        vst1q_s8((int8_t*)p, xmm);
    }
    // Member function to store into array,aligned by 16
    void store_a(void * p) const {
        vst1q_s8((int8_t*)p, xmm);
    }
    // Partial load. Load n elements and set the rest to 0
    Vec16c & load_partial(int n, void const * p) {
        if (n >= 16) load(p);
        else if (n <= 0) *this = 0;
        else if (((int)(intptr_t)p & 0xFFF) < 0xFF0) {
            // p is at least 16 bytes from a page boundary. OK to read 16 bytes
            load(p);// 1<=n<=15,should call cutoff
        }
        else {
            // worst case. read 1 byte at a time and suffer store forwarding penalty
            // unless the compiler can optimize this
            char x[16] = {0};
            for (int i = 0; i < n; i++) x[i] = ((char const *)p)[i];
            load(x);
        }
        cutoff(n);// used to padding zero, when n is less than 16
        return *this;
    }
    // Partial store. Store n elements
    void store_partial(int n, void * p) const {
        // storing in bigger blocks may be unsafe unless compiler option -fno-strict-aliasing is specified,
        // therefore we have to rely on the compiler to optimize this
        int8_t s[16];
        store(s);
        if (uint32_t(n) > 16) n = 16;
        for (int i = 0; i < n; i++) {
            ((int8_t*)p)[i] = s[i];
        }
    }
    // cut off vector to n elements. The last 16-n elements are set to zero
    Vec16c & cutoff(int n) {
        if (uint32_t(n) >= 16) return *this;
        //   This line defines a constant array mask of 32 `char` elements. The first 16 elements are set to `-1` (which corresponds to `0xFF` in hexadecimal, representing all bits set to 1), and the remaining 16 elements are set to `0` (representing all bits set to 0). This mask will be used to selectively clear elements in the vector.
        const int8_t mask[32] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        *this &= Vec16c().load(mask + 16 - n);
        return *this;
    }
    // Overload the &= operator
    Vec16c& operator&=(const Vec16c& rhs) {
        xmm = vandq_s8(xmm, rhs.xmm);
        return *this;
    }

    // Member function to change a single element in vector
    Vec16c & insert(int index, int8_t value) {
        // const int8_t maskl[32] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        //     -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
        // int8x16_t broad = vdupq_n_s8(value);  // broadcast value into all elements
        // int8x16_t mask  = _mm_loadu_si128((__m128i const*)(maskl + 16 - (index & 0x0F))); // mask with FF at index position
        // xmm = selectb(mask, broad, xmm);
        xmm[index & 0x0F] = value;
        //xmm = vsetq_lane_s8(value, xmm, index & 0x0F);
        return *this;
    }
    /* Note: The extract(), insert(), size(), [], etc. all use int index for consistency.
    An unsigned type for index might cause problems in case of underflow, for example:
    for (i = 0; i < a.size() - 4; i++) a[i] = ...
    This would go nuts if a.size() is 2.
    */
    // Member function extract a single element from vector
    int8_t extract(int index) const {
        int8_t x[16];
        store(x);
        return x[index & 0x0F];
    }
    // Extract a single element. Use store function if extracting more than one element.
    // Operator [] can only read an element, not write.
    int8_t operator [] (int index) const {
        return extract(index);
    }
    static constexpr int size() {
        return 16;
    }
    static constexpr int elementtype() {
        return 4;
    };
};

// vector operator + : add element by element
static inline Vec16c operator + (Vec16c const a, Vec16c const b) {
    return vqaddq_s8(a, b);
}

// vector operator += : add
static inline Vec16c & operator += (Vec16c & a, Vec16c const b) {
    a = a + b;
    return a;
}

// postfix operator ++
static inline Vec16c operator ++ (Vec16c & a, int) {
    Vec16c a0 = a;
    a = a + 1;
    return a0;
}

// prefix operator ++
static inline Vec16c & operator ++ (Vec16c & a) {
    a = a + 1;
    return a;
}

// vector operator - : subtract element by element
static inline Vec16c operator - (Vec16c const a, Vec16c const b) {
    return vqsubq_s8(a, b);
}
// vector operator - : unary minus
static inline Vec16c operator - (Vec16c const a) {
    //return vqsubq_s8(Vec16c(0), a);
    return vqnegq_s8(a);
}
// vector operator -= : add
static inline Vec16c & operator -= (Vec16c & a, Vec16c const b) {
    a = a - b;
    return a;
}

// postfix operator --
static inline Vec16c operator -- (Vec16c & a, int) {
    Vec16c a0 = a;
    a = a - 1;
    return a0;
}

// prefix operator --
static inline Vec16c & operator -- (Vec16c & a) {
    a = a - 1;
    return a;
}

// vector operator * : multiply element by element
#define _INT8_SATURATION_ 1
static inline Vec16c operator * (Vec16c const a, Vec16c const b) {
#ifdef _INT8_SATURATION_
    int16x8_t temp_low = vmull_s8(vget_low_s8(a), vget_low_s8(b));
    int16x8_t temp_high = vmull_s8(vget_high_s8(a), vget_high_s8(b));

    int8x8_t result_low = vqmovn_s16(temp_low);
    int8x8_t result_high = vqmovn_s16(temp_high);

    return vcombine_s8(result_low, result_high);
#else
    return vmulq_s8(a, b);
#endif
}

// vector operator *= : multiply
static inline Vec16c & operator *= (Vec16c & a, Vec16c const b) {
    a = a * b;
    return a;
}

// vector operator << : shift left all elements
static inline Vec16c operator << (Vec16c const a, int b) {
    return vshrq_n_s8(a, b);
}
// vector operator <<= : shift left
static inline Vec16c & operator <<= (Vec16c & a, int b) {
    a = a << b;
    return a;
}

// vector operator >> : shift right arithmetic all elements
static inline Vec16c operator >> (Vec16c const a, int b) {
    return vshrq_n_s8(a, b);
}

// vector operator >>= : shift right arithmetic
static inline Vec16c & operator >>= (Vec16c & a, int b) {
    a = a >> b;
    return a;
}

// vector operator == : returns true for elements for which a == b
static inline Vec16uc operator == (Vec16c const a, Vec16c const b) {
    return vceqq_s8(a, b);
}

// vector operator != : returns true for elements for which a != b
static inline Vec16uc operator != (Vec16c const a, Vec16c const b) {
    return vmvnq_u8(a == b);
}

// vector operator > : returns true for elements for which a > b (signed)
static inline Vec16uc operator > (Vec16c const a, Vec16c const b) {
    return vcgtq_s8(a, b);
}

// vector operator < : returns true for elements for which a < b (signed)
static inline Vec16uc operator < (Vec16c const a, Vec16c const b) {
    return b > a;
}

// vector operator >= : returns true for elements for which a > b (signed)
static inline Vec16uc operator >= (Vec16c const a, Vec16c const b) {
    return vcgeq_s8(a, b);
}

// vector operator <= : returns true for elements for which a < b (signed)
static inline Vec16uc operator <= (Vec16c const a, Vec16c const b) {
    return b >= a;
}

// vector operator & : bitwise and
static inline Vec16c operator & (Vec16c const a, Vec16c const b) {
    return vandq_s8(a, b);
}
static inline Vec16c operator && (Vec16c const a, Vec16c const b) {
    return a & b;
}
// vector operator &= : bitwise and
// static inline Vec16c & operator &= (Vec16c & a, Vec16c const b) {
//     a = a & b;
//     return a;
// }

// vector operator | : bitwise or
static inline Vec16c operator | (Vec16c const a, Vec16c const b) {
    return vorrq_s8(a, b);
}
static inline Vec16c operator || (Vec16c const a, Vec16c const b) {
    return a | b;
}
// vector operator |= : bitwise or
static inline Vec16c & operator |= (Vec16c & a, Vec16c const b) {
    a = a | b;
    return a;
}

// vector operator ^ : bitwise xor
static inline Vec16c operator ^ (Vec16c const a, Vec16c const b) {
    return veorq_s8(a, b);
}
// vector operator ^= : bitwise xor
static inline Vec16c & operator ^= (Vec16c & a, Vec16c const b) {
    a = a ^ b;
    return a;
}

// vector operator ~ : bitwise not
static inline Vec16c operator ~ (Vec16c const a) {
    return vmvnq_s8(a);
}

// vector operator ! : logical not, returns true for elements == 0
static inline Vec16uc operator ! (Vec16c const a) {
    return vceqzq_s8(a);
}

// Functions for this class

// Select between two operands. Corresponds to this pseudocode:
// for (int i = 0; i < 16; i++) result[i] = s[i] ? a[i] : b[i];
// Each byte in s must be either 0 (false) or -1 (true). No other values are allowed.
static inline Vec16c select(Vec16uc const s, Vec16c const a, Vec16c const b) {
    return vbslq_s8(s, a, b);
}

// Conditional add: For all vector elements i: result[i] = f[i] ? (a[i] + b[i]) : a[i]
static inline Vec16c if_add(Vec16uc const f, Vec16c const a, Vec16c const b) {
    //These conversions do not change the bit pattern represented by the vector.
    return a + (Vec16c(vreinterpretq_s8_u8(f)) & b);
}

// Conditional sub: For all vector elements i: result[i] = f[i] ? (a[i] - b[i]) : a[i]
static inline Vec16c if_sub(Vec16uc const f, Vec16c const a, Vec16c const b) {
    return a - (Vec16c(vreinterpretq_s8_u8(f)) & b);
}

// Conditional mul: For all vector elements i: result[i] = f[i] ? (a[i] * b[i]) : a[i]
static inline Vec16c if_mul(Vec16uc const f, Vec16c const a, Vec16c const b) {
    return select(f, a * b, a);
}

// Horizontal add: Calculates the sum of all vector elements. Overflow will wrap around
static inline int32_t horizontal_add(Vec16c const a) {
    // Pairwise add adjacent elements and accumulate into 16-bit integers
    int16x8_t pairwise_sum = vpaddlq_s8(a);
    // Pairwise add adjacent elements and accumulate into 32-bit integers
    int32x4_t pairwise_sum_32 = vpaddlq_s16(pairwise_sum);
    // Pairwise add adjacent elements and accumulate into 64-bit integers
    int64x2_t pairwise_sum_64 = vpaddlq_s32(pairwise_sum_32);
    // Extract the final sum from the 64-bit integers
    int64_t sum = vgetq_lane_s64(pairwise_sum_64, 0) + vgetq_lane_s64(pairwise_sum_64, 1);
    return static_cast<int32_t>(sum);
}

// function max: a > b ? a : b
static inline Vec16c max(Vec16c const a, Vec16c const b) {
    return vmaxq_s8(a, b);
}

// function min: a < b ? a : b
static inline Vec16c min(Vec16c const a, Vec16c const b) {
    return vminq_s8(a, b);
}

// function abs: a >= 0 ? a : -a
static inline Vec16c abs(Vec16c const a) {
    return vabsq_s8(a);
}

int8x16_t abs_saturate(int8x16_t vec) {
    // Compute the absolute value
    int8x16_t abs_vec = vabsq_s8(vec);

    // Create a vector with all elements set to 127
    int8x16_t max_val = vdupq_n_s8(127);

    // Compare the original vector with -128
    uint8x16_t mask = vceqq_s8(vec, vdupq_n_s8(-128));

    // Use the mask to select between the absolute value and 127
    abs_vec = vbslq_s8(mask, max_val, abs_vec);

    return abs_vec;
}

//rotate each element left by b bits
static inline Vec16c rotate_left(Vec16c const a, int b) 
{
    return vshlq_n_s8(a, b);
}

//rotate each element right by b bits
static inline Vec16c rotate_right(Vec16c const a, int b) 
{
    return vshrq_n_s8(a, b);
}
}
#endif