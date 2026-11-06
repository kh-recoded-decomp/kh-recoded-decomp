# Report UI and popup data contracts

The report-top menu (overlay 091) and trophy-report menu (overlay 093) use the following layouts, formats, task descriptors and work-pointer globals. Keep original active source files, physical definitions, allocation sizes, binding and relocations. The evidence below is a read-only review; integration still requires compilation and the official byte-exact checks.

| Identity | Name | Bytes | Active source | Direct consumer |
|---|---|---:|---|---|
| `data_ov091_020c2834` | `gReportTopEntrySceneIds` | 8 | `eu/src/overlays/ov091/data/Rodata_ov091_020c2834.c` | `eu/src/overlays/ov091/calls/OpenSelectedEntryScene.c` |
| `data_ov091_020c2a50` | `gReportTopScrollListTemplate` | 44 | `eu/src/overlays/ov091/data/Data_ov091_020c2a50.c` | `eu/src/overlays/ov091/calls/InitRecordMenuScene.c` |
| `data_ov091_020c2bd4` | `gReportTopUpperPanelLayouts` | 144 | `eu/src/overlays/ov091/data/Data_ov091_020c2ad8.c` | `eu/src/overlays/ov091/calls/CreateReportTopPanelSlots.c` |
| `data_ov091_020c2c88` | `gReportTopSummaryPopupFlagTables` | 224 | `eu/src/overlays/ov091/data/Data_ov091_020c2c88.c` | `eu/src/overlays/ov091/calls/SyncRecordFlags.c` |
| `data_ov091_020c2d68` | `gReportTopCounterProgressFieldOffsets` | 160 | `eu/src/overlays/ov091/data/Data_ov091_020c2d68.c` | `eu/src/overlays/ov091/calls/UpdateReportTopCounterProgress.c` |
| `data_ov091_020c3580` | `gReportTopEntryDefinitionStorage` | 448 | `eu/src/overlays/ov091/data/Data_ov091_020c3500.c` | `eu/src/overlays/ov091/calls/GetPlayerFlagRecord_020c2820.c` |
| `data_ov091_020c3740` | `gReportTopSceneWork` | 4 | `eu/src/overlays/ov091/data/bss/Bss_ov091_020c3740.c` | `eu/src/overlays/ov091/calls/InitRecordMenuScene.c` |
| `data_ov091_020c3744` | `gReportTopLowerPanelLayout` | 24 | `eu/src/overlays/ov091/data/bss/Bss_ov091_020c3740.c` | `eu/src/overlays/ov091/calls/CreateReportTopPanelSlots.c` |
| `data_ov091_020c375c` | `gReportTopPopupWork` | 4 | `eu/src/overlays/ov091/data/bss/Bss_ov091_020c375c.c` | `eu/src/overlays/ov091/calls/ReportTopPopup_InitTaskWork.c` |
| `data_ov093_020c3f94` | `gTrophyRewardThresholdEntries` | 64 | `eu/src/ov093/data/Data_ov093_020c3f94.c` | `eu/src/overlays/ov093/calls/RunEntryUnlockSequence.c` |
| `data_ov093_020c4058` | `gTrophyLeftScrollBarTemplate` | 44 | `eu/src/ov093/data/Data_ov093_020c4058.c` | `eu/src/overlays/ov093/calls/InitEntryGridScene.c` |
| `data_ov093_020c4084` | `gTrophyRightScrollBarTemplate` | 44 | `eu/src/ov093/data/Data_ov093_020c4084.c` | `eu/src/overlays/ov093/calls/InitEntryGridScene.c` |
| `data_ov093_020c4128` | `gTrophyLeftSlotTemplatesHead` | 56 | `eu/src/ov093/data/Data_ov093_020c4128.c` | `eu/src/overlays/ov093/calls/InitEntrySlotSprites.c` |
| `data_ov093_020c4160` | `gTrophyLeftSlotTemplatesTail` | 308 | `eu/src/ov093/data/Data_ov093_020c4128.c` | `eu/src/overlays/ov093/calls/InitEntrySlotSprites.c` |
| `data_ov093_020c4294` | `gTrophyRightSlotTemplates` | 840 | `eu/src/ov093/data/Data_ov093_020c4128.c` | `eu/src/overlays/ov093/calls/InitEntrySlotSprites.c` |
| `data_ov093_020c4d88` | `gTrophyBooleanProgressBlankText` | 4 | `eu/src/ov093/data/Data_ov093_020c4d88.c` | `eu/src/overlays/ov093/calls/RedrawEntryPanelText.c` |
| `data_ov093_020c4d8c` | `gTrophyEntryUnlockLanguage1Format` | 24 | `eu/src/ov093/data/Data_ov093_020c4d88.c` | `eu/src/overlays/ov093/calls/RunEntryUnlockSequence.c` |
| `data_ov093_020c4da4` | `gTrophyEntryUnlockDefaultFormat` | 16 | `eu/src/ov093/data/Data_ov093_020c4da4.c` | `eu/src/overlays/ov093/calls/RunEntryUnlockSequence.c` |
| `data_ov093_020c4db4` | `gTrophyRewardLanguages234Format` | 32 | `eu/src/ov093/data/Data_ov093_020c4da4.c` | `eu/src/overlays/ov093/calls/RunRewardUnlockSequence.c` |
| `data_ov093_020c4dd4` | `gTrophyRewardLanguage1Format` | 32 | `eu/src/ov093/data/Data_ov093_020c4dd4.c` | `eu/src/overlays/ov093/calls/RunRewardUnlockSequence.c` |
| `data_ov093_020c4df4` | `gTrophyRewardLanguage5Format` | 28 | `eu/src/ov093/data/Data_ov093_020c4df4.c` | `eu/src/overlays/ov093/calls/RunRewardUnlockSequence.c` |
| `data_ov093_020c4e10` | `gTrophyRewardDefaultFormat` | 28 | `eu/src/ov093/data/Data_ov093_020c4e10.c` | `eu/src/overlays/ov093/calls/RunRewardUnlockSequence.c` |
| `data_ov093_020c4e2c` | `gTrophyPrizeLanguage3Format` | 28 | `eu/src/ov093/data/Data_ov093_020c4e2c.c` | `eu/src/overlays/ov093/calls/RunPrizeMessageSequence.c` |
| `data_ov093_020c4e48` | `gTrophyPrizeLanguage4Format` | 28 | `eu/src/ov093/data/Data_ov093_020c4e48.c` | `eu/src/overlays/ov093/calls/RunPrizeMessageSequence.c` |
| `data_ov093_020c4e64` | `gTrophyPrizeLanguage1Format` | 28 | `eu/src/ov093/data/Data_ov093_020c4e64.c` | `eu/src/overlays/ov093/calls/RunPrizeMessageSequence.c` |
| `data_ov093_020c4e80` | `gTrophyPrizeDefaultFormat` | 24 | `eu/src/ov093/data/Data_ov093_020c4e80.c` | `eu/src/overlays/ov093/calls/RunPrizeMessageSequence.c` |
| `data_ov093_020c4e98` | `gTrophyEntryDefinitionsHead` | 328 | `eu/src/ov093/data/Data_ov093_020c4e80.c` | `eu/src/overlays/ov093/calls/BuildAchievementList.c` |
| `data_ov093_020c4fe0` | `gTrophyEntryDefinitionsTail` | 248 | `eu/src/ov093/data/Data_ov093_020c4fe0.c` | `eu/src/overlays/ov093/calls/BuildAchievementList.c` |
| `data_ov093_020c50d8` | `gTrophyPopupTaskDescriptorStorage` | 40 | `eu/src/ov093/data/Data_ov093_020c50d8.c` | `eu/src/overlays/ov093/calls/CreatePopupManager.c` |
| `data_ov093_020c5100` | `gTrophySceneWork` | 4 | `eu/src/overlays/ov093/data/bss/Bss_ov093_020c5100.c` | `eu/src/overlays/ov093/calls/InitEntryGridScene.c` |
| `data_ov093_020c5104` | `gTrophyPopupWorkStorage` | 28 | `eu/src/overlays/ov093/data/bss/Bss_ov093_020c5100.c` | `eu/src/overlays/ov093/calls/InitPopupManager.c` |

