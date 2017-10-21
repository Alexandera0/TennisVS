#ifndef COMMONDEFS_H
#define COMMONDEFS_H

#include <QCoreApplication>
#include <QVector>
#include <QString>
#include <QTime>

typedef int naint;
#define TEStr QString
#define TEList QVector<naint>
#define TETimer QTime

enum SurfaceTypeEnum
{
    ST_Clay,
    ST_Hard,
    ST_Grass,
    ST_Carpet
};

enum TournamentTypeEnum
{
    TT_GrandSlamSeries,
    TT_Masters1000Series,
    TT_500Series,
    TT_250Series,
    TT_125Series,
    TT_90Series,
    TT_33Series,
    TT_25Series,
    TT_Friendly
};

enum EventEnum
{
    EV_Match,
    EV_Tournament,
    EV_Season
};

enum AdvantageEnum
{
    AD_None,
    AD_More,
    AD_Less
};

#endif // COMMONDEFS_H
