/**
 * Angelehnt an das Beispielprogramm "quicksrt.c" von
 * Goll S.490 (7.Aufl.).
 * 1. Semester
 *
 * Meine Matrikelnummer:
 * Mein Name:
 *
 */

//Systemheader
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Eigene Header
#include "mein_qSort.h"



/*
 * Divide-And-Conquer Algorithmus zum Sortieren eines Arrays beliebigen Typs.
 * An Quicksort angelehnt mit mittlerem Pivot Element
 *
 * Parameter:
 * teil_feld_ptr: Zeiger auf den Start des Werte Arrays
 * member_size: Größe eines Elements im Array
 * num_member: Anzahl an Elementen im Array
 * startLinks: Linke Betrachtungsgrenze des Arrays(siehe Quicksort)
 * startRechts: Rechte Betrachtungsgrenze des Arrays(siehe Quicksort)
*/
void mein_zerlegen(void *teil_feld_ptr, size_t member_size, int num_member, int startLinks, int startRechts
        , int (*compar)(const void *, const void *))
{

    int i;
    int laufLinks = startLinks;
    int laufRechts = startRechts;
    int vergleichselementIndex =
            (startLinks + startRechts) / 2; /*(1)*/
    void *vergleichselement_ptr = calc_eff_addr_void_arr(teil_feld_ptr, vergleichselementIndex
            , member_size, num_member);

    void *zwischen_ptr = malloc(member_size);
    do /*(2)*/
    { /* Schleife, bis laufLinks und laufRechts zusammentreffen */
        /* Suche von links groessere Elemente als */
        /* Vergleichselement (2.1)*/

        //neues Element muss in der Schleife errechnet werden
        void *laufLinks_elem = calc_eff_addr_void_arr(teil_feld_ptr, laufLinks, member_size, num_member);
        while (compar(laufLinks_elem, vergleichselement_ptr) < 0) {
            laufLinks++;
            laufLinks_elem = calc_eff_addr_void_arr(teil_feld_ptr, laufLinks, member_size, num_member);
        }
        /* Suche von rechts kleinere Elemente als */
        /* Vergleichselement (2.2)*/
        void *laufRechts_elem = calc_eff_addr_void_arr(teil_feld_ptr, laufRechts, member_size, num_member);
        while (compar(laufRechts_elem, vergleichselement_ptr) > 0) {
            laufRechts--;
            laufRechts_elem = calc_eff_addr_void_arr(teil_feld_ptr, laufRechts, member_size, num_member);
        }
        if (laufLinks <= laufRechts) /* Vertauschen (2.3)*/
        {
            //zwischen aus Schleife rausgezogen, nicht jedes mal neu Speicher zu reservieren und freizugeben
            memcpy(zwischen_ptr, laufLinks_elem, member_size);
            memcpy(laufLinks_elem, laufRechts_elem, member_size);
            memcpy(laufRechts_elem, zwischen_ptr, member_size);
            laufLinks++; laufRechts--;
            //Für den Fall, dass das Vergleichselement getauscht wurde, so müssen die Pointer auch
            //aktualisiert werden
            if(laufLinks == vergleichselementIndex) {
                void *temp = laufLinks_elem;
                laufLinks_elem = vergleichselement_ptr;
                vergleichselement_ptr = temp;
            }else if(laufRechts == vergleichselementIndex) {
                void *temp = laufRechts_elem;
                laufRechts_elem = vergleichselement_ptr;
                vergleichselement_ptr = temp;
            }
        }
    } while (laufLinks <= laufRechts); /*(2.4)*/
    free(zwischen_ptr);

    /* Vorsortiertes Feld ausgeben */
    for (i = 0; i < startLinks; i++)
        printf(" ");
    for (i=startLinks; i <= startRechts; i++) {
        void *elem = calc_eff_addr_void_arr(teil_feld_ptr, i, member_size, num_member);
        printf("%i ", *((int*)elem));
    }
    printf("\n");
    /* Jetzt beide Teilfelder rekursiv gleich behandeln (3)*/
    if (startLinks < laufRechts)
        mein_zerlegen(teil_feld_ptr, member_size, num_member, startLinks, laufRechts, compar);
    if (laufLinks < startRechts)
        mein_zerlegen(teil_feld_ptr, member_size, num_member, laufLinks, startRechts, compar);
} // mein_zerlegen

/*
 * Berechnet die effektive Addresse zum Umgang mit void Pointer Arithmetik
 *
 * Parameter:
 *  arr_start_ptr: Zeiger auf den Start des Werte Arrays
 *  index: Auf das wievielte Element soll zugegriffen werden
 *  member_size: Größe eines Elements des Arrays
 *  num_member: Anzahl der Elemente im Array
 *
 *  Rückgabewert:
 *   Kein Rückgabewert
 */
void* calc_eff_addr_void_arr(void *arr_start_ptr, unsigned int index, size_t member_size, unsigned int num_member) {
    if(arr_start_ptr == NULL) {
        perror("Kann nicht die effektive Addresse aus ungueltigem Zeiger errechnen.\n");
        exit(EXIT_FAILURE);
    }
    char *arr_char_ptr = (char*) arr_start_ptr;
    void *arr_end_ptr = (void*)(arr_char_ptr + (member_size * num_member));

    void *eff_addr = (void*)(arr_char_ptr + (member_size * index));
    //Schutz vor rechtem out-of-bounds beim Array Zugriff
    //Out-of-bounds über die linke Seite wird per unsigned index verhindert
    if(eff_addr > arr_end_ptr) {
        perror("Effektive Adresse liegt nicht mehr in geliefertem Array.\n");
        exit(EXIT_FAILURE);
    }
    return eff_addr;
}
/*
 * Wrapper Funktion zum Aufruf der eigenen QSort Implementierung
 *
 * Parameter:
 *  base: Zeiger auf den Beginn des Werte Arrays
 *  nmemb: Anzahl der Elemente im Array
 *  compar: Vergleichsfunktion zum Vergleichen zweier Werte im gelieferten Array
 */
void mein_qSort (void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    mein_zerlegen(base, size, nmemb, 0, nmemb-1, compar);
} // mein_qSort
