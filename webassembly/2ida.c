#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct {
  char top[0x80];
  char ctx[10 * 0x10];
  char key[0x20];
  char msg[0x10];
  char flag[0x40];
  char middle[1024 - (0x80 + 10*0x10 + 0x20 + 0x10 + 0x40)];
  char table[361];
  char heap[0x10000];
} main_memory_t;


uint32_t malloc_ptr = 0;

main_memory_t main_memory = {0};


uint8_t __attribute__ ((noinline)) d(uint8_t x) {
  return ((200 * x * x) + (255 * x) + 92) % 0x100;
}

// extern wasm_rt_memory_t (*Z_envZ_memory);

#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#define LIKELY(x) __builtin_expect(!!(x), 1)

#define TRAP() \
  {printf("WASM_RT_TRAP\n");  \
  exit(1);}

#define MEMCHECK(mem, a, t)  \
  if (UNLIKELY((a) + sizeof(t) > mem->size)) TRAP()

#define DEFINE_LOAD(name, t1, t2, t3)              \
  static inline t3 name(u64 addr) {   \
    t1 result;                                     \
    memcpy(&result, &((char *)(&main_memory))[addr], sizeof(t1)); \
    return (t3)(t2)result;                         \
  }

#define DEFINE_STORE(name, t1, t2)                           \
  static inline void name(u64 addr, t2 value) { \
    t1 wrapped = (t1)value;                                  \
    memcpy(&((char *)(&main_memory))[addr], &wrapped, sizeof(t1));          \
  }

#define  u8 uint8_t
#define  s8 int8_t
#define  u16 uint16_t
#define  s16 int16_t
#define  u32 uint32_t
#define  s32 int32_t
#define  u64 uint64_t
#define  s64 int64_t

DEFINE_LOAD(i32_load, u32, u32, u32);
DEFINE_LOAD(i64_load, u64, u64, u64);
DEFINE_LOAD(i32_load8_s, s8, s32, u32);
DEFINE_LOAD(i64_load8_s, s8, s64, u64);
DEFINE_LOAD(i32_load8_u, u8, u32, u32);
DEFINE_LOAD(i64_load8_u, u8, u64, u64);
DEFINE_LOAD(i32_load16_s, s16, s32, u32);
DEFINE_LOAD(i64_load16_s, s16, s64, u64);
DEFINE_LOAD(i32_load16_u, u16, u32, u32);
DEFINE_LOAD(i64_load16_u, u16, u64, u64);
DEFINE_LOAD(i64_load32_s, s32, s64, u64);
DEFINE_LOAD(i64_load32_u, u32, u64, u64);
DEFINE_STORE(i32_store, u32, u32);
DEFINE_STORE(i64_store, u64, u64);
DEFINE_STORE(i32_store8, u8, u32);
DEFINE_STORE(i32_store16, u16, u32);
DEFINE_STORE(i64_store8, u8, u64);
DEFINE_STORE(i64_store16, u16, u64);
DEFINE_STORE(i64_store32, u32, u64);

#define DIV_S(ut, min, x, y)    (ut)((x) / (y))
#define I32_DIV_S(x, y) DIV_S(u32, INT32_MIN, (s32)x, (s32)y)

#define DIVREM_U(op, x, y) ((x) op (y))

#define DIV_U(x, y) DIVREM_U(/, x, y)

static uint32_t g3;
static char *g4;
static uint32_t g5;
static uint32_t g6;
static uint32_t g7;
static uint32_t g8;

static u32 stackAlloc(u32);
static u32 stackSave(void);
static void stackRestore(u32);
static void establishStackSpace(u32, u32);
static void setThrew(u32, u32);
static void setTempRet0(u32);
static u32 getTempRet0(void);
static void f13(u32, u32);
static void _setDecryptKey(u32, u32);
static void _decryptBlock(u32, u32);
static u32 f16(u32, u32, u32, u32);
static u32 f17(u32);
static u32 _getFlag(u32, u32);
static u32 _malloc(u32);
static void _free(u32);
static u32 f21(u32, u32);
static u32 ___errno_location(void);
static void runPostSets(void);
static u32 _memcpy(u32, u32, u32);
static u32 _memset(u32, u32, u32);
static u32 _sbrk(u32);


static u32 stackAlloc(u32 p0) {
  u32 l0 = 0;
  //FUNC_PROLOGUE;
  u32 i0, i1;
  i0 = g4;
  l0 = i0;
  i0 = g4;
  i1 = p0;
  i0 += i1;
  g4 = i0;
  i0 = g4;
  i1 = 15u;
  i0 += i1;
  i1 = 4294967280u;
  i0 &= i1;
  g4 = i0;
  i0 = l0;
  //FUNC_EPILOGUE;
  return i0;
}

static u32 stackSave(void) {
  //FUNC_PROLOGUE;
  u32 i0;
  i0 = g4;
  //FUNC_EPILOGUE;
  return i0;
}

static void stackRestore(u32 p0) {
  //FUNC_PROLOGUE;
  u32 i0;
  i0 = p0;
  g4 = i0;
  //FUNC_EPILOGUE;
}

static void establishStackSpace(u32 p0, u32 p1) {
  //FUNC_PROLOGUE;
  u32 i0;
  i0 = p0;
  g4 = i0;
  i0 = p1;
  g5 = i0;
  //FUNC_EPILOGUE;
}

static void setThrew(u32 p0, u32 p1) {
  //FUNC_PROLOGUE;
  u32 i0;
  i0 = g6;
  i0 = !(i0);
  if (i0) {
    i0 = p0;
    g6 = i0;
    i0 = p1;
    g7 = i0;
  }
  //FUNC_EPILOGUE;
}

static void setTempRet0(u32 p0) {
  //FUNC_PROLOGUE;
  u32 i0;
  i0 = p0;
  g8 = i0;
  //FUNC_EPILOGUE;
}

static u32 getTempRet0(void) {
  //FUNC_PROLOGUE;
  u32 i0;
  i0 = g8;
  //FUNC_EPILOGUE;
  return i0;
}

