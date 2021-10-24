#!/usr/bin/env python3

# on importe et utilise le MODULE 'greeter' :
import greeter
greeter.greet()

# greeter est bien un module, et n'a pas d'attribut __path__ :
assert not hasattr(greeter, "__path__")

# greeter n'est pas un package, et ne contient pas le sous-module 'pouet' :
try:
    import greeter.pouet
except ModuleNotFoundError:
    pass

# on crée un module '/tmp/pouet.py', qui sera le sous-module de notre futur package 'greeter' :
with open("/tmp/pouet.py", "w") as f:
    f.write("""
def talk():
    print("What I am saying is : pouetpouet")
""")

# keypoint : on transforme le MODULE 'greeter' en un PACKAGE, en lui définissant un
# attribut '__path__', permettant d'importer 'greeter.pouet' :
greeter.__path__ = ["/tmp"]

# 'greeter' est maintenant un PACKAGE, qui "contient" le sous-module 'pouet' :
import greeter.pouet
greeter.pouet.talk()
