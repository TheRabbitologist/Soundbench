/*
    This file is part of Soundbench.

    Soundbench is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Soundbench is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Soundbench.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2012  Amaya S.
*/

#include "soundbenchmain.h"


void SoundbenchMain::importOpen() {
    stopAndReset();
    met->pauseMeter();
    QString chosenfile = QFileDialog::getOpenFileName(
                NULL,"Choose a file to import...", "~/", "Standard MIDI Files (*.mid *.smf);;All Files (*)");

    if (!chosenfile.size()) {
        em->start();
        met->startMeter();
        return;
    }
    plai->setFile(chosenfile.toStdString());
    if(!plai->loadFile()) {
        em->start();
        met->startMeter();
        return;
    }
    ui->exportButton->setEnabled(true);
    ui->songsTracksList->setCurrentRow(0);

    ui->tempoBox->setValue(plai->getTempo());
    if (plai->getTempo()) {
        ui->tempoBox->setEnabled(true);
        ui->tempoBox->setToolTip("Change the starting tempo of the current track.");
    }
    else {
        ui->tempoBox->setDisabled(true);
        ui->tempoBox->setToolTip("This MIDI file does not represent time in terms of beats, and thus the tempo box has been disabled.");
    }

    em->start();
    met->startMeter();
}

void SoundbenchMain::exportOpen() {
    if(plai->empty())
        return;
    stopAndReset();
    met->setProgress(0);
    QString chosenfile = QFileDialog::getSaveFileName(
                NULL,"Choose a file to export to...", "~/",
                "Wave File (*.wav);;AIFF File (*.aiff);;Free Lossless Audio Codec File (*.flac);;Headerless RAW file (*.raw);;MAT5 Binary Data File (*.mat)"); //Put .mid back in here in version 0.3.0.
    if (!chosenfile.size()) {
        em->start();
        met->startMeter();
        return;
    }

    plai->setFile(chosenfile.toStdString());
    plai->writeFile();
    syn->reset();
    met->startMeter();
    em->start();
}

void SoundbenchMain::setTempo(int tiem) {
    plai->setTempo(tiem);
    plai->loadTrack(ui->songsTracksList->currentRow());
}

void SoundbenchMain::playSynth(bool b) {
    if (plai->empty())
        return;
    if (b)
        plai->startPlay();
    else
        plai->stopPlay();
}

void SoundbenchMain::loadPorts() {
    ui->inputsList->clear();
    for(std::string dev : plai->getPorts())
        ui->inputsList->addItem(dev.c_str());
    ui->inputsList->setCurrentRow(plai->getCurrentPort());
}
void SoundbenchMain::loadDevices() {
    ui->outputsList->clear();
    for(std::string dev : em->getDevices())
        ui->outputsList->addItem(dev.c_str());
    ui->outputsList->setCurrentRow(em->getCurrentDevice());
}

void SoundbenchMain::setTrack(int e) {
    if(!plai->loadTrack(static_cast<uint16_t>(e)))
        return;
    ui->tempoBox->setValue(plai->getTempo());
    met->startMeter();
}