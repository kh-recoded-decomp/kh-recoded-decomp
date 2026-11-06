# Overlay058 scene resources and inline storage

These 16 DATA/BSS names describe overlay058's scene resources, placement constants, cached entry-zero actor reference and inline scene control/model storage. The large BSS state is spread across original physical objects. Its storage is kept intact; the documentation combines only the partial views demonstrated by actual consumers, without inventing a new complete public struct.

## Identity and stable source table

| EU identity | Original identifier | Descriptive identifier | Physical bytes | Stable source | Direct consumer |
|---|---|---|---:|---|---|
| ov058:20d896c | `data_ov058_020d896c` | `gOverlay058EnemyAiCrossAxis` | 12 | `eu/src/ov058/data/Rodata_ov058_020d896c.c` | `eu/src/overlays/ov058/calls/UpdateEnemyCombatAi.c` |
| ov058:20d8978 | `data_ov058_020d8978` | `gOverlay058StateChangeEffectOffsets` | 24 | `eu/src/ov058/data/Rodata_ov058_020d896c.c` | `eu/src/overlays/ov058/calls/ChangeEnemyState.c` |
| ov058:20d8990 | `data_ov058_020d8990` | `gOverlay058EnemySidePlacementOffsets` | 36 | `eu/src/ov058/data/Rodata_ov058_020d896c.c` | `eu/src/overlays/ov058/calls/SnapEnemyBesidePlayer_020d5468.c` |
| ov058:20d89b4 | `data_ov058_020d89b4` | `gOverlay058SceneSlotAngleOffsets` | 8 | `eu/src/ov058/data/Rodata_ov058_020d89b4.c` | `eu/src/overlays/ov058/calls/GetSceneSlotAngle.c` |
| ov058:20d89bc | `data_ov058_020d89bc` | `gOverlay058ApproachOffset` | 12 | `eu/src/ov058/data/Rodata_ov058_020d89b4.c` | `eu/src/overlays/ov058/calls/ComputeApproachTarget.c` |
| ov058:20d89c8 | `data_ov058_020d89c8` | `gOverlay058AnchorPlacementOffset` | 12 | `eu/src/ov058/data/Rodata_ov058_020d89c8.c` | `eu/src/overlays/ov058/calls/StartAnchorSequence.c` |
| ov058:20d89d4 | `data_ov058_020d89d4` | `gOverlay058RigPlayerOffsets` | 36 | `eu/src/ov058/data/Rodata_ov058_020d89c8.c` | `eu/src/overlays/ov058/calls/PlaceRigAtPlayerOffset.c` |
| ov058:20d8a40 | `data_ov058_020d8a40` | `gOverlay058EntryZeroActor` | 4 | `eu/src/overlays/ov058/data/bss/Bss_ov058_020d8a40.c` | `eu/src/overlays/ov058/calls/UpdateEnemyCombatAi.c` |
| ov058:20d8a44 | `data_ov058_020d8a44` | `gOverlay058SceneControlHead` | 8 | `eu/src/overlays/ov058/data/bss/Bss_ov058_020d8a40.c` | `eu/src/overlays/ov058/calls/UpdateSceneIntroSequence.c` |
| ov058:20d8a4c | `data_ov058_020d8a4c` | `gOverlay058SceneCenter` | 12 | `eu/src/overlays/ov058/data/bss/Bss_ov058_020d8a40.c` | `eu/src/overlays/ov058/calls/ComputeApproachTarget.c` |
| ov058:20d8a58 | `data_ov058_020d8a58` | `gOverlay058SceneControlTail` | 40 | `eu/src/overlays/ov058/data/bss/Bss_ov058_020d8a40.c` | `eu/src/overlays/ov058/calls/LoadSceneModelResources.c` |
| ov058:20d8a80 | `data_ov058_020d8a80` | `gOverlay058SceneAnimatedModel` | 312 | `eu/src/overlays/ov058/data/bss/Bss_ov058_020d8a40.c` | `eu/src/overlays/ov058/calls/LoadSceneModelResources.c` |
| ov058:20d8bb8 | `data_ov058_020d8bb8` | `gOverlay058ArchiveEffect2Model` | 308 | `eu/src/overlays/ov058/data/bss/Bss_ov058_020d8bb8.c` | `eu/src/overlays/ov058/calls/LoadSceneModelResources.c` |
| ov058:20d8cec | `data_ov058_020d8cec` | `gOverlay058ArchiveEffect3Models` | 924 | `eu/src/overlays/ov058/data/bss/Bss_ov058_020d8bb8.c` | `eu/src/overlays/ov058/calls/LoadSceneModelResources.c` |
| ov058:20d9088 | `data_ov058_020d9088` | `gOverlay058ArchiveEffect4ModelPrefix` | 164 | `eu/src/overlays/ov058/data/bss/Bss_ov058_020d9088.c` | `eu/src/overlays/ov058/calls/LoadSceneModelResources.c` |
| ov058:20d912c | `data_ov058_020d912c` | `gOverlay058SceneStorageTail` | 308 | `eu/src/overlays/ov058/data/bss/Bss_ov058_020d9088.c` | `eu/src/overlays/ov058/calls/RunAreaBlastHitScan.c` |

