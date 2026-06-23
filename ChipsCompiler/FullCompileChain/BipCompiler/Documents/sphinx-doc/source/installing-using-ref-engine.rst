.. _reference-engine-label:

Installing & using available engines
====================================

Requirements
------------

The reference engine does not require any special software aside from a standard
C++ compiler and the `STL <http://www.sgi.com/tech/stl/>`_ (usually installed
along with the C++ compiler). In addition, a support for
`C++0x <http://en.wikipedia.org/wiki/C%2B%2B11>`_ is required when working with the
optimized engine, and `C++11 <http://en.wikipedia.org/wiki/C%2B%2B11>`_ for the
multithread engine. We are currently working with the GNU compiler g++ version
4.8.2, and for ABI compatibility issues we recommend to use g++ version 4.8 or
higher when compiling the generated code.


Downloading & installing
------------------------

Getting latest version
^^^^^^^^^^^^^^^^^^^^^^

Go to the `download page <http://www-verimag.imag.fr/New-BIP-tools.html>`_ for the
BIP tools. As for the compiler, you may install the engines separately using
specific archives, or you can install everything at once (compiler & engines).
Only the first installation procedure is presented here. For the *one archive*
installation, read the :ref:`installing-compiler-label`.

.. _engine-installation-label:

Installation of the engine
^^^^^^^^^^^^^^^^^^^^^^^^^^

The archive is a self-contained. You need to extract it in a dedicated
directory, for example ``/home/a_user/local/bip2``::

    $ mkdir /home/a_user/local/bip2
    $ cd /home/a_user/local/bip2
    $ tar zxvf /path/to/the/BIP-reference-engine_2012.01.tar.gz
    BIP-reference-engine-2012.01/
    ...
    ...

For easier use, set the following environment variables:

* ``BIP2_ENGINE_GENERIC_DIR`` : *absolute* path to *generic* header files.
* ``BIP2_ENGINE_SPECIFIC_DIR`` : *absolute* path to *specific* header files.
* ``BIP2_ENGINE_LIB_DIR`` : *absolute* path to library containing engine
  library.

This can be done adding the following in your ``~/.bashrc`` (if you are using
bash)::

  export BIP2_ENGINE_SPECIFIC_DIR=/path/to/BIP-reference-engine-2012.01/include/specific
  export BIP2_ENGINE_GENERIC_DIR=/path/to/BIP-reference-engine-2012.01/include/generic
  export BIP2_ENGINE_LIB_DIR=/path/to/BIP-reference-engine-2012.01/lib/static

Quick-tour of installation
^^^^^^^^^^^^^^^^^^^^^^^^^^

After extracting the archive, you should have a similar setup::

    .
    ÷── generic/
    │   `── include
    │       ÷── AtomExportPortItf.hpp
    │       ÷── AtomInternalPortItf.hpp
    │       ÷── AtomItf.hpp
    │       ÷── bip-engineiface-config.hpp
    │       ÷── BipErrorItf.hpp
    │
    ÷── specific/
    │    `── include
    │       ÷── AtomExportPort.hpp
    │       ÷── Atom.hpp
    │       ÷── AtomInternalPort.hpp
    │        ...
    `── lib/
        `── libengine.a

* the ``generic`` directory contains the header files that should be common to
  all engines following the standard API (see
  :ref:`dev-doc-engine_std_API-label` ).
* the ``specific`` directory contains the header files specific to the engine
  being installed (here, the reference engine).
* the ``lib`` directory contains the compiled code of the engine being
  installed.


Using the reference engine
--------------------------

Compiling & linking with generated code
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You need to generate code from your BIP source as explained in
:ref:`cpp-backend-label`.

