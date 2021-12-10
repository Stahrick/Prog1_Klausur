/**
 * TINF21CS1, Programmieraufgabe
 * 1. Semester
 * 
 * Meine Matrikelnummer: 
 * Mein Name:
 *
 */

// System-Header-Dateien
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Eigene Header-Dateien
#include "datentypen.h"
#include "ausgaben.h"
#include "../verallgemeinern/mein_qSort.h"

// Prototypen
int vgl_fkt_kurs_nachname_vorname(
	const void*v1_ptr, const void*v2_ptr);
struct studenten_typ* kopiere_studenten_auf_heap(struct studenten_typ);
int vgl_fkt_zeiger_matrikel_nr(
	const void*v1_ptr, const void*v2_ptr);
void studenten_feld_ausgeben(struct studenten_typ *feld, int feld_n
        , void (*ausgabe_fkt_ptr)(struct studenten_typ student));
void free_student_arr(struct studenten_typ **stud_arr, int n_members);


/**
 * Hauptprogramm.
 */
int main(int argc, char*argv[])
{
	// Initialisierungsliste mit Testdaten
	struct studenten_typ studenten_feld[] = {
			{ 1000, { "Eva",	"Meier"		}, "TINF21CS1" },
			{ 1001, { "Eva",	"Meier"		}, "TINF21CS1" },
			{ 1002, { "Karla",	"Schulze"	}, "TINF21CS1" },
			{ 1003, { "Eva",	"Schlau"	}, "TINF21CS1" },
			{ 1004, { "Berta",	"Meier"		}, "TINF21CS1" },
			{ 1005, { "Tom",	"Schmitt"	}, "TINF21CS1" },
			{ 1006, { "Peter",	"Weise"		}, "TINF21CS1" },
			{ 1007, { "Max",	"Weise"		}, "TINF21CS1" },
			{ 1008, { "Anton",	"Meyer"		}, "TINF21CS1" },
			{ 1009, { "Eva",	"Meier"		}, "TINF20CS2" },
	};
	// Aufgabe 1.2
	// Anzahl der Beispieldatensaetze in "studenten_feld"
	//size_t studenten_feld_n = 10;
    size_t studenten_feld_n = sizeof(studenten_feld) / sizeof(studenten_feld[0]);
    printf("Anzahl: %lu\n", studenten_feld_n);
	// Zeiger fuer die Indizierung mit 1..n
	struct studenten_typ *studenten_feld_1_bis_n_ptr = &(studenten_feld[-1]);
	// Zeigerfeld, das auf die im Heap liegenden Studenten-Objekte verweist
	struct studenten_typ **studenten_feld_2ptr = NULL;
	// Laufvariable
	size_t i;

	printf("Das urspruengliche Feld mit den Studenten (kurze Ausgabe):\n");
	// Aufgabe 1.7 (1/2)
	if(0)
	{
		for(i = 0; i < studenten_feld_n; i++)
			drucke_studenten_kurz_by_val(studenten_feld[i]);
		printf("\n");
	}
	else
	{
		// Aufgabe 1.7 (1/2)
		// ... studenten_feld_ausgeben(...);
        studenten_feld_ausgeben(studenten_feld, studenten_feld_n, drucke_studenten_kurz_by_val);
	}
	
	printf("Sortieren des Feldes nach dem Kurs, dem Nachnamen und dem Vornamen ...\n");
	/*qsort(studenten_feld, studenten_feld_n, sizeof(studenten_feld[0]),
		vgl_fkt_kurs_nachname_vorname);
	 */
    mein_qSort(studenten_feld, studenten_feld_n, sizeof(studenten_feld[0]),
          vgl_fkt_kurs_nachname_vorname);

	printf("Das sortierte Feld mit den Studenten (lange Ausgabe):\n");
	// Aufgabe 1.7 (2/2)
	if(0)
	{
		for(i = 0; i < studenten_feld_n; i++)
			drucke_studenten_lang_by_val(studenten_feld[i]);
		printf("\n");
	}
	else
	{
		// Aufgabe 1.7 (2/2)
		// ... studenten_feld_ausgeben(...);
        studenten_feld_ausgeben(studenten_feld, studenten_feld_n, drucke_studenten_lang_by_val);
	}
	

	printf("Nach Eva Meier (TINF21CS1) suchen...\n");
	{
		// Aufgabe 1.4
		struct studenten_typ student;
		struct studenten_typ *ergebnis_ptr = NULL;

		// Studenten-Variable mit 0 fuellen, damit keine
		//  Warnung erscheint, auch wenn Sie die Aufgabe 1.4
		//  noch nicht bearbeitet haben
		memset(&student, 0, sizeof(student));

		// student initialisieren
		//    ... Ihr Quelltext!!! ...

        strcpy(student.kurs, "TINF21CS1");
        //Initialisiere vollständigkeitshalber auch matr_nr auch wenn nicht von vgl benötigt
        student.matrikel_nr = 1001;

        //Setze Werte für namens_typ
        struct namens_typ stud_name;
        //memset ist hierbei nicht notwendig, da wir die beiden Speicherbereiche vorname_ptr und
        //nachname_ptr nach dem deklarieren direkt durch die strdup pointer beschreiben.
        stud_name.vorname_ptr = strdup("Eva");
        stud_name.nachname_ptr = strdup("Meier");

        student.name = stud_name;


		// bsearch() aufrufen
		//    ... Ihr Quelltext!!! ...

        //Es gibt zwei Eva Meier in TINF21CS1
        //Da die Vergleichsfunktion nicht nach Matr-Nummer filtern soll, wird erste gefundene von
        //bsearch verwendet
        ergebnis_ptr = bsearch(&student, studenten_feld, studenten_feld_n
                , sizeof(studenten_feld[0]), vgl_fkt_kurs_nachname_vorname);

        // Suchergebnis auswerten
		// Aufgabe 1.5

        /*
         * Es gibt in diesem Array 2 Treffer für die gegebenen Suchanforderungen.
         * Man könnte die Treffer stattdessen einem Array oder einer Liste hinzufügen
         * Da wir vor dem bsearch nicht wissen, wieviele Treffer wird haben ist ein Array in
         * diesem Fall unpraktisch
         * Eine Liste kann durch generierung neuer Listenelemente dynamisch erweitert werden
         * Bei jedem Treffer wird Speicher für ein neues Listenelement reserviert und der
         * gefundene studenten_feld eintrag per zeiger ins listenelement eingetragen.
         * Danach wird das Listenelement noch mit der Liste per vorwärtszeiger und ggf
         * rückwertszeiger verknüpft.
         * Zusätzlich ist dann bsearch in der jetzigen Form unpraktisch, da es laut man Doku
         * unspezifiziert ist, welches Element zurückgegeben wird, wenn es mehrere passende gibt.
         * Durch den vorherigen Einsatz von qsort ist das Array aber sortiert, also könnte man um
         * den Ergebnis Pointer nach oben und unten nach weiteren Ergebnissen suchen und sie der
         * Liste hinzufügen.
         */

		if(ergebnis_ptr != NULL)
			printf("Die Studentin gibt es; Matrikelnummer = %d\n",
				ergebnis_ptr->matrikel_nr);
		else
			printf("Die gesuchte Studentin wurde nicht gefunden.\n");
	}
	
	printf("Das Feld in Kurzform; Ausgabefunktion erhaelt die Speicheradresse:\n");
	for(i = 0; i < studenten_feld_n; i++)
	{
		// Aufgabe 1.8 (2/2)
		// ... drucke_studenten_kurz_by_ref(...);
        drucke_studenten_kurz_by_ref(&(studenten_feld[i]));
	}
	printf("\n");

	// Aufgabe 1.9
	printf("Das Feld mit der Indizierung 1..n durchlaufen:\n");
	// studenten_feld_1_bis_n_ptr ....
	for(i = 1; i <= studenten_feld_n; i++)
	{
		drucke_studenten_kurz_by_val(studenten_feld_1_bis_n_ptr[i]);
	}
	printf("\n");

	printf("Ein Feld mit Zeigern auf die Studenten-Objekte\n"
		"auf dem Heap einrichten...\n");
	studenten_feld_2ptr = (struct studenten_typ**)calloc(studenten_feld_n, sizeof(*studenten_feld_2ptr));
	if(studenten_feld_2ptr == NULL)
	{
		fprintf(stderr, "Heap voll! Datei %s, Zeile %d, Version %s %s\n",
			__FILE__, __LINE__, __DATE__, __TIME__);
		exit(EXIT_FAILURE);
	}

	// Aufgabe 1.10 (2/2)
	if(1)
	{
		printf("Die Studenten auf den Heap kopieren...\n");
		for(i = 0; i < studenten_feld_n; i++)
			studenten_feld_2ptr[i] = kopiere_studenten_auf_heap(studenten_feld[i]);

		printf("Das Feld mit den Zeigern auf die Studenten ausgeben:\n");
		for(i = 0; i < studenten_feld_n; i++)
			drucke_studenten_lang_by_val(*studenten_feld_2ptr[i]);

		// Aufgabe 1.11 (2/2)
		if(1)
		{
			printf("Das Zeigerfeld entsprechend den Matrikelnummern sortieren...\n");
			/*qsort(studenten_feld_2ptr, studenten_feld_n, sizeof(*studenten_feld_2ptr),
				vgl_fkt_zeiger_matrikel_nr);
			 */
            mein_qSort(studenten_feld_2ptr, studenten_feld_n, sizeof(*studenten_feld_2ptr),
                  vgl_fkt_zeiger_matrikel_nr);

			printf("Das sortierte Zeigerfeld ausgeben:\n");
			for(i = 0; i < studenten_feld_n; i++)
				drucke_studenten_lang_by_val(*studenten_feld_2ptr[i]);
		}

	}

    //Aufgabe 1.12
    //Reservierten Heap Speicher wieder freigeben
    free_student_arr(studenten_feld_2ptr, studenten_feld_n);
    free(studenten_feld_2ptr);

	return EXIT_SUCCESS;
} // main



