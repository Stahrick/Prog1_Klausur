//
// Created by Peddy on 06.12.2021.
//

#ifndef PROGRAMMIERAUFGABE_SEM1_MEIN_QSORT_H
#define PROGRAMMIERAUFGABE_SEM1_MEIN_QSORT_H

void mein_qSort (void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
void mein_zerlegen(void *teil_feld_ptr, size_t member_size, int num_member, int startLinks, int startRechts
        , int (*compar)(const void *, const void *));
void* calc_eff_addr_void_arr(void *arr_start_ptr, unsigned int index, size_t member_size, unsigned int num_member);


#endif //PROGRAMMIERAUFGABE_SEM1_MEIN_QSORT_H
