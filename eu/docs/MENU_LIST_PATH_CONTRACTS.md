# Menu list path, cursor and highlight contracts

This document records 10 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

The menu wrapper owns an embedded list at work +0x64f4. The list contains a three-pointer path array at +0x70, scroll position at +0x94, cursorIndex at +0xa4 and selected/highlight index at +0xa8. These names follow the matched input view and readers, rather than conflicting private field labels.

The path is a parent/child graph with at most three stored path nodes. Its count includes the root and is therefore 1..4, including 1 when all three pointers are NULL. The list-level count and its menu wrapper report that same value; the current native wrapper declaration says `void` even though a field caller consumes its integer result. A port must correct that interface from the caller/callee evidence, not infer a void result from the wrapper text.

Cursor depth is derived from the row's horizontal `tileX` halfword at row +2: `(tileX - 2) / 16`, with signed division lowering. It is not a screen-Y row number. Path-node IDs are halfwords at node +4, distinct from parent/child row fields at +6/+8. The direct ID getter has no bounds or NULL check.

Highlight placement stores selectedIndex and refreshes overlay-cell positions. Cursor placement moves the dedicated cursor cell without assigning selectedIndex or rebuilding the path. Path changes may redraw rows and call onChange; the scroll wrappers also inherit callback and scrolling effects from their callees. All list/path pointers are borrowed from their owner.

This block assigns no gameplay meaning to graph IDs, availability states or callback payloads. Related old labels such as `ResetMenuLayerTransforms` are not evidence of transforms: that separately tracked helper uploads BG2/BG3 screen buffers. Its semantic correction is outside this inventory.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov025:020b6184` | THUMB | `func_ov025_020b6184` | `ScrollMenuListDownOneRow` | [eu/src/overlays/ov025/calls/ScrollMenuListDownOneRow.c](../src/overlays/ov025/calls/ScrollMenuListDownOneRow.c) |
| `ov025:020b619c` | THUMB | `func_ov025_020b619c` | `ResetMenuListToFirstEntry` | [eu/src/overlays/ov025/calls/ResetMenuListToFirstEntry.c](../src/overlays/ov025/calls/ResetMenuListToFirstEntry.c) |
| `ov025:020b6330` | THUMB | `func_ov025_020b6330` | `GetMenuListPathEntryCount` | [eu/src/overlays/ov025/calls/GetMenuListPathEntryCount.c](../src/overlays/ov025/calls/GetMenuListPathEntryCount.c) |
| `ov025:020b65e4` | THUMB | `func_ov025_020b65e4` | `RebuildListEntryStatesAndRedraw` | [eu/src/overlays/ov025/calls/RebuildListEntryStatesAndRedraw.c](../src/overlays/ov025/calls/RebuildListEntryStatesAndRedraw.c) |
| `ov025:020b6850` | THUMB | `func_ov025_020b6850` | `TryChangeListPathAtEntry` | [eu/src/overlays/ov025/calls/TryChangeListPathAtEntry.c](../src/overlays/ov025/calls/TryChangeListPathAtEntry.c) |
| `ov025:020b6cc0` | THUMB | `func_ov025_020b6cc0` | `SetListHighlightEntry` | [eu/src/overlays/ov025/calls/SetListHighlightEntry.c](../src/overlays/ov025/calls/SetListHighlightEntry.c) |
| `ov025:020b6d20` | THUMB | `func_ov025_020b6d20` | `SetListCursorEntry` | [eu/src/overlays/ov025/calls/SetListCursorEntry.c](../src/overlays/ov025/calls/SetListCursorEntry.c) |
| `ov025:020b74dc` | THUMB | `func_ov025_020b74dc` | `GetListCursorDepth` | [eu/src/overlays/ov025/calls/GetListCursorDepth.c](../src/overlays/ov025/calls/GetListCursorDepth.c) |
| `ov025:020b74f8` | THUMB | `CountActiveSlots` | `GetListPathEntryCount` | [eu/src/overlays/ov025/calls/GetListPathEntryCount.c](../src/overlays/ov025/calls/GetListPathEntryCount.c) |
| `ov025:020b7650` | THUMB | `func_ov025_020b7650` | `GetListPathNodeId` | [eu/src/overlays/ov025/auto/GetListPathNodeId.c](../src/overlays/ov025/auto/GetListPathNodeId.c) |

## ScrollMenuListDownOneRow

Identity: `ov025:020b6184`, THUMB, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov025_020b6184`.

