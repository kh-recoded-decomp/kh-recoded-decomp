# Drift, actor, record-group and carousel data

These physical data objects have demonstrated consumers or fixed pointer values. Keep all original active source filenames, physical extents, values, binding and relocations. The grouping below documents distinct owners; it does not imply a common engine layout. Native integration and object/module checks are recorded below.

| Identity | Name | Bytes | Active source | Direct evidence |
|---|---|---:|---|---|
| `data_ov044_020d0de0` | `gPanelDriftPresetHead` | 4 | `eu/src/ov044/data/Data_ov044_020d0de0.c` | `eu/src/overlays/ov044/calls/SpawnPanelDriftPreset.c` |
| `data_ov044_020d0de4` | `gPanelDriftPresetAndCallbackTail` | 44 | `eu/src/ov044/data/Data_ov044_020d0de0.c` | `eu/src/overlays/ov044/calls/SpawnPanelDriftPreset.c` |
| `data_ov052_020d211c` | `gOv052ActorState17Parameters` | 24 | `eu/src/ov052/data/Rodata_ov052_020d210c.c` | `eu/src/overlays/ov052/calls/ConfigureCameraMode.c` |
| `data_ov052_020d2134` | `gForcedHitElementOverrides` | 40 | `eu/src/ov052/data/Rodata_ov052_020d210c.c` | `eu/src/overlays/ov052/calls/BuildHitResult_020d1880.c` |
| `data_ov086_020c23c0` | `gRecordGroupEntryDefinitionsHead` | 1880 | `eu/src/overlays/ov086/data/Data_ov086_020c23c0.c` | `eu/src/overlays/ov086/calls/CountGroupEntriesInStateOne.c` |
| `data_ov086_020c2b18` | `gRecordGroupEntryDefinitionsTail` | 1228 | `eu/src/overlays/ov086/data/Data_ov086_020c2b18.c` | `eu/src/overlays/ov086/calls/IsGroupEntryStateOne.c` |
| `data_ov089_020c0540` | `gEntryCarouselSessionFlagIds` | 24 | `eu/src/ov089/data/Rodata_ov089_020c0530.c` | `eu/src/overlays/ov089/calls/InitEntryUnlocks.c` |
| `data_ov089_020c0560` | `gEntryCarouselSingleModelDefinition` | 12 | `eu/src/ov089/data/Data_ov089_020c0560.c` | `eu/src/overlays/ov089/calls/LoadEntryModels.c` |
| `data_ov089_020c05b0` | `gEntryCarouselSixModelDefinitionsHead` | 20 | `eu/src/ov089/data/Data_ov089_020c05b0.c` | `eu/src/overlays/ov089/calls/LoadEntryModels.c` |
| `data_ov089_020c05c4` | `gEntryCarouselSixModelDefinitionsTail` | 52 | `eu/src/ov089/data/Data_ov089_020c05b0.c` | `eu/src/overlays/ov089/calls/LoadEntryModels.c` |
| `data_ov089_020c05f8` | `gEntryCarouselSevenModelDefinitions` | 84 | `eu/src/ov089/data/Data_ov089_020c05b0.c` | `eu/src/overlays/ov089/calls/LoadEntryModels.c` |

## Contracts and limits

