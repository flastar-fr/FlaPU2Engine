add_rules("mode.debug", "mode.release")
set_languages("c++17")

add_requires("gtest 1.16", {configs = {main = false}, system = false})
add_requires("imgui docking", {alias = "imgui-docking", configs = {glfw_opengl3 = true}})

add_includedirs("src", {public = true})

target("FlaPU2Engine")
    set_kind("binary")
    add_files("src/**.cpp")
    add_packages("imgui-docking")
    after_build(function (target)
        os.cp("ressources/", path.join(target:targetdir(), "."))
    end)

target("tests")
    set_kind("binary")
    add_files("tests/**.cpp")
    add_includedirs("tests")
    add_packages("gtest")
