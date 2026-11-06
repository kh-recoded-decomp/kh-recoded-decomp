# Actor resources and scene parameters

These 20 DATA names are based on active actor/scene constructors and consumers in overlays059,061,064,067,068 and070–072. The names retain unresolved descriptor fields and index meanings as parameters. Original files, physical sizes, values, pointer bases and addends remain unchanged.

## Identity and stable source table

| EU identity | Original identifier | Descriptive identifier | Native bytes | Stable source | Direct consumer |
|---|---|---|---:|---|---|
| ov059:20cfe10 | `data_ov059_020cfe10` | `gOverlay059AnimationSlotStorage` | 48 | `eu/src/ov059/data/Rodata_ov059_020cfe10.c` | `eu/src/overlays/ov059/calls/Actor_LoadAnimResources.c` |
| ov059:20cfe80 | `data_ov059_020cfe80` | `gOverlay059HitEffectOffset` | 12 | `eu/src/ov059/data/Rodata_ov059_020cfe80.c` | `eu/src/overlays/ov059/calls/SpawnHitEffects.c` |
| ov059:20cfe8c | `data_ov059_020cfe8c` | `gOverlay059JointBlendResourceIds` | 16 | `eu/src/ov059/data/Rodata_ov059_020cfe80.c` | `eu/src/overlays/ov059/calls/Actor_LoadJointBlendSets.c` |
| ov059:20cfe9c | `data_ov059_020cfe9c` | `gOverlay059EntryGroupTemplates` | 60 | `eu/src/ov059/data/Rodata_ov059_020cfe80.c` | `eu/src/overlays/ov059/calls/Actor_Init.c` |
| ov059:20cfed8 | `data_ov059_020cfed8` | `gOverlay059EffectGroupResourceParameters` | 24 | `eu/src/ov059/data/Rodata_ov059_020cfed8.c` | `eu/src/overlays/ov059/calls/EffectGroup_Init.c` |
| ov061:20d8520 | `data_ov061_020d8520` | `gOverlay061BurstSpawnFrames` | 16 | `eu/src/ov061/data/Rodata_ov061_020d8520.c` | `eu/src/overlays/ov061/calls/UpdateTimedBurstAction.c` |
| ov064:20d8844 | `data_ov064_020d8844` | `gOverlay064TimedMarkerOffset` | 12 | `eu/src/ov064/data/Rodata_ov064_020d8844.c` | `eu/src/overlays/ov064/calls/UpdateOv064BossSequence.c` |
| ov064:20d8850 | `data_ov064_020d8850` | `gOverlay064InitialMarkerOffset` | 12 | `eu/src/ov064/data/Rodata_ov064_020d8850.c` | `eu/src/overlays/ov064/calls/UpdateOv064BossSequence.c` |
| ov064:20d885c | `data_ov064_020d885c` | `gOverlay064EntryGroupParameters` | 16 | `eu/src/ov064/data/Rodata_ov064_020d8850.c` | `eu/src/overlays/ov064/calls/CreateMarkedSceneTask.c` |
| ov067:20d8560 | `data_ov067_020d8560` | `gOverlay067ResourcePaths` | 64 | `eu/src/ov067/data/Ov067ResourcePaths.c` | `eu/src/overlays/ov067/calls/CreateOv067BossObject.c` |
| ov068:20d8674 | `data_ov068_020d8674` | `gOverlay068EmitterStartFrames` | 12 | `eu/src/ov068/data/Rodata_ov068_020d8674.c` | `eu/src/overlays/ov068/calls/RunOv068BossState.c` |
| ov070:20d8a24 | `data_ov070_020d8a24` | `gOverlay070EntryGroupParameters` | 12 | `eu/src/ov070/data/Rodata_ov070_020d8a24.c` | `eu/src/overlays/ov070/calls/CreateOv070BossObject.c` |
| ov070:20d8a30 | `data_ov070_020d8a30` | `gOverlay070EntryGroupResourceIndices` | 12 | `eu/src/ov070/data/Rodata_ov070_020d8a30.c` | `eu/src/overlays/ov070/calls/CreateOv070BossObject.c` |
| ov070:20d8a3c | `data_ov070_020d8a3c` | `gOverlay070TaskCounterThresholds` | 32 | `eu/src/ov070/data/Rodata_ov070_020d8a30.c` | `eu/src/overlays/ov070/calls/GetOv070PaletteEntry.c` |
| ov071:20d9680 | `data_ov071_020d9680` | `gOverlay071ContactReferenceUp` | 12 | `eu/src/ov071/data/Rodata_ov071_020d967c.c` | `eu/src/overlays/ov071/calls/UpdateOv071BossState.c` |
| ov071:20d968c | `data_ov071_020d968c` | `gOverlay071EntryGroupParameters` | 16 | `eu/src/ov071/data/Rodata_ov071_020d967c.c` | `eu/src/overlays/ov071/calls/CreateOv071SceneTask.c` |
| ov071:20d969c | `data_ov071_020d969c` | `gOverlay071TaskCounterThresholds` | 32 | `eu/src/ov071/data/Rodata_ov071_020d967c.c` | `eu/src/overlays/ov071/calls/GetOv071PaletteEntry.c` |
| ov072:20d9bdc | `data_ov072_020d9bdc` | `gOverlay072ContactUpNormal` | 12 | `eu/src/ov072/data/Rodata_ov072_020d9bdc.c` | `eu/src/overlays/ov072/calls/SnapContactNormalUp.c` |
| ov072:20d9be8 | `data_ov072_020d9be8` | `gOverlay072EntryGroupParameters` | 20 | `eu/src/ov072/data/Rodata_ov072_020d9bdc.c` | `eu/src/overlays/ov072/calls/CreateOv072SceneTask.c` |
| ov072:20d9bfc | `data_ov072_020d9bfc` | `gOverlay072TaskCounterThresholds` | 32 | `eu/src/ov072/data/Rodata_ov072_020d9bdc.c` | `eu/src/overlays/ov072/calls/GetObjectPaletteValue.c` |

