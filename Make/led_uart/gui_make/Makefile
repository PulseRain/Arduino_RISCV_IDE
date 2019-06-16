TOPDIR := $(shell pwd)

export TOPDIR


config_targets := menuconfig config xconfig
config_folder_name := config
       
# Pull in the user's configuration
ifeq (,$(filter $(config_targets),$(MAKECMDGOALS)))
	-include $(TOPDIR)/$(config_folder_name)/.config
endif       

#############################################################################
ifeq ($(strip $(CONFIG_HAVE_DOT_CONFIG)),y)

        include $(TOPDIR)/Rules.mak

#############################################################################
else # need to be configured

$(config_targets):
	@make -C $(config_folder_name) $(MAKECMDGOALS)
   
.PHONY: $(config_targets)

endif
