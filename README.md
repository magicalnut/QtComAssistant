# 串口调试助手 (QtComAssistant)

基于 Qt 6.5.3 的 Windows 串口调试工具，SSCOM 风格界面，终端风格交互。

## 功能

- **文本 / HEX 双模收发** — 支持 ASCII 文本和十六进制两种发送/显示模式
- **转义字符** — 支持 `\r` `\n` `\t` `\\` `\xHH`
- **编码切换** — UTF-8 / GBK / Latin1
- **换行符控制** — CRLF / LF / CR / 无换行
- **时间戳** — 可选毫秒级时间戳前缀
- **校验码计算** — XOR、累加和、CRC16-CCITT、CRC16-Modbus（查表法），实时显示
- **关键字高亮** — KMP 算法实时匹配，黄色背景标记
- **定时发送** — 可配置 10ms~60s 间隔
- **文件发送** — 256 字节分块，UI 不卡顿
- **保存** — 支持保存全部/仅发送/仅接收/原始二进制
- **指令列表** — 增删改管理，一键填充输入行，支持标记 HEX 模式
- **自动回复** — 基于内容匹配的规则引擎，匹配则自动回复
- **发送历史** — ↑↓ 键浏览历史记录
- **串口热插拔检测** — 设备拔出自动关闭并提示

## 界面

- 参数栏（串口号/波特率/数据位/停止位/校验位/流控 + DTR/RTS）
- 终端区（深色背景，NSimSun 等宽字体，10000 行上限，暂停滚动）
- 输入行 + 发送选项
- 状态栏（TX/RX 计数、信号引脚状态）

## 架构

```
main.cpp              — 入口，国际化初始化
mainwindow.h/cpp      — UI 层：布局、信号/槽、终端渲染
serialservice.h/cpp   — 逻辑层：串口读写、自动回复
utils.h/cpp           — 工具层：纯函数（HEX、校验码、编码、转义）
commanddialog.h/cpp   — 指令列表管理对话框
```

UI 层与逻辑层通过 Qt 信号/槽通信，`utils` 为纯函数命名空间，无状态无副作用。

## 构建

**要求：**
- Qt 6.5+ (Core, Widgets, SerialPort, Core5Compat, LinguistTools)
- CMake 3.19+
- MSVC 2022 (Windows)

```powershell
cmake -S . -B build/MSVC2022_Qt6_5_Release
cmake --build build/MSVC2022_Qt6_5_Release --target all
```

## 测试

- 虚拟串口：com0com / VSPD 创建 COM 对
- 硬件自环：USB-TTL 模块 TX-RX 短接

## 部署

编译后在 Qt Creator 中运行部署步骤，或手动执行 `windeployqt`：

```powershell
windeployqt --qmldir . build/MSVC2022_Qt6_5_Release/QtComAssistant.exe
```
