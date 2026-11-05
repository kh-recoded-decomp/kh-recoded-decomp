# Late-menu rendering and resource helpers

These 35 EU names are established by the actual function bodies, their bound
resources and their consumers. Similar helpers remain separate overlay entries;
the following contracts record both their shared behavior and their differences.

## Names and evidence

| Previous symbol | Current name | Established behavior |
|---|---|---|
| `func_ov075_020cd0c0` | `BuildItemPickerListForType` | Builds cached item/record pointer list according to enabled type bit, type11=all, nonzero count and sortKey<9999; excludes item indices0..127; qsort uses item-picker comparator. |
| `func_ov085_020c1cdc` | `BuildShopItemListForType` | Same list filter as ov075; uses shop count builder and comparator. No type/index validation. |
| `func_ov075_020cd470` | `LoadItemPickerTextureDrawParams` | Loads encoded archive/index file; dispatches resource; selects texture/palette entry0; extracts width/height/imageParam/paletteBase and frees source. Assumes valid entries; handles compressed4x4 key/palette units. |
| `func_ov076_020c96b8` | `LoadSlotMenuTextureDrawParams` | Same entry0 extraction as ov075 with slot-menu overlay binding. Keep independent function. |
| `func_ov077_020c66ec` | `LoadItemScreenTextureDrawParams` | Same entry0 extraction as ov075 with item-screen overlay binding. Keep independent function. |
| `func_ov075_020cd874` | `DrawItemPickerTexturedQuad` | Builds ImageQuad scale/translation, rotation/texture/palette/color and four UV/vertex pairs. BOOL controls decal polygon mode; y<=0 adds1fx32 height; no clipping/state restoration. |
| `func_ov077_020c9f80` | `DrawItemScreenImageFromPackedArgs` | select high16=image index/low16=color; pos high/low signed16=XY; depth passed separately. Emits full textured quad, unlike ov075 subrectangle/decal interface. |
| `func_ov075_020ceea4` | `UpdateItemPickerCharUpload` | Skips paused work/mismatched VBlank parity; if upload enabled copies2400h bytes to BG1 char+140h; updates renderer only if renderer busy==0. Busy does not guard upload. |
| `func_ov076_020cacb4` | `UpdateSlotMenuCharUpload` | Same parity/upload/idle-renderer behavior with gSlotMenuPanelWork, distinct from item-picker work. |
| `func_ov075_020cef00` | `BuildItemPickerFrameTilemap` | Builds 3x3-style frame in32x24 screen, fills middle strips and clears outside. Upper-clamps only, narrows origins/sizes unsigned, preserves width-2 behavior. |
| `func_ov076_020cad10` | `BuildSlotMenuFrameTilemap` | Same32x24 frame builder using distinct slot-menu tile table. No lower rectangle validation. |
| `func_ov075_020cf204` | `HandleItemPickerTextTag` | Tags1/2/4 assignF2/highlight/FA;1F centers next line using measured width and linefeed+vSpace. Other tags untouched; retain(width+1)/2 arithmetic. |
| `func_ov076_020cb154` | `HandleSlotMenuTextTag` | Same tag contract; distinct work and helper binding TextCanvas_GetLineWidth rather than MeasureTextLine. |
| `func_ov075_020d0f70` | `LoadItemPickerMenuTipImages` | Opens literal ui/menu/tips.p2 and language tips archive; loads85h entries with sequential localized fallback only for empty primary entry, extracts texture/palette metadata, frees buffers/containers, toggles dispatch0 then1. |
| `func_ov076_020ccda4` | `LoadSlotMenuTipImages` | Same85h tip metadata/fallback algorithm with slot menu path globals. Fallback counter advances only for empty primary; VRAM metadata survives source free. |
| `func_ov077_020c9df0` | `LoadItemScreenMenuTipImages` | Same85h tip metadata/fallback algorithm with item-screen path globals; preserve independent overlay binding. |
| `func_ov085_020c1fd4` | `LoadShopMenuTipImages` | Same85h tip metadata/fallback algorithm with shop path globals; preserve independent overlay binding. |
| `func_ov091_020bf1b4` | `LoadReportTopMessageContainers` | Opens all3 gReportTopResourcePaths with modeE/head allocation into owner table work+4; no prior-owner cleanup/failure check. |
| `func_ov097_020bf6c8` | `LoadStoryReportMessageContainers` | Opens all3 gStoryReportResourcePaths with modeE/head allocation into work+18h. Existing private type Ov101State is misleading; no prior-owner cleanup. |
| `func_ov103_020bef14` | `LoadTheaterReportMessageContainers` | Opens both gTheaterReportResourcePaths modeE/head into work+10h;2entries rather than3; no prior-owner cleanup. |
| `func_ov095_020c0064` | `DrawItemGridTextWithShadow` | DrawTextColored at XY+1 with color+1 for both colors then foreground suppliedXY/colors. Legacy flags parameter is second color here, not proven flags. |
| `func_ov099_020c060c` | `DrawEnemyViewerTextWithShadow` | Same two-pass shadow operation as ov095; preserve integer color+1 and custom tagged-text semantics. |
| `func_ov099_020becb4` | `InitEnemyViewerScreen` | Sets global work, clearsD6F8h bytes, initializes progress/resources/scroll/text/slots/model viewer and enters mode1. Returns1; not complete allocation-schema proof. |
| `func_ov099_020bedd0` | `DestroyEnemyViewerScreen` | Destroys viewer/models/object managers, frees resources, resets base rotation/dirty state, releases slots4/0 and manager, frees message container and clears global. Preserve cleanup order; not full renderer restore. |
| `func_ov099_020c2078` | `LoadEnemyViewerSelectionModels` | Releases old selection models; clears/builds each104h model from selection list; selects all5tracks, attaches models and applies pose. No selection/capacity guard. |
| `func_ov103_020c033c` | `InitTheaterReportScreen` | ClearsCBC4h work; clamps negative restored selection to0; loads messages/graphics/background/text/slots, setups list/unlocks, redraws and sets phase2. No upper selection guard. |
| `func_ov103_020bf5e8` | `CreateTheaterReportSlotEntries` | Initializes manager at work+174h from container entryDh, creates12 slots with14h descriptor stride. No complete descriptor schema inferred. |
| `func_ov086_020bfba0` | `RefreshRecordStatisticsRows` | Clears text via virtualslot1; dirties layer18h/trackerrow19h; draws statistic rows0..3 using established RecordPageMenu. |
| `func_ov086_020bf3b4` | `CountUnlockedRecordGroupEntries` | Sums earlier group counts for base, scans group and counts IsSessionFlagSet(base+i+581h). No group bounds validation or further flag-role claim. |
| `func_ov088_020bed2c` | `InitOverlay088CaptionLayer` | Loads literal ui/menu/str/&/cd.s.z into packed view+34h; inits text layer, draws entry0 at(4,0), uploads and dirties1Ah. Does not expand unknown cd abbreviation. |
| `func_ov088_020bedf0` | `DestroyOverlay088CaptionLayer` | FreePointerIfSet at owner slot context+34h, then DestroyFndObjectList. Normalize actual void** release if changing types; cached view fields become stale. |
| `func_ov097_020c1864` | `InitStoryReportSpriteFromFile` | Clears2Ch prefix; loads resource at+28h with flags11h; RebindSpriteToCell(slot,1,1,0); true return. No load failure guard. |
| `func_ov097_020c188c` | `ReleaseStoryReportSpriteResource` | Frees/clears+28h owner if nonzero; clears upper3bits at byte+26h; returns1. Does not clear whole sprite or other flags. |
| `func_ov079_020c4c0c` | `SaveOptionsAndCloseConfigMenu` | Plays close sound; ConfigMenu_SaveOptions(work); PopStackEntry; StartSubScene(0,-1,0). Preserve persistence/navigation order. |
| `func_ov087_020c4734` | `DrawChoiceWindowTextAndUpload` | Uses indexed34h layer at work+9F8h; draws text at(40h,2) with411h flags and uploads. No window bounds guard; flags remain numeric. |

