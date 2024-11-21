#include <libcomp/ConsoleChars.h>

void
CreateCharPlus (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 0);
        }
    }
  bc_setbigcharpos (ar, 2, 3, 1);
  bc_setbigcharpos (ar, 2, 4, 1);
  for (int i = 1; i < 7; i++)
    {
      bc_setbigcharpos (ar, 3, i, 1);
    }
  bc_setbigcharpos (ar, 4, 3, 1);
  bc_setbigcharpos (ar, 4, 4, 1);
}

void
CreateCharMin (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 0);
        }
    }
  for (int i = 1; i < 7; i++)
    {
      bc_setbigcharpos (ar, 3, i, 1);
    }
}

void
CreateCharZero (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  for (int i = 3; i < 5; i++)
    {
      bc_setbigcharpos (ar, 2, i, 0);
      bc_setbigcharpos (ar, 3, i, 0);
      bc_setbigcharpos (ar, 4, i, 0);
      bc_setbigcharpos (ar, 5, i, 0);
    }
}

void
CreateCharOne (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 0);
        }
    }
  for (int i = 2; i < 6; i++)
    {
      bc_setbigcharpos (ar, 0, i, 1);
    }
  for (int i = 1; i < 6; i++)
    {
      bc_setbigcharpos (ar, 1, i, 1);
    }
  for (int i = 0; i < 5; i++)
    {
      bc_setbigcharpos (ar, 2, i, 1);
    }
  for (int i = 3; i < 6; i++)
    {
      bc_setbigcharpos (ar, 3, i, 1);
      bc_setbigcharpos (ar, 4, i, 1);
      bc_setbigcharpos (ar, 4, i, 1);
    }
  for (int i = 0; i < 8; i++)
    {
      bc_setbigcharpos (ar, 6, i, 1);
      bc_setbigcharpos (ar, 7, i, 1);
    }
}

void
CreateCharTwo (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  for (int i = 0; i < 5; i++)
    {
      bc_setbigcharpos (ar, 2, i, 0);
    }
  for (int i = 3; i < 8; i++)
    {
      bc_setbigcharpos (ar, 5, i, 0);
    }
}

void
CreateCharThre (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  for (int i = 0; i < 5; i++)
    {
      bc_setbigcharpos (ar, 2, i, 0);
    }
  for (int i = 0; i < 5; i++)
    {
      bc_setbigcharpos (ar, 5, i, 0);
    }
}

void
CreateCharThro (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  for (int i = 0; i < 3; i++)
    {
      bc_setbigcharpos (ar, i, 3, 0);
      bc_setbigcharpos (ar, i, 4, 0);
    }
  for (int i = 7; i > 4; i--)
    {
      bc_setbigcharpos (ar, i, 0, 0);
      bc_setbigcharpos (ar, i, 1, 0);
      bc_setbigcharpos (ar, i, 2, 0);
      bc_setbigcharpos (ar, i, 3, 0);
      bc_setbigcharpos (ar, i, 4, 0);
    }
}

void
CreateCharFive (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  for (int i = 3; i < 8; i++)
    {
      bc_setbigcharpos (ar, 2, i, 0);
    }
  for (int i = 0; i < 5; i++)
    {
      bc_setbigcharpos (ar, 5, i, 0);
    }
}

void
CreateCharSix (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  for (int i = 3; i < 8; i++)
    {
      bc_setbigcharpos (ar, 2, i, 0);
    }
  bc_setbigcharpos (ar, 5, 3, 0);
  bc_setbigcharpos (ar, 5, 4, 0);
}

void
CreateCharSeve (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  bc_setbigcharpos (ar, 0, 7, 0);
  for (int i = 2; i < 5; i++)
    {
      bc_setbigcharpos (ar, i, 0, 0);
      bc_setbigcharpos (ar, i, 1, 0);
    }
  bc_setbigcharpos (ar, 2, 2, 0);
  bc_setbigcharpos (ar, 3, 2, 0);
  bc_setbigcharpos (ar, 2, 3, 0);
  for (int i = 0; i < 2; i++)
    {
      bc_setbigcharpos (ar, 6, i, 0);
      bc_setbigcharpos (ar, 7, i, 0);
    }
  for (int i = 5; i < 7; i++)
    {
      bc_setbigcharpos (ar, 6, i, 0);
      bc_setbigcharpos (ar, 7, i, 0);
    }
  bc_setbigcharpos (ar, 4, 4, 0);
  bc_setbigcharpos (ar, 4, 5, 0);
  bc_setbigcharpos (ar, 3, 5, 0);
  bc_setbigcharpos (ar, 0, 7, 0);
  for (int i = 2; i < 8; i++)
    {
      bc_setbigcharpos (ar, i, 6, 0);
      bc_setbigcharpos (ar, i, 7, 0);
    }
  bc_setbigcharpos (ar, 5, 6, 1);
}

