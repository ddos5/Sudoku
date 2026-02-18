#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

typedef struct Riesenie {
    char SID[20];
    char NarHry;
    char GID[20];
    char NarSut;
    char DatHry[20];
    int Trvanie;
    struct Riesenie *next;
} RIESENIE;
typedef struct Hrac {
    char PID[20];
    char Identita[100];
    char Krajina[50];
    int RokNar;
    RIESENIE *zoznam_rieseni;
    struct Hrac *next;
} HRAC;

void funkcia_v1(FILE **p_sudoku, FILE **p_hraci, FILE **p_rieseni) {
    char hraci_str[500];
    char temphraci[500];
    char *pid, *meno, *krajina, *rok;
    char gamestr[100];
    int game_count;
    char gamestrcopy[500];
    char *pid_rieseni;
    /*logika pre otvorenia vstekych suborov*/
    if (*p_sudoku == NULL) {
        *p_sudoku = fopen("Sudoku.txt", "r");
        if (*p_sudoku == NULL) {
            printf("V1: Neotvorene txt subory.\n");
        }
    }
    if (*p_hraci == NULL) {
        *p_hraci = fopen("RegisterHracov.txt", "r");
        if (*p_hraci == NULL) {
            printf("V1: Neotvorene txt subory.\n");
        }
    }
    if (*p_rieseni == NULL) {
        *p_rieseni = fopen("RegisterRieseni.txt", "r");
        if (*p_rieseni == NULL) {
            printf("V1: Neotvorene txt subory.\n");
        }
    }

    if (*p_sudoku == NULL || *p_hraci == NULL || *p_rieseni == NULL) {
        if (*p_sudoku != NULL) {
            fclose(*p_sudoku);
        }
        if (*p_hraci != NULL) {
            fclose(*p_hraci);
        }
        if (*p_rieseni != NULL) {
            fclose(*p_rieseni);
        }
        *p_rieseni = NULL;
        *p_hraci = NULL;
        *p_sudoku = NULL;
        return;
    }

    /*citame subor ester raz ked on bude na EOF aby compiler mohol vytlacit inu informaciu*/
    rewind(*p_hraci);

    while (fgets(hraci_str, sizeof(hraci_str), *p_hraci) != NULL) {
        hraci_str[strcspn(hraci_str, "\n")] = 0;
        /*robime copy retazca hraci_str do temphraci aby pracovat z nim*/
        strcpy(temphraci, hraci_str);
        /*funkcia strtok cita subor, a ak vidi # tak robi tam \0, a prvok NULL startuje z toho isteho miesta, kde bol #*/
        pid = strtok(temphraci, "#");
        meno = strtok(NULL, "#");
        krajina = strtok(NULL, "#");
        rok = strtok(NULL, "#");
        if (pid) {
            printf("Identifikator: %s\n", pid);
        }
        else {
            pid = "";
            printf("Identifikator: \n");
        }
        if (meno) {
            printf("Meno a prezvisko: %s\n", meno);
        }
        else {
            meno = "";
            printf("Meno a prezvisko: \n");
        }
        if (krajina) {
            printf("Krajina: %s\n", krajina);
        }
        else {
            krajina = "";
            printf("Krajina: \n");
        }
        if (rok) {
            printf("Rok: %s\n", rok);
        }
        else {
            rok = "";
            printf("Rok: \n");
        }
        printf("Vzorka:\n");

        /*overenie pre hry, cize mame 10 ihr alebo nie*/
        game_count = 0;
        /*este raz citame subor znova*/
        rewind(*p_rieseni);

        while (fgets(gamestr, sizeof(gamestr), *p_rieseni) != NULL && game_count < 10) {
            gamestr[strcspn(gamestr, "\n")] = 0;
            if (pid != NULL) {
                strcpy(gamestrcopy, gamestr);
                strtok(gamestrcopy, "#");
                pid_rieseni = strtok(NULL, "#");

                /*ak existuje pid_rieseni, cize nas PID, a ak on je rovnaky ak v subore hracov vypisime vsetku informaciu*/
                if (pid_rieseni != NULL && strcmp(pid_rieseni, pid) == 0){
                    printf("\t%s\n", gamestr);
                    /*pridame game count aby pozret, ci ma tento hrac 10 hier*/
                    game_count++;
                }
            }
        }
        printf("\n");
    }
}
/*robi to iste ako funkcia v1, ale z dynamickych poli*/
void funkcia_v2(
    char(*pole_hracov_pid)[10], char(*pole_hracov_meno)[100], char(*pole_hracov_krajina)[50],
    char(*pole_hracov_rok)[5],
    char(*pole_rieseni_gid)[10], char(*pole_rieseni_pid)[10], char(*pole_rieseni_sid)[10],
    char(*pole_rieseni_data)[50], char(*pole_rieseni_min)[50], char(*pole_rieseni_sek)[50],
    int pocet_rieseni, int pocet_hracov) {

    int i, j;
    char *pid, *meno, *krajina, *rok;
    int game_count;
    char *gid_r, *pid_r, *sid_r, *data_r, *min_r, *sek_r;
    char narocnost_sutaze, narocnost_hry;
    int minuty, secundy, celkom;


    if (pocet_hracov == 0 || pole_hracov_pid == NULL) {
        printf("V2: Nenaplnene polia.\n");
        return;
    }
    /*z funkcii n pridavame udaje do pid meno atd*/
    for (i = 0; i < pocet_hracov; i++) {
        pid = pole_hracov_pid[i];
        meno = pole_hracov_meno[i];
        krajina = pole_hracov_krajina[i];
        rok = pole_hracov_rok[i];
        /*vypisujeme tuto informaciu v cmd*/
        printf("PID: %s / %s / %s\n", pid, rok, krajina);
        printf("Identita: %s\n", meno);
        printf("Vysledok:\n");
        /*robime to iste ale viac rozsirene*/
        game_count = 0;
        for (j = 0; j < pocet_rieseni; j++) {
            if (strcmp(pole_rieseni_pid[j], pid) == 0 && game_count < 10) {
                gid_r = pole_rieseni_gid[j];
                pid_r = pole_rieseni_pid[j];
                sid_r = pole_rieseni_sid[j];
                data_r = pole_rieseni_data[j];
                min_r = pole_rieseni_min[j];
                sek_r = pole_rieseni_sek[j];

                narocnost_sutaze = ' ';
                if (strlen(gid_r) > 3) {
                    narocnost_sutaze = gid_r[3];
                }
                narocnost_hry = ' ';
                if (strlen(sid_r) > 3) {
                    narocnost_hry = sid_r[3];
                }
                /*prevod string do inta cez funkciu atoi*/
                minuty = atoi(min_r);
                secundy = atoi(sek_r);
                celkom = (minuty * 60) + secundy;
                printf("\t%s / %s / %s / %s / %c / %c / %d\n", gid_r, pid_r, sid_r, data_r, narocnost_sutaze, narocnost_hry, celkom);
                game_count++;
            }
        }
        printf("\n");
    }
}
/*funkcia na vypis spajaneho zaznamu*/
void funkcia_v3(HRAC* hlava_zoznamu) {
    HRAC* aktualny_hrac = hlava_zoznamu;
    RIESENIE* aktualne_riesenie;

    if (hlava_zoznamu == NULL) {
        printf("V3: Nenaplneny spajany zoznam.\n");
        return;
    }
    /*vypiseme kazdeho hraca*/
    while (aktualny_hrac != NULL) {
        printf("PID: %s\n", aktualny_hrac->PID);
        printf("Identita: %s\n", aktualny_hrac->Identita);
        printf("Krajina: %s\n", aktualny_hrac->Krajina);
        printf("RokNar: %d\n", aktualny_hrac->RokNar);
        printf("Vysledky:\n");

        /*potom ideme na cyklus pre riesenia*/
        aktualne_riesenie = aktualny_hrac->zoznam_rieseni;
        while (aktualne_riesenie != NULL) {
            printf(" %s / %c / %s / %c / %s / %d\n", aktualne_riesenie->SID, aktualne_riesenie->NarHry, aktualne_riesenie->GID,
                aktualne_riesenie->NarSut, aktualne_riesenie->DatHry, aktualne_riesenie->Trvanie);
            aktualne_riesenie = aktualne_riesenie->next;
        }
        printf("\n");
        /*ideme na nasledujuceho hraca*/
        aktualny_hrac = aktualny_hrac->next;
    }
}