EU entrypoint: [eu/src/overlays/ov025/calls/ScrollMenuListDownOneRow.c](../src/overlays/ov025/calls/ScrollMenuListDownOneRow.c).

```c
void ScrollMenuListDownOneRow(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Passes the exact menu work pointer +0x64f4 to ScrollListDownOneRow. Source: [eu/src/overlays/ov025/calls/ScrollMenuListDownOneRow.c:1-8](../src/overlays/ov025/calls/ScrollMenuListDownOneRow.c).
- The callee advances to the next path entry when not busy, rebuilds the path, moves cursor/highlight and sets a clamped scroll target. Source: [src/ov025/status_menu/ScrollListDownOneRow_020b72e8.c:1-80](../../src/ov025/status_menu/ScrollListDownOneRow_020b72e8.c).

Contract limits:

- The receiver is the list embedded in data_ov025_020b7780, not a global generic list.

## ResetMenuListToFirstEntry

Identity: `ov025:020b619c`, THUMB, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov025_020b619c`.

EU entrypoint: [eu/src/overlays/ov025/calls/ResetMenuListToFirstEntry.c](../src/overlays/ov025/calls/ResetMenuListToFirstEntry.c).

```c
void ResetMenuListToFirstEntry(void);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Passes menu work+0x64f4 to ResetListToFirstEntry. Source: [eu/src/overlays/ov025/calls/ResetMenuListToFirstEntry.c:1-8](../src/overlays/ov025/calls/ResetMenuListToFirstEntry.c).
- The callee selects entry zero, rebuilds path, repositions list cells and schedules scrolling. Source: [src/ov025/status_menu/ResetListToFirstEntry_020b74f0.c:1-61](../../src/ov025/status_menu/ResetListToFirstEntry_020b74f0.c).

Contract limits:

- Also inherits the callee callback and scrolling effects.

## GetMenuListPathEntryCount

Identity: `ov025:020b6330`, THUMB, native extent 24 bytes (including any configured pool). Previous symbol: `func_ov025_020b6330`.

EU entrypoint: [eu/src/overlays/ov025/calls/GetMenuListPathEntryCount.c](../src/overlays/ov025/calls/GetMenuListPathEntryCount.c).

```c
void GetMenuListPathEntryCount(void);
```

The native `void` declaration is contradicted by the consumed integer result. The semantic result is the root-inclusive path count 1..4; no prototype change is included in this rename plan.

Demonstrated behavior and evidence:

- Calls CountActiveSlots on menu work+0x64f4; its return word is consumed by GetPartySize. Source: [eu/src/overlays/ov025/calls/GetMenuListPathEntryCount.c:1-8](../src/overlays/ov025/calls/GetMenuListPathEntryCount.c).
- Counts leading nonnull pointers in the three-element path array, then adds one. Source: [src/ov025/leaf_research/CountActiveSlots_020b74d8.c:1-12](../../src/ov025/leaf_research/CountActiveSlots_020b74d8.c).
- The field caller returns this wrapper result in the alternate list-controlled party mode. Source: [src/ov001/unclassified_helpers/GetPartySize_0207b590.c:1-25](../../src/ov001/unclassified_helpers/GetPartySize_0207b590.c).

Contract limits:

- The existing void prototype hides a consumed integer result.
- The count includes the root entry and is in 1..4, not a count of arbitrary active slots.

Additional native ABI observations:

- A real integer return is justified by caller use; keep byte-exact matching when repairing the interface.

## RebuildListEntryStatesAndRedraw

Identity: `ov025:020b65e4`, THUMB, native extent 618 bytes (including any configured pool). Previous symbol: `func_ov025_020b65e4`.

EU entrypoint: [eu/src/overlays/ov025/calls/RebuildListEntryStatesAndRedraw.c](../src/overlays/ov025/calls/RebuildListEntryStatesAndRedraw.c).

```c
void RebuildListEntryStatesAndRedraw(ListPanel *panel, int arg1, int arg2);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Rebuilds entry/node availability states from cursor depth, level limit and selected path; rebuilds the path and redraws rows with state-dependent tiles/palettes. Source: [eu/src/overlays/ov025/calls/RebuildListEntryStatesAndRedraw.c:1-149](../src/overlays/ov025/calls/RebuildListEntryStatesAndRedraw.c).
- Native matched touch view proves tileX +2, cursorIndex +0xa4 and selectedIndex +0xa8. Source: [eu/src/overlays/ov025/SlotListTouch.h:1-52](../src/overlays/ov025/SlotListTouch.h).
- Reconstructs up to three linked path nodes using preferred and available entries. Source: [src/ov025/status_menu/RebuildSlotChain_020b63d0.c:1-79](../../src/ov025/status_menu/RebuildSlotChain_020b63d0.c).

