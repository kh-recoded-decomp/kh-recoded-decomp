# Overlay 087 carousel and choice data

These identities describe the data used by the overlay 087 carousel, choice windows and item-availability check. Keep the original source filenames, physical definitions, sizes, binding, alignment and adjacency. This document supplies source and native-data evidence; it does not claim a new compile or official byte-exact gate.

| Identity | Name | Bytes | Active source | Direct consumer |
|---|---|---:|---|---|
| `data_ov087_020c7c90` | `gOv087TwoChoiceMessageIds` | 8 | `eu/src/ov087/data/Rodata_ov087_020c7c90.c` | `eu/src/overlays/ov087/calls/OpenTwoChoiceMenu.c` |
| `data_ov087_020c7c98` | `gOv087HiddenArrowWidgetIds` | 8 | `eu/src/ov087/data/Rodata_ov087_020c7c98.c` | `eu/src/overlays/ov087/calls/HideChoiceWidgets_020c4a48.c` |
| `data_ov087_020c7ca0` | `gOv087ConfirmWidgetIds` | 8 | `eu/src/ov087/data/Rodata_ov087_020c7ca0.c` | `eu/src/overlays/ov087/calls/ShowConfirmWindows.c` |
| `data_ov087_020c7ca8` | `gOv087VariantMessageIds` | 12 | `eu/src/ov087/data/Rodata_ov087_020c7ca0.c` | `eu/src/overlays/ov087/calls/ShowVariantMessageAndSetFlag.c` |
| `data_ov087_020c7cb4` | `gOv087CarouselPositionTemplate` | 12 | `eu/src/ov087/data/Rodata_ov087_020c7cb4.c` | `eu/src/overlays/ov087/calls/DrawEntryCarousel_020c6ca4.c` |
| `data_ov087_020c7cc0` | `gOv087HiddenChoiceWidgetIds` | 12 | `eu/src/ov087/data/Rodata_ov087_020c7cc0.c` | `eu/src/overlays/ov087/calls/HideChoiceWidgets_020c4a48.c` |
| `data_ov087_020c7ccc` | `gOv087VariantSessionFlagOffsets` | 12 | `eu/src/ov087/data/Rodata_ov087_020c7ccc.c` | `eu/src/overlays/ov087/calls/ShowVariantMessageAndSetFlag.c` |
| `data_ov087_020c7cd8` | `gOv087ChoiceMessageIds` | 12 | `eu/src/ov087/data/Rodata_ov087_020c7cd8.c` | `eu/src/overlays/ov087/calls/RefreshChoiceMenu_020c4d6c.c` |
| `data_ov087_020c7ce4` | `gOv087ShownChoiceWidgetIds` | 12 | `eu/src/ov087/data/Rodata_ov087_020c7ce4.c` | `eu/src/overlays/ov087/calls/ShowChoiceWindows.c` |
| `data_ov087_020c7cf0` | `gOv087TestedSessionFlagOffsets` | 12 | `eu/src/ov087/data/Rodata_ov087_020c7cf0.c` | `eu/src/overlays/ov087/calls/IsSessionFlagClear.c` |
| `data_ov087_020c7cfc` | `gOv087InfoTextFrameTemplate` | 16 | `eu/src/ov087/data/Rodata_ov087_020c7cf0.c` | `eu/src/overlays/ov087/calls/InitPanelTextLayers.c` |
| `data_ov087_020c7d0c` | `gOv087WidgetManagerConfigTemplate` | 16 | `eu/src/ov087/data/Rodata_ov087_020c7d0c.c` | `eu/src/overlays/ov087/calls/SetupPanelWidgetHandlers.c` |
| `data_ov087_020c7d1c` | `gOv087CarouselRecordIds` | 32 | `eu/src/ov087/data/Rodata_ov087_020c7d0c.c` | `eu/src/overlays/ov087/calls/LoadCarouselModels.c` |
| `data_ov087_020c7d3c` | `gOv087CarouselInfoFileIds` | 32 | `eu/src/ov087/data/Rodata_ov087_020c7d3c.c` | `eu/src/overlays/ov087/calls/LoadCarouselModels.c` |
| `data_ov087_020c7d5c` | `gOv087ItemRangesHead` | 4 | `eu/src/ov087/data/Rodata_ov087_020c7d5c.c` | `eu/src/overlays/ov087/calls/RefreshSelectedEntryInfo.c` |
| `data_ov087_020c7d60` | `gOv087ItemRangesTail` | 60 | `eu/src/ov087/data/Rodata_ov087_020c7d5c.c` | `eu/src/overlays/ov087/calls/RefreshSelectedEntryInfo.c` |
| `data_ov087_020c7e2c` | `gOv087ItemAvailabilityThresholds` | 100 | `eu/src/ov087/data/Data_ov087_020c7e2c.c` | `eu/src/overlays/ov087/calls/RefreshSelectedEntryInfo.c` |
| `data_ov087_020c7e90` | `gOv087EntryNameSuffixFormat` | 12 | `eu/src/ov087/data/Data_ov087_020c7e90.c` | `eu/src/overlays/ov087/calls/RefreshSelectedEntryInfo.c` |

