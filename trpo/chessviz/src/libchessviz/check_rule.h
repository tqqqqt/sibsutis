#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <chessviz/main_body.h>

void check_rule(
        int x,
        int y,
        int x1,
        int y1,
        int* flag,
        int figures,
        int enemy,
        int* error);
