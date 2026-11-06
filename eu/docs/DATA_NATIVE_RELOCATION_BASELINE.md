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

## Title/panel and text-format block

The subsequent 65-symbol title/panel/format block has 52 affected function
checks. 51 pass; the same-path original-source control reproduces the remaining
verdict for `RefreshStatusMenuData` (ov073:020c1ed4, Thumb, 2852 bytes).
Its original index records two internal `BL` instructions as relocations to
local labels: +0x14 calls 0x020c29ee and +0x48 calls 0x020c29b0. Both targets
are inside this function's native extent. The compiler encodes these local
calls directly, without corresponding external ELF relocations.

The original instruction words are `00 f0 81 fd` and `00 f0 48 fd` in both
versions. Preserve the function and verify the original local-call metadata
before repairing the index. An eventual index correction must compare these
instruction bytes directly; it must not mask or ignore their contents.

```sh
python tools/verify_idx.py src/overlays/ov073/calls/RefreshStatusMenuData.c RefreshStatusMenuData --thumb
```

## Field/session global block

The 27-global field/session block checks 777 affected functions. 768 standalone
checks pass. The following nine reproduce their original relocation-map
verdicts with the preserved source graph, headers and symbol configuration
restored at the actual compilation paths. Their expected symbolic callback
slots are still emitted as the same numeric pointer words. The current
function instructions, pointer values and resolved targets are unchanged.

| Function | EU identity | Expected relocation / existing literal word |
|---|---|---|
| [InitEventTriggerScene](../src/overlays/ov001/calls/InitEventTriggerScene.c) | ov001:02068efc | +0x4c `WaitForEventTriggerActivation` (`0x02068f4d`) |
| [InitModeHandlerContext](../src/overlays/ov001/calls/InitModeHandlerContext.c) | ov001:0207a458 | +0x44 `RunActiveModeHandler` (`0x0207a4d1`) |
| [InitOverlayObjectSystem](../src/overlays/ov001/calls/InitOverlayObjectSystem.c) | ov001:02088278 | +0x58 `func_ov001_020882d4` (`0x020882d5`) |
| [InitScreenFadeContext](../src/overlays/ov001/calls/InitScreenFadeContext.c) | ov001:0206a0a0 | +0x74 `SelectScreenFadeHandler` (`0x0206a139`) |
| [SelectScreenFadeHandler](../src/overlays/ov001/calls/SelectScreenFadeHandler.c) | ov001:0206a138 | +0x3c `ScreenFadeInStep` (`0x0206a185`); +0x40 `ScreenFadeOutStep` (`0x0206a209`); +0x44 `StepBrightnessFadeIn` (`0x0206a291`); +0x48 `StepBrightnessFade` (`0x0206a365`) |
| [ShutdownSceneWork](../src/overlays/ov001/calls/ShutdownSceneWork.c) | ov001:0206ae58 | +0x24 `RefreshActiveMenuObjects` (`0x0206c46d`) |
| [SubScene9_Create_02066c80](../src/overlays/ov001/calls/SubScene9_Create_02066c80.c) | ov001:02066c80 | +0x1c `FinishFadeTween` (`0x02066cb5`) |
| [SubScene9_Create_02068c0c](../src/overlays/ov001/calls/SubScene9_Create_02068c0c.c) | ov001:02068c0c | +0x2c `StartTimerState` (`0x02068c51`) |
| [TryShutdownActorSystem](../src/overlays/ov001/calls/TryShutdownActorSystem.c) | ov001:02088330 | +0x78 `func_ov001_020882d4` (`0x020882d5`) |

These constructors/transitions need a separate source cleanup using their
real callback symbols and demonstrated ABI. `func_ov001_020882d4` retains its
numeric identity while its precise callback contract is under review. No
parameter or callback role is added merely to force relocation emission.

## Early overlay context/constant block

The 44-symbol early-overlay block checks 248 affected functions. 247 standalone
checks pass. The preserved full-source-graph control at the actual compilation
path reproduces the same relocation-map verdict for `InstallResultPanelCallbacks`
(ov015:02079d6c, ARM, 96 bytes): its callback word at +0x50 is the literal
`0x02079d08`, while the original index expects `PlaySoundOnPanelEntryMatch`.
Both identify the existing ARM callback at ov015:02079d08. The rename changes
neither the word nor the callback registration behavior; a separate cleanup
must use the demonstrated callback signature before replacing the literal.

```sh
python tools/verify_idx.py src/overlays/ov015/calls/InstallResultPanelCallbacks.c InstallResultPanelCallbacks
```

All affected production object layouts and instructions remain unchanged, and
the fresh full-module gate passes all 108 modules with identical hashes.
