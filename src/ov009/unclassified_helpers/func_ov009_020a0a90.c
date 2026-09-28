#include "nitro/types.h"

extern int func_ov009_020a0980(void);
extern int func_ov001_02063838(void);
extern int func_ov009_020a095c(int arg);
extern int func_ov001_0206ca68(int a, int b, int c);

int func_ov009_020a0a90(int arg) {
    int result;

    func_ov009_020a0980();
    result = func_ov001_02063838();
    if ((result == 0) && (result = func_ov009_020a095c(arg), result != 0)) {
        func_ov001_0206ca68(0, 1, 0);
    }
    return 0;
}
