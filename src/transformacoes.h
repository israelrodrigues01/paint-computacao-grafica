#ifndef TRANSFORMACOES_H
#define TRANSFORMACOES_H

#include "structs.h"


Matriz3x3 multiplicarMatrizes(Matriz3x3 A, Matriz3x3 B);

Matriz3x3 criarMatrizTransladaIda(float xr, float yr);


Matriz3x3 criarMatrizTransladaVolta(float xr, float yr);

void aplicarTransformacao(Shape *shape, Matriz3x3 M);

void rotacao(Shape *shape, float theta_graus);

void escala(Shape *shape, float sx, float sy);

void reflexao(Shape *shape, float x, float y);

void cisalhamento(Shape *shape, float shx, float shy);

void translacao(Shape *shape, float tx, float ty);


#endif


