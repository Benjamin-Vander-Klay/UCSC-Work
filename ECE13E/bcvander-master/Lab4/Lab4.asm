###############################################################################
#
#	Lab4: Sorting Integers	
#	Author: Vander Klay, Benjamin
#			bcvander
#			5/24/2020
#			
#	Class: CSE 12/L Spring 2020 
#			UCSC, Professor Logan
#
#	Description: This Program takes in a user inputed string of Hex numbers
# 					and prints out the numbers in Decimal
#					then prints them out again in a sorted order
#
#	Notes: This program is intended to be run on the MARS IDE
#
###############################################################################

###############################################################################
#	PsuedoCode
#	
#	Print "Program Arguments:\n"
#
#	//Allocate sufficient memory
#	Save arguments into $s0 && $s1
#	each # will take at most 4 bytes, set $a1 to 4
#	new/malloc($a0, $a1)
# 	
#// go thru all the args
#	for(i = 0; i< argc; i++){
#		
#		print the string at the address of the word 
#		
#		
#	}
#	
#	print a \n
#	print the "Integers:" string
#address at $a1/$s1 is the array of addresses 

#for each element in the address array which was can be $t2 $t0 is counter; $s0 is comparator
#    $t1 used to properly increment $s1  
#    load address stored in $s1 into $t2 
#//    follow the address. skip two bytes (0x)  
#    load 0 into $t3 #used to sum the numbers
#
#    load byte into $t4 from $t2 #this will skip two bytes I think 
#    load byte into $t5
#    if $t5 == '\0', branch1
#    else:
#
#	load byte into $t6	
#	if $t6 == \0, branch2
#	else:
#	    $t4 is 256's place
#	        lb $a1, $t4
#		Run function
#		lb $t4, $a1
#	    $t5 is 16's place
#		lb $a1, $t5
#		Run function
#		lb $t5, $a1
#           $t6 is 0's place
#		lb $a1, $t6
#		Run function
#		lb $t6, $a1
#	    j after
#	branch2: # if 3rd byte === \0
#	$t4 is 16's place
#	    lb $a1, $t4
#	    Run function
#	    lb $t4, $a1
#	$t5 is 0's place
#	    lb $a1, $t5
#	    Run function
#	    lb $$t5, $a1   
#	$6 = 0	
#	j after    
#
#   branch1: # if 2nd byte == \0
#	don't read the next one
#	$t4 is the 0's place in hex.
#           lb $a1, $t4
#	    Run function
#	    lb $t4, $a1
#	$t5, $t6 = 0
#
#    after:
#	$t0++
#	DON'T ADD A SPACE. ADD A SPACE WHEN PRINTING OUT
#	sum $t4, %t5, $t6 into $t3 
#	save $t3 into respective location in the array

#Sort Int Array
# for each index bubble it up
# for( i = 0; i < argc - 1 ; i++){
    
#    for(j = 0; j < (argc - 1) - i; j++){
#	if(A[j] > A[j+1]){
#	    int temp = A[j];  ### COULD USE SUBROUTINE
#	    A[j] = A[j+1];
#           A[j+1] = temp;
#	}
#   }
#  }

# PRINT FUNCTION
#//for each element in the array
#	//array_length = $s0 likely. All arrays are the same length
#	for(i = 0; i < array_length; i++){
#		print the int
#		if (i < array_length-1)
#			print a " " character;
#	
#	}
#	print \n 
#
#
# FUNCTION TO CONVERT TO DECIMAL
# if $a1 less than 0x40,
#	subtract 0x30 or 48
#
#    else: 
#	subtract 0x37 or 55  #source of error? 56/0x38? 
#	RETURN




###############################################################################

###############################################################################
#	Register Assignments:
# 	$s0 = argc (agrument count, initially $a0) 
#	$s1 = pointer to pointer set argv. (initially $a1)
#	$s2 = pointer to array to store the strings
#	
###############################################################################
.macro end_program
	li $v0, 10
	syscall
.end_macro

