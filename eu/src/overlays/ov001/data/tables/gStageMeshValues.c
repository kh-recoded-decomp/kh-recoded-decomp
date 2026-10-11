#include "src/overlays/ov001/StageMeshValues.h"

extern const char sOv001_Slide_0209ea34[];
extern const char sOv001_Sicon_0209ea3c[];
extern const char sOv001_Nohit_0209ea44[];
extern const char sOv001_Nocam_0209ea4c[];
extern const char sOv001_Ladder_0209ea54[];
extern const char sOv001_W5rock_0209ea5c[];
extern const char sOv001_Trcola_0209ea64[];
extern const char sOv001_Trcolb_0209ea6c[];
extern const char sOv001_Nocatch_0209ea74[];
extern const char sOv001_2dblock_0209ea7c[];

/* Values assigned to named meshes when opening the stage model group. */
const NamedMeshValue gStageMeshValues[10] = {
    {sOv001_Nohit_0209ea44, 2},
    {sOv001_Nocatch_0209ea74, 3},
    {sOv001_Nocam_0209ea4c, 4},
    {sOv001_Slide_0209ea34, 5},
    {sOv001_Sicon_0209ea3c, 6},
    {sOv001_Trcola_0209ea64, 0x204},
    {sOv001_Trcolb_0209ea6c, 0x60204},
    {sOv001_Ladder_0209ea54, 7},
    {sOv001_W5rock_0209ea5c, 9},
    {sOv001_2dblock_0209ea7c, 10}
};
