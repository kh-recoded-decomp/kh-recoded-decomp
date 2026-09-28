#include "nitro/types.h"

extern int ProjectPositionDownward_020352e0(void *cont, int p3, void *out);
extern void *g_recordTablePtr_0206083c;

int func_02036564(int p3, void *out) {
    return ProjectPositionDownward_020352e0(g_recordTablePtr_0206083c, p3, out);
}
