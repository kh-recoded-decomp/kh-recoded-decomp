#include "nitro/types.h"

extern void HandleListCursorDown_020bef40(void);
extern void HandleListPageDown_020bf018(void);
extern void func_ov099_020befac(void);
extern void func_ov099_020bf084(void);
extern void func_ov099_020bf0ac(void);
extern void func_ov099_020bf0dc(void);
extern void func_ov099_020bf134(void);

void (*data_ov099_020c2360[11])(void) = {
    HandleListCursorDown_020bef40,
    func_ov099_020befac,
    HandleListPageDown_020bf018,
    NULL,
    func_ov099_020bf084,
    NULL,
    NULL,
    func_ov099_020bf0dc,
    func_ov099_020bf134,
    NULL,
    func_ov099_020bf0ac,
};
