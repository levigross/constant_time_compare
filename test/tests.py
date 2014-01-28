#!/usr/bin/env python
import unittest
from random import choice
from string import printable

try:
    from constant_time_compare import compare
except ImportError:
    print "I am unable to import constant_time_compare, did it compile?"
    raise SystemExit


class TestConstantTimeCompare(unittest.TestCase):
    def test_invalid_num_args(self):
        self.assertRaises(ValueError, compare, 1, 2, 3)

    def test_invalid_lengths(self):
        self.assertFalse(compare('aa', 'a'))

    def test_valid_comparison(self):
        for i in xrange(1000):
            rand_string_one = ''.join((choice(printable) for i in range(20)))
            rand_string_two = ''.join((choice(printable) for i in range(20)))
            self.assertTrue(compare(rand_string_one, rand_string_one[:]))
            self.assertFalse(compare(rand_string_one, rand_string_two))


if __name__ == '__main__':
    unittest.main(verbosity=2)