.text
main:
	
	# set $s0 as array size
	add $s0, $a0, $zero
	# set $s1 as array origin pointer 
	add $s1, $a1, $zero
	
	#initialize/Allocate the input array
	#jal create_array
	
	# save the array
	#la $s2, ($v0)
	
	la $a0, program_arguments
	li $v0, 4
	syscall
	
	##### 
	#
	# $t0 = for loop counter
	# $t1 = 4 in order to properly increment words
	# $t2 = address of current token
	#
	#####
	li $t0, 0
	# for loop to load arguments into allocated array
	print_arg:
		#branch if counter == argc
		beq $t0, $s0, print_arg_end
		#{ for loop contents
			# increment the address to get each number
			li  $t1, 4
			mul $t1, $t0, $t1
			add $t2, $s1, $t1
			
			#$t2 stores the address of the current hex int 				
			#print out the \0 ended string			
			lw  $a0, ($t2)
			li  $v0, 4
			syscall
			
			#increment before to skip space if it is the last number
			addi $t0, $t0, 1
			beq  $t0, $s0, print_arg_end
				# Print Space char
				li $a0, ' '
				li $v0, 11
				syscall
		#}
		
		j print_arg
	print_arg_end:
	#print a new line char
	li $a0, '\n'
	li $v0, 11
	syscall
	
	
	##### 
	#
	# $t0 = for loop counter
	# $t1 = 4 in order to properly increment words
	# $t2 = address of current token
	# $t3 = sum of registers $t4, $t5, $t6 to be stored as one integer
	# $t4 = the third byte of each string (0x$t4)
	# $t5 = the fourth byte of each string (0x0$t5)
	# $t6 = the fifth byte of each string (0x00$t6)
	# $t7 = 16  (to multiply the 16's place # by)
	# $t8 = 256 (to multiply the 256's place # by)
	# $t9 = the current address/index in the address array
	#
	#####
	
	
	#reset $t0
	li $t0, 0
	# constants for multiplication/conversion
	li $t7, 16
	li $t8, 256
	
	
	# For loop to store the strings in the array and convert them to decimal
	conv_arg:
	
	beq $t0, $s0, conv_arg_end
	# {	
		# $t3 used to as sum storage at end of loop
		li  $t3, 0	
		# increment the address to get each number
		li  $t1, 4
		mul $t1, $t0, $t1
		# increment the address to get the current index
		add $t2, $s1, $t1
		#load the address from 
		lw   $t9, ($t2)		
		
		#skip two bytes WORKS!
		lb   $t4, 2($t9)	
		lb   $t5, 3($t9)	
		beqz $t5, single_digit
		#else:
			lb $t6, 4($t9)
			beqz $t6, double_digit
			# else:
				
				# $t4 is 256's place
				move $a1, $t4
				jal convert
				move $t4, $a1
				mul  $t4, $t4, $t8
				
				# $t5 is 16's place
				move $a1, $t5
				jal convert
				move $t5, $a1
				mul  $t5, $t5, $t7
				
				# $t6 is 0's place 
				move $a1, $t6
				jal convert
				move $t6, $a1
				# multiply by 1	
				j end_if
				
			#branch2 if 3rd byte == 0
			double_digit: 
			
				# $t4 is 16's place
				move $a1, $t4
				jal convert
				move $t4, $a1
				# multiply by 16
				mul  $t4, $t4, $t7  
				
				# $t5 is 0's place
				move $a1, $t5
				jal convert
				move $t5, $a1
				# "multiply by 1"
		
				j end_if
		#branch1 if 2nd byte == 0
		single_digit:
			#don't read anything into $t6, $t5 is already = 0
			li $t6, 0
			# $t4 is 0's place
			move $a1, $t4
			jal convert
			move $t4, $a1
		end_if:
		#increment counter
		addi $t0, $t0, 1
		
		#sum the registers:
		add $t5, $t5, $t6 
		add $t3, $t4, $t5
		#add to array
		sw $t3, argv($t1)
		
		
		
		j conv_arg
	# }
	conv_arg_end:
		
	# print out the next string 
	la $a0, integer_values
	li $v0, 4
	syscall
	
	# print out the array with the decimal numbers 
	la $a0, argv
	move $a1, $s0
	li $t0, 0
	jal print_array
	
	##### 
	#
	# $t0 = outer for loop counter
	# $t1 = inner for loop counter
	# $t2 = 4 for the index adjuster 
	# $t3 = A[j]
	# $t4 = j+1 >> the next index 
	# $t5 = A[j+1]
	# $t8 = inner loop end condition
	# $t9 = outer loop end condition
	#
	#####
	
	
	# sort integer Array 
	#initialize values
	li   $t0, 0 
	subi $t9, $s0, 1
	#outside loop
	bb_sort:
		bge $t0, $t9, bb_sort_end
	# {	
		
		
		# condition for inner loop dep on outer
		sub $t8, $t9, $t0
		li  $t1, 0
		in_sort:
			bge $t1, $t8, in_sort_end
		# {
   			
   			# shift by 4		
			li   $t2, 4
			mul  $t2, $t1, $t2
			
			# load in A[j]
			lw   $t3, argv($t2)
			# load in A[j+1]. Put it in a separate one to not screw up next iterations
			addi $t4, $t2, 4
			lw   $t5, argv($t4)
			
			# compre the two integers
			bgt $t3, $t5, if_true
				addi $t1, $t1, 1
				j in_sort
			
			
			if_true:
			#swap OOO PUT IT ON THE STACK
			#addi $sp, $sp, -4
			#sw   $t3, ($sp)
			
			#A[j] = A[j+1]
			sw   $t5, argv($t2)
			sw   $t3, argv($t4)
			
		    addi $t1, $t1, 1
			j in_sort	
		# }	
		in_sort_end:
	
		addi $t0, $t0, 1
		j bb_sort
	# }
	bb_sort_end:
	
	# print out the next string 
	la $a0, sorted_values
	li $v0, 4
	syscall
	
	# print the array again
	la $a0, argv
	move $a1, $s0
	li $t0, 0
	jal print_array
	
	end_program	

