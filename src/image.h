#include <vector>

typedef enum {PILG_BIN, PILG_NIV, PILG_RVB} PILG_Comp;

typedef struct Pixel {
    PILG_Comp typeComposantes;
    unsigned int maxComposante;
    unsigned int r;
    unsigned int v;
    unsigned int b;
    unsigned int g;
    bool n;
} Pixel;

class Image {
public:
    Image(unsigned int dimensionX, unsigned int dimensionY, unsigned int maxComposante, PILG_Comp typeComposantes);
    // Getters
    unsigned int g_dimensionX() const;
    unsigned int g_dimensionY() const;
    PILG_Comp g_typeComposantes() const;
    unsigned int g_maxComposante() const;
    int g_pixel(unsigned int x, unsigned int y, Pixel &pixel) const;
    // Setters
    int s_pixel(unsigned int x, unsigned int y, Pixel pixel);
    // Utilitaires
    Pixel g_pixelVide() const;
    // Validateurs
    bool v_pixel(Pixel pixel) const;
    bool v_dimensions(unsigned int x, unsigned int y) const;

private:
    // Variables
    unsigned int m_dimensionX;
    unsigned int m_dimensionY;
    PILG_Comp m_typeComposantes;
    unsigned int m_maxComposante;  // Maximum de composante (sauf binaire)
    std::vector< std::vector< Pixel > > m_tab;
};
