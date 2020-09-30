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

LIBS += -L/usr/lib/python3.8/config -lpython3.8
INCLUDEPATH += /usr/include/python3.8
