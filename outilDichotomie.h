/**------------------------------
 * \Author Abdel-Malik Bouhassoun
 * \date 29 Mai 2017
 * Ce header contient ...todo...
 */

#ifndef _outilDichotomie_h_
#define _outilDichotomie_h_

//--************************************--//
//--****** definition énumération ******--//
//--************************************--//
enum ChangementPression{
    SERRER,
    RELACHER
};

//--************************************--//
//--******   definition Classe    ******--//
//--************************************--//

class BornesDichotomie{

    //--*attributs*--//
    static constexpr double ZERO_DICHOTOMIE_REALISEE = -1;
    double inf = 0;
    double sup = 1;
    double index = ZERO_DICHOTOMIE_REALISEE;

    //--*Méthodes*--//
    public:
    /*Constructeurs*/
    BornesDichotomie(){
    };

    /*méthodes*/

    /** \brief  modifier la valeur de freinage par dichotomie
     * \param[in] choix l'évolution souhaité d'une étape de dichotomie (Sérrer / Relacher)
     */
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

    /** \brief  mettre à jour l'intervalle d'exécution de la dichotomie (zone réduisant l'intervalle de pressions applicable)
     */
    void versIntervalleFaible(){
        sup = index;
        inf = 0;
        index = ZERO_DICHOTOMIE_REALISEE;
    };

    /** \brief  mettre à jour l'intervalle d'exécution de la dichotomie (zone augmentant l'intervalle de pressions applicable)
     */
    void versIntervalleFort(){
        sup = 1;
        inf = index;
        index = ZERO_DICHOTOMIE_REALISEE;
    };

    /*getter*/
    double getInf(){
        return inf;
    };
    double getSup(){
        return sup;
    };
    double getIndex(){
        return index;
    };

    /*setter*/
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
