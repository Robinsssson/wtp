/*
 * wtp_ansys.cpp
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

#include "../include/wtp_ansys.h"

#include <stdlib.h>

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <system_error>

void wtp_ansys::get(option opt, std::string src, std::string dst) {
    switch (opt) {
        case option::copy:
            copy(src, dst);
            break;
        case option::remove:
            remove(src);
            break;
        case option::help:
            help();
            break;
        case option::version:
            version();
            break;
    }
}
wtp_ansys::wtp_ansys() {
    char *str = std::getenv("WIN");
    if (str == nullptr) {
        std::cout << "WIN environment variable not set" << std::endl;
        std::cout << "Please set WIN environment variable" << std::endl;
        std::cout << "Example: export WIN=/mnt/c/Users/username" << std::endl;
        std::cout << "Or you can set in wtp" << std::endl;
        std::cout << "Do you want to set WIN in wtp? [y/n]: ";

        char c;
        std::cin >> c;
        if (c == 'y') {
            std::string user_name;
            auto pout = popen("whoami", "r");
            if (pout) {
                char buf[1024];
                while (!feof(pout)) {
                    if (fgets(buf, 1024, pout) != NULL) user_name += buf;
                }
                pclose(pout);
            }
            std::cout << "User: " << user_name;
            user_name.pop_back();
            std::cout << "Which shell are you using? [1/2]:" << std::endl;
            std::cout << "\t1. bash" << std::endl;
            std::cout << "\t2. zsh" << std::endl;
            int x;
            std::cin >> x;
            std::string shell_file;
            if (x == 1)
                shell_file = ".bashrc";
            else if (x == 2)
                shell_file = ".zshrc";
            else
                exit(1);

            std::fstream file;
            try {
                file.open("/home/" + user_name + "/" + shell_file,
                          std::ios::app | std::ios::out);

                if (!file.is_open())
                    throw std::runtime_error("Error opening file");
                std::cout << "/home/" + user_name + "/" + shell_file
                          << " has opened!" << std::endl;

                // Check if WIN is already set
                std::string line;
                while (std::getline(file, line)) {
                    if (line.find("export WIN=") != std::string::npos) {
                        std::cout << "WIN already set" << std::endl;
                        exit(1);
                    }
                }

                std::string win;
                std::cout << "Enter WIN path:";
                std::cin >> win;
                win_path = win;
                file << "# WIN path\n";
                // check win is right path
                if (std::filesystem::exists(win)) {
                    std::cout << "WIN path exists" << std::endl;
                } else {
                    throw std::runtime_error("WIN path does not exist");
                }
                file << "export WIN=" << win << std::endl;
                file.close();
            } catch (const std::runtime_error &e) {
                std::cerr << e.what() << std::endl;
                file.close();
            }
        } else {
            exit(1);
        }
    } else {
        win_path = str;
    }
}

void wtp_ansys::copy(std::string src, std::string dst) {
    std::string command = "cp " + src + " " + win_path + dst;
    auto ret = std::system(command.c_str());
    try {
        if (ret == 0)
            std::cout << "File copied successfully" << std::endl;
        else
            throw std::runtime_error("Error copying file");
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

void wtp_ansys::remove(std::string src) {
    std::string command = "rm " + src;
    auto ret = std::system(command.c_str());
    try {
        if (ret == 0)
            std::cout << "File removed successfully" << std::endl;
        else
            throw std::runtime_error("Error removing file");
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }
}

void wtp_ansys::help() {
    std::cout << "wtp [option] [file]" << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "wtp -c [file] [destination]\tCopy file to WIN/destination"
              << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "-v, --version\t\tShow version" << std::endl;
    std::cout << "-h, --help\t\tShow help" << std::endl;
    std::cout << "-c, --copy\t\tCopy file" << std::endl;
    std::cout << "-r, --remove\t\tRemove file" << std::endl;
}
void wtp_ansys::version() {
    std::cout << "wtp " << VERSION << std::endl;
    std::cout << "Copyright (C) 2024 Free Software Foundation, Inc.\n"
                 "This is free software; see the source for copying "
                 "conditions.  There is NO\n"
                 "warranty; not even for MERCHANTABILITY or FITNESS FOR A "
                 "PARTICULAR PURPOSE."
              << std::endl;
}