#include "nitro/types.h"

#pragma explicit_zero_data on

extern void EnterState10_020ba8c0(void);
extern void EnterState12_020ba940(void);
extern void EnterState15_020ba9a8(void);
extern void EnterState2_020ba640(void);
extern void EnterState7Alt_020ba890(void);
extern void InitMoviePlayerState_020ba3e0(void);
extern void SelectNextState_020ba7f8(void);
extern void ShutdownActiveState_020ba5d0(void);
extern void TryEnterState16_020ba9d0(void);
extern void TryEnterState17_020baa0c(void);
extern void TryEnterState18_020baa34(void);
extern void TryEnterState1_020ba614(void);
extern void TryEnterState3_020ba678(void);
extern void TryEnterState4_020ba6a4(void);
extern void TryEnterState5_020ba6bc(void);
extern void TryEnterState6_020ba72c(void);
extern void TryEnterState7_020ba7c4(void);
extern void TryLeaveToState7_020ba8e0(void);
extern void TryReenterState7Clear_020ba980(void);
extern void TryReenterState7_020ba95c(void);
extern void func_ov031_020baae4(void);

typedef struct UnalignedPtr {
    void *ptr __attribute__((packed));
} __attribute__((packed)) UnalignedPtr;

struct {
    UnalignedPtr pointers0[19];
    u8 bytes1[17];
} __attribute__((packed)) data_ov031_020bc798 = {
    {
        {(void *)TryEnterState1_020ba614},
        {(void *)EnterState2_020ba640},
        {(void *)TryEnterState3_020ba678},
        {(void *)TryEnterState4_020ba6a4},
        {(void *)TryEnterState5_020ba6bc},
        {(void *)TryEnterState6_020ba72c},
        {(void *)TryEnterState7_020ba7c4},
        {(void *)SelectNextState_020ba7f8},
        {(void *)EnterState7Alt_020ba890},
        {(void *)EnterState10_020ba8c0},
        {(void *)TryLeaveToState7_020ba8e0},
        {(void *)EnterState12_020ba940},
        {(void *)TryReenterState7_020ba95c},
        {(void *)TryReenterState7Clear_020ba980},
        {(void *)EnterState15_020ba9a8},
        {(void *)TryEnterState16_020ba9d0},
        {(void *)TryEnterState17_020baa0c},
        {(void *)TryEnterState18_020baa34},
        {(void *)func_ov031_020baae4},
    },
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00,
    },
};

void *data_ov031_020bc784[5] = {
    (void *)0x0002000E,
    (void *)InitMoviePlayerState_020ba3e0,
    (void *)ShutdownActiveState_020ba5d0,
    (void *)0x00000408,
    NULL,
};

u32 data_ov031_020bc780[1] = {
    0xFFFFFFFF,
};
