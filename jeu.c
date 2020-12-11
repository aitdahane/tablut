#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <time.h>

#include "jeu.h"

void tourOrdinateur(SDL_Surface* Ecran,int* T,int* turn,int* player,int *Deplacer)
{
    int k1,k2; /// Il vont servir pour indexer un pion ou un case s�lctionn�
    int c,d;
    int e;
    srand(time(NULL));
    //coupOrdinateur=1;
    SDL_Rect position;
    *player=0;
    e=0;
    if (*turn==0) /// Si l'ordinateur est le joueur Blanc
    {
        do{
            do{                         /// On cherche un pion blanc ou le roi
                k1=rand()%9; ///On g�n�re deux indice
                k2=rand()%9;
            }while ((*(T+k1*9+k2)!=2)&&(*(T+k1*9+k2)!=1));

            if (*(T+k1*9+k2)==2)  /// Si Blanc
            {
                position.x=80+40*k2;     ///On r�cup�re la position du pion s�l�ctionn�
                position.y=80+40*k1;
                deplacerPion(Ecran, T,position,player,&c,&d,Deplacer); ///On affiche l'itin�raire
                do{
                        k1=rand()%9;
                        k2=rand()%9;
                }while(*(T+k1*9+k2)!=-3);
                position.x=80+40*k2;     ///On r�cup�re la position du pion s�l�ctionn�
                position.y=80+40*k1;
                deplacerPion(Ecran, T, position,player, &c, &d,Deplacer);
                e=1;
                prisePion(Ecran,T,position,player,Deplacer);

            }
            else if (*(T+k1*9+k2)==1)  /// Si Roi
            {
                position.x=80+40*k2;     ///On r�cup�re la position du pion s�l�ctionn�
                position.y=80+40*k1;
                deplacerPion(Ecran, T,position,player,&c,&d,Deplacer); ///On affiche l'itin�raire
                do{
                        k1=rand()%9;
                        k2=rand()%9;
                }while(*(T+k1*9+k2)!=-2);
                position.x=80+40*k2;     ///On r�cup�re la position du pion s�l�ctionn�
                position.y=80+40*k1;
                deplacerPion(Ecran, T, position,player, &c, &d,Deplacer);
                e=1;
                prisePion(Ecran,T,position,player,Deplacer);

                }

        }while(e==0);
        }
    else if (*turn==1)
    {do{
        do{                         /// On cherche al�atoirement un pion noir

            k1=rand()%9; //On g�n�re deux indice
            k2=rand()%9;
        }while (*(T+k1*9+k2)!=3);
        position.x=80+40*k2;     ///On r�cup�re la position du pion s�l�ctionn�
        position.y=80+40*k1;
        deplacerPion(Ecran, T,position,player,&c,&d,Deplacer); ///On affiche l'itin�raire
        do{
            k1=rand()%9;
            k2=rand()%9;
        }while(*(T+k1*9+k2)!=-3);
        position.x=80+40*k2;     ///On r�cup�re la position du pion s�l�ctionn�
        position.y=80+40*k1;
        deplacerPion(Ecran, T, position,player, &c, &d,Deplacer);
        e=1;
        prisePion(Ecran,T,position,player,Deplacer);

    }while(e==0);


}
}



