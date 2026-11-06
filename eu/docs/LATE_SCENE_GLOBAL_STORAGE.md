# Menu, actor and camera global storage

These 20 BSS names identify the storage used by concrete initializers and consumers. They preserve the original physical objects, filenames, zero initialization, alignment and binding. The names distinguish global pointer prefixes from text scratch buffers; they do not supply a complete layout or change ownership.

## Identity and stable sources

| EU identity | Original identifier | Descriptive identifier | BSS bytes | Stable source | Initializer or direct consumer |
|---|---|---|---:|---|---|
| ov042:020be5e0 | `data_ov042_020be5e0` | `gCameraSceneGlobalStorage` | 32 | `eu/src/overlays/ov042/data/bss/Bss_ov042_020be5e0.c` | `eu/src/overlays/ov042/calls/InitCameraScene.c` |
| ov044:020d0ec0 | `data_ov044_020d0ec0` | `gPanelCameraGlobalStorage` | 32 | `eu/src/overlays/ov044/data/bss/Bss_ov044_020d0ec0.c` | `eu/src/overlays/ov044/calls/InitPanel.c` |
| ov045:020c08a0 | `data_ov045_020c08a0` | `gBattleGaugeGlobalStorage` | 32 | `eu/src/overlays/ov045/data/bss/Bss_ov045_020c08a0.c` | `eu/src/overlays/ov045/calls/InitBattleGaugeContext.c` |
| ov052:020d21e0 | `data_ov052_020d21e0` | `gPlayerActorJointNameScratch` | 32 | `eu/src/overlays/ov052/data/bss/Bss_ov052_020d21e0.c` | `eu/src/overlays/ov052/calls/InitPlayerActorModel_020c7460.c` |
| ov055:020d3f20 | `data_ov055_020d3f20` | `gOverlay055EntityGlobalStorage` | 29 | `eu/src/overlays/ov055/data/bss/Bss_ov055_020d3f20.c` | `eu/src/overlays/ov055/calls/CreateOverlay055Entity.c` |
| ov057:020d4500 | `data_ov057_020d4500` | `gOverlay057EntityGlobalStorage` | 32 | `eu/src/overlays/ov057/data/bss/Bss_ov057_020d4500.c` | `eu/src/overlays/ov057/calls/CreateOverlay057Entity.c` |
| ov059:020cffc4 | `data_ov059_020cffc4` | `gOverlay059ActorGlobalStorage` | 28 | `eu/src/overlays/ov059/data/bss/Bss_ov059_020cffc0.c` | `eu/src/overlays/ov059/calls/Actor_Init.c` |
| ov073:020c4260 | `data_ov073_020c4260` | `gStatusPanelGlobalStorage` | 32 | `eu/src/overlays/ov073/data/bss/Bss_ov073_020c4260.c` | `eu/src/overlays/ov073/calls/InitStatusPanel.c` |
| ov075:020d1900 | `data_ov075_020d1900` | `gMatrixMenuWork` | 4 | `eu/src/overlays/ov075/data/bss/Bss_ov075_020d1900.c` | `eu/src/overlays/ov075/calls/InitMatrixMenu.c` |
| ov075:020d1904 | `data_ov075_020d1904` | `gMatrixDialogTextBuffer` | 512 | `eu/src/overlays/ov075/data/bss/Bss_ov075_020d1900.c` | `eu/src/overlays/ov075/calls/OpenMessageDialog.c` |
| ov078:020c51e0 | `data_ov078_020c51e0` | `gPageMenuGlobalStorage` | 32 | `eu/src/overlays/ov078/data/bss/Bss_ov078_020c51e0.c` | `eu/src/overlays/ov078/calls/InitPageMenu.c` |
| ov080:020c5e20 | `data_ov080_020c5e20` | `gSaveSelectGlobalStorage` | 32 | `eu/src/overlays/ov080/data/bss/Bss_ov080_020c5e20.c` | `eu/src/overlays/ov080/calls/InitSaveSelectScreen.c` |
| ov081:020c5da0 | `data_ov081_020c5da0` | `gTutorialMenuGlobalStorage` | 32 | `eu/src/overlays/ov081/data/bss/Bss_ov081_020c5da0.c` | `eu/src/overlays/ov081/calls/InitOv081Screen.c` |
| ov086:020c3020 | `data_ov086_020c3020` | `gRecordMenuGlobalStorage` | 32 | `eu/src/overlays/ov086/data/bss/Bss_ov086_020c3020.c` | `eu/src/overlays/ov086/calls/InitRecordMenu.c` |
| ov095:020c28e0 | `data_ov095_020c28e0` | `gItemReportGlobalStorage` | 32 | `eu/src/overlays/ov095/data/bss/Bss_ov095_020c28e0.c` | `eu/src/overlays/ov095/calls/InitGridMenu.c` |
| ov097:020c2540 | `data_ov097_020c2540` | `gStoryReportGlobalStorage` | 32 | `eu/src/overlays/ov097/data/bss/Bss_ov097_020c2540.c` | `eu/src/overlays/ov097/calls/InitMenuScene_020beb20.c` |
| ov099:020c2900 | `data_ov099_020c2900` | `gEnemyViewerWork` | 4 | `eu/src/overlays/ov099/data/bss/Bss_ov099_020c2900.c` | `eu/src/overlays/ov099/calls/InitEnemyViewerScreen.c` |
| ov099:020c2904 | `data_ov099_020c2904` | `gEnemyViewerDrawNodeStorage` | 28 | `eu/src/overlays/ov099/data/bss/Bss_ov099_020c2900.c` | `eu/src/overlays/ov099/calls/DrawViewerSceneNode.c` |
| ov101:020c5920 | `data_ov101_020c5920` | `gListMenuGlobalStorage` | 32 | `eu/src/overlays/ov101/data/bss/Bss_ov101_020c5920.c` | `eu/src/overlays/ov101/calls/InitializeListScene.c` |
| ov103:020c0720 | `data_ov103_020c0720` | `gTheaterMenuGlobalStorage` | 32 | `eu/src/overlays/ov103/data/bss/Bss_ov103_020c0720.c` | `eu/src/overlays/ov103/calls/InitMenuScene_020beb40.c` |

