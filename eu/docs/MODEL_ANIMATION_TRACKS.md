# Model animation tracks and native frame updates

The common `src/animation/ModelAnimation.h` describes three established helpers
and the prefixes they use. These are borrowed views, not complete model or SDK
allocation types. Matching arithmetic and caller conversions are preserved.

## Evidence and names

| Previous symbol | Current name | Direct behavior and consumers |
|---|---|---|
| `func_01ffb2d4` | `GetModelAnimationTrackState` | Reads an indexed track pointer; bit 4 selects a separate pointer for index zero. `Anim_GetFrame`, the duration getter and frame setter consume its track state. |
| `func_01ffb2f8` | `SetModelAnimationFrameWithSingleWrap` | Stores a frame and subtracts one duration when it is at least that duration. Title, panel, stage-item and path-model callers use it to set animation frames. |
| `func_0202f4cc` | `GetModelAnimationDurationFx32` | Reads the bound resource's unsigned halfword frame count and shifts it left by 12. Turning animation, title animation and path-model callers use it as a duration/last-frame bound. |
| `func_ov001_02080a38` | `SetActiveModelAnimationFrames` | Visits five signed halfword track selectors at state `+0xd8`; applies the same frame only where a selector is positive. |

## Lookup origin and prefixes

The lookup's `state` argument is the origin of its animation-flags view. It can
be inside a larger object: `PlayActorTurnAnimation` passes the address of the
model's `animationFlags`, not the beginning of its enclosing model. Other
callers use model/animation storage whose view already starts at that origin.
Do not replace all such pointers with the same complete host model type.

| Offset from lookup origin | Read |
|---|---|
| `0x00` | `u16` flags; mask `4` enables the special index-zero binding. |
| `0x0c + index * 4` | Normal borrowed track pointer. |
| `0xcc` | Alternate pointer used only when mask `4` is set and index is zero. |

Other indices keep the normal table even with mask `4` set. There is no index,
null-state or allocation-bounds check. No complete table capacity follows from
this accessor alone; the separate active-track loop visits exactly five slots.

The recovered track prefix has `fx32 frame` at `+0`, an uninterpreted word at
`+4`, and its resource pointer at `+8`. The resource prefix's frame count is
`u16` at `+4`; its preceding word remains uninterpreted. Offset checks enforce
the observed DS layout. Nothing here validates a resource format or establishes
the full size of either allocation.

The track getter returns a borrowed mutable pointer. The frame setter returns
that same pointer, including null for an unbound track. Its non-null path
assumes a valid resource pointer. The duration getter returns zero for an
unbound track; this is indistinguishable from a bound zero-frame resource by
that result alone. It performs no null-resource validation on a bound track.

## Frame arithmetic

Frames and durations use twelve fractional bits. The resource count itself
counts whole frames; the getter returns `frameCount << 12`, not the last frame.
For example, title and path callers explicitly subtract `0x1000` to select the
last whole frame.

The setter is a **single subtraction**, not modulo and not clamping:

```c
track->frame = frame;
if (frame >= duration) {
    track->frame = frame - duration;
}
```

Negative frames remain negative. Values at least twice the duration can remain
outside one cycle. A zero duration is not a special error path: subtraction
leaves the stored value unchanged. Preserve signed comparisons and native
32-bit arithmetic rather than substituting host unsigned modulo or clamping.

`SetActiveModelAnimationFrames` tests `s16 > 0`, not nonzero, and makes five
calls at most. Zero and negative selectors are skipped. This selector table is
relative to that function's own state argument; it is not extra storage in the
12-byte track prefix. The common frame setter still owns lookup and single-wrap
behavior for each selected track.

## Native consumers and port boundary

Six native consumers now include the same header: `UpdateTitlePanel`,
`PlaceSlotPanelAtWorldPosition`, `PlayActorTurnAnimation`,
`SetScenePanelAnimation`, `SpawnStageResourceItem` and `StepEntryPathModel`.
This removes pointer-shaped integer returns and the setter's obsolete extra
lookup argument. `PlaceSlotPanelAtWorldPosition` passes its panel pointer
without converting it to a DS integer.

The old declarations in `SetScenePanelAnimation` and `SpawnStageResourceItem`
narrowed loop indices to `u16`. The shared helper now exposes its real signed
integer lookup index, so those two callers retain the conversion explicitly as
`(u16)i`. This preserves their generated instructions and calling convention.
Other included shared-region caller templates keep their original views behind
EU aliases; normalize them deliberately before adopting a host-wide interface.

Use native host pointers for the bound tracks/resources in a port. The DS byte
strides and interior-pointer origins describe existing storage, not serialized
host pointers or a complete replacement engine object. Establish resource
lifetime separately; these helpers neither retain nor free the bound objects.

## Reproduction

From `eu/`:

```sh
python tools/rebuild_index.py --write --refresh-reloc-names
python tools/verify_idx.py src/calls/GetModelAnimationTrackState.c GetModelAnimationTrackState
python tools/verify_idx.py src/calls/SetModelAnimationFrameWithSingleWrap.c SetModelAnimationFrameWithSingleWrap
python tools/verify_idx.py src/calls/GetModelAnimationDurationFx32.c GetModelAnimationDurationFx32
python tools/verify_idx.py src/overlays/ov001/calls/SetActiveModelAnimationFrames.c SetActiveModelAnimationFrames --thumb
bash tools/gate.sh
```

These function sizes remain 36, 48, 32 and 40 bytes. The six typed native
consumers also pass their direct official byte/relocation checks. Full linked
verification covers all affected caller bindings and DATA across 108 modules.
Names and recovered interfaces add no reconstruction credit.
