Template Manager (Tm) is a macroprocessor that takes a code template
and some datastructure definitions, and generates source code for
an arbitrary programming language. Thus, by using Tm you can have
templates in any programming language.

           +---------------+        +----------------+
           | datastructure |        |      code      |
           |   definition  |        |    template    |
           +---------------+        +----------------+
                  |                         |
                  -----------      ----------
                            |      |
                            V      V
                         /-------------\
                         |     Tm      |
                         |             |
                         \-------------/
                                |
                                V
                        +---------------+
                        |    source     |
                        |     code      |
                        +---------------+

Although it has been used a general-purpose preprocessor and template
language, it has special support for the generation of data-structure
manipulation code. We use it extensively to generate C code to manipulate
the abstract syntax trees of our compiler. The generated code comprises
tree manipulation code, but also `tree walkers' to apply user-provided
functions on all instances of specific node types, and analyzers that
apply a reduction over a whole tree of different node types.

The kernel distribution package of Tm contains extensive C templates
(including the tree walker and analyzer templates described above)
and a support library. They have been tested and used extensively in
the past ten years. These templates have been used in more than ten
medium and large programming project.  There are separate packages on
the web site with a Pascal and a Miranda template, but these have been
used less intensively.

Tm is flexible enough that useful templates can be written for any
sufficiently powerful programming language. For example, I have
written templates for Lisp and for the functional programming
language Clean, although these are not good enough for public
release. Templates for languages such as Java and Fortran, and for
other functional languages, are also eminently possible.

By using templates, especially the standard templates, you can reap
the benefits of any template: the code is re-used more intensively, is
therefore tested more intensively, is more likely to be documented, and
is standardized.

All Tm-related software is licensed under the Gnu Public License (GPL), or
the Library Gnu Public License (LGPL).

Tm is used extensively in our Timber compiler, a static compiler for
a superset of Java. The Timber compiler has its own GitHub repository at 

<https://github.com/CvR42/timber-compiler>

To give an indication of how intensively Tm is used in the Timber compiler:
the Spar/Java frontend of the compiler has 47433 lines of code in Tm input
files, Yacc input files, and non-generated C source and header files. The
final C source and header files (from Yacc, Tm, or not generated) have
a total of 136681 lines of code.
