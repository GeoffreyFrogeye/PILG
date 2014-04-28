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
    int g_point(unsigned int x, unsigned int y, Pixel &pixel) const;
    // Setters
    int s_point(unsigned int x, unsigned int y, Pixel pixel);
    // Utilitaires
    Pixel g_pixelVide() const;

private:
    // Utilitaires
    static bool enLimitesComposantes(Pixel pixel);
    bool enLimites(unsigned int x, unsigned int y) const;
    // Variables
    unsigned int m_dimensionX;
    unsigned int m_dimensionY;
    PILG_Comp m_typeComposantes;  // 0 : N&B, 1 : Niveaux de gris, 2 : RVB
    unsigned int m_maxComposante;  // Maximum de composante (sauf binaire)
    std::vector< std::vector< Pixel > > m_tab;
};
