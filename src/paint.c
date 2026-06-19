#include "paint.h"

Shape shapes[MAX_SHAPES];
int totalShapes = 0;

Tool currentTool = TOOL_POINT;

// Controle da linha
Point lineStart;
Point lineEnd;

int drawingLine = 0;

Point squareStart;
Point squareEnd;
Point squarePoints[4];

int drawingSquare = 0;

Point polygonPoints[MAX_POINTS];
int polygonPointCount = 0;
int drawingPolygon = 0;

int selectedShape = -1;
int draggingShape = 0;
Point dragOffset;