## One cached actor reference and one inline scene state

gOverlay058EntryZeroActor is the separate four-byte reference at 020d8a40. UpdateEnemyCombatAi assigns GetBoundedEntryField(0) before using the actor in distance and AI decisions. Other facing/request/tracking consumers read the same reference. The assignment proves the cached slot, not ownership transfer, permanent nonnull state or a separately allocated player actor in BSS.

The inline scene state begins at 020d8a44 and occupies the contiguous physical range through 020d9260. Its exact physical fragments are:

| Physical fragment | Native range | Demonstrated view |
|---|---|---|
| gOverlay058SceneControlHead | [020d8a44,020d8a4c), 8 B | signed intro-mode byte; timer word at logical +4 |
| gOverlay058SceneCenter | [020d8a4c,020d8a58), 12 B | inline VecFx32 center at logical +8 |
| gOverlay058SceneControlTail | [020d8a58,020d8a80), 40 B | previous center; heading/speed; sequence state fields; archive reference at logical +0x38 |
| gOverlay058SceneAnimatedModel | [020d8a80,020d8bb8), 312 B | inline model initialized by InitAnimatedModel and torn down through TeardownBigObj |
| gOverlay058ArchiveEffect2Model | [020d8bb8,020d8cec), 308 B | archive file-index 2 model |
| gOverlay058ArchiveEffect3Models | [020d8cec,020d9088), 924 B | three archive file-index 3 models with stride 0x134 |
| gOverlay058ArchiveEffect4ModelPrefix | [020d9088,020d912c), 164 B | first 0xa4 bytes of the archive file-index 4 model |
| gOverlay058SceneStorageTail | [020d912c,020d9260), 308 B | remaining effect-4 model bytes, hit-scan slots, camera path and later intro controls |

These are inline objects and fragments, not an array of pointers. LoadSceneModelResources and ReleaseSceneModelResources use the same addresses for model initialization/drawing/resource release. The global state itself is not freed by the naming change. Resource handles and allocations inside the models/path retain the actual helper contracts; no ownership transfer is inferred merely from the global names.

## Tail subviews and camera path

The effect-4 model begins at 020d9088 and has the same 0x134 logical stride as the other archive models, so it continues 144 bytes into the next physical fragment. The first 12 bytes of gOverlay058SceneStorageTail are its +0xa4 vector; RunAreaBlastHitScan reads that exact vector as the sphere center. The matching rig views store their position/offset at +0xa4. The fragment is therefore not a standalone three-word constant despite one consumer's partial extern declaration.

| Offset from scene base 020d8a44 | Native address | Demonstrated role |
|---:|---|---|
| +0x644 | 020d9088 | start of effect-4 model |
| +0x6e8 | 020d912c | model +0xa4 vector / area-blast center |
| +0x774 | 020d91b8 | final model phase/active word in reset/rig views |
| +0x778 | 020d91bc | three groups of four s16 hit-scan slots |
| +0x790 | 020d91d4 | four additional s16 slots |
| +0x798 | 020d91dc | address passed to CameraPath_Load and CameraPath_Free |
| +0x7f8 | 020d923c | speed-phase byte in UpdateSceneIntroSequence |
| +0x7fc | 020d9240 | speed-timer word in the same intro view |

