Installing & using the BIP compiler
===================================

Requirements
------------

BIP compiler is currently only tested on GNU/Linux systems. It is know to
work correctly on Mac OSX, and probably other Unices, but we do not support them
currently.

Before installing the compiler, you must install:

* Java VM, version 6 (or above) for the core compiler. We have mainly used
  `OpenJDK <http://openjdk.java.net/>`_.

.. TIP::
   On GNU/Debian Linux and its derivative (*eg.* Ubuntu), you can install this
   dependency with::

     $ apt-get install openjdk-6-jre

.. WARNING::
   Theses instructions covers the installation of the compiler. The common
   usage involves the generation of C++ code and need the use of an engine. The
   quick installation contains the engines. If you are not using the quick
   installation procedure, see :ref:`reference-engine-label` for engine
   installation instructions.

.. _installing-compiler-label:

Downloading & installing
------------------------

Getting latest version
^^^^^^^^^^^^^^^^^^^^^^

Go to the `download page <http://www-verimag.imag.fr/New-BIP-tools.html>`_ for the
BIP tools. You are offered two solutions to install the BIP compiler and
engines:

 * the first is easier and quicker but may not fit all systems. Compiler and
   engines are packaged in the same archive and setup scripts are provided.
 * separate archives for compiler & engines are also provided. The installation of
   the compiler using these archives is explained in a second step.

