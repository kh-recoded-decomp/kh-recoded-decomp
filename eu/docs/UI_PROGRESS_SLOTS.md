# UI progress, slot construction and state views

These names describe observed operations on their particular menu work owners.
They do not assign gameplay meanings to zero states, counters or flag bits.
The analogous overlay copies remain separate functions with their own bindings.

| Previous name | Current name | Established behavior |
|---|---|---|
| `func_ov077_020c7ce8` | `UpdateItemScreenCharUpload` | Same paused/parity-gated2400h copy to BG1char+140h and idle-renderer update as075/076, using gItemListPanelWork. |
| `func_ov077_020c7d44` | `BuildItemScreenFrameTilemap` | Same32x24 three-style frame-tilemap algorithm as075/076 with item-screen frame table. |
| `func_ov077_020c8188` | `HandleItemScreenTextTag` | Same colorsF2/highlight/FA and1F centered-next-line tag callback, using MeasureTextLine_020c8120 and item-screen owner. |
| `func_ov095_020c0148` | `CreateItemGridSlots` | Builds manager at180h from container entry31h and creates13 grid slots using gItemGridLayoutRecords with14h stride. |
| `func_ov091_020bf7a8` | `CreateReportTopPanelSlots` | Initializes managerF4h from entry7, binds extra resource, creates6slots with18h descriptor stride; initializes second manager6528h from entry4 and creates one slot. |
| `func_ov095_020c1628` | `UpdateItemGridBackgroundVariant` | Changes BG3screen to resource154h when selected variant1 and stored variant1, marks stored2; otherwise restores resource144h when stored2, marks1. |
| `func_ov091_020c12d4` | `UpdateReportTopFlagProgress` | Counts8table-selected global flags, sets11B2h+i for found entries, marksnew entry category(2,2) when unacknowledged, stores percentageC9FCh. |
| `func_ov091_020c1370` | `UpdateReportTopCounterProgress` | Counts40nonzero17-bit counters selected by table, sets1172h+i, marks new-entry category(2,3) when unacknowledged, stores percentCA00h. |
| `func_ov076_020c8b48` | `IsSlotMenuTotalWithinLimit` | Sums eight unsigned-halfword values at49818h and returns total<=100. |
| `func_ov076_020ca644` | `ApplySlotMenuItemReward` | Called by ItemList_ReturnCursorItem with selected definition reward. Dispatches B7h..BDh into counters, level-threshold helper, resets and feedback requests. |
| `func_ov077_020c7678` | `ApplyItemScreenItemReward` | Equivalent selected-item reward dispatch B7h..BDh, using item-screen helper bindings and QueueAndPlaySound feedback. |
| `func_ov075_020cecf0` | `AreItemPickerSessionStatesZero` | Returns true only when every session state word selected by global byte count is zero; zero count is true. |
| `func_ov076_020cab00` | `AreSlotMenuSessionStatesZero` | Same zero-state scan for slot-menu copy; global array begins session+27A8h. |
| `func_ov077_020c7b34` | `AreItemScreenSessionStatesZero` | Same zero-state scan for item-screen copy. |
| `func_ov091_020c1774` | `GetReportTopMode` | ReturnsCC68h word; paired SetSceneMode writes same field and UpdateRecordMenuScene dispatches by getter. |
| `CountUnlockedRecordGroupEntries` | `CountSetRecordGroupFlags` | Counts set flags at0x581+group base+index; no unlocked/completed meaning assigned. |

## Record-group flag-count correction

`CountSetRecordGroupFlags` sums preceding group sizes to obtain a base and
counts set session bits at `0x581 + base + index`. Its earlier descriptive name
`CountUnlockedRecordGroupEntries` overstated what those bits mean. The count
consumer displays it as a statistic; the availability consumer separately
requires the bit to be clear and checks a minimum progress level. Neither
consumer identifies a setter/event contract that proves unlocked, completed or
collected semantics. The new name deliberately describes the set-bit count.
The implementation, its group indexing and its unchecked bounds are unchanged.

## Parallel UI rendering copies

