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
#include "Intermediaire.h"
#define NB_ROUES (4)
/************************************/
/******   definition Classe    ******/
/************************************/

/** La classe ABS est la classe modélisant le fonctionnement d'un ABS
agissant sur chaque roue du véhicule sur lequel il est employé. **/
class ABS{

    ///**attributs**///
    Intermediaire i = Intermediaire();
    std::vector<Roue> rouesVehicule;
    std::vector<int> rouesASerrer;
    std::vector<int> rouesARelacher;
    char compteur;
    double chargeFrein;
    static constexpr double GLISSEMENT_OPTIMAL = 0.18;
    static constexpr double alpha = 0.015;

    ///**Méthodes**///
    public:
    /*Constructeurs*/
    ABS(){
        chargeFrein = i.getChargeFrein();
        initialiserRoues(i.getNbRoues());
    };

    /*méthodes publiques*/

    //but : Simuler le comportement de l'ABS
    //La phase 1 permet de détecter le besoin d'activer l'ABS. (boucle utilisé une seule fois)
    //Le groupement des phases 2 et 3 assure le fonctionnement continuel de l'ABS Si
    //le véhicule roule et la pédale de frein est enclenchée.
    void principale(){
        bool fonctionnementABS = true;
        phase1();
        std::cout << " -- Fin Phase1 -- " << std:: endl;
        do{
            if(phase2()){
                for(unsigned int i = 0 ; i < rouesVehicule.size() ; i++){
                    rouesVehicule[i].setFreinageRoue(this->i.getChargeFrein());
                }
                break;
            }
            std::cout << " -- Fin Phase2 -- " << std:: endl;
            fonctionnementABS = phase3();
            std::cout << " -- Fin Phase3 -- " << std:: endl;
        }while(fonctionnementABS && (this->i.getVitesse()>5)); //et vitesse > 5
    };

    /*getter*/

    /*setter*/

    ///**Méthodes privées**///

    private:

    //but : vérifie l'absence de blocage des roues
    //Une fois un blocage constaté,
    //un premier relachement des freins est executé puis la phase s'arrête
    void phase1(){
        do{
            Sleep(40);
            calculGlissement();
            affichageGlissement(0);
        }while(!blocageRoues());
            calculGlissement();
            chargeFrein = this->i.getChargeFrein();
        for(unsigned int i = 0 ; i < rouesVehicule.size() ; i++){
            this->i.setFreinageRoue(chargeFrein,i);
        }
        relacherRoues();
    };

    //but : Réaliser une dichotomie sur les roues ayant un glissement non optimal
    //Après 3 boucles conservant un glissment optimal, cette phase s'arrête
    //Si la pédale
    bool phase2(){
        bool pedale = false;
        double chrgFrein2;
        do{
            affichageGlissement(0);
            Sleep(40);
            calculGlissement();
            glissementNonOptimal();
            if((rouesARelacher.size()+rouesASerrer.size()) == 0)
                compteur++;
            else{
                compteur = 0;
                relacherRoues();
                serrerRoues();
            }
            chrgFrein2 = this->i.getChargeFrein();
            if(chargeFrein > 2*chrgFrein2){
                chargeFrein = chrgFrein2;
                pedale = true;
            }
        }while(compteur < 3 && !pedale);
        return pedale;
    };//TODO modifier la sortie à TRUE si la pedale de frein est relaché

    //param :
    //out : booléen définissant si une modification significative des valeurs de glissement des roues à eu lieu
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
            chrgFrein2 = this->i.getChargeFrein();
            if(chargeFrein > 2*chrgFrein2 || (this->i.getVitesse()<5)){
                chgmtGliss = false;
                chargeFrein = chrgFrein2;
                break;
            }
        }while((rouesARelacher.size()+rouesASerrer.size()) == 0);
        if(chgmtGliss){
            //calculGlissement();
            modifierBornes();
        }
        return chgmtGliss;
    };

    //param :
    //in : le nombre de roues à créer/stocker
    //but : Initialise un tableau contenant les n roues du véhicule simulé. [nécessité de remplacer n par une méthode récupérant cette valeur]
    void initialiserRoues(int n){
        for(int i = 0 ; i < n ; i++)
            rouesVehicule.push_back(Roue(this->i.getRayonRoues(i),&(this->i),i));
    };

    //but : calculer le glissement de chaque roue au moment de l'appel.
    //Met à jour la vitesse angulaire des roues, appel d'une methode[classe Roue] calculant le glissement pour une vitesse donnée en paramêtre
    void calculGlissement(){
        this->i.majDonnees();
        for(unsigned int i = 0 ; i < rouesVehicule.size() ; i++){
            rouesVehicule[i].majDonnees(&(this->i));
            rouesVehicule[i].glissementRoue(this->i.getVitesse()); //Vitesse du véhicule en paramètre
        }
    };

   void affichageGlissement(){
        for(unsigned int i = 0 ; i < rouesVehicule.size() ; i++)
            std::cout << "glissement r"<<i<<": "<< rouesVehicule[i].getGlissement()<< std:: endl;
    };
    void affichageGlissement(int i){
        std::cout << "glissement r"<<i<<": "<< rouesVehicule[i].getGlissement()<< std:: endl;
    };

    //but : Remplir les listes "rouesASerrer" et "rouesARelacher" avec les indices des roues sur lesquelles effectuer des modifications.
    void glissementNonOptimal(){
        for(unsigned int i = 0 ; i < rouesVehicule.size() ; i++){
            if(rouesVehicule[i].getGlissement() < GLISSEMENT_OPTIMAL-alpha)
                rouesASerrer.push_back(i);
            if(rouesVehicule[i].getGlissement() > GLISSEMENT_OPTIMAL+alpha)
                rouesARelacher.push_back(i);

        }
    };

    //but : Mettre à jour les bornes sur lesquelles la dichotomie est réalisée
    //boucle 1 : La roue à brusquement perdu de l'adhérence. Les nouvelles bornes sont : [0 - la pression actuelle (devenu trop importante)]
    //boucle 2 : La roue à brusquement gagné de l'adhérence. Les nouvelles bornes sont : [la pression actuelle (devenu trop faible) - 1]
    void modifierBornes(){
        for(int& r : rouesARelacher){
            rouesVehicule[r].bornesIntervalleFaible();
        }
        for(int& r : rouesASerrer){
            rouesVehicule[r].bornesIntervalleFort();
        }
    };

    //but : détecter un blocage des roues
    //si le glissement d'une roue s'approche grandement de 1, alors elle est considérée bloquée.
    bool blocageRoues(){
        bool res = false;
        for(unsigned int i = 0 ; i < rouesVehicule.size() ; i++){
            if(rouesVehicule[i].getGlissement() > 0.85){
                res = true;
                rouesARelacher.push_back(i); //Liste d'index des roues bloquées
            }
        }
        return res;
    };

    //but : relacher les roues trop serrées par le freinage.
    void relacherRoues(){
        for(int& r : rouesARelacher){
            rouesVehicule[r].dichotomie(ChangementPression::RELACHER);
            i.setFreinageRoue(r,rouesVehicule[r].pressionAppliquee());
        }
        rouesARelacher.resize(0);
    };

    //but : serrer les roues pas assez solicitées par le freinage.
    void serrerRoues(){
        for(int& r : rouesASerrer){
            rouesVehicule[r].dichotomie(ChangementPression::SERRER);
            i.setFreinageRoue(r,rouesVehicule[r].pressionAppliquee());
        }
        rouesASerrer.resize(0);
    };
};
#endif
