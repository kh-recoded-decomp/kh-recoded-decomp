# Field HUD, menu and message-window helpers

This block names 28 EU helpers from their bodies, real consumers and resource
lifecycles. The inventory was reviewed at EU checkpoint
`d0db6a9d7acc4c9c95c290cbfc0c6dfe087efb0f` and integrated after
`3a5e62a572785bf3ec55d0077923b66c1f8139c9`. It describes native behavior and limits;
the validation section records the official checks for the accepted names.
All 28 entrypoints are Thumb. The source views below are partial and are not
portable host layouts.

## Owners and returned pointers

| Owner | Exact global access | Proven boundary |
|---|---|---|
| Field scene manager | Second word of `data_ov001_020a04c4`, at handle `+4` | HUD buffers, fonts, tasks and the message writer use this manager. `InitFieldManager` obtains framework task work and records this pointer. |
| Field menu | Second word of `data_ov001_020a04d0`, at handle `+4` | Cursor state, entry arrays, active slot and menu counters belong here. |
| Message-window work | Pointer stored in `data_ov001_020a04e4` | Window phase, uploaded resources and cleanup use this separate work object. |
| Subscene panel work | Pointer stored in `data_ov001_020a04e8` | Overlay file work, overlay info, subscene task and panel buffers belong here. |

`GetFieldSceneManager` has no input and returns the manager pointer borrowed from
the first handle. Its legacy native declaration uses an integer word; that does
not make the result an ID or transfer ownership. The other globals are not aliases
for this manager, and equal offsets or private typedef names do not establish
shared ownership.

Evidence: `eu/src/overlays/ov001/calls/InitFieldManager.c`,
`eu/src/overlays/ov001/calls/InitModeHandlerContext.c`,
`eu/src/overlays/ov001/calls/InitFieldPanelScene.c`,
`eu/src/overlays/ov001/MessageWindowState.h`, and the getter's shared body
`src/ov001/shared_engine/func_ov001_0207123c.c` interpreted through its EU alias.

## HUD graphics, fonts and task teardown

`SplitFieldHudIconTilesAndUploadBg3` clears mask `0x8000` at manager `+0x480`,
unpacks character data, and preserves this copy order:

| Source byte range | Destination pointer field |
|---|---:|
| `0x000..0x07f` | manager `+0x460` |
| `0x080..0x0ff` | manager `+0x468` |
| `0x100..0x17f` | manager `+0x464` |

After the cache flush, the remaining payload from byte `0x180` is uploaded to
main BG3 character offset `0x5900`. The palette upload selects one `0x20`-byte
segment from manager `+0x470` and writes it at BG palette offset `0x100`.
The code assumes a valid unpacked payload of at least `0x180` bytes; it does not
return a success result. `ReleaseFieldHudGraphics` releases the embedded record
pool at `+0x1c`, calls `FreeAllocatedBuffers(context)` to free pointers at
`+0x10` and then `+0`, and frees the pointer at `+0x470` and buffer at `+0x614`.
Only `+0x614` is explicitly cleared in this body. The three icon-copy buffers
at `+0x460/+0x468/+0x464` are not freed here; broader scene teardown handles those
allocations separately. The outer manager is not freed by this helper.

The four font resources are loaded and released in the same deliberate order:

| Manager offset | Resource path |
|---:|---|
| `0x9c` | `text/font_eu_10.nftr` |
| `0x78` | `text/font_eu_08.nftr` |
| `0x84` | `text/font_eu_08s.nftr` |
| `0x90` | `text/font_eu_10s.nftr` |

These are the existing 12-byte native `FontResource` wrappers described by
`eu/src/text/FontResources.h`. `LoadFieldSceneFonts` discards the loader's return
word; `ReleaseFieldSceneFonts` releases each backing file buffer through the
existing release/probe helper. Neither wrapper returns allocation status, frees
the manager or clears those resource pointers itself.

`DestroyFieldHudTasks` visits fields in this order:
`+0x418`, `+0x414`, `+0x41c`, `+0x420`, `+0x424`, `+0x428`,
`+0x430`, `+0x434`, `+0x438`.
Only the `+0x430` and `+0x434` calls have local null guards. The fields are not
cleared by this helper. The old empty-argument calls at those guards still pass
the loaded task pointer in native R0; they are not argument-free destruction.

