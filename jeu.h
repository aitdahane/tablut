


#ifndef DEF_JEU
#define DEF_JEU void regles(SDL_Surface *Ecran);void menuSecondaire(SDL_Surface *Ecran);
    void tourOrdinateur(SDL_Surface* Ecran,int* T,int* computer,int* player,int *Deplacer);

    void vsOrdinateur(SDL_Surface *Ecran);

    int blancBloque(int *T,int i,int j);

    int positionBloquante(int *T,int i,int j);

    int captureRoi(int *T,int i,int j);

    void afficherPlateau(SDL_Surface *Ecran);

    void vsJoueur(SDL_Surface* Ecran);

    void afficherPions(SDL_Surface *Ecran,int* T);

    void deplacerPion(SDL_Surface* Ecran,int* T,SDL_Rect position,int* player,int* c,int* d,int *Deplacer);

    int prisePion(SDL_Surface* Ecran,int* T,SDL_Rect position,int* player,int* Deplacer);

#endif // DEF_JEU
