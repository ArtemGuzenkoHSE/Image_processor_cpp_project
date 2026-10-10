#include "Image.h"
#include <vector>
#pragma once

Color CalculatePixelInMatrix(const Image &image, int x, int y,
                             const std::vector<std::vector<int>> &multiplication_matrix);
