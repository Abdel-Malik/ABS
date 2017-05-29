/*///////////////////////////////////////////////////////////////
// * Author : Abdel-Malik Bouhassoun
// * Date : 29 Mai 2017
// Ce header contient ...todo...
///////////////////////////////////////////////////////////////*/
#ifndef _Roue_h_
#define _Roue_h_
#include "outilDichotomie.h"

class Roue{
    //attributs
    double vitesseAngulaire;
    double rayon;
    double glissement;
    BornesDichotomie bornes;
    //Méthodes

    public:
    //Constructeurs
    Roue(){
        bornes = BornesDichotomie();
        vitesseAngulaire = 0;
        rayon = 7;
        glissement = 0;
    };
    //méthodes
    double test(){
    return rayon;
    }
    void glissementRoue(double v_auto){
        glissement = (v_auto-(vitesseAngulaire*rayon))/v_auto;
    }

    void dichotomie(ChangementPression choix){
        bornes.dichotomie(choix);
    }
    //getter
    double getVitesseAngulaire(){
        return vitesseAngulaire;
    };
    double getRayon(){
        return rayon;
    };
    double getGlissement(){
        return glissement;
    };
    //setter
    void setVitesseAngulaire(double va){
        vitesseAngulaire = va;
    };
    void setRayon(double r){
        rayon = r;
    };
    void setGlissement(double g){
        glissement = g;
    };


};

#endif