static void f13(u32 p0, u32 p1) {
  u32 l0 = 0, l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0, l6 = 0, l7 = 0, 
      l8 = 0, l9 = 0, l10 = 0, l11 = 0, l12 = 0, l13 = 0, l14 = 0, l15 = 0, 
      l16 = 0, l17 = 0, l18 = 0, l19 = 0, l20 = 0, l21 = 0, l22 = 0, l23 = 0, 
      l24 = 0, l25 = 0, l26 = 0, l27 = 0;
  u64 l28 = 0, l29 = 0, l30 = 0, l31 = 0, l32 = 0, l33 = 0;
  //FUNC_PROLOGUE;
  u32 i0, i1, i2, i3;
  u64 j0, j1, j2, j3;
  i0 = g4;
  l6 = i0;
  i0 = g4;
  i1 = 64u;
  i0 += i1;
  g4 = i0;
  i0 = l6;
  i1 = 32u;
  i0 += i1;
  l2 = i0;
  i1 = p1;
  j1 = i64_load((u64)(i1));
  i64_store((u64)(i0), j1);
  i0 = l2;
  i1 = p1;
  j1 = i64_load((u64)(i1 + 8));
  i64_store((u64)(i0 + 8), j1);
  i0 = l6;
  i1 = 16u;
  i0 += i1;
  l1 = i0;
  i1 = p1;
  i2 = 16u;
  i1 += i2;
  p1 = i1;
  j1 = i64_load((u64)(i1));
  i64_store((u64)(i0), j1);
  i0 = l1;
  i1 = p1;
  j1 = i64_load((u64)(i1 + 8));
  i64_store((u64)(i0 + 8), j1);
  i0 = p0;
  i1 = l2;
  j1 = i64_load((u64)(i1));
  l30 = j1;
  i64_store((u64)(i0), j1);
  i0 = p0;
  i1 = l2;
  j1 = i64_load((u64)(i1 + 8));
  l31 = j1;
  i64_store((u64)(i0 + 8), j1);
  i0 = p0;
  i1 = l1;
  j1 = i64_load((u64)(i1));
  l32 = j1;
  i64_store((u64)(i0 + 16), j1);
  i0 = p0;
  i1 = l1;
  j1 = i64_load((u64)(i1 + 8));
  l33 = j1;
  i64_store((u64)(i0 + 24), j1);
  i0 = l6;
  i1 = 48u;
  i0 += i1;
  l3 = i0;
  i1 = 8u;
  i0 += i1;
  l18 = i0;
  i0 = l3;
  i1 = 15u;
  i0 += i1;
  l12 = i0;
  i0 = l6;
  l0 = i0;
  i1 = 8u;
  i0 += i1;
  l9 = i0;
  i0 = l0;
  i1 = 1u;
  i0 += i1;
  l19 = i0;
  i0 = l0;
  i1 = 2u;
  i0 += i1;
  l20 = i0;
  i0 = l0;
  i1 = 3u;
  i0 += i1;
  l21 = i0;
  i0 = l0;
  i1 = 4u;
  i0 += i1;
  l22 = i0;
  i0 = l0;
  i1 = 5u;
  i0 += i1;
  l23 = i0;
  i0 = l0;
  i1 = 6u;
  i0 += i1;
  l24 = i0;
  i0 = l0;
  i1 = 7u;
  i0 += i1;
  l25 = i0;
  i0 = l0;
  i1 = 8u;
  i0 += i1;
  l26 = i0;
  i0 = l0;
  i1 = 9u;
  i0 += i1;
  l27 = i0;
  i0 = l0;
  i1 = 10u;
  i0 += i1;
  l13 = i0;
  i0 = l0;
  i1 = 11u;
  i0 += i1;
  l14 = i0;
  i0 = l0;
  i1 = 12u;
  i0 += i1;
  l15 = i0;
  i0 = l0;
  i1 = 13u;
  i0 += i1;
  l16 = i0;
  i0 = l0;
  i1 = 14u;
  i0 += i1;
  l17 = i0;
  i0 = l0;
  i1 = 15u;
  i0 += i1;
  l10 = i0;
  i0 = 1u;
  l7 = i0;
  L0: 
    i0 = l3;
    j1 = 0ull;
    i64_store((u64)(i0), j1);
    i0 = l3;
    j1 = 0ull;
    i64_store((u64)(i0 + 8), j1);
    i0 = l12;
    i1 = l7;
    i2 = 255u;
    i1 &= i2;
    l2 = i1;
    i32_store8((u64)(i0), i1);
    i0 = 0u;
    l8 = i0;
    L1: 
      i0 = 14u;
      l1 = i0;
      L2: 
        i0 = l3;
        i1 = l1;
        i2 = 1u;
        i1 += i2;
        i0 += i1;
        i1 = l3;
        i2 = l1;
        i1 += i2;
        i1 = i32_load8_s((u64)(i1));
        p1 = i1;
        i32_store8((u64)(i0), i1);
        i0 = 0u;
        l4 = i0;
        i0 = l1;
        i1 = 1305u;
        i0 += i1;
        i0 = i32_load8_s((u64)(i0));
        l5 = i0;
        L3: 
          i0 = l5;
          i1 = 1u;
          i0 &= i1;
          if (i0) {
            i0 = p1;
          } else {
            i0 = 0u;
          }
          i1 = l4;
          i0 ^= i1;
          l4 = i0;
          i0 = p1;
          i1 = 255u;
          i0 &= i1;
          p1 = i0;
          i1 = 1u;
          i0 <<= (i1 & 31);
          l11 = i0;
          i0 = p1;
          i1 = 128u;
          i0 &= i1;
          if (i0) {
            i0 = 195u;
          } else {
            i0 = 0u;
          }
          i1 = l11;
          i0 ^= i1;
          i1 = 255u;
          i0 &= i1;
          p1 = i0;
          i0 = l5;
          i1 = 255u;
          i0 &= i1;
          i1 = 1u;
          i0 >>= (i1 & 31);
          l5 = i0;
          if (i0) {goto L3;}
        i0 = l4;
        i1 = l2;
        i0 ^= i1;
        l2 = i0;
        i0 = l1;
        i1 = 4294967295u;
        i0 += i1;
        p1 = i0;
        i0 = l1;
        i1 = 0u;
        i0 = (u32)((s32)i0 > (s32)i1);
        if (i0) {
          i0 = p1;
          l1 = i0;
          goto L2;
        }
      i0 = l3;
      i1 = l2;
      i32_store8((u64)(i0), i1);
      i0 = l8;
      i1 = 1u;
      i0 += i1;
      l8 = i0;
      i1 = 16u;
      i0 = i0 != i1;
      if (i0) {
        i0 = l12;
        i0 = i32_load8_s((u64)(i0));
        l2 = i0;
        goto L1;
      }
    i0 = l3;
    j0 = i64_load((u64)(i0));
    j1 = l30;
    j0 ^= j1;
    l28 = j0;
    i0 = l9;
    i1 = l18;
    j1 = i64_load((u64)(i1));
    j2 = l31;
    j1 ^= j2;
    l29 = j1;
    i64_store((u64)(i0), j1);
    i0 = l0;
    i1 = 0u;
    j2 = l28;
    i2 = (u32)(j2);
    i3 = 255u;
    i2 &= i3;
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l19;
    i1 = 0u;
    j2 = l28;
    j3 = 8ull;
    j2 >>= (j3 & 63);
    i2 = (u32)(j2);
    i3 = 255u;
    i2 &= i3;
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l20;
    i1 = 0u;
    j2 = l28;
    j3 = 16ull;
    j2 >>= (j3 & 63);
    i2 = (u32)(j2);
    i3 = 255u;
    i2 &= i3;
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l21;
    i1 = 0u;
    j2 = l28;
    j3 = 24ull;
    j2 >>= (j3 & 63);
    i2 = (u32)(j2);
    i3 = 255u;
    i2 &= i3;
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l22;
    i1 = 0u;
    j2 = l28;
    j3 = 32ull;
    j2 >>= (j3 & 63);
    i2 = (u32)(j2);
    i3 = 255u;
    i2 &= i3;
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l23;
    i1 = 0u;
    j2 = l28;
    j3 = 40ull;
    j2 >>= (j3 & 63);
    i2 = (u32)(j2);
    i3 = 255u;
    i2 &= i3;
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l24;
    i1 = 0u;
    j2 = l28;
    j3 = 48ull;
    j2 >>= (j3 & 63);
    i2 = (u32)(j2);
    i3 = 255u;
    i2 &= i3;
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l25;
    i1 = 0u;
    j2 = l28;
    j3 = 56ull;
    j2 >>= (j3 & 63);
    i2 = (u32)(j2);
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l26;
    i1 = 0u;
    j2 = l29;
    i2 = (u32)(j2);
    i3 = 255u;
    i2 &= i3;
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l27;
    i1 = 0u;
    j2 = l29;
    j3 = 8ull;
    j2 >>= (j3 & 63);
    i2 = (u32)(j2);
    i3 = 255u;
    i2 &= i3;
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l13;
    i1 = 0u;
    i2 = l13;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l14;
    i1 = 0u;
    i2 = l14;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l15;
    i1 = 0u;
    i2 = l15;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l16;
    i1 = 0u;
    i2 = l16;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l17;
    i1 = 0u;
    i2 = l17;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l10;
    i1 = 0u;
    i2 = l10;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i2 = 255u;
    i1 &= i2;
    l2 = i1;
    i32_store8((u64)(i0), i1);
    i0 = 0u;
    l8 = i0;
    L8: 
      i0 = 14u;
      l1 = i0;
      L9: 
        i0 = l0;
        i1 = l1;
        i2 = 1u;
        i1 += i2;
        i0 += i1;
        i1 = l0;
        i2 = l1;
        i1 += i2;
        i1 = i32_load8_s((u64)(i1));
        p1 = i1;
        i32_store8((u64)(i0), i1);
        i0 = 0u;
        l4 = i0;
        i0 = l1;
        i1 = 1305u;
        i0 += i1;
        i0 = i32_load8_s((u64)(i0));
        l5 = i0;
        L10: 
          i0 = l5;
          i1 = 1u;
          i0 &= i1;
          if (i0) {
            i0 = p1;
          } else {
            i0 = 0u;
          }
          i1 = l4;
          i0 ^= i1;
          l4 = i0;
          i0 = p1;
          i1 = 255u;
          i0 &= i1;
          p1 = i0;
          i1 = 1u;
          i0 <<= (i1 & 31);
          l11 = i0;
          i0 = p1;
          i1 = 128u;
          i0 &= i1;
          if (i0) {
            i0 = 195u;
          } else {
            i0 = 0u;
          }
          i1 = l11;
          i0 ^= i1;
          i1 = 255u;
          i0 &= i1;
          p1 = i0;
          i0 = l5;
          i1 = 255u;
          i0 &= i1;
          i1 = 1u;
          i0 >>= (i1 & 31);
          l5 = i0;
          if (i0) {goto L10;}
        i0 = l4;
        i1 = l2;
        i0 ^= i1;
        l2 = i0;
        i0 = l1;
        i1 = 4294967295u;
        i0 += i1;
        p1 = i0;
        i0 = l1;
        i1 = 0u;
        i0 = (u32)((s32)i0 > (s32)i1);
        if (i0) {
          i0 = p1;
          l1 = i0;
          goto L9;
        }
      i0 = l0;
      i1 = l2;
      i32_store8((u64)(i0), i1);
      i0 = l8;
      i1 = 1u;
      i0 += i1;
      l8 = i0;
      i1 = 16u;
      i0 = i0 != i1;
      if (i0) {
        i0 = l10;
        i0 = i32_load8_s((u64)(i0));
        l2 = i0;
        goto L8;
      }
    i0 = l0;
    i1 = l0;
    j1 = i64_load((u64)(i1));
    j2 = l32;
    j1 ^= j2;
    l28 = j1;
    i64_store((u64)(i0), j1);
    i0 = l9;
    i1 = l9;
    j1 = i64_load((u64)(i1));
    j2 = l33;
    j1 ^= j2;
    l29 = j1;
    i64_store((u64)(i0), j1);
    i0 = l7;
    i1 = 7u;
    i0 &= i1;
    i0 = !(i0);
    if (i0) {
      i0 = p0;
      i1 = l7;
      i2 = 2u;
      i1 = (u32)((s32)i1 >> (i2 & 31));
      p1 = i1;
      i2 = 4u;
      i1 <<= (i2 & 31);
      i0 += i1;
      j1 = l28;
      i64_store((u64)(i0), j1);
      i0 = p0;
      i1 = p1;
      i2 = 4u;
      i1 <<= (i2 & 31);
      i0 += i1;
      j1 = l29;
      i64_store((u64)(i0 + 8), j1);
      i0 = p0;
      i1 = p1;
      i2 = 1u;
      i1 += i2;
      p1 = i1;
      i2 = 4u;
      i1 <<= (i2 & 31);
      i0 += i1;
      j1 = l30;
      i64_store((u64)(i0), j1);
      i0 = p0;
      i1 = p1;
      i2 = 4u;
      i1 <<= (i2 & 31);
      i0 += i1;
      j1 = l31;
      i64_store((u64)(i0 + 8), j1);
    }
    i0 = l7;
    i1 = 1u;
    i0 += i1;
    l7 = i0;
    i1 = 33u;
    i0 = i0 != i1;
    if (i0) {
      j0 = l31;
      l33 = j0;
      j0 = l30;
      l32 = j0;
      j0 = l28;
      l30 = j0;
      j0 = l29;
      l31 = j0;
      goto L0;
    }
  i0 = l6;
  g4 = i0;
  //FUNC_EPILOGUE;
}

