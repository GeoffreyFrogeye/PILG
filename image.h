class Pixel {
public:
	int Pixel(int typeComposantes, int maxComposante); // Crée l'objet Pixel
	int getR(); // Récupère la composante Rouge
	int getV(); // Récupère la composante Vert
	int getB(); // Récupère la composante Bleu
	int getG(); // Récupère la composante Gris
	bool getN(); // Récupère la composante Noir
	int setR(int R); // Change la composante Rouge
	int setV(int V); // Change la composante Vert
	int setB(int B); // Change la composante Bleu
	int setG(int G); // Change la composante Gris
	int setN(bool N); // Change la composante Noir
	
private:
	int m_typeComposantes; // 0 : N&B, 1 : Niveaux de gris, 2 : RVB
	int m_maxComposante; // Maximum de composante (inutilisé pour binaire)
	int m_R;
	int m_V;
	int m_B;
	int m_G;
	bool m_N;
};

class Image {
public:
	int Image(int dimensionX, int dimensionY, int maxComposante); // Crée l'objet Image
	int point(int x, int y, Pixel pixel); // Définit une couleur au point
};