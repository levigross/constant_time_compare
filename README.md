Python Constant Time Comparison
=====================

This is a constant time comparison written in C for Python 2.7.x

Use
====
```python
from constant_time_compare import compare
print compare('foo', 'bar')
#False
print compare('foo', 'foo')
#True
```

Running Tests
=============
```bash
python test/tests.py
```