static void _setDecryptKey(u32 p0, u32 p1) {
  //FUNC_PROLOGUE;
  u32 i0, i1;
  i0 = p0;
  i1 = p1;
  f13(i0, i1);
  //FUNC_EPILOGUE;
}

static void _decryptBlock(u32 p0, u32 p1) {
  u32 l0 = 0, l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0, l6 = 0, l7 = 0, 
      l8 = 0, l9 = 0, l10 = 0, l11 = 0, l12 = 0, l13 = 0, l14 = 0, l15 = 0, 
      l16 = 0, l17 = 0, l18 = 0, l19 = 0, l20 = 0, l21 = 0, l22 = 0, l23 = 0, 
      l24 = 0, l25 = 0, l26 = 0;
  u64 l27 = 0, l28 = 0;
  //FUNC_PROLOGUE;
  u32 i0, i1, i2, i3, i4;
  u64 j1, j2;
  i0 = g4;
  l23 = i0;
  i0 = g4;
  i1 = 16u;
  i0 += i1;
  g4 = i0;
  i0 = l23;
  l0 = i0;
  i1 = p0;
  j1 = i64_load((u64)(i1 + 144));
  i2 = p1;
  j2 = i64_load((u64)(i2));
  j1 ^= j2;
  i64_store((u64)(i0), j1);
  i0 = l0;
  i1 = 8u;
  i0 += i1;
  l4 = i0;
  i1 = p0;
  j1 = i64_load((u64)(i1 + 152));
  i2 = p1;
  i3 = 8u;
  i2 += i3;
  l26 = i2;
  j2 = i64_load((u64)(i2));
  j1 ^= j2;
  i64_store((u64)(i0), j1);
  i0 = l0;
  i1 = 15u;
  i0 += i1;
  l3 = i0;
  i0 = l0;
  i1 = 1u;
  i0 += i1;
  l5 = i0;
  i0 = l0;
  i1 = 2u;
  i0 += i1;
  l6 = i0;
  i0 = l0;
  i1 = 3u;
  i0 += i1;
  l7 = i0;
  i0 = l0;
  i1 = 4u;
  i0 += i1;
  l8 = i0;
  i0 = l0;
  i1 = 5u;
  i0 += i1;
  l9 = i0;
  i0 = l0;
  i1 = 6u;
  i0 += i1;
  l10 = i0;
  i0 = l0;
  i1 = 7u;
  i0 += i1;
  l11 = i0;
  i0 = l0;
  i1 = 8u;
  i0 += i1;
  l12 = i0;
  i0 = l0;
  i1 = 9u;
  i0 += i1;
  l13 = i0;
  i0 = l0;
  i1 = 10u;
  i0 += i1;
  l14 = i0;
  i0 = l0;
  i1 = 11u;
  i0 += i1;
  l15 = i0;
  i0 = l0;
  i1 = 12u;
  i0 += i1;
  l16 = i0;
  i0 = l0;
  i1 = 13u;
  i0 += i1;
  l17 = i0;
  i0 = l0;
  i1 = 14u;
  i0 += i1;
  l18 = i0;
  i0 = 8u;
  l2 = i0;
  L0: 
    i0 = 0u;
    l24 = i0;
    L1: 
      i0 = 0u;
      l1 = i0;
      i0 = l0;
      i0 = i32_load8_s((u64)(i0));
      l19 = i0;
      L2: 
        i0 = l0;
        i1 = l1;
        i0 += i1;
        i1 = l0;
        i2 = l1;
        i3 = 1u;
        i2 += i3;
        l25 = i2;
        i1 += i2;
        i1 = i32_load8_s((u64)(i1));
        l20 = i1;
        i32_store8((u64)(i0), i1);
        i0 = 0u;
        l21 = i0;
        i0 = l1;
        i1 = 1305u;
        i0 += i1;
        i0 = i32_load8_s((u64)(i0));
        l22 = i0;
        i0 = l20;
        l1 = i0;
        L3: 
          i0 = l22;
          i1 = 1u;
          i0 &= i1;
          if (i0) {
            i0 = l1;
          } else {
            i0 = 0u;
          }
          i1 = l21;
          i0 ^= i1;
          l21 = i0;
          i0 = l1;
          i1 = 255u;
          i0 &= i1;
          l1 = i0;
          i1 = 1u;
          i0 <<= (i1 & 31);
          l20 = i0;
          i0 = l1;
          i1 = 128u;
          i0 &= i1;
          if (i0) {
            i0 = 195u;
          } else {
            i0 = 0u;
          }
          i1 = l20;
          i0 ^= i1;
          i1 = 255u;
          i0 &= i1;
          l1 = i0;
          i0 = l22;
          i1 = 255u;
          i0 &= i1;
          i1 = 1u;
          i0 >>= (i1 & 31);
          l22 = i0;
          if (i0) {goto L3;}
        i0 = l21;
        i1 = l19;
        i0 ^= i1;
        l19 = i0;
        i0 = l25;
        i1 = 15u;
        i0 = i0 != i1;
        if (i0) {
          i0 = l25;
          l1 = i0;
          goto L2;
        }
      i0 = l3;
      i1 = l19;
      i32_store8((u64)(i0), i1);
      i0 = l24;
      i1 = 1u;
      i0 += i1;
      l24 = i0;
      i1 = 16u;
      i0 = i0 != i1;
      if (i0) {goto L1;}
    i0 = l0;
    i1 = 0u;
    i2 = l0;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l5;
    i1 = 0u;
    i2 = l5;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l6;
    i1 = 0u;
    i2 = l6;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l7;
    i1 = 0u;
    i2 = l7;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l8;
    i1 = 0u;
    i2 = l8;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l9;
    i1 = 0u;
    i2 = l9;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l10;
    i1 = 0u;
    i2 = l10;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l11;
    i1 = 0u;
    i2 = l11;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l12;
    i1 = 0u;
    i2 = l12;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l13;
    i1 = 0u;
    i2 = l13;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l14;
    i1 = 0u;
    i2 = l14;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l15;
    i1 = 0u;
    i2 = l15;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l16;
    i1 = 0u;
    i2 = l16;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l17;
    i1 = 0u;
    i2 = l17;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l18;
    i1 = 0u;
    i2 = l18;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l3;
    i1 = 0u;
    i2 = l3;
    i2 = i32_load8_u((u64)(i2));
    i3 = 1024u;
    i2 += i3;
    i2 = i32_load8_u((u64)(i2));
    i1 = d(i2);
    i32_store8((u64)(i0), i1);
    i0 = l0;
    i1 = l0;
    j1 = i64_load((u64)(i1));
    i2 = p0;
    i3 = l2;
    i4 = 4u;
    i3 <<= (i4 & 31);
    i2 += i3;
    j2 = i64_load((u64)(i2));
    j1 ^= j2;
    l27 = j1;
    i64_store((u64)(i0), j1);
    i0 = l4;
    i1 = l4;
    j1 = i64_load((u64)(i1));
    i2 = p0;
    i3 = l2;
    i4 = 4u;
    i3 <<= (i4 & 31);
    i2 += i3;
    j2 = i64_load((u64)(i2 + 8));
    j1 ^= j2;
    l28 = j1;
    i64_store((u64)(i0), j1);
    i0 = l2;
    i1 = 4294967295u;
    i0 += i1;
    l1 = i0;
    i0 = l2;
    i1 = 0u;
    i0 = (u32)((s32)i0 > (s32)i1);
    if (i0) {
      i0 = l1;
      l2 = i0;
      goto L0;
    }
  i0 = l0;
  j1 = l27;
  i1 = (u32)(j1);
  i2 = 255u;
  i1 &= i2;
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l5;
  j1 = l27;
  j2 = 8ull;
  j1 >>= (j2 & 63);
  i1 = (u32)(j1);
  i2 = 255u;
  i1 &= i2;
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l6;
  j1 = l27;
  j2 = 16ull;
  j1 >>= (j2 & 63);
  i1 = (u32)(j1);
  i2 = 255u;
  i1 &= i2;
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l7;
  j1 = l27;
  j2 = 24ull;
  j1 >>= (j2 & 63);
  i1 = (u32)(j1);
  i2 = 255u;
  i1 &= i2;
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l8;
  j1 = l27;
  j2 = 32ull;
  j1 >>= (j2 & 63);
  i1 = (u32)(j1);
  i2 = 255u;
  i1 &= i2;
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l9;
  j1 = l27;
  j2 = 40ull;
  j1 >>= (j2 & 63);
  i1 = (u32)(j1);
  i2 = 255u;
  i1 &= i2;
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l10;
  j1 = l27;
  j2 = 48ull;
  j1 >>= (j2 & 63);
  i1 = (u32)(j1);
  i2 = 255u;
  i1 &= i2;
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l11;
  j1 = l27;
  j2 = 56ull;
  j1 >>= (j2 & 63);
  i1 = (u32)(j1);
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l12;
  j1 = l28;
  i1 = (u32)(j1);
  i2 = 255u;
  i1 &= i2;
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l13;
  j1 = l28;
  j2 = 8ull;
  j1 >>= (j2 & 63);
  i1 = (u32)(j1);
  i2 = 255u;
  i1 &= i2;
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l14;
  j1 = l28;
  j2 = 16ull;
  j1 >>= (j2 & 63);
  i1 = (u32)(j1);
  i2 = 255u;
  i1 &= i2;
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l15;
  j1 = l28;
  j2 = 24ull;
  j1 >>= (j2 & 63);
  i1 = (u32)(j1);
  i2 = 255u;
  i1 &= i2;
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l16;
  j1 = l28;
  j2 = 32ull;
  j1 >>= (j2 & 63);
  i1 = (u32)(j1);
  i2 = 255u;
  i1 &= i2;
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l17;
  j1 = l28;
  j2 = 40ull;
  j1 >>= (j2 & 63);
  i1 = (u32)(j1);
  i2 = 255u;
  i1 &= i2;
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l18;
  j1 = l28;
  j2 = 48ull;
  j1 >>= (j2 & 63);
  i1 = (u32)(j1);
  i2 = 255u;
  i1 &= i2;
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = l3;
  j1 = l28;
  j2 = 56ull;
  j1 >>= (j2 & 63);
  i1 = (u32)(j1);
  i2 = 1024u;
  i1 += i2;
  i1 = i32_load8_s((u64)(i1));
  i32_store8((u64)(i0), i1);
  i0 = p1;
  i1 = l0;
  j1 = i64_load((u64)(i1));
  i64_store((u64)(i0), j1);
  i0 = l26;
  i1 = l4;
  j1 = i64_load((u64)(i1));
  i64_store((u64)(i0), j1);
  i0 = l23;
  g4 = i0;
  //FUNC_EPILOGUE;
}

