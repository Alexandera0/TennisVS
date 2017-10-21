#include "Headers/PlayUnits/teplayer.h"

//-------------------------------------------------------------------------
TEPlayer::TEPlayer( )
{
    PlayerCharacteristics.Name = "NewPlayer";
    PlayerCharacteristics.NativeCity = new City;
    PlayerCharacteristics.NativeCity->Name = "Moscow";
    PlayerCharacteristics.NativeCity->Country = "RUS";
    PlayerCharacteristics.Age = 14;
    PlayerCharacteristics.Rank = 0;
    PlayerCharacteristics.PowerSkill = 50;
    PlayerCharacteristics.ServeSkill = 1;
    PlayerCharacteristics.RecieveSkill = 1;
    PlayerCharacteristics.Talent = 1;
    PlayerCharacteristics.Charisma = 1;
    PlayerCharacteristics.FavouriteSurface = ST_Hard;
    RatingPointsSum = 0;
    RatingPoints.clear();
}

//-------------------------------------------------------------------------
TEPlayer::TEPlayer(Characteristics * characterictics )
{
    PlayerCharacteristics.Age = characterictics->Age;
    PlayerCharacteristics.Charisma = characterictics->Charisma;
    PlayerCharacteristics.FavouriteSurface = characterictics->FavouriteSurface;
    PlayerCharacteristics.Name = characterictics->Name;
    PlayerCharacteristics.NativeCity = characterictics->NativeCity;
    PlayerCharacteristics.PowerSkill = characterictics->PowerSkill;
    PlayerCharacteristics.Rank = characterictics->Rank;
    PlayerCharacteristics.RecieveSkill = characterictics->RecieveSkill;
    PlayerCharacteristics.ServeSkill = characterictics->ServeSkill;
    PlayerCharacteristics.Talent = characterictics->Talent;
    RatingPointsSum = 0;
}

//-------------------------------------------------------------------------
void TEPlayer::operator = ( TEPlayer newPlayer )
{
    PlayerCharacteristics = newPlayer.PlayerCharacteristics;
    RatingPoints = newPlayer.RatingPoints;
    IsPlayingNow = newPlayer.IsPlayingNow;
}

//-------------------------------------------------------------------------
bool TEPlayer::operator == ( TEPlayer somePlayer )
{
    return PlayerCharacteristics == somePlayer.PlayerCharacteristics;
}

//-------------------------------------------------------------------------
void TEPlayer::SetNewRatingPointsAtWeek( naint newPoints,
                                   naint week )
{
    if ( week > 0 ){
        naint size = RatingPoints.size( );
        if ( week - 1 < size ) {
            RatingPointsSum -= RatingPoints[week - 1];
            RatingPoints[week - 1] = newPoints;
            RatingPointsSum += newPoints;
        } else {
            while( week - 1 >= size )
            {
                RatingPoints.append( 0 );
            }
                RatingPoints[week - 1] = newPoints;
                RatingPointsSum += newPoints;
        }
    }
}

//-------------------------------------------------------------------------
void TEPlayer::SetNewRatingPoints( TEList * newRatingPoints )
{
    RatingPoints = *newRatingPoints;
    RatingPointsSum = 0;
    naint size = RatingPoints.size( );
    for ( naint i = 0; i < size; i++) {
        RatingPointsSum += RatingPoints[i];
    }
}

//-------------------------------------------------------------------------
void TEPlayer::SetPlaying( bool playingStatus )
{
    IsPlayingNow = playingStatus;
}

//-------------------------------------------------------------------------
void TEPlayer::SetServing( bool servingStatus)
{
    IsServingNow = servingStatus;
}

//-------------------------------------------------------------------------
void TEPlayer::SetDeclared( bool declaredStatus )
{
    IsDeclaredNow = declaredStatus;
}

//-------------------------------------------------------------------------
double TEPlayer::CalculateCurrentSkill( TEPlayer * rival,
                                        Enviroment * enviroment )
{
    double rivalryCoefficient = GetRivalryCoefficient( rival );
    double enviromentCoefficient = GetEnviromentCoefficient( enviroment );
    double serveRecieveCoefficient = GetServeRecieveCoefficient( );
    double charismaCoefficient = GetCharismaCoefficient( );
    double surfaceCoefficient = GetSurfaceCoefficient( enviroment );
    double currentSkill = PlayerCharacteristics.PowerSkill * (1 +
                                                      surfaceCoefficient+
                                                      rivalryCoefficient +
                                                      enviromentCoefficient +
                                                      serveRecieveCoefficient +
                                                      charismaCoefficient);

    return currentSkill;
}

//-------------------------------------------------------------------------
double TEPlayer::GetRivalryCoefficient( TEPlayer * rival )
{
    return 0;
}

//-------------------------------------------------------------------------
double TEPlayer::GetSurfaceCoefficient ( Enviroment * enviroment )
{
  if ( enviroment->Surface == PlayerCharacteristics.FavouriteSurface ) {
      return 0.15;
  } else {
      return 0;
  }
}

