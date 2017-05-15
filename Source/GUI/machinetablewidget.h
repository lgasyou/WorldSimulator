﻿/*
 *  Copyright 2017 Li Zeqing
 *
 *  This file is part of World Simulator.
 *  
 *  World Simulator is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  World Simulator is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with World Simulator. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MACHINETABLEWIDGET_H
#define MACHINETABLEWIDGET_H

#include <QTableWidget>

#include "Source/Objects/land.h"
#include "Source/Objects/baseindustry.h"
#include "Source/Objects/machine.h"

class MachineTableWidget : public QTableWidget {
    Q_OBJECT

public:
    MachineTableWidget(QWidget *parent = nullptr);

    ~MachineTableWidget();

    void init();

    void setIndustry(Land *industry);
    
public slots:
    void receiveShowDetailSignal(int);

    void updateDisplay();
    
signals:
    void sendSelectedMachine(Machine *);

private:
    BaseIndustry *industry_ = nullptr;
};

#endif // MACHINETABLEWIDGET_H