Contract limits:

- The private selectedIndex member at +0xa4 is the cursorIndex in the native matched header.
- The private y at entry+2 is tileX, used for horizontal path depth; do not export the old misleading field names.
- The callback/chain rebuild arguments are forwarded unchanged.

## TryChangeListPathAtEntry

Identity: `ov025:020b6850`, THUMB, native extent 648 bytes (including any configured pool). Previous symbol: `func_ov025_020b6850`.

EU entrypoint: [eu/src/overlays/ov025/calls/TryChangeListPathAtEntry.c](../src/overlays/ov025/calls/TryChangeListPathAtEntry.c).

```c
BOOL TryChangeListPathAtEntry(ListPanel *panel, int row);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Checks that the requested entry is deeper than the cursor and connected to the current parent; updates the path, redraws affected rows and invokes onChange when successful. Source: [eu/src/overlays/ov025/calls/TryChangeListPathAtEntry.c:1-145](../src/overlays/ov025/calls/TryChangeListPathAtEntry.c).
- Separates cursorIndex +0xa4 from selectedIndex +0xa8. Source: [eu/src/overlays/ov025/SlotListTouch.h:1-52](../src/overlays/ov025/SlotListTouch.h).
- The selection wrapper moves the highlight first, then changes the path only if the entry state is selectable. Source: [src/ov025/status_menu/TrySelectListEntry_020b6d10.c:1-24](../../src/ov025/status_menu/TrySelectListEntry_020b6d10.c).

Contract limits:

- Returns false for invalid depth, missing parent or no matching edge.
- Private selectedIndex +0xa4 means cursorIndex, not current highlight selection.
- The parent/child graph and three-level limit are proven; no story/menu domain is inferred.

## SetListHighlightEntry

Identity: `ov025:020b6cc0`, THUMB, native extent 94 bytes (including any configured pool). Previous symbol: `func_ov025_020b6cc0`.

EU entrypoint: [eu/src/overlays/ov025/calls/SetListHighlightEntry.c](../src/overlays/ov025/calls/SetListHighlightEntry.c).

```c
void SetListHighlightEntry(ListView *list, int entryIndex);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Places the highlight cell at the requested entry, stores selectedIndex and updates all overlay-cell positions using scroll/base X. Source: [eu/src/overlays/ov025/calls/SetListHighlightEntry.c:1-44](../src/overlays/ov025/calls/SetListHighlightEntry.c).
- Native view identifies selectedIndex +0xa8 and scrollPos +0x94. Source: [eu/src/overlays/ov025/SlotListTouch.h:1-52](../src/overlays/ov025/SlotListTouch.h).
- The placement helper derives cell coordinates from tile coordinates and calls SetWidgetPosition. Source: [src/ov025/status_menu/PlaceCellAtListEntry_020b6c68.c:1-45](../../src/ov025/status_menu/PlaceCellAtListEntry_020b6c68.c).

Contract limits:

- Also refreshes overlay positions; it is not only an index assignment.

## SetListCursorEntry

Identity: `ov025:020b6d20`, THUMB, native extent 16 bytes (including any configured pool). Previous symbol: `func_ov025_020b6d20`.

EU entrypoint: [eu/src/overlays/ov025/calls/SetListCursorEntry.c](../src/overlays/ov025/calls/SetListCursorEntry.c).

```c
void SetListCursorEntry(ListView *list, int entryIndex);
```

Native source view: void result. Apply the callback or tail-forwarding qualifications below before designing a portable signature.

Demonstrated behavior and evidence:

- Places the dedicated cursor cell at the requested list entry. Source: [eu/src/overlays/ov025/calls/SetListCursorEntry.c:1-13](../src/overlays/ov025/calls/SetListCursorEntry.c).

Contract limits:

- Does not assign selectedIndex or change the path.

## GetListCursorDepth

Identity: `ov025:020b74dc`, THUMB, native extent 26 bytes (including any configured pool). Previous symbol: `func_ov025_020b74dc`.

EU entrypoint: [eu/src/overlays/ov025/calls/GetListCursorDepth.c](../src/overlays/ov025/calls/GetListCursorDepth.c).

