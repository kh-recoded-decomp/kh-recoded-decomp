#include "nitro/types.h"

typedef struct DeviceInfo {
    u8 pad_00[0x10];
    void *capability;
} DeviceInfo;

typedef struct Owner {
    u8 pad_00[0x24];
    DeviceInfo *deviceInfo;
} Owner;

typedef struct CommandState {
    u32 field_00;
    u32 field_04;
    Owner *owner;
    u32 flags;
    void *params;
    u32 status;
    u32 field_18;
    u32 field_1c;
    u8 pad_20[0x28];
} CommandState;

typedef struct Descriptor {
    u32 field0;
    void *buffer;
    u32 field8;
    u32 field_c;
} Descriptor;

typedef struct GlobalContext {
    void *listHead;
    Owner *current;
    u16 field_08;
    u16 field_0a;
    u32 field_0c;
} GlobalContext;

extern Owner *func_0200ac28(void *context, u32 *outValue, u8 *buffer);
extern void func_02010bcc(u8 *dest, u8 *src, u32 maxLen);
extern void func_0200b394(CommandState *state);
extern int func_0200a930(CommandState *cmd, int priority, int urgent);
extern GlobalContext g_context_020578ec;
extern u8 data_020579fc[];

int SubmitSaveRequest_0200aaf4(void *context, u32 reserved1, u32 reserved2, u32 reserved3) {
    int result = 0;
    u32 outValue = 0;
    u8 buffer[0x104];
    Owner *owner = func_0200ac28(context, &outValue, buffer);

    if (owner != 0) {
        g_context_020578ec.current = owner;
        g_context_020578ec.field_08 = 0;
        g_context_020578ec.field_0a = 0;
        g_context_020578ec.field_0c = 0;
        func_02010bcc(data_020579fc, buffer, 0x104);
        if (owner->deviceInfo->capability != 0) {
            CommandState cmd;
            Descriptor descriptor;
            int submitResult;
            func_0200b394(&cmd);
            cmd.owner = owner;
            cmd.params = &descriptor;
            descriptor.field0 = outValue;
            descriptor.buffer = buffer;
            descriptor.field_c = 1;
            submitResult = func_0200a930(&cmd, 4, 1);
            if (submitResult != 0) {
                g_context_020578ec.field_08 = (u16)descriptor.field8;
                func_02010bcc(data_020579fc, buffer, 0x104);
            }
        }
        result = 1;
    }
    return result;
}
