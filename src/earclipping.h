#ifndef EARCLIPPING_H
#define EARCLIPPING_H

#include "structs.h"

// Aplica o algoritmo Ear Clipping no shape recebido,
// transformando o polígono côncavo em convexo (fecho convexo).
// O shape é modificado diretamente (in-place).
// Só age se o shape for TOOL_POLYGON com pelo menos 4 vértices.
void earClipping(Shape *s);

#endif
