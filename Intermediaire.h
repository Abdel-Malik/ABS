/**------------------------------
 * \Author Abdel-Malik Bouhassoun
 * \date 01 Juin 2017
 */
#ifndef _Intermediaire_h_
#define _Intermediaire_h_

#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>

/** \file Cette classe permet de déplacer le problème de la réception de données
 * des classes principales pour pouvoir terminer la création de celles-ci.
 */
class Intermediaire{

    /*--attributs--*/
    //Véhicule
    int currentGear;
    int nbRoues;
    const int GEAR_MIN = 1;
    const int GEAR_MAX = 12;
    double vitesseVehicule;
    std::vector<double> vitesseRoues;
    std::vector<double> rayonRoues;
    std::vector<double> freinRoues;
    double chargeMoteur;
    double chargeFrein;

    public:
    static constexpr double VITESSE_MIN = 0;
    static constexpr double VITESSE_MAX = 178.6;

    static constexpr double CHARGE_MIN = 0;
    static constexpr double CHARGE_MAX = 1;
    //Interpolation
    int echAxe;
    //autre
    int event = 0;


    /*--Méthodes--*/

    public:
    //Constructeurs
    Intermediaire(){
        recuperationDonnees();
        initRoues();
    };
    /*Méthodes publiques*/
    void majDonnees(){
        recupVitesseRoues();
    }
    /*getter*/
    int getGear(){
        return currentGear;
    };
    int getGearMin(){
        return GEAR_MIN;
    };
    int getGearMax(){
        return GEAR_MAX;
    };
    double getVitesse(){
        return vitesseVehicule;
    };
    double getChargeMoteur(){
        return chargeMoteur;
    };
    double getEchAxe(){
        return echAxe;
    };
    double getNbRoues(){
        return nbRoues;
    };
    double getChargeFrein(){
        return chargeFrein;
    };

    //metre
    double getRayonRoues(int i){
        return rayonRoues[i];
    };
    double getVitesseAngulaire(int i){
        return vitesseRoues[i];
    };
    /*setter*/
    void setFreinageRoue(int i, double chrg){
        freinRoues[i] = chrg;
    };

    /*--Méthodes privées--*/

    private:
    void recuperationDonnees(){
        nbRoues = 6;
        currentGear = 2;
        vitesseVehicule = 115;
        chargeMoteur = .3;
        chargeFrein = 0;
        //Interpolation
        echAxe = 20;
    };

    void initRoues(){
        for(int i = 0; i < nbRoues ; i++){
            rayonRoues.push_back(0.29545);
            vitesseRoues.push_back(0);
            freinRoues.push_back(0);
        }
        recupVitesseRoues();
    }

    void recupVitesseRoues(){
        event++;
        for(unsigned int i = 0; i < vitesseRoues.size() ; i++){
            if(event != 5 && event !=41 && event != 26)
                vitesseRoues[i] = vitesseVehicule*(1-freinRoues[i])/(rayonRoues[i]*3.6);
        }
        if(event != 5 && event != 16 && event !=18 &&  event != 26)
            vitesseVehicule -= 0.01*vitesseVehicule*chargeFrein;

        if(event == 4){
            std::cout << "Event 1 -- freinage" << std:: endl;
            chargeFrein = 1;
            for(unsigned int i = 0; i < vitesseRoues.size() ; i++){
                vitesseRoues[i] = vitesseVehicule*(1-chargeFrein)/(rayonRoues[i]*3.6);
                freinRoues[i] = chargeFrein;
            }
        }

        if(event == 15){
            std::cout << "Event 1 -- relacher" << std:: endl;
            chargeFrein = 0.52;
            for(unsigned int i = 0; i < vitesseRoues.size() ; i++){
                vitesseRoues[i] += 2;
            }
        }

        if(event == 25){
            std::cout << "Event 2 -- appuie2" << std:: endl;
            chargeFrein = 0.9;
            for(unsigned int i = 0; i < vitesseRoues.size() ; i++){
                vitesseRoues[i] -= 5.1;
            }
        }

        if(event == 40){
            std::cout << "Event 2 -- lâcher" << std:: endl;
            chargeFrein = 0;
        }
    }
};

//signatures autres

#endif
