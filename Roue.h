﻿/**------------------------------
 * \Author Abdel-Malik Bouhassoun
 * \date 29 Mai 2017
 * Ce header contient ...todo...
 */

#ifndef _Roue_h_
#define _Roue_h_

#include "../IntermediaireG/IntermediaireG.h"
#include "outilDichotomie.h"

//--************************************--//
//--******   definition Classe    ******--//
//--************************************--//

/** \file La classe Roue est la classe se raportant à une roue du véhicule simulé,
cette roue contient les informations utiles pour une manipulation par l'ABS. **/
class Roue{

    //--*attributs*--//
    IntermediaireG* inter;
    int noRoue;
    double vitesseAngulaire;
    double rayon;
    double glissement;
    BornesDichotomie bornes;

    //--*Méthodes*--//
    public:
    /*Constructeurs*/
    Roue(double r, IntermediaireG* i, int no){
        noRoue = no;
        inter = i;
        bornes = BornesDichotomie();
        vitesseAngulaire = 0;
        rayon = r;
        glissement = 0;
    };
    /*méthodes*/


    /** \brief calculer le glissement de la roue en fonction de la vitesse du véhicule.
     * \param[in] v_auto la vitesse du véhicule
     */
    void glissementRoue(double v_auto){
        v_auto = v_auto/3.6;
        glissement = (v_auto-(vitesseAngulaire*rayon))/v_auto;
        std::cout << "G "<<noRoue<<": "<< glissement<<"vitesse : "<<v_auto*3.6<<" roue "<<vitesseAngulaire*rayon<< std:: endl;
    };

    /** \brief modifier la valeur de freinage par dichotomie
     * \param[in] choix l'évolution souhaité d'une étape de dichotomie (Serrer / Relacher)
     */
    void dichotomie(ChangementPression choix){
        bornes.dichotomie(choix);
    };

    /** \brief mettre à jour l'intervalle d'exécution de la dichotomie (zone réduisant l'intervalle de pressions applicable)
     */
    void bornesIntervalleFaible(){
        bornes.versIntervalleFaible();
    };

    /** \brief mettre à jour l'intervalle d'exécution de la dichotomie (zone augmentant l'intervalle de pressions applicable)
     */
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

    void setFreinageRoue(double f){
        bornes.setSup(f);
    }

    /** \brief mettre à jour l'intervalle d'exécution de la dichotomie (zone augmentant l'intervalle de pressions applicable)
     */
    void majDonnees(IntermediaireG* inter){
        vitesseAngulaire = (*inter).getVitesseAngulaire(noRoue);
    };

};

#endif
