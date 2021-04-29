QMAKE_CXXFLAGS += -I/usr/include/python3.9
QMAKE_LFLAGS += -lpthread -lpython3.9
HEADERS += \
    Weathersens/ConfigParser/ConfigParser.h \
    Weathersens/DriverListParser/DriverListParser.h \
    Weathersens/ExceptionClass/ExceptionClass.h \
    Weathersens/HNNetworking/HNNetworking.h \
    Weathersens/HNPython/HNPython.h \
    Weathersens/StartupMsg/StartupMsg.h \
    Weathersens/WSHistory/WSHistory.h \
    Weathersens/WSHistory/history/history.h \
    Weathersens/WSValueserver/WSValueserver.h \
    Weathersens/Weathersens/Weathersens.h \
    log/log.h

SOURCES += \
    Weathersens/ConfigParser/ConfigParser.cpp \
    Weathersens/DriverListParser/DriverListParser.cpp \
    Weathersens/ExceptionClass/ExceptionClass.cpp \
    Weathersens/HNNetworking/HNNetworking.cpp \
    Weathersens/HNPython/HNPython.cpp \
    Weathersens/StartupMsg/StartupMsg.cpp \
    Weathersens/WSHistory/WSHistory.cpp \
    Weathersens/WSHistory/history/history.cpp \
    Weathersens/WSValueserver/WSValueserver.cpp \
    Weathersens/Weathersens/Weathersens.cpp \
    main.cpp
