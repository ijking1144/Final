SD_CARD_VERSION = 1.0
SD_CARD_SITE = $(TOPDIR)/package/sd-card
SD_CARD_SITE_METHOD = local
SD_CARD_DEPENDENCIES = linux
SD_CARD_LICENSE = GPL-2.0

define SD_CARD_BUILD_CMDS
	$(MAKE) -C $(LINUX_DIR) M=$(@D) \
		ARCH=$(KERNEL_ARCH) \
		CROSS_COMPILE=$(TARGET_CROSS) \
		modules
endef

define SD_CARD_INSTALL_TARGET_CMDS
	$(INSTALL) -d $(TARGET_DIR)/lib/modules/$(LINUX_VERSION_PROBED)/extra
	$(INSTALL) -m 0644 $(@D)/spi.ko \
		$(TARGET_DIR)/lib/modules/$(LINUX_VERSION_PROBED)/extra/
	$(INSTALL) -D -m 0755 $(TOPDIR)/package/sd-card/S99sd-spi \
		$(TARGET_DIR)/etc/init.d/S99sd-spi
	$(INSTALL) -d -m 0755 $(TARGET_DIR)/mnt/sdcard
		
endef

$(eval $(generic-package))
