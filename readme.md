
## 🌻vscode terminal 設置MSBuild環境

```json
    {"terminal.integrated.shellArgs.windows": [
        "-noe",
        "-c",
        "&{Import-Module ""C:\\'Program Files (x86)'\\'Microsoft Visual Studio'\\2019\\Community\\Common7\\Tools\\Microsoft.VisualStudio.DevShell.dll""; Enter-VsDevShell c53db29e}"
    ]}
```

## 🎐編譯debug exe

```sh
    cl /Zi /EHsc -DDLL_IMPORT -I. -Fe"mecab/main.exe" main.cpp mecab/libmecab.lib
    g++ -g -DDLL_IMPORT -I. main.cpp mecab/libmecab.lib -o mecab/main.exe
```

## 👆使用
* 需解壓縮mecab.z7
* 終端轉碼顯示日文 chcp 65001