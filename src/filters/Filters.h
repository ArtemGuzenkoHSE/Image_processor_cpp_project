#pragma once

#include "Image.h"

#include <memory>
#include <string>
#include <vector>

class BaseFilter {
public:
    virtual Image Apply(const Image &image) = 0;
    virtual std::string GetName() const = 0;
    virtual ~BaseFilter() = default;
};

class GrayscaleFilter : public BaseFilter {
public:
    Image Apply(const Image &image) override;
    std::string GetName() const override;
};

class NegativeFilter : public BaseFilter {
public:
    Image Apply(const Image &image) override;
    std::string GetName() const override;
};

class CropFilter : public BaseFilter {
private:
    int width_, height_;

public:
    explicit CropFilter(int width, int height);
    Image Apply(const Image &image) override;
    std::string GetName() const override;
};

class SharpeningFilter : public BaseFilter {
public:
    Image Apply(const Image &image) override;
    std::string GetName() const override;
};

class EdgeDetectionFilter : public BaseFilter {
private:
    double threshold_;

public:
    explicit EdgeDetectionFilter(double threshold);
    Image Apply(const Image &image) override;
    std::string GetName() const override;
};

class BlurFilter : public BaseFilter {
private:
    double sigma_;

public:
    explicit BlurFilter(double sigma);
    Image Apply(const Image &image) override;
    std::string GetName() const override;

private:
    Color CalculateBlurredPixel(const Image &image, int x, int y) const;
};

class ComicFilter : public BaseFilter {
public:
    ComicFilter(int r_levels, int g_levels, int b_levels, float contrast, float saturation, double edge_threshold,
                Color outline_color);

    Image Apply(const Image &image) override;
    std::string GetName() const override;

private:
    int r_levels_, g_levels_, b_levels_;
    float contrast_, saturation_;
    double edge_threshold_;
    Color outline_color_;
};

class FilterFactory {
public:
    static std::unique_ptr<BaseFilter> Create(const std::string &name, const std::vector<std::string> &args);
};