`RefreshFieldHudIconRecords` invokes record callbacks for IDs **10 and 11 in
decimal**, respectively `0x0a` and `0x0b`, in that order. It then calls
`BlendIconTiles` with the manager's `+0x476` value. These are not IDs `0x10` and
`0x11`; the callback business meanings remain unassigned.

## Text, tile upload and loader callbacks

`AdvanceFieldMessageAndCloseWhenDone` calls the typewriter at manager `+0x550`.
The underlying writer reads a `u16` code unit, renders and uploads it, increments
the cursor and returns true. It returns false only when the current unit is zero.
Therefore the close occurs on the next invocation after the last nonzero unit,
not on the invocation that drew it. This establishes one code unit per call,
not a Unicode grapheme, a frame frequency or a general message-container encoding.
An empty UTF-16 fallback alone is not evidence that a nonempty packed-file
string has the same encoding; its actual decoder must establish that separately.

`UploadFieldWidgetSixBySixTileBlock` chooses widget layer selector `0x0b`, saves
the current node, selects the node from source `+0x1c`, sets the field through
`SetFieldAt2C(widget,0x370)`, writes dimensions 6 by 6 and uploads the tile buffer.
It restores the saved node afterward. That does not restore every widget field;
the third argument is forwarded to the tile operation and is not proved to be a
pixel coordinate.

`AllocCopyOrClearBuffer` allocates exactly the requested size, stores the new
pointer through its output argument, then copies source bytes or clears when the
source is null. The function is void and does not check allocation failure, free
a previous output value, or relax the fast-copy/clear helper's preconditions.

The two message-window file callbacks consume the request buffer before calling
`DestroyFileLoadRequest(request,TRUE)`:

- The character callback unpacks the payload and uploads it to main BG3 character
  offset `0x800`, then destroys the request and its owned buffer.
- The palette callback first tests window `+0xf8`. A nonzero word discards the
  request without uploading or opening layers. Otherwise it flushes `0x200` bytes,
  uploads only `0x1a0` bytes to main BG palette offset zero, destroys the request,
  then opens message-window layers using window `+4`. Do not rename `+0xf8` as a
  cancel/pause flag without its writers.

`eu/src/overlays/ov027/FileLoadQueue.h` and `ProcessFileLoadQueue.c` establish the
callback dispatch as `(request,userData)`. Only the request is logically consumed
here; the matched callback bodies still carry additional unused native words.
A request-only description is not a replacement public callback prototype.
Preserve upload-before-buffer-release order when separating renderer and assets.

## Field-menu state and numeric results

`DrawFieldMenuOrPartyGaugeFrames` chooses the menu panel when
`!IsModeSetOrFlag370aClear() || IsHudFlag7Set() || IsFieldFlag10Set()`; otherwise
it chooses party gauge frames. Its forwarded second native word has no newly
proved animation/time role.

`TryCycleFieldMenuCursor` requires the availability word at menu `+0x138`, state
zero, at least two entries, the mode/HUD/field guards and a clear leader-flag
predicate. It sets state 2, clears `+0x108`, preserves the old cursor and calls
`CycleMenuEntry` with selector 2. It returns true only on that transition; no
next/previous direction is inferred from selector 2.
`TryEnterFieldMenuState3` applies its own availability/idle/mode/leader guards,
then returns the result of `FieldMenu_TryEnterState3`, whose additional count and
HUD/field guards precede its state-3 transition.

The array and list views must stay distinct:

| Access | Proven record/data contract |
|---|---|
| menu entries pointer at `+0xac` | `0x3c`-byte records; current `u32` at 0, limit `u32` at 4, ID at 8, value at `0x0c`, state at `0x10`, flags at `0x28`. |
| menu slots pointer at `+0xb0` | `0x3c`-byte records with the compared ID at `0x0c`; the setter searches 14 slots. Equal stride does not make this the entry layout. |
| menu list at `+0xb8` | The selected index at `+0xec` is narrowed to the lookup's `u16`; the selected object's word at `+8` is then narrowed to the getter's `u16` result. |