## Physical storage and partial views

The identity table gives the exact physical extent of each object. Most global-storage objects are 32 bytes while only the first four-byte NDS pointer word has a demonstrated role. The ov055 entity object is 29 bytes, the ov059 actor and ov099 draw-node objects are 28 bytes, and the ov075/ov099 work-pointer words are exactly four bytes. The scratch buffers are 32 and 512 bytes. No block is shortened to match a consumer declaration.

Existing sources sometimes declare the same first word as a pointer or integer in consumers while its physical definition is a scalar array. This rename block preserves that legacy representation. A port should introduce a consistent typed view only after its own layout and ABI validation. Unreferenced tail bytes have an unknown contract: they are not proved padding, additional pointers or part of the pointed-to work allocation.

An initializer storing a supplied pointer establishes a reference, not an ownership transfer, unique live instance or lifetime beyond the source contract. A factory storing its newly allocated result similarly does not prove this global is the only reference. Null-after-destroy is asserted only for the specific implementations cited below.

## Per-object evidence and limits

### `gCameraSceneGlobalStorage`

Stores the camera state supplied to InitCameraScene in its first pointer word; camera update/goal/collider helpers read that same state.

The EU identity is ov042:020be5e0; its physical definition is `eu/src/overlays/ov042/data/bss/Bss_ov042_020be5e0.c` (32 bytes). The direct evidence starts at `eu/src/overlays/ov042/calls/InitCameraScene.c`.

The wrapper selects the actual shared body: `src/ov042/camera/InitCameraScene_020bdb4c.c`.

Only the first word has this demonstrated pointer role. The remaining 28 bytes stay unspecified and retain their existing extent.

### `gPanelCameraGlobalStorage`

InitPanel stores its supplied Panel pointer; the same owner contains projection, target/origin and camera-update state.

The EU identity is ov044:020d0ec0; its physical definition is `eu/src/overlays/ov044/data/bss/Bss_ov044_020d0ec0.c` (32 bytes). The direct evidence starts at `eu/src/overlays/ov044/calls/InitPanel.c`.

The wrapper selects the actual shared body: `src/ov044/panel_state/InitPanel_020d05e8.c`.

Only the first word has this demonstrated pointer role. The remaining 28 bytes stay unspecified and retain their existing extent.

