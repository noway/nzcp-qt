QT += widgets
requires(qtConfig(combobox))

HEADERS     = dialog.h
SOURCES     = dialog.cpp \
              main.cpp

# install
INSTALLS += target
INCLUDEPATH += compiled-nzcp-c/usr/local/include
LIBPATH += compiled-nzcp-c/usr/local/lib
LIBS += -lnzcp