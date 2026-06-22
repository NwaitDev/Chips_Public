Developer reference for Compiler
================================

Compiler design
---------------

Goals:

* users/devs usually write different code generator : adding a new code
  generator should be as easy as possible
* users/devs usually enrich the input language for driving the code
  generator. Avoid the burden of changing the core grammar as this is very often
  overkill.

Big picture:

* front-end : *any to BIP-EMF* transformation. Takes any source code in a given
  language and translate it to *BIP-EMF*
* middle-end :*BIP-EMF to BIP-EMF*. Apply operations on a *BIP-EMF* input
  (operations can be read and/or write).
* back-end : *BIP-EMF to any*. Generates source code in a given language from a
  *BIP-EMF* input.

The current BIP compiler is developed with eclipse, but this is not a hard
requirement. Not using eclipse can be a bit hard because of the compiler use of
some eclipse technologies (in particular, *EMF*). The compiler is composed of
more than 10 different modules, each module being a single eclipse project. The
layout must be the following one::

  .
  ÷── Middleend
  │   ÷── ujf.verimag.bip.middleend
  │   `── ujf.verimag.bip.middleend.example
  ÷── Backend
  │   ÷── acceleo.standalone.compiler
  │   ÷── ujf.verimag.bip.backend
  │   ÷── ujf.verimag.bip.backend.aseba
  │   ÷── ujf.verimag.bip.backend.bip
  │   ÷── ujf.verimag.bip.backend.cpp
  │   ÷── ujf.verimag.bip.backend.example
  │   `── ujf.verimag.bip.backend.tests
  ÷── Common
  │   ÷── ujf.verimag.bip
  │   `── ujf.verimag.bip.error
  `── Frontend
      ÷── ujf.verimag.bip.frontend.tests
      ÷── ujf.verimag.bip.instantiator
      ÷── ujf.verimag.bip.metamodel
      ÷── ujf.verimag.bip.parser
      `── ujf.verimag.bip.userinterface.cli

We give here a very brief description of each module. Full description is given
in the following sections.

Middle-end
^^^^^^^^^^

The middle-end only contains the needed mechanics so that *filters* can be
executed. One simple example is provided.

Common
^^^^^^

* ``ujf.verimag.bip`` : contains elements shared by every parts of the compiler
  (mainly a java interface for *plug-in* mechanism)
* ``ujf.verimag.bip.error`` : the base of the error handling in all the compiler
* ``ujf.verimag.bip.exception`` : contains a single **unchecked**
  ``CompilerErrorException`` exception. This exception can be raised without
  having to explicitely declare it. It must be used only when a bug in the
  compiler has been detected. No recovery mechanism is present. The only
  handling done is to display a message to the user with the bare minium
  information to provide the developpers.



Front-end
^^^^^^^^^

* ``ujf.verimag.bip.metamodel`` : defines the BIP2 meta-model used in every bits
  of the compiler.
* ``ujf.verimag.bip.parser`` : defines the BIP2 grammar and the rules to build a
  *BIP-EMF* model from a BIP source 
* ``ujf.verimag.bip.instantiator`` : builds an instance model from a type model
  and a *root* component definition
* ``ujf.verimag.bip.userinterface.cli`` : interacts with the user and
  instantiate all parts of the compiler and bind them together to form a
  coherent compiler
* ``ujf.verimag.bip.frontend.tests`` : JUnit tests for the previous parts


Back-end
^^^^^^^^

* ``ujf.verimag.bip.backend`` : contains code shared by all *back-ends*
  (*eg.* some acceleo templates, back-end specific errors)
* ``ujf.verimag.bip.backend.aseba`` : ASEBA *back-end*
* ``ujf.verimag.bip.backend.bip`` : BIP *back-end*
* ``ujf.verimag.bip.backend.cpp`` : C++ *back-end*
* ``ujf.verimag.bip.backend.example`` : an example *back-end*, intended to be
  copied and used as a basis for new *back-end* development
* ``ujf.verimag.bip.backend.tests`` : JUnit for the previous parts
* ``acceleo.standalone.compiler`` : acceleo standalone compiler used to build
  the BIP compiler *outside* eclipse


Generalities
------------

Before describing every internal parts of the compiler, we need to describe how
the build system works and how to setup a correct development environment.

ivy
^^^

.. index::
   single: ivy

Ivy is used to define the dependencies between all modules and in conjunction
with ant or eclipse, for the correct building of the compiler. Each module
contains the following files:

``ivy.xml``
"""""""""""

This file simply contains information on the dependencies of the module.
When a module depends on another module, ivy automatically computes the
transitive dependencies.
When a module depends on an external library (*eg.* a *jar* file), it simply
declares this dependency and ivy will take care of not uselessly duplicating this *jar*
file because of transitive dependencies.

The following excerpt from ``ujf.verimag.bip`` module in ``Common`` shows the 2
types of dependencies::

  <dependency name="joptsimple" rev="3.2">
    <artifact name="joptsimple" type="jar"
              url="file://${basedir}/externals/jopt-simple-3.2.jar" />
  </dependency>
  <dependency name="ujf.verimag.bip.error"
              rev="latest.integration"></dependency>

It defines 2 dependencies:

* the first one, named ``joptsimple``, at version 3.2. This dependencies is
  *direct* as we also provide the corresponding *artifact* (a path to the *jar*
  file).
* the second one, named ``ujf.verimag.bip.error``. As there is no more
  information, ivy will have to find the provider for this dependency (in this
  case, the ``ujf.verimag.bip.error`` module).

A single dependencies can have several artifacts, as is the case of the EMF in
``ujf.verimag.bip.metamodel`` module::

  <dependency name="org.eclipse.emf" rev="2.7.0">
    <artifact name="org.eclipse.emf" type="jar" 
              url="file://${basedir}/externals/org.eclipse.emf_2.6.0.v20110913-1156.jar"/>
    <artifact name="org.eclipse.emf.common" type="jar" 
              url="file://${basedir}/externals/org.eclipse.emf.common_2.7.0.v20110912-0920.jar"/>
    <artifact name="org.eclipse.emf.ecore" type="jar" 
              url="file://${basedir}/externals/org.eclipse.emf.ecore_2.7.0.v20110912-0920.jar"/>
    <artifact name="org.eclipse.emf.ecore.xmi" type="jar" 
              url="file://${basedir}/externals/org.eclipse.emf.ecore.xmi_2.7.0.v20110520-1406.jar"/>
    <artifact name="org.eclipse.emf.mapping.ecore2xml" type="jar" 
              url="file://${basedir}/externals/org.eclipse.emf.mapping.ecore2xml_2.7.0.v20110331-2022.jar"/>
  </dependency>

The full documentation on ivy can be found at `<http://ant.apache.org/ivy/>`_