static u32 __attribute__ ((noinline)) f16(u32 p0, u32 p1, u32 p2, u32 p3) {
  u32 l0 = 0, l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0;
  u64 l6 = 0, l7 = 0, l8 = 0, l9 = 0, l10 = 0, l11 = 0;
  //FUNC_PROLOGUE;
  u32 i0, i1, i2;
  u64 j0, j1, j2, j3;
  i0 = p3;
  i1 = 15u;
  i0 &= i1;
  if (i0) {
    i0 = 4294967295u;
    goto Bfunc;
  }
  i0 = p3;
  i1 = 16u;
  i0 = I32_DIV_S(i0, i1);
  l3 = i0;
  i0 = p3;
  i1 = 15u;
  i0 = (u32)((s32)i0 <= (s32)i1);
  if (i0) {
    i0 = 0u;
    goto Bfunc;
  }
  i0 = 0u;
  p3 = i0;
  L2: 
    i0 = p0;
    i0 = i32_load((u64)(i0));
    l4 = i0;
    i0 = 32u;
    l0 = i0;
    i0 = p1;
    i1 = p3;
    i2 = 4u;
    i1 <<= (i2 & 31);
    l5 = i1;
    i0 += i1;
    l1 = i0;
    i1 = 8u;
    i0 += i1;
    l2 = i0;
    i0 = i32_load8_u((u64)(i0 + 6));
    j0 = (u64)(i0);
    j1 = 48ull;
    j0 <<= (j1 & 63);
    i1 = l2;
    i1 = i32_load8_u((u64)(i1 + 7));
    j1 = (u64)(i1);
    j2 = 56ull;
    j1 <<= (j2 & 63);
    j0 |= j1;
    i1 = l2;
    i1 = i32_load8_u((u64)(i1 + 5));
    j1 = (u64)(i1);
    j2 = 40ull;
    j1 <<= (j2 & 63);
    j0 |= j1;
    i1 = l2;
    i1 = i32_load8_u((u64)(i1 + 4));
    j1 = (u64)(i1);
    j2 = 32ull;
    j1 <<= (j2 & 63);
    j0 |= j1;
    i1 = l2;
    i1 = i32_load8_u((u64)(i1 + 3));
    j1 = (u64)(i1);
    j2 = 24ull;
    j1 <<= (j2 & 63);
    j0 |= j1;
    i1 = l2;
    i1 = i32_load8_u((u64)(i1 + 2));
    j1 = (u64)(i1);
    j2 = 16ull;
    j1 <<= (j2 & 63);
    j0 |= j1;
    i1 = l2;
    i1 = i32_load8_u((u64)(i1 + 1));
    j1 = (u64)(i1);
    j2 = 8ull;
    j1 <<= (j2 & 63);
    j0 |= j1;
    i1 = l2;
    i1 = i32_load8_u((u64)(i1));
    j1 = (u64)(i1);
    j0 |= j1;
    l8 = j0;
    i0 = l1;
    i0 = i32_load8_u((u64)(i0 + 6));
    j0 = (u64)(i0);
    j1 = 48ull;
    j0 <<= (j1 & 63);
    i1 = l1;
    i1 = i32_load8_u((u64)(i1 + 7));
    j1 = (u64)(i1);
    j2 = 56ull;
    j1 <<= (j2 & 63);
    j0 |= j1;
    i1 = l1;
    i1 = i32_load8_u((u64)(i1 + 5));
    j1 = (u64)(i1);
    j2 = 40ull;
    j1 <<= (j2 & 63);
    j0 |= j1;
    i1 = l1;
    i1 = i32_load8_u((u64)(i1 + 4));
    j1 = (u64)(i1);
    j2 = 32ull;
    j1 <<= (j2 & 63);
    j0 |= j1;
    i1 = l1;
    i1 = i32_load8_u((u64)(i1 + 3));
    j1 = (u64)(i1);
    j2 = 24ull;
    j1 <<= (j2 & 63);
    j0 |= j1;
    i1 = l1;
    i1 = i32_load8_u((u64)(i1 + 2));
    j1 = (u64)(i1);
    j2 = 16ull;
    j1 <<= (j2 & 63);
    j0 |= j1;
    i1 = l1;
    i1 = i32_load8_u((u64)(i1 + 1));
    j1 = (u64)(i1);
    j2 = 8ull;
    j1 <<= (j2 & 63);
    j0 |= j1;
    i1 = l1;
    i1 = i32_load8_u((u64)(i1));
    j1 = (u64)(i1);
    j0 |= j1;
    l9 = j0;
    L3: 
      i0 = l4;
      i1 = l0;
      i2 = 4294967295u;
      i1 += i2;
      l1 = i1;
      i2 = 3u;
      i1 <<= (i2 & 31);
      i0 += i1;
      j0 = i64_load((u64)(i0));
      j1 = l8;
      j0 ^= j1;
      j1 = l8;
      j2 = l9;
      j1 ^= j2;
      l7 = j1;
      j2 = 3ull;
      j1 >>= (j2 & 63);
      l11 = j1;
      j2 = l7;
      j3 = 61ull;
      j2 <<= (j3 & 63);
      j1 |= j2;
      l9 = j1;
      j0 -= j1;
      l6 = j0;
      j1 = 56ull;
      j0 >>= (j1 & 63);
      l10 = j0;
      j0 = l6;
      j1 = 8ull;
      j0 <<= (j1 & 63);
      j1 = l10;
      j0 |= j1;
      l8 = j0;
      i0 = l0;
      i1 = 1u;
      i0 = (u32)((s32)i0 > (s32)i1);
      if (i0) {
        i0 = l1;
        l0 = i0;
        goto L3;
      }
    i0 = p2;
    i1 = l5;
    i0 += i1;
    l0 = i0;
    j1 = l11;
    i64_store8((u64)(i0), j1);
    i0 = l0;
    j1 = l7;
    j2 = 11ull;
    j1 >>= (j2 & 63);
    i64_store8((u64)(i0 + 1), j1);
    i0 = l0;
    j1 = l7;
    j2 = 19ull;
    j1 >>= (j2 & 63);
    i64_store8((u64)(i0 + 2), j1);
    i0 = l0;
    j1 = l7;
    j2 = 27ull;
    j1 >>= (j2 & 63);
    i64_store8((u64)(i0 + 3), j1);
    i0 = l0;
    j1 = l7;
    j2 = 35ull;
    j1 >>= (j2 & 63);
    i64_store8((u64)(i0 + 4), j1);
    i0 = l0;
    j1 = l7;
    j2 = 43ull;
    j1 >>= (j2 & 63);
    i64_store8((u64)(i0 + 5), j1);
    i0 = l0;
    j1 = l7;
    j2 = 51ull;
    j1 >>= (j2 & 63);
    i64_store8((u64)(i0 + 6), j1);
    i0 = l0;
    j1 = l9;
    j2 = 56ull;
    j1 >>= (j2 & 63);
    i64_store8((u64)(i0 + 7), j1);
    i0 = l0;
    i1 = 8u;
    i0 += i1;
    l0 = i0;
    j1 = l10;
    i64_store8((u64)(i0), j1);
    i0 = l0;
    j1 = l6;
    i64_store8((u64)(i0 + 1), j1);
    i0 = l0;
    j1 = l6;
    j2 = 8ull;
    j1 >>= (j2 & 63);
    i64_store8((u64)(i0 + 2), j1);
    i0 = l0;
    j1 = l6;
    j2 = 16ull;
    j1 >>= (j2 & 63);
    i64_store8((u64)(i0 + 3), j1);
    i0 = l0;
    j1 = l6;
    j2 = 24ull;
    j1 >>= (j2 & 63);
    i64_store8((u64)(i0 + 4), j1);
    i0 = l0;
    j1 = l6;
    j2 = 32ull;
    j1 >>= (j2 & 63);
    i64_store8((u64)(i0 + 5), j1);
    i0 = l0;
    j1 = l6;
    j2 = 40ull;
    j1 >>= (j2 & 63);
    i64_store8((u64)(i0 + 6), j1);
    i0 = l0;
    j1 = l6;
    j2 = 48ull;
    j1 >>= (j2 & 63);
    i64_store8((u64)(i0 + 7), j1);
    i0 = p3;
    i1 = 1u;
    i0 += i1;
    p3 = i0;
    i1 = l3;
    i0 = i0 != i1;
    if (i0) {goto L2;}
    i0 = 0u;
    p0 = i0;
  i0 = p0;
  Bfunc:;
  //FUNC_EPILOGUE;
  return i0;
}

