import os, sys
from Source.Dependencies.Panshilar import buildutils

CMD_ARG_MAKE_ANDROID_PROJ = '-androidproj' in sys.argv

FOLDER_STRUCTURE = buildutils.getFolderStructure(os.path.dirname(os.path.abspath(__file__)))
MAIN_FILE_C   = FOLDER_STRUCTURE.srcDir + 'zzzz_Unity.c'
MAIN_FILE_CXX = FOLDER_STRUCTURE.srcDir + 'zzzz_Unity.cpp'

if __name__ == '__main__':
    buildutils.setupVsCodeLspStuff()

    if CMD_ARG_MAKE_ANDROID_PROJ:
        buildutils.createAndroidProject(
            appName = 'Vizkaar',
            pkgName = "com.herohiralal.vizkaar",
            projDir = "ProjectFiles/Vizkaar_Android",
            cMain   = 'Source/zzzz_Unity.c',
            cxxMain = 'Source/zzzz_Unity.cpp',
        )

    for plt in buildutils.PLATFORMS_TO_BUILD:
        if CMD_ARG_MAKE_ANDROID_PROJ or plt.tgt != 'windows':
            continue

        cOut   = FOLDER_STRUCTURE.tmpDir + buildutils.getObjectOutputFileName('Vzkr-C',   plt)
        cxxOut = FOLDER_STRUCTURE.tmpDir + buildutils.getObjectOutputFileName('Vzkr-Cxx', plt)

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

        linkCmd = buildutils.getExecBuildCommand(
            plt,
            True,
            [cOut, cxxOut],
            [],
            FOLDER_STRUCTURE.binDir + buildutils.getExecOutputFileName('Vizkaar', plt),
            True
        )

        success = buildutils.runCommand(cBuildCmd,   f'Vizkaar {plt.prettyTgt}-{plt.prettyArch} C Compile') and \
                  buildutils.runCommand(cxxBuildCmd, f'Vizkaar {plt.prettyTgt}-{plt.prettyArch} C++ Compile') and \
                  buildutils.runCommand(linkCmd,     f'Vizkaar {plt.prettyTgt}-{plt.prettyArch} Link')

    buildutils.printSummary()
    if len(buildutils.failedProcesses) > 0:
        exit(1)
