#include "nitro/types.h"

typedef struct {
    u32 flag0 : 1;
    u32 flag1 : 1;
    u32 exitRequested : 1;
} ExitFlags;

extern int data_ov039_020bea00;
extern void func_ov039_020bcf20(int arg0);
extern void func_ov039_020bd054(int arg0);
extern void func_0204d7f4(int new_value);
extern BOOL IsSoundStreamActive_0204ded4(int handleIndex);
extern BOOL IsCachedSeqPlaying_0204da48(void);
extern void SetCardThreadStartTick_02027258(void);
extern void func_ov039_020baae0(int phase);

void UpdateExitSequence_020bb33c(void)
{
    int base = data_ov039_020bea00;

    func_ov039_020bcf20(*(int *)(base + 0xc998));
    func_ov039_020bd054(*(int *)(base + 0xc99c));
    if (!((ExitFlags *)(base + 0xc9e8))->exitRequested) {
        return;
    }
    if (*(int *)(base + 0xca34) != 0) {
        if (*(int *)(base + 0xca38) == 0) {
            func_0204d7f4(5);
            *(int *)(base + 0xca38) = 1;
        }
        if (IsSoundStreamActive_0204ded4(1)) {
            return;
        }
        if (IsCachedSeqPlaying_0204da48()) {
            return;
        }
        func_ov039_020baae0(9);
    } else if (*(int *)(base + 0xc994) == 3 && *(int *)(base + 0xca80) == 1) {
        if (IsSoundStreamActive_0204ded4(1)) {
            return;
        }
        SetCardThreadStartTick_02027258();
        func_ov039_020baae0(9);
    } else {
        func_ov039_020baae0(9);
    }
}
