#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define VEL 3
//defineovi uvijek velikim slovima

void izbornik();
void upisi_igrace();
void pokreni_igru();
void kraj_igre();
void ispis_mape();
int provjera_pobjede(); //vraca 0 ako nije zavrseno, 1 ako je 1. pobjedio, 2 ako drugi
int provjera_nitko_ne_pobjeduje();
int provjera_pobjede_hipotetski(int polje[][VEL]);

char igrac1[15], igrac2[15];
int bodovi_igrac_1, bodovi_igrac_2;	
int polje[VEL][VEL], prvi=1, broj_poteza;

int main()
{
    izbornik();

    return 0;
}

/*funkcija vraca 1 ako nitko ne moze pobjediti, 0 ako se moze pobjediti*/
/*turn = 1 za provjeru samo kruzica */
int provjera_nitko_ne_pobjeduje(){
    int probno_polje[VEL][VEL];
    int i, j;
    int val1=0;
    int val2=0;
        for(i = 0; i < VEL; i++){
            for(j = 0; j < VEL; j++){
                probno_polje[i][j] = polje[i][j];
            }
        }
        /*provjera za prvog */
        for(i = 0; i < VEL; i++){
            for(j = 0; j < VEL; j++){
                if(probno_polje[i][j] == 0)
                    probno_polje[i][j] = 1;
            }
        }
        if(provjera_pobjede_hipotetski(probno_polje)==1)
            val1=1;

    for(i = 0; i < VEL; i++){
        for(j = 0; j < VEL; j++){
            probno_polje[i][j] = polje[i][j];
        }
    }
    for(i = 0; i < VEL; i++){
        for(j = 0; j < VEL; j++){
            if(probno_polje[i][j] == 0)
                probno_polje[i][j] = 2;
        }
    }
    if(provjera_pobjede_hipotetski(probno_polje)==2)
        val2=1;
    if(val2||val1)
        return 0;
    return 1;
}
int provjera_pobjede_hipotetski(int ppolje[][VEL]){
    /* provjerava redove */
    if(ppolje[0][0]==1 && ppolje[0][1]==1 && ppolje[0][2] ==1)
        return 1; //pobjedio je prvi igrac
    if(ppolje[1][0]==1 && ppolje[1][1]==1 && ppolje[1][2] ==1)
        return 1; //pobjedio je prvi igrac
    if(ppolje[2][0]==1 && ppolje[2][1]==1 && ppolje[2][2] ==1)
        return 1; //pobjedio je prvi igrac

    /* provjerava stupce */
    if(ppolje[0][0]==1 && ppolje[1][0]==1 && ppolje[2][0] ==1)
        return 1; //pobjedio je prvi igrac
    if(ppolje[0][1]==1 && ppolje[1][1]==1 && ppolje[2][1] ==1)
        return 1; //pobjedio je prvi igrac
    if(ppolje[0][2]==1 && ppolje[1][2]==1 && ppolje[2][2] ==1)
        return 1; //pobjedio je prvi igrac

    /* provjerava dijagonale */
    if(ppolje[0][0]==1 && ppolje[1][1]==1 && ppolje[2][2] ==1)
        return 1; //pobjedio je prvi igrac
    if(ppolje[2][0]==1 && ppolje[1][1]==1 && ppolje[0][2] ==1)
        return 1; //pobjedio je prvi igrac

    /* DRUGI IGRAC */
    /* provjerava redove */
    if(ppolje[0][0]==2 && ppolje[0][1]==2 && ppolje[0][2] ==2)
        return 2; //pobjedio je drugi igrac
    if(ppolje[1][0]==2 && ppolje[1][1]==2 && ppolje[1][2] ==2)
        return 2; //pobjedio je drugi igrac
    if(ppolje[2][0]==2 && ppolje[2][1]==2 && ppolje[2][2] ==2)
        return 2; //pobjedio je drugi igrac

    /* provjerava stupce */
    if(ppolje[0][0]==2 && ppolje[1][0]==2 && ppolje[2][0] ==2)
        return 2; //pobjedio je drugi igrac
    if(ppolje[0][1]==2 && ppolje[1][1]==2 && ppolje[2][1] ==2)
        return 2; //pobjedio je drugi igrac
    if(ppolje[0][2]==2 && ppolje[1][2]==2 && ppolje[2][2] ==2)
        return 2; //pobjedio je drugi igrac

    /* provjerava dijagonale */
    if(ppolje[0][0]==2 && ppolje[1][1]==2 && ppolje[2][2] ==2)
        return 2; //pobjedio je drugi igrac
    if(ppolje[2][0]==2 && ppolje[1][1]==2 && ppolje[0][2] ==2)
        return 2; //pobjedio je drugi igrac
    return 0;//nema pobjedinka jos
}