static u32 __attribute__ ((noinline)) f17(u32 p0) {
  u32 l0 = 0, l1 = 0, l2 = 0;
  u64 l3 = 0, l4 = 0;
  //FUNC_PROLOGUE;
  u32 i0, i1, i2;
  u64 j0, j1, j2, j3, j4;
  i0 = p0;
  i0 = !(i0);
  if (i0) {
    i0 = 0u;
    goto Bfunc;
  }
  i0 = 1u;
  i1 = 4u;
  i0 = f21(i0, i1);
  l2 = i0;
  i0 = !(i0);
  if (i0) {
    i0 = 0u;
    goto Bfunc;
  }
  i0 = l2;
  i1 = 256u;
  i1 = _malloc(i1);
  l0 = i1;
  i32_store((u64)(i0), i1);
  i0 = l0;
  i0 = !(i0);
  if (i0) {
    i0 = 0u;
    goto Bfunc;
  }
  i0 = p0;
  i0 = i32_load8_u((u64)(i0 + 14));
  j0 = (u64)(i0);
  j1 = 48ull;
  j0 <<= (j1 & 63);
  i1 = p0;
  i1 = i32_load8_u((u64)(i1 + 15));
  j1 = (u64)(i1);
  j2 = 56ull;
  j1 <<= (j2 & 63);
  j0 |= j1;
  i1 = p0;
  i1 = i32_load8_u((u64)(i1 + 13));
  j1 = (u64)(i1);
  j2 = 40ull;
  j1 <<= (j2 & 63);
  j0 |= j1;
  i1 = p0;
  i1 = i32_load8_u((u64)(i1 + 12));
  j1 = (u64)(i1);
  j2 = 32ull;
  j1 <<= (j2 & 63);
  j0 |= j1;
  i1 = p0;
  i1 = i32_load8_u((u64)(i1 + 11));
  j1 = (u64)(i1);
  j2 = 24ull;
  j1 <<= (j2 & 63);
  j0 |= j1;
  i1 = p0;
  i1 = i32_load8_u((u64)(i1 + 10));
  j1 = (u64)(i1);
  j2 = 16ull;
  j1 <<= (j2 & 63);
  j0 |= j1;
  i1 = p0;
  i1 = i32_load8_u((u64)(i1 + 9));
  j1 = (u64)(i1);
  j2 = 8ull;
  j1 <<= (j2 & 63);
  j0 |= j1;
  i1 = p0;
  i1 = i32_load8_u((u64)(i1 + 8));
  j1 = (u64)(i1);
  j0 |= j1;
  l4 = j0;
  i0 = l0;
  i1 = p0;
  i1 = i32_load8_u((u64)(i1 + 6));
  j1 = (u64)(i1);
  j2 = 48ull;
  j1 <<= (j2 & 63);
  i2 = p0;
  i2 = i32_load8_u((u64)(i2 + 7));
  j2 = (u64)(i2);
  j3 = 56ull;
  j2 <<= (j3 & 63);
  j1 |= j2;
  i2 = p0;
  i2 = i32_load8_u((u64)(i2 + 5));
  j2 = (u64)(i2);
  j3 = 40ull;
  j2 <<= (j3 & 63);
  j1 |= j2;
  i2 = p0;
  i2 = i32_load8_u((u64)(i2 + 4));
  j2 = (u64)(i2);
  j3 = 32ull;
  j2 <<= (j3 & 63);
  j1 |= j2;
  i2 = p0;
  i2 = i32_load8_u((u64)(i2 + 3));
  j2 = (u64)(i2);
  j3 = 24ull;
  j2 <<= (j3 & 63);
  j1 |= j2;
  i2 = p0;
  i2 = i32_load8_u((u64)(i2 + 2));
  j2 = (u64)(i2);
  j3 = 16ull;
  j2 <<= (j3 & 63);
  j1 |= j2;
  i2 = p0;
  i2 = i32_load8_u((u64)(i2 + 1));
  j2 = (u64)(i2);
  j3 = 8ull;
  j2 <<= (j3 & 63);
  j1 |= j2;
  i2 = p0;
  i2 = i32_load8_u((u64)(i2));
  j2 = (u64)(i2);
  j1 |= j2;
  l3 = j1;
  i64_store((u64)(i0), j1);
  L3: 
    i0 = l0;
    i1 = l1;
    i2 = 1u;
    i1 += i2;
    p0 = i1;
    i2 = 3u;
    i1 <<= (i2 & 31);
    i0 += i1;
    j1 = l4;
    j2 = 8ull;
    j1 >>= (j2 & 63);
    j2 = l4;
    j3 = 56ull;
    j2 <<= (j3 & 63);
    j1 |= j2;
    j2 = l3;
    j1 += j2;
    i2 = l1;
    j2 = (u64)(s64)(s32)(i2);
    j1 ^= j2;
    l4 = j1;
    j2 = l3;
    j3 = 3ull;
    j2 <<= (j3 & 63);
    j3 = l3;
    j4 = 61ull;
    j3 >>= (j4 & 63);
    j2 |= j3;
    j1 ^= j2;
    l3 = j1;
    i64_store((u64)(i0), j1);
    i0 = p0;
    i1 = 31u;
    i0 = i0 != i1;
    if (i0) {
      i0 = p0;
      l1 = i0;
      goto L3;
    }
  i0 = l2;
  Bfunc:;
  //FUNC_EPILOGUE;
  return i0;
}

