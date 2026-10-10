#pragma once

#include <cstdint>
#include <vector>
#include <stdexcept>

using BYTE = uint8_t;

class Color {
private:
    BYTE red_, green_, blue_;

public:
    Color() = default;
    Color(BYTE red, BYTE green, BYTE blue);

    BYTE GetRed() const;
    BYTE GetGreen() const;
    BYTE GetBlue() const;

    void SetRed(BYTE value);
    void SetGreen(BYTE value);
    void SetBlue(BYTE value);

    bool operator==(const Color &other) const;
    bool operator!=(const Color &other) const;
};

class Image {
private:
    int width_, height_;
    std::vector<Color> pixels_;

public:
    Image();
    Image(int width, int height);

    int GetWidth() const;
    int GetHeight() const;

    Color &SetColor(int x, int y);
    const Color &GetColor(int x, int y) const;

    int GetPudding() const;
    bool IsCorrect(int x, int y) const;
};
