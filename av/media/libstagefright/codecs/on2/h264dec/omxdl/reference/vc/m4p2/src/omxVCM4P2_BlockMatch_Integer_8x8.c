/**
 * 
 * File Name:  omxVCM4P2_BlockMatch_Integer_8x8.c
 * OpenMAX DL: v1.0.2
 * Revision:   9641
 * Date:       Thursday, February 7, 2008
 * 
 * (c) Copyright 2007-2008 ARM Limited. All Rights Reserved.
 * 
 * 
 *
 * Description:
 * Contains modules for Block matching, a full search algorithm
 * is implemented
 * 
 */

#include "omxtypes.h"
#include "armOMX.h"
#include "omxVC.h"

#include "armVC.h"
#include "armCOMM.h"

/**
 * Function:  omxVCM4P2_BlockMatch_Integer_8x8   (6.2.4.2.2)
 *
 * Description:
 * Performs an 8x8 block search; estimates motion vector and associated 
 * minimum SAD.  Both the input and output motion vectors are represented 
 * using half-pixel units, and therefore a shift left or right by 1 bit may be 
 * required, respectively, to match the input or output MVs with other 
 * functions that either generate output MVs or expect input MVs represented 
 * using integer pixel units. 
 *
 * Input Arguments:
 *   
 *   pSrcRefBuf - pointer to the reference Y plane; points to the reference 
 *            block that corresponds to the location of the current 8x8 block 
 *            in the current plane. 
 *   refWidth - width of the reference plane 
 *   pRefRect - pointer to the valid reference plane rectangle; coordinates 
 *            are specified relative to the image origin.  Rectangle 
 *            boundaries may extend beyond image boundaries if the image has 
 *            been padded. 
 *   pSrcCurrBuf - pointer to the current block in the current macroblock 
 *            buffer extracted from the original plane (linear array, 128 
 *            entries); must be aligned on an 8-byte boundary.  The number of 
 *            bytes between lines (step) is 16 bytes. 
 *   pCurrPointPos - position of the current block in the current plane 
 *   pSrcPreMV - pointer to predicted motion vector; NULL indicates no 
 *            predicted MV 
 *   pSrcPreSAD - pointer to SAD associated with the predicted MV (referenced 
 *            by pSrcPreMV); may be set to NULL if unavailable. 
 *   pMESpec - vendor-specific motion estimation specification structure; 
 *            must have been allocated and then initialized using 
 *            omxVCM4P2_MEInit prior to calling the block matching function. 
 *
 * Output Arguments:
 *   
 *   pDstMV - pointer to estimated MV 
 *   pDstSAD - pointer to minimum SAD 
 *
 * Return Value:
 *    
 *    OMX_Sts_NoErr - no error 
 *    OMX_Sts_BadArgErr - bad arguments.  Returned if one of the following 
 *              conditions is true: 
 *    -    at least one of the following pointers is NULL: pSrcRefBuf, 
 *              pRefRect, pSrcCurrBuff, pCurrPointPos, pDstMV, pDstSAD or 
 *              pMESpec, or 
 *    -    pSrcCurrBuf is not 8-byte aligned 
 *
 */

OMXResult omxVCM4P2_BlockMatch_Integer_8x8(
     const OMX_U8 *pSrcRefBuf,
     OMX_INT refWidth,
     const OMXRect *pRefRect,
     const OMX_U8 *pSrcCurrBuf,
     const OMXVCM4P2Coordinate *pCurrPointPos,
     const OMXVCMotionVector *pSrcPreMV,
     const OMX_INT *pSrcPreSAD,
     void *pMESpec,
     OMXVCMotionVector *pDstMV,
     OMX_INT *pDstSAD
)
{
   OMX_U8 BlockSize = 8;
   
   /* Argument error checks */  
   armRetArgErrIf(!armIs8ByteAligned(pSrcCurrBuf), OMX_Sts_BadArgErr);
   
   return ( armVCM4P2_BlockMatch_Integer(
     pSrcRefBuf,
     refWidth,
     pRefRect,
     pSrcCurrBuf,
     pCurrPointPos,
     pSrcPreMV,
     pSrcPreSAD,
     pMESpec,
     pDstMV,
     pDstSAD,
     BlockSize)
     );

}

/* End of file */
