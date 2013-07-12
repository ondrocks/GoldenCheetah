/*
 * Copyright (c) 2013 Mark Liversedge (liversedge@gmail.com)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _GC_Athlete_h
#define _GC_Athlete_h 1

#include <QDir>
#include <QSqlDatabase>
#include <QtGui>
#include <QNetworkReply>

class MetricAggregator;
class Zones;
class HrZones;
class RideFile;
class ErgFile;
class RideMetadata;
class WithingsDownload;
class ZeoDownload;
class CalendarDownload;
class ICalendar;
class CalDAV;
class Seasons;
class RideNavigator;
class Lucene;
class NamedSearches;
class RideFileCache;

class Context;
class Context;

class Athlete : public QObject
{
    Q_OBJECT

    public:
        Athlete(Context *context, const QDir &home);

        // basic athlete info
        QString cyclist; // the cyclist name
        bool useMetricUnits;
        QDir home;
        const Zones *zones() const { return zones_; }
        const HrZones *hrZones() const { return hrzones_; }
        Zones *zones_;
        HrZones *hrzones_;
        void setCriticalPower(int cp);
        QSqlDatabase db;
        MetricAggregator *metricDB;
        RideMetadata *rideMetadata_;
        Seasons *seasons;
        QList<RideFileCache*> cpxCache;

        // athlete's calendar
        CalendarDownload *calendarDownload;
        WithingsDownload *withingsDownload;
        ZeoDownload *zeoDownload;
#ifdef GC_HAVE_ICAL
        ICalendar *rideCalendar;
        CalDAV *davCalendar;
#endif

        // ride metadata definitions
        RideMetadata *rideMetadata() { return rideMetadata_; }

        // indexes / filters
#ifdef GC_HAVE_LUCENE
        Lucene *lucene;
        NamedSearches *namedSearches;
#endif
        Context *context;

        void notifyZonesChanged() { zonesChanged(); }
        void notifySeasonsChanged() { seasonsChanged(); }

    signals:
        void zonesChanged();
        void seasonsChanged();

    public slots:
        void configChanged();

};
#endif