void izbornik () {
    int izbor, i, j;
    printf ("~ TIC TAC TOE ~\n");
    printf ("1. Igranje igre\n2. Upis imena igrača\n3. Kraj igre");
    printf ("\nUpisi jedan od prethodno navedenih brojeva: ");
    scanf ("%d", &izbor);

    switch(izbor) {
        case 2: upisi_igrace();
        case 1: system ("clear");
                for(i=0; i<VEL; i++)
                    for(j=0; j<VEL; j++)
                        polje[i][j]=0;
                broj_poteza=0;
                pokreni_igru();
                break;
        case 3: kraj_igre(); break;
    }
}

void upisi_igrace () {
    printf ("\nUpisi ime prvog igraca: ");
    scanf ("%s", igrac1);
    printf ("Upisi ime drugog igraca: ");
    scanf ("%s", igrac2);
}

void pokreni_igru() {
    int red, stupac;
    char Stupac;
    ispis_mape();
    while (1) {
        if(provjera_nitko_ne_pobjeduje() == 1){
            printf("Nitko ne moze pobjediti, iako ima slobodnih polja.\n");
            izbornik();
            return;
        }
        //PRVI IGRAČ
        if(prvi==1){
            while (1) {
                printf ("\n*igra %s*", igrac1);
                printf ("\nUpisi koordinatu: (najprije slovo pa broj, npr b2)");
                scanf (" %c%d", &Stupac, &red);
                if(isupper(Stupac)) Stupac=tolower(Stupac);
                system("clear"); //problem je u ovome kod ponovnog upisa koordinate!
                red=red-1;
                switch(Stupac) {
                    case 'a': stupac=0; break;
                    case 'b': stupac=1; break;
                    case 'c': stupac=2; break;
                }
                if(red >2 || red < 0 || stupac < 0 || stupac>2){
                    printf("Upisite neku koordinatu koja postoji\n");
                }
                else if (polje[red][stupac]==0){
                    polje[red][stupac]=1;
                    broj_poteza++;
                    ispis_mape();
                    if(provjera_pobjede() == 1){
                        bodovi_igrac_1++;
                        prvi=0;
                        izbornik();
                        return;
                    }
                    break;
                }
                else {
                    printf ("Upisite neku koordinatu koja je slobodna");
                }
                ispis_mape();
            }
        }
        if(provjera_nitko_ne_pobjeduje() == 1){
            printf("Nitko ne moze pobjediti, iako ima slobodnih polja.\n");
            izbornik();
            return;
        }
        if(broj_poteza==9){//nema pobjednika
            printf("Nema pobjednika!\n");
            izbornik();
            return;
        }

        //DRUGI IGRAČ
        while (1) {
            prvi = 1;
            printf ("\n*igra %s*", igrac2);
            printf ("\nUpisi koordinatu: (najprije slovo pa broj, npr b2) ");
            scanf (" %c%d", &Stupac, &red);
            if(isupper(Stupac)) Stupac=tolower(Stupac);
            system ("clear");
            red=red-1;
            switch(Stupac) {
                case 'a': stupac=0; break;
                case 'b': stupac=1; break;
                case 'c': stupac=2; break;
            } 
            if(red >2 || red < 0 || stupac < 0 || stupac>2){
                printf("Upisite neku koordinatu koja postoji\n");
            }
            else if (polje[red][stupac]==0){
                broj_poteza++;
                polje[red][stupac]=2;
                ispis_mape();
                if(provjera_pobjede() == 2){
                    bodovi_igrac_2++;
                    prvi =1;
                    izbornik();
                    return;
                }
                break;
            }
            else {
                printf ("Upisite neku koordinatu koja je slobodna");
            }
            ispis_mape();
        }	
    }
}

