#float* get_stacks(tID)
#int    get_players(tID)
#float* get_blinds(tID)
#char** get_names(tID) ??
#char** get_pIDs(tID)
#char*  get_name(pID)
#int*   get_prizes(tID, int* num)
TARGET = iicm
TEMPLATE = app

CONFIG = \
    qt \
#    gcc \
    debug
# release
qt =\
    core \
    gui

INCLUDEPATH += . \
    /usr/include/libpq \
    /usr/include/poker-eval \
    /usr/include/wine/windows
LIBRARY_PATH = /usr/lib
DEPENDPATH += .
OBJECTS_DIR = /tmp/
MOC_DIR = /tmp/

LIBS += -lpq -luser32
SOURCES += \
    main.cpp \
    calc_icm.c \
    iicm_gui.cpp \
    sql_main.c \
    misc_helpers.c \
    win_tabledata.c
HEADERS += \
    iicm_gui.hpp \
    calc_icm.h \
    sql_main.h \
    misc_helpers.h \
    misc_bool.h \
    win_tabledata.h

RELEASEFLAGS += \
#    -O4 \
    -O3 \
    -fomit-frame-pointer \
    -march=i686 \
    -ffast-math \
#   -flto \
    -fwhole-program
DEBUGFLAGS += \
    -O0 \
    -ggdb \
    -pedantic \
    -W \
    -Wall \
    -Wextra \
    -Wuninitialized \
    -Wshadow \
    -Wsign-compare \
    -Wwrite-strings \
    -Wunused \
    -Wfloat-equal \
    -Wmissing-declarations \
    -Wunreachable-code \
    -Wcast-qual
QMAKE_LFLAGS_RELEASE = $$RELEASEFLAGS
QMAKE_LFLAGS_DEBUG = $$DEBUGFLAGS
QMAKE_CFLAGS_GENERIC = \
    -std=c99 \
    -Wc++-compat \
    -pipe
QMAKE_CFLAGS_RELEASE = \
    $$QMAKE_CFLAGS_GENERIC \
    $$RELEASEFLAGS
QMAKE_CFLAGS_DEBUG = \
    $$QMAKE_CFLAGS_GENERIC \
    $$DEBUGFLAGS
QMAKE_CXXFLAGS_GENERIC = \
    -std=c++98 \
    -pipe
QMAKE_CXXFLAGS_RELEASE = \
    $$QMAKE_CXXFLAGS_GENERIC \
    $$RELEASEFLAGS
QMAKE_CXXFLAGS_DEBUG = \
    $$QMAKE_CXXFLAGS_GENERIC \
    $$DEBUGFLAGS

QMAKE_CC = clang
QMAKE_CXX = clang
CONFIG(gcc) {
    QMAKE_CC = gcc
    QMAKE_CXX = g++
}
