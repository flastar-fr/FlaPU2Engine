add_rules("mode.debug")

add_requires("gtest")

add_includedirs("src")

target("BatPU2Engine")
    set_kind("binary")
    add_files("src/**.cpp")
    after_build(function (target)
            os.cp("ressources/", path.join(target:targetdir(), "ressources/"))
        end)

target("tests")
    set_kind("binary")
    add_files("tests/*.cpp")
    add_includedirs("src", { public = true })

    add_packages("gtest")
