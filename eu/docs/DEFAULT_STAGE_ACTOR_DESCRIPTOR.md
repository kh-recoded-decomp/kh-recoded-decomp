# Default stage-actor descriptor

`gDefaultStageActorDescriptor` corrects the former gNearestEntrySyncHandlers identity at ov001:020a0260. CreateStageActor selects this address when its descriptor input is NULL; InitStageObjectActor also stores it as the actor descriptor. This is one existing 52-byte allocation, not thirteen independent handlers or a table indexed by target kinds.

The definition now reuses the existing StageActorDescriptor type. Four scalar words precede nine method words. Native size and method offsets are checked at compile time for the DS target:

| Offset | Value | Actual consumer |
|---|---|---|
| +0x00 | 0 | Low halfword copied to the actor/spawn-info prefix |
| +0x04 | 0 | Low byte copied to actor kind |
| +0x08 | 0 | ORed into actor flags |
| +0x0c | 0 | ORed into actor attributes |
| +0x10 | StageActor_DefaultInitNoop | Direct constructor invocation |
| +0x14 | SyncNearestEntryPosition | Existing placement method |
| +0x18 | StageActor_DefaultUpdateNoop | Copied to actor-slot +0x1cc |
| +0x1c | StageActor_DefaultDrawNoop | Copied to actor-slot +0x1c8 |
| +0x20..+0x30 | Five NULL words | No new tail-field interpretation |

The MAIN invokers prove the update and draw channels. ActorRegistry_ForEachCallback invokes slot+0x1cc with (slot, argument); UpdateActorSlotsAndBillboards invokes slot+0x1c8 with (slot, pass). The descriptor member at +0x1c is therefore named draw, correcting postUpdate. Other descriptors retain their positional initializers and exact layout. The similarly spelled postUpdate member of the separate overlay-052 Entity type is unrelated and unchanged.

The physical source path stays [gNearestEntrySyncHandlers.c](../src/overlays/ov001/data/tables/gNearestEntrySyncHandlers.c), preserving its configured owner. The [common descriptor header](../src/overlays/ov001/StageActorTables.h) declares the new identity. There is no second allocation, object movement, added callback or changed pointer value. All four method relocations retain their original offsets and targets.

These are native 32-bit layout assertions, not certification of a host ABI. The empty methods keep void(void) implementations even though native invokers supply arguments; their erased interface is documented in [the actor-hook contract](DEFAULT_STAGE_ACTOR_BODY_SOUND.md). A port must reconcile such declarations consistently rather than copying the native address views directly into host headers.

## Byte-exact validation

Both affected official function checks pass. All 18 complete production objects preserve allocated bytes/alignment, symbol offsets/sizes and relocation targets/types/addends. A fresh gate passes all 108 native modules with every module hash unchanged. The definition retains exactly 52 bytes and four method relocations.

Run from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/CreateStageActor.c CreateStageActor --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InitStageObjectActor.c InitStageObjectActor --thumb
bash tools/gate.sh
```
