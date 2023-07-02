//BATTLESHIP

//spustaj cez Online GDB

#include <stdio.h>

//struktura player obsahujuca informacie o hracovi
typedef struct _player{
    int pocetPoli;
    int strely;
    int zasahy;
    int strelyMimo;

}Player;

//funckia na resetovanie farby
void reset() {
    printf("\033[0m");
}

//funkcia na nastavenie červenej farby
void red() {
    printf("\033[31m");
}

//funkcia na nastavenie zelenej farby
void green() {
    printf("\033[32m");
}

//funkcia na nastavenie modrej farby
void blue() {
    printf("\033[34m");
}

//funkcia na nastavenie žltej farby
void yellow() {
    printf("\033[33m");
}

//funkcia na vymazanie konzoly
void clear() {
    printf("\033[2J\033[H");
}

//funkcia na vypis loga hry
void logo(){
    clear();
    blue();
    printf("**************\n");
    printf("* ");
    reset();
    printf("BATTLESHIP");
    blue();
    printf(" *\n");
    printf("**************\n\n");
    reset();
}

//funkcia na vypis loga hry na poziciu medzi herne mriezky
void logoStred(int pocet){
    blue();
    for (int i=0; i!=pocet*5; i++)
        printf(" ");

    printf("**************\n");
    for (int i=0; i!=pocet*5; i++)
        printf(" ");

    printf("* ");
    reset();
    printf("BATTLESHIP");
    blue();
    printf(" *\n");
    for (int i=0; i!=pocet*5; i++)
        printf(" ");

    printf("**************\n");
}

//funkcia na vypis textu hraca 1
void textP1(int pocet){
    logoStred(pocet);
    green();
    printf("PLAYER 1\n");
    reset();
}

//funkcia na vypis textu hraca 2
void textP2(int pocet){
    logoStred(pocet);
    red();
    printf("PLAYER 2\n");
    reset();
}

//funkcia na zakladnu kontrolu prijatych suradnic
int kontrolaSuradnic(int x, int y, int suradnicaX1, int suradnicaX2, int suradnicaY1,int suradnicaY2){
    if (suradnicaX1 >= x || suradnicaX2 >= x) {
        red();
        printf("\nNeplatne suradnice.\n");
        reset();
        return 1;
    }
    else if (suradnicaX1 < 1 || suradnicaX2 < 1) {
        red();
        printf("\nNeplatne suradnice.\n");
        reset();
        return 1;
    }
    else if (suradnicaY1 >= y || suradnicaY2 >= y){
        red();
        printf("\nNeplatne suradnice.\n");
        reset();
        return 1;
    }
    else if (suradnicaY1 < 1 || suradnicaY2 < 1){
        red();
        printf("\nNeplatne suradnice.\n");
        reset();
        return 1;
    }
    else
        return 0;
}

//funkcia na vypis lodi(flotili), ktoré sú v hre
void tlacLode(int i){
    if (i == 1)
        printf(" Fleet:         ");
    else if (i == 2) {
        green();
        printf(" Carrier [5]    ");
        reset();
    }
    else if (i == 3) {
        green();
        printf(" Battleship [4] ");
        reset();
    }
    else if (i == 4) {
        green();
        printf(" Destroyer [3]  ");
        reset();
    }
    else if (i == 5) {
        green();
        printf(" Submarine [3]   ");
        reset();
    }
    else if (i == 6) {
        green();
        printf(" Patrol Boat [2]");
        reset();
    }
    else
        printf("\t\t");
}

//funkcia na vypis hernej mriezky daneho hraca
void tlacMriezku(int x, int y, int mriezka[x][y]){
    for (int i=0; i<y; i++) {
        printf("\n");
        for (int j = 0; j < x; j++) {
            if (mriezka[j][i] == 126)
                blue();
            else if (mriezka[j][i] == 42)
                red();
            else if (mriezka[j][i] == 48 && i != 0)
                green();
            else
                reset();

            if (i == 0 && j > 9)
                printf("[1%c]", mriezka[j][i]);
            else
                printf("[%c] ", mriezka[j][i]);

            reset();
        }
        tlacLode(i);
    }
    printf("\n\n");
}

