#ifndef TEPLAYER_H
#define TEPLAYER_H

#include "Headers/Common/commonfunctions.h"

using namespace CommonFunctions;

class TEPlayer
{
    /////////////////////////////////////////////////////
    Characteristics PlayerCharacteristics;
    TEList RatingPoints;
    naint RatingPointsSum;
    bool IsPlayingNow = false;
    bool IsDeclaredNow = false;
    bool IsServingNow = false;
    /////////////////////////////////////////////////////
public:
    TEPlayer( );
    TEPlayer( Characteristics * characterictics );
    void operator = ( TEPlayer newPlayer );
    bool operator == ( TEPlayer somePlayer);
    void SetNewRatingPointsAtWeek( naint newPoints, naint week);
    void SetNewRatingPoints( TEList * newRatingPoints );
    void SetPlaying( bool playingStatus );
    void SetServing( bool servingStatus);
    void SetDeclared( bool declaredStatus );
    double CalculateCurrentSkill( TEPlayer * rival, Enviroment * enviroment);
    void RefreshCharacteristics( bool isWinner, TEPlayer * rival);
    TEStr ReturnTitle( );
    TEStr ReturnName( );

private:
    double GetRivalryCoefficient( TEPlayer * rival );
    double GetSurfaceCoefficient ( Enviroment * enviroment );
    double GetEnviromentCoefficient( Enviroment * enviroment );
    double GetServeRecieveCoefficient();
    double GetCharismaCoefficient();
};


#endif // TEPLAYER_H
