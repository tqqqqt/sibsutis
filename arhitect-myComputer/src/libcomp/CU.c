#include <libcomp/CU.h>

int
CU ()
{
  int val = 0, com = 0, oper = 0;
  int tempValue = 0;
  sc_memoryGet (ins_count, &val);
  if (sc_commandDecode (val & 0x3FFF, &com, &oper))
    {
      sc_regSet (16, 1);
      sc_regSet (8, 1);
      sc_regSet (1, 1);
      alarm (0);
      return -1;
    }
  if (com == 0x10)
    {
      if (readVvod (oper))
        return -1;
    }
  else if (com == 0x11)
    {
      if (writeMemoryValue (oper))
        return -1;
    }
  else if (com == 0x20)
    {
      if (sc_memoryGet (oper, &tempValue))
        {
          sc_regSet (16, 1);
          return -1;
        }
      ac = tempValue;
    }
  else if (com == 0x21)
    {
      if (oper < 0 || oper > 99)
        {
          sc_regSet (4, 1);
          return -1;
        }
      if (sc_memorySet (oper, ac))
        {
          return -1;
        }
    }
  else if (com == 0x30)
    {
      ALU (com, oper);
    }
  else if (com == 0x31)
    {
      ALU (com, oper);
    }
  else if (com == 0x32)
    {
      ALU (com, oper);
    }
  else if (com == 0x33)
    {
      ALU (com, oper);
    }
  else if (com == 0x40)
    {
      if (oper < 0 || oper > 99)
        {
          sc_regSet (4, 1);
          return -1;
        }
      ins_count = oper - 1;
    }
  else if (com == 0x41)
    {
      if ((ac >> 14) & 1)
        {
          if (oper < 0 || oper > 99)
            {
              sc_regSet (4, 1);
              return -1;
            }
          ins_count = oper - 1;
        }
    }
  else if (com == 0x42)
    {
      if ((ac & 0x3FFF) == 0)
        {
          if (oper < 0 || oper > 99)
            {
              sc_regSet (4, 1);
              return -1;
            }
          ins_count = oper - 1;
        }
    }
  else if (com == 0x43)
    {
      return -1;
    }
  else if (com == 0x52)
    {
      ALU (com, oper);
    }
  else
    {
      sc_regSet (1, 1);
      sc_regSet (2, 1);
      sc_regSet (4, 1);
      sc_regSet (8, 1);
      sc_regSet (16, 1);
      return -1;
    }
  return 0;
}

int
readVvod (int oper)
{
  char vvvod[10] = { 0 };
  int vvod;
  rk_mytermrestore ();
  mt_gotoXY (23, 14);
  write (0, " --> ", strlen (" --> "));
  read (0, vvvod, sizeof (vvod));
  fflush (0);
  rk_mytermregime (1, 30, 0, 1, 1);
  if (vvvod[0] != '+' && vvvod[0] != '-')
    {
      return -1;
    }
  vvod = (int)strtol (&vvvod[1], NULL, 16);
  if (vvod > 0x3FFF)
    {
      return -1;
    }
  if (vvvod[0] == '-')
    {
      vvod = vvod | 0x4000;
    }
  sc_memorySet (oper, vvod);
  return 0;
}

int
writeMemoryValue (int operand)
{
  int value, command;
  char buf[6];
  if (sc_memoryGet (operand, &value)
      || sc_commandDecode (value & 0x3FFF, &command, &operand))
    {
      sc_regSet (16, 1);
      return -1;
    }
  size_t need = snprintf (NULL, 0, "%c%02X%02X", (value & 0x4000) ? '-' : '+',
                          command, operand);
  snprintf (buf, 6, "%c%02X%02X", (value & 0x4000) ? '-' : '+', command,
            operand);
  mt_gotoXY (23, 14);
  write (1, buf, need);
  getchar ();
  return 0;
}
