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

#include "warningpopup.h"
#include "ui_warningpopup.h"

WarningPopup::WarningPopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarningPopup)
{
    ui->setupUi(this);
    QObject::connect(ui->ignoreButton,SIGNAL(clicked()),this,SLOT(close()));
}

WarningPopup::~WarningPopup() {
    delete ui;
}

void WarningPopup::setWarningText(std::string text) {
    ui->warningText->setText(text.c_str());
}

void WarningPopup::setInfoText(std::string text) {
    ui->warningInfo->setText(text.c_str());
}
