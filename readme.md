
## 🌻vscode terminal 設置環境

```json
    {"terminal.integrated.shellArgs.windows": [
        "-noe",
        "-c",
        "&{Import-Module ""C:\\'Program Files (x86)'\\'Microsoft Visual Studio'\\2019\\Community\\Common7\\Tools\\Microsoft.VisualStudio.DevShell.dll""; Enter-VsDevShell c53db29e}"
    ]}
```

## 🎐編譯debug exe

```sh
    cl /Zi /EHsc -DDLL_IMPORT -I. main.cpp libmecab.lib
    g++ -g -DDLL_IMPORT -I. main.cpp -o main.exe libmecab.lib
```