Quick installation using self-contained archive
"""""""""""""""""""""""""""""""""""""""""""""""

For using the *quick installation*, you need to download the
``bip-full_<ARCH>.tar.gz`` archive. Replace ``<ARCH>`` with your own
architecture (eg. ``i686``). Then simply follow the following steps:

* create a directory where everything will be installed::

    $ mkdir bip2

* extract the archive::

    $ cd bip2 ; tar zxvf /path/to/bip-full_i686.tar.gz
    bip-full/
    bip-full/BIP-reference-engine-2012.04_Linux-i686/
    bip-full/BIP-reference-engine-2012.04_Linux-i686/include/
    ...

* setup the environement (works only in a bash shell)::

    $ cd bip-full
    $ source ./setup.sh
    Environment configured for engine:  reference-engine

  By default, ``setup.sh`` configure the installation for the reference engine.
  If you wish, you can also select the optimized engine or the multithread
  engine by passing respectively ``optimized-engine`` or ``multithread-engine``
  to ``setup.sh``, e.g. to select the optimized engine use::

    $ cd bip-full
    $ source ./setup.sh optimized-engine
    Environment configured for engine:  optimized-engine


Using separate archives for compiler
""""""""""""""""""""""""""""""""""""

The archive name should resemble
``bipc_2012.01.tar.gz``, the version number being dependent of the latest
version at the moment you are downloading it.

The compiler is a self-contained archive that you need to extract in a dedicated
directory, for example ``/home/a_user/local/bip2``::

    $ mkdir /home/a_user/local/bip2
    $ cd /home/a_user/local/bip2
    $ tar zxvf /path/to/the/bipc_2012.01.tar.gz
    bipc-2012.01/
    bipc-2012.01/lib/
    bipc-2012.01/lib/org.eclipse.acceleo.common_3.2.0.v20111027-0537.jar
    bipc-2012.01/lib/lpg.runtime.java_2.0.17.v201004271640.jar
    ...
    bipc-2012.01/bin/
    bipc-2012.01/bin/bipc.sh
    ...

Then, you need to add ``/home/a_user/local/bip2/bipc-2012.01/bin`` to your
``PATH`` environment variable.

In bash: ::

   $ export PATH=$PATH:/home/a_user/local/bip2/bipc-2012.01/bin

In tcsh: ::

   $ setenv PATH ${PATH}:/home/a_user/local/bip2/bipc-2012.01/bin


Quick tour of installation
^^^^^^^^^^^^^^^^^^^^^^^^^^

After installation, you should get something similar to the following setup: ::

    .
    ÷── bin
    │   `── bipc.sh
    `── lib
        ÷── acceleo.standalone.compiler_1.0-20120102155443.jar
        ÷── apache.tool.ant_1.8.0.jar
        ÷── backends
        │   ÷── ujf.verimag.bip.backend.aseba_1.0-20120102155513.jar
        │   ÷── ujf.verimag.bip.backend.bip_1.0-20120102155537.jar
        │   `── ujf.verimag.bip.backend.cpp_1.0-20120102155558.jar
        ÷── com.google.collect_1.0.0.v201105210816.jar
        ÷── filters
        ÷── joptsimple_3.2.jar
        ÷── lpg.runtime.java_2.0.17.v201004271640.jar
        ...

* the ``bin`` directory contains the compiler's executables. Usually, there is
  only the ``bipc.sh`` script used to run the compiler.
* the ``lib`` directory contains all java dependencies for the compiler. The
  sub-directory ``backends`` contains the back-end installed with the
  compiler. The ``filters`` contains the filter composing the middle-end. All
  files outside this sub-directory are libraries used by the compiler (EMF,
  eclipse runtime, command line parsing, ...)


Front-end checks for BIP model correctness
------------------------------------------

The compiler always checks if a given input is valid with respect to the
language (*eg.* syntax is correct, presence of cycles in priorities, correct
data flow in up/down of connectors). These checks are applied to both models
(type & instance). The compiler may emit two kinds of messages:

* *WARNING*: a potential error has been detected, but the it may be a
  false positive because of runtime dependency. Example of such warning is a
  cycle in priorities with at least one guarded priority: if the guard is false
  when all rules apply, then there is no cycle. These message are preceded by
  ``[WARNING]`` by the compiler.

* *ERROR*: an error has been found and the compiler stops as soon as
  possible. The input is not correct. A cycle in priority rules and writing to
  bound port's of a connector during the *up* phase are examples of such
  errors. These message are preceded by ``[SEVERE]`` by the compiler.

.. TIP::
   The compiler can treat *warnings* as *errors* and stop compilation when
   ``--Werr`` is used (very similar to regular C/C++ compiler behavior regarding
   ``-Werr``).

Sample output with a fatal error (the *root* declaration references a type that
the compiler could not find): ::

   $ bipc.sh -p ASamplePackage -d "ThisTypeDoesNotExists()" -I .
   [SEVERE] Type not found : ThisTypeDoesNotExists

Sample output with a warning (there may be more than one internal transition
from the same state, depending on the guards): ::

   $ bipc.sh -p ASamplePackage -d "SomeCompoundType()" -I .
   [WARNING] In ASamplePackage.bip:
   Transition from this state triggered by the same port (or internal) already exists :
       19:   on tic from S1 to S3 do { c = c + 1; tosend = tosend + 1; start = 1;}
       20:   internal from S3 to S2 provided (c <= 10)
   ----------^
       21:   internal from S3 to S1 provided ( c > 10)
       22:   on toc from S2 to S1 provided (c < 10)

When you run the compiler, you need to provide at least the following
parameters:

* a package name to compile: ``-p`` followed by the package name. The package
  name must match the file name that contains it (*ie.* package *Sample* must be
  stored in a file named ``Sample.bip``)
* one or more package search directories. This list of directories is used by the
  compiler to look for the package to compile (and the potential other packages
  that are needed because of dependencies): ``-I`` followed by a directory. Use
  the parameter several times to use multiple directories. The compiler will use
  the first correct match when searching (order is important).

By using only these two parameters, the compiler will load the types contained
in the package (and its dependencies) and check them for validity. Nothing is
produced by default.

You can also create an instance model along with the type model by giving the
compiler a component declaration using a type from the loaded package:

* ``-d`` followed by a declaration (*eg.* ``-p ACompound(1,2)``). Beware that
  it may be required to enclose the declaration by " " in order to protect it
  from being interpreted by your shell.

Example execution of the compiler: ::

    $ bipc.sh -p SamplePackage -I /home/a_user/my_bip_lib/ -d "MyType()"

Silencing warnings
^^^^^^^^^^^^^^^^^^

Some warnings can be silenced. This is useful when you are 100% sure that the
warning is not a problem in your specific case. You must never silence a warning
because you don't understand its presence !

To suppress a warning, you need to attach a ''@SuppressWarning'' annotation on
the element that triggers the warning along with the type of warnings you want
to silence. For example, in case of possible non-determinism in a petrinet::

 on work from a to a provided (x == 1) do { Max = 0; }
 on work from a to a provided (x > 1)  do { Max = 0; }

The compiler will output ::

 [WARNING] In bla.bip:
  Transition from this state triggered by the same port (or internal) already exists :
     108:  
     109:  on work from a to a provided (x == 1) do { Max = 0; }
  ---------^
     110:  on work from a to a provided (x > 1)  do { Max = 0; }
     111:  

You can silence this warning by adding annotations::

 @SuppressWarning(nondeterminism)
 on work from a to a provided (x == 1) do { Max = 0; }
 @SuppressWarning(nondeterminism)
 on work from a to a provided (x > 1)  do { Max = 0; }

The list of possible warning to silence is given below:

* nondeterminism
* unboundcomponentport
* unboundconnectorport
* missingup
* atomprioritycycle
* compoundprioritycycle
* uselessdown
* nointeraction
* missinginteraction
* modifiedvariabletransition
* modifiedvariableinteraction

Hints on using package
^^^^^^^^^^^^^^^^^^^^^^

A package named ''a.b.c.D'' must be stored in a directory hierarchy
''a/b/c/D.bip''. Anything else *will* not work. If you want to use packages
located outside of your current working directoy, you must use the ''-I''
parameter to add the directories that contain them. For example:

* you are developping in ''/somewhere/myApp'' a BIP package named ''Foo''
* you want to use the package ''my.other.package.Bar'' located in
  ''/a/bip/repository'' directory

Here's the tree snapshot and the corresponding compiler command to use::

  .
  |-- a
  |   `-- bip
  |       `-- repository
  |           `-- my
  |               `-- other
  |                   `-- package
  |                       `-- Bar.bip
  `-- somewhere
      `-- myApp
          `-- Foo.bip

  somewhere/myApp $ bipc.sh -p Foo -I /a/bip/repository


Using middle-ends (*aka.* filters)
----------------------------------

Filters are responsible for model to model transformations. A filter has the
same input and output type: a BIP model (type or instance model). Common use
cases for filters:

* flattening : remove hierarchy by flattening compound and connectors.
* dead code optimization : modify petrinet by removing unused parts.
* annotation : attach extra information on model element used by other filters
  or back-ends.

A filter can be used alone or a filter chain can be build. The chain is
specified using a simple syntax::

  filter1_name foo=bar foo2=bar2 ! filter2_name bla=bar

This will chain ``filter1_name`` and ``filter2_name``. Each filter will be
configured using its corresponding list of ``key=value`` pairs.

The chain specification can be given directly on from the command line using
``-f`` (or ``--filter``)::

  bipc.sh -f "filter1_name foo=bar foo2=bar2 ! filter2_name bla=bar"

.. IMPORTANT::
   Do not forget to enclose the chain specification between " or ', as the shell
   will most certainly interpret the ``!`` character, leading to unwanted
   behavior.

The chain specification can also be read from a file using
``--filter-file``. This is useful when the chain is getting complex as handling
very long lines can be tedious work. You simply need to write the chain in a
text file. To enhance readability, you can use a *1 filter by line* convention,
as the line feed is ignored::

  filter1_name foo=bar foo2=bar2 ! 
  filter2_name bla=bar !
  filter3_name some_very_complex_arg=something_very_very_long

And simply give this file to the compiler::

  bipc.sh --filter-file filters.txt ...


Using back-ends (code generators)
---------------------------------

General principles
^^^^^^^^^^^^^^^^^^

A back-end (*aka.* code generator) defines a set of specific parameters. Usually, using one of them will
enable the corresponding back-end. For example, for the C++ back-end, you can
see the following command line arguments (see :ref:`cpp-backend-label`): ::

    --gencpp-cc-I                           Add a path to the include search path  
                                              (used when calling the C++ compiler) 
    --gencpp-cc-extra-src                   Add an extra source file to the        
                                              compilation list                     
    --gencpp-follow-used-packages           Also generate code for used packages.  
    --gencpp-ld-L                           Add a path to the libraries search     
                                              path (used when calling the linker)  
    --gencpp-ld-extra-obj                   Add an extra object file to be linked  
                                              with the other parts                 
    --gencpp-ld-l                           Link with this library (use several    
                                              times to add many libraries)         
    --gencpp-no-serial                      Disable the generation of              
                                              serialization code                   
    --gencpp-output-dir                     Output directory for CPP backend       
    --gencpp-optim                          Set the optimization level (defaults   
                                            to none = 0). Each level includes a  
                                            set of optimization.                 
    --gencpp-set-optim-param                Set an optimisation parameter:         
                                            optimname:key:value                  
    --gencpp-disable-optim                  Disable a specific optimization (can   
                                            be used several times)               
    --gencpp-enable-optim                   Enable a specific optimization (can be 
                                            used several times)                  
    --gencpp-enable-bip-debug               Generates extra code to enable GDB to 
                                            debug at the BIP level

Calling the compiler using any on these parameter will enable the C++ back-end.

You can use more than one back-end at once without any problem as back-end are
meant to be independent. For example, for generating both a C++ and Aseba source
code in a single compiler run, you could use the following command: ::

    $ bipc.sh -p SamplePackage -I /home/a_user/my_bip_lib/ -d "MyType()" \
      --gencpp-output-dir cpp-output --genaesl-output-dir aseba-output

BIP back-end
^^^^^^^^^^^^

The BIP back-end can be used to generate back BIP source code. It is very simple
and uses two parameters:

* ``--genbip-output-dir`` : to specify the directory where the generated will be
  created
* ``--genbip-follow-used-packages`` : to enable the hierarchical generation. By
  default, only the package being compiled is generated back to BIP source
  code. When this parameter is present, the package's dependencies are also
  generated.

If no transformation are being executed in the middle-end, then this back-end
should produce a source code equivalent to the source code compiled (some
code reformating and reordering is very likely to happen): ::

    $ bipc.sh -p SamplePackage -I /home/a_user/my_bip_lib/ --genbip-output-dir bip-output

.. IMPORTANT::
   This back-end only supports type model compilation. It won't use the instance
   model that the compiler may produce (if a ``-d`` parameter is used).

C++ back-end
^^^^^^^^^^^^

Simple case, for compiling the package ``SomePackage`` and creating an
executable by taking an instance of the ``RootDefinition`` component use the
following command : ::

    $ bipc --gencpp-output build -p SomePackage -d 'RootDefinition()'

This command will generate several files, mainly C++ source code, but not
only. This code can't be compiled as is, it needs some glue code from a standard
engine. See :ref:`cpp-backend-label` for more details on this back-end.

.. Aseba back-end (experimental)
.. ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. This back-end is highly experimental. Documentation may be added latter. 
