# ----------------------------
# Makefile Options
# ----------------------------

NAME = ISO
ICON = icon.png
DESCRIPTION = "Isometric sandbox"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
