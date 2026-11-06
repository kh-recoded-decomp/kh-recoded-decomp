# Map and board screen configuration DATA (EU)

Review source baseline: `28dc258674c86cde06bc8456c4c7cb9087e28905`. Native source paths and physical storage remain unchanged; the integration results are recorded below.

## Configuration boundaries

The map resource-index table maps menu entries to file IDs, not palettes. Text-layer data are native configuration words; misleading local TextColors typedefs do not prove a palette layout. Static object-manager descriptors contain a first resource word replaced in a local copy before initialization. Board BG layer IDs, object-manager config and background-container callback config remain separate objects with their existing bytes and relocations.

## Inventory and evidence

### `ov023:020b6e94` → `gMapMenuHeaderTextLayerConfig`

Previous label `data_ov023_020b6e94`; existing ELF size **16 bytes**. Source: `eu/src/ov023/data/Rodata_ov023_020b6e94.c`.

16 initialized bytes copied as eight u16 words into a local text-layer configuration.

InitOv023TextLayer26 obtains layer 0x1a of the field tile table and GetFieldFont3, then passes this copied configuration to InitTextLayerAtFromEnd with count 6 and marks that row dirty.

Limits: Do not call these eight values a palette: the native text-layer constructor consumes configuration. Field interpretations and full host layout are not newly assigned in this rename-only block.

Pinned references:

- `eu/src/ov023/data/Rodata_ov023_020b6e94.c`; reference line(s) 3.
- `eu/src/overlays/ov023/calls/InitOv023TextLayer26.c`; reference line(s) 4, 22.

### `ov023:020b6ea4` → `gMapScreenInitialSlotPosition`

Previous label `data_ov023_020b6ea4`; existing ELF size **8 bytes**. Source: `eu/src/ov023/data/Rodata_ov023_020b6ea4.c`.

8 initialized bytes, a native pair of 32-bit X/Y values.

InitMapScreen copies this point pair and supplies it to IndexedRecord_SetPair for handles 0,1 and4. It later overwrites the local pair for handle 5.

Limits: The name records the initialized slot position, not a camera/world position or a promise that every map slot starts there.

Pinned references:

- `eu/src/ov023/data/Rodata_ov023_020b6ea4.c`; reference line(s) 3.
- `eu/src/overlays/ov023/calls/InitMapScreen.c` → `src/ov023/menu_graphics/InitMapScreen_020b5de0.c`; reference line(s) 32, 56.

### `ov023:020b6eac` → `gMapMenuCursorResetPosition`

Previous label `data_ov023_020b6eac`; existing ELF size **8 bytes**. Source: `eu/src/ov023/data/Rodata_ov023_020b6eac.c`.

8 initialized bytes, native MapPoint {fx32 x,fx32 y}.

ResetMapMenuCursor copies this point, resets the cursor animation and sends it to IndexedRecord_SetPair for the cursor slot. Its subsequent marker-slot update uses separately computed X/Y values.

Limits: Cursor reset and marker placement are distinct. Preserve both fixed-point words and do not infer screen-pixel conversion in the native storage.

Pinned references:

- `eu/src/ov023/data/Rodata_ov023_020b6eac.c`; reference line(s) 7.
- `eu/src/overlays/ov023/calls/ResetMapMenuCursor.c` → `src/ov023/menu_graphics/ResetMapMenuCursor_020b69bc.c`; reference line(s) 28, 35.

### `ov023:020b6eb4` → `gMapScreenObjectManagerConfig`

Previous label `data_ov023_020b6eb4`; existing ELF size **16 bytes**. Source: `eu/src/ov023/data/Rodata_ov023_020b6eac.c`.

16 initialized bytes, four native manager-configuration words.

InitMapScreen copies the descriptor, replaces its first resource-key word using screen->vramBase and passes the local copy to InitObjManagerVariant for screen->manager.

Limits: The first static word is a placeholder replaced in the local copy. No new semantic names are assigned to the other three configuration words.

Pinned references:

- `eu/src/ov023/data/Rodata_ov023_020b6eac.c`; reference line(s) 3.
- `eu/src/overlays/ov023/calls/InitMapScreen.c` → `src/ov023/menu_graphics/InitMapScreen_020b5de0.c`; reference line(s) 31, 55.

### `ov023:020b6efc` → `gMapMenuEntryFileIndices`