void vsOrdinateur(SDL_Surface *Ecran)
{
    int continuer=1;
    SDL_Event event;

    SDL_Rect positionActuel;

    SDL_Surface *homme,*ordinateur;
    SDL_Rect positionHomme,positionOrdinateur;

    int M[9][9]={{0,-1,-1,3,3,3,-1,-1,0},      /// -1 signifie un case vide
                 {-1,-1,-1,-1,3,-1,-1,-1,-1},       /// 0 signifie un case d'angle ou le Konakis
                 {-1,-1,-1,-1,2,-1,-1,-1,-1},       /// 1 signifie que ce case contient le roi
                 {3,-1,-1,-1,2,-1,-1,-1,3},       /// 2 signifie que ce case contient un pion blanc
                 {3,3,2,2,1,2,2,3,3},       /// 3 signifie que ce case contient un pion noir
                 {3,-1,-1,-1,2,-1,-1,-1,3},  ///-3 signifie que ce case est dans l'itin�raire d'un pion(noir/blanc)
                 {-1,-1,-1,-1,2,-1,-1,-1,-1},  ///-2 signifie que ce case est dans l'itin�raire du roi
                 {-1,-1,-1,-1,3,-1,-1,-1,-1},
                 {0,-1,-1,3,3,3,-1,-1,0}};

    int* P;
    P=(int*)M;   ///On pointe sur M pour qu'on puisse changer les valeurs

    SDL_Surface* tour; ///Il va indique le tour de chaque joueur
    SDL_Rect positionTour;
    positionTour.x=230;   ///On le met en bas
    positionTour.y=460;

    int r;
    srand(time(NULL));
    r=rand()%2;    ///On g�n�re un entier qui vaut 0 si le tour de l'ordinateur et 1 sinon

    int a; ///Il vont servir pour des indices interm�diaires entre les fonctions pour r�cup�rer les positions souhait�es
    int b;
    int t=0;
    int joueur=0;

    int deplacer=0;  ///Il va indiquer s'il y a un d�placement ou un simple clique

    afficherPlateau(Ecran);    /// Afficher le plateau

    afficherPions(Ecran,P);    /// Mettre les pions dans ses positions

    ordinateur=IMG_Load("ordinateur.png"); ///Mettre un indicateur des joueurs
    homme=IMG_Load("homme.png");

    tour=IMG_Load("joueur-blanc.png");
    SDL_BlitSurface(tour, NULL, Ecran, &positionTour);
    SDL_Flip(Ecran);

    if(r==0)    /// Si r=0 l'ordinateur va �tre le joueur blanc
    {
        positionOrdinateur.x=80;
        positionOrdinateur.y=10;
        SDL_BlitSurface(ordinateur, NULL, Ecran, &positionOrdinateur);
        positionHomme.x=300;
        positionHomme.y=10;
        SDL_BlitSurface(homme, NULL, Ecran, &positionHomme);
        SDL_Flip(Ecran);
        tourOrdinateur(Ecran,P,&r,&joueur,&deplacer);   ///L'ordinateur est le premier � jouer donc il va commencer

    }
    else if (r==1)
    {

        positionOrdinateur.x=300;
        positionOrdinateur.y=10;
        SDL_BlitSurface(ordinateur, NULL, Ecran, &positionOrdinateur);
        positionHomme.x=80;
        positionHomme.y=10;
        SDL_BlitSurface(homme, NULL, Ecran, &positionHomme);
        SDL_Flip(Ecran);
    }

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT :
                {
                    continuer=0;
                    break;
                }
            case SDL_MOUSEBUTTONUP:
                {
                    if ((event.button.button == SDL_BUTTON_LEFT))
                    {
                        SDL_FillRect(Ecran, NULL, SDL_MapRGB(Ecran->format,0,0,0)); /// On efface l'ecran

                        afficherPlateau(Ecran);  /// Afficher le plateau et son entourage

                        afficherPions(Ecran,P);  /// Mettre les pions dans ses nouvelles positions

                        positionActuel.x=event.button.x;  /// Indiquer l'endroit o� il est cliqu�
                        positionActuel.y=event.button.y;

                        deplacerPion(Ecran,P,positionActuel,&joueur,&a,&b,&deplacer); /// D�placer le pion s�l�ctionn� ou afficher son itin�raire

                        prisePion(Ecran,P,positionActuel,&joueur,&deplacer);  /// Faire des prises si c'est possible et indiquer la situation de la partie
                        if(joueur==r)
                        {
                            tourOrdinateur(Ecran,P,&r,&joueur,&deplacer);
                        }
                    }
                    break;


                }


    }
        }

}


void regles(SDL_Surface *Ecran)
{/** Elle affiche les r�gles du jeu **/

    SDL_Surface* regle[3];
    SDL_Rect positionRegle;

    int i=0;

    int continuer=1;
    SDL_Event event;

    positionRegle.x=0;
    positionRegle.y=0;

    regle[0]=IMG_Load("regle-1.png");  /// � chaque �l�ment du tableau regle on associe une image de r�gles
    regle[1]=IMG_Load("regle-2.png");
    regle[2]=IMG_Load("regle-3.png");
    SDL_BlitSurface(regle[0], NULL, Ecran, &positionRegle); /// On colle l'image � l'�cran
    SDL_Flip(Ecran);

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT : /// On retourne au menu principale en cliquant sur fermer
            {
                continuer=0;
                break;
            }
            case SDL_KEYDOWN :
            {
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:   /// On retourne au menu principale en cliquant sur le boutton "echap"
                        continuer = 0;
                        break;
                }
            }
            case SDL_MOUSEBUTTONUP :
            {
                if(event.button.button== SDL_BUTTON_LEFT)
                {
                    if((event.button.x>=400)&&(event.button.y>=460))   /// Si on clique sur la fl�che en bas � droite
                    {
                        i=i+1;
                        SDL_BlitSurface(regle[i%3], NULL, Ecran, &positionRegle); /// On passe � la page suivant
                        SDL_Flip(Ecran);
                    }
                    else if ((event.button.x<=120)&&(event.button.y>=460))  /// Si on clique sur la fl�che en haut � droite
                    {
                        i=i+2;
                        SDL_BlitSurface(regle[i%3], NULL, Ecran, &positionRegle); /// On revient � la page pr�c�dente
                        SDL_Flip(Ecran);

                    }
                }
                break;
            }
        }
    }
    for(i=0;i<3;i++)
    {
        SDL_FreeSurface(regle[i]);   ///On lib�re les surfaces allou�es
    }
}


