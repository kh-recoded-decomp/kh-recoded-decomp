# Widget indexed-record operations

A widget's existing `WidgetPositionRecord` prefix stores two signed record IDs
at offset `0x14`. The helpers in `WidgetRecordOps.h` apply active-flag, animation
frame and mode operations to those indexed records. They reuse that prefix;
they do not recover another widget allocation size or change widget positioning.

## Names and evidence

| Previous symbol | Current name | Established operation |
|---|---|---|
| `func_ov027_020b9604` | `ClearWidgetRecordActiveBits` | Clears mask `0x02` in each configured indexed record's flags. |
| `func_ov027_020b9640` | `SetWidgetRecordActiveBits` | Sets mask `0x02` in each configured record's flags. |
| `func_ov027_020b967c` | `GetWidgetAnimationFrame` | Queries the first record ID other than `-1`, returning zero when both IDs are absent. |
| `func_ov027_020b96c0` | `SetWidgetAnimationFrame` | Passes the requested frame to each configured record's cell-animation setter. |
| `func_ov027_020b97d8` | `SetWidgetRecordMode` | Stores the low two mode bits in each configured indexed record. |
| `func_0204f23c` | `GetIndexedRecordAnimationFrame` | With a nonnegative index, queries the animation controller at record offset `0x18`; otherwise returns zero. |
| `func_0204f218` | `SetIndexedRecordAnimationFrame` | With a nonnegative index, passes the cell animation at `+0x18` to the SDK frame setter; otherwise returns. |
| `Slot_SetMode2Bit` | `SetIndexedRecordMode` | Replaces the mode word at `+0x74` with `mode & 3`. It does not toggle one bit or OR into the old mode. |

The frame names follow the actual call chain. The setter reaches
`NNS_G2dSetAnimCtrlCurrentFrame` and `SetAnimCtrlCurrentFrameImpl_`, which select
an animation frame array entry by index, validate it against the sequence's
frame count and reset current time on success. The shared SDK file's old
`TickCellAnimation` filename and its `fx32 frames` parameter label do not make
this EU binding an elapsed-time tick. The getter derives the frame index from
the current frame pointer and the sequence frame array, returning `u16`.

The active terminology is inherited from the established indexed helpers;
its exact proven operation here is flags mask `0x02`. This block does not
assign every rendering, interaction or lifetime meaning to that flag.

## Layouts and index contracts

`src/indexed_records/IndexedRecordState.h` describes a DS memory view with the
existing `0x8c` stride. Its size check records that stride, with explicit
unknown regions around the established fields:

| Record offset | Established use |
|---|---|
| `0x18` | Beginning of the SDK cell animation/controller passed to frame helpers. |
| `0x74` | Mode word, replaced with a value in `0..3`. |
| `0x7c` | Flag word; the active helpers modify only mask `0x02`. |

The byte region beginning at `0x18` is not presented as a fully recovered SDK
object type. The record view and widget prefix are DS layout descriptions.
They do not establish the containing pool's capacity, a complete widget size,
or host layouts for SDK objects containing pointers.

Widget mutators visit slot zero, then slot one. The widget-level absent-ID
check is exactly `-1`. Any other negative value is still forwarded to the
indexed helper, whose separate guard ignores all negative indices. Positive
indices have no upper-bound check here: callers must supply indices belonging
to the actual allocated record pool. A readable widget prefix is required;
there is no null-widget check.

The getter stops on the first ID different from `-1`, even if that ID is another
negative number. It does not fall back to the second slot when the indexed
getter returns zero. Examples:

| Widget IDs | Getter behavior |
|---|---|
| `[-1, -1]` | Returns zero without an indexed query. |
| `[-1, 5]` | Queries record 5. |
| `[-2, 5]` | Selects `-2`; indexed query returns zero; record 5 is not queried. |
| `[3, 5]` | Queries record 3 only. |

Zero is also a valid first animation frame, so the getter's return value is not
a found/not-found Boolean. Duplicate IDs cause two mutator calls in slot order;
do not deduplicate them when preserving the SDK's update/callback effects.
The helpers read each ID as they visit it and do not build a separate snapshot.

