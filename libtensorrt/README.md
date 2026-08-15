# libtensort - A C++ library

> **NOTE:**  
This package is not open source and does not contain any source code. Instead,
in order to "build" the exported target(s) it downloads (potentially large)
pre-built binaries provided by NVIDIA for the target platform.
>
> CI for this package is disabled due to the above.  
Supported platforms/compilers are Windows/MSVC and Linux/GCC or Clang
(x86_64).

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
depends: libtensorrt ^10.16.1
```

Then import the library in your `buildfile`:

```
import libs = libtensorrt%libs{nvinfer}
```


## Importable targets

This package provides the following importable targets:

```
libs{nvinfer}            # core builder and runtime (main TensorRT API)
libs{nvinfer_plugin}     # standard built-in op plugins (batch norm, RNN cells, etc.)
libs{nvinfer_lean}       # runtime-only nvinfer without the builder, smaller footprint
libs{nvinfer_dispatch}   # forward-compatible dispatch shim, delegates to the installed lean runtime
libs{nvinfer_vc_plugin}  # version-compatible plugin library, pairs with nvinfer_dispatch
libs{nvonnxparser}       # ONNX parser, converts .onnx graphs into TensorRT networks
libs{tensorrt_shim}      # plugin loader shim for version-compatible deployments
```

`libs{tensorrt_shim}` is only available on Linux.
