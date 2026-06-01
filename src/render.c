#include <GL/glut.h>
#include "paint.h"

void drawShape(Shape shape)
{
    glColor3f(
        shape.color.r,
        shape.color.g,
        shape.color.b);

    switch (shape.tool)
    {
    case TOOL_POINT:

        glPointSize(8);

        glBegin(GL_POINTS);

        glVertex2f(
            shape.points[0].x,
            shape.points[0].y);

        glEnd();

        break;

    case TOOL_LINE:

        glBegin(GL_LINES);

        glVertex2f(
            shape.points[0].x,
            shape.points[0].y);

        glVertex2f(
            shape.points[1].x,
            shape.points[1].y);

        glEnd();

        break;

    case TOOL_POLYGON:

        glBegin(GL_POLYGON);

        for (int i = 0; i < shape.totalPoints; i++)
        {
            glVertex2f(
                shape.points[i].x,
                shape.points[i].y);
        }

        glEnd();

        break;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < totalShapes; i++)
    {
        drawShape(shapes[i]);
    }

    if (drawingLine)
    {
        glColor3f(0, 0, 1);

        glBegin(GL_LINES);

        glVertex2f(lineStart.x, lineStart.y);
        glVertex2f(lineEnd.x, lineEnd.y);

        glEnd();
    }

    if (drawingPolygon && polygonPointCount > 0)
    {
        glColor3f(0, 1, 0);

        glBegin(GL_LINE_STRIP);

        for (int i = 0; i < polygonPointCount; i++)
        {
            glVertex2f(
                polygonPoints[i].x,
                polygonPoints[i].y);
        }

        glEnd();
    }

    glutSwapBuffers();
}