## Operations and limits

- `gOv087TwoChoiceMessageIds`: Two message indices {5,6} are read from the scene text bank and drawn into choice windows 0 and 1. Message indices, not widget or resource IDs.
- `gOv087HiddenArrowWidgetIds`: Widget IDs {7,8} are looked up and hidden after the three choice widgets. A separate physical copy from confirm widget IDs even though values agree.
- `gOv087ConfirmWidgetIds`: Widget IDs {7,8} are made visible while two confirm windows are placed; focus is then set to widget 8. Do not merge with the separate hide-only pair.
- `gOv087VariantMessageIds`: Variant indexes three message IDs {0x1a,0x1b,0x1c} before drawing centered prompt text. The valid variant domain is not expanded or bounds-checked by this rename.
- `gOv087CarouselPositionTemplate`: VecFx32 {0,0x1000,0x5000} is copied locally; x is replaced per visible entry while y/z remain from this template. Fixed-point position, not a unit vector or camera position.
- `gOv087HiddenChoiceWidgetIds`: Widget IDs {2,3,4} are looked up and hidden. Separate physical copy from the show-choice array.
- `gOv087VariantSessionFlagOffsets`: Variant selects {0x74,0x75,0x76}; caller adds 0xf50 and sets the resulting session flag. Offsets, not full session IDs; no unlock/completion meaning is assigned.
- `gOv087ChoiceMessageIds`: Three message indices {4,0,1} select choice text; kind 6 starts from element 1. Choice display routing is proved; no names for the gameplay choices are inferred.
- `gOv087ShownChoiceWidgetIds`: Widget IDs {2,3,4} are made visible and their alternate subitem values applied for up to three windows. Count is capped at 3; there is no new lower-bound guard.
- `gOv087TestedSessionFlagOffsets`: Index selects {0x74,0x75,0x76}; caller adds 0xf50 and tests that session flag is clear. Distinct physical copy from set-flag offsets; not named unlocked.
- `gOv087InfoTextFrameTemplate`: Eight u16 values initialize info text frame {x=8,y=3,width=16,height=2,charBase=32,palette=15,hSpace=0,vSpace=0}; local copy is edited for later layers. Preserve 16-byte frame; later edits are to the local copy.
- `gOv087WidgetManagerConfigTemplate`: Four-word config {0,1,0,0} is copied locally; first word is replaced by BuildSlotImageParams(2,0x13) before InitObjManagerAndMark. Only first word has a demonstrated cell-file role; remaining words keep opaque semantics.
- `gOv087CarouselRecordIds`: Eight record IDs are indexed by effective carousel entry ID and passed to InitSharedRecordAndDispatchAlt through LoadCarouselModel. Record IDs are distinct from the info-file IDs in the following physical array.
- `gOv087CarouselInfoFileIds`: Eight file IDs are indexed by effective entry ID, passed through BuildSlotImageParams(2,id), loaded from heap tail and freed after model binding. The center model uses separate literal IDs and is not indexed through these arrays.
- `gOv087ItemRangesHead`: First word of eight logical {firstItem,itemCount} records; firstItem of record 0 is 0. Physical size is 4 bytes; the remaining 60 bytes are a separate object. Keep adjacency and physical split.
- `gOv087ItemRangesTail`: Remaining 15 words of eight logical {firstItem,itemCount} records, beginning with record 0 itemCount=3. Preserve 60-byte extent and address relation head+4; do not treat this as fifteen independent ranges.
- `gOv087ItemAvailabilityThresholds`: 25 integer thresholds are compared <= GetPlayerEntryCount(0,9) while scanning a selected item range and requiring session flag itemIndex+0x581 to be clear. Numeric threshold role is proved; no gameplay level or unlock semantics are inferred. Consumer also addresses the following format at +0x64.
- `gOv087EntryNameSuffixFormat`: UTF16 format "%s %s" joins selected entry name with message 0x1d or 0x1e for IDs 5 or 6. Access is via thresholds base+0x64 in ItemUnlockData.nameFormat. Physical format is six u16/12 bytes, a separate object after the 100-byte thresholds. Preserve cross-object contiguous access; this closes the previously retained consumer-evidence case.

