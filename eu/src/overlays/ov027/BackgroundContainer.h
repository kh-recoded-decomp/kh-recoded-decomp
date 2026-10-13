#ifndef KH_RECODED_BACKGROUND_CONTAINER_H
#define KH_RECODED_BACKGROUND_CONTAINER_H

#include "nitro/types.h"

typedef struct BackgroundContainerConfig {
    s32 entryCapacity;
    s32 spriteCapacity;
    s32 tagCapacity;
    s32 parameter0c;
    s32 parameter10;
} BackgroundContainerConfig;

typedef struct PanelObjectResourceConfig {
    u32 cellFileId;
    u32 parameters[4];
    u32 animFileId;
} PanelObjectResourceConfig;

typedef struct BackgroundContainer {
    u8 entryList[0xc];
    void *entryRecords;
    void *spriteRecords;
    void *tagRecords;
    u8 reserved18[0x18];
    BackgroundContainerConfig config;
    u8 reserved44[8];
} BackgroundContainer;

typedef char BackgroundContainerConfigMustBe20Bytes[
    sizeof(BackgroundContainerConfig) == 20 ? 1 : -1];
typedef char PanelObjectResourceConfigMustBe24Bytes[
    sizeof(PanelObjectResourceConfig) == 24 ? 1 : -1];
typedef char BackgroundContainerMustBe76Bytes[
    sizeof(BackgroundContainer) == 0x4c ? 1 : -1];
typedef char BackgroundContainerCapacityOffsetMustBe48Bytes[
    (u32)&((BackgroundContainer *)0)->config == 0x30 ? 1 : -1];

void InitBackgroundContainer(BackgroundContainer *container,
                             BackgroundContainerConfig *config);

extern const BackgroundContainerConfig gRecordSelectionBgConfig;
extern const PanelObjectResourceConfig gRecordSelectionObjConfig;

#endif