//funkcia na vypis hernych mriezok
void tlacMriezky(int x, int y, int mriezka1[x][y], int mriezka2[x][y]){
    for (int i=0; i<y; i++) {
        printf("\n");
        for (int j=0; j<x; j++) {
            if (mriezka1[j][i] == 126)
                blue();
            else if (mriezka1[j][i] == 42)
                red();
            else if (mriezka1[j][i] == 48 && i != 0)
                green();
            else
                reset();

            if (i == 0 && j > 9)
                printf("[1%c]", mriezka1[j][i]);
            else
                printf("[%c] ", mriezka1[j][i]);

            reset();
        }
        tlacLode(i);
        printf("\t\t");
        for (int j=0; j<x; j++) {
            if (mriezka2[j][i] == 126)
                blue();
            else if (mriezka2[j][i] == 42)
                red();

            if (i == 0 && j > 9)
                printf("[1%c]", mriezka2[j][i]);
            else
                printf("[%c] ", mriezka2[j][i]);

            reset();
        }
        tlacLode(i);
    }
    printf("\n\n");
}

//funkcia na vygenreovanie hernych mriezok
void genMriezka(int x, int y, int mriezka1[x][y], int mriezka2[x][y]){
    for (int i=0; i<y; i++){
        for (int j=0; j<x; j++){
            if (j == 0 && i == 0){
                mriezka1[j][i] = 32;
                mriezka2[j][i] = 32;
            }
            else if (i == 0){
                if (j < 10) {
                    mriezka1[j][i] = 48 + j;
                    mriezka2[j][i] = 48 + j;
                }
                else{
                    mriezka1[j][i] = 38 + j;
                    mriezka2[j][i] = 38 + j;
                }
            }
            else{
                if (j == 0){
                    mriezka1[j][i] = 64+i;
                    mriezka2[j][i] = 64+i;
                }
                else{
                    mriezka1[j][i] = 126;
                    mriezka2[j][i] = 126;
                }
            }
        }
    }
}