void
CreateCharEight (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  bc_setbigcharpos (ar, 0, 0, 0);
  bc_setbigcharpos (ar, 7, 0, 0);
  bc_setbigcharpos (ar, 0, 7, 0);
  bc_setbigcharpos (ar, 7, 7, 0);
  bc_setbigcharpos (ar, 3, 0, 0);
  bc_setbigcharpos (ar, 4, 0, 0);
  bc_setbigcharpos (ar, 3, 7, 0);
  bc_setbigcharpos (ar, 4, 7, 0);
  bc_setbigcharpos (ar, 2, 3, 0);
  bc_setbigcharpos (ar, 2, 4, 0);
  bc_setbigcharpos (ar, 5, 3, 0);
  bc_setbigcharpos (ar, 5, 4, 0);
}

void
CreateCharNine (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  bc_setbigcharpos (ar, 2, 3, 0);
  bc_setbigcharpos (ar, 2, 4, 0);
  bc_setbigcharpos (ar, 5, 0, 0);
  bc_setbigcharpos (ar, 5, 1, 0);
  bc_setbigcharpos (ar, 5, 2, 0);
  bc_setbigcharpos (ar, 5, 3, 0);
  bc_setbigcharpos (ar, 5, 4, 0);
}

void
CreateCharA (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  bc_setbigcharpos (ar, 0, 0, 0);
  bc_setbigcharpos (ar, 0, 7, 0);
  bc_setbigcharpos (ar, 2, 3, 0);
  bc_setbigcharpos (ar, 2, 4, 0);
  for (int i = 5; i < 8; i++)
    {
      bc_setbigcharpos (ar, i, 4, 0);
      bc_setbigcharpos (ar, i, 3, 0);
    }
}

void
CreateCharB (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  bc_setbigcharpos (ar, 0, 7, 0);
  bc_setbigcharpos (ar, 7, 7, 0);
  bc_setbigcharpos (ar, 4, 7, 0);
  bc_setbigcharpos (ar, 3, 7, 0);
  bc_setbigcharpos (ar, 2, 3, 0);
  bc_setbigcharpos (ar, 2, 4, 0);
  bc_setbigcharpos (ar, 5, 3, 0);
  bc_setbigcharpos (ar, 5, 4, 0);
}

void
CreateCharC (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  bc_setbigcharpos (ar, 7, 0, 0);
  bc_setbigcharpos (ar, 0, 0, 0);
  bc_setbigcharpos (ar, 0, 7, 0);
  bc_setbigcharpos (ar, 7, 7, 0);
  for (int i = 2; i < 6; i++)
    {
      bc_setbigcharpos (ar, i, 3, 0);
      bc_setbigcharpos (ar, i, 4, 0);
    }
  for (int i = 3; i < 5; i++)
    {
      bc_setbigcharpos (ar, i, 5, 0);
      bc_setbigcharpos (ar, i, 6, 0);
      bc_setbigcharpos (ar, i, 7, 0);
    }
}

void
CreateCharD (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  for (int i = 2; i < 6; i++)
    {
      bc_setbigcharpos (ar, i, 3, 0);
      bc_setbigcharpos (ar, i, 4, 0);
    }
  for (int i = 5; i < 8; i++)
    {
      bc_setbigcharpos (ar, 0, i, 0);
      bc_setbigcharpos (ar, 7, i, 0);
    }
}

void
CreateCharE (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  for (int i = 2; i < 8; i++)
    {
      bc_setbigcharpos (ar, 2, i, 0);
      bc_setbigcharpos (ar, 5, i, 0);
    }
}

void
CreateCharF (int *ar)
{
  for (int i = 0; i < 8; i++)
    {
      for (int j = 0; j < 8; j++)
        {
          bc_setbigcharpos (ar, j, i, 1);
        }
    }
  for (int i = 2; i < 8; i++)
    {
      bc_setbigcharpos (ar, 2, i, 0);
    }
  for (int i = 5; i < 8; i++)
    {
      for (int j = 2; j < 8; j++)
        {
          bc_setbigcharpos (ar, i, j, 0);
        }
    }
}
