# Explicit stage resource-ID predicate

`IsStageResourceId70To97Or99` is ov001:0209d08c, Thumb, 28 bytes. The
definition remains `BOOL(u32 id)`. For every possible unsigned 32-bit
input, it returns canonical TRUE exactly for the inclusive range 70..97
or the separate value 99, and canonical FALSE otherwise. It reads no
memory and has no allocation, mutation or ownership effect.

The native comparison with 99 is followed by unsigned lower/upper range
branches: BHS after comparing 70 and BHI after comparing 97. The name is
a complete statement of that predicate over its actual argument domain.
It does not assign a Boss, Special or another unproved gameplay family.

## Same resource-ID domain in the callers

`StartStageEvent` passes the remapped member/resource ID into this
predicate and passes that same ID and its result into
`SpawnStageResourceTree`. The latter uses type&0x1ff for resource lookup
through manager+0x18e00. `CreateStageManager` loads en/pa/DD.p2f into that
same archive slot. The result also feeds the event-initialization flag
at actor+6 bit0x100 through `InitializeActorStats`; this document assigns
no universal gameplay meaning to that field.

`RefreshStageEventDisplay_02093330` passes event.objectId at +0xe. Its
display-style branch separately excludes 99 before testing the predicate.
Therefore a true predicate result alone does not mean that the style
branch will run. `ApplyHitToEnemyGroup` passes its group.kind and uses
the result to control a session counter 0x1b increment. That selector does
not establish the counter's gameplay meaning.

## Asset extent is not an API bound

The current en/pa/DD.p2f archive contains 100 records named 00.def..99.def.
Its header, FAT, selected entries 69..99 and their hashes have been
checked against the extracted asset using the runtime container readers'
format. This proves numeric resource identity, not a semantic family.
The independent DP stat-table indices and model IDs are not substituted
for these resource IDs.

The count 100 is an observation of this asset. It is not a guard or an
input restriction in the predicate. Inputs 100 through 0xffffffff are
still represented by `u32` and return FALSE. No array bound, enum,
additional condition or runtime validation is introduced.

Original classification purpose, the reason for the separate 99 case,
and any meaningful family name remain unknown. Those questions remain
documented even though the C identifier now states the full proved
operation clearly.

Evidence sources:

- `eu/src/overlays/ov001/calls/IsStageResourceId70To97Or99.c`
- `eu/src/overlays/ov001/calls/StartStageEvent.c`
- `eu/src/overlays/ov001/calls/SpawnStageResourceTree.c`
- `eu/src/overlays/ov001/calls/CreateStageManager.c`
- `eu/src/overlays/ov001/calls/InitializeActorStats.c`
- `eu/src/overlays/ov001/calls/RefreshStageEventDisplay_02093330.c`
- `eu/src/overlays/ov001/calls/ApplyHitToEnemyGroup.c`
- `src/arm9/shared_engine/Msg_OpenContainerAndReadHeader_0202cc6c.c`
- `src/arm9/filesystem/openFileFromNitroRomArchive_0202ce60.c`
- `src/arm9/resource_management/findSharedResourceByName_0202cd8c.c`

Ten complete original functions were compared with the extracted EU ROM.
This proposal changes only the name and leaves formal types, ranges,
constants and body untouched. Official configured-path checks and the
full byte-exact gate remain integration work.


## Active EU sources

- [IsStageResourceId70To97Or99](../src/overlays/ov001/calls/IsStageResourceId70To97Or99.c).

## Byte-exact validation

The following official function checks pass using the EU compiler and mode
from the function index. A fresh `tools/gate.sh` also passes all 108
linked modules. All module hashes, affected production function bytes,
resolved relocation targets/types and addends are unchanged.

Run these commands from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/IsStageResourceId70To97Or99.c IsStageResourceId70To97Or99 --thumb
bash tools/gate.sh
```
