#include <libcomp/mySimpleComputer.h>

uint16_t mas[n];
uint8_t reg_flag;
uint16_t ac = 0;
uint8_t ins_count = 0;
int selected_mas = 0;

int
sc_memoryInit ()
{
  int i = 0;
  for (i = 0; i < n; i += 1)
    mas[i] = 0;
  return 0;
}

int
sc_memorySet (int address, int value)
{
  if (address < 0 || address > 99)
    {
      return -1;
    }
  else
    {
      int sign = value < 0;
      uint16_t num = value & 0x3FFF;
      if (sign == 1)
        {
          num = -value & 0x3FFF;
          num = num | 0x4000;
        }
      else
        {
          num = value & 0x7FFF;
        }
      mas[address] = num;
      return 0;
    }
}

int
sc_memoryGet (int address, int *value)
{
  if (address < 0 || address > 99)
    {
      return -1;
    }
  else
    {
      *value = (int)mas[address];
      return 0;
    }
}

int
sc_memorySave (char *filename)
{
  FILE *file = fopen (filename, "wb");
  fwrite (mas, sizeof (uint16_t), 100, file);
  fclose (file);
  return 0;
}

int
sc_memoryLoad (char *filename)
{
  FILE *file = fopen (filename, "rb");
  if (file == NULL)
    return -1;
  else
    {
      fread (mas, sizeof (uint16_t), 100, file);
      fclose (file);
    }
  return 0;
}

int
sc_regInit (void)
{
  reg_flag = 0;
  return 0;
}

int
sc_regSet (int reggister, int value)
{
  if (reggister != 1 && reggister != 2 && reggister != 4 && reggister != 8
      && reggister != 16)
    return -1;
  if (value != 0 && value != 1)
    return -1;
  if (value == 1)
    {
      reg_flag |= reggister;
    }
  else
    reg_flag &= ~reggister;
  return 0;
}

int
sc_regGet (int reggister, int *value)
{
  if (reggister != 1 && reggister != 2 && reggister != 4 && reggister != 8
      && reggister != 16)
    return -1;
  *value = reg_flag & reggister;
  return 0;
}

int
sc_commandEncode (int command, int operand, int *value)
{
  *value = 0;
  *value |= (command & 127);
  *value = *value << 7;
  *value |= (operand & 127);
  return 0;
}

int
sc_commandDecode (int value, int *command, int *operand)
{
  if ((value >> 14) != 0)
    return -1;
  *operand = (value & 127);
  *command = ((value >> 7) & 127);
  return 0;
}