/**
 * Diese Vergleichsfunktion dient zum Vergleichen
 * von 2 Studentenobjekten, wobei die Adressen der
 * beiden Studenten als Parameter erwartet werden.
 * Als Vergleichskriterien dienen der Kurs, der Nachname
 * und der Vorname.
 * Parameter:
 *	v1_ptr - Adresse des 1. Studenten-Objektes.
 *	v2_ptr - Adresse des 2. Studenten-Objektes.
 * Rueckgabewert:
 *	neg. Wert --> 1. Student vor 2. Student einzusortieren.
 *	0 --> beide Studenten gleich.
 *	pos. Wert --> 1. Student nach 2. Student einzusortieren.
 */
int vgl_fkt_kurs_nachname_vorname(
	const void*v1_ptr, const void*v2_ptr)
{
	// Aufgabe 1.3
	//    ... Ihr Quelltext!!! ...

    //Auf NULL Pointer überprüfen
    if(v1_ptr == NULL || v2_ptr == NULL){
        perror("Kann keine Null Zeiger vergleichen.\n");
        exit(EXIT_FAILURE);
    }
    //Cast zu Studenten_Typ Pointer
    struct studenten_typ *stud1_ptr = (struct studenten_typ *) v1_ptr;
    struct studenten_typ *stud2_ptr = (struct studenten_typ *) v2_ptr;

    int kurs_comp = strcmp(stud1_ptr->kurs, stud2_ptr->kurs);
    if(kurs_comp == 0) {
        struct namens_typ name1 = stud1_ptr->name;
        struct namens_typ name2 = stud2_ptr->name;

        //Überprüfen ob nachname und später vorname für beide zugewiesen sind vor vergleich
        //Nötige konsistenz der daten wird erst überprüft wenn nötig. Performance Optimierung
        if(name1.nachname_ptr == NULL || name2.nachname_ptr == NULL) {
            perror("Nachname nicht gesetzt. Vergleich kann nicht durchgefuehrt werden.\n");
            exit(EXIT_FAILURE);
        }
        int nachn_comp = strcmp(name1.nachname_ptr, name2.nachname_ptr);
        if(nachn_comp == 0) {
            if(name1.vorname_ptr == NULL || name2.vorname_ptr == NULL) {
                perror("Vorname nicht gesetzt. Vergleich kann nicht durchgefuehrt werden.\n");
                exit(EXIT_FAILURE);
            }

            int vorn_comp = strcmp(name1.vorname_ptr, name2.vorname_ptr);
            return vorn_comp;
        }else{
            return nachn_comp;
        }
    }else{
        return kurs_comp;
    }
} // vgl_fkt_kurs_nachname_vorname


