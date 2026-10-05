#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x94];
    u8 font[1];
} TextPrinter;

typedef struct {
    u32 unk_00;
    union {
        TextPrinter printer;
        struct {
            u32 unk_04;
            s32 printMode;
            s32 state;
        } header;
    } body;
} MessageWindow;

extern MessageWindow *data_ov001_020a04c4;

extern BOOL DrawMessageWindowPage_02079b4c(TextPrinter *printer, int step);
extern BOOL func_ov001_02079a9c(TextPrinter *printer);
extern BOOL func_ov001_02079c88(TextPrinter *printer, int step);
extern void Text_UploadTileBuffer_02001520(void *font);
extern void FinishMessageWindowPage_02079f2c(TextPrinter *printer);
extern void func_ov001_02079f70(TextPrinter *printer);
extern void CloseModeWindow_0207a260(TextPrinter *printer);

int UpdateMessageWindow_0207a68c(void) {
    int result = 0;
    MessageWindow *window = data_ov001_020a04c4;

    switch (window->body.header.state) {
    case 0:
        return result;
    case 1:
    case 2:
    case 3:
        result = 1;
        break;
    case 4:
        switch (window->body.header.printMode) {
        case 0:
            if (!DrawMessageWindowPage_02079b4c(&window->body.printer, 1)) {
                FinishMessageWindowPage_02079f2c(&window->body.printer);
                result = 3;
            } else {
                result = 2;
            }
            break;
        case 1:
            while (func_ov001_02079a9c(&window->body.printer)) {
            }
            Text_UploadTileBuffer_02001520((&window->body.printer)->font);
            FinishMessageWindowPage_02079f2c(&window->body.printer);
            result = 3;
            break;
        case 2:
            if (!func_ov001_02079c88(&window->body.printer, 1)) {
                FinishMessageWindowPage_02079f2c(&window->body.printer);
                result = 3;
            } else {
                result = 2;
            }
            break;
        }
        break;
    case 5:
        func_ov001_02079f70(&window->body.printer);
        result = 3;
        break;
    case 6:
        CloseModeWindow_0207a260(&window->body.printer);
        result = 4;
        break;
    case 7:
        result = 4;
        break;
    default:
        return 0;
    }
    return result;
}
