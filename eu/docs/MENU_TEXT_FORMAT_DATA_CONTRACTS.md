# Menu numeric and text format DATA

These 25 DATA names identify the format objects consumed by status, item/slot, save, tutorial, score, shop and report text routines. The original C files and object grouping remain unchanged. The names follow both the stored text and real formatter callers; identical text in another overlay remains a separate object.

Every object below stores 16-bit code units (`u16[]`). Native size includes the terminator and any trailing zero words. Some legacy extern declarations use char pointers; a name change does not retype those consumers or substitute the host printf implementation.

## Identity, native extent and consumer evidence

Source paths are retained. Consumer paths below are EU wrappers/direct implementations; shared bodies must be interpreted with those wrappers' aliases.

| EU identity | Original symbol | Descriptive symbol | Stored format | Native bytes | Stable source | Representative consumer |
|---|---|---|---|---:|---|---|
| ov073:020c41a0 | `data_ov073_020c41a0` | `gStatusHeaderTextFormat` | `%s` | 8 | `eu/src/ov073/data/Data_ov073_020c41a0.c` | `eu/src/overlays/ov073/calls/OpenStatusPageView.c` |
| ov073:020c41d4 | `data_ov073_020c41d4` | `gStatusNumberFormat` | `%d` | 8 | `eu/src/ov073/data/Data_ov073_020c41d4.c` | `eu/src/overlays/ov073/calls/DrawRecordSlotRows.c` |
| ov073:020c41ec | `data_ov073_020c41ec` | `gStatusHpValueFormat` | `%3d` | 8 | `eu/src/ov073/data/Data_ov073_020c41ec.c` | `eu/src/overlays/ov073/calls/RefreshStatusMenuData.c` |
| ov073:020c41f4 | `data_ov073_020c41f4` | `gStatusHpRatioFormat` | `%3d / %3d` | 20 | `eu/src/ov073/data/Data_ov073_020c41ec.c` | `eu/src/overlays/ov073/calls/RefreshStatusMenuData.c` |
| ov073:020c4208 | `data_ov073_020c4208` | `gStatusDecimalMultiplierFormat` | `x %d.%d` | 16 | `eu/src/ov073/data/Data_ov073_020c4208.c` | `eu/src/overlays/ov073/calls/RefreshStatusMenuData.c` |
| ov073:020c4218 | `data_ov073_020c4218` | `gStatusDecimalPercentFormat` | `%d.%d%%` | 16 | `eu/src/ov073/data/Data_ov073_020c4218.c` | `eu/src/overlays/ov073/calls/RefreshStatusMenuData.c` |
| ov073:020c4228 | `data_ov073_020c4228` | `gStatusWholeMultiplierWithDecimalZeroFormat` | `x %d.0` | 16 | `eu/src/ov073/data/Data_ov073_020c4228.c` | `eu/src/overlays/ov073/calls/RefreshStatusMenuData.c` |
| ov073:020c4238 | `data_ov073_020c4238` | `gStatusIntegerMultiplierFormat` | `x %d` | 12 | `eu/src/ov073/data/Data_ov073_020c4238.c` | `eu/src/overlays/ov073/calls/RefreshStatusMenuData.c` |
| ov073:020c4244 | `data_ov073_020c4244` | `gStatusReciprocalMultiplierFormat` | `1/%d` | 28 | `eu/src/ov073/data/Data_ov073_020c4238.c` | `eu/src/overlays/ov073/calls/RefreshStatusMenuData.c` |
| ov076:020cd370 | `data_ov076_020cd370` | `gSlotMenuWidth2CountFormat` | `x%2d` | 12 | `eu/src/ov076/data/Data_ov076_020cd370.c` | `eu/src/overlays/ov076/calls/SlotMenu_DrawPanelLabel.c` |
| ov076:020cd388 | `data_ov076_020cd388` | `gSlotPickerCountFormat` | `x%d` | 8 | `eu/src/ov076/data/Data_ov076_020cd388.c` | `eu/src/overlays/ov076/calls/ItemPicker_DrawRows_020c9db8.c` |
| ov077:020ca324 | `data_ov077_020ca324` | `gEquipmentItemCountFormat` | `x%d` | 8 | `eu/src/ov077/data/Data_ov077_020ca324.c` | `eu/src/overlays/ov077/calls/ItemListPanel_Create.c` |
| ov080:020c5dfc | `data_ov080_020c5dfc` | `gSaveSlotNumberFormat` | `%d` | 8 | `eu/src/ov080/data/Data_ov080_020c5dfc.c` | `eu/src/overlays/ov080/calls/BuildSlotSummary.c` |
| ov080:020c5e04 | `data_ov080_020c5e04` | `gSaveSlotTitleFormat` | `%s` | 28 | `eu/src/ov080/data/Data_ov080_020c5dfc.c` | `eu/src/overlays/ov080/calls/BuildSlotSummary.c` |
| ov081:020c5d60 | `data_ov081_020c5d60` | `gTutorialPageCounterFormat` | ` %d/%d` | 16 | `eu/src/ov081/data/Data_ov081_020c5d60.c` | `eu/src/overlays/ov081/calls/DrawListPageCounter.c` |
| ov083:020bf6f8 | `data_ov083_020bf6f8` | `gScoreScreenNumberFormat` | `%d` | 8 | `eu/src/ov083/data/Data_ov083_020bf6f8.c` | `eu/src/overlays/ov083/calls/UpdateScoreScreen.c` |
| ov083:020bf700 | `data_ov083_020bf700` | `gScoreScreenWidth3RatioFormat` | `%3d / %3d` | 32 | `eu/src/ov083/data/Data_ov083_020bf6f8.c` | `eu/src/overlays/ov083/calls/UpdateScoreScreen.c` |
| ov085:020c23bc | `data_ov085_020c23bc` | `gShopNumberFormat` | `%d` | 8 | `eu/src/ov085/data/Data_ov085_020c23bc.c` | `eu/src/overlays/ov085/calls/FormatItemValue.c` |
| ov086:020c2ff0 | `data_ov086_020c2ff0` | `gRecordStatTextFormat` | `%s` | 8 | `eu/src/overlays/ov086/data/Data_ov086_020c2ff0.c` | `eu/src/overlays/ov086/calls/DrawRecordStatRow.c` |
| ov089:020c0674 | `data_ov089_020c0674` | `gEntryCarouselTitleFormat` | `%s%s%s` | 44 | `eu/src/ov089/data/Data_ov089_020c0674.c` | `eu/src/overlays/ov089/calls/DrawEntryMenuTexts_020bf49c.c` |
| ov091:020c2c7c | `data_ov091_020c2c7c` | `gReportEntryCountOutOf30Format` | `%d/30` | 12 | `eu/src/overlays/ov091/data/Data_ov091_020c2c7c.c` | `eu/src/overlays/ov091/calls/DrawRecordSummaryText.c` |
| ov093:020c4d78 | `data_ov093_020c4d78` | `gTrophyValueWidth5Format` | `%5d` | 8 | `eu/src/ov093/data/Data_ov093_020c4d78.c` | `eu/src/overlays/ov093/calls/RedrawEntryPanelText.c` |
| ov093:020c4d80 | `data_ov093_020c4d80` | `gTrophyPercentValueFormat` | `%d%` | 8 | `eu/src/ov093/data/Data_ov093_020c4d80.c` | `eu/src/overlays/ov093/calls/RedrawEntryPanelText.c` |
| ov095:020c28cc | `data_ov095_020c28cc` | `gItemReportRecipePairFormat` | `%s + %s` | 20 | `eu/src/overlays/ov095/data/Data_ov095_020c28cc.c` | `eu/src/overlays/ov095/calls/RefreshItemReportText.c` |
| ov099:020c279c | `data_ov099_020c279c` | `gEnemyViewerWidth2NumberFormat` | `%2d` | 8 | `eu/src/ov099/data/Data_ov099_020c279c.c` | `eu/src/overlays/ov099/calls/DrawEntryStatsPanels.c` |

