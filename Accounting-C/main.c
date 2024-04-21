#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

typedef struct item
{
    char *data, *categorie;
    int suma;
}Item;

typedef struct intrari
{
    int nr_iteme;
    Item *intrare;
}Intrare;

typedef struct iesire
{
    int nr_iteme;
    Item *iesire;
}Iesire;

Intrare lista_intrari;
Iesire lista_iesiri;

void citire_liste ()
{
    FILE *fintr, *fiesr;
    fintr = fopen ("intrari.txt", "r");
    fiesr = fopen ("iesiri.txt", "r");
    char *dateintrare = (char*) malloc (50);
    while (fgets(dateintrare, 50, fintr)!= NULL)
    {
        char *p;
        Item *itm_tmp = (Item*) malloc (sizeof(Item));
        itm_tmp->suma = 0;
        itm_tmp->categorie = NULL;
        itm_tmp->data = NULL;

        p = strtok(dateintrare, ",");
        while (p!=NULL)
        {
            if (itm_tmp->suma == 0)
            {
                itm_tmp->suma = atoi(p);
            }
            else if (itm_tmp->data == NULL)
            {
                itm_tmp->data = (char*) malloc (11);
                if (p[strlen(p)-1]=='\n')
                {
                    p[strlen(p)-1] = '\0';
                }
                strcpy(itm_tmp->data, p);
            }
            else if (itm_tmp->categorie == NULL)
            {
                itm_tmp->categorie = (char*) malloc (21);
                if (p[strlen(p)-1]=='\n')
                {
                    p[strlen(p)-1] = '\0';
                }
                strcpy(itm_tmp->categorie, p);
            }
            p = strtok(0,",");
        }
        lista_intrari.nr_iteme += 1;
        lista_intrari.intrare = (Item*) realloc (lista_intrari.intrare, lista_intrari.nr_iteme*sizeof(Item));
        lista_intrari.intrare[lista_intrari.nr_iteme-1] = *itm_tmp;
    }

     while (fgets(dateintrare, 50, fiesr)!= NULL)
    {
        char *p;
        Item *itm_tmp = (Item*) malloc (sizeof(Item));
        itm_tmp->suma = 0;
        itm_tmp->categorie = NULL;
        itm_tmp->data = NULL;

        p = strtok(dateintrare, ",");
        while (p!=NULL)
        {
            if (itm_tmp->suma == 0)
            {
                itm_tmp->suma = atoi(p);
            }
            else if (itm_tmp->data == NULL)
            {
                itm_tmp->data = (char*) malloc (11);
                if (p[strlen(p)-1]=='\n')
                {
                    p[strlen(p)-1] = '\0';
                }
                strcpy(itm_tmp->data, p);
            }
            else if (itm_tmp->categorie == NULL)
            {
                itm_tmp->categorie = (char*) malloc (21);
                if (p[strlen(p)-1]=='\n')
                {
                    p[strlen(p)-1] = '\0';
                }
                strcpy(itm_tmp->categorie, p);
            }
            p = strtok(0,",");
        }
        lista_iesiri.nr_iteme += 1;
        lista_iesiri.iesire = (Item*) realloc (lista_iesiri.iesire, lista_iesiri.nr_iteme*sizeof(Item));
        lista_iesiri.iesire[lista_iesiri.nr_iteme-1] = *itm_tmp;
    }
    fclose(fintr);
    fclose(fiesr);
}

void setColor (int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute (hStdOut, wColor);
    }
    return;

}

void meniu()
{
    int choice = -1;
    while (choice)
    {
        system("cls");
        setColor(2);
        printf ("-------------------------------------BUN VENIT IN MENIU---------------------------------------\n\n");
        setColor(7);
        printf ("--> Pentru optiunile privind intrarile (veniturile) introduceti \"1\" \n");
        printf ("--> Pentru optiunile privind iesirile (cheltuieli) introduceti \"2\" \n");
        printf ("\n\n");
        setColor(4);
        printf ("<- EXIT \"9\"\n");


        setColor(7);
        printf ("Tasta : ");
        do
        {
            scanf("%d", &choice);
            getchar();
            switch (choice)
            {
            case 1 :
                choice = intrOption();
                break;
            case 2 :
                choice = iesrOption();
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! ACEASTA COMANDA NU EXISTA !! \n\n");
                setColor(7);
            }
            printf ("Tasta : ");
        }
        while (choice != 8);
    }
}

