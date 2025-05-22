#ifndef VEC128_4F_ARM_H
#define VEC128_4F_ARM_H
#include <arm_neon.h>
#include "Vec4ui.h"
namespace VCL_NAMESPACE {
/*****************************************************************************
*
*     // Vec4f: Vector of 4 single precision floating point values
*
*****************************************************************************/
class Vec4f {
private:
    float32x4_t xmm;
public:
    // Default constructor
    Vec4f() {
        xmm = vdupq_n_f32(0.0f);
    }
    // Broadcast constructor
    Vec4f(float i) {
        xmm = vdupq_n_f32(i);
    }
    // Constructor to build from all elements
    Vec4f(float f0, float f1, float f2, float f3) {
        float tmp[4] = {f0, f1, f2, f3};
        xmm = vld1q_f32(tmp);
    }
    // Constructor to convert from float32x4_t
    Vec4f(float32x4_t const x) {
        xmm = x;
    }
    // Copy constructor
    Vec4f(const Vec4f& other) {
        xmm = other.xmm;
    }
    // Assignment operator to convert from type int8x16_t used in intrinsics:
    Vec4f & operator = (float32x4_t const x) {
        xmm = x;
        return *this;
    }
    // Type cast operator to convert to float32x4_t
    operator float32x4_t() const {
        return xmm;
    }
    // Member functions to load from array
    Vec4f & load(void const * p) {
        xmm = vld1q_f32((float const*)p);
        return *this;
    }
// Member function to load from array (aligned)
    Vec4f & load_a(void const * p) {
        //https://stackoverflow.com/questions/45714535/performance-of-unaligned-simd-load-store-on-aarch64
        float *ap = (float*)__builtin_assume_aligned(p, 16);
        xmm = vld1q_f32(ap);
        return *this;
    }
    // Member function to store into array (unaligned)
    void store(void * p) const {
        vst1q_f32((float *)p, xmm);
    }
    // Member function to store into array,aligned by 8
    void store_a(void * p) const {
        vst1q_f32((float *)p, xmm);
    }
    // Overload the &= operator
    Vec4f& operator&=(const Vec4f& rhs) {
        // xmm = vreinterpretq_f32_u32(vandq_u32(vreinterpretq_u32_f32(xmm), vreinterpretq_u32_f32(rhs)));
        xmm = vreinterpretq_f32_s32(vandq_s32(vreinterpretq_s32_f32(xmm), vreinterpretq_s32_f32(rhs)));
        return *this;
    }

    // Partial load. Load n elements and set the rest to 0
    Vec4f & load_partial(int n, void const * p) {
        if (n >= 4) load(p);
        else if (n <= 0) *this = 0;
        else if (((int)(intptr_t)p & 0xFFF) < 0xFF0) {
            // p is at least 16 bytes from a page boundary. OK to read 16 bytes
            load(p);// 1<=n<=15,should call cutoff
        }
        else {
            // worst case. read 1 byte at a time and suffer store forwarding penalty
            // unless the compiler can optimize this
            float x[4] = {0};
            for (int i = 0; i < n; i++) x[i] = ((float const *)p)[i];
            load(x);
        }
        cutoff(n);// used to padding zero, when n is less than 16
        return *this;
    }

    // Partial store. Store n elements
    void store_partial(int n, void * p) const {
        // storing in bigger blocks may be unsafe unless compiler option -fno-strict-aliasing is specified,
        // therefore we have to rely on the compiler to optimize this
        float s[4];
        store(s);
        if (uint32_t(n) > 4) n = 4;
        for (int i = 0; i < n; i++) {
            ((float*)p)[i] = s[i];
        }
    }
    // cut off vector to n elements. The last 8-n elements are set to zero
    Vec4f& cutoff(int n) {
        if (uint32_t(n) >= 4) return *this;
        const uint32_t mask[8] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 
                                  0, 0, 0, 0};
        *this &= Vec4f().load(mask + 4 - n);
        return *this;
    }

