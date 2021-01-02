import qbs.FileInfo

QtApplication {
    Depends { name: "Qt.widgets" }

    cpp.defines: [
        // You can make your code fail to compile if it uses deprecated APIs.
        // In order to do so, uncomment the following line.
        //"QT_DISABLE_DEPRECATED_BEFORE=0x060000" // disables all the APIs deprecated before Qt 6.0.0
    ]

    files: [
        "des/descalc.cpp",
        "des/descalc.h",
        "des/destable.h",
        "des/desui.cpp",
        "des/desui.h",
        "des/desui.ui",
        "des/ip_inv_substitute_dlg.cpp",
        "des/ip_inv_substitute_dlg.h",
        "des/ip_inv_substitute_dlg.ui",
        "des/ip_substitute_dlg.cpp",
        "des/ip_substitute_dlg.h",
        "des/ip_substitute_dlg.ui",
        "des/iteration_16_dlg.cpp",
        "des/iteration_16_dlg.h",
        "des/iteration_16_dlg.ui",
        "des/key_gen_dlg.cpp",
        "des/key_gen_dlg.h",
        "des/key_gen_dlg.ui",
        "main.cpp",
        "mainwindow.cpp",
        "mainwindow.h",
    ]

    install: true
    installDir: qbs.targetOS.contains("qnx") ? FileInfo.joinPaths("/tmp", name, "bin") : base
}
