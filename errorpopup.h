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
#ifndef ERRORPOPUP_H
#define ERRORPOPUP_H

#include <QDialog>

#include "problemfix.h"

namespace Ui {
    class ErrorPopup;
}

class ErrorPopup : public QDialog
{
    Q_OBJECT

public:
    explicit ErrorPopup(QWidget *parent = 0);
    ~ErrorPopup();

private:
    Ui::ErrorPopup *ui;
};

#endif // ERRORPOPUP_H
