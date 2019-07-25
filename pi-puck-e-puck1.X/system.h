/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* Microcontroller MIPs (FCY) */
#define FOSC 7.3728e6 // 7.3728 MHz crystal in XTL mode 
#define PLL 8.0 // 8x PLL
#define FCY ((FOSC * PLL) / (4.0)) // Instruction cycle frequency 
#define TCY (1e9 / FCY) // Instruction cycle period (in nanoseconds)

/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/