void funkcia_v(FILE **p_sudoku,FILE **p_hraci, FILE **p_rieseni,
    char(*pole_hracov_pid)[10], char(*pole_hracov_meno)[100], char(*pole_hracov_krajina)[50],
    char(*pole_hracov_rok)[5],
    char(*pole_rieseni_gid)[10], char(*pole_rieseni_pid)[10], char(*pole_rieseni_sid)[10],
    char(*pole_rieseni_data)[50], char(*pole_rieseni_min)[50], char(*pole_rieseni_sek)[50],
    int pocet_rieseni, int pocet_hracov, HRAC* hlava_zoznamu) {
    int volba;
    int bufferclean;

    /*overenie ci je to cislo alebo nie*/
    if (scanf("%d", &volba) == 1) {
        while ((bufferclean = getchar()) != '\n');
        if (volba == 1) {
            /*prechod na funkciu v1*/
            funkcia_v1(p_sudoku, p_hraci, p_rieseni);
        }
        else if (volba == 2) {
            /*volame funkciu v2*/
            funkcia_v2(
                pole_hracov_pid, pole_hracov_meno, pole_hracov_krajina,
                pole_hracov_rok,
                pole_rieseni_gid, pole_rieseni_pid, pole_rieseni_sid,
                pole_rieseni_data, pole_rieseni_min, pole_rieseni_sek,
                pocet_rieseni, pocet_hracov);
        }
        /*volame funkciu v3*/
        else if (volba == 3) {
            funkcia_v3(hlava_zoznamu);
        }
        else {
            printf("V: Nespravna volba vypisu.\n");
        }
    }
}

