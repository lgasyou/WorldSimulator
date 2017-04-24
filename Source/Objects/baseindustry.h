/*
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

#ifndef BASEINDUSTRY_H
#define BASEINDUSTRY_H

#include <vector>
#include <QString>

#include "land.h"
#include "warehouse.h"
#include "garage.h"
#include "goods.h"
#include "machine.h"

// This class should not be instantiated.
class BaseIndustry : public Land {
public:
    BaseIndustry(const QString &name, const QString &type);

    virtual ~BaseIndustry();

    // Adds a new Machine and update products and materials of this building.
    void addMachine(Machine *);

    void removeMachine(Machine *);

    // Updates data after each turn
    virtual void update() override;

    void manufacture();

    double store(const Goods &goods);

    double fetch(const Goods &goods);

public:
    Warehouse *warehouse() const { return warehouse_; }

    const std::vector<Machine *> &machines() const { return machines_; }

    const std::vector<GoodsLabel> &products() const { return products_; }

    const std::vector<GoodsLabel> &materials() const { return materials_; }

private:
    void setMaterialsAccordingToMachine(Machine *);

    void setProductsAccordingToMachine(Machine *);

private:
    Warehouse *warehouse_;

    std::vector<Machine *> machines_;

    std::vector<GoodsLabel> products_;

    std::vector<GoodsLabel> materials_;
};

inline void BaseIndustry::addMachine(Machine *machine) {
    machines_.push_back(machine);
    setMaterialsAccordingToMachine(machine);
    setProductsAccordingToMachine(machine);
}

inline void BaseIndustry::removeMachine(Machine *machine) {
    auto iter = std::find(machines_.begin(), machines_.end(), machine);
    machines_.erase(iter);
}

inline void BaseIndustry::update() {
    changeBaseValue();
    manufacture();
}

inline void BaseIndustry::manufacture() {
    std::for_each(machines_.begin(), machines_.end(), [](Machine *m) { m->produce(); });
}

inline double BaseIndustry::store(const Goods &goods) {
    return warehouse_->store(goods);
}

inline double BaseIndustry::fetch(const Goods &goods) {
    return warehouse_->fetch(goods);
}

#endif // BASEINDUSTRY_H
