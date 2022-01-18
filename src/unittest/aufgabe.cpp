//============================================================================
// Name           : aufgabe.cpp
// Description    : unit test of class Duartion
// 		    (in exam "Softwarequalitaet" a.k.a. "Testen")
//============================================================================
//
// Aufgabe:
// ========
// Sie sollen einige Tests mit dem Verfahren "Grenzwertanalyse" fuer die
// Klasse Duration entwickeln, welche eine teilweise normierte Zeitdauer
// definiert (Details siehe unten).
//
// Folgende Aufgaben sind durchzufuehren:
// 1. Erzeugen Sie einen Fork des Pruefungs-Repositories in ihr
//    _persoenliches_ Bitbucket-Projekt, aendern Sie dabei bitte nicht den
//    Repository-Namen.
// 2. Clonen Sie das Repository auf den Rechner im Labor.
// 3. Erstellen Sie die unten angegebenen Tests.
// 4. Aendern Sie moeglichst den Git-Commiter auf Ihren Namen und Ihre E-Mail
//    (es soll also moeglichst nicht "labor" als Commiter auftauchen).
// 5. Committen Sie die Aenderungen im lokalen Repository (Laborrechner).
// 6. Pushen Sie die Aenderungen zu ihrem Bitbucket-Repository
// 7. Schreiben Sie die ersten 11 Zeichen der git-Commit-Nummer Ihrer
//    Loesung auf das Deckblatt (ablesen in Ihrem Bitbucket-Repository,
//    Menu-Punkt "Navigation->Commits")
//
// **************************************************
// * ACHTUNG: Ohne Push kann nicht bewertet werden! *
// **************************************************
//
// Zur Berechnung von Bankzinsen werden Zeitdauern in Zinstage umgerechnet.
// Dabei wird fuer diese Aufgabe angenommen, dass die Banken vereinfacht
// umrechnen (was sie auch tun - aber vielleicht nicht genau so):
// - eine Woche hat 7 Tage (wie immer),
// - ein Monat hat immer 30 Zins-Tage (Tage mit 28/29/31 Tagen werden
//                                     also nicht genau umgerechnet),
// - ein Jahr hat immer 360 Zins-Tage (= 12 Monate * 30 Zinstage).
//
// Zur Sicherheit gegen falsche Zins-Berechnungen wird (fuer diese Aufgabe)
// festgelegt, dass keine Zeitdauer von mehr als 100 Jahren in Zins-Tage
// umgerechnet werden darf. Anderenfalls wird eine Exception vom Typ
// std::out_of_range ausgeloest.
//
// Das beschriebene Verhalten ist in der Funktion Duration::asBankDays()
// umgesetzt.
//
//
// Folgende Auszuege von Grenzfall-Tests sollen entwickelt werden; es
// gilt dabei jeweils:
// - wenn sinnvoll, verwenden Sie moeglichst datengetriebene Tests
// - die zu verwendenden Daten entnehmen Sie Ihrer Grenzwertanalyse
//
// 1. Gutfall-Tests fuer Duration::asBankDays():
//    Erstellen Sie 8 Tests entsprechend des Testverfahrens Grenzwertanalyse.
//
// 2. Fehlerfall-Test fuer Duration::asBankDays():
//    Erstellen Sie 2 Tests entsprechend des Testverfahrens Grenzwertanalyse.
//
// Falls durch Ihre Tests Fehler gefunden werden, muessen Sie den
// Quellcode der Applikation nicht korrigieren; Sie sollten aber
// moeglichst sicher sein, dass nicht Ihr Test den Fehlerzustand
// enthaelt.
//
// Minimalanforderungen fuer die Punktevergabe:
// - Sie haben eine Aenderung durchgefuehrt.
// - Das Unit-Test-Programm ist mit Ihren Tests uebersetzbar, linkbar
//   und ausfuehrbar.
// - Sie haben Ihre Loesung in Ihr Git-Repository des Bitbucket-Servers gepusht.
// - Sie haben die Commit-Nummer Ihrer Loesung auf das Deckblatt geschrieben.
//
// Bewertungskriterien:
// - Vollstaendigkeit des Testumfangs entsprechend der Anforderungen oben
// - Korrektheit der Testfaelle
// - Struktur der Testfaelle (wartbar kodiert, datengetrieben falls
//   sinnvoll, Ersteller:in im Commit-Log erkennbar etc.)
//============================================================================

#include "app-lib/CalendarDate.h"

#include "Helpers.h"
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
using namespace  std;

//TEST(TestenPruefungsaufgabe, ersetzenSieDiesenUnsinnigenBeispielTest) {
//    // Setup
//    CalendarDate someDummyTestDateWhichShouldBeDeleted_Really(1,1,2018);
//    Duration someDummyDurationWhichHasNoSense_don_t_you_think(1,0,0,0);

//    // Execute
//    // ...

//    // Verify
//    EXPECT_EQ(someDummyTestDateWhichShouldBeDeleted_Really, CalendarDate(1,1,2018));
//    EXPECT_EQ(OneDay, someDummyDurationWhichHasNoSense_don_t_you_think);
//    EXPECT_NE(OneDay, OneWeek);
//    FAIL() << "loeschen Sie diesen voellig unsinnigen "
//              "Beispieltestfall und ersetzen Sie ihn "
//              "durch Ihre kreativen Loesungen";

//    // Teardown
//}

struct dataDuration{
    int tag;
    int woche;
    int monat;
    int jahr;
    int ergebnis;
};

vector<dataDuration> durationEimer ={
    {0,0,0,0,0},
    {0,0,0,100,36000},
    {0,0,11,0,330},
    {6,5,12,0,401},
    {7,0,0,0,7},
    {0,5,0,0,35},
    {0,0,0,1,360},
    {0,36000/7,0,0,36000/7*7}
};

class durationGetterTest : public ::testing::TestWithParam<dataDuration>{

};

INSTANTIATE_TEST_CASE_P( OnSomeDayValues, durationGetterTest, ::testing::ValuesIn(durationEimer) );

TEST_P(durationGetterTest, gutfallTests){
    dataDuration data=GetParam();
    Duration object(data.tag, data.woche, data.monat, data.jahr);

    //VERIFY
    EXPECT_EQ(object.asBankDays(), data.ergebnis);
}



TEST(fehlerfallTests, test1){

    //ARRANGE
    Duration data(0,36000/7+1,0,0);

    //VERIFY
    EXPECT_THROW(data.asBankDays(),out_of_range);


}

TEST(fehlerfallTests, test2){

    //ARRANGE
    Duration data(0,0,0,101);

    //VERIFY
    EXPECT_THROW(data.asBankDays(),out_of_range);

}
