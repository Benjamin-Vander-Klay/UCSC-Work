###############################################################################
#Author: Benjamin Vander Klay 
#		 bcvander
# 
#		 13 May 2020
#
#Assignment: Lab3: "ASCII-Risks"
#
#File: Lab3.asm
#
#Class: CSE12/L, UCSC, Spring 2020 
#
#Prints out a pyramid of user-determined height
#
#Notes: Intended to be run from MARS IDE
###############################################################################

#Macros for end program
.macro end_program
	li $v0, 10
	syscall
.end_macro

#	Pseudo-code
#
#	
#	Width = input * 2
# //use half then mirror loop?
#	count = 1;
#	for( currentHeight: cH = 1; CH <= input; CH++){
#		currentWidth;
#		for(CW = 0; CW < input; CW++){
#			if(CW <= CH){
#				print count && \t
#			}
#			else
#				print *
#		}
#		for(CW = input; CW > 0; CW--){
#			int shift = 0
#			if(CW <= CH){
#				print count - shift \t
#				shift++;
#			}
#			else print * \t
#		}
#		\n	
# WATCH FOR OFF 1 ERROR	SUB 1 FORM INPUT?

# $s0 = user-input height
# $t0 = count
# $t1 = currentHeight
# $t2 = currentWidth
# $t3 = shift
# $t4 = shifted count to be printed

.text 

	main:  		
	
	#Start the program with initial prompt
	li $v0, 4  #load immediate (4) into syscall determinant
	la $a0, initial_prompt
	syscall #message goes out onto screen
	
	#receive user's input. puts it in $v0
	li $v0, 5
	syscall
	
	#user's input is in $v0.
	#Need too move before changing v0. Save it first
	move $s0, $v0
	
	#branch if > 0
	bgtz $s0, input_is_correct
		li $v0, 4 #print string
		la $a0, i_e 
		syscall
		j main
		
	input_is_correct: nop
	#put in a \n
	li $v0, 11
	li $a0, '\n'
	syscall
	
	#count = 1
	li $t0, 1
	#currentHeight = 0
	li $t1, 0
	#begin loops
	start_loop1: nop
		# move on when the currentHeight == input
		beq $s0, $t1, end_loop1
			
			li $t2, 0	#  currentWidth = 0
			#first inner for loop
			start_loop2: nop
				beq $s0, $t2, end_loop2
					#if statement to determine what to print
					ble $t2, $t1, else_2
						#print * 
						li $v0, 11
						li $a0, '*'
						syscall #print out astrisk
						#go back to beginning of inner loop
						b end_if2
										
					else_2: nop #else, print the count  
						li  $v0, 1
						li  $a0, 0 #ensures $a0 = $t0
						add $a0, $zero, $t0
						syscall #print out the count
						#increment the count only when printed
						addi $t0, $t0, 1 
						
					end_if2: nop
						
						addi $t2, $t2, 1 #increment the width 
						li $v0, 11
						li $a0, '\t'
						syscall #print tab char
						b start_loop2
						nop
				
				end_loop2: nop #print tab and move on
					
			#shift factor for mirroring
			li $t3, 1
			#2nd inner loop for RHS
			start_loop3: nop
				beqz $t2, end_loop3
								
					#Register to hold shifted count. Wiped every iteration
					li $t4, 0
					#Decrement before determine character
					subi $t2, $t2, 1							
					#if statement to determine what to print
					ble $t2, $t1, else_3
						#print * 
						li $v0, 11
						li $a0, '*'
						syscall #print out astrisk
						#go back to beginning of inner loop
						b end_if3
										
					else_3: nop #else, print the count 
						li  $v0, 1
						sub $t4, $t0, $t3
						addi $t3, $t3, 1
						li  $a0, 0 #ensures $a0 = $t0
						add $a0, $zero, $t4
						syscall #print out the count
						#go back to beginning of inner loop
						
					end_if3: nop
						#branch if the last one in line. no \t at end
						beqz $t2, no_tab
							li $v0, 11
							li $a0, '\t'
							syscall #print tab char
						
						no_tab:
							b start_loop3
						
				#move on
				end_loop3: nop 
					
		
			#increment currentHeight		
			addi $t1, $t1, 1
		
			#print new line character
			li $v0, 11
			li $a0, '\n'
			syscall
		
		#run outer loop again
		b start_loop1	
		nop
	end_loop1:	#continue 
	
	
	end_program #see macro 		
	
.data #for methods 

    #Prompt to start the program
	initial_prompt: .asciiz "Enter the height of the pattern (must be greater than 0): "
    
	#Prompt if the input is incorrect. <= 0
	i_e: .asciiz "Invalid Entry!\n"
	
	
	#astrisk: .asciiz "*"
	
	#tab: .asciiz "\t"
	
	#new_line: .asciiz "\n"
	
	
	
	

