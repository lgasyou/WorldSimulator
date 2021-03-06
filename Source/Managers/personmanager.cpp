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

#include "PersonManager.h"

PersonManager &PersonManager::instance() {
    static PersonManager personManager;
    return personManager;
}

void PersonManager::add(Person *person) {
    persons_.push_back(person);
}

void PersonManager::remove(Person *person) {
    persons_.erase(std::find(persons_.begin(), persons_.end(), person));
}

void PersonManager::update() { }

PersonManager::PersonManager() { }

PersonManager::~PersonManager() { }