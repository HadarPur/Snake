********************************************************************
*
*                  Assembly Project
*
*********************************************************************
* File Name:       lcd_mes.S
*
* Processor:       PIC32MX
*
* Assembler/Compiler/Linker:  MPLAB C32
*
* Company:         Microchip Technology, Inc.
*
* Software License Agreement
*
*

********************************************************************/
#include <p32xxxx.h>

/* define all global symbols here */
.global main
.global control
.global name

/* define all global symbols here */
.data
control:
.byte 0x38,0x38,0x38,0xe,0x6,0x1,'$'
name:
.ascii  "GAME OVER <3"
/* define which section (for example "text")
 * does this portion of code resides in. Typically,
 * all your code will reside in .text section as
 * shown below.
 */
.text
/* This is important for an assembly programmer. This
 * directive tells the assembler that don't optimize
 * the order of the instructions as well as don't insert
 * 'nop' instructions after jumps and branches.
 */
.set noreorder


/************************************************************************
 * main()
 * This is where the PIC32 start-up code will jump to after initial
 * set-up.
 ********************************************************************/
.ent main /* directive that marks symbol 'main' as function in ELF
           * output
           */
main:
nop
and        $s0,$zero
sw         $s0,TRISF
sw         $s0,TRISE
sw         $s0,TRISD
lw         $s0,TRISB
andi       $s0,$s0,0x7fff
sw         $s0,TRISB
li         $s0,0
sw         $s0,PORTF

/*   lcd control */
la $s4,control
lw $s5,PORTB
andi $s5,$s5,0x7fff
sw $s5,PORTB #RS=0 control RB15
jal print        //#output control char Lcd

nop
/*  Lcd print_mes */
la $s4,name
li $5,0xffff
sw $5,PORTB #RS=1 data RB15
jal print       // #out_print_mes_lcd
nop
start:
j	  start
nop
.end main /* directive that marks end of 'main' function and registers
           * size in ELF output
           */

.ent print

//print function
print:
pr1:  lb   $3,($s4)
beq  $3,'$',x1
nop
sw $3,PORTE
li    $2,0x10
sw $2,PORTD
li    $2,0x00
sw $2,PORTD
/*  delay  */
addi $s4,$s4,1
andi $s1,$s1,0
andi $s2,$s2,0
ori $s2,$s2,0xffff
x:    addi $s1,$s1,1
bne $s1,$s2,x
nop
/* delay */
j  pr1
nop
x1:
/* return to caller */
jr	$ra
nop
.end print
