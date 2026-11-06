# Field-script HP and camera-displacement gate

The numeric name is retained. The HP contract closes the record-field question, and
the ov042 getter is now resolved exactly; the intended command-level meaning
of state 4 plus camera displacement is not yet established. The documented contract corrects
the pending ledger without inventing a camera-completion or mission-failure role.

`func_ov001_020656d4` is Thumb, 88 bytes. The same pointer 020656d5 occupies run
and resume slots 92/93, group 2 entry 0x2e, in gFieldScriptCommandHandlers. It reads
no operand descriptors. The return/side-effect cases are:

| Condition | HP read and side effects | Return |
|---|---|---:|
| FieldSessionState != 4 or camera magnitude <= 0 | No HP read; no flag changes | 1 |
| FieldSessionState == 4 and magnitude > 0 and current HP != 0 | Reads primary actor record u16+2; no flag changes | 0 |
| FieldSessionState == 4 and magnitude > 0 and current HP == 0 | Clear packed 0x3525; clear session byte+0x27b6 mask 0x10; set packed 0x3637 | 0 |

The primary actor and its stats are dereferenced without a NULL check. HP 0
does not directly complete the command: both HP branches return 0 under the
state/magnitude gate.

## Corrections and newly resolved evidence

The byte mask is **0x10**, not the old ledger's 0x4. Native 02065704 is
`movs r0,#0x10` (`10 20`), followed at 02065708 by `bics r2,r0` (`82 43`). The
existing C bitfield has four low bits followed by this flag, and already agrees
with ROM. No source repair is needed for this correction.

The actual callee is ov042:020bd39c, Thumb, 24 bytes,
`fx32 GetCameraColliderOffsetMagnitude(void)`. It returns
`VEC_Mag(&gOv042CameraState->colliderOffset)`, where the existing header asserts
colliderOffset at camera work+0x11c. This is a fixed-point vector magnitude,
not an opaque status enumeration. Preserve the exact `> 0` test; no generic
movement/idle interpretation is inferred from that magnitude alone.

RunMenuEntryCallbacks and UpdateHudGauges test the OR of packed 0x3525 and the
same session byte flag for primary/menu 0 palette behavior. Clearing both removes
that keep/skip predicate. StepSessionScriptOrAbort separately tests 0x3637,
session flags+0x214 mask 0x40 and signed request halfword+0x20e==-3; when all
hold it releases the session handle, clears byte+0x2738 and returns 4 to its
caller. That extra guard is part of the observed abort path; setting 0x3637
alone is not proof of a universal failure state.

## Remaining evidence gap

The HP field, vector-magnitude operation, native mask and run/resume binding
are known. What remains is the intended state-4 command/completion contract.
An actual group-2/0x2e script use paired with its state and camera-offset setup
would resolve it. The observed wait and flag changes alone do not justify a
mission-failure or camera-completion name. Repeating the HP-field or raw-global
search does not address this specific gap.

## Active sources and validation

- [func_ov001_020656d4](../src/overlays/ov001/calls/func_ov001_020656d4.c).
- [StepSessionScriptOrAbort](../src/overlays/ov001/calls/StepSessionScriptOrAbort.c).
- [RunMenuEntryCallbacks](../src/overlays/ov001/calls/RunMenuEntryCallbacks.c).
- [UpdateHudGauges](../src/overlays/ov001/calls/UpdateHudGauges.c).
- [GetCameraColliderOffsetMagnitude](../src/overlays/ov042/calls/GetCameraColliderOffsetMagnitude.c).
- [Ov042CameraState](../src/overlays/ov042/Ov042CameraState.h).
- [gFieldScriptCommandHandlers](../src/overlays/ov001/data/tables/gFieldScriptCommandHandlers.c).

Five complete original function bodies were compared unmasked with the EU
ROM; the review also checks both script-table words and exact flag instructions.
The review receipt has SHA-256
`7b47ee70d82fced090dc6fadcde6cf2fa967a4753fd313a531352e3763ef835b`.
This follow-up changes documentation only. Sources, prototypes, layouts,
compiler choices and all 108 last-validated module hashes are unchanged.