void funkcia_h(FILE **p_rieseni) {
    /*pridame vsetky volby*/
    char idhry[20];
    int i;
    char hracy[100];
    char hracytemp[100];
    char *sid_h;

    FILE *vystuph;
    /*ak spustime program s prikazu h, aj ne bude otvoreny subor riesen, tak budeme mat' taky vysledok*/
    if (*p_rieseni == NULL) {
        printf("H: Neotvoreny txt subor.\n");
        return;
    }
    /*zrusime \n, aby dlzka bola iba string, bez niekych inych charov*/
    if (fgets(idhry, sizeof(idhry), stdin) != NULL) {
        i = 0;
        while (idhry[i] != '\0') {
            if (idhry[i] == '\n') {
                idhry[i] = '\0';
                break;
            }
            i++;
        }
        /*overime, ci dlzka je 8 charov, na zaciatku ma pismena SID, a ci su pismena velky*/
        if (strlen(idhry) != 8 || strncmp(idhry, "SID", 3) != 0 || !isupper((unsigned char)idhry[3])) {
            /*ak ne overili sme, tak mame printf nespravny vstup string aj potom vyjdeme z funkcii h*/
            printf("H: Nespravny vstup.\n");
            return;
        }
        /*overime ze od 4 do 8 miesta mame cisla cez funkciu isdigit*/
        for (i = 4; i < 8; i++) {
            if (!isdigit((unsigned char)idhry[i])) {
                printf("H: Nespravny vstup.\n");
                return;
            }
        }
    }
    /*overime, ak vobec ne napisali pismena, a napisali sme medzeru*/
    else {
        printf("H: Nespravny vstup.\n");
        return;
    }
    /*otvorime subor pre "writing" v ktory zapiseme sumar*/
    vystuph = fopen("Vystup_H.txt", "w");
    if (vystuph == NULL) {
        printf("H: Neotvoreny txt subor.\n");
        return;
    }
    /*ideme na zaciatok suboru, aby najst novy riesenia*/
    rewind(*p_rieseni);
    /*citame 1 string z suboru, ked sa nedostaneme do \0   */
    while (fgets(hracy, sizeof(hracy), *p_rieseni) != NULL) {
        strcpy(hracytemp, hracy);
        strtok(hracytemp, "#");
        strtok(NULL, "#");
        sid_h = strtok(NULL, "#");
        /*ak v subore mame SID...... tak funguje program d'alej, ak nie, tak cykl while ide na nasledujuci string*/
        if (sid_h != NULL) {
            /*ak idhry ktory user napisal je tak isty ak sid_h z suboru vytlacime v subor vystupu*/
            if (strcmp(sid_h, idhry) == 0) {
                fprintf(vystuph, "%s", hracy);
            }
        }
    }
    /*zatvorime subor*/
    fclose(vystuph);
    printf("H: Uspesne vytvoreny sumar.\n");
}
/*funkcia n tvori dynamicky polia*/
void funkcia_n(FILE **p_sudoku, FILE **p_hraci, FILE **p_rieseni,
    char(**p_pole_hracov_pid)[10], char(**p_pole_hracov_meno)[100], char(**p_pole_hracov_krajina)[50],
    char(**p_pole_hracov_rok)[5],

    char(**p_pole_rieseni_gid)[10], char(**p_pole_rieseni_pid)[10], char(**p_pole_rieseni_sid)[10],
    char(**p_pole_rieseni_data)[50], char(**p_pole_rieseni_min)[50], char(**p_pole_rieseni_sek)[50],

    char(**p_pole_sudoku_id)[20],
    char(**p_pole_sudoku_gid)[1000],

    int *p_pocet_hracov, int *p_pocet_riesen, int *p_pocet_sudoku
    ) {
    char buffer_n[4096];
    int count_hraci = 0, count_rieseni = 0, count_sudoku = 0;
    int i;
    char temp_n[4096];
    char *pid, *meno, *krajina, *rok;
    char buffer_riad1[1000];
    char temp1[4096];
    char *id;
    char *gid;
    char *gid_r, *pid_r, *sid_r, *data_r, *min_r, *sek_r;
    /*ak subory neotvotvorene tak pokracujeme v nacitani*/
    if (*p_sudoku == NULL || *p_hraci == NULL || *p_rieseni == NULL){
        printf("N: Neotvoreny subory.\n");
        return;
    }
    /*ak pred tym sme mali uz funkciu n musime deallokovat pamat*/
    if (*p_pole_hracov_pid != NULL) {
        free(*p_pole_hracov_pid);
    }
    if (*p_pole_hracov_meno != NULL) {
        free(*p_pole_hracov_meno);
    }
    if (*p_pole_hracov_krajina != NULL) {
        free(*p_pole_hracov_krajina);
    }
    if (*p_pole_hracov_rok != NULL) {
        free(*p_pole_hracov_rok);
    }
    if (*p_pole_rieseni_gid != NULL) {
        free(*p_pole_rieseni_gid);
    }
    if (*p_pole_rieseni_pid != NULL) {
        free(*p_pole_rieseni_pid);
    }
    if (*p_pole_rieseni_sid != NULL) {
        free(*p_pole_rieseni_sid);
    }
    if (*p_pole_rieseni_data != NULL) {
        free(*p_pole_rieseni_data);
    }
    if (*p_pole_rieseni_min != NULL) {
        free(*p_pole_rieseni_min);
    }
    if (*p_pole_rieseni_sek != NULL) {
        free(*p_pole_rieseni_sek);
    }
    if (*p_pole_sudoku_gid != NULL) {
        free(*p_pole_sudoku_gid);
    }
    if (*p_pole_sudoku_id != NULL) {
        free(*p_pole_sudoku_id);
    }

    /*pridavame NULL do pointera aby nemali nejaky seg fault*/
    *p_pole_hracov_pid = NULL;
    *p_pole_hracov_meno = NULL;
    *p_pole_hracov_krajina = NULL;
    *p_pole_hracov_rok = NULL;

    *p_pole_rieseni_gid = NULL;
    *p_pole_rieseni_pid = NULL;
    *p_pole_rieseni_sid = NULL;
    *p_pole_rieseni_data = NULL;
    *p_pole_rieseni_min = NULL;
    *p_pole_rieseni_sek = NULL;

    *p_pole_sudoku_gid = NULL;
    *p_pole_sudoku_id = NULL;

    *p_pocet_hracov = 0;
    *p_pocet_riesen = 0;
    *p_pocet_sudoku = 0;

    /*ideme na zaciatok subora ak uz predtym sme citali ho*/
    rewind(*p_hraci);
    /*pocitame hracov*/
    while (fgets(buffer_n, sizeof(buffer_n), *p_hraci) != NULL) {
        count_hraci++;
    }
    /*pocitame sudoku*/
    rewind(*p_sudoku);
    while (fgets(buffer_n, sizeof(buffer_n), *p_sudoku) != NULL) {
        count_sudoku++;
    }
    /*pocitame rieseni*/
    rewind(*p_rieseni);
    while (fgets(buffer_n, sizeof(buffer_n), *p_rieseni) != NULL) {
        count_rieseni++;
    }
    /*ak mame hracov v subore tak allokujeme pamat*/
    if (count_hraci > 0) {
        *p_pole_hracov_pid = malloc(count_hraci * sizeof(**p_pole_hracov_pid));
        *p_pole_hracov_meno = malloc(count_hraci * sizeof(**p_pole_hracov_meno));
        *p_pole_hracov_krajina = malloc(count_hraci * sizeof(**p_pole_hracov_krajina));
        *p_pole_hracov_rok = malloc(count_hraci * sizeof(**p_pole_hracov_rok));
        *p_pocet_hracov = count_hraci;
    }
    /*ak mame rieseni v subore tak allokujeme pamat*/
    if (count_rieseni > 0) {
        *p_pole_rieseni_gid = malloc(count_rieseni * sizeof(**p_pole_rieseni_gid));
        *p_pole_rieseni_pid = malloc(count_rieseni * sizeof(**p_pole_rieseni_pid));
        *p_pole_rieseni_sid = malloc(count_rieseni * sizeof(**p_pole_rieseni_sid));
        *p_pole_rieseni_data = malloc(count_rieseni * sizeof(**p_pole_rieseni_data));
        *p_pole_rieseni_min = malloc(count_rieseni * sizeof(**p_pole_rieseni_min));
        *p_pole_rieseni_sek = malloc(count_rieseni * sizeof(**p_pole_rieseni_sek));
        *p_pocet_riesen = count_rieseni;
    }
    /*ak mame sudoku v subore tak allokujeme pamat*/
    if (count_sudoku > 0) {
        *p_pole_sudoku_id = malloc(count_sudoku * sizeof(**p_pole_sudoku_id));
        *p_pole_sudoku_gid = malloc(count_sudoku * sizeof(**p_pole_sudoku_gid));
        *p_pocet_sudoku = count_sudoku;
    }
    i = 0;
    rewind(*p_hraci);
    /*citame subor*/
    while (fgets(buffer_n, sizeof(buffer_n), *p_hraci) != NULL && i < *p_pocet_hracov) {
        strcpy(temp_n, buffer_n);
        /*pridame kazdy parametr napriklad pid meno atd do premmenych*/
        pid = strtok(temp_n, "#\n");
        meno = strtok(NULL, "#\n");
        krajina = strtok(NULL, "#\n");
        rok = strtok(NULL, "#\n");
        /*ak podarilo pridat pid z suboru do char *pid tak kopirujem pid do naseho dynamyckeho polia atd*/
        if (pid) {
            /*pouzivame strncpy aby sme nemali heap corruption*/
            strncpy((*p_pole_hracov_pid)[i], pid, 9);
            (*p_pole_hracov_pid)[i][9] = '\0';
        }
        else {
            (*p_pole_hracov_pid)[i][0] = '\0';
        }
        if (meno) {
            strncpy((*p_pole_hracov_meno)[i], meno, 99);
            (*p_pole_hracov_meno)[i][99] = '\0';
        }
        else {
            (*p_pole_hracov_meno)[i][0] = '\0';
        }
        if (krajina) {
            strncpy((*p_pole_hracov_krajina)[i], krajina, 49);
            (*p_pole_hracov_krajina)[i][49] = '\0';
        }
        else {
            (*p_pole_hracov_krajina)[i][0] = '\0';
        }
        if (rok) {
            strncpy((*p_pole_hracov_rok)[i], rok, 4);
            (*p_pole_hracov_rok)[i][4] = '\0';
        }
        else {
            (*p_pole_hracov_rok)[i][0] = '\0';
        }
        i++;
    }


    /*dalej nacitame udaje z sudoku.txt*/
    rewind(*p_sudoku);
    for (i = 0; i < *p_pocet_sudoku; i++){
        if (fgets(buffer_riad1, sizeof(buffer_riad1), *p_sudoku) == NULL) {
            break;
        }
        strcpy(temp1, buffer_riad1);
        /*pridame id hry aj cele sudoku do premmenych id aj gid*/
        id = strtok(temp1, "#");
        gid = strtok(NULL, "\n");
        /*ak podarilo nacitat udaje tak pridame ich do dynamickych poli*/
        if (id) {
            /*tiez kopiruejem*/
            strcpy((*p_pole_sudoku_id)[i], id);
        }
        else {
            (*p_pole_sudoku_id)[i][0] = '\0';
        }
        if (gid != NULL) {
            strcpy((*p_pole_sudoku_gid)[i], gid);
        }
        else {
            (*p_pole_sudoku_gid[i][0] = '\0');
        }
    }

    i = 0;
    rewind(*p_rieseni);
    /*teraz z suboru riesen nacitame udaje*/
    while (fgets(buffer_n, sizeof(buffer_n), *p_rieseni) != NULL && i < *p_pocet_riesen) {
        strcpy(temp_n, buffer_n);
        /*pridame ich do premennych napriklad gid z suboru do char *gid atd*/
        gid_r = strtok(temp_n, "#");
        pid_r = strtok(NULL, "#");
        sid_r = strtok(NULL, "#");
        data_r = strtok(NULL, "#");
        min_r = strtok(NULL, "#");
        sek_r = strtok(NULL, "#\n");
        if (gid_r) {
            /*ak podarilo skopirovat pridame a na koniec pridame \0*/
            strncpy((*p_pole_rieseni_gid)[i], gid_r, 9);
            (*p_pole_rieseni_gid)[i][9] = '\0';
        }
        else {
            /*ak nepodarilo tak pridame na vsetky string \0*/
            (*p_pole_rieseni_gid)[i][0] = '\0';
        }
        if (pid_r) {
            strncpy((*p_pole_rieseni_pid)[i], pid_r, 9);
            (*p_pole_rieseni_pid)[i][9] = '\0';
        }
        else {
            (*p_pole_rieseni_pid)[i][0] = '\0';
        }
        if (sid_r) {
            strncpy((*p_pole_rieseni_sid)[i], sid_r, 9);
            (*p_pole_rieseni_sid)[i][9] = '\0';
        }
        else {
            (*p_pole_rieseni_sid)[i][0] = '\0';
        }
        if (data_r) {
            strncpy((*p_pole_rieseni_data)[i], data_r, 49);
            (*p_pole_rieseni_data)[i][49] = '\0';
        }
        else {
            (*p_pole_rieseni_data)[i][0] = '\0';
        }
        if (min_r) {
            strncpy((*p_pole_rieseni_min)[i], min_r, 49);
            (*p_pole_rieseni_min)[i][49] = '\0';
        }
        else {
            (*p_pole_rieseni_min)[i][0] = '\0';
        }
        if (sek_r) {
            strncpy((*p_pole_rieseni_sek)[i], sek_r, 49);
            (*p_pole_rieseni_sek)[i][49] = '\0';
        }
        else {
            (*p_pole_rieseni_sek)[i][0] = '\0';
        }
        i++;
    }
}
/*funkcia q pridava novu informaciu do dynamickych poli*/
void funkcia_q(char(**p_pole_rieseni_gid)[10], char(**p_pole_rieseni_pid)[10], char(**p_pole_rieseni_sid)[10],
    char(**p_pole_rieseni_data)[50], char(**p_pole_rieseni_min)[50], char(**p_pole_rieseni_sek)[50],
    int *p_pocet_riesen) {

    int Y;
    char buffer_y[100];
    char gid_str[10];
    char pid_str[10];
    char sid_str[10];
    long int data_q;
    int min_q;
    int sek_q;
    char data_str[50];
    char min_str[50];
    char sek_str[50];
    int i;
    int validgid, validpid, validsid, validdata;
    int mesiac, den;
    int count, novy_count, pos_index;

    /*ak nevytvorene dynamicke polia tak vratime sa*/
    if (*p_pole_rieseni_gid == NULL) {
        printf("Q: Polia nie su vytvorene.\n");
        return;
    }
    /*nacitame na ake miesto pridame nove udaje*/
    if (fgets(buffer_y, sizeof(buffer_y), stdin ) == NULL) {
        return;
    }
    /*ak napiseme nie cislo tak budeme mat chybu*/
    if (sscanf(buffer_y, "%d", &Y) != 1) {
        printf("Q: Nespravny vstup pre Y(ne cislo).\n");
        return;
    }
    /*robime tento cykl ked nenacitame spravne udaje*/
    while (1) {
        if (fgets(buffer_y, sizeof(buffer_y), stdin) == NULL) {
            return;
        }
        i = 0;
        /*ak nacitame retazec vymazeme \n na konci*/
        while (buffer_y[i] != '\0') {
            if (buffer_y[i] == '\n') {
                buffer_y[i] = '\0';
                break;
            }
            i++;
        }
        /*ovrujeme ze gid je spravny*/
        validgid = 1;
        /*dlzka musi byt 7*/
        if (strlen(buffer_y) != 7) {
            validgid = 0;
        }
        /*prvy symboly su GID*/
        else if (strncmp(buffer_y, "GID", 3) != 0) {
            validgid = 0;
        }
        /*musi byt nejake pismeno*/
        else if (!isalpha((unsigned char)buffer_y[3])) {
            validgid = 0;
        }
        /*ak je velke pismeno tak nepouzivame tento prikaz*/
        else if (isupper((unsigned char)buffer_y[3])) {
            validgid = 0;
        }
        else {
            for (i = 4; i < 7; i++) {
                /*ak nie su cisla tak zrusim nacitane*/
                if (!isdigit((unsigned char)buffer_y[i])) {
                    validgid = 0;
                    break;
                }
            }
        }
        /*ak vsetko je v pohode tak pridame do premmenej*/
        if (validgid) {
        strcpy(gid_str, buffer_y);
        break;
        }
        /*ak nie je spravne tak pokracujeme v nacitavani este raz aj viac*/
        printf("Q: nespravny format vstupu, zadaj znova: ");
    }

    while (1) {
        if (fgets(buffer_y, sizeof(buffer_y), stdin) == NULL) {
            return;
        }
        i = 0;
        /*ak nacitame retazec vymazeme \n na konci*/
        while (buffer_y[i] != '\0') {
            if (buffer_y[i] == '\n') {
                buffer_y[i] = '\0';
                break;
            }
            i++;
        }
        validpid = 1;
        /*retazec musi byt 9*/
        if (strlen(buffer_y) != 9) {
            validpid = 0;
        }
        /*prvy 3 prvky musia byt PID*/
        else if (strncmp(buffer_y, "PID", 3) != 0) {
            validpid = 0;
        }
        /*dalej musime mat pismeno*/
        else if (!isalpha((unsigned char)buffer_y[3])) {
            validpid = 0;
        }
        else {
            for (i = 4; i <= 8; i++) {
                /*dalej musime mat cisla*/
                if (!isdigit((unsigned char)buffer_y[i])) {
                    validpid = 0;
                    break;
                }
            }
        }
        /*ak podarilo urobit vsetko pridame nas vstup do premennej*/
        if (validpid) {
            strcpy(pid_str, buffer_y);
            break;
        }
        /*ak nie tak pokracujeme*/
        printf("Q: nespravny format vstupu, zadaj znova: ");
    }

    while (1) {
        if (fgets(buffer_y, sizeof(buffer_y), stdin) == NULL) {
            return;
        }
        i = 0;
        /*ak nacitame retazec vymazeme \n na konci*/
        while (buffer_y[i] != '\0') {
            if (buffer_y[i] == '\n') {
                buffer_y[i] = '\0';
                break;
            }
            i++;
        }
        validsid = 1;
        /*dlzka musi byt 8*/
        if (strlen(buffer_y) != 8) {
            validsid = 0;
        }
        /*prvy 3 prvky musia byt SID*/
        else if (strncmp(buffer_y, "SID", 3) != 0) {
            validsid = 0;
        }
        /*prve pismeno musi byt male pismeno*/
        else if (!isupper((unsigned char)buffer_y[3])) {
            validsid = 0;
        }
        else {
            for (i = 4; i <= 7; i++) {
                /*musia byt cisla*/
                if (!isdigit((unsigned char)buffer_y[i])) {
                    validsid = 0;
                    break;
                }
            }
        }
        /*ak podarilo nacitat pridame*/
        if (validsid) {
            strcpy(sid_str, buffer_y);
            break;
        }
        /*ak nie tak nacitame dalej*/
        printf("Q: nespravny format vstupu, zadaj znova: ");
    }

    while (1) {
        if (fgets(buffer_y, sizeof(buffer_y), stdin) == NULL) {
            return;
        }
        /*teraz vsetko iste pre data*/
        if (sscanf(buffer_y, "%ld %d %d", &data_q, &min_q, &sek_q) == 3) {
            validdata = 1;
            mesiac = (data_q % 10000) / 100;
            den = data_q % 100;
            if (mesiac < 1 || mesiac > 12) {
                validdata = 0;
            }
            else if (den < 1 || den > 31) {
                validdata = 0;
            }
            else if (min_q < 0) {
                validdata = 0;
            }
            else if (sek_q < 0 || sek_q > 59) {
                validdata = 0;
            }
            if (validdata) {
                sprintf(data_str, "%ld", data_q);
                sprintf(min_str, "%d", min_q);
                sprintf(sek_str, "%d", sek_q);
                break;
            }
        }
        printf("Q: nespravny format vstupu, zadaj znova: ");
    }
    count = *p_pocet_riesen;
    /*robime novy count aby realokovat pamat*/
    novy_count = count + 1;
    /*ak budeme mat nespravny vsutp Y = -1*/
    pos_index = (Y - 1 < 0) ? 0 : Y - 1;
    /*ak nase cislo je vacsie tak bude na konci*/
    if (pos_index > count) {
        pos_index = count;
    }
    /*realokujeme pamat*/
    *p_pole_rieseni_gid = realloc(*p_pole_rieseni_gid, novy_count * sizeof(**p_pole_rieseni_gid));
    *p_pole_rieseni_pid = realloc(*p_pole_rieseni_pid, novy_count * sizeof(**p_pole_rieseni_pid));
    *p_pole_rieseni_sid = realloc(*p_pole_rieseni_sid, novy_count * sizeof(**p_pole_rieseni_sid));
    *p_pole_rieseni_data = realloc(*p_pole_rieseni_data, novy_count * sizeof(**p_pole_rieseni_data));
    *p_pole_rieseni_min = realloc(*p_pole_rieseni_min, novy_count * sizeof(**p_pole_rieseni_min));
    *p_pole_rieseni_sek = realloc(*p_pole_rieseni_sek, novy_count * sizeof(**p_pole_rieseni_sek));
    /*ak ne alokovalo tak chyba*/
    if (*p_pole_rieseni_gid == NULL) {
        printf("Q: Chyba alokacie pamate.\n");
        return;
    }
    if (pos_index < count) {
        /*menime miestami retazci, o jeden*/
        for (i = count; i > pos_index; i--) {
            /*posuvame na novu volnu realokovanu bunku*/
            strcpy((*p_pole_rieseni_gid)[i], (*p_pole_rieseni_gid)[i-1]);
            strcpy((*p_pole_rieseni_pid)[i], (*p_pole_rieseni_pid)[i-1]);
            strcpy((*p_pole_rieseni_sid)[i], (*p_pole_rieseni_sid)[i-1]);
            strcpy((*p_pole_rieseni_data)[i], (*p_pole_rieseni_data)[i-1]);
            strcpy((*p_pole_rieseni_min)[i], (*p_pole_rieseni_min)[i-1]);
            strcpy((*p_pole_rieseni_sek)[i], (*p_pole_rieseni_sek)[i-1]);
        }
    }
    /*kopirujeme na potrebny index*/
    strcpy((*p_pole_rieseni_gid)[pos_index], gid_str);
    strcpy((*p_pole_rieseni_pid)[pos_index], pid_str);
    strcpy((*p_pole_rieseni_sid)[pos_index], sid_str);
    strcpy((*p_pole_rieseni_data)[pos_index], data_str);
    strcpy((*p_pole_rieseni_min)[pos_index], min_str);
    strcpy((*p_pole_rieseni_sek)[pos_index], sek_str);
    /*aj piseme novy count v nas main*/
    *p_pocet_riesen = novy_count;
}

