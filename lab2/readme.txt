/**********************************************************************
 *  Knäcka lösenord readme.txt
 **********************************************************************/

 Ungefärligt antal timmar spenderade på labben (valfritt):
5

/**********************************************************************
 *  Ge en högnivåbeskrivning av ditt program decrypt.c.
 **********************************************************************/

Decrypt använder sig av algoritmen "meet in the middle" och den algoritmen går ut på att dela upp beräkningarna 
i två delar. Eftersom det krypterade lösenordet är givet kan vi säga att den lägre delen av lösenordet krypterat 
plus den övre delen av lösenordet krypterat är lika med det hela krypterade lösenordet. Om vi då tar det hela 
minus den lägre får vi krypteringen för den högre. 

Så vi kan göra en loop som går igenom hälften av tabellen och vid varje iteration så subtraheras det hela
med den lägre värdet och resultatet blir då det krypterade högre och det läggs in i en hashtabell som nyckel 
med värdet som det okrypterade lägre. Därefter går vi in i en ny loop där vi itererar den högre halvan av 
tabellen och kollar vid varje iteration om den krypterade versionen av den högre finns som nyckel i hashtabellen 
från den andra loopen. Finns den betyder det att denna högre och värdet till dess nyckel adderar till lösenordet.

/**********************************************************************
 *  Beskriv symboltabellen du använt för decrypt.c.
 **********************************************************************/

Vi använde en unordered_map med datatypen Key som nyckel och en vector av Keys som värde. Vi använder en vector för att hantera
kollision på nycklarna. Sedan överlagrade vi structmallen hash där vi använde vår egna Key. Detta medför att när vi 
skapar en unordered_map med vår egenskapade typ så kommer den "automatiskt" använda sig av den överlagrade hash-structen.

/**********************************************************************
 *  Ge de dekrypterade versionerna av alla lösenord med 8 och 10
 *  bokstäver i uppgiften du lyckades knäca med DIN kod.
 **********************************************************************/


8 bokstäver         10 bokstäver
-----------         ------------
congrats            completely
youfound            unbreakabl
theright            cryptogram
solution            ormaybenot



/****************************************************************************
 *  Hur lång tid använder brute.c för att knäcka lösenord av en viss storlek?
 *  Ge en uppskattning (baserad på tidskomplexiteten)  markerad med en asterisk
 *  om det tar längre tid än vad du orkar vänta. Ge en kort motivering för
 *  dina uppskattningar.
 ***************************************************************************/


Char     Brute     
--------------
 4       0 s
 5       2 s
 6       109 s
 8       *


/******************************************************************************
 *  Hur lång tid använder decrypt.c för att knäcka lösenord av en viss storlek?
 *  Hur mycket minne använder programmet?
 *  Ge en uppskattning markerad med en asterisk om det tar längre tid än vad
 *  du orkar vänta. Ge en kort motivering för dina uppskattningar.
 ******************************************************************************/

Char    Tid (sekunder)    Minne (bytes)
----------------------------------------
6        0                4 540 181 
8        1                274 549 980 
10       72               * Tog väldigt lång tid med valgrind..
12       *                *

/*************************************************************************
 * Hur många operationer använder brute.c för ett N-bitars lösenord?
 * Hur många operationer använder din decrypt.c för ett N-bitars lösenord?
 * Använd ordo-notation.
 *************************************************************************/

Brute == O(2^N)
Decrypt == O(2^N/2)

/*************************************************************************
 * Vilka egenskaper skulle ni leta efter i en hashfunktion för att
 * försäkra er om att den är "säker"?
 *************************************************************************/

Inversen till en effektiv hashfunkion bör vara svår att hitta. Så även om det hashade lösenordet
läcker så är det ytterst svårt att dekryptera det för att få ut det riktiga lösenordet. Det är lämpligt
att använda mycket olika data som tillhör objektet på ett slumpmässigt sätt.  