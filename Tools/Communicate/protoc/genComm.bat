
@set protofiles=CSMessage.proto login.proto
@set outpath=..\..\..\Include\Communicate

@set curpath=%cd%
@pushd ..\scripts

@%curpath%\protoc --proto_path=. --cpp_out=%outpath% %protofiles%

@popd

@pushd %outpath%

@echo #include "stdafx.h" > temp
@for /R . %%f IN (*.cc) do @(
	copy temp+%%f %%f.tmp > nul
	@rem 第一个文件move时会说“另一个程序正在使用”，所以加上choice用以延迟执行
	choice /t 1 /d y /n >nul 
	move /Y %%f.tmp %%f
)
@del /F temp 

@popd 