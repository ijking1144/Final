UM982_VERSION = 1.0
UM982_SITE = $(TOPDIR)/package/um982
UM982_SITE_METHOD = local

define UM982_BUILD_CMDS
    @echo "=== DEBUG INFO ==="
    @echo "CC = $(TARGET_CC)"
    @echo "CXX = $(TARGET_CXX)" 
    @echo "TARGET_CROSS = $(TARGET_CROSS)"
    @echo "CROSS_COMPILE = $(CROSS_COMPILE)"
    @echo "=================="
    $(TARGET_MAKE_ENV) $(MAKE) CC="$(TARGET_CC)" CXX="$(TARGET_CXX)" -C $(@D)
endef

define UM982_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/um982 $(TARGET_DIR)/usr/bin/um982
endef

$(eval $(generic-package))
