# Stage-manager flag access

The first word of the object referenced by `gStageManager` is a 32-bit flag
word. Seven matched operations read, OR or AND it with masks. The recovered
field is now part of the existing partial `StageMotionManager` view in
`StageMotionState.h`, instead of maintaining separate pointer declarations in
these operations. `StageManagerFlags.h` supplies the public operation contracts.

## Evidence and names

| Previous symbol | Current name | Established behavior |
|---|---|---|
| `func_ov001_0209c5ac` (`0x0209c5ac`) | `GetMaskedStageManagerFlags` | Returns `mask & flags`, or zero when there is no manager. |
| `func_ov001_0209c5c4` (`0x0209c5c4`) | `SetStageManagerFlagBits` | ORs the selected bits into the existing flags, if the manager exists. |
| `func_ov001_0209c5d8` (`0x0209c5d8`) | `ClearStageManagerFlagBits` | ANDs the flags with the complement of the mask, if the manager exists. |
| `AllocateActorSlotOrReportError` (`0x02093b08`) | `ClearStageMask30WhenBit0Clear` | If bit 0 is clear, clears mask `0x30` and returns 3; otherwise returns 0. The old label did not describe this EU binding. |

The last name uses `30` for hexadecimal mask `0x30`; it intentionally describes
the proven operation and condition without guessing the gameplay meaning of
bit 0. The function allocates no actor or other object and calls no error
reporter. Its return values remain numeric because their state-machine meaning
has not been established by this block. In particular, 3 is not newly labelled
as an allocation error.

## Layout and value semantics

`gStageManager` is the existing four-byte DS pointer at `0x020a0528`. The flag
word is at offset zero in its pointed-to object. The new field replaces the
first four bytes of padding in the existing partial view. Padding is shortened
by four bytes, keeping `groups` at `0x210` and `setMotionMode` at `0x18f5c`.
This does not establish a complete manager allocation size, all intervening
fields or the meaning of each bit.

The getter returns the selected **bits**, not a normalized Boolean. For
example, flags `0x50` queried with `0x30` return `0x10`. A zero result alone
cannot distinguish an absent manager from a present manager with no selected
bits set. Set/clear preserve all bits outside the mask; they do not replace the
whole word. With a present manager, a zero mask leaves the value unchanged but
the native mutator still performs its read/write operation. With an absent
manager, both mutators return before accessing the pointed-to word.

`ClearStageMask30WhenBit0Clear` also takes its clear-bit path when the manager
is absent: the getter returns zero, the clear mutator does nothing and the
helper returns 3. Preserve this case when expressing its state-machine contract
in a host port; adding a null-manager error would change the observed behavior.

## Related uses and unresolved bits

The matched callers establish where masks are used, without proving universal
names for those bits:

- `UpdateFieldActorMovement` queries `0x20` and `0x10` around movement paths.
- `UpdateStageEvent` queries `0x01`.
- `RunScriptThread` queries `0x40` together with its existing player/scale test.
- `UpdateProximityTrigger` queries `0x01` and `0x40`, and can set `0x10` or
  `0x20` through the same generic bit-setting API.

The four fixed-mask helpers now use the same typed flag field, while retaining
their address names pending stronger evidence about their roles:

| Function | Exact flag operation |
|---|---|
| `func_ov001_0209c440` | Clears `0x31`, retaining the rest. |
| `func_ov001_0209c520` | Clears `0x42`, retaining the rest. |
| `func_ov001_0209c538` | Clears `0x40000000`, retaining the rest. |
| `func_ov001_0209c554` | Sets `0x40000000`, retaining the rest. |

All four skip the operation for a null manager. This block introduces no guessed
pause, ownership, collision or script-state enums for these masks. The generic
accessors' bitwise behavior is established even while individual bit meanings
remain unresolved.

## Guidance for a host port

Use the manager's real host flag field and consistent unsigned-mask signatures.
Keep manager lifetime separate from these nullable accessors: the native null
checks do not validate a stale or otherwise invalid non-null pointer. Preserve
the getter's mask-valued result, unrelated bits, conditional helper return
values and each caller's ordering of separate queries/updates.

The native operations are ordinary read/modify/write accesses; they add no lock
or atomic operation. Choose host synchronization according to the port's actual
threading model. Other subsystems still have partial views of manager storage;
merge those views only where offsets and ownership are established. Do not use
the size of this padded motion view as a recovered allocation contract.

Shared US source identifiers remain in wrappers, bound to these EU names. The
renamed conditional helper is now expressed directly in EU C with the same
public flag prototypes, so its behavior is visible without the misleading
shared-source label.

`gStageScriptStateHandlers` still has a legacy `void (void)` address-table
view for its heterogeneous entries. This helper entry now includes its actual
`int (void)` prototype and uses an explicit function-pointer conversion for
that existing table view, rather than declaring the helper as returning void.
Its 48-byte table and all eleven references are unchanged. Recover a consistent
dispatcher/table interface before treating the legacy erased type as a host
call contract.

## Reproduction

From `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov001/calls/GetMaskedStageManagerFlags.c GetMaskedStageManagerFlags --thumb
python tools/verify_idx.py src/overlays/ov001/calls/SetStageManagerFlagBits.c SetStageManagerFlagBits --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ClearStageManagerFlagBits.c ClearStageManagerFlagBits --thumb
python tools/verify_idx.py src/overlays/ov001/calls/ClearStageMask30WhenBit0Clear.c ClearStageMask30WhenBit0Clear --thumb
python tools/verify_idx.py src/overlays/ov001/calls/func_ov001_0209c440.c func_ov001_0209c440 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/func_ov001_0209c520.c func_ov001_0209c520 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/func_ov001_0209c538.c func_ov001_0209c538 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/func_ov001_0209c554.c func_ov001_0209c554 --thumb
python tools/verify_idx.py src/overlays/ov001/calls/DispatchStageObjectMotions.c DispatchStageObjectMotions --thumb
python tools/verify_idx.py src/overlays/ov001/calls/GetStageManager.c GetStageManager --thumb
python tools/verify_idx.py src/overlays/ov001/calls/StartStageObjectMotions.c StartStageObjectMotions --thumb
python tools/verify_idx.py src/overlays/ov001/calls/UpdateFieldActorMovement.c UpdateFieldActorMovement --thumb
python tools/verify_idx.py src/overlays/ov001/calls/UpdateStageEvent.c UpdateStageEvent --thumb
python tools/verify_idx.py src/overlays/ov021/calls/RunScriptThread.c RunScriptThread --thumb
bash tools/gate.sh
```

The four renamed functions retain 24, 20, 24 and 26 bytes. The typed fixed-mask
helpers retain 24, 24, 28 and 24 bytes; the three motion-view controls retain
124, 12 and 120 bytes. The direct consumers retain 1796, 2124 and 348 bytes.
The fresh linked gate must preserve all 108 modules and the existing global
pointer storage. Naming and field recovery add no C reconstruction credit.
