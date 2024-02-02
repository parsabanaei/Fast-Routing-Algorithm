QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CustomComboBox.cpp \
    admineditwindow.cpp \
    adminmaintenance.cpp \
    adminpanel.cpp \
    adminwindow.cpp \
    customtrip.cpp \
    dbhandler.cpp \
    europeancities.cpp \
    foodpurchase.cpp \
    main.cpp \
    mainwindow.cpp \
    purchaseform.cpp \
    purchasehistory.cpp \
    startingFromParis.cpp \
    traditionalFood.cpp

HEADERS += \
    CustomComboBox.h \
    GlobalCitiesArray.h \
    GlobalVector.h \
    admineditwindow.h \
    adminmaintenance.h \
    adminpanel.h \
    adminwindow.h \
    consts.h \
    customtrip.h \
    dbhandler.h \
    europeancities.h \
    foodpurchase.h \
    mainwindow.h \
    purchaseform.h \
    purchasehistory.h \
    startingFromParis.h \
    traditionalFood.h

FORMS += \
    admineditwindow.ui \
    adminmaintenance.ui \
    adminpanel.ui \
    adminwindow.ui \
    customtrip.ui \
    europeancities.ui \
    food.ui \
    foodpurchase.ui \
    mainwindow.ui \
    purchaseform.ui \
    purchasehistory.ui \
    startingFromParis.ui \
    traditionalFood.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
