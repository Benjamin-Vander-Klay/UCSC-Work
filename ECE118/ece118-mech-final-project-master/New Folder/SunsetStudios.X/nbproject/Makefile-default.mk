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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SunsetStudios.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/SunsetStudios.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
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
SOURCEFILES_QUOTED_IF_SPACED=C:/ECE118/src/AD.c C:/ECE118/src/BOARD.c C:/ECE118/src/serial.c C:/ECE118/src/ES_CheckEvents.c C:/ECE118/src/ES_Framework.c C:/ECE118/src/ES_KeyboardInput.c C:/ECE118/src/ES_PostList.c C:/ECE118/src/ES_Queue.c C:/ECE118/src/ES_TattleTale.c C:/ECE118/src/ES_Timers.c C:/ECE118/src/IO_Ports.c C:/ECE118/src/LED.c C:/ECE118/src/pwm.c SimpleFunctionService.c Beacon_Detector.c Bumpers.c Sense_EventChecker.c Solenoid_Driver.c Tape_Sensors.c Track_Wire_Sensor.c ../../Encoder_Test.X/EncoderService.c ../../Encoder_Test.X/EncoderEventChecker.c ../../Encoder_Test.X/Motor_Driver.c TopHSM.c Final_ES_Main.c Bumpers_Gen_v1SubHSM.c ActiveSearchSubHSM.c FindTapeSubHSM.c TowerScopeSubHSM.c TowerSubHSM.c TowerApproachSubHSM.c CircleTowerSubHSM.c CorrectSideFoundSubHSM.c DeadBotAvoidSubHSM.c CorrectHoleFoundSubHSM.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1975241074/AD.o ${OBJECTDIR}/_ext/1975241074/BOARD.o ${OBJECTDIR}/_ext/1975241074/serial.o ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o ${OBJECTDIR}/_ext/1975241074/ES_Framework.o ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1975241074/ES_PostList.o ${OBJECTDIR}/_ext/1975241074/ES_Queue.o ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o ${OBJECTDIR}/_ext/1975241074/ES_Timers.o ${OBJECTDIR}/_ext/1975241074/IO_Ports.o ${OBJECTDIR}/_ext/1975241074/LED.o ${OBJECTDIR}/_ext/1975241074/pwm.o ${OBJECTDIR}/SimpleFunctionService.o ${OBJECTDIR}/Beacon_Detector.o ${OBJECTDIR}/Bumpers.o ${OBJECTDIR}/Sense_EventChecker.o ${OBJECTDIR}/Solenoid_Driver.o ${OBJECTDIR}/Tape_Sensors.o ${OBJECTDIR}/Track_Wire_Sensor.o ${OBJECTDIR}/_ext/2062664799/EncoderService.o ${OBJECTDIR}/_ext/2062664799/EncoderEventChecker.o ${OBJECTDIR}/_ext/2062664799/Motor_Driver.o ${OBJECTDIR}/TopHSM.o ${OBJECTDIR}/Final_ES_Main.o ${OBJECTDIR}/Bumpers_Gen_v1SubHSM.o ${OBJECTDIR}/ActiveSearchSubHSM.o ${OBJECTDIR}/FindTapeSubHSM.o ${OBJECTDIR}/TowerScopeSubHSM.o ${OBJECTDIR}/TowerSubHSM.o ${OBJECTDIR}/TowerApproachSubHSM.o ${OBJECTDIR}/CircleTowerSubHSM.o ${OBJECTDIR}/CorrectSideFoundSubHSM.o ${OBJECTDIR}/DeadBotAvoidSubHSM.o ${OBJECTDIR}/CorrectHoleFoundSubHSM.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1975241074/AD.o.d ${OBJECTDIR}/_ext/1975241074/BOARD.o.d ${OBJECTDIR}/_ext/1975241074/serial.o.d ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d ${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d ${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d ${OBJECTDIR}/_ext/1975241074/LED.o.d ${OBJECTDIR}/_ext/1975241074/pwm.o.d ${OBJECTDIR}/SimpleFunctionService.o.d ${OBJECTDIR}/Beacon_Detector.o.d ${OBJECTDIR}/Bumpers.o.d ${OBJECTDIR}/Sense_EventChecker.o.d ${OBJECTDIR}/Solenoid_Driver.o.d ${OBJECTDIR}/Tape_Sensors.o.d ${OBJECTDIR}/Track_Wire_Sensor.o.d ${OBJECTDIR}/_ext/2062664799/EncoderService.o.d ${OBJECTDIR}/_ext/2062664799/EncoderEventChecker.o.d ${OBJECTDIR}/_ext/2062664799/Motor_Driver.o.d ${OBJECTDIR}/TopHSM.o.d ${OBJECTDIR}/Final_ES_Main.o.d ${OBJECTDIR}/Bumpers_Gen_v1SubHSM.o.d ${OBJECTDIR}/ActiveSearchSubHSM.o.d ${OBJECTDIR}/FindTapeSubHSM.o.d ${OBJECTDIR}/TowerScopeSubHSM.o.d ${OBJECTDIR}/TowerSubHSM.o.d ${OBJECTDIR}/TowerApproachSubHSM.o.d ${OBJECTDIR}/CircleTowerSubHSM.o.d ${OBJECTDIR}/CorrectSideFoundSubHSM.o.d ${OBJECTDIR}/DeadBotAvoidSubHSM.o.d ${OBJECTDIR}/CorrectHoleFoundSubHSM.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1975241074/AD.o ${OBJECTDIR}/_ext/1975241074/BOARD.o ${OBJECTDIR}/_ext/1975241074/serial.o ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o ${OBJECTDIR}/_ext/1975241074/ES_Framework.o ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1975241074/ES_PostList.o ${OBJECTDIR}/_ext/1975241074/ES_Queue.o ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o ${OBJECTDIR}/_ext/1975241074/ES_Timers.o ${OBJECTDIR}/_ext/1975241074/IO_Ports.o ${OBJECTDIR}/_ext/1975241074/LED.o ${OBJECTDIR}/_ext/1975241074/pwm.o ${OBJECTDIR}/SimpleFunctionService.o ${OBJECTDIR}/Beacon_Detector.o ${OBJECTDIR}/Bumpers.o ${OBJECTDIR}/Sense_EventChecker.o ${OBJECTDIR}/Solenoid_Driver.o ${OBJECTDIR}/Tape_Sensors.o ${OBJECTDIR}/Track_Wire_Sensor.o ${OBJECTDIR}/_ext/2062664799/EncoderService.o ${OBJECTDIR}/_ext/2062664799/EncoderEventChecker.o ${OBJECTDIR}/_ext/2062664799/Motor_Driver.o ${OBJECTDIR}/TopHSM.o ${OBJECTDIR}/Final_ES_Main.o ${OBJECTDIR}/Bumpers_Gen_v1SubHSM.o ${OBJECTDIR}/ActiveSearchSubHSM.o ${OBJECTDIR}/FindTapeSubHSM.o ${OBJECTDIR}/TowerScopeSubHSM.o ${OBJECTDIR}/TowerSubHSM.o ${OBJECTDIR}/TowerApproachSubHSM.o ${OBJECTDIR}/CircleTowerSubHSM.o ${OBJECTDIR}/CorrectSideFoundSubHSM.o ${OBJECTDIR}/DeadBotAvoidSubHSM.o ${OBJECTDIR}/CorrectHoleFoundSubHSM.o

# Source Files
SOURCEFILES=C:/ECE118/src/AD.c C:/ECE118/src/BOARD.c C:/ECE118/src/serial.c C:/ECE118/src/ES_CheckEvents.c C:/ECE118/src/ES_Framework.c C:/ECE118/src/ES_KeyboardInput.c C:/ECE118/src/ES_PostList.c C:/ECE118/src/ES_Queue.c C:/ECE118/src/ES_TattleTale.c C:/ECE118/src/ES_Timers.c C:/ECE118/src/IO_Ports.c C:/ECE118/src/LED.c C:/ECE118/src/pwm.c SimpleFunctionService.c Beacon_Detector.c Bumpers.c Sense_EventChecker.c Solenoid_Driver.c Tape_Sensors.c Track_Wire_Sensor.c ../../Encoder_Test.X/EncoderService.c ../../Encoder_Test.X/EncoderEventChecker.c ../../Encoder_Test.X/Motor_Driver.c TopHSM.c Final_ES_Main.c Bumpers_Gen_v1SubHSM.c ActiveSearchSubHSM.c FindTapeSubHSM.c TowerScopeSubHSM.c TowerSubHSM.c TowerApproachSubHSM.c CircleTowerSubHSM.c CorrectSideFoundSubHSM.c DeadBotAvoidSubHSM.c CorrectHoleFoundSubHSM.c



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

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/SunsetStudios.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="..\..\..\..\..\..\..\ECE118\bootloader320.ld"
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
${OBJECTDIR}/_ext/1975241074/AD.o: C:/ECE118/src/AD.c  .generated_files/flags/default/9575935463805d2037071a6a75c120ece2a1fbb4 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/AD.o.d" -o ${OBJECTDIR}/_ext/1975241074/AD.o C:/ECE118/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/BOARD.o: C:/ECE118/src/BOARD.c  .generated_files/flags/default/63a0a2e0bf9ed77ab25ce178426545528067a596 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/BOARD.o.d" -o ${OBJECTDIR}/_ext/1975241074/BOARD.o C:/ECE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/serial.o: C:/ECE118/src/serial.c  .generated_files/flags/default/b6ef2088613def551a567de09a1d5cf9cac70f6 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/serial.o.d" -o ${OBJECTDIR}/_ext/1975241074/serial.o C:/ECE118/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o: C:/ECE118/src/ES_CheckEvents.c  .generated_files/flags/default/c9440d873b849edefbd554019b1389bb9752f2ba .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o C:/ECE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Framework.o: C:/ECE118/src/ES_Framework.c  .generated_files/flags/default/4261e9eecc7c2c5f1de099f1e7b60a3aecf2e612 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Framework.o C:/ECE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o: C:/ECE118/src/ES_KeyboardInput.c  .generated_files/flags/default/1bcf2d9f399e2625fa986f348a0d04d66d969eac .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o C:/ECE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_PostList.o: C:/ECE118/src/ES_PostList.c  .generated_files/flags/default/98179669686487621d100423d9b3d690d8d66746 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_PostList.o C:/ECE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Queue.o: C:/ECE118/src/ES_Queue.c  .generated_files/flags/default/ac8284bcfe8fe6ccb0a2fc4bbf6ae440fd25730e .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Queue.o C:/ECE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o: C:/ECE118/src/ES_TattleTale.c  .generated_files/flags/default/a5e739cf029c8a3667fa7ada71b15971007c1f9a .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o C:/ECE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Timers.o: C:/ECE118/src/ES_Timers.c  .generated_files/flags/default/5f3c22f1ad66951c92df1092345d7514ac127035 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Timers.o C:/ECE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/IO_Ports.o: C:/ECE118/src/IO_Ports.c  .generated_files/flags/default/7ecaa6ad3d84b6544c5dc01825285f8765ce742d .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1975241074/IO_Ports.o C:/ECE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/LED.o: C:/ECE118/src/LED.c  .generated_files/flags/default/f1e67c483b7b9c33400435404906f8a4fecdbb9 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/LED.o.d" -o ${OBJECTDIR}/_ext/1975241074/LED.o C:/ECE118/src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/pwm.o: C:/ECE118/src/pwm.c  .generated_files/flags/default/ff16aea7613ec274329750cf3e04f9e32da504d3 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/pwm.o.d" -o ${OBJECTDIR}/_ext/1975241074/pwm.o C:/ECE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/SimpleFunctionService.o: SimpleFunctionService.c  .generated_files/flags/default/34d60a19fdc5e67434828d25ba180e41d7af22e4 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SimpleFunctionService.o.d 
	@${RM} ${OBJECTDIR}/SimpleFunctionService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/SimpleFunctionService.o.d" -o ${OBJECTDIR}/SimpleFunctionService.o SimpleFunctionService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Beacon_Detector.o: Beacon_Detector.c  .generated_files/flags/default/aefeff738fa47b5135369445100d607225243c0e .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Beacon_Detector.o.d 
	@${RM} ${OBJECTDIR}/Beacon_Detector.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Beacon_Detector.o.d" -o ${OBJECTDIR}/Beacon_Detector.o Beacon_Detector.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Bumpers.o: Bumpers.c  .generated_files/flags/default/8b5345930a96b81bfc38d245193ed27d852517a .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Bumpers.o.d 
	@${RM} ${OBJECTDIR}/Bumpers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Bumpers.o.d" -o ${OBJECTDIR}/Bumpers.o Bumpers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Sense_EventChecker.o: Sense_EventChecker.c  .generated_files/flags/default/5af246038c7d0e7f1e8f965236cd859a668ffd8f .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Sense_EventChecker.o.d 
	@${RM} ${OBJECTDIR}/Sense_EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Sense_EventChecker.o.d" -o ${OBJECTDIR}/Sense_EventChecker.o Sense_EventChecker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Solenoid_Driver.o: Solenoid_Driver.c  .generated_files/flags/default/f6d042fc18373d55bd366b48691f0ff0f7a5e3f5 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Solenoid_Driver.o.d 
	@${RM} ${OBJECTDIR}/Solenoid_Driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Solenoid_Driver.o.d" -o ${OBJECTDIR}/Solenoid_Driver.o Solenoid_Driver.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Tape_Sensors.o: Tape_Sensors.c  .generated_files/flags/default/56e0ea9e4c21c08cb1c4bce68f267634729df2ce .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Tape_Sensors.o.d 
	@${RM} ${OBJECTDIR}/Tape_Sensors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Tape_Sensors.o.d" -o ${OBJECTDIR}/Tape_Sensors.o Tape_Sensors.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Track_Wire_Sensor.o: Track_Wire_Sensor.c  .generated_files/flags/default/2ba30544af3459264bc9ddea7d5a78350fa9ad50 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Track_Wire_Sensor.o.d 
	@${RM} ${OBJECTDIR}/Track_Wire_Sensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Track_Wire_Sensor.o.d" -o ${OBJECTDIR}/Track_Wire_Sensor.o Track_Wire_Sensor.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062664799/EncoderService.o: ../../Encoder_Test.X/EncoderService.c  .generated_files/flags/default/dba73f79cc442bf647f3718d3a22fbf2a1ef6905 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/2062664799" 
	@${RM} ${OBJECTDIR}/_ext/2062664799/EncoderService.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062664799/EncoderService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/2062664799/EncoderService.o.d" -o ${OBJECTDIR}/_ext/2062664799/EncoderService.o ../../Encoder_Test.X/EncoderService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062664799/EncoderEventChecker.o: ../../Encoder_Test.X/EncoderEventChecker.c  .generated_files/flags/default/a1f519b6f9fff81d63fba1b6ff33934f10e82667 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/2062664799" 
	@${RM} ${OBJECTDIR}/_ext/2062664799/EncoderEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062664799/EncoderEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/2062664799/EncoderEventChecker.o.d" -o ${OBJECTDIR}/_ext/2062664799/EncoderEventChecker.o ../../Encoder_Test.X/EncoderEventChecker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062664799/Motor_Driver.o: ../../Encoder_Test.X/Motor_Driver.c  .generated_files/flags/default/f67285d88392f5f5d2aaa9713456e8588d0b9b03 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/2062664799" 
	@${RM} ${OBJECTDIR}/_ext/2062664799/Motor_Driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062664799/Motor_Driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/2062664799/Motor_Driver.o.d" -o ${OBJECTDIR}/_ext/2062664799/Motor_Driver.o ../../Encoder_Test.X/Motor_Driver.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TopHSM.o: TopHSM.c  .generated_files/flags/default/3ebf50ab84a85b905e3fa1ca0be1b4a855a66b5b .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TopHSM.o.d 
	@${RM} ${OBJECTDIR}/TopHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/TopHSM.o.d" -o ${OBJECTDIR}/TopHSM.o TopHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Final_ES_Main.o: Final_ES_Main.c  .generated_files/flags/default/5e0799ee6328ee50d30eb6a063c3dd56d55417ce .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Final_ES_Main.o.d 
	@${RM} ${OBJECTDIR}/Final_ES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Final_ES_Main.o.d" -o ${OBJECTDIR}/Final_ES_Main.o Final_ES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Bumpers_Gen_v1SubHSM.o: Bumpers_Gen_v1SubHSM.c  .generated_files/flags/default/61372b4895495805098028312926fde8a23a865 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Bumpers_Gen_v1SubHSM.o.d 
	@${RM} ${OBJECTDIR}/Bumpers_Gen_v1SubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Bumpers_Gen_v1SubHSM.o.d" -o ${OBJECTDIR}/Bumpers_Gen_v1SubHSM.o Bumpers_Gen_v1SubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ActiveSearchSubHSM.o: ActiveSearchSubHSM.c  .generated_files/flags/default/f69d00d996cb5601a2b29dc0e7aa3a3d410b0ee2 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ActiveSearchSubHSM.o.d 
	@${RM} ${OBJECTDIR}/ActiveSearchSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/ActiveSearchSubHSM.o.d" -o ${OBJECTDIR}/ActiveSearchSubHSM.o ActiveSearchSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FindTapeSubHSM.o: FindTapeSubHSM.c  .generated_files/flags/default/c17af04d200e92d0c7bfbf0e8396132c534f65ef .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FindTapeSubHSM.o.d 
	@${RM} ${OBJECTDIR}/FindTapeSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/FindTapeSubHSM.o.d" -o ${OBJECTDIR}/FindTapeSubHSM.o FindTapeSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TowerScopeSubHSM.o: TowerScopeSubHSM.c  .generated_files/flags/default/ae4f5fb34c523be4364a9c5963e75a3607b573e1 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TowerScopeSubHSM.o.d 
	@${RM} ${OBJECTDIR}/TowerScopeSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/TowerScopeSubHSM.o.d" -o ${OBJECTDIR}/TowerScopeSubHSM.o TowerScopeSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TowerSubHSM.o: TowerSubHSM.c  .generated_files/flags/default/1f3175f6e4e39469cadd77882675d0ef81b22d01 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TowerSubHSM.o.d 
	@${RM} ${OBJECTDIR}/TowerSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/TowerSubHSM.o.d" -o ${OBJECTDIR}/TowerSubHSM.o TowerSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TowerApproachSubHSM.o: TowerApproachSubHSM.c  .generated_files/flags/default/aee66592c887f322f0996c0eda142220ecab7bab .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TowerApproachSubHSM.o.d 
	@${RM} ${OBJECTDIR}/TowerApproachSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/TowerApproachSubHSM.o.d" -o ${OBJECTDIR}/TowerApproachSubHSM.o TowerApproachSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/CircleTowerSubHSM.o: CircleTowerSubHSM.c  .generated_files/flags/default/6e6387f8aa7c639652f74f0cdd805c37c205bd02 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CircleTowerSubHSM.o.d 
	@${RM} ${OBJECTDIR}/CircleTowerSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/CircleTowerSubHSM.o.d" -o ${OBJECTDIR}/CircleTowerSubHSM.o CircleTowerSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/CorrectSideFoundSubHSM.o: CorrectSideFoundSubHSM.c  .generated_files/flags/default/51166a512f61e80d9ead0eda53f4a435be5e14a1 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CorrectSideFoundSubHSM.o.d 
	@${RM} ${OBJECTDIR}/CorrectSideFoundSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/CorrectSideFoundSubHSM.o.d" -o ${OBJECTDIR}/CorrectSideFoundSubHSM.o CorrectSideFoundSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/DeadBotAvoidSubHSM.o: DeadBotAvoidSubHSM.c  .generated_files/flags/default/8af58d1d955097448d0a1ef39b16706ff94cbbcf .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DeadBotAvoidSubHSM.o.d 
	@${RM} ${OBJECTDIR}/DeadBotAvoidSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/DeadBotAvoidSubHSM.o.d" -o ${OBJECTDIR}/DeadBotAvoidSubHSM.o DeadBotAvoidSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/CorrectHoleFoundSubHSM.o: CorrectHoleFoundSubHSM.c  .generated_files/flags/default/211528b2411fcc413d62cf9c25ad29a4bef9bf21 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CorrectHoleFoundSubHSM.o.d 
	@${RM} ${OBJECTDIR}/CorrectHoleFoundSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/CorrectHoleFoundSubHSM.o.d" -o ${OBJECTDIR}/CorrectHoleFoundSubHSM.o CorrectHoleFoundSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1975241074/AD.o: C:/ECE118/src/AD.c  .generated_files/flags/default/55f267b18ced218c5e7260ebb9297853a3822bff .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/AD.o.d" -o ${OBJECTDIR}/_ext/1975241074/AD.o C:/ECE118/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/BOARD.o: C:/ECE118/src/BOARD.c  .generated_files/flags/default/340bc73a003bba7f060af8e63acd1bff18799b19 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/BOARD.o.d" -o ${OBJECTDIR}/_ext/1975241074/BOARD.o C:/ECE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/serial.o: C:/ECE118/src/serial.c  .generated_files/flags/default/1d67033d357c493440dc3ce144eda1a94c23d02d .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/serial.o.d" -o ${OBJECTDIR}/_ext/1975241074/serial.o C:/ECE118/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o: C:/ECE118/src/ES_CheckEvents.c  .generated_files/flags/default/53146ec8d0d2cecca8ed6b82145a9623e5df47b0 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o C:/ECE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Framework.o: C:/ECE118/src/ES_Framework.c  .generated_files/flags/default/27588a00b7588cd5b249ec222f37861482e4d4a3 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Framework.o C:/ECE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o: C:/ECE118/src/ES_KeyboardInput.c  .generated_files/flags/default/c91cccd1acbe65f714027b7d4f22c123eb421a66 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o C:/ECE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_PostList.o: C:/ECE118/src/ES_PostList.c  .generated_files/flags/default/4a958f2f8ddd4d514d1116f2fb509eb17ead213f .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_PostList.o C:/ECE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Queue.o: C:/ECE118/src/ES_Queue.c  .generated_files/flags/default/309ae743b4552c0e2dcb48c9b62487e621031c66 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Queue.o C:/ECE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o: C:/ECE118/src/ES_TattleTale.c  .generated_files/flags/default/9a12c6b022de37cf3c3121e1b8e257880f3a0889 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o C:/ECE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Timers.o: C:/ECE118/src/ES_Timers.c  .generated_files/flags/default/49c390b2a8c4098e9bb2ff22983d9ae14af40258 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Timers.o C:/ECE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/IO_Ports.o: C:/ECE118/src/IO_Ports.c  .generated_files/flags/default/d951802f44b552e1704e8b243c41cf78d71baf1d .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1975241074/IO_Ports.o C:/ECE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/LED.o: C:/ECE118/src/LED.c  .generated_files/flags/default/e8c22a475ac2ab7e3b9bbf0dabf95db1c488c146 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/LED.o.d" -o ${OBJECTDIR}/_ext/1975241074/LED.o C:/ECE118/src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/pwm.o: C:/ECE118/src/pwm.c  .generated_files/flags/default/c35b0d3b51d7d93436bc9a9a2a6a27fc3c39dc92 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/pwm.o.d" -o ${OBJECTDIR}/_ext/1975241074/pwm.o C:/ECE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/SimpleFunctionService.o: SimpleFunctionService.c  .generated_files/flags/default/e737e123e1b7aed5113d5b01c3f29bc0fc0824e3 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/SimpleFunctionService.o.d 
	@${RM} ${OBJECTDIR}/SimpleFunctionService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/SimpleFunctionService.o.d" -o ${OBJECTDIR}/SimpleFunctionService.o SimpleFunctionService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Beacon_Detector.o: Beacon_Detector.c  .generated_files/flags/default/5ae75e689fd8892538a5853f56d631c583d9eba9 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Beacon_Detector.o.d 
	@${RM} ${OBJECTDIR}/Beacon_Detector.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Beacon_Detector.o.d" -o ${OBJECTDIR}/Beacon_Detector.o Beacon_Detector.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Bumpers.o: Bumpers.c  .generated_files/flags/default/db7bf7cb19cbc95db2d73b01fbf52e3d78ca4493 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Bumpers.o.d 
	@${RM} ${OBJECTDIR}/Bumpers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Bumpers.o.d" -o ${OBJECTDIR}/Bumpers.o Bumpers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Sense_EventChecker.o: Sense_EventChecker.c  .generated_files/flags/default/64b177ab2de436883329e8849dc49d53c908e018 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Sense_EventChecker.o.d 
	@${RM} ${OBJECTDIR}/Sense_EventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Sense_EventChecker.o.d" -o ${OBJECTDIR}/Sense_EventChecker.o Sense_EventChecker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Solenoid_Driver.o: Solenoid_Driver.c  .generated_files/flags/default/48e01fc814ec88ba29ca62263e8a99fa351c8772 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Solenoid_Driver.o.d 
	@${RM} ${OBJECTDIR}/Solenoid_Driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Solenoid_Driver.o.d" -o ${OBJECTDIR}/Solenoid_Driver.o Solenoid_Driver.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Tape_Sensors.o: Tape_Sensors.c  .generated_files/flags/default/2985047f56578ae2b9d2fd67ce83572ab0e7fdeb .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Tape_Sensors.o.d 
	@${RM} ${OBJECTDIR}/Tape_Sensors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Tape_Sensors.o.d" -o ${OBJECTDIR}/Tape_Sensors.o Tape_Sensors.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Track_Wire_Sensor.o: Track_Wire_Sensor.c  .generated_files/flags/default/3c63ce4597f58e5f245080398c6157db32fceafb .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Track_Wire_Sensor.o.d 
	@${RM} ${OBJECTDIR}/Track_Wire_Sensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Track_Wire_Sensor.o.d" -o ${OBJECTDIR}/Track_Wire_Sensor.o Track_Wire_Sensor.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062664799/EncoderService.o: ../../Encoder_Test.X/EncoderService.c  .generated_files/flags/default/cf7b9b89843913763d58863ab6751eb2c2aa4e62 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/2062664799" 
	@${RM} ${OBJECTDIR}/_ext/2062664799/EncoderService.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062664799/EncoderService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/2062664799/EncoderService.o.d" -o ${OBJECTDIR}/_ext/2062664799/EncoderService.o ../../Encoder_Test.X/EncoderService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062664799/EncoderEventChecker.o: ../../Encoder_Test.X/EncoderEventChecker.c  .generated_files/flags/default/3404f68b9cb788cff863dfb4ff0e723923d2c15e .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/2062664799" 
	@${RM} ${OBJECTDIR}/_ext/2062664799/EncoderEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062664799/EncoderEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/2062664799/EncoderEventChecker.o.d" -o ${OBJECTDIR}/_ext/2062664799/EncoderEventChecker.o ../../Encoder_Test.X/EncoderEventChecker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/2062664799/Motor_Driver.o: ../../Encoder_Test.X/Motor_Driver.c  .generated_files/flags/default/eb7808b6a7ba14a81ecbef26c5ddd90be522534b .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/2062664799" 
	@${RM} ${OBJECTDIR}/_ext/2062664799/Motor_Driver.o.d 
	@${RM} ${OBJECTDIR}/_ext/2062664799/Motor_Driver.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/_ext/2062664799/Motor_Driver.o.d" -o ${OBJECTDIR}/_ext/2062664799/Motor_Driver.o ../../Encoder_Test.X/Motor_Driver.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TopHSM.o: TopHSM.c  .generated_files/flags/default/44b7a139fc85334e57809587cd50e7492539db40 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TopHSM.o.d 
	@${RM} ${OBJECTDIR}/TopHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/TopHSM.o.d" -o ${OBJECTDIR}/TopHSM.o TopHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Final_ES_Main.o: Final_ES_Main.c  .generated_files/flags/default/ae5edec4d2a4a142a77ab95fb843b046b12d8a3f .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Final_ES_Main.o.d 
	@${RM} ${OBJECTDIR}/Final_ES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Final_ES_Main.o.d" -o ${OBJECTDIR}/Final_ES_Main.o Final_ES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/Bumpers_Gen_v1SubHSM.o: Bumpers_Gen_v1SubHSM.c  .generated_files/flags/default/6646488497f6b521842e9a128a1bc001828368ae .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Bumpers_Gen_v1SubHSM.o.d 
	@${RM} ${OBJECTDIR}/Bumpers_Gen_v1SubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/Bumpers_Gen_v1SubHSM.o.d" -o ${OBJECTDIR}/Bumpers_Gen_v1SubHSM.o Bumpers_Gen_v1SubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ActiveSearchSubHSM.o: ActiveSearchSubHSM.c  .generated_files/flags/default/362e9daf1a2a08161b200f9486b02ed3b7758582 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ActiveSearchSubHSM.o.d 
	@${RM} ${OBJECTDIR}/ActiveSearchSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/ActiveSearchSubHSM.o.d" -o ${OBJECTDIR}/ActiveSearchSubHSM.o ActiveSearchSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FindTapeSubHSM.o: FindTapeSubHSM.c  .generated_files/flags/default/256bea2c8550aaae455b7cc7ac7b58220e357db6 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FindTapeSubHSM.o.d 
	@${RM} ${OBJECTDIR}/FindTapeSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/FindTapeSubHSM.o.d" -o ${OBJECTDIR}/FindTapeSubHSM.o FindTapeSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TowerScopeSubHSM.o: TowerScopeSubHSM.c  .generated_files/flags/default/3a05cbd374f6ea94ae402f9378635a57b8873469 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TowerScopeSubHSM.o.d 
	@${RM} ${OBJECTDIR}/TowerScopeSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/TowerScopeSubHSM.o.d" -o ${OBJECTDIR}/TowerScopeSubHSM.o TowerScopeSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TowerSubHSM.o: TowerSubHSM.c  .generated_files/flags/default/86cc89a2060344fb0e3960162f8d430a6b598dec .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TowerSubHSM.o.d 
	@${RM} ${OBJECTDIR}/TowerSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/TowerSubHSM.o.d" -o ${OBJECTDIR}/TowerSubHSM.o TowerSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TowerApproachSubHSM.o: TowerApproachSubHSM.c  .generated_files/flags/default/580de333c5cd540225a9616dd3f4cbfd2c581501 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TowerApproachSubHSM.o.d 
	@${RM} ${OBJECTDIR}/TowerApproachSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/TowerApproachSubHSM.o.d" -o ${OBJECTDIR}/TowerApproachSubHSM.o TowerApproachSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/CircleTowerSubHSM.o: CircleTowerSubHSM.c  .generated_files/flags/default/496d8cd1680df01f7a6040633c2aa95ee2fa3365 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CircleTowerSubHSM.o.d 
	@${RM} ${OBJECTDIR}/CircleTowerSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/CircleTowerSubHSM.o.d" -o ${OBJECTDIR}/CircleTowerSubHSM.o CircleTowerSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/CorrectSideFoundSubHSM.o: CorrectSideFoundSubHSM.c  .generated_files/flags/default/31fe0fa688db45d1868051b6b812bfa8a64bb6d4 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CorrectSideFoundSubHSM.o.d 
	@${RM} ${OBJECTDIR}/CorrectSideFoundSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/CorrectSideFoundSubHSM.o.d" -o ${OBJECTDIR}/CorrectSideFoundSubHSM.o CorrectSideFoundSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/DeadBotAvoidSubHSM.o: DeadBotAvoidSubHSM.c  .generated_files/flags/default/6b7ad8858f854b5c18b7c85f06e1a0bf7adc6f7d .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/DeadBotAvoidSubHSM.o.d 
	@${RM} ${OBJECTDIR}/DeadBotAvoidSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/DeadBotAvoidSubHSM.o.d" -o ${OBJECTDIR}/DeadBotAvoidSubHSM.o DeadBotAvoidSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/CorrectHoleFoundSubHSM.o: CorrectHoleFoundSubHSM.c  .generated_files/flags/default/583ebe94ad340a2d6db3fa095acc8dec1c2f5d65 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/CorrectHoleFoundSubHSM.o.d 
	@${RM} ${OBJECTDIR}/CorrectHoleFoundSubHSM.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -O1 -fno-common -I"." -I"C:/ECE118" -I"C:/ECE118/include" -I"../../Encoder_Test.X" -MP -MMD -MF "${OBJECTDIR}/CorrectHoleFoundSubHSM.o.d" -o ${OBJECTDIR}/CorrectHoleFoundSubHSM.o CorrectHoleFoundSubHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/SunsetStudios.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../../../../../../ECE118/bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SunsetStudios.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=_min_heap_size=100,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/SunsetStudios.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../../../../../../ECE118/bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/SunsetStudios.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=100,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/SunsetStudios.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


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
