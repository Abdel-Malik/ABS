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

class ABS{
    //attributs
    std::vector<Roue> rouesVehicule;
    std::vector<int> rouesASerrer;
    std::vector<int> rouesARelacher;
    double chargeFrein;
    char cpt;
    double alpha;
    //Méthodes

    public:
    //Constructeurs
    ABS(){
        initialiserRoues();
    };
    //méthodes
    void phase1(){
        calculGlissement();
        while(!blocageRoues()){
            Sleep(40);
            calculGlissement();
        }
        //set valeur sup de la borne dichotomique des roues
        relacherRoues();

    }
    void test(){
        for(unsigned int i = 0; i < rouesVehicule.size() ; i++){
            std::cout << rouesVehicule[i].test() << std::endl;
        }
    }
    private:
    void initialiserRoues(){
        for(unsigned int i = 0 ; i < rouesVehicule.size() ; i++)
            rouesVehicule.push_back(Roue());
    }
    void calculGlissement(){
        for(unsigned int i = 0 ; i < rouesVehicule.size() ; i++){
            rouesVehicule[i].setVitesseAngulaire(i);
            rouesVehicule[i].glissementRoue(15); //Vitesse du véhicule en paramètre
        }
    }
    bool blocageRoues(){
        bool res = false;
        for(unsigned int i = 0 ; i < rouesVehicule.size() ; i++){
            if(rouesVehicule[i].getGlissement() > 0.95){
                res = true;
                rouesARelacher.push_back(i); //Liste d'index des roues bloquées
            }
        }
        return res;
    }
    void relacherRoues(){
        for(int& r : rouesARelacher){
            rouesVehicule[r].dichotomie(ChangementPression::RELACHER);
        }
    }
    void serrerRoues(){
        for(int& r : rouesASerrer){
            rouesVehicule[r].dichotomie(ChangementPression::SERRER);
        }
    }
    public:
    //getter

    //setter

};

//signatures autres

#endif
