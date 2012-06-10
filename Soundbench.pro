#######################################################################
# Automatically generated by the Soundbench team at some point in time.
#######################################################################

QMAKE_CXXFLAGS_WARN_ON += -Wall -Wextra -pedantic
QMAKE_CXXFLAGS += -std=c++0x

DEFINES += IS_SOUNDBENCH NO_JACK  #JACK support doesn't exist yet.

TEMPLATE = app
TARGET = 
DEPENDPATH += .

unix: INCLUDEPATH += /usr/include/

# Input
HEADERS += architect.h \
    backend/portaudio.h \
    basicwaves.h \
    blueprint.h \
    common.h \
    emitter/emitter.h \
    errorpopup.h \
    gentypedialog.h \
    ui/sbmain/soundbenchmain.h \
    synth.h \
    warningpopup.h \
    application.h \
    meterupdater.h \
    player/player.h \
    midichain.h \
    problemfix.h \
    backend/base.h \
    sbutilities.h \
    midienums.h \
    ui/settings/basicgen.h \
    soundbases.h \
    gener/basic.h \
    cpumeter.h \
    midifio/midifio.h \
    sfwriter.h \
    sampletable.h \
    backend/jack.h \
    frontend/base.h \
    frontend/portmidi.h \
    noteinput.h \
    trapezoid.h \
    presetenums.h \
    ticker.h \
    printhelp.h

FORMS += errorpopup.ui \
    gentypedialog.ui \
    ui/sbmain/soundbenchmain.ui \
    warningpopup.ui \
    ui/settings/basicgen.ui

SOURCES += emitter/initportaudio.cpp \
    architect.cpp \
    backend/portaudio.cpp \
    basicwaves.cpp \
    emitter/emitter.cpp \
    errorpopup.cpp \
    gentypedialog.cpp \
    main.cpp \
    warningpopup.cpp \
    synth.cpp \
    application.cpp \
    meterupdater.cpp \
    ui/sbmain/slots.cpp \
    ui/sbmain/func.cpp \
    ui/settings/basicgen.cpp \
    gener/basic.cpp \
    ui/sbmain/init.cpp \
    midifio/read.cpp \
    midifio/readeropen.cpp \
    midifio/misc.cpp \
    sfwriter.cpp \
    player/load.cpp \
    player/write.cpp \
    sampletable.cpp \
    backend/jack.cpp \
    frontend/portmidi.cpp \
    frontend/portmidi-parse.cpp \
    noteinput.cpp \
    trapezoid.cpp \
    emitter/initsomething.cpp

RESOURCES += \
    resources.qrc

unix: LIBS += -L/usr/lib/

LIBS += -lsndfile

#Configuration switches to remove certain functionality and dependencies where necessary.
!noPortAudio {
    LIBS += -lportaudio -lportaudiocpp
}
noPortAudio {
    DEFINES += NO_PORTAUDIO
}

!noPortMidi{
    LIBS += -lportmidi
}
noPortMidi {
    DEFINES += NO_MIDI
}


OTHER_FILES += \
    ProgrammingStyleRegulations.txt \
    COPYING \
    README