## Field and formatter behavior

- `gStatusHeaderTextFormat`: Header-text string substitution, used by SetStatusHeaderText/ResetStatusHeaderText and status page setup.
- `gStatusNumberFormat`: Decimal numeric text reused for status level/attack/magic/defense/capacity/experience and remaining values; it is not a single stat ID.
- `gStatusHpValueFormat`: Width 3 value for max-HP comparisons in status data refresh.
- `gStatusHpRatioFormat`: Current/max HP pair formatted with two width 3 decimal fields and literal spaces/slash.
- `gStatusDecimalMultiplierFormat`: One-decimal multiplier columns receive whole/tenths inputs in status bonus display.
- `gStatusDecimalPercentFormat`: One-decimal percent columns receive whole/tenths inputs; the final percent is escaped in the stored format.
- `gStatusWholeMultiplierWithDecimalZeroFormat`: Whole multiplier displayed with literal decimal zero in status bonus column 4.
- `gStatusIntegerMultiplierFormat`: Integer multiplier branch selected when scaleBonus==0x1000; paired with reciprocal format for other values.
- `gStatusReciprocalMultiplierFormat`: Reciprocal multiplier branch used with the quotient 0x1000/scaleBonus.
- `gSlotMenuWidth2CountFormat`: Slot panel label formats slotNumbers[slot] using x and a width 2 decimal field.
- `gSlotPickerCountFormat`: Item-picker row remaining count uses x followed by decimal count.
- `gEquipmentItemCountFormat`: Equipment item-picker row remaining count uses the parallel distinct x/count object.
- `gSaveSlotNumberFormat`: Save-slot summary level+1 and money numeric fields.
- `gSaveSlotTitleFormat`: Save-slot summary title string returned by its saved-title lookup.
- `gTutorialPageCounterFormat`: Tutorial list page indicator formats before+1 and total, retaining the leading space.
- `gScoreScreenNumberFormat`: Score-screen integer marks, values and counters passed to DrawFormattedText.
- `gScoreScreenWidth3RatioFormat`: Score-screen paired baseA/baseB width 3 values.
- `gShopNumberFormat`: Shop quantity, unit price, total, current money and projected money decimal text.
- `gRecordStatTextFormat`: Record-stat text substitution used repeatedly for fallback stat-row text.
- `gEntryCarouselTitleFormat`: Entry-carousel title concatenates name, separator and localized grid/table text without extra literal separators.
- `gReportEntryCountOutOf30Format`: Report summary scene values displayed with the literal denominator 30.
- `gTrophyValueWidth5Format`: Trophy entry numeric value rendered with width 5 in the value branch.
- `gTrophyPercentValueFormat`: Trophy entry percent-value branch uses the exact stored trailing-percent sequence.
- `gItemReportRecipePairFormat`: Item-report recipe text combines the two material names with literal space-plus-space.
- `gEnemyViewerWidth2NumberFormat`: Enemy-viewer count/stat panel formats its numeric count with width 2.