The wrappers do not create or free widgets or their record arrays. They keep
the current SDK calls, so SDK animation validation/update behavior remains
part of the contract. There is no new local frame-range clamp or conversion
in the indexed setter. Existing UI callers that previously narrowed a frame
to `u16` retain that conversion explicitly before the shared `int` API call.
Do not infer new behavior for out-of-contract full-width frame words from the
misleading fixed-point name in an older SDK view.

## Type and return boundaries

The five widget implementations now share the existing widget prefix and one
public operation header. Thirteen direct EU callers include that header
instead of maintaining private operation declarations. Their casts explicitly
identify the common prefix of their older private widget views; the operations
read that prefix without directly changing it. Shared US-source wrappers still
retain legacy DS argument views through EU aliases.

The five indexed implementations share the same record view and prototypes.
`IndexedRecord_ClearActive` returns void. The existing native return word of
`IndexedRecord_SetActive` is preserved: for a negative index it returns the
base-address word, and otherwise the updated complete flags. The widget
wrapper discards it. This is not a Boolean success contract and cannot be
copied literally to a 64-bit host as a pointer-to-int return convention. Audit
other consumers before choosing a simpler host mutator interface.

For a host port, use the real host widget/record and SDK replacement types.
Express record/member access through those types once their layouts are
established. Keep absent-ID handling, first-selected getter behavior, duplicate
updates, frame selection and the low-two-bit mode replacement distinct from
visibility or object ownership. Replace the DS byte/pointer view deliberately;
copying the `0x8c` layout as a host SDK object would assume pointer sizes and
object types that this block does not establish.

## Matching and reproduction

The two indexed frame helpers retain the original address construction order:
base plus animation offset, then index times record stride. Equivalent direct
member indexing made CodeWarrior emit a different instruction sequence. The
matching source uses the byte-address expression with the recovered stride;
this expresses the same address without inline assembly, extra arguments or
instruction substitutions. The host implementation can use ordinary typed
member access.

From `eu/`, after renaming symbols in an existing checkout:

```sh
python tools/rebuild_index.py --write --refresh-reloc-names
python tools/test_rebuild_index.py -v
python tools/verify_idx.py src/calls/GetIndexedRecordAnimationFrame.c GetIndexedRecordAnimationFrame
python tools/verify_idx.py src/calls/SetIndexedRecordAnimationFrame.c SetIndexedRecordAnimationFrame
python tools/verify_idx.py src/calls/SetIndexedRecordMode.c SetIndexedRecordMode
python tools/verify_idx.py src/calls/IndexedRecord_ClearActive.c IndexedRecord_ClearActive
python tools/verify_idx.py src/calls/IndexedRecord_SetActive.c IndexedRecord_SetActive
python tools/verify_idx.py src/overlays/ov027/calls/ClearWidgetRecordActiveBits.c ClearWidgetRecordActiveBits
python tools/verify_idx.py src/overlays/ov027/calls/SetWidgetRecordActiveBits.c SetWidgetRecordActiveBits
python tools/verify_idx.py src/overlays/ov027/calls/GetWidgetAnimationFrame.c GetWidgetAnimationFrame
python tools/verify_idx.py src/overlays/ov027/calls/SetWidgetAnimationFrame.c SetWidgetAnimationFrame
python tools/verify_idx.py src/overlays/ov027/calls/SetWidgetRecordMode.c SetWidgetRecordMode
bash tools/gate.sh
```

The index refresh is opt-in. It reuses the existing reconstruction's checks of
ROM instructions/relocation targets, masked bytes, sizes, mode and module. It
updates only proven relocation spellings, preserving every indexed byte and
all other historical metadata. Unproven or disagreeing entries are retained;
default `--write` behavior still only adds missing entries. The verifier and
its acceptance rules are unchanged. Tests cover dry runs, removed names with
linked-byte proof, zeroed unproven targets, offset count/order, metadata disagreements, invalid
ROM targets and the existing widespread-disagreement guard.

The five indexed functions retain 36, 36, 24, 36 and 36 bytes. Widget functions
retain 60, 60, 68, 68 and 68 bytes. The position controls still retain 408, 8 and
200 bytes. The official unit checks and fresh full gate must pass, including
all renamed callers across 108 modules. Naming/type recovery adds no C or DATA
reconstruction credit.
