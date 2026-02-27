import os, sys
from Source.Dependencies.Panshilar import buildutils, genprojandroid, genprojxcode
from Source.Dependencies.Muzent import build as BuildMuzent

CMD_ARG_MAKE_ANDROID_PROJ = '-androidproj' in sys.argv
CMD_ARG_MAKE_XCODE_PROJ   = '-xcodeproj'   in sys.argv
CMD_ARG_BUILD_SHADERS     = '-shaders'     in sys.argv

FOLDER_STRUCTURE = buildutils.getFolderStructure(os.path.dirname(os.path.abspath(__file__)))
MAIN_FILE_C    = FOLDER_STRUCTURE.srcDir + 'zzzz_Unity.c'
MAIN_FILE_CXX  = FOLDER_STRUCTURE.srcDir + 'zzzz_Unity.cpp'
MAIN_FILE_OBJC = FOLDER_STRUCTURE.srcDir + 'zzzz_Unity.m'

if __name__ == '__main__':
    buildutils.setupVsCodeLspStuff()

    if CMD_ARG_MAKE_ANDROID_PROJ:
        genprojandroid.run(
            appName = 'Vizkaar',
            pkgName = "com.herohiralal.vizkaar",
            projDir = "ProjectFiles/Vizkaar_Android",
            cMain   = 'Source/zzzz_Unity.c',
            cxxMain = 'Source/zzzz_Unity.cpp',
        )
        exit(0)

    if CMD_ARG_MAKE_XCODE_PROJ:
        genprojxcode.run(
            projName = 'Vizkaar',
            pkgName  = 'com.herohiralal.vizkaar',
            projDir  = 'ProjectFiles/Vizkaar_Xcode',
            cMain    = 'Source/zzzz_Unity.c',
            cxxMain  = 'Source/zzzz_Unity.cpp',
            objcMain = 'Source/zzzz_Unity.m',
        )
        exit(0)

    if CMD_ARG_BUILD_SHADERS:
        BuildMuzent.recompileShaders()
        buildutils.printSummary()
        exit(0 if len(buildutils.failedProcesses) == 0 else 1)

    for plt in buildutils.PLATFORMS_TO_BUILD:
        if plt.tgt != 'windows' and plt.tgt != 'osx':
            continue

        cOut    = FOLDER_STRUCTURE.tmpDir + buildutils.getObjectOutputFileName('Vzkr-C',   plt)
        cxxOut  = FOLDER_STRUCTURE.tmpDir + buildutils.getObjectOutputFileName('Vzkr-Cxx', plt)
        objcOut = FOLDER_STRUCTURE.tmpDir + buildutils.getObjectOutputFileName('Vzkr-ObjC', plt)

        cBuildCmd = buildutils.getCompilationCommand(
            plt,
            True,
            MAIN_FILE_C,
            cOut,
            False,
        )

        cxxBuildCmd = buildutils.getCompilationCommand(
            plt,
            True,
            MAIN_FILE_CXX,
            cxxOut,
            True,
        )

        objcBuildCmd = buildutils.getCompilationCommand(
            plt,
            True,
            MAIN_FILE_OBJC,
            FOLDER_STRUCTURE.tmpDir + buildutils.getObjectOutputFileName('Vzkr-ObjC', plt),
            False,
        )

        linkCmd = buildutils.getExecBuildCommand(
            plt,
            True,
            [cOut, cxxOut] + ([objcOut] if plt.tgt == 'osx' else []),
            [],
            FOLDER_STRUCTURE.binDir + buildutils.getExecOutputFileName('Vizkaar', plt),
            True,
            ['Cocoa', 'Metal', 'QuartzCore', 'Foundation'] if plt.tgt == 'osx' else []
        )

        success = buildutils.runCommand(cBuildCmd,   f'Vizkaar {plt.prettyTgt}-{plt.prettyArch} C Compile') and \
                  buildutils.runCommand(cxxBuildCmd, f'Vizkaar {plt.prettyTgt}-{plt.prettyArch} C++ Compile') and \
                  (plt.tgt != 'osx' or buildutils.runCommand(objcBuildCmd, f'Vizkaar {plt.prettyTgt}-{plt.prettyArch} ObjC Compile')) and \
                  buildutils.runCommand(linkCmd,     f'Vizkaar {plt.prettyTgt}-{plt.prettyArch} Link')

    buildutils.printSummary()
    if len(buildutils.failedProcesses) > 0:
        exit(1)