## Actor resources and partial physical objects

gOverlay059AnimationSlotStorage is 48 bytes. Actor_LoadAnimResources copies only its first three words as destination slots 0,1,2. The remaining nine stored words have no additional animation-slot contract established here. They are preserved as unknown parameter storage, not treated as nine more slots or padding.

The joint-blend resource IDs select four record/source pairs at ID and ID+1 in the actor's current archive. The equal-valued ov052 model-ID table remains a distinct bank-qualified object. The five entry-group templates each have three stored words; their output-pointer words are zero and are replaced only in a local copy with addresses of actor group-ID fields. No new relocations are invented for those placeholders.

The six-word effect-group descriptor supplies its base resource ID and is passed to the existing trail setup helper. Only those demonstrated operations are assigned here; the remaining descriptor words are not given meanings from equal nearby values.

## Frame thresholds, offsets and group parameters

The burst table has four animation-frame thresholds. UpdateTimedBurstAction checks a separate mask bit for each threshold so each corresponding spawn happens once. The emitter-start table is selected when saved action ID is 0x18 and the sound handle is inactive. Numeric selectors are not labeled as named abilities or difficulties.

The two overlay064 placement offsets are separate vectors for the initial marker and the later request after elapsed exceeds 0x6000. No named gameplay attack is inferred. The overlay071 contact reference and overlay072 normal are positive-Y FX12 unit vectors, used by the actual dot-product and ContactPlane_SetNormal operations.

Constructors in overlays064,070,071,072 copy DATA parameters into entry-group descriptor word +8. Some private typedefs misleadingly call this word modelName/name, while another family calls it slotCount. These DATA names retain the proved group-parameter role without asserting those labels or repairing the descriptor ABI. Overlay070's parallel resource-index array forms key pairs at index and index+1; its repeated index 2 remains unchanged.

## Structured path record in overlay067

gOverlay067ResourcePaths has a nine-byte effectDirectory prefix, a seven-byte archiveName, a 16-byte characterPathFormat and a 32-byte commonArchive. The constructor passes the address of effectDirectory as a complete archive path. That prefix is not NUL-terminated by itself: the path continues into archiveName to form ba/ef/fn/ss.p2. Preserve member adjacency and capacities; splitting each field into an independent string would break that reference.

The same record supplies ba/ch/%s/ci.b.z to formatting and cm/QC to CameraPath_Load. These uses demonstrate resource paths, without assigning a character identity from a filename abbreviation.

## Counter thresholds in overlays070–072

The existing accessor names contain Palette, but their downstream consumers use the returned values as deadlines and remaining-counter limits. Each table is two rows of four words. The row comes from a concrete task-ID predicate; the column comes from GetClampedPaletteSlot, which reads a signed manager field and clamps it to 0..3. Its legacy name does not establish palette-color semantics, named difficulty levels or gameplay variant meanings.

| Table | Row predicate | Actual deadline consumer | Comparison |
|---|---|---|---|
| gOverlay070TaskCounterThresholds | task ID equals 0x10f | UpdateOv070BossTurnState progress | progress >= selected value |
| gOverlay071TaskCounterThresholds | task ID equals 0x110 | UpdateOv071BossState timer | timer > selected value |
| gOverlay072TaskCounterThresholds | task ID equals 0x111 | UpdatePillarRide counter | counter >= selected value |

All three consumers also compute a nonnegative remaining value and pass remaining/30+0xfff to SetPendingSlotFlagWithValue. Preserve the different > and >= comparisons and the integer expression. Equal table values across these overlays do not authorize deduplicating storage or equating task owners.

