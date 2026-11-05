# EU handoff for a future host port

The EU reconstruction is byte-exact within the project's current ARM9 module
scope: main, ITCM, DTCM and 105 overlays. A fresh linked-module gate must keep all
108 modules equal to the reference ROM. At the `35e102237` baseline, C covers
95.98% of code bytes and separately verified libraries cover the other 4.02%.
This is a matching decompilation; a host port is a separate project.

## Start here

- [Collision geometry](COLLISION_GEOMETRY.md), [tree traversal](COLLISION_TRAVERSAL.md),
  [contact motion](CONTACT_MOTION.md) and [sphere/rim sweep](SPHERE_RIM.md)
  describe recovered layouts, fixed-point math, ownership and the relevant
  calling conventions.
- [Symbol evidence](SYMBOL_EVIDENCE.md) records justified semantic renames and
  the recovered traversal workspace, including unresolved overlapping views.
- [Session buffers](SESSION_BUFFERS.md) describes the shared slot record,
  allocation/release ownership and the DS address representation.
- [Captured touch](CAPTURED_TOUCH.md) describes the task-owned input record,
  selection fallback, partial clear and legacy copy interface.
- [Results scene](RESULTS_SCENE.md), [scene loading](SCENE_LOAD_STEP.md),
  [carousel models](CAROUSEL_MODELS.md), [widgets](WIDGET_POSITION.md) and
  [field-menu palette](FIELD_MENU_PALETTE.md) record behavior and the matching
  constraints that a host implementation must interpret explicitly.
- [Portable library references](../portable/README.md) lists C counterparts
  compiled and checked against the original ARM behavior. They are separate
  from matched-C accounting.

These pages cover specific recovered systems. Their existence is not a claim
that every function, data object or subsystem has a complete semantic contract.
An address-based name is retained where a more descriptive name lacks evidence.

## Library boundaries

| Area | Existing contracts | What a host port must provide |
|---|---|---|
| Matrix initialization/conversion | [MI/MTX](library/sdk_mtx.md), [portable C](library/portable_mtx.md) | Fixed-point coefficients, layout and overlap rules; nine C counterparts are available. |
| Memory kernels | [Memory](library/sdk_memory.md), [converted C](library/sdk_c_routines.md) | Copy/fill/move with the documented sizes, alignment and overlap; do not carry DS VRAM read-modify-write rules into ordinary host memory unnecessarily. |
| Runtime arithmetic | [32-bit division](library/msl_runtime.md), [64-bit division](library/msl_div64.md), [float arithmetic](library/msl_float_arith.md), [float conversion](library/msl_float_convert.md) | Equivalent integer/float edge behavior where gameplay depends on it; audit nonstandard register results and flags before replacing a helper with a host operator. |
| BIOS services | [BIOS](library/sdk_bios.md) | Host waits, arithmetic, CRC, transfers and decompression; the game does not contain the BIOS implementation. |
| Threads/startup | [OS](library/sdk_os.md), [miscellaneous](library/sdk_misc.md) | Scheduling, interrupt/event behavior and initialization; DS context layouts and banked ARM registers are not host context objects. |
| Graphics hardware | [GX](library/sdk_gx.md), [converted C](library/sdk_c_routines.md) | A renderer/backend for command submission and completion. |
| Wireless | [Wireless helper](library/sdk_wh.md) | An explicit decision about networking behavior and callbacks; current helper tests stub WM calls and do not emulate radio firmware. |
| Protection | [DS Protect](library/dsprot.md) | Handle its documented protection boundary explicitly; do not transplant encrypted ARM dispatch into the host runtime. |

MobiClip's decoder and kernel models are under `tools/mobiclip/` in the shared
repository. Their verification policy and capture requirements are described
in [PROGRESS_POLICY.md](PROGRESS_POLICY.md). This guide does not certify a host
codec replacement or its integration.

## Changes that need explicit adapters

1. Separate fixed-width ROM layouts from host-owned objects. The existing DS
   layout checks can intentionally reject 64-bit pointers. Keep file/resource
   offsets and addresses as data until resolved by the host loader.
2. Choose consistent function declarations across definitions and callers.
   CodeWarrior structure returns, split 64-bit arguments and runtime helpers
   can have interfaces that differ from the host C ABI.
3. Preserve fixed-point rounding, truncation and overflow behavior deliberately.
   Replacing integer math with floating point or relying on signed C overflow
   can change collision and animation behavior even when results look close.
4. Inventory hardware access in each subsystem before adapting it: registers,
   IRQs, DMA/cache ownership, graphics/audio, filesystem/save, timers and input.
   The library pages are entry points, not a complete game-wide inventory.
5. Treat overlay loading, callbacks and retained pointers as lifetime rules.
   Reconstructed DATA does not by itself establish ownership or make every
   address safe to retain across unloads.
6. Read documented matching exceptions before simplifying them. Source pragmas,
   register bindings and approved steering symbols may be removable in a host
   implementation, while real state updates and aliasing requirements remain.

## Validation and build expectations

The DS byte-matching build retains its per-file CodeWarrior, GCC, Clang and
ARMCC selections. Free-compiler alternatives should be preferred when they
reproduce the original bytes; changing a compiler selection still requires the
per-function verifier and complete linked gate. Portable counterparts have
their own free-compiler behavior tests and must not be counted as byte matches.

When handing off a subsystem, provide its public types, inputs and outputs,
buffer ownership, callbacks, supported aliasing and edge cases, hardware
dependencies and a command that checks the implementation against the original
behavior. Preserve uncertainty where the evidence is incomplete. Re-run the
relevant behavior checks and full DS gate when publishing each validated block.
