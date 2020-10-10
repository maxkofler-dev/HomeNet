HEADERS += \
    ConfigParser.h \
    DriverListParser.h \
    ExceptionClass.h \
    HNPython.h \
    StartupMsg.h \
    WSValueserver.h \
    Weathersens.h

SOURCES += \
    ConfigParser.cpp \
    DriverListParser.cpp \
    ExceptionClass.cpp \
    HNPython.cpp \
    StartupMsg.cpp \
    WSValueserver.cpp \
    Weathersens.cpp \
    main.cpp

LIBS += -L/usr/lib/python3.9/config -lpython3.9
INCLUDEPATH += /usr/include/python3.9