//funkcia na vygenerovanie lodi, vlozenie lodi na poziciu, ktoru si zvoli hrac
void genLode(int x, int y, int mriezka1[x][y], int hrac){
    int suradnicaX1, suradnicaX2, suradnicaY1, suradnicaY2, povodnaX1, povodnaY1;
    char znakY1, znakY2;

    for (int i=0; i<5; i++) {
        if (hrac == 2) {
            textP2(x);
            tlacMriezku(x, y, mriezka1);
        }
        else {
            textP1(x);
            tlacMriezku(x, y, mriezka1);
        }

        start:
        reset();
        if (i == 0)
            printf("\nZadajte suradnice Carrier [5] (A1-A5): ");
        else if (i == 1)
            printf("\nZadajte suradnice Battleship [4] (A1-A4): ");
        else if (i == 2)
            printf("\nZadajte suradnice Destroyer [3] (A1-A3): ");
        else if (i == 3)
            printf("\nZadajte suradnice Submarine [3] (A1-A3): ");
        else
            printf("\nZadajte suradnice Patrol Boat [2] (A1-A2): ");

        if (hrac == 1)
            scanf("%c%d-%c%d", &znakY1, &suradnicaX1, &znakY2, &suradnicaX2);
        scanf("%c%d-%c%d", &znakY1, &suradnicaX1, &znakY2, &suradnicaX2);
        suradnicaY1 = (int) znakY1 - 64;
        suradnicaY2 = (int) znakY2 - 64;
        povodnaX1 = suradnicaX1;
        povodnaY1 = suradnicaY1;
        if (kontrolaSuradnic(x, y, suradnicaX1, suradnicaX2, suradnicaY1, suradnicaY2) == 1)
            goto start;

        if (suradnicaX1 != suradnicaX2 && suradnicaY1 != suradnicaY2){
            red();
            printf("\nNeplatne suradnice, lode mozu byt vodorovne alebo zvislo.\n");
            goto start;
        }
        else if (i == 0){
            if (suradnicaX2-suradnicaX1 != -4 && suradnicaY2-suradnicaY1 != -4) {
                if (suradnicaX2 - suradnicaX1 != 4 && suradnicaY2 - suradnicaY1 != 4) {
                    red();
                    printf("\nNeplatne suradnice, musi mat velkost 5.\n");
                    goto start;
                }
            }
        }
        else if (i == 1){
            if (suradnicaX2-suradnicaX1 != -3 && suradnicaY2-suradnicaY1 != -3) {
                if (suradnicaX2 - suradnicaX1 != 3 && suradnicaY2 - suradnicaY1 != 3) {
                    red();
                    printf("\nNeplatne suradnice, musi mat velkost 4.\n");
                    goto start;
                }
            }
        }
        else if (i == 2 || i == 3){
            if (suradnicaX2-suradnicaX1 != -2 && suradnicaY2-suradnicaY1 != -2) {
                if (suradnicaX2 - suradnicaX1 != 2 && suradnicaY2 - suradnicaY1 != 2) {
                    red();
                    printf("\nNeplatne suradnice, musi mat velkost 3.\n");
                    goto start;
                }
            }
        }
        else if (i == 4){
            if (suradnicaX2-suradnicaX1 != -1 && suradnicaY2-suradnicaY1 != -1) {
                if (suradnicaX2 - suradnicaX1 != 1 && suradnicaY2 - suradnicaY1 != 1) {
                    red();
                    printf("\nNeplatne suradnice, musi mat velkost 2.\n");
                    goto start;
                }
            }
        }

        while (suradnicaX1 != suradnicaX2 || suradnicaY1 != suradnicaY2) {
            if (mriezka1[suradnicaX1][suradnicaY1] == 48){
                red();
                printf("\nNeplatne suradnice, na tejto pozicii sa uz nachadza lod.\n");
                goto start;
            }

            if (suradnicaX1 < suradnicaX2 || suradnicaY1 < suradnicaY2) {
                if (suradnicaX1 == suradnicaX2)
                    suradnicaY1++;
                else if (suradnicaY1 == suradnicaY2)
                    suradnicaX1++;
            }
            else if (suradnicaX1 > suradnicaX2 || suradnicaY1 > suradnicaY2) {
                if (suradnicaX1 == suradnicaX2)
                    suradnicaY1--;
                else if (suradnicaY1 == suradnicaY2)
                    suradnicaX1--;
            }
        }
        suradnicaX1 = povodnaX1;
        suradnicaY1 = povodnaY1;

        while (suradnicaX1 != suradnicaX2 || suradnicaY1 != suradnicaY2) {
            mriezka1[suradnicaX1][suradnicaY1] = 48;
            if (suradnicaX1 < suradnicaX2 || suradnicaY1 < suradnicaY2) {
                if (suradnicaX1 == suradnicaX2)
                    suradnicaY1++;
                else if (suradnicaY1 == suradnicaY2)
                    suradnicaX1++;
            }
            else if (suradnicaX1 > suradnicaX2 || suradnicaY1 > suradnicaY2){
                if (suradnicaX1 == suradnicaX2)
                    suradnicaY1--;
                else if (suradnicaY1 == suradnicaY2)
                    suradnicaX1--;
            }
        }
        mriezka1[suradnicaX1][suradnicaY1] = 48;
        clear();
    }
    if (hrac == 2) {
        textP2(x);
        tlacMriezku(x, y, mriezka1);
        printf("\nStlac enter pre start hry!");
        while (getchar() != '\n');
        while (getchar() != '\n');
    }
    else {
        textP1(x);
        tlacMriezku(x, y, mriezka1);
        printf("\nStlac enter!");
        while (getchar() != '\n');
        while (getchar() != '\n');
    }
    clear();
}

