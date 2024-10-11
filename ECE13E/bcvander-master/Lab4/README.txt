-------------------------------------------------------------------------------

Benjamin Vander Klay
bcvander
CSE 12/L Spring 2020
Lab 4: Sorting Integers 

-------------------------------------------------------------------------------

DESCRIPTION

In this Lab is this lab we used MARS to code a program in MIPS that takes in
    a user inputed hexidecimal number string as program arguments, 
    prints the program arguments to the output screen,
    prints the Integer string out in decimal  
    and then prints the integer string again in sorted decimal order 
    from smallest to greatest  

-------------------------------------------------------------------------------

FILES 
* Lab4.asm
	This file is the MIPs file containing the entire MIPS program

* Diagram.pdf
	This file contains the block diagram and the pseudocode that describes
	and outlines the program 

-------------------------------------------------------------------------------

INSTRUCTIONS 

Read the Diagram.pdf file to gain a top-level understanding of the program.
Boot up the Lab4.asm file on MARS and run the program after assembling it. 

-------------------------------------------------------------------------------

SOURCES
For implementing Arrays, printing arrays, and Bubble sort help:
	https://cupola.gettysburg.edu/cgi/viewcontent.cgi?article=1001&context=oer

Read for conversion to decimal:
	https://codeforwin.org/2015/09/c-program-to-convert-hexadecimal-to-decimal-number-system.html

Watched for array help, how much memory to allocate, how to place in array, etc
	https://www.youtube.com/watch?v=BfHcogmKM20

For Array printing inspiration
	https://www.youtube.com/watch?v=Vb8kuvxc4NE

For the use of "34" syscall 
	https://stackoverflow.com/questions/39820484/having-an-integer-and-printing-out-the-hexadecimal-in-mips


-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

Notes for self (SCRATCH):
	$a0 = # number fo args. argc
	$a1 = argv
	0 < $a0 <= 8
	
*	Might as well just make the array of size 8 by 32 bits and only use
	what I need. Save argc intoo $s0 or smtg

*	Going to need a print array function
	
*	Parse thru the string. Each pointer to the next element of the argv is 
		just the incrementation of 

*	need to convert from hex to deci     * lb - load byte
		0x2C
	ASCII 0 = 48(deci) and 30(hex) 
	ASCII 9 = 57(deci) and 39(hex)
	ASCII A = 65(deci) and 41(hex)
		

*	need to sort that deci string > Prof said bubble sort is easiest to imp

* 	Probably want an in-place sorting alg. printing out 



	Prog Arg:
		$a0 = argc
		$a1 => Address 1 => Address 2A => IS THIS JUST A NUMBER? just has to work on an int	first char of Argument A
				    Address 2B => first char of Arg B
				    *			*	
				    *			*
				    Address 2N		*



	What to store in an Array? store Address 1 in $s1 for ease

	Address 2N => array I think

	could put it in three arrays... 2 arrays perhaps. 

	printing an array... 

	Probably more than enough memory cap

	for loop to copy the arg array into allocated space?

	just print the original from the original place I think. 
	but that array is broken and segmented. 


	// go thru all the args
	for(i = 0; i< argc; i++){
		find the arg
		//for each argument go thru each char 
		while(charHere != '\0'){
			
			//copy this char into the Array	
		}
		put a space char into the array
	}

	Then we can print the array
	can print char by char but can we do the whole enchilada?

	screw it just print the chars. not dying for EC here just tryna survive n learn

	//for each element in the array
	//array_length = $s0 likely. All arrays are the same length
	for(i = 0; i < array_length; i++){
		print the char
		print a " " character
	}
	print \n 

	code in sections. Don't try to code up the whole enchilada then debug the W.E. yuk

	Each integer is 4 bytes. each hex # won't be bigger than an int.  
	
	Might have to code in the "0x" part w letters n shit ://


-------------------------------------------------------------------------------

Part B. Convert to deci

loop:
Skip two bytes 0x
read byte, store in $t0
if == \0 beq, 
    put in a space?-- unless it is the last one, then just \n -- maybe check loop? argc!
    if \0 then loop back and read the next one
if != \0
    if less than 0x40,
	subtract 0x30 or 48

    else: no wrong input, as long as x is discounted, thenshould be fine
	subtract 0x37 or 55 maybe 56/0x37

then load the next byte?
and the next?
how to determine if it is the first or second or third byte?
enter into array after sum the places
When I print integer, needs to be the hexidecimal equivilent of the decimal number
 if it is 16 to be printed then i need to have it = 0x0000...10
    

	
store into the array



#address at $a1/$s1 is the array of addresses 

#for each element in the address array which was can be $t2 $t0 is counter; $s0 is comparator
#    $t1 used to properly increment $s1  
#    load address stored in $s1 into $t2 
#//    follow the address. skip two bytes (0x)  
#    load 0 into $t3 #used to sum the numbers
#
#    load byte into $t4 from 2($t2) #this will skip two bytes I think 
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
#	    $t5 is 16's place         #still needs to be multiplied
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
#	    lb $t5, $a1   
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


# FUNCTION TO CONVERT TO DECIMAL
# if $a1 less than 0x40,
#	subtract 0x30 or 48
#
#    else: 
#	subtract 0x37 or 55  #source of error? 56/0x38? 
#	RETURN!

	 

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
			sge
			
				
			b p_loop	
		p_loop_end:


16 1 2730 0 1 256 273


#Sort Int Array
# for each index bubble it up
# for( i = 0; i < argc - 1 ; i++){
    
    for(j = 0; j < (argc - 1) - i; j++){
	if(A[j] > A[j+1]){
	    int temp = A[j];  ### COULD USE SUBROUTINE
	    A[j] = A[j+1];
            A[j+1] = temp;
	}
    }
  }
            $t0 being the counter
			li  $t1, 4
			mul $t1, $t0, $t1
			add $t2, $s1, $t1


0x111 0x101 0xAAB 0xABC 0x123 0x100 0x321 0x567
 273   257  2731  2748   291   256   801    1383
MF i got it 