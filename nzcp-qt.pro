QT += widgets
requires(qtConfig(combobox))

HEADERS     = dialog.h
SOURCES     = dialog.cpp \
              main.cpp

# install
INSTALLS += target
INCLUDEPATH += nzcp-c-install/usr/local/include
LIBPATH += nzcp-c-install/usr/local/lib
LIBS += -lnzcp