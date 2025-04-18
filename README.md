# NVIDIA® TensorRT™ SDK

> **NOTE:**  
These packages are not open source and do not contain any source code. Instead,
in order to "build" the exported target(s) they download (potentially large)
pre-built binaries provided by NVIDIA for the target platform.
>
> CI for these packages are disabled due to the above.  
Supported platforms/compilers are Windows/MSVC. Linux binaries exist but are
currently not available through these packages.

This is a `build2` package repository for [NVIDIA® TensorRT™ SDK](https://developer.nvidia.com/tensorrt).

NVIDIA TensorRT is an SDK for high-performance deep learning inference,
includes a deep learning inference optimizer and runtime that delivers
low latency and high throughput for inference applications.

This file contains setup instructions and other details that are more
appropriate for package development rather than consumption. If you want to use
`nvidia-tensorrt` in your `build2`-based project, then instead see the accompanying
package(s) corresponding [`README.md`](libtensorrt/README.md) file.

The development setup for `nvidia-tensorrt` uses the standard `bdep`-based workflow.
For example:

```
git clone https://github.com/build2-packaging/nvidia-tensorrt
cd nvidia-tensorrt

bdep init -C @msvc c config.c=cl.exe
bdep update
bdep test
```