``build.xml``
"""""""""""""

This file is used by ``ant`` to schedule the build. This includes the actual
compilation of source files (acceleo templates, antlr grammar, java code, ...)
and the use of ivy to resolve each module's dependencies.

Module with only java code in the ``src/main/java`` directory have a 3 liner as
``build.xml``::

  <project name="ujf.verimag.bip.FOO" default="compile">
     <property file="build.properties" />
     <import file="${distribution.dir}/common.xml" />
  </project>

When the module needs to do other actions, you need to override the ``compile``
target. This is the case for the metamodel, as java code is located in two
different directories::

  <target name="compile" depends="resolve" description="--> compile the project">
    <mkdir dir="${classes.dir}" />
    <javac srcdir="${src.dir}" destdir="${classes.dir}" 
           classpathref="lib.path.id" debug="true">
      <src path="${src.dir}" />
      <src path="src/main/emf-generated" />
    </javac>
  </target>


Eclipse
^^^^^^^

In order for all modules to be correctly imported in eclipse, you need to
install the following *plug-ins*:

* Eclipse Modeling Framework (EMF): its part of eclipse and directly available
  in the *plug-ins* list.
* IvyIDE : you need to install this *plug-in* by following instructions
  available on the project webpage: `<http://ant.apache.org/ivy/ivyde/>`_
* Acceleo : also available from the eclipse *plug-ins* list

Then, you simply need to use the *import existing project* of eclipse and point
it to the directory containing the ``Common``, ``Frontend`` and ``Backend``
directories. Eclipse should see all sub-project and import them.

.. IMPORTANT::
   If you import projects from a fresh source tree, eclipse will fail at
   building the compiler because of missing java code in the *parser*
   project. Indeed, you need to build the ant target ``gencode-for-eclipse``. See the
   description of the parser module for more details.

