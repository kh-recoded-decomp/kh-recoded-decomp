/* BK9E ARM9, 32-bit pointers. Partial layouts describe observed fields only.
 * The reserved regions and total sizes are not claims about the original types.
 * Evidence and confidence live in analysis/actor_model.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct ModelResource {
    u8 unknown_000[0x08];
    u32 materialsRelativeOffset;
    u8 unknown_00c[0x0c];
    u8 materialCount;
} ModelResource;

typedef struct ActorNode {
    u8 unknown_000[0x7c];
    ModelResource *modelResource;
    u8 unknown_080[0x34];
    VecFx32 offset;
} ActorNode;

typedef struct ActorStorage {
    u8 unknownHeader[0x10];
    ActorNode actor;
} ActorStorage;

typedef struct ActorRegistry {
    u8 unknownHeader[0x20];
    ActorStorage *actors[1]; /* variable-length array; actual capacity unconfirmed */
} ActorRegistry;

typedef struct ScriptOperand {
    short type;
    u8 undecodedPayload[6];
} ScriptOperand;
