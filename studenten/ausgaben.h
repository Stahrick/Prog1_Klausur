/**
 * TINF21CS1, Programmieraufgabe
 * 1. Semester
 *
 * Meine Matrikelnummer:
 * Mein Name:
 *
 */

#ifndef PROGRAMMIERAUFGABE_SEM1_AUSGABEN_H
#define PROGRAMMIERAUFGABE_SEM1_AUSGABEN_H

//Systemheader
#include <stdio.h>

//Eigene Header
#include "datentypen.h"

//Prototypen
void drucke_studenten_lang_by_val(struct studenten_typ student);
void drucke_studenten_kurz_by_val(struct studenten_typ student);
void drucke_studenten_kurz_by_ref(struct studenten_typ *student_ptr);

#endif //PROGRAMMIERAUFGABE_SEM1_AUSGABEN_H