.. IMPORTANT::
   It is **normal** that under the *projects* tab in the *build path*
   configuration windows, the list is empty. It should always be empty, as
   project dependencies are handled by the ivy pluggin. The only case where you
   need to add a dependency is when debugging a filter or back-end. This change
   must never be pushed to the code repository.

.. _dev-doc-frontend-label:

Front-end
---------

``u.v.b.metamodel``
^^^^^^^^^^^^^^^^^^^

.. index::
   single: meta-model

This module defines the BIP2 meta-model used by all parts of the compiler, as
the meta-model is the intermediate representation of BIP models. It contains:

* the meta-model itself, as an ``.ecore`` file
* the constraints on the models of this meta-models

The ``bip2.ecore`` file is located in the ``model/`` sub-directory. This is the
file you need to use with tools dealing with EMF models. It comes with 2 other
files:

* ``bip2.ecorediag`` : it is tied to the ``ecore`` and allows the graphical
  editing of the meta-model with EMF editor. Opening this file and editing the
  displayed model will modify automatically the ``ecore`` accordingly.
* ``bip2.genmodel`` : this file is used by the EMF code generator. In BIP, we
  use only the Java code generation mechanism.

The regular work-flow when touching the meta-model is given below:

* modify the meta-model by editing the *ecorediag* (or the *ecore* directly).
* generate Java code (see below) 
* implement constraints (if needed)

Meta-model organization
"""""""""""""""""""""""

The meta-model is split in two parts:

* the *type model* is used to describe a BIP source code and nothing more:
  collections of types organized in packages.
* the *instance model* is used to describe a deployed system: instances of BIP
  types. This model points to the *type model*.

The instance model lives under the ``instance`` package. Everything else is
related to the *type model*.

Generating Java code from the meta-model
""""""""""""""""""""""""""""""""""""""""

Open the ``bip2.genmodel`` file in Eclipse, right-click on the single line named
*Bip2* and select ``Generate Model code``. This will generate code in the
``src/main/emf-generated`` directory. 

.. IMPORTANT::
   The directory ``src/main/emf-generated`` *is* versioned, please *review* the
   changes before commiting !