void menuSecondaire(SDL_Surface *Ecran)
{/** Elle permet de passer au menu secondaire o� il y a les modes de jeu **/
    SDL_Surface *menu2;
    SDL_Rect positionMenu2;
    menu2=IMG_Load("menu-2.jpg");
    positionMenu2.x=0;
    positionMenu2.y=0;
    SDL_BlitSurface(menu2, NULL, Ecran, &positionMenu2); /// On affiche le menu secondaire
    SDL_Flip(Ecran);

    SDL_Event event;
    int continuer=1;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_KP1:
                        vsJoueur(Ecran);   /// Si on clique sur "1" on passe au mode joueur contre joueur
                        break;
                   case SDLK_KP2:
                        vsOrdinateur(Ecran); /// Si on clique sur "2" on passe au mode joueur contre ordinateur
                        break;
               }
                break;
                }

    }
     SDL_FreeSurface(menu2);
}


void afficherPlateau(SDL_Surface *Ecran)
{/** Cette proc�dure sert � afficher � l'�cran le plateau du jeu **/
        SDL_Surface* plateau;
        SDL_Rect positionPlateau;
        int i=0,j=0;

        plateau=IMG_Load("plateau.png");
        positionPlateau.x=0;
        positionPlateau.y=0;
        SDL_BlitSurface(plateau, NULL, Ecran,&positionPlateau);
        SDL_Flip(Ecran);
        SDL_FreeSurface(plateau);
}

void afficherPions(SDL_Surface *Ecran,int* T)
{/** Cette proc�dure sert � afficher � l'�cran les pions dans leurs positions d�termin�es � partir de T **/


        SDL_Surface *pion;
        SDL_Rect positionPion;
        int i=0,j=0;
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                if (*(T+i*9+j)==1)
                {

                    pion=IMG_Load("roi.png");
                    positionPion.x=80+j*40+2;
                    positionPion.y=80+i*40+2;
                    SDL_BlitSurface(pion, NULL, Ecran, &positionPion);
                    SDL_Flip(Ecran);
                }
                if (*(T+i*9+j)==2)
                {

                    pion=IMG_Load("pion-blanc.png");
                    positionPion.x=80+j*40+2;
                    positionPion.y=80+i*40+2;
                    SDL_BlitSurface(pion, NULL, Ecran, &positionPion);
                    SDL_Flip(Ecran);


                }
                if (*(T+i*9+j)==3)
                {
                    pion=IMG_Load("pion-noir.png");
                    positionPion.x=80+j*40+2;
                    positionPion.y=80+i*40+2;
                    SDL_BlitSurface(pion, NULL, Ecran, &positionPion);
                    SDL_Flip(Ecran);

                }
            }
        }SDL_FreeSurface(pion);



}

int blancBloque(int *T,int i,int j)
{/** Elle indique si un pion blanc d'indice (i,j) est bloqu� ou non **/
    if(*(T+i*9+j)==2)
    {

        if((i>0)&&(i<8)&&(j>0)&&(j<8))  /// Si le pion n'est pas sur les bords
        {
            if((*(T+(i+1)*9+j)!=-1)&&(*(T+(i-1)*9+j)!=-1)&&(*(T+i*9+j+1)!=-1)&&(*(T+i*9+j-1)!=-1))
            {
                return 1;
            }

        }
        else if (i==0)  /// Si le pion sur le bord en haut
        {
            if((*(T+(i+1)*9+j)!=-1)&&(*(T+i*9+j+1)!=-1)&&(*(T+i*9+j-1)!=-1))
            {
                return 1;
            }
        }
        else if (i==8)  /// Si le pion le bord en bas
        {
            if((*(T+(i-1)*9+j)!=-1)&&(*(T+i*9+j+1)!=-1)&&(*(T+i*9+j-1)!=-1))
            {
                return 1;
            }
        }
         else if (j==0) /// Si le pion le bord � qauche
        {
            if((*(T+i*9+j+1)!=-1)&&(*(T+(i+1)*9+j)!=-1)&&(*(T+(i-1)*9+j)!=-1))
            {
                return 1;
            }
        }
         else if (j==8) /// Si le pion le bord � droite
        {
            if((*(T+i*9+j-1)!=-1)&&(*(T+(i+1)*9+j)!=-1)&&(*(T+(i-1)*9+j)!=-1))
            {
                return 1;
            }
        }else return 0;
    }
}

