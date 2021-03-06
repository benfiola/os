
SET(CWD ${CMAKE_CURRENT_LIST_DIR})
SET(KERNEL_ARCH_PROLOGUE_SOURCES "${CWD}/crti.s")
SET(KERNEL_ARCH_EPILOGUE_SOURCES "${CWD}/crtn.s")
FILE(GLOB KERNEL_ARCH_SOURCES ${CWD}/*.cpp ${CWD}/*.s ${CWD}/*.c)
LIST(REMOVE_ITEM KERNEL_ARCH_SOURCES ${KERNEL_ARCH_PROLOGUE_SOURCES} ${KERNEL_ARCH_EPILOGUE_SOURCES})
SET(KERNEL_ARCH_LINKER ${CWD}/linker.ld)
