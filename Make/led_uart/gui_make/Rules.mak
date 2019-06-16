ifndef TOPDIR
    TOPDIR := ..
endif


config_targets ?= menuconfig config xconfig
config_folder_name ?= config

#check to see if we need to include ".config"
ifneq ($(strip $(CONFIG_HAVE_DOT_CONFIG)),y)
   
    ifeq (,$(filter $(config_targets), "$(MAKECMDGOALS)"))
        -include $(TOPDIR)/$(config_folder_name)/.config
    endif
   
endif

ifeq ($(strip $(CONFIG_HAVE_DOT_CONFIG)),y)
    config_file := $(TOPDIR)/$(config_folder_name)/.config
else
    config_file :=
endif


HOST_CC ?= gcc


CROSS ?= $(strip $(subst ",, $(CONFIG_CROSS_COMPILER_PREFIX)))

CROSS_CC ?= $(CROSS)gcc
CROSS_CXX ?= $(CROSS)g++
CROSS_AS ?= $(CROSS)as
CROSS_AR ?= $(CROSS)ar
CROSS_LD ?= $(CROSS)gcc
CROSS_NM ?= $(CROSS)nm
CROSS_STRIP ?= $(CROSS)strip
CROSS_OBJDUMP = $(CROSS)objdump


VMAJOR ?= $(strip $(subst ",, $(CONFIG_VMAJOR_STR)))
VMINOR ?= $(strip $(subst ",, $(CONFIG_VMINOR_STR)))
REVISION ?= $(strip $(subst ",, $(CONFIG_REVISION_STR)))
VENDOR_NAME ?= $(strip $(CONFIG_VENDOR_NAME))


CFLAGS += -DVMAJOR=$(VMAJOR) -DVMINOR=$(VMINOR)
CFLAGS += -DVENDOR_NAME=$(VENDOR_NAME)

CFLAGS = -I. -I../../../PulseRain_RISCV/Reindeer/cores/Reindeer -I../../../PulseRain_RISCV/Reindeer/variants/generic
CFLAGS += --specs=nosys.specs -march=rv32i -mabi=ilp32 -Os -fno-builtin-printf -fdata-sections -ffunction-sections -fno-exceptions -fno-unwind-tables -fno-rtti
CFLAGS += -W -D__GXX_EXPERIMENTAL_CXX0X__

LDFLAGS = -T ../Reindeer.ld --specs=nosys.specs -march=rv32i -mabi=ilp32 -Os -fdata-sections -ffunction-sections -Wl,--gc-sections -static -fno-exceptions -fno-unwind-tables -fno-rtti

#pattern rule


#== Put all the object files here
obj = ../../../PulseRain_RISCV/Reindeer/cores/Reindeer/main.o \
	../../../PulseRain_RISCV/Reindeer/cores/Reindeer/Print.o \
	../../../PulseRain_RISCV/Reindeer/cores/Reindeer/Stream.o \
	../../../PulseRain_RISCV/Reindeer/cores/Reindeer/HardwareSerial.o \
	../../../PulseRain_RISCV/Reindeer/cores/Reindeer/Reindeer.o
      
obj += ../sketch.o

target = step.elf
dump = $(patsubst %.elf,%.dump,$(target)) 


all: $(obj)
	@echo "====> Linking $(target)"
	@$(CROSS_LD) $(LDFLAGS) $(obj) -o $(target) 
	@chmod 755 $(target)
	@echo "===> Dumping sections for $@"
	@$(CROSS_OBJDUMP) --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.data --section=.rodata --section=.sdata --section=.sdata2 --section=.init_array --section=.fini_array $(target) > $(dump)

%.o : %.c 
	@echo "===> Building $@"
	@echo "============> Building Dependency"
	@$(CROSS_CC) $(CFLAGS) -M $< | sed "s,$(@F)\s*:,$@ :," > $*.d
	@echo "============> Generating OBJ"
	@$(CROSS_CC) $(CFLAGS) -c -o $@ $<; \
	if [ $$? -ge 1 ] ; then \
		exit 1; \
	fi
	@echo "----------------------------------------------------------------------------"

%.o : %.cpp 
	@echo "===> Building $@"
	@echo "============> Building Dependency"
	@$(CROSS_CXX) $(CFLAGS) -M $< | sed "s,$(@F)\s*:,$@ :," > $*.d
	@echo "============> Generating OBJ"
	@$(CROSS_CXX) $(CFLAGS) -c -o $@ $<; \
	if [ $$? -ge 1 ] ; then \
		exit 1; \
	fi
	@echo "----------------------------------------------------------------------------"

    
dependency = $(patsubst %.o,%.d,$(obj)) 

ifneq "$(MAKECMDGOALS)" "clean"
	-include $(dependency)
endif

	
clean :
	-@rm -vf $(target)
	-@find . -type f \( -name "*.riscv" -o -name "*.d" -o -name "*.o" -o -name "*.lst" -o -name "*.dump" \
	                    -o -name "*.bin" -o -name "*.out" -o -name "*.elf" \) -exec rm -vf {} \;


.PHONY: clean all
