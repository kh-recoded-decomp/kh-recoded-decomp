#include "nitro/types.h"

extern void FinishMovieSkip_020ba668(void);
extern void PollOverlay40Phase_020ba628(void);
extern void func_ov035_020ba574(void);
extern void func_ov035_020ba5b8(void);
extern void func_ov035_020ba5c4(void);
extern void func_ov035_020ba5f0(void);
extern void func_ov035_020ba6a0(void);
extern void func_ov035_020ba6b8(void);
extern void func_ov035_020ba6c4(void);
extern void func_ov035_020ba740(void);

void (*data_ov035_020bc478[10])(void) = {
    func_ov035_020ba574,
    func_ov035_020ba5b8,
    func_ov035_020ba5c4,
    func_ov035_020ba5f0,
    PollOverlay40Phase_020ba628,
    FinishMovieSkip_020ba668,
    func_ov035_020ba6a0,
    func_ov035_020ba6b8,
    func_ov035_020ba6c4,
    func_ov035_020ba740,
};
