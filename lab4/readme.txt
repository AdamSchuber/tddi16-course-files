/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

 Ungefärligt antal timmar spenderade på labben (valfritt):

/**********************************************************************
 * Empirisk analys
 *
 * Fyll i tabellen nedan med riktiga körtider i sekunder när det känns
 * vettigt att vänta på hela beräkningen.
 * Ge uppskattningar av körtiden (baserat på tidskomplexiteten)
 * i övriga fall.
 *
 **********************************************************************/
    
      N       brute       sortering
 ----------------------------------
    150
    200
    300
    400
    800
   1600
   3200
   6400
  12800


/**********************************************************************
 * Teoretisk analys
 *
 * Ge ordo-uttryck för värstafallstiden för programmen som en funktion
 * av N. Ge en kort motivering.
 *
 * Matchar brute-lösningen sitt värstafall i praktiken, eller har den
 * ett medelfall som är bättre?
 *
 **********************************************************************/

Brute:

Sortering:


/**********************************************************************
 * Energianvändning
 *
 * Antag att du använder mönsterigenkänningsprogrammet för att analysera
 * data från en kamera. Kameran sitter i en byggnad och tar en bild
 * på stommen av byggnaden var 30:e minut. Bilden förbehandlas sedan
 * lite, innan punkter som representerar stommen skickas till
 * mönsterigenkänningsprogrammet. Hittas inte tillräckligt många raka
 * linjer så betyder det att något håller på att gå sönder, och
 * att byggnaden behöver noggrannare inspektion.
 *
 * Hur mycket energi sparar du på ett år om du använder din snabbare
 * sorteringslösning i stället för brute-lösningen? Du kan anta följande:
 * - Systemet körs 24/7 under hela året.
 * - Inget annat körs på det här systemet.
 * - Systemet drar 8 W när det inte gör något (idle)
 * - Systemet drar 36 W när det arbetar (med 1 kärna)
 * - Räkna med att ditt program körs var 30:e minut (= 2 gånger/timme)
 * - För- och efterbehandling är snabba, så vi kan bortse från dem
 * - Indata till programmet innehåller ca 6400 punkter
 * - Det är inte skottår (= 365 dagar)
 *
 * Att jämföra med drar en kombinerad kyl/frys ca 200 kWh per år
 * (enligt Energimyndigheten).
 *
 * Kom ihåg: energi mäts ofta i kWh, vilket är:
 *  energi (kWh) = effekt (kW) * tid (h)
 *
 * Tips: ett sätt att räkna på är att först räkna förbrukningen av
 * ett system som inte gör något på ett helt år, sedan lägga till
 * den extra förbrukningen (36 W - 8 W = 28 W) för tiden som systemet
 * är aktiv.
 *
 * (Siffrorna är löst baserade på en Intel i9-9900K, vi räknar bara på
 * CPU:n för enkelhets skull, besparingarna blir sannolikt större om
 * vi räknar på större delar av systemet, även om andra komponenter
 * också drar ström i "idle".)
 *
 **********************************************************************/

Förbrukning av brute på ett år: ? kWh

Förbrukning av sotering på ett år: ? kWh

Skillnad: ? kWh

