#ifndef PAINT_H
#define PAINT_H

#include "structs.h"

extern Shape shapes[MAX_SHAPES];
extern int totalShapes;

extern Tool currentTool;

extern Point lineStart;
extern Point lineEnd;
extern int drawingLine;

extern Point squareStart;
extern Point squareEnd;
extern Point squarePoints[4];
extern int drawingSquare;

extern Point polygonPoints[MAX_POINTS];
extern int polygonPointCount;
extern int drawingPolygon;

extern int selectedShape; // Recebe o índice do shape selecionado e -1 caso nenhuma forma esteja selecionada
extern int draggingShape; // Recebe 1 se estiver sendo arrastado o shape selecionado
extern Point dragOffset; // Guarda o deslocamento do clique ao centro do shape selecionado

#endif