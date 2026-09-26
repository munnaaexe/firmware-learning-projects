#include<cstdio>
#include<cstdint>

/*
#include<iostream>
using namespace std;
*/

typedef struct  

 {
 volatile uint32_t PENDING ;
 volatile uint32_t ENABLE ; 
 volatile uint32_t CLEAR ;  

}INTERRUPT_STRUCT_DATATYPE;   // data type created 

#define INTC (&fake_interrupt_ctrl ) 


// variable creation & variable declartion 
INTERRUPT_STRUCT_DATATYPE fake_interrupt_ctrl = {0};
 



int main()
{

   printf("ENABLE register  before = 0x%08X   \n",INTC -> ENABLE );

   INTC -> ENABLE |= (1<<0);  //bit zero of the enable regsiter is enabled
   
    printf("ENABLE register  after = 0x%08X   \n",INTC -> ENABLE );



    // now source connected to the enable register bit 0 , example timer is enabled without disturbing other sources 


    printf("pedning register  before = 0x%08X   \n",INTC -> PENDING );
    INTC -> PENDING |= (1 <<0); 
     printf("pedning register  after = 0x%08X   \n",INTC -> PENDING );
     


    // check bit 0 of both the registers seperatly and if both 1 , print a sttament and clear pending register 

    int reg1 = (INTC -> ENABLE >> 0) & 1 ; 

    int reg2 = (INTC -> PENDING >> 0) &1 ; 

    if ( reg1 && reg2 == 1)
    {
       printf("handling the button press , handleded done ");

        // now clear the pending bit 0 


    printf("\n clearing the pedning register bit 0") ; 
    

    INTC->CLEAR |= (1 << 0);      // step 1: record "acknowledged"


    INTC->PENDING &= ~(1 << 0);   // step 2: simulate the hardware effect of that acknowledgment


    printf("\nhandled done ");
    }





    return 0;


}

