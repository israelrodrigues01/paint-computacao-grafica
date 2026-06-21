#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX_POINTS 100

typedef enum
{
    TOOL_POINT,
    TOOL_LINE,
    TOOL_SQUARE,
    TOOL_POLYGON,
    TOOL_SELECTION

} Tool;

typedef struct
{
    float r;
    float g;
    float b;

} Color;

typedef struct
{
    float x;
    float y;
    float h;

} Point;

typedef struct
{
    float m[3][3];
} Matriz3x3;


typedef struct
{
    Tool tool;
    Color color;
    int totalPoints;
    Point points[MAX_POINTS];
    Point centroide;
    Point centroideOriginal;//animação

} Shape;

#endif