## Separate copies and relative layouts

Similar functions remain separate overlay entry points. Their resource globals,
comparators, measurement helpers and menu work owners are part of the binding.
A shared algorithm is not permission to merge code or storage during naming.

| Family | Copies | Differences retained |
|---|---|---|
| Type-filtered item lists | overlays 75 and 85 | Item-picker/shop count-cache builders and comparators differ. |
| Texture draw-parameter extraction | overlays 75, 76 and 77 | Separate overlay entry points, otherwise the same entry-zero resource operation. |
| Menu-tip image metadata | overlays 75, 76, 77 and 85 | Separate primary/localized path globals and destination tables. |
| Frame tilemaps | overlays 75 and 76 | Each uses its own three-row frame tile table. |
| Text tags | overlays 75 and 76 | Distinct work owner and line-measurement helper alias. |
| Character uploads | overlays 75 and 76 | `gItemPickerPanelWork` versus `gSlotMenuPanelWork`. |
| Shadow text | overlays 95 and 99 | Separate item-grid/enemy-viewer entry points. |

Offsets in these views are relative to the parameter or work pointer used by
that function. Different helpers may receive different subobjects of the same
menu allocation. Do not combine their private padded views into one full menu
structure solely because their field names resemble each other.

## Texture and palette metadata

The three 216-byte extractors return the following observed 12-byte record:

