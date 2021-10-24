#!/usr/bin/env python3

from xxx import something
import sys

something()
print(type(something))

module_object = sys.modules["xxx"]
print(module_object.ANSWER_TO_AN_IMPORTANT_QUESTION)
