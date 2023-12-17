ifneq ($(PKGS),)
PKG_CONFIG ?= $(CROSS_COMPILE)pkg-config

CXXFLAGS += $(shell $(PKG_CONFIG) --cflags $(PKGS))
LIBS += $(shell $(PKG_CONFIG) --libs $(PKGS))
endif
