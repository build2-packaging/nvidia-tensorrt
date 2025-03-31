#include <NvInfer.h>
#include <NvInferPluginUtils.h>
#include <NvInferRuntime.h>
#include <NvInferVersion.h>
#include <NvOnnxParser.h>
#include <cuda.h>
#include <cuda_runtime_api.h>

#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <stdio.h>

int main() {
  int version = 0, major = 0, minor = 0, patch = 0;

  printf("NV_TENSORRT_MAJOR|MINOR|PATCH: %d.%d.%d\n", NV_TENSORRT_MAJOR,
         NV_TENSORRT_MINOR, NV_TENSORRT_PATCH);

  version = getInferLibVersion();
  major = version / 10000;
  minor = (version / 100) % 100;
  patch = version % 100;
  printf("getInferLibVersion(): %d.%d.%d (%d)\n", major, minor, patch, version);

  version = getNvOnnxParserVersion();
  major = version / 10000;
  minor = (version / 100) % 100;
  patch = version % 100;
  printf("getNvOnnxParserVersion(): %d.%d.%d (%d)\n", major, minor, patch,
         version);
  return 0;
}
