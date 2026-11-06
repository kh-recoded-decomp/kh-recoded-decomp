# Additional menu descriptor and record-statistic DATA

These 20 DATA names preserve the existing files, object grouping, native extents and pointer relationships. Six objects represent complete menu descriptors or one descriptor fragment; fourteen objects are concrete tables consumed by the ov086 record panel. Names follow the registry/consumer evidence rather than equal values or nearby labels.

## Identity and stable source table

| EU identity | Original identifier | Descriptive identifier | Native bytes | Stable source | Direct consumer/evidence |
|---|---|---|---:|---|---|
| ov079:020c4c60 | `data_ov079_020c4c60` | `gConfigMenuDescriptor` | 68 | `eu/src/ov079/data/Data_ov079_020c4c60.c` | `eu/src/overlays/ov039/calls/UpdateSubOverlayHandlers.c` |
| ov081:020c5cc0 | `data_ov081_020c5cc0` | `gTutorialMenuDescriptor` | 68 | `eu/src/ov081/data/Data_ov081_020c5cc0.c` | `eu/src/overlays/ov039/calls/UpdateSubOverlayHandlers.c` |
| ov082:020bf6a0 | `data_ov082_020bf6a0` | `gOverlay082EntryListDescriptor` | 64 | `eu/src/ov082/data/Data_ov082_020bf6a0.c` | `eu/src/overlays/ov039/calls/UpdateSubOverlayHandlers.c` |
| ov083:020bf6a0 | `data_ov083_020bf6a0` | `gScoreScreenDescriptor` | 64 | `eu/src/ov083/data/Data_ov083_020bf6a0.c` | `eu/src/overlays/ov039/calls/UpdateSubOverlayHandlers.c` |
| ov084:020bfca0 | `data_ov084_020bfca0` | `gTwoChoiceMenuDescriptor` | 68 | `eu/src/ov084/data/Data_ov084_020bfca0.c` | `eu/src/overlays/ov039/calls/UpdateSubOverlayHandlers.c` |
| ov085:020c2368 | `data_ov085_020c2368` | `gShopMenuDescriptorMiddle` | 24 | `eu/src/ov085/data/Data_ov085_020c2368.c` | `eu/src/overlays/ov039/calls/UpdateSubOverlayHandlers.c` |
| ov086:020c20fc | `data_ov086_020c20fc` | `gRecordGroupTierFlagBases` | 12 | `eu/src/overlays/ov086/data/Rodata_ov086_020c20fc.c` | `src/ov086/panel_state/GetHighestSetFlagTier_020bf658.c` |
| ov086:020c2108 | `data_ov086_020c2108` | `gRecordStatTierLabelIds` | 16 | `eu/src/overlays/ov086/data/Rodata_ov086_020c2108.c` | `src/ov086/panel_state/DrawRecordStatRow_020bee0c.c` |
| ov086:020c2168 | `data_ov086_020c2168` | `gRecordGroupTwoBitStatOffsets` | 20 | `eu/src/overlays/ov086/data/Rodata_ov086_020c2168.c` | `eu/src/overlays/ov086/calls/DrawRecordPanelStats.c` |
| ov086:020c217c | `data_ov086_020c217c` | `gRecordGroupSevenBitStatOffsets` | 32 | `eu/src/overlays/ov086/data/Rodata_ov086_020c217c.c` | `eu/src/overlays/ov086/calls/DrawRecordPanelStats.c` |
| ov086:020c219c | `data_ov086_020c219c` | `gRecordGroupStatFlagIds` | 32 | `eu/src/overlays/ov086/data/Rodata_ov086_020c219c.c` | `eu/src/overlays/ov086/calls/DrawRecordPanelStats.c` |
| ov086:020c21f0 | `data_ov086_020c21f0` | `gRecordStatRowLabelIds` | 28 | `eu/src/overlays/ov086/data/Rodata_ov086_020c21f0.c` | `src/ov086/panel_state/DrawRecordStatRow_020bee0c.c` |
| ov086:020c220c | `data_ov086_020c220c` | `gRecordGroupFlagCountTargets` | 32 | `eu/src/overlays/ov086/data/Rodata_ov086_020c220c.c` | `eu/src/overlays/ov086/calls/DrawRecordPanelStats.c` |
| ov086:020c222c | `data_ov086_020c222c` | `gRecordGroupFlagFieldWidths` | 32 | `eu/src/overlays/ov086/data/Rodata_ov086_020c222c.c` | `eu/src/overlays/ov086/calls/CountSessionGroupFlags.c` |
| ov086:020c224c | `data_ov086_020c224c` | `gRecordPageNodeBaseIndices` | 32 | `eu/src/overlays/ov086/data/Rodata_ov086_020c224c.c` | `eu/src/overlays/ov086/calls/RefreshRecordPageLayout.c` |
| ov086:020c226c | `data_ov086_020c226c` | `gRecordGroupFlagFieldOffsets` | 32 | `eu/src/overlays/ov086/data/Rodata_ov086_020c226c.c` | `eu/src/overlays/ov086/calls/CountSessionGroupFlags.c` |
| ov086:020c228c | `data_ov086_020c228c` | `gRecordInitialTextNodeBaseIndices` | 32 | `eu/src/overlays/ov086/data/Rodata_ov086_020c228c.c` | `src/ov086/panel_state/InitRecordPanelText_020c1078.c` |
| ov086:020c22ac | `data_ov086_020c22ac` | `gRecordDigitCellXGaps` | 36 | `eu/src/overlays/ov086/data/Rodata_ov086_020c22ac.c` | `src/ov086/panel_state/InitRecordPanelDigits_020c1ba8.c` |
| ov086:020c2360 | `data_ov086_020c2360` | `gRecordGroupEntryCountsHead` | 8 | `eu/src/overlays/ov086/data/Data_ov086_020c2360.c` | `eu/src/overlays/ov086/calls/CountSetRecordGroupFlags.c` |
| ov086:020c2368 | `data_ov086_020c2368` | `gRecordGroupEntryCountsTail` | 24 | `eu/src/overlays/ov086/data/Data_ov086_020c2368.c` | `eu/src/overlays/ov086/calls/CountSetRecordGroupFlags.c` |

