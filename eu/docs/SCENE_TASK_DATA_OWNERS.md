# Scene task descriptors, handles and work globals (EU)

These 41 DATA names identify checked native owners without changing storage,
ABI or source placement. Constructors, expanded EU shared-source aliases,
consumers and existing ELF extents establish the contracts below. Source
paths are retained, including aggregate files with several objects.

## Task descriptor and lifetime contract

The native 20-byte class descriptor starts with two u16 class/subclass IDs, a constructor at +4, a destructor at +8, the work size at +0xc, and an optional heap reference at +0x10. `Obj_Construct` allocates and clears work, temporarily makes the new task current, calls the constructor with its caller argument, and stores the returned function as the task update callback. The descriptor destructor is a different slot. Global task handles and global work pointers refer to different objects.

The names ending in `Storage` retain larger native symbols whose full semantics are not known. A four-byte pointer view does not justify shrinking a 24-, 28- or 32-byte allocation. Raw u32/integer pointer declarations and inherited callback prototypes remain native ABI work; this proposal does not turn them into portable headers. Overlay bank plus address establishes identity. Same-address labels in another overlay are not evidence of the same owner.

## Inventory and source evidence

### `ov023:020b6ee0` → `gMenuResourceCacheTaskClass`

Previous label: `data_ov023_020b6ee0`. Existing ELF symbol size: **20 bytes**. Source: `eu/src/ov023/data/Data_ov023_020b6ee0.c`.

Native ClassDescriptor prefix: classId/subId packed word 0x000e0018; constructor at +4 (InitMenuResourceCache); destructor at +8 (DestroyResourceCache); workSize +0xc = 0x40; heapRef +0x10 = NULL.

The initializer supplies this five-word prefix to CreateTaskObject; Obj_Construct copies classId/subId/workSize, allocates and clears task work, invokes the constructor with the task as current, and stores its returned update callback. The descriptor +8 callback is used during destruction.

Limits: TaskObject class IDs are not priorities or flags. Constructor return is the update callback; +8 is not the update callback. Preserve raw declarations and relocation targets. The existing symbol is exactly the 20-byte descriptor.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov023/data/Data_ov023_020b6ee0.c`, symbol reference line(s) 8.
- `eu/src/overlays/ov001/data/tables/gPanelModeDataPointers.c`, symbol reference line(s) 3, 9, 12.

Relocations inside this symbol: 2. Native target expressions and addends are retained.

### `ov023:020b6f2c` → `gMapMenuTaskClass`

Previous label: `data_ov023_020b6f2c`. Existing ELF symbol size: **20 bytes**. Source: `eu/src/ov023/data/Data_ov023_020b6f2c.c`.

Native ClassDescriptor prefix: classId/subId packed word 0x000e0019; constructor at +4 (InitMapMenuState); destructor at +8 (DestroyScreenState); workSize +0xc = 0x7fc4; heapRef +0x10 = NULL.

The initializer supplies this five-word prefix to CreateTaskObject; Obj_Construct copies classId/subId/workSize, allocates and clears task work, invokes the constructor with the task as current, and stores its returned update callback. The descriptor +8 callback is used during destruction.

Limits: TaskObject class IDs are not priorities or flags. Constructor return is the update callback; +8 is not the update callback. Preserve raw declarations and relocation targets. The existing symbol is exactly the 20-byte descriptor.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov023/data/Data_ov023_020b6f2c.c`, symbol reference line(s) 8.
- `eu/src/overlays/ov023/calls/InitMenuResourceCache.c`, symbol reference line(s) 10, 31.

Relocations inside this symbol: 2. Native target expressions and addends are retained.

### `ov023:020b6f80` → `gMenuResourceCacheWork`

Previous label: `data_ov023_020b6f80`. Existing ELF symbol size: **4 bytes**. Source: `eu/src/overlays/ov023/data/bss/Bss_ov023_020b6f80.c`.

4-byte pointer to the resource-cache task work.

InitMenuResourceCache stores GetRunningTaskWork; DestroyResourceCache releases child resources and clears the pointer. DrawCacheHeaderText and menu entry/resource loaders borrow it.

Limits: Opaque bytes retain their original representation and size; this is a symbol rename only.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov023/calls/DestroyResourceCache.c` → `src/ov023/shared_engine/DestroyResourceCache_020b5a08.c`, symbol reference line(s) 9, 18, 22.
- `eu/src/overlays/ov023/calls/DrawCacheHeaderText.c` → `src/ov023/shared_engine/DrawCacheHeaderText_020b5a30.c`, symbol reference line(s) 10, 19.
- `eu/src/overlays/ov023/calls/EnterMenuScreenState.c` → `src/ov023/menu_graphics/EnterMenuScreenState_020b59e0.c`, symbol reference line(s) 1, 13, 15.
- `eu/src/overlays/ov023/calls/InitMenuResourceCache.c`, symbol reference line(s) 9, 28.
- `eu/src/overlays/ov023/calls/LoadMenuBackground.c` → `src/ov023/menu_graphics/LoadMenuBackground_020b5800.c`, symbol reference line(s) 26, 63.
- `eu/src/overlays/ov023/data/bss/Bss_ov023_020b6f80.c`, symbol reference line(s) 3.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov023:020b6f84` → `gMapMenuWork`

Previous label: `data_ov023_020b6f84`. Existing ELF symbol size: **4 bytes**. Source: `eu/src/overlays/ov023/data/bss/Bss_ov023_020b6f84.c`.

4-byte pointer to map-menu task work.

InitMapMenuState stores the current task work; DestroyScreenState clears the pointer. Map-menu entry/resource/position/alpha operations consume it.

Limits: The same source also owns already-named palette work; do not rename or resize that neighbor.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov023/calls/ApplyFormationSlots.c` → `src/ov023/shared_engine/ApplyFormationSlots_020b6d90.c`, symbol reference line(s) 16, 24.
- `eu/src/overlays/ov023/calls/ApplyMenuScreenEntry.c` → `src/ov023/menu_graphics/ApplyMenuScreenEntry_020b5bcc.c`, symbol reference line(s) 26, 38.
- `eu/src/overlays/ov023/calls/ApplyScreenAlphaBlend.c` → `src/ov023/shared_engine/ApplyScreenAlphaBlend_020b6e60.c`, symbol reference line(s) 9, 13.
- `eu/src/overlays/ov023/calls/DestroyScreenState.c` → `src/ov023/shared_engine/DestroyScreenState_020b6ac4.c`, symbol reference line(s) 18, 24, 32.
- `eu/src/overlays/ov023/calls/InitMapMenuState.c` → `src/ov023/menu_graphics/InitMapMenuState_020b6a18.c`, symbol reference line(s) 15, 37.
- `eu/src/overlays/ov023/calls/LoadMenuScreenResource.c` → `src/ov023/menu_graphics/LoadMenuScreenResource_020b5b94.c`, symbol reference line(s) 1, 13.
- `eu/src/overlays/ov023/calls/MarkMapMenuDirty.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov023/calls/PlayEnabledMenuSound.c` → `src/ov023/menu_sound/PlayEnabledMenuSound_020b5b50.c`, symbol reference line(s) 3, 9.
- `eu/src/overlays/ov023/calls/PrepareMenuScreenEntry.c`, symbol reference line(s) 3, 20, 21.
- `eu/src/overlays/ov023/calls/RefreshScaledMenuScreen.c` → `src/ov023/menu_graphics/RefreshScaledMenuScreen_020b5a80.c`, symbol reference line(s) 31, 43.
- `eu/src/overlays/ov023/calls/ResetMapMenuScreen.c` → `src/ov023/menu_graphics/ResetMapMenuScreen_020b6cf4.c`, symbol reference line(s) 29, 41.
- `eu/src/overlays/ov023/calls/UpdateMapMenuState.c` → `src/ov023/menu_graphics/UpdateMapMenuState_020b6afc.c`, symbol reference line(s) 34, 58.
- `eu/src/overlays/ov023/calls/UpdateMenuRangePosition.c` → `src/ov023/menu_graphics/UpdateMenuRangePosition_020b6e40.c`, symbol reference line(s) 1, 9, 11.
- `eu/src/overlays/ov023/data/bss/Bss_ov023_020b6f84.c`, symbol reference line(s) 4.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov025:020b7748` → `gMenuListTaskClass`

Previous label: `data_ov025_020b7748`. Existing ELF symbol size: **20 bytes**. Source: `eu/src/ov025/data/Data_ov025_020b7748.c`.

Native ClassDescriptor prefix: classId/subId packed word 0x000e0018; constructor at +4 (InitMenuScreen); destructor at +8 (ShutdownMenuScreen); workSize +0xc = 0x66dc; heapRef +0x10 = NULL.

The initializer supplies this five-word prefix to CreateTaskObject; Obj_Construct copies classId/subId/workSize, allocates and clears task work, invokes the constructor with the task as current, and stores its returned update callback. The descriptor +8 callback is used during destruction.

Limits: TaskObject class IDs are not priorities or flags. Constructor return is the update callback; +8 is not the update callback. Preserve raw declarations and relocation targets. The existing symbol is exactly the 20-byte descriptor.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov025/data/Data_ov025_020b7748.c`, symbol reference line(s) 8.
- `eu/src/overlays/ov001/calls/InitFieldPanelScene.c`, symbol reference line(s) 44, 89.
- `eu/src/overlays/ov001/data/tables/gPanelModeDataPointers.c`, symbol reference line(s) 5, 11.

Relocations inside this symbol: 2. Native target expressions and addends are retained.

### `ov025:020b7780` → `gMenuListWorkStorage`

Previous label: `data_ov025_020b7780`. Existing ELF symbol size: **32 bytes**. Source: `eu/src/overlays/ov025/data/bss/Bss_ov025_020b7780.c`.

32-byte BSS symbol; only the first word is the menu-list task-work pointer. Remaining 28 bytes are opaque.

InitMenuScreen stores GetRunningTaskWork into the first word. Slot-list operations use work+0x64f4, tile-table operations use work+0x64c8; ShutdownMenuScreen releases the work-owned resources.

Limits: ShutdownMenuScreen clears readiness within the pointee; it does not clear this global pointer. Do not shrink the BSS object to four bytes or call its opaque tail additional pointers.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov025/calls/ActivatePanelEntity.c` → `src/ov025/panel_state/ActivatePanelEntity_020b6328.c`, symbol reference line(s) 9, 13, 14.
- `eu/src/overlays/ov025/calls/ApplySubBgScroll.c` → `src/ov025/menu_widgets/ApplySubBgScroll_020b5800.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov025/calls/DrawMenuEntryWidget.c` → `src/ov025/menu_widgets/DrawMenuEntryWidget_020b59d8.c`, symbol reference line(s) 8, 16.
- `eu/src/overlays/ov025/calls/DrawMenuWidgetGraphic.c` → `src/ov025/menu_widgets/DrawMenuWidgetGraphic_020b597c.c`, symbol reference line(s) 20, 35.
- `eu/src/overlays/ov025/calls/DrawNumberInPanelSlot.c` → `src/ov025/panel_state/DrawNumberInPanelSlot_020b62c4.c`, symbol reference line(s) 3, 13.
- `eu/src/overlays/ov025/calls/GetMenuListPathEntryCount.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov025/calls/HandleDefaultMenuAction.c` → `src/ov025/menu_widgets/HandleDefaultMenuAction_020b5a94.c`, symbol reference line(s) 3, 14.
- `eu/src/overlays/ov025/calls/InitMenuScreen.c` → `src/ov025/shared_engine/InitMenuScreen_020b5acc.c`, symbol reference line(s) 38, 75.
- `eu/src/overlays/ov025/calls/LoadMenuWidgetResource.c` → `src/ov025/menu_widgets/LoadMenuWidgetResource_020b5954.c`, symbol reference line(s) 1, 13.
- `eu/src/overlays/ov025/calls/LookupChannelEntry.c` → `src/ov025/shared_variants/LookupChannelEntry_020b6270.c`, symbol reference line(s) 1, 5.
- `eu/src/overlays/ov025/calls/LookupChannelEntry_020b62ac.c` → `src/ov025/shared_variants/LookupChannelEntry_020b628c.c`, symbol reference line(s) 1, 5.
- `eu/src/overlays/ov025/calls/LookupChannelEntry_020b62c8.c` → `src/ov025/shared_variants/LookupChannelEntry_020b62a8.c`, symbol reference line(s) 1, 5.
- `eu/src/overlays/ov025/calls/RefreshRemainingCount.c` → `src/ov025/menu_widgets/RefreshRemainingCount_020b58d8.c`, symbol reference line(s) 3, 10.
- `eu/src/overlays/ov025/calls/RefreshTagCallbacksAndSchedule.c`, symbol reference line(s) 3, 16.
- `eu/src/overlays/ov025/calls/ResetMenuLayerTransforms.c` → `src/ov025/menu_widgets/ResetMenuLayerTransforms_020b6194.c`, symbol reference line(s) 13, 22.
- `eu/src/overlays/ov025/calls/ResetMenuListToFirstEntry.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov025/calls/ScrollMenuListDownOneRow.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov025/calls/SetAlternateMenuWidgets.c` → `src/ov025/menu_widgets/SetAlternateMenuWidgets_020b61f4.c`, symbol reference line(s) 3, 13, 14.
- `eu/src/overlays/ov025/calls/SetupMenuTextLayers.c` → `src/ov025/shared_engine/SetupMenuTextLayers_020b5c78.c`, symbol reference line(s) 18, 43.
- `eu/src/overlays/ov025/calls/ShutdownMenuScreen.c` → `src/ov025/shared_engine/ShutdownMenuScreen_020b5e8c.c`, symbol reference line(s) 3, 17.
- `eu/src/overlays/ov025/calls/UpdateMenuScreen.c` → `src/ov025/menu_widgets/UpdateMenuScreen_020b5f08.c`, symbol reference line(s) 10, 47.
- `eu/src/overlays/ov025/data/bss/Bss_ov025_020b7780.c`, symbol reference line(s) 3.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov026:020b5ae0` → `gOverlayDisplaySessionTaskClass`

Previous label: `data_ov026_020b5ae0`. Existing ELF symbol size: **20 bytes**. Source: `eu/src/ov026/data/Data_ov026_020b5ae0.c`.

Native ClassDescriptor prefix: classId/subId packed word 0x000e0019; constructor at +4 (BeginOverlayDisplaySession); destructor at +8 (EndOverlayDisplaySession); workSize +0xc = 0x649c; heapRef +0x10 = NULL.

The initializer supplies this five-word prefix to CreateTaskObject; Obj_Construct copies classId/subId/workSize, allocates and clears task work, invokes the constructor with the task as current, and stores its returned update callback. The descriptor +8 callback is used during destruction.

Limits: TaskObject class IDs are not priorities or flags. Constructor return is the update callback; +8 is not the update callback. Preserve raw declarations and relocation targets. The existing symbol is exactly the 20-byte descriptor.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov026/data/Data_ov026_020b5ae0.c`, symbol reference line(s) 8.
- `eu/src/overlays/ov001/calls/InitFieldPanelScene.c`, symbol reference line(s) 45, 97.
- `eu/src/overlays/ov001/data/tables/gPanelModeDataPointers.c`, symbol reference line(s) 6, 13.

