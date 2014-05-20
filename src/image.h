#include <vector>

typedef enum {PILG_BIN, PILG_NIV, PILG_RVB} PILG_Comp;

typedef struct Pixel {
    PILG_Comp typeComposantes;
    int maxComposante;
    int r;
    int v;
    int b;
    int g;
    bool n;
} Pixel;

class Image {
public:
    Image(int dimensionX, int dimensionY, int maxComposante,
          PILG_Comp typeComposantes);
    // Getters
    int g_dimensionX() const;
    int g_dimensionY() const;
    PILG_Comp g_typeComposantes() const;
    int g_maxComposante() const;
    int g_pixel(int x, int y, Pixel &pixel) const;
    // Setters
    int s_pixel(int x, int y, Pixel pixel);
    // Utilitaires
    Pixel g_pixelVide() const;
    Image g_vide() const;
    // Validateurs
    bool v_pixel(Pixel pixel) const;
    bool v_dimensions(int x, int y) const;

private:
    // Variables
    int m_dimensionX;
    int m_dimensionY;
    PILG_Comp m_typeComposantes;
    int m_maxComposante;  // Maximum de composante (sauf binaire)
    std::vector< std::vector< Pixel > > m_tab;
};
