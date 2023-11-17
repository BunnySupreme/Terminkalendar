#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Uhrzeit immer 8-21 Uhr
// Dauer dynamisch, verändert sich
// abhängig von Uhrzeit
//Termin nicht länger als 22 Uhr
// z.b. bei 21 Uhr Termin, Gib eine Dauer ein (1-1)
// bei 8 Uhr wäre es (1-14)

//Ausbrechen nicht berücksichtigen
//Termine in aufsteigender Reihenfolge
// bei 'i' muss überschneidung angezeigt werden
// Das komplizierteste: alle termine anschauen, ob überschneiden
// Wenn 3 Termine, dann 2 Zeilen ausgeben

// Kollisionen ausgeben
// Zeitfenster ausgeben


/*
Es empfiehlt sich, zuerst die Enumeration und die Strukturen zu definieren,
dann die Funktion printAppointments(struct appointment *, int)
zu implementieren, zu testen und erst danach den Rest zu implementieren.
Dadurch können Sie die ausgebende Funktionen zum Debuggen benutzen
und sich anzeigen lassen, ob das Einfügen und Löschen von Terminen
funktioniert hat. Dazu können Sie vorübergehend in der Ausgabefunktion
Anpassungen vornehmen, zum Beispiel alle 10 Termine auszugeben.
*/

//keine globale Variablen

/*
Allgemein zu Eingaben:
Leerzeichen und Zeilenumbrüche sollen ignoriert werden. Wenn etwas Ungültiges eingegeben wurde,
muss Ungueltige Eingabe! ausgegeben und die Eingabeaufforderung wiederholt werden. Sie können sich
aber darauf verlassen, dass Zeichen eingegeben werden, wenn Zeichen erwartet werden und Zahlen
eingegeben werden, wenn Zahlen erwartet werden.
*/




enum types
{
    Freunde, Geschaeftlich, Pause
};


struct appointment
{
    enum types type;
    int time;
    int duration;
};

void printAppointments(struct appointment * schedule, int length);
void printInformation(struct appointment * schedule, int length);
struct appointment createAppointment();
void addAppointment(struct appointment * schedule, int * length);
void deleteAppointment(struct appointment * schedule, int * length);



int main()
{
    struct appointment schedule[10];
    int length = 0;
    char auswahl = 'x';


    do
    {
        printf("\nNeuen Termin (n), Termin loeschen (d), Termine auflisten (l), Informationen ausgeben (i), Programm beenden (x)");
        printf("\nAuswahl: ");
        scanf(" %c", &auswahl);
        switch (auswahl)
        {
            case 'n': addAppointment(schedule, &length);
            break;
            case 'l': printAppointments(schedule, length);
            break;
            case 'd': deleteAppointment(schedule, &length);
            break;
            case 'i': printInformation(schedule, length);
            break;
            case 'x': break;
            default: printf("\nUngueltige Eingabe!");
        }

    }while (auswahl != 'x');

    return 0;
}

void printAppointments(struct appointment * schedule, int length)
{

    for (int i = 0; i < length; i++)
    {

        printf("\n%d: ", i+1);
        switch(schedule[i].type)
        {
            case Geschaeftlich: printf("Geschaeftlich: ");
            break;
            case Pause: printf("Pause: ");
            break;
            case Freunde: printf("Freunde: ");
            break;
        }
        printf("%d Uhr, Dauer %dh", schedule[i].time, schedule[i].duration);
    }

}



void printInformation(struct appointment * schedule, int length)
{
     /*Die Funktion gibt Informationen über den Kalender aus. Wenn es eine Terminkollision gibt,
    wird vorgeschlagen, dass einer der beiden abgesagt werden sollte.
    */

    int kollision = 0;

    for (int i = 0; i < length; i++)
    {
        for(int j = i + 1; j < length; j++)
        {
            /*Dabei bedeutet eine Terminkollision, dass zwei nacheinander liegende Termine sich überschneiden,
            also dass das Ende des ersten Termins nach Beginn des zweiten Termins ist.
            */
            if ((schedule[i].time +  schedule[i].duration) > schedule[j].time)
            {
                printf("\nEntweder Termin %d oder Termin %d sollte abgesagt werden.", i+1, j+1);
                kollision++;
            }
        }
    }

    if (kollision <= 0)
    {
        printf("\nDer Kalender hat keine Kollisionen!");
    }

    //Danach werden Terminpaare ausgegeben, wenn beide Termine hintereinanderliegen und keine Pausen sind.
    for (int i = 0; i < length-1; i++)
    {
        if (schedule[i].type!=Pause && schedule[i+1].type!=Pause)
        {
            printf("\nZwischen Termin %d und %d wird eine Pause benoetigt.", i+1, i+2);
        }
    }

    int g = 0;
    int f = 0;
    int p = 0;

    for (int i = 0; i < length; i++)
    {
       switch (schedule[i].type)
       {
           case Freunde: f++;
           break;
           case Geschaeftlich: g++;
           break;
           case Pause: p++;
           break;
       }
    }
    printf("\nSie haben %d Geschaeftstermin(e), %d Termin(e) mit Freunden und %d Pause(n) in Ihrem Kalender.", g, f, p);
}



