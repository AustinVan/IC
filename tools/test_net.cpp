// Copyright 2014 BVLC and contributors.
//
// This is a simple script that allows one to quickly test a network whose
// structure is specified by text format protocol buffers, and whose parameter
// are loaded from a pre-trained network.
// Usage:
//    test_net net_proto pretrained_net_proto iterations [CPU/GPU]

#include <cuda_runtime.h>

#include <cstring>
#include <cstdlib>
#include <vector>
#include <caffe/util/benchmark.hpp>
#include <caffe/common.hpp>
#include "caffe/caffe.hpp"

using namespace caffe;  // NOLINT(build/namespaces)
using caffe::Timer;
int main(int argc, char** argv) {
  if (argc < 3 || argc > 6) {
    LOG(ERROR) << "test_net net_proto pretrained_net_proto iterations "
        << "[CPU/GPU] [Device ID]";
    return 1;
  }

  Caffe::set_phase(Caffe::TEST);

  if (argc >= 5 && strcmp(argv[4], "GPU") == 0) {
    Caffe::set_mode(Caffe::GPU);
    int device_id = 0;
    if (argc == 6) {
      device_id = atoi(argv[5]);
    }
    Caffe::SetDevice(device_id);
    LOG(ERROR) << "Using GPU #" << device_id;
  } else {
    LOG(ERROR) << "Using CPU";
    Caffe::set_mode(Caffe::CPU);
  }

  Net<float> caffe_test_net(argv[1]);
  caffe_test_net.CopyTrainedLayersFrom(argv[2]);

  int total_iter = atoi(argv[3]);
  LOG(ERROR) << "Running " << total_iter << " iterations.";
  Timer total_timer;
  total_timer.Start();
  Timer forward_timer;
  Timer timer;
  double forward_time = 0.0;
  double test_accuracy = 0;
  for (int i = 0; i < total_iter; ++i) {
    forward_timer.Start();
    const vector<Blob<float>*>& result = caffe_test_net.ForwardPrefilled();
    forward_time += forward_timer.MilliSeconds();
    test_accuracy += result[0]->cpu_data()[0];
    LOG(ERROR) << "Batch " << i << ", accuracy: " << result[0]->cpu_data()[0];
  }
  total_timer.Stop();
  LOG(INFO) << "Average Forward pass: " << forward_time / total_iter << " ms.";
  test_accuracy /= total_iter;
  LOG(ERROR) << "Test accuracy: " << test_accuracy;

  return 0;
}