The item-screen upload, frame and text-tag helpers extend the existing families
in [UI_RENDER_HELPERS.md](UI_RENDER_HELPERS.md). Upload eligibility uses pause,
VBlank parity and upload suppression; renderer busy only gates its update call.
The frame builder retains the item-screen tile table and native narrowed
32x24 bounds arithmetic. The tag callback retains its own measurement helper,
work owner, known colors and centering behavior. Similar code does not make
those bindings interchangeable or justify merging the entry points.

## Slot managers and background selection

`CreateItemGridSlots` initializes the manager at work `+0x180` from container
entry `0x31`, then creates 13 slots using `0x14`-byte layout records.
`CreateReportTopPanelSlots` initializes the manager at `+0xf4` from entry 7,
binds its extra resource and creates six slots with `0x18`-byte record stride.
It also initializes a second manager at `+0x6528` from entry 4 and creates one
slot. These accesses establish counts and record strides, not complete host
manager/descriptor definitions. The extra binding call is retained even though
its old `PXI` helper label is misleading.

`UpdateItemGridBackgroundVariant` swaps the BG3 screen resource between the
native IDs `0x154` and `0x144`, recording the corresponding variant state.
It copies a 32x19 tile area and derives source dimensions by shifting the pixel
dimensions right by three. It avoids a repeated copy when the stored variant
already matches the relevant branch; it adds no new clipping policy.

## Flag/counter progress and rewards

`UpdateReportTopFlagProgress` examines eight table-selected global flags.
It sets report flags `0x11b2 + i`, checks acknowledgment bits `0x1262 + i`,
marks the existing new-entry category `(2, 2)` where needed, and writes the
percentage `count * 100 / 8` at work `+0xc9fc`.

`UpdateReportTopCounterProgress` checks 40 table-selected 17-bit counters for
nonzero values. It sets flags `0x1172 + i`, uses acknowledgment bits
`0x1222 + i`, marks category `(2, 3)`, and writes `count * 100 / 40` at
`+0xca00`. These numeric mappings are established; their specific gameplay
categories are not inferred from the percentages.

The two item-reward helpers dispatch IDs `0xb7..0xbd` to the existing counter,
level-threshold, reset and feedback operations. They retain their distinct menu
bindings and the original effect/call order; unknown IDs are ignored. The
selection/stock-consumption caller and these effect dispatchers have separate
responsibilities. The old `LoadOverlaySync` dependency name is not proof that
its effect loads an overlay; that dependency needs its own semantic audit.

`IsSlotMenuTotalWithinLimit` sums eight unsigned halfwords at work `+0x49818`
and returns whether the sum is at most 100, including equality. Their gameplay
units remain unnamed. Eight u16 values fit in the native 32-bit sum.

## State and mode interfaces

The three `Are...SessionStatesZero` helpers read the shared session-state array
starting at `+0x27a8`, for the number of entries selected by the global byte
count. Zero entries yield true. The helpers add no count/capacity or null check,
and zero is not renamed idle, ready or network-quiescent without a protocol.

`GetReportTopMode` reads the mode word at work `+0xcc68`. `SetSceneMode` writes
that same word and `UpdateRecordMenuScene` dispatches on it. The getter now
states its actual single work-pointer input and u32 result rather than three
additional unused generated register slots. It remains a native byte view,
not a complete report-work layout or a promise of host pointer-sized offsets.
Other shared caller declarations still need normalization before a host API.

## Reproduction

From `eu/`:

```sh
python tools/rebuild_index.py --write --refresh-reloc-names
python tools/verify_idx.py src/overlays/ov086/calls/CountSetRecordGroupFlags.c CountSetRecordGroupFlags
python tools/verify_idx.py src/overlays/ov077/calls/UpdateItemScreenCharUpload.c UpdateItemScreenCharUpload --thumb
python tools/verify_idx.py src/overlays/ov091/calls/UpdateReportTopFlagProgress.c UpdateReportTopFlagProgress
python tools/verify_idx.py src/overlays/ov091/auto/GetReportTopMode.c GetReportTopMode
bash tools/gate.sh
```

All 16 direct official byte/relocation checks pass. All 35 reviewed production
functions retain instructions, resolved targets/types and addends. The fresh
official gate passes 108/108 modules with every hash unchanged. Naming and the
getter interface recovery add no C or DATA reconstruction credit.
