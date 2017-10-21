#ifndef FILEWRITER_H
#define FILEWRITER_H

#include "Headers/PlayUnits/tematch.h"

class TEMatchFileWriter : public QObject
{
    Q_OBJECT

    TEStr FilePath;

    // Players
    TEStr OnePlayerName;
    TEStr RivalName;

    // Counters
    naint OnePlayerSets;
    naint RivalsSets;
    TEList OnePlayerGames;
    TEList RivalGames;
    naint OnePlayerPoints;
    naint RivalPoints;
    TEList OnePlayerTieBreakPoints;
    TEList RivalTieBreakPoints;
    bool OnePlayerServing;
    AdvantageEnum OnePlayerAdvantage;

    // Refreshing strings
    TEStr ServingString;
    TEStr SetsString;
    TEStr GamesString;
    TEStr PointsString;
    TEStr WinnerString;
    // Refreshing methods
    void RefreshServingString( );
    void RefreshSetsString( );
    void RefreshGamesString( );
    void RefreshPointsString( );
    // Saving methods
    void SaveGeneralMatchInfo( TEMatch * teMatch );
    void SaveCounterFile( );

public:

    TEMatchFileWriter( TEMatch * teMatch );
    void SetFilePath( TEStr newFilePath );
    ~TEMatchFileWriter( );

public slots:
    // Points slots
    void PlayerPointsChanged( naint points );
    void RivalPointsChanged( naint points );
    void PlayerAdvantageAchieved( );
    void RivalAdvantageAchieved( );
    void DeuceAchieved( );
    // Games slots
    void PlayerGameChanged( naint games );
    void RivalGameChanged( naint games );
    // Sets slots
    void NewSetStarted( );
    void PlayerSetsChanged( naint sets );
    void RivalSetsChanged( naint sets );
    // Tie break slots
    void PlayerTiePointChanged( naint tieBreakPoints );
    void RivalTiePointChanged( naint tieBreakPoints );
    // Serve swapping slot
    void RecieveSwapped( bool isOnePlayerServing );
    // Match ending slot
    void MatchFinished( bool isOnePlayerWinner );
};

#endif // FILEWRITER_H