Quick-start : follow regular *cmake* procedure
""""""""""""""""""""""""""""""""""""""""""""""

* create a ``build`` directory, for example within the generated code. This
  directory will host all files created during the compilation and the linking
  of the generated code. This directory can be wiped clean if needed without the
  need to run again the BIP compiler.
* from this new directory, invoke ``cmake`` by pointing to the directory
  containing the generated code.
* still from this new directory, invoke ``make`` to actually compile and link
  everything together

Step-by-step guide
""""""""""""""""""

You need to create a *build* subdirectory where all the compiled code will be
located. Usually, this directory is a sub-directory within the generated code
tree. For example, if the ``output`` directory contains all our generated code::

    /home/a_user/output $ mkdir build && cd build

Then you need to invoke ``cmake`` from within this new *build* directory by
pointing to the directory containing the generated code (in our example,
``..``). If you did not set environment variables as detailed in the
:ref:`engine-installation-label`, then you need to provide cmake with
*absolutes* paths to engine files: ``BIP2_ENGINE_GENERIC_DIR`` and
``BIP2_ENGINE_SPECIFIC_DIR`` for the engine interface code (*ie.* *header*
files), and ``BIP2_ENGINE_LIB_DIR`` for the compiled engine code.

Example cmake invocation *with* environment variables set::

    $ cmake ..
    -- The C compiler identification is GNU
    -- The CXX compiler identification is GNU
    -- Check for working C compiler: /usr/bin/gcc
    -- Check for working C compiler: /usr/bin/gcc -- works
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Check for working CXX compiler: /usr/bin/c++
    -- Check for working CXX compiler: /usr/bin/c++ -- works
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /home/a_user/output/build

Example cmake invocation *without* environment variables set::

  $ cmake \
  -DBIP2_ENGINE_GENERIC_DIR=/absolute/path/to/engines/BIP-reference-engine-2012.01/include/generic/ \
  -DBIP2_ENGINE_SPECIFIC_DIR=/absolute/path/to/engines/BIP-reference-engine-2012.01/include/specific/ \
  -DBIP2_ENGINE_LIB_DIR=/absolute/path/to/engines/BIP-reference-engine-2012.01/lib/static \
  ..
    -- The C compiler identification is GNU
    -- The CXX compiler identification is GNU
    -- Check for working C compiler: /usr/bin/gcc
    -- Check for working C compiler: /usr/bin/gcc -- works
    -- Detecting C compiler ABI info
    -- Detecting C compiler ABI info - done
    -- Check for working CXX compiler: /usr/bin/c++
    -- Check for working CXX compiler: /usr/bin/c++ -- works
    -- Detecting CXX compiler ABI info
    -- Detecting CXX compiler ABI info - done
    -- Configuring done
    -- Generating done
    -- Build files have been written to: /home/a_user/output/build

If your output matches the examples, you can proceed to the actual C++
compilation & linking by simply invoking ``make``::

  $ make

The result will be a single executable file called ``system``.


Running the resulting executable
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The resulting executable is called **system** and is created in the build
directory created previously (see previous section).
It includes both the code generated specifically for the considered BIP2 model
and the reference engine. Engines are runtime used for scheduling execution
sequences of BIP models.

Once the executable is built, help information is provided when executing
**system** with option ``--help``::

  ./system --help
  Usage: ./system [options]

  BIP Engine general options:
   -d, --debug       allows debug of the system, i.e. diplays the state of the system
   --execute         execute a single sequence of interactions (default)
   --explore         compute all possible sequences of interactions
   -h, --help        display this help and exit
   -i, --interactive interactive mode of execution
   -l, --limit LIMIT limits the execution to LIMIT interactions
   --seed SEED       set the seed for random to SEED
   -s, --silent      disables the display of the sequence of enabled/chosen interactions
   -v, --verbose     enables the display of the sequence of enabled/chosen interactions (default)
   -V, --version     displays engine version and exits

  BIP Engine semantics options (WARNING: modify the official semantics of BIP!):
   --disable-maximal-progress    disable the application of maximal progress priorities

Executing a single sequence
"""""""""""""""""""""""""""
An execution sequence can be scheduled simply by running directly **system**
without any option (execution of a single sequence is a default mode)::

  $ ./system

