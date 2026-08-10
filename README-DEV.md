# NVIDIA TensorRT - Packaging Details

This document describes an approach applied to packaging `libtensorrt`  
for `build2`. In particular, this understanding will be useful when  
upgrading to a new upstream version.

## Release New Version
1. Go to [NVIDIA's download page](https://developer.nvidia.com/tensorrt/download).  
   _Note: This requires logging in with (free) developer account._
2. Navigate to the URL list with the version you'd like to package.
3. For each platform (eg. `x86_64-windows`, `x86_64-linux`, `aarch64-linux`),
   copy the download URL's path (relative to `baseUrl`) and update the
   corresponding platform's `relativePath`/`version` entry in
   [manifest.json](./libtensorrt/libtensorrt/manifest.json).  
   _Note: Pick the ones built for the latest CUDA version_.
4. Update `version` & `upstream-version` in [`manifest`](./libtensorrt/manifest).  
   _Note: `upstream-version` is the one embedded in the URL._
