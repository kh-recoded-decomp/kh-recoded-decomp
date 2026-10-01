#include "nitro/types.h"

typedef struct SelectionRecord {
    u8 pad_000[0x130];
    s16 sceneId;
} SelectionRecord;

typedef struct FieldState {
    u8 pad_0000[0x434];
    void *minigameTask;
    u8 pad_0438[0xf08];
    void (*callbacks[6])(void);
} FieldState;

typedef struct FieldGlobals {
    u32 unk_00;
    FieldState *state;
} FieldGlobals;

typedef void *(*FieldStep)(void);

extern FieldGlobals data_ov001_020a04a4;
extern char data_ov001_0209f004[];
extern SelectionRecord *func_0204f768(int index);
extern void *func_0202a448(void *descriptor, void *userData);
extern void func_ov001_0207ea14(void);
extern void func_ov001_0207eadc(void);
extern void func_ov001_0207eb0c(void);
extern void func_ov001_0207eb70(void);
extern void func_ov001_0207eb8c(void);
extern void func_ov001_0207eb9c(void);
extern void *func_ov001_02070e98(void);

FieldStep StartSceneMinigameTask_02070cfc(void)
{
    FieldState *state = data_ov001_020a04a4.state;
    s16 sceneId = func_0204f768(0)->sceneId;

    if (state->minigameTask == NULL) {
        switch (sceneId) {
        case 0xc5:
            state->minigameTask = func_0202a448(data_ov001_0209f004, (void *)1);
            break;
        case 0xc6:
            state->minigameTask = func_0202a448(data_ov001_0209f004, (void *)2);
            break;
        case 0xca:
            state->minigameTask = func_0202a448(data_ov001_0209f004, (void *)3);
            break;
        default:
            goto done;
        }
        state->callbacks[0] = func_ov001_0207ea14;
        state->callbacks[1] = func_ov001_0207eadc;
        state->callbacks[2] = func_ov001_0207eb0c;
        state->callbacks[3] = func_ov001_0207eb70;
        state->callbacks[4] = func_ov001_0207eb8c;
        state->callbacks[5] = func_ov001_0207eb9c;
    }
done:
    return func_ov001_02070e98;
}
