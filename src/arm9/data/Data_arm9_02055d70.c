#include "nitro/types.h"

extern void func_01ffa624(void);
extern void func_01ffa73c(void);
extern void func_01ffad00(void);
extern void func_01ffae7c(void);

void (*data_02055d7c[4])(void) = {
    func_01ffad00,
    NULL,
    func_01ffae7c,
    NULL,
};

void (*data_02055d70[3])(void) = {
    func_01ffa624,
    func_01ffa73c,
    NULL,
};