Relocations inside this symbol: 2. Native target expressions and addends are retained.

### `ov026:020b5b20` → `gOverlayDisplaySessionWorkStorage`

Previous label: `data_ov026_020b5b20`. Existing ELF symbol size: **32 bytes**. Source: `eu/src/overlays/ov026/data/bss/Bss_ov026_020b5b20.c`.

32-byte BSS symbol; first word points to display-session task work, trailing 28 bytes opaque.

BeginOverlayDisplaySession publishes task work; RunOverlayDisplayUpdate reads it; EndOverlayDisplaySession clears the pointer after resource teardown.

Limits: Opaque bytes retain their original representation and size; this is a symbol rename only.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov026/calls/BeginOverlayDisplaySession.c`, symbol reference line(s) 12, 26.
- `eu/src/overlays/ov026/calls/EndOverlayDisplaySession.c` → `src/ov026/display_session/EndOverlayDisplaySession.c`, symbol reference line(s) 12, 20.
- `eu/src/overlays/ov026/calls/RunOverlayDisplayUpdate.c` → `src/ov026/display_session/RunOverlayDisplayUpdate.c`, symbol reference line(s) 12, 15.
- `eu/src/overlays/ov026/data/bss/Bss_ov026_020b5b20.c`, symbol reference line(s) 3.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov028:020bb324` → `gOv028FieldSceneTaskClass`

Previous label: `data_ov028_020bb324`. Existing ELF symbol size: **20 bytes**. Source: `eu/src/ov028/data/Data_ov028_020bb320.c`.

Native ClassDescriptor prefix: classId/subId packed word 0x0002000e; constructor at +4 (InitFieldOverlayState); destructor at +8 (ReleaseFieldContext); workSize +0xc = 0x24; heapRef +0x10 = NULL.

The initializer supplies this five-word prefix to CreateTaskObject; Obj_Construct copies classId/subId/workSize, allocates and clears task work, invokes the constructor with the task as current, and stores its returned update callback. The descriptor +8 callback is used during destruction.

Limits: TaskObject class IDs are not priorities or flags. Constructor return is the update callback; +8 is not the update callback. Preserve raw declarations and relocation targets. The existing symbol is exactly the 20-byte descriptor.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov028/data/Data_ov028_020bb320.c`, symbol reference line(s) 8.
- `eu/src/overlays/ov028/calls/CreateOv028FieldSceneTask.c` → `src/ov028/reviewed_helpers/func_ov028_020bafc8.c`, symbol reference line(s) 2, 6.

Relocations inside this symbol: 2. Native target expressions and addends are retained.

### `ov028:020bb320` → `gOv028FieldSceneTaskHandle`

Previous label: `data_ov028_020bb320`. Existing ELF symbol size: **4 bytes**. Source: `eu/src/ov028/data/Data_ov028_020bb320.c`.

4-byte task handle, ROM initialized to 0xffffffff.

The scene creator stores CreateTaskObject result; release/request paths pass the handle to task destruction and use -1 as the inactive sentinel.

Limits: Task handle is distinct from the scene-work pointer stored in the separate 32-byte BSS object. Preserve signed sentinel bits.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov028/data/Data_ov028_020bb320.c`, symbol reference line(s) 16.
- `eu/src/overlays/ov028/calls/CreateOv028FieldSceneTask.c` → `src/ov028/reviewed_helpers/func_ov028_020bafc8.c`, symbol reference line(s) 3, 6.
- `eu/src/overlays/ov028/calls/HasFieldSceneTaskSignal.c`, symbol reference line(s) 3, 8.
- `eu/src/overlays/ov028/calls/ReleaseHandle_020bb0a4.c` → `src/ov028/unclassified_helpers/ReleaseHandle_020bb084.c`, symbol reference line(s) 3, 8, 9.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov028:020bb3a0` → `gOv028FieldSceneWorkStorage`

Previous label: `data_ov028_020bb3a0`. Existing ELF symbol size: **32 bytes**. Source: `eu/src/overlays/ov028/data/bss/Bss_ov028_020bb3a0.c`.

32-byte BSS symbol; first word points to scene task work, trailing 28 bytes opaque.

InitFieldOverlayState publishes the current task work; ReleaseFieldContext and field-scene operations borrow that pointer. Ov028FieldState.h exposes the same owner.

Limits: Do not reinterpret this storage as a handle/work pair; the handle is at ov028:020bb320.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov028/Ov028FieldState.h`, symbol reference line(s) 14, 15.
- `eu/src/overlays/ov028/calls/BeginFieldSceneSlowdownTransition.c`, symbol reference line(s) 5, 30.
- `eu/src/overlays/ov028/calls/ClearFieldSceneReadyFlag.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov028/calls/EnterOverlayTransition.c` → `src/ov028/overlay_state/EnterOverlayTransition_020bac78.c`, symbol reference line(s) 1, 10, 12.
- `eu/src/overlays/ov028/calls/FieldSceneState_EndSlowdownWhenScreenIdle.c`, symbol reference line(s) 3, 11.
- `eu/src/overlays/ov028/calls/FieldSceneState_RestoreActorsAndLoadShadow.c`, symbol reference line(s) 3, 11, 12, 15.
- `eu/src/overlays/ov028/calls/FinishFieldSceneState.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov028/calls/InitFieldOverlayState.c` → `src/ov028/overlay_state/InitFieldOverlayState_020ba3e0.c`, symbol reference line(s) 31, 63, 64, 65, 66, 76, 100, 102, 103, 104, 106.
- `eu/src/overlays/ov028/calls/IsFieldSceneStartupComplete.c`, symbol reference line(s) 8, 12, 15.
- `eu/src/overlays/ov028/calls/IsSceneUnpaused.c` → `src/ov028/overlay_state/IsSceneUnpaused_020bb15c.c`, symbol reference line(s) 8, 13.
- `eu/src/overlays/ov028/calls/Ov028SceneState_BeginFadeOutWhenIdle.c`, symbol reference line(s) 3, 13, 14.
- `eu/src/overlays/ov028/calls/Ov028SceneState_BeginScreenModeTransition.c`, symbol reference line(s) 3, 8, 10.
- `eu/src/overlays/ov028/calls/Ov028SceneState_FinishMenuResourceLoad.c`, symbol reference line(s) 6, 42.
- `eu/src/overlays/ov028/calls/Ov028SceneState_PushVramWhenIdle.c`, symbol reference line(s) 3, 13.
- `eu/src/overlays/ov028/calls/Ov028SceneState_StoreEventRecordBytes.c`, symbol reference line(s) 3, 11.
- `eu/src/overlays/ov028/calls/Ov028SceneState_WaitFadeOut.c`, symbol reference line(s) 3, 11.
- `eu/src/overlays/ov028/calls/Ov028SceneState_WaitForListNodes.c`, symbol reference line(s) 3, 13.
- `eu/src/overlays/ov028/calls/ReleaseFieldContext.c` → `src/ov028/unclassified_helpers/ReleaseFieldContext_020ba60c.c`, symbol reference line(s) 3, 14, 15, 17, 19, 23.
- `eu/src/overlays/ov028/calls/ResumeFieldFromMenu.c`, symbol reference line(s) 11, 30, 57, 67.
- `eu/src/overlays/ov028/calls/RunSceneStateMachine.c`, symbol reference line(s) 10, 20, 21, 23, 25, 26, 29.
- `eu/src/overlays/ov028/calls/SceneState_WaitPanelReady.c`, symbol reference line(s) 8, 17, 18.
- `eu/src/overlays/ov028/calls/SceneState_WaitScreenIdle.c`, symbol reference line(s) 14, 21.
- `eu/src/overlays/ov028/calls/SetFieldModeFlag.c` → `src/ov028/unclassified_helpers/SetFieldModeFlag_020bb03c.c`, symbol reference line(s) 3, 7, 8.
- `eu/src/overlays/ov028/calls/SetOrClearStatusBit2.c` → `src/ov028/unclassified_helpers/SetOrClearStatusBit2_020bb2a8.c`, symbol reference line(s) 3, 8, 11.
- `eu/src/overlays/ov028/calls/SetupSceneFromParams.c` → `src/ov028/overlay_state/SetupSceneFromParams_020bb0a4.c`, symbol reference line(s) 20, 29, 30, 31, 32, 33, 34, 35.
- `eu/src/overlays/ov028/calls/ShutdownFieldAndSaveActorPoses.c`, symbol reference line(s) 9, 34, 48, 55.
- `eu/src/overlays/ov028/calls/UpdateOv028FieldScene.c`, symbol reference line(s) 3, 15.
- `eu/src/overlays/ov028/data/bss/Bss_ov028_020bb3a0.c`, symbol reference line(s) 3.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov029:020bab84` → `gOv029SceneTaskClass`

Previous label: `data_ov029_020bab84`. Existing ELF symbol size: **20 bytes**. Source: `eu/src/ov029/data/Data_ov029_020bab80.c`.

Native ClassDescriptor prefix: classId/subId packed word 0x0002000e; constructor at +4 (InitOv029OverlayState); destructor at +8 (ShutdownOv029SoundCtx); workSize +0xc = 0x18; heapRef +0x10 = NULL.

The initializer supplies this five-word prefix to CreateTaskObject; Obj_Construct copies classId/subId/workSize, allocates and clears task work, invokes the constructor with the task as current, and stores its returned update callback. The descriptor +8 callback is used during destruction.

Limits: TaskObject class IDs are not priorities or flags. Constructor return is the update callback; +8 is not the update callback. Preserve raw declarations and relocation targets. The existing symbol is exactly the 20-byte descriptor.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov029/data/Data_ov029_020bab80.c`, symbol reference line(s) 8.
- `eu/src/overlays/ov029/calls/CreateOv029FieldSceneTask.c` → `src/ov029/reviewed_helpers/func_ov029_020ba9b0.c`, symbol reference line(s) 2, 6.

Relocations inside this symbol: 2. Native target expressions and addends are retained.

### `ov029:020bab80` → `gOv029SceneTaskHandle`

Previous label: `data_ov029_020bab80`. Existing ELF symbol size: **4 bytes**. Source: `eu/src/ov029/data/Data_ov029_020bab80.c`.

4-byte task handle initialized to 0xffffffff.

Scene creation stores CreateTaskObject result; scene shutdown uses this task handle.

Limits: The native destructor name contains SoundCtx, but the descriptor and scene owner do not establish a general sound-engine owner.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov029/data/Data_ov029_020bab80.c`, symbol reference line(s) 16.
- `eu/src/overlays/ov029/calls/CreateOv029FieldSceneTask.c` → `src/ov029/reviewed_helpers/func_ov029_020ba9b0.c`, symbol reference line(s) 3, 6.
- `eu/src/overlays/ov029/calls/HasOv029ObjectField28.c` → `src/ov029/reviewed_helpers/HasOv029ObjectField28_020baa40.c`, symbol reference line(s) 4, 10.
- `eu/src/overlays/ov029/calls/ReleaseOv029Object.c` → `src/ov029/reviewed_helpers/ReleaseOv029Object_020baa64.c`, symbol reference line(s) 4, 8, 9.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov029:020babc0` → `gOv029SceneWorkStorage`

Previous label: `data_ov029_020babc0`. Existing ELF symbol size: **32 bytes**. Source: `eu/src/overlays/ov029/data/bss/Bss_ov029_020babc0.c`.

32-byte BSS symbol; first word points to scene task work, trailing 28 bytes opaque.

InitOv029OverlayState publishes the work; ShutdownOv029SoundCtx and Ov029SceneState.h consumers access the same pointer.