    // Member function to change a single element in vector
    Vec4f& insert(int index, float value) {
        xmm[index & 0x03] = value;
        return *this;
    }
    /* Note: The extract(), insert(), size(), [], etc. all use int index for consistency.
    An unsigned type for index might cause problems in case of underflow, for example:
    for (i = 0; i < a.size() - 4; i++) a[i] = ...
    This would go nuts if a.size() is 2.
    */
    // Member function extract a single element from vector
    float extract(int index) const {
        float x[4];
        store(x);
        return x[index & 0x03];
    }
    // Extract a single element. Use store function if extracting more than one element.
    // Operator [] can only read an element, not write.
    float operator [] (int index) const {
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
static inline Vec4f operator + (Vec4f const a, Vec4f const b) {
    return vaddq_f32(a, b);
}
// vector operator += : add
static inline Vec4f & operator += (Vec4f & a, Vec4f const b) {
    a = a + b;
    return a;
}
// postfix operator ++
static inline Vec4f operator ++ (Vec4f & a, int) {
    Vec4f a0 = a;
    a = a + 1;
    return a0;
}
// prefix operator ++
static inline Vec4f & operator ++ (Vec4f & a) {
    a = a + 1;
    return a;
}
// vector operator - : subtract element by element
static inline Vec4f operator - (Vec4f const a, Vec4f const b) {
    return vsubq_f32(a, b);
}
// vector operator - : unary minus
static inline Vec4f operator - (Vec4f const a) {
    return vnegq_f32(a);
}
// vector operator -= : subtract
static inline Vec4f & operator -= (Vec4f & a, Vec4f const b) {
    a = a - b;
    return a;
}
// postfix operator --
static inline Vec4f operator -- (Vec4f & a, int) {
    Vec4f a0 = a;
    a = a - 1;
    return a0;
}
// prefix operator --
static inline Vec4f & operator -- (Vec4f & a) {
    a = a - 1;
    return a;
}
// vector operator * : multiply element by element
static inline Vec4f operator * (Vec4f const a, Vec4f const b) {
    return vmulq_f32(a, b);
}
// vector operator *= : multiply
static inline Vec4f & operator *= (Vec4f & a, Vec4f const b) {
    a = a * b;
    return a;
}

// vector operator / : divide vector and scalar
static inline Vec4f operator / (Vec4f const a, float b) {
    return vdivq_f32(a, Vec4f(b));
}
// vector operator / : divide scalar and vector
static inline Vec4f operator / (float a, Vec4f const b) {
    return vdivq_f32(Vec4f(a), b);
}
// vector operator / : divide
static inline Vec4f operator / (Vec4f const a, Vec4f const b) {
    return vdivq_f32(a, b);
}
// vector operator /= : divide
static inline Vec4f & operator /= (Vec4f & a, Vec4f const b) {
    a = vdivq_f32(a, b);;
    return a;
}

// vector operator == : returns true for elements for which a == b
static inline Vec4ui operator == (Vec4f const a, Vec4f const b) {
    return vceqq_f32(a, b);
}
// vector operator != : returns true for elements for which a != b
static inline Vec4ui operator != (Vec4f const a, Vec4f const b) {
    return vmvnq_u32(vceqq_f32(a, b));
}
// vector operator > : returns true for elements for which a > b (signed)
static inline Vec4ui operator > (Vec4f const a, Vec4f const b) {
    return vcgtq_f32(a, b);
}
// vector operator < : returns true for elements for which a < b (signed)
static inline Vec4ui operator < (Vec4f const a, Vec4f const b) {
    return b > a;
}
// vector operator >= : returns true for elements for which a >= b (signed)
static inline Vec4ui operator >= (Vec4f const a, Vec4f const b) {
    return vcgeq_f32(a, b);
}
// vector operator <= : returns true for elements for which a <= b (signed)
static inline Vec4ui operator <= (Vec4f const a, Vec4f const b) {
    return b >= a;
}
// vector operator & : bitwise and
static inline Vec4f operator & (Vec4f const a, Vec4f const b) {
    return vreinterpretq_f32_u32(vandq_u32(vreinterpretq_u32_f32(a), vreinterpretq_u32_f32(b)));
}
// vector operator | : bitwise or
static inline Vec4f operator | (Vec4f const a, Vec4f const b) {
    return vreinterpretq_f32_u32(vorrq_u32(vreinterpretq_u32_f32(a), vreinterpretq_u32_f32(b)));
}
// vector operator ^ : bitwise xor
static inline Vec4f operator ^ (Vec4f const a, Vec4f const b) {
    return vreinterpretq_f32_u32(veorq_u32(vreinterpretq_u32_f32(a), vreinterpretq_u32_f32(b)));
}
// vector operator ~ : bitwise not
static inline Vec4f operator ~ (Vec4f const a) {
    return vreinterpretq_f32_u32(vmvnq_u32(vreinterpretq_u32_f32(a)));
}
// // vector operator &= : bitwise and equal
// static inline Vec4f & operator &= (Vec4f & a, Vec4f const b) {
//     a = a & b;
//     return a;
// }

// Select between two operands
static inline Vec4f select(Vec4ui const s, Vec4f const a, Vec4f const b) {
    return vbslq_f32(s, a, b);
}
// Conditional add
static inline Vec4f if_add(Vec4ui const f, Vec4f const a, Vec4f const b) {
    return a + (Vec4f(vreinterpretq_f32_u32(f)) & b);
}
// Conditional sub
static inline Vec4f if_sub(Vec4ui const f, Vec4f const a, Vec4f const b) {
    return a - (Vec4f(vreinterpretq_f32_u32(f)) & b);
}
// Conditional mul
static inline Vec4f if_mul(Vec4ui const f, Vec4f const a, Vec4f const b) {
    return select(f, a * b, a);
}
// Horizontal add
static inline float horizontal_add(Vec4f const a) {
    return vaddvq_f32(a);
}
// function max
static inline Vec4f max(Vec4f const a, Vec4f const b) {
    return vmaxq_f32(a, b);
}
// function min
static inline Vec4f min(Vec4f const a, Vec4f const b) {
    return vminq_f32(a, b);
}
// function abs
static inline Vec4f abs(Vec4f const a) {
    return vabsq_f32(a);
}
} // namespace VCL_NAMESPACE

#endif // VEC128_4F_ARM_H