INA228_VERSION = 1.0
INA228_SITE = $(TOPDIR)/package/ina228
INA228_SITE_METHOD = local

define INA228_BUILD_CMDS
    @echo "=== DEBUG INFO ==="
    @echo "CC = $(TARGET_CC)"
    @echo "CXX = $(TARGET_CXX)" 
    @echo "TARGET_CROSS = $(TARGET_CROSS)"
    @echo "CROSS_COMPILE = $(CROSS_COMPILE)"
    @echo "=================="
    $(TARGET_MAKE_ENV) $(MAKE) CC="$(TARGET_CC)" CXX="$(TARGET_CXX)" -C $(@D)
endef

define INA228_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/ina228 $(TARGET_DIR)/usr/bin/ina228
endef

$(eval $(generic-package))