void funkcia_w(char(**p_pole_rieseni_gid)[10], char(**p_pole_rieseni_pid)[10], char(**p_pole_rieseni_sid)[10],
    char(**p_pole_rieseni_data)[50], char(**p_pole_rieseni_min)[50], char(**p_pole_rieseni_sek)[50],
    int *p_pocet_riesen) {
    char buffer_w[100];
    char pid_vymazat[20];
    int i,j;
    int count_riesen;
    int vymazane_count;
    int dobrerieseni_count;
    int novy_count;
    if (*p_pole_rieseni_gid == NULL) {
        /*ak nie je allokovana pamat*/
        printf("W: Polia nie su vytvorene.\n");
        return;
    }
    /*ak nenacita tak vyjdeme z funkcie*/
    if (fgets(buffer_w, sizeof(buffer_w), stdin) == NULL) {
        return;
    }
    i = 0;
    /*ak nacitame retazec vymazeme \n na konci*/
    while (buffer_w[i] != '\0') {
        if (buffer_w[i] == '\n') {
            buffer_w[i] = '\0';
            break;
        }
        i++;
    }
    /*kopirujeme udaje z bufferu do premennej*/
    strncpy(pid_vymazat, buffer_w, 19);
    pid_vymazat[19] = '\0';

    count_riesen = *p_pocet_riesen;
    /*count kolko sme vymazali*/
    vymazane_count = 0;
    dobrerieseni_count = 0;

    for (j = 0; j < count_riesen; j++) {
        /*ak nas retiazec je taky isty napiseme ze vymazali ho*/
        if (strcmp((*p_pole_rieseni_pid)[j], pid_vymazat) == 0) {
            vymazane_count++;
        }
        else {
            if (j != dobrerieseni_count) {
                /*ideme odzadu a posuvam vsetko spat*/
                strcpy((*p_pole_rieseni_gid)[dobrerieseni_count], (*p_pole_rieseni_gid)[j]);
                strcpy((*p_pole_rieseni_pid)[dobrerieseni_count], (*p_pole_rieseni_pid)[j]);
                strcpy((*p_pole_rieseni_sid)[dobrerieseni_count], (*p_pole_rieseni_sid)[j]);
                strcpy((*p_pole_rieseni_data)[dobrerieseni_count], (*p_pole_rieseni_data)[j]);
                strcpy((*p_pole_rieseni_min)[dobrerieseni_count], (*p_pole_rieseni_min)[j]);
                strcpy((*p_pole_rieseni_sek)[dobrerieseni_count], (*p_pole_rieseni_sek)[j]);
            }
            dobrerieseni_count++;
        }
    }
    if (vymazane_count > 0) {
        /*robime novy count napriklad count-1*/
        novy_count = count_riesen - vymazane_count;
        if (novy_count == 0) {
            /*ak vymazame vsetko tak zrusime allokaciju*/
            free(*p_pole_rieseni_gid);
            *p_pole_rieseni_gid = NULL;
            free(*p_pole_rieseni_pid);
            *p_pole_rieseni_pid = NULL;
            free(*p_pole_rieseni_sid);
            *p_pole_rieseni_sid = NULL;
            free(*p_pole_rieseni_data);
            *p_pole_rieseni_data = NULL;
            free(*p_pole_rieseni_min);
            *p_pole_rieseni_min = NULL;
            free(*p_pole_rieseni_sek);
            *p_pole_rieseni_sek = NULL;
        } else {
            /*znizime pamat pomocou reallocu*/
            *p_pole_rieseni_gid = realloc(*p_pole_rieseni_gid, novy_count * sizeof(**p_pole_rieseni_gid));
            *p_pole_rieseni_pid = realloc(*p_pole_rieseni_pid, novy_count * sizeof(**p_pole_rieseni_pid));
            *p_pole_rieseni_sid = realloc(*p_pole_rieseni_sid, novy_count * sizeof(**p_pole_rieseni_sid));
            *p_pole_rieseni_data = realloc(*p_pole_rieseni_data, novy_count * sizeof(**p_pole_rieseni_data));
            *p_pole_rieseni_min = realloc(*p_pole_rieseni_min, novy_count * sizeof(**p_pole_rieseni_min));
            *p_pole_rieseni_sek = realloc(*p_pole_rieseni_sek, novy_count * sizeof(**p_pole_rieseni_sek));
        }
        /*pridame novy count do mainu*/
        *p_pocet_riesen = novy_count;
    }
    /*vypisime kolko zaznamov podarilo vymazat*/
    printf("W; Vymazalo sa : %d zaznamov !\n", vymazane_count);
}