```c
u32 GetListCursorDepth(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Returns (table.rows[cursorIndex].tileX - 2)/16 using signed division lowering. Source: [eu/src/overlays/ov025/calls/GetListCursorDepth.c:1-16](../src/overlays/ov025/calls/GetListCursorDepth.c).
- The native matched view proves cursorIndex +0xa4 and tileX at row+2. Source: [eu/src/overlays/ov025/SlotListTouch.h:1-52](../src/overlays/ov025/SlotListTouch.h).

Contract limits:

- Reads +0xa4 cursorIndex, not +0xa8 selectedIndex.
- Depth follows the horizontal layout coordinate; it is not a screen Y row.

## GetListPathEntryCount

Identity: `ov025:020b74f8`, THUMB, native extent 22 bytes (including any configured pool). Previous symbol: `CountActiveSlots`.

EU entrypoint: [eu/src/overlays/ov025/calls/GetListPathEntryCount.c](../src/overlays/ov025/calls/GetListPathEntryCount.c).

```c
int GetListPathEntryCount(u32 entity);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- Counts up to three leading nonnull path nodes and returns that count plus one. Source: [src/ov025/leaf_research/CountActiveSlots_020b74d8.c:1-12](../../src/ov025/leaf_research/CountActiveSlots_020b74d8.c).
- The same array at +0x70 contains the three parent-linked path entries. Source: [src/ov025/status_menu/RebuildSlotChain_020b63d0.c:1-79](../../src/ov025/status_menu/RebuildSlotChain_020b63d0.c).

Contract limits:

- The old active-slot name obscures the root-inclusive path count.
- Returns 1 even if all three path pointers are null.

## GetListPathNodeId

Identity: `ov025:020b7650`, THUMB, native extent 10 bytes (including any configured pool). Previous symbol: `func_ov025_020b7650`.

EU entrypoint: [eu/src/overlays/ov025/auto/GetListPathNodeId.c](../src/overlays/ov025/auto/GetListPathNodeId.c).

```c
u32 GetListPathNodeId(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
```

Native source view: register-word slots or placeholder parameter labels remain. The behavior/evidence below defines the proven inputs and result; unused slots are not additional portable parameters.

Demonstrated behavior and evidence:

- Returns the halfword at path[pathIndex]+4, with path pointers stored at list+0x70. Source: [src/ov025/leaf_research/func_ov025_020b7630.c:1-8](../../src/ov025/leaf_research/func_ov025_020b7630.c).
- The typed node view identifies id+4, parentRow+6, childRow+8; path is the three-pointer array at +0x70. Source: [eu/src/overlays/ov025/calls/RebuildListEntryStatesAndRedraw.c:1-149](../src/overlays/ov025/calls/RebuildListEntryStatesAndRedraw.c).

Contract limits:

- No null or index guard exists in the helper.
- The node ID is distinct from parent/child entry indices at +6/+8.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov025/calls/ScrollMenuListDownOneRow.c ScrollMenuListDownOneRow --thumb
python tools/verify_idx.py src/overlays/ov025/calls/ResetMenuListToFirstEntry.c ResetMenuListToFirstEntry --thumb
python tools/verify_idx.py src/overlays/ov025/calls/GetMenuListPathEntryCount.c GetMenuListPathEntryCount --thumb
python tools/verify_idx.py src/overlays/ov025/calls/RebuildListEntryStatesAndRedraw.c RebuildListEntryStatesAndRedraw --thumb
python tools/verify_idx.py src/overlays/ov025/calls/TryChangeListPathAtEntry.c TryChangeListPathAtEntry --thumb
python tools/verify_idx.py src/overlays/ov025/calls/SetListHighlightEntry.c SetListHighlightEntry --thumb
python tools/verify_idx.py src/overlays/ov025/calls/SetListCursorEntry.c SetListCursorEntry --thumb
python tools/verify_idx.py src/overlays/ov025/calls/GetListCursorDepth.c GetListCursorDepth --thumb
python tools/verify_idx.py src/overlays/ov025/calls/GetListPathEntryCount.c GetListPathEntryCount --thumb
python tools/verify_idx.py src/overlays/ov025/auto/GetListPathNodeId.c GetListPathNodeId --thumb
bash tools/gate.sh
```

All entrypoints in this document pass their official function checks. The
combined106-entrypoint block passes the fresh108-module gate; affected function
bytes, resolved relocation targets/types and addends, and all module hashes
match the preserved pre-rename baseline. No algorithm, signature or native
matching-policy change is included. Verified-library receipts remain current.
