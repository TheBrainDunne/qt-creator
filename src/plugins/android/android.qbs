import qbs 1.0

Project {
    name: "Android"

    QtcDevHeaders { }

    QtcPlugin {
        Depends { name: "Qt"; submodules: ["widgets", "xml", "network"] }
        Depends { name: "Core" }
        Depends { name: "Debugger" }
        Depends { name: "ProParser" }
        Depends { name: "ProjectExplorer" }
        Depends { name: "QmlDebug" }
        Depends { name: "QtSupport" }
        Depends { name: "TextEditor" }
        Depends { name: "Utils" }
        Depends { name: "app_version_header" }

        files: [
            "android_global.h",
            "android.qrc",
            "adbcommandswidget.cpp",
            "adbcommandswidget.h",
            "adbcommandswidget.ui",
            "addnewavddialog.ui",
            "androidavdmanager.cpp",
            "androidavdmanager.h",
            "androidconfigurations.cpp",
            "androidconfigurations.h",
            "androidconstants.h",
            "androidcreatekeystorecertificate.cpp",
            "androidcreatekeystorecertificate.h",
            "androidcreatekeystorecertificate.ui",
            "androidbuildapkstep.cpp",
            "androidbuildapkstep.h",
            "androidbuildapkwidget.cpp",
            "androidbuildapkwidget.h",
            "androidbuildapkwidget.ui",
            "androiddeployqtstep.cpp",
            "androiddeployqtstep.h",
            "androiddebugsupport.cpp",
            "androiddebugsupport.h",
            "androiddevicedialog.cpp",
            "androiddevicedialog.h",
            "androiddevicedialog.ui",
            "androiddeployconfiguration.cpp",
            "androiddeployconfiguration.h",
            "androiddeployqtwidget.cpp",
            "androiddeployqtwidget.h",
            "androiddeployqtwidget.ui",
            "androiddevice.cpp",
            "androiddevice.h",
            "androiddevicefactory.cpp",
            "androiddevicefactory.h",
            "androiderrormessage.h",
            "androiderrormessage.cpp",
            "androidgdbserverkitinformation.cpp",
            "androidgdbserverkitinformation.h",
            "androidglobal.h",
            "androidmanager.cpp",
            "androidmanager.h",
            "androidmanifestdocument.cpp",
            "androidmanifestdocument.h",
            "androidmanifesteditor.cpp",
            "androidmanifesteditor.h",
            "androidmanifesteditorfactory.cpp",
            "androidmanifesteditorfactory.h",
            "androidmanifesteditorwidget.cpp",
            "androidmanifesteditorwidget.h",
            "androidpackageinstallationstep.cpp",
            "androidackageinstallationstep.h",
            "androidplugin.cpp",
            "androidplugin.h",
            "androidpotentialkit.cpp",
            "androidpotentialkit.h",
            "androidqmltoolingsupport.cpp",
            "androidqmltoolingsupport.h",
            "androidqtsupport.cpp",
            "androidqtsupport.h",
            "androidqtversion.cpp",
            "androidqtversion.h",
            "androidqtversionfactory.cpp",
            "androidqtversionfactory.h",
            "androidrunconfiguration.cpp",
            "androidrunconfiguration.h",
            "androidrunconfigurationwidget.cpp",
            "androidrunconfigurationwidget.h",
            "androidrunconfigurationwidget.ui",
            "androidruncontrol.cpp",
            "androidruncontrol.h",
            "androidrunnable.cpp",
            "androidrunnable.h",
            "androidrunner.cpp",
            "androidrunner.h",
            "androidsdkmanager.cpp",
            "androidsdkmanager.h",
            "androidsdkmanagerwidget.cpp",
            "androidsdkmanagerwidget.h",
            "androidsdkmanagerwidget.ui",
            "androidsdkmodel.cpp",
            "androidsdkmodel.h",
            "androidsdkpackage.cpp",
            "androidsdkpackage.h",
            "androidsettingspage.cpp",
            "androidsettingspage.h",
            "androidsettingswidget.cpp",
            "androidsettingswidget.h",
            "androidsettingswidget.ui",
            "androidsignaloperation.cpp",
            "androidsignaloperation.h",
            "androidtoolchain.cpp",
            "androidtoolchain.h",
            "androidtoolmanager.cpp",
            "androidtoolmanager.h",
            "avddialog.cpp",
            "avddialog.h",
            "certificatesmodel.cpp",
            "certificatesmodel.h",
            "javaeditor.cpp",
            "javaeditor.h",
            "javaindenter.cpp",
            "javaindenter.h",
            "javaparser.cpp",
            "javaparser.h",
        ]
    }
}
