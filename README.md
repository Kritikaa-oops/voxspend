# VoxSpend200

This project is a Qt 6 application built with CMake.

## Requirements

- Qt Creator
- Qt 6.11.1 (or compatible Qt 6 version)
- CMake 3.16 or newer
- A supported compiler for your Qt kit (MinGW 64-bit is used in the existing build folder)

## Open in Qt Creator

1. Start Qt Creator.
2. Choose `File` -> `Open File or Project...`.
3. Select `CMakeLists.txt` from the project root:
   - `c:\Users\Lenovo\Desktop\voxspend200\CMakeLists.txt`
4. When prompted, select a Qt kit that uses Qt 6.11.1 and a compatible compiler (for example, Qt 6.11.1 MinGW 64-bit).
5. Accept the default build directory or choose a folder such as `build`.

## Build the project

1. In Qt Creator, switch to the `Projects` view if needed.
2. Make sure the selected kit is configured correctly.
3. Click the `Build` button or press `Ctrl+Shift+B`.
4. Wait until the build finishes successfully.

## Run the project

1. After a successful build, click the `Run` button or press `Ctrl+R`.
2. The application should launch and display the Qt QML interface.

## Create a distributable Windows executable

1. In Qt Creator, open the `Projects` view and select the `Release` build configuration.   - If `Release` does not appear, open `Build` -> `Select Build Configuration` and choose `Release`.
   - If there is still no `Release` option, open `Tools` -> `Options` -> `Kits` and ensure your selected Qt kit supports CMake configurations, then reconfigure the project.
   - Alternatively, use CMake manually with `-DCMAKE_BUILD_TYPE=Release` when configuring the build directory.2. Build the project again for Release.
3. Locate the Release executable in the build folder, for example:
   - `build\Desktop_Qt_6_11_1_MinGW_64_bit_Release\appVoxSpend200.exe`
4. Open a terminal and run Qt's deployment tool:
   - `C:\Qt\6.11.1\mingw_64\bin\windeployqt.exe --release path\to\appVoxSpend200.exe`
5. This copies the required Qt DLLs, plugins, and QML dependencies into the executable folder.
6. Copy the entire folder to another Windows PC; the app should run without requiring Qt to be installed.

### Notes on deployment

- If your app uses QML, `windeployqt` usually finds the QML imports automatically. If not, add `--qmldir` with your QML source directory.
- For a clean distributable, package the executable folder as a ZIP.
- If you want a true standalone executable, you need a static Qt build, which is not the default for Qt 6 MinGW installations.

## Notes

- The project is configured in `CMakeLists.txt`.
- If Qt Creator finds an older or stale build directory, you can delete the `build` folder or use `Build` -> `Clean All` before rebuilding.
- The header file `BackendManager.h` must be referenced exactly without a stray space. The project has been corrected to use `BackendManager.h` consistently.

## File structure

- `main.cpp` — application entry point
- `CMakeLists.txt` — CMake build configuration
- `*.cpp` / `*.h` — C++ backend files
- `*.qml` — QML UI files

## Troubleshooting

- If the application does not build, verify your Qt kit is using Qt 6 and the correct compiler.
- If CMake configuration fails, remove the existing `build` directory and re-open the project.
- If the file `BackendManager .h` causes problems, rename it to `BackendManager.h` and update any include statements.