static __attribute__ ((noinline)) u32 _getFlag(u32 p0, u32 p1) {
  u32 l0 = 0, l1 = 0, l2 = 0;
  //FUNC_PROLOGUE;
  u32 i0, i1, i2, i3;
  u64 j1;
  i0 = g4;
  l1 = i0;
  i0 = g4;
  i1 = 112u;
  i0 += i1;
  g4 = i0;
  i0 = l1;
  i1 = 64u;
  i0 += i1;
  l2 = i0;
  i1 = 1321u;
  j1 = i64_load((u64)(i1));
  i64_store((u64)(i0), j1);
  i0 = l2;
  i1 = 1329u;
  j1 = i64_load((u64)(i1));
  i64_store((u64)(i0 + 8), j1);
  i0 = l2;
  i1 = 1337u;
  j1 = i64_load((u64)(i1));
  i64_store((u64)(i0 + 16), j1);
  i0 = l2;
  i1 = 1345u;
  j1 = i64_load((u64)(i1));
  i64_store((u64)(i0 + 24), j1);
  i0 = l2;
  i1 = 1353u;
  j1 = i64_load((u64)(i1));
  i64_store((u64)(i0 + 32), j1);
  i0 = l2;
  i1 = 1361u;
  j1 = i64_load((u64)(i1));
  i64_store((u64)(i0 + 40), j1);
  i0 = l1;
  l0 = i0;
  i1 = 1369u;
  j1 = i64_load((u64)(i1));
  i64_store((u64)(i0), j1);
  i0 = l0;
  i1 = 1377u;
  j1 = i64_load((u64)(i1));
  i64_store((u64)(i0 + 8), j1);
  i0 = p0;
  i1 = 89594904u;
  i0 = i0 != i1;
  if (i0) {
    i0 = l1;
    g4 = i0;
    i0 = 0u;
    goto Bfunc;
  }
  i0 = l0;
  i0 = f17(i0);
  p0 = i0;
  i0 = !(i0);
  if (i0) {
    i0 = l1;
    g4 = i0;
    i0 = 0u;
    goto Bfunc;
  }
  i0 = p0;
  i1 = l2;
  i2 = l1;
  i3 = 16u;
  i2 += i3;
  l0 = i2;
  i3 = 48u;
  i0 = f16(i0, i1, i2, i3);
  i0 = p1;
  i1 = l0;
  j1 = i64_load((u64)(i1));
  i64_store((u64)(i0), j1);
  i0 = p1;
  i1 = l0;
  j1 = i64_load((u64)(i1 + 8));
  i64_store((u64)(i0 + 8), j1);
  i0 = p1;
  i1 = l0;
  j1 = i64_load((u64)(i1 + 16));
  i64_store((u64)(i0 + 16), j1);
  i0 = p1;
  i1 = l0;
  j1 = i64_load((u64)(i1 + 24));
  i64_store((u64)(i0 + 24), j1);
  i0 = p1;
  i1 = l0;
  j1 = i64_load((u64)(i1 + 32));
  i64_store((u64)(i0 + 32), j1);
  i0 = p1;
  i1 = l0;
  i1 = i32_load((u64)(i1 + 40));
  i32_store((u64)(i0 + 40), i1);
  i0 = p0;
  _free(i0);
  i0 = l1;
  g4 = i0;
  i0 = 1u;
  Bfunc:;
  //FUNC_EPILOGUE;
  return i0;
}

static u32 __attribute__ ((noinline)) _malloc(u32 p0) {
  u32 l0 = 0, l1 = 0, l2 = 0, l3 = 0, l4 = 0, l5 = 0, l6 = 0, l7 = 0, 
      l8 = 0, l9 = 0, l10 = 0, l11 = 0;
  //FUNC_PROLOGUE;
  uint32_t ret = (sizeof(main_memory) - sizeof(main_memory.heap)) + malloc_ptr;
  //printf("malloc(0x%x) = 0x%x\n", p0, ret);
  malloc_ptr += p0;
  return ret;
}

static void __attribute__ ((noinline)) _free(u32 p0) {
}

static u32 __attribute__ ((noinline)) f21(u32 p0, u32 p1) {
  u32 l0 = 0;
  //FUNC_PROLOGUE;
  u32 i0, i1, i2;
  i0 = p0;
  if (i0) {
    i0 = p1;
    i1 = p0;
    i0 *= i1;
    l0 = i0;
    i0 = p1;
    i1 = p0;
    i0 |= i1;
    i1 = 65535u;
    i0 = i0 > i1;
    if (i0) {
      i0 = l0;
      i1 = p0;
      i0 = DIV_U(i0, i1);
      i1 = p1;
      i0 = i0 != i1;
      if (i0) {
        i0 = 4294967295u;
        l0 = i0;
      }
    }
  }
  i0 = l0;
  i0 = _malloc(i0);
  p0 = i0;
  i0 = !(i0);
  if (i0) {
    i0 = p0;
    goto Bfunc;
  }
  i0 = p0;
  i1 = 4294967292u;
  i0 += i1;
  i0 = i32_load((u64)(i0));
  i1 = 3u;
  i0 &= i1;
  i0 = !(i0);
  if (i0) {
    i0 = p0;
    goto Bfunc;
  }
  i0 = p0;
  i1 = 0u;
  i2 = l0;
  i0 = _memset(i0, i1, i2);
  i0 = p0;
  Bfunc:;
  //FUNC_EPILOGUE;
  return i0;
}

