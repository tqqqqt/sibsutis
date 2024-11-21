#include <libcomp/ConsoleContent.h>

size_t size_need_writ = 0;
int masForChars[18][2];

void
Memory_block ()
{
  bc_box (1, 1, 62, 12);
  mt_gotoXY (1, 27);
  write (1, "Memory", strlen ("Memory"));
  int line = 2, value = 0, comand = 0, operand = 0, flag = 0;
  char buf[6];
  sc_regGet (8, &flag);
  for (int i = 0; i < 100; i++)
    {
      if (i % 10 == 0)
        {
          mt_gotoXY (line, 2);
          line++;
        }
      if (sc_memoryGet (i, &value) < 0
          || sc_commandDecode (value & 0x3FFF, &comand, &operand) < 0)
        {
          sc_regSet (16, 1);
          break;
        }
      size_need_writ = snprintf (
          buf, 6, "%c%02X%02X", (value & 0x4000) ? '-' : '+', comand, operand);
      if (flag == 0)
        {
          if (i == ins_count)
            {
              mt_setbgcolor (white);
              mt_setfgcolor (no_col);
              write (1, buf, size_need_writ);
              mt_setbgcolor (no_col);
              mt_setfgcolor (white);
            }
          else
            {
              write (1, buf, 5);
            }
        }
      else
        {
          if (i == selected_mas)
            {
              mt_setbgcolor (white);
              mt_setfgcolor (no_col);
              write (1, buf, size_need_writ);
              mt_setbgcolor (no_col);
              mt_setfgcolor (white);
            }
          else
            write (1, buf, size_need_writ);
        }
      if ((i + 1) % 10 != 0)
        write (1, " ", strlen (" "));
    }
}

void
Acum_block ()
{
  bc_box (63, 1, 82, 3);
  mt_gotoXY (0, 67);
  write (1, "Accumulator", strlen ("Accumulator"));
  int comand, operand;
  char buf[6];
  mt_gotoXY (2, 69);
  if (sc_commandDecode (ac & 0x3FFF, &comand, &operand) < 0)
    {
      sc_regSet (16, 1);
      return;
    }
  size_need_writ = snprintf (buf, 6, "%c%02X%02X", (ac & 0x4000) ? '-' : '+',
                             comand, operand);
  write (1, buf, size_need_writ);
}

void
Ins_block ()
{
  bc_box (63, 4, 82, 6);
  mt_gotoXY (4, 65);
  write (1, "InstructCounter", strlen ("InstructCounter"));
  char buf[6];
  mt_gotoXY (5, 70);
  size_need_writ
      = snprintf (buf, 6, "%c%02d", (ins_count & 0x80) ? '-' : '+', ins_count);
  write (1, buf, size_need_writ);
  mt_gotoXY (23, 14);
}

void
Operation_block ()
{
  bc_box (63, 7, 82, 9);
  mt_gotoXY (7, 67);
  write (1, "Operation", strlen ("Operation"));
  int value = 0, comand = 0, operand = 0, flag = 0;
  char buf[10];
  sc_regGet (8, &flag);
  mt_gotoXY (8, 67);
  if (flag == 0)
    {
      if (sc_memoryGet (ins_count, &value) < 0
          || sc_commandDecode (value, &comand, &operand) < 0)
        {
          // return;
        }
    }
  else
    {
      if (sc_memoryGet (selected_mas, &value) < 0
          || sc_commandDecode (value, &comand, &operand) < 0)
        {
          // return;
        }
    }
  size_need_writ = snprintf (buf, 10, "%c%02X : %02X",
                             (value & 0x4000) ? '-' : '+', comand, operand);
  write (1, buf, size_need_writ);
}

void
Flag_block ()
{
  bc_box (63, 10, 82, 12);
  mt_gotoXY (10, 68);
  write (1, "FLags", strlen ("Flags"));
  mt_gotoXY (11, 67);
  for (int i = 1; i < 6; i++)
    {
      switch (i)
        {
        case 1:
          if (reg_flag & 1)
            {
              mt_setbgcolor (no_col);
              mt_setfgcolor (red);
              write (1, "P", strlen ("P"));
              mt_setbgcolor (no_col);
              mt_setfgcolor (white);
            }
          else
            write (1, "P", strlen ("P"));
          break;
        case 2:
          if (reg_flag & 2)
            {
              mt_setbgcolor (no_col);
              mt_setfgcolor (red);
              write (1, "O", strlen ("O"));
              mt_setbgcolor (no_col);
              mt_setfgcolor (white);
            }
          else
            write (1, "O", strlen ("O"));
          break;
        case 3:
          if (reg_flag & 4)
            {
              mt_setbgcolor (no_col);
              mt_setfgcolor (red);
              write (1, "M", strlen ("M"));
              mt_setbgcolor (no_col);
              mt_setfgcolor (white);
            }
          else
            write (1, "M", strlen ("M"));
          break;
        case 4:
          if (reg_flag & 8)
            {
              mt_setbgcolor (no_col);
              mt_setfgcolor (red);
              write (1, "T", strlen ("T"));
              mt_setbgcolor (no_col);
              mt_setfgcolor (white);
            }
          else
            write (1, "T", strlen ("T"));
          break;
        case 5:
          if (reg_flag & 16)
            {
              mt_setbgcolor (no_col);
              mt_setfgcolor (red);
              write (1, "E", strlen ("E"));
              mt_setbgcolor (no_col);
              mt_setfgcolor (white);
            }
          else
            write (1, "E", strlen ("E"));
          break;
        }
      write (1, " ", strlen (" "));
    }
  mt_gotoXY (23, 14);
}

