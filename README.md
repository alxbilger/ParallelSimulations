# ParallelSimulations

Simple C++-based example running two SOFA simulations in parallel.

The simulations are simple cantilever beams using a corotational FEM formulation. They are defined with the `simpleapi` from SOFA: objects are defined using strings instead of C++ objects. The underlying C++ objects are instantiated at runtime using the Object Factory. It eases the writing of C++ scenes.

The goal of this example is to check that two identical simulations running in parallel take the same time than a single simulation.

## Compilation Instructions

Read [SOFA documentation](https://www.sofa-framework.org/community/doc/plugins/build-a-plugin-from-sources/)

## Links

- [SOFA](https://github.com/sofa-framework/sofa)