Limits: Do not infer sound-only ownership from the legacy native destructor name.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov029/Ov029SceneState.h`, symbol reference line(s) 22.
- `eu/src/overlays/ov029/calls/ApplyOv029SceneParams.c`, symbol reference line(s) 19, 23, 24, 25, 26, 27.
- `eu/src/overlays/ov029/calls/DisableOv029Sound.c` → `src/ov029/reviewed_helpers/DisableOv029Sound_020ba768.c`, symbol reference line(s) 3, 42, 48.
- `eu/src/overlays/ov029/calls/EnableOv029Sound.c` → `src/ov029/reviewed_helpers/EnableOv029Sound_020ba670.c`, symbol reference line(s) 3, 21, 31.
- `eu/src/overlays/ov029/calls/FinishOv029MenuLoad.c` → `src/ov029/overlay_state/FinishOv029MenuLoad_020ba5dc.c`, symbol reference line(s) 8, 41.
- `eu/src/overlays/ov029/calls/HandleOverlayExitFlag.c` → `src/ov029/unclassified_helpers/HandleOverlayExitFlag_020ba708.c`, symbol reference line(s) 4, 13, 19.
- `eu/src/overlays/ov029/calls/InitOv029OverlayState.c` → `src/ov029/overlay_state/InitOv029OverlayState_020ba3e0.c`, symbol reference line(s) 29, 46, 47, 48, 49, 50, 58, 59, 60.
- `eu/src/overlays/ov029/calls/IsOv029SceneStartupComplete.c`, symbol reference line(s) 8, 12, 15.
- `eu/src/overlays/ov029/calls/MarkSoundCtxActive.c` → `src/ov029/reviewed_helpers/MarkSoundCtxActive_020ba5a0.c`, symbol reference line(s) 3, 9.
- `eu/src/overlays/ov029/calls/Ov029SceneState_PushVramWhenIdle.c`, symbol reference line(s) 3, 13.
- `eu/src/overlays/ov029/calls/Ov029_ClearSceneFlag1.c`, symbol reference line(s) 5.
- `eu/src/overlays/ov029/calls/Ov029_ClearSceneModeBits.c`, symbol reference line(s) 5.
- `eu/src/overlays/ov029/calls/Ov029_SetSceneFlag4000.c`, symbol reference line(s) 5.
- `eu/src/overlays/ov029/calls/RunSceneStateMachine_020ba4c4.c`, symbol reference line(s) 10, 20, 21, 23, 25, 26, 29.
- `eu/src/overlays/ov029/calls/ShutdownOv029SoundCtx.c` → `src/ov029/reviewed_helpers/ShutdownOv029SoundCtx_020ba52c.c`, symbol reference line(s) 3, 11, 12, 14.
- `eu/src/overlays/ov029/data/bss/Bss_ov029_020babc0.c`, symbol reference line(s) 3.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov030:020bd020` → `gOv030SceneWork`

Previous label: `data_ov030_020bd020`. Existing ELF symbol size: **4 bytes**. Source: `eu/src/overlays/ov030/data/bss/Bss_ov030_020bd020.c`.

4-byte pointer to the ov030 scene task work.

InitMovieOverlayState obtains and publishes running task work; scene flag and vector operations access that allocation.

Limits: The native constructor name contains Movie but does not make this the MobiClip decoder owner. Already-named gMarkerReset storage in the same source is unchanged.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov030/auto/GetOv030FieldTransitionFlags.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov030/auto/GetOv030SceneLock.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov030/calls/ApplyMovieStartParams.c` → `src/ov030/movie/ApplyMovieStartParams_020bac48.c`, symbol reference line(s) 26, 35, 38, 39, 40, 41, 42, 43, 44.
- `eu/src/overlays/ov030/calls/ApplyOverlayScaleMode.c` → `src/ov030/overlay_state/ApplyOverlayScaleMode_020baab4.c`, symbol reference line(s) 1, 14.
- `eu/src/overlays/ov030/calls/ClearMovieSceneFlag1.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov030/calls/ClearSceneEntry.c` → `src/ov030/shared_engine/ClearSceneEntry_020bb424.c`, symbol reference line(s) 13, 18.
- `eu/src/overlays/ov030/calls/FinishMoviePlaybackState.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov030/calls/FinishSceneSetup.c` → `src/ov030/shared_engine/FinishSceneSetup_020ba594.c`, symbol reference line(s) 9, 15, 16, 19.
- `eu/src/overlays/ov030/calls/InitMovieOverlayState_020ba400.c` → `src/ov030/movie/InitMovieOverlayState_020ba3e0.c`, symbol reference line(s) 41, 67, 68, 69, 70, 74, 75, 81, 82, 88, 89, 91, 96.
- `eu/src/overlays/ov030/calls/IsOv030SceneStartupComplete.c`, symbol reference line(s) 3, 6, 9.
- `eu/src/overlays/ov030/calls/IsSceneUnpaused_020bacd4.c` → `src/ov030/shared_engine/IsSceneUnpaused_020bacb4.c`, symbol reference line(s) 8, 13.
- `eu/src/overlays/ov030/calls/LoadCameraParams.c` → `src/ov030/movie/LoadCameraParams_020bb390.c`, symbol reference line(s) 25, 42, 43, 48, 50, 51, 54, 55, 56.
- `eu/src/overlays/ov030/calls/MoviePlayer_Close.c` → `src/ov030/movie/MoviePlayer_Close_020ba518.c`, symbol reference line(s) 3, 15, 16, 17, 19, 21, 25.
- `eu/src/overlays/ov030/calls/MoviePlayer_EnterPlayback.c`, symbol reference line(s) 18, 38, 55, 60, 61, 68.
- `eu/src/overlays/ov030/calls/MoviePlayer_Stop.c` → `src/ov030/movie/MoviePlayer_Stop_020ba9d0.c`, symbol reference line(s) 3, 30, 52, 59.
- `eu/src/overlays/ov030/calls/Ov030SceneState_BeginFadeOutWhenIdle.c`, symbol reference line(s) 3, 13, 14.
- `eu/src/overlays/ov030/calls/Ov030SceneState_BeginScreenModeTransition.c`, symbol reference line(s) 3, 10, 11.
- `eu/src/overlays/ov030/calls/Ov030SceneState_FinishMenuResourceLoad.c`, symbol reference line(s) 6, 45.
- `eu/src/overlays/ov030/calls/Ov030SceneState_FinishSlowdownTransition.c`, symbol reference line(s) 3, 12, 13.
- `eu/src/overlays/ov030/calls/Ov030SceneState_FinishStartupWhenPanelReady.c`, symbol reference line(s) 3, 15, 16.
- `eu/src/overlays/ov030/calls/Ov030SceneState_PushVramWhenIdle.c`, symbol reference line(s) 3, 16.
- `eu/src/overlays/ov030/calls/Ov030SceneState_StartIdleObjects.c`, symbol reference line(s) 3, 11, 12.
- `eu/src/overlays/ov030/calls/Ov030SceneState_StoreEventRecordBytes.c`, symbol reference line(s) 3, 15.
- `eu/src/overlays/ov030/calls/Ov030SceneState_WaitFadeOut.c`, symbol reference line(s) 3, 12.
- `eu/src/overlays/ov030/calls/Ov030SceneState_WaitForListNodes.c`, symbol reference line(s) 3, 16.
- `eu/src/overlays/ov030/calls/RequestOv030SceneExit.c`, symbol reference line(s) 3, 7, 8.
- `eu/src/overlays/ov030/calls/ResolveMovieSceneAction.c`, symbol reference line(s) 9, 19, 22, 29, 35.
- `eu/src/overlays/ov030/calls/RunSceneStateMachine_020ba4e0.c` → `src/ov030/shared_engine/RunSceneStateMachine_020ba4c0.c`, symbol reference line(s) 10, 20, 21, 23, 25, 26, 29.
- `eu/src/overlays/ov030/calls/SceneState_WaitScreenIdle_020ba894.c`, symbol reference line(s) 14, 21.
- `eu/src/overlays/ov030/calls/SetOv030SceneDrawEnabled.c`, symbol reference line(s) 3, 8, 11.
- `eu/src/overlays/ov030/calls/SetSceneLock.c` → `src/ov030/shared_engine/SetSceneLock_020bb374.c`, symbol reference line(s) 8, 13.
- `eu/src/overlays/ov030/calls/SuspendSceneAtQuarterRate.c` → `src/ov030/movie/SuspendSceneAtQuarterRate_020bb220.c`, symbol reference line(s) 16, 36.
- `eu/src/overlays/ov030/calls/UpdateCameraTriggers.c` → `src/ov030/movie/UpdateCameraTriggers_020baccc.c`, symbol reference line(s) 57, 137, 146, 151, 160, 178, 182, 206, 216, 218, 219, 220, 263, 267, 269, 281, 292, 306, 313, 314.
- `eu/src/overlays/ov030/calls/GetOv030SceneReferenceAxis.c`, symbol reference line(s) 3, 7, 8.
- `eu/src/overlays/ov030/data/bss/Bss_ov030_020bd020.c`, symbol reference line(s) 4.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov031:020bc7a4` → `gOv031SceneTaskClass`

Previous label: `data_ov031_020bc7a4`. Existing ELF symbol size: **20 bytes**. Source: `eu/src/ov031/data/Data_ov031_020bc7a0.c`.

Native ClassDescriptor prefix: classId/subId packed word 0x0002000e; constructor at +4 (InitMoviePlayerState); destructor at +8 (ShutdownActiveState); workSize +0xc = 0x408; heapRef +0x10 = NULL.

The initializer supplies this five-word prefix to CreateTaskObject; Obj_Construct copies classId/subId/workSize, allocates and clears task work, invokes the constructor with the task as current, and stores its returned update callback. The descriptor +8 callback is used during destruction.

Limits: TaskObject class IDs are not priorities or flags. Constructor return is the update callback; +8 is not the update callback. Preserve raw declarations and relocation targets. The existing symbol is exactly the 20-byte descriptor.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov031/data/Data_ov031_020bc7a0.c`, symbol reference line(s) 62.
- `eu/src/overlays/ov031/calls/CreateOv031FieldSceneTask.c` → `src/ov031/shared_engine/MobiClip_SrcOpen_020bb474.c`, symbol reference line(s) 2, 6.

Relocations inside this symbol: 2. Native target expressions and addends are retained.

### `ov031:020bc7a0` → `gOv031SceneTaskHandle`

Previous label: `data_ov031_020bc7a0`. Existing ELF symbol size: **4 bytes**. Source: `eu/src/ov031/data/Data_ov031_020bc7a0.c`.

4-byte task handle initialized to 0xffffffff.

CreateTaskObject for the ov031 descriptor publishes this handle; shutdown acts on that task.

Limits: Scene ownership is established by its bank and descriptor; the old MoviePlayerState constructor name does not prove decoder ownership.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov031/data/Data_ov031_020bc7a0.c`, symbol reference line(s) 70.
- `eu/src/overlays/ov031/calls/CreateOv031FieldSceneTask.c` → `src/ov031/shared_engine/MobiClip_SrcOpen_020bb474.c`, symbol reference line(s) 3, 6.
- `eu/src/overlays/ov031/calls/IsPxiFifoTagSet.c` → `src/ov031/unclassified_helpers/IsPxiFifoTagSet_020bb4dc.c`, symbol reference line(s) 3, 10.
- `eu/src/overlays/ov031/calls/ReleasePxiFifoTag.c` → `src/ov031/unclassified_helpers/ReleasePxiFifoTag_020bb4f8.c`, symbol reference line(s) 3, 10, 11.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov031:020bc7b8` → `gOv031SceneStateHandlerStorage`

Previous label: `data_ov031_020bc7b8`. Existing ELF symbol size: **93 bytes**. Source: `eu/src/ov031/data/Data_ov031_020bc7a0.c`.

93-byte packed initialized symbol: 19 native code-pointer words followed by 17 zero bytes.

RunStateMachine indexes the 19-handler prefix with current state; the packed initializer and ELF relocations establish the pointer slots.

Limits: Do not type the entire 93 bytes as a 19-element pointer array, discard the 17-byte tail, or absorb the neighboring bc815 symbol. Handler return/state protocol remains unchanged.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov031/data/Data_ov031_020bc7a0.c`, symbol reference line(s) 34.
- `eu/src/overlays/ov031/calls/RunStateMachine.c` → `src/ov031/state_machine/RunStateMachine_020ba4b4.c`, symbol reference line(s) 15, 26.

Relocations inside this symbol: 19. Native target expressions and addends are retained.

### `ov031:020bc820` → `gOv031SceneWorkStorage`

Previous label: `data_ov031_020bc820`. Existing ELF symbol size: **32 bytes**. Source: `eu/src/overlays/ov031/data/bss/Bss_ov031_020bc820.c`.

32-byte BSS symbol; first word points to ov031 task work, trailing 28 bytes opaque.

InitMoviePlayerState publishes current task work; ShutdownActiveState and scene state/record/scroll operations use it.

