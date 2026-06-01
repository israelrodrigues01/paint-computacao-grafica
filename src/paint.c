#include "paint.h"

Shape shapes[MAX_SHAPES];

int totalShapes = 0;

Tool currentTool = TOOL_POINT;

// Controle da linha
Point firstLinePoint;
int waitingSecondPoint = 0;

Point lineStart;
Point lineEnd;

int drawingLine = 0;

Point polygonPoints[MAX_POINTS];

int polygonPointCount = 0;

int drawingPolygon = 0;