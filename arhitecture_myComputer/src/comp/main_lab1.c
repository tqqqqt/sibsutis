#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <libcomp/mySimpleComputer.h>

#define file_name "mem.txt"

static char *Error_mes_func[] = { "\n MemoryInit error.",
                                  "\n MemorySet error.",
                                  "\n MemoryGet error",
                                  "\n MemorySave error",
                                  "\n MemoryLoad error",
                                  "\n RegInit error",
                                  "\n RegSet error",
                                  "\n RegGet error"
                                  "\n CommandEncode error",
                                  "\n CommandDecode error" };

int
main ()
{
  // func
  int adr = 0, value = 0, command = 0, operand = 0, reg = 0;

  // main_func
  int number = 0, exit = 0, error_func = 0;

  while (exit == 0)
    {
      printf ("\n \n Computer function: \n 1 - memoryInit \n 2 - memorySet \n "
              "3 - memoryGet \n 4 - memorySave \n 5 - memoryLoad \n 6 - "
              "regInit \n "
              "7 - regSet \n 8 - regGet \n 9 - commandEncode \n 10 - "
              "commandDecode \n "
              "11 - Exit \n \n --> ");
      scanf ("%d", &number);
      switch (number)
        {
        case 1:
          error_func = sc_memoryInit ();
          break;
        case 2:
          printf (" Address -> ");
          scanf ("%d", &adr);
          printf (" Value -> ");
          scanf ("%d", &value);
          error_func = sc_memorySet (adr, value);
          break;
        case 3:
          printf (" Address -> ");
          scanf ("%d", &adr);
          error_func = sc_memoryGet (adr, &value);
          printf (" \nValue -> %d", value);
          break;
        case 4:
          error_func = sc_memorySave (file_name);
          break;
        case 5:
          error_func = sc_memoryLoad (file_name);
          break;
        case 6:
          error_func = sc_regInit ();
          break;
        case 7:
          printf ("\n Register -> ");
          scanf ("%d", &reg);
          printf ("\n Value -> ");
          scanf ("%d", &value);
          error_func = sc_regSet (reg, value);
          break;
        case 8:
          printf ("\n Register -> ");
          scanf ("%d", &reg);
          error_func = sc_regGet (reg, &value);
          printf ("\n %d register - %d", reg, value);
          break;
        case 9:
          printf ("\n Command -> ");
          scanf ("%d", &command);
          printf ("\n Operand -> ");
          scanf ("%d", &operand);
          error_func = sc_commandEncode (command, operand, &value);
          printf ("\n Value - %d", value);
          break;
        case 10:
          error_func = sc_commandDecode (value, &command, &operand);
          printf ("\n Command - %d \n Operand - %d ", command, operand);
          break;
        case 11:
          printf (" \n \n End of work \n \n");
          exit += 2;
          break;
        default:
          printf ("\n Unknown key. Try again. \n \n");
          break;
        }
      if (error_func > 1)
        {
          printf ("\n %s \n", Error_mes_func[error_func - 1]);
          exit += 2;
        }
    }
}