## Per-object evidence and limits

### `gOverlay059AnimationSlotStorage`

The first three words select destination animation slots 0,1,2 while three path suffixes are loaded into the actor.

Evidence: `eu/src/overlays/ov059/calls/Actor_LoadAnimResources.c`. Physical 48 B stores 12 words; only the initial 12 B slot list is demonstrated here. The remaining 36 B are not extra proven slot IDs or padding.

The EU wrapper selects `src/ov059/unclassified_helpers/Actor_LoadAnimResources_020c7590.c`.

### `gOverlay059HitEffectOffset`

Copies and rotates the VecFx32 offset about the actor facing, then adds actor model position before placing hit effects.

Evidence: `eu/src/overlays/ov059/calls/SpawnHitEffects.c`. Preserve the signed/local offset and the original rotation/rounding sequence.

The EU wrapper selects `src/ov059/actor_effects/SpawnHitEffects_020caea0.c`.

### `gOverlay059JointBlendResourceIds`

Four IDs select shared record/source pairs for four animation-blend model slots, with source ID equal to record ID+1.

Evidence: `eu/src/overlays/ov059/calls/Actor_LoadJointBlendSets.c`. Distinct from ov052 equal-valued model resource IDs; retain physical storage and runtime archive selection.

The EU wrapper selects `src/ov059/unclassified_helpers/Actor_LoadJointBlendSets_020c8a84.c`.

### `gOverlay059EntryGroupTemplates`

Five 3-word templates provide file ID, slot count and local output pointer; initialization patches pointers to actor group IDs before creation.

Evidence: `eu/src/overlays/ov059/calls/Actor_Init.c`. Stored pointer words are zero placeholders replaced in a local copy, not missing relocations or heap-owned group allocations.

The EU wrapper selects `src/ov059/unclassified_helpers/Actor_Init_020cba3c.c`.

### `gOverlay059EffectGroupResourceParameters`

Copies six resource-parameter words; first base ID and its paired successor configure the effect owner, and the descriptor is also forwarded to the trail setup helper.

Evidence: `eu/src/overlays/ov059/calls/EffectGroup_Init.c`. Only the demonstrated base-ID/passing behavior is named; all 24 B and remaining descriptor words stay exact without unproved per-field semantics.

The EU wrapper selects `src/ov059/unclassified_helpers/EffectGroup_Init_020cedbc.c`.

### `gOverlay061BurstSpawnFrames`

Four animation-frame thresholds trigger one spawn each under a per-entry spawned-mask bit.

Evidence: `eu/src/overlays/ov061/calls/UpdateTimedBurstAction.c`. Stored fx32 thresholds7,19,23,34frames; no new timing units, sorting or event coalescing.

The EU wrapper selects `src/ov061/actor_motion/UpdateTimedBurstAction_020d81c0.c`.

### `gOverlay064TimedMarkerOffset`

After elapsed exceeds 0x6000, rotates this offset relative to the actor and records the resulting position for the next marker request.

Evidence: `eu/src/overlays/ov064/calls/UpdateOv064BossSequence.c`. A timed sequence offset; no named gameplay attack or difficulty is assigned.

The EU wrapper selects `src/ov064/object_state/UpdateOv064BossSequence_020d8234.c`.

### `gOverlay064InitialMarkerOffset`

Rotates this initial offset relative to actor position/facing before creating the sequence marker request with its sound handle.

Evidence: `eu/src/overlays/ov064/calls/UpdateOv064BossSequence.c`. Separate physical vector from the later timed marker offset.

The EU wrapper selects `src/ov064/object_state/UpdateOv064BossSequence_020d8234.c`.

### `gOverlay064EntryGroupParameters`

Four values are assigned to descriptor word +8 when creating four archive-backed entry groups.

Evidence: `eu/src/overlays/ov064/calls/CreateMarkedSceneTask.c`. Legacy field modelName is not proof of string/model-name semantics. This block names the group parameters without changing descriptor ABI.

The EU wrapper selects `src/ov064/object_factory/CreateMarkedSceneTask_020d86e8.c`.

### `gOverlay067ResourcePaths`

The structured record supplies the effect archive path, formatted character resource path and common camera-path archive name to the constructor.

Evidence: `eu/src/overlays/ov067/calls/CreateOv067BossObject.c`. The 9-byte effectDirectory prefix is not separately terminated; the string continues into archiveName. Preserve field adjacency, capacities and pointer addends.

### `gOverlay068EmitterStartFrames`

Three frame thresholds gate emitter request creation when the saved action ID is 0x18 and no sound handle is active.

Evidence: `eu/src/overlays/ov068/calls/RunOv068BossState.c`. Index comes from the actor selector byte; no named ability level or difficulty is assigned.

The EU wrapper selects `src/ov068/object_state/RunOv068BossState_020d81a0.c`.

