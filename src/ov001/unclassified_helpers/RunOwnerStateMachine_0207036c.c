#include "nitro/types.h"

typedef struct Owner Owner;

typedef struct {
    int state;
    u8 timer[0x7c - 4];
    int restartPending;
} StateBlock;

struct Owner {
    u8 pad[0x550];
    StateBlock block;
};

typedef void (*StateHandler)(Owner *owner);

extern StateHandler data_ov001_0209ec78[];
extern u32 func_ov001_02064490(void);
extern void func_0205255c(void *timer);

void RunOwnerStateMachine_0207036c(Owner *owner) {
    StateBlock *block = &owner->block;
    if (func_ov001_02064490() == 0 && block->restartPending != 0) {
        func_0205255c(block->timer);
        block->state = 1;
        block->restartPending = 0;
    }
    if (data_ov001_0209ec78[block->state] != NULL) {
        data_ov001_0209ec78[block->state](owner);
    }
}
