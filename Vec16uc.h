#ifndef VEC128_16UC_ARM_H
#define VEC128_16UC_ARM_H
#include <arm_neon.h>
namespace VCL_NAMESPACE 
{
/*****************************************************************************
*
*     Vector of 16 8-bit unsigned integers
*
*****************************************************************************/
class Vec16uc{
private:
    uint8x16_t xmm;
public:
    // Default constructor:
    Vec16uc() {
        xmm = vdupq_n_u8(0);
    }
    // Constructor to broadcast the same value into all elements:
    Vec16uc(uint8_t i) {
        xmm = vdupq_n_u8(i);
    }
    // Constructor to build from all elements:
    Vec16uc(uint8_t i0, uint8_t i1, uint8_t i2, uint8_t i3, uint8_t i4, uint8_t i5, uint8_t i6, uint8_t i7,
        uint8_t i8, uint8_t i9, uint8_t i10, uint8_t i11, uint8_t i12, uint8_t i13, uint8_t i14, uint8_t i15) {
        uint8_t _data[16] = {i0, i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15};
        xmm = vld1q_u8(_data);
    }
    // Constructor to convert from type uint8x16_t used in intrinsics:
    Vec16uc(uint8x16_t const x) {
        xmm = x;
    }
    // Copy constructor
    Vec16uc(const Vec16uc& other) {
        xmm = other.xmm;
    }
    // Assignment operator to convert from type uint8x16_t used in intrinsics:
    Vec16uc & operator = (uint8x16_t const x) {
        xmm = x;
        return *this;
    }
    // Type cast operator to convert to uint8x16_t used in intrinsics
    operator uint8x16_t() const {
        return xmm;
    }
    // Member function to load from array (unaligned)
    Vec16uc & load(void const * p) {
        xmm = vld1q_u8((uint8_t const*)p);
        return *this;
    }
    // Member function to load from array (aligned)
    Vec16uc & load_a(void const * p) {
        uint8_t *ap = (uint8_t*)__builtin_assume_aligned(p, 16);
        xmm = vld1q_u8(ap);
        return *this;
    }
    // Member function to store into array (unaligned)
    void store(void * p) const {
        vst1q_u8((uint8_t*)p, xmm);
    }
    // Member function to store into array, aligned by 16
    void store_a(void * p) const {
        vst1q_u8((uint8_t*)p, xmm);
    }
    // Partial load. Load n elements and set the rest to 0
    Vec16uc & load_partial(int n, void const * p) {
        if (n >= 16) load(p);
        else if (n <= 0) *this = 0;
        else if (((int)(intptr_t)p & 0xFFF) < 0xFF0) {
            load(p);
        }
        else {
            uint8_t x[16] = {0};
            for (int i = 0; i < n; i++) x[i] = ((uint8_t const *)p)[i];
            load(x);
        }
        cutoff(n);
        return *this;
    }
    // Partial store. Store n elements
    void store_partial(int n, void * p) const {
        uint8_t s[16];
        store(s);
        if (uint32_t(n) > 16) n = 16;
        for (int i = 0; i < n; i++) {
            ((uint8_t*)p)[i] = s[i];
        }
    }
    // cut off vector to n elements. The last 16-n elements are set to zero
    Vec16uc & cutoff(int n) {
        if (uint32_t(n) >= 16) return *this;
        const uint8_t mask[32] = { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        *this &= Vec16uc().load(mask + 16 - n);
        return *this;
    }
    // Overload the &= operator
    Vec16uc& operator&=(const Vec16uc& rhs) {
        xmm = vandq_u8(xmm, rhs.xmm);
        return *this;
    }

    // Member function to change a single element in vector
    Vec16uc & insert(int index, uint8_t value) {
        xmm[index & 0x0F] = value;
        return *this;
    }

    /* Note: The extract(), insert(), size(), [], etc. all use int index for consistency.
    An unsigned type for index might cause problems in case of underflow, for example:
    for (i = 0; i < a.size() - 4; i++) a[i] = ...
    This would go nuts if a.size() is 2.
    */
    // Member function extract a single element from vector
    uint8_t extract(int index) const {
        uint8_t x[16];
        store(x);
        return x[index & 0x0F];
    }
    // Extract a single element. Use store function if extracting more than one element.
    // Operator [] can only read an element, not write.
    uint8_t operator [] (int index) const {
        return extract(index);
    }
    static constexpr int size() {
        return 16;
    }
    static constexpr int elementtype() {
        return 5;
    };
};

// vector operator + : add element by element
static inline Vec16uc operator + (Vec16uc const a, Vec16uc const b) {
    return vqaddq_u8(a, b);
}

// vector operator += : add
static inline Vec16uc & operator += (Vec16uc & a, Vec16uc const b) {
    a = a + b;
    return a;
}

// postfix operator ++
static inline Vec16uc operator ++ (Vec16uc & a, int) {
    Vec16uc a0 = a;
    a = a + 1;
    return a0;
}

// prefix operator ++
static inline Vec16uc & operator ++ (Vec16uc & a) {
    a = a + 1;
    return a;
}

// vector operator - : subtract element by element
static inline Vec16uc operator - (Vec16uc const a, Vec16uc const b) {
    return vqsubq_u8(a, b);
}

// vector operator -= : subtract
static inline Vec16uc & operator -= (Vec16uc & a, Vec16uc const b) {
    a = a - b;
    return a;
}

// postfix operator --
static inline Vec16uc operator -- (Vec16uc & a, int) {
    Vec16uc a0 = a;
    a = a - 1;
    return a0;
}

// prefix operator --
static inline Vec16uc & operator -- (Vec16uc & a) {
    a = a - 1;
    return a;
}

// vector operator * : multiply element by element
static inline Vec16uc operator * (Vec16uc const a, Vec16uc const b) {
    return vmulq_u8(a, b);
}

// vector operator *= : multiply
static inline Vec16uc & operator *= (Vec16uc & a, Vec16uc const b) {
    a = a * b;
    return a;
}

// vector operator << : shift left all elements
static inline Vec16uc operator << (Vec16uc const a, int b) {
    return vshlq_n_u8(a, b);
}

// vector operator <<= : shift left
static inline Vec16uc & operator <<= (Vec16uc & a, int b) {
    a = a << b;
    return a;
}

// vector operator >> : shift right all elements
static inline Vec16uc operator >> (Vec16uc const a, int b) {
    return vshrq_n_u8(a, b);
}

// vector operator >>= : shift right
static inline Vec16uc & operator >>= (Vec16uc & a, int b) {
    a = a >> b;
    return a;
}

// vector operator == : returns true for elements for which a == b
static inline Vec16uc operator == (Vec16uc const a, Vec16uc const b) {
    return vceqq_u8(a, b);
}

// vector operator != : returns true for elements for which a != b
static inline Vec16uc operator != (Vec16uc const a, Vec16uc const b) {
    return vmvnq_u8(a == b);
}

// vector operator > : returns true for elements for which a > b
static inline Vec16uc operator > (Vec16uc const a, Vec16uc const b) {
    return vcgtq_u8(a, b);
}

// vector operator < : returns true for elements for which a < b
static inline Vec16uc operator < (Vec16uc const a, Vec16uc const b) {
    return vcltq_u8(a, b);
}

// vector operator >= : returns true for elements for which a >= b
static inline Vec16uc operator >= (Vec16uc const a, Vec16uc const b) {
    return vcgeq_u8(a, b);
}

// vector operator <= : returns true for elements for which a <= b
static inline Vec16uc operator <= (Vec16uc const a, Vec16uc const b) {
    return vcleq_u8(a, b);
}

// vector operator & : bitwise and
static inline Vec16uc operator & (Vec16uc const a, Vec16uc const b) {
    return vandq_u8(a, b);
}

// vector operator &= : bitwise and
// static inline Vec16uc & operator &= (Vec16uc & a, Vec16uc const b) {
//     a = a & b;
//     return a;
// }

// vector operator | : bitwise or
static inline Vec16uc operator | (Vec16uc const a, Vec16uc const b) {
    return vorrq_u8(a, b);
}

// vector operator |= : bitwise or
static inline Vec16uc & operator |= (Vec16uc & a, Vec16uc const b) {
    a = a | b;
    return a;
}

// vector operator ^ : bitwise xor
static inline Vec16uc operator ^ (Vec16uc const a, Vec16uc const b) {
    return veorq_u8(a, b);
}

// vector operator ^= : bitwise xor
static inline Vec16uc & operator ^= (Vec16uc & a, Vec16uc const b) {
    a = a ^ b;
    return a;
}

// vector operator ~ : bitwise not
static inline Vec16uc operator ~ (Vec16uc const a) {
    return vmvnq_u8(a);
}

// vector operator ! : logical not, returns true for elements == 0
static inline Vec16uc operator ! (Vec16uc const a) {
    return vceqq_u8(a, vdupq_n_u8(0));
}

// // Functions for this class

// Select between two operands. Corresponds to this pseudocode:
// for (int i = 0; i < 16; i++) result[i] = s[i] ? a[i] : b[i];
// Each byte in s must be either 0 (false) or -1 (true). No other values are allowed.
static inline Vec16uc select(Vec16uc const s, Vec16uc const a, Vec16uc const b) {
    return vbslq_u8(s, a, b);
}

// Conditional add: For all vector elements i: result[i] = f[i] ? (a[i] + b[i]) : a[i]
static inline Vec16uc if_add(Vec16uc const f, Vec16uc const a, Vec16uc const b) {
    return a + (f & b);
}

// Conditional sub: For all vector elements i: result[i] = f[i] ? (a[i] - b[i]) : a[i]
static inline Vec16uc if_sub(Vec16uc const f, Vec16uc const a, Vec16uc const b) {
    return a - (f & b);
}

// Conditional mul: For all vector elements i: result[i] = f[i] ? (a[i] * b[i]) : a[i]
static inline Vec16uc if_mul(Vec16uc const f, Vec16uc const a, Vec16uc const b) {
    return select(f, a * b, a);
}

// Horizontal add: Calculates the sum of all vector elements. Overflow will wrap around
static inline uint32_t horizontal_add(Vec16uc const a) {
    // Pairwise add adjacent elements and accumulate into 16-bit integers
    uint16x8_t pairwise_sum = vpaddlq_u8(a);
    // Pairwise add adjacent elements and accumulate into 32-bit integers
    uint32x4_t pairwise_sum_32 = vpaddlq_u16(pairwise_sum);
    // Pairwise add adjacent elements and accumulate into 64-bit integers
    uint64x2_t pairwise_sum_64 = vpaddlq_u32(pairwise_sum_32);
    // Extract the final sum from the 64-bit integers
    uint64_t sum = vgetq_lane_u64(pairwise_sum_64, 0) + vgetq_lane_u64(pairwise_sum_64, 1);
    return static_cast<uint32_t>(sum);
}

// function max: a > b ? a : b
static inline Vec16uc max(Vec16uc const a, Vec16uc const b) {
    return vmaxq_u8(a, b);
}

// function min: a < b ? a : b
static inline Vec16uc min(Vec16uc const a, Vec16uc const b) {
    return vminq_u8(a, b);
}

//rotate each element left by b bits
static inline Vec16uc rotate_left(Vec16uc const a, int b) {
    return vshlq_n_u8(a, b);
}

//rotate each element right by b bits
static inline Vec16uc rotate_right(Vec16uc const a, int b) {
    return vshrq_n_u8(a, b);
}
}
#endif