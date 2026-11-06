# Six functions retained pending semantic evidence

These functions remain in C with their existing numeric identities. Their mechanical behavior is documented below. A byte match establishes the generated instructions; it does not establish a missing callback role, field meaning or output layout. Names are retained until the specific evidence gap is closed.

No source-body, prototype or runtime behavior change is part of this ledger.

## Identity and mechanical contract

| EU bank/address | Symbol | Native mode / bytes | Stable source path | Proven mechanical behavior |
|---|---|---|---|---|
| ov002:02065c4c | `func_ov002_02065c4c` | arm / 4 | `eu/src/overlays/ov002/auto/func_ov002_02065c4c.c` | Empty function address is present in both main/sub background configs at config+0xc. InitMenuContext copies the descriptors; InitBackgroundContainer copies this word to container+0x3c. |
| ov002:02065c50 | `func_ov002_02065c50` | arm / 4 | `eu/src/overlays/ov002/auto/func_ov002_02065c50.c` | Empty function address is present in both main/sub background configs at config+0x10. InitMenuContext copies the descriptors; InitBackgroundContainer copies this word to container+0x40. |
| ov043:020bc8d4 | `func_ov043_020bc8d4` | arm / 8 | `eu/src/overlays/ov043/auto/func_ov043_020bc8d4.c` | ARM leaf returns literal0 and reads no input. No owning-bank registration or direct caller has been established. |
| ov043:020bd0a4 | `func_ov043_020bd0a4` | arm / 4 | `eu/src/overlays/ov043/auto/func_ov043_020bd0a4.c` | Empty ARM BX LR preserves incoming R0 and makes no memory changes. No owning-bank registration or direct caller has been established. |
| ov044:020d0000 | `func_ov044_020d0000` | thumb / 32 | `eu/src/overlays/ov044/calls/func_ov044_020d0000.c` | Writes five u32 output words {0x1922,0x2b8,0x333,0,0xa000}, leaves R0 unchanged. Thumb pointer appears in own-bank table 020d0df8 slot 2 at 020d0e00. |
| ov044:020d0020 | `func_ov044_020d0020` | thumb / 32 | `eu/src/overlays/ov044/calls/func_ov044_020d0020.c` | Writes five u32 output words {0x1922,0x666,0x666,0,0x14000}, leaves R0 unchanged. Thumb pointer appears in the same table slot 3 at 020d0e04. |

## Specific blockers and next proof

### `func_ov002_02065c4c`

No actual reader/invoker of the copied word has been proven. Header parameter0c/parameter10 intentionally remain opaque. Pointer presence and empty body do not establish init/update/draw/cleanup.

Next proof: Find a bank-qualified indirect call or another layout consumer of BackgroundContainer+0x3c; distinguish main/sub descriptors and container lifetime.

Source/consumer evidence:
- `eu/src/overlays/ov002/auto/func_ov002_02065c4c.c`
- `eu/src/overlays/ov002/calls/InitMenuContext.c`
- `eu/src/ov002/data/Rodata_ov002_0206acb4.c`
- `eu/src/ov002/data/Rodata_ov002_0206acd8.c`
- `eu/src/overlays/ov027/BackgroundContainer.h`
- `eu/src/overlays/ov027/calls/InitBackgroundContainer.c`

### `func_ov002_02065c50`

No actual reader/invoker of the copied word has been proven. Header parameter0c/parameter10 intentionally remain opaque. Pointer presence and empty body do not establish init/update/draw/cleanup.

Next proof: Find a bank-qualified indirect call or another layout consumer of BackgroundContainer+0x40; distinguish main/sub descriptors and container lifetime.

Source/consumer evidence:
- `eu/src/overlays/ov002/auto/func_ov002_02065c50.c`
- `eu/src/overlays/ov002/calls/InitMenuContext.c`
- `eu/src/ov002/data/Rodata_ov002_0206acb4.c`
- `eu/src/ov002/data/Rodata_ov002_0206acd8.c`
- `eu/src/overlays/ov027/BackgroundContainer.h`
- `eu/src/overlays/ov027/calls/InitBackgroundContainer.c`

### `func_ov043_020bc8d4`

Two raw references from ov036 point to that bank's ARM LoadTextureInChunks at the same RAM address, not this ov043 leaf. No ov043 role follows from them.

Next proof: Find an ov043 registration/caller/exported-interface consumer, qualified by the loader and owner. Do not transfer the ov036 texture callback role.

Source/consumer evidence:
- `eu/src/overlays/ov043/auto/func_ov043_020bc8d4.c`
- `eu/src/overlays/ov036/calls/SwapActorSlotResource.c`
- `eu/src/overlays/ov036/calls/AttachPendingSceneModel.c`
- `src/ov043/leaf_research/func_ov043_020bc8b4.c`

### `func_ov043_020bd0a4`

The neighboring bd0a8 initialization hook is separately proven; adjacency does not identify this function. No raw addr/addr|1 references were found.

Next proof: Find its own callback slot or caller and inspect the actual incoming arguments/result use before choosing a lifecycle name.

