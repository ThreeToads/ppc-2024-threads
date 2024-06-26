// Copyright 2024 Vanushkin Dmitry3

#include "seq/vanushkin_d_sobel_operator/include/sobel_operator_seq.hpp"

#include <cmath>

ConvolutionKernel SobelOperatorSequential::convolutionByX = {{-1, 0, +1}, {-2, 0, +2}, {-1, 0, +1}};

ConvolutionKernel SobelOperatorSequential::convolutionByY = {{-1, -2, -1}, {0, 0, 0}, {+1, +2, +1}};

bool SobelOperatorSequential::validation() {
  internal_order_test();
  auto& inputsCount = taskData->inputs_count;
  auto& outputsCount = taskData->outputs_count;
  auto& inputs = taskData->inputs;
  auto& outputs = taskData->outputs;

  if (inputsCount.size() != 2 || outputsCount.size() != 2 || inputs.size() != 1 || outputs.size() != 1) {
    return false;
  }

  if (inputsCount[0] - outputsCount[0] != 2 || inputsCount[1] - outputsCount[1] != 2) {
    return false;
  }

  if (inputs[0] == nullptr || outputs[0] == nullptr) {
    return false;
  }

  return true;
}

bool SobelOperatorSequential::pre_processing() {
  internal_order_test();
  try {
    imageHeight = taskData->inputs_count[0];
    imageWidth = taskData->inputs_count[1];

    auto square = imageHeight * imageWidth;

    grayscaleImage = {};
    grayscaleImage.reserve(square);

    const auto* inputImage = reinterpret_cast<const Color*>(taskData->inputs[0]);

    for (size_t i = 0; i < square; ++i) {
      grayscaleImage.push_back(inputImage[i].to_grayscale());
    }

    resultImage = std::vector<Grayscale>((imageWidth - 2) * (imageHeight - 2), 0);
    return true;
  } catch (...) {
    return false;
  }
}

bool SobelOperatorSequential::run() {
  internal_order_test();
  for (size_t y = 1; y < imageHeight - 1; ++y) {
    for (size_t x = 1; x < imageWidth - 1; ++x) {
      auto resultIntensity = apply_convolution(x, y);
      resultImage[(y - 1) * (imageWidth - 2) + (x - 1)] = resultIntensity;
    }
  }
  return true;
}

bool SobelOperatorSequential::post_processing() {
  internal_order_test();
  try {
    auto* outputImage = reinterpret_cast<Grayscale*>(taskData->outputs[0]);
    std::copy(resultImage.cbegin(), resultImage.cend(), outputImage);
    return true;
  } catch (...) {
    return false;
  }
}

Grayscale SobelOperatorSequential::apply_convolution(size_t x, size_t y) {
  auto dx = 0;
  auto dy = 0;

  for (int j = -1; j <= 1; ++j) {
    for (int i = -1; i <= 1; ++i) {
      auto intensity = grayscaleImage[(y + j) * imageWidth + (x + i)];
      dx += convolutionByX[j + 1][i + 1] * intensity;
      dy += convolutionByY[j + 1][i + 1] * intensity;
    }
  }

  return static_cast<Grayscale>(std::min(255, static_cast<int>(sqrt(dx * dx + dy * dy))));
}
