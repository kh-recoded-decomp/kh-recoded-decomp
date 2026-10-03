#include "nitro/types.h"

typedef struct {
    int param30;
    int param2c;
} DriftParams;

extern DriftParams data_ov044_020d0dc0[];

extern void func_ov044_020d058c(int param30, int param2c);

void SpawnPanelDriftPreset_020d05c0(int index)
{
    func_ov044_020d058c(data_ov044_020d0dc0[index].param30, data_ov044_020d0dc0[index].param2c);
}
