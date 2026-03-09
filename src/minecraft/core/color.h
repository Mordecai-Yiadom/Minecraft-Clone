#ifndef MINECRAFT_CORE_COLOR_H
#define MINECRAFT_CORE_COLOR_H

typedef struct Color
{
    float red;
    float green;
    float blue;
    float alpha;
}Color;

#define COLOR_RGB(r, g, b) ((Color){.red=(r/255.0f), .green=(g/255.0f), .blue=(b/255.0f), .alpha=(1.0f)})
#define COLOR_RGBA(r, g, b, a)((Color){.red=(r/255.0f), .green=(g/255.0f), .blue=(b/255.0f), .alpha=(a/255.0f)})

#endif