#include "Headers/PlayUnits/tematch.h"

//-------------------------------------------------------------------------
TEMatch::TEMatch( TEPlayer * newPlayer,
                  TEPlayer * newRival,
                  Enviroment * newEnviroment,
                  MatchRules * newRules )
{
    Set = new TESet( newPlayer,
                     newRival,
                     newEnviroment );
    OnePlayer = newPlayer;
    Rival = newRival;
    ServingPlayer = newPlayer;
    Rules = newRules;
    CurrentEnviroment = newEnviroment;
    Winner = NULL;
    OnePlayerSets = 0;
    RivalSets = 0;
}

//-------------------------------------------------------------------------
TEMatch::~TEMatch()
{
    delete Set;
    OnePlayer = NULL;
    Rival = NULL;
    ServingPlayer = NULL;
    Rules = NULL;
    CurrentEnviroment = NULL;
    Winner = NULL;
}

//-------------------------------------------------------------------------
void TEMatch::SwapServe( )
{
    if ( ServingPlayer == OnePlayer ) {
        ServingPlayer = Rival;
    } else {
        ServingPlayer = OnePlayer;
    }
    emit Swapped( ServingPlayer == OnePlayer );
}

//-------------------------------------------------------------------------
void TEMatch::CalculateMatchWinner( )
{
    while ( OnePlayerSets != Rules->SetsForWin
           && RivalSets != Rules->SetsForWin ) {
        emit NewSetStarted( );
        Set->SetServingPlayer( ServingPlayer );
        if ( Set->CalculateSetWinner( ) == OnePlayer ) {
            OnePlayerSets++;
            emit PlayerSetChange( OnePlayerSets );
        } else {
            RivalSets++;
            emit RivalSetChange( RivalSets );
        }
        SwapServe( );
        Set->Nulify( );
    }

    if ( OnePlayerSets == Rules->SetsForWin ) {
        OnePlayer->RefreshCharacteristics( true, Rival );
        Winner = OnePlayer;
        emit MatchFinished( true );
    } else {
        Rival->RefreshCharacteristics( true, OnePlayer );
        Winner = Rival;
        emit MatchFinished( false );
    }
}
