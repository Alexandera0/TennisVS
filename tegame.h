#ifndef TEGAME_H
#define TEGAME_H

#include "Headers/PlayUnits/teplayer.h"

class TEGame : public QObject
{
     Q_OBJECT


public:
    ////////////////////////////////////////////
    TEPlayer * OnePlayer;
    TEPlayer * Rival;
    TEPlayer * ServingPlayer;
    Enviroment * CurrentEnviroment;
    naint OnePlayerPoints;
    naint RivalPoints;
    naint DelayTime;
    ////////////////////////////////////////////
    TEGame( TEPlayer * newPlayer,
            TEPlayer * newRival,
            Enviroment * newEnviroment );
    ~TEGame( );
    void SetServingPlayer( TEPlayer * newServingPlayer );
    void Nulify();
    TEPlayer * CalculateGameWinner( );

private:
    TEPlayer * CalculatePointWinner( );
    void EmitPlayerPointWin( );
    void EmitRivalPointWin( );

signals:
    void PointForPlayer( naint newPoints );
    void PointForRival( naint newPoints );
    void DeuceAchieved( );
    void PlayerAdvantageAchieved( );
    void RivalAdvantageAchieved( );
    void PlayerWins( );
    void RivalWins( );
};

#endif // TEGAME_H
