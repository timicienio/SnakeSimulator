# SnakeSimulator
Graphic simulator based on SFML interface. Dedicated for IM 1010 Final Project.

## Preperation
In order to use this tool, you need to:
1. [Install Visual Studio.](https://visualstudio.microsoft.com/zh-hant/vs/)
2. [Download SFML2.5.1.](https://www.sfml-dev.org/download/sfml/2.5.1/)
3. (Optional) Unzip SFML to `C:\Program Files\SFML-2.5.1`

## How to use
1. Clone this repo.
2. Put your own `Snake.h` and `Snake.cpp` in `\SnakeSimulator\ConsoleApplication1\ConsoleApplication1` folder.
3. Open `\SnakeSimulator\ConsoleApplication1\SnakeSimulator` with Visual Studio.
4. If the path to the SFML file on your computor is not `C:\Program Files\SFML-2.5.1` (which means you didn't follow 3. in preperation), you'll need to modify the path of `SFML-2.5.1\include` and `SFML-2.5.1\lib`. Follow [this instruction video](https://www.youtube.com/watch?v=YfMQyOw1zik&t=201s) until 1:23. 
5. Right click on `SnakeSimulator` in Solution Explorer, click `Add -> Existing Item`, and add `Snake.h` and `Snake.cpp`, which you just put in the `\SnakeSimulator\ConsoleApplication1\ConsoleApplication1` folder.
6. Click Local Windows Debugger. It should work.

## Notice
- Do not include `<Windows.h>` in any file, it causes conflict with SFML.
- If you don't want to/can not use Visual Studio for this, you can still clone this repo, copy the files and figure it out yourself.
- Report issue [here](https://github.com/desk2000/SnakeSimulator/issues) or contact us.