### `gBattleGaugeGlobalStorage`

InitBattleGaugeContext stores GetRunningTaskWork after initializing the 0x1a4c-byte task work and copying the 16-byte input prefix.

The EU identity is ov045:020c08a0; its physical definition is `eu/src/overlays/ov045/data/bss/Bss_ov045_020c08a0.c` (32 bytes). The direct evidence starts at `eu/src/overlays/ov045/calls/InitBattleGaugeContext.c`.

Only the first word has this demonstrated pointer role. The remaining 28 bytes stay unspecified and retain their existing extent.

### `gPlayerActorJointNameScratch`

A character buffer, not an actor pointer: initializer clears the first 16 bytes, formats each joint name into it and passes it to the model dictionary lookup. Native object extent is 32 bytes.

The EU identity is ov052:020d21e0; its physical definition is `eu/src/overlays/ov052/data/bss/Bss_ov052_020d21e0.c` (32 bytes). The direct evidence starts at `eu/src/overlays/ov052/calls/InitPlayerActorModel_020c7460.c`.

The wrapper selects the actual shared body: `src/ov052/model_display/InitPlayerActorModel_020c7460.c`.

This object is scratch storage rather than a global work pointer. Keep its complete physical capacity and the actual formatter/clear arguments.

### `gOverlay055EntityGlobalStorage`

Factory stores the newly allocated 0x1294-byte Entity pointer in the first word before initializing it and resetting combat state.

The EU identity is ov055:020d3f20; its physical definition is `eu/src/overlays/ov055/data/bss/Bss_ov055_020d3f20.c` (29 bytes). The direct evidence starts at `eu/src/overlays/ov055/calls/CreateOverlay055Entity.c`.

Only the first word has this demonstrated pointer role. The remaining 25 bytes stay unspecified and retain their existing extent.

### `gOverlay057EntityGlobalStorage`

Parallel distinct factory stores its newly allocated 0x1294-byte Entity pointer in the first word. Bank-specific owner and globals remain separate.

The EU identity is ov057:020d4500; its physical definition is `eu/src/overlays/ov057/data/bss/Bss_ov057_020d4500.c` (32 bytes). The direct evidence starts at `eu/src/overlays/ov057/calls/CreateOverlay057Entity.c`.

Only the first word has this demonstrated pointer role. The remaining 28 bytes stay unspecified and retain their existing extent.

### `gOverlay059ActorGlobalStorage`

Actor_Init stores the supplied actor pointer; command-type and global gauge-panel callbacks subsequently use the same actor.

The EU identity is ov059:020cffc4; its physical definition is `eu/src/overlays/ov059/data/bss/Bss_ov059_020cffc0.c` (28 bytes). The direct evidence starts at `eu/src/overlays/ov059/calls/Actor_Init.c`.

The wrapper selects the actual shared body: `src/ov059/unclassified_helpers/Actor_Init_020cba3c.c`.

Only the first word has this demonstrated pointer role. The remaining 24 bytes stay unspecified and retain their existing extent.

### `gStatusPanelGlobalStorage`

Stores InitStatusPanel second argument, the StatusPanel pointer, not its separate StatusMenu first argument. RestoreStatusSubScreen reads upload/layer flags through that pointer.

The EU identity is ov073:020c4260; its physical definition is `eu/src/overlays/ov073/data/bss/Bss_ov073_020c4260.c` (32 bytes). The direct evidence starts at `eu/src/overlays/ov073/calls/InitStatusPanel.c`.

Only the first word has this demonstrated pointer role. The remaining 28 bytes stay unspecified and retain their existing extent.

### `gMatrixMenuWork`

Four-byte global word stores the supplied MatrixMenu work pointer after its initialization; separate from the following dialog-text buffer.

The EU identity is ov075:020d1900; its physical definition is `eu/src/overlays/ov075/data/bss/Bss_ov075_020d1900.c` (4 bytes). The direct evidence starts at `eu/src/overlays/ov075/calls/InitMatrixMenu.c`.

The wrapper selects the actual shared body: `src/ov075/matrix_menu/InitMatrixMenu_020c49cc.c`.

This is a four-byte reference word on NDS; the pointed-to work is a separate object. No host pointer-width or prototype change is included.

### `gMatrixDialogTextBuffer`