Notice that the reference engine is in verbose mode by default. At each state,
it displays the enabled interactions and internal ports, and the chosen sequence
, *e.g.*::

  ...
  [BIP ENGINE]: initialize components...
  [BIP ENGINE]: random scheduling based on seed=6
  [BIP ENGINE]: state #0: 14 interactions:
  [BIP ENGINE]:   [0] ROOT.f1take1: ROOT.f1.take() ROOT.p1.take_left()
  [BIP ENGINE]:   [1] ROOT.f1take2: ROOT.f1.take() ROOT.p7.take_right()
  [BIP ENGINE]:   [2] ROOT.f2take1: ROOT.f2.take() ROOT.p2.take_left()
  [BIP ENGINE]:   [3] ROOT.f2take2: ROOT.f2.take() ROOT.p1.take_right()
  [BIP ENGINE]:   [4] ROOT.f3take1: ROOT.f3.take() ROOT.p3.take_left()
  [BIP ENGINE]:   [5] ROOT.f3take2: ROOT.f3.take() ROOT.p2.take_right()
  [BIP ENGINE]:   [6] ROOT.f4take1: ROOT.f4.take() ROOT.p4.take_left()
  [BIP ENGINE]:   [7] ROOT.f4take2: ROOT.f4.take() ROOT.p3.take_right()
  [BIP ENGINE]:   [8] ROOT.f5take1: ROOT.f5.take() ROOT.p5.take_left()
  [BIP ENGINE]:   [9] ROOT.f5take2: ROOT.f5.take() ROOT.p4.take_right()
  [BIP ENGINE]:   [10] ROOT.f6take1: ROOT.f6.take() ROOT.p6.take_left()
  [BIP ENGINE]:   [11] ROOT.f6take2: ROOT.f6.take() ROOT.p5.take_right()
  [BIP ENGINE]:   [12] ROOT.f7take1: ROOT.f7.take() ROOT.p7.take_left()
  [BIP ENGINE]:   [13] ROOT.f7take2: ROOT.f7.take() ROOT.p6.take_right()
  [BIP ENGINE]: -> choose [1] ROOT.f1take2: ROOT.f1.take() ROOT.p7.take_right()
  [BIP ENGINE]: state #1: 12 interactions:
  [BIP ENGINE]:   [0] ROOT.f2take1: ROOT.f2.take() ROOT.p2.take_left()
  [BIP ENGINE]:   [1] ROOT.f2take2: ROOT.f2.take() ROOT.p1.take_right()
  [BIP ENGINE]:   [2] ROOT.f3take1: ROOT.f3.take() ROOT.p3.take_left()
  [BIP ENGINE]:   [3] ROOT.f3take2: ROOT.f3.take() ROOT.p2.take_right()
  [BIP ENGINE]:   [4] ROOT.f4take1: ROOT.f4.take() ROOT.p4.take_left()
  [BIP ENGINE]:   [5] ROOT.f4take2: ROOT.f4.take() ROOT.p3.take_right()
  [BIP ENGINE]:   [6] ROOT.f5take1: ROOT.f5.take() ROOT.p5.take_left()
  [BIP ENGINE]:   [7] ROOT.f5take2: ROOT.f5.take() ROOT.p4.take_right()
  [BIP ENGINE]:   [8] ROOT.f6take1: ROOT.f6.take() ROOT.p6.take_left()
  [BIP ENGINE]:   [9] ROOT.f6take2: ROOT.f6.take() ROOT.p5.take_right()
  [BIP ENGINE]:   [10] ROOT.f7take1: ROOT.f7.take() ROOT.p7.take_left()
  [BIP ENGINE]:   [11] ROOT.f7take2: ROOT.f7.take() ROOT.p6.take_right()
  [BIP ENGINE]: -> choose [11] ROOT.f7take2: ROOT.f7.take() ROOT.p6.take_right()
  ...
  [BIP ENGINE]: state #26: 2 interactions:
  [BIP ENGINE]:   [0] ROOT.f7take1: ROOT.f7.take() ROOT.p7.take_left()
  [BIP ENGINE]:   [1] ROOT.f7take2: ROOT.f7.take() ROOT.p6.take_right()
  [BIP ENGINE]: -> choose [1] ROOT.f7take2: ROOT.f7.take() ROOT.p6.take_right()
  [BIP ENGINE]: state #27: deadlock!