static u32 ___errno_location(void) {
  //FUNC_PROLOGUE;
  u32 i0;
  i0 = 1884u;
  //FUNC_EPILOGUE;
  return i0;
}

static void runPostSets(void) {
  //FUNC_PROLOGUE;
  //FUNC_EPILOGUE;
}

static u32 _memcpy(u32 p0, u32 p1, u32 p2) {
  u32 l0 = 0, l1 = 0, l2 = 0;
  //FUNC_PROLOGUE;
  u32 i0, i1, i2;
  i0 = p2;
  i1 = 8192u;
  i0 = p0;
  l1 = i0;
  i0 = p0;
  i1 = p2;
  i0 += i1;
  l0 = i0;
  i0 = p0;
  i1 = 3u;
  i0 &= i1;
  i1 = p1;
  i2 = 3u;
  i1 &= i2;
  i0 = i0 == i1;
  if (i0) {
    L2: 
      i0 = p0;
      i1 = 3u;
      i0 &= i1;
      if (i0) {
        i0 = p2;
        i0 = !(i0);
        if (i0) {
          i0 = l1;
          goto Bfunc;
        }
        i0 = p0;
        i1 = p1;
        i1 = i32_load8_s((u64)(i1));
        i32_store8((u64)(i0), i1);
        i0 = p0;
        i1 = 1u;
        i0 += i1;
        p0 = i0;
        i0 = p1;
        i1 = 1u;
        i0 += i1;
        p1 = i0;
        i0 = p2;
        i1 = 1u;
        i0 -= i1;
        p2 = i0;
        goto L2;
      }
    i0 = l0;
    i1 = 4294967292u;
    i0 &= i1;
    p2 = i0;
    i1 = 64u;
    i0 -= i1;
    l2 = i0;
    L5: 
      i0 = p0;
      i1 = l2;
      i0 = (u32)((s32)i0 <= (s32)i1);
      if (i0) {
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1));
        i32_store((u64)(i0), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 4));
        i32_store((u64)(i0 + 4), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 8));
        i32_store((u64)(i0 + 8), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 12));
        i32_store((u64)(i0 + 12), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 16));
        i32_store((u64)(i0 + 16), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 20));
        i32_store((u64)(i0 + 20), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 24));
        i32_store((u64)(i0 + 24), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 28));
        i32_store((u64)(i0 + 28), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 32));
        i32_store((u64)(i0 + 32), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 36));
        i32_store((u64)(i0 + 36), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 40));
        i32_store((u64)(i0 + 40), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 44));
        i32_store((u64)(i0 + 44), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 48));
        i32_store((u64)(i0 + 48), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 52));
        i32_store((u64)(i0 + 52), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 56));
        i32_store((u64)(i0 + 56), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1 + 60));
        i32_store((u64)(i0 + 60), i1);
        i0 = p0;
        i1 = 64u;
        i0 += i1;
        p0 = i0;
        i0 = p1;
        i1 = 64u;
        i0 += i1;
        p1 = i0;
        goto L5;
      }
    L7: 
      i0 = p0;
      i1 = p2;
      i0 = (u32)((s32)i0 < (s32)i1);
      if (i0) {
        i0 = p0;
        i1 = p1;
        i1 = i32_load((u64)(i1));
        i32_store((u64)(i0), i1);
        i0 = p0;
        i1 = 4u;
        i0 += i1;
        p0 = i0;
        i0 = p1;
        i1 = 4u;
        i0 += i1;
        p1 = i0;
        goto L7;
      }
  } else {
    i0 = l0;
    i1 = 4u;
    i0 -= i1;
    p2 = i0;
    L9: 
      i0 = p0;
      i1 = p2;
      i0 = (u32)((s32)i0 < (s32)i1);
      if (i0) {
        i0 = p0;
        i1 = p1;
        i1 = i32_load8_s((u64)(i1));
        i32_store8((u64)(i0), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load8_s((u64)(i1 + 1));
        i32_store8((u64)(i0 + 1), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load8_s((u64)(i1 + 2));
        i32_store8((u64)(i0 + 2), i1);
        i0 = p0;
        i1 = p1;
        i1 = i32_load8_s((u64)(i1 + 3));
        i32_store8((u64)(i0 + 3), i1);
        i0 = p0;
        i1 = 4u;
        i0 += i1;
        p0 = i0;
        i0 = p1;
        i1 = 4u;
        i0 += i1;
        p1 = i0;
        goto L9;
      }
  }
  L11: 
    i0 = p0;
    i1 = l0;
    i0 = (u32)((s32)i0 < (s32)i1);
    if (i0) {
      i0 = p0;
      i1 = p1;
      i1 = i32_load8_s((u64)(i1));
      i32_store8((u64)(i0), i1);
      i0 = p0;
      i1 = 1u;
      i0 += i1;
      p0 = i0;
      i0 = p1;
      i1 = 1u;
      i0 += i1;
      p1 = i0;
      goto L11;
    }
  i0 = l1;
  Bfunc:;
  //FUNC_EPILOGUE;
  return i0;
}

static u32 _memset(u32 p0, u32 p1, u32 p2) {
  u32 l0 = 0, l1 = 0, l2 = 0, l3 = 0;
  //FUNC_PROLOGUE;
  u32 i0, i1, i2;
  i0 = p0;
  i1 = p2;
  i0 += i1;
  l1 = i0;
  i0 = p1;
  i1 = 255u;
  i0 &= i1;
  p1 = i0;
  i0 = p2;
  i1 = 67u;
  i0 = (u32)((s32)i0 >= (s32)i1);
  if (i0) {
    L1: 
      i0 = p0;
      i1 = 3u;
      i0 &= i1;
      if (i0) {
        i0 = p0;
        i1 = p1;
        i32_store8((u64)(i0), i1);
        i0 = p0;
        i1 = 1u;
        i0 += i1;
        p0 = i0;
        goto L1;
      }
    i0 = l1;
    i1 = 4294967292u;
    i0 &= i1;
    l2 = i0;
    i1 = 64u;
    i0 -= i1;
    l3 = i0;
    i0 = p1;
    i1 = p1;
    i2 = 8u;
    i1 <<= (i2 & 31);
    i0 |= i1;
    i1 = p1;
    i2 = 16u;
    i1 <<= (i2 & 31);
    i0 |= i1;
    i1 = p1;
    i2 = 24u;
    i1 <<= (i2 & 31);
    i0 |= i1;
    l0 = i0;
    L3: 
      i0 = p0;
      i1 = l3;
      i0 = (u32)((s32)i0 <= (s32)i1);
      if (i0) {
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 4), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 8), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 12), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 16), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 20), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 24), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 28), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 32), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 36), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 40), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 44), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 48), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 52), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 56), i1);
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0 + 60), i1);
        i0 = p0;
        i1 = 64u;
        i0 += i1;
        p0 = i0;
        goto L3;
      }
    L5: 
      i0 = p0;
      i1 = l2;
      i0 = (u32)((s32)i0 < (s32)i1);
      if (i0) {
        i0 = p0;
        i1 = l0;
        i32_store((u64)(i0), i1);
        i0 = p0;
        i1 = 4u;
        i0 += i1;
        p0 = i0;
        goto L5;
      }
  }
  L7: 
    i0 = p0;
    i1 = l1;
    i0 = (u32)((s32)i0 < (s32)i1);
    if (i0) {
      i0 = p0;
      i1 = p1;
      i32_store8((u64)(i0), i1);
      i0 = p0;
      i1 = 1u;
      i0 += i1;
      p0 = i0;
      goto L7;
    }
  i0 = l1;
  i1 = p2;
  i0 -= i1;
  //FUNC_EPILOGUE;
  return i0;
}

