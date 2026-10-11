#include "nitro/types.h"

typedef union {
    struct {
        s16 width;
        s16 height;
    };
    u32 packed;
} TileSize;

typedef struct PromptDef PromptDef;
typedef void (*PromptHook)(void *arg, const PromptDef *def);
typedef BOOL (*PromptCheck)(void *arg);

struct PromptDef {
    u8 flagIndex;
    u8 messageIndex;
    s8 align;
    u8 pad_03[0x5];
    PromptHook onOpen;
};

typedef struct ChoiceHandler {
    void *callback;
    void *owner;
} ChoiceHandler;

typedef struct ItemScreen {
    u8 pad_00000[0x4e5c];
    u8 messages[0x7f9c - 0x4e5c];
    u8 window[0x11be0 - 0x7f9c];
    ChoiceHandler choices[3];
    u8 pad_11bf8[0x11c04 - 0x11bf8];
    const PromptDef *promptDef;
    void *promptParam;
    void *promptArg;
    void *promptContext;
    u16 windowTop;
    u16 windowMargin;
} ItemScreen;

extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern void *func_ov027_020ba2a8(void *messages, int index);
extern TileSize MenuPanel_MeasureMessage_020cb2b8(void *window, int style, const void *text);
extern void MenuPanel_InitStandard_020cb380(void *window, u32 owner, u16 x, u16 y, u16 width, u16 height,
                                              void *text);
extern void MenuScreen_RefreshMarker_020cbb3c(void);
extern void AdvanceHintPrompt_020caf8c(void);

static inline ChoiceHandler MakeChoiceHandler(void *callback, void *owner)
{
    ChoiceHandler handler;
    handler.callback = callback;
    handler.owner = owner;
    return handler;
}

BOOL OpenHintPrompt_020cbba0(ItemScreen *screen, void *arg, PromptCheck canOpen, void *context, const PromptDef *def,
                             void *param)
{
    int top;

    if (!IsGlobalPackedBitSet_02027304(def->flagIndex + 0xf50) && (canOpen == NULL || canOpen(arg))) {
        void *text;
        TileSize size;
        s8 align;
        int avail;

        screen->promptDef = def;
        screen->promptParam = param;
        screen->promptArg = arg;
        screen->promptContext = context;
        if (screen->promptDef->onOpen != NULL) {
            screen->promptDef->onOpen(arg, screen->promptDef);
        }
        text = func_ov027_020ba2a8(screen->messages, screen->promptDef->messageIndex);
        size = MenuPanel_MeasureMessage_020cb2b8(screen->window, 1, text);
        align = screen->promptDef->align;
        avail = 0x18 - screen->windowMargin - screen->windowTop;
        if (align == 0) {
            top = (avail - size.height) / 2;
        } else if (align < 0) {
            top = (avail / 2 - size.height) / 2;
            if (top < 0) {
                top = 0;
            }
        } else {
            top = avail / 2 + (avail / 2 - size.height) / 2;
            if (top + size.height > avail) {
                top = avail - size.height;
            }
        }
        top += screen->windowTop;
        MenuPanel_InitStandard_020cb380(screen->window, 1, 0, top, size.width, size.height, text);
        screen->choices[1] = MakeChoiceHandler(MenuScreen_RefreshMarker_020cbb3c, screen);
        screen->choices[0] = MakeChoiceHandler(AdvanceHintPrompt_020caf8c, screen);
        return TRUE;
    }
    return FALSE;
}