| Byte offset | Type | Field |
|---|---|---|
| `0x00` | `u16` | Width |
| `0x02` | `u16` | Height |
| `0x04` | `u32` | Texture-image parameter word |
| `0x08` | `u32` | Palette-base word |

They encode an archive/index file ID, load with the existing mode `0x0e`, call
`ValidateResourceTagAndDispatch`, select texture dictionary entry zero and select
palette dictionary entry zero. Width is `extraParam & 0x7ff`; height is the next
11 bits. The texture format selector `((texImageParam >> 26) & 7) == 5` chooses
the 4x4 texture key; the other branch uses the ordinary texture key. The emitted
image word adds the selected key and sets `0x20000000`.

The palette path narrows the stored VRAM key to 16 bits and applies its existing
flag-controlled halving to the palette offset/key before combining them. The
narrowing and arithmetic order are part of the native code. This block does not
assign new hardware-unit names to those intermediate values.

The loaded file buffer is freed after metadata extraction. No pointer into that
file is returned in this record. A port must establish the graphics-resource
lifetime separately: freeing a temporary source file does not by itself describe
ownership of a host texture/palette object. Existing callers assume a valid
texture, palette dictionary and first entries; the helpers do not provide a
malformed-file or null-resource recovery path.

### Tip-image tables and localization

The four 396-byte tip loaders open the literal `ui/menu/tips.p2` container and
the corresponding language-specific container. They process `0x85` output
entries. A primary file whose first byte is zero is freed and replaced by the
next sequential localized file. The fallback index advances **only** for such
empty primary entries; it is not the primary image index.

Each chosen file is dispatched and converted into width/height/image/palette
metadata, then freed. Both containers are released after the loop. The code
changes the loader dispatch selector to zero before loading and restores one
at the end. Preserve that call order and investigate its backend contract when
porting; do not assume the selector is a generic asynchronous/synchronous switch
from its numeric value alone. No allocation/resource failure branch is added by
these matching implementations.

## Two different textured-quad interfaces