int positionBloquante(int *T,int i,int j)
{/**Elle indique si cette position est bloquante pour le roi ou non **/
    if((i>=0)&&(j<=8))
    {
        if((*(T+i*9+j)==0)||(*(T+i*9+j)==3))
        {
            return 1;
        }
        else if (*(T+i*9+j)==2)
        {
            if (blancBloque(T,i,j)==1)  /// Si le pion blanc est bloqu�
            {
                return 1;
            }
        }
        return 0;
    }
    return 1;

}

int captureRoi(int *T,int i,int j)
{/**Elle indique si le roi est captur� ou non **/

    if((positionBloquante(T,i-1,j)+positionBloquante(T,i+1,j)+positionBloquante(T,i,j+1)+positionBloquante(T,i,j-1))==4)
    {
        return 1;
    }
    return 0;
}


void deplacerPion(SDL_Surface* Ecran,int* T,SDL_Rect position,int* player,int* c,int* d,int *Deplacer)
{/**Elle indique l'itin�raire pour un pion selectionn� ensuite Elle le deplace si le joueur veut le d�placer **/

    SDL_Surface* Itineraire;
    SDL_Surface* tour;
    SDL_Rect positionTour;
    SDL_Rect positionItineraire;

    Itineraire=IMG_Load("focus.png");
    int k1,k2,i,j,k;

    int continuer=1;
    SDL_Event event;

    positionTour.x=230;  /// On positionne l'indicateur du tour en dessous
    positionTour.y=460;

    k1=(position.y-80)/40;
    k2=(position.x-80)/40;
    if(*player==0) /// Si la tour du joueur blanc, on affiche cela sur l'�cran
    {
        tour=IMG_Load("joueur-blanc.png");
        SDL_BlitSurface(tour, NULL, Ecran, &positionTour);
        SDL_Flip(Ecran);
    }
    else /// Si la tour du joueur noir, on affiche cela sur l'�cran
    {
        tour=IMG_Load("joueur-noir.png");
        SDL_BlitSurface(tour, NULL, Ecran, &positionTour);
        SDL_Flip(Ecran);
    }
    if ((position.x>80)&&(position.y>80)&&(position.x<440)&&(position.y<440)) /// Si le joueur � cliqu� sur le plateau
       {
           if(*player==0) ///Si ce joueur est blanc
           {
               if(*(T+k1*9+k2)==2) /// Si pion blanc
               {
                    *c=k1; /// On r�cup�re les indices du pion s�l�ctionn�
                    *d=k2;
                    for(j=k2+1;j<9;j++)
                    {
                        if(*(T+k1*9+j)<=0) /// Si les cases � droites sont vides
                        {
                            if(*(T+k1*9+j)<=-1) /// Pour �viter le Konakis et les cases angles dans la valeur = 0
                            {
                                positionItineraire.x=80+40*j;
                                positionItineraire.y=80+40*k1;
                                *(T+k1*9+j)=-3;  /// c'est une position possible pour ce pion
                                SDL_BlitSurface(Itineraire, NULL, Ecran, &positionItineraire);
                                SDL_Flip(Ecran);
                            }
                        }else break; /// On arr�te lorsqu'on rencontre un obstacle
                    }
                    for(j=k2-1;j>=0;j--)
                    {
                        if(*(T+k1*9+j)<=0) /// si les cases � gauche sont vides
                        {
                            if(*(T+k1*9+j)<=-1) /// pour �viter le Konakis et les angles
                             {
                                positionItineraire.x=80+40*j;
                                positionItineraire.y=80+40*k1;
                                *(T+k1*9+j)=-3;  /// c'est une position possible pour ce pion
                                SDL_BlitSurface(Itineraire, NULL, Ecran, &positionItineraire);
                                SDL_Flip(Ecran);
                            }
                        }else break; /// On arr�te lorsqu'on rencontre un obstacle
                    }
                    for(i=k1+1;i<9;i++)
                    {
                        if(*(T+i*9+k2)<=0) /// si les cases au dessous sont vides
                        {
                            if(*(T+i*9+k2)<=-1) /// pour �viter le Konakis et les cases angles
                            {
                                positionItineraire.x=80+40*k2;
                                positionItineraire.y=80+40*i;
                                *(T+i*9+k2)=-3;  /// c'est une position possible pour ce pion
                                SDL_BlitSurface(Itineraire, NULL, Ecran, &positionItineraire);
                                SDL_Flip(Ecran);
                            }
                        }else break; /// On arr�te lorsqu'on rencontre un obstacle
                    }
                    for(i=k1-1;i>=0;i--)
                    {
                        if(*(T+i*9+k2)<=0) /// si les cases au dessus sont vides
                        {
                            if(*(T+i*9+k2)<=-1) /// pour �viter le Konakis et les cases angles
                            {
                                positionItineraire.x=80+40*k2;
                                positionItineraire.y=80+40*i;
                                *(T+i*9+k2)=-3;  /// c'est une position possible pour ce pion
                                SDL_BlitSurface(Itineraire, NULL, Ecran, &positionItineraire);
                                SDL_Flip(Ecran);
                            }
                        }else break; /// On arr�te lorsqu'on rencontre un obstacle
                    }*Deplacer=0;

               }
               else if (*(T+k1*9+k2)==1)  /// si roi
               {
                   *c=k1;
                   *d=k2;
                   if((*(T+k1*9+k2+1)<=0)&&(k2<8)) ///si la case � droite est vide
                   {
                       positionItineraire.x=80+40*(k2+1);
                       positionItineraire.y=80+40*k1;
                       *(T+k1*9+k2+1)=-2;
                       SDL_BlitSurface(Itineraire, NULL, Ecran, &positionItineraire);
                       SDL_Flip(Ecran);
                   }
                   if((*(T+k1*9+k2-1)<=0)&&(k2>0)) ///si la case � gauche est vide
                   {
                       positionItineraire.x=80+40*(k2-1);
                       positionItineraire.y=80+40*k1;
                       *(T+k1*9+k2-1)=-2;
                       SDL_BlitSurface(Itineraire, NULL, Ecran, &positionItineraire);
                       SDL_Flip(Ecran);
                   }
                    if((*(T+(k1+1)*9+k2)<=0)&&(k1<8)) ///si la case au dessous est vide
                   {
                       positionItineraire.x=80+40*k2;
                       positionItineraire.y=80+40*(k1+1);
                       *(T+(k1+1)*9+k2)=-2;
                       SDL_BlitSurface(Itineraire, NULL, Ecran, &positionItineraire);
                       SDL_Flip(Ecran);
                   }
                   if ((*(T+(k1-1)*9+k2)<=0)&&(k1>0))
                   {
                       positionItineraire.x=80+40*k2;
                       positionItineraire.y=80+40*(k1-1);
                       *(T+(k1-1)*9+k2)=-2;
                       SDL_BlitSurface(Itineraire, NULL, Ecran, &positionItineraire);
                       SDL_Flip(Ecran);
                   }
                   *Deplacer=0;

               }
               else if (*(T+k1*9+k2)==-3)  /// Si cette position est cibl�e par un pion blanc
               {
                   *(T+k1*9+k2)=*(T+*c*9+*d);
                   *(T+*c*9+*d)=-1;
                   *c=k1; ///On r�cup�re les indices de destination
                   *d=k2;
                   for(i=0;i<9;i++)
                   {
                       for(j=0;j<9;j++)
                       {
                           if (*(T+i*9+j)==-3)
                               {
                                   *(T+i*9+j)=-1;  /// Supprimer l'itineraire
                               }
                       }
                   }
                   SDL_FillRect(Ecran, NULL,SDL_MapRGB(Ecran->format,255,255,255));
                   afficherPlateau(Ecran);
                   afficherPions(Ecran,T);
                   SDL_Flip(Ecran);
                   *player=1;
                   *Deplacer=1;

               }
               else if(*(T+k1*9+k2)==-2)   /// Si cette position est cibl�e par le roi
               {
                   *(T+k1*9+k2)=*(T+*c*9+*d);
                   *(T+*c*9+*d)=-1;
                   *c=k1; ///On r�cup�re les indices de destination
                   *d=k2;
                   for(i=0;i<9;i++)
                   {
                       for(j=0;j<9;j++)
                       {
                           if (*(T+i*9+j)==-2)
                               {
                                   *(T+i*9+j)=-1; /// supprimer l'itin�raire
                               }
                       }
                   }
                   if((k1!=4)||(k2!=4)) *(T+4*9+4)=0;   /// pour k1=k2=4 entraine la disparition du roi du plateau
                   *(T)=0; /// 0 pour qu'elles restent interdites aux autres pions
                   *(T+8)=0;
                   *(T+8*9+8)=0;
                   *(T+8*9)=0;
                   SDL_FillRect(Ecran, NULL,SDL_MapRGB(Ecran->format,255,255,255));
                   afficherPlateau(Ecran);
                   afficherPions(Ecran,T);
                   SDL_Flip(Ecran);
                   *player=1;
                   *Deplacer=1;
               }

               }
           else if (*player==1)  /// Si le tour du joueur-noir
           {
                tour=IMG_Load("joueur-noir.png");
                SDL_BlitSurface(tour, NULL, Ecran, &positionTour);
                SDL_Flip(Ecran);
              if(*(T+k1*9+k2)==3) /// si pion noir
               {
                    *c=k1;
                    *d=k2;
                    for(j=k2+1;j<9;j++)
                    {
                        if(*(T+k1*9+j)<=0) /// si les cases � droites sont vides
                        {
                            if(*(T+k1*9+j)<=-1) /// pour �viter le Konakis et les cases angles
                            {
                                positionItineraire.x=80+40*j;
                                positionItineraire.y=80+40*k1;
                                *(T+k1*9+j)=-3;  /// c'est une position possible pour ce pion
                                SDL_BlitSurface(Itineraire, NULL, Ecran, &positionItineraire);
                                SDL_Flip(Ecran);
                            }
                        }else break; /// On arr�te lorsqu'on rencontre un obstacle
                    }
                    for(j=k2-1;j>=0;j--)
                    {
                        if(*(T+k1*9+j)<=0) /// si les cases � gauche sont vides
                        {
                            if(*(T+k1*9+j)<=-1) /// pour �viter le Konakis et les cases angles
                            {
                                positionItineraire.x=80+40*j;
                                positionItineraire.y=80+40*k1;
                                *(T+k1*9+j)=-3;  /// c'est une position possible pour ce pion
                                SDL_BlitSurface(Itineraire, NULL, Ecran, &positionItineraire);
                                SDL_Flip(Ecran);
                            }
                        }else break; /// On arr�te lorsqu'on rencontre un obstacle
                    }
                    for(i=k1+1;i<9;i++)
                    {
                        if(*(T+i*9+k2)<=0) /// si les cases au dessous sont vides
                        {
                            if(*(T+i*9+k2)<=-1) /// pour �viter le Konakis et les cases angles
                            {
                                positionItineraire.x=80+40*k2;
                                positionItineraire.y=80+40*i;
                                *(T+i*9+k2)=-3;  /// c'est une position possible pour ce pion
                                SDL_BlitSurface(Itineraire, NULL, Ecran, &positionItineraire);
                                SDL_Flip(Ecran);
                            }
                        }else break; /// On arr�te lorsqu'on rencontre un obstacle
                    }
                    for(i=k1-1;i>=0;i--)
                    {
                        if(*(T+i*9+k2)<=0) /// si les cases au dessus sont vides
                        {
                            if(*(T+i*9+k2)<=-1) /// pour �viter le Konakis et les cases angles
                            {
                                positionItineraire.x=80+40*k2;
                                positionItineraire.y=80+40*i;
                                *(T+i*9+k2)=-3;  /// c'est une position possible pour ce pion
                                SDL_BlitSurface(Itineraire, NULL, Ecran, &positionItineraire);
                                SDL_Flip(Ecran);
                            }
                        }else break; /// On arr�te lorsqu'on rencontre un obstacle
                    }*Deplacer=0;
               }
              else if (*(T+k1*9+k2)==-3)  /// Si cette position est cibl�e par un pion noir
               {
                   *(T+k1*9+k2)=*(T+*c*9+*d);
                   *(T+*c*9+*d)=-1;
                   *c=k1; ///On r�cup�re les indices de destination
                   *d=k2;
                   for(i=0;i<9;i++)
                   {
                       for(j=0;j<9;j++)
                       {
                           if (*(T+i*9+j)==-3)
                               {
                                   *(T+i*9+j)=-1;  /// Supprimer l'itineraire
                               }
                       }
                   }
                   SDL_FillRect(Ecran, NULL,SDL_MapRGB(Ecran->format,255,255,255));
                   afficherPlateau(Ecran);
                   afficherPions(Ecran,T);
                   SDL_Flip(Ecran);
                   *player=0;
                   *Deplacer=1;
                   tour=IMG_Load("joueur-noir.png");
                   SDL_BlitSurface(tour, NULL, Ecran, &positionTour);
                   SDL_Flip(Ecran);
               }
           }
           }
           SDL_FreeSurface(tour);
           SDL_FreeSurface(Itineraire);

}

