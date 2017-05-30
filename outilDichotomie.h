/*///////////////////////////////////////////////////////////////
// * Author : Abdel-Malik Bouhassoun
// * Date : 29 Mai 2017
// Ce header contient ...todo...
///////////////////////////////////////////////////////////////*/
#ifndef _outilDichotomie_h_
#define _outilDichotomie_h_

/************************************/
/****** definition énumération ******/
/************************************/
enum ChangementPression{
    SERRER,
    RELACHER
};


/************************************/
/******   definition Classe    ******/
/************************************/
class BornesDichotomie{
    //attributs
    static constexpr double ZERO_DICHOTOMIE_REALISEE = -1;
    double inf = 0;
    double sup = 1;
    double index = ZERO_DICHOTOMIE_REALISEE;
    //méthodes
    public:
    //Constructeurs
    BornesDichotomie(){
    };
    void dichotomie(ChangementPression choix){
        if(index == ZERO_DICHOTOMIE_REALISEE)
            index = (inf+sup)/2;
        else{
            if(choix == ChangementPression::SERRER){
                inf = index;
                index = (inf+sup)/2;
            }
            if(choix == ChangementPression::RELACHER){
                sup = index;
                index = (inf+sup)/2;
            }
        }
    };
    //getter
    double getInf(){
        return inf;
    };
    double getSup(){
        return sup;
    };
    double getIndex(){
        return index;
    };
    //setter
    void setInf(double i){
        inf = i;
    };
    void setSup(double s){
        sup = s;
    };
    void setIndex(double ind){
        index = ind;
    };

};

#endif
