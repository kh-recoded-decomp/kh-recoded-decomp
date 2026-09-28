# Contributing a verified match

1. Run `python -m pip install -r requirements.txt` and
   `python tools/compile_match.py install` on Windows. Compiler archives and
   executables are pinned by SHA-256 in `profiles/compilers.json`.
2. Read the module symbols and ranges under `config/bk9e/arm9/`. Add reviewed
   C/C++ under `src/`. Sources may include shared type headers from `include/`
   and use compiler optimization pragmas. Inline assembly (also inside headers),
   other includes, binary inclusions, and arbitrary build recipes cannot count as
   C matches. Credit reused source. Use clear variable names and at most one
   short comment per function. `python tools/match_tool.py show|try|stage`
   prints the target, diffs a candidate, and queues a verified match.
3. Register the original module/symbol, source path, descriptive `source_symbol`,
   compiler variant, ARM/Thumb `mode`, and external address `bindings` in
   `matches.json`. The fixed compiler wrapper produces an ELF object, selects
   the named function, resolves supported ARMv5 relocations, and compares every
   byte including literal pools. It never reads the reference ROM while building.
   The complete compiled size must match: no trimming or masks.
4. Explain `behavior` in terms of what the player sees or does. Record `evidence`,
   `uncertainty`, `domain`, `origin`, and an `understanding` level: `gameplay` for
   a proven in-game feature, `subsystem` for a shared operation such as model
   animation, or `unknown`. Do not infer a specific enemy, item, or mechanic
   from a generic helper. Use readable variable names. Unproven functions retain
   address-based names.
5. Run `python tools/khrecoded.py progress` and
   `python tools/khrecoded.py check --profile full`. Each progress run recompiles
   registered functions in fresh temporary directories. Size differences,
   unresolved relocations, duplicate claims, overlaps, and changed bytes fail.

Recovered C from shared middleware contributes to C coverage with its origin
explicitly recorded. Original SDK binaries and assembly do not. Understanding
and byte matching are separate measures. Changing names alone adds no coverage.

The full source build remains a future milestone. These checks prove individual
functions at their original addresses; they do not yet link entire source
modules. `strict` reports the full module gate as unavailable until linked
modules exist. An exact baseline ROM repack is a separate check.