//funkcia na vypis koncoveho skore hracov
void vyhra(int player, Player player1, Player player2){
    clear();
    logoStred(7);
    reset();
    if (player == 2){
        printf("\t************\n");
        printf("\t* ");
        red();
        printf("Player 2");
        reset();
        printf(" *\t\t");
        green();
        printf("\t\t\tPlayer 1\n");
        reset();
        printf("\t************\n\n");
        printf("Pocet striel\t\t\t%d\t\tPocet striel\t\t\t%d\n", player2.strely, player1.strely);
        printf("Pocet zasahov\t\t\t%d\t\tPocet zasahov\t\t\t%d\n", player2.zasahy, player1.zasahy);
        printf("Pocet striel mimo\t\t%d\t\tPocet striel mimo\t\t%d\n", player2.strelyMimo, player1.strelyMimo);
        red();
        printf("\nVyhral hrac 2!\n\n");
        reset();
    }
    else{
        printf("\t************\n");
        printf("\t* ");
        green();
        printf("Player 1");
        reset();
        printf(" *\t\t");
        red();
        printf("\t\t\tPlayer 2\n");
        reset();
        printf("\t************\n\n");
        printf("Pocet striel\t\t\t%d\t\tPocet striel\t\t\t%d\n", player1.strely, player2.strely);
        printf("Pocet zasahov\t\t\t%d\t\tPocet zasahov\t\t\t%d\n", player1.zasahy, player2.zasahy);
        printf("Pocet striel mimo\t\t%d\t\tPocet striel mimo\t\t%d\n", player1.strelyMimo, player2.strelyMimo);
        green();
        printf("\nVyhral hrac 1!\n\n");
        reset();
    }
    printf("\nStlac enter pre navrat do menu!");
    while (getchar() != '\n');
}

//funkcia na priebeh hry, striedanie hracov, spracovanie utocnych suradnic a vypis informacii o utoku
void hra(int x, int y, int mriezka1[x][y], int mriezka2[x][y], int mriezka3[x][y], int mriezka4[x][y]){
    int suradnicaX, suradnicaY, player;
    char znakY;
    Player player1 = {17,0,0,0};
    Player player2 = {17,0,0,0};

    //scanf("%c", &znakY);
    while (player1.pocetPoli != 0 && player2.pocetPoli != 0) {
        clear();
        textP1(x);
        tlacMriezky(x, y, mriezka1, mriezka2);
        start1:
        printf("\nZadajte suradnice utoku (A1): ");
        scanf("%c%d", &znakY, &suradnicaX);
        suradnicaY = (int) znakY - 64;
        if (kontrolaSuradnic(x, y, suradnicaX, 1, suradnicaY, 1) == 1)
            goto start1;

        else if (mriezka3[suradnicaX][suradnicaY] == 48){
            mriezka2[suradnicaX][suradnicaY] = 42;
            mriezka3[suradnicaX][suradnicaY] = 42;
            player2.pocetPoli--;
            player1.zasahy++;
            clear();
            textP1(x);
            tlacMriezky(x, y, mriezka1, mriezka2);
            green();
            printf("\nStrela zasiahla\n\n");
            reset();
        }
        else if (mriezka3[suradnicaX][suradnicaY] != 42 && mriezka3[suradnicaX][suradnicaY] != 88){
            mriezka2[suradnicaX][suradnicaY] = 88;
            mriezka3[suradnicaX][suradnicaY] = 88;
            player1.strelyMimo++;
            clear();
            textP1(x);
            tlacMriezky(x, y, mriezka1, mriezka2);
            blue();
            printf("\nStrela mimo\n\n");
            reset();
        }
        else{
            red();
            printf("\nNeplatna suradnica, na danu poziciu ste uz zautocili.\n");
            reset();
            goto start1;
        }

        player1.strely++;
        printf("\nStlac enter!");
        while (getchar() != '\n');
        while (getchar() != '\n');

        if (player2.pocetPoli == 0)
            break;

        clear();
        textP2(x);
        tlacMriezky(x, y, mriezka3, mriezka4);
        start2:
        printf("\nZadajte suradnice utoku (A1): ");
        scanf("%c%d", &znakY, &suradnicaX);
        suradnicaY = (int) znakY - 64;
        if (kontrolaSuradnic(x, y, suradnicaX, 1, suradnicaY, 1) == 1)
            goto start2;

        else if (mriezka1[suradnicaX][suradnicaY] == 48){
            mriezka4[suradnicaX][suradnicaY] = 42;
            mriezka1[suradnicaX][suradnicaY] = 42;
            player1.pocetPoli--;
            player2.zasahy++;
            clear();
            textP2(x);
            tlacMriezky(x, y, mriezka3, mriezka4);
            green();
            printf("\nStrela zasiahla\n\n");
            reset();
        }
        else if (mriezka1[suradnicaX][suradnicaY] != 42 && mriezka1[suradnicaX][suradnicaY] != 88){
            mriezka4[suradnicaX][suradnicaY] = 88;
            mriezka1[suradnicaX][suradnicaY] = 88;
            player2.strelyMimo++;
            clear();
            textP2(x);
            tlacMriezky(x, y, mriezka3, mriezka4);
            blue();
            printf("\nStrela mimo\n\n");
            reset();
        }
        else{
            red();
            printf("\nNeplatna suradnica, na danu poziciu ste uz zautocili.\n");
            reset();
            goto start2;
        }
        player2.strely++;
        printf("\nStlac enter!");
        while (getchar() != '\n');
        while (getchar() != '\n');
    }

    if (player1.pocetPoli == 0)
        player = 2;

    else
        player = 1;

    vyhra(player, player1, player2);
}

