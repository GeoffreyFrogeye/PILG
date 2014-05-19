#include "image.h"

Image::Image(int dimensionX, int dimensionY, int maxComposante, PILG_Comp typeComposantes): m_dimensionX(dimensionX), m_dimensionY(dimensionY), m_maxComposante(maxComposante), m_typeComposantes(typeComposantes) {
    Pixel pixelVide = g_pixelVide();
    for (int xT = 0; xT < dimensionX; xT++) {
        std::vector< Pixel > colonne;
        for (int yT = 0; yT < dimensionX; yT++) {
            colonne.push_back(pixelVide);
        }
        m_tab.push_back(colonne);
    }
}

// Getters
int Image::g_dimensionX() const {
    return m_dimensionX;
}

int Image::g_dimensionY() const {
    return m_dimensionY;
}

PILG_Comp Image::g_typeComposantes() const {
    return m_typeComposantes;
}

int Image::g_maxComposante() const {
    return m_maxComposante;
}

int Image::g_pixel(int x, int y, Pixel &pixel) const {
    if (v_dimensions(x, y)) {
        pixel = m_tab[x][y];
        return 0;
    } else {
        pixel = g_pixelVide();
        return 1;
    }
}

// Setters
int Image::s_pixel(int x, int y, Pixel pixel) {
    if (v_dimensions(x, y) && v_pixel(pixel)) {
        m_tab[x][y] = pixel;
        return 0;
    } else {
        return 1;
    }
}

// Utilitaires
Pixel Image::g_pixelVide() const {
    Pixel pixel;
    pixel.typeComposantes = m_typeComposantes;
    pixel.maxComposante = m_maxComposante;
    switch (pixel.typeComposantes) {
    case PILG_BIN:
        pixel.b = false;
        break;
    case PILG_NIV:
        pixel.g = 0;
        break;
    case PILG_RVB:
        pixel.r = pixel.v = pixel.b = 0;
        break;
    }
    return pixel;
}

Image Image::g_vide() const {
    return Image(m_dimensionX, m_dimensionY, m_maxComposante, m_typeComposantes);
}

// Validateurs
bool Image::v_pixel(Pixel pixel) const {
    if  (pixel.typeComposantes == m_typeComposantes
            && pixel.maxComposante == m_maxComposante) {
        switch (pixel.typeComposantes) {
        case PILG_BIN:
            return true;
            break;
        case PILG_NIV:
            return (pixel.g <= pixel.maxComposante);
            break;
        case PILG_RVB:
            return (pixel.r <= pixel.maxComposante
                    && pixel.v <= pixel.maxComposante
                    && pixel.b <= pixel.maxComposante);
            break;
        default:
            return false;
            break;
        }
    } else {
        return false;
    }
}

bool Image::v_dimensions(int x, int y) const {
    return (x >= 0 && x < m_dimensionX && y >= 0 && y < m_dimensionY);
}
