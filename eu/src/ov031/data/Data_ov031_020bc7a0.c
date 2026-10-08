#include "nitro/types.h"

#pragma explicit_zero_data on

extern void EnterState10(void);
extern void EnterState12(void);
extern void EnterState15(void);
extern void EnterState2(void);
extern void EnterState7Alt(void);
extern void InitMoviePlayerState(void);
extern void SelectNextState(void);
extern void ShutdownActiveState(void);
extern void TryEnterState1(void);
extern void TryEnterState16(void);
extern void TryEnterState17(void);
extern void TryEnterState18(void);
extern void TryEnterState3(void);
extern void TryEnterState4(void);
extern void TryEnterState5(void);
extern void TryEnterState6(void);
extern void TryEnterState7(void);
extern void TryReenterState7(void);
extern void TryReenterState7Clear(void);
extern void func_ov031_020ba900(void);
extern void FinishMoviePlayerState(void);

typedef struct UnalignedPtr {
    void *ptr __attribute__((packed));
} __attribute__((packed)) UnalignedPtr;

struct {
    UnalignedPtr pointers0[19];
    u8 bytes1[17];
} __attribute__((packed)) data_ov031_020bc7b8 = {
    {
        {(void *)TryEnterState1},
        {(void *)EnterState2},
        {(void *)TryEnterState3},
        {(void *)TryEnterState4},
        {(void *)TryEnterState5},
        {(void *)TryEnterState6},
        {(void *)TryEnterState7},
        {(void *)SelectNextState},
        {(void *)EnterState7Alt},
        {(void *)EnterState10},
        {(void *)func_ov031_020ba900},
        {(void *)EnterState12},
        {(void *)TryReenterState7},
        {(void *)TryReenterState7Clear},
        {(void *)EnterState15},
        {(void *)TryEnterState16},
        {(void *)TryEnterState17},
        {(void *)TryEnterState18},
        {(void *)FinishMoviePlayerState},
    },
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00,
    },
};

void *data_ov031_020bc7a4[5] = {
    (void *)0x0002000E,
    (void *)InitMoviePlayerState,
    (void *)ShutdownActiveState,
    (void *)0x00000408,
    NULL,
};

u32 data_ov031_020bc7a0[1] = {
    0xFFFFFFFF,
};