`DrawItemPickerTexturedQuad` takes a descriptor with an image pointer, signed
halfword X/Y, fx32 depth, texture offsets, width, height and color. It positions a
unit quad using the requested dimensions and offsets, flips Y around 192 and
selects polygon mode according to its `decal` argument. When the supplied Y is
nonpositive, its vertical scale increases by one fx32 unit. Texture offsets are
added when forming the opposite UV edge. This behavior is not general clipping.

`DrawItemScreenImageFromPackedArgs` instead selects an entire image using the
high 16 bits of `select`; the low 16 bits supply its color. The high/low signed
halfwords of `pos` supply X/Y, and depth is a separate fx32 argument. It has no
independent subrectangle/decal interface. Both functions set scale/translation,
copy their fixed rotation, update SDK dirty flags and emit four vertices and
UV pairs. Neither restores all prior geometry state after drawing.

A host renderer should model these two APIs explicitly rather than casting
between their descriptors or silently changing packed-coordinate signs.

## Frame tilemaps and text tags

The 280-byte frame builders address a 32-by-24 halfword screen map and use three
row styles: top, middle and bottom, each with left/middle/right tile IDs. They
clear the region above the frame, the left/right portions of its rows and the
region below it. The interior horizontal strip is filled with the row's middle
tile; it is not an untextured pixel rectangle.

The code upper-clamps dimensions against the remaining screen width/height,
then uses narrowed unsigned coordinates/dimensions. It supplies `(width - 2) * 2`
as a byte count to the middle fill. There is no lower-bound validation for an
arbitrary negative origin, too-small width or out-of-range height. These are
caller contracts, not safe clipping guarantees. Preserve them in matching C;
make any deliberate host-side validation policy separately reviewable.

The two 112-byte tag callbacks handle:

| Tag | Effect |
|---|---|
| `1` | Set text color `0xf2`. |
| `2` | Use the work owner's highlight-color halfword. |
| `4` | Set text color `0xfa`. |
| `0x1f` | Measure the following line, center it and advance vertically. |

For `0x1f`, area width is the character canvas width multiplied by eight. The
new X is `(areaWidth + 1) / 2 - (lineWidth + 1) / 2`; Y advances by canvas vSpace
plus the font linefeed. Unknown tags leave these fields unchanged. Tag 2 relies
on the correct `cbParam` work owner. The two copies retain their distinct
line-measurement aliases; the names do not prove the helpers interchangeable.

## Character upload scheduling and shadow text

The two 92-byte upload routines use the persistent menu work owner. They skip
both upload and renderer update when paused, and also skip when the low parity
bit differs between stored work parity and the VBlank callback word. When upload
is enabled they copy `0x2400` bytes into `G2_GetBG1CharPtr() + 0x140`. The source
is the work-owned character buffer, not an independent allocation.

The renderer's busy word is tested only before calling its update routine.
It does not guard the preceding character copy. Suppressing the copy does not
suppress an otherwise eligible idle-renderer update. The routines add no local
interrupt masking or host synchronization.

The item-grid and enemy-viewer shadow helpers each draw text twice: first at
`(x + 1, y + 1)` with `color + 1` in both color slots, then at the requested
position with the caller's two colors. The second-color parameter is now named `altColor`, replacing the misleading
`flags` name without changing its type or expressions. That worker uses the project's custom tagged-text/color callback path.
Do not substitute an ordinary host text renderer and lose its tag semantics.

## Message containers, captions and sprite owners

| Loader | Number of owners | First owner relative to work |
|---|---:|---:|
| Report top | 3 | `+0x04` |
| Story report | 3 | `+0x18` |
| Theater report | 2 | `+0x10` |

These loaders iterate the existing resource-path tables with mode `0x0e` and
`allocFromEnd = FALSE`. They neither free an existing owner before replacement
nor validate each returned handle. The story loader's private prefix view is now named `StoryReportMessageWorkView`;
its old `Ov101State` name did not identify its overlay or full allocation.
Other private placeholder views likewise require their own recovered layout. Container owners are distinct from borrowed packed entries.