Constraints
"""""""""""

A constraint is added on an element of the meta-model by adding an annotation:

* the *source* field for the annotation must be
  ``http://www.eclipse.org/emf/2002/Ecore``
* then, an item with the key ``constraints`` contains a space separated list of
  constraint names.

When the java code is generated, EMF will create empty stubs that must be
completed by the actual constraint code. In order to keep these changes even
when the code generator is executed again, you *must* modify the comment before
the constraint method. The convention adopted by most project is to add ``NOT``
(in capitals) after the ``@generated``::

  /**
   * Validates the constraintName constraint of '<em>Elt Name</em>'.
   * <!-- begin-user-doc -->
   * <!-- end-user-doc -->
   * @generated NOT
   */

Omitting this will end up in the loss of your changes during the next code
generation execution.

The default code for error handling (*ie.* when a constraint is violated) must
be changed to integrate well with the compiler error handling. By default, EMF
produces the following code::

  diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                    DIAGNOSTIC_SOURCE, 0,
                    "_UI_GenericConstraint_diagnostic", 
                    new Object[] {
                      "exportedDataListsSynchronized",
                      getObjectLabel(theElementWithAConstraint, context)
                    },
                    new Object[] { 
                      theElementWithAConstraint,
                    }
                    context));

You must add an extra information to identify precisely the exact error detected
by the constraint (codes are defined in ``ujf.verimag.bip.error`` module :
:ref:`dev-doc-common-error-label`). This code must be added in the array of
``Object`` created near the end of the previous excerpt::

  diagnostics.add(createDiagnostic(Diagnostic.ERROR,
                    DIAGNOSTIC_SOURCE, 0,
                    "_UI_GenericConstraint_diagnostic", 
                    new Object[] {
                      "exportedDataListsSynchronized",
                      getObjectLabel(theElementWithAConstraint, context)
                    },
                    new Object[] { 
                      theElementWithAConstraint,
		      /*
                       * BIP Error code corresponding to this constraint
                       */ 
                      ErrorCodeEnum.constraintXYViolation,
                    },
                    context));

EMF allows the use of different *level* for each ``Diagnostic`` object
created. In the BIP compiler, we only use the ``ERROR`` when the constraint
violation is fatal (*ie.* the compiler must stop) and ``WARNING`` when the
violation is a sign of potential error (in general, these can only be detected
at runtime).

Versionning generated code
""""""""""""""""""""""""""

As we need to implement our constraints in the generated code, we need to add it
in the code repository. In order to differentiate handwritten code (that we
really need to keep track of) from automatically generated code (thousands of
lines), split your commits ! Use the following steps :

* add constraints in the meta-model

  * commit changes in ``.ecore`` and ``.ecorediag`` files with regular comments.

* generate java code
 
  * commit only the generated code and state that this is generated code for new
    constraints

* implement the constraints

  * commit your changes with ``[MODEL CODE MODIF]`` with the names of the
    constraints you've modified.

.. IMPORTANT:: 
   When adding a new constraint, *always* **always** create the corresponding
   error message and JUnit test at the same time. *Never* commit the constraint
   code if you don't have the tests and errors ready. If you do so, you *will*
   forget about them and hit problems later. See corresponding sections for adding
   error and tests.


``u.v.b.parser``
^^^^^^^^^^^^^^^^
.. index::
   single: parser
   single: parser; antlr

For historical reasons (*ie.* no real technical reasons), the ``parser`` modules
contains not only a parser, but also the code for the *package loader* and its
*package registry*.

Parser
""""""

The parser is using the `antlr <http://www.antlr.org>`_ tool. You can find many
GUI for helping in the development of antlr grammar.

The BIP compiler follows the antlr recommended work-flow:

* ``Bip2.g``: a regular grammar is used to read a BIP source code. This pass
  creates an abstract syntax tree (*aka.* AST) by using antlr *automatic* tree
  building.
* ``Bip2Walker.g``: a second grammar expressed on tree is used to recognize the
  AST created by the previous pass. Rules embed the necessary java code for
  building a *BIP-EMF* model. This model describes only the types found in the
  parsed BIP code; instances are handled later.

The goal of this split is to have the grammar part as language agnostic as
possible: rules do not embed any java code. The file ``grammar/Bip2.g`` could be
used to build parsers for other languages supported by antlr (*eg.* ruby or
python).

.. IMPORTANT::
   The previous statement is not 100% true, as we want to plug the compiler's
   error management inside the parser to be able to rewrap parser's errors and
   display present them to the user in a coherent way. There are few lines of
   java in the header of the grammar file: these lines can be safely removed if
   the grammar is to be used for a different target language than java.

The java code generated by antlr from the previous two grammar files is *not* in
the code repository. You need to generate it first. Invoking the ant target
``gencode-for-eclipse`` should do the job are generate java code in ``build/generated-src``
directory.

.. IMPORTANT::
   When you change one of the grammar files, you **must** regenerate the code.

.. IMPORTANT::
   You must not use directly the ``gencode`` ant target as it's used for
   packaging the compiler. The generated code won't be in the correct location
   for eclipse developement.

Package Loader & Package registry
"""""""""""""""""""""""""""""""""

The package loader is a simple object that uses:

* a *classloader* to locate BIP files across different directories with the
  dotted package naming.
* a registry, that is nothing more than a hash table, used to store the BIP
  packages already loaded.

It is the package loader that takes care of running the parser when a BIP file
needs to be parsed.

The loader has a very simple interface, mainly consisting of the method:

* ``Package getPackage(String package_name)`` : returns the type model
  corresponding to the package named after the ``package_name`` parameter.


``u.v.b.instantiator``
^^^^^^^^^^^^^^^^^^^^^^

The instantiator is responsible for creating an instance model from a set of BIP
packages and a *root* component declaration. Its result is a DAG with instance
of ``*Instance`` java classes as nodes. The entry point is the method:

* ``ComponentInstance instantiate(ComponentDeclaration declaration)``

It reads the declaration, search for the corresponding type in the loaded types
and returns a ``ComponentInstance`` object describing an instance of a
component. This call will recursively invoke other ``*Instance
instantiate(*Declaration declaration)`` methods while browsing the types found
for all sub-declarations (*eg.* taking an instance of a compound triggers the
instantiation of sub-components, connectors, priorities, ports).

