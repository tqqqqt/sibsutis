#include <stdio.h>
#include <stdlib.h>

#define Weight 8
#define Height 8
#define size 40

#define Wait_mode 0
#define Party_over 1
#define Violation_of_rules 2
#define Piece_not_in_pos 3
#define Error_quite_move 4
#define Error_capture_move 5
#define Exceeding_field_bound 6
#define Broken_sequence_moves 7

void main_body(FILE* file, FILE* ofile);
