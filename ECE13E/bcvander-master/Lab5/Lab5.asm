###############################################################################
#
#	Lab5: Functions and Graphics	
#	Author: Vander Klay, Benjamin
#			bcvander
#			6/5/2020
#			
#	Class: CSE 12/L Spring 2020 
#			UCSC, Professor Logan
#
#	Description: 
#
#	This lab, implements functions that perform some 
#	primitive graphics operations on a small simulated display. 
#	These functions clear the entire display to a color, 
#	display a filled colored circle and display an unfilled colored circle
#	using a memory-mapped bitmap graphics display in MARS.
#	This is done utilizing Arrays, memory-mapped input/output,
#	Functions, Macros, and the MIPS stack
#
#	Notes: This program is intended to be run on the MARS IDE
#
###############################################################################


###############################################################################
#					PsuedoCode
#
#
###############################################################################



# Macro that stores the value in %reg on the stack 
#  and moves the stack pointer.
.macro push(%reg) #order could be wrong
	
	addi $sp, $sp, -4
	sw   %reg, ($sp)
.end_macro 

# Macro takes the value on the top of the stack and 
#  loads it into %reg then moves the stack pointer.
.macro pop(%reg)
	lw %reg ($sp)
	addi $sp, $sp, 4
	
.end_macro

# Macro that takes as input coordinates in the format
# (0x00XX00YY) and returns 0x000000XX in %x and
# returns 0x000000YY in %y
.macro getCoordinates(%input %x %y)
	#
	srl %x, %input, 16
	#dump the XX values and shift back
	sll %y, %input, 16
	srl %y, %y,     16
	

.end_macro

# Macro that takes Coordinates in (%x,%y) where
# %x = 0x000000XX and %y= 0x000000YY and
# returns %output = (0x00XX00YY)
.macro formatCoordinates(%output %x %y)
	sll %x, %x, 16
	add %output, %x, %y
	
.end_macro 


.data
originAddress: .word 0xFFFF0000

.text
j done
    
    done: nop
    li $v0 10 
    syscall

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#  Subroutines defined below
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#*****************************************************
#Clear_bitmap: Given a color, will fill the bitmap display with that color.
#   Inputs:
#    $a0 = Color in format (0x00RRGGBB) 
#   Outputs:
#    No register outputs
#    Side-Effects: 
#    Colors the Bitmap display all the same color
#*****************************************************
clear_bitmap: nop
# Save the 3 s registers used
	addi $sp, $sp, -12
	sw   $ra,   ($sp)
	sw   $s0,  4($sp)
    sw   $s1,  8($sp)
   

    # $s0 being the counter
    li $s0, 0xffff0000
    # $s1 being the end marker 
    li $s1, 0xfffffffc
    
    clear_map:    
	beq $s0, $s1, clear_end
		sw   $a0, ($s0)
		addi $s0,  $s0, 4 
		j clear_map
	clear_end:
	
	#Load the saved registers back in	

	lw   $s1,  8($sp)
	lw   $s0,  4($sp)	
	lw   $ra,   ($sp)
	addi $sp,    $sp, 12
	jr   $ra
	
#*****************************************************
# draw_pixel:
#  Given a coordinate in $a0, sets corresponding value
#  in memory to the color given by $a1	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of pixel in format (0x00XX00YY)
#    $a1 = color of pixel in format (0x00RRGGBB)
#   Outputs:
#    No register outputs
#    
#	 $s0 = XX
#    $s1 = YY
#    address associated w pixel coords= 0xfff_0000 + (4 * ((XX * ROW_SIZE) + YY))
#*****************************************************
draw_pixel: nop
	#save the $s registers
	addi $sp, $sp, -20
	sw   $ra,    ($sp)
	sw   $s0,   4($sp)
    sw   $s1,   8($sp)
    sw   $s2,  12($sp)
    sw   $s3,  16($sp)
    
    # Get coords
    getCoordinates($a0, $s0, $s1)