`IncrementFieldMenuEntryProgress` visits `activeCount` entries only when the field
flag8 predicate permits it. For records with mask `0x10`, it performs the `u32`
increment before comparing with the limit and assigning the limit if larger.
Overflow can wrap before that comparison; this is not an unconditionally
saturating increment and no gameplay unit is assigned to progress.
`FillFieldMenuEntryProgressById` stops at the first matching active entry; state3
leaves it unchanged, otherwise current becomes limit. A missing ID does nothing.

`SetFieldMenuActiveSlotById` clears the selected pointer and its `u16` value, then
sets `+0x114` to 1 when value is zero. For a nonzero value it searches the 14-slot
array; the first matching ID clears the HUD popup, stores that slot and value,
and clears counter `+0x10c`. An absent ID makes no change. No units are inferred
for the value or counter.
`FindFieldMenuEntryValueById` instead searches `entryCount` entries, returning
the first value or -1; it does not filter state/flags. The selected-entry getter
has no local null/index guard and returns a narrowed stored ID, not a list index.

## Message-window cleanup and phase groups

`ReleaseMessageWindowWork` releases the owned object at `+0xd4` when present,
clears that field, frees the buffer at `+0xd0` and clears the global window work
pointer. The body does not free the outer task work or clear `+0xd0`. Its legacy
`FreeSceneListObject()` call still relies on the object pointer in native R0.
The task descriptor and constructor, not its old HUD timer label, establish this
work's lifecycle.

`GetMessageWindowPhaseGroup` maps the internal word at `+0x0c` literally:

| Internal state | Returned group |
|---|---:|
|0|0|
|1, 2, 3|1|
|4|2|
|5, 6|3|
|7|4|
|Other|0|

The returned group is `u32`. This mapping does not prove names such as open,
finished, cancelled or successful for those states.

## Subscene overlay lifecycle

`StartSubsceneOverlayLoad(panel,overlayId)` waits for the existing GX geometry
transfer helper, calls `FS_LoadOverlayInfo(panel+0xa4,0,overlayId)`, then calls
`FS_LoadOverlayImageAsync` with that info and file work at `panel+0x5c`.
The second argument is an overlay ID, not a count. The wrapper is void, discards
the SDK results and does not wait for asynchronous image-load completion.
The historic directory of `WaitForGeometryTransfer` is not evidence of a card
thread operation.

`UnloadSubsceneOverlayAndDestroyTask` does all of its work only when the task
pointer at panel `+0` is nonnull: destroy the task, clear it, end the overlay and
unload its image using info at `+0xa4`. A null task skips the whole operation,
including unloading. It does not return the task destructor's next-object word.

`ReloadSubsceneOverlayAfterFade` calls `StepSubScreenFade` on every invocation.
Only when it returns nonzero does it query `IsFileLoadQueueEmpty`; only when both
are nonzero does it write `+0xdc=-1`, unload the current overlay, start the overlay
whose ID is stored at `+0xd0`, clear `+0x4c` and set phase `+0x30=2`.
The fade can advance while the overlay transition is still blocked; do not turn
this into a no-op until both conditions are ready.

`ReleaseSubscenePanelBuffers` frees the pointer at `+0x1c` without clearing it,
then uses `FreePointerIfSet` on the pointer field at `+0x20`, which does clear it.
`ReleaseSubscenePanelWork` calls task/overlay teardown, releases the buffer array
and those shared buffers, then conditionally frees and clears fields `+4`, `+8`,
`+0x0c`, `+0x10` and `+0x18`. It calls `SetDisplaySetting(0)` and clears the panel
global. The framework owns the outer task-work allocation; this callback does
not free it. Keep the order and the distinction between cleared and uncleared
fields. Empty-argument native free calls consume the loaded pointers in R0.

## Inventory and evidence

The following wrapper paths identify each native bank/address and accepted
name. Shared reference-region bodies are interpreted through their EU aliases. No prototype rewrite
or reconstruction-credit change follows from these names.

