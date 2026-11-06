# Current board-node code: recovered owner and writers

**GetCurrentBoardNodeCode** (formerly `func_ov032_020bb828`, ov032:020bb828). It returns the signed code for the selected node of the shared six-node board. It is not a Boolean lock getter and does not return the mapped rank. The name leaves the gameplay names of the individual codes unresolved.

The missing owner chain is now demonstrated: InitResultsScene allocates/clears the 0x90-byte SessionBuffer10; CreateBoardScreen takes that slot as its board cursor; InitSceneOverlayState takes the same slot as its route/challenge context. The pointer is persistent session storage, not either screen task-work allocation.

| Context offset | Proven native role |
|---|---|
| +0x55 | Signed current node index; initial value is the generated first occupied node. |
| +0x56..+0x5b | Six signed node codes. |
| +0x6b | Unsigned mask used to choose code = set-bit index +1. |

Overlay024 RerollBoardSlots clears the six codes to 0. PlaceBoardBonuses writes a selected mask-bit index plus1 only into an occupied node whose current code is 0. Overlay032 UpdateChallengeScene later clears the selected code to 0 when the all-events condition has completed its timer. Those writers explain both the persistent per-node selector and its pending/cleared lifecycle without inheriting the private slotItems/slotBonuses/slotLocked names.

SetupStageParams copies StageEntry byte+0x1e into context+0x6b; its special branch overwrites that mask with 1. In all 135 original ROM stage records (27 sentinels), the nonsentinel masks are 01,02,03,04,08,0a,0b. Therefore the recovered generation paths produce nonzero codes 1..4, plus 0 from initialization/completion. The general u8-mask algorithm can represent more values; this review does not impose a new enum range or runtime guard.

The three existing consumers use the same code differently: GetSessionRankValue maps 0..4 to 0,3,2,0,1; InitializeActorStats forwards it to the actor variant field; RemapGroupMemberId uses nonzero as one remap condition. The separate lock mask is context+0x5f. A universal rank, variant or lock name would lose those distinctions.

The leaf remains exactly `s32 GetCurrentBoardNodeCode(void)`: signed byte at+0x55, then signed byte at+0x56+index, sign-extended to s32. Preserve both LDRSB operations and the absence of NULL, negative-index and range checks. The rename preserves parameters, signed loads, source body and layout.

The JSON records exact EU bank/address/mode/extent and current wrapper/shared-source paths for the constructors, writers and known consumers. Direct NDS extraction confirms their complete function hex against the existing index. The owner and writer evidence comes from Re:coded itself; no Days layout assumption is needed.


## Active source evidence

- [InitResultsScene](../src/overlays/ov034/calls/InitResultsScene.c).
- [CreateBoardScreen](../src/overlays/ov024/calls/CreateBoardScreen.c).
- [InitSceneOverlayState](../src/overlays/ov032/calls/InitSceneOverlayState.c).
- [RerollBoardSlots](../src/overlays/ov024/calls/RerollBoardSlots.c).
- [PlaceBoardBonuses](../src/overlays/ov024/calls/PlaceBoardBonuses.c).
- [UpdateChallengeScene](../src/overlays/ov032/calls/UpdateChallengeScene.c).
- [SetupStageParams](../src/overlays/ov034/calls/SetupStageParams.c).
- [GetCurrentBoardNodeCode](../src/overlays/ov032/calls/GetCurrentBoardNodeCode.c).

## Byte-exact validation

All four official checks pass. The four complete production objects retain allocated bytes and alignment, symbol offsets/sizes and relocation targets/types/addends after the rename. A fresh gate passes all 108 modules with identical hashes. Run from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov032/calls/GetCurrentBoardNodeCode.c GetCurrentBoardNodeCode --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSessionRankValue.c GetSessionRankValue --thumb
python tools/verify_idx.py src/overlays/ov001/calls/InitializeActorStats.c InitializeActorStats --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RemapGroupMemberId.c RemapGroupMemberId --thumb
bash tools/gate.sh
```
