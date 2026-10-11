#ifndef KH_RECODED_G3D_COMMAND_TEMPLATES_H
#define KH_RECODED_G3D_COMMAND_TEMPLATES_H
#include "nitro/fx_types.h"

/* Packed FIFO opcodes: POP, MODE, LOAD_4x3, SCALE. */
#define G3D_TEMPLATE_BILLBOARD_OPCODES 0x1b171012U
#define G3D_TEMPLATE_TEXIMAGE_OPCODE 0x2aU

typedef struct CommandMatrix33 { fx32 m[3][3]; } CommandMatrix33;
typedef struct CommandMatrix44 { fx32 m[4][4]; } CommandMatrix44;
typedef struct TextureImageCommandWords {
    u32 projectionParam;
    u32 environmentOpcode;
} TextureImageCommandWords;
typedef struct BillboardRestoreModeParams {
    u32 popCount;
    u32 matrixMode;
} BillboardRestoreModeParams;

/* Contiguous FIFO packet fields in the original .data layout: opcodes,
 * POP/MODE arguments, 4x3 matrix (basis plus translation), then scale.
 * Keep this order in the delinks.
 */
extern u32 gProjectionTextureImageOpcode;
extern TextureImageCommandWords gProjectionTextureImageWords;
extern u32 gEnvironmentTextureImageParam;
extern CommandMatrix44 gProjectionTextureMatrix;
extern u32 gBillboardCommandOpcodes;
extern BillboardRestoreModeParams gBillboardRestoreModeParams;
extern CommandMatrix33 gBillboardBasis;
extern VecFx32 gBillboardTranslation;
extern VecFx32 gBillboardScale;
extern u32 gRollBillboardCommandOpcodes;
extern BillboardRestoreModeParams gRollBillboardRestoreModeParams;
extern CommandMatrix33 gRollBillboardBasis;
extern VecFx32 gRollBillboardTranslation;
extern VecFx32 gRollBillboardScale;
#endif