## Descriptor ownership and physical fragments

Overlay039 registry records store an overlay ID and a descriptor address. The ID fixes the bank before descriptor interpretation. Primary descriptors use init/destroy/update at +0/+4/+8, secondary index+0x0c, work size+0x10 and twelve input slots from +0x14. Secondary descriptors use work size+0x0c and input slots from +0x10. The accessor/allocator evidence is UpdateSubOverlayHandlers and the primary/secondary work-size and secondary-index accessors in `eu/src/overlays/ov039/calls/`.

| Object | Registry / index | Logical descriptor | Header facts |
|---|---|---|---|
| `gConfigMenuDescriptor` | primary 5 -> ov079 | 020c4c60 | 68-byte primary; secondary index 0, work size 0x1c0 |
| `gTutorialMenuDescriptor` | primary 18 -> ov081 | 020c5cc0 | 68-byte primary; secondary index 11, work size 0x63e8 |
| `gOverlay082EntryListDescriptor` | secondary 11 -> ov082 | 020bf6a0 | 64-byte secondary; work size 0x372c |
| `gScoreScreenDescriptor` | secondary 1 -> ov083 | 020bf6a0 | 64-byte secondary; work size 0x76c |
| `gTwoChoiceMenuDescriptor` | primary 7 -> ov084 | 020bfca0 | 68-byte primary; secondary index 1, work size 0x1d4 |
| `gShopMenuDescriptorMiddle` | primary 8 -> ov085 | 020c2360 | 24-byte fragment at logical+8; secondary index 1, work size 0x5ea8; update plus first three input slots |

The shop descriptor is split into three physical objects at logical base ov085:020c2360:

| Existing physical object | Native range / size | Role in the same logical descriptor |
|---|---|---|
| gOv085InitHandlers | [020c2360,020c2368), 8 bytes | init and destroy pointers |
| gShopMenuDescriptorMiddle | [020c2368,020c2380), 24 bytes | update, secondary index, size, input slots+0x14/+0x18/+0x1c |
| gOv085StateHandlers | [020c2380,020c23a4), 36 bytes | remaining nine input slots |

The existing Head/Tail storage must not be merged or mistaken for a separate state machine. The legacy gOv085StateHandlers name also occurs in another bank's descriptor context; bank qualification is mandatory. This block renames only the uniquely identified middle object. No pointer target or addend is rebound.

The config menu is identified by its actual option-navigation/save callbacks. The tutorial descriptor is identified by the tutorial page/entry consumers. The score secondary descriptor exposes the score renderer. The two-choice descriptor uses its two-choice text/selection implementations. Ov082 retains the conservative entry-list role; no unsupported gameplay submenu name is inferred.

## Record-panel tables

All following tables belong to ov086. The packed-bit offset tables are separate from menu node indices even where a legacy shared-source alias uses a similar address suffix. Each EU wrapper selects the actual table.

