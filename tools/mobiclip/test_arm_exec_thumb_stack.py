"""ARMv5 Thumb stack/address instructions needed by compiler-generated C."""
import struct
import unittest

from arm_exec import ArmFault, Cpu, Memory


class ThumbStackTests(unittest.TestCase):
    def cpu(self, instruction, pc=0x1002):
        memory = Memory()
        memory.map(pc, struct.pack('<H', instruction))
        memory.map(0x2000, bytes([0xa5]) * 0x1000)
        cpu = Cpu(memory)
        cpu.thumb, cpu.r[15], cpu.r[13] = True, pc, 0x2000
        cpu.n, cpu.z, cpu.c, cpu.v = 1, 0, 1, 1
        return cpu

    def assert_flags_unchanged(self, cpu):
        self.assertEqual((cpu.n, cpu.z, cpu.c, cpu.v), (1, 0, 1, 1))

    def test_stack_word_offsets_all_low_registers(self):
        for register in range(8):
            for immediate in (0, 1, 255):
                cpu = self.cpu(0x9000 | register << 8 | immediate)
                cpu.r[register] = 0x12340000 + register
                cpu.step()
                self.assertEqual(cpu.mem.read(0x2000 + immediate * 4, 4), 0x12340000 + register)
                self.assert_flags_unchanged(cpu)
                cpu = self.cpu(0x9800 | register << 8 | immediate)
                cpu.mem.write(0x2000 + immediate * 4, 4, 0xfedc0000 + register)
                cpu.step()
                self.assertEqual(cpu.r[register], 0xfedc0000 + register)
                self.assertEqual(cpu.r[13], 0x2000)
                self.assert_flags_unchanged(cpu)

    def test_address_generation_aligns_pc_and_preserves_sp_and_flags(self):
        for register in range(8):
            for immediate in (0, 1, 255):
                for use_sp in (False, True):
                    cpu = self.cpu(0xa000 | use_sp << 11 | register << 8 | immediate)
                    cpu.step()
                    self.assertEqual(cpu.r[register], (0x2000 if use_sp else 0x1004) + immediate * 4)
                    self.assertEqual(cpu.r[13], 0x2000)
                    self.assert_flags_unchanged(cpu)

    def test_stack_adjustment_both_signs_and_wrapping(self):
        for immediate in (0, 1, 4, 127):
            for subtract in (False, True):
                for stack in (0, 0x2000, 0xfffffffc):
                    cpu = self.cpu(0xb000 | subtract << 7 | immediate)
                    cpu.r[13] = stack
                    cpu.step()
                    self.assertEqual(cpu.r[13], (stack + (-1 if subtract else 1) * immediate * 4) & 0xffffffff)
                    self.assert_flags_unchanged(cpu)

    def test_unaligned_stack_word_access_is_refused(self):
        for instruction in (0x9000, 0x9800):
            cpu = self.cpu(instruction)
            cpu.r[13] += 2
            with self.assertRaises(ArmFault):
                cpu.step()

    def test_breakpoint_is_still_refused(self):
        with self.assertRaises(ArmFault):
            self.cpu(0xbe00).step()


if __name__ == '__main__':
    unittest.main()
