#include "nitro/types.h"

typedef struct MovieSourceOps {
    void *open;
    void *op1;
    void *op2;
    void *op3;
    void *isOpen;
    void *close;
    void *op6;
    void *op7;
    void *op8;
    void *unused9;
    void *op10;
} MovieSourceOps;

extern void MobiClip_SrcOpen_020ba940(void);
extern void func_ov035_020ba958(void);
extern void func_ov035_020ba974(void);
extern void func_ov035_020ba98c(void);
extern void MobiClip_SrcIsOpen_020ba9a4(void);
extern void MobiClip_SrcClose_020ba9c0(void);
extern void func_ov035_020ba9d8(void);
extern void func_ov035_020bad44(void);
extern void func_ov035_020ba7dc(void);
extern void func_ov035_020baa18(void);
extern void func_ov001_02064734(int mode);

void InitMovieSourceOps_020bad94(MovieSourceOps *ops) {
    ops->open = MobiClip_SrcOpen_020ba940;
    ops->op1 = func_ov035_020ba958;
    ops->op2 = func_ov035_020ba974;
    ops->op3 = func_ov035_020ba98c;
    ops->isOpen = MobiClip_SrcIsOpen_020ba9a4;
    ops->close = MobiClip_SrcClose_020ba9c0;
    ops->op6 = func_ov035_020ba9d8;
    ops->op7 = func_ov035_020bad44;
    ops->op8 = func_ov035_020ba7dc;
    ops->op10 = func_ov035_020baa18;
    func_ov001_02064734(3);
}