| Table group | Demonstrated contract | Limits |
|---|---|---|
| Group tier flag bases | Three base IDs added to group; consumer returns last set ordinal+1 | The result is not a popcount and no gameplay difficulty is assigned. |
| Tier/row label IDs | Message indices read by DrawRecordStatRow for the tier and normal row labels | Keep the special row 6 branch and stored trailing label word. |
| Two-bit statistic offsets | Five offsets read with width 2 for group < 5, displayed against 3 | Other groups take another display path; no extension to eight entries. |
| Seven-bit statistic offsets / stat flag IDs | Eight offsets read with width 7, value+1 paired with a per-group flag in row 5 | No time/level/completed/unlocked meaning without separate writer evidence. |
| Flag-count targets / widths / offsets | Row 0 displayed targets; separate packed-bit width/offset pairs used by CountSessionGroupFlags | Targets differ from field widths; do not deduplicate or make them an unlock threshold. |
| Page-node / initial-text-node bases | Separate eight-value tables select nodes during refresh and initial creation | Equal values do not establish shared storage or interchangeable references. |
| Digit-cell X gaps | Nine whole-pixel decrements before x<<12 when placing digit cells | Keep separators, frame 10 and later visibility operations independent. |

The group-entry counts form one eight-value logical sequence split at a physical object boundary:

| Object | Native range | Values |
|---|---|---|
| gRecordGroupEntryCountsHead | [020c2360,020c2368), 8 bytes | 3,6 |
| gRecordGroupEntryCountsTail | [020c2368,020c2380), 24 bytes | 4,1,5,2,4,0 |

CountSetRecordGroupFlags sums earlier group lengths and scans the corresponding flags starting at 0x581. Other group counters share the same lengths. The head is only two words and the tail six; neither is a newly allocated complete array. Naming this distribution does not make every set flag an unlocked record. The final zero-length group is retained.

## Per-object evidence and limits

### `gConfigMenuDescriptor`

Registry overlay ID selects this bank and logical descriptor base 0x20c4c60. Native primary layout is read by overlay039 lifecycle/work-size/input accessors. Callback declarations in the retained source identify the exact owner and operations.

Keep all pointer words, NULL slots, Thumb tags, ID/size words and relocation addends. Primary header differs from secondary: primary+0xc is secondary-index and size+0x10; secondary size is+0xc. This is a rename of the physical object only; legacy pointer-array declarations are not a complete host callback interface.

### `gTutorialMenuDescriptor`

Registry overlay ID selects this bank and logical descriptor base 0x20c5cc0. Native primary layout is read by overlay039 lifecycle/work-size/input accessors. Callback declarations in the retained source identify the exact owner and operations.

Keep all pointer words, NULL slots, Thumb tags, ID/size words and relocation addends. Primary header differs from secondary: primary+0xc is secondary-index and size+0x10; secondary size is+0xc. This is a rename of the physical object only; legacy pointer-array declarations are not a complete host callback interface.

### `gOverlay082EntryListDescriptor`

Registry overlay ID selects this bank and logical descriptor base 0x20bf6a0. Native secondary layout is read by overlay039 lifecycle/work-size/input accessors. Callback declarations in the retained source identify the exact owner and operations.

Keep all pointer words, NULL slots, Thumb tags, ID/size words and relocation addends. Primary header differs from secondary: primary+0xc is secondary-index and size+0x10; secondary size is+0xc. This is a rename of the physical object only; legacy pointer-array declarations are not a complete host callback interface.

### `gScoreScreenDescriptor`

Registry overlay ID selects this bank and logical descriptor base 0x20bf6a0. Native secondary layout is read by overlay039 lifecycle/work-size/input accessors. Callback declarations in the retained source identify the exact owner and operations.

Keep all pointer words, NULL slots, Thumb tags, ID/size words and relocation addends. Primary header differs from secondary: primary+0xc is secondary-index and size+0x10; secondary size is+0xc. This is a rename of the physical object only; legacy pointer-array declarations are not a complete host callback interface.

### `gTwoChoiceMenuDescriptor`

Registry overlay ID selects this bank and logical descriptor base 0x20bfca0. Native primary layout is read by overlay039 lifecycle/work-size/input accessors. Callback declarations in the retained source identify the exact owner and operations.

Keep all pointer words, NULL slots, Thumb tags, ID/size words and relocation addends. Primary header differs from secondary: primary+0xc is secondary-index and size+0x10; secondary size is+0xc. This is a rename of the physical object only; legacy pointer-array declarations are not a complete host callback interface.

### `gShopMenuDescriptorMiddle`

Registry overlay ID selects this bank and logical descriptor base 0x20c2360. Native primary_middle_fragment layout is read by overlay039 lifecycle/work-size/input accessors. Callback declarations in the retained source identify the exact owner and operations.

Keep all pointer words, NULL slots, Thumb tags, ID/size words and relocation addends. Primary header differs from secondary: primary+0xc is secondary-index and size+0x10; secondary size is+0xc. This is a rename of the physical object only; legacy pointer-array declarations are not a complete host callback interface. This 24-byte object starts at logical descriptor+8 and ends after input slot+0x1c. The 8-byte prefix gOv085InitHandlers and 36-byte tail gOv085StateHandlers are separate existing objects; do not merge/reslice or treat this fragment as a whole descriptor.

