#include "tennisengine.h"


// Engine construtor
//-------------------------------------------------------------------------
TennisEngine::TennisEngine( TEStr newStoragePath,
              TEStr newDataBasePath )
{
    StoragePath = newStoragePath;
    DatabasePath = newDataBasePath;
}

// Defaults
//-------------------------------------------------------------------------
City * TennisEngine::CreateDefaultCity( )
{
    City * newCity = new City;
    newCity->Name = "Moscow";
    newCity->Country = "Rus";
    return newCity;
}

//-------------------------------------------------------------------------
Enviroment * TennisEngine::CreateDefaultEnviroment( )
{
    Enviroment * newEnviroment = new Enviroment;
    newEnviroment->CurrentCity = CreateDefaultCity();
    newEnviroment->Surface = ST_Hard;
    return newEnviroment;
}

//-------------------------------------------------------------------------
MatchRules * TennisEngine::CreateDefaultRules( )
{
    MatchRules * newRules = new MatchRules;
    newRules->SetsForWin = 3;
    newRules->SetsMaxCount = 5;
    return newRules;
}

//-------------------------------------------------------------------------
Characteristics * TennisEngine::CreateDefaultCharacteristics( )
{
    Characteristics * newCharacterictics = new Characteristics;
    newCharacterictics->Age = 16;
    newCharacterictics->Charisma = 5;
    newCharacterictics->FavouriteSurface = ST_Hard;
    newCharacterictics->Name = "Yakovlev";
    newCharacterictics->NativeCity = CreateDefaultCity( );
    newCharacterictics->PowerSkill = 50;
    newCharacterictics->Rank = 0;
    newCharacterictics->RecieveSkill = 5;
    newCharacterictics->ServeSkill = 5;
    newCharacterictics->Talent = 5;
    return newCharacterictics;
}

//-------------------------------------------------------------------------
TEPlayer * TennisEngine::CreateDefaultPlayer( )
{
    TEPlayer * player = new TEPlayer( );
    return player;
}

// Customized
//-------------------------------------------------------------------------
City * TennisEngine::CreateCity( TEStr cityName,
                 TEStr countryName )
{
    City * newCity = new City;
    newCity->Name = cityName;
    newCity->Country = countryName;
    return newCity;
}

//-------------------------------------------------------------------------
Enviroment * TennisEngine::CreateEnviroment( City * newCity,
                             SurfaceTypeEnum surfaceType)
{
    Enviroment * newEnviroment = new Enviroment;
    newEnviroment->CurrentCity = newCity;
    newEnviroment->Surface = surfaceType;
    return newEnviroment;
}

//-------------------------------------------------------------------------
MatchRules * TennisEngine::CreateRules( naint setsForWin,
                        naint setsMaxCount)
{
    MatchRules * newRules = new MatchRules;
    newRules->SetsForWin = setsForWin;
    newRules->SetsMaxCount = setsMaxCount;
    return newRules;
}

//-------------------------------------------------------------------------
Characteristics * TennisEngine::CreateCharacteristics( TEStr newName,
                                       SurfaceTypeEnum newFavouriteSurface,
                                       City * newNativeCity,
                                       naint newAge,
                                       naint newRank,
                                       naint newServeSkill,
                                       naint newRecieveSkill,
                                       naint newTalent,
                                       naint newCharisma,
                                       double newPowerSkill )
{
    Characteristics * newCharacterictics = new Characteristics;
    newCharacterictics->Age = newAge;
    newCharacterictics->Charisma = newCharisma;
    newCharacterictics->FavouriteSurface = newFavouriteSurface;
    newCharacterictics->Name = newName;
    newCharacterictics->NativeCity = newNativeCity;
    newCharacterictics->PowerSkill = newPowerSkill;
    newCharacterictics->Rank = newRank;
    newCharacterictics->RecieveSkill = newRecieveSkill;
    newCharacterictics->ServeSkill = newServeSkill;
    newCharacterictics->Talent = newTalent;
    return newCharacterictics;
}

