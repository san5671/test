include ../../AppBuildSettings.mk

program_NAME           = ais140ExternalSensor
dest_DIR               = ${EXT_BIN_DIR}

# Uncomment this line to add include directories, space delimited
program_INCLUDE_DIRS += $(COMMON_INC_DIR) $(MOSQUITTO_INC_DIR) $(IPC_INC_DIR) $(VTPAPP_INC_DIR)

# Uncomment this line to add library directories, space delimited
#program_LIBRARY_DIRS +=   

# Uncomment this line to add libraries, space delimited
program_LIBRARIES    += $(COMMON_LIB) $(VTPAPP_LIB) pthread crypto $(COMMON_LIB) $(IPC_LIB) $(MOSQUITTO_LIB) ssl

include ../../vtp/VtpTargets.mk
