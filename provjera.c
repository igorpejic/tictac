#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define vel 3

void izbornik();
void upisi_igrace();
void pokreni_igru();
void kraj_igre();
void ispis_mape(int broj, int broj2);

char igrac1[15], igrac2[15];
int bodovi_igrac_1, bodovi_igrac_2;	
int polje[vel][vel], prvi=1, broj_poteza;

int main()
{
    izbornik();

    return 0;
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
                for(i=0; i<vel; i++)
                    for(j=0; j<vel; j++)
                        polje[i][j]=0;
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
    int red, stupac, br=1;
    char Stupac;
    ispis_mape(3, 3);
    while (1) {
        //PRVI IGRAČ
        if (prvi==1) 
        {
            while (br==1) {
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
                if (polje[red][stupac]==0){
                    polje[red][stupac]=1;
                    br=0;
                    broj_poteza++;
                }
                else {
                    printf ("Upisite neku koordinatu koja je slobodna");
                }
                ispis_mape(1, 2);

            }
        }

        //DRUGI IGRAČ
        while (br==0) {
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
            if (polje[red][stupac]==0){
                polje[red][stupac]=2;
                br=1;
                broj_poteza++;
            }
            else {
                printf ("Upisite neku koordinatu koja je slobodna");
            }
            prvi=1;
            ispis_mape(2, 1);
        }	

    }}

void ispis_mape (int broj, int broj2) {
    int i, j, dijagonalno=0, dijagonalno2=0, okomito=0, okomito2=0, okomito3=0, vodoravno=0, vodoravno2=0, vodoravno3=0;
    int d1=0, d2=0, o1=0, o2=0, o3=0, v1=0, v2=0, v3=0, br=0;
    printf ("\n");
    printf("   a   b   c  \n");
    for (i=0; i<vel; i++) {
        printf("%d",i+1);
        for (j=0; j<vel; j++) {
            if (polje[i][j]==1) printf ("| X ");
            if (polje[i][j]==2) printf ("| O ");
            if (polje[i][j]==0) printf ("| . ");
            if (i==j) {
                if (polje[i][j]==broj) dijagonalno++;
                if (polje[i][j]==broj2) d1++;
                if (((dijagonalno>=1) && (d1>=1)) || ((d1==2) && broj_poteza==7)) br++; //ovo tu pa na dalje isto ti if-ovi ne znam zasto nisu dobri
            }
            if (i+j==vel-1) {
                if (polje[i][j]==broj) dijagonalno2++;
                if (polje[i][j]==broj2) d2++;
                if (((dijagonalno2>=1) && (d2>=1)) || ((d2==2)  && broj_poteza==7)) br++;
            }
            if (i==0) {
                if (polje[i][j]==broj) vodoravno++;
                if (polje[i][j]==broj2) v1++;
                if (((vodoravno>=1) && (v1>=1)) || ((v1==2)  && broj_poteza==7)) br++;
            }
            if (i==1) {
                if (polje[i][j]==broj) vodoravno2++;
                if (polje[i][j]==broj2) v2++;
                if (((vodoravno2>=1) && (v2>=1)) || ((v2==2)  && broj_poteza==7)) br++;
            }
            if (i==2) {
                if (polje[i][j]==broj) vodoravno3++;
                if (polje[i][j]==broj2) v3++;
                if (((vodoravno3>=1) && (v3>=1)) || ((v3==2)  && broj_poteza==7))br++;
            }
            if (j==0) {
                if (polje[i][j]==broj) okomito++;
                if (polje[i][j]==broj2) o1++;
                if (((okomito>=1) && (o1>=1)) || ((o1==2)  && broj_poteza==7))br++;
            }
            if (j==1) {
                if (polje[i][j]==broj) okomito2++;
                if (polje[i][j]==broj2) o2++;
                if (((okomito2>=1) && (o2>=1)) || ((o2==2)  && broj_poteza==7))br++;
            }
            if (j==2) {
                if (polje[i][j]==broj) okomito3++;
                if (polje[i][j]==broj2) o3++;
                if (((okomito3>=1) && (o3>=1)) || ((o3==2)  && broj_poteza==7))br++;
            }
        }
        printf ("|\n");
    }
    printf ("\n%d", br); //tu ne ide 1,2,3.. nego samo odjednom skoci na 2 ili 4, a ponekad ide samo po jedan. bo :D
    // PA NORMALNO DA IDE ZA 2 KADA FUNKCIJA IMITIRA 2 POTEZA, 1 PRVOG i 1 DRUGO IGRACA
    //printf ("\n%d %d", dijagonalno2, d2);
    //printf ("\n%d %d", dijagonalno, d1);

    if (br==8) izbornik();

    if (dijagonalno==3 || dijagonalno2==3 || vodoravno==3 || vodoravno2==3|| vodoravno3==3 || okomito==3|| okomito2==3|| okomito3==3) {
        if (broj==1) {
            bodovi_igrac_1++;
            prvi=1;
        }
        if (broj==2) {
            bodovi_igrac_2++;
            prvi=2;
        }
        for (i=0; i<vel; i++) {
            for (j=0; j<vel; j++) {
                polje[i][j]=0;
            }}
        izbornik();
    }
}


void kraj_igre() {
    printf ("\nIgrač %s osvojio je %d bodova", igrac1, bodovi_igrac_1);
    printf ("\nIgrač %s osvojio je %d bodova", igrac2, bodovi_igrac_2);
    if (bodovi_igrac_1>bodovi_igrac_2) printf ("\nPobjedio je igrač %s!", igrac1);
    else printf ("\nPobjedio je igrač %s!", igrac2);
    exit (1);
}
