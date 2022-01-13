CONFIG += link_pkgconfig
QT += widgets
requires(qtConfig(combobox))

HEADERS     = dialog.h uri.h qrfile.h
SOURCES     = dialog.cpp \
              uri.cpp \
              qrfile.cpp \
              main.cpp

# install
INSTALLS += target

PKGCONFIG += Magick++ zbar
INCLUDEPATH += compiled-nzcp-c/usr/local/include
LIBPATH += compiled-nzcp-c/usr/local/lib
LIBS += -lnzcp