/**
 * Diese Funktion gibt ein Feld mit Studenten aus,
 * wobei die Ausgabe nicht direkt erfolgt, sondern
 * mittels einer Callback-Funktion. Diese ermoeglicht
 * es, die Form der Ausgabe weitgehend frei einstellen
 * zu koennen.
 * Parameter:
 *	feld - Anfangsadresse des Feldes mit den Studenten.
 *	feld_n - Anzahl der Feldelemente.
 *	ausgabe_fkt_ptr - Einsprungadresse der aktuell
 *		gewuenschten Callback-Funktion fuer die
 *		Ausgabe eines Studenten.
 * Rueckgabewert:
 *	Keiner!
 */
// Aufgabe 1.6
// ... studenten_feld_ausgeben(... feld, ... feld_n,
//						...ausgabe_fkt_ptr...)
// {
//    ... Ihr Quelltext!!! ...
// } // studenten_feld_ausgeben
void studenten_feld_ausgeben(struct studenten_typ *feld, int feld_n, void (*ausgabe_fkt_ptr)(struct studenten_typ student)) {
    //Auf ungültige Parameter prüfen
    if(feld == NULL || ausgabe_fkt_ptr == NULL || feld_n < 0) {
        perror("Ungueltige Parameter fuer Funktion studenten_feld_ausgeben");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < feld_n; i++) {
        ausgabe_fkt_ptr(feld[i]);
    }
}


