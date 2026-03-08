#ifndef MINECRAFT_CLIENT_GENERICPIPELINE_H
#define MINECRAFT_CLIENT_GENERICPIPELINE_H


#include "../renderpipeline.h"


RenderPipeline GenericPipeline_create();

#ifdef MINECRAFT_CLIENT_GENERICPIPELINE_C
static inline void GenericPipeline_load(RenderPipeline *pipeline, RenderTarget *renderTarget);
static inline void GenericPipeline_unload(RenderPipeline *pipeline, RenderTarget *renderTarget);
#endif


#endif