Source/consumer evidence:
- `eu/src/overlays/ov043/auto/func_ov043_020bd0a4.c`
- `src/ov043/panel_state/func_ov043_020bd084.c`

### `func_ov044_020d0000`

The table invoker and destination owner are not established. SpawnPanelDriftPreset reads scalar pairs and jumps directly to SpawnPanelDriftParticle; it does not dispatch this table. Callback slot 2 is distinct from scalar preset index 2.

Next proof: Find a bank-qualified table load/copy/invocation establishing the selected slot and incoming R0 destination, or a proven output consumer. A narrow writer name would not require every field's units, but still requires this owner/role evidence.

Source/consumer evidence:
- `eu/src/overlays/ov044/calls/func_ov044_020d0000.c`
- `eu/src/ov044/data/Data_ov044_020d0de0.c`
- `eu/src/overlays/ov044/calls/SpawnPanelDriftPreset.c`

### `func_ov044_020d0020`

Same missing invoker/destination proof as slot 2. A cross-bank pointer020d0e11 belongs to ov052 ChooseNextAction, not the ov044 table. This callback slot 3 is outside the three scalar preset selectors observed in the actual spawner calls.

Next proof: Find the owning-bank invocation or output consumer and identify the destination owner. Preserve the five raw values and incoming R0 behavior without inferring motion units.

Source/consumer evidence:
- `eu/src/overlays/ov044/calls/func_ov044_020d0020.c`
- `eu/src/ov044/data/Data_ov044_020d0de0.c`
- `eu/src/overlays/ov052/calls/SelectFallStateHandler.c`

## Reference-search boundary

Raw-reference searches covered all 108 available extracted modules: 105 overlay files plus MAIN, ITCM and DTCM. Both little-endian addr and addr|1 were searched at byte alignment. Raw hits were classified by owning bank and real source/loader chain; a shared RAM address alone was not treated as a call edge. A zero raw count does not exclude direct BL/BLX branches, computed pointers or unavailable representations.

This search found a genuine ov030 caller of the ov042 setter that the earlier Ghidra xref result omitted. It also excluded the two ov036 texture-loader pointers from the ov043 literal-zero function. A separate bounded scan of u32 values in [020d0d80,020d0e40) across the same modules found no new consumer of ov044 callback table 020d0df8: owning-bank hits reference drift-pair values 020d0de0/e4 or later path data 020d0e10. The ov052:020d0e11 hit belongs to ChooseNextAction in ov052. None of those observations establishes a preset layout for the two table entries.

The background configuration functions have same-bank pointer values in their two configuration objects and a proven copy into the runtime container. No callback invoker has been identified. Until one is found, assigning init/draw/update/cleanup or a return contract to those words would go beyond the evidence.

These are concrete, separate research questions. They should not be resolved by assigning names solely from an offset, neighboring function or equal bytes in another overlay.

## Follow-up: scalar presets and the separate six-pointer table

SpawnPanelDriftPreset at ov044:020d05e0 is ARM. Its loads at 020d05ec and
020d05f0 read the head/tail scalar bases with an eight-byte stride. The BX IP
at 020d05f8 targets the fixed SpawnPanelDriftParticle address 020d05ac, loaded
from literal 020d0604. Eight native stage-action calls use selectors 0, 1 or 2
for pairs {0x19a,0xa000}, {0x333,0xa000} and {0x4cd,0x14000}. None of this
invokes the six-pointer table beginning at 020d0df8.

A bounded mode-aware review of all 36 configured ov044 functions found three
register-indirect transfers, each with a fixed literal target. None reads the
six-pointer table; matching-bank Ghidra xrefs add no invoker. These checks do
not exclude computed or runtime-decoded references. Original ROM overlays
044, 041 and 021 decompress exactly to the extracted modules used for this
review. No source, prototype or binary changed.

The review receipt has SHA-256
`7dfd29e02971828eb2cca414686d470b98843031d69d8422b4214553570d0fa4`.
It records instructions, literal targets, scalar callers and reference limits.
The remaining gap is the invoker and destination owner; a complete five-word
semantic layout is not a prerequisite for a future narrowly justified name.

## Closed jump-step hook

The former ov059:020c99ec helper is [Actor_TryOverrideJumpStepNoop](ACTOR_JUMP_STEP_OVERRIDE.md). The embedded jump-state argument and BOOL consumer prove its narrow step-override role. The control-record lookup and canonical FALSE remain; no ability or phase transition is invented.

## Closed stage-local fade and camera snap

[StopStageBrightnessFade](STAGE_BRIGHTNESS_FADE.md) stops only the stage-local brightness loop. [SetCameraGoalSnapEnabled](CAMERA_GOAL_SNAP.md) controls direct versus proportional goal placement. Their actual reader/writer chains resolve the former +0x52c and +0x144 gaps. [The retained callback follow-up](BACKGROUND_CALLBACK_EVIDENCE_LIMITS.md) records the six remaining gaps and the exact background-owner paths.