Limits: No assertion that this scene work is a decoder. The task handle is separately stored at ov031:020bc7a0.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov031/Ov031MovieState.h`, symbol reference line(s) 23, 24.
- `eu/src/overlays/ov031/auto/GetOv031FieldTransitionFlag.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov031/auto/GetSceneScrollTargetSpeed.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov031/calls/AdvanceGroupObjects.c` → `src/ov031/overlay_state/AdvanceGroupObjects_020baf38.c`, symbol reference line(s) 42, 75, 78, 79, 80, 84, 85, 86.
- `eu/src/overlays/ov031/calls/AdvanceRecordStep.c` → `src/ov031/overlay_state/AdvanceRecordStep_020bc554.c`, symbol reference line(s) 13, 22, 23.
- `eu/src/overlays/ov031/calls/ApplyOverlayScaleMode_020bab40.c` → `src/ov031/overlay_state/ApplyOverlayScaleMode_020bab20.c`, symbol reference line(s) 1, 16.
- `eu/src/overlays/ov031/calls/ApplyStartParams.c` → `src/ov031/overlay_state/ApplyStartParams_020bb518.c`, symbol reference line(s) 21, 26, 27, 28, 29, 30, 31, 32.
- `eu/src/overlays/ov031/calls/BeginNextRecord.c` → `src/ov031/overlay_state/BeginNextRecord_020bb62c.c`, symbol reference line(s) 37, 52, 53, 54, 55, 58, 67, 68, 69, 74, 76, 82, 83.
- `eu/src/overlays/ov031/calls/BuildSceneGroups.c` → `src/ov031/overlay_state/BuildSceneGroups_020bb6f0.c`, symbol reference line(s) 106, 125, 126, 168, 170, 171, 173, 174, 175, 176, 178, 179, 180, 181, 182, 184, 188, 193, 194, 212, 227, 228, 234, 238, 239, 243, 244, 245, 246, 247, 248, 249, 251, 264, 265, 266, 282.
- `eu/src/overlays/ov031/calls/CanLeaveActiveRecord.c` → `src/ov031/overlay_state/CanLeaveActiveRecord_020bb010.c`, symbol reference line(s) 17, 22.
- `eu/src/overlays/ov031/calls/CanStartIdleRecord.c` → `src/ov031/overlay_state/CanStartIdleRecord_020bc650.c`, symbol reference line(s) 17, 24, 27.
- `eu/src/overlays/ov031/calls/ClearMovieSourceReadyFlag.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov031/calls/DrawSceneGroups.c` → `src/ov031/overlay_state/DrawSceneGroups_020bb2d4.c`, symbol reference line(s) 27, 38, 39, 40, 46, 48, 50, 52.
- `eu/src/overlays/ov031/calls/EnterState10.c` → `src/ov031/state_machine/EnterState10_020ba8c0.c`, symbol reference line(s) 10, 17, 18.
- `eu/src/overlays/ov031/calls/EnterState15.c` → `src/ov031/state_machine/EnterState15_020ba9a8.c`, symbol reference line(s) 8, 16, 17.
- `eu/src/overlays/ov031/calls/EnterState2.c` → `src/ov031/state_machine/EnterState2_020ba640.c`, symbol reference line(s) 10, 16, 17, 20.
- `eu/src/overlays/ov031/calls/EnterState7Alt.c` → `src/ov031/state_machine/EnterState7Alt_020ba890.c`, symbol reference line(s) 8, 20.
- `eu/src/overlays/ov031/calls/FindNearestStageEvent.c` → `src/ov031/overlay_state/FindNearestStageEvent_020bab74.c`, symbol reference line(s) 9, 28, 37.
- `eu/src/overlays/ov031/calls/FinishMoviePlayerState.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov031/calls/FreeSceneRecords.c` → `src/ov031/overlay_state/FreeSceneRecords_020ba51c.c`, symbol reference line(s) 32, 40, 41, 43, 44, 46, 47, 48, 49, 50, 51, 52, 54, 55, 56.
- `eu/src/overlays/ov031/calls/GetField28.c` → `src/ov031/unclassified_helpers/GetField28_020bbff4.c`, symbol reference line(s) 8, 12, 13.
- `eu/src/overlays/ov031/calls/GetNegatedCombinedOffset.c` → `src/ov031/overlay_state/GetNegatedCombinedOffset_020bc68c.c`, symbol reference line(s) 1, 10.
- `eu/src/overlays/ov031/calls/GetSceneDepthCullDistance.c` → `src/ov031/leaf_research/func_ov031_020bc700.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov031/calls/GetSceneScrollAccelerationStep.c` → `src/ov031/overlay_state/GetSeekStep_020bc018.c`, symbol reference line(s) 11, 15.
- `eu/src/overlays/ov031/calls/GetSceneScrollDirection.c` → `src/ov031/unclassified_helpers/GetSubStruct1C_020bbfe0.c`, symbol reference line(s) 3, 7, 8.
- `eu/src/overlays/ov031/calls/InitMoviePlayerState.c` → `src/ov031/shared_engine/InitMoviePlayerState_020ba3e0.c`, symbol reference line(s) 43, 66, 67, 68, 69, 73, 74, 75, 76, 77, 81, 84, 85, 91, 94, 95.
- `eu/src/overlays/ov031/calls/IsOv031SceneStartupComplete.c`, symbol reference line(s) 3, 6, 9.
- `eu/src/overlays/ov031/calls/IsStopFlagClear.c` → `src/ov031/overlay_state/IsStopFlagClear_020bb55c.c`, symbol reference line(s) 8, 13.
- `eu/src/overlays/ov031/calls/LinkPendingNode.c` → `src/ov031/overlay_state/LinkPendingNode_020bc5e0.c`, symbol reference line(s) 12, 19, 24, 28.
- `eu/src/overlays/ov031/calls/LoadSceneData.c`, symbol reference line(s) 145, 221, 223, 228, 229, 230, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 250, 251, 252, 253, 254, 255, 257, 258, 259, 260, 261, 262, 264, 265, 266, 267, 268, 269, 271, 272, 273, 274, 275, 278, 279, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 300, 303, 304, 305, 306, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 322.
- `eu/src/overlays/ov031/calls/PlaceRecordPanels.c` → `src/ov031/overlay_state/PlaceRecordPanels_020bbce8.c`, symbol reference line(s) 43, 71.
- `eu/src/overlays/ov031/calls/ReleaseActiveRecordItems.c` → `src/ov031/overlay_state/ReleaseActiveRecordItems_020bbe6c.c`, symbol reference line(s) 23, 31.
- `eu/src/overlays/ov031/calls/ReleaseCurrentSceneRecord.c`, symbol reference line(s) 3, 12, 13, 16, 21.
- `eu/src/overlays/ov031/calls/RemoveGroupObjectsFromTree.c` → `src/ov031/overlay_state/RemoveGroupObjectsFromTree_020bbde4.c`, symbol reference line(s) 27, 37, 38, 39.
- `eu/src/overlays/ov031/calls/ReportContextError.c` → `src/ov031/unclassified_helpers/ReportContextError_020bc524.c`, symbol reference line(s) 8, 17.
- `eu/src/overlays/ov031/calls/ResetField44.c` → `src/ov031/unclassified_helpers/ResetField44_020bbea4.c`, symbol reference line(s) 8, 14.
- `eu/src/overlays/ov031/calls/ResetOverlaySelection.c` → `src/ov031/overlay_state/ResetOverlaySelection_020bc4f0.c`, symbol reference line(s) 1, 10, 12.
- `eu/src/overlays/ov031/calls/ResetSceneState.c` → `src/ov031/state_machine/ResetSceneState_020bbf34.c`, symbol reference line(s) 17, 37.
- `eu/src/overlays/ov031/calls/RestoreActiveRecordItems.c` → `src/ov031/overlay_state/RestoreActiveRecordItems_020bbc84.c`, symbol reference line(s) 24, 35.
- `eu/src/overlays/ov031/calls/RunStateMachine.c` → `src/ov031/state_machine/RunStateMachine_020ba4b4.c`, symbol reference line(s) 14, 23, 25, 26, 28, 30, 31, 34.
- `eu/src/overlays/ov031/calls/SelectNextState.c` → `src/ov031/state_machine/SelectNextState_020ba7f8.c`, symbol reference line(s) 10, 19, 23, 31, 38.
- `eu/src/overlays/ov031/calls/SetFlagBit4.c` → `src/ov031/unclassified_helpers/SetFlagBit4_020bc748.c`, symbol reference line(s) 8, 13, 16.
- `eu/src/overlays/ov031/calls/SetModeByte.c` → `src/ov031/unclassified_helpers/SetModeByte_020bb4c0.c`, symbol reference line(s) 10, 14, 15.
- `eu/src/overlays/ov031/calls/SetSceneScrollSpeedTarget.c` → `src/ov031/unclassified_helpers/SetFields30And34_020bc008.c`, symbol reference line(s) 9, 13, 14.
- `eu/src/overlays/ov031/calls/ShutdownActiveState.c` → `src/ov031/state_machine/ShutdownActiveState_020ba5d0.c`, symbol reference line(s) 9, 23, 25, 27, 31.
- `eu/src/overlays/ov031/calls/TryEnterState1.c` → `src/ov031/state_machine/TryEnterState1_020ba614.c`, symbol reference line(s) 8, 21.
- `eu/src/overlays/ov031/calls/TryEnterState16.c` → `src/ov031/state_machine/TryEnterState16_020ba9d0.c`, symbol reference line(s) 10, 20, 21.
- `eu/src/overlays/ov031/calls/TryEnterState17.c` → `src/ov031/state_machine/TryEnterState17_020baa0c.c`, symbol reference line(s) 8, 17.
- `eu/src/overlays/ov031/calls/TryEnterState18.c` → `src/ov031/state_machine/TryEnterState18_020baa34.c`, symbol reference line(s) 8, 36, 62, 68.
- `eu/src/overlays/ov031/calls/TryEnterState3.c` → `src/ov031/state_machine/TryEnterState3_020ba678.c`, symbol reference line(s) 8, 21.
- `eu/src/overlays/ov031/calls/TryEnterState5.c` → `src/ov031/state_machine/TryEnterState5_020ba6bc.c`, symbol reference line(s) 8, 49.
- `eu/src/overlays/ov031/calls/TryEnterState6.c` → `src/ov031/state_machine/TryEnterState6_020ba72c.c`, symbol reference line(s) 10, 28, 38, 49.
- `eu/src/overlays/ov031/calls/TryEnterState7.c` → `src/ov031/state_machine/TryEnterState7_020ba7c4.c`, symbol reference line(s) 8, 20, 21.
- `eu/src/overlays/ov031/calls/TryLeaveToState7.c`, symbol reference line(s) 15, 22.
- `eu/src/overlays/ov031/calls/TryReenterState7Clear.c` → `src/ov031/state_machine/TryReenterState7Clear_020ba980.c`, symbol reference line(s) 8, 17.
- `eu/src/overlays/ov031/calls/UnlinkPendingNode.c` → `src/ov031/overlay_state/UnlinkPendingNode_020bc618.c`, symbol reference line(s) 12, 19, 24.
- `eu/src/overlays/ov031/calls/UpdateRecordActors.c` → `src/ov031/overlay_state/UpdateRecordActors_020bbb88.c`, symbol reference line(s) 44, 68.
- `eu/src/overlays/ov031/calls/UpdateSceneRecord.c` → `src/ov031/overlay_state/UpdateSceneRecord_020babf8.c`, symbol reference line(s) 88, 131, 132, 136, 138, 141, 144, 145, 146, 147, 148, 149, 151, 152, 155, 156, 161, 165, 168, 171, 174, 175, 179, 186, 188, 192, 193, 194, 213, 214, 219, 224, 226, 227, 228, 229, 231.
- `eu/src/overlays/ov031/calls/UpdateSceneScroll.c` → `src/ov031/overlay_state/UpdateSceneScroll_020bb054.c`, symbol reference line(s) 80, 148, 159, 160, 161, 163, 164, 173, 177, 180, 181, 182, 190, 191, 194, 195, 196, 201, 209, 210.
- `eu/src/overlays/ov031/data/bss/Bss_ov031_020bc820.c`, symbol reference line(s) 3.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov032:020bffe4` → `gGroupSceneTaskClass`

Previous label: `data_ov032_020bffe4`. Existing ELF symbol size: **20 bytes**. Source: `eu/src/ov032/data/Data_ov032_020bffe0.c`.

Native ClassDescriptor prefix: classId/subId packed word 0x0002000e; constructor at +4 (InitSceneOverlayState); destructor at +8 (DestroySceneState); workSize +0xc = 0x50; heapRef +0x10 = NULL.

The initializer supplies this five-word prefix to CreateTaskObject; Obj_Construct copies classId/subId/workSize, allocates and clears task work, invokes the constructor with the task as current, and stores its returned update callback. The descriptor +8 callback is used during destruction.

Limits: TaskObject class IDs are not priorities or flags. Constructor return is the update callback; +8 is not the update callback. Preserve raw declarations and relocation targets. The existing symbol is exactly the 20-byte descriptor.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov032/data/Data_ov032_020bffe0.c`, symbol reference line(s) 8.
- `eu/src/overlays/ov032/calls/CreateOv032FieldSceneTask.c` → `src/ov032/shared_engine/MobiClip_SrcOpen_020bb448.c`, symbol reference line(s) 2, 6.

Relocations inside this symbol: 2. Native target expressions and addends are retained.

### `ov032:020bffe0` → `gGroupSceneTaskHandle`

Previous label: `data_ov032_020bffe0`. Existing ELF symbol size: **4 bytes**. Source: `eu/src/ov032/data/Data_ov032_020bffe0.c`.

4-byte task handle initialized to 0xffffffff.

Group-scene task creation stores the returned task object handle; destruction uses the same global.

Limits: Do not confuse the task handle with routed-context or scene-work pointers.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov032/data/Data_ov032_020bffe0.c`, symbol reference line(s) 16.
- `eu/src/overlays/ov032/calls/CreateOv032FieldSceneTask.c` → `src/ov032/shared_engine/MobiClip_SrcOpen_020bb448.c`, symbol reference line(s) 3, 6.
- `eu/src/overlays/ov032/calls/MobiClip_SrcClose.c` → `src/ov032/shared_engine/MobiClip_SrcClose_020bb4c8.c`, symbol reference line(s) 3, 8, 9.
- `eu/src/overlays/ov032/calls/MobiClip_SrcIsOpen.c` → `src/ov032/shared_engine/MobiClip_SrcIsOpen_020bb4ac.c`, symbol reference line(s) 3, 8.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov032:020c0050` → `gGroupMenuGaugeTaskClass`

Previous label: `data_ov032_020c0050`. Existing ELF symbol size: **20 bytes**. Source: `eu/src/ov032/data/Data_ov032_020c0050.c`.

Native ClassDescriptor prefix: classId/subId packed word 0x000e0015; constructor at +4 (InitGroupMenuGauge); destructor at +8 (ReleaseGroupResourceBuffers); workSize +0xc = 0x2c; heapRef +0x10 = NULL.

The initializer supplies this five-word prefix to CreateTaskObject; Obj_Construct copies classId/subId/workSize, allocates and clears task work, invokes the constructor with the task as current, and stores its returned update callback. The descriptor +8 callback is used during destruction.

Limits: TaskObject class IDs are not priorities or flags. Constructor return is the update callback; +8 is not the update callback. Preserve raw declarations and relocation targets. The existing symbol is exactly the 20-byte descriptor.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov032/data/Data_ov032_020c0050.c`, symbol reference line(s) 8.
- `eu/src/overlays/ov032/calls/InitSceneOverlayState.c` → `src/ov032/unclassified_helpers/InitSceneOverlayState_020ba3e0.c`, symbol reference line(s) 63, 124.

Relocations inside this symbol: 2. Native target expressions and addends are retained.

### `ov032:020c0080` → `gGroupSceneGlobals`

Previous label: `data_ov032_020c0080`. Existing ELF symbol size: **8 bytes**. Source: `eu/src/overlays/ov032/data/bss/Bss_ov032_020c0080.c`.

8-byte BSS object: routed context pointer at +0 and scene-work pointer at +4.

InitSceneOverlayState publishes scene work at +4. AdvanceToRoutedSlot explicitly reads separate context/scene pointer fields and routes through the former.

