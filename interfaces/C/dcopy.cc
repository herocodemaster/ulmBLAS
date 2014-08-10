#include <interfaces/C/config.h>
#include <src/level1/copy.h>
#include <src/level1/copy.tcc>

extern "C" {

void
ULMBLAS(dcopy)(const int    n,
               const double *x,
               const int    incX,
               double       *y,
               const int    incY)
{
    return ulmBLAS::copy(n, x, incX, y, incY);
}

} // extern "C"
