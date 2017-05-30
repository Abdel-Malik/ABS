/*///////////////////////////////////////////////////////////////
// * Author : Abdel-Malik Bouhassoun
// * Date : 29 Mai 2017
// Ce header contient ...todo...
///////////////////////////////////////////////////////////////*/
#ifndef _Roue_h_
#define _Roue_h_
#include "outilDichotomie.h"

/************************************/
/******   definition Classe    ******/
/************************************/

/** La classe Roue est la classe se raportant à une roue du véhicule simulé,
cette roue contient les informations utiles pour une manipulation par l'ABS. **/
class Roue{

    ///**attributs**///
    double vitesseAngulaire;
    double rayon;
    double glissement;
    BornesDichotomie bornes;

    ///**Méthodes**///
    public:
    /*Constructeurs*/
    Roue(){
        bornes = BornesDichotomie();
        vitesseAngulaire = 0;
        rayon = 7;
        glissement = 0;
    };
    /*méthodes*/

    //param :
    //in : la vitesse du véhicule
    //but : calculer le glissement de la roue en fonction de la vitesse du véhicule.
    void glissementRoue(double v_auto){
        glissement = (v_auto-(vitesseAngulaire*rayon))/v_auto;
    };

    //param :
    //in : l'évolution souhaité d'une étape de dichotomie (Serrer / Relacher)
    //but : modifier la valeur de freinage par dichotomie
    void dichotomie(ChangementPression choix){
        bornes.dichotomie(choix);
    };

    //but : mettre à jour l'intervalle d'exécution de la dichotomie (zone réduisant l'intervalle de pressions applicable)
    void bornesIntervalleFaible(){
        bornes.versIntervalleFaible();
    };

    //but : mettre à jour l'intervalle d'exécution de la dichotomie (zone augmentant l'intervalle de pressions applicable)
    void bornesIntervalleFort(){
        bornes.versIntervalleFort();
    };

    /*getter*/

    double getVitesseAngulaire(){
        return vitesseAngulaire;
    };
    double getRayon(){
        return rayon;
    };
    double getGlissement(){
        return glissement;
    };

    double pressionAppliquee(){
        return bornes.getIndex();
    };

    /*setter*/

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
