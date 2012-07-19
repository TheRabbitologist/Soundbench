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

#include <fstream>

void SoundbenchMain::loadInternalPreset() {
    stopAndReset();
    currpreset = ui->presetList->currentRow();
    auto dat = arch->loadPreset(presetlist[currpreset].path,datadir+"/presets",blu);
    if(dat.path.empty()) {
        loadPresetList(); //Maybe a preset got deleted.
        displayPresets();
        em->start();

        ui->presetLabel->setEnabled(false);
        ui->presetLabel->setText("Preset Loading Failed");

        return;
    }
    else { //Update the preset's data just in case.
        presetlist[currpreset].name = dat.name;
        presetlist[currpreset].arti = dat.arti;
        presetlist[currpreset].desc = dat.desc;
    }

    ui->importButton->setDisabled(true);
    ui->saveButton->setEnabled(true);
    ui->exportButton->setEnabled(true);

    ui->presetLabel->setEnabled(true);
    ui->presetLabel->setText(presetlist[currpreset].name.c_str());

    external = false;
    arch->buildSynth(syn,blu);
    updateToBlueprint();
    em->start();
}

void SoundbenchMain::loadExternalPreset() {
    stopAndReset();
    met->pauseMeter();
    QString chosenfile = QFileDialog::getOpenFileName(NULL,"Choose a preset to open...", "~/", "Soundbench Presets (*.sbp)");
    if (!chosenfile.size()) {
        em->start();
        met->startMeter();
        return;
    }
    plai->stopRt();
    externalpresetdata = arch->loadPreset(chosenfile.toStdString(),"",blu);
    if(externalpresetdata.path.empty()) {
        ui->presetLabel->setEnabled(false);
        ui->presetLabel->setText("Preset Loading Failed");
        em->start();
        met->startMeter();
    }

    external = true;
    arch->buildSynth(syn,blu);
    updateToBlueprint();
    plai->startRt();
    em->start();
    met->startMeter();

    ui->presetLabel->setEnabled(true);
    ui->presetLabel->setText((externalpresetdata.name + " (External)").c_str());

    ui->saveButton->setEnabled(true);

    ui->importButton->setEnabled(true);
    ui->deleteButton->setEnabled(true);
}

void SoundbenchMain::deletePreset() {
    WarningPopup popu;
    popu.setWarningText("Confirm Deletion");
    popu.setInfoText("Once you delete a preset, the operation cannot be trivially undone.");
    popu.exec();

    if (!popu.fixed())
        return;

    QFile delfile;
    if (external)
        delfile.setFileName(externalpresetdata.path.c_str());
    else
        delfile.setFileName((datadir+"/presets/"+presetlist[currpreset].path).c_str());
    delfile.remove();
    loadPresetList(); //Reload the list

    ui->deleteButton->setEnabled(false);
    if (!external) {
        writePresetRecord();
        displayPresets();
        loadPresetList();
    }
}

void SoundbenchMain::importPreset() {
    if (!external)
        return;
    QFile inport(externalpresetdata.path.c_str());
    inport.copy(externalpresetdata.path.c_str(),(datadir+"/presets/"+externalpresetdata.name+"_imported.sbp").c_str());

    presetlist.push_back(externalpresetdata);
    currpreset = presetlist.size()-1;
    external = false;

    ui->importButton->setEnabled(false);
    ui->presetLabel->setText(externalpresetdata.name.c_str());
}

void SoundbenchMain::savePreset() {
    if (external) {
        arch->savePreset(externalpresetdata.path,
                         "",blu,
                         externalpresetdata.name,
                         externalpresetdata.arti,
                         externalpresetdata.desc);
    }
    else {
        arch->savePreset(presetlist[currpreset].path,
                         datadir+"/presets",blu,
                         presetlist[currpreset].name,
                         presetlist[currpreset].arti,
                         presetlist[currpreset].desc);
    }
}

void SoundbenchMain::exportPreset() {
    std::string newname = QFileDialog::getOpenFileName(NULL,"Choose a file to save a copy to...", "~/", "Soundbench Presets (*.sbp)").toStdString();
    if(newname.find_last_of('.') != newname.size()-5) {
        newname += ".sbp";
    }
    if (external) {
        arch->savePreset(newname,
                         "",blu,
                         externalpresetdata.name,
                         externalpresetdata.arti,
                         externalpresetdata.desc);
    }
    else {
        arch->savePreset(newname,
                         "",blu,
                         presetlist[currpreset].name,
                         presetlist[currpreset].arti,
                         presetlist[currpreset].desc);
    }
}

void SoundbenchMain::refreshPresets() {
    std::cerr << "Removing " << datadir << "/presetrecord...\n";
    QFile delfile((datadir+"/presetrecord").c_str());
    delfile.remove(); //Get rid of a certain preset record.
    writePresetRecord();
    loadPresetList();
    displayPresets();
}

void SoundbenchMain::resetBlueprint() {
    stopAndReset();
    arch->planAllDefaults(blu);
    arch->buildSynth(syn,blu);

    ui->presetLabel->setDisabled(true);
    ui->presetLabel->setText("Unnamed Preset");

    ui->gener1TypeBox->setCurrentIndex(0);
    ui->gener2TypeBox->setCurrentIndex(0);
    ui->gener3TypeBox->setCurrentIndex(0);
    ui->gener4TypeBox->setCurrentIndex(0);

    ui->gen1SettButton->setDisabled(true);
    ui->gen2SettButton->setDisabled(true);
    ui->gen3SettButton->setDisabled(true);
    ui->gen4SettButton->setDisabled(true);

    em->start();
}
