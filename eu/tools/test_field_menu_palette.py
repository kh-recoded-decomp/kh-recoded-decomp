"""Replay EU palette selection with the real RGB555 and signed-division code.

Only the VRAM queue boundary is modeled. Tests compare state, RGB555 words,
queued source addresses/data, callback effects and the calling convention.
The pending C is also compiled with GCC/Clang; no matching coverage is awarded.
"""
import struct
import sys
import unittest

from project import EXTRACT_DIR, FUNC_INDEX, MWCC_DIR, ROOT
from thumb_replay_link import compile_thumb_image

sys.path.insert(0, str(ROOT.parent / 'tools/mobiclip'))
from arm_exec import Cpu, Memory

TARGET = 'func_ov001_02076ebc'
MENU = 0x01000000
STACK = MENU + 0xfff0
OTHER_PALETTE = MENU + 0x1000
COLORS = (0x2840, 0x54c1, 0x6d24, 0x006f, 0x04b7, 0x0cfe,
          0x00c0, 0x11a0, 0x1a60)


def signed_byte(value):
    return ((value + 128) & 255) - 128


def blend_color(source, target, level):
    channels = []
    for shift in (0, 5, 10):
        start, finish = (source >> shift) & 31, (target >> shift) & 31
        numerator = (finish - start) * level
        delta = abs(numerator) // 8
        channels.append(start + (-delta if numerator < 0 else delta))
    return (channels[0] | channels[1] << 5 | channels[2] << 10) & 0xffff


class QueueBoundaryCpu(Cpu):
    def __init__(self, memory, queue, handle, change_pointer, queue_result):
        super().__init__(memory)
        self.queue, self.handle = queue, handle
        self.change_pointer, self.queue_result = change_pointer, queue_result
        self.events = []

    def step(self):
        if self.r[15] != self.queue:
            return super().step()
        kind, destination, source, size = self.r[:4]
        self.events.append((kind, destination, source, size, self.mem.bytes(source, size)))
        if len(self.events) == 1 and self.change_pointer:
            self.mem.write(self.handle + 8, 4, OTHER_PALETTE)
        self.r[:4] = [self.queue_result, 0xa1a1a1a1, 0xb2b2b2b2, 0xc3c3c3c3]
        self.r[12] = 0xcccccccc
        self.n, self.z, self.c, self.v = 1, 0, 1, 1
        self.thumb = bool(self.r[14] & 1)
        self.r[15] = self.r[14] & ~1
        self.steps += 1


class FieldMenuPaletteTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not FUNC_INDEX.is_file():
            raise unittest.SkipTest('requires the local EU ROM-derived function index')
        if not (MWCC_DIR / 'dsi/1.1/mwccarm.exe').is_file():
            raise unittest.SkipTest('requires CodeWarrior dsi/1.1')
        import verify_idx
        cls.index, cls.addresses = verify_idx._index(), verify_idx.SYM_ADDR
        cls.entry = cls.addresses[TARGET]
        cls.original = (cls.entry | 1, [(cls.entry, bytes.fromhex(cls.index[TARGET]['hex']))])
        cls.handle = cls.addresses['data_ov001_020a04d0']
        cls.ramps = cls.addresses['gFieldMenuStateRamps']
        # Old index relocation names predate consolidation into the real 3x3 array.
        # Read data from the extracted ROM, not from those stale symbolic names.
        overlay = EXTRACT_DIR / 'arm9_overlays/ov001.bin'
        if not overlay.is_file():
            raise unittest.SkipTest('requires the extracted original ov001')
        blob = overlay.read_bytes()
        base = 0x020613e0
        offset = cls.entry - base
        if blob[offset:offset + 312] != cls.original[1][0][1]:
            raise AssertionError('overlay and index do not describe the same original code')
        cls.original_colors = blob[cls.ramps - base:cls.ramps - base + 18]
        cls.candidate = cls.compile_candidate('dsi/1.1')

    @classmethod
    def compile_candidate(cls, compiler):
        externs = {name: cls.addresses[name] for name in (
            'func_ov001_02076e30', 'NNS_GfdRegisterNewVramTransferTask',
            'gFieldMenuStateRamps', 'data_ov001_020a04d0')}
        externs['func_ov001_02076e30'] |= 1
        return compile_thumb_image(ROOT / 'src/nonmatching/UpdateFieldMenuPalette.c',
                                   'UpdateFieldMenuPalette', compiler, cls.entry, externs,
                                   thumb_functions={'func_ov001_02076e30'})

    def cpu(self, image, change_pointer=False, queue_result=1):
        memory = Memory()
        for address, code in image[1]:
            memory.map(address, code)
        for name in ('func_ov001_02076e30', '_s32_div_f'):
            memory.map(self.addresses[name], bytes.fromhex(self.index[name]['hex']))
        memory.map(MENU, bytes([0xa5]) * 0x10000)
        memory.map(self.handle, bytes([0xa5]) * 0x20)
        memory.map(self.ramps, self.original_colors)
        return QueueBoundaryCpu(memory, self.addresses['NNS_GfdRegisterNewVramTransferTask'],
                                self.handle, change_pointer, queue_result)

    def expected(self, before_menu, before_handle, advance, change_pointer):
        menu, handle = bytearray(before_menu), bytearray(before_handle)
        mode, previous, level, step = struct.unpack_from('<iibb', menu, 0x68)
        restore = mode == -1
        if restore:
            mode = previous
        if mode in (0, 7):
            palette = self.ramps + 6
        elif mode in (11, 13):
            if mode != previous:
                level, step, palette = 0, 2, self.ramps + 6
            else:
                if level >= 8:
                    step = -2
                elif level <= 0:
                    step = 2
                if advance:
                    level = min(8, max(0, signed_byte(level + step)))
                colors = [blend_color(source, target, level)
                          for source, target in zip(COLORS[3:6], (0x210, 0x318, 0x3ff))]
                struct.pack_into('<3H', handle, 12, *colors)
                palette = self.handle + 12
        elif mode == 10:
            palette = self.ramps
        else:
            palette = self.ramps + 12
        struct.pack_into('<iibb', menu, 0x68, -1 if restore else mode,
                         previous if restore else mode, level, step)
        struct.pack_into('<I', handle, 8, palette)

        def payload(address):
            if address == OTHER_PALETTE:
                return bytes([0xa5]) * 6
            if address == self.handle + 12:
                return bytes(handle[12:18])
            return self.original_colors[address - self.ramps:address - self.ramps + 6]

        events = [(15, 0x138, palette, 6, payload(palette))]
        if change_pointer:
            palette = OTHER_PALETTE
            struct.pack_into('<I', handle, 8, palette)
        events.append((15, 0x158, palette, 6, payload(palette)))
        return bytes(menu), bytes(handle), events

    def run_case(self, image, mode, previous, level, step, advance,
                 change_pointer=False, queue_result=1):
        cpu = self.cpu(image, change_pointer, queue_result)
        for offset, size, value in ((0x68, 4, mode), (0x6c, 4, previous),
                                    (0x70, 1, level), (0x71, 1, step)):
            cpu.mem.write(MENU + offset, size, value)
        before_menu, before_handle = cpu.mem.bytes(MENU, 0x100), cpu.mem.bytes(self.handle, 0x20)
        saved = [0x44440000 + n for n in range(8)]
        cpu.r[4:12] = saved
        cpu.call(image[0], [MENU, advance], sp=STACK, limit=10000)
        expected_menu, expected_handle, events = self.expected(
            before_menu, before_handle, advance, change_pointer)
        self.assertEqual(cpu.mem.bytes(MENU, 0x100), expected_menu)
        self.assertEqual(cpu.mem.bytes(self.handle, 0x20), expected_handle)
        self.assertEqual(cpu.mem.bytes(self.ramps, 18), self.original_colors)
        self.assertEqual(cpu.events, events)
        self.assertEqual(cpu.r[4:12], saved)
        self.assertEqual(cpu.r[13], STACK)

    def check_image(self, image):
        for mode in (-0x80000000, -2, -1, *range(17), 0x7fffffff):
            for previous in (-1, 0, 7, 10, 11, 13):
                for advance in (0, 1, -7):
                    with self.subTest(mode=mode, previous=previous, advance=advance):
                        self.run_case(image, mode, previous, 4, -2, advance)
        # Full signed-byte level domain, clamp/wrap boundaries and odd levels.
        # Out-of-range levels are instruction stress cases, not confirmed caller inputs.
        for level in range(-128, 128):
            for advance in (0, 1):
                self.run_case(image, 11, 11, level, -2, advance)
        for step in (-128, -3, 0, 1, 2, 127):
            self.run_case(image, 13, 13, 4, step, 1)
        for mode in (0, 10, 11, 13, 99):
            for result in (0, 1):
                self.run_case(image, mode, mode, 8, 2, 1, True, result)

    def test_original_palette_words(self):
        self.assertEqual(struct.unpack('<9H', self.original_colors), COLORS)

    def test_rom_and_pending_c(self):
        self.check_image(self.original)
        self.check_image(self.candidate)

    def test_continuous_pulse_and_restore_sentinel(self):
        for image in (self.original, self.candidate):
            cpu = self.cpu(image)
            cpu.mem.write(MENU + 0x68, 4, 11)
            cpu.mem.write(MENU + 0x6c, 4, 7)
            for frame in range(64):
                if frame == 16:
                    cpu.mem.write(MENU + 0x68, 4, -1)
                before_menu = cpu.mem.bytes(MENU, 0x100)
                before_handle = cpu.mem.bytes(self.handle, 0x20)
                cpu.events.clear()
                cpu.call(image[0], [MENU, 1], sp=STACK, limit=10000)
                menu, handle, events = self.expected(before_menu, before_handle, True, False)
                self.assertEqual(cpu.mem.bytes(MENU, 0x100), menu)
                self.assertEqual(cpu.mem.bytes(self.handle, 0x20), handle)
                self.assertEqual(cpu.events, events)
                self.assertEqual(cpu.mem.read(MENU + 0x70, 1), (0, 2, 4, 6, 8, 6, 4, 2)[frame % 8])

    def test_gcc_behavior(self):
        self.check_image(self.compile_candidate('gcc/12.2.1'))

    def test_clang_behavior(self):
        self.check_image(self.compile_candidate('clang/22.1.3'))


if __name__ == '__main__':
    unittest.main()
