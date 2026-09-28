# Third-party source and research

## Kingdom Hearts 358/2 Days matching decompilation

Some shared engine and middleware functions are adapted from
[Yokimitsuro/khdays-decomp](https://github.com/Yokimitsuro/khdays-decomp)
(revisions `ab832f38b943c15f461228968a89002e1a99c03e` and later), distributed under
CC0 1.0 Universal. The full license text is in
[`licenses/khdays-CC0.txt`](licenses/khdays-CC0.txt). The NitroSDK/NitroSystem
type headers under `include/nitro/` and `include/nnsys/` come from the same project.

Each adapted function records its source path and revision in
`matches.json`. Names and variable names are reviewed for the Re:coded context.
Every counted function must independently compile and match Re:coded bytes;
sharing an implementation or name with Days is not sufficient evidence.

## Tools

- [ds-decomp](https://github.com/AetiasHax/ds-decomp): extraction, analysis, and
  baseline packing. The Windows executable is downloaded locally and pinned.
- [decomp.me compiler distribution](https://github.com/decompme/compilers):
  compiler archive download. Compiler files remain local under ignored `.tools/`;
  the project's source license grants no rights to those binaries.
- [pyelftools](https://github.com/eliben/pyelftools): ELF parsing, pinned in
  `requirements.txt`.

Reference repositories are read from a separate local directory, outside this
repository. Original game binaries, disassembly dumps, and assets are not included.
