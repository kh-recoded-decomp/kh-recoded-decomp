# Default stage-actor hooks and periodic body sound

`StageActor_DefaultInitNoop` (ov001:0208f6e0), `StageActor_DefaultUpdateNoop` (0208f708) and `StageActor_DefaultDrawNoop` (0208f70c) belong to the fallback descriptor selected by CreateStageActor when its descriptor argument is NULL. Its existing DATA name, gNearestEntrySyncHandlers, is misleading: the 52-byte object at 020a0260 is a descriptor with four scalar words and nine method words, not a homogeneous handler-index table. Its declaration and DATA name are handled separately from this function-name block.

The constructor invokes descriptor+0x10 with the actor in R0, copies +0x18 to actor-slot+0x1cc, and copies +0x1c to slot+0x1c8. The actual MAIN invokers establish the latter channels: ActorRegistry_ForEachCallback invokes +0x1cc as (slot, argument); UpdateActorSlotsAndBillboards invokes +0x1c8 as (slot, 0/1) during drawing passes. Historical postUpdate or private field labels are not evidence of a different role. Other descriptors can perform game logic on the draw channel.

Each default is only BX LR. It reads no input and changes no memory. Keep its existing void(void) implementation and distinct nonnull identity; the caller's arguments are ignored, and residual R0 has no status meaning. No synthetic parameters are added.

`EncodeActorBodySoundKind` (02089a1c) maps 0 to 1, 1 to 2, 2 to 5, and every other value to value+4. `ConfigureActorPeriodicBodySound` corrects the old ConfigureActorPeriodicBodySound label. Its three actor words have real consumers: +4 is the period, +8 is the encoded sound kind, and +0xc is the alternating variant toggle.

The period is (track-0 duration in fx32 / signed actor-slot step) / 2, using signed integer division with truncation toward zero. The actor ID is narrowed to 16 bits for the slot lookup. The configuration sets actor flag 0x80, but does not clear 0x100. Actor_StepPeriodicAnimEvent therefore processes queued animation cues when 0x100 is set; otherwise it plays body sound when the integral frame is nonzero and divisible by the period. Preserve the calculation order, absent period clamp and absent frame deduplication.

PlayActorBodySound chooses bank offset 5 for encoded kind 2, offset 4 for kind 3 and offset 0 otherwise. It uses the previous toggle, then stores whether that toggle was zero, alternating variants from the configured initial zero. Asset meanings remain unknown. ClearActorTimerFields clears flags 0x180 and these three words. No original sound enum, clamp or dialog behavior is inferred.

`StageActor_GroupCommandResetNoop` (02090f28) returns literal 1 without reading input or touching memory. ResetGroupCommandState forwards the resolved group leader in R0, calls it, then overwrites R0 before selecting command state 6 and clearing reset-pending. That result is ignored; it is not VM advancement or acknowledgement. The existing int(void) definition remains intact.


## Active EU sources

- [StageActor_DefaultInitNoop](../src/overlays/ov001/auto/StageActor_DefaultInitNoop.c).
- [StageActor_DefaultUpdateNoop](../src/overlays/ov001/auto/StageActor_DefaultUpdateNoop.c).
- [StageActor_DefaultDrawNoop](../src/overlays/ov001/auto/StageActor_DefaultDrawNoop.c).
- [EncodeActorBodySoundKind](../src/overlays/ov001/calls/EncodeActorBodySoundKind.c).
- [StageActor_GroupCommandResetNoop](../src/overlays/ov001/auto/StageActor_GroupCommandResetNoop.c).
- [ConfigureActorPeriodicBodySound](../src/overlays/ov001/calls/ConfigureActorPeriodicBodySound.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/auto/StageActor_DefaultInitNoop.c StageActor_DefaultInitNoop --thumb
python tools/verify_idx.py src/overlays/ov001/auto/StageActor_DefaultUpdateNoop.c StageActor_DefaultUpdateNoop --thumb
python tools/verify_idx.py src/overlays/ov001/auto/StageActor_DefaultDrawNoop.c StageActor_DefaultDrawNoop --thumb
python tools/verify_idx.py src/overlays/ov001/calls/EncodeActorBodySoundKind.c EncodeActorBodySoundKind --thumb
python tools/verify_idx.py src/overlays/ov001/auto/StageActor_GroupCommandResetNoop.c StageActor_GroupCommandResetNoop --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ConfigureActorPeriodicBodySound.c ConfigureActorPeriodicBodySound --thumb
bash tools/gate.sh
```