Previous label `data_ov023_020b6efc`; existing ELF size **16 bytes**. Source: `eu/src/overlays/ov023/data/tables/MapTargetPalettes.c`.

16 initialized bytes: eight u16 file indexes {0,1,2,3,4,5,5,6}.

For menu index < 8, PrepareMenuScreenEntry reads this halfword table and inserts its low nine bits into a resource ID, then queues a load with ApplyMenuScreenEntry callback. For index >= 8 it takes the fallback branch instead.

Limits: This is a file-index mapping, not a palette-index table. Keep the repeated value 5 and original branch order; no index type or bound check is changed.

Pinned references:

- `eu/src/overlays/ov023/calls/PrepareMenuScreenEntry.c`; reference line(s) 4, 45.
- `eu/src/overlays/ov023/data/tables/MapTargetPalettes.c`; reference line(s) 13.

### `ov024:020b7340` → `gBoardTextLayerConfig`

Previous label `data_ov024_020b7340`; existing ELF size **16 bytes**. Source: `eu/src/ov024/data/Rodata_ov024_020b7340.c`.

16 initialized bytes copied through the native eight-halfword text-layer configuration view.

SetupBoardTextLayer supplies this configuration to InitTextLayerAtFromEnd for board layer 0x18, using either its loaded font or GetFieldFont3, then marks that layer dirty.

Limits: The local typedef TextColors is not proof that all fields are colors. Keep the raw configuration words and defer a portable struct layout to the text-layer constructor contract.

Pinned references:

- `eu/src/ov024/data/Rodata_ov024_020b7340.c`; reference line(s) 3.
- `eu/src/overlays/ov024/calls/SetupBoardTextLayer.c` → `src/ov024/unclassified_helpers/SetupBoardTextLayer_020b664c.c`; reference line(s) 25, 42.

### `ov024:020b7350` → `gBoardBgLayerIds`

Previous label `data_ov024_020b7350`; existing ELF size **16 bytes**. Source: `eu/src/ov024/data/Rodata_ov024_020b7350.c`.

16 initialized bytes: four u32 tile-table layer IDs 24,25,26,27.

CreateBoardScreen copies these four IDs into the local layout used by a BgLayerDesc with count 4 and 32x32 dimensions. It supplies that descriptor to InitTileTableFrom only when the standalone useChannel branch is taken.

Limits: Other modes borrow GetFieldSceneManager instead. Do not merge these IDs with its separate background-container callback descriptor or graphics archive resources.

Pinned references:

- `eu/src/ov024/data/Rodata_ov024_020b7350.c`; reference line(s) 3.
- `eu/src/overlays/ov024/calls/CreateBoardScreen.c`; reference line(s) 51, 83.

### `ov024:020b7360` → `gBoardObjectManagerConfig`

Previous label `data_ov024_020b7360`; existing ELF size **16 bytes**. Source: `eu/src/ov024/data/Rodata_ov024_020b7360.c`.

16 initialized bytes, four native object-manager configuration words.

CreateBoardScreen copies the descriptor, replaces word 0 with the resource key for file index 0x13 in resourceA and passes the local descriptor to InitObjManagerAndMark.

Limits: Preserve the overwritten static placeholder and the three other words without deriving undocumented graphics parameters from their values.

Pinned references:

- `eu/src/ov024/data/Rodata_ov024_020b7360.c`; reference line(s) 19.
- `eu/src/overlays/ov024/calls/CreateBoardScreen.c`; reference line(s) 52, 128.

### `ov024:020b7370` → `gBoardBackgroundContainerConfig`

Previous label `data_ov024_020b7370`; existing ELF size **20 bytes**. Source: `eu/src/ov024/data/Rodata_ov024_020b7360.c`.

20 initialized bytes: three prefix words and two native function-pointer words at+0xc/+0x10.

CreateBoardScreen copies this descriptor and supplies it to InitBackgroundContainer for the board animation/tag container. The two relocations target BlitBoardWidgetAndFinishPendingTeardown and ClearBoardWidgetTileArea.

Limits: The generic BackgroundContainer parameter0c/parameter10 slots remain operationally opaque until their invokers are proven. Do not relabel them init/draw/cleanup based only on callback names; preserve both relocations and the entire descriptor.

Pinned references:

- `eu/src/ov024/data/Rodata_ov024_020b7360.c`; reference line(s) 11.
- `eu/src/overlays/ov024/calls/CreateBoardScreen.c`; reference line(s) 53, 124.


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
