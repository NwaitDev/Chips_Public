Introduction
============

This document starts by introducing the main concepts of the BIP2 language:
types, semantics and of course its syntax (see :ref:`language-label`). Then, it
presents tools used to compile and execute BIP2 programs. The compiler and the
engine: their installations and basic usage. As the main use cases involve the
generation of C++ code, a dedicated part explains more deeply how to use the C++
code generator of BIP2 (see :ref:`cpp-backend-label`). A step-by-step tutorial
shows how to use the main features of the BIP2 language (see
:ref:`tutorial-label`). Finally, the full language syntax is included as a
reference (see :ref:`bip2-grammar-label`).

.. a more developper oriented documentation can be found at the end,

.. Why using BIP2?
.. ---------------

.. TO BE DONE



Conventions used in this documentation
--------------------------------------

Shell commands
^^^^^^^^^^^^^^

Shell command are preceded by '``$``'::

  $ cd /etc/

When a command needs to be executed from within a given directory, this
directory is mentioned before the ``$``::

  /home/bla/ $ mkdir toto

If a command line is too long, the line is cut by escaping the line ending
character::

 $ ./bla --this --is="a very long" --command \
   --line \
   --that --is --cut=twice

