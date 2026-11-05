# Menu resource cache idle task method

This document records 1 EU entrypoints from the source snapshot `00280f0886bde656b648fc7ec7a6c5f900ec0112`. Bank, address and ARM/Thumb mode identify each function; shared source addresses may differ between regions. It records reviewed contracts and naming evidence, with the official validation results recorded below.

The cache constructor returns `EnterMenuScreenState` as its first task method. That method waits for resource readiness, builds the header layer and returns the method documented here. `MenuResourceCacheIdleUpdate` returns the literal 0 and changes no state. In the native task scheduler, a zero method result retains the existing method rather than removing the task. The function closes no file and releases no cache allocation.

## Native declarations and evidence

Declaration blocks reproduce the matched native source after EU alias expansion and the accepted name substitution. They are traceability views, not finalized portable headers. The source preserves generated word arguments, private typedefs and occasional incomplete return declarations. The per-entry notes distinguish those views from demonstrated caller/dispatcher behavior. No prototype or layout change is part of this name-only inventory.

Source links point to the accepted EU paths and to unchanged shared bodies. Line ranges identify the reviewed snapshot; subsequent comments or native-view cleanups may move those lines. Resource lifetimes are assigned only where the writer/release/consumer chain establishes them.

| Bank:address | Mode | Previous symbol | Name | EU source |
| --- | --- | --- | --- | --- |
| `ov023:020b5a4c` | THUMB | `func_ov023_020b5a4c` | `MenuResourceCacheIdleUpdate` | [eu/src/overlays/ov023/auto/MenuResourceCacheIdleUpdate.c](../src/overlays/ov023/auto/MenuResourceCacheIdleUpdate.c) |

## MenuResourceCacheIdleUpdate

Identity: `ov023:020b5a4c`, THUMB, native extent 4 bytes (including any configured pool). Previous symbol: `func_ov023_020b5a4c`.

EU entrypoint: [eu/src/overlays/ov023/auto/MenuResourceCacheIdleUpdate.c](../src/overlays/ov023/auto/MenuResourceCacheIdleUpdate.c).

```c
int MenuResourceCacheIdleUpdate(void);
```

Native source view: preserve the stated result and the qualifications below. This declaration alone does not prove pointer ownership, Boolean normalization or callback readiness.

Demonstrated behavior and evidence:

- EU wrapper identifies constant-return0 update function. Source: [eu/src/overlays/ov023/auto/MenuResourceCacheIdleUpdate.c:1-2](../src/overlays/ov023/auto/MenuResourceCacheIdleUpdate.c).
- Function returns0 without changes. Source: [src/ov023/library_nitro_fs/FSi_CloseFileCommand_020b5a2c.c:1-1](../../src/ov023/library_nitro_fs/FSi_CloseFileCommand_020b5a2c.c).
- EU wrapper aliases this function into menu resource cache transition. Source: [eu/src/overlays/ov023/calls/EnterMenuScreenState.c:1-7](../src/overlays/ov023/calls/EnterMenuScreenState.c).
- After cache readiness, builds header layer and returns this function as the next task method. Source: [src/ov023/menu_graphics/EnterMenuScreenState_020b59e0.c:1-20](../../src/ov023/menu_graphics/EnterMenuScreenState_020b59e0.c).
- Constructor returns EnterMenuScreenState as its initial method. Source: [eu/src/overlays/ov023/calls/InitMenuResourceCache.c:1-36](../src/overlays/ov023/calls/InitMenuResourceCache.c).

Contract limits:

- The function is an idle task update, not file closure.

## Reproducible byte-exact validation

Run the existing verifier from `eu/`:

```sh
python tools/verify_idx.py src/overlays/ov023/auto/MenuResourceCacheIdleUpdate.c MenuResourceCacheIdleUpdate --thumb
bash tools/gate.sh
```

All entrypoints in this document pass their official function checks. The
combined106-entrypoint block passes the fresh108-module gate; affected function
bytes, resolved relocation targets/types and addends, and all module hashes
match the preserved pre-rename baseline. No algorithm, signature or native
matching-policy change is included. Verified-library receipts remain current.