## Logical tables crossing physical definitions

`RefreshSelectedEntryInfo.c` aliases the shared source base `data_ov087_020c7d3c` to EU `0x020c7d5c`. The eight logical item ranges are `{0,3}`, `{3,6}`, `{9,4}`, `{13,1}`, `{14,5}`, `{19,2}`, `{21,4}`, `{25,0}`. Their physical storage remains a 4-byte head followed by a 60-byte tail.

The same wrapper aliases the shared `ItemUnlockData` base `data_ov087_020c7e0c` to EU `0x020c7e2c`. That view contains 25 integer thresholds and then `u16 nameFormat[6]`, so the format read at base + `0x64` is the separate physical object at `0x020c7e90`. For selected IDs 5 and 6, the formatter combines the entry name and suffix message `0x1d` or `0x1e` using `%s %s`. Preserve both definitions and their adjacency. This access supplies consumer evidence for the format despite the absence of a direct symbol reference.

Availability requires the per-item threshold to be at most `GetPlayerEntryCount(0,9)` and the session flag `itemIndex + 0x581` to be clear, alongside the existing selected-ID/mode exclusions. The table does not establish the gameplay meaning of the progress selector or of a set flag.

Repeated widget-ID and flag-offset values occur in distinct physical copies. They remain distinct objects. The carousel resource arrays contain record IDs and info-file IDs respectively; effective entry IDs may substitute the final entry, while the center model uses separate literal resources.

## Reproducing the evidence

Read `eu/src/overlays/ov087/calls/RefreshSelectedEntryInfo.c` with `src/ov087/panel_state/RefreshSelectedEntryInfo_020c5ef0.c` to apply the EU aliases. Read `eu/src/overlays/ov087/calls/LoadCarouselModels.c` directly for the two resource arrays. `eu/config/arm9/overlays/ov087/delinks.txt` selects the physical source owners listed above. Each existing object symbol has the listed size, no interior relocations, and the same bytes as the corresponding range in `eu/dsd_extract/arm9_overlays/ov087.bin`; native base and code size are in `eu/dsd_extract/arm9_overlays/overlays.yaml`. Symbol renaming still requires the official project validation during integration.


## Byte-exact validation

98 DATA identities retain their source paths, native sizes and storage.
All 103 affected official function checks pass. A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 180 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