/**
 * Diese Funktion kopiert einen Studentendatensatz,
 * der mittels call-by-value uebergeben wird, auf 
 * den Heap, wobei auch der Vor- und Nachname als
 * neue Objekte angelegt werden.
 * Parameter:
 *  student - Auf den Heap zu kopierender Student; wird
 *		mittels call-by-value uebergeben.
 * Rueckgabewert:
 *	Adresse des Studenten-Objektes auf dem Heap.
 */
struct studenten_typ* kopiere_studenten_auf_heap(struct studenten_typ student)
{
    struct studenten_typ *student_heap = (struct studenten_typ*) malloc(sizeof(student));
    //Ein Aufruf von malloc für namens_typ ist hier nicht mehr notwendig, da bereits mit
    //malloc für student_heap auch Speicher für namens_typ reserivert wurde.
    if(student_heap == NULL) {
        //Hier Ausnahmsweise fprintf statt perror verwendet um Aufgabenstellung zu entsprechen
        //perror erlaubt nämlich keine Parameter wie __FILE__
        fprintf(stderr, "Speicherplatz auf heap reicht nicht aus!"
                        "Student konnte nicht auf Heap kopiert werden."
                        "Datei %s, Zeile %d, Version %s %s\n",
                __FILE__, __LINE__, __DATE__, __TIME__);
        exit(EXIT_FAILURE);
    }
    struct namens_typ name = student_heap->name;

    student_heap->matrikel_nr = student.matrikel_nr;
    strcpy(student_heap->kurs, student.kurs);
    name.nachname_ptr = strdup(student.name.nachname_ptr);
    name.vorname_ptr = strdup(student.name.vorname_ptr);

    student_heap->name = name;

	return student_heap;
} // kopiere_studenten_auf_heap


/**
 * Diese Vergleichsfunktion dient zum Vergleichen
 * von 2 Studentenobjekten, wobei die Adressen der
 * Adressen der beiden Studenten als Parameter
 * erwartet werden.
 * Als Vergleichskriterium dient die Matrikelnummer.
 * Parameter:
 *	v1_ptr - Adresse der Adresse des 1. Studenten-Objektes.
 *	v2_ptr - Adresse der Adresse des 2. Studenten-Objektes.
 * Rueckgabewert:
 *	neg. Wert --> 1. Student vor 2. Student einzusortieren.
 *	0 --> beide Studenten gleich.
 *	pos. Wert --> 1. Student nach 2. Student einzusortieren.
 */
int vgl_fkt_zeiger_matrikel_nr(const void*v1_ptr, const void*v2_ptr)
{
	// Aufgabe 1.11 (1/2)
	//    ... Ihr Quelltext!!! ...

    //Überprüfung auf NULL pointer
    if(v1_ptr == NULL || v2_ptr == NULL) {
        perror("Ungueltige Parameter fuer funktion vgl_fkt_zeiger_matrikel_nr");
        exit(EXIT_FAILURE);
    }

    //Umcasten auf studenten_typ für bessere handhabung
    struct studenten_typ *stud1_ptr = *((struct studenten_typ**)v1_ptr);
    struct studenten_typ *stud2_ptr = *((struct studenten_typ**)v2_ptr);

    //Uns interessiert hier nur die matr_nr und deshalb direktes ansprechen schneller
    int matr1 = stud1_ptr->matrikel_nr;
    int matr2 = stud2_ptr->matrikel_nr;

    //Sparen uns if Schleife für Vergleich, da auf Assembler Ebene sowieso Sub für Flag setzen
    //des Vergleichs ausgeführt wird. Performance optimierung
    return matr1 - matr2;
} // vgl_fkt_zeiger_matrikel_nr

/**
 * Dient dem freigeben des reservierten Heap Speichers zum Schluss des Programms
 * Dieser ist speziell auf das definierte Studenten struct und seine member ausgelegt
 *
 * Parameter:
 *	stud_arr : Erwartet das zu löschende Studenten Array
 *	n_members : Erwartet die Anzahl der Elemente des Arrays
 * Rueckgabewert:
 *	Kein Rückgabewert
 */
void free_student_arr(struct studenten_typ **stud_arr, int n_members) {
    if(n_members != 0) {
        for(int i = 0; i < n_members; i++) {
            struct studenten_typ *student = stud_arr[i];
            free(student->name.vorname_ptr);
            free(student->name.nachname_ptr);
            free(student);
        }
    }
}//free_student_arr

