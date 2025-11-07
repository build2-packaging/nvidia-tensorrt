# NVIDIA TensorRT - Packaging Details

This document describes an approach applied to packaging `libtensorrt`  
for `build2`. In particular, this understanding will be useful when  
upgrading to a new upstream version.

## Release New Version
1. Go to [NVIDIA's download page](https://developer.nvidia.com/tensorrt/download).  
   _Note: This requires logging in with (free) developer account._
2. Navigate to the URL list with the version you'd like to package.
3. For each platform (eg. Windows & Linux, x86_64 & ARM), copy the  
   download URL and update the corresponding entry in [redistrib.json](./libtensorrt/libtensorrt/redistrib.json).  
   _Note: Pick the ones built for the latest CUDA version_.
4. Update `version` & `upstream-version` in [`manifest`](./libtensorrt/manifest).  
   _Note: `upstream-version` is the one embedded in the URL._
