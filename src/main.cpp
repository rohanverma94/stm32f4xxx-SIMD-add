/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
    #include "stm32f4xx_conf.h"

    #include <cstdint>

    int main(void)
    {
        uint16_t  A1[1024],A2[1024],A3[1024],B[1024],C[1024];
        uint32_t *B1 = (uint32_t*)B;
        uint32_t *C1 = (uint32_t*)C;
        uint32_t *A31 = (uint32_t*)A3;

        for(uint32_t  i = 0 ; i < 1024 ; i=i+4){

            B[i] = 1;
            B[i + 1] = 1;
            B[i + 2] = 1;
            B[i+ 3] = 1;
        }

        for(uint32_t  i = 0 ; i < 1024 ; i=i+4){

               C[i] = 1;
            C[i + 1] = 1;
            C[i + 2] = 1;
            C[i + 3] = 1;
        }

        //Optimization - with SIMD
/*
    	// Addition
        for (uint32_t  i =0 ; i < 1024; i=i+4){
                uint32_t word1 = (uint32_t(B[i+1]) << 16) | B[i];
                uint32_t word2 = (uint32_t(C[i+1])<<16) | C[i];
                uint32_t word11 = (uint32_t(B[i+3]) << 16) | B[i+2];
                uint32_t word22 = (uint32_t(C[i+3])<<16) | C[i+2];
                uint32_t mm = __UADD16 (word1 , word2);
                uint32_t mm2 = __UADD16 (word11, word22);

                A1[i] = (uint16_t) mm;
                A1[i+1] = mm >> 16;
                A1[i+2] = (uint16_t) mm2;
                A1[i+3] = mm2 >> 16;
     }
*/
     //Alternative Fast SIMD
           for (uint32_t  i =0 ; i < 1024; i=i+4){

                A31[i] = __UADD16 (B1[i] , C1[i]);
                A31[i+2] = __UADD16 (B1[i+2], C1[i+2]);

     }



        //Optimization - without SIMD
        for(uint32_t  i = 0 ; i < 1024 ; i = i+4){

            A2[i] = B[i] + C[i];
            A2[i + 1] = B[i + 1] + C[i + 1];
            A2[i + 2] = B[i + 2] + C[i + 2];
            A2[i + 3] = B[i + 3] + C[i + 3];

        }



    }
