add_rules("mode.debug", "mode.release")

package("qt-ads")
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "/3rd/qt-ads"))
    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DCMAKE_BUILD_TYPE=" .. (package:debug() and "Debug" or "Release"))
        table.insert(configs, "-DBUILD_SHARED_LIBS=" .. (package:config("shared") and "ON" or "OFF"))
        import("package.tools.cmake").install(package, configs)
    end)
package_end()

add_requires("qt-ads", {configs = {vs_runtime = "MD", shared = true}})

target("testqt")
    add_rules("qt.widgetapp")
    add_includedirs("3rd/qt-ads/src")
    add_headerfiles("src/*.h")
    add_files("src/*.cpp")
    add_files("src/mainwindow.ui")
    add_files("src/mainwindow.h")
    add_packages("qt-ads")
