@echo off
for %%f in (*PS.hlsl) do "%DXSDK_DIR%\Utilities\bin\x86\fxc.exe" /T ps_2_0 /nologo /E main /Fo obj\%%~nf.cso %%f
for %%f in (*VS.hlsl) do "%DXSDK_DIR%\Utilities\bin\x86\fxc.exe" /T vs_2_0 /nologo /E main /Fo obj\%%~nf.cso %%f

"%DXSDK_DIR%\Utilities\bin\x86\fxc.exe" /T vs_2_0 /nologo /E main /DENVMAP /Fo obj\leedsDefault_ENV_VS.cso leedsDefault_VS_x.hlsl
"%DXSDK_DIR%\Utilities\bin\x86\fxc.exe" /T ps_2_0 /nologo /E main /DPASS_ADD /Fo obj\leedsDefault_ADD_PS.cso leedsDefault_PS_x.hlsl
"%DXSDK_DIR%\Utilities\bin\x86\fxc.exe" /T ps_2_0 /nologo /E main /DPASS_BLEND /Fo obj\leedsDefault_BLEND_PS.cso leedsDefault_PS_x.hlsl
