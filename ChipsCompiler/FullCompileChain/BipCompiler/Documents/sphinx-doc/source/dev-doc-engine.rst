Developer reference for Engines
===============================

.. _dev-doc-engine_std_API-label:

Standard engine
---------------

Usually, back-end output and runtime are closely tied and hardly independent. In
order to avoid the dispersion of the development effort by having multiple
back-end/engine combination, we have introduced a *standard* API between
produced C++ code and engine. This means that the regular back-end can be used
with several engines, provided that these engines only rely on the published
API.

Currently, we have two standard engines:

* the *reference engine* that strictly implements the BIP semantic as defined
  by the language with no effort towards optimization. Readability has
  precedence over performances. This leads to a very slow execution platform in
  some not-so-rare use cases.
* an *optimized engine*, still in early stage development. Even if this engine
  implements *basic* optimization, the performance boost is huge.

Full API
--------

Need for a documentation about this API.
