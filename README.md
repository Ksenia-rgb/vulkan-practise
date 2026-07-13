# Vulkan summer practise project

Vulkan и OpenGL - кроссплатформенные графические API

## Установка и подключение

*Vulkan SDK*:
- установщик
- подключение в проект Visual Studio
	- C/C++ -> Общие -> Дополнительные каталоги включаемых файлов -> vulkanSDK/.../Include
	- Linker -> Общие -> Дополнительные каталоги библиотек -> vulkanSDK/.../Lib
	- Linker -> Ввод -> Дополнительные зависимости -> vulkanSDK/.../Lib/vulkan-1.lib

*OpenGL:*
- встроенная библиотека
- подключение в проект Visual Studio
	- Linker -> Ввод -> Дополнительные зависимости -> opengl32.lib

*GLFW (Graphic Library for Windows)*:
- архив glfw
- подключение в проект Visual Studio
	- C/C++ -> Общие -> Дополнительные каталоги включаемых файлов -> glfw/.../include
	- Linker -> Общие -> Дополнительные каталоги библиотек -> glfw/.../lib-vc2022
	- Linker -> Ввод -> Дополнительные зависимости -> glfw3.lib

*GLEW (OpenGL Extensions Wrangler Library):*
- архив glew
- подключение в проект Visual Studio
	- C/C++ -> Общие -> Дополнительные каталоги включаемых файлов -> glew/.../include
	- Linker -> Общие -> Дополнительные каталоги библиотек -> glew/.../lib/Release/x64
	- Linker -> Ввод -> Дополнительные зависимости -> glew32.lib
	- В Path добавлен путь glew/.../bin/Realese/x64

## Компиляция шейдеров
**SPIR-V (Standard Portable Intermediate Representation - Vulkan)** - представление байткода - промежуточный результат для параллельных вычислений и графики, разработан для использования в Vulkan и OpenGL (Khronors APIs).

- `.vert` - "расширение" для vertex шейдера
- `.frag` - "расширение" для fragment шейдера

Преобразование в SPIR-V на Windows:
```
C:/.../VulkanSDK/x.x.x.x/Bin/glslc.exe shaders/shader.vert -o vert.spv
C:/.../VulkanSDK/x.x.x.x/Bin/glslc.exe shaders/shader.frag -o frag.spv
```
Чтение исходных GLSL (`shader.vert`, `shader.frag`) файлов и создание (-o: output) файлов с SPIR-V байткодом (`vert.spv`, `frag.spv`) в папке shaders.
