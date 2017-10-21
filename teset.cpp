#include "Headers/PlayUnits/teset.h"

//-------------------------------------------------------------------------
TESet::TESet( TEPlayer * newPlayer,
              TEPlayer * newRival,
              Enviroment * newEnviroment )
{
    Game = new TEGame( newPlayer,
                       newRival,
                       newEnviroment );
    OnePlayer = newPlayer;
    Rival = newRival;
    ServingPlayer = newPlayer;
    CurrentEnviroment = newEnviroment;
    OnePlayerGames = 0;
    RivalGames = 0;
    OnePlayerTieBreakPoints = 0;
    RivalTieBreakPoints = 0;
}

//-------------------------------------------------------------------------
TESet::~TESet( )
{
    delete Game;
    OnePlayer = NULL;
    Rival = NULL;
    ServingPlayer = NULL;
    CurrentEnviroment = NULL;
}

//-------------------------------------------------------------------------
void TESet::SetServingPlayer( TEPlayer * newServingPlayer )
{
    ServingPlayer = newServingPlayer;
}

//-------------------------------------------------------------------------
void TESet::SwapServe( )
{
    if ( ServingPlayer == OnePlayer) {
        ServingPlayer = Rival;
    } else {
        ServingPlayer = OnePlayer;
    }
    emit Swapped( ServingPlayer == OnePlayer);
}

//-------------------------------------------------------------------------
void TESet::Nulify( )
{
    OnePlayerGames = 0;
    RivalGames = 0;
    OnePlayerTieBreakPoints = 0;
    RivalTieBreakPoints = 0;
}

//-------------------------------------------------------------------------
TEPlayer * TESet::CalculateSetWinner( )
{
    while ( OnePlayerGames != 6
            && RivalGames != 6 )
    {
        emit NewGameStarted( );
        Game->SetServingPlayer( ServingPlayer );
        TEPlayer * winner = Game->CalculateGameWinner( );
        if ( winner == OnePlayer ) {
            OnePlayerGames++;
            emit PlayerGamesChange( OnePlayerGames );
        } else {
            RivalGames++;
            emit RivalGamesChange( RivalGames );
        }
        winner = NULL;
        SwapServe( );
        Game->Nulify( );
    }

    if ( OnePlayerGames == 6
        && RivalGames < 5 ) {
        return OnePlayer;
    }

    if ( RivalGames == 6
         && OnePlayerGames < 5 ) {
        return Rival;
    }

    while ( OnePlayerGames != 7
            && RivalGames != 7 )
    {
        TEPlayer * winner;
        emit NewGameStarted( );
        if ( OnePlayerGames == 6
             && RivalGames == 6 ) {
            winner = CalculateTieBreakWinner();
        } else {
            Game->SetServingPlayer( ServingPlayer );
            winner = Game->CalculateGameWinner( );
        }
        if ( winner == OnePlayer ) {
            OnePlayerGames++;
            emit PlayerGamesChange( OnePlayerGames );
        } else {
            RivalGames++;
            emit RivalGamesChange( RivalGames );
        }
        winner = NULL;
        SwapServe( );
        Game->Nulify( );
    }

    if ( OnePlayerGames == 7 ) {
        return OnePlayer;
    } else {
        return Rival;
    }
}

//-------------------------------------------------------------------------
TEPlayer * TESet::CalculateTieBreakWinner( )
{
    emit TieBreakStarted( );

    while ( OnePlayerTieBreakPoints != 7
            && RivalTieBreakPoints != 7 )
    {
        TEPlayer * winner = CalculatePointWinner( );
        if ( winner == OnePlayer ) {
            OnePlayerTieBreakPoints++;
            emit PlayerTiePointsChange( OnePlayerTieBreakPoints );
        } else {
            RivalTieBreakPoints++;
            emit RivalTiePointsChange( RivalTieBreakPoints );
        }
        winner = NULL;
        if ( ( OnePlayerTieBreakPoints
              + RivalTieBreakPoints
              + 1 ) % 2 == 0) {
            SwapServe( );
        }
    }

    if ( abs( OnePlayerTieBreakPoints - RivalTieBreakPoints ) > 1 ) {
        if ( OnePlayerTieBreakPoints == 7 ) {
            return OnePlayer;
        } else {
            return Rival;
        }
    } else {
        while ( abs( OnePlayerTieBreakPoints - RivalTieBreakPoints ) < 2 )
        {
            TEPlayer * winner = CalculatePointWinner( );
            if ( winner == OnePlayer ) {
                OnePlayerTieBreakPoints++;
                emit PlayerTiePointsChange( OnePlayerTieBreakPoints );
            } else {
                RivalTieBreakPoints++;
                emit RivalTiePointsChange( RivalTieBreakPoints );
            }

            winner = NULL;
            if ( ( OnePlayerTieBreakPoints
                  + RivalTieBreakPoints
                  + 1 ) %2 == 0) {
                SwapServe( );
            }
        }
    }

    if ( OnePlayerTieBreakPoints - RivalTieBreakPoints > 0 ) {
        return OnePlayer;
    } else {
        return Rival;
    }
}

//-------------------------------------------------------------------------
TEPlayer * TESet::CalculatePointWinner( )
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
