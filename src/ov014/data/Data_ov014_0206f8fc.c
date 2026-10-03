#include "nitro/types.h"

extern void UpdatePanelCloseStep_0206e86c(void);
extern void UpdatePanelOpenStep_0206d25c(void);
extern void func_ov014_0206d2e0(void);
extern void func_ov014_0206d2e4(void);
extern void func_ov014_0206d2e8(void);
extern void func_ov014_0206e84c(void);
extern void func_ov014_0206e850(void);
extern void func_ov014_0206e8fc(void);

void (*data_ov014_0206f900[7])(void) = {
    func_ov014_0206d2e0,
    func_ov014_0206d2e4,
    func_ov014_0206d2e8,
    func_ov014_0206e84c,
    func_ov014_0206e850,
    UpdatePanelCloseStep_0206e86c,
    func_ov014_0206e8fc,
};

void (*data_ov014_0206f8fc[1])(void) = {
    UpdatePanelOpenStep_0206d25c,
};
