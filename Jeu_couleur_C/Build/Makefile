PROJDIR := $(realpath $(CURDIR)/..)
SOURCEDIR := $(PROJDIR)/Source
BUILDDIR := $(PROJDIR)/Build

TARGET = myApp.exe

VERBOSE = TRUE

DIRS = Inonde_grille
SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCEDIR)/, $(dir)))
TARGETDIRS = $(foreach dir, $(DIRS), $(addprefix $(BUILDDIR)/, $(dir)))

INCLUDES = $(foreach dir, $(SOURCEDIRS), $(addprefix -I, $(dir)))

VPATH = $(SOURCEDIRS)

SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))

OBJS := $(subst $(SOURCEDIR),$(BUILDDIR),$(SOURCES:.c=.o))

DEPS = $(OBJS:.o=.d)

CC = gcc

ifeq ($(OS),Windows_NT)
	RM = del /F /Q 
	RMDIR = -RMDIR /S /Q
	MKDIR = -mkdir
	ERRIGNORE = 2>NUL || true
	SEP=\\
else
	RM = rm -rf 
	RMDIR = rm -rf 
	MKDIR = mkdir -p
	ERRIGNORE = 2>/dev/null
	SEP=/
endif

PSEP = $(strip $(SEP))

ifeq ($(VERBOSE),TRUE)
	HIDE =  
else
	HIDE = @
endif

define generateRules
$(1)/%.o: %.c
	@echo Building $$@
	$(HIDE)$(CC) -c $$(INCLUDES) -o $$(subst \,$$(PSEP),$$@) $$(subst \,$$(PSEP),$$<) -MMD
endef

.PHONY: all clean directories 

all: directories $(TARGET)

$(TARGET): $(OBJS)
	$(HIDE)echo Linking $@
	@echo projdir = $(PROJDIR)
	@echo sourcedir = $(SOURCEDIR)
	@echo targetdirs = $(TARGETDIRS)
	@echo sources = $(SOURCES)
	@echo sources = $(SOURCES)
	@echo objs = $(OBJS)
	$(HIDE)$(CC) $(OBJS) -o $(TARGET)

-include $(DEPS)

$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))

directories: 
	$(HIDE)$(MKDIR) $(subst \,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)

clean:
	$(HIDE)$(RMDIR) $(subst \,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)
	$(HIDE)$(RM) $(TARGET) $(ERRIGNORE)
	@echo Cleaning done !
