# Standalone relocation checks at the DATA naming baseline

## Current validation state

All 21 standalone cases recorded below now pass fresh official checks. Eight
native metadata corrections and thirteen C reference cleanups preserve every
original instruction and linked word. The final gate passes all 108 modules
with identical hashes.

[NATIVE_RELOCATION_METADATA.md](NATIVE_RELOCATION_METADATA.md) documents the
ROM-derived metadata scope and explicit builder mode.
[NATIVE_CALLBACK_REFERENCE_CONTRACTS.md](NATIVE_CALLBACK_REFERENCE_CONTRACTS.md)
records the real callback, descriptor and key identities and the strict
seventeen-word equivalence proof. No comparator tolerance is changed.

The following sections retain historical block counts and original-source
control verdicts; they describe the former baseline, not unresolved current
standalone failures.


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

The first three commands now report MATCH. The table preserves the original
discrepancies for audit; their repairs are linked under Current validation
state above. The final command checks complete linked binaries against the
original EU modules.

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

## Layout and stage-storage block

The 86-symbol layout/stage block checks 102 affected functions. 100 standalone
checks pass; the same-path original-source controls reproduce two verdicts.
`SpawnStageEntryActor` retains the four previously documented callback
relocations absent from its original map. `ModelRenderCallbackKindC`
(ov041:020c2690, Thumb, 72 bytes) emits a call relocation at +0x38 to
`NNS_G3dGetCurrentMtx` that its original map omits. The native instruction at
020c26c8 is `57 f7 24 eb`, a BLX to the existing ARM function 02019d14.
Its separate DATA relocation at +0x44 is present in both maps.

```sh
python tools/verify_idx.py src/overlays/ov041/calls/ModelRenderCallbackKindC.c ModelRenderCallbackKindC --thumb
```

The missing call classification needs a separate metadata repair based on the
native instruction. This naming block preserves all 163 complete affected
objects and all 108 freshly linked module hashes.

## Actor, matrix and slot-template block

The 73-symbol actor/matrix/template block checks 69 affected functions. 67
standalone checks pass; two reproduce their original same-path verdicts.

| Function | Native identity/extent | Reference map discrepancy |
|---|---|---|
| `DrawMatrixMenu` | ov075:020c910c, Thumb, 3872 bytes | Internal BLs at +0x322, +0x5d4 and +0xe04 target 020c9f14, 020c9efa and 020c9686 within the same function; the index records external relocations to local labels. |
| `UpdateMatrixEventAnimation` | ov075:020ca078, Thumb, 2520 bytes | Internal BLs at +0x0e and +0x10a both target local 020caa0e; DATA word +0x9bc is 020d143d, emitted as `sMatrixNavigationGraph` with its native addend but represented by an address string in the index. |

The internal call bytes remain directly comparable and must stay unmasked in
an eventual metadata repair. The odd navigation DATA address does not establish
a Thumb callback; check its actual table definition and interior offset.

```sh
python tools/verify_idx.py src/overlays/ov075/calls/DrawMatrixMenu.c DrawMatrixMenu --thumb
python tools/verify_idx.py src/overlays/ov075/calls/UpdateMatrixEventAnimation.c UpdateMatrixEventAnimation --thumb
```

The naming block preserves all 120 complete affected objects and all 108
freshly linked module hashes. Original-source controls retain nonzero verifier
verdicts; these are not reported as individual MATCH results.

## Engine and platform storage block

The 98-symbol engine/platform block checks 282 affected functions. 280
standalone checks pass; two reproduce their preserved original-source-graph
verdicts at the actual paths:

| Function | Native identity/extent | Internal BL offsets recorded as external relocations |
|---|---|---|
| `HandleResultsInput` | ov034:020bd130, Thumb, 2656 bytes | +0x6e targets local 020bdb8c. |
| `RefreshResultsScreen` | ov034:020bb598, Thumb, 6264 bytes | +0x30, +0x92, +0x11e, +0xa42, +0xc76, +0xcaa, +0x1498 and +0x1676 target labels inside the same function. |

The maps also spell native DATA references using interior addresses or field
aliases where the object uses its aggregate base and addend. Those word values
remain unchanged; differing spellings alone do not establish an independent
failure. The internal BL bytes must remain fully compared during the separate
metadata repair.

```sh
python tools/verify_idx.py src/overlays/ov034/calls/HandleResultsInput.c HandleResultsInput --thumb
python tools/verify_idx.py src/overlays/ov034/calls/RefreshResultsScreen.c RefreshResultsScreen --thumb
```

All 348 complete affected objects and all 108 freshly linked module hashes are
unchanged. The official SDK verifiers separately reproduce 160 IRQ-thread-switch
cases and 120 exception-display cases against the ROM instructions; only the
source hashes in those two receipts are regenerated after their alias changes.

## Movie and game-service block

The 103-identity game-service block checks 410 affected functions. 405
standalone checks pass; five reproduce their original-source-graph verdicts.
Four are documented above: `HandleResultsInput`, `RefreshStatusMenuData`,
`DrawMatrixMenu` and `UpdateMatrixEventAnimation`.

The additional case is `DrawMatrixCellGlyph` (ov075:020c7fc8, Thumb, 2248
bytes). Its +0x6c instruction is `00 f0 2a fc`, a BL to local 020c888c inside
the same function. The reference map records it as an external relocation;
the compiler resolves it directly. An eventual metadata repair must compare
all four instruction bytes without masking them.

```sh
python tools/verify_idx.py src/overlays/ov075/calls/DrawMatrixCellGlyph.c DrawMatrixCellGlyph --thumb
```

The fresh gate passes all 108 modules with identical hashes. All 474 complete
affected production objects preserve allocated bytes, alignment, symbol
layouts and relocation records, including the actual compiled 24-byte movie
prompt-pointer table and its six native relocations.

## Board, results and text-window block

The 75-identity board/results/text block checks 144 affected functions. 141
standalone checks pass; the original-source-graph controls reproduce the
known `HandleResultsInput` and `RefreshResultsScreen` verdicts and one further
raw-literal case: `DestroyResultsGraphics` (ov034:020bce10, Thumb, 96 bytes).
Its +0x54 word is `0x020c0f10`, where the original map expects the existing
`sOv034_SYSAREAMENU_020c0f10` storage. That 16-byte name storage identifies
`SYS_AREA_MENU`; initialization registers the same name and destruction
unregisters it. A separate source cleanup must use this real storage without
changing the existing registration/channel behavior.

```sh
python tools/verify_idx.py src/overlays/ov034/calls/DestroyResultsGraphics.c DestroyResultsGraphics --thumb
```
