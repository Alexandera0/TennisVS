#include "Headers/Common/commonfunctions.h"

using namespace CommonStruters;

//-------------------------------------------------------------------------
void CommonFunctions::SetDelay( naint millisecondsToWait )
{
    TETimer dieTime = TETimer::currentTime().addMSecs( millisecondsToWait );
    while( TETimer::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

//-------------------------------------------------------------------------
bool CommonFunctions::operator == ( Characteristics left, Characteristics right )
{
    return left.Name == right.Name;
}

//-------------------------------------------------------------------------
TEStr CommonFunctions::CityTitle( City * proceededCity )
{
    TEStr cityTitle = proceededCity->Name
                    + TEStr(" [")
                    + proceededCity->Country
                    + TEStr("]");
    return cityTitle;
}

//-------------------------------------------------------------------------
TEStr CommonFunctions::TournamentTypeTitle( TournamentTypeEnum tournamentType )
{
    TEStr title;
    switch( tournamentType ) {
        case TT_GrandSlamSeries:
            title = "Grand Slam Series";
            break;
        case TT_Masters1000Series:
            title = "Masters 1000 Series";
            break;
        case TT_500Series:
            title = "500 Series";
            break;
        case TT_250Series:
            title = "250 Series";
            break;
        case TT_125Series:
            title = "125 Series";
            break;
        case TT_90Series:
            title = "90 Series";
            break;
        case TT_33Series:
            title = "33 Series";
            break;
        case TT_25Series:
            title = "25 Series";
            break;
        case TT_Friendly:
            title = "Friendly";
            break;
    }
    return title;
}

//-------------------------------------------------------------------------
// Сортировка номеров участников
TEList * CommonFunctions::SortParticipation( TEList participationsList )
{
    naint tempNumber;
    bool exit = false;
    while (!exit) {
        exit = true;
        naint listSize = participationsList.size();
        for ( naint i = 0; i < listSize - 1; i++) {
            if ( participationsList[i] > participationsList[i + 1] ) {
                tempNumber = participationsList[i];
                participationsList[i] = participationsList[i + 1];
                participationsList[i + 1] = tempNumber;
                exit = false;
            }
        }
    }
    TEList * sortedList = new TEList( participationsList );
    return sortedList;
}

//-------------------------------------------------------------------------
// Сортировка случайным образом
TEList * CommonFunctions::RandomSwap( TEList proceededList, naint start, naint number)
{
    //создаем вектор из случайных чисел размерности степени двойки (это number)
    TEList randomVector;
    for (int i = 0; i < number; i++) {
        randomVector.push_back( qrand() % 200 );
    }

    //запускаем сортировку рандомного вектора
    int tempNumber;
    bool exit = false;
    while (!exit)
    {
        exit = true;
        for ( int i = 0; i < number - 1; i++ ) {
            if ( randomVector[i] > randomVector[i + 1] ) {
                // здесь выполняется сортировка не только вектора случайных чисел
                // но и соответствующего участка вектора сеяных (т.е. сортируем только тех, кто попал в интересующую нас степень двойки)
                tempNumber = randomVector[i];
                randomVector[i] = randomVector[i + 1];
                randomVector[i + 1] = tempNumber;
                tempNumber = proceededList[start + i];
                proceededList[i + start] = proceededList[i + start + 1];
                proceededList[i + start + 1] = tempNumber;
                exit = false;
            }
        }
    }
    TEList * randomSortedList = new TEList( proceededList );
    return randomSortedList;
}

