#ifndef NITRO_SPI_TP_STATE_INTERNAL_H
#define NITRO_SPI_TP_STATE_INTERNAL_H

#include "nitro/types.h"

typedef struct TPTouchSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TPTouchSample;

typedef struct TPiCalibration {
    s32 xOrigin;
    s32 xDotSize;
    s32 xDotSizeInverse;
    s32 yOrigin;
    s32 yDotSize;
    s32 yDotSizeInverse;
} TPiCalibration;

typedef void (*TPiReceiveCallback)(int command, int result, u16 index);

typedef struct TPiTouchPanelState {
    u16 initialized;
    u16 reserved02;
    TPiReceiveCallback callback;
    TPTouchSample sample;
    u16 latestIndex;
    u16 samplingFrequency;
    TPTouchSample *samplingBuffers;
    u16 bufferCount;
    u16 reserved1a;
    TPiCalibration calibration;
    u16 calibrationEnabled;
    vu16 state;
    vu16 errorFlags;
    vu16 commandFlags;
} TPiTouchPanelState;

extern TPiTouchPanelState sTouchPanelState;

#endif
