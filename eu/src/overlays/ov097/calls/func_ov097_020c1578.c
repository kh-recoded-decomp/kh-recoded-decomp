#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xf06c];
    int value;
    int unk_F070;
    int unk_F074;
} MenuScene;

void func_ov097_020c1578(int value, MenuScene *scene)
{
    scene->value = value;
    scene->unk_F070 = 0;
    scene->unk_F074 = 0;
}
