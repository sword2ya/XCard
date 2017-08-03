
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
	@rem ��һ���ļ�moveʱ��˵����һ����������ʹ�á������Լ���choice�����ӳ�ִ��
	choice /t 1 /d y /n >nul 
	move /Y %%f.tmp %%f
)
@del /F temp 

@popd 