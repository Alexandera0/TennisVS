#include "Headers/PlayUnits/tegame.h"

//-------------------------------------------------------------------------
TEGame::TEGame( TEPlayer * newPlayer,
                TEPlayer * newRival,
                Enviroment * newEnviroment )
{
    OnePlayer = newPlayer;
    Rival = newRival;
    ServingPlayer = newPlayer;
    CurrentEnviroment = newEnviroment;
    OnePlayerPoints = 0;
    RivalPoints = 0;
    DelayTime = 200;
}

//-------------------------------------------------------------------------
TEGame::~TEGame( )
{
    OnePlayer = NULL;
    Rival = NULL;
    ServingPlayer = NULL;
    CurrentEnviroment = NULL;
}

//-------------------------------------------------------------------------
void TEGame::SetServingPlayer( TEPlayer * newServingPlayer )
{
    ServingPlayer = newServingPlayer;
}

//-------------------------------------------------------------------------
void TEGame::Nulify( )
{
    OnePlayerPoints = 0;
    RivalPoints = 0;
}

//-------------------------------------------------------------------------
TEPlayer * TEGame::CalculateGameWinner( )
{
    while ( OnePlayerPoints != 4
            && RivalPoints != 4 ) {
        TEPlayer * winner = CalculatePointWinner( );
        if ( winner == OnePlayer ) {
            OnePlayerPoints++;
            EmitPlayerPointWin( );
            SetDelay( DelayTime );
        } else {
            RivalPoints++;
            EmitRivalPointWin( );
            SetDelay( DelayTime );
        }

        winner = NULL;

        if ( OnePlayerPoints == 3
             && RivalPoints == 3 ) {
            emit DeuceAchieved( );
            SetDelay( DelayTime );
            break;
        }
    }

    if ( OnePlayerPoints == 4
         && RivalPoints < 3 ) {
        emit PlayerWins( );
        SetDelay( DelayTime );
        return OnePlayer;
    }

    if ( RivalPoints == 4
         && OnePlayerPoints < 3 ) {
        emit RivalWins( );
        SetDelay( DelayTime );
        return Rival;
    }

    Nulify();

    while ( abs( OnePlayerPoints - RivalPoints ) < 2 ) {
        TEPlayer * winner = CalculatePointWinner( );
        if ( winner == OnePlayer ) {
            OnePlayerPoints++;
        } else {
            RivalPoints++;
        }
        winner = NULL;

        if ( RivalPoints == OnePlayerPoints ) {
            RivalPoints = 0;
            OnePlayerPoints = 0;
            emit DeuceAchieved( );
            SetDelay( DelayTime );
        }

        if ( RivalPoints > OnePlayerPoints ) {
            emit RivalAdvantageAchieved( );
            SetDelay( DelayTime );
        }

        if ( OnePlayerPoints > RivalPoints ) {
            emit PlayerAdvantageAchieved( );
            SetDelay( DelayTime );
        }
    }

    if ( OnePlayerPoints == 2 ) {
        emit PlayerWins( );
        SetDelay( DelayTime );
        return OnePlayer;
    } else {
        emit RivalWins( );
        SetDelay( DelayTime );
        return Rival;
    }
}

//-------------------------------------------------------------------------
TEPlayer * TEGame::CalculatePointWinner( )
{
    OnePlayer->SetServing( OnePlayer == ServingPlayer );
    Rival->SetServing( Rival == ServingPlayer );

    double playerSkill = OnePlayer->CalculateCurrentSkill( Rival, CurrentEnviroment );
    double rivalSkill = Rival->CalculateCurrentSkill( OnePlayer, CurrentEnviroment );

    double randomSkillCompetitionValue = qrand( ) * 1.0 / RAND_MAX;
    if ( randomSkillCompetitionValue < playerSkill / ( rivalSkill + playerSkill ) ) {
        return OnePlayer;
    } else {
        return Rival;
    }
}

//-------------------------------------------------------------------------
void TEGame::EmitPlayerPointWin( )
{
    switch ( OnePlayerPoints ) {
    case 1:
        emit PointForPlayer( 15 );
        break;
    case 2:
        emit PointForPlayer( 30 );
        break;
    case 3:
        emit PointForPlayer( 40 );
        break;
    }
}

//-------------------------------------------------------------------------
void TEGame::EmitRivalPointWin( )
{
    switch ( RivalPoints ) {
    case 1:
        emit PointForRival( 15 );
        break;
    case 2:
        emit PointForRival( 30 );
        break;
    case 3:
        emit PointForRival( 40 );
        break;
    }
}
