/* NitroSDK crt0 parameter block in .text after the autoload callbacks: four zero words, the
 * {0x900, 1} pair with its byte-swapped magic (0xdec08133 / 0x3381c0de), then BuildInfo, the
 * module parameters the loader reads (autoload list start and end, autoload start, static .bss
 * start and end, compressed static end, SDK version and the NITRO code magic in both byte orders),
 * and the library tags the SDK embeds in every image. */
    .syntax unified
    .text
    .align 2
    .global SDK_ModuleParamsBlock
    .type SDK_ModuleParamsBlock, %object
SDK_ModuleParamsBlock:
    .word 0, 0, 0, 0
    .word 0x00000900, 0x00000001
    .word 0xdec08133, 0x3381c0de
    .global BuildInfo
    .type BuildInfo, %object
BuildInfo:
    .word data_0205e100          /* autoload list */
    .word data_0205e118          /* autoload list end */
    .word gMainDisplayState      /* autoload start */
    .word gMainDisplayState      /* static .bss start */
    .word 0x020613e0             /* static .bss end */
    .word 0                      /* compressed static end */
    .word 0x05047532             /* SDK version */
    .word 0xdec00621, 0x2106c0de /* NITRO code, big and little endian */
    .global cardi_backup_assert
    .type cardi_backup_assert, %object
cardi_backup_assert:
    .asciz "[SDK+NINTENDO:BACKUP]"
    .align 2
    .asciz "[SDK+Actimagine:Mobiclip SDK V1.1.1]"
    .align 2
    .size SDK_ModuleParamsBlock, . - SDK_ModuleParamsBlock
