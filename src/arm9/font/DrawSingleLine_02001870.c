#include "nitro/types.h"

extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void func_01ff869c(const void *src, void *dst, u32 size);
extern void func_02001668(void *context, int x, int y, int color, int param5, const void *param6);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void DrawSingleLine_02001870(void *context, int x, int y, int color, int param5, u16 *text, void **cursorOut)
{
    int count = 0;
    u16 *p = text;
    u16 ch;

    if (cursorOut != 0) {
        *cursorOut = 0;
    }
    while ((ch = *p) != 0 && ch != 10) {
        p++;
        count++;
    }
    if (count != 0) {
        void *line;
        if (cursorOut != 0 && ch != 0) {
            *cursorOut = p + 1;
        }
        line = NNSi_FndAllocFromDefaultHeapEx_0202a19c((count + 1) * 2, -4);
        func_01ff869c(text, line, count * 2);
        ((u16 *)line)[count] = 0;
        func_02001668(context, x, y, color, param5, line);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(line);
    }
}
