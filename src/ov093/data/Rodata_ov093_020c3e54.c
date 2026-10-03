#include "nitro/types.h"

extern void StartNextPopup_020c31d8(void);
extern void func_ov093_020c31d4(void);
extern void func_ov093_020c324c(void);
extern void func_ov093_020c336c(void);
extern void func_ov093_020c3418(void);
extern void func_ov093_020c34a4(void);
extern void func_ov093_020c351c(void);
extern void func_ov093_020c35cc(void);

void (*const data_ov093_020c3e54[8])(void) = {
    func_ov093_020c31d4,
    StartNextPopup_020c31d8,
    func_ov093_020c324c,
    func_ov093_020c336c,
    func_ov093_020c3418,
    func_ov093_020c34a4,
    func_ov093_020c351c,
    func_ov093_020c35cc,
};
