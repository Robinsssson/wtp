#pragma once
/*
 * wtp_ansys.hpp
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

#include <string>
constexpr const char* VERSION = "1.0.0";

enum class option {
    version,
    help,
    copy,
    remove,
};

class wtp_ansys {
   public:
    wtp_ansys();
    void get(option opt, std::string src = "", std::string = "");

   private:
    void copy(std::string src, std::string dst);
    void remove(std::string src);
    void help();
    void version();

    std::string win_path;
};
