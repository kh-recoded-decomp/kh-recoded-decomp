# Contributing a verified match

The project currently has a complete BK9E extraction and an exact baseline
repack. The next major work is identifying the original compiler and flags,
building a linked-source pipeline, then replacing individual functions with C.
There is no claim of source decompilation until a function passes a live byte
comparison from authored source.

1. Read the symbol and range files under `config/bk9e/arm9/`. All 105 overlay
   profiles are present. `build/bk9e/extract/` contains the local reference
   binaries after `setup`.
2. Add original C or C++ under `src/`. Do not commit extracted assembly, object
   files, game data, SDK binaries, or the ROM.
3. Add a `matches.json` entry with `module`, `symbol`, `language`, `source`, and
   `build`. The build commands are arrays of argument arrays and run from the
   project root. `{source}`, `{object}`, `{output}`, and `{workdir}` placeholders
   expand to absolute paths. The recipe must consume `{source}` and write a raw
   function byte sequence to `{output}`. A candidate object section that still
   needs relocation is not a byte match; link it correctly before registering.
4. Run `python tools/khrecoded.py progress` and
   `python tools/khrecoded.py check --profile full`. A stale candidate or a
   source file whose current bytes no longer compile to the match fails.

Example shape, with tool and flags intentionally left to be proven for this
game:

```json
{
  "module": "arm9",
  "symbol": "func_0200093c",
  "language": "c",
  "source": "src/arm9/example.c",
  "build": [
    ["C:/path/to/proven-compiler.exe", "{source}", "-o", "{object}"],
    ["C:/path/to/objcopy.exe", "-O", "binary", "-j", ".text", "{object}", "{output}"]
  ]
}
```

This example is a manifest format illustration, not a known working compiler
recipe. Each verified output must be exactly the symbol size. Duplicate symbol
claims and overlapping matched ranges are rejected. Keep ASM and SDK matches
under their own `language` categories; they never increase the C count.

The full source build is a future milestone. `dsd lcf` and `dsd check modules`
provide linker metadata and module verification after a matching toolchain has
been identified. The `strict` check reports the module gate as unavailable
until linked modules exist. Avoid using the exact baseline repack as a source
build claim.

