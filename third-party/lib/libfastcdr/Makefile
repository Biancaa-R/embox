PKG_NAME := Fast-CDR
PKG_VER := 1.0.24


PKG_SOURCES := https://github.com/eProsima/$(Fast-CDR)/archive/refs/tags/v$(PKG_VER).tar.gz

PKG_MD5     := e49533638bd1ba7115b6c72d2c17d5fc

PKG_PATCHES := patch.txt

include $(EXTBLD_LIB)

$(CONFIGURE) :
	cd $(PKG_SOURCE_DIR) && ( \
		cmake . \
			-DBUILD_SHARED_LIBS=OFF \
			-DCMAKE_INSTALL_PREFIX=$(PKG_INSTALL_DIR) \
			-DCMAKE_SYSTEM_PROCESSOR:STRING=$(AUTOCONF_TARGET_TRIPLET) \
			-DCMAKE_C_COMPILER:PATH=$(EMBOX_GCC) \
			-DCMAKE_CXX_COMPILER:PATH=$(EMBOX_GXX) \
			-DCMAKE_AR:PATH=$(CROSS_COMPILE)ar\
			-DCMAKE_SYSTEM_NAME:STRING=Generic \
			-DCMAKE_BUILD_TYPE:STRING=None \
			-DCMAKE_VERBOSE_MAKEFILE:BOOL=on \
			-DCMAKE_PREFIX_PATH=$(PKG_INSTALL_DIR) \
	)

	touch $@

$(BUILD) :
	cd $(PKG_SOURCE_DIR) && ( \
		$(MAKE) MAKEFLAGS='$(EMBOX_IMPORTED_MAKEFLAGS)' install; \
	)

	touch $@

$(INSTALL) :
#	cp $(PKG_SOURCE_DIR)/src/libpaho-mqttpp3-static.a $(PKG_INSTALL_DIR)/libpaho-mqttpp3-static.a
#	mkdir -p $(PKG_INSTALL_DIR)/include/mqtt
#	cp $(PKG_SOURCE_DIR)/src/mqtt/*.h $(PKG_INSTALL_DIR)/include/mqtt/

	touch $@

