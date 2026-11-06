# EU kind-4 pool trigger-hit callback table

At ov017 `020a5e5c`, `gKind4PoolTriggerHitHandlers` is a five-pointer constant table. Slots 0–3 are NULL; slot 4 is `FinishPoolActions`. The pool category 4 is the constructor's native category, distinct from the per-object kind values used inside its callbacks.

`ResetPoolDefaultParams` copies four consecutive 20-byte blocks beginning at pool `+0x174`. The fourth block therefore begins at `+0x1b0`. `CreateKind4EntryPool` performs this initialization and installs `HandleFieldObjectActivation` at operations-table offset `+0x1c`.

That installed consumer obtains the pool from object `+4`, takes the trigger pointer at object `+0x60`, and indexes the callback table with the trigger's byte-0 kind. It passes four arguments: the object's work at `+0x70`, the object, the trigger's u16 value at `+2`, and the hit payload. A NULL callback leaves the ordinary path unchanged; a callback returning zero aborts that path with raw status `0x10`. Native instructions at relative `+0x24/+0x26` form `0x1b0`; `+0x28` loads the indexed callback, and `+0x2e..+0x38` prepare arguments and call it.

For selector 4, `FinishPoolActions` uses the trigger argument to select a pool-4 linked-list head. It returns zero when hit `+0x14` is 1. Active camera shake returns one without performing the later reset. Otherwise it processes the linked actions, resets its work state at `+4`, starts the configured effect/sound and returns one. These branch-specific results must be preserved; return one alone does not prove the reset occurred. The gameplay meaning of selector 4 and hit `+0x14` remains numeric.

The short `HitInfo` declaration in one consumer is a partial view: `FinishPoolActions` also reads at `+0x14`. This naming change does not repair prototypes or claim a complete shared hit structure.

Evidence: `src/ov017/data/Rodata_ov017_020a5e5c.c`, `src/overlays/ov017/calls/ResetPoolDefaultParams.c`, `src/overlays/ov017/calls/CreateKind4EntryPool.c`, `src/overlays/ov017/calls/HandleFieldObjectActivation.c`, and `src/overlays/ov017/calls/FinishPoolActions.c`.


## Byte-exact validation

44 DATA identities retain their source paths, native sizes and storage.
247/248 affected official function checks pass; the remaining
1 reproduce the preserved baseline relocation discrepancies described in
[DATA_NATIVE_RELOCATION_BASELINE.md](DATA_NATIVE_RELOCATION_BASELINE.md).
A fresh gate passes
all 108 linked modules, with every module hash unchanged. Comparing
all 283 affected production objects also preserves allocated bytes and
alignment, symbol offsets/sizes and relocation targets/types/addends.

Run from `eu/`:

```sh
python tools/test_rename_symbol.py
python tools/audit_progress.py --check-receipts
bash tools/gate.sh
```