More details on the instantiation of component
""""""""""""""""""""""""""""""""""""""""""""""

The entry point of the instantiator is the the
''instantiateTopLevel(ComponentDeclaration declaration)'' method. The component
declaration must be a compound, else it will fail. This method will simply
*unroll* the hierarchy starting from the root compound and build an instance
tree. Each encountered declaration (port, data, connector, component, priority,
etc) will trigger the creation of an instance object in the tree (the instance
objects make a tree). It is important to note that components parameters need
special handling.

Parameters for a component declaration can only involve the following:

* direct values: 3, 18.5
* data references to container's data parameters
* data references to constant data declaration 

There is a need when instantiating a parameterized component declaration to
resolve the data references, in particular for reference to container's
parameters. What we do is that we duplicate the expressions found in the
declaration (involving only objects within the type graph) and then we resolve
data references to point to instance objects instead of pointing to type
objects.

``u.v.b.userinterface.cli``
^^^^^^^^^^^^^^^^^^^^^^^^^^^

Any user interface is expected to instantiate compiler's building blocks and
assemble them to create a working compiler. This module contains a *command line
interface*.

It basically does the following steps:

* initializes the command line parsing tool:

 * with common arguments (package, verbosity, search paths, root declaration,
   etc)
 * with arguments from back-ends (this is achieved by introspecting the
   back-ends classes)

* creates a package loader
* loads the package requested from the command line
* if a root declaration was given, instantiate it
* executes all back-ends in turn.

All steps may fail and should report the cause by transmitting an Error
object. The actual class and mean of transmission depends on the step failing.

``u.v.b.frontend.tests``
^^^^^^^^^^^^^^^^^^^^^^^^

Tests are using JUnit and follow the conventions:

* classes with tests are named ``SomethingTests``, with ``Something`` being
  explicit enough about the content. The class name can't start with
  ``Abstract``.
* tests that need the package loader are located in the package
  ``loader``. Store other tests in separate packages: keep tests tidy!
* resources needed by tests must be stored in sub-directories of
  ``src/tests/resources/``. Name the sub-directories so that it is easy to match
  the files to their corresponding test classes.


.. _dev-doc-common-label:

Common
------

u.v.bip
^^^^^^^

This module contains parts that may be shared by every part of the
compiler. Currently, it only contains the needed interface and library to parse
command line arguments. The ``Configurable`` interface is used for plug-in after
command line has been parsed: arguments are passed to the plug-in so that it can
configure itself.

.. _dev-doc-common-error-label:

u.v.b.error
^^^^^^^^^^^

The error module is the base of all error handling in the compiler. The main
idea behind it is the following:

* an error type has a unique identifier across all compiler: all identifiers are
  defined in this module. This is a major problem concerning modularity as a
  plug-in must have its specific errors defined in the base of the compiler.
* error messages are not hardcoded and are shipped as properties. Currently,
  only an English version is available, but translating the few dozens of
  message is straightforward.

All errors must inherit from the ``GenericError`` class. This class defines the
most common attributes needed to handle error and display useful error message
to the user:

* the error code
* when possible, the location in the BIP source file

The error identifiers are defined as an enumerated type in ``ErrorCodeEnum``.

The class ``ErrorMessage`` must be used to get human readable error
messages. Its ``getMessage()`` method takes an error identifier and returns the
corresponding error message from the property file used when starting the
compiler (by default, it uses the ``english-messages.properties`` file.

If you need the user to designate a given warning, you should use the helper
mapping ''userFriendlyNames'' provided within ''ErrorCodeEnum''. It maps names
that the user can easily understand to internal names that maybe too verbose to
be user friendly. This is what is used by the ''@SuppressWarning'' annotation.

.. IMPORTANT::
   Having a pluggable system for error handling is completely possible. It has
   not been implemented yet for simplicity and because of limited development
   resources. It may be fixed in future versions, if needed.

u.v.b.exception
^^^^^^^^^^^^^^^

This package only contains a single class called
``CompilerErrorException``. This exception class is **unchecked** and must be
used if and only if a bug in the compiler has been found. This class is very
minimalist and contains members that could be useful to track the origin of the
bug.

.. _dev-doc-middleend-label:

Middle-end
----------

This module contains currently 2 elements:

* the common part that contains the interface between the middle-ends and the
  user interfaces: the ``Filterable`` java interface and the necessary
  classes/enums for error handling.
* an example

.. HINT::
   The *pipe* like syntax used to chain the filters from the command line is
   handled in the command line user interface, not in this module.

.. _dev-doc-backend-label:

Back-end
--------


``u.v.b.backend``
^^^^^^^^^^^^^^^^^

This module contains 3 elements shared by all the back-ends and needed for
interacting with the other parts of the compiler:

* the ``Backendable`` interface that back-ends must implement.
* the acceleo runtime, that is meant to be used by all back-ends (even though a
  back-end can be in pure Java)
* some acceleo template/queries that are useful for all back-ends (*eg.*
  extracting information from annotations, some other common operations, ...)

.. IMPORTANT::
   As of this writing, acceleo has some limitation (bug) that prevent the real
   sharing of common templates/queries. The templates/queries provided here are
   currently copied in all back-ends modules that need them. This is a
   work-around.

``u.v.b.backend.aseba``
^^^^^^^^^^^^^^^^^^^^^^^

This back-end is used to generate Aseba code. It is highly experimental and does
not cover all the BIP language.


``u.v.b.backend.bip``
^^^^^^^^^^^^^^^^^^^^^

This back-end produces BIP code. It is very simple, as templates are used to
translate the *BIP-EMF* to the textual BIP representation, with both being by
construction very close.

There are 6 templates:

* 4 BIP types (*ie.* port, connector, atom, compound)
* 1 for the package
* 1 for the port declarations
* 1 for the annotations

This backend can be a good starting point for understanding the internals of the backends
using acceleo templates.

.. WARNING::
   When writing unit test for BIP, we mainly use the EMF *equals()* method to
   check that *bip(bip(a-test-source)) == bip(a-test-source)*. EMF models are
   sensitive to *order*, meaning that even if some model are equivalent from the
   BIP point of view, they are not from EMF point of view. For example, the
   generated code will *always* have : data types, port types, connector types,
   atom types, compound types. Same goes for atom internals, where data comes
   before export port, that comes before internal ports.

``u.v.b.backend.cpp``
^^^^^^^^^^^^^^^^^^^^^

This back-end is the most complex (and used) available in the compiler.
It uses both the type model and the instance model to generate a set of C++
source file along with the cmake scripts used to build everything.

The type model is used to generate C++ classes. All these classes inherit from
classes in the BIP engine interface.

The instance model is used to create the needed statements and variable creation
for the deployment of the system.

Entry points for this back-ends are:

* the ``GeneratePackage`` class that is the interface between the java code and
  the acceleo engine that applies the templates for the generation of classes
  corresponding to BIP types. From the outside (java world), it is only possible
  to generate something from a package (*ie.* it is not possible to generate
  simply the C++ code corresponding to an atom type).
* the ``GenerateDeploy`` class is the interface between java code and the
  acceleo engine for the creation of the deploy code.
* the ``Cmake`` class is used to generate all the necessary files for cmake to
  build all the generated code.

More details are given in the separate :ref:`dev-doc-cpp-backend-label`.

``u.v.b.backend.example``
^^^^^^^^^^^^^^^^^^^^^^^^^

This back-end is empty and its only use is to be a starting point for creating
new back-end.

``u.v.b.backend.tests``
^^^^^^^^^^^^^^^^^^^^^^^

All JUnit tests are stored in this module. As for the front-end tests:

* test classes must be named ``SomethingTests`` with ``Something`` being a
  descriptive name that does not start with ``Abstract``
* tests resources must be placed in sub-directories of
  ``src/tests/resources/``. The current convention is to store C++ backend
  related resources in a ``cpp/`` subdirectory.


``acceleo.standalone.compiler``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A back-end is a *black box* that is used for generating something from a
*BIP-EMF* model. Typical lifecycle of a back-end:

* configuration (*eg.* output directory, optimization level, ...)
* if the back-end is able to generate something from a type model, then it is
  called with the type model at the end of the compilation process
* if the back-end is able to generate something from an instance model and an
  instance model has been build during compilation, the it is called with the
  instance model.

.. _dev-doc-cpp-backend-label:

C++ back-end
------------

The back-end must be fed with both the type model and the instance model. The
type model is used to create C++ classes and the instance model to create a
deployment *script* (*ie.* creates instances of previously created classes, in a
correct order). 

.. IMPORTANT::
   The *limitation* only exists for simplification purposes. It is completely
   possible to compile only BIP types into C++ classes and package the result as
   a library, but our current compilation flow does not support the use of
   precompiled BIP package. This feature will be handled in later version.


Type code generation
^^^^^^^^^^^^^^^^^^^^

All type templates (*ie.* template for any sub-class of the ``BipType`` class in
the meta-model) must conform to the following interface (not conforming templates
won't raise any compilation error, but will most certainly produce wrong code in
an unspecified manner), with ``XXXXType`` the sub-class name. The interface is
defined in ``generateBipType.mtl``:

* ``generateHeaderBody(anElt: XXXXType, disableSerialization : Boolean)``,
  **mandatory**. The content of the *main* header file. No need to handle the
  multiple-inclusion guards. Always include only the minimum set of files: never
  use the *include everything as it's easier to implement* strategy as you'll
  quickly introduce loops.
* ``generateImplemBody(anElt : XXXXType, disableSerialization: Boolean)``,
  **mandatory**. The content of the cpp file. No need to include the
  corresponding hpp. Only implement class's members or **static**
  functions. Avoid non-static functions as it *violates* the design principles.
* ``generateSubClasses(anElt : XXXXType, aCMakeList : String,
  disableSerialization: Boolean)``, **optional**. When the generation process
  needs to produce more than 1 class for a given BIP type, you need to hook your
  *other templates* in this template. The ``aCMakeList`` is the filename to use to
  append cmake instructions relative to the *other classes* produced.

The ``disableSerialization`` parameter can be set *true* when all serialization
mechanisms should be skipped. This parameter should be moved to some higher
global context instead of being part of all template interfaces.

Examples of templates using the sub-class generation include:
``generatePortType.mtl`` and ``generateConnectorType.mtl``.


Instance deployment code generation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The ``generateDeploy.mtl`` template is responsible for walking the instance
model, that can be seen as a tree if you omit type references that point to the
type model. It uses the recursive aspect of the component hierarchy to *unroll*
the instance tree and create C++ object declaration in an order that meets all
the classes constructors requirements (*eg.* a compound constructor expects
references to all its connectors, priorities, components, exported data and
exported ports). As much as possible, the template uses static initializations
to minimize runtime initializations and allow for better optimization from the
C++ compiler. It means that there is no ``new`` calls in the generated code for
deployment: the size of the system can be statically known after the C++
compiler is done (it does not include, of course, runtime data like interactions
objects) and everything is allocated in the heap.

The generated code includes a ``Component* deploy(int argc, char **argv);``
function that is the entry point that standard engine use. Currently, ``argc``
and ``argv`` are not used. This function returns a pointer to the root component
instance.


CMake
^^^^^

The template ``generateMasterCMakeLists`` produces the main ``CMakeLists.txt``
file that will be used to configure and compile all C++ code produced by the
compiler (*ie.* packages and deployment). It expects a set of parameters from
the user interface. Some of these parameters are directory lists and should be
given as absolute path. Using relative path may or may not work depending on the
specific setup: it is *not* supported and should not be used.

The templates ``startPackageCmake``/``endPackageCmake`` must be called
respectively at the beginning/ending of a package.

Misc
^^^^

The C++ back-end includes 2 *utility* templates:

* ``traceBip.mtl``: contains the needed queries/templates for injecting in the
  C++ code back-links to the BIP code. Some templates can be used to drive the
  GNU Debugger (*aka.* gdb) so that it displays the BIP source code instead of
  the generated C++ code. This features has been prototyped only and has been
  put on hold in favor of other developments. 
* ``gcc.mtl`` : used to store everything specific to the GNU Compiler Collection
  (*aka.* gcc). It is currently nearly empty as it only includes a query for
  asking the compiler not to raise a warning when a specific variable
  declaration is never used.


Tutorial
--------

Debugging a Filter or a Backend
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The way the compiler is built and configured by default in eclipse won't let you
use any of your filters or backend. The compiler will load dynamically the
classes for your filters/backends provided they are in the java classpath.

Adding a new constraint
^^^^^^^^^^^^^^^^^^^^^^^

You must always follow **all** the folowing steps. Do not leave some steps as
*todo* tasks, you will always forget to do them, leading to future bugs, longer
misunderstanding, etc.

* add constraint in the meta-model. Choose a name as discriminant as
  possible. You should include everything possible in the name as the constraint
  name will also be used in error handling. Better use
  ``ConnectorParameterHasBadType`` than ``BadType``.
* commit the change in the ecore file.
* generate the code. This will create an empty method with a ``FIXME`` inside
  (look in the ``Tasks`` perspective in eclipse, the new method should appear
  here).
  
  * open the ``genmodel`` file, right click on ``Bip2`` and run the *Generate
    model code*

* commit the generated code corresponding to the new constraint. In the comment,
  add explicitly that it is only automatic code
* add the corresponding error message and error code in the ``u.v.b.error``
  module:

  * add a new enumeration item in the ``ErrorCodeEnum`` Enum type: item name
    must match the constraint name
  * if needed, add one more mapping in the ''ErrorCodeEnum.userFriendlyNames''
    map to map your newly *verbose* name to some shorter names.
  * add a new string in the error message file
    ``english-strings.properties``. The new string name must match the
    constraint name

* implement the constraint.

  * add **NOT** after the *@generated* in the comment before the method.
  * implement the check. If you need to create error or warning, do the
    following:
  
    * choose between *error* or *warning* by changer (or leaving) the
      ``Diagnostic.ERROR`` as the first parameter of the ``createDiagnostic()``
      method call
    * the 6th parameter is an array of ``Object``. Add the error code
      corresponding to the error/warning in second position of this new array.

* commit the handwritten code and add ``[MODEL CODE MODIF]`` in the commit
  message and give as much info as you can (which constraint, which ticket, ...)
* implement a new unit test

You can see this kind of hack in commits r5062 though r5068 of the BIP2
subversion repository.

Changing the syntax
^^^^^^^^^^^^^^^^^^^

A change in the syntax can impact the compiler in various ways:

* only the first parser pass: most likely, the change is syntatic-suggar
  related. The change is invisible after the first parser (*ie.* the AST
  structure given to the walker is unchanged).
* only the parser: the AST produced is different, and the walker needs to be
  adapted as well, but the resulting model still uses the same metamodel (*ie.*
  still dealing with syntactic suggar).
* parser and meta-model are impacted: this means that you need to change the
  grammar, the walker, the meta-model and also all middleends & backends.

.. IMPORTANT::
   Do not forget to add corresponding tests in the unit test database! Run
   theses tests as much as possible to check that you are not breaking
   something.

Grammar modification
""""""""""""""""""""

Change the ''Bip2.g'' to match your syntax change. If your changes do not change
the kind of AST the parser produces, it's really easy and quick: you're done
(run the ''gencode-for-eclipse'' ant target if you need these changes to be
visible in your eclipse).

If your changes DO change the produced AST, you need to add the *imaginary
nodes* at the top of the ''Bip2.g'' file and proceed with the next section.

Walker modification
"""""""""""""""""""

If you changed the AST produced by the first pass or if you need to change the
model produced, you need to modify ''Bip2Walker.g''.

You need to take *extra* care about the asumptions (often implicit) made at the
interface between the 2 passes. Some abstractions can be safely made in the
walker, but your change may change this: be extra-careful. For example, in the
first pass, the rules will forbid some expressions in some context. No indirect
data reference can be made in an atom transition. But this restriction does not
exist in the walker: the walker trusts the first pass.

Meta-model modification
"""""""""""""""""""""""