#    address associated w pixel coords = 0xfff_0000 + (4 * ((XX * ROW_SIZE) + YY))    
#    MIGHT WANT TO ERROR CHECK	MAY CAUSE SEG FAULTS

	    
        
            
    li   $s2, 128
    li   $s3, 4
   
    mul  $s0, $s0, $s2   
    add  $s0, $s0, $s1
    mul  $s0, $s0, $s3
    addi $s0, $s0, 0xffff0000
    
    # set the pixel color
    sw   $a1, ($s0)
    
	# load the registers
	lw   $s3,  16($sp)
	lw   $s2,  12($sp)
	lw   $s1,   8($sp)
	lw   $s0,   4($sp)	
	lw   $ra,    ($sp)
	addi $sp,     $sp, 20
	jr   $ra
	
#*****************************************************
# get_pixel:
#  Given a coordinate, returns the color of that pixel	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of pixel in format (0x00XX00YY)
#   Outputs:
#    Returns pixel color in $v0 in format (0x00RRGGBB)
#    
#    (0xfff_0000 + (XX * ROW_SIZE) + YY)
#*****************************************************
get_pixel: nop
	# Save the registers
	addi $sp, $sp, -20
	sw   $ra,    ($sp)
	sw   $s0,   4($sp)
    sw   $s1,   8($sp)
    sw   $s2,  12($sp)
    sw   $s3,  16($sp)
    
    # Get coords
    getCoordinates($a0, $s0, $s1)
#    address associated w pixel coords = 0xfff_0000 + (4 * ((XX * ROW_SIZE) + YY))    
    li   $s2, 128
    li   $s3, 4
   
    mul  $s0, $s0, $s2   
    add  $s0, $s0, $s1
    mul  $s0, $s0, $s3
    addi $s0, $s0, 0xffff0000
    
    # load the pixel color
    lw   $v0, ($s0)
    
	# load the registers
	lw   $s3,  16($sp)
	lw   $s2,  12($sp)
	lw   $s1,   8($sp)
	lw   $s0,   4($sp)	
	lw   $ra,    ($sp)
	addi $sp,     $sp, 20
	jr $ra

