#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Uno_Pins_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Uno_Pins_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=C:/ECE118/src/AD.c C:/ECE118/src/BOARD.c C:/ECE118/src/IO_Ports.c C:/ECE118/src/LED.c C:/ECE118/src/RC_Servo.c C:/ECE118/src/pwm.c C:/ECE118/src/serial.c C:/ECE118/src/timers.c "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Beacon_Detector.c" "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Bumpers.c" "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Motor_Driver.c" "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Sense_EventChecker.c" "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Solenoid_Driver.c" "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Tape_Sensors.c" "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Track_Wire_Sensor.c" C:/ECE118/src/ES_CheckEvents.c C:/ECE118/src/ES_Framework.c C:/ECE118/src/ES_KeyboardInput.c C:/ECE118/src/ES_PostList.c C:/ECE118/src/ES_Queue.c C:/ECE118/src/ES_TattleTale.c C:/ECE118/src/ES_Timers.c "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/EncoderEventChecker.c" "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/EncoderService.c"

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1975241074/AD.o ${OBJECTDIR}/_ext/1975241074/BOARD.o ${OBJECTDIR}/_ext/1975241074/IO_Ports.o ${OBJECTDIR}/_ext/1975241074/LED.o ${OBJECTDIR}/_ext/1975241074/RC_Servo.o ${OBJECTDIR}/_ext/1975241074/pwm.o ${OBJECTDIR}/_ext/1975241074/serial.o ${OBJECTDIR}/_ext/1975241074/timers.o ${OBJECTDIR}/_ext/777325913/Beacon_Detector.o ${OBJECTDIR}/_ext/777325913/Bumpers.o ${OBJECTDIR}/_ext/777325913/Motor_Driver.o ${OBJECTDIR}/_ext/777325913/Sense_EventChecker.o ${OBJECTDIR}/_ext/777325913/Solenoid_Driver.o ${OBJECTDIR}/_ext/777325913/Tape_Sensors.o ${OBJECTDIR}/_ext/777325913/Track_Wire_Sensor.o ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o ${OBJECTDIR}/_ext/1975241074/ES_Framework.o ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1975241074/ES_PostList.o ${OBJECTDIR}/_ext/1975241074/ES_Queue.o ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o ${OBJECTDIR}/_ext/1975241074/ES_Timers.o ${OBJECTDIR}/_ext/777325913/EncoderEventChecker.o ${OBJECTDIR}/_ext/777325913/EncoderService.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1975241074/AD.o.d ${OBJECTDIR}/_ext/1975241074/BOARD.o.d ${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d ${OBJECTDIR}/_ext/1975241074/LED.o.d ${OBJECTDIR}/_ext/1975241074/RC_Servo.o.d ${OBJECTDIR}/_ext/1975241074/pwm.o.d ${OBJECTDIR}/_ext/1975241074/serial.o.d ${OBJECTDIR}/_ext/1975241074/timers.o.d ${OBJECTDIR}/_ext/777325913/Beacon_Detector.o.d ${OBJECTDIR}/_ext/777325913/Bumpers.o.d ${OBJECTDIR}/_ext/777325913/Motor_Driver.o.d ${OBJECTDIR}/_ext/777325913/Sense_EventChecker.o.d ${OBJECTDIR}/_ext/777325913/Solenoid_Driver.o.d ${OBJECTDIR}/_ext/777325913/Tape_Sensors.o.d ${OBJECTDIR}/_ext/777325913/Track_Wire_Sensor.o.d ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d ${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d ${OBJECTDIR}/_ext/777325913/EncoderEventChecker.o.d ${OBJECTDIR}/_ext/777325913/EncoderService.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1975241074/AD.o ${OBJECTDIR}/_ext/1975241074/BOARD.o ${OBJECTDIR}/_ext/1975241074/IO_Ports.o ${OBJECTDIR}/_ext/1975241074/LED.o ${OBJECTDIR}/_ext/1975241074/RC_Servo.o ${OBJECTDIR}/_ext/1975241074/pwm.o ${OBJECTDIR}/_ext/1975241074/serial.o ${OBJECTDIR}/_ext/1975241074/timers.o ${OBJECTDIR}/_ext/777325913/Beacon_Detector.o ${OBJECTDIR}/_ext/777325913/Bumpers.o ${OBJECTDIR}/_ext/777325913/Motor_Driver.o ${OBJECTDIR}/_ext/777325913/Sense_EventChecker.o ${OBJECTDIR}/_ext/777325913/Solenoid_Driver.o ${OBJECTDIR}/_ext/777325913/Tape_Sensors.o ${OBJECTDIR}/_ext/777325913/Track_Wire_Sensor.o ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o ${OBJECTDIR}/_ext/1975241074/ES_Framework.o ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1975241074/ES_PostList.o ${OBJECTDIR}/_ext/1975241074/ES_Queue.o ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o ${OBJECTDIR}/_ext/1975241074/ES_Timers.o ${OBJECTDIR}/_ext/777325913/EncoderEventChecker.o ${OBJECTDIR}/_ext/777325913/EncoderService.o

# Source Files
SOURCEFILES=C:/ECE118/src/AD.c C:/ECE118/src/BOARD.c C:/ECE118/src/IO_Ports.c C:/ECE118/src/LED.c C:/ECE118/src/RC_Servo.c C:/ECE118/src/pwm.c C:/ECE118/src/serial.c C:/ECE118/src/timers.c C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Beacon_Detector.c C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Bumpers.c C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Motor_Driver.c C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Sense_EventChecker.c C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Solenoid_Driver.c C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Tape_Sensors.c C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Track_Wire_Sensor.c C:/ECE118/src/ES_CheckEvents.c C:/ECE118/src/ES_Framework.c C:/ECE118/src/ES_KeyboardInput.c C:/ECE118/src/ES_PostList.c C:/ECE118/src/ES_Queue.c C:/ECE118/src/ES_TattleTale.c C:/ECE118/src/ES_Timers.c C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/EncoderEventChecker.c C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/EncoderService.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
_/_=\\
ShExtension=.bat
Device=PIC32MX320F128H
ProjectDir="C:\Users\Abner\Downloads\ECE118Project\ece118-mech-final-project\New Folder\Uno_Pins_Test.X"
ProjectName=Uno_Pins_Test
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\Uno_Pins_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="Uno_Pins_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  .pre ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Uno_Pins_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="C:\ECE118\bootloader320.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1975241074/AD.o: C:/ECE118/src/AD.c  .generated_files/flags/default/123de15811a5cf331fa4751d69fbe5af9bf433bd .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/AD.o.d" -o ${OBJECTDIR}/_ext/1975241074/AD.o C:/ECE118/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/BOARD.o: C:/ECE118/src/BOARD.c  .generated_files/flags/default/b57845dd319ba4adc7783ec3c4d8ba67aca1c45 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/BOARD.o.d" -o ${OBJECTDIR}/_ext/1975241074/BOARD.o C:/ECE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/IO_Ports.o: C:/ECE118/src/IO_Ports.c  .generated_files/flags/default/4e89f885278666575546a2f867dc9dc261bd4050 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1975241074/IO_Ports.o C:/ECE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/LED.o: C:/ECE118/src/LED.c  .generated_files/flags/default/30f0e17c162dd8383008cb0a27575172d6bd16ac .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/LED.o.d" -o ${OBJECTDIR}/_ext/1975241074/LED.o C:/ECE118/src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/RC_Servo.o: C:/ECE118/src/RC_Servo.c  .generated_files/flags/default/abc7188f69be2d0f51aef222bac07c137cebcca .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1975241074/RC_Servo.o C:/ECE118/src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/pwm.o: C:/ECE118/src/pwm.c  .generated_files/flags/default/cfb92a0f96655bdd11dd229f4d686d9c7c96bed5 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/pwm.o.d" -o ${OBJECTDIR}/_ext/1975241074/pwm.o C:/ECE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/serial.o: C:/ECE118/src/serial.c  .generated_files/flags/default/990c85e01a5f5405e4a5f974140827d4578cd57 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/serial.o.d" -o ${OBJECTDIR}/_ext/1975241074/serial.o C:/ECE118/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/timers.o: C:/ECE118/src/timers.c  .generated_files/flags/default/988f19390d3d695580b22a08933140268e284a56 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/timers.o.d" -o ${OBJECTDIR}/_ext/1975241074/timers.o C:/ECE118/src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/Beacon_Detector.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/Beacon_Detector.c  .generated_files/flags/default/985b5c60dc8560b810b61427e17c29df9c936ffe .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/Beacon_Detector.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/Beacon_Detector.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/Beacon_Detector.o.d" -o ${OBJECTDIR}/_ext/777325913/Beacon_Detector.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Beacon_Detector.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/Bumpers.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/Bumpers.c  .generated_files/flags/default/81579c13238f82e4335951fbe85a1e13fde127ef .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/Bumpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/Bumpers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/Bumpers.o.d" -o ${OBJECTDIR}/_ext/777325913/Bumpers.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Bumpers.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/Motor_Driver.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/Motor_Driver.c  .generated_files/flags/default/48af4241a216989fb13e41df1bd6861c4aa7de36 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/Motor_Driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/Motor_Driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/Motor_Driver.o.d" -o ${OBJECTDIR}/_ext/777325913/Motor_Driver.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Motor_Driver.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/Sense_EventChecker.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/Sense_EventChecker.c  .generated_files/flags/default/1f0a5595cd3dbcde2b49c03272e27f4321755d5b .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/Sense_EventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/Sense_EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/Sense_EventChecker.o.d" -o ${OBJECTDIR}/_ext/777325913/Sense_EventChecker.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Sense_EventChecker.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/Solenoid_Driver.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/Solenoid_Driver.c  .generated_files/flags/default/4a1f6dd2aaa2864cf8dd6b65b99707cfcbb04ab3 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/Solenoid_Driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/Solenoid_Driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/Solenoid_Driver.o.d" -o ${OBJECTDIR}/_ext/777325913/Solenoid_Driver.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Solenoid_Driver.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/Tape_Sensors.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/Tape_Sensors.c  .generated_files/flags/default/417f6d97304fd8e01bb54b2eb7a26eda9d831f36 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/Tape_Sensors.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/Tape_Sensors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/Tape_Sensors.o.d" -o ${OBJECTDIR}/_ext/777325913/Tape_Sensors.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Tape_Sensors.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/Track_Wire_Sensor.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/Track_Wire_Sensor.c  .generated_files/flags/default/dbfa42b4bd10f789f864b560d9142340caff428e .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/Track_Wire_Sensor.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/Track_Wire_Sensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/Track_Wire_Sensor.o.d" -o ${OBJECTDIR}/_ext/777325913/Track_Wire_Sensor.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Track_Wire_Sensor.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o: C:/ECE118/src/ES_CheckEvents.c  .generated_files/flags/default/471cba51f9ade506d192f8516c071aa79cdcb05f .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o C:/ECE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Framework.o: C:/ECE118/src/ES_Framework.c  .generated_files/flags/default/aebf467411112badd5023aa272d8d1b50e95791b .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Framework.o C:/ECE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o: C:/ECE118/src/ES_KeyboardInput.c  .generated_files/flags/default/d3419ae5cce0479c69a3d3211ff1a1134b9ea5dc .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o C:/ECE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_PostList.o: C:/ECE118/src/ES_PostList.c  .generated_files/flags/default/13c4dfe77c07109abad29193cc21a8cf20839db4 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_PostList.o C:/ECE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Queue.o: C:/ECE118/src/ES_Queue.c  .generated_files/flags/default/62b07490002cdc0eb991163060b5e9a57254ae93 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Queue.o C:/ECE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o: C:/ECE118/src/ES_TattleTale.c  .generated_files/flags/default/8374ededf870e6675212c8877d5be9cb5dd2aba6 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o C:/ECE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Timers.o: C:/ECE118/src/ES_Timers.c  .generated_files/flags/default/64cebb92ca511db1b56a42d84b28f1a45c40cdee .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Timers.o C:/ECE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/EncoderEventChecker.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/EncoderEventChecker.c  .generated_files/flags/default/7d9dd49501d43d2c2087d644bc71112bf11306a8 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/EncoderEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/EncoderEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/EncoderEventChecker.o.d" -o ${OBJECTDIR}/_ext/777325913/EncoderEventChecker.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/EncoderEventChecker.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/EncoderService.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/EncoderService.c  .generated_files/flags/default/d99e1869d187ce2e4fed6a2fb1c02af35ff983a4 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/EncoderService.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/EncoderService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/EncoderService.o.d" -o ${OBJECTDIR}/_ext/777325913/EncoderService.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/EncoderService.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1975241074/AD.o: C:/ECE118/src/AD.c  .generated_files/flags/default/99ae8d7dc50d4f6e2eeae1378e9bbfe7849759c1 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/AD.o.d" -o ${OBJECTDIR}/_ext/1975241074/AD.o C:/ECE118/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/BOARD.o: C:/ECE118/src/BOARD.c  .generated_files/flags/default/d9b7db458149920c6f31a4b0ffeb2c5d7d4a8d3d .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/BOARD.o.d" -o ${OBJECTDIR}/_ext/1975241074/BOARD.o C:/ECE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/IO_Ports.o: C:/ECE118/src/IO_Ports.c  .generated_files/flags/default/d28e4350a8dd9b53b29834500df6cd1e79ce4c79 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1975241074/IO_Ports.o C:/ECE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/LED.o: C:/ECE118/src/LED.c  .generated_files/flags/default/9982fcea91b4499ccb80cd829d25a1dddfabec4 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/LED.o.d" -o ${OBJECTDIR}/_ext/1975241074/LED.o C:/ECE118/src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/RC_Servo.o: C:/ECE118/src/RC_Servo.c  .generated_files/flags/default/e454683ff656721eeb7ccd21d9699b2d711ffdc8 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1975241074/RC_Servo.o C:/ECE118/src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/pwm.o: C:/ECE118/src/pwm.c  .generated_files/flags/default/5c77d79ae384aa7bac715bb926ccd2b1d6445bd7 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/pwm.o.d" -o ${OBJECTDIR}/_ext/1975241074/pwm.o C:/ECE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/serial.o: C:/ECE118/src/serial.c  .generated_files/flags/default/f7dad710abbef926113a831e3b6389ba18b925b0 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/serial.o.d" -o ${OBJECTDIR}/_ext/1975241074/serial.o C:/ECE118/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/timers.o: C:/ECE118/src/timers.c  .generated_files/flags/default/1badd75d147dd1808f99f6cd1c58094da24b8f28 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/timers.o.d" -o ${OBJECTDIR}/_ext/1975241074/timers.o C:/ECE118/src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/Beacon_Detector.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/Beacon_Detector.c  .generated_files/flags/default/f3b3e08d209f9b2a4bafbcf1b9ecdcb286c2624d .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/Beacon_Detector.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/Beacon_Detector.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/Beacon_Detector.o.d" -o ${OBJECTDIR}/_ext/777325913/Beacon_Detector.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Beacon_Detector.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/Bumpers.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/Bumpers.c  .generated_files/flags/default/13ed613bb3acffe79bdf344f774cdcf0b8317e4f .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/Bumpers.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/Bumpers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/Bumpers.o.d" -o ${OBJECTDIR}/_ext/777325913/Bumpers.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Bumpers.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/Motor_Driver.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/Motor_Driver.c  .generated_files/flags/default/20df24f0f459132fa26394a516a19ec1ac3a740a .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/Motor_Driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/Motor_Driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/Motor_Driver.o.d" -o ${OBJECTDIR}/_ext/777325913/Motor_Driver.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Motor_Driver.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/Sense_EventChecker.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/Sense_EventChecker.c  .generated_files/flags/default/dde237fac00567efb14edf549228d21cd7c5a049 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/Sense_EventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/Sense_EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/Sense_EventChecker.o.d" -o ${OBJECTDIR}/_ext/777325913/Sense_EventChecker.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Sense_EventChecker.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/Solenoid_Driver.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/Solenoid_Driver.c  .generated_files/flags/default/77ef71334c191a6642d8f83bdf7b04ec35e440db .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/Solenoid_Driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/Solenoid_Driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/Solenoid_Driver.o.d" -o ${OBJECTDIR}/_ext/777325913/Solenoid_Driver.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Solenoid_Driver.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/Tape_Sensors.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/Tape_Sensors.c  .generated_files/flags/default/8febbd39938062fb077d7e448d09e623dbf57a9d .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/Tape_Sensors.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/Tape_Sensors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/Tape_Sensors.o.d" -o ${OBJECTDIR}/_ext/777325913/Tape_Sensors.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Tape_Sensors.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/Track_Wire_Sensor.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/Track_Wire_Sensor.c  .generated_files/flags/default/93cbacbb74f6e46cb2eda2a17684fc201ff4f9cc .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/Track_Wire_Sensor.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/Track_Wire_Sensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/Track_Wire_Sensor.o.d" -o ${OBJECTDIR}/_ext/777325913/Track_Wire_Sensor.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/Track_Wire_Sensor.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o: C:/ECE118/src/ES_CheckEvents.c  .generated_files/flags/default/e83f3d6a4ff7e00ce6c4b38ce28d67410db96810 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o C:/ECE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Framework.o: C:/ECE118/src/ES_Framework.c  .generated_files/flags/default/400f9218261528cac7698f6e93482dc5b2713dbf .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Framework.o C:/ECE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o: C:/ECE118/src/ES_KeyboardInput.c  .generated_files/flags/default/cd95be01715225ae7b3ca04804f59a07d14c5118 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o C:/ECE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_PostList.o: C:/ECE118/src/ES_PostList.c  .generated_files/flags/default/97d7e329de487ae3ce5dfbe2f2586403c3de4df1 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_PostList.o C:/ECE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Queue.o: C:/ECE118/src/ES_Queue.c  .generated_files/flags/default/3678a9112f68b5a3571789e289b4a4e536036824 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Queue.o C:/ECE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o: C:/ECE118/src/ES_TattleTale.c  .generated_files/flags/default/a7996d4e143a87cd9af2bbe83d1a63669fbf3eae .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o C:/ECE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Timers.o: C:/ECE118/src/ES_Timers.c  .generated_files/flags/default/29a2e390331f1c7079557339548c880335417d4c .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Timers.o C:/ECE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/EncoderEventChecker.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/EncoderEventChecker.c  .generated_files/flags/default/96dc3d4bd9de069c081b5375fb8249095c3e8661 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/EncoderEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/EncoderEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/EncoderEventChecker.o.d" -o ${OBJECTDIR}/_ext/777325913/EncoderEventChecker.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/EncoderEventChecker.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/777325913/EncoderService.o: C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New\ Folder/Uno_Pins_Test.X/EncoderService.c  .generated_files/flags/default/61ee941a719eb7bb71f45d5d9b0aae21280ae8cc .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/777325913" 
	@${RM} ${OBJECTDIR}/_ext/777325913/EncoderService.o.d 
	@${RM} ${OBJECTDIR}/_ext/777325913/EncoderService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -DEVENTCHECKER_TEST -I"." -I"C:/ECE118/include" -I"C:/ECE118/src" -I"../../../../../Projects/amspatin/projects/Lab0/Slugbot_HSM.X" -MP -MMD -MF "${OBJECTDIR}/_ext/777325913/EncoderService.o.d" -o ${OBJECTDIR}/_ext/777325913/EncoderService.o "C:/Users/Abner/Downloads/ECE118Project/ece118-mech-final-project/New Folder/Uno_Pins_Test.X/EncoderService.c"    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Uno_Pins_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    C:/ECE118/bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Uno_Pins_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Uno_Pins_Test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   C:/ECE118/bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Uno_Pins_Test.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Uno_Pins_Test.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif

.pre:
	@echo "--------------------------------------"
	@echo "User defined pre-build step: [python C:\ECE118\scripts\Enum_To_String.py]"
	@python C:\ECE118\scripts\Enum_To_String.py
	@echo "--------------------------------------"

# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