Limits: The two pointers are distinct owners/views; do not merge their allocations or assume a uniform scene structure.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov032/calls/AcknowledgeGroupTransition.c` → `src/ov032/object_group/AcknowledgeGroupTransition_020ba940.c`, symbol reference line(s) 3, 4.
- `eu/src/overlays/ov032/calls/AdvanceToRoutedSlot.c`, symbol reference line(s) 41, 52, 56, 57, 58, 60, 62, 63, 64, 68, 71, 75.
- `eu/src/overlays/ov032/calls/ApplySlotStyleToSession.c` → `src/ov032/unclassified_helpers/ApplySlotStyleToSession_020ba570.c`, symbol reference line(s) 32, 41, 43, 45, 47, 48, 52, 53, 55, 57, 60.
- `eu/src/overlays/ov032/calls/ClearGroupTransitionFlags.c` → `src/ov032/object_group/ClearGroupTransitionFlags_020bb330.c`, symbol reference line(s) 3, 4.
- `eu/src/overlays/ov032/calls/CommitGroupActionState.c` → `src/ov032/object_group/CommitGroupActionState_020bb1c8.c`, symbol reference line(s) 3, 4.
- `eu/src/overlays/ov032/calls/CompleteGroupTransition.c` → `src/ov032/object_group/CompleteGroupTransition_020baad0.c`, symbol reference line(s) 3, 4.
- `eu/src/overlays/ov032/calls/DestroySceneState.c` → `src/ov032/unclassified_helpers/DestroySceneState_020ba804.c`, symbol reference line(s) 24, 37, 38, 39, 40, 41, 44, 46, 50, 56.
- `eu/src/overlays/ov032/calls/EnterGroupActionState.c` → `src/ov032/object_group/EnterGroupActionState_020bb1f8.c`, symbol reference line(s) 3, 4.
- `eu/src/overlays/ov032/calls/FinishGroupActionState.c` → `src/ov032/object_group/FinishGroupActionState_020bb25c.c`, symbol reference line(s) 3, 4.
- `eu/src/overlays/ov032/calls/FinishGroupTransition.c` → `src/ov032/object_group/FinishGroupTransition_020bb150.c`, symbol reference line(s) 1, 2.
- `eu/src/overlays/ov032/calls/FinishMovieMenuLoad.c` → `src/ov032/shared_engine/FinishMovieMenuLoad_020ba984.c`, symbol reference line(s) 13, 47, 51.
- `eu/src/overlays/ov032/calls/GetContextIndexedByte.c` → `src/ov032/object_group/GetContextIndexedByte_020bb81c.c`, symbol reference line(s) 9, 13.
- `eu/src/overlays/ov032/calls/GetGroupIndexedValue.c` → `src/ov032/object_group/GetGroupIndexedValue_020bb86c.c`, symbol reference line(s) 3, 4.
- `eu/src/overlays/ov032/calls/GroupSceneState_SaveActorPosesAndExit.c`, symbol reference line(s) 5, 31, 53, 60.
- `eu/src/overlays/ov032/calls/InitSceneOverlayState.c` → `src/ov032/unclassified_helpers/InitSceneOverlayState_020ba3e0.c`, symbol reference line(s) 58, 92, 93, 94, 95, 96, 97, 112, 114, 115, 116, 117, 119, 121, 122, 124, 125, 126, 127, 132, 135, 139, 140, 141, 142, 143.
- `eu/src/overlays/ov032/calls/InitializeGroupAction.c` → `src/ov032/object_group/InitializeGroupAction_020bb12c.c`, symbol reference line(s) 3, 4.
- `eu/src/overlays/ov032/calls/IsContextFlag10Clear.c` → `src/ov032/object_group/IsContextFlag10Clear_020bb554.c`, symbol reference line(s) 3, 8.
- `eu/src/overlays/ov032/calls/IsContextFlag20Set.c` → `src/ov032/object_group/IsContextFlag20Set_020bb56c.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov032/calls/IsContextSlotEnabled.c` → `src/ov032/object_group/IsContextSlotEnabled_020bb840.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov032/calls/IsOv032SceneStartupComplete.c`, symbol reference line(s) 5, 6.
- `eu/src/overlays/ov032/calls/LoadShadowAndFlagScene.c` → `src/ov032/unclassified_helpers/LoadShadowAndFlagScene_020ba90c.c`, symbol reference line(s) 14, 19, 20, 23.
- `eu/src/overlays/ov032/calls/PulseMenuHighlightColor.c`, symbol reference line(s) 9, 25.
- `eu/src/overlays/ov032/calls/ResumeSceneAndAdvance.c` → `src/ov032/unclassified_helpers/ResumeSceneAndAdvance_020baa08.c`, symbol reference line(s) 19, 37, 41, 51, 60.
- `eu/src/overlays/ov032/calls/RollContextReward.c` → `src/ov032/object_group/RollContextReward_020bb884.c`, symbol reference line(s) 10, 24, 25, 27, 30, 31.
- `eu/src/overlays/ov032/calls/RunSceneStateMachine_020ba7b0.c` → `src/ov032/unclassified_helpers/RunSceneStateMachine_020ba790.c`, symbol reference line(s) 22, 29, 33, 34, 36, 38, 39, 42.
- `eu/src/overlays/ov032/calls/SetContextModeAndFlag.c` → `src/ov032/object_group/SetContextModeAndFlag_020bb494.c`, symbol reference line(s) 9, 13, 14.
- `eu/src/overlays/ov032/calls/SetSlotDisplayStyle.c` → `src/ov032/unclassified_helpers/SetSlotDisplayStyle_020ba8a0.c`, symbol reference line(s) 20, 33, 43.
- `eu/src/overlays/ov032/calls/StartMoviePlayback.c` → `src/ov032/shared_engine/StartMoviePlayback_020bb4e0.c`, symbol reference line(s) 20, 31, 32, 33, 34, 35, 36, 37.
- `eu/src/overlays/ov032/calls/TryOpenGroupAction.c` → `src/ov032/object_group/TryOpenGroupAction_020bb220.c`, symbol reference line(s) 3, 4.
- `eu/src/overlays/ov032/calls/UpdateChallengeProgress.c` → `src/ov032/unclassified_helpers/UpdateChallengeProgress_020bb57c.c`, symbol reference line(s) 43, 131, 164, 167.
- `eu/src/overlays/ov032/calls/UpdateChallengeScene.c` → `src/ov032/state_machine/UpdateChallengeScene_020bab04.c`, symbol reference line(s) 46, 72, 73.
- `eu/src/overlays/ov032/calls/UpdateStageLinkPanels.c` → `src/ov032/panel_state/UpdateStageLinkPanels_020ba604.c`, symbol reference line(s) 23, 40, 42, 45, 50, 52, 57, 58, 61, 63, 65, 70, 75, 79, 80, 83, 86, 91, 93, 96, 97.
- `eu/src/overlays/ov032/calls/GroupSceneOnLeaveClearFlag2.c`, symbol reference line(s) 3, 4.
- `eu/src/overlays/ov032/calls/func_ov032_020bb828.c`, symbol reference line(s) 3, 6, 7.
- `eu/src/overlays/ov032/data/bss/Bss_ov032_020c0080.c`, symbol reference line(s) 4.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov032:020c0088` → `gGroupMenuGaugeGlobalsStorage`

Previous label: `data_ov032_020c0088`. Existing ELF symbol size: **24 bytes**. Source: `eu/src/overlays/ov032/data/bss/Bss_ov032_020c0080.c`.

24-byte BSS symbol: packed highlight color u16 at +0, gauge-work pointer at +4, remaining bytes opaque.

InitGroupMenuGauge stores current task work at +4; ReleaseGroupResourceBuffers frees four work-owned buffers and clears +4. PulseMenuHighlightColor writes the low u16 at +0 and queues a 2-byte VRAM transfer from its address.

Limits: The word at +0 is not another work pointer. Only its low 16 bits are proven as a color. Preserve the opaque 16-byte tail and upper halfword of the first word.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov032/calls/InitGroupMenuGauge.c` → `src/ov032/object_group/InitGroupMenuGauge_020bba70.c`, symbol reference line(s) 24, 50.
- `eu/src/overlays/ov032/calls/PulseMenuHighlightColor.c`, symbol reference line(s) 8, 23.
- `eu/src/overlays/ov032/calls/ReleaseGroupResourceBuffers.c` → `src/ov032/object_group/ReleaseGroupResourceBuffers_020bbb24.c`, symbol reference line(s) 1, 2.
- `eu/src/overlays/ov032/calls/SetGroupMenuPercent.c` → `src/ov032/object_group/SetGroupMenuPercent_020bbb7c.c`, symbol reference line(s) 3, 8.
- `eu/src/overlays/ov032/calls/SetGroupMenuProgress.c` → `src/ov032/object_group/SetGroupMenuProgress_020bb9b8.c`, symbol reference line(s) 3, 4.
- `eu/src/overlays/ov032/calls/UpdateGroupMenuCounter.c` → `src/ov032/object_group/UpdateGroupMenuCounter_020bbb4c.c`, symbol reference line(s) 3, 4.
- `eu/src/overlays/ov032/calls/UploadGroupMenuTiles.c` → `src/ov032/object_group/UploadGroupMenuTiles_020bbba8.c`, symbol reference line(s) 15, 21.
- `eu/src/overlays/ov032/data/bss/Bss_ov032_020c0080.c`, symbol reference line(s) 3.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov033:020baaa0` → `gResumeModeTaskHandle`

Previous label: `data_ov033_020baaa0`. Existing ELF symbol size: **4 bytes**. Source: `eu/src/ov033/data/Data_ov033_020baaa0.c`.

4-byte task handle initialized to 0xffffffff.

Resume-mode task creation and teardown access this handle separately from the work pointer.

Limits: Preserve -1 bit pattern and distinguish the task node from the 0x18-byte task work.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov033/data/Data_ov033_020baaa0.c`, symbol reference line(s) 5.
- `eu/src/overlays/ov033/calls/CreateResumeModeTask.c` → `src/ov033/reviewed_helpers/func_ov033_020ba8d4.c`, symbol reference line(s) 3, 6.
- `eu/src/overlays/ov033/calls/DestroyResumeModeTask.c`, symbol reference line(s) 3, 8, 9.
- `eu/src/overlays/ov033/calls/HasResumeModeTaskExitSignal.c`, symbol reference line(s) 3, 8.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov033:020baab4` → `gResumeModeTaskClassStorage`

Previous label: `data_ov033_020baab4`. Existing ELF symbol size: **44 bytes**. Source: `eu/src/ov033/data/Data_ov033_020baab4.c`.

Native ClassDescriptor prefix: classId/subId packed word 0x0002000e; constructor at +4 (InitResumeModeContext); destructor at +8 (ShutdownResumeModeContext); workSize +0xc = 0x18; heapRef +0x10 = NULL. Existing symbol is 44 bytes: descriptor prefix 20 bytes plus six zero words (24 opaque bytes). Preserve that tail.

The initializer supplies this five-word prefix to CreateTaskObject; Obj_Construct copies classId/subId/workSize, allocates and clears task work, invokes the constructor with the task as current, and stores its returned update callback. The descriptor +8 callback is used during destruction.