#***********************************************
# draw_solid_circle:
#  Considering a square arround the circle to be drawn  
#  iterate through the square points and if the point 
#  lies inside the circle (x - xc)^2 + (y - yc)^2 = r^2
#  then plot it.
#-----------------------------------------------------
# draw_solid_circle(int xc, int yc, int r) 
#    xmin = xc-r
#    xmax = xc+r
#    ymin = yc-r
#    ymax = yc+r
#    for (i = xmin; i <= xmax; i++) 
#        for (j = ymin; j <= ymax; j++) 
#            a = (i - xc)*(i - xc) + (j - yc)*(j - yc)	 
#            if (a < r*r ) 
#                draw_pixel(x,y) 	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of circle center in format (0x00XX00YY)
#    $a1 = radius of the circle
#    $a2 = color in format (0x00RRGGBB)
#   Outputs:
#    No register outputs
#
# ---------------------------------------------------
#	 REGISTER CONVENTIONS:
#    $s0 = xc
#    $s1 = yc
#    $t0 = xmin / outer counter
#    $t1 = xmax / outer marker
#    $t2 = ymin / inner counter
#    $t3 = ymax / inner marker
#                   // $t4 = i //outer counter
#                   // $t5 = j //inner counter
#    $t4 = a = (i – xc)*(i – xc)  //in the algorithm
#    $t5 = (j – yc)*(j – yc) 
#	 $t6 = r * r // for the final if statement
#
#***************************************************
draw_solid_circle: nop
    # Save Registers
    addi $sp,     $sp, -16
	sw   $ra,    ($sp)
	sw   $s0,   4($sp)
    sw   $s1,   8($sp)
    sw   $s2,  12($sp)
    
    # Uses temp registers because it is a callee 
    # the subroutines do not use temp functions 
    
    # get coords
    getCoordinates($a0, $s0, $s1)
    # set $s2 as radius
    move $s2, $a1
    #move the RGB color to $a0 for draw_pixel
    move $a1, $a2
    
    # Start Algorithm
    # SETUP
    # xmin
    sub $t0, $s0, $s2
    #lw $t9, 1($a0)
    # xmax
    add $t1, $s0, $s2
    #ymin
    sub $t2, $s1, $s2
    #ymax
    add $t3, $s1, $s2
    
    #counters are the xmin && ymin
    # LOOP
    solid_outer:
    	bgt $t0, $t1, solid_outer_end
    		# recalculate inside loop?
    		sub $t2, $s1, $s2
    		solid_inner:
    		
	     		bgt $t2, $t3, solid_inner_end
	   	 			# left hand side of +
	    			sub $t4, $t0, $s0
	   	 			mul $t4, $t4, $t4
	    			# right hand side of +
	    			sub $t5, $t2, $s1
	    			mul $t5, $t5, $t5
	    			# a = ...
	    			add $t4, $t4, $t5
	    			# r * r
	    			mul $t6, $s2, $s2
	    		
	    			# if statement
	    			bge $t4, $t6, dont_draw
	    				# set the coordinates
	    				formatCoordinates($a0, $t0, $t2)
	    				#lw $t9, 1($a0)
	    				jal draw_pixel
	    				
	    			dont_draw:
	    			# increment by 1 because we are in format: 0x00XX00YY
	    			addi $t2, $t2, 1
					j solid_inner
			solid_inner_end:	
			addi $t0, $t0, 1
		j solid_outer
	solid_outer_end:
	#lw $t9, ($a0)
	
	# End Algorithm 
	
	# load the registers
	
	lw   $s2,  12($sp)
	lw   $s1,   8($sp)
	lw   $s0,   4($sp)	
	lw   $ra,    ($sp)
	addi $sp,     $sp, 16
	jr   $ra
		
#***********************************************
# draw_circle:
#  Given the coordinates of the center of the circle
#  plot the circle using the Bresenham's circle 
#  drawing algorithm 	
#-----------------------------------------------------
# draw_circle(xc, yc, r) 
#    x = 0 
#    y = r 
#    d = 3 - 2 * r 
#    draw_circle_pixels(xc, yc, x, y) 
#    while (y >= x) 
#        x=x+1 
#        if (d > 0) 
#            y=y-1  
#            d = d + 4 * (x - y) + 10 
#        else
#            d = d + 4 * x + 6 
#        draw_circle_pixels(xc, yc, x, y) 	
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of the circle center in format (0x00XX00YY)
#    $a1 = radius of the circle
#    $a2 = color of line in format (0x00RRGGBB)
#   Outputs:
#    No register outputs
#***************************************************
draw_circle: nop
	
	jr $ra
	
#*****************************************************
# draw_circle_pixels:
#  Function to draw the circle pixels 
#  using the octans' symmetry
#-----------------------------------------------------
# draw_circle_pixels(xc, yc, x, y)  
#    draw_pixel(xc+x, yc+y) 
#    draw_pixel(xc-x, yc+y)
#    draw_pixel(xc+x, yc-y)
#    draw_pixel(xc-x, yc-y)
#    draw_pixel(xc+y, yc+x)
#    draw_pixel(xc-y, yc+x)
#    draw_pixel(xc+y, yc-x)
#    draw_pixel(xc-y, yc-x)
#-----------------------------------------------------
#   Inputs:
#    $a0 = coordinates of circle center in format (0x00XX00YY)
#    $a1 = color of pixel in format (0x00RRGGBB)
#    $a2 = current x value from the Bresenham's circle algorithm
#    $a3 = current y value from the Bresenham's circle algorithm
#   Outputs:
#    No register outputs	
#*****************************************************
draw_circle_pixels: nop
	
	jr $ra