//-------------------------------------------------------------------------
TEPlayer * TennisEngine::CreatePlayer( Characteristics * newCharacteristics,
                         TEList * ratingPoints )
{
    TEPlayer * player = new TEPlayer( newCharacteristics );
    if ( ratingPoints != NULL ) {
        player->SetNewRatingPoints( ratingPoints );
    }
    return player;
}

// Players loading
//-------------------------------------------------------------------------
TEPlayer * TennisEngine::LoadTEPlayerFromDatabase( TEStr playerName )
{
    return NULL;
}

// Match managment
//-------------------------------------------------------------------------
TEMatch * TennisEngine::CreateMatch( TEPlayer * onePlayer,
             TEPlayer * rival,
             Enviroment * newEnviroment,
             MatchRules * newRules )
{
    TEMatch * teMatch = new TEMatch( onePlayer,
                                     rival,
                                     newEnviroment,
                                     newRules );
    return teMatch;
}

//-------------------------------------------------------------------------
void TennisEngine::ProcessMatch( TEMatch * proceededMatch )
{
    TEMatchFileWriter * fileWriter = new TEMatchFileWriter( proceededMatch );
    fileWriter->SetFilePath( StoragePath );
    AttachFileWriterToMatch( fileWriter, proceededMatch );
    proceededMatch->CalculateMatchWinner( );
}

//-------------------------------------------------------------------------
void TennisEngine::AttachFileWriterToMatch( TEMatchFileWriter * fileWriter, TEMatch * teMatch )
{
    QObject::connect( teMatch, SIGNAL( NewSetStarted( ) ), fileWriter, SLOT( NewSetStarted( ) ) );
    QObject::connect( teMatch, SIGNAL( PlayerSetChange( naint ) ), fileWriter, SLOT( PlayerSetsChanged( naint ) ) );
    QObject::connect( teMatch, SIGNAL( RivalSetChange( naint ) ), fileWriter, SLOT( RivalSetsChanged( naint ) ) );
    QObject::connect( teMatch, SIGNAL( Swapped( bool ) ), fileWriter, SLOT( RecieveSwapped( bool ) ) );
    QObject::connect( teMatch, SIGNAL( MatchFinished( bool ) ), fileWriter, SLOT( MatchFinished( bool ) ) );

    QObject::connect( teMatch->Set, SIGNAL( PlayerGamesChange( naint ) ), fileWriter, SLOT( PlayerGameChanged( naint ) ) );
    QObject::connect( teMatch->Set, SIGNAL( RivalGamesChange( naint ) ), fileWriter, SLOT( RivalGameChanged( naint ) ) );
    QObject::connect( teMatch->Set, SIGNAL( PlayerTiePointsChange( naint ) ), fileWriter, SLOT( PlayerTiePointChanged( naint ) ) );
    QObject::connect( teMatch->Set, SIGNAL( RivalTiePointsChange( naint ) ), fileWriter, SLOT( RivalTiePointChanged( naint ) ) );
    QObject::connect( teMatch->Set, SIGNAL( Swapped( bool ) ), fileWriter, SLOT( RecieveSwapped( bool ) ) );

    QObject::connect( teMatch->Set->Game, SIGNAL( PointForPlayer( naint ) ), fileWriter, SLOT( PlayerPointsChanged( naint ) ) );
    QObject::connect( teMatch->Set->Game, SIGNAL( PointForRival( naint ) ), fileWriter, SLOT( RivalPointsChanged( naint ) ) );
    QObject::connect( teMatch->Set->Game, SIGNAL( DeuceAchieved( ) ), fileWriter, SLOT( DeuceAchieved( ) ) );
    QObject::connect( teMatch->Set->Game, SIGNAL( PlayerAdvantageAchieved( ) ), fileWriter, SLOT( PlayerAdvantageAchieved( ) ) );
    QObject::connect( teMatch->Set->Game, SIGNAL( RivalAdvantageAchieved( ) ), fileWriter, SLOT( RivalAdvantageAchieved( ) ) );
}
