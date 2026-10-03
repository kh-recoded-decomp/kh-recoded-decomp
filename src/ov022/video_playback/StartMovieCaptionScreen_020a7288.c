#include "nitro/types.h"

typedef struct {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
    u16 unk_10;
    u16 tileOffset;
    u16 unk_14;
} CaptionFrame;

typedef struct {
    void *arg;
    void (*onFinish)(void);
    int enabled;
} MovieRequest;

typedef struct {
    u8 pad_000[2];
    u16 flags;
    u8 pad_004[0x820];
    u8 captionData[0xc];
    u8 textLayer[0x80];
    int state;
} MoviePlayer;

extern MoviePlayer *data_ov022_020b7d80;

extern void func_ov022_020a6f24(void);
extern void func_ov022_020a8a04(void *textLayer, int mode, void *data, CaptionFrame *frame);
extern u16 *func_0202b3b8(int screen);
extern void FillBackgroundTileRectangle_02017adc(u16 *dst, int width, int height, int x, int y, int stride, int value, int palette);
extern void func_ov022_020a8a70(void *textLayer, int visible);
extern BOOL func_ov022_020a8338(MovieRequest *request);
extern void StoreGlobalArrayEntry_02025668(int index, int value);

void StartMovieCaptionScreen_020a7288(void *arg) {
    MoviePlayer *player = data_ov022_020b7d80;
    MovieRequest request;
    CaptionFrame frame;

    request.arg = arg;
    request.onFinish = func_ov022_020a6f24;
    request.enabled = 1;
    player->state = 1;
    frame.x = 0;
    frame.y = 0;
    frame.width = 0x20;
    frame.height = 0x16;
    frame.charBase = 1;
    frame.palette = 0xd;
    frame.hSpace = 2;
    frame.vSpace = 0;
    frame.unk_10 = 0;
    frame.tileOffset = 0x98;
    frame.unk_14 = 0;
    func_ov022_020a8a04(player->textLayer, 0, player->captionData, &frame);
    FillBackgroundTileRectangle_02017adc(func_0202b3b8(1), frame.width, frame.height, frame.x, frame.y, 0x20, frame.charBase, 0xe);
    FillBackgroundTileRectangle_02017adc(func_0202b3b8(2), frame.width, frame.height, frame.x, frame.y, 0x20, frame.charBase, 0xe);
    func_ov022_020a8a70(player->textLayer, 1);
    if (func_ov022_020a8338(&request)) {
        return;
    }
    player->flags |= 2;
    StoreGlobalArrayEntry_02025668(3, 0);
}
