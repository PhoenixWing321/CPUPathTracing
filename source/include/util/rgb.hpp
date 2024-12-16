#pragma once

#include <glm/glm.hpp>
#include <array>

// class FilmRGB Lerp(const FilmRGB &a, const FilmRGB &b, float t);

class FilmRGB {
public:
    static FilmRGB GenerateHeatmapRGB(float t);

    FilmRGB(int r, int g, int b) : r(r), g(g), b(b) {}

    FilmRGB(const glm::vec3 &color);

    operator glm::vec3() const;
public:
    int r, g, b;
};

FilmRGB Lerp(const FilmRGB &a, const FilmRGB &b, float t);