int prisePion(SDL_Surface* Ecran,int* T,SDL_Rect position,int* player,int* Deplacer)
{/** Elle permet de faire des prises s'il y en a **/
    int i,j,k1,k2,p,q;
    k1=(position.y-80)/40;
    k2=(position.x-80)/40;
    SDL_Surface *Fin;
    SDL_Rect positionFin;
    if(*Deplacer==1) /// Si on a effectu� un d�placement
    {
        if(*player==0) /// *player=0 signifie que les noirs ont derni�rement jou�
        {
                for(i=0;i<9;i++)
                {
                    for(j=0;j<9;j++)
                    {
                        if(*(T+i*9+j)==1)
                        {
                            p=captureRoi(T,i,j);
                            if (p==1)
                            {
                                 Fin=IMG_Load("winner-noir.png");
                                 positionFin.x=0;
                                 positionFin.y=0;
                                 SDL_BlitSurface(Fin, NULL, Ecran, &positionFin);
                                 SDL_Flip(Ecran);
                                 return 1;
                            }

                        }

                    }
                }
                if ((*(T+k1*9+k2+1)==2)&&((*(T+k1*9+k2+2)==3)||(*(T+k1*9+k2+2)==0)))
                {
                    *(T+k1*9+k2+1)=-1;
                    SDL_FillRect(Ecran, NULL,SDL_MapRGB(Ecran->format,0,0,0));
                    afficherPlateau(Ecran);
                    afficherPions(Ecran,T);
                    SDL_Flip(Ecran);
                }
                if ((*(T+k1*9+k2-1)==2)&&((*(T+k1*9+k2-2)==3)||(*(T+k1*9+k2-2)==0)))
                {
                    *(T+k1*9+k2-1)=-1;
                    SDL_FillRect(Ecran, NULL,SDL_MapRGB(Ecran->format,0,0,0));
                    afficherPlateau(Ecran);
                    afficherPions(Ecran,T);
                    SDL_Flip(Ecran);
                }
                if ((*(T+(k1+1)*9+k2)==2)&&((*(T+(k1+2)*9+k2)==3)||(*(T+(k1+2)*9+k2)==0)))
                {
                    *(T+(k1+1)*9+k2)=-1;
                    SDL_FillRect(Ecran, NULL,SDL_MapRGB(Ecran->format,0,0,0));
                    afficherPlateau(Ecran);
                    afficherPions(Ecran,T);
                    SDL_Flip(Ecran);
                }
                if ((*(T+(k1-1)*9+k2)==2)&&((*(T+(k1-2)*9+k2)==3)||(*(T+(k1-2)*9+k2)==0)))
                {
                    *(T+(k1-1)*9+k2)=-1;
                    SDL_FillRect(Ecran, NULL,SDL_MapRGB(Ecran->format,0,0,0));
                    afficherPlateau(Ecran);
                    afficherPions(Ecran,T);
                    SDL_Flip(Ecran);
                }


        }
        else if (*player==1) /// les blancs qui ont derni�rement jou�
        {
            if ((*(T+k1*9+k2+1)==3)&&((*(T+k1*9+k2+2)==2)||(*(T+k1*9+k2+2)==1)||(*(T+k1*9+k2+2)==0)))
            {
                *(T+k1*9+k2+1)=-1;
                SDL_FillRect(Ecran, NULL,SDL_MapRGB(Ecran->format,0,0,0));
                afficherPlateau(Ecran);
                afficherPions(Ecran,T);
                SDL_Flip(Ecran);
            }
            if ((*(T+k1*9+k2-1)==3)&&((*(T+k1*9+k2-2)==2)||(*(T+k1*9+k2-2)==1)||(*(T+k1*9+k2-2)==0)))
            {
                *(T+k1*9+k2-1)=-1;
                SDL_FillRect(Ecran, NULL,SDL_MapRGB(Ecran->format,0,0,0));
                afficherPlateau(Ecran);
                afficherPions(Ecran,T);
                SDL_Flip(Ecran);
            }
            if ((*(T+(k1+1)*9+k2)==3)&&((*(T+(k1+2)*9+k2)==2)||(*(T+(k1+2)*9+k2)==1)||(*(T+(k1+2)*9+k2)==0)))
            {
                *(T+(k1+1)*9+k2)=-1;
                SDL_FillRect(Ecran, NULL,SDL_MapRGB(Ecran->format,255,255,255));
                afficherPlateau(Ecran);
                afficherPions(Ecran,T);
                SDL_Flip(Ecran);
            }
            if ((*(T+(k1-1)*9+k2)==3)&&((*(T+(k1-2)*9+k2)==2)||(*(T+(k1-2)*9+k2+2)==1)||(*(T+(k1-2)*9+k2)==0)))
            {
                *(T+(k1-1)*9+k2)=-1;
                SDL_FillRect(Ecran, NULL,SDL_MapRGB(Ecran->format,255,255,255));
                afficherPlateau(Ecran);
                afficherPions(Ecran,T);
                SDL_Flip(Ecran);
            }
            q=1;
            for(i=0;i<9;i++)
            {
                for(j=0;j<9;j++)
                {
                    if(*(T+i*9+j)==1)
                    {
                        q=0;
                    }
                }
            }
            if(q==1)
            {
                Fin=IMG_Load("winner-blanc.png");
                positionFin.x=0;
                positionFin.y=0;
                SDL_BlitSurface(Fin, NULL, Ecran, &positionFin);
                SDL_Flip(Ecran);
            }
        }
    }


}




