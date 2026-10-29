# EU contact-motion projection

`func_02034d78` modifies a motion vector using selected collision normals.
The matching implementation is `src/calls/func_02034d78.c`, included in the linked
EU build. It uses the recovered `CollisionContacts` type shared with query
initialization. The superseded nonmatching draft has been removed.

`src/collision/CollisionContacts.h` records only the recovered workspace fields:
sixteen `VecFx32` normals at `0xc0`, the byte at `0x180`, three selected normal
indices at `0x181`, and the projection mode at `0x1a1`. The mode is a distinct
field; interpreting it directly as the number of contacts would be incorrect.
The workspace occupies `0x1a4` bytes in the DS ABI. Remaining fields retain their
offsets and unknown names rather than inferred gameplay meanings.

## Behavior

Let `a`, `b`, and `c` be the selected normals. All coordinates use signed 20.12
fixed point. Multiplication and dot/cross products retain the SDK's integer
rounding, including on negative values; replacing them with floating point
normalization need not give the same results.

| Mode | Result |
|---|---|
| `0` | Leave motion unchanged. |
| `1`, `2` | Clear motion when `abs(dot(a,b)) < 0xff0`; otherwise subtract its component along `a`. |
| `3` | Clear motion when any pair has `abs(dot) > 0xff0`. Otherwise normalize `cross(a,b)` into an axis; clear motion if `abs(dot(axis,c)) > 0x10`, or project motion along that axis. |
| Other values | Clear motion. |

The strict inequalities matter at both thresholds. In particular, equality at
`0xff0` does not trigger either rejection, and equality at `0x10` passes the
axis test. It writes only the motion vector. With distinct motion and workspace
buffers, the workspace is unchanged; motion can also alias a selected normal,
in which case those twelve workspace bytes become the output. Its established
caller `SweepSphereAgainstWorld` applies it to the contact result vector; this
alone does not identify a particular enemy or player action.

The axis used to scale the final result is a saved value; a separate immutable
snapshot is exposed to the dot-product helpers. The matching C keeps those
objects and the helper return values explicit. Its public interface remains
the original two pointers.

## Verification

With CodeWarrior `dsi/1.3p1`, the implementation matches all 528 original bytes
and thirteen relocations through the ordinary verifier. Its public interface is
two pointers, with the contact workspace read through a const view.

```sh
python tools/verify_idx.py src/calls/func_02034d78.c func_02034d78
```

`python tools/test_contact_motion.py -v`, run from `eu/`, separately checks:

- 1,260 inputs against an independent integer model, executing both the ROM ARM
  instructions and the compiled matching C, including their actual SDK vector
  helpers. Modes `0`, `1`, `2`, `3`, `4` and `255`, randomized selected indices,
  negative motion, threshold equality and every modeled outcome are covered.
- 260 SDK normalization inputs against the integer normalization model.
- Unchanged workspace bytes and guards around a separate output vector, plus
  eighteen cases where motion aliases a selected normal.
- The exact bytes written by query initialization, including preserved context
  slots and reserved data.
- Rejection of unsupported arithmetic-unit modes and division by zero.

The test links the implementation's ELF relocations using the symbol addresses and
addends, checks their offsets and targets, and executes the resulting memory
image. It does not alter the object, ROM, index, or production verifier.

## Arithmetic-unit boundary

The original `VEC_Normalize` uses the DS division and square-root units. The test
models functional results for DIV mode 2 (64/64 signed division, restricted here
to a nonnegative numerator and positive denominator) and SQRT mode 1 (unsigned
64-bit input). The register addresses and modes are also documented in the
[libnds math header](https://github.com/blocksds/libnds/blob/master/include/nds/arm9/math.h).

The model completes synchronously. It does not simulate busy durations, interrupt
interference, negative division operands, division by zero or hardware ownership.
Unsupported result reads raise an error. No helper calls or system instructions
are replaced with no-ops. These are functional differential tests, not a hardware
capture or a proof for every possible 32-bit input.

## Query initialization

`CollisionQuery_Init` now uses the same recovered contacts workspace type and
still matches all 120 original bytes. It initializes selected fields rather
than clearing the entire query. The workspace writes reset only bytes `0x180`
and `0x1a1`; the normal vectors and selected indices survive. Query slots
`0x4c`, `0x54` and `0x5c` also survive. Callers that install callbacks must still
provide their context, as the touched-object sweep does.
