#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Matrix33 {
    fx32 m[3][3];
} Matrix33;

extern void func_0204bf28(int first, int second, Matrix33 *out);

void BuildMatrix33_020495b8(Matrix33 *out, int first, int second)
{
    Matrix33 result;

    func_0204bf28(first, second, &result);
    *out = result;
}
