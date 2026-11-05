#ifndef KH_RECODED_PORTABLE_NITRO_MATRIX_H
#define KH_RECODED_PORTABLE_NITRO_MATRIX_H

#include <stdint.h>

/* Host-side equivalents, not inputs to the byte-matching DS build.
 * Row-major signed 20.12 coefficients: 0x1000 represents one.
 * See docs/library/sdk_mtx.md for the original register interfaces.
 */
typedef struct KHMatrix22 { int32_t row[2][2]; } KHMatrix22;
typedef struct KHMatrix33 { int32_t row[3][3]; } KHMatrix33;
typedef struct KHMatrix43 { int32_t row[4][3]; } KHMatrix43;
typedef struct KHMatrix44 { int32_t row[4][4]; } KHMatrix44;

typedef char KHMatrix22SizeCheck[sizeof(KHMatrix22) == 16 ? 1 : -1];
typedef char KHMatrix33SizeCheck[sizeof(KHMatrix33) == 36 ? 1 : -1];
typedef char KHMatrix43SizeCheck[sizeof(KHMatrix43) == 48 ? 1 : -1];
typedef char KHMatrix44SizeCheck[sizeof(KHMatrix44) == 64 ? 1 : -1];

#if defined(_WIN32) && defined(KH_PORTABLE_TEST_DLL)
#define KH_MATRIX_API __declspec(dllexport)
#else
#define KH_MATRIX_API
#endif

KH_MATRIX_API void KH_MTX_Identity22(KHMatrix22 *destination);
KH_MATRIX_API void KH_MTX_Identity33(KHMatrix33 *destination);
KH_MATRIX_API void KH_MTX_Identity43(KHMatrix43 *destination);
KH_MATRIX_API void KH_MTX_Identity44(KHMatrix44 *destination);

/* Expansion requires disjoint buffers. Compaction also supports equal bases. */
KH_MATRIX_API void KH_MTX_Copy43To44(const KHMatrix43 *source, KHMatrix44 *destination);
KH_MATRIX_API void KH_MTX_Copy44To43(const KHMatrix44 *source, KHMatrix43 *destination);

/* Sine/cosine are already fixed-point coefficients; they are not angles. */
KH_MATRIX_API void KH_MTX_RotX43(KHMatrix43 *destination, int32_t sine, int32_t cosine);
KH_MATRIX_API void KH_MTX_RotY43(KHMatrix43 *destination, int32_t sine, int32_t cosine);

/* The nine destination words must be aligned and writable. */
KH_MATRIX_API void KH_MI_Zero36B(uint32_t *destination);

#undef KH_MATRIX_API
#endif
