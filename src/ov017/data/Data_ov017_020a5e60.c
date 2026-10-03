#include "nitro/types.h"

extern void DefaultStepDone_020a2214(void);
extern void ScriptCmd_CreateGridObject_020a2350(void);
extern void ScriptCmd_CreateManagerObject_020a1e10(void);
extern void ScriptCmd_CreatePoolObject_020a2440(void);
extern void ScriptCmd_CreateSlotObjectKind4_020a1de0(void);
extern void ScriptCmd_CreateSlotObjectKind7_020a2410(void);
extern void ScriptCmd_CreateSlotObjectKind8_020a2320(void);
extern void ScriptCmd_InitPool0_020a2554(void);
extern void ScriptCmd_InitPool1_020a256c(void);
extern void ScriptCmd_InitPool2_020a2584(void);
extern void ScriptCmd_InitPool3_020a259c(void);
extern void ScriptCmd_InitPool4_020a25b4(void);
extern void ScriptCmd_QueueEntryCommand_020a2288(void);
extern void ScriptCmd_QueueEntryDirectionMessage_020a20b0(void);
extern void ScriptCmd_QueueEntryMessageRange_020a25cc(void);
extern void ScriptCmd_QueueEntryMessage_020a2244(void);
extern void ScriptCmd_QueueEntryPathMessages_020a213c(void);
extern void ScriptCmd_QueueEntryPositionMessage_020a1f68(void);
extern void ScriptCmd_QueueEntryRotationMessage_020a1ff8(void);
extern void ScriptCmd_QueueEntryValueMessage_020a1f18(void);
extern void ScriptCmd_ResetEntry_020a2218(void);
extern void ScriptCmd_SetEntryFlag_020a1edc(void);
extern void ScriptCmd_SetManagerValue_020a2628(void);

void (*data_ov017_020a5e60[46])(void) = {
    ScriptCmd_CreateSlotObjectKind4_020a1de0,
    NULL,
    ScriptCmd_CreateManagerObject_020a1e10,
    NULL,
    ScriptCmd_QueueEntryValueMessage_020a1f18,
    NULL,
    ScriptCmd_QueueEntryPositionMessage_020a1f68,
    NULL,
    ScriptCmd_QueueEntryRotationMessage_020a1ff8,
    NULL,
    ScriptCmd_QueueEntryDirectionMessage_020a20b0,
    NULL,
    ScriptCmd_QueueEntryPathMessages_020a213c,
    NULL,
    DefaultStepDone_020a2214,
    NULL,
    ScriptCmd_SetEntryFlag_020a1edc,
    NULL,
    ScriptCmd_ResetEntry_020a2218,
    NULL,
    ScriptCmd_QueueEntryMessage_020a2244,
    NULL,
    ScriptCmd_QueueEntryCommand_020a2288,
    NULL,
    ScriptCmd_CreateSlotObjectKind8_020a2320,
    NULL,
    ScriptCmd_CreateGridObject_020a2350,
    NULL,
    ScriptCmd_CreateSlotObjectKind7_020a2410,
    NULL,
    ScriptCmd_CreatePoolObject_020a2440,
    NULL,
    ScriptCmd_InitPool0_020a2554,
    NULL,
    ScriptCmd_InitPool1_020a256c,
    NULL,
    ScriptCmd_InitPool2_020a2584,
    NULL,
    ScriptCmd_InitPool3_020a259c,
    NULL,
    ScriptCmd_InitPool4_020a25b4,
    NULL,
    ScriptCmd_QueueEntryMessageRange_020a25cc,
    NULL,
    ScriptCmd_SetManagerValue_020a2628,
    NULL,
};