Interactions or internal ports are chosen randomly amongst the enabled ones.
The reference engine is based on a uniform distribution of probability for
the choice of the interactions or internal ports. By default, the seed
used to initialize randomize choices is computed from the current value of time,
but it can be set to a given value using option ``--seed``. The execution is
stopped if no interaction and no internal port is enabled, or if ctrl-D is hit.


Exhaustive execution
""""""""""""""""""""
Option ``--explore`` allows the exhaustive execution of the sequences defined by
a model. In order to perform back-tracking, this mode of execution requires the
generation of additional code, which is enforced using option
``--gencpp-enable-marshalling`` when compiling the model.

.. IMPORTANT::
  Enabling option ``--gencpp-enable-marshalling`` generates code for storing and
  retrieving states of atomic components, which requires storing / retrieving
  their variables. For custom types, such code has to be provided by the user
  (as the definition of the type). For a custom type ``custom_t``, the generated
  code expect the presence of an implementation for following methods:

  * ``size_t custom_t_sizeof(const custom_t &v)``: returns the number of bytes
    necessary to allocate for storing the current value of variable ``v`` of
    type ``custom_t`` provided as a parameter. Notice that it can return non
    constant numbers of bytes that depend on the value of ``v`` (e.g. useful for
    a ``string``, a list, etc.).
  * ``void custom_t_toBytes(char *b, const custom_t *ptr_v)`` encode the value
    of a variable of type ``custom_t`` pointed by ``ptr_v`` into a sequence of
    ``n`` bytes which are stored in a location starting from ``b``. The number
    of bytes ``n`` must satisfy ``n = custom_t_sizeof(*ptr_v)``.
  * ``void custom_t_fromBytes(custom_t *ptr_v, const char *b)``: decode a
    sequence of bytes stored at ``b`` and assign the corresponding value to
    the variable of type ``custom_t`` pointed by ``ptr_v``. Notice that this
    method must be able to guess the number of bytes to read from the sequence
    itself, i.e. it is the user responsibility to provide a way for kwowing when
    to stop reading bytes from ``b``.

  Notice that the exploration mode requires comparison of states. It assumes
  deterministic execution of the above methods, that is, they must provide the
  same results for the same input values. Obviously, the application of
  ``fromBytes`` to the sequence of bytes computed by ``toBytes`` for a variable
  ``v`` must assign to ``v`` the value it had when calling ``toBytes``.


The current version of the engine displays dots each time an interaction or an
internal port is executed. Moreover, the number of reachable states, deadlocks,
and errors is displayed, *e.g.*::

  $ ./system --explore
  ...
  [BIP ENGINE]: initialize components...
  [BIP ENGINE]: computing reachable states:..............................................
  .......................................................................................
  .......................................................................................
  .......................................................................................
  .......................................................................................
  ...
  .................... found 27303 reachable states, 2 deadlocks, and 0 error in 0 state




Using the optimized engine
--------------------------
Since the reference engine (presented in the previous section) can be very, very
slow, we recommend to use the optimized engine whenever performance is an issue.
The optimized engine implements minimal optimizations required for reasonable
runtime performances in terms of both execution time and memory usage. It
currently passes the same tests as the reference engine, and it accepts the same
general options.

