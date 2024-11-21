#include <libcomp/ALU.h>

int
ALU (int command, int operand)
{
  int value;
  if (command == 0x30)
    {
      if (sc_memoryGet (operand, &value))
        {
          sc_regSet (4, 1);
          return -1;
        }
      if (add (value))
        {
          return -1;
        }
    }
  else if (command == 0x31)
    {
      if (sc_memoryGet (operand, &value))
        {
          sc_regSet (4, 1);
          return -1;
        }
      if (sub (value))
        {
          return -1;
        }
    }
  else if (command == 0x32)
    {
      if (sc_memoryGet (operand, &value))
        {
          sc_regSet (4, 1);
          return -1;
        }
      if (divv (value))
        {
          return -1;
        }
    }
  else if (command == 0x33)
    {
      if (sc_memoryGet (operand, &value))
        {
          sc_regSet (4, 1);
          return -1;
        }
      if (mul (value))
        {
          return -1;
        }
    }
  return 0;
}

int
add (int value)
{
  int tempAcc, tempValue, res;
  tempAcc = ac & 0x3FFF;
  if (ac & 0x4000)
    {
      tempAcc *= -1;
    }
  tempValue = value & 0x3FFF;
  if (tempValue & 0x4000)
    {
      tempValue *= -1;
    }
  res = tempAcc + tempValue;
  if (res < 0)
    {
      res *= -1;
      res |= 0x4000;
    }
  ac = res & 0x7FFF;
  return 0;
}

int
sub (int value)
{
  int tempAcc, tempValue, res;
  tempAcc = ac & 0x3FFF;
  if (ac & 0x4000)
    {
      tempAcc *= -1;
    }
  tempValue = value & 0x3FFF;
  if (value & 0x4000)
    {
      tempValue *= -1;
    }
  res = tempAcc - tempValue;
  if (res < 0)
    {
      res *= -1;
      res |= 0x4000;
    }
  ac = res & 0x7FFF;
  return 0;
}

int
divv (int value)
{
  int tempAcc, tempValue, res;
  if (value == 0)
    {
      sc_regSet (2, 1);
      return -1;
    }
  tempAcc = ac & 0x3FFF;
  if (ac & 0x4000)
    {
      tempAcc *= -1;
    }
  tempValue = value & 0x3FFF;
  if (value & 0x4000)
    {
      tempValue *= -1;
    }
  res = tempAcc / tempValue;
  if (res < 0)
    {
      res *= -1;
      res |= 0x4000;
    }
  ac = res & 0x7FFF;
  return 0;
}

int
mul (int value)
{
  int tempAcc, tempValue, res;
  tempAcc = ac & 0x3FFF;
  if (ac & 0x4000)
    {
      tempAcc *= -1;
    }
  tempValue = value & 0x3FFF;
  if (value & 0x4000)
    {
      tempValue *= -1;
    }
  res = tempAcc * tempValue;
  if (res < 0)
    {
      res *= -1;
      res |= 0x4000;
    }
  ac = res & 0x7FFF;
  return 0;
}
