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
#include <memory>
#include <stdio.h>

namespace {
  class logger: public nvinfer1::ILogger {
    void log (Severity s, const char* m) noexcept override {
      if (s <= Severity::kWARNING)
        printf ("  trt: %s\n", m);
    }
  };
}

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

  int count = 0;
  cudaError_t err = cudaGetDeviceCount(&count);
  printf("cudaGetDeviceCount: %s (%d devices)\n", cudaGetErrorString(err), count);

  if (err != cudaSuccess || count == 0) {
    printf ("no device, skipping the engine build\n");
    return 0;
  }

  // buildSerializedNetwork() loads nvinfer_builder_resource_<arch> by bare
  // name.
  //
  logger log;
  std::unique_ptr<nvinfer1::IBuilder> builder (
    nvinfer1::createInferBuilder (log));
  assert (builder);

  std::unique_ptr<nvinfer1::INetworkDefinition> network (
    builder->createNetworkV2 (0));
  assert (network);

  nvinfer1::ITensor* in (
    network->addInput ("in", nvinfer1::DataType::kFLOAT,
                       nvinfer1::Dims4 {1, 1, 1, 4}));
  assert (in != nullptr);

  nvinfer1::IActivationLayer* relu (
    network->addActivation (*in, nvinfer1::ActivationType::kRELU));
  assert (relu != nullptr);

  relu->getOutput (0)->setName ("out");
  network->markOutput (*relu->getOutput (0));

  std::unique_ptr<nvinfer1::IBuilderConfig> config (
    builder->createBuilderConfig ());
  assert (config);

  std::unique_ptr<nvinfer1::IHostMemory> plan (
    builder->buildSerializedNetwork (*network, *config));
  assert (plan && plan->size () != 0);

  printf ("buildSerializedNetwork(): %zu bytes\n", plan->size ());

  return 0;
}
