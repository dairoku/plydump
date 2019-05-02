# ----------------------------------------------------------------------
#  Macros for plydump
# ----------------------------------------------------------------------
PLYDUMP_DIR		= .
PLYDUMP_OBJS	= \
  main.o
PLYDUMP_SOURCES	= $(PLYDUMP_OBJS:.o=.cpp)
PLYDUMP_DEPENDS	= $(PLYDUMP_OBJS:.o=.d)
PLYDUMP_NAME	= plydump

# ----------------------------------------------------------------------
#  Macros for Common part
# ----------------------------------------------------------------------
SOURCES	= $(PLYDUMP_SOURCES)
DEPENDS	= $(PLYDUMP_DEPENDS)
OBJS	= $(PLYDUMP_OBJS)
TARGETS	= $(PLYDUMP_NAME)
VPATH	= $(PLYDUMP_DIR)

# ----------------------------------------------------------------------
#  Build Options
# ----------------------------------------------------------------------
CC			= g++
LD			= $(CC)
CFLAGS		= -MD -fpic
LDFLAGS 	=
INCLUDES	= -I /usr/include -I $(PLYDUMP_DIR)

# ----------------------------------------------------------------------
#  Default Rules
# ----------------------------------------------------------------------
# Note that we are using "-0 $@" option to generate target objects
# in the source file directory
#
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

.cpp.d:
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

# ----------------------------------------------------------------------
#  Build Rules
# ----------------------------------------------------------------------
all: $(TARGETS)

$(DEPENDS) : $(SOURCES)

$(TARGETS) : $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

.PHONY : clean depend
clean:
	$(RM) output/$(TARGETS) $(OBJS) $(DEPENDS)

-include $(DEPENDS)
