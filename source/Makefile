.PHONY: clean all run

TARGET 		= game
CC 			= gcc
CXX			= g++
CLANGC		= clang
CLANGXX		= clang++
CLANG_TIDY	= clang-tidy

PROJ_DIR	= $(realpath $(CURDIR)/..)
SRC_DIR 	= $(PROJ_DIR)/src

CPP_DIRS	= application\
				application/config\
				application/input\
				application/player\
				application/scene\
				application/window\
				core\
				core/algorithms\
				core/error\
				core/GL\
				core/logging\
				core/math\
				core/physics\
				core/platform\
				core/threads\
				core/utils\
				rendering\
			 	rendering/components rendering/components/textures rendering/components/shaders\
				rendering/data\
				rendering/renderer\
				rendering/world rendering/world/block rendering/world/chunk\
				rendering/world/generation rendering/world/generation/biome rendering/world/generation/terrain

CPP_INC		= application core physics rendering 

LIBS 		= -L$(PROJ_DIR)/lib

INC_DIRS	= -I$(PROJ_DIR)/lib
INC_DIRS	+= -I$(PROJ_DIR)/src
INC_DIRS	+= -I$(PROJ_DIR)/include
INC_DIRS	+= $(foreach dir, $(CPP_INC), -I$(dir))

BUILD_DIR 	= ./../build
BUILD_DIRS 	= $(BUILD_DIR)
BUILD_DIRS	+= $(foreach dir, $(CPP_DIRS), ./../build/$(dir))

CFLAGS		= -ggdb3 -pthread -std=c++17 -Wno-c++98-compat-pedantic -Wno-c++98-compat -Wall -Wextra
CPPFLAGS	= -ltbb -ldl -lglfw3 -lglut -lGLEW -lGLU -lX11 -lpthread -lassimp

CFILES 		= $(wildcard *.c)
CPPFILES	= $(wildcard *.cpp)
CPPFILES	+= $(foreach dir,$(CPP_DIRS), $(wildcard $(dir)/*.cpp))


OBJ_FILES 	= $(patsubst %.c, $(BUILD_DIR)/%.o, $(CFILES))
OBJ_FILES  += $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(CPPFILES))

DEPS_FILE 	= $(OBJ_FILES:.o=.d)

VPATH 		= $(CFILES)

all: $(BUILD_DIR)/$(TARGET) run

$(BUILD_DIR)/$(TARGET) : $(OBJ_FILES)
	@echo linking $(TARGET)
	@echo $@
	@$(CLANGXX) -o $@ $^ $(CPPFLAGS)

$(BUILD_DIR)/%.o: %.c
	@echo compiling $<
	$(shell mkdir -p $(BUILD_DIRS))
	@$(CLANGC) $(INC_DIRS) -c $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	@echo compiling $<
	$(shell mkdir -p $(BUILD_DIRS))
	@$(CLANGXX) $(CFLAGS) $(INC_DIRS) -c $< -o $@

run:
	@echo Running $(TARGET)
	@./../build/$(TARGET)

clean:
	rm -r $(BUILD_DIR)