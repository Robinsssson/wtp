/*
 * main.cpp
 *
 * Copyright (C) 2024 robinsssson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <string>

#include "../include/wtp_ansys.h"

int main(int argc, char **argv) {
    wtp_ansys wtp;
    std::string strings[argc];
    for (int i = 0; i < argc; i++) {
        strings[i] = argv[i];
    }
    if (argc == 1) {
        wtp.get(option::help);
    } else if (strings[1] == "-v" || strings[1] == "--version") {
        wtp.get(option::version);
    } else if (strings[1] == "-h" || strings[1] == "--help") {
        wtp.get(option::help);
    } else if (strings[1] == "-c" || strings[1] == "--copy") {
        std::string src = strings[2];
        std::string dst = strings[3];
        try {
            if (src == "") throw std::runtime_error("Invalid source");
        } catch (const std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
        }
        wtp.get(option::copy, src, dst);
    } else if (strings[1] == "-r" || strings[1] == "--remove") {
        std::string src = strings[2];
        wtp.get(option::remove, src);
    } else {
        std::cerr << "Invalid option" << std::endl;
        std::cout << strings[1] << std::endl;
    }
    return 0;
}
