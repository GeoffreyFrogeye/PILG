int Image::Image(int dimensionX, int dimensionY, int maxComposante, int typeComposantes) { // Crée l'objet Image
	
}
// Getters
int Image::g_dimensionX() {
	return m_dimensionX;
}
int Image::g_dimensionY() {
	return m_dimensionY;

}
int Image::g_typeComposante() {
	return m_typeComposante;
}
int Image::g_maxComposante() {
	return m_typeComposante;

}
int g_point(int x, int y, Pixel &pixel) {
	if (en_Limites(x, y)) {
		pixel = m_tab[x][y];
		return 0;
	} else {
		return 1;
	}
}
// Setters

int Image::s_point(int x, int y, Pixel pixel) {
	if (en_Limites(x, y) && pixel.typeComposantes == Image.g_typeComposante && pixel.maxComposante == Image.g_maxComposante && enLimitesComposantes(pixel)) {
		m_tab[x][y] = pixel;
	}

}

bool Image::enLimitesComposantes(Pixel pixel) {
	switch (pixel.typeComposantes) {
		case 0:
			return true;
			break;
		case 1:
			return pixel.m <= pixel.maxComposante;
			break;
		case 2:
			return (pixel.r <= pixel.maxComposante && pixel.v <= pixel.maxComposante && pixel.b <= pixel.maxComposante);
			break;
		default:
			return false;
			break;
	}
}

bool Image::enLimites(int x, int y) {
	return (x >= 0 && x < g_dimensionX && y >= 0 && y < g_dimensionY);
}