## Proven operations and boundaries

- `gReportTopEntrySceneIds`: First five signed bytes select the primary subscene for the chosen report-top row. Physical size is 8 B; preserve the remaining three bytes and signed-byte indexing.
- `gReportTopScrollListTemplate`: Eleven words initialize the scroll-list prefix through InitScrollList_020bfc8c. Only the copied 44-byte template prefix is storage here; runtime ScrollList is larger.
- `gReportTopUpperPanelLayouts`: Six 24-byte panel layouts are passed to bank-0 CreateListPanelSlot and used during list refresh. Bank-0 layouts are distinct from the dynamic bank-1 layout.
- `gReportTopSummaryPopupFlagTables`: 224-byte bundle: 12-byte UTF16 summary format, task descriptor at +0x0c, eight source-flag IDs at +0x20, forty record-source flag IDs at +0x40. Legacy messageIds/newline/recordFlagDescriptors byte members split integer flag IDs arbitrarily; they are not proof of message tables or a newline string. Preserve bytes and relocations.
- `gReportTopCounterProgressFieldOffsets`: Forty 17-bit packed field offsets are tested for nonzero to update source and notification flags and compute count*100/40. These are bit offsets, not counter values.
- `gReportTopEntryDefinitionStorage`: GetPlayerFlagRecord returns base+index*12; progress builder reads 36 {id,type,visibility} records. 36*12=432 B are demonstrated; physical extent is 448 B, so preserve the remaining 16 bytes without assigning a role.
- `gReportTopSceneWork`: Four-byte global stores the caller-supplied scene work pointer; flag accessors use its packed flag sets. Borrowed scene view, not independently allocated/freed by this global. Do not extend lifetime beyond its owner.
- `gReportTopLowerPanelLayout`: 24-byte zero-initialized dynamic layout is passed to bank-1 panel creation and read by RefreshScrollList. Preserve all six words and runtime writes; it is not another scene pointer.
- `gReportTopPopupWork`: Four-byte global receives GetRunningTaskWork; its first pointed-to word stores the TaskObject returned by the creator. Task runtime work and TaskObject are different addresses. Integrate consistently with the separately queued popup prototype correction; do not infer fluent returns from residual r0.
- `gTrophyRewardThresholdEntries`: Eight {requiredCount,recordHandle} pairs: confirmed entry count selects reward thresholds, and reward processing uses each handle and its requiredCount in the message. The first field is a threshold in the entry sequence; legacy itemId wording in the reward sequence is not a distinct item ID proof.
- `gTrophyLeftScrollBarTemplate`: 44-byte descriptor is passed directly to SetupScrollBar for id 0. Runtime scroll bar is larger; preserve the descriptor prefix only.
- `gTrophyRightScrollBarTemplate`: 44-byte descriptor for id 1 is copied locally; its rangeEnd word at +8 is replaced by the built row count before SetupScrollBar. Keep local mutation and do not mutate the shared template as part of renaming.
- `gTrophyLeftSlotTemplatesHead`: First 56 bytes of thirteen logical 28-byte left-side slot templates; also supplies layout x/y fields for scroll-bar positioning. Physical head is two records; next physical object contains the remaining eleven.
- `gTrophyLeftSlotTemplatesTail`: Remaining eleven 28-byte records of the left-side slot template table, reached through the preceding base. 308-byte physical tail is not an independent 77-word semantic table. Preserve adjacency.
- `gTrophyRightSlotTemplates`: Thirty 28-byte right-side slot templates create animation slots; refresh reads each template x/y at +8/+0xc. 840-byte exact table; preserve side-specific indexing and existing slot flags.
- `gTrophyBooleanProgressBlankText`: UTF16 space and terminator (two u16 packed in a 4-byte definition) format the type-2 boolean-progress row as blank text. Physical C declaration remains u32[1]; changing text type is outside this symbol-only block.
- `gTrophyEntryUnlockLanguage1Format`: Language selector 1 uses a tagged UTF16 format with three text arguments: label, entry name, and message 1. Preserve embedded control codes and final extra zero; language number is the observed selector, no language-name assumption.
- `gTrophyEntryUnlockDefaultFormat`: Other language selectors use a tagged UTF16 two-text-argument format: entry name then label. Legacy char* externs do not establish narrow text; physical array is u16[8].
- `gTrophyRewardLanguages234Format`: Language selectors 2,3,4 share this tagged UTF16 reward format with five arguments. Preserve all 32 bytes and control codes; do not reorder arguments to normalize localization.
- `gTrophyRewardLanguage1Format`: Language selector 1 uses this tagged UTF16 reward format with the same five argument positions. Preserve all 32 bytes and control codes.
- `gTrophyRewardLanguage5Format`: Language selector 5 uses this tagged UTF16 reward format. Preserve all 28 bytes and control codes.
- `gTrophyRewardDefaultFormat`: Default language branch uses this tagged UTF16 reward format. Preserve all 28 bytes and control codes.
- `gTrophyPrizeLanguage3Format`: Language selector 3 formats prize text using name,prefix,count,suffix. Preserve tagged UTF16 data and 28-byte extent.
- `gTrophyPrizeLanguage4Format`: Language selector 4 formats prize text using name,prefix,count,suffix. Preserve tagged UTF16 data and 28-byte extent.
- `gTrophyPrizeLanguage1Format`: Language selector 1 formats prize text using suffix,name,prefix,count in that order. This argument order differs deliberately from the other prize formats; preserve all 28 bytes.
- `gTrophyPrizeDefaultFormat`: Selectors 0,2,5 and default use name,prefix,count,suffix with this prize format. Preserve tagged UTF16 data and 24-byte extent.
- `gTrophyEntryDefinitionsHead`: Begins thirty-six logical 16-byte {id,type,alwaysVisible,revealFlag} records returned by GetPopupDefinition and consumed by the progress builder. 328-byte head ends after record 20 type; next physical object starts at its alwaysVisible word. PopupDefinition legacy field names are not semantic proof.
- `gTrophyEntryDefinitionsTail`: Remaining 248 bytes of the thirty-six 16-byte entry definitions reached through the preceding base. Keep the cross-object indexing and physical split; this is not a separate table or padding.
- `gTrophyPopupTaskDescriptorStorage`: Creator passes this base to CreateTaskObject; first five words encode task flags/heap, init, shutdown, work size 0x270 and NULL. Physical extent is 40 B; preserve the five additional zero words, without calling them extra task fields or padding.
- `gTrophySceneWork`: Four-byte global stores caller-supplied scene work; smooth-value, grid and flag functions access the same owner. Preserve existing static/local binding and allocation ownership; no complete public SceneWork layout is introduced.
- `gTrophyPopupWorkStorage`: First word stores GetRunningTaskWork pointer for the popup manager; creator writes TaskObject to the first word of the pointed-to task work. Physical BSS allocation is 28 B; only its pointer prefix is established. Preserve six unknown words and static/local binding; coordinate with separately queued popup ABI corrections.