int intrOption ()
{
    int choice  = -1;
    while (choice)
    {
        system("cls");
        setColor(2);
        printf ("-------------------------------------OPTIUNI INTRARI---------------------------------------\n\n");
        setColor(7);
        printf ("--> Pentru a vizualiza lista de intrari, introduceti \"1\"\n");
        printf ("--> Pentru a adauga in lista de intrari o pozitie noua, introduceti \"2\"\n");
        printf ("--> Pentru a sterge din lista de intrari o pozitie, introduceti \"3\"\n");
        printf ("--> Pentru a salva schimbarile facute \"4\"\n");
        printf ("\n\n");
        setColor(6);
        printf ("<- BACK \"8\"\n");
        setColor(4);
        printf ("<- EXIT \"9\"\n");

        setColor(7);
        printf ("Tasta : ");
        do
        {
            scanf("%d", &choice);
            getchar();
            switch (choice)
            {
            case 1 :
                choice = viewIntr();
                break;
            case 2 :
                choice = addIntr();
                break;
            case 3 :
                choice = deleteIntr();
                break;
            case 4 :
                choice = saveChanges ();
                setColor(2);
                printf ("Schimbarile au fost salvate cu succes !!\n\n");
                setColor(7);
                break;
            case 8 :
                return 8;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
            printf ("Tasta : ");
        }
        while (choice != 8);
    }
}

int iesrOption ()
{
    int choice = -1;
    while (choice)
    {
        system("cls");
        setColor(2);
        printf ("-------------------------------------OPTIUNI IESIRI---------------------------------------\n\n");
        setColor(7);
        printf ("--> Pentru a vizualiza lista de iesiri, introduceti \"1\"\n");
        printf ("--> Pentru a adauga in lista de iesiri o pozitie noua, introduceti \"2\"\n");
        printf ("--> Pentru a sterge din lista de iesiri o pozitie, introduceti \"3\"\n");
        printf ("--> Pentru a salva schimbarile facute \"4\"\n");
        printf ("\n\n");
        setColor(6);
        printf ("<- BACK \"8\"\n");
        setColor(4);
        printf ("<- EXIT \"9\"\n");

        setColor(7);
        printf ("Tasta : ");

        do
        {
            scanf("%d", &choice);
            getchar();
            switch (choice)
            {
            case 1 :
                choice = viewIesr();
                break;
            case 2 :
                choice = addIesr();
                break;
            case 3 :
                choice = deleteIesr();
                break;
            case 4 :
                choice = saveChanges ();
                setColor(2);
                printf ("Schimbarile au fost salvate cu succes !!\n\n");
                setColor(7);
                break;
            case 8 :
                return 8;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
            printf ("Tasta : ");
        }
        while (choice != 8);
    }
}

int viewIntr()
{
    system("cls");
    char **categorii = NULL;
    int nr_categorii = 0;
    for (int i = 0; i<lista_intrari.nr_iteme; i++)
    {
        int found = 0;
        for (int j = 0; j<nr_categorii; j++)
        {
            if (strcmp(categorii[j], lista_intrari.intrare[i].categorie)== 0)
            {
                found = 1;
            }
        }
        if (found == 0)
        {
            nr_categorii += 1;
            categorii = (char**) realloc (categorii, nr_categorii*sizeof(char*));
            categorii[nr_categorii-1] = (char*) malloc (40);
            strcpy(categorii[nr_categorii-1], lista_intrari.intrare[i].categorie);
        }
    }
    setColor(6);
    for (int i = 0; i<nr_categorii; i++)
       printf ("%d. %s\n", i+1, categorii[i]);
    printf("\n\n");
    printf ("<- BACK \"8\" \n");
    setColor(4);
    printf ("<- EXIT \"9\" \n");
    setColor(7);
    int ok =0;
    char *chosen_cat = (char*) malloc (40);

    while (ok == 0)
    {
        printf("Introduceti categoria : ");
        fgets (chosen_cat, 40, stdin);
        chosen_cat[strlen(chosen_cat)-1] = '\0';
        for (int i = 0; i<nr_categorii; i++)
        {
            if (strcmp(chosen_cat, categorii[i])== 0)
                ok = 1;
        }

        if (ok == 0)
        {
            switch (atoi(chosen_cat))
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
        }

    }

    system("cls");
    setColor(6);
    int nr_date = 0;
    for (int i = 0; i<lista_intrari.nr_iteme; i++)
    {
        if (strcmp(lista_intrari.intrare[i].categorie, chosen_cat) == 0)
            {
                printf ("%d. %s\n",nr_date+1,lista_intrari.intrare[i].data);
                nr_date += 1;
            }
    }
    printf("\n\n");
    printf ("<- BACK \"8\" \n");
    setColor(4);
    printf ("<- EXIT \"9\" \n");
    setColor(7);
    char *chosen_date = (char*) malloc (40);
    ok = 0;
    while (ok == 0)
    {
        printf("Introduceti data : ");
        fgets (chosen_date, 40, stdin);
        chosen_date[strlen(chosen_date)-1] = '\0';
        for (int i = 0; i<lista_intrari.nr_iteme; i++)
        {
            if (strcmp(chosen_date, lista_intrari.intrare[i].data)== 0)
                ok = 1;
        }

        if (ok == 0)
        {
            switch (atoi(chosen_date))
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
        }

    }

    system("cls");
    setColor(6);
    int nr_sums = 0;
    for (int i = 0; i<lista_intrari.nr_iteme; i++)
    {
        if (strcmp(lista_intrari.intrare[i].categorie, chosen_cat) == 0)
            if (strcmp(lista_intrari.intrare[i].data, chosen_date) == 0)
            {
                printf ("%d. %d\n",nr_sums+1,lista_intrari.intrare[i].suma);
                nr_sums += 1;
            }
    }
    printf("\n\n");
    printf ("<- BACK \"8\" \n");
    setColor(4);
    printf ("<- EXIT \"9\" \n");
    setColor(7);
    ok = 1;
    while (ok)
    {
        printf("Tasta : ");
        scanf("%d", &ok);
        getchar();
            switch (ok)
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
    }
}

int viewIesr ()
{
    system("cls");
    char **categorii = NULL;
    int nr_categorii = 0;
    for (int i = 0; i<lista_iesiri.nr_iteme; i++)
    {
        int found = 0;
        for (int j = 0; j<nr_categorii; j++)
        {
            if (strcmp(categorii[j], lista_iesiri.iesire[i].categorie)== 0)
            {
                found = 1;
            }
        }
        if (found == 0)
        {
            nr_categorii += 1;
            categorii = (char**) realloc (categorii, nr_categorii*sizeof(char*));
            categorii[nr_categorii-1] = (char*) malloc (40);
            strcpy(categorii[nr_categorii-1], lista_iesiri.iesire[i].categorie);
        }
    }
    setColor(6);
    for (int i = 0; i<nr_categorii; i++)
       printf ("%d. %s\n", i+1, categorii[i]);
    printf("\n\n");
    printf ("<- BACK \"8\" \n");
    setColor(4);
    printf ("<- EXIT \"9\" \n");
    setColor(7);
    int ok =0;
    char *chosen_cat = (char*) malloc (40);

    while (ok == 0)
    {
        printf("Introduceti categoria : ");
        fgets (chosen_cat, 40, stdin);
        chosen_cat[strlen(chosen_cat)-1] = '\0';
        for (int i = 0; i<nr_categorii; i++)
        {
            if (strcmp(chosen_cat, categorii[i])== 0)
                ok = 1;
        }

        if (ok == 0)
        {
            switch (atoi(chosen_cat))
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
        }

    }

    system("cls");
    setColor(6);
    for (int i = 0; i<lista_iesiri.nr_iteme; i++)
    {
        if (strcmp(lista_iesiri.iesire[i].categorie, chosen_cat) == 0)
            printf ("%d. %s\n",i+1,lista_iesiri.iesire[i].data);
    }
    printf("\n\n");
    printf ("<- BACK \"8\" \n");
    setColor(4);
    printf ("<- EXIT \"9\" \n");
    setColor(7);
    char *chosen_date = (char*) malloc (40);
    ok = 0;
    while (ok == 0)
    {
        printf("Introduceti data : ");
        fgets (chosen_date, 40, stdin);
        chosen_date[strlen(chosen_date)-1] = '\0';
        for (int i = 0; i<lista_iesiri.nr_iteme; i++)
        {
            if (strcmp(chosen_date, lista_iesiri.iesire[i].data)== 0)
                ok = 1;
        }

        if (ok == 0)
        {
            switch (atoi(chosen_date))
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
        }

    }

    system("cls");
    setColor(6);
    for (int i = 0; i<lista_iesiri.nr_iteme; i++)
    {
        if (strcmp(lista_iesiri.iesire[i].categorie, chosen_cat) == 0)
            if (strcmp(lista_iesiri.iesire[i].data, chosen_date) == 0)
                printf ("%d. %d\n",i+1,lista_iesiri.iesire[i].suma);
    }
    printf("\n\n");
    printf ("<- BACK \"8\" \n");
    setColor(4);
    printf ("<- EXIT \"9\" \n");
    setColor(7);
    ok = 1;
    while (ok)
    {
        printf("Tasta : ");
        scanf("%d", &ok);
        getchar();
            switch (ok)
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
    }
}

int addIesr ()
{

    system("cls");
    setColor(2);
    printf("==========Bun venit in meniul de adaugare iesiri==========\n\n");
    setColor(7);
    printf("Introduceti categoria pentru care adaugati o iesire(max. 40 caractere) : ");
    char* chosen_cat = (char*) malloc (40);
    fgets(chosen_cat, 40, stdin);
    chosen_cat[strlen(chosen_cat)-1] = '\0';
    for (int i =0 ;i<strlen(chosen_cat); i++)
    {
        chosen_cat[i] = tolower(chosen_cat[i]);
    }
    printf("\n");

    char *luna, *ziua, *anul;
    printf ("Introduceti data iesirii :\n");
    printf("Anul (min. anul 1950) : ");
    anul = (char*) malloc (10);
    int ok = 0;
    while (ok == 0)
    {
        fgets(anul, 10, stdin);
        anul[strlen(anul)-1] = '\0';
        if (strlen(anul) <= 0 || strlen(anul) > 4)
        {
            setColor(4);
            printf("Anul introdus este incorect !! \n\n");
            setColor(7);
        }
        else if (atoi(anul) < 1950 || atoi(anul) > 2023)
        {
            setColor(4);
            printf("Anul introdus este incorect !! \n\n");
            setColor(7);
        }
        else
            ok = 1;

        if (ok == 0)
            printf ("Reintroduceti anul : ");
    }


    printf ("Luna : ");
    luna = (char*) malloc (40);
    ok = 0;
    while (ok == 0)
    {
        fgets (luna,10,stdin);
        luna[strlen(luna)-1] = '\0';
        if (strlen(luna) <= 0 || strlen(luna)>2)
        {
            setColor(4);
            printf("Luna introdusa este incorecta !! \n\n");
            setColor(7);
        }
        else if (atoi(luna) < 1 || atoi(luna) > 12)
        {
            setColor(4);
            printf("Luna introdusa este incorecta !! \n\n");
            setColor(7);
        }
        else
        ok = 1;

        if (ok == 0)
            printf ("Reintroduceti luna : ");
    }

    printf ("Ziua : ");
    ziua = (char*) malloc (10);
    ok = 0;
    while (ok == 0)
    {
        fgets (ziua, 10, stdin);
        ziua[strlen(ziua)-1] = '\0';
        if (strlen(ziua) <= 0 || strlen(ziua)>2)
        {
            setColor(4);
            printf("Ziua introdusa este incorecta !! \n\n");
            setColor(7);
        }
        else
        {
            if (atoi(luna) == 1 || atoi(luna) == 3 || atoi(luna) == 5 ||
            atoi(luna) == 7 || atoi(luna) == 8 || atoi(luna) == 10 || atoi(luna) == 12)
            {
                if (atoi(ziua) > 31 || atoi(ziua) < 1)
                {
                    setColor(4);
                    printf("Ziua introdusa este incorecta !! \n\n");
                    setColor(7);
                }
                else
                {
                    ok = 1;
                }
            }

            if (atoi(luna) == 2 || atoi(luna) == 4 || atoi(luna) == 6 ||
            atoi(luna) == 9 || atoi(luna) == 11)
            {
                if (atoi(luna) == 2)
                {
                    if (atoi(anul)%4 == 0)
                    {
                        if (atoi(ziua) > 29 || atoi(ziua) < 1)
                        {
                            setColor(4);
                            printf("Ziua introdusa este incorecta !! \n\n");
                            setColor(7);
                        }
                        else
                        {
                            ok = 1;
                        }
                    }
                    else
                    {
                        if (atoi(ziua) > 28 || atoi(ziua) < 1)
                        {
                            setColor(4);
                            printf("Ziua introdusa este incorecta !! \n\n");
                            setColor(7);
                        }
                        else
                        {
                            ok = 1;
                        }
                    }
                }
                else if (atoi(ziua) > 30 || atoi(ziua) < 1)
                {
                    setColor(4);
                    printf("Ziua introdusa este incorecta !! \n\n");
                    setColor(7);
                }
                else
                {
                    ok = 1;
                }
            }
        }
        if (ok == 0)
            printf ("Reintroduceti ziua : ");
    }

    char* chosen_date = (char*) malloc (30);
    strcpy(chosen_date,ziua);
    strcat(chosen_date,"/");
    strcat(chosen_date,luna);
    strcat(chosen_date,"/");
    strcat(chosen_date,anul);

    int chosen_suma;
    printf ("\n");
    printf ("Introduceti suma iesirii :");
    ok = 0;
    while (ok == 0)
    {
        scanf("%d", &chosen_suma);
        getchar();
        if (chosen_suma == 0)
        {
            setColor(4);
            printf("Nu poate sa existe intrare cu suma 0 !! \n\n");
            setColor(7);
        }
        else
            ok = 1;

        if (ok == 0)
        {
            printf ("Reintroduceti suma : ");
        }
    }

    Item itm_temp;
    itm_temp.categorie = (char*) malloc (40);
    itm_temp.data = (char*) malloc (30);
    strcpy (itm_temp.categorie, chosen_cat);
    strcpy (itm_temp.data, chosen_date);
    itm_temp.suma = chosen_suma;

    lista_iesiri.nr_iteme += 1;
    lista_iesiri.iesire = (Item*) realloc (lista_iesiri.iesire, lista_iesiri.nr_iteme*sizeof(Item));
    lista_iesiri.iesire[lista_iesiri.nr_iteme-1] = itm_temp;
    setColor(2);
    printf ("! Iesirea a fost inregistrata cu succes !");

    setColor(6);
    printf("\n\n");
    printf ("<- BACK \"8\" \n");
    setColor(4);
    printf ("<- EXIT \"9\" \n");
    setColor(7);
    ok = 1;
    while (ok)
    {
        printf("Tasta : ");
        scanf("%d", &ok);
        getchar();
            switch (ok)
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
    }
}

int addIntr ()
{
    system("cls");
    setColor(2);
    printf("==========Bun venit in meniul de adaugare intrare==========\n\n");
    setColor(7);
    printf("Introduceti categoria pentru care adaugati o intrare(max. 40 caractere) : ");
    char* chosen_cat = (char*) malloc (40);
    fgets(chosen_cat, 40, stdin);
    chosen_cat[strlen(chosen_cat)-1] = '\0';
    for (int i =0 ;i<strlen(chosen_cat); i++)
    {
        chosen_cat[i] = tolower(chosen_cat[i]);
    }
    printf("\n");

    char *luna, *ziua, *anul;
    printf ("Introduceti data iesiri :\n");
    printf("Anul (min. anul 1950) : ");
    anul = (char*) malloc (10);
    int ok = 0;
    while (ok == 0)
    {
        fgets(anul, 10, stdin);
        anul[strlen(anul)-1] = '\0';
        if (strlen(anul) <= 0 || strlen(anul) > 4)
        {
            setColor(4);
            printf("Anul introdus este incorect !! \n\n");
            setColor(7);
        }
        else if (atoi(anul) < 1950 || atoi(anul) > 2023)
        {
            setColor(4);
            printf("Anul introdus este incorect !! \n\n");
            setColor(7);
        }
        else
            ok = 1;

        if (ok == 0)
            printf ("Reintroduceti anul : ");
    }


    printf ("Luna : ");
    luna = (char*) malloc (40);
    ok = 0;
    while (ok == 0)
    {
        fgets (luna,10,stdin);
        luna[strlen(luna)-1] = '\0';
        if (strlen(luna) <= 0 || strlen(luna)>2)
        {
            setColor(4);
            printf("Luna introdusa este incorecta !! \n\n");
            setColor(7);
        }
        else if (atoi(luna) < 1 || atoi(luna) > 12)
        {
            setColor(4);
            printf("Luna introdusa este incorecta !! \n\n");
            setColor(7);
        }
        else
        ok = 1;

        if (ok == 0)
            printf ("Reintroduceti luna : ");
    }

    printf ("Ziua : ");
    ziua = (char*) malloc (10);
    ok = 0;
    while (ok == 0)
    {
        fgets (ziua, 10, stdin);
        ziua[strlen(ziua)-1] = '\0';
        if (strlen(ziua) <= 0 || strlen(ziua)>2)
        {
            setColor(4);
            printf("Ziua introdusa este incorecta !! \n\n");
            setColor(7);
        }
        else
        {
            if (atoi(luna) == 1 || atoi(luna) == 3 || atoi(luna) == 5 ||
            atoi(luna) == 7 || atoi(luna) == 8 || atoi(luna) == 10 || atoi(luna) == 12)
            {
                if (atoi(ziua) > 31 || atoi(ziua) < 1)
                {
                    setColor(4);
                    printf("Ziua introdusa este incorecta !! \n\n");
                    setColor(7);
                }
                else
                {
                    ok = 1;
                }
            }

            if (atoi(luna) == 2 || atoi(luna) == 4 || atoi(luna) == 6 ||
            atoi(luna) == 9 || atoi(luna) == 11)
            {
                if (atoi(luna) == 2)
                {
                    if (atoi(anul)%4 == 0)
                    {
                        if (atoi(ziua) > 29 || atoi(ziua) < 1)
                        {
                            setColor(4);
                            printf("Ziua introdusa este incorecta !! \n\n");
                            setColor(7);
                        }
                        else
                        {
                            ok = 1;
                        }
                    }
                    else
                    {
                        if (atoi(ziua) > 28 || atoi(ziua) < 1)
                        {
                            setColor(4);
                            printf("Ziua introdusa este incorecta !! \n\n");
                            setColor(7);
                        }
                        else
                        {
                            ok = 1;
                        }
                    }
                }
                else if (atoi(ziua) > 30 || atoi(ziua) < 1)
                {
                    setColor(4);
                    printf("Ziua introdusa este incorecta !! \n\n");
                    setColor(7);
                }
                else
                {
                    ok = 1;
                }
            }
        }
        if (ok == 0)
            printf ("Reintroduceti ziua : ");
    }

    char* chosen_date = (char*) malloc (30);
    strcpy(chosen_date,ziua);
    strcat(chosen_date,"/");
    strcat(chosen_date,luna);
    strcat(chosen_date,"/");
    strcat(chosen_date,anul);

    int chosen_suma;
    printf ("\n");
    printf ("Introduceti suma intrarii :");
    ok = 0;
    while (ok == 0)
    {
        scanf("%d", &chosen_suma);
        getchar();
        if (chosen_suma == 0)
        {
            setColor(4);
            printf("Nu poate sa existe intrare cu suma 0 !! \n\n");
            setColor(7);
        }
        else
            ok = 1;

        if (ok == 0)
        {
            printf ("Reintroduceti suma : ");
        }
    }

    Item itm_temp;
    itm_temp.categorie = (char*) malloc (40);
    itm_temp.data = (char*) malloc (30);
    strcpy (itm_temp.categorie, chosen_cat);
    strcpy (itm_temp.data, chosen_date);
    itm_temp.suma = chosen_suma;

    lista_intrari.nr_iteme += 1;
    lista_intrari.intrare = (Item*) realloc (lista_intrari.intrare, lista_intrari.nr_iteme*sizeof(Item));
    lista_intrari.intrare[lista_intrari.nr_iteme-1] = itm_temp;
    setColor(2);
    printf ("! Intrarea a fost inregistrata cu succes !");

    setColor(6);
    printf("\n\n");
    printf ("<- BACK \"8\" \n");
    setColor(4);
    printf ("<- EXIT \"9\" \n");
    setColor(7);
    ok = 1;
    while (ok)
    {
        printf("Tasta : ");
        scanf("%d", &ok);
        getchar();
            switch (ok)
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
    }
}

int deleteIntr()
{
    system("cls");
    char **categorii = NULL;
    int nr_categorii = 0;
    for (int i = 0; i<lista_intrari.nr_iteme; i++)
    {
        int found = 0;
        for (int j = 0; j<nr_categorii; j++)
        {
            if (strcmp(categorii[j], lista_intrari.intrare[i].categorie)== 0)
            {
                found = 1;
            }
        }
        if (found == 0)
        {
            nr_categorii += 1;
            categorii = (char**) realloc (categorii, nr_categorii*sizeof(char*));
            categorii[nr_categorii-1] = (char*) malloc (40);
            strcpy(categorii[nr_categorii-1], lista_intrari.intrare[i].categorie);
        }
    }
    setColor(6);
    for (int i = 0; i<nr_categorii; i++)
       printf ("%d. %s\n", i+1, categorii[i]);
    printf("\n\n");
    printf ("<- BACK \"8\" \n");
    setColor(4);
    printf ("<- EXIT \"9\" \n");
    setColor(7);
    int ok =0;
    char *chosen_cat = (char*) malloc (40);

    while (ok == 0)
    {
        printf("Introduceti categoria : ");
        fgets (chosen_cat, 40, stdin);
        chosen_cat[strlen(chosen_cat)-1] = '\0';
        for (int i = 0; i<nr_categorii; i++)
        {
            if (strcmp(chosen_cat, categorii[i])== 0)
                ok = 1;
        }

        if (ok == 0)
        {
            switch (atoi(chosen_cat))
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
        }

    }

    system("cls");
    setColor(6);
    int nr_date = 0;
    for (int i = 0; i<lista_intrari.nr_iteme; i++)
    {
        if (strcmp(lista_intrari.intrare[i].categorie, chosen_cat) == 0)
            {
                printf ("%d. %s\n",nr_date+1,lista_intrari.intrare[i].data);
                nr_date += 1;
            }
    }
    printf("\n\n");
    printf ("<- BACK \"8\" \n");
    setColor(4);
    printf ("<- EXIT \"9\" \n");
    setColor(7);
    char *chosen_date = (char*) malloc (40);
    ok = 0;
    while (ok == 0)
    {
        printf("Introduceti data : ");
        fgets (chosen_date, 40, stdin);
        chosen_date[strlen(chosen_date)-1] = '\0';
        for (int i = 0; i<lista_intrari.nr_iteme; i++)
        {
            if (strcmp(chosen_date, lista_intrari.intrare[i].data)== 0)
                ok = 1;
        }

        if (ok == 0)
        {
            switch (atoi(chosen_date))
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
        }

    }

    system("cls");
    setColor(6);
    int nr_sums = 0;
    for (int i = 0; i<lista_intrari.nr_iteme; i++)
    {
        if (strcmp(lista_intrari.intrare[i].categorie, chosen_cat) == 0)
            if (strcmp(lista_intrari.intrare[i].data, chosen_date) == 0)
            {
                printf ("%d. %d\n",nr_sums+1,lista_intrari.intrare[i].suma);
                nr_sums += 1;
            }
    }

    int chosen_sum = 0;
    ok = 0;
    while (ok == 0)
    {
        printf("Introduceti suma : ");
        scanf("%d", &chosen_sum);
        getchar();

        for (int i = 0; i<lista_intrari.nr_iteme; i++)
        {
        if (strcmp(lista_intrari.intrare[i].categorie, chosen_cat) == 0)
            if (strcmp(lista_intrari.intrare[i].data, chosen_date) == 0)
                if (lista_intrari.intrare[i].suma == chosen_sum)
                ok = 1;
        }

        if (ok == 0)
        {
            switch (chosen_sum)
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
        }
    }

    int sters = 0;
    int nr_iteme_temp = 0;
    Item *intrare_temp = NULL;

    for (int i = 0; i<lista_intrari.nr_iteme; i++)
    {
        if (strcmp(lista_intrari.intrare[i].categorie, chosen_cat) == 0)
        {
            if (strcmp(lista_intrari.intrare[i].data, chosen_date) == 0)
            {
                if (lista_intrari.intrare[i].suma == chosen_sum)
                {
                    if (sters == 0)
                    sters = 1;
                    else
                    {
                        nr_iteme_temp += 1;
                        intrare_temp = (Item*) realloc (intrare_temp,nr_iteme_temp*sizeof(Item));
                        intrare_temp[nr_iteme_temp-1]  = lista_intrari.intrare[i];
                    }
                }
                else
                {
                    nr_iteme_temp += 1;
                    intrare_temp  = (Item*) realloc (intrare_temp,nr_iteme_temp*sizeof(Item));
                    intrare_temp[nr_iteme_temp-1]  = lista_intrari.intrare[i];
                }
            }
            else
            {
                nr_iteme_temp += 1;
                intrare_temp  = (Item*) realloc (intrare_temp,nr_iteme_temp*sizeof(Item));
                intrare_temp[nr_iteme_temp-1]  = lista_intrari.intrare[i];
            }

        }
        else
        {
            nr_iteme_temp += 1;
            intrare_temp = (Item*) realloc (intrare_temp,nr_iteme_temp*sizeof(Item));
            intrare_temp[nr_iteme_temp-1]  = lista_intrari.intrare[i];
        }
    }

    lista_intrari.intrare = intrare_temp;
    lista_intrari.nr_iteme = nr_iteme_temp;
    setColor(2);
    printf (" ! Stergerea a fost inregistrata cu succes ! ");
    setColor(6);
    printf("\n\n");
    printf ("<- BACK \"8\" \n");
    setColor(4);
    printf ("<- EXIT \"9\" \n");
    setColor(7);
    ok = 1;
    while (ok)
    {
        printf("Tasta : ");
        scanf("%d", &ok);
        getchar();
            switch (ok)
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
    }

}

int deleteIesr()
{
    system("cls");
    char **categorii = NULL;
    int nr_categorii = 0;
    for (int i = 0; i<lista_iesiri.nr_iteme; i++)
    {
        int found = 0;
        for (int j = 0; j<nr_categorii; j++)
        {
            if (strcmp(categorii[j], lista_iesiri.iesire[i].categorie)== 0)
            {
                found = 1;
            }
        }
        if (found == 0)
        {
            nr_categorii += 1;
            categorii = (char**) realloc (categorii, nr_categorii*sizeof(char*));
            categorii[nr_categorii-1] = (char*) malloc (40);
            strcpy(categorii[nr_categorii-1], lista_iesiri.iesire[i].categorie);
        }
    }
    setColor(6);
    for (int i = 0; i<nr_categorii; i++)
       printf ("%d. %s\n", i+1, categorii[i]);
    printf("\n\n");
    printf ("<- BACK \"8\" \n");
    setColor(4);
    printf ("<- EXIT \"9\" \n");
    setColor(7);
    int ok =0;
    char *chosen_cat = (char*) malloc (40);

    while (ok == 0)
    {
        printf("Introduceti categoria : ");
        fgets (chosen_cat, 40, stdin);
        chosen_cat[strlen(chosen_cat)-1] = '\0';
        for (int i = 0; i<nr_categorii; i++)
        {
            if (strcmp(chosen_cat, categorii[i])== 0)
                ok = 1;
        }

        if (ok == 0)
        {
            switch (atoi(chosen_cat))
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
        }

    }

    system("cls");
    setColor(6);
    int nr_date = 0;
    for (int i = 0; i<lista_iesiri.nr_iteme; i++)
    {
        if (strcmp(lista_iesiri.iesire[i].categorie, chosen_cat) == 0)
            {
                printf ("%d. %s\n",nr_date+1,lista_iesiri.iesire[i].data);
                nr_date += 1;
            }
    }
    printf("\n\n");
    printf ("<- BACK \"8\" \n");
    setColor(4);
    printf ("<- EXIT \"9\" \n");
    setColor(7);
    char *chosen_date = (char*) malloc (40);
    ok = 0;
    while (ok == 0)
    {
        printf("Introduceti data : ");
        fgets (chosen_date, 40, stdin);
        chosen_date[strlen(chosen_date)-1] = '\0';
        for (int i = 0; i<lista_iesiri.nr_iteme; i++)
        {
            if (strcmp(chosen_date, lista_iesiri.iesire[i].data)== 0)
                ok = 1;
        }

        if (ok == 0)
        {
            switch (atoi(chosen_date))
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
        }

    }

    system("cls");
    setColor(6);
    int nr_sums = 0;
    for (int i = 0; i<lista_iesiri.nr_iteme; i++)
    {
        if (strcmp(lista_iesiri.iesire[i].categorie, chosen_cat) == 0)
            if (strcmp(lista_iesiri.iesire[i].data, chosen_date) == 0)
            {
                printf ("%d. %d\n",nr_sums+1,lista_iesiri.iesire[i].suma);
                nr_sums += 1;
            }
    }

    int chosen_sum = 0;
    ok = 0;
    while (ok == 0)
    {
        printf("Introduceti suma : ");
        scanf("%d", &chosen_sum);
        getchar();

        for (int i = 0; i<lista_iesiri.nr_iteme; i++)
        {
        if (strcmp(lista_iesiri.iesire[i].categorie, chosen_cat) == 0)
            if (strcmp(lista_iesiri.iesire[i].data, chosen_date) == 0)
                if (lista_iesiri.iesire[i].suma == chosen_sum)
                ok = 1;
        }

        if (ok == 0)
        {
            switch (chosen_sum)
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
        }
    }

    int sters = 0;
    int nr_iteme_temp = 0;
    Item *intrare_temp = NULL;

    for (int i = 0; i<lista_iesiri.nr_iteme; i++)
    {
        if (strcmp(lista_iesiri.iesire[i].categorie, chosen_cat) == 0)
        {
            if (strcmp(lista_iesiri.iesire[i].data, chosen_date) == 0)
            {
                if (lista_iesiri.iesire[i].suma == chosen_sum)
                {
                    if (sters == 0)
                    sters = 1;
                    else
                    {
                        nr_iteme_temp += 1;
                        intrare_temp = (Item*) realloc (intrare_temp,nr_iteme_temp*sizeof(Item));
                        intrare_temp[nr_iteme_temp-1]  = lista_iesiri.iesire[i];
                    }
                }
                else
                {
                    nr_iteme_temp += 1;
                    intrare_temp  = (Item*) realloc (intrare_temp,nr_iteme_temp*sizeof(Item));
                    intrare_temp[nr_iteme_temp-1]  = lista_iesiri.iesire[i];
                }
            }
            else
            {
                nr_iteme_temp += 1;
                intrare_temp  = (Item*) realloc (intrare_temp,nr_iteme_temp*sizeof(Item));
                intrare_temp[nr_iteme_temp-1]  = lista_iesiri.iesire[i];
            }

        }
        else
        {
            nr_iteme_temp += 1;
            intrare_temp = (Item*) realloc (intrare_temp,nr_iteme_temp*sizeof(Item));
            intrare_temp[nr_iteme_temp-1]  = lista_iesiri.iesire[i];
        }
    }

    lista_iesiri.iesire = intrare_temp;
    lista_iesiri.nr_iteme = nr_iteme_temp;
    setColor(2);
    printf (" ! Stergerea a fost inregistrata cu succes ! ");
    setColor(6);
    printf("\n\n");
    printf ("<- BACK \"8\" \n");
    setColor(4);
    printf ("<- EXIT \"9\" \n");
    setColor(7);
    ok = 1;
    while (ok)
    {
        printf("Tasta : ");
        scanf("%d", &ok);
        getchar();
            switch (ok)
            {
            case 8 :
                return 8;
                break;
            case 9 :
                exit(0);
            default :
                setColor(4);
                printf ("  !! OPTIUNEA ALEASA NU EXISTA !! \n\n");
                setColor(7);
            }
    }
}

int saveChanges()
{
    FILE *fintr;
    FILE *fiesr;
    fintr = fopen("intrari.txt", "w");
    fiesr = fopen ("iesiri.txt", "w");

    for (int i = 0; i<lista_intrari.nr_iteme; i++)
    {
        fprintf(fintr, "%d,%s,%s\n", lista_intrari.intrare[i].suma,lista_intrari.intrare[i].data,lista_intrari.intrare[i].categorie);
    }

    for (int i = 0; i<lista_iesiri.nr_iteme; i++)
    {
        fprintf(fiesr, "%d,%s,%s\n", lista_iesiri.iesire[i].suma, lista_iesiri.iesire[i].data, lista_iesiri.iesire[i].categorie);
    }
    fclose(fintr);
    fclose(fiesr);
    return 4;
}

int main()
{
    lista_intrari.nr_iteme = 0;
    lista_iesiri.nr_iteme = 0;
    citire_liste();
    meniu();

    return 0;
}
