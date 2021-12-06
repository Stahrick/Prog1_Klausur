cmake_minimum_required(VERSION 3.16)
project(Programmieraufgabe_Sem1 C)

set(CMAKE_C_STANDARD 11)

add_executable(Programmieraufgabe_Studenten
        studenten/studenten01.c
         studenten/datentypen.h studenten/ausgaben.c studenten/ausgaben.h verallgemeinern/mein_qSort.c verallgemeinern/mein_qSort.h)

add_executable(Programmieraufgabe_Verallge verallgemeinern/verallgemeinern01.c verallgemeinern/mein_qSort.c verallgemeinern/mein_qSort.h)
