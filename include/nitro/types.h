/* Basic types, with the NitroSDK's names.
 *
 * Under CodeWarrior the 32-bit types are `long`, as the SDK spells them and the game was built
 * with: mwcc does not always generate the same code for `long` and `int` (NitroSystem's G3D
 * decoders only match with `long`). Elsewhere they are `int`, which stays 32 bits on a 64-bit
 * host.
 */
#ifndef NITRO_TYPES_H
#define NITRO_TYPES_H

typedef unsigned char u8;
typedef unsigned short u16;
#ifdef __MWERKS__
typedef unsigned long u32;
#else
typedef unsigned int u32;
#endif
typedef unsigned long long u64;

typedef signed char s8;
typedef short s16;
#ifdef __MWERKS__
typedef signed long s32;
#else
typedef int s32;
#endif
typedef long long s64;

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;

typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef float f32;

typedef int BOOL;

#define TRUE 1
#define FALSE 0

#define NULL ((void *)0)

/* Hardware register views, as the SDK's register headers name them. */
typedef volatile u8 REGType8v;
typedef volatile u16 REGType16v;
typedef volatile u32 REGType32v;

#endif
