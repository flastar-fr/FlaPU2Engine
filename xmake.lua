add_rules("mode.debug", "mode.release")
set_languages("c++17")

add_requires("gtest", {configs = {main = false}, system = false})

add_includedirs("src", {public = true})

target("FlaPU2Engine")
    set_kind("binary")
    add_files("src/**.cpp")
    after_build(function (target)
        os.cp("ressources/", path.join(target:targetdir(), "."))
    end)

target("tests")
    set_kind("binary")
    add_files("tests/**.cpp")
    add_includedirs("tests")
    add_packages("gtest")