## Shared views and legacy declarations

`gReportTopSummaryPopupFlagTables` is physically one 224-byte object. The first twelve bytes are the UTF16 summary format `%2d%` including terminators. The task descriptor is reached at +`0x0c`; eight flag IDs at +`0x20` feed `UpdateReportTopFlagProgress`; forty flag IDs at +`0x40` feed `SyncRecordFlags`. The source byte fields called `messageIds`, `newline`, `recordFlagDescriptors` and `recordFlagTail` split those 32-bit IDs. Those legacy member labels are not text-role evidence. Preserve the exact format, including its final percent character, and the descriptor relocations.

`gTrophyEntryDefinitionsHead` and `Tail` form 36 logical records of 16 bytes (576 B). The 328-byte head ends after the type word of record 20; the 248-byte tail begins with its always-visible word. `GetPopupDefinition` returns pointers into this table, but `BuildAchievementList` demonstrates `{id,type,alwaysVisible,revealFlag}`. The legacy header names `messageId/category/flags/reserved` are incomplete and should not be copied as a semantic port layout. This data-renaming block does not change that ABI or header.

The left-side slot table is thirteen 28-byte records. Its 56-byte head contains records 0 and 1; its 308-byte tail contains 2..12. The right-side table is thirty complete records (840 B). Creation and scroll refresh use the same 28-byte stride, including x/y at +8/+`0x0c`.

