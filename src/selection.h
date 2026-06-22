#ifndef SELECTION_H
#define SELECTION_H

#include "structs.h"

#define SELECTION_TOLERANCE 0.03f

// Retorna o índice da forma selecionada ou -1 se nenhuma forma for selecionada
int pickPonto(float px, float py, float mx, float my, float t);

// Retorna 1 se o segmento (x0, y0)-(x1,y1) intercepta o retângulo centrado em (mx, my)
int pickLinha(float x0, float y0, float x1, float y1, float mx, float my, float t);

// Retorna 1 se o ponto (px, py) está dentro do polígono centrado em (mx, my)
int pickArea(Point *points, int n, float mx, float my);

// Retorna o índice da forma selecionada ou -1 se nenhuma forma for selecionada, para qualquer clique em (mx, my)
int pickShape(Shape *shapes, int total, float mx, float my);

#endif