"""Replay widget positioning and its real SDK/record helpers from the EU ROM.

The matching C is linked in memory using its ELF relocations and replayed too.
No helper is mocked. Byte matching is checked by the separate ordinary verifier.
"""
from pathlib import Path
import random
import struct
import sys
import unittest

from project import BUILD_DIR, FUNC_INDEX, MWCC_DIR, ROOT

sys.path.insert(0, str(ROOT.parent / 'tools/mobiclip'))
from arm_exec import Cpu, Memory

BASE = 0x01000000
RECORDS = BASE + 0x1000
WIDGET = BASE + 0x2000
INPUT = BASE + 0x3000
RECORD_STRIDE = 0x8c


def wrap(value):
    value &= 0xffffffff
    return value - (1 << 32) if value & 0x80000000 else value


class ObservedMemory(Memory):
    def __init__(self):
        super().__init__()
        self.record_writes = []

    def write(self, address, size, value):
        if RECORDS <= address < RECORDS + 4 * RECORD_STRIDE:
            if (address - RECORDS) % RECORD_STRIDE in (0x10, 0x14):
                self.record_writes.append((address, size, value & 0xffffffff))
        super().write(address, size, value)


class WidgetPositionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        if not FUNC_INDEX.is_file():
            raise unittest.SkipTest('requires the local EU ROM-derived function index')
        if not (MWCC_DIR / 'dsi/1.1/mwccarm.exe').is_file():
            raise unittest.SkipTest('requires CodeWarrior dsi/1.1')
        if not (MWCC_DIR / 'dsi/1.3p1/mwccarm.exe').is_file():
            raise unittest.SkipTest('requires CodeWarrior dsi/1.3p1')
        import verify_idx
        cls.index = verify_idx._index()
        cls.addresses = verify_idx.SYM_ADDR
        target = 'func_ov027_020b91e8'
        cls.entry = cls.addresses[target]
        cls.original = bytes.fromhex(cls.index[target]['hex'])
        cls.candidate = cls.compile_candidate('dsi/1.3p1')
        cls.getter_candidate = cls.compile_candidate('dsi/1.1', 'ResolveWidgetPositionComponents')

    @classmethod
    def compile_candidate(cls, compiler, target='func_ov027_020b91e8'):
        from arm_replay_link import compile_image
        setter = target == 'func_ov027_020b91e8'
        name = target
        source = ROOT / ('src/overlays/ov027/calls/func_ov027_020b91e8.c' if setter else
                         'src/overlays/ov027/calls/ResolveWidgetPositionComponents.c')
        return compile_image(source, name, target, compiler, cls.index, cls.addresses)

    def cpu(self, code, getter_code=None):
        memory = ObservedMemory()
        memory.map(self.entry, code)
        for name in ('GetWidgetPosition', 'MI_CpuFill8', 'MI_CpuCopy8', 'IndexedRecord_SetPair'):
            entry = self.index[name]
            self.assertEqual(entry['mode'], 'arm')
            self.assertEqual(entry['relocs'], [])
            memory.map(self.addresses[name], bytes.fromhex(entry['hex']))
        getter = 'ResolveWidgetPositionComponents'
        memory.map(self.addresses[getter], getter_code if getter_code is not None else
                   bytes.fromhex(self.index[getter]['hex']))
        memory.map(BASE, bytes([0xa5]) * 0x10000)
        return Cpu(memory)

    @staticmethod
    def point(cpu, address, values=None):
        if values is not None:
            for index, value in enumerate(values):
                cpu.mem.write(address + 4 * index, 4, value)
        return struct.unpack('<2i', cpu.mem.bytes(address, 8))

    def prepare(self, cpu, base, offset, requested, record_ids):
        cpu.mem.write(WIDGET + 0x14, 4, record_ids[0])
        cpu.mem.write(WIDGET + 0x18, 4, record_ids[1])
        self.point(cpu, WIDGET + 0x34, base)
        self.point(cpu, WIDGET + 0x3c, offset)
        self.point(cpu, INPUT, requested)
        cpu.mem.record_writes.clear()

    def call(self, cpu, mode, input_address=INPUT):
        cpu.call(self.entry, [RECORDS, WIDGET, input_address, mode & 0xffffffff],
                 sp=BASE + 0xfff0, limit=5000)

    def check_modes(self, images):
        cpus = [self.cpu(code) for code in images]
        rng = random.Random(0x020b91e8)
        inputs = [((100, -200), (7, -11), (-30, 40)),
                  ((0x7fffffff, -0x80000000), (1, -1), (-1, 1))]
        inputs += [tuple(tuple(wrap(rng.getrandbits(32)) for _ in range(2)) for _ in range(3))
                   for _ in range(64)]
        for base, old_offset, requested in inputs:
            for mode in range(6):
                # Absolute modes replace a coordinate; relative modes replace an offset.
                wanted_offset = list(old_offset)
                axes = ((0, 1), (0,), (1,))[mode % 3]
                for axis in axes:
                    wanted_offset[axis] = wrap(requested[axis] - base[axis]) if mode < 3 else requested[axis]
                wanted_position = tuple(wrap(a + b) for a, b in zip(base, wanted_offset))
                for ids in ((-1, -1), (0, -1), (-1, 2), (1, 1), (0, 3), (-7, 2)):
                    for cpu in cpus:
                        with self.subTest(mode=mode, ids=ids, base=base, image=cpus.index(cpu)):
                            self.prepare(cpu, base, old_offset, requested, ids)
                            before = bytearray(cpu.mem.bytes(RECORDS, 0x3008))
                            self.call(cpu, mode)
                            expected = before
                            struct.pack_into('<2i', expected, WIDGET + 0x3c - RECORDS, *wanted_offset)
                            expected_writes = []
                            for record in ids:
                                if record < 0:
                                    continue
                                address = RECORDS + record * RECORD_STRIDE + 0x10
                                struct.pack_into('<2i', expected, address - RECORDS, *wanted_position)
                                expected_writes.extend((address + 4 * i, 4, value & 0xffffffff)
                                                       for i, value in enumerate(wanted_position))
                            self.assertEqual(cpu.mem.bytes(RECORDS, len(expected)), bytes(expected))
                            self.assertEqual(cpu.mem.record_writes, expected_writes)

    def test_modes_offsets_records_and_untouched_bytes(self):
        self.check_modes([self.original, self.candidate])

    def test_invalid_modes_preserve_widget_input_and_records(self):
        for code in (self.original, self.candidate):
            cpu = self.cpu(code)
            for mode in (-0x80000000, -1, 6, 7, 255, 0x7fffffff):
                self.prepare(cpu, (11, 22), (-3, 4), (100, 200), (0, 1))
                before = cpu.mem.bytes(RECORDS, 0x3008)
                self.call(cpu, mode)
                self.assertEqual(cpu.mem.bytes(RECORDS, len(before)), before)
                self.assertEqual(cpu.mem.record_writes, [])

    def check_aliases(self, candidate):
        cpus = [self.cpu(self.original), self.cpu(candidate)]
        # Shifted pairs are machine-code stress inputs, not confirmed valid C objects/callers.
        for relative in (0x34, 0x38, 0x3c, 0x40):
            for mode in range(6):
                results = []
                for cpu in cpus:
                    self.prepare(cpu, (13, -19), (29, -31), (0, 0), (0, 2))
                    self.call(cpu, mode, WIDGET + relative)
                    results.append((cpu.mem.bytes(RECORDS, 0x3008), list(cpu.mem.record_writes)))
                with self.subTest(input_offset=hex(relative), mode=mode):
                    self.assertEqual(results[0], results[1])

    def test_input_aliases_widget_fields(self):
        self.check_aliases(self.candidate)

    def test_getter_and_setter_y_conventions(self):
        for code in (self.original, self.candidate):
            cpu = self.cpu(code)
            for mode, expected in ((2, (0, 33)), (5, (13, 0))):
                self.prepare(cpu, (10, 20), (7, 13), (111, 222), (0, -1))
                cpu.call(self.addresses['ResolveWidgetPositionComponents'],
                         [RECORDS, WIDGET, INPUT, mode], sp=BASE + 0xfff0, limit=5000)
                self.assertEqual(self.point(cpu, INPUT), expected)
                # Setter's Y input always occupies the second word.
                self.point(cpu, INPUT, (111, 222))
                self.call(cpu, mode)
                self.assertEqual(self.point(cpu, WIDGET + 0x3c), (7, 202 if mode == 2 else 222))

    def check_getter(self, images):
        rng = random.Random(0x020b90e4)
        inputs = [((0x7fffffff, -0x80000000), (1, -1)),
                  ((13, -19), (29, -31))]
        inputs += [tuple(tuple(wrap(rng.getrandbits(32)) for _ in range(2))
                         for _ in range(2)) for _ in range(30)]
        for image in images:
            cpu = self.cpu(self.original, image)
            for base, offset in inputs:
                for mode in (*range(6), -1, 6, -0x80000000):
                    for out in (INPUT, WIDGET + 0x34, WIDGET + 0x3c):
                        with self.subTest(mode=mode, out=hex(out), base=base):
                            self.prepare(cpu, base, offset, (111, 222), (0, 1))
                            expected = bytearray(cpu.mem.bytes(RECORDS, 0x3008))
                            # The original clears the output before reading either point.
                            struct.pack_into('<2i', expected, out - RECORDS, 0, 0)
                            origin = struct.unpack_from('<2i', expected, WIDGET + 0x34 - RECORDS)
                            relative = struct.unpack_from('<2i', expected, WIDGET + 0x3c - RECORDS)
                            absolute = tuple(wrap(a + b) for a, b in zip(origin, relative))
                            result = {0: absolute, 1: (absolute[0], 0), 2: (0, absolute[1]),
                                      3: relative, 4: (relative[0], 0), 5: (relative[1], 0)}.get(mode, (0, 0))
                            struct.pack_into('<2i', expected, out - RECORDS, *result)
                            returned = cpu.call(self.addresses['ResolveWidgetPositionComponents'],
                                                [RECORDS, WIDGET, out, mode],
                                                sp=BASE + 0xfff0, limit=5000)
                            self.assertEqual(returned, out)
                            self.assertEqual(cpu.mem.bytes(RECORDS, len(expected)), bytes(expected))
                            self.assertEqual(cpu.mem.record_writes, [])

    def test_getter_wrap_modes_and_complete_point_aliases(self):
        original = bytes.fromhex(self.index['ResolveWidgetPositionComponents']['hex'])
        self.check_getter([original, self.getter_candidate])

    def test_gcc_c_preserves_the_behavior_contract(self):
        from _run_gcc import find_compiler
        try:
            compiler = find_compiler()
        except SystemExit as error:
            self.skipTest(str(error))
        if not Path(compiler).is_file():
            self.skipTest('requires Arm GNU 12.2.Rel1')
        code = self.compile_candidate('gcc/12.2.1')
        self.check_modes([code])
        self.check_aliases(code)
        self.check_getter([self.compile_candidate('gcc/12.2.1', 'ResolveWidgetPositionComponents')])

    def test_clang_c_preserves_the_behavior_contract(self):
        from _run_clang import find_compiler
        try:
            compiler = find_compiler()
        except SystemExit as error:
            self.skipTest(str(error))
        if not Path(compiler).is_file():
            self.skipTest('requires Clang 22.1.3')
        code = self.compile_candidate('clang/22.1.3')
        self.check_modes([code])
        self.check_aliases(code)
        self.check_getter([self.compile_candidate('clang/22.1.3', 'ResolveWidgetPositionComponents')])


if __name__ == '__main__':
    unittest.main()
