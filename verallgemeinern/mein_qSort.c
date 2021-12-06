//
// Created by Peddy on 06.12.2021.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mein_qSort.h"

/*
 * Parameter:
 * teil_feld_
*/
void mein_zerlegen(void *teil_feld_ptr, size_t member_size, int num_member, int startLinks, int startRechts
        , int (*compar)(const void *, const void *))
{

    int i;
    int laufLinks = startLinks;
    int laufRechts = startRechts;
    int vergleichselementIndex =
            (startLinks + startRechts) / 2; /*(1)*/
    //int vergleichselement = teil_feld_ptr[vergleichselementIndex];
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
            //while (laufLinks_elem < vergleichselement_ptr)
            laufLinks++;
            laufLinks_elem = calc_eff_addr_void_arr(teil_feld_ptr, laufLinks, member_size, num_member);
        }
        /* Suche von rechts kleinere Elemente als */
        /* Vergleichselement (2.2)*/
        void *laufRechts_elem = calc_eff_addr_void_arr(teil_feld_ptr, laufRechts, member_size, num_member);
        while (compar(laufRechts_elem, vergleichselement_ptr) > 0) {
            //while (laufRechts_elem > vergleichselement_ptr)
            laufRechts--;
            laufRechts_elem = calc_eff_addr_void_arr(teil_feld_ptr, laufRechts, member_size, num_member);
        }
        if (laufLinks <= laufRechts) /* Vertauschen (2.3)*/
        {
            //int zwischen = teil_feld_ptr[laufLinks];
            //zwischen aus Schleife rausgezogen, nicht jedes mal neu Speicher zu res und freizugeben
            memcpy(zwischen_ptr, laufLinks_elem, member_size);
            memcpy(laufLinks_elem, laufRechts_elem, member_size);
            memcpy(laufRechts_elem, zwischen_ptr, member_size);
            laufLinks++; laufRechts--;
            /*teil_feld_ptr[laufLinks] = teil_feld_ptr[laufRechts];
            teil_feld_ptr[laufRechts] = zwischen_ptr;
            laufLinks++; laufRechts--;*/
        }
    } while (laufLinks <= laufRechts); /*(2.4)*/
    free(zwischen_ptr);

    /* Vorsortiertes Feld ausgeben */
    for (i = 0; i < startLinks; i++)
        printf(" ");
    for (i=startLinks; i <= startRechts; i++) {
        void *elem = calc_eff_addr_void_arr(teil_feld_ptr, i, member_size, num_member);
        printf("%i ", *((int *)elem));
    }
    printf("\n");
    /* Jetzt beide Teilfelder rekursiv gleich behandeln (3)*/
    if (startLinks < laufRechts)
        mein_zerlegen(teil_feld_ptr, member_size, num_member, startLinks, laufRechts, compar);
    if (laufLinks < startRechts)
        mein_zerlegen(teil_feld_ptr, member_size, num_member, laufLinks, startRechts, compar);
} // mein_zerlegen

void* calc_eff_addr_void_arr(void *arr_start_ptr, unsigned int index, size_t member_size, unsigned int num_member) {
    if(arr_start_ptr == NULL) {
        perror("Kann nicht die effektive Addresse aus ungueltigem Zeiger errechnen.\n");
        exit(EXIT_FAILURE);
    }
    char *arr_char_ptr = (char*) arr_start_ptr;
    void *arr_end_ptr = (void*)(arr_char_ptr + (member_size * num_member));

    void *eff_addr = (void*)(arr_char_ptr + (member_size * index));
    if(eff_addr > arr_end_ptr) {
        perror("Effektive Adresse liegt nicht mehr in geliefertem Array.\n");
        exit(EXIT_FAILURE);
    }
    return eff_addr;
}

void mein_qSort (void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    mein_zerlegen(base, size, nmemb, 0, nmemb-1, compar);
} // mein_qSort
