# NVIDIA TensorRT - Packaging Details

This document describes an approach applied to packaging `libtensorrt`  
for `build2`. In particular, this understanding will be useful when  
upgrading to a new upstream version.

## Cache directory

Downloaded archives are placed in `$out_root` by default. They are not
registered as build2 targets, so `bdep clean` leaves them untouched. Set
one of the two `dir_path` variables below to redirect them to a different
location (for example, a directory shared across multiple build configurations):

  Variable                        Scope
  --------                        -----
  config.tensorrt.cache           global: applies to all packages when set
  config.<pkg>.cache              per-package: overrides the global value

Resolution order (evaluated in `root.build` for each package):

  1. `config.<pkg>.cache` if explicitly set, otherwise
  2. `config.tensorrt.cache` if explicitly set, otherwise
  3. `$out_root` (the package output directory)

The per-package variable uses the package name with hyphens replaced by
underscores. For example, `libtensorrt` uses `config.libtensorrt.cache`.

Set the global variable once to share a cache across all packages:

  bdep init -C @gcc cc config.cxx=g++ \
    "config.tensorrt.cache=/path/to/cache-dir"

Or override a single package:

  b "config.libtensorrt.cache=/path/to/tensorrt-cache-dir"

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
