QT += widgets
requires(qtConfig(combobox))

HEADERS     = dialog.h
SOURCES     = dialog.cpp \
              main.cpp

# install
INSTALLS += target