### `gRecordGroupTierFlagBases`

Three base flag IDs are each added to the supplied group index. The consumer tracks the last set ordinal and returns ordinal+1, or 0 when none is set.

Array order controls the reported tier ordinal; it is not a count of all set flags and does not assign gameplay difficulty meanings.

### `gRecordStatTierLabelIds`

Four message IDs indexed by the tier argument when rendering stat row 4. EU wrapper aliases old20e8 to this 2108 object.

Keep all four labels and native unchecked index behavior; no new tier validation or message remapping.

### `gRecordGroupTwoBitStatOffsets`

Five persistent/session packed-bit offsets, used with width 2 for group < 5 and rendered against 3 in stat row 1.

Only five group slots are represented. Other groups use a separate row path; do not extend the table to eight by analogy.

### `gRecordGroupSevenBitStatOffsets`

Eight bit offsets read with width 7; the row 5 consumer adds 1 to the read value before formatting.

Do not attach level/time/percentage units absent a separate writer proof. Preserve width, arithmetic and per-group index.

### `gRecordGroupStatFlagIds`

Eight per-group flag IDs tested with IsSessionFlagSet and passed as the second stat-row 5 argument.

This proves flag-driven presentation, not a generic unlocked/completed meaning for all consumers.

### `gRecordStatRowLabelIds`

Seven row-to-message IDs used by the normal stat-label renderer. Row6 takes its own special branch before the normal lookup.

Keep stored trailing entry and special row 6 path. Do not remove a word merely because the current normal branch skips it.

### `gRecordGroupFlagCountTargets`

Eight displayed row 0 comparison/target counts paired with CountSessionGroupFlags(group).

These are displayed targets here; no unlock cutoff, reward condition or percentage is introduced by naming the table.

### `gRecordGroupFlagFieldWidths`

Eight packed-bit field widths paired with group offsets. CountSessionGroupFlags reads that field and counts only width[index] low bits.

Do not normalize widths or merge with displayed target counts, which differ for some groups.

### `gRecordPageNodeBaseIndices`

Eight page-index-to-node bases; the consumer selects pageNodes[base[pageIndex]+stepCount] during layout refresh.

This is distinct physical storage from the equal-valued init text-node table; preserve both registrations/references.

### `gRecordGroupFlagFieldOffsets`

Eight packed-bit offsets paired with the width table for popcount-style session-group statistics.

Preserve exact offsets and width pairing. They are independent of row 5 seven-bit statistic offsets.

### `gRecordInitialTextNodeBaseIndices`

Initial group-to-text-node bases copied by InitRecordPanelText; creates/selects the node for each group, then its subpages.

Equal values to page-node bases do not make a shared allocation. EU alias old 226c resolves to this 228c object, not the packed-bit offset table.

### `gRecordDigitCellXGaps`

Nine pixel X gaps subtracted while placing digit cells from x=0x43; y is converted to native fixed-point separately.

Gaps are whole pixels before x<<12. Keep all nine cells and subsequent frame 10/separator/visibility behavior.

### `gRecordGroupEntryCountsHead`

First two u32 group counts of the contiguous eight-count table starting at 0x020c2360. Counter routines sum earlier group lengths and scan flags starting at 0x581.

Only 8 bytes are this symbol. The next six counts are a separate 24-byte object; no merge/reslice or unlocked semantics from bit-set count alone.

### `gRecordGroupEntryCountsTail`

Remaining six u32 group counts immediately after the head; groups 2..7 complete the same eight-count logical table.

Tail is not a standalone six-group table or descriptor. Preserve contiguous layout and the final zero count.

## Native layout checks

The pre-existing ELF symbol extents and data words agree with the EU image for all 20 objects after resolving their existing ABS32 callback relocations through the same bank's function metadata. Stored NULL words, ARM/Thumb tags, constants and source grouping remain unchanged. No compilation or official matching gate is claimed by this review.

For reproducible inspection:

```powershell
Get-Content eu/src/overlays/ov039/calls/UpdateSubOverlayHandlers.c
Get-Content eu/src/ov085/data/Data_ov085_020c2368.c
Get-Content eu/src/overlays/ov086/calls/CountSetRecordGroupFlags.c
Get-Content eu/src/overlays/ov086/calls/CountSessionGroupFlags.c
Get-Content eu/src/overlays/ov086/calls/DrawRecordPanelStats.c
Get-Content eu/src/overlays/ov086/calls/RefreshRecordPageLayout.c
```


## Byte-exact validation

74 DATA identities retain their source paths, native sizes and storage.
All 191 affected official function checks pass. A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 259 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