The report-top definition storage has 36 demonstrated 12-byte rows plus sixteen bytes of unknown tail. The trophy popup descriptor storage has a demonstrated five-word task descriptor plus five zero words of unassigned role. The trophy popup BSS has a demonstrated four-byte work-pointer prefix plus twenty-four bytes of unassigned role. Preserve these physical extents.

## Task work, ownership and popup ABI

The popup initializers receive work from `GetRunningTaskWork`. The task creator writes the resulting `TaskObject` pointer into the first word of that work. The global work pointer and the task object are different addresses; destroying the owner does not establish a safe longer lifetime for a saved global view. Scene-work globals store caller-supplied scene pointers. These operations do not justify changing callback returns or treating residual r0 values as logical booleans.

Popup prototype corrections are a separate change. When applying those separately, update their old global spellings consistently with these identities; keep the original evidence and do not mix speculative return-type or allocation changes into a symbol rename. Preserve static/local binding in the overlay-093 BSS source.

## Reproducing the evidence

Read the EU consumers listed in the identity table, applying their macros to included shared bodies. `eu/config/arm9/overlays/ov091/delinks.txt` and `eu/config/arm9/overlays/ov093/delinks.txt` select the active source owners. Existing object symbol sizes match the listed physical extents; initialized symbols reconstructed with their ABS32 relocations match the corresponding native module bytes. BSS symbols are NOBITS and fit the native BSS ranges from `eu/dsd_extract/arm9_overlays/overlays.yaml`; they have no stored ROM bytes to compare.


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
