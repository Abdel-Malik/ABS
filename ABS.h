/*///////////////////////////////////////////////////////////////
// * Author : Abdel-Malik Bouhassoun
// * Date : 29 Mai 2017
// Ce header contient ...todo...
///////////////////////////////////////////////////////////////*/
#ifndef _ABS_h_
#define _ABS_h_


#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include <windows.h>
#include "Roue.h"

/************************************/
/******   definition Classe    ******/
/************************************/

/** La classe ABS est la classe modélisant un fonctionnement d'un ABS
agissant sur chaque roue du véhicule sur lequel il est employé. **/
class ABS{
    ///**attributs**///
    std::vector<Roue> rouesVehicule;
    std::vector<int> rouesASerrer;
    std::vector<int> rouesARelacher;
    double chargeFrein;
    char cpt;
    static constexpr double GLISSEMENT_OPTIMAL = 0.18;
    static constexpr double alpha = 0.015;

    ///**Méthodes**///
    public:
    /*Constructeurs*/
    ABS(){
        initialiserRoues();
    };
    /*méthodes*/
    //but : vérifie l'absence de blocage des roues
    //Une fois un blocage constaté,
    //un premier relachement des frein est executé puis la phase s'arrête
    void phase1(){
        do{
            Sleep(40);
            calculGlissement();
        }while(!blocageRoues());
        //set valeur sup de la borne dichotomique des roues (c%)
        relacherRoues();

    };

    //but : Réaliser une dichotomie sur les roues ayant un glissement non optimal
    //Après 3 boucles conservant un glissment optimal, cette phase s'arrête
    void phase2(){
        do{
            Sleep(40);
            calculGlissement();
            glissementNonOptimal();
            if((rouesARelacher.size()+rouesASerrer.size()) == 0)
                cpt++;
            else{
                cpt = 0;
                relacherRoues();
                serrerRoues();
            }
        }while(cpt < 3);
    };

    //but : Vérifier la conservation du glissement optimal ainsi que le besoin de freiner
    //Si le conducteur lâche suffisamment la pédale, l'ABS s'arrête.
    //Si le véhicule perd/gagne de l'adhérence,
    //les bornes sont réajustées puis la phase 3 est quittée
    bool phase3(){
        bool chgmtGliss = true;
        double chrgFrein2;
        do{
            Sleep(40);
            calculGlissement();
            glissementNonOptimal();
            if(chargeFrein > 2*chrgFrein2){
                chgmtGliss = false;
                chargeFrein = chrgFrein2;
                break;
            }
        }while((rouesARelacher.size()+rouesASerrer.size()) == 0);
        if(chgmtGliss){
            calculGlissement();
            ModifierBornes();
        }
        return chgmtGliss;
    };

    void principale(){
        phase1();
        phase2();
        phase3();
    };
    private:
    void initialiserRoues(){
        for(unsigned int i = 0 ; i < rouesVehicule.size() ; i++)
            rouesVehicule.push_back(Roue());
    };
    void calculGlissement(){
        for(unsigned int i = 0 ; i < rouesVehicule.size() ; i++){
            rouesVehicule[i].setVitesseAngulaire(i);
            rouesVehicule[i].glissementRoue(15); //Vitesse du véhicule en paramètre
        }
    };
    void glissementNonOptimal(){
        for(unsigned int i = 0 ; i < rouesVehicule.size() ; i++){
            if(rouesVehicule[i].getGlissement() < GLISSEMENT_OPTIMAL-alpha)
                rouesASerrer.push_back(i);
            if(rouesVehicule[i].getGlissement() > GLISSEMENT_OPTIMAL+alpha)
                rouesARelacher.push_back(i);

        }
    };
    void ModifierBornes(){
    };
    bool blocageRoues(){
        bool res = false;
        for(unsigned int i = 0 ; i < rouesVehicule.size() ; i++){
            if(rouesVehicule[i].getGlissement() > 0.95){
                res = true;
                rouesARelacher.push_back(i); //Liste d'index des roues bloquées
            }
        }
        return res;
    };
    void relacherRoues(){
        for(int& r : rouesARelacher){
            rouesVehicule[r].dichotomie(ChangementPression::RELACHER);
        }
    };
    void serrerRoues(){
        for(int& r : rouesASerrer){
            rouesVehicule[r].dichotomie(ChangementPression::SERRER);
        }
    };
    public:
    //getter

    //setter

};
#endif