### `gOverlay070EntryGroupParameters`

Three values are copied to entry-group descriptor word +8 while constructing resource groups.

Evidence: `eu/src/overlays/ov070/calls/CreateOv070BossObject.c`. Keep them separate from the parallel resource-index table; parameter semantics are not inferred from private type names.

The EU wrapper selects `src/ov070/object_factory/CreateOv070BossObject_020d8894.c`.

### `gOverlay070EntryGroupResourceIndices`

Three indices select archive record/source key pairs at index and index+1 for entry-group creation.

Evidence: `eu/src/overlays/ov070/calls/CreateOv070BossObject.c`. Repeated index 2 is retained; do not deduplicate the groups or swap key ordering.

The EU wrapper selects `src/ov070/object_factory/CreateOv070BossObject_020d8894.c`.

### `gOverlay070TaskCounterThresholds`

A 2x4 table is selected by task-ID 0x10f predicate and clamped slot 0..3; UpdateOv070BossTurnState uses the result as a progress threshold and remaining-value limit.

Evidence: `eu/src/overlays/ov070/calls/GetOv070PaletteEntry.c`. No palette-color semantics or gameplay name for either row/column is established by legacy accessor names.

The EU wrapper selects `src/ov070/unclassified_helpers/GetOv070PaletteEntry_020d8114.c`.

### `gOverlay071ContactReferenceUp`

The positive-Y FX12 unit vector is the dot-product reference when constraining contact-adjusted movement directions.

Evidence: `eu/src/overlays/ov071/calls/UpdateOv071BossState.c`. Preserve the 0xd6 comparison and subsequent flatten/normalize behavior; no new contact classification.

The EU wrapper selects `src/ov071/object_state/UpdateOv071BossState_020d836c.c`.

### `gOverlay071EntryGroupParameters`

Four values are assigned to entry-group descriptor word +8 while constructing resource groups.

Evidence: `eu/src/overlays/ov071/calls/CreateOv071SceneTask.c`. Opaque group parameter role is proved; the private name field does not establish a string or bone/model identifier.

The EU wrapper selects `src/ov071/object_factory/CreateOv071SceneTask_020d954c.c`.

### `gOverlay071TaskCounterThresholds`

A 2x4 table is selected by task-ID 0x110 predicate and clamped slot; UpdateOv071BossState compares timer to the result and calculates remaining.

Evidence: `eu/src/overlays/ov071/calls/GetOv071PaletteEntry.c`. Do not label rows as harder/enraged or columns as difficulty without their separate writer proof.

The EU wrapper selects `src/ov071/unclassified_helpers/GetOv071PaletteEntry_020d8114.c`.

### `gOverlay072ContactUpNormal`

Supplies normal {0,0x1000,0} to ContactPlane_SetNormal when the callback accepts the plane.

Evidence: `eu/src/overlays/ov072/calls/SnapContactNormalUp.c`. Distinct from EU9bfc counter thresholds despite the shared GetObjectPaletteValue old9bdc label.

The EU wrapper selects `src/ov072/unclassified_helpers/SnapContactNormalUp_020d84b0.c`.

### `gOverlay072EntryGroupParameters`

Five values are assigned to entry-group descriptor word +8 for the five archive-backed groups.

Evidence: `eu/src/overlays/ov072/calls/CreateOv072SceneTask.c`. Preserve all five values and resource key pairing; no unproved name/slot-count semantics are encoded in the DATA identifier.

The EU wrapper selects `src/ov072/object_factory/CreateOv072SceneTask_020d9aac.c`.

### `gOverlay072TaskCounterThresholds`

A 2x4 table is selected by task-ID 0x111 predicate and clamped slot; UpdatePillarRide uses it as a counter deadline and remaining-value limit.

Evidence: `eu/src/overlays/ov072/calls/GetObjectPaletteValue.c`. The actual use is a counter threshold, not a palette value; no named gameplay variant is inferred.

The EU wrapper selects `src/ov072/unclassified_helpers/GetObjectPaletteValue_020d8114.c`.

## Reproducible review and validation boundary

Locate each identity in its `eu/config/arm9/overlays/ovNNN/symbols.txt` and active owner range in that bank's `delinks.txt`. Follow EU wrapper aliases before reading shared bodies. For threshold meaning, follow the accessor into its actual turn/ride-state consumer rather than copying a legacy name.

Existing ELF symbol bytes and extents of all 20 DATA objects agree with the extracted native EU overlay bytes. Both physical source and direct evidence source are active delink inputs. No new compilation or official gate result is claimed by this review. Integration must preserve the module matches, physical object extents and all source/consumer address relationships.


## Byte-exact validation

73 DATA identities retain their source paths, native sizes and storage.
67/69 affected official function checks pass; the remaining
2 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 120 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
