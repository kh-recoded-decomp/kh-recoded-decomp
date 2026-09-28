typedef int s32;
typedef unsigned int u32;
typedef volatile u32 REGType32v;

#define reg_G3_MTX_MODE       (*(REGType32v *)0x4000440)
#define reg_G3_MTX_POP        (*(REGType32v *)0x4000448)
#define reg_G3_MTX_IDENTITY   (*(REGType32v *)0x4000454)

extern int G3X_GetMtxStackLevelPV(int *level);
extern int G3X_GetMtxStackLevelPJ(int *level);

void G3X_InitMtxStack_02006a68(void) {
    volatile unsigned int *graphicsStatus = (volatile unsigned int *)0x4000600;
    int projectionVectorStackLevel;
    int projectionJointStackLevel;

    *graphicsStatus = *graphicsStatus | 0x8000;

    while (G3X_GetMtxStackLevelPV(&projectionVectorStackLevel) != 0) {}
    while (G3X_GetMtxStackLevelPJ(&projectionJointStackLevel) != 0) {}

    reg_G3_MTX_MODE = 3;
    reg_G3_MTX_IDENTITY = 0;
    reg_G3_MTX_MODE = 0;

    if (projectionJointStackLevel != 0) {
        reg_G3_MTX_POP = projectionJointStackLevel;
    }

    reg_G3_MTX_IDENTITY = 0;
    reg_G3_MTX_MODE = 2;
    reg_G3_MTX_POP = projectionVectorStackLevel;
    reg_G3_MTX_IDENTITY = 0;
}