Limits: TaskObject class IDs are not priorities or flags. Constructor return is the update callback; +8 is not the update callback. Preserve raw declarations and relocation targets. Existing symbol is 44 bytes: descriptor prefix 20 bytes plus six zero words (24 opaque bytes). Preserve that tail.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov033/data/Data_ov033_020baab4.c`, symbol reference line(s) 8.
- `eu/src/overlays/ov033/calls/CreateResumeModeTask.c` → `src/ov033/reviewed_helpers/func_ov033_020ba8d4.c`, symbol reference line(s) 2, 6.

Relocations inside this symbol: 2. Native target expressions and addends are retained.

### `ov033:020baae0` → `gResumeModeWorkStorage`

Previous label: `data_ov033_020baae0`. Existing ELF symbol size: **28 bytes**. Source: `eu/src/overlays/ov033/data/bss/Bss_ov033_020baae0.c`.

28-byte BSS symbol; first word points to the 0x18-byte resume-mode task work; trailing 24 bytes opaque.

InitResumeModeContext publishes task work; BeginResumeMode/CompleteResumeMode and ShutdownResumeModeContext use it.

Limits: The global BSS size is not the pointee size. Do not absorb the adjacent baafc symbol or give that unproven neighbor a role.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov033/calls/BeginResumeMode.c`, symbol reference line(s) 14, 25, 46.
- `eu/src/overlays/ov033/calls/ClearResumeModePending.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov033/calls/ClearResumeModeReadyFlag.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov033/calls/CompleteResumeModeWithResult.c`, symbol reference line(s) 10, 14, 15.
- `eu/src/overlays/ov033/calls/FinishResumeMenuAndRestoreField.c`, symbol reference line(s) 4, 21, 22, 25, 31.
- `eu/src/overlays/ov033/calls/GetResumeModeResult.c`, symbol reference line(s) 1, 4.
- `eu/src/overlays/ov033/calls/InitResumeModeContext.c`, symbol reference line(s) 23, 42, 49, 54, 59, 60, 61, 62, 63, 64, 66.
- `eu/src/overlays/ov033/calls/IsResumeModeReady.c`, symbol reference line(s) 8, 12, 15.
- `eu/src/overlays/ov033/calls/RunResumeModeStateMachine.c`, symbol reference line(s) 12, 20, 21, 23, 25.
- `eu/src/overlays/ov033/calls/ShutdownResumeModeContext.c`, symbol reference line(s) 3, 12.
- `eu/src/overlays/ov033/calls/UpdateResumeMenuUntilResult.c`, symbol reference line(s) 8, 13.
- `eu/src/overlays/ov033/data/bss/Bss_ov033_020baae0.c`, symbol reference line(s) 3.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov035:020bc4c8` → `gAreaSceneModelNameFormat`

Previous label: `data_ov035_020bc4c8`. Existing ELF symbol size: **8 bytes**. Source: `eu/src/overlays/ov035/data/sOv035ModelNameFormat.c`.

8-byte initialized char object containing the NUL-terminated format %s%02d and padding.

LoadFadeModel passes this format, sOv035AreaName and an index to OS_SPrintf when constructing a model name.

Limits: This DATA belongs to ov035. A function at the same RAM address in ov036 is a different identity; do not bind this format as a callback.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov035/calls/LoadFadeModel.c` → `src/ov035/unclassified_helpers/LoadFadeModel_020bb50c.c`, symbol reference line(s) 43, 89.
- `eu/src/overlays/ov035/data/sOv035ModelNameFormat.c`, symbol reference line(s) 1.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov035:020bc4e0` → `gAreaSceneActiveColorUploadData`

Previous label: `data_ov035_020bc4e0`. Existing ELF symbol size: **8 bytes**. Source: `eu/src/overlays/ov035/data/sOv035ActiveColors.c`.

8 initialized bytes, currently represented as two u32 words (0x04b7006f, 0x0cfe04da).

QueueColorUpload selects these eight bytes when its argument is nonzero; otherwise selects the inactive-color object, then queues transfer type 0x0f to destination 0x186 with byte count 8.

Limits: The proposed name describes the branch/upload contract; no new portable palette type, channel order or memory ownership is asserted. US bare numeric spelling is not EU owner evidence.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov035/calls/QueueColorUpload.c` → `src/ov035/unclassified_helpers/QueueColorUpload_020bb7d8.c`, symbol reference line(s) 4, 8.
- `eu/src/overlays/ov035/data/sOv035ActiveColors.c`, symbol reference line(s) 3.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov035:020bc504` → `gAreaSceneMaterialFadeWork`

Previous label: `data_ov035_020bc504`. Existing ELF symbol size: **4 bytes**. Source: `eu/src/overlays/ov035/data/bss/Bss_ov035_020bc504.c`.

4-byte pointer to allocated material-fade scene work.

CreateMaterialFadeWork allocates/clears and publishes the owner; LoadFadeModel, material-fade entry application, drawing and model release borrow it; FreeAreaMaterialFadeWork frees it.

Limits: FreeAreaMaterialFadeWork does not clear this global. Do not promise a NULL-after-free contract.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov035/calls/ApplyAreaMaterialFadeEntry.c`, symbol reference line(s) 45, 57, 59, 62.
- `eu/src/overlays/ov035/calls/CreateMaterialFadeWork.c` → `src/ov035/unclassified_helpers/CreateMaterialFadeWork_020bb4a4.c`, symbol reference line(s) 14, 23, 24, 25.
- `eu/src/overlays/ov035/calls/DrawMovieSceneIfVisible.c` → `src/ov035/unclassified_helpers/DrawMovieSceneIfVisible_020bb73c.c`, symbol reference line(s) 8, 13, 14.
- `eu/src/overlays/ov035/calls/FreeAreaMaterialFadeWork.c`, symbol reference line(s) 3, 9, 10.
- `eu/src/overlays/ov035/calls/LoadFadeModel.c` → `src/ov035/unclassified_helpers/LoadFadeModel_020bb50c.c`, symbol reference line(s) 42, 58.
- `eu/src/overlays/ov035/calls/ReleaseAreaFadeModelIfLoaded.c`, symbol reference line(s) 3, 9, 10, 11.
- `eu/src/overlays/ov035/calls/SetMovieModelAlpha.c` → `src/ov035/unclassified_helpers/SetMovieModelAlpha_020bb758.c`, symbol reference line(s) 10, 16, 20.
- `eu/src/overlays/ov035/calls/SetMovieSlotFlags.c` → `src/ov035/unclassified_helpers/SetMovieSlotFlags_020bb40c.c`, symbol reference line(s) 16, 20.
- `eu/src/overlays/ov035/calls/UpdateMaterialFades.c` → `src/ov035/unclassified_helpers/UpdateMaterialFades_020bb670.c`, symbol reference line(s) 18, 27.
- `eu/src/overlays/ov035/data/bss/Bss_ov035_020bc504.c`, symbol reference line(s) 4.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov035:020bc508` → `gAreaSceneGaugeGlobalsStorage`

Previous label: `data_ov035_020bc508`. Existing ELF symbol size: **24 bytes**. Source: `eu/src/overlays/ov035/data/bss/Bss_ov035_020bc504.c`.

24-byte BSS symbol: first word opaque, gauge/level-queue task-work pointer at +4, trailing 16 bytes opaque.

InitBarGauge stores current task work at +4; QueueGaugeLevelEntry consumes its queue at +0x3c and clamps to twelve entries; ReleaseAreaGaugeBuffers frees owned buffers and clears +4.

Limits: Do not label the first word as a sound pointer, and do not shrink this symbol to the eight-byte partial view used by native consumers.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov035/calls/ArmAreaSequence1AtGaugeMax.c`, symbol reference line(s) 4, 14.
- `eu/src/overlays/ov035/calls/InitBarGauge.c` → `src/ov035/unclassified_helpers/InitBarGauge_020bc00c.c`, symbol reference line(s) 26, 50.
- `eu/src/overlays/ov035/calls/QueueGaugeLevelEntry.c` → `src/ov035/shared_engine/QueueGaugeLevelEntry_020bc2f0.c`, symbol reference line(s) 22, 28.
- `eu/src/overlays/ov035/calls/ReleaseAreaGaugeBuffers.c`, symbol reference line(s) 1, 2.
- `eu/src/overlays/ov035/calls/SetChannelRatioLevels.c` → `src/ov035/unclassified_helpers/SetChannelRatioLevels_020bc1f0.c`, symbol reference line(s) 20, 24.
- `eu/src/overlays/ov035/calls/SetGaugeLevel.c` → `src/ov035/unclassified_helpers/SetGaugeLevel_020bbef0.c`, symbol reference line(s) 15, 24.
- `eu/src/overlays/ov035/calls/SetMovieMenuRow.c` → `src/ov035/unclassified_helpers/SetMovieMenuRow_020bc1d4.c`, symbol reference line(s) 15, 19, 20.
- `eu/src/overlays/ov035/calls/UpdateChannelLevel.c` → `src/ov035/unclassified_helpers/UpdateChannelLevel_020bc250.c`, symbol reference line(s) 20, 29.
- `eu/src/overlays/ov035/calls/UpdateGaugeFrame.c` → `src/ov035/unclassified_helpers/UpdateGaugeFrame_020bc0ec.c`, symbol reference line(s) 33, 48.
- `eu/src/overlays/ov035/data/bss/Bss_ov035_020bc504.c`, symbol reference line(s) 3.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov038:020bd160` → `gResultsPageOuterTaskWork`

Previous label: `data_ov038_020bd160`. Existing ELF symbol size: **4 bytes**. Source: `eu/src/overlays/ov038/data/bss/Bss_ov038_020bd160.c`.

4-byte pointer to the outer ov038 task work.

Outer task initialization publishes it; readiness, initial state and shutdown use this owner separately from the allocated results page context.

Limits: A legacy SoundCtx label is not evidence that this pointer owns the audio system. Keep it distinct from bd164.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov038/Ov038SoundContext.h`, symbol reference line(s) 12, 13.
- `eu/src/overlays/ov038/calls/ClearSoundContextReadyFlag.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov038/calls/DisableOv038Sound.c` → `src/ov038/reviewed_helpers/DisableOv038Sound_020ba5b4.c`, symbol reference line(s) 8, 20.
- `eu/src/overlays/ov038/calls/EnableOv038SoundCtx.c` → `src/ov038/reviewed_helpers/EnableOv038SoundCtx_020ba52c.c`, symbol reference line(s) 8, 15, 16.
- `eu/src/overlays/ov038/calls/IsOv038SoundCtxFlag0Clear.c` → `src/ov038/reviewed_helpers/IsOv038SoundCtxFlag0Clear_020ba620.c`, symbol reference line(s) 8, 12, 15.
- `eu/src/overlays/ov038/calls/MarkSoundCtxRepeatIfReady.c` → `src/ov038/reviewed_helpers/MarkSoundCtxRepeatIfReady_020ba58c.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov038/calls/RunOv038SoundCtxStates.c` → `src/ov038/reviewed_helpers/RunOv038SoundCtxStates_020ba468.c`, symbol reference line(s) 12, 20, 21, 23, 25.
- `eu/src/overlays/ov038/calls/SetSoundCtxMode.c` → `src/ov038/reviewed_helpers/SetSoundCtxMode_020ba670.c`, symbol reference line(s) 9, 13, 14.
- `eu/src/overlays/ov038/calls/ShutdownOv038SoundCtx.c`, symbol reference line(s) 4, 12.
- `eu/src/overlays/ov038/calls/StartOv038SoundCtx.c`, symbol reference line(s) 21, 31, 32, 33, 34, 35, 36, 37.
- `eu/src/overlays/ov038/calls/TryMarkSoundCtxActive.c` → `src/ov038/reviewed_helpers/TryMarkSoundCtxActive_020ba4f8.c`, symbol reference line(s) 8, 17.
- `eu/src/overlays/ov038/data/bss/Bss_ov038_020bd160.c`, symbol reference line(s) 4.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov038:020bd164` → `gResultsPageContextStorage`

Previous label: `data_ov038_020bd164`. Existing ELF symbol size: **28 bytes**. Source: `eu/src/overlays/ov038/data/bss/Bss_ov038_020bd160.c`.

28-byte BSS symbol; first word points to allocated results/page context, trailing 24 bytes opaque.

BuildCompletionStats allocates, publishes and clears the context before filling statistics. Results graphics, sprite managers and digit drawers use it. ReleaseOv038Context tears down its resources, frees it and clears the first word.

Limits: The 28-byte global storage is not the allocated page context size. Do not expose the opaque tail as six additional context pointers.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov038/calls/AdvanceOv038ExitTimer.c` → `src/ov038/unclassified_helpers/AdvanceOv038ExitTimer_020babb4.c`, symbol reference line(s) 3, 14.
- `eu/src/overlays/ov038/calls/BuildCompletionStats.c`, symbol reference line(s) 35, 212.
- `eu/src/overlays/ov038/calls/CreateOv038Sprite.c` → `src/ov038/unclassified_helpers/CreateOv038Sprite_020bb13c.c`, symbol reference line(s) 32, 44.
- `eu/src/overlays/ov038/calls/DrawOv038PercentDigits.c` → `src/ov038/unclassified_helpers/DrawOv038PercentDigits_020bb35c.c`, symbol reference line(s) 12, 19.
- `eu/src/overlays/ov038/calls/DrawResultsTimeDigits.c`, symbol reference line(s) 11, 20.
- `eu/src/overlays/ov038/calls/DrawScoreDigits.c` → `src/ov038/display_setup/DrawScoreDigits_020bb41c.c`, symbol reference line(s) 12, 19.
- `eu/src/overlays/ov038/calls/FreeOv038ContextBuffers.c` → `src/ov038/unclassified_helpers/FreeOv038ContextBuffers_020bae2c.c`, symbol reference line(s) 3, 11.
- `eu/src/overlays/ov038/calls/FreeOv038ContextSlots.c` → `src/ov038/unclassified_helpers/FreeOv038ContextSlots_020baf7c.c`, symbol reference line(s) 3, 11.
- `eu/src/overlays/ov038/calls/GetResultsPageState.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov038/calls/HandleOv038PageInput.c` → `src/ov038/unclassified_helpers/HandleOv038PageInput_020baa98.c`, symbol reference line(s) 8, 16.
- `eu/src/overlays/ov038/calls/UpdateResultsPageSpriteManagers.c` → `src/ov038/unclassified_helpers/InitOv038SlotPools_020bb104.c`, symbol reference line(s) 3, 12.
- `eu/src/overlays/ov038/calls/InitOv038SpriteManagers.c` → `src/ov038/unclassified_helpers/InitOv038SpriteManagers_020bafb4.c`, symbol reference line(s) 27, 36.
- `eu/src/overlays/ov038/calls/LoadOv038Graphics.c` → `src/ov038/unclassified_helpers/LoadOv038Graphics_020bae5c.c`, symbol reference line(s) 25, 34.
- `eu/src/overlays/ov038/calls/LoadOv038MsgContainers.c` → `src/ov038/unclassified_helpers/LoadOv038MsgContainers_020bade0.c`, symbol reference line(s) 8, 14.
- `eu/src/overlays/ov038/calls/ReleaseOv038Context.c` → `src/ov038/unclassified_helpers/ReleaseOv038Context_020bbcb8.c`, symbol reference line(s) 3, 13, 18.
- `eu/src/overlays/ov038/calls/ReleaseOv038SlotPools.c` → `src/ov038/unclassified_helpers/ReleaseOv038SlotPools_020bb0c0.c`, symbol reference line(s) 3, 13.
- `eu/src/overlays/ov038/calls/ResetOv038ExitState.c` → `src/ov038/unclassified_helpers/ResetOv038ExitState_020bb638.c`, symbol reference line(s) 3, 9.
- `eu/src/overlays/ov038/calls/SetOv038PoolRecordFlags.c` → `src/ov038/unclassified_helpers/SetOv038PoolRecordFlags_020bb32c.c`, symbol reference line(s) 12, 17.
- `eu/src/overlays/ov038/calls/SetOv038SpriteOffset.c` → `src/ov038/unclassified_helpers/SetOv038SpriteOffset_020bb2ac.c`, symbol reference line(s) 27, 32.
- `eu/src/overlays/ov038/calls/SetOv038SpritePosition.c` → `src/ov038/unclassified_helpers/SetOv038SpritePosition_020bb230.c`, symbol reference line(s) 27, 32.
- `eu/src/overlays/ov038/calls/ShowOv038ResultsFadeIn.c` → `src/ov038/unclassified_helpers/ShowOv038ResultsFadeIn_020ba768.c`, symbol reference line(s) 23, 35.
- `eu/src/overlays/ov038/data/bss/Bss_ov038_020bd160.c`, symbol reference line(s) 3.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov039:020bea20` → `gMenuOverlayWork`

Previous label: `data_ov039_020bea20`. Existing ELF symbol size: **4 bytes**. Source: `eu/src/overlays/ov039/data/bss/Bss_ov039_020bea20.c`.

4-byte pointer to the main menu-overlay work allocation.

InitOverlayState allocates and clears Ov039State then publishes it; menu widgets, input, state and overlay dispatchers access the same allocation.

Limits: The same BSS source contains the already-named gGridLabelBuffer; preserve it. Primary/secondary context allocations are fields inside the pointee, not this global.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov039/Ov039MenuState.h`, symbol reference line(s) 50, 51.
- `eu/src/overlays/ov039/RuntimeState.h`, symbol reference line(s) 15, 18.
- `eu/src/overlays/ov039/calls/AllocateListEntry.c` → `src/ov039/reviewed_helpers/AllocateListEntry_020bc6b0.c`, symbol reference line(s) 9, 25.
- `eu/src/overlays/ov039/calls/BuildSlotImageParams.c` → `src/ov039/widget_layers/BuildSlotImageParams_020bc220.c`, symbol reference line(s) 1, 5.
- `eu/src/overlays/ov039/calls/CallStateWidget.c` → `src/ov039/widget_layers/CallStateWidget_020bc14c.c`, symbol reference line(s) 1, 6.
- `eu/src/overlays/ov039/calls/CleanupHandlersAndSetPhase5.c` → `src/ov039/event_state/CleanupHandlersAndSetPhase5_020bb680.c`, symbol reference line(s) 1, 11.
- `eu/src/overlays/ov039/calls/ClearScreenLayerDirty.c` → `src/ov039/widget_layers/ClearScreenLayerDirty_020bc128.c`, symbol reference line(s) 8, 13.
- `eu/src/overlays/ov039/calls/ClearWidgetOnScreenLayer.c` → `src/ov039/widget_layers/ClearWidgetOnScreenLayer_020bb730.c`, symbol reference line(s) 8, 13.
- `eu/src/overlays/ov039/calls/DestroyAllListEntries.c` → `src/ov039/reviewed_helpers/DestroyAllListEntries_020bc788.c`, symbol reference line(s) 1, 7, 14.
- `eu/src/overlays/ov039/calls/DrawWidgetOnScreenLayer.c` → `src/ov039/widget_layers/DrawWidgetOnScreenLayer_020bb70c.c`, symbol reference line(s) 8, 13.
- `eu/src/overlays/ov039/calls/FormatStateText.c` → `src/ov039/widget_layers/FormatStateText_020bccac.c`, symbol reference line(s) 4, 12.
- `eu/src/overlays/ov039/calls/GetEventStateWordCa48.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov039/calls/GetFieldCa4a.c` → `src/ov039/event_state/GetFieldCa4a_020bc9e0.c`, symbol reference line(s) 1, 6.
- `eu/src/overlays/ov039/calls/GetFieldCad0.c` → `src/ov039/event_state/GetFieldCad0_020bcb00.c`, symbol reference line(s) 1, 5.
- `eu/src/overlays/ov039/calls/GetMenuPhase.c` → `src/ov039/event_state/GetStateC9C4.c`, symbol reference line(s) 5, 6.
- `eu/src/overlays/ov039/calls/InitOverlayState.c`, symbol reference line(s) 62, 109, 159, 160, 161, 162.
- `eu/src/overlays/ov039/calls/StartMenuBrightnessTweens.c` → `src/ov039/reviewed_helpers/InitStreamBufferPair_020bacbc.c`, symbol reference line(s) 3, 9.
- `eu/src/overlays/ov039/calls/InitThenDispatchTwoHandlers.c` → `src/ov039/overlay_event_dispatch/InitThenDispatchTwoHandlers_020bb308.c`, symbol reference line(s) 1, 9, 10.
- `eu/src/overlays/ov039/calls/IsStatePhase3.c` → `src/ov039/event_state/IsStatePhase3_020bcaa0.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov039/calls/IsStatePhase4.c` → `src/ov039/event_state/IsStatePhase4_020bca30.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov039/calls/IsStatePhaseActive.c` → `src/ov039/event_state/IsStatePhaseActive_020bca60.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov039/calls/IsStatePhaseIdle.c` → `src/ov039/event_state/IsStatePhaseIdle_020bcad0.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov039/calls/LoadBgLayerSet3.c` → `src/ov039/widget_layers/LoadBgLayerSet3_020bab8c.c`, symbol reference line(s) 15, 30, 31.
- `eu/src/overlays/ov039/calls/LoadBgLayerSet4.c` → `src/ov039/widget_layers/LoadBgLayerSet4_020bac24.c`, symbol reference line(s) 15, 30, 31.
- `eu/src/overlays/ov039/calls/LoadMainBgAndTriggerTags.c` → `src/ov039/widget_layers/LoadMainBgAndTriggerTags_020bc318.c`, symbol reference line(s) 9, 22.
- `eu/src/overlays/ov039/calls/LoadSelectedHandlerAndStart.c` → `src/ov039/event_state/LoadSelectedHandlerAndStart_020bb40c.c`, symbol reference line(s) 13, 25.
- `eu/src/overlays/ov039/calls/LoadSlotSubBgImage.c` → `src/ov039/widget_layers/LoadSlotSubBgImage_020bc55c.c`, symbol reference line(s) 35, 51.
- `eu/src/overlays/ov039/calls/LoadSubBgAndTriggerTags.c` → `src/ov039/widget_layers/LoadSubBgAndTriggerTags_020bc488.c`, symbol reference line(s) 9, 22.
- `eu/src/overlays/ov039/calls/PollHandlerInput.c` → `src/ov039/input/PollHandlerInput_020baf1c.c`, symbol reference line(s) 19, 38.
- `eu/src/overlays/ov039/calls/PopStackEntry.c` → `src/ov039/event_state/PopStackEntry_020bc8a0.c`, symbol reference line(s) 1, 5.
- `eu/src/overlays/ov039/calls/PushStackEntry.c` → `src/ov039/event_state/PushStackEntry_020bc874.c`, symbol reference line(s) 1, 5.
- `eu/src/overlays/ov039/calls/RemoveListEntry.c` → `src/ov039/reviewed_helpers/RemoveListEntry_020bc70c.c`, symbol reference line(s) 1, 8, 12, 18.
- `eu/src/overlays/ov039/calls/ReplaceStackTop.c` → `src/ov039/event_state/ReplaceStackTop_020bc8d0.c`, symbol reference line(s) 1, 5.
- `eu/src/overlays/ov039/calls/SetEventStateFlagCa34.c`, symbol reference line(s) 8, 12.
- `eu/src/overlays/ov039/calls/SetMenuButtonsEnabled.c` → `src/ov039/event_state/SetMenuButtonsEnabled_020bae84.c`, symbol reference line(s) 3, 11.
- `eu/src/overlays/ov039/calls/SetPrimaryElementEnabled.c` → `src/ov039/event_state/SetPrimaryElementEnabled_020bc054.c`, symbol reference line(s) 12, 17.
- `eu/src/overlays/ov039/calls/SetScreenBrightness.c` → `src/ov039/event_state/SetScreenBrightness_020bc648.c`, symbol reference line(s) 11, 16.
- `eu/src/overlays/ov039/calls/SetScreenLayerDirty.c` → `src/ov039/widget_layers/SetScreenLayerDirty_020bc104.c`, symbol reference line(s) 8, 13.
- `eu/src/overlays/ov039/calls/SetSecondaryElementEnabled.c` → `src/ov039/event_state/SetSecondaryElementEnabled_020bc084.c`, symbol reference line(s) 12, 19.
- `eu/src/overlays/ov039/calls/SetSelectionIfChanged_020bc94c.c` → `src/ov039/event_state/SetSelectionIfChanged_020bc92c.c`, symbol reference line(s) 1, 7.
- `eu/src/overlays/ov039/calls/SetStateFlagBits.c` → `src/ov039/leaf_research/SetStateFlagBits_020bc688.c`, symbol reference line(s) 3, 7.
- `eu/src/overlays/ov039/calls/SelectMenuFontForWidth.c` → `src/ov039/widget_layers/SetTextColorIfFits_020bcd04.c`, symbol reference line(s) 3, 9.
- `eu/src/overlays/ov039/calls/ShutdownHandlersAndExit.c`, symbol reference line(s) 19, 36.
- `eu/src/overlays/ov039/calls/ShutdownOverlay.c`, symbol reference line(s) 28, 53, 71, 72, 73, 74.
- `eu/src/overlays/ov039/calls/StartSubScene.c` → `src/ov039/event_state/StartSubScene_020bbf78.c`, symbol reference line(s) 3, 12.
- `eu/src/overlays/ov039/calls/UpdateBrightnessAndTasks.c` → `src/ov039/event_state/UpdateBrightnessAndTasks_020bad34.c`, symbol reference line(s) 31, 42.
- `eu/src/overlays/ov039/calls/UpdateExitSequence.c` → `src/ov039/event_state/UpdateExitSequence_020bb33c.c`, symbol reference line(s) 9, 20.
- `eu/src/overlays/ov039/calls/UpdateOverlayFrame.c` → `src/ov039/overlay_lifecycle/UpdateOverlayFrame_020bbb6c.c`, symbol reference line(s) 58, 74.
- `eu/src/overlays/ov039/calls/UpdateScreenWidgetLayer.c` → `src/ov039/widget_layers/UpdateScreenWidgetLayer_020bc1e4.c`, symbol reference line(s) 8, 13.
- `eu/src/overlays/ov039/calls/UpdateSubOverlayHandlers.c`, symbol reference line(s) 20, 40.
- `eu/src/overlays/ov039/calls/WaitMenuFadeInThenEnableInput.c`, symbol reference line(s) 3, 12, 13.
- `eu/src/overlays/ov039/calls/WaitSubMenuFadeInThenEnableButtons.c`, symbol reference line(s) 3, 12, 13.
- `eu/src/overlays/ov039/calls/WaitMenuFadeOutThenEnterShutdown.c`, symbol reference line(s) 3, 11, 12.
- `eu/src/overlays/ov039/calls/SetMenuInputEnabled.c`, symbol reference line(s) 3, 8.
- `eu/src/overlays/ov039/calls/GetMenuWork.c`, symbol reference line(s) 1, 4.
- `eu/src/overlays/ov039/data/bss/Bss_ov039_020bea20.c`, symbol reference line(s) 4.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov039:020beaa4` → `gMenuSubOverlayIndexStorage`

Previous label: `data_ov039_020beaa4`. Existing ELF symbol size: **28 bytes**. Source: `eu/src/overlays/ov039/data/bss/Bss_ov039_020beaa4.c`.

28-byte BSS symbol: signed primary index at +0, signed secondary index at +4; trailing 20 bytes opaque.

ResetMenuSubOverlayIndices sets both indexes to -1. LoadPrimarySubOverlay/LoadSecondarySubOverlay store their respective registry indexes; dispatch and unload read those indexes.

Limits: These are registry indexes, not overlay IDs. Do not label the entire seven-word symbol as seven indexes or merge it with the separate registry DATA covered by another plan.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov039/calls/CloseSecondarySubOverlay.c` → `src/ov039/overlay_handling/CloseSecondarySubOverlay_020bd00c.c`, symbol reference line(s) 18, 25, 28, 29.
- `eu/src/overlays/ov039/calls/DispatchActiveOverlayCallback.c` → `src/ov039/overlay_handling/DispatchActiveOverlayCallback_020bceb0.c`, symbol reference line(s) 8, 14.
- `eu/src/overlays/ov039/calls/DispatchOverlayEventPairA.c` → `src/ov039/overlay_event_dispatch/DispatchOverlayEventPairA_020bd0fc.c`, symbol reference line(s) 2, 9, 14.
- `eu/src/overlays/ov039/calls/DispatchOverlayEventPairB.c` → `src/ov039/overlay_event_dispatch/DispatchOverlayEventPairB_020bd264.c`, symbol reference line(s) 2, 9, 14.
- `eu/src/overlays/ov039/calls/DispatchOverlayEventPairC.c` → `src/ov039/overlay_event_dispatch/DispatchOverlayEventPairC_020bd3cc.c`, symbol reference line(s) 2, 9, 14.
- `eu/src/overlays/ov039/calls/DispatchOverlayEventPairD.c` → `src/ov039/overlay_event_dispatch/DispatchOverlayEventPairD_020bd534.c`, symbol reference line(s) 2, 9, 14.
- `eu/src/overlays/ov039/calls/LoadPrimarySubOverlay.c` → `src/ov039/overlay_handling/LoadPrimarySubOverlay_020bce34.c`, symbol reference line(s) 6, 14.
- `eu/src/overlays/ov039/calls/LoadSecondarySubOverlay.c` → `src/ov039/overlay_handling/LoadSecondarySubOverlay_020bcf50.c`, symbol reference line(s) 6, 14.
- `eu/src/overlays/ov039/calls/UnloadAllSubOverlays.c` → `src/ov039/overlay_handling/UnloadAllSubOverlays_020bcdd0.c`, symbol reference line(s) 6, 13, 14, 15, 17, 18, 19.
- `eu/src/overlays/ov039/calls/UnloadPrimarySubOverlay.c` → `src/ov039/overlay_handling/UnloadPrimarySubOverlay_020bce6c.c`, symbol reference line(s) 6, 13, 17.
- `eu/src/overlays/ov039/calls/UnloadSecondarySubOverlay.c` → `src/ov039/overlay_handling/UnloadSecondarySubOverlay_020bcf88.c`, symbol reference line(s) 6, 13, 17.
- `eu/src/overlays/ov039/calls/dispatchMenuHandlerPairAt1c.c` → `src/ov039/menu_dispatch/dispatchMenuHandlerPairAt1c_020bd174.c`, symbol reference line(s) 2, 9, 14.
- `eu/src/overlays/ov039/calls/dispatchMenuHandlerPairAt28.c` → `src/ov039/menu_dispatch/dispatchMenuHandlerPairAt28_020bd2dc.c`, symbol reference line(s) 2, 9, 14.
- `eu/src/overlays/ov039/calls/dispatchMenuHandlerPairAt34.c` → `src/ov039/menu_dispatch/dispatchMenuHandlerPairAt34_020bd444.c`, symbol reference line(s) 2, 9, 14.
- `eu/src/overlays/ov039/calls/dispatchMenuHandlerPairAt40.c` → `src/ov039/menu_dispatch/dispatchMenuHandlerPairAt40_020bd5ac.c`, symbol reference line(s) 2, 9, 14.
- `eu/src/overlays/ov039/calls/dispatchSelectedMenuCallback.c` → `src/ov039/menu_dispatch/dispatchSelectedMenuCallback_020bcfcc.c`, symbol reference line(s) 8, 14.
- `eu/src/overlays/ov039/calls/dispatch_input_handler_pair_14.c` → `src/ov039/input/dispatch_input_handler_pair_14_020bd084.c`, symbol reference line(s) 2, 9, 14.
- `eu/src/overlays/ov039/calls/dispatch_input_handler_pair_20.c` → `src/ov039/input/dispatch_input_handler_pair_20_020bd1ec.c`, symbol reference line(s) 2, 9, 14.
- `eu/src/overlays/ov039/calls/dispatch_input_handler_pair_2c.c` → `src/ov039/input/dispatch_input_handler_pair_2c_020bd354.c`, symbol reference line(s) 2, 9, 14.
- `eu/src/overlays/ov039/calls/dispatch_input_handler_pair_38.c` → `src/ov039/input/dispatch_input_handler_pair_38_020bd4bc.c`, symbol reference line(s) 2, 9, 14.
- `eu/src/overlays/ov039/calls/ResetMenuSubOverlayIndices.c`, symbol reference line(s) 1, 4, 5.
- `eu/src/overlays/ov039/calls/InvokePrimaryMenuSubOverlayDestroy.c`, symbol reference line(s) 1, 6.
- `eu/src/overlays/ov039/calls/UpdatePrimaryMenuSubOverlay.c`, symbol reference line(s) 1, 6.
- `eu/src/overlays/ov039/calls/UpdateSecondaryMenuSubOverlay.c`, symbol reference line(s) 1, 6.
- `eu/src/overlays/ov039/calls/GetPrimaryMenuSubOverlayIndex.c`, symbol reference line(s) 1, 4.
- `eu/src/overlays/ov039/calls/GetPrimaryMenuSecondaryOverlayIndex.c` → `src/ov039/reviewed_helpers/func_ov039_020bd634.c`, symbol reference line(s) 1, 5.
- `eu/src/overlays/ov039/calls/GetPrimaryMenuSubOverlayWorkSize.c` → `src/ov039/reviewed_helpers/func_ov039_020bd654.c`, symbol reference line(s) 1, 5.
- `eu/src/overlays/ov039/calls/GetSecondaryMenuSubOverlayWorkSize.c` → `src/ov039/reviewed_helpers/func_ov039_020bd674.c`, symbol reference line(s) 1, 5.
- `eu/src/overlays/ov039/data/bss/Bss_ov039_020beaa4.c`, symbol reference line(s) 3.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov040:020be280` → `gAreaRewardSceneWork`

Previous label: `data_ov040_020be280`. Existing ELF symbol size: **4 bytes**. Source: `eu/src/overlays/ov040/data/bss/Bss_ov040_020be280.c`.

4-byte pointer to the ov040 area/reward scene work.

InitAreaRewardScene publishes the scene allocation; scene load/transition/state/model-draw consumers borrow it.

Limits: This is the ov040 scene owner, distinct from ov035 material-fade work and ov040 resource globals.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov040/calls/AdvanceLoopingAnimation.c` → `src/ov040/animation/AdvanceLoopingAnimation_020bdb0c.c`, symbol reference line(s) 9, 15, 17, 19, 20.
- `eu/src/overlays/ov040/calls/FadeInAreaScreens.c` → `src/ov040/unclassified_helpers/FadeInAreaScreens_020bd464.c`, symbol reference line(s) 26, 66.
- `eu/src/overlays/ov040/calls/FinishAreaSceneLoad.c`, symbol reference line(s) 24, 52, 61, 62, 65, 70, 74.
- `eu/src/overlays/ov040/calls/FinishAreaTransition.c` → `src/ov040/unclassified_helpers/FinishAreaTransition_020bd66c.c`, symbol reference line(s) 17, 42, 61.
- `eu/src/overlays/ov040/calls/InitAreaRewardScene.c` → `src/ov040/shared_engine/InitAreaRewardScene_020bd730.c`, symbol reference line(s) 86, 179.
- `eu/src/overlays/ov040/calls/ResetAreaMeshValues.c` → `src/ov040/unclassified_helpers/ResetAreaMeshValues_020bcc60.c`, symbol reference line(s) 20, 52.
- `eu/src/overlays/ov040/calls/RunMenuStateMachine.c` → `src/ov040/unclassified_helpers/RunMenuStateMachine_020bd918.c`, symbol reference line(s) 13, 18, 24, 29.
- `eu/src/overlays/ov040/calls/SetupAreaFieldState.c` → `src/ov040/unclassified_helpers/func_ov040_020bce50.c`, symbol reference line(s) 67, 128, 144, 200, 205.
- `eu/src/overlays/ov040/calls/ShutdownScreenWork.c` → `src/ov040/unclassified_helpers/ShutdownScreenWork_020bd990.c`, symbol reference line(s) 26, 38, 49, 50.
- `eu/src/overlays/ov040/calls/StartAreaCameraIntro.c` → `src/ov040/unclassified_helpers/StartAreaCameraIntro_020bd298.c`, symbol reference line(s) 29, 45, 46, 47, 68.
- `eu/src/overlays/ov040/calls/TickIntroRotation.c` → `src/ov040/unclassified_helpers/TickIntroRotation_020bd364.c`, symbol reference line(s) 17, 40.
- `eu/src/overlays/ov040/calls/UpdateAreaSceneState.c`, symbol reference line(s) 28, 85.
- `eu/src/overlays/ov040/calls/AreaSceneState_SetTransitionAudioAndFlags.c`, symbol reference line(s) 5, 23.
- `eu/src/overlays/ov040/calls/AreaSceneState_WaitForExitTransition.c`, symbol reference line(s) 4, 20.
- `eu/src/overlays/ov040/calls/DrawAreaRewardModel.c`, symbol reference line(s) 3, 8.
- `eu/src/overlays/ov040/data/bss/Bss_ov040_020be280.c`, symbol reference line(s) 4.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov040:020be284` → `gAreaRewardResourceGlobalsStorage`

Previous label: `data_ov040_020be284`. Existing ELF symbol size: **28 bytes**. Source: `eu/src/overlays/ov040/data/bss/Bss_ov040_020be280.c`.

28-byte BSS symbol: first word points to an allocated 0x14-byte resource/reward block, trailing 24 bytes opaque.

The native resource initializer allocates 0x14 bytes, publishes its pointer, stores two acquired record handles and one palette entry at +0/+4/+8, and clears +0xc. Reward consumers use that block; FreeCueTable_020be00c frees it and clears the global.

Limits: The constructor does not initialize the pointee word +0x10. Do not treat all 0x14 bytes as zeroed, infer a general animation owner, or confuse the 28-byte global with its 20-byte allocation.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/overlays/ov040/Ov040RewardAnimationState.h`, symbol reference line(s) 16, 17.
- `eu/src/overlays/ov040/calls/FreeCueTable_020be00c.c` → `src/ov040/shared_engine/FreeCueTable_020bdfec.c`, symbol reference line(s) 2, 5, 6, 8.
- `eu/src/overlays/ov040/calls/GrantRewardItem.c` → `src/ov040/shared_engine/GrantRewardItem_020be02c.c`, symbol reference line(s) 17, 30.
- `eu/src/overlays/ov040/calls/ShowRewardPopupForItem.c` → `src/ov040/shared_engine/ShowRewardPopupForItem_020be0f8.c`, symbol reference line(s) 19, 26.
- `eu/src/overlays/ov040/calls/UpdateRewardMenuHighlights.c` → `src/ov040/shared_engine/UpdateRewardMenuHighlights_020bde68.c`, symbol reference line(s) 42, 54.
- `eu/src/overlays/ov040/calls/InitAreaRewardResources.c`, symbol reference line(s) 3, 16.
- `eu/src/overlays/ov040/calls/GetAreaRewardAnimationTable.c`, symbol reference line(s) 3, 6.
- `eu/src/overlays/ov040/data/bss/Bss_ov040_020be280.c`, symbol reference line(s) 3.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov036:020c36e4` → `gEvent2DPanelTaskClass`

Previous label: `data_ov036_020c36e4`. Existing ELF symbol size: **20 bytes**. Source: `eu/src/ov036/data/Data_ov036_020c36e0.c`.

Native ClassDescriptor prefix: classId/subId packed word 0x0002000e; constructor at +4 (InitEvent2DPanel); destructor at +8 (ShutdownSceneWork_020ba6c4); workSize +0xc = 0x10fc; heapRef +0x10 = NULL.

The initializer supplies this five-word prefix to CreateTaskObject; Obj_Construct copies classId/subId/workSize, allocates and clears task work, invokes the constructor with the task as current, and stores its returned update callback. The descriptor +8 callback is used during destruction.

Limits: TaskObject class IDs are not priorities or flags. Constructor return is the update callback; +8 is not the update callback. Preserve raw declarations and relocation targets. The existing symbol is exactly the 20-byte descriptor.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov036/data/Data_ov036_020c36e0.c`, symbol reference line(s) 7.
- `eu/src/overlays/ov036/calls/CreateEvent2DPanelTask.c` → `src/ov036/reviewed_helpers/func_ov036_020bc384.c`, symbol reference line(s) 2, 6.

