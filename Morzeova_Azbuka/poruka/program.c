#include <string.h>
#include <stdio.h>
#include <ctype.h>

int brojac = 0;

/*
Napomone:
Duzine:
1 kratak signal
3 dug signal
1 razmak u slovu
3 razmak izmedju slova
7 razmak izmedju reci.
*/

void stampanje(char karakteri[])
{
    int i;
    FILE *vhdl;
    vhdl = fopen("../morzeova_azbuka.vhd", "a+");
    for(i=0; i<strlen(karakteri); i++)
    {
        if(karakteri[i] == '-')
        {

            fprintf(vhdl, "if( BROJAC >= %d AND BROJAC < %d) then\n\t\t LED <= '1';\nend if;\n\n", brojac, brojac+3);
            brojac=brojac+3;
        }
        else if(karakteri[i] == '.')
        {
            fprintf(vhdl, "if( BROJAC >= %d AND BROJAC < %d) then\n\t\t LED <= '1';\nend if;\n\n", brojac, brojac+1);
            brojac=brojac+1;
        }
        else if(karakteri[i] == ' ')
        {
            fprintf(vhdl, "if( BROJAC >= %d AND BROJAC < %d) then\n\t\t LED <= '0';\nend if;\n\n", brojac, brojac+7);
            brojac=brojac+7;
        }
        if(i==(strlen(karakteri)-1))
        {
            fprintf(vhdl, "if( BROJAC >= %d AND BROJAC < %d) then\n\t\t LED <= '0';\nend if;\n\n", brojac, brojac+3);
            brojac=brojac+3;
        }
        else if(i!=(strlen(karakteri)-1))
        {
            fprintf(vhdl, "if( BROJAC >= %d AND BROJAC < %d) then\n\t\t LED <= '0';\nend if;\n\n", brojac, brojac+1);
            brojac=brojac+1;
        }
    }
    fclose(vhdl);
}

void morse (char slovo)        /* print out Morse code */
{
  switch (slovo)
  {
    case '0' : stampanje("-----");
      break;
    case '1' : stampanje(".----");
      break;
    case '2' : stampanje("..---");
      break;
    case '3' : stampanje ("...--");
      break;
    case '4' : stampanje("....-");
      break;
    case '5' : stampanje(".....");
      break;
    case '6' : stampanje("-....");
      break;
    case '7' : stampanje("--...");
      break;
    case '8' : stampanje("---..");
      break;
    case '9' : stampanje("----.");
      break;
    case 'A' : stampanje(".-");
      break;
    case 'B' : stampanje("-...");
      break;
    case 'C' : stampanje("-.-.");
      break;
    case 'D' : stampanje("-..");
      break;
    case 'E' : stampanje(".");
      break;
    case 'F' : stampanje("..-.");
      break;
    case 'G' : stampanje("--.");
      break;
    case 'H' : stampanje ("....");
      break;
    case 'I' : stampanje ("..");
      break;
    case 'J' : stampanje (".---");
      break;
    case 'K' : stampanje ("-.-");
      break;
    case 'L' : stampanje (".-..");
      break;
    case 'M' : stampanje ("--");
      break;
    case 'N' : stampanje ("-.");
      break;
    case 'O' : stampanje ("---");
      break;
    case 'P' : stampanje (".--.");
      break;
    case 'Q' : stampanje ("--.-");
      break;
    case 'R' : stampanje (".-.");
      break;
    case 'S' : stampanje ("...");
      break;
    case 'T' : stampanje ("-");
      break;
    case 'U' : stampanje ("..-");
      break;
    case 'V' : stampanje ("...-");
      break;
    case 'W' : stampanje (".--");
      break;
    case 'X' : stampanje ("-..-");
      break;
    case 'Y' : stampanje ("-.--");
      break;
    case 'Z' : stampanje ("--..");
      break;
    case ' ' : stampanje (" ");
  }
}

int main()
{
    char poruka[1000], poruka_secure[1000], header_array[2000], footer_array[100], c;
    int i, j = 0;

    printf("Унесите поруку\n\t(само латинична слова и бројеви):\n");
    scanf(" %[^\n]s", &poruka);
    fflush(stdin);

    FILE *header;
    FILE *vhdl;
    FILE *footer;

    //UPIS HEADER-A
    header = fopen("header.txt", "r");
    if(header == NULL)
    {
        printf("Грешка при отварању датотеке! Проверите да ли се header.txt налази у истом фолдеру!");
        return 0;
    }
    do
    {
        c = fgetc(header);
        header_array[j++] = c;
    }
    while(c!=EOF);
    fclose(header);

    vhdl = fopen("../morzeova_azbuka.vhd", "w+");
    if(vhdl == NULL)
    {
        printf("Грешка при отварању датотеке!");
        return 0;
    }

    for(i = 0; i < j-1; i++)
    {
        fprintf(vhdl, "%c", header_array[i]);
    }
    fclose(vhdl);

    //ZAPIS LOGIKE
    for(i = 0, j = 0; i < strlen(poruka); i++)
    {
        if(isalpha(poruka[i]) || isdigit(poruka[i]) || poruka[i] == ' ')
        {
            morse(toupper(poruka[i]));
            poruka_secure[j] = poruka[i];
            j++;
        }
    }

    //UPIS FOOTER-a
    vhdl = fopen("../morzeova_azbuka.vhd", "a+");
    footer = fopen("footer.txt", "r");
    if(footer == NULL)
    {
        printf("Грешка при отварању датотеке! Проверите да ли се footer.txt налази у истом фолдеру!");
        return 0;
    }
    j = 0;
    do
    {
        c = fgetc(footer);
        footer_array[j++] = c;
    }
    while(c!=EOF);
    fclose(footer);
    fprintf(vhdl, "if( BROJAC > %d ) then\n\t\t BROJAC <= 0;\nend if;\n\n", brojac + 10); //DEO ZA PONAVLJANJE PORUKE NAKON 10 s
    for(i = 0; i < j-1; i++)
    {
        fprintf(vhdl, "%c", footer_array[i]);
    }
    fclose(vhdl);

    printf("VHDL датотека (morzeova_azbuka.vhd) је спремна. ");
    return 0;
}
