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
typedef void (*FinishHook)(void *arg);

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
    u8 pad_00000[0x18];
    void *container;
    u8 pad_0001c[0x4e5c - 0x1c];
    u8 messages[0x7f9c - 0x4e5c];
    u8 window[0x11be0 - 0x7f9c];
    ChoiceHandler choices[3];
    u8 pad_11bf8[0x11c04 - 0x11bf8];
    const PromptDef *promptDef;
    s32 promptsLeft;
    void *promptArg;
    FinishHook onFinish;
    u16 windowTop;
    u16 windowMargin;
} ItemScreen;

extern void SetGlobalPackedBit_02027320(int bitIndex);
extern void *func_ov027_020ba2a8(void *messages, int index);
extern TileSize MenuPanel_MeasureMessage_020cb2b8(void *window, int style, const void *text);
extern void MenuPanel_InitStandard_020cb380(void *window, u32 owner, u16 x, u16 y, u16 width, u16 height,
                                              void *text);
extern void *func_ov027_020b90a4(void *container, int elementId);
extern void func_ov027_020b9580(void *container, void *element, int visible);
extern void MenuScreen_RefreshMarker_020cbb3c(void);

static inline ChoiceHandler MakeChoiceHandler(void *callback, void *owner)
{
    ChoiceHandler handler;
    handler.callback = callback;
    handler.owner = owner;
    return handler;
}

void AdvanceHintPrompt_020caf8c(ItemScreen *screen)
{
    int top;

    SetGlobalPackedBit_02027320(screen->promptDef->flagIndex + 0xf50);
    if (--screen->promptsLeft != 0) {
        void *text;
        TileSize size;
        s8 align;
        int avail;

        screen->promptDef++;
        if (screen->promptDef->onOpen != NULL) {
            screen->promptDef->onOpen(screen->promptArg, screen->promptDef);
        }
        text = func_ov027_020ba2a8(screen->messages, screen->promptDef->messageIndex);
        size = MenuPanel_MeasureMessage_020cb2b8(screen->window, 1, text);
        align = screen->promptDef->align;
        avail = 0x18 - screen->windowMargin - screen->windowTop;
        if (align == 0) {
            top = (avail - size.height) / 2;
        } else if (align < 0) {
            top = align + ((avail / 2 - size.height) / 2 + 1);
            if (top < 0) {
                top = 0;
            }
        } else {
            top = align;
            top += (avail / 2 - 1) + (avail / 2 - size.height) / 2;
            if (top + size.height > avail) {
                top = avail - size.height;
            }
        }
        top += screen->windowTop;
        MenuPanel_InitStandard_020cb380(screen->window, 1, 0, top, size.width, size.height, text);
        screen->choices[1] = MakeChoiceHandler(MenuScreen_RefreshMarker_020cbb3c, screen);
        screen->choices[0] = MakeChoiceHandler(AdvanceHintPrompt_020caf8c, screen);
    } else if (screen->onFinish != NULL) {
        screen->onFinish(screen->promptArg);
    }
    func_ov027_020b9580(screen->container, func_ov027_020b90a4(screen->container, 0x2a), 0);
}