struct appointment createAppointment()
{
    /*
     Die Funktion fordert den Nutzer auf, den Typ, den Beginn und die
      Dauer des Termins einzugeben und prüft diese auf Validität. Wenn valide Daten
       eingegeben wurden wird der entsprechende Termin zurückgegeben. Dabei müssen Termine immer zwischen
       8 Uhr und 21 Uhr beginnen und spätestens um 22 Uhr enden. Die minimale Dauer ist eine
        Stunde und die maximale Dauer berechnet sich aus der Differenz von 22 Uhr und dem Beginn
        des Termins (zB. unten 22 - 8 = 14, also Dauer 1-14).
    */
    struct appointment newAppointment;
    char type = 'x';
    int ungueltigeEingabe = 1;
    while(ungueltigeEingabe == 1)
    {
        printf("\nGib einen Typen ein: Freunde (f), Geschaeftlich (b), Pause (p): ");
        scanf(" %c", &type);
        switch (type)
        {
            case 'f': newAppointment.type = Freunde;
            ungueltigeEingabe = 0;
            break;
            case 'b': newAppointment.type = Geschaeftlich;
            ungueltigeEingabe = 0;
            break;
            case 'p': newAppointment.type = Pause;
            ungueltigeEingabe = 0;
            break;
            default: printf("\nUngueltige Eingabe!");
        }
    }

    do
    {
        printf("\nGib eine Uhrzeit ein (8-21):");
        scanf("%d", &newAppointment.time);
        if (newAppointment.time > 21 || newAppointment.time < 8)
        {
            ungueltigeEingabe = 1;
            printf("\nUngueltige Eingabe!");
        }
        else
        {
            ungueltigeEingabe = 0;
        }
    } while(ungueltigeEingabe == 1);

    do
    {
        printf("\nGib eine Dauer ein (1-%d):", 22-(newAppointment.time));
        scanf("%d", &newAppointment.duration);
        if (newAppointment.duration < 1 || newAppointment.duration > 22-(newAppointment.time))
        {
            ungueltigeEingabe = 1;
            printf("\nUngueltige Eingabe!");
        }
        else
        {
            ungueltigeEingabe = 0;
        }
    } while(ungueltigeEingabe == 1);
    return newAppointment;
}

void addAppointment(struct appointment * schedule, int * length)
{
    if (*length >= 10)
    {
        printf("Der Kalender ist voll!");
    }
    else
    {
        schedule[*length] = createAppointment();
        int currentAppointment = *length;
        (*length)++;

        for (int i = currentAppointment-1; i >= 0; i--)
        {
            if(schedule[currentAppointment].time < schedule[i].time)
            {
                struct appointment temp = schedule[i];
                schedule[i] = schedule[currentAppointment];
                schedule[currentAppointment] = temp;
                currentAppointment = i;
            }
        }
    }
}

void deleteAppointment(struct appointment * schedule, int * length)
{
    if (*length <= 0)
    {
        printf("\nDer Kalender ist leer!");
    }
    else
    {
        int eingabe = 0;
        printAppointments(schedule, *length);
        printf("\nWelchen dieser Termine moechten Sie loeschen? (1-%d): ", *length);
        do
        {
            scanf("%d", &eingabe);
            if (eingabe < 1 || eingabe > *length)
            {
                printf("Ungueltige Eingabe!");
            }

        } while (eingabe < 1 || eingabe > *length);

        int geloescht = eingabe-1;
        int letztesAppointment = *length-1;


        for (int i = geloescht; i < letztesAppointment; i++)
        {
            schedule[i] = schedule[i+1]; //Einträge werden einfach nachgeschoben und überschrieben
        }
        (*length)--;
        printf("\nTermin %d wurde geloescht!", eingabe);
    }

}

