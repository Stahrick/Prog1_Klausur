//
// Created by Peddy on 05.12.2021.
//

#ifndef PROGRAMMIERAUFGABE_SEM1_AUSGABEN_H
#define PROGRAMMIERAUFGABE_SEM1_AUSGABEN_H

#include <stdio.h>

#include "datentypen.h"

void drucke_studenten_lang_by_val(struct studenten_typ student);
void drucke_studenten_kurz_by_val(struct studenten_typ student);
void drucke_studenten_kurz_by_ref(struct studenten_typ *student_ptr);

#endif //PROGRAMMIERAUFGABE_SEM1_AUSGABEN_H
