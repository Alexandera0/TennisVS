#ifndef TEMATCH_H
#define TEMATCH_H

#include "Headers/PlayUnits/teset.h"

class TEMatch : public QObject
{
    Q_OBJECT

public:
    //////////////////////////////////
    TESet * Set;
    TEPlayer * OnePlayer;
    TEPlayer * Rival;
    TEPlayer * ServingPlayer;
    TEPlayer * Winner;
    MatchRules * Rules;
    Enviroment * CurrentEnviroment;
    naint OnePlayerSets;
    naint RivalSets;
    //////////////////////////////////

    TEMatch( TEPlayer * newPlayer,
             TEPlayer * newRival,
             Enviroment * newEnviroment,
             MatchRules * newRules );
    ~TEMatch();
    void SwapServe( );
    void CalculateMatchWinner( );

signals:
    void NewSetStarted( );
    void PlayerSetChange( naint sets );
    void RivalSetChange( naint sets );
    void Swapped( bool isPlayerServing );
    void MatchFinished(bool isPlayerWinner);
};

#endif // TEMATCH_H