CameraPath_Load/Free prove pointer fields and allocated node/key storage through the object starting at 020d91dc. This does not make the rest of the 308-byte tail a CameraPath object. Different sequence views assign context-dependent roles to some control words; do not combine their private typedef labels as simultaneous meanings. Unspecified spans and the final 28 bytes after the listed timer remain unchanged and are not declared padding.

## Placement constants and exact units

The AI cross-product reference is {0,1,0}, with integer Y value 1. It is not the FX12 unit vector {0,0x1000,0}; replacing it would alter the native calculation. The state-change effect table has two signed VecFx32 offsets, and the enemy-side placement table has three. Their names assign no named attack or gameplay element.

The slot-angle table contains the three u16 offsets 0,0x5555,0xaaaa, added to the current scene base angle and 0x8000. Its physical object is eight bytes and keeps a fourth stored zero word. Approach and anchor placement each have a separate equal-valued offset; both stay distinct. The three rig/player offsets are indexed slots, without inferring named actor identities from index.

## Per-object evidence and limits

### `gOverlay058EnemyAiCrossAxis`

Uses the stored vector {0,1,0} as the cross-product reference while building a side target relative to the tracked entry-zero actor.

Evidence: `eu/src/overlays/ov058/calls/UpdateEnemyCombatAi.c`. The Y value is1, not FX_ONE 0x1000; do not normalize or replace it as an equal unit vector.

### `gOverlay058StateChangeEffectOffsets`

Two VecFx32 offsets are copied into effect requests while changing enemy state.

Evidence: `eu/src/overlays/ov058/calls/ChangeEnemyState.c`. No gameplay element or attack name is assigned to either offset; preserve both signed triplets.

The EU wrapper selects `src/ov058/unclassified_helpers/ChangeEnemyState_020d65c4.c`.

### `gOverlay058EnemySidePlacementOffsets`

Three VecFx32 offsets are indexed by enemy side before rotated placement trials around the tracked player actor.

Evidence: `eu/src/overlays/ov058/calls/SnapEnemyBesidePlayer_020d5468.c`. Do not infer additional valid side indices or fold the zero-vector entry into another object.

The EU wrapper selects `src/ov058/unclassified_helpers/SnapEnemyBesidePlayer_020d5468.c`.

### `gOverlay058SceneSlotAngleOffsets`

Three u16 angles 0,0x5555,0xaaaa are added to scene baseAngle and 0x8000 for a slot.

Evidence: `eu/src/overlays/ov058/calls/GetSceneSlotAngle.c`. Physical 8 bytes include a fourth stored zero u16; no bounds validation or removal of that word.

The EU wrapper selects `src/ov058/unclassified_helpers/GetSceneSlotAngle_020d88e4.c`.

### `gOverlay058ApproachOffset`

Rotates this offset around the stored scene center using GetSceneSlotAngle to form an approach target.

Evidence: `eu/src/overlays/ov058/calls/ComputeApproachTarget.c`. This equal-valued offset remains separate from anchor placement storage.

The EU wrapper selects `src/ov058/unclassified_helpers/ComputeApproachTarget_020d8814.c`.

### `gOverlay058AnchorPlacementOffset`

Rotates this offset from the supplied position and heading to derive the initial anchor position.

Evidence: `eu/src/overlays/ov058/calls/StartAnchorSequence.c`. Do not merge it with the approach offset or replace its signed Z component.

The EU wrapper selects `src/ov058/unclassified_helpers/StartAnchorSequence_020d7f60.c`.

### `gOverlay058RigPlayerOffsets`

Three VecFx32 offsets are selected for rig placement relative to the corresponding bounded entry position and linked angle.

Evidence: `eu/src/overlays/ov058/calls/PlaceRigAtPlayerOffset.c`. No named actor identity is assigned to the three indexed slots.

The EU wrapper selects `src/ov058/unclassified_helpers/PlaceRigAtPlayerOffset_020d7818.c`.

### `gOverlay058EntryZeroActor`

The exact 4-byte global reference is assigned GetBoundedEntryField(0), then read by enemy AI, facing and request helpers.

Evidence: `eu/src/overlays/ov058/calls/UpdateEnemyCombatAi.c`. This is a reference to the currently cached entry-zero actor, not ownership transfer or an inline actor allocation.

### `gOverlay058SceneControlHead`

