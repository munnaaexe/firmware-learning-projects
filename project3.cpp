#include<cstdio>
#include<cstdint>

typedef struct
{
    volatile uint32_t PENDING;
    volatile uint32_t ENABLE;
    volatile uint32_t CLEAR;
} INTERRUPT_STRUCT_DATATYPE;

INTERRUPT_STRUCT_DATATYPE fake_interrupt_ctrl = {0};

#define INTC (&fake_interrupt_ctrl)


void set_bit(volatile uint32_t *reg, int pin)
{
    *reg |= (1 << pin);
}

void clear_bit(volatile uint32_t *reg, int pin)
{
    *reg &= ~(1 << pin);
}

int read_bit(volatile uint32_t *reg, int pin)
{
    return (*reg >> pin) & 1;
}

void check_interrupt(INTERRUPT_STRUCT_DATATYPE *intc_ptr, int pin)
{
    int is_enabled = read_bit(&(intc_ptr->ENABLE), pin);          // *intc_ptr > derefrebce taking value // &intc_ptr  > address of the varibale 
    int is_pending = read_bit(&(intc_ptr->PENDING), pin);          // for the red func , e need to give regsiter address  
    // & gives adderess of register , becuase intc_ptr -> pending value we dont need now 

    if (is_enabled && is_pending)
    {
        printf("interrupt fired on source [ %d bit ] \n handling ... \n", pin);

        set_bit(&intc_ptr->CLEAR, pin);     // acknowledge
        clear_bit(&intc_ptr->PENDING, pin); // simulate hardware's reset of PENDING
    }
}


int main()
{


    // set source , set pending , clear pending all done 
    printf("ENABLE before  = 0x%08X\n", INTC->ENABLE);
    set_bit(&INTC->ENABLE, 0);
    printf("ENABLE after   = 0x%08X\n", INTC->ENABLE);

    printf("PENDING before = 0x%08X\n", INTC->PENDING);
    set_bit(&INTC->PENDING, 0);   // simulate button press
    printf("PENDING after  = 0x%08X\n", INTC->PENDING);

    check_interrupt(INTC, 0);

    printf("PENDING final  = 0x%08X\n", INTC->PENDING);

    return 0;
}