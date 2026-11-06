# Menu DATA registries, descriptors and state tables

These 23 DATA names identify four registry fragments, seventeen physical descriptor objects and two popup-state tables. Filenames and physical storage boundaries remain unchanged. Names describe the demonstrated owner and layout; they do not introduce new allocation, dispatch or input behavior.

Native sizes below are symbol extents, not complete source-file sizes. In particular, a descriptor inside a mixed source file and the split enemy-viewer descriptor head must not be treated as the entire file.

## Identities and stable source paths

| EU bank/address | Original identifier | Descriptive identifier | Native bytes | Original source path (retained) |
|---|---|---|---:|---|
| ov039:020be8ec | `sOv039_I_020be8ec` | `gSecondaryMenuFirstOverlayId` | 4 | `eu/src/overlays/ov039/data/strings/Strings_ov039_020be8ec.c` |
| ov039:020be8f0 | `data_ov039_020be8f0` | `gSecondaryMenuRegistryTail` | 92 | `eu/src/ov039/data/Data_ov039_020be8f0.c` |
| ov039:020be94c | `sOv039_J_020be94c` | `gPrimaryMenuFirstOverlayId` | 4 | `eu/src/overlays/ov039/data/strings/Strings_ov039_020be94c.c` |
| ov039:020be950 | `data_ov039_020be950` | `gPrimaryMenuRegistryTail` | 148 | `eu/src/ov039/data/Data_ov039_020be950.c` |
| ov073:020c4160 | `data_ov073_020c4160` | `gStatusMenuDescriptor` | 64 | `eu/src/ov073/data/Data_ov073_020c4160.c` |
| ov078:020c4fe0 | `data_ov078_020c4fe0` | `gPageMenuDescriptor` | 68 | `eu/src/ov078/data/Data_ov078_020c4fe0.c` |
| ov080:020c5da0 | `data_ov080_020c5da0` | `gSaveSelectMenuDescriptor` | 68 | `eu/src/ov080/data/Data_ov080_020c5da0.c` |
| ov087:020c7da0 | `data_ov087_020c7da0` | `gSelectionPanelMenuDescriptor` | 68 | `eu/src/ov087/data/Data_ov087_020c7da0.c` |
| ov088:020bee80 | `data_ov088_020bee80` | `gOverlay088CaptionMenuDescriptor` | 64 | `eu/src/ov088/data/Data_ov088_020bee80.c` |
| ov089:020c056c | `data_ov089_020c056c` | `gEntryCarouselMenuDescriptor` | 68 | `eu/src/ov089/data/Data_ov089_020c0560.c` |
| ov091:020c2b18 | `data_ov091_020c2b18` | `gReportTopMenuDescriptor` | 68 | `eu/src/overlays/ov091/data/Data_ov091_020c2ad8.c` |
| ov093:020c4014 | `data_ov093_020c4014` | `gTrophyReportMenuDescriptor` | 68 | `eu/src/ov093/data/Data_ov093_020c3fd4.c` |
| ov099:020c2368 | `data_ov099_020c2368` | `gEnemyViewerMenuDescriptorHead` | 24 | `eu/src/ov099/data/Data_ov099_020c2368.c` |
| ov103:020c05c4 | `data_ov103_020c05c4` | `gTheaterMenuDescriptor` | 68 | `eu/src/ov103/data/Data_ov103_020c05c4.c` |
| ov091:020c2a10 | `data_ov091_020c2a10` | `gReportTopPopupStateHandlers` | 32 | `eu/src/overlays/ov091/data/Rodata_ov091_020c2a10.c` |
| ov093:020c3e74 | `data_ov093_020c3e74` | `gTrophyPopupStateHandlers` | 36 | `eu/src/ov093/data/Rodata_ov093_020c3e74.c` |
| ov090:020beae0 | `data_ov090_020beae0` | `gOv090SecondaryMenuDescriptor` | 64 | `eu/src/ov090/data/Data_ov090_020beae0.c` |
| ov092:020beae0 | `data_ov092_020beae0` | `gOv092SecondaryMenuDescriptor` | 64 | `eu/src/ov092/data/Data_ov092_020beae0.c` |
| ov094:020beae0 | `data_ov094_020beae0` | `gOv094SecondaryMenuDescriptor` | 64 | `eu/src/ov094/data/Data_ov094_020beae0.c` |
| ov096:020beae0 | `data_ov096_020beae0` | `gOv096SecondaryMenuDescriptor` | 64 | `eu/src/ov096/data/Data_ov096_020beae0.c` |
| ov098:020beae0 | `data_ov098_020beae0` | `gOv098SecondaryMenuDescriptor` | 64 | `eu/src/ov098/data/Data_ov098_020beae0.c` |
| ov100:020beae0 | `data_ov100_020beae0` | `gOv100SecondaryMenuDescriptor` | 64 | `eu/src/ov100/data/Data_ov100_020beae0.c` |
| ov102:020beae0 | `data_ov102_020beae0` | `gOv102SecondaryMenuDescriptor` | 64 | `eu/src/ov102/data/Data_ov102_020beae0.c` |