//-------------------------------------------------------------------------
double TEPlayer::GetEnviromentCoefficient( Enviroment * enviroment )
{
    if ( enviroment->CurrentCity->Country == PlayerCharacteristics.NativeCity->Country ) {
        return 0.1;
    } else {
        return 0;
    }
}

//-------------------------------------------------------------------------
double TEPlayer::GetServeRecieveCoefficient( )
{
    double serveRecieveCoefficient;
    if ( IsServingNow ) {
        serveRecieveCoefficient = PlayerCharacteristics.ServeSkill * 1.0 / 20;
    } else {
        serveRecieveCoefficient = PlayerCharacteristics.RecieveSkill * 1.0 / 250;
    }
    return serveRecieveCoefficient;
}

//-------------------------------------------------------------------------
double TEPlayer::GetCharismaCoefficient( )
{
    double charismaCoefficient = 0;

    if ( PlayerCharacteristics.Charisma <= 7 ) {
        charismaCoefficient = -0.02;
    }
    if ( PlayerCharacteristics.Charisma > 7
         && PlayerCharacteristics.Charisma <= 9 ) {
        charismaCoefficient = -0.01;
    }
    if ( PlayerCharacteristics.Charisma > 9
         && PlayerCharacteristics.Charisma <= 12 ) {
        charismaCoefficient = 0.0075;
    }
    if ( PlayerCharacteristics.Charisma > 12
         && PlayerCharacteristics.Charisma <= 14 ) {
        charismaCoefficient = 0.015;
    }
    if ( PlayerCharacteristics.Charisma >= 14 ) {
        charismaCoefficient = 0.02;
    }

    int randomMood = qrand() % 21;

    if ( randomMood <= 7 ) {
        charismaCoefficient += -0.0015;
    }
    if ( randomMood > 7
         && randomMood <= 13 ) {
        charismaCoefficient += 0.0;
    }
    if ( randomMood > 13
         && randomMood <= 16 ) {
        charismaCoefficient += 0.0015;
    }
    if ( randomMood > 16 ) {
        charismaCoefficient += 0.002;
    }

    return charismaCoefficient;
}

//-------------------------------------------------------------------------
void TEPlayer::RefreshCharacteristics( bool isWinner,
                                       TEPlayer * rival )
{
    if ( isWinner ) {
        int randomSkillChanger = qrand() % 2 + 1;

        if ( PlayerCharacteristics.Age >= 24
             && randomSkillChanger == 1 ) {
            PlayerCharacteristics.PowerSkill++;
        }

        if ( PlayerCharacteristics.Rank > rival->PlayerCharacteristics.Rank + 20 ) {
            PlayerCharacteristics.PowerSkill++;
        }

        if ( rival->PlayerCharacteristics.Rank < 10
               && PlayerCharacteristics.Rank > 25 ) {
            PlayerCharacteristics.PowerSkill++;
        }

        if ( rival->PlayerCharacteristics.Rank < 3
               && PlayerCharacteristics.Rank > 6 ) {
            PlayerCharacteristics.PowerSkill++;
        }

        randomSkillChanger = qrand() % 2 + 1;

        if ( PlayerCharacteristics.Age < 24
                && randomSkillChanger == 1 ) {
            PlayerCharacteristics.PowerSkill += 2;
        }

        if ( PlayerCharacteristics.Rank < 8
            && rival->PlayerCharacteristics.Rank > 30
            && rival->PlayerCharacteristics.Age <= 22 ) {
            rival->PlayerCharacteristics.PowerSkill++;
        }

        if ( PlayerCharacteristics.Age <= 28 ) {
            PlayerCharacteristics.PowerSkill--;
        }

        if ( PlayerCharacteristics.Rank - 35 > rival->PlayerCharacteristics.Rank ) {
            rival->PlayerCharacteristics.PowerSkill--;
        }

        if ( rival->PlayerCharacteristics.Age > 28) {
                    rival->PlayerCharacteristics.PowerSkill -= 2;
        }

        randomSkillChanger = qrand() % 2 + 1;

        if ( PlayerCharacteristics.Age > 34
             && randomSkillChanger == 1) {
            PlayerCharacteristics.PowerSkill--;
        }

        randomSkillChanger = qrand( ) % 2 + 1;

        if ( rival->PlayerCharacteristics.Age > 34
             && randomSkillChanger == 1 ) {
            rival->PlayerCharacteristics.PowerSkill--;
        }
     }
}

//-------------------------------------------------------------------------
TEStr TEPlayer::ReturnTitle( )
{
    TEStr title = TEStr("[")
                + TEStr::number(PlayerCharacteristics.Rank)
                + TEStr("] ")
                + PlayerCharacteristics.Name
                + TEStr(" (")
                + PlayerCharacteristics.NativeCity->Country
                + TEStr(")");
    return title;
}

//-------------------------------------------------------------------------
TEStr TEPlayer::ReturnName( )
{
    return PlayerCharacteristics.Name;
}
