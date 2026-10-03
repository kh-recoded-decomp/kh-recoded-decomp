#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ChannelMeter {
    u8 unknown_00[0x1c];
    int baseY;
    u8 levelA[3];
    u8 levelB[3];
    u8 levelC[3];
    u8 levelD[3];
    u8 levelE[3];
    u8 levelF[3];
} ChannelMeter;

extern void SetupMovieCamera_020bb8f0(void);
extern void QueueOrSendGeometryCommand_01ffa37c(u32 op, const u32 *args, u32 numWords);

static inline void GeomBegin(u32 primitive) {
    u32 arg = primitive;
    QueueOrSendGeometryCommand_01ffa37c(0x40, &arg, 1);
}

static inline void GeomColor(u32 color) {
    u32 arg = color;
    QueueOrSendGeometryCommand_01ffa37c(0x20, &arg, 1);
}

static inline void GeomVtx(fx16 x, fx16 y, fx16 z) {
    u32 args[2];
    args[0] = (u32)(u16)x | ((u32)(u16)y << 16);
    args[1] = (u32)(u16)z;
    QueueOrSendGeometryCommand_01ffa37c(0x23, args, 2);
}

static inline void GeomEnd(void) {
    QueueOrSendGeometryCommand_01ffa37c(0x41, NULL, 0);
}

void DrawChannelMeter_020bb96c(ChannelMeter *meter, int channel) {
    int rowTop = meter->baseY + channel * 16;
    int top = 0xbf - rowTop;
    int bottom = 0xbf - (rowTop + 8);
    u8 *energy;
    u8 value;

    SetupMovieCamera_020bb8f0();
    energy = meter->levelE;
    if (energy[channel] != 0) {
        GeomBegin(1);
        GeomColor(0x27f4);
        GeomVtx(energy[channel] + 0xe0, top, 0x2000);
        GeomVtx(0xe0, top, 0x2000);
        GeomColor(0x1e2);
        GeomVtx(0xe0, bottom, 0x2000);
        GeomVtx(energy[channel] + 0xe0, bottom, 0x2000);
        GeomEnd();
    }
    GeomBegin(1);
    GeomColor(0x2108);
    GeomVtx(0xf8, top, 0x1000);
    GeomVtx(meter->levelD[channel] + 0xe0, top, 0x1000);
    GeomVtx(meter->levelD[channel] + 0xe0, bottom, 0x1000);
    GeomVtx(0xf8, bottom, 0x1000);
    GeomEnd();
    GeomBegin(3);
    GeomColor(0x1f);
    GeomVtx(0xd8, top, 0);
    GeomVtx(0xd8, bottom, 0);
    GeomVtx(meter->levelF[channel] + 0xd8, top, 0);
    GeomVtx(meter->levelF[channel] + 0xd8, bottom, 0);
    GeomColor(0x2108);
    GeomVtx(meter->levelF[channel] + 0xe0, top, 0);
    GeomVtx(meter->levelF[channel] + 0xe0, bottom, 0);
    GeomEnd();
    if (energy[channel] < meter->levelB[channel]) {
        energy[channel] = energy[channel] + 1;
        if (meter->levelF[channel] <= energy[channel]) {
            meter->levelA[channel] = energy[channel];
        }
    }
    if (meter->levelF[channel] > meter->levelA[channel]) {
        meter->levelF[channel]--;
        value = meter->levelF[channel];
        if (value < meter->levelD[channel]) {
            if (value > meter->levelC[channel]) {
                value = meter->levelC[channel];
            }
            meter->levelD[channel] = value;
        }
    }
}