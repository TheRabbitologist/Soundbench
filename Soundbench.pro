#######################################################################
# Automatically generated by the Soundbench team at some point in time.
#######################################################################

CONFIG += noPortAudio noJack

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS_WARN_ON += -Wall -Wextra -pedantic
QMAKE_CXXFLAGS += -std=c++11

DEFINES += IS_SOUNDBENCH

TEMPLATE = app
TARGET = Soundbench
DEPENDPATH += .

unix: INCLUDEPATH += /usr/include/
unix: INCLUDEPATH += /usr/local/include/
unix: LIBS += -L/usr/lib/
unix: LIBS += -L/usr/local/lib/

macx: INCLUDEPATH += /Library/Developer/CommandLineTools/usr/lib/c++/v1/
macx: LIBS += -lc++

# Input
HEADERS += common.h \
	emitter/emitter.h \
    player/player.h \
    backend/base.h \
    sbutilities.h \
	sampletable/periodictable.h \
    gener/basic.h \
    midifio/midifio.h \
    frontend/base.h \
    presetenums.h \
    printhelp.h \
    waves/basicwaves.h \
    backend/portaudio.h \
    backend/rtaudio.h \
    frontend/rtmidi.h \
    backend/jackaudio.h \
    emitter/initbackend.h \
    frontend/jackmidi.h \
	synth/synth.h \
    fx/biquad.h \
    gener/sampler.h \
    util/jackbase.h \
    err/problemfix.h \
    err/errorpopup.h \
    err/warningpopup.h \
    envelope/trapezoid.h \
    util/basicticker.h \
	waves/wavebase.h \
    util/fileparsers.h \
    util/filewriters.h \
    player/midichain.h \
    util/sfwriter.h \
    midifio/midievents.h \
    util/meterupdater.h \
    synth/synth.h

SOURCES += \
    backend/portaudio.cpp \
    emitter/emitter.cpp \
	main.cpp \
    gener/basic.cpp \
    waves/basicwaves.cpp \
    backend/rtaudio.cpp \
	frontend/rtmidi.cpp \
    player/playermisc.cpp \
    player/midiinit.cpp \
    player/playerload.cpp \
    player/playerwrite.cpp \
	player/playerinit.cpp \
    midifio/fiomisc.cpp \
    midifio/fioread.cpp \
    midifio/fioreadopen.cpp \
    backend/jackaudio.cpp \
	frontend/jackmidi.cpp \
    fx/biquad.cpp \
	fx/biquad_ctrl.cpp \
    gener/sampler.cpp \
    envelope/trapezoid.cpp \
	sampletable/periodictable.cpp \
    err/errorpopup.cpp \
    util/sfwriter.cpp \
    synth/doevent.cpp \
    player/makenode.cpp \
    err/warningpopup.cpp \
    util/meterupdater.cpp

LIBS += -lsndfile

#Configuration switches to remove certain functionality and dependencies where necessary.
!noPortAudio {
    LIBS += -lportaudio -lportaudiocpp
}
noPortAudio {
    DEFINES += NO_PORTAUDIO
}

!noRtAudio{
    LIBS += -lrtaudio
}
noRtAudio {
    DEFINES += NO_RTAUDIO
}

!noRtMidi{
    LIBS += -lrtmidi
}
noRtMidi {
    DEFINES += NO_RTMIDI
}

!noJack{
    LIBS += -ljack
}
noJack {
    DEFINES += NO_JACK
}


OTHER_FILES += \
    ProgrammingStyleRegulations.txt \
    COPYING \
    README \
    PresetSpecification.txt \
    RecordSpecification.txt