int provjera_pobjede(){
    /* provjerava redove */
    if(polje[0][0]==1 && polje[0][1]==1 && polje[0][2] ==1)
        return 1; //pobjedio je prvi igrac
    if(polje[1][0]==1 && polje[1][1]==1 && polje[1][2] ==1)
        return 1; //pobjedio je prvi igrac
    if(polje[2][0]==1 && polje[2][1]==1 && polje[2][2] ==1)
        return 1; //pobjedio je prvi igrac

    /* provjerava stupce */
    if(polje[0][0]==1 && polje[1][0]==1 && polje[2][0] ==1)
        return 1; //pobjedio je prvi igrac
    if(polje[0][1]==1 && polje[1][1]==1 && polje[2][1] ==1)
        return 1; //pobjedio je prvi igrac
    if(polje[0][2]==1 && polje[1][2]==1 && polje[2][2] ==1)
        return 1; //pobjedio je prvi igrac

    /* provjerava dijagonale */
    if(polje[0][0]==1 && polje[1][1]==1 && polje[2][2] ==1)
        return 1; //pobjedio je prvi igrac
    if(polje[2][0]==1 && polje[1][1]==1 && polje[0][2] ==1)
        return 1; //pobjedio je prvi igrac

    /* DRUGI IGRAC */
    /* provjerava redove */
    if(polje[0][0]==2 && polje[0][1]==2 && polje[0][2] ==2)
        return 2; //pobjedio je drugi igrac
    if(polje[1][0]==2 && polje[1][1]==2 && polje[1][2] ==2)
        return 2; //pobjedio je drugi igrac
    if(polje[2][0]==2 && polje[2][1]==2 && polje[2][2] ==2)
        return 2; //pobjedio je drugi igrac

    /* provjerava stupce */
    if(polje[0][0]==2 && polje[1][0]==2 && polje[2][0] ==2)
        return 2; //pobjedio je drugi igrac
    if(polje[0][1]==2 && polje[1][1]==2 && polje[2][1] ==2)
        return 2; //pobjedio je drugi igrac
    if(polje[0][2]==2 && polje[1][2]==2 && polje[2][2] ==2)
        return 2; //pobjedio je drugi igrac

    /* provjerava dijagonale */
    if(polje[0][0]==2 && polje[1][1]==2 && polje[2][2] ==2)
        return 2; //pobjedio je drugi igrac
    if(polje[2][0]==2 && polje[1][1]==2 && polje[0][2] ==2)
        return 2; //pobjedio je drugi igrac
    return 0;//nema pobjedinka jos
}


void ispis_mape () {
    int i, j;
    printf ("\n");
    printf("   a   b   c  \n");
    for (i=0; i<VEL; i++) {
        printf("%d",i+1);
        for (j=0; j<VEL; j++) {
            if (polje[i][j]==1) printf ("| X ");
            if (polje[i][j]==2) printf ("| O ");
            if (polje[i][j]==0) printf ("| . ");
        }
        printf ("|\n");
    }
}


void kraj_igre() {
    printf ("\nIgrač %s osvojio je %d bodova", igrac1, bodovi_igrac_1);
    printf ("\nIgrač %s osvojio je %d bodova", igrac2, bodovi_igrac_2);
    if (bodovi_igrac_1==bodovi_igrac_2)
        printf ("\nIzjednaceno!");
    else if(bodovi_igrac_1 > bodovi_igrac_2)
        printf ("\nPobjedio je igrač %s!", igrac1);
    else
        printf ("\nPobjedio je igrač %s!", igrac2);
    exit (1);
}