static u32 _sbrk(u32 p0) {
  u32 l0 = 0, l1 = 0;
  //FUNC_PROLOGUE;
  u32 i0, i1, i2;
  i0 = g3;
  i0 = i32_load((u64)(i0));
  l1 = i0;
  i1 = p0;
  i2 = 15u;
  i1 += i2;
  i2 = 4294967280u;
  i1 &= i2;
  p0 = i1;
  i0 += i1;
  l0 = i0;
  i0 = p0;
  i1 = 0u;
  i0 = (u32)((s32)i0 > (s32)i1);
  i1 = l0;
  i2 = l1;
  i1 = (u32)((s32)i1 < (s32)i2);
  i0 &= i1;
  i1 = l0;
  i2 = 0u;
  i1 = (u32)((s32)i1 < (s32)i2);
  i0 |= i1;
  if (i0) {
    goto Bfunc;
  }
  i0 = g3;
  i1 = l0;
  i32_store((u64)(i0), i1);
  i0 = l0;
  i1 = 4294967295u;
  i0 = (u32)((s32)i0 > (s32)i1);
  if (i0) {
    i0 = 1;
    i0 = !(i0);
  }
  i0 = l1;
  Bfunc:;
  //FUNC_EPILOGUE;
  return i0;
}

static const u8 data_segment_data_0[] = {
  0xdc, 0x63, 0x7a, 0x21, 0x58, 0x1f, 0x76, 0x5d, 0xd4, 0xdb, 0x72, 0x99, 
  0x50, 0x97, 0x6e, 0xd5, 0xcc, 0x53, 0x6a, 0x11, 0x48, 0x0f, 0x66, 0x4d, 
  0xc4, 0xcb, 0x62, 0x89, 0x40, 0x87, 0x5e, 0xc5, 0xbc, 0x43, 0x5a, 0x01, 
  0x38, 0xff, 0x56, 0x3d, 0xb4, 0xbb, 0x52, 0x79, 0x30, 0x77, 0x4e, 0xb5, 
  0xac, 0x33, 0x4a, 0xf1, 0x28, 0xef, 0x46, 0x2d, 0xa4, 0xab, 0x42, 0x69, 
  0x20, 0x67, 0x3e, 0xa5, 0x9c, 0x23, 0x3a, 0xe1, 0x18, 0xdf, 0x36, 0x1d, 
  0x94, 0x9b, 0x32, 0x59, 0x10, 0x57, 0x2e, 0x95, 0x8c, 0x13, 0x2a, 0xd1, 
  0x08, 0xcf, 0x26, 0x0d, 0x84, 0x8b, 0x22, 0x49, 0x00, 0x47, 0x1e, 0x85, 
  0x7c, 0x03, 0x1a, 0xc1, 0xf8, 0xbf, 0x16, 0xfd, 0x74, 0x7b, 0x12, 0x39, 
  0xf0, 0x37, 0x0e, 0x75, 0x6c, 0xf3, 0x0a, 0xb1, 0xe8, 0xaf, 0x06, 0xed, 
  0x64, 0x6b, 0x02, 0x29, 0xe0, 0x27, 0xfe, 0x65, 0x5c, 0xe3, 0xfa, 0xa1, 
  0xd8, 0x9f, 0xf6, 0xdd, 0x54, 0x5b, 0xf2, 0x19, 0xd0, 0x17, 0xee, 0x55, 
  0x4c, 0xd3, 0xea, 0x91, 0xc8, 0x8f, 0xe6, 0xcd, 0x44, 0x4b, 0xe2, 0x09, 
  0xc0, 0x07, 0xde, 0x45, 0x3c, 0xc3, 0xda, 0x81, 0xb8, 0x7f, 0xd6, 0xbd, 
  0x34, 0x3b, 0xd2, 0xf9, 0xb0, 0xf7, 0xce, 0x35, 0x2c, 0xb3, 0xca, 0x71, 
  0xa8, 0x6f, 0xc6, 0xad, 0x24, 0x2b, 0xc2, 0xe9, 0xa0, 0xe7, 0xbe, 0x25, 
  0x1c, 0xa3, 0xba, 0x61, 0x98, 0x5f, 0xb6, 0x9d, 0x14, 0x1b, 0xb2, 0xd9, 
  0x90, 0xd7, 0xae, 0x15, 0x0c, 0x93, 0xaa, 0x51, 0x88, 0x4f, 0xa6, 0x8d, 
  0x04, 0x0b, 0xa2, 0xc9, 0x80, 0xc7, 0x9e, 0x05, 0xfc, 0x83, 0x9a, 0x41, 
  0x78, 0x3f, 0x96, 0x7d, 0xf4, 0xfb, 0x92, 0xb9, 0x70, 0xb7, 0x8e, 0xf5, 
  0xec, 0x73, 0x8a, 0x31, 0x68, 0x2f, 0x86, 0x6d, 0xe4, 0xeb, 0x82, 0xa9, 
  0x60, 0xa7, 0x7e, 0xe5, 0x7b, 0x20, 0x72, 0x65, 0x74, 0x75, 0x72, 0x6e, 
  0x20, 0x4d, 0x6f, 0x64, 0x75, 0x6c, 0x65, 0x2e, 0x64, 0x28, 0x24, 0x30, 
  0x29, 0x3b, 0x20, 0x7d, 0x00, 0x94, 0x20, 0x85, 0x10, 0xc2, 0xc0, 0x01, 
  0xfb, 0x01, 0xc0, 0xc2, 0x10, 0x85, 0x20, 0x94, 0x01, 0xbb, 0x6b, 0xd9, 
  0xcf, 0x25, 0x71, 0xef, 0x52, 0x52, 0xbd, 0x1b, 0xfc, 0x09, 0x6e, 0x41, 
  0xbe, 0x9b, 0x28, 0xea, 0x83, 0x5c, 0x3f, 0x08, 0x80, 0x7e, 0x13, 0xda, 
  0xfd, 0xe9, 0xd8, 0x84, 0x97, 0x93, 0xb2, 0xac, 0xc6, 0x79, 0xf1, 0x5a, 
  0x70, 0x91, 0xf2, 0xc7, 0x74, 0xb8, 0xa2, 0xf0, 0xa6, 0x2b, 0x39, 0xf2, 
  0x70, 0xc8, 0x87, 0xae, 0x96, 0xc4, 0x0f, 0xbe, 0x85, 0x2e, 0x53, 0xd0, 
  0x8d, 
};


static void init_table(void) {
  uint32_t offset;
}




static void init_memory(void) {
	g4=4;
}


int main(int argc, char const *argv[])
{

  int i;
  init_memory();
  uint8_t ctx [10*16] = {0};
  uint8_t msg [16] ={0};
  uint8_t key[32] = {};
  uint8_t flag[0x40] = {};
  memset(key,0x0,16);

  memcpy((char *)(&main_memory) + 1024, data_segment_data_0, 361);


  uint32_t ctx_offset=0x80;
  memcpy((char *)(&main_memory) + ctx_offset, ctx, sizeof(ctx));
  uint32_t key_offset=ctx_offset + sizeof(ctx);
  memcpy((char *)(&main_memory) + key_offset, key, sizeof(key));
  uint32_t msg_offset= key_offset + sizeof(key);
  memcpy((char *)(&main_memory) + msg_offset, msg, sizeof(msg));

  uint32_t flag_offset= msg_offset + sizeof(msg);

  printf("------------------ _getFlag ------------------\n");
  _getFlag(0x5571c18, flag_offset);
  memcpy(flag, (char *)(&main_memory) + flag_offset, sizeof(flag));
  printf("flag : ");
  for(i=0;i<sizeof(flag); i++) {
    if(i%0x10 == 0) {
	    printf("\n");
    }
    printf("%02x",flag[i]);
  }
  printf("\n");


  printf("--------------- _setDecryptKey ---------------\n");
  f13(ctx_offset,key_offset);
  memcpy(ctx, (char *)(&main_memory) + ctx_offset, sizeof(ctx));
  printf("ctx : ");
  for(i=0;i<(0x10*10); i++) {
    if(i%0x10 == 0) {
	    printf("\n");
    }
    printf("%02x",ctx[i]);
  }
  printf("\n");


  printf("--------------- _decryptBlock  ---------------\n");
  _decryptBlock(ctx_offset,msg_offset);
  memcpy(msg, (char *)(&main_memory) + msg_offset, sizeof(msg));
  printf("msg out : ");
  for(i=0;i<(0x10); i++) {
    if(i%0x10 == 0) {
	    printf("\n");
    }
    printf("%02x",msg[i]);
  }
  printf("\n");

  return 0;
}

