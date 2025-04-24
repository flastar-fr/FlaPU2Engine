add_rules("mode.debug", "mode.release")

add_requires("gtest")

target("BatPU2Engine")
    set_kind("binary")
    add_files("src/*.cpp")

target("tests")
    set_kind("binary")
    add_files("tests/*.cpp")
    add_includedirs("src", { public = true })

    add_packages("gtest")
