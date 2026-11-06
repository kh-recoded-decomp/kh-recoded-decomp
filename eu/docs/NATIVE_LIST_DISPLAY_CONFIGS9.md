# Menu-list and overlay display configuration DATA (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

## Configuration boundaries

The menu-list layer-ID pairs, pointer-containing tile-table descriptor, object-manager config, text frames, background callbacks and slot-list template remain separate objects. Native constructors copy them and replace selected fields locally. The old ResetMenuLayerTransforms label actually uploads two BG screen buffers. Overlay-display initialization owns a separate settings template and a two-byte color upload within a four-byte symbol.

## Inventory and evidence

### `ov025:020b76a0` → `gPanelListBgLayerIds`

Previous label `data_ov025_020b76a0`; existing ELF size **8 bytes**. Source: `eu/src/ov025/data/Rodata_ov025_020b76a0.c`.

8 initialized bytes: two native u32 tile-table layer IDs.

ResetMenuLayerTransforms obtains each layer buffer from menu+0x64c8 using these IDs, then invokes the matching gSubBgScreenLoaders entry with (buffer,0,0x1000) when menu exists and readiness+0x64e4 is nonzero.

Limits: The inherited function name does not make these transform/scale values. They select two layer buffers for screen uploads; preserve the two IDs and their ordering.

Pinned references:

- `eu/src/ov025/data/Rodata_ov025_020b76a0.c`; reference line(s) 3.
- `eu/src/overlays/ov025/calls/ResetMenuLayerTransforms.c` → `src/ov025/menu_widgets/ResetMenuLayerTransforms_020b6194.c`; reference line(s) 14, 20.

### `ov025:020b76a8` → `gPanelListTileTableLayerIds`

Previous label `data_ov025_020b76a8`; existing ELF size **8 bytes**. Source: `eu/src/ov025/data/Rodata_ov025_020b76a8.c`.

8 initialized bytes: two native u32 layer IDs used by the menu-list tile table.

InitMenuScreen copies this pair, replaces the copied LayerConfig.params with its address, and supplies that local descriptor to InitTileTableFrom(menu+0x64c8,...).

Limits: This is a static layer-ID pair, separate from the pointer-containing descriptor. Keep both objects and the local rebinding; no borrowed stack-pointer lifetime is changed.

Pinned references:

- `eu/src/ov025/data/Rodata_ov025_020b76a8.c`; reference line(s) 7.
- `eu/src/overlays/ov025/calls/InitMenuScreen.c` → `src/ov025/shared_engine/InitMenuScreen_020b5acc.c`; reference line(s) 36, 69.

### `ov025:020b76b0` → `gPanelListTileTableConfig`

Previous label `data_ov025_020b76b0`; existing ELF size **16 bytes**. Source: `eu/src/ov025/data/Rodata_ov025_020b76a8.c`.

16 initialized bytes: native layer-table descriptor whose first word is a relocation to gPanelListTileTableLayerIds.

InitMenuScreen copies this descriptor, repoints params to the local layer-ID copy and initializes its embedded tile table.

Limits: Do not keep a new pointer to the local descriptor after initialization or replace the pointer relocation with an integer constant. Other native descriptor fields remain in their original representation.

Pinned references:

- `eu/src/ov025/data/Rodata_ov025_020b76a8.c`; reference line(s) 3.
- `eu/src/overlays/ov025/calls/InitMenuScreen.c` → `src/ov025/shared_engine/InitMenuScreen_020b5acc.c`; reference line(s) 37, 70.

### `ov025:020b76c0` → `gPanelListObjectManagerConfig`

Previous label `data_ov025_020b76c0`; existing ELF size **16 bytes**. Source: `eu/src/ov025/data/Rodata_ov025_020b76c0.c`.

16 initialized bytes: resource-key word followed by three native configuration words.

InitMenuScreen copies this descriptor, replaces its vramKey with MakePrimaryVramKey(0x69) and initializes the object manager at menu+0x4c using the local copy.

Limits: The static first word is a placeholder. No new semantic names or types are inferred for the other configuration words.

Pinned references:

- `eu/src/ov025/data/Rodata_ov025_020b76c0.c`; reference line(s) 3.
- `eu/src/overlays/ov025/calls/InitMenuScreen.c` → `src/ov025/shared_engine/InitMenuScreen_020b5acc.c`; reference line(s) 35, 68.

### `ov025:020b76d0` → `gPanelListTextLayerConfig`

Previous label `data_ov025_020b76d0`; existing ELF size **16 bytes**. Source: `eu/src/ov025/data/Rodata_ov025_020b76d0.c`.

16 initialized bytes: native TextFrame {x,y,width,height,tileOffset,three remaining u16 fields}.

