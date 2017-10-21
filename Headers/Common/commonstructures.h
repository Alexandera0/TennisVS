#ifndef COMMONSTRUCTURES_H
#define COMMONSTRUCTURES_H

#include "commondefs.h"

namespace CommonStruters {

    struct City
    {
        TEStr Name;
        TEStr Country;
    };

    struct Characteristics
    {
        naint CharacteristicCount = 9;
        TEStr Name;
        SurfaceTypeEnum FavouriteSurface;
        City * NativeCity;
        naint Age;
        naint Rank;
        naint ServeSkill;
        naint RecieveSkill;
        naint Talent;
        naint Charisma;
        double PowerSkill;
    };

    struct MatchRules
    {
        naint SetsForWin;
        naint SetsMaxCount;
    };

    struct Enviroment
    {
        City * CurrentCity;
        SurfaceTypeEnum Surface;
    };

    struct TournamentInfo
    {
        TEStr Name;
        Enviroment * TournamentEnviroment;
        MatchRules * Rules;
        TournamentTypeEnum TournamentType;
    };

}

#endif // COMMONSTRUCTURES_H
