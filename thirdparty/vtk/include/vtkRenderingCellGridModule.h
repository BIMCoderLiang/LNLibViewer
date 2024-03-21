
#ifndef VTKRENDERINGCELLGRID_EXPORT_H
#define VTKRENDERINGCELLGRID_EXPORT_H

#ifdef VTKRENDERINGCELLGRID_STATIC_DEFINE
#  define VTKRENDERINGCELLGRID_EXPORT
#  define VTKRENDERINGCELLGRID_NO_EXPORT
#else
#  ifndef VTKRENDERINGCELLGRID_EXPORT
#    ifdef RenderingCellGrid_EXPORTS
        /* We are building this library */
#      define VTKRENDERINGCELLGRID_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define VTKRENDERINGCELLGRID_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef VTKRENDERINGCELLGRID_NO_EXPORT
#    define VTKRENDERINGCELLGRID_NO_EXPORT 
#  endif
#endif

#ifndef VTKRENDERINGCELLGRID_DEPRECATED
#  define VTKRENDERINGCELLGRID_DEPRECATED __declspec(deprecated)
#endif

#ifndef VTKRENDERINGCELLGRID_DEPRECATED_EXPORT
#  define VTKRENDERINGCELLGRID_DEPRECATED_EXPORT VTKRENDERINGCELLGRID_EXPORT VTKRENDERINGCELLGRID_DEPRECATED
#endif

#ifndef VTKRENDERINGCELLGRID_DEPRECATED_NO_EXPORT
#  define VTKRENDERINGCELLGRID_DEPRECATED_NO_EXPORT VTKRENDERINGCELLGRID_NO_EXPORT VTKRENDERINGCELLGRID_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VTKRENDERINGCELLGRID_NO_DEPRECATED
#    define VTKRENDERINGCELLGRID_NO_DEPRECATED
#  endif
#endif

/* VTK-HeaderTest-Exclude: vtkRenderingCellGridModule.h */

/* Include ABI Namespace */
#include "vtkABINamespace.h"
/* AutoInit dependencies. */
#include "vtkRenderingCoreModule.h"
#include "vtkRenderingOpenGL2Module.h"


/* AutoInit implementations. */
#ifdef vtkRenderingCellGrid_AUTOINIT_INCLUDE
#include vtkRenderingCellGrid_AUTOINIT_INCLUDE
#endif
#ifdef vtkRenderingCellGrid_AUTOINIT
#include "vtkAutoInit.h"
VTK_MODULE_AUTOINIT(vtkRenderingCellGrid)
#endif

#endif /* VTKRENDERINGCELLGRID_EXPORT_H */
