#ifndef ULMBLAS_SRC_LEVEL1EXTENSIONS_KERNEL_SSE_DOTXAXPYF_H
#define ULMBLAS_SRC_LEVEL1EXTENSIONS_KERNEL_SSE_DOTXAXPYF_H 1

namespace ulmBLAS { namespace sse {

template <typename T>
    int
    dotxaxpyf_fusefactor();

template <typename IndexType>
    void
    dotxaxpyf(IndexType      n,
              bool           conjX,
              bool           conjXt,
              bool           conjY,
              const double   &alpha,
              const double   *a,
              IndexType      incA,
              const double   *X,
              IndexType      incRowX,
              IndexType      incColX,
              const double   *y,
              IndexType      incY,
              double         *z,
              IndexType      incZ,
              double         *rho,
              IndexType      incRho);

} } // namespace sse, ulmBLAS

#endif // ULMBLAS_SRC_LEVEL1EXTENSIONS_KERNEL_SSE_DOTXAXPYF_H 1

#include <src/level1extensions/kernel/sse/dotxaxpyf.tcc>