| EU identity (Thumb) | Entrypoint | Return and proven limit | Target wrapper |
|---|---|---|---|
| `ov001:0206efac`, 148 B | `SplitFieldHudIconTilesAndUploadBg3` | void; preserve split order 0x460/0x468/0x464, payload offsets and selected palette segment. | `eu/src/overlays/ov001/calls/SplitFieldHudIconTilesAndUploadBg3.c` |
| `ov001:0206f174`, 44 B | `ReleaseFieldHudGraphics` | void; releases children, clears only its 0x614 field and retains the outer manager. | `eu/src/overlays/ov001/calls/ReleaseFieldHudGraphics.c` |
| `ov001:0206f1a0`, 60 B | `LoadFieldSceneFonts` | void; loads font wrappers in 0x9c/0x78/0x84/0x90 order, not a sorted font enum. | `eu/src/overlays/ov001/calls/LoadFieldSceneFonts.c` |
| `ov001:0206f1dc`, 36 B | `ReleaseFieldSceneFonts` | void; releases four backing buffers; no outer free, no local pointer clear. | `eu/src/overlays/ov001/calls/ReleaseFieldSceneFonts.c` |
| `ov001:0206fbec`, 104 B | `DestroyFieldHudTasks` | void; nine task fields, with local null guards only for 0x430/0x434; no field clear. | `eu/src/overlays/ov001/calls/DestroyFieldHudTasks.c` |
| `ov001:0207031c`, 26 B | `AdvanceFieldMessageAndCloseWhenDone` | void; closes only when the typewriter sees the zero terminator on a later invocation. | `eu/src/overlays/ov001/calls/AdvanceFieldMessageAndCloseWhenDone.c` |
| `ov001:0207123c`, 12 B | `GetFieldSceneManager` | borrowed manager pointer, currently an integer native return view; no ownership transfer or input. | `eu/src/overlays/ov001/calls/GetFieldSceneManager.c` |
| `ov001:02073718`, 64 B | `RefreshFieldHudIconRecords` | void; invokes decimal IDs 10 and 11 (0x0a/0x0b), then blends icons. | `eu/src/overlays/ov001/calls/RefreshFieldHudIconRecords.c` |
| `ov001:02073cb0`, 42 B | `AllocCopyOrClearBuffer` | void; output pointer receives the allocation; no allocation-failure or old-buffer release handling. | `eu/src/overlays/ov001/calls/AllocCopyOrClearBuffer.c` |
| `ov001:02075d1c`, 86 B | `UploadFieldWidgetSixBySixTileBlock` | void; selects layer 0x0b, writes 6 by 6 and restores the node; third word remains an opaque tile argument. | `eu/src/overlays/ov001/calls/UploadFieldWidgetSixBySixTileBlock.c` |
| `ov001:020761a4`, 50 B | `DrawFieldMenuOrPartyGaugeFrames` | void; exact mode/HUD/field predicate chooses one of two renderers. | `eu/src/overlays/ov001/calls/DrawFieldMenuOrPartyGaugeFrames.c` |
| `ov001:02077e68`, 140 B | `TryCycleFieldMenuCursor` | BOOL; false leaves local menu state untouched; true enters state 2 with cycle selector 2. | `eu/src/overlays/ov001/calls/TryCycleFieldMenuCursor.c` |
| `ov001:02077ef4`, 72 B | `TryEnterFieldMenuState3` | BOOL; returns the guarded state-3 helper result, not a gameplay-action result. | `eu/src/overlays/ov001/calls/TryEnterFieldMenuState3.c` |
| `ov001:0207865c`, 36 B | `GetSelectedFieldMenuEntryId` | u16; narrows the selected object's u32 ID and the lookup index; neither is a new list-index result. | `eu/src/overlays/ov001/calls/GetSelectedFieldMenuEntryId.c` |
| `ov001:02078680`, 80 B | `IncrementFieldMenuEntryProgress` | void; u32 increment can wrap before the upper-limit comparison. | `eu/src/overlays/ov001/calls/IncrementFieldMenuEntryProgress.c` |
| `ov001:020786d0`, 64 B | `FillFieldMenuEntryProgressById` | void; first active ID match wins; state 3 is left unchanged. | `eu/src/overlays/ov001/calls/FillFieldMenuEntryProgressById.c` |
| `ov001:020788b8`, 88 B | `SetFieldMenuActiveSlotById` | void; zero clears the selection, nonzero searches 14 slots; missing ID leaves it unchanged. | `eu/src/overlays/ov001/calls/SetFieldMenuActiveSlotById.c` |
| `ov001:020789b8`, 64 B | `FindFieldMenuEntryValueById` | s32; first entry value or -1; no state/flag filter. | `eu/src/overlays/ov001/calls/FindFieldMenuEntryValueById.c` |
| `ov001:02078cf8`, 42 B | `UploadMessageWindowBg3CharactersCallback` | void; consumes request buffer, uploads BG3 offset 0x800, then destroys request and buffer. | `eu/src/overlays/ov001/calls/UploadMessageWindowBg3CharactersCallback.c` |
| `ov001:02078d7c`, 92 B | `UploadMessageWindowPaletteCallback` | void; 0xf8 guard can discard; flush 0x200 differs from upload 0x1a0; opens layers after destruction. | `eu/src/overlays/ov001/calls/UploadMessageWindowPaletteCallback.c` |
| `ov001:02079f70`, 16 B | `DrawGridMenuCellsAndEnterState6` | void; calls DrawGridMenuCells with argument 0 and writes state 6 at object+8. | `eu/src/overlays/ov001/calls/DrawGridMenuCellsAndEnterState6.c` |
| `ov001:0207a4a0`, 48 B | `ReleaseMessageWindowWork` | void; releases owned children and clears the global; no outer task-work free. | `eu/src/overlays/ov001/calls/ReleaseMessageWindowWork.c` |
| `ov001:0207a648`, 68 B | `GetMessageWindowPhaseGroup` | u32; exact 0/1/2/3/4 grouping, with default 0 and no inferred phase labels. | `eu/src/overlays/ov001/calls/GetMessageWindowPhaseGroup.c` |
| `ov001:0207a920`, 36 B | `StartSubsceneOverlayLoad` | void; waits for geometry transfer, starts async loading by overlay ID and discards SDK results. | `eu/src/overlays/ov001/calls/StartSubsceneOverlayLoad.c` |
| `ov001:0207a944`, 36 B | `UnloadSubsceneOverlayAndDestroyTask` | void; a null task prevents both destruction and overlay unload. | `eu/src/overlays/ov001/calls/UnloadSubsceneOverlayAndDestroyTask.c` |
| `ov001:0207ab68`, 20 B | `ReleaseSubscenePanelBuffers` | void; frees 0x1c without clearing, but the pointer-field helper clears 0x20. | `eu/src/overlays/ov001/calls/ReleaseSubscenePanelBuffers.c` |
| `ov001:0207abdc`, 58 B | `ReloadSubsceneOverlayAfterFade` | void; fade is stepped every call; panel/overlay mutations require fade-ready and empty queue. | `eu/src/overlays/ov001/calls/ReloadSubsceneOverlayAfterFade.c` |
| `ov001:0207ae58`, 112 B | `ReleaseSubscenePanelWork` | void; releases owned allocations in order, resets display setting, clears global; no outer free. | `eu/src/overlays/ov001/calls/ReleaseSubscenePanelWork.c` |