512-byte dialog text buffer passed as destination to VFormatPackedWideText with limit argument 0x100, then to tile measurement and dialog drawing.

The EU identity is ov075:020d1904; its physical definition is `eu/src/overlays/ov075/data/bss/Bss_ov075_020d1900.c` (512 bytes). The direct evidence starts at `eu/src/overlays/ov075/calls/OpenMessageDialog.c`.

The wrapper selects the actual shared body: `src/ov075/unclassified_helpers/OpenMessageDialog_020c8ba0.c`.

This object is scratch storage rather than a global work pointer. Keep its complete physical capacity and the actual formatter/clear arguments.

### `gPageMenuGlobalStorage`

Stores the PageMenu work supplied to its initializer; page selection, cursor and close helpers use this same current owner.

The EU identity is ov078:020c51e0; its physical definition is `eu/src/overlays/ov078/data/bss/Bss_ov078_020c51e0.c` (32 bytes). The direct evidence starts at `eu/src/overlays/ov078/calls/InitPageMenu.c`.

The wrapper selects the actual shared body: `src/ov078/unclassified_helpers/InitPageMenu_020c4260.c`.

Only the first word has this demonstrated pointer role. The remaining 28 bytes stay unspecified and retain their existing extent.

### `gSaveSelectGlobalStorage`

Stores the supplied save-select screen pointer; DestroySaveSelectScreen clears the first pointer word.

The EU identity is ov080:020c5e20; its physical definition is `eu/src/overlays/ov080/data/bss/Bss_ov080_020c5e20.c` (32 bytes). The direct evidence starts at `eu/src/overlays/ov080/calls/InitSaveSelectScreen.c`.

The wrapper selects the actual shared body: `src/ov080/unclassified_helpers/InitSaveSelectScreen_020c42b0.c`.

Only the first word has this demonstrated pointer role. The remaining 28 bytes stay unspecified and retain their existing extent.

### `gTutorialMenuGlobalStorage`

Stores the tutorial screen state supplied to initialization; tutorial state/text getters use it and DestroyOv081Screen clears the pointer word.

The EU identity is ov081:020c5da0; its physical definition is `eu/src/overlays/ov081/data/bss/Bss_ov081_020c5da0.c` (32 bytes). The direct evidence starts at `eu/src/overlays/ov081/calls/InitOv081Screen.c`.

The wrapper selects the actual shared body: `src/ov081/unclassified_helpers/InitOv081Screen_020c4c30.c`.

Only the first word has this demonstrated pointer role. The remaining 28 bytes stay unspecified and retain their existing extent.

### `gRecordMenuGlobalStorage`

Stores current RecordMenu work; DestroyRecordMenu reads the same owner for resource teardown.

The EU identity is ov086:020c3020; its physical definition is `eu/src/overlays/ov086/data/bss/Bss_ov086_020c3020.c` (32 bytes). The direct evidence starts at `eu/src/overlays/ov086/calls/InitRecordMenu.c`.

The wrapper selects the actual shared body: `src/ov086/panel_state/InitRecordMenu_020c1da8.c`.

Only the first word has this demonstrated pointer role. The remaining 28 bytes stay unspecified and retain their existing extent.

### `gItemReportGlobalStorage`

Stores current item-report/grid-menu work supplied to its initializer, consumed by its state and navigation helpers.

The EU identity is ov095:020c28e0; its physical definition is `eu/src/overlays/ov095/data/bss/Bss_ov095_020c28e0.c` (32 bytes). The direct evidence starts at `eu/src/overlays/ov095/calls/InitGridMenu.c`.

The wrapper selects the actual shared body: `src/ov095/panel_state/InitGridMenu_020beb00.c`.

Only the first word has this demonstrated pointer role. The remaining 28 bytes stay unspecified and retain their existing extent.

### `gStoryReportGlobalStorage`

Stores supplied story-report work before initialization; DestroyMenuScene clears the pointer word after teardown.

The EU identity is ov097:020c2540; its physical definition is `eu/src/overlays/ov097/data/bss/Bss_ov097_020c2540.c` (32 bytes). The direct evidence starts at `eu/src/overlays/ov097/calls/InitMenuScene_020beb20.c`.

The wrapper selects the actual shared body: `src/ov097/panel_state/InitMenuScene_020beb00.c`.