The overlay-88 caption initializes one text layer from packed
`ui/menu/str/&/cd.s.z` entry zero, draws at `(4, 0)`, uploads it and dirties layer
`0x1a`. The name deliberately does not expand the asset abbreviation `cd` into
a guessed gameplay role. Its destructor releases the packed owner at `+0x34`
then destroys the Fnd object list. The actual release operation writes through
a `void **` owner slot; the old erased declaration does not establish a new
buffer type or transfer ownership of borrowed entries.

The story-report sprite initializer clears a `0x2c`-byte prefix, loads a resource
owner at `+0x28` with flags `0x11` and rebinds using the existing selector values `(1, 1, 0)`. The paired release function frees/clears that owner
and clears only the upper three bits of byte `+0x26`, then returns one. It does
not clear the whole sprite or define every packed flag field.

## Enemy viewer, theater and record clients

The enemy-viewer initializer establishes global work, clears its observed work
region, loads progress/messages/graphics, creates slots and model-viewer state,
and enters mode one. Its paired destructor releases these systems in the
existing sequence, resets SDK base rotation/dirty state and
clears the global work pointer. This is not a complete renderer-state backup
and restore contract.

`LoadEnemyViewerSelectionModels` releases previous selection models when the
stored selection is nonnegative. It clears and initializes each `0x104`-byte
model from the selected resource list, selects all five animation tracks,
attaches the models, stores the new selection and applies its pose. Valid
selection/list counts and model capacity remain upstream contracts.

The theater initializer restores a nonnegative selection, clears its observed
work, loads the resource systems, draws entries and enters phase two. Its slot
helper initializes the manager from container entry `0x0d` and creates twelve
slots using the existing `0x14`-byte descriptor stride. Neither operation proves
a complete slot-descriptor or work schema.

The record-group counter sums preceding group sizes and counts set session bits
starting at `0x581 + baseIndex`. Group/index validation is not present. The
record-statistics refresh clears its text context, dirties the established
layer/tracker row and draws rows zero through three. The remaining two callbacks
save options before closing the config menu, or draw/upload one indexed choice
window. Their ordering and fixed draw flags stay unchanged.

## Reproduction

Run from `eu/`; the EU wrappers retain their original shared-source include
paths and macro identities:

```sh
python tools/rebuild_index.py --write --refresh-reloc-names
python tools/verify_idx.py src/overlays/ov075/calls/LoadItemPickerTextureDrawParams.c LoadItemPickerTextureDrawParams --thumb
python tools/verify_idx.py src/overlays/ov075/calls/LoadItemPickerMenuTipImages.c LoadItemPickerMenuTipImages --thumb
python tools/verify_idx.py src/overlays/ov075/calls/DrawItemPickerTexturedQuad.c DrawItemPickerTexturedQuad --thumb
python tools/verify_idx.py src/overlays/ov075/calls/BuildItemPickerFrameTilemap.c BuildItemPickerFrameTilemap --thumb
python tools/verify_idx.py src/overlays/ov075/calls/HandleItemPickerTextTag.c HandleItemPickerTextTag --thumb
python tools/verify_idx.py src/overlays/ov076/calls/UpdateSlotMenuCharUpload.c UpdateSlotMenuCharUpload --thumb
python tools/verify_idx.py src/overlays/ov097/calls/LoadStoryReportMessageContainers.c LoadStoryReportMessageContainers
python tools/verify_idx.py src/overlays/ov099/calls/InitEnemyViewerScreen.c InitEnemyViewerScreen
python tools/verify_idx.py src/overlays/ov103/calls/InitTheaterReportScreen.c InitTheaterReportScreen
bash tools/gate.sh
```

All 35 direct official byte/relocation checks pass. The 73 reviewed production
functions retain instructions, resolved relocation targets/types and addends.
The fresh official gate passes all 108 linked modules, with every module hash
unchanged. Naming and the local identifier corrections add no C or DATA
reconstruction credit.
