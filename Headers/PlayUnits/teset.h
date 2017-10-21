#ifndef TESET_H
#define TESET_H

#include "Headers/PlayUnits/tegame.h"

class TESet : public QObject
{
    Q_OBJECT

public:
    //////////////////////////////////
    TEGame * Game;
    TEPlayer * OnePlayer;
    TEPlayer * Rival;
    TEPlayer * ServingPlayer;
    Enviroment * CurrentEnviroment;
    naint OnePlayerGames;
    naint RivalGames;
    naint OnePlayerTieBreakPoints;
    naint RivalTieBreakPoints;
    //////////////////////////////////

    TESet( TEPlayer * newPlayer,
           TEPlayer * newRival,
           Enviroment * newEnviroment );
    ~TESet( );
    void SetServingPlayer( TEPlayer * newServingPlayer );
    void Nulify( );
    TEPlayer * CalculateSetWinner( );

private:
    void SwapServe( );
    TEPlayer * CalculateTieBreakWinner( );
    TEPlayer * CalculatePointWinner();

signals:
    void PlayerGamesChange( naint games);
    void RivalGamesChange( naint games);
    void NewGameStarted( );
    void TieBreakStarted( );
    void PlayerTiePointsChange( naint points );
    void RivalTiePointsChange( naint points );
    void Swapped( bool isPlayerServing );
};

#endif // TESET_H
