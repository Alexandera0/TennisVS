#ifndef COMMONFUNCTIONS_H
#define COMMONFUNCTIONS_H

#include "Headers/Common/commonstructures.h"

using namespace CommonStruters;

namespace CommonFunctions {

    void SetDelay( naint millisecondsToWait );

    bool operator == ( Characteristics left, Characteristics right );

    TEStr CityTitle( City * someCity );

    TEStr TournamentTypeTitle( TournamentTypeEnum tournamentType );

    // сортировка номеров участников
    TEList * SortParticipation( TEList participantsList);

    // сортировка случайным образом
    TEList * RandomSwap( TEList proceededList, naint start, naint number);

}

#endif // COMMONFUNCTIONS_H
