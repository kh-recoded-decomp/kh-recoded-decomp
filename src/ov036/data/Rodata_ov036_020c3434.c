#include "nitro/types.h"

extern void AdvanceTextWindowPage_020c0e14(void);
extern void CloseTextWindowEntry_020c1234(void);
extern void LoadTextWindowFrame_020bfb0c(void);
extern void UpdateTextWindowTyping_020c0d34(void);
extern void func_ov036_020bf6bc(void);
extern void func_ov036_020bf6c0(void);
extern void func_ov036_020bfe18(void);
extern void func_ov036_020c0328(void);
extern void func_ov036_020c03e0(void);
extern void func_ov036_020c0e10(void);
extern void func_ov036_020c1168(void);
extern void func_ov036_020c12e8(void);
extern void func_ov036_020c180c(void);
extern void func_ov036_020c1d28(void);

void (*const data_ov036_020c3434[14])(void) = {
    func_ov036_020bf6bc,
    func_ov036_020bf6c0,
    LoadTextWindowFrame_020bfb0c,
    func_ov036_020bfe18,
    func_ov036_020c0328,
    func_ov036_020c03e0,
    UpdateTextWindowTyping_020c0d34,
    func_ov036_020c0e10,
    AdvanceTextWindowPage_020c0e14,
    func_ov036_020c1168,
    CloseTextWindowEntry_020c1234,
    func_ov036_020c12e8,
    func_ov036_020c180c,
    func_ov036_020c1d28,
};
