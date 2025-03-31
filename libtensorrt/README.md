# libtensort - A C++ library

NVIDIA® TensorRT™ is a C++ library that facilitates high-performance inference
on NVIDIA GPUs. TensorRT takes a trained network, which consists of a network
definition and a set of trained parameters, and produces a highly optimized
runtime engine that performs inference for that network. TensorRT provides APIs
using C++ and Python that help to express deep learning models using the Network
Definition API or load a pre-defined model using the parsers that allow TensorRT
to optimize and run them on an NVIDIA GPU. TensorRT applies graph optimizations,
layer fusion, among other optimizations, while also finding the fastest
implementation of that model leveraging a diverse collection of highly optimized
kernels. TensorRT also supplies a runtime that you can use to execute this
network on NVIDIA’s GPUs.

For more information about TensorRT, visit https://developer.nvidia.com/tensorrt.

## Usage

To start using `libtensorrt` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libtensorrt ^10.8.0
```

Then import the library in your `buildfile`:

```
import libs = libtensorrt%libs{tensorrt}
```


## Importable targets

This package provides the following importable targets:

```
libs{tensorrt}
```