For installing and using the optimized engine, proceeds as explained above for
the reference engine (see :ref:`engine-installation-label`), after downloading
the optimized engine instead of the reference engine from
`download page <http://www-verimag.imag.fr/New-BIP-tools.html>`_. Performances
can be again improved when combining the use of the optimized engine and the
activation of optimizations in the code generator (see
:ref:`cpp-optimizations-label`).

To allow maximal optimization, combine the following:

* pass ``--gencpp-optim 3`` to the C++ back-end when compiling your BIP model
* use the optimized engine
* pass ``-DCMAKE_BUILD_TYPE=Release`` to ``cmake`` when compiling the generated C++ code (i.e. use ``cmake -DCMAKE_BUILD_TYPE=Release ..``).




Using the multithread engine (beta version)
-------------------------------------------
The multithread engine is proposed for increasing further the performance when
running on multicore platforms. It is available in a beta version that is
experimental is and should not be considered as mature as the reference and the
optimized engine. It relies on the latest standard C++11 of C++, requiring
version 4.8 or higher of GCC for compiling the generated C++ code.
Moreover, it may require additional library implementing threads, e.g. to use
``pthread`` add the option ``--gencpp-ld-l pthread`` when invoking the BIP
compiler.

The options proposed by the multithread engine are listed
below::
  BIP Engine general options:
                    (i.e. executes interactions in parallel, if obs. equivalent)
   -d, --debug        allows debug of the system, i.e. diplays the state of the system
   -h, --help         display this help and exit
   -i, --interactive  interactive mode of execution
   -l, --limit LIMIT  limits the execution to LIMIT interactions
   --seed SEED        set the seed for random to SEED
   --threads NB       set the number of threads (by default, use the maximal HW
                      parallelism or 8)
   -s, --silent       disables the display of the sequence of enabled/chosen interactions
   -v, --verbose      enables the display of the sequence of enabled/chosen interactions
                      (default)
   -V, --version      displays engine version and exits

The multithread engine does not support any exploration mode and can only
execute sequences of interactions. It executes components involved in
interactions is parallel, based on the notion of partial state: interactions can
start from partial states, that is, even if some components are still running.
The multithread engine guarantees that interactions are always started in an
order meeting the global state semantics which is implemented in the reference
and the optimized engine.

Option ``--threads`` can be used to control the total number of threads used for
executing the model. Notice that these threads are used not only for executing
the atomic components, but also for computing the enabled interactions:
connectors evaluate enabled interactions in a parallel and concurrent way.

.. IMPORTANT::
    * The partial state semantics execution implemented by the multithread
      engine is equivalent to the one of the global state semantics if the
      execution of components is side-effect free (i.e. the external code
      executed by a component modifies only its local variables).

    * Due to the partial state semantics and the concurrent execution of
      connectors, the multithread engine cannot guarantee fairness of the
      execution of interactions and internal ports.

Notice that performances obtained when using the multithread engine depend on
many factors, and may be worse than the ones obtained when using the optimized
engine. This is due to the overhead introduced by the use of threads and threads
synchronizations, which is inherent to the concurrent design implemented by the
multithread engine.


Troubleshooting
---------------

``libengine_path`` error when running cmake
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you get the following error::

  CMake Error: The following variables are used in this project, but they are set to NOTFOUND.
  Please set them or make sure they are set and tested correctly in the CMake files:
  libengine_path
      linked by target "system" in directory ..../output

It's probably because you are trying to use a relative path for the
``BIP2_ENGINE_LIB_DIR``. Always use *absolute* paths!

``Atom.hpp: No such file or directory`` error
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If you get::

  In file included from .../src/simple/AT_At1.cpp:3:
  .../include/simple/AT_At1.hpp:6:20: error: Atom.hpp: No such file or directory

It's probably because you are trying to use a relative path for one or both
``BIP2_ENGINE_GENERIC_DIR`` and ``BIP2_ENGINE_SPECIFIC_DIR``. Always use
*absolute* paths !
