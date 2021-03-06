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

#ifndef INDUSTRY_CHAIN_MANAGER_H
#define INDUSTRY_CHAIN_MANAGER_H

#include <vector>

#include "Source/Objects/Goods.h"

#include "Source/graph.h"

// This class contains the industry chain of this game.
class IndustryChainManager {
public:
    // Gets single instance.
    static IndustryChainManager &instance();

    void init();

    // Returns the cost from origin to destination.
    double cost(const QString &orig, const QString &dest) const;

    std::vector<Goods> precursors(const QString &item) const;

    std::vector<Goods> successors(const QString &item) const;

private:
    // Hides constructor and destructor.
    IndustryChainManager();

    ~IndustryChainManager();

private:
    Graph industryChain_;

};
#endif // !INDUSTRY_CHAIN_MANAGER_H