If you need to change the meta-model, you should make these changes *before*
changing the walker (you won't be able to change the walker before...).

Middleends & Backends modifications
"""""""""""""""""""""""""""""""""""

After the previous changes are working (you can run the compiler without
executing any middlend/backend to check that everything is fine), you can proceed with
their modifications. 
 

Updating dependencies
^^^^^^^^^^^^^^^^^^^^^

You should always try to stick to latest stable version of all dependencies. Not
doing so may lead to big problems when you will try to update from very old
libraries. It's easier to fix little API change from one version to the next
than fixing a large set of changes.

Usually, you should simply follow these simple steps. Beware that sometimes,
some dependencies must be added or can be removed. For a given compiler module:

* list jar files located in the ''external/'' directory
* check if you have more recent version of these jar files inside your
  ''plugins/'' subdirectory in your eclipse installation.
* for all jar with more recent version, replace old version by the newest
  version
* run the ''Tools/helper-scripts/gen-ivy-deps2.py''::

    externals/ $ ls *.jar | Tools/helper-scripts/gen-ivy-deps2.py

* copy the result inside the ''ivy.xml'' file (first remove the old dependencies
  related to jar files)

That's it. **Always** run all the test before merging. It is very important, as
it has happened that some class moved from one jar to another and the compiler
crashes in very specific cases.
