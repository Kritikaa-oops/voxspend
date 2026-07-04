# VoxSpend

VoxSpend is an offline-first personal finance tracker built with Qt Quick/QML and a small C++17 backend.

## Project Structure

- `src/models` - C++ data objects.
- `src/controllers` - QObject controllers exposed to QML.
- `src/database` - local JSON persistence.
- `ui/views` - full QML screens.
- `ui/components` - reusable QML widgets.
- `assets/icons` - static app assets.

## Build

Install Qt 6 with the `Core`, `Gui`, `Quick`, and `QuickControls2` modules, then run:

```powershell
cmake -S . -B build
cmake --build build
.\build\VoxSpend.exe
```
