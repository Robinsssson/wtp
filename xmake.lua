add_rules("mode.debug", "mode.release")
set_languages("c++17")

target("wtp")
    set_kind("binary")
    add_files("src/*.cpp")
    add_includedirs("include")
    set_license("GPL-2.0")
target_end()