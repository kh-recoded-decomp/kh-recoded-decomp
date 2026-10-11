#include "src/overlays/ov101/ListMenuData.h"

#pragma explicit_zero_data on

extern char sOv101_UiReportTextLanguageCharacterSZ_020c1a54[];
extern char sOv101_UiReportTextLanguageCharacterDetailSZ_020c1a74[];
const char *gListTextArchivePaths[4] = {
    sOv101_UiReportTextLanguageCharacterSZ_020c1a54,
    sOv101_UiReportTextLanguageCharacterDetailSZ_020c1a74,
    NULL, sListStoryTextPath,
};
