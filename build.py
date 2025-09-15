import os
from Source.Dependencies.Panshilar import buildutils

FOLDER_STRUCTURE = buildutils.getFolderStructure(os.path.dirname(os.path.abspath(__file__)))
MAIN_FILE = FOLDER_STRUCTURE.srcDir + 'zzzz_Unity.c'

if __name__ == '__main__':
    buildutils.setupVsCodeLspStuff()

    for plt in buildutils.PLATFORMS_TO_BUILD:
        if plt.tgt != 'windows':
            continue

        buildCmd = buildutils.getExecBuildCommand(
            plt,
            True,
            [MAIN_FILE],
            ['iphlpapi.lib', 'Ws2_32.lib', 'Shell32.lib', 'Gdi32.lib', 'User32.lib'] if plt.tgt == 'windows' else ['pthread'] if plt.tgt == 'linux' else [],
            FOLDER_STRUCTURE.binDir + buildutils.getExecOutputFileName('Vizkaar', plt),
            False
        )

        buildutils.runCommand(buildCmd, f'{plt.prettyTgt}-{plt.prettyArch} Vizkaar Build')

    buildutils.printSummary()
    if len(buildutils.failedProcesses) > 0:
        exit(1)