SetupMenuTextLayers copies this frame for the first text layer, then modifies the local frame for two further layers. All three initialize with the selected field tile-table row and GetFieldFont3. Subsequent label draws supply GetFieldFont2 to DrawTextAnchoredWithFontFallback.

Limits: Preserve all eight halfwords and do not label the remaining fields as a palette without the text-layer constructor contract. The shared initializer does not mutate this static object.

Pinned references:

- `eu/src/ov025/data/Rodata_ov025_020b76d0.c`; reference line(s) 31.
- `eu/src/overlays/ov025/calls/SetupMenuTextLayers.c` → `src/ov025/shared_engine/SetupMenuTextLayers_020b5c78.c`; reference line(s) 20, 50.

### `ov025:020b76e0` → `gPanelListBackgroundContainerConfig`

Previous label `data_ov025_020b76e0`; existing ELF size **20 bytes**. Source: `eu/src/ov025/data/Rodata_ov025_020b76d0.c`.

20 initialized bytes copied as five native words for the background/tag container.

SetupMenuTextLayers copies this object and passes it to InitBackgroundContainer(menu,...), before setting up the text-layer frames and scheduling the next update callback.

Limits: The generic callback parameter0c/parameter10 slots remain operationally opaque. Keep raw prefix fields and relocation words; do not infer init/draw/cleanup slots from names alone.

Pinned references:

- `eu/src/ov025/data/Rodata_ov025_020b76d0.c`; reference line(s) 23.
- `eu/src/overlays/ov025/calls/SetupMenuTextLayers.c` → `src/ov025/shared_engine/SetupMenuTextLayers_020b5c78.c`; reference line(s) 19, 44.

### `ov025:020b76f4` → `gPanelListViewConfig`

Previous label `data_ov025_020b76f4`; existing ELF size **48 bytes**. Source: `eu/src/ov025/data/Rodata_ov025_020b76d0.c`.

48 initialized bytes: native ListViewConfig template with path resolver, change callback, data/async fields, mode and entry/cell/sequence settings.

InitMenuScreen copies this template, fills data and field values, cellSet/highlight/cursor pointers, depth/maxSlots and normal/highlight sequence selectors; it adjusts asyncLoad for immediate mode and passes the local copy to InitSlotListView(menu+0x64f4,...).

Limits: Preserve the exact native 48 bytes and function relocations. Fields replaced in the local copy are not changed in the static object. Portable callback prototypes need their actual invokers; this naming block does not standardize them.

Pinned references:

- `eu/src/ov025/data/Rodata_ov025_020b76d0.c`; reference line(s) 8.
- `eu/src/overlays/ov025/calls/InitMenuScreen.c` → `src/ov025/shared_engine/InitMenuScreen_020b5acc.c`; reference line(s) 34, 67.

### `ov026:020b5ab0` → `gOverlayDisplayResourceContainerConfig`

Previous label `data_ov026_020b5ab0`; existing ELF size **24 bytes**. Source: `eu/src/ov026/data/Rodata_ov026_020b5ab0.c`.

24 initialized bytes copied as six native settings words.

InitializeOverlayDisplaySession copies these settings, saves current display/brightness state, sets initial-update flags and supplies the local settings to InitializeResourceContainer for the session owner.

Limits: The caller establishes a resource-container configuration, not six display registers. No field semantics beyond the initializer API are invented.

Pinned references:

- `eu/src/ov026/data/Rodata_ov026_020b5ab0.c`; reference line(s) 6.
- `eu/src/overlays/ov026/calls/InitializeOverlayDisplaySession.c` → `src/ov026/display_session/InitializeOverlayDisplaySession.c`; reference line(s) 13, 21.

### `ov026:020b5af4` → `gOverlayDisplayWhiteColorStorage`

Previous label `data_ov026_020b5af4`; existing ELF size **4 bytes**. Source: `eu/src/ov026/data/Data_ov026_020b5af4.c`.

4 initialized bytes; low u16 is 0x7fff, remaining halfword preserved.

When cached sub brightness equals 0x10, InitializeOverlayDisplaySession copies the first two bytes with GXS_LoadBGPltt(source,0,2) and sets restorePositiveBrightness.

Limits: Keep the four-byte object although the demonstrated upload uses only two bytes. This is a fallback palette color, not a brightness limit or a maximum-record count.

Pinned references:

- `eu/src/ov026/data/Data_ov026_020b5af4.c`; reference line(s) 5.
- `eu/src/overlays/ov026/calls/InitializeOverlayDisplaySession.c` → `src/ov026/display_session/InitializeOverlayDisplaySession.c`; reference line(s) 14, 28.


## Byte-exact validation

103 DATA identities retain their source paths, native sizes and storage.
405/410 affected official function checks pass; the remaining
5 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 474 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