Relocations inside this symbol: 2. Native target expressions and addends are retained.

### `ov036:020c36e0` → `gEvent2DPanelTaskHandle`

Previous label: `data_ov036_020c36e0`. Existing ELF symbol size: **4 bytes**. Source: `eu/src/ov036/data/Data_ov036_020c36e0.c`.

4-byte task handle initialized to 0xffffffff.

The Event2D panel task creator stores CreateTaskObject result using the neighboring panel descriptor; teardown uses the same handle.

Limits: Preserve bank identity and do not infer a complete panel layout from this handle.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov036/data/Data_ov036_020c36e0.c`, symbol reference line(s) 15.
- `eu/src/overlays/ov036/calls/InvalidatePxiFifoTag.c` → `src/ov036/library_nitro_pxi/InvalidatePxiFifoTag_020bc438.c`, symbol reference line(s) 3, 8, 9.
- `eu/src/overlays/ov036/calls/IsPxiFifoTagSet_020bc434.c` → `src/ov036/library_nitro_pxi/IsPxiFifoTagSet_020bc414.c`, symbol reference line(s) 3, 10.
- `eu/src/overlays/ov036/calls/CreateEvent2DPanelTask.c` → `src/ov036/reviewed_helpers/func_ov036_020bc384.c`, symbol reference line(s) 3, 6.

Relocations inside this symbol: 0. Native target expressions and addends are retained.

### `ov036:020c3868` → `gTextWindowTaskClass`

Previous label: `data_ov036_020c3868`. Existing ELF symbol size: **20 bytes**. Source: `eu/src/ov036/data/Data_ov036_020c3868.c`.

Native ClassDescriptor prefix: classId/subId packed word 0x000e001b; constructor at +4 (InitTextWindowTask (InitTextWindowTask proposal)); destructor at +8 (DestroyTextWindowTask (DestroyTextWindowTask proposal)); workSize +0xc = 0x68b4; heapRef +0x10 = NULL.

The initializer supplies this five-word prefix to CreateTaskObject; Obj_Construct copies classId/subId/workSize, allocates and clears task work, invokes the constructor with the task as current, and stores its returned update callback. The descriptor +8 callback is used during destruction.

Limits: TaskObject class IDs are not priorities or flags. Constructor return is the update callback; +8 is not the update callback. Preserve raw declarations and relocation targets. The existing symbol is exactly the 20-byte descriptor.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov036/data/Data_ov036_020c3868.c`, symbol reference line(s) 8.
- `eu/src/overlays/ov036/calls/CreateTextWindowTask.c`, symbol reference line(s) 4, 10.