Primary evidence is each corresponding native body in the table and its
callers. Related contracts are visible in these stable paths:

- `src/ov001/shared_engine/func_ov001_0207123c.c`: getter word and EU alias origin.
- `eu/src/overlays/ov001/calls/InitFieldManager.c` and
  `src/ov001/field_manager/CreateFieldHudWidgets_0206fa74.c`: work owner, buffers
  and paired task-field writes.
- `eu/src/text/FontResources.h` and `eu/src/calls/LoadUtf16FontResource.c`:
  12-byte font wrappers and real loader interface.
- `src/ov001/text_rendering/DrawNextTypewriterGlyph_0206feb4.c`:
  code-unit advance and terminator return.
- `src/ov001/field_manager/FieldMenu_TryEnterState3_02075db8.c`:
  inner transition guards and result.
- `eu/src/overlays/ov027/FileLoadQueue.h` and
  `eu/src/overlays/ov027/calls/ProcessFileLoadQueue.c`: real callback arguments,
  request buffer ownership and dispatch.
- `eu/src/overlays/ov001/calls/InitModeHandlerContext.c`,
  `eu/src/overlays/ov001/calls/InitFieldPanelScene.c`,
  `eu/src/overlays/ov001/data/tables/gFieldHudTimerTaskDescriptor.c` and
  `eu/src/overlays/ov001/data/tables/gFieldHudCounterTaskDescriptor.c`:
  the distinct work owners and registered cleanup callbacks.