## Overlay registries

The primary registry starts at ov039:020be94c and contains 19 records; the secondary registry starts at ov039:020be8ec and contains 12. Each logical record is eight bytes: a 32-bit overlay ID followed by the descriptor address in that overlay bank. LoadPrimarySubOverlay and LoadSecondarySubOverlay read the ID with an eight-byte stride. The callback/work-size/input dispatchers read the descriptor from the parallel base+4 view.

The first overlay ID is a separate four-byte C object, historically stored as a short char array in a strings source file. Its bytes encode ID 74 (primary) or ID 73 (secondary). The following 148-byte/92-byte RegistryTail begins with that first descriptor pointer and then alternates later IDs/pointers. The new names preserve this split. They do not make either tail or the four-byte head a complete typed registry.

| Registry | Logical extent | Physical objects |
|---|---|---|
| Primary | [020be94c,020be9e4), 19 x 8 bytes | gPrimaryMenuFirstOverlayId (4) + gPrimaryMenuRegistryTail (148) |
| Secondary | [020be8ec,020be94c), 12 x 8 bytes | gSecondaryMenuFirstOverlayId (4) + gSecondaryMenuRegistryTail (92) |

Overlay ID establishes the descriptor owner. A stale C relocation symbol can mention a different bank at the same RAM address. For example, a legacy symbol from ov034 at 020beae0 can occur in a registry record whose overlay ID selects ov090,092,094,096,098,100 or 102. Those are separate descriptors and work allocations. Their equal byte patterns or addresses do not merge their ownership.

The registry loaders are the evidence for these relationships:

- `eu/src/overlays/ov039/calls/LoadPrimarySubOverlay.c` includes `src/ov039/overlay_handling/LoadPrimarySubOverlay_020bce34.c` with EU aliases.
- `eu/src/overlays/ov039/calls/LoadSecondarySubOverlay.c` includes `src/ov039/overlay_handling/LoadSecondarySubOverlay_020bcf50.c`.
- `eu/src/overlays/ov039/calls/UpdateSubOverlayHandlers.c` loads the selected overlay, obtains its work size, allocates/clears its work and calls init until ready, then update.

## Descriptor layouts and consumers

Primary and secondary descriptors have different headers. The registered pointer identifies a descriptor, not the allocated work buffer. The common update owner stores distinct primaryWork and secondaryWork pointers and separately tracks readiness.

| Offset | Primary descriptor (68 bytes) | Secondary descriptor (64 bytes) |
|---|---|---|
| +0x00 | init(work), readiness result | init(work), readiness result |
| +0x04 | destroy(work) | destroy(work) |
| +0x08 | update(work) | update(work) |
| +0x0c | secondary overlay index | work size |
| +0x10 | work size | first input slot |
| +0x14..+0x40 | twelve input slots | remaining input slots end at +0x3c |

The accessor evidence is `GetPrimaryMenuSubOverlayWorkSize`, `GetSecondaryMenuSubOverlayWorkSize` and `GetPrimaryMenuSecondaryOverlayIndex` in `eu/src/overlays/ov039/calls/`. The former reads primary+0x10; secondary size is +0x0c. UpdateSubOverlayHandlers consumes those sizes. ShutdownHandlersAndExit and CloseSecondarySubOverlay use destroy+4 before releasing their owner. Input dispatchers retain their exact slot offsets, NULL checks and caller-specific return behavior.

