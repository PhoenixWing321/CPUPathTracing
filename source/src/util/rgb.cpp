
#include "util/rgb.hpp" 
 
FilmRGB FilmRGB::GenerateHeatmapRGB(float t) {
    std::array<FilmRGB, 25> color_pallet {
        FilmRGB { 68, 1, 84 },
        FilmRGB { 71, 17, 100 },
        FilmRGB { 72, 31, 112 },
        FilmRGB { 71, 45, 123 },
        FilmRGB { 68, 58, 131 },

        FilmRGB { 64, 70, 136 },
        FilmRGB { 59, 82, 139 },
        FilmRGB { 54, 93, 141 },
        FilmRGB { 49, 104, 142 },
        FilmRGB { 44, 114, 142 },

        FilmRGB { 40, 124, 142 },
        FilmRGB { 36, 134, 142 },
        FilmRGB { 33, 144, 140 },
        FilmRGB { 31, 154, 138 },
        FilmRGB { 32, 164, 134 },

        FilmRGB { 39, 173, 129 },
        FilmRGB { 53, 183, 121 },
        FilmRGB { 71, 193, 110 },
        FilmRGB { 93, 200, 99 },
        FilmRGB { 117, 208, 84 },

        FilmRGB { 143, 215, 68 },
        FilmRGB { 170, 220, 50 },
        FilmRGB { 199, 224, 32 },
        FilmRGB { 227, 228, 24 },
        FilmRGB { 253, 231, 37 },
    };

    if (t < 0 || t >= 1) {
        return FilmRGB { 255, 0, 0 };
    }
    float idx_float = t * color_pallet.size();
    size_t idx = glm::floor(idx_float);
    return Lerp(color_pallet[idx], color_pallet[idx + 1], glm::fract(idx_float));
}
 
FilmRGB::FilmRGB(const glm::vec3 &color) {
    r = glm::clamp<int>(glm::pow(color.x, 1.0 / 2.2) * 255, 0, 255);
    g = glm::clamp<int>(glm::pow(color.y, 1.0 / 2.2) * 255, 0, 255);
    b = glm::clamp<int>(glm::pow(color.z, 1.0 / 2.2) * 255, 0, 255);
}

FilmRGB::operator glm::vec3() const  {
    return glm::vec3 {
        glm::pow(r / 255.f, 2.2),
        glm::pow(g / 255.f, 2.2),
        glm::pow(b / 255.f, 2.2),
    };
} 

FilmRGB Lerp(const FilmRGB &a, const FilmRGB &b, float t) {
    return FilmRGB {
        glm::clamp<int>(a.r + (b.r - a.r) * t, 0, 255),
        glm::clamp<int>(a.g + (b.g - a.g) * t, 0, 255),
        glm::clamp<int>(a.b + (b.b - a.b) * t, 0, 255),
    };
}