Only the first word has this demonstrated pointer role. The remaining 28 bytes stay unspecified and retain their existing extent.

### `gEnemyViewerWork`

Four-byte work-pointer word set by InitEnemyViewerScreen, used by flag helpers and cleared by DestroyEnemyViewerScreen.

The EU identity is ov099:020c2900; its physical definition is `eu/src/overlays/ov099/data/bss/Bss_ov099_020c2900.c` (4 bytes). The direct evidence starts at `eu/src/overlays/ov099/calls/InitEnemyViewerScreen.c`.

This is a four-byte reference word on NDS; the pointed-to work is a separate object. No host pointer-width or prototype change is included.

### `gEnemyViewerDrawNodeStorage`

First word stores the current draw node when it has a child; native NNS model draw and child joint-matrix updates follow. This is separate from EnemyViewerWork.

The EU identity is ov099:020c2904; its physical definition is `eu/src/overlays/ov099/data/bss/Bss_ov099_020c2900.c` (28 bytes). The direct evidence starts at `eu/src/overlays/ov099/calls/DrawViewerSceneNode.c`.

Only the first word has this demonstrated pointer role. The remaining 24 bytes stay unspecified and retain their existing extent.

### `gListMenuGlobalStorage`

Stores the supplied list-scene state before clearing and initializing it; typed state/page-scroll getters use this owner.

The EU identity is ov101:020c5920; its physical definition is `eu/src/overlays/ov101/data/bss/Bss_ov101_020c5920.c` (32 bytes). The direct evidence starts at `eu/src/overlays/ov101/calls/InitializeListScene.c`.

Only the first word has this demonstrated pointer role. The remaining 28 bytes stay unspecified and retain their existing extent.

### `gTheaterMenuGlobalStorage`

Stores current theater-menu scene work supplied to initialization and read by its selection/phase logic.

The EU identity is ov103:020c0720; its physical definition is `eu/src/overlays/ov103/data/bss/Bss_ov103_020c0720.c` (32 bytes). The direct evidence starts at `eu/src/overlays/ov103/calls/InitMenuScene_020beb40.c`.

The wrapper selects the actual shared body: `src/ov103/panel_state/InitMenuScene_020beb20.c`.

Only the first word has this demonstrated pointer role. The remaining 28 bytes stay unspecified and retain their existing extent.

## Particular boundaries

InitStatusPanel stores its second argument, the StatusPanel pointer. Its separate StatusMenu first argument must not be substituted. Actor globals in overlays055,057 and059 are distinct bank-qualified owners; the ActorManager embedded ScriptVm layout does not apply to them.

InitPlayerActorModel clears the first 0x10 bytes of gPlayerActorJointNameScratch, formats each joint name and passes the buffer to dictionary lookup. Its physical BSS symbol remains 32 bytes. This does not prove bounded sprintf behavior or justify reducing its capacity.

OpenMessageDialog passes gMatrixDialogTextBuffer to VFormatPackedWideText with limit argument 0x100, then measures and draws the resulting text. The physical buffer is 512 bytes. The legacy character declaration alone does not establish the formatter limit unit; preserve both the native capacity and argument.

gEnemyViewerDrawNodeStorage is separate from gEnemyViewerWork. DrawViewerSceneNode writes its first word only when the node has a child, then performs model drawing and child joint-matrix updates. No unconditional update, ownership or clearing behavior is inferred for that reference.

The cited save-select, tutorial, story-report and enemy-viewer teardown implementations clear their pointer word. InitializeListScene stores its supplied ListSceneState; ShutdownListScene also clears the same first word. Other objects do not inherit those teardown properties.

## Reproducible review and validation boundary

Inspect the stable physical source in the identity table, then its EU initializer and the included shared body selected by that wrapper. The relevant metadata is `eu/config/arm9/overlays/ovNNN/symbols.txt`; native BSS placement comes from `eu/dsd_extract/arm9_overlays/overlays.yaml`.

Existing ELF symbols were checked for SHT_NOBITS section type, physical extent and containment in their native overlay BSS interval. BSS has no stored bytes in the extracted overlay, so this check is not a ROM-byte comparison. This review does not claim a new compilation or an official gate result. Integration must preserve the official module matches and the full physical BSS layout.


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