void funkcia_e(char (*p_pole_sudoku_id)[20], char (*p_pole_sudoku_gid)[1000],
    int pocet_sudoku) {

    char buffer_e[100];
    char sid_vstup[20];
    int X;
    char *sudoku_gid_hladanie;
    int vyhladat;
    int i, j, k;
    int br, bc, r, c;
    char sudoku_2d[9][9];
    int stlpcy[9];
    int n, temp;
    int real_row, real_col;
    char value;
    FILE *vystup_e;

    /*ak ne sa nevytvorili polia alebo mame prazny subor tak vyjdeme z funkcii */
    if (p_pole_sudoku_id == NULL || pocet_sudoku == 0) {
        printf("E: Polia nie su vytvorene.\n");
        return;
    }
    /*nacitame id hry aj hodnotu*/
    if (fgets(buffer_e, sizeof(buffer_e), stdin) == NULL) {
        return;
    }
    /*pridame tieto udaje do sidvstupu aj do premennej X*/
    if (sscanf(buffer_e, "%s %d", sid_vstup, &X) != 2) {
        printf("E: Nespravny vstup.\n");
        return;
    }
    /*ak X < 1 alebo X > 5 vyjdeme z funkcii*/
    if (X < 1 || X > 5) {
        printf("E: Nespravny vstup3.\n");
        return;
    }
    sudoku_gid_hladanie = NULL;
    vyhladat = 0;
    for (i = 0; i < pocet_sudoku; i++) {
        /*hladame nasu hru*/
        if (strcmp(p_pole_sudoku_id[i], sid_vstup) == 0) {
            sudoku_gid_hladanie = p_pole_sudoku_gid[i];
            vyhladat = 1;
            /*ak najdeme tak zastavime*/
            break;
        }
    }
    /*ak string nie je 81 char aj nenasli sme ho tar zrusime funkciu*/
    if (!vyhladat) {
        printf("E: Nespravny vstup4.\n");
        return;
    }
    /*vytvorime 2d pole*/
    k = 0;
    for (br = 0; br < 3; br++) {
        for (bc = 0; bc < 3; bc++) {
            for (r = 0; r < 3; r++) {
                for (c = 0; c < 3; c++) {
                    real_row = br * 3 + r;
                    real_col = bc * 3 + c;
                        sudoku_2d[real_row][real_col] = sudoku_gid_hladanie[k++];
                }
            }
        }
    }
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            stlpcy[j] = j;
        }
        for (j = 8; j > 0; j--) {
            n = rand() % (j+1);
            temp = stlpcy[j];
            stlpcy[j] = stlpcy[n];
            stlpcy[n] = temp;
        }
        for (j = 0; j < X; j++) {
            sudoku_2d[i][stlpcy[j]] = ' ';
        }
    }
    /*otvorime subor*/
    vystup_e = fopen("Vystup_E.txt", "w");
    if (vystup_e == NULL) {
        printf("E: Chyba pri vytavarani suboru.\n");
        return;
    }
    /*vypiseme hodnoty v subor*/
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            value = sudoku_2d[i][j];
                fprintf(vystup_e, "|%c", value);
        }
        fprintf(vystup_e, "|\n");
    }
    fclose(vystup_e);
}
/*funkcia ktora vytvora spajany zaznam*/
void funkcia_m(FILE **p_hraci, FILE **p_rieseni, HRAC **hlava_zoznamu) {
    char buffer[1000];
    char temp_buffer[1000];
    int pocet_zaznamov = 0;
    char *pomocka;
    HRAC *aktualny_hrac, *dalsi_hrac_temp;
    RIESENIE *aktualne_riesenie, *dalsie_riesenie_temp;
    char pid[20], meno[100], krajina[50];
    int rok;
    char gid_r[20], pid_r[20], sid_r[20], datum_r[20], min_r[10], sek_r[10];
    int minuty, sekundy;
    HRAC *novy_hrac, *posledny_hrac = NULL;
    HRAC *hladany_hrac;
    RIESENIE *nove_riesenie, *posledne_riesenie;

    if (*p_hraci == NULL|| *p_rieseni == NULL) {
        printf("M: Neotvoreny subor.\n");
        return;
    }
    if (*hlava_zoznamu != NULL) {
        aktualny_hrac = *hlava_zoznamu;
        while (aktualny_hrac!=NULL) {
            aktualne_riesenie = aktualny_hrac->zoznam_rieseni;
            while (aktualne_riesenie!=NULL) {
                dalsie_riesenie_temp = aktualne_riesenie->next;
                free(aktualne_riesenie);
                aktualne_riesenie = dalsie_riesenie_temp;
            }
            dalsi_hrac_temp = aktualny_hrac->next;
            free(aktualny_hrac);
            aktualny_hrac = dalsi_hrac_temp;
        }
        *hlava_zoznamu = NULL;
    }
    rewind(*p_hraci);
    /*citame subor z hracami*/
    while (fgets(buffer, sizeof(buffer), *p_hraci) != NULL) {
        /*kopirujem ich v temp buffer*/
        strcpy(temp_buffer, buffer);
        if (temp_buffer[strlen(temp_buffer) - 1] == '\n') {
            temp_buffer[strlen(temp_buffer) - 1] = '\0';
        }
        /*teraz musime rozdielit ich*/
        pomocka = strtok(temp_buffer, "#");
        if (pomocka) {
            strcpy(pid, pomocka);
        }
        else {
            strcpy(pid, "");
        }
        pomocka = strtok(NULL, "#");
        if (pomocka) {
            strcpy(meno, pomocka);
        }
        else {
            strcpy(meno, "");
        }
        pomocka = strtok(NULL, "#");
        if (pomocka) {
            strcpy(krajina, pomocka);
        }
        else {
            strcpy(krajina, "");
        }
        pomocka = strtok(NULL, "#\n");
        if (pomocka) {
            rok = atoi(pomocka);
        }
        else {
            rok = 0;
        }
        /*robime novy spajany zoznam, aj allokujeme pamat*/
        novy_hrac = (HRAC*)malloc(sizeof(HRAC));
        strcpy(novy_hrac->PID, pid);
        strcpy(novy_hrac->Identita, meno);
        strcpy(novy_hrac->Krajina, krajina);
        novy_hrac->RokNar = rok;
        novy_hrac->zoznam_rieseni = NULL;
        novy_hrac->next = NULL;
        /*ak hlava == NULL, nas novy block bude zaciatkom*/
        if (*hlava_zoznamu == NULL) {
            *hlava_zoznamu = novy_hrac;
        }
        /*ak nie, tak to bude nasa nasledujuca bunka*/
        else {
            posledny_hrac->next = novy_hrac;
        }
        /*pridame pocet zaznamov*/
        posledny_hrac = novy_hrac;
        pocet_zaznamov++;
    }
    /*citame subor z riesen*/
    rewind(*p_rieseni);
    while (fgets(buffer, sizeof(buffer), *p_rieseni)) {
        /*kopirujeme ich v temp buffer*/
        strcpy(temp_buffer, buffer);
        if (temp_buffer[strlen(temp_buffer) - 1] == '\n') {
            temp_buffer[strlen(temp_buffer) - 1] = '\0';
        }
        /*musim rozdielit to este raz*/
        pomocka = strtok(temp_buffer, "#");
        if (pomocka) {
            strcpy(gid_r, pomocka);
        }
        else {
            continue;
        }
        pomocka = strtok(NULL, "#");
        if (pomocka) {
            strcpy(pid_r, pomocka);
        }
        else {
            continue;
        }
        pomocka = strtok(NULL, "#");
        if (pomocka) {
            strcpy(sid_r, pomocka);
        }
        else {
            continue;
        }
        pomocka = strtok(NULL, "#");
        if (pomocka) {
            strcpy(datum_r, pomocka);
        }
        else {
            continue;
        }
        pomocka = strtok(NULL, "#");
        if (pomocka) {
            strcpy(min_r, pomocka);
        }
        else {
            continue;
        }
        pomocka = strtok(NULL, "#");
        if (pomocka) {
            strcpy(sek_r, pomocka);
        }
        else {
            continue;
        }
        /*hladame hraca aby pridat mu ho riesenie*/
        hladany_hrac = *hlava_zoznamu;
        while (hladany_hrac != NULL) {
            /*ak su iste tak robime nove riesnie*/
            if (strcmp(hladany_hrac->PID, pid_r) == 0) {
                nove_riesenie = (RIESENIE*)malloc(sizeof(RIESENIE));
                strcpy(nove_riesenie->SID, sid_r);
                strcpy(nove_riesenie->GID, gid_r);
                strcpy(nove_riesenie->DatHry, datum_r);
                if (strlen(sid_r) > 3){
                nove_riesenie->NarHry = sid_r[3];
                }
                if (strlen(gid_r) > 3){
                    nove_riesenie->NarSut = gid_r[3];
                }
                minuty = atoi(min_r);
                sekundy = atoi(sek_r);
                nove_riesenie->Trvanie = (minuty*60) + sekundy;
                /*aj zapiseme ze to je koniec nasho spajaneho zoznamu*/
                nove_riesenie->next = NULL;

                /*ak nema hrac zoznam riesen, pridame nove riesenie tam*/
                if (hladany_hrac->zoznam_rieseni == NULL) {
                    hladany_hrac->zoznam_rieseni = nove_riesenie;
                }
                else {
                    /*posledne riesenie teraz aktualne*/
                    posledne_riesenie = hladany_hrac->zoznam_rieseni;
                    /*potom pozerame aby ne mali sme este spajanych bunok*/
                    while (posledne_riesenie->next != NULL) {
                        posledne_riesenie = posledne_riesenie->next;
                    }
                    /*vtedy nasledujuca bunka je nase nove riesenie*/
                    posledne_riesenie->next = nove_riesenie;
                }
                break;
            }
            /*ideme na nasledujuceho ak nam ne podarilo*/
            hladany_hrac = hladany_hrac->next;
        }
    }
    printf("M: Nacitalo sa %d zaznamov.\n", pocet_zaznamov);
}
/*pridanie do spajaneho zoznamu*/
void funkcia_a(HRAC** hlava_zoznamu) {
    int Y;
    int input_rok;
    int vypis;
    char input_meno[50];
    char input_krajina[50];
    int pocet_zaznamov = 0;
    size_t len;
    HRAC* aktualny;
    HRAC* novy;
    HRAC* predchadzajuci;
    int i;
    int max_num = 0;
    HRAC* pid_aktualny;
    int current_num;
    char new_pid_buffer[10];

    /*nacitame hodnotu Y*/
    if (scanf("%d", &Y) != 1) {
        printf("A: Nespravny vstup.\n");
        while (getchar() != '\n')
        return;
    }
    while (getchar() != '\n');
    /*nacitame meno*/
    if (fgets(input_meno, sizeof(input_meno), stdin) != NULL) {
        len = strlen(input_meno);
        if (len > 0 && input_meno[len-1] == '\n') {
            input_meno[len-1] = '\0';
        }
    }
    else {
        input_meno[0] = '\0';
    }
    /*nacitame krajinu*/
    if (fgets(input_krajina, sizeof(input_krajina), stdin) != NULL) {
        len = strlen(input_krajina);
        if (len > 0 && input_krajina[len-1] == '\n') {
            input_krajina[len-1] = '\0';
        }
    }
    else {
        input_krajina[0] = '\0';
    }
    /*nacitame rok*/
    if (scanf("%d", &input_rok) != 1) {
        while (getchar() != '\n')
        return;
    }
    while (getchar() != '\n');

    aktualny = *hlava_zoznamu;
    while (aktualny != NULL) {
        /*pocet spajanych zaznamov*/
        pocet_zaznamov++;
        if (strcmp(aktualny->Identita, input_meno) == 0 && aktualny->RokNar == input_rok) {
            printf("A: Duplicita zaznamu.\n");
            return;
        }
        aktualny = aktualny->next;
    }

    pid_aktualny = *hlava_zoznamu;
    while (pid_aktualny != NULL) {
        if (strncmp(pid_aktualny->PID, "PIDa", 4) == 0) {
            /*chceme porovnat input z najnizsim pid, a to je PIDa*/
            current_num = atoi(pid_aktualny->PID + 4);
            if (current_num > max_num) {
                max_num = current_num;
            }
        }
        pid_aktualny = pid_aktualny->next;
    }
    /*pridame novu hodnotu nasho pid*/
    if (max_num < 99999) {
        sprintf(new_pid_buffer, "PIDa%05d", max_num+1);
    }
    else {
        return;
    }
    /*robime novy spajany zoznam*/
    novy = (HRAC*)malloc(sizeof(HRAC));
    if (novy == NULL) {
        return;
    }
    strcpy(novy->PID, new_pid_buffer);
    strcpy(novy->Identita, input_meno);
    strcpy(novy->Krajina, input_krajina);
    novy->RokNar = input_rok;
    novy->zoznam_rieseni = NULL;
    novy->next = NULL;
    /*ak mame prave 1 bunku tak pridame sem*/
    if (*hlava_zoznamu == NULL) {
        *hlava_zoznamu = novy;
        vypis = 1;
    }
    /*ak mame menej 1, tak na zaciatok*/
    else if (Y<=1) {
        novy->next = *hlava_zoznamu;
        *hlava_zoznamu = novy;
        vypis = 1;
    }
    /*ak vacsie na koniec*/
    else if (Y>pocet_zaznamov) {
        aktualny = *hlava_zoznamu;
        while (aktualny->next != NULL) {
            aktualny = aktualny->next;
        }
        aktualny->next = novy;
        vypis = pocet_zaznamov + 1;
    }
    /*ak niekde medzi 0 a Y, tak medzi nimi*/
    else {
        predchadzajuci = NULL;
        aktualny = *hlava_zoznamu;
        i = 1;
        while (i < Y) {
            predchadzajuci = aktualny;
            aktualny = aktualny->next;
            i++;
        }
        /*posuvame 1 bunku spajaneho zoznamu pred sebou, a potom na prazdnu bunku dublikujeme novy zaznam*/
        if (predchadzajuci != NULL) {
            predchadzajuci->next = novy;
            novy->next = aktualny;
            vypis = Y;
        }
        else {
            free(novy);
            return;
        }
    }
    printf("A: Uspesne pridany zaznam na poziciu %d.\n", vypis);
}
/*funkcia na vymazanier spajanych zaznamov*/
void funkcia_s(HRAC** hlava_zoznamu) {
    char input_gid[20];
    size_t len;
    int vymazane_count = 0;
    HRAC* aktualny_hrac;
    RIESENIE* aktualne_riesenie;
    RIESENIE* predchadzujuce_riesenie;
    RIESENIE* na_vymazanie;

    if (*hlava_zoznamu == NULL) {
        printf("S: Spajany zoznam nie je vytvoreny.\n");
        while (getchar() != '\n');
        return;
    }
    if (fgets(input_gid, sizeof(input_gid), stdin) != NULL) {
        len = strlen(input_gid);
        if (len > 0 && input_gid[len-1] == '\n') {
            input_gid[len-1] = '\0';
        }
        else {
            return;
        }
        aktualny_hrac = *hlava_zoznamu;
        while (aktualny_hrac != NULL) {
            aktualne_riesenie = aktualny_hrac->zoznam_rieseni;
            predchadzujuce_riesenie = NULL;
            while (aktualne_riesenie != NULL) {
                if (strcmp(aktualne_riesenie->GID, input_gid) == 0) {
                    na_vymazanie = aktualne_riesenie;
                    /*vymazeme 1 bunku spajanego zoznamu*/
                    if (predchadzujuce_riesenie == NULL) {
                        aktualny_hrac->zoznam_rieseni = aktualne_riesenie->next;
                        aktualne_riesenie = aktualny_hrac->zoznam_rieseni;
                    }
                    else {
                        /*vymazeme hociktoru bunku*/
                        predchadzujuce_riesenie->next = aktualne_riesenie->next;
                        aktualne_riesenie = predchadzujuce_riesenie->next;
                    }
                    free(na_vymazanie);
                    vymazane_count++;
                }
                else {
                    predchadzujuce_riesenie = aktualne_riesenie;
                    aktualne_riesenie = aktualne_riesenie->next;
                }
            }
            aktualny_hrac = aktualny_hrac->next;
        }
    }
    printf("S: Vymazalo sa : %d zaznamov !\n", vymazane_count);
}
/*funkcia aby vymenit miestami trvanie u hracov*/
void funkcia_d(HRAC** hlava_zoznamu) {
    HRAC* aktualny_hrac = *hlava_zoznamu;
    RIESENIE *h;
    RIESENIE *p1;
    RIESENIE *p2;
    RIESENIE *prev;
    RIESENIE *lptr = NULL;
    int vymena;
    if (aktualny_hrac == NULL) {
        return;
    }
    while (aktualny_hrac != NULL) {
        h = aktualny_hrac->zoznam_rieseni;
        /*ak zoznam je prazdny alebo ma 1 prvok netriedime*/
        if (h == NULL || h->next == NULL) {
            aktualny_hrac = aktualny_hrac->next;
            continue;
        }
        do {
            vymena = 0;
            prev = NULL;
            p1 = h;
            while (p1->next != lptr) {
                p2 = p1->next;
                /*porovnanie casu*/
                if (p1->Trvanie > p2->Trvanie) {
                    if (prev == NULL) {
                        /*ak menime prvy prvok posuvame hlavu zoznamu*/
                        h = p2;
                        aktualny_hrac->zoznam_rieseni = p2;
                    }
                    else {
                        /*inak prepojime predchad. prvok  na novy prvy (p2)*/
                        prev->next = p2;
                    }
                    /*vymena nextov medzi p1 a p2*/
                    p1->next = p2->next;
                    p2->next = p1;
                    /*vymena teraz sa rovna 1*/
                    vymena = 1;
                    /*ak vymenili sme prvky, tak teda predchad. bude p2*/
                    prev = p2;
                }
                else {
                    /*ziadnia vymena, ideme d'alej*/
                    prev = p1;
                    p1 = p1->next;
                }
            }
            /*posledny prvok je na svojom mieste*/
            lptr = p1;
        }while (vymena);
        aktualny_hrac = aktualny_hrac->next;
    }
}
int main() {
    /*pridal som suboram null hodnotu, pretoze este ich ne otvorili*/
    FILE *sudoku = NULL;
    FILE *hraci = NULL;
    FILE *rieseni = NULL;
    char prikaz;
    int bufferclean;
    /*pointery na zaciatky spajanych zoznamov*/
    HRAC *zoznam_hracov = NULL;

    /*robime pointery na polia*/
    char(*pole_hracov_pid)[10] = NULL;
    char(*pole_hracov_meno)[100] = NULL;
    char(*pole_hracov_krajina)[50] = NULL;
    char(*pole_hracov_rok)[5] = NULL;

    char(*pole_rieseni_gid)[10] = NULL;
    char(*pole_rieseni_pid)[10] = NULL;
    char(*pole_rieseni_sid)[10] = NULL;
    char(*pole_rieseni_data)[50] = NULL;
    char(*pole_rieseni_min)[50] = NULL;
    char(*pole_rieseni_sek)[50] = NULL;

    char(*pole_sudoku_id)[20] = NULL;
    char(*pole_sudoku_gid)[1000] = NULL;

    /*counter pre dynamicke polia*/
    int pocet_hracov = 0;
    int pocet_sudoku = 0;
    int pocet_rieseni = 0;

    /*robime generator random cisel*/
    srand(time(NULL));

    while (scanf(" %c", &prikaz) == 1) {
        /*logika pre funkcii*/
        switch (prikaz) {
            case 'v':
                /*prechod na funkciu v*/
                funkcia_v(&sudoku, &hraci, &rieseni, pole_hracov_pid, pole_hracov_meno,
                pole_hracov_krajina, pole_hracov_rok, pole_rieseni_gid, pole_rieseni_pid, pole_rieseni_sid,
                pole_rieseni_data, pole_rieseni_min, pole_rieseni_sek, pocet_rieseni, pocet_hracov, zoznam_hracov);
                break;
            case 'h':
                /*prechod na funkciu h*/
                while ((bufferclean = getchar()) != '\n');
                funkcia_h(&rieseni);
                break;
            case 'n':
                /*prechod na funkciu n*/
                funkcia_n(&sudoku, &hraci, &rieseni, &pole_hracov_pid, &pole_hracov_meno,
                &pole_hracov_krajina, &pole_hracov_rok, &pole_rieseni_gid, &pole_rieseni_pid, &pole_rieseni_sid,
                &pole_rieseni_data, &pole_rieseni_min, &pole_rieseni_sek, &pole_sudoku_id, &pole_sudoku_gid,
                &pocet_hracov, &pocet_rieseni, &pocet_sudoku);
                break;
            case 'q':
                /*prechod na funkciu q*/
                funkcia_q(&pole_rieseni_gid, &pole_rieseni_pid, &pole_rieseni_sid,
                &pole_rieseni_data, &pole_rieseni_min, &pole_rieseni_sek, &pocet_rieseni);
                break;
            case 'w':
                /*prechod na funkciu w*/
                while ((bufferclean = getchar()) != '\n');
                funkcia_w(&pole_rieseni_gid, &pole_rieseni_pid, &pole_rieseni_sid,
                &pole_rieseni_data, &pole_rieseni_min, &pole_rieseni_sek, &pocet_rieseni);
                break;
            case 'e':
                /*prechod na funkciu e*/
                while ((bufferclean = getchar()) != '\n');
                funkcia_e(pole_sudoku_id, pole_sudoku_gid, pocet_sudoku);
                break;
            case 'm':
                while ((bufferclean = getchar()) != '\n');
                funkcia_m(&hraci, &rieseni, &zoznam_hracov);
                break;
            case 'a':
                funkcia_a(&zoznam_hracov);
                break;
            case 's':
                while ((bufferclean = getchar()) != '\n');
                funkcia_s(&zoznam_hracov);
                break;
            case 'd':
                while ((bufferclean = getchar()) != '\n');
                funkcia_d(&zoznam_hracov);
                break;
            case 'k':
                while (getchar() != '\n');
                if (sudoku != NULL) {
                    fclose(sudoku);
                }
                if (hraci != NULL) {
                    fclose(hraci);
                }
                if (rieseni != NULL) {
                    fclose(rieseni);
                }

                if (pole_hracov_pid != NULL) {
                    free(pole_hracov_pid);
                }
                if (pole_hracov_meno != NULL) {
                    free(pole_hracov_meno);
                }
                if (pole_hracov_krajina != NULL) {
                    free(pole_hracov_krajina);
                }
                if (pole_hracov_rok != NULL) {
                    free(pole_hracov_rok);
                }
                if (pole_rieseni_gid != NULL) {
                    free(pole_rieseni_gid);
                }
                if (pole_rieseni_pid != NULL) {
                    free(pole_rieseni_pid);
                }
                if (pole_rieseni_sid != NULL) {
                    free(pole_rieseni_sid);
                }
                if (pole_rieseni_data != NULL) {
                    free(pole_rieseni_data);
                }
                if (pole_rieseni_min != NULL) {
                    free(pole_rieseni_min);
                }
                if (pole_rieseni_sek != NULL) {
                    free(pole_rieseni_sek);
                }
                if (pole_sudoku_id != NULL) {
                    free(pole_sudoku_id);
                }
                if (pole_sudoku_gid != NULL) {
                    free(pole_sudoku_gid);
                }

                if (zoznam_hracov != NULL) {
                    HRAC* aktualny_hrac = zoznam_hracov;
                    HRAC* dalsi_hrac;
                    RIESENIE* aktualne_riesenie;
                    RIESENIE* dalsie_riesenie;
                    while (aktualny_hrac != NULL) {
                        aktualne_riesenie = aktualny_hrac->zoznam_rieseni;
                        while (aktualne_riesenie != NULL) {
                            dalsie_riesenie = aktualne_riesenie->next;
                            free(aktualne_riesenie);
                            aktualne_riesenie = dalsie_riesenie;
                        }
                        dalsi_hrac = aktualny_hrac->next;
                        free(aktualny_hrac);
                        aktualny_hrac = dalsi_hrac;
                    }
                    zoznam_hracov = NULL;
                }
                return 0;
                break;
            default:
                break;
        }
    }
    return 0;
}