The 8-byte head starts the inline scene control view; its first signed byte is the intro-sequence mode and its second word is the timer.

Evidence: `eu/src/overlays/ov058/calls/UpdateSceneIntroSequence.c`. It is inline BSS state, not a global pointer. Other logical scene fields continue in separate physical objects.

### `gOverlay058SceneCenter`

The inline 12-byte VecFx32 center supplies approach, emitter and proximity calculations; UpdateSceneCameraTransform uses it as translation.

Evidence: `eu/src/overlays/ov058/calls/ComputeApproachTarget.c`. This is an inline vector within the same scene state, not a pointer or separately owned rig allocation.

The EU wrapper selects `src/ov058/unclassified_helpers/ComputeApproachTarget_020d8814.c`.

### `gOverlay058SceneControlTail`

This 40-byte continuation contains previous center, heading/speed and sequence fields, ending with the archive reference at logical +0x38.

Evidence: `eu/src/overlays/ov058/calls/LoadSceneModelResources.c`. Different sequence views give some words context-dependent roles. Keep all 40 bytes and the cross-object logical view; no complete public struct is invented.

### `gOverlay058SceneAnimatedModel`

Initializes the 312-byte inline animated-model storage from ba/ch/so_t.m.p.z; teardown passes the same address to TeardownBigObj.

Evidence: `eu/src/overlays/ov058/calls/LoadSceneModelResources.c`. This is inline global model storage, not the loaded file allocation. Resource lifetime remains with the actual initializer/teardown routines.

The EU wrapper selects `src/ov058/unclassified_helpers/LoadSceneModelResources_020d7e30.c`.

### `gOverlay058ArchiveEffect2Model`

A 308-byte inline model is initialized using archive file index 2, drawn by its effect helper and released by ReleaseRecordEntry.

Evidence: `eu/src/overlays/ov058/calls/LoadSceneModelResources.c`. 2 is the resource file index, not a gameplay effect category. Do not free the BSS object itself.

The EU wrapper selects `src/ov058/unclassified_helpers/LoadSceneModelResources_020d7e30.c`.

### `gOverlay058ArchiveEffect3Models`

Three contiguous 308-byte inline models are initialized with archive file index 3; per-index hazard scans access their position/activation data.

Evidence: `eu/src/overlays/ov058/calls/LoadSceneModelResources.c`. The physical 924-byte array is retained with the exact 0x134stride and all three elements.

### `gOverlay058ArchiveEffect4ModelPrefix`

The 164-byte physical prefix begins the 308-byte model initialized from archive file index 4; its remaining 144 bytes continue at020d912c.

Evidence: `eu/src/overlays/ov058/calls/LoadSceneModelResources.c`. Do not reduce the logical model to 164 B or merge physical objects as part of naming.

The EU wrapper selects `src/ov058/unclassified_helpers/LoadSceneModelResources_020d7e30.c`.

### `gOverlay058SceneStorageTail`

The 308-byte tail starts at effect 4 model+0xa4, whose position is the area-blast center; it also contains the rest of that model and the later camera-path/control views.

Evidence: `eu/src/overlays/ov058/calls/RunAreaBlastHitScan.c`. This mixed physical fragment is not a single VecFx32 despite that partial extern view. Only documented subranges have assigned roles; keep its full extent and unspecified regions.

## Reproducible review and validation boundary

Use `eu/config/arm9/overlays/ov058/symbols.txt` for identities and the same bank's `delinks.txt` for active physical owners. Read EU wrapper aliases before shared bodies. The control/model relationships come from LoadSceneModelResources, ReleaseSceneModelResources, UpdateSceneIntroSequence, ResetSceneModelState, PulseHazardHitScans and RunAreaBlastHitScan; the camera-path fields are read/written by the actual CameraPath_Load/Free implementations in overlay046.

All seven DATA objects agree with the existing ELF bytes at the extracted EU ROM addresses. All nine BSS objects have SHT_NOBITS extents within the native overlay BSS interval; this is an extent check, not stored ROM-byte comparison. Physical sources and direct evidence sources are active delink inputs. No new compilation or official gate result is claimed. Integration must preserve module matches, complete physical extents and all cross-object views.


## Byte-exact validation

86 DATA identities retain their source paths, native sizes and storage.
100/102 affected official function checks pass; the remaining
2 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 163 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