- `gPanelDriftPresetHead`: First word of a logical {param30,param2c} drift preset array; index 0 passes 0x19a and 0xa000 to SpawnPanelDriftParticle. Physical head is 4 B; five more scalar words and six function-pointer values are in the following 44-byte object. No callback invocation or callback ABI is established by their presence.
- `gPanelDriftPresetAndCallbackTail`: First five words continue the preset scalars; final six words contain InitPanelSwayB, InitPanelSwayA, func_ov044_020d0000, func_ov044_020d0020, InitPanelMotionA and InitPanelMotionB pointers. The first 24 logical bytes across head/tail form three scalar pairs, but the index domain is not newly guarded. The six trailing pointers are identified values only; their invoker, parameters and logical returns remain unproved.
- `gOv052ActorState17Parameters`: Two 12-byte parameter rows are selected when actor state kind is 0x11 using GetPlayerEntryCount(0,0xe), decremented only if positive. Values write the actor-local state view +0x1c (s16), +4 and +0xc. EnterActorState passes actor+0xa10 to the legacy ConfigureCameraMode helper. This is actor-local state storage, not evidence of a camera owner; names scale/speed/accel in the private typedef do not define a public port layout. No new clamp protects row indexes beyond 1.
- `gForcedHitElementOverrides`: Five {playerEntryFlag,elementValue} pairs are tried in order when the input forced flag is set and the initial result element is zero. First matching player flag assigns the element and sets duration to 0x32000. Preserve priority {0x34->1,0x35->2,0x36->3,0x37->4,0x38->6}; no gameplay names are assigned to the numeric element values.
- `gRecordGroupEntryDefinitionsHead`: Begins 259 logical 12-byte record-group definitions. Consumers scan signed id at +0 for -1 group delimiters and test signed state byte at +8 against 1. 1880-byte head contains records 0..155 and the first eight bytes of record156. Remaining state and records are in the following 1228-byte physical object. Preserve all unknown record bytes.
- `gRecordGroupEntryDefinitionsTail`: Completes the 259 logical 12-byte group definitions from the preceding base. First byte belongs to record156 state, not a descriptor header. 1228-byte tail completes3108B total; legacy menu/pages/details byte member labels are not semantic table boundaries. The foreign ov039 registry entry with loader ID91 is separately bound to the actual ov091 descriptor; it is not a consumer of this physical record-table tail.
- `gEntryCarouselSessionFlagIds`: Six session flag IDs 0x370e..0x3713 set the corresponding bits in the per-entry mask; masked entries receive animation track3 frame0x1000. The seventh mask bit uses separate conditions, not this table. No additional meaning is inferred for each individual flag.
- `gEntryCarouselSingleModelDefinition`: One {recordFile,infoFile,index} record is selected when ReadSessionPackedBits(0x3700,3)==0; the loader uses its first two file IDs. 12-byte physical definition; third word remains an unassigned extra value.
- `gEntryCarouselSixModelDefinitionsHead`: Default selector branch loads six logical 12-byte model/info records from this base. 20-byte head ends after the second record info-file word; next physical tail begins at that record extra word.
- `gEntryCarouselSixModelDefinitionsTail`: Remaining 52 bytes of the six logical 12-byte model/info records reached through the preceding base. Preserve 20+52-byte split and all unassigned extra words; not thirteen independent resource records.
- `gEntryCarouselSevenModelDefinitions`: Seven 12-byte model/info records are selected when ReadSessionPackedBits(0x3700,3)==6. 84-byte physical array; third words are not used by this loader, including final -1. Do not interpret that -1 as a loop terminator; loop count is seven.

## Logical tables and owners

The overlay-086 record group view is 259 records of twelve bytes, totaling 3108 bytes across a 1880-byte head and 1228-byte tail. The head ends after the first eight bytes of record 156; the tail begins with its state word. Group readers scan signed 16-bit id `-1` delimiters and compare the signed byte at +8 with 1. Other fields remain opaque. The byte-member labels `menu/pages/details` do not correspond to proved table boundaries.

The former `data_ov086_020c2b18` token in the ov039 loader-ID91 registry entry has been independently rebound to ov091 `gReportTopMenuDescriptor`. [Bank-qualified ownership](BANK_QUALIFIED_OWNER_BINDINGS.md) records the native loader/pointer proof. The physical ov086 tail retains its own record-group role.

The overlay-089 default branch indexes six 12-byte model/info records across a twenty-byte head and fifty-two-byte tail. Selector 0 uses one separate record; selector 6 uses seven records in a separate eighty-four-byte object. The loaded info file is freed after record initialization and five animation-track bindings. The third word of each record is preserved without assigning gameplay semantics.

For overlay 052, `EnterActorState` supplies the embedded actor-local view at actor +`0xa10` to the legacy `ConfigureCameraMode` function. Kind `0x11` selects one of two 12-byte rows using the player count selector `0xe`; values are stored at view +`0x1c`, +4 and +`0x0c`. This does not establish a camera owner or validate the private camera-related field names. The hit-result override table is a different owner and code path.

The overlay-044 data split has three scalar pairs in its first twenty-four logical bytes and six following function pointers. `SpawnPanelDriftPreset` proves scalar-pair access. Merely listing pointer targets does not prove their invocation, parameter list, return contract or the semantics of the two still-numeric targets. Preserve them as unresolved callback entries.

The spawner's ARM BX IP at ov044:020d05f8 has the fixed target
SpawnPanelDriftParticle (020d05ac); it does not index the six-pointer table.
Native stage-action calls select scalar pairs 0..2, independently of callback
slots 2/3. The [callback follow-up](EU_PENDING_CALLBACK_FUNCTIONS.md#follow-up-scalar-presets-and-the-separate-six-pointer-table)
records the bounded instruction review and the precise missing invoker/owner
evidence. Do not export the five-word writers as drift presets from adjacency.

## Reproducing the evidence

Apply EU wrapper aliases before reading included shared bodies. The corresponding per-overlay `eu/config/arm9/overlays/ovNNN/delinks.txt` files select the listed active sources. Each existing ELF symbol has the listed size and, after resolving ABS32 function relocations with mode bits from the matching-bank symbol metadata, matches its native module range in `eu/dsd_extract/arm9_overlays/ovNNN.bin`. The separately validated bank binding and the native integration checks below retain the original references.


## Byte-exact validation

11 DATA identities retain their source paths, native sizes and storage.
All 7 affected official function checks pass. A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 14 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