void vsJoueur(SDL_Surface* Ecran)
{
    int continuer=1;
    SDL_Event event;
    SDL_Surface *joueur1,*joueur2;
    SDL_Rect positionJoueur1,positionJoueur2;
    SDL_Rect positionClique;
    int M[9][9]={{0,-1,-1,3,3,3,-1,-1,0},      /// -1 signifie case vide
                 {-1,-1,-1,-1,3,-1,-1,-1,-1},       /// 0 signifie case angle
                 {-1,-1,-1,-1,2,-1,-1,-1,-1},       /// 1 signifie que la case contient le roi
                 {3,-1,-1,-1,2,-1,-1,-1,3},       /// 2 signifie que la case contient un pion blanc
                 {3,3,2,2,1,2,2,3,3},       /// 3 signifie que la case contient un pion noir
                 {3,-1,-1,-1,2,-1,-1,-1,3},
                 {-1,-1,-1,-1,2,-1,-1,-1,-1},
                 {-1,-1,-1,-1,3,-1,-1,-1,-1},
                 {0,-1,-1,3,3,3,-1,-1,0}};
    int* P;
    P=(int*)M;   /// P pointe sur M pour qu'on puisse changes sa valeur
    SDL_Surface* tour;
    SDL_Rect positionTour;
    positionTour.x=230;
    positionTour.y=460;
    int a,b;   /// Elles vont contenir les indices cibl�s
    int joueur=0; /// Elles va indiquer le tour de chaque joueur : 0 si joueur blanc, 1 si joueur noir
    int gagnant=0; /// Elles vont indiquer si la partie est termin�e ou pas : 0 si non, 1 si joueur blanc qui a gagn�, 2 si joueur noir qui a gagn�
    int deplacer=0;  /// Elle va indiquer s'il ya un d�placement ou bien un clic  : 1 si d�placement, 0 sinon



    afficherPlateau(Ecran);    /// Afficher le plateau et son entourage

    afficherPions(Ecran,P);    /// Mettre les pions dans ses positions


    joueur1=IMG_Load("joueur-1.png");
    positionJoueur1.x=80;
    positionJoueur1.y=10;
    SDL_BlitSurface(joueur1, NULL, Ecran, &positionJoueur1);

    joueur2=IMG_Load("joueur-2.png");
    positionJoueur2.x=300;
    positionJoueur2.y=10;
    SDL_BlitSurface(joueur2, NULL, Ecran, &positionJoueur2);

    tour=IMG_Load("joueur-blanc.png");  /// Ajouter une image qui va servir pour l'indexation des tours
    SDL_BlitSurface(tour, NULL, Ecran, &positionTour);
    SDL_Flip(Ecran);


    while (continuer)
    {

        joueur1=IMG_Load("joueur-1.png");
        positionJoueur1.x=80;
        positionJoueur1.y=10;
        SDL_BlitSurface(joueur1, NULL, Ecran, &positionJoueur1);
        joueur2=IMG_Load("joueur-2.png");
        positionJoueur2.x=300;
        positionJoueur2.y=10;
        SDL_BlitSurface(joueur2, NULL, Ecran, &positionJoueur2);
        SDL_Flip(Ecran);
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT :
                {
                    continuer=0;
                    break;
                }
            case SDL_MOUSEBUTTONUP:
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        SDL_FillRect(Ecran, NULL, SDL_MapRGB(Ecran->format,0,0,0)); /// On efface l'ecran

                        afficherPlateau(Ecran);  /// Afficher le plateau et son entourage

                        afficherPions(Ecran,P);  /// Mettre les pions dans ses nouvelles positions

                        positionClique.x=event.button.x;  /// Indiquer l'endroit o� il est cliqu�
                        positionClique.y=event.button.y;

                        deplacerPion(Ecran,P,positionClique,&joueur,&a,&b,&deplacer); /// D�placer le pion s�l�ctionn� ou afficher son itin�raire

                        prisePion(Ecran,P,positionClique,&joueur,&deplacer);  /// Faire des prises si c'est possible et indiquer la situation de la partie



                    }
                    break;


                }
        }
    }
}