//funkcia na vypis napovedy
void napoveda(){
    clear();
    logo();
    yellow();
    printf("Napoveda\n\n");
    reset();
    printf("1. Po zvoleni moznosti Hrat (1) je potrebne vybrat velkost hracej mriezky vo formate ");
    red();
    printf("x y");
    reset();
    printf(" (10 10).\n");
    printf("2. Vyberiete pozicie lodi od najvacsej po najmensiu vo formate ");
    red();
    printf("yx-yx");
    reset();
    printf(" (A1-A5, nezabudni -), najprv hrac 1 potom hrac 2.\n");
    printf("3. Hra zacina hracom 1, hraci sa striedaju, hraci vyberaju suradnice utoku vo formate ");
    red();
    printf("xy");
    reset();
    printf(" (A1).\n");
    printf("4. Ak jeden s hracom znici vsetky lode druheho hraca, hra skonci a vypise sa skore hracov.\n");
    printf("\nStlac enter pre navrat do menu!");
    while (getchar() != '\n');
    while (getchar() != '\n');
}

//funkcia na vypis menu hry
int menu(){
    int index;

    logo();
    green();
    printf("Hrat\t [1]\n");
    yellow();
    printf("Napoveda [2]\n");
    red();
    printf("Ukoncit  [3]\n");
    reset();
    printf("\nZadaj cislo 1-3: ");
    scanf("%d", &index);
    while (index < 1 || index > 3){
        printf("\nZadaj cislo 1-3: ");
        scanf("%d", &index);
    }

    return index;
}

//hlavna funkcia, na zavolanie potrebnych funkcii vzhladom na vybranu moznost z menu hry
int main() {
    int x, y, index, hrac = 1;

    index = menu();
    if (index == 1) {
        logo();
        printf("Zvolte velkost hracej mriezky (10 10): ");
        scanf("%d %d", &x, &y);
        if (x > 20 || y > 20) {
            red();
            printf("\nNeplatna velkost hracej mriezky, max 20.\n");
            reset();
            return 0;
        } else if (x < 5 || y < 5) {
            red();
            printf("\nNeplatna velkost hracej mriezky, min 5.\n");
            reset();
            return 0;
        }
        clear();
        x += 1;
        y += 1;
        int mriezka1[x][y], mriezka2[x][y], mriezka3[x][y], mriezka4[x][y];

        genMriezka(x, y, mriezka1, mriezka2);
        genMriezka(x, y, mriezka3, mriezka4);
        genLode(x, y, mriezka1, hrac);
        hrac = 2;
        genLode(x, y, mriezka3, hrac);
        hra(x, y, mriezka1, mriezka2, mriezka3, mriezka4);
        main();
    }
    else if (index == 2) {
        napoveda();
        main();
    }

    return 0;
}
