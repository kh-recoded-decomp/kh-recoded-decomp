/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
#include "nitro/types.h"

struct TexMtxState;

/* Only these six affine terms are written; the rest of the matrix is retained. */
void SetAlternateTextureIdentityTerms(u32 *matrix, const struct TexMtxState *unusedState)
{
    matrix[0] = 0x1000;
    matrix[1] = 0;
    matrix[4] = 0;
    matrix[5] = 0x1000;
    matrix[12] = 0;
    matrix[13] = 0;
}