###############################################################################
# Functions
#	create_array:
#		addi $t0, $t0, 4
#		mul  $a0, $a0, $t0 
#		#create space the size of the input
#		li $v0, 9
#		syscall
#		#saves the A[0] if you will to 
#		jr $ra
	

		
# 	FUNCTION TO CONVERT TO DECIMAL
	convert:
		#save $t0 and $t1 to stack
		addi $sp, $sp, -4
		sw   $t0, 0($sp)
		#sw   $t1, 4($sp)
		
		li   $t0, 65
		# if $a1 less than 0x40
		blt  $a1, $t0, conv_else
		# subtract 0x37 or 55  #source of error? 56/0x38? 
		subi $a1, $a1, 55
		j conv_return
		
        conv_else: 
        # subtract 0x30 or 48
        subi $a1, $a1, 48

#	RETURN!
		conv_return:
		#load the saved items back
		lw $t0, 0($sp)
		#lw $t0, 4($sp)
		addi $sp, $sp, 4
		jr $ra
		
# $a0 should be loaded with the address of the start of the Array 	
	print_array:	
		# save the $s registers and the return address //$ra just for security 
		addi $sp, $sp, -16
		sw   $ra, 0($sp)
		sw   $s0, 4($sp)
		sw   $s1, 8($sp)
		sw   $s2, 12($sp)
		
		#move base of array from argument to saved reg
		move $s0, $a0
		# move number of elements from arg to saved reg
		move $s1, $a1
		
		#for loop initializer, $s2 is the counter
		li   $s2, 0
		p_loop:
			# set greater than/equal 
			sge $t0, $s2, $s1
			bnez $t0, p_loop_end
				#multiply $s2 by 4 and store in $t0 
				sll $t0, $s2, 2
				#set $t0 to be addy of current element 
				add $t0, $t0, $s0
				#print the Integer
				lw $a0, ($t0)
				li $v0, 1
				syscall
				 
				#increment $s2 //counter
				addi $s2, $s2, 1
				# only print ' ' if not the end of the loop
				sge $t0, $s2, $s1
				bnez $t0, p_loop_end
					# Print Space char
					li $a0, ' '
					li $v0, 11
					syscall
				j p_loop
		p_loop_end:
		#print newline char
		li $a0, '\n'
		li $v0, 11
		syscall
		
		lw $ra, 0($sp)
        lw $s0, 4($sp)
		lw $s1, 8($sp)
 		lw $s2, 12($sp) # restore stack and return
 		addi $sp, $sp, 16
 		jr $ra 
		

.data
	
	program_arguments: .asciiz "Program Arguments:\n"
	
	integer_values:    .asciiz "Integer values:\n"
	
	sorted_values:     .asciiz "Sorted values:\n"
	
	.align 2
	argv: .space 32
	
	
		
		
		