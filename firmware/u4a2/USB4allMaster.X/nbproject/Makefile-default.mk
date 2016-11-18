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
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USB4allMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/USB4allMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../usb4all/proxys/T0Service.c ../user/adminModule.c ../user/descriptorManager.c ../usb4all/dynamicISR/dynamicISR.c ../user/handlerManager.c ../user/loaderModule.c ../main.c ../user/pnp.c ../user/port.c ../user/usb4butia.c ../system/usb/usb9/usb9.c ../system/usb/usbctrltrf/usbctrltrf.c ../system/usb/usbdrv/usbdrv.c ../usb4all/usbconf/desc/usbdsc.c ../usb4all/usbconf/usballoc/usbmmap.c ../user/usr_ax.c ../user/ax12.c ../user/usr_button.c ../user/usr_hackpoints.c ../user/usr_motors.c ../user/usr_butia.c ../user/usr_modAct.c ../user/usr_modSen.c ../user/usr_i2c.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/2126317742/T0Service.o ${OBJECTDIR}/_ext/760557894/adminModule.o ${OBJECTDIR}/_ext/760557894/descriptorManager.o ${OBJECTDIR}/_ext/175588566/dynamicISR.o ${OBJECTDIR}/_ext/760557894/handlerManager.o ${OBJECTDIR}/_ext/760557894/loaderModule.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/760557894/pnp.o ${OBJECTDIR}/_ext/760557894/port.o ${OBJECTDIR}/_ext/760557894/usb4butia.o ${OBJECTDIR}/_ext/592281999/usb9.o ${OBJECTDIR}/_ext/875386773/usbctrltrf.o ${OBJECTDIR}/_ext/2047694304/usbdrv.o ${OBJECTDIR}/_ext/533038235/usbdsc.o ${OBJECTDIR}/_ext/1414290683/usbmmap.o ${OBJECTDIR}/_ext/760557894/usr_ax.o ${OBJECTDIR}/_ext/760557894/ax12.o ${OBJECTDIR}/_ext/760557894/usr_button.o ${OBJECTDIR}/_ext/760557894/usr_hackpoints.o ${OBJECTDIR}/_ext/760557894/usr_motors.o ${OBJECTDIR}/_ext/760557894/usr_butia.o ${OBJECTDIR}/_ext/760557894/usr_modAct.o ${OBJECTDIR}/_ext/760557894/usr_modSen.o ${OBJECTDIR}/_ext/760557894/usr_i2c.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/2126317742/T0Service.o.d ${OBJECTDIR}/_ext/760557894/adminModule.o.d ${OBJECTDIR}/_ext/760557894/descriptorManager.o.d ${OBJECTDIR}/_ext/175588566/dynamicISR.o.d ${OBJECTDIR}/_ext/760557894/handlerManager.o.d ${OBJECTDIR}/_ext/760557894/loaderModule.o.d ${OBJECTDIR}/_ext/1472/main.o.d ${OBJECTDIR}/_ext/760557894/pnp.o.d ${OBJECTDIR}/_ext/760557894/port.o.d ${OBJECTDIR}/_ext/760557894/usb4butia.o.d ${OBJECTDIR}/_ext/592281999/usb9.o.d ${OBJECTDIR}/_ext/875386773/usbctrltrf.o.d ${OBJECTDIR}/_ext/2047694304/usbdrv.o.d ${OBJECTDIR}/_ext/533038235/usbdsc.o.d ${OBJECTDIR}/_ext/1414290683/usbmmap.o.d ${OBJECTDIR}/_ext/760557894/usr_ax.o.d ${OBJECTDIR}/_ext/760557894/ax12.o.d ${OBJECTDIR}/_ext/760557894/usr_button.o.d ${OBJECTDIR}/_ext/760557894/usr_hackpoints.o.d ${OBJECTDIR}/_ext/760557894/usr_motors.o.d ${OBJECTDIR}/_ext/760557894/usr_butia.o.d ${OBJECTDIR}/_ext/760557894/usr_modAct.o.d ${OBJECTDIR}/_ext/760557894/usr_modSen.o.d ${OBJECTDIR}/_ext/760557894/usr_i2c.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/2126317742/T0Service.o ${OBJECTDIR}/_ext/760557894/adminModule.o ${OBJECTDIR}/_ext/760557894/descriptorManager.o ${OBJECTDIR}/_ext/175588566/dynamicISR.o ${OBJECTDIR}/_ext/760557894/handlerManager.o ${OBJECTDIR}/_ext/760557894/loaderModule.o ${OBJECTDIR}/_ext/1472/main.o ${OBJECTDIR}/_ext/760557894/pnp.o ${OBJECTDIR}/_ext/760557894/port.o ${OBJECTDIR}/_ext/760557894/usb4butia.o ${OBJECTDIR}/_ext/592281999/usb9.o ${OBJECTDIR}/_ext/875386773/usbctrltrf.o ${OBJECTDIR}/_ext/2047694304/usbdrv.o ${OBJECTDIR}/_ext/533038235/usbdsc.o ${OBJECTDIR}/_ext/1414290683/usbmmap.o ${OBJECTDIR}/_ext/760557894/usr_ax.o ${OBJECTDIR}/_ext/760557894/ax12.o ${OBJECTDIR}/_ext/760557894/usr_button.o ${OBJECTDIR}/_ext/760557894/usr_hackpoints.o ${OBJECTDIR}/_ext/760557894/usr_motors.o ${OBJECTDIR}/_ext/760557894/usr_butia.o ${OBJECTDIR}/_ext/760557894/usr_modAct.o ${OBJECTDIR}/_ext/760557894/usr_modSen.o ${OBJECTDIR}/_ext/760557894/usr_i2c.o

