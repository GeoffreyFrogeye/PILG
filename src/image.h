#include <vector>

typedef Pixel {
	int typeComposantes;
	int maxComposante;
	int r;
	int v;
	int b;
	int g;
	bool n;

} Pixel;

class Image {
public:
	int Image(int dimensionX, int dimensionY, int maxComposante, int typeComposantes); // Crée l'objet Image
	// Getters
	int g_dimensionX();
	int g_dimensionY();
	int g_typeComposante();
	int g_maxComposante();
	Pixel g_point(int x, int y);
	// Setters
	int s_point(int x, int y, Pixel pixel);

private:
	bool enLimitesComposantes(Pixel pixel);
	bool enLimites(int x, int y);
	int m_dimensionX;
	int m_dimensionY;
	int m_typeComposantes; // 0 : N&B, 1 : Niveaux de gris, 2 : RVB
	int m_maxComposante; // Maximum de composante (inutilisé pour binaire)
	vector< vector< Pixel > > m_tab;
};