void
BigChar_block ()
{
  bc_box (1, 13, 47, 22);
  int value, comand, operand, bg[2], needChar = 0, flag = 0;
  char buf[6];
  sc_regGet (8, &flag);
  if (flag == 0)
    {
      if (sc_memoryGet (ins_count, &value) < 0
          || sc_commandDecode (value & 0x3FFF, &comand, &operand) < 0)
        {
          return;
        }
    }
  else
    {
      if (sc_memoryGet (selected_mas, &value) < 0
          || sc_commandDecode (value & 0x3FFF, &comand, &operand) < 0)
        {
          return;
        }
    }
  snprintf (buf, 6, "%c%02X%02X", (value & 0x4000) ? '-' : '+', comand,
            operand);
  for (int i = 0; i < 5; i++)
    {
      memset (bg, 0, sizeof (int) * 2);
      switch (buf[i])
        {
        case '+':
          needChar = 0;
          break;
        case '-':
          needChar = 1;
          break;
        case '0':
          needChar = 2;
          break;
        case '1':
          needChar = 3;
          break;
        case '2':
          needChar = 4;
          break;
        case '3':
          needChar = 5;
          break;
        case '4':
          needChar = 6;
          break;
        case '5':
          needChar = 7;
          break;
        case '6':
          needChar = 8;
          break;
        case '7':
          needChar = 9;
          break;
        case '8':
          needChar = 10;
          break;
        case '9':
          needChar = 11;
          break;
        case 'A':
          needChar = 12;
          break;
        case 'B':
          needChar = 13;
          break;
        case 'C':
          needChar = 14;
          break;
        case 'D':
          needChar = 15;
          break;
        case 'E':
          needChar = 16;
          break;
        case 'F':
          needChar = 17;
          break;
        }
      bc_printbigchar (masForChars[needChar], 2 + (i * 8) + i, 14, white,
                       no_col);
    }
}

void
Button_block ()
{
  bc_box (48, 13, 82, 22);
  mt_gotoXY (13, 63);
  write (1, "Keys", strlen ("Keys"));
  mt_gotoXY (14, 49);
  write (1, "l-load", strlen ("l-load"));
  mt_gotoXY (15, 49);
  write (1, "s-save", strlen ("s-save"));
  mt_gotoXY (16, 49);
  write (1, "r-run", strlen ("r-run"));
  mt_gotoXY (17, 49);
  write (1, "t-step", strlen ("t-step"));
  mt_gotoXY (18, 49);
  write (1, "i-reset", strlen ("i-reset"));
  mt_gotoXY (19, 49);
  write (1, "f5-accumulator", strlen ("f5-accumulator"));
  mt_gotoXY (20, 49);
  write (1, "f6-IP", strlen ("f6-IP"));
  mt_gotoXY (23, 0);
  write (1, "Input\\Output:", strlen ("Input\\Output:"));
  mt_gotoXY (24, 0);
  write (1, "35< +1F1F", strlen ("35< +1F1F"));
  mt_gotoXY (25, 0);
  write (1, "35> +1F1F", strlen ("35> +1F1F"));
}

void
LoadCharFont ()
{
  int fd = open ("bigCharFont.bin", O_RDONLY, S_IREAD);
  int temp;
  int tempMas[36];
  bc_bigcharread (fd, tempMas, 18, &temp);
  close (fd);
  temp = 0;
  for (int i = 0; i < 18; i++)
    {
      for (int j = 0; j < 2; j++)
        {
          masForChars[i][j] = tempMas[temp];
          temp++;
        }
    }
}

void
ClearSpace (int y, int x, int llenght)
{
  mt_gotoXY (y, x);
  mt_setbgcolor (no_col);
  mt_setfgcolor (no_col);
  if (llenght == 1)
    write (1, "     ", strlen ("     "));
  else if (llenght == 2)
    write (1, "                        ", strlen ("                        "));
  mt_setbgcolor (no_col);
  mt_setfgcolor (white);
}

void
SignalHandler (int signal)
{
  int flag = 0, temp = 0;
  if (signal == SIGALRM)
    {
      sc_regGet (8, &flag);
      if (flag == 0)
        {
          temp = CU ();
          if (temp)
            {
              sc_regSet (8, 1);
              alarm (0);
            }
          else
            {
              if (++ins_count == 100)
                {
                  ins_count--;
                  sc_regSet (8, 1);
                  alarm (0);
                }
            }
          BigChar_block ();
          Memory_block ();
          Acum_block ();
          Ins_block ();
          Operation_block (ins_count);
          Flag_block ();
        }
    }
  else if (signal == SIGUSR1)
    {
      ac = 0;
      ins_count = 0;
      sc_memoryInit ();
      sc_regInit ();
      sc_regSet (8, 1);
      Flag_block ();
    }
  else if (signal == SIGUSR2)
    {
      sc_regGet (8, &flag);
      if (flag == 0)
        {
          temp = CU ();
          if (temp)
            {
              sc_regSet (8, 1);
            }
          else
            {
              if (++ins_count == 100)
                {
                  ins_count--;
                  sc_regSet (8, 1);
                }
            }
        }
      Ins_block ();
    }
}
