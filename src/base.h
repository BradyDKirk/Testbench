#ifndef BASE_H
#define BASE_H

#define global        static
#define internal      static
#define local_persist static

#include <stdbool.h>
#include <stdint.h>

typedef int8_t    i8;
typedef int16_t   i16;
typedef int32_t   i32;
typedef int64_t   i64;

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

typedef i8        b8;
typedef i16       b16;
typedef i32       b32;
typedef i64       b64;

typedef float     f32;
typedef double    f64;

#define KB(n) (((u64)n) << 10)
#define MB(n) (((u64)n) << 20)
#define GB(n) (((u64)n) << 30)
#define TB(n) (((u64)n) << 40)

#define Minimum(a, b) ((a < b) ? (a) : (b))
#define Maximum(a, b) ((a > b) ? (a) : (b))

#define Assert(expression) if (!(expression)) { *(int *)0 = 0; }

#endif // BASE_H