Relocations inside this symbol: 2. Native target expressions and addends are retained.

### `ov036:020c392c` → `gTextWindowControllerTaskClass`

Previous label: `data_ov036_020c392c`. Existing ELF symbol size: **20 bytes**. Source: `eu/src/ov036/data/Data_ov036_020c392c.c`.

Native ClassDescriptor prefix: classId/subId packed word 0x000e001b; constructor at +4 (InitTextWindowControllerTask (InitTextWindowControllerTask proposal)); destructor at +8 (DestroyPxiChannelState); workSize +0xc = 0x20; heapRef +0x10 = NULL.

The initializer supplies this five-word prefix to CreateTaskObject; Obj_Construct copies classId/subId/workSize, allocates and clears task work, invokes the constructor with the task as current, and stores its returned update callback. The descriptor +8 callback is used during destruction.

Limits: TaskObject class IDs are not priorities or flags. Constructor return is the update callback; +8 is not the update callback. Preserve raw declarations and relocation targets. The existing symbol is exactly the 20-byte descriptor.

Pinned references (EU wrapper → shared source where applicable):

- `eu/src/ov036/data/Data_ov036_020c392c.c`, symbol reference line(s) 8.
- `eu/src/overlays/ov036/calls/InitEvent2DPanel.c`, symbol reference line(s) 13, 50.

Relocations inside this symbol: 2. Native target expressions and addends are retained.

## Integration limits

Rename tokens and configured symbols only. Keep all source paths, declarations, private views, opaque tails and relocation expressions intact. The ov039 primary/secondary registry fragments are excluded because a separate bank-aware plan owns them. The ov033 descriptor remains 44 bytes, and the ov031 packed handler storage remains 93 bytes. Names inherited from Movie/Sound/PXI labels are not used as evidence of a decoder, audio engine or PXI owner.


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