- `eu/libs/nitro/fs/calls/WaitForGeometryTransfer.c`: the actual GX wait;
  directory names and old SDK aliases are not a file/card-thread contract.
- `src/ov027/shared_engine/FreePointerIfSet_020ba294.c`: frees and clears a
  pointer field, unlike the direct frees around it.

Native ABI recovery remains separate: use actual pointer arguments and the
loader's callback type, retain unused native words until checked, and do not
promote integer register views or task-destructor residual returns into new
portable interfaces. The checks below establish byte-exact preservation for this naming block.

## Reproducible byte-exact validation

Run from `eu/` with the existing toolchain:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/SplitFieldHudIconTilesAndUploadBg3.c SplitFieldHudIconTilesAndUploadBg3 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldHudGraphics.c ReleaseFieldHudGraphics --thumb
python tools/verify_idx.py src/overlays/ov001/calls/LoadFieldSceneFonts.c LoadFieldSceneFonts --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseFieldSceneFonts.c ReleaseFieldSceneFonts --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DestroyFieldHudTasks.c DestroyFieldHudTasks --thumb
python tools/verify_idx.py src/overlays/ov001/calls/AdvanceFieldMessageAndCloseWhenDone.c AdvanceFieldMessageAndCloseWhenDone --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetFieldSceneManager.c GetFieldSceneManager --thumb
python tools/verify_idx.py src/overlays/ov001/calls/RefreshFieldHudIconRecords.c RefreshFieldHudIconRecords --thumb
python tools/verify_idx.py src/overlays/ov001/calls/AllocCopyOrClearBuffer.c AllocCopyOrClearBuffer --thumb
python tools/verify_idx.py src/overlays/ov001/calls/UploadFieldWidgetSixBySixTileBlock.c UploadFieldWidgetSixBySixTileBlock --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DrawFieldMenuOrPartyGaugeFrames.c DrawFieldMenuOrPartyGaugeFrames --thumb
python tools/verify_idx.py src/overlays/ov001/calls/TryCycleFieldMenuCursor.c TryCycleFieldMenuCursor --thumb
python tools/verify_idx.py src/overlays/ov001/calls/TryEnterFieldMenuState3.c TryEnterFieldMenuState3 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetSelectedFieldMenuEntryId.c GetSelectedFieldMenuEntryId --thumb
python tools/verify_idx.py src/overlays/ov001/calls/IncrementFieldMenuEntryProgress.c IncrementFieldMenuEntryProgress --thumb
python tools/verify_idx.py src/overlays/ov001/calls/FillFieldMenuEntryProgressById.c FillFieldMenuEntryProgressById --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetFieldMenuActiveSlotById.c SetFieldMenuActiveSlotById --thumb
python tools/verify_idx.py src/overlays/ov001/calls/FindFieldMenuEntryValueById.c FindFieldMenuEntryValueById --thumb
python tools/verify_idx.py src/overlays/ov001/calls/UploadMessageWindowBg3CharactersCallback.c UploadMessageWindowBg3CharactersCallback --thumb
python tools/verify_idx.py src/overlays/ov001/calls/UploadMessageWindowPaletteCallback.c UploadMessageWindowPaletteCallback --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DrawGridMenuCellsAndEnterState6.c DrawGridMenuCellsAndEnterState6 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseMessageWindowWork.c ReleaseMessageWindowWork --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetMessageWindowPhaseGroup.c GetMessageWindowPhaseGroup --thumb
python tools/verify_idx.py src/overlays/ov001/calls/StartSubsceneOverlayLoad.c StartSubsceneOverlayLoad --thumb
python tools/verify_idx.py src/overlays/ov001/calls/UnloadSubsceneOverlayAndDestroyTask.c UnloadSubsceneOverlayAndDestroyTask --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseSubscenePanelBuffers.c ReleaseSubscenePanelBuffers --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReloadSubsceneOverlayAfterFade.c ReloadSubsceneOverlayAfterFade --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ReleaseSubscenePanelWork.c ReleaseSubscenePanelWork --thumb
bash tools/gate.sh
```

All 28 official function checks pass. The fresh gate passes all 108 linked
modules; affected function bytes, resolved relocation targets/types and addends,
and all module hashes match the preserved pre-rename baseline.
