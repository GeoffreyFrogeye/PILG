class Fenetre {

public: 
	int Fenetre(int dimensionX, int dimensionY, string nom); // Crée une fenêtre
	int setNom(string nom); // Change le nom de la fenêtre
	int point(int x, int y);
private:
	int dimensionX; // Stocke les dimensions X de la fenêtre
	int dimensionY; // Stocke les dimensions Y de la fenêtre
	string m_nom; // Stocke le nom de la fenêtre
	vector< vector< int[3] > > tab; // Tableau qui stocke les pixels
};
