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
INCLUDEPATH += compiled-nzcp-c/usr/local/include /opt/homebrew/include 
LIBPATH += compiled-nzcp-c/usr/local/lib /opt/homebrew/lib
PKGCONFIG += MagickWand


LIBS += -lnzcp -lzbar 