Status formats cover both current and preview stats. The width 3 HP value differs from the two-field current/max ratio. Multiplier/percentage formats receive their actual whole/tenths or quotient inputs; this block does not recalculate those values or assign new gameplay units. The generic status/shop decimal formats are reused across several fields, so their names do not imply a single stat or currency input.

The tutorial counter retains its leading space. Carousel titles concatenate three supplied strings without adding literal separators. Report-top count text retains the literal denominator 30. The item-report recipe format inserts exactly a space, plus sign and space between two material-name strings.

The trophy percent-value object contains the exact sequence `%d%`, while the status decimal-percent object contains `%d.%d%%`. Preserve that distinction. This change neither normalizes the former to `%d%%` nor assumes that host printf parsing/error behavior matches the project's formatter.

## Adjacent path references in the two item pickers

The slot-picker and equipment-item count format objects at ov076:020cd388 and ov077:020ca324 each occupy eight bytes (`x%d` in 16-bit code units plus terminator). Besides the row formatter, each panel constructor computes a byte addend +8 from that symbol. In the native image, that address reaches the separately named adjacent ASCII `ui/menu/str/&/matrix.s.z` path object.

The relevant source chain is `MenuPanel_Create_020cbccc.c` through its ov076 wrapper and `func_ov077_020c8d00.c` through ItemListPanel_Create in ov077. The path is not part of the eight-byte format array. Keep both physical boundaries and all relocation/addend relationships in the byte-exact build. A future port can express the adjacent path through its real resource identity once that separate interface is reconstructed; renaming the format alone does not rebind it.

## Storage and evidence limits

The observed C array extents and pre-existing ELF symbol extents agree with the original EU bytes for all 25 objects. This is data/identity evidence; official compilation and project matching remain integration checks. No format text, padding, pointer tag, relocation, display calculation or formatter-call order is changed.

The remaining ov087 object at 020c7e90 stores `%s %s`, but an actual consumer was not established in this review. Its numeric name is retained rather than assigning a title/name-pair purpose from the bytes alone.

For reproduction, read the stable source and the corresponding consumer in the identity table. Examples:

```powershell
Get-Content eu/src/overlays/ov073/calls/RefreshStatusMenuData.c
Get-Content eu/src/overlays/ov085/calls/RedrawShopMenu.c
Get-Content eu/src/overlays/ov093/calls/RedrawEntryPanelText.c
Get-Content eu/src/overlays/ov095/calls/RefreshItemReportText.c
```


## Byte-exact validation

65 DATA identities retain their source paths, native sizes and storage.
51/52 affected official function checks pass; the remaining
1 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 102 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
