# Standalone relocation checks at the DATA naming baseline

The 64-symbol scene/menu DATA block checked all 443 affected production
functions individually. 440 standalone checks pass. The other three produce
the same relocation-map verdict with both the preserved original source and
the renamed source, compiled at the actual source path with its normal flags.
The original objects and every source version are retained in the local
experiment record.

All 498 affected production objects retain their allocated section bytes and
alignment, symbol offsets/sizes and relocation records after accounting for
the reviewed symbol renames. All 108 linked module hashes are identical, and
the full official gate passes 108/108. The three standalone discrepancies
remain visible; neither the original index nor the official verifier was
changed for this naming block.

Offsets below are relative to the native function start. All three functions
are Thumb.

| EU identity and source | Standalone reference discrepancy | Evidence boundary and next check |
|---|---|---|
| ov025:020b5e44, 104 bytes; [RefreshTagCallbacksAndSchedule.c](../src/overlays/ov025/calls/RefreshTagCallbacksAndSchedule.c) | At +0x60 the original index expects `ApplySubBgScroll`; the C emits literal `0x020b5821`. At +0x64 it expects `UpdateMenuScreen`; the C emits `0x020b5f29`. | These are the matching Thumb-tagged callback addresses. `InvokeForChannelOrBoth` passes the first callback through registration, and the constructor returns the second as its next update function. A separate source cleanup can replace the numeric addresses with these real symbols, preserving the native ABI and all linked bytes. |
| ov040:020bcd6c, 260 bytes; [FinishAreaSceneLoad.c](../src/overlays/ov040/calls/FinishAreaSceneLoad.c) | At +0xfc the index expects `gBarGaugeClassDescriptor`; the C emits descriptor literal `0x020bc4e8`. | That descriptive label is configured in overlay 035. The consumer is in overlay 040, so the shared RAM address alone does not prove the descriptor owner. Establish the actual loader/lifetime and descriptor before replacing this native pointer literal. |
| ov041:020c18ec, 1100 bytes; [SpawnStageEntryActor.c](../src/overlays/ov041/calls/SpawnStageEntryActor.c) | The object has function-pointer relocations at +0x344, +0x348, +0x354 and +0x358 which the original index omits. Their ROM words are `0x020c21f5`, `0x020c2325`, `0x020c23ed` and `0x020c2451`. | The targets are `UpdateStageEntryAnimation`, `DrawStageEntryModels`, `UpdateStageShadowActor` and `DrawTrackedStageShadow`. Preserve the current C callbacks and verify their native installation/dispatch and bank-qualified ROM metadata before repairing the index. |

The fourth argument of `InvokeForChannelOrBoth` is a signed channel selector;
-1 registers in both channels. Its historical `duration` parameter spelling
does not establish a timing contract. The third word reaches the callback slot
invoked by the VBlank handler.

To reproduce the current standalone verdicts, run from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov025/calls/RefreshTagCallbacksAndSchedule.c RefreshTagCallbacksAndSchedule --thumb
python tools/verify_idx.py src/overlays/ov040/calls/FinishAreaSceneLoad.c FinishAreaSceneLoad --thumb
python tools/verify_idx.py src/overlays/ov041/calls/SpawnStageEntryActor.c SpawnStageEntryActor --thumb
bash tools/gate.sh
```

The first three commands report the reference discrepancies above. The final
command checks complete linked binaries against the original EU modules.
