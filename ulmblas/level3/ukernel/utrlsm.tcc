#ifndef ULMBLAS_LEVEL3_UKERNEL_UTRLSM_TCC
#define ULMBLAS_LEVEL3_UKERNEL_UTRLSM_TCC 1

#include <ulmblas/config/simd.h>
#include <ulmblas/level1/scal.h>
#include <ulmblas/level1extensions/gecopy.h>
#include <ulmblas/level3/ukernel/ugemm.h>
#include <ulmblas/level3/ukernel/utrlsm.h>

//
//  Selected optimized micro kernel
//
#if defined(USE_SSE)
#   define  SELECT_UTRLSM_KERNEL    sse
#   include <ulmblas/level3/ukernel/sse/utrlsm.h>
#else
#   define  SELECT_UTRLSM_KERNEL    ref
#   include <ulmblas/level3/ukernel/ref/utrlsm.h>
#endif


namespace ulmBLAS {

//
//  Buffered variant.  Used for zero padded panels.
//
template <typename IndexType, typename T, typename TC>
void
utrlsm(IndexType    mr,
       IndexType    nr,
       const T      *A,
       const T      *B,
       TC           *C,
       IndexType    incRowC,
       IndexType    incColC)
{
    const IndexType MR = BlockSizeUGemm<T>::MR;
    const IndexType NR = BlockSizeUGemm<T>::NR;

    T   A_[MR*MR];
    T   B_[MR*NR];
    T   C_[MR*NR];

    scal(MR*MR, T(0), A_, IndexType(1));
    scal(MR*NR, T(0), B_, IndexType(1));

    gecopy(mr, mr, false, A, IndexType(1), MR, A_, IndexType(1), MR);
    gecopy(mr, nr, false, B, NR, IndexType(1), B_, NR, IndexType(1));

    utrlsm(A_, B_, C_, IndexType(1), MR);
    gecopy(mr, nr, false, C_, IndexType(1), MR, C, incRowC, incColC);
}

//
//  Buffered variant.  Used if the result A^(-1)*B needs to be upcasted for
//  computing C <- A^(-1)*B
//
template <typename T, typename TC, typename IndexType>
void
utrlsm(const T     *A,
       const T     *B,
       TC          *C,
       IndexType   incRowC,
       IndexType   incColC)
{
    const IndexType MR = BlockSizeUGemm<T>::MR;
    const IndexType NR = BlockSizeUGemm<T>::NR;

    utrlsm(MR, NR, A, B, C, incRowC, incColC);
}

//
//  Unbuffered variant.
//
template <typename IndexType, typename T>
void
utrlsm(const T     *A,
       const T     *B,
       T           *C,
       IndexType   incRowC,
       IndexType   incColC)
{
    SELECT_UTRLSM_KERNEL::utrlsm(A, B, C, incRowC, incColC);
}

} // namespace ulmBLAS

#endif // ULMBLAS_LEVEL3_UKERNEL_UTRLSM_TCC