| Descriptor | Role | Secondary index | Allocated work bytes | Registered init / destroy / update |
|---|---|---:|---:|---|
| `gStatusMenuDescriptor` | secondary | - | 4656 | `InitStatusMenu` / `DestroyStatusMenu` / `UpdateStatusMenu` |
| `gPageMenuDescriptor` | primary | 0 | 1496 | `InitPageMenu` / `ShutdownPageMenu` / `UpdatePageMenuNoop` |
| `gSaveSelectMenuDescriptor` | primary | 0 | 43304 | `InitSaveSelectScreen` / `DestroySaveSelectScreen` / `UpdateSaveSelectScreen` |
| `gSelectionPanelMenuDescriptor` | primary | 2 | 3040 | `InitPanelScene_020c713c` / `DestroyPanelScene` / `UpdateEntryScroll` |
| `gOverlay088CaptionMenuDescriptor` | secondary | - | 64 | `InitializeOverlay088` / `ShutdownOverlay088` / `UpdateOverlay088CaptionLayerNoop` |
| `gEntryCarouselMenuDescriptor` | primary | 3 | 2316 | `InitEntryMenu` / `ShutdownOverlay089` / `UpdateEntryCarousel` |
| `gReportTopMenuDescriptor` | primary | 4 | 52352 | `InitRecordMenuScene` / `DestroyMenuScene` / `UpdateRecordMenuScene` |
| `gTrophyReportMenuDescriptor` | primary | 5 | 53796 | `InitEntryGridScene` / `ShutdownTrophyReport` / `UpdateSceneFrame` |
| `gEnemyViewerMenuDescriptorHead` | primary head fragment | 8 | 55032 | `InitEnemyViewerScreen` / `DestroyEnemyViewerScreen` / `UpdateModelViewerScreen` |
| `gTheaterMenuDescriptor` | primary | 10 | 52164 | `InitMenuScene_020beb40` / `DestroyMenuScene_020beb84` / `RunSceneStateHandler` |
| `gOv090SecondaryMenuDescriptor` | secondary | - | 4 | `InitOv090SecondaryMenu` / `DestroyOv090SecondaryMenu` / `UpdateOv090SecondaryMenu` |
| `gOv092SecondaryMenuDescriptor` | secondary | - | 4 | `InitOv092SecondaryMenu` / `DestroyOv092SecondaryMenu` / `UpdateOv092SecondaryMenu` |
| `gOv094SecondaryMenuDescriptor` | secondary | - | 4 | `InitOv094SecondaryMenu` / `DestroyOv094SecondaryMenu` / `UpdateOv094SecondaryMenu` |
| `gOv096SecondaryMenuDescriptor` | secondary | - | 4 | `InitOv096SecondaryMenu` / `DestroyOv096SecondaryMenu` / `UpdateOv096SecondaryMenu` |
| `gOv098SecondaryMenuDescriptor` | secondary | - | 4 | `InitOv098SecondaryMenu` / `DestroyOv098SecondaryMenu` / `UpdateOv098SecondaryMenu` |
| `gOv100SecondaryMenuDescriptor` | secondary | - | 4 | `InitOv100SecondaryMenu` / `DestroyOv100SecondaryMenu` / `UpdateOv100SecondaryMenu` |
| `gOv102SecondaryMenuDescriptor` | secondary | - | 4 | `InitOv102SecondaryMenu` / `DestroyOv102SecondaryMenu` / `UpdateOv102SecondaryMenu` |

These callback identities come from the retained source objects and their relocations. The original source paths in the identity table are the direct evidence for each descriptor. The registry and ov039 consumers above establish the role of the words. A legacy zero-argument/void declaration in a pointer table is not a complete host interface contract; retain the real work argument and each actual callback behavior when constructing a port.

The seven four-byte-work secondary owners (ov090,092,094,096,098,100,102) have separate descriptors despite equal layouts. The bank-specific names deliberately avoid attributing a report/menu purpose unsupported by their own bodies. The ov088 caption-layer role is supported by its resource/renderer callbacks; its descriptor remains distinct from those placeholders.

The ov099 object is only the first 24 bytes of its primary descriptor, through the first input slot at +0x14. The adjacent 44-byte existing symbol gEnemyReportListHandlers supplies the remaining input words, yielding the same 68-byte logical descriptor. The Head suffix is intentional; no merge, reslice or duplicate allocation is implied.

## Popup-state DATA tables

gReportTopPopupStateHandlers has eight handler words (32 bytes). gTrophyPopupStateHandlers has eight nonnull handlers followed by one stored NULL word (36 bytes). They belong to popup windows embedded at manager work+0x2c, not to the outer report-state tables.

The evidence is `eu/src/overlays/ov091/calls/UpdatePopupManager.c` and `eu/src/overlays/ov093/calls/UpdatePopupManager_020c2da0.c`, through their shared includes. Each reads the signed popup state and indexes the corresponding table, passing the embedded window pointer. The trailing Trophy NULL is storage, not a ninth named state.

| State index | Report-top table | Trophy table |
|---:|---|---|
| 0 | `ReportTopPopup_HandleState0Noop` | `TrophyPopup_HandleState0Noop` |
| 1 | `ShowNextQueuedPopup` | `StartNextPopup` |
| 2 | `OpenPopupWindow_020c1e38` | `OpenPopupMessage` |
| 3 | `GrowPopupWindow` | `FadeInPopup` |
| 4 | `ShowPopupFrame` | `OpenPopupWindow_020c3438` |
| 5 | `HandleEntryConfirmInput` | `WaitForPopupDismiss` |
| 6 | `ShrinkPopupWindow` | `FadeOutPopup` |
| 7 | `HidePopupWindow` | `ClosePopupPanel` |
| Stored word 8 | outside the 32-byte object | NULL |

## Storage and relocation limits

Every existing word, explicit NULL, ARM/Thumb pointer tag and relocation target/addend remains part of the native layout. Registry words can interleave integer IDs and descriptor pointers even where the legacy C uses a pointer array. A symbol rename does not rebind a cross-bank relocation or change that representation.

The larger mixed ov091 object at 020c2c88 is outside these 23 names. A separate task descriptor starts inside it at +0x0c; naming the whole 224-byte aggregate as that 20-byte descriptor would be false. Existing descriptive descriptor symbols outside the table above are retained.

For reproducible inspection, read the original DATA source path beside the named ov039 loader/accessor/dispatch source. Native address and symbol size fix which object is being described; file-level declarations, neighboring symbols and shared RAM values alone do not establish a larger layout or owner.


## Byte-exact validation

64 DATA identities retain their source paths, native sizes and storage.
440/443 affected official function checks pass; the remaining
3 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 498 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
