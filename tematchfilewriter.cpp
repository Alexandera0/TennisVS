#include "Headers/FileWriter/tematchfilewriter.h"


// Refreshing methods
//-------------------------------------------------------------------------
void TEMatchFileWriter::RefreshServingString( )
{
    if ( OnePlayerServing ) {
        ServingString = "\"IsPlayerServing\":\"true\"";
    } else {
        ServingString = "\"IsPlayerServing\":\"false\"";
    }
    SaveCounterFile( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::RefreshSetsString( )
{
    SetsString = TEStr("\"Sets\":[")
               + TEStr::number( OnePlayerSets ) + TEStr(",")
               + TEStr::number( RivalsSets ) + TEStr("]");
    SaveCounterFile( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::RefreshGamesString( )
{
    GamesString = TEStr("\"Games\":{");
    TEStr OnePlayerGamesString = TEStr("\"Player1\":[");
    TEStr RivalGamesString = TEStr("\"Player2\":[");
    naint sizeGamesOnePlayer = OnePlayerGames.size( );
    for ( naint i = 0; i < sizeGamesOnePlayer; i++ ) {
        if ( i < sizeGamesOnePlayer - 1) {
            OnePlayerGamesString += TEStr::number( OnePlayerGames[i] ) + TEStr(",");
            RivalGamesString += TEStr::number( RivalGames[i] ) + TEStr(",");
        } else {
            OnePlayerGamesString += TEStr::number( OnePlayerGames[i] ) + TEStr( "]" );
            RivalGamesString += TEStr::number( RivalGames[i] ) + TEStr( "]" );
        }
    }
    GamesString += OnePlayerGamesString
                + TEStr(",")
                + RivalGamesString
                + TEStr("}");
    SaveCounterFile( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::RefreshPointsString( )
{
    switch( OnePlayerAdvantage ) {
        case AD_None:
            PointsString = "\"Points\":["
                    + TEStr::number( OnePlayerPoints ) + TEStr(",")
                    + TEStr::number( RivalPoints )
                    + "]";
            break;
        case AD_Less:
            PointsString = "\"Points\":["
                    + TEStr::number( OnePlayerPoints ) + TEStr(",")
                    + TEStr( "A" )
                    + "]";
            break;
        case AD_More:
            PointsString = "\"Points\":["
                    + TEStr( "A" ) + TEStr(",")
                    + TEStr::number( RivalPoints )
                    + "]";
            break;
    }
    SaveCounterFile( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::SaveGeneralMatchInfo( TEMatch * teMatch )
{
    OnePlayerName = teMatch->OnePlayer->ReturnName( );
    RivalName = teMatch->Rival->ReturnName( );
    TEStr surface = TEStr( teMatch->CurrentEnviroment->Surface );
    TEStr cityTitle = CityTitle( teMatch->CurrentEnviroment->CurrentCity );
    TEStr command = TEStr("echo {")
                  + TEStr("\"Event\": \"Match\",")
                  + TEStr("\"Player1\":\"") + OnePlayerName + TEStr("\",")
                  + TEStr("\"Player2\":\"") + RivalName + TEStr("\",")
                  + TEStr("\"Surface\":") + surface + TEStr(",")
                  + TEStr("\"City\":\"") + cityTitle + TEStr("\"}")
                  + TEStr(" > ") + TEStr("GeneralInfo.json");
    system( command.toStdString( ).c_str( ) );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::SaveCounterFile( )
{
    TEStr commandCreateTempFile = TEStr("echo {")
                  + ServingString + TEStr(",")
                  + SetsString + TEStr(",")
                  + GamesString + TEStr(",")
                  + PointsString + TEStr(",")
                  + WinnerString
                  + TEStr("} > ") + TEStr( "CounterFile.json.tmp");
    TEStr commandDeletePreviousFile = TEStr( "del CounterFile.json" );
    TEStr commandRenameTemp = TEStr( "rename CounterFile.json.tmp CounterFile.json" );
    system( commandCreateTempFile.toStdString( ).c_str( ) );
    system( commandDeletePreviousFile.toStdString( ).c_str( ) );
    system( commandRenameTemp.toStdString( ).c_str( ) );
}

// Constructor and destrutor
//-------------------------------------------------------------------------
TEMatchFileWriter::TEMatchFileWriter( TEMatch * teMatch )
{
    OnePlayerSets = 0;
    RivalsSets = 0;
    OnePlayerGames.clear( );
    RivalGames.clear( );
    OnePlayerPoints = 0;
    RivalPoints = 0;
    OnePlayerTieBreakPoints.clear( );
    RivalTieBreakPoints.clear( );
    OnePlayerServing = true;
    OnePlayerAdvantage = AD_None;
    ServingString = "\"IsPlayerServing\":\"true\"";
    SetsString = "\"Sets\":[0,0]";
    GamesString = "";
    PointsString = "";
    WinnerString = "";
    SaveGeneralMatchInfo( teMatch );
}

TEMatchFileWriter::~TEMatchFileWriter( )
{
    OnePlayerName = "";
    RivalName = "";
    OnePlayerSets = 0;
    RivalsSets = 0;
    OnePlayerGames.clear( );
    RivalGames.clear( );
    OnePlayerPoints = 0;
    RivalPoints = 0;
    OnePlayerTieBreakPoints.clear( );
    RivalTieBreakPoints.clear( );
    OnePlayerServing = true;
    OnePlayerAdvantage = AD_None;
    ServingString = "";
    SetsString = "";
    GamesString = "";
    PointsString = "";
    WinnerString = "\"Winner\":\"none\"";
}

// Slots
//-------------------------------------------------------------------------
void TEMatchFileWriter::PlayerPointsChanged( naint points )
{
    OnePlayerPoints = points;
    RefreshPointsString( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::RivalPointsChanged( naint points )
{
    RivalPoints = points;
    RefreshPointsString();
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::PlayerAdvantageAchieved( )
{
    OnePlayerAdvantage = AD_More;
    RefreshPointsString( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::RivalAdvantageAchieved( )
{
    OnePlayerAdvantage = AD_Less;
    RefreshPointsString( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::DeuceAchieved( )
{
    OnePlayerAdvantage = AD_None;
    RefreshPointsString( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::PlayerGameChanged( naint games )
{
    naint size = OnePlayerGames.size( );
    OnePlayerGames[ size - 1 ] = games;
    RefreshGamesString( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::RivalGameChanged( naint games )
{
    naint size = RivalGames.size( );
    RivalGames[ size - 1 ] = games;
    RefreshGamesString( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::NewSetStarted( )
{
    OnePlayerGames.append( 0 );
    RivalGames.append( 0 );
    OnePlayerTieBreakPoints.append( 0 );
    RivalTieBreakPoints.append( 0 );
    OnePlayerAdvantage = AD_None;
    RefreshGamesString( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::PlayerSetsChanged( naint sets )
{
    OnePlayerSets = sets;
    RefreshSetsString( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::RivalSetsChanged( naint sets )
{
    RivalsSets = sets;
    RefreshSetsString( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::PlayerTiePointChanged( naint tieBreakPoints )
{
    naint size = OnePlayerTieBreakPoints.size( );
    OnePlayerTieBreakPoints[ size - 1 ] = tieBreakPoints;
    RefreshGamesString( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::RivalTiePointChanged( naint tieBreakPoints )
{
    naint size = RivalTieBreakPoints.size( );
    RivalTieBreakPoints[ size - 1 ] = tieBreakPoints;
    RefreshGamesString( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::RecieveSwapped( bool isOnePlayerServing )
{
    OnePlayerServing = isOnePlayerServing;
    RefreshServingString( );
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::MatchFinished( bool isOnePlayerWinner )
{
    WinnerString = TEStr(" \"Winner\" = \"");
    if ( isOnePlayerWinner ) {
        WinnerString += OnePlayerName;
    } else {
        WinnerString += RivalName;
    }
    WinnerString += TEStr( "\"");
}

//-------------------------------------------------------------------------
void TEMatchFileWriter::SetFilePath( TEStr newFilePath )
{
    FilePath = newFilePath;
}
