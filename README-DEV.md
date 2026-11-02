# Maintaining this package

`libtensorrt` is the only package here. It has the same shape as the packages
in `nvidia-cuda-toolkit`, which it depends on. The buildfile comments carry
the details at the point of use.

## What the package is

    libtensorrt/manifest.json   which TensorRT archive to fetch, per platform
    libtensorrt/package.json    which extracted files become which targets
    libtensorrt/buildfile       the loop that turns package.json into targets
    build/root.build            the cache configuration variable

`redist.build` at the root holds the download and extract machinery,
symlinked into the package and sourced by its buildfile. Nothing is compiled:

    archive{...}            download the platform archive into the cache
    extract{...}            unpack into $out_base, discovering the files
    lib{} exe{} file{}      stamp those files as targets

`manifest.json`: `baseUrl`, `includeDirs` (the public include roots), and per
platform `relativePath`. There is no index to fetch, NVIDIA publishes none
for TensorRT.

`package.json`: per platform a `libs` and an `exes` object. Per library,

    linkage     shared, static or binless, see below
    linked      a DLL together with its link-time file
    shared      a shared object linked directly
    archives    static archives, this library's own one first
    runtime     loaded at run time, never linked
    resources   data files installed verbatim where upstream expects them
    depends     another library in this same package

and per executable `path` and `depends`. Every platform section is always
declared and gated with `include =`, so the build graph is the same in every
configuration.

## Release a new version

1. Go to [NVIDIA's download page](https://developer.nvidia.com/tensorrt/download),
   which needs a free developer account.
2. Navigate to the URL list for the version to package.
3. Per platform, copy the download URL path relative to `baseUrl` into that
   platform's `relativePath` in
   [manifest.json](./libtensorrt/libtensorrt/manifest.json). Pick the ones
   built for the latest CUDA version.
4. Update `version` and `upstream-version` in
   [manifest](./libtensorrt/manifest). `upstream-version` is the one embedded
   in the URL.
5. `bdep update`, then check that every extracted file under `out_base` that
   should ship is named in `package.json`. Upstream adds and renames
   libraries between releases.

## Cache directory

Archives land in `$out_root` by default. Only a symlink to the archive is a
target, so `b clean` leaves the cache alone. Set `config.libtensorrt.cache`
for this package or `config.tensorrt.cache` for all, the per-package value
wins.

    b "config.libtensorrt.cache=/path/to/cache"

`config.tensorrt.cache` is read at configure time into the per-package value,
so changing it afterwards needs a reconfigure.

## Library linkage

`linkage` says what the binary installed under that library's name actually
is, and picks the aggregate target `libs{}`, `liba{}` or `lib{}`. It is not
derivable from the file name: NVIDIA ships both real import libraries and
static archives of loader shims as `lib/<name>.lib`. Look inside:

    lib /list <file>.lib

`.dll` members mean `shared`, `.obj` members mean `static`, even when the
archive only `LoadLibrary`s a DLL. build2 applies the same test to the
installed file, so the two have to agree. Disagree and consuming an installed
prefix fails with `dependency cycle detected`, far from the cause. A stray
`*-unused.*.pc` is inert and expected.

As of 10.16.1 every TensorRT library is shared. `cuda-cudart` is not, which
is why the imports here spell `lib{}` and never `libs{}`: the group picks the
member, the importer does not.

## Testing

Two scripts at the repository root, each documented in its own header. Both
take an `nvidia-cuda-toolkit` checkout, since this package is neither
buildable nor consumable without it:

    bx test-install.bx <scratch-dir> <toolkit-dir>   both repositories, one prefix
    bx test-dist.bx <scratch-dir> <toolkit-dir>      the package from its distribution

Run both on every target platform before publishing.
