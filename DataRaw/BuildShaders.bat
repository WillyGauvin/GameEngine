@setlocal EnableDelayedExpansion

@echo off

set shadercompiler=..\Libraries\shaderc

@mkdir ..\Data\Shaders
@mkdir ..\Data\Shaders\dx9
@mkdir ..\Data\Shaders\dx11
rem @mkdir ..\Data\Shaders\pssl
rem @mkdir ..\Data\Shaders\metal
rem @mkdir ..\Data\Shaders\nvn
@mkdir ..\Data\Shaders\glsl
rem @mkdir ..\Data\Shaders\essl
@mkdir ..\Data\Shaders\spirv

@call; rem clear the errorlevel

@FOR %%G in ("Shaders\*.vert") DO (
    %shadercompiler% -f %%G -o ../Data/Shaders/dx9/%%~nxG.bin   --type v --platform windows -i ../Libraries/bgfx/src -p vs_3_0
    IF !ERRORLEVEL! NEQ 0 (echo Errors in %%G && goto error) ELSE (echo Built dx9 %%G)
    %shadercompiler% -f %%G -o ../Data/Shaders/dx11/%%~nxG.bin  --type v --platform windows -i ../Libraries/bgfx/src -p vs_4_0
    IF !ERRORLEVEL! NEQ 0 (echo Errors in %%G && goto error) ELSE (echo Built dx11 %%G)
    %shadercompiler% -f %%G -o ../Data/Shaders/glsl/%%~nxG.bin  --type v --platform windows -i ../Libraries/bgfx/src -p 440
    IF !ERRORLEVEL! NEQ 0 (echo Errors in %%G && goto error) ELSE (echo Built glsl %%G)
    %shadercompiler% -f %%G -o ../Data/Shaders/spirv/%%~nxG.bin --type v --platform windows -i ../Libraries/bgfx/src -p spirv
    IF !ERRORLEVEL! NEQ 0 (echo Errors in %%G && goto error) ELSE (echo Built spirv %%G)
)

IF !ERRORLEVEL! NEQ 0 (goto error)

@FOR %%G in ("Shaders\*.frag") DO (
    %shadercompiler% -f %%G -o ../Data/Shaders/dx9/%%~nxG.bin   --type f --platform windows -i ../Libraries/bgfx/src -p ps_3_0
    IF !ERRORLEVEL! NEQ 0 (echo Errors in %%G && goto error) ELSE (echo Built dx9 %%G)
    %shadercompiler% -f %%G -o ../Data/Shaders/dx11/%%~nxG.bin  --type f --platform windows -i ../Libraries/bgfx/src -p ps_4_0
    IF !ERRORLEVEL! NEQ 0 (echo Errors in %%G && goto error) ELSE (echo Built dx11 %%G)
    %shadercompiler% -f %%G -o ../Data/Shaders/glsl/%%~nxG.bin  --type f --platform windows -i ../Libraries/bgfx/src -p 440
    IF !ERRORLEVEL! NEQ 0 (echo Errors in %%G && goto error) ELSE (echo Built glsl %%G)
    %shadercompiler% -f %%G -o ../Data/Shaders/spirv/%%~nxG.bin --type f --platform windows -i ../Libraries/bgfx/src -p spirv
    IF !ERRORLEVEL! NEQ 0 (echo Errors in %%G && goto error) ELSE (echo Built spirv %%G)
)

goto :end

:error
echo.
pause
exit /B 1

:end