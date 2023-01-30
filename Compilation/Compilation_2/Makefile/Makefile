# Donne l'emplacement du projet et $(CURDIR) est une variable du GNU qui contient le chemin vers le projet
# Donne l'emplacement du fichier "Sources" pour accèder aux fichiers contenu dedans
# Donne l'emplacement du fichier "Build" pour construire de nouveaux fichiers dedans
PROJDIR := $(realpath $(CURDIR)/..)
SOURCEDIR := $(PROJDIR)/Sources
BUILDDIR := $(PROJDIR)/Build

# Nom de l’exécutable final, que l'on peut modifier par un autre nom
TARGET = myApp.exe

# Décide si les commandes seront exécutés ou non, puis il donne toutes les opérations exécutés
VERBOSE = TRUE

# Donne le nom des fichiers où les mettre
# Crée la liste des fichiers
DIRS = Folder0 Folder1
SOURCEDIRS = $(foreach dir, $(DIRS), $(addprefix $(SOURCEDIR)/, $(dir)))
TARGETDIRS = $(foreach dir, $(DIRS), $(addprefix $(BUILDDIR)/, $(dir)))


# Génère le CCG inclut dans les paramètres en ajoutant des -I avant chaque dossier source
INCLUDES = $(foreach dir, $(SOURCEDIRS), $(addprefix -I, $(dir)))

# Ajoute cette liste à VPATH, qui cherchent les fichiers source
VPATH = $(SOURCEDIRS)

# Crée une liste de fichiers sources avec l'extension .c dans DIRS
SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c))

# Définit les objets pour toutes les sources
OBJS := $(subst $(SOURCEDIR),$(BUILDDIR),$(SOURCES:.c=.o))

# Définit les fichiers de dépendance pour tous les objets
DEPS = $(OBJS:.o=.d)

# nom du compilateur
CC = gcc

# Partie spécifique de l’OS, ici "Windows_NT"
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

# Enlève l’espace après le séparateur
PSEP = $(strip $(SEP))

# Masque ou non les appels selon VERBOSE
ifeq ($(VERBOSE),TRUE)
	HIDE =  
else
	HIDE = @
endif

# Définit la fonction qui génère chaque règle
define generateRules
$(1)/%.o: %.c
	@echo Building $$@
	$(HIDE)$(CC) -c $$(INCLUDES) -o $$(subst \,$$(PSEP),$$@) $$(subst \,$$(PSEP),$$<) -MMD
endef

# Donne une fausse cible qui reconstruit les dépendances, parce que clean peut-être le nom d'un fichier qui peut-être plus récent que ses dépendances et la règle ne sera pas exécutée
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

# Inclut les dépendances
-include $(DEPS)

# Génère les règles
$(foreach targetdir, $(TARGETDIRS), $(eval $(call generateRules, $(targetdir))))

directories: 
	$(HIDE)$(MKDIR) $(subst \,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)

# Supprime tous les objets, dépendances et fichiers exécutables générés au cours de la construction
clean:
	$(HIDE)$(RMDIR) $(subst \,$(PSEP),$(TARGETDIRS)) $(ERRIGNORE)
	$(HIDE)$(RM) $(TARGET) $(ERRIGNORE)
	@echo Cleaning done !