# Source Files
SOURCEFILES=../usb4all/proxys/T0Service.c ../user/adminModule.c ../user/descriptorManager.c ../usb4all/dynamicISR/dynamicISR.c ../user/handlerManager.c ../user/loaderModule.c ../main.c ../user/pnp.c ../user/port.c ../user/usb4butia.c ../system/usb/usb9/usb9.c ../system/usb/usbctrltrf/usbctrltrf.c ../system/usb/usbdrv/usbdrv.c ../usb4all/usbconf/desc/usbdsc.c ../usb4all/usbconf/usballoc/usbmmap.c ../user/usr_ax.c ../user/ax12.c ../user/usr_button.c ../user/usr_hackpoints.c ../user/usr_motors.c ../user/usr_butia.c ../user/usr_modAct.c ../user/usr_modSen.c ../user/usr_i2c.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/USB4allMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4550
MP_PROCESSOR_OPTION_LD=18f4550
MP_LINKER_DEBUG_OPTION= -u_DEBUGCODESTART=0x7dc0 -u_DEBUGCODELEN=0x240 -u_DEBUGDATASTART=0x3f4 -u_DEBUGDATALEN=0xb
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/2126317742/T0Service.o: ../usb4all/proxys/T0Service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2126317742" 
	@${RM} ${OBJECTDIR}/_ext/2126317742/T0Service.o.d 
	@${RM} ${OBJECTDIR}/_ext/2126317742/T0Service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/2126317742/T0Service.o   ../usb4all/proxys/T0Service.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2126317742/T0Service.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2126317742/T0Service.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/adminModule.o: ../user/adminModule.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/adminModule.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/adminModule.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/adminModule.o   ../user/adminModule.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/adminModule.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/adminModule.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/descriptorManager.o: ../user/descriptorManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/descriptorManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/descriptorManager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/descriptorManager.o   ../user/descriptorManager.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/descriptorManager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/descriptorManager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/175588566/dynamicISR.o: ../usb4all/dynamicISR/dynamicISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/175588566" 
	@${RM} ${OBJECTDIR}/_ext/175588566/dynamicISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/175588566/dynamicISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/175588566/dynamicISR.o   ../usb4all/dynamicISR/dynamicISR.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/175588566/dynamicISR.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/175588566/dynamicISR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/handlerManager.o: ../user/handlerManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/handlerManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/handlerManager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/handlerManager.o   ../user/handlerManager.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/handlerManager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/handlerManager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/loaderModule.o: ../user/loaderModule.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/loaderModule.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/loaderModule.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/loaderModule.o   ../user/loaderModule.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/loaderModule.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/loaderModule.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/main.o   ../main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/pnp.o: ../user/pnp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/pnp.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/pnp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/pnp.o   ../user/pnp.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/pnp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/pnp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/port.o: ../user/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/port.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/port.o   ../user/port.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usb4butia.o: ../user/usb4butia.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usb4butia.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usb4butia.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usb4butia.o   ../user/usb4butia.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usb4butia.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usb4butia.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/592281999/usb9.o: ../system/usb/usb9/usb9.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/592281999" 
	@${RM} ${OBJECTDIR}/_ext/592281999/usb9.o.d 
	@${RM} ${OBJECTDIR}/_ext/592281999/usb9.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/592281999/usb9.o   ../system/usb/usb9/usb9.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/592281999/usb9.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/592281999/usb9.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/875386773/usbctrltrf.o: ../system/usb/usbctrltrf/usbctrltrf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/875386773" 
	@${RM} ${OBJECTDIR}/_ext/875386773/usbctrltrf.o.d 
	@${RM} ${OBJECTDIR}/_ext/875386773/usbctrltrf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/875386773/usbctrltrf.o   ../system/usb/usbctrltrf/usbctrltrf.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/875386773/usbctrltrf.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/875386773/usbctrltrf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2047694304/usbdrv.o: ../system/usb/usbdrv/usbdrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2047694304" 
	@${RM} ${OBJECTDIR}/_ext/2047694304/usbdrv.o.d 
	@${RM} ${OBJECTDIR}/_ext/2047694304/usbdrv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/2047694304/usbdrv.o   ../system/usb/usbdrv/usbdrv.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2047694304/usbdrv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2047694304/usbdrv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/533038235/usbdsc.o: ../usb4all/usbconf/desc/usbdsc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/533038235" 
	@${RM} ${OBJECTDIR}/_ext/533038235/usbdsc.o.d 
	@${RM} ${OBJECTDIR}/_ext/533038235/usbdsc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/533038235/usbdsc.o   ../usb4all/usbconf/desc/usbdsc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/533038235/usbdsc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/533038235/usbdsc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1414290683/usbmmap.o: ../usb4all/usbconf/usballoc/usbmmap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1414290683" 
	@${RM} ${OBJECTDIR}/_ext/1414290683/usbmmap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1414290683/usbmmap.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1414290683/usbmmap.o   ../usb4all/usbconf/usballoc/usbmmap.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1414290683/usbmmap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1414290683/usbmmap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_ax.o: ../user/usr_ax.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_ax.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_ax.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_ax.o   ../user/usr_ax.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_ax.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_ax.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/ax12.o: ../user/ax12.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/ax12.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/ax12.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/ax12.o   ../user/ax12.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/ax12.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/ax12.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_button.o: ../user/usr_button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_button.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_button.o   ../user/usr_button.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_button.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_button.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_hackpoints.o: ../user/usr_hackpoints.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_hackpoints.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_hackpoints.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_hackpoints.o   ../user/usr_hackpoints.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_hackpoints.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_hackpoints.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_motors.o: ../user/usr_motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_motors.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_motors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_motors.o   ../user/usr_motors.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_motors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_butia.o: ../user/usr_butia.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_butia.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_butia.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_butia.o   ../user/usr_butia.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_butia.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_butia.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_modAct.o: ../user/usr_modAct.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_modAct.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_modAct.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_modAct.o   ../user/usr_modAct.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_modAct.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_modAct.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_modSen.o: ../user/usr_modSen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_modSen.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_modSen.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_modSen.o   ../user/usr_modSen.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_modSen.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_modSen.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_i2c.o: ../user/usr_i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PICKIT2=1 -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_i2c.o   ../user/usr_i2c.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/_ext/2126317742/T0Service.o: ../usb4all/proxys/T0Service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2126317742" 
	@${RM} ${OBJECTDIR}/_ext/2126317742/T0Service.o.d 
	@${RM} ${OBJECTDIR}/_ext/2126317742/T0Service.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/2126317742/T0Service.o   ../usb4all/proxys/T0Service.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2126317742/T0Service.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2126317742/T0Service.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/adminModule.o: ../user/adminModule.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/adminModule.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/adminModule.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/adminModule.o   ../user/adminModule.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/adminModule.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/adminModule.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/descriptorManager.o: ../user/descriptorManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/descriptorManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/descriptorManager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/descriptorManager.o   ../user/descriptorManager.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/descriptorManager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/descriptorManager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/175588566/dynamicISR.o: ../usb4all/dynamicISR/dynamicISR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/175588566" 
	@${RM} ${OBJECTDIR}/_ext/175588566/dynamicISR.o.d 
	@${RM} ${OBJECTDIR}/_ext/175588566/dynamicISR.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/175588566/dynamicISR.o   ../usb4all/dynamicISR/dynamicISR.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/175588566/dynamicISR.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/175588566/dynamicISR.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/handlerManager.o: ../user/handlerManager.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/handlerManager.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/handlerManager.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/handlerManager.o   ../user/handlerManager.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/handlerManager.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/handlerManager.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/loaderModule.o: ../user/loaderModule.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/loaderModule.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/loaderModule.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/loaderModule.o   ../user/loaderModule.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/loaderModule.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/loaderModule.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1472/main.o: ../main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1472" 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/1472/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1472/main.o   ../main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1472/main.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1472/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/pnp.o: ../user/pnp.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/pnp.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/pnp.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/pnp.o   ../user/pnp.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/pnp.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/pnp.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/port.o: ../user/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/port.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/port.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/port.o   ../user/port.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/port.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usb4butia.o: ../user/usb4butia.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usb4butia.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usb4butia.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usb4butia.o   ../user/usb4butia.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usb4butia.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usb4butia.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/592281999/usb9.o: ../system/usb/usb9/usb9.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/592281999" 
	@${RM} ${OBJECTDIR}/_ext/592281999/usb9.o.d 
	@${RM} ${OBJECTDIR}/_ext/592281999/usb9.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/592281999/usb9.o   ../system/usb/usb9/usb9.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/592281999/usb9.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/592281999/usb9.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/875386773/usbctrltrf.o: ../system/usb/usbctrltrf/usbctrltrf.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/875386773" 
	@${RM} ${OBJECTDIR}/_ext/875386773/usbctrltrf.o.d 
	@${RM} ${OBJECTDIR}/_ext/875386773/usbctrltrf.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/875386773/usbctrltrf.o   ../system/usb/usbctrltrf/usbctrltrf.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/875386773/usbctrltrf.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/875386773/usbctrltrf.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/2047694304/usbdrv.o: ../system/usb/usbdrv/usbdrv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/2047694304" 
	@${RM} ${OBJECTDIR}/_ext/2047694304/usbdrv.o.d 
	@${RM} ${OBJECTDIR}/_ext/2047694304/usbdrv.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/2047694304/usbdrv.o   ../system/usb/usbdrv/usbdrv.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/2047694304/usbdrv.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/2047694304/usbdrv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/533038235/usbdsc.o: ../usb4all/usbconf/desc/usbdsc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/533038235" 
	@${RM} ${OBJECTDIR}/_ext/533038235/usbdsc.o.d 
	@${RM} ${OBJECTDIR}/_ext/533038235/usbdsc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/533038235/usbdsc.o   ../usb4all/usbconf/desc/usbdsc.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/533038235/usbdsc.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/533038235/usbdsc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/1414290683/usbmmap.o: ../usb4all/usbconf/usballoc/usbmmap.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1414290683" 
	@${RM} ${OBJECTDIR}/_ext/1414290683/usbmmap.o.d 
	@${RM} ${OBJECTDIR}/_ext/1414290683/usbmmap.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/1414290683/usbmmap.o   ../usb4all/usbconf/usballoc/usbmmap.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/1414290683/usbmmap.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1414290683/usbmmap.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_ax.o: ../user/usr_ax.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_ax.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_ax.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_ax.o   ../user/usr_ax.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_ax.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_ax.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/ax12.o: ../user/ax12.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/ax12.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/ax12.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/ax12.o   ../user/ax12.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/ax12.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/ax12.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_button.o: ../user/usr_button.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_button.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_button.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_button.o   ../user/usr_button.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_button.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_button.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_hackpoints.o: ../user/usr_hackpoints.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_hackpoints.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_hackpoints.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_hackpoints.o   ../user/usr_hackpoints.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_hackpoints.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_hackpoints.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_motors.o: ../user/usr_motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_motors.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_motors.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_motors.o   ../user/usr_motors.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_motors.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_butia.o: ../user/usr_butia.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_butia.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_butia.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_butia.o   ../user/usr_butia.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_butia.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_butia.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_modAct.o: ../user/usr_modAct.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_modAct.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_modAct.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_modAct.o   ../user/usr_modAct.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_modAct.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_modAct.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_modSen.o: ../user/usr_modSen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_modSen.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_modSen.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_modSen.o   ../user/usr_modSen.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_modSen.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_modSen.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/_ext/760557894/usr_i2c.o: ../user/usr_i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/760557894" 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_i2c.o.d 
	@${RM} ${OBJECTDIR}/_ext/760557894/usr_i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -w3 -I"../user" -I"../usb4all/proxys" -I"../usb4all/dynamicISR" -I"../usb4all/usbconf/usballoc" -I"../usb4all/usbconf/desc" -I"../system" -I"../system/usb" -I"../autofiles" -I".." -ms -oa- -o-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/_ext/760557894/usr_i2c.o   ../user/usr_i2c.c 
	@${DEP_GEN} -d ${OBJECTDIR}/_ext/760557894/usr_i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/760557894/usr_i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/USB4allMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../18f4550.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "../18f4550.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -l"/usr/local/microchip/mplabc18/v3.40/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PICKIT2=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}/../lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/USB4allMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/USB4allMaster.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../18f4550.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "../18f4550.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -l"/usr/local/microchip/mplabc18/v3.40/lib"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}/../lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/USB4allMaster.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
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

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
