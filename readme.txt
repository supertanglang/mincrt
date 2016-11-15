Release设置:
1.VC++ 目录:$(WindowsSdk_71A_IncludePath);$(VSInstallDir)VC\atlmfc\include;\mincrt\inc;\mincrt
2.链接器->常规->附加库目录:/mincrt/lib/$(PlatformShortName)
3.C/C++->代码生成->:安全检查=禁用安全检查(/GS-) 运行库=多线程DLL(/MD)
4.C/C++->命令行:加入/d2noftol3 
5.链接器->输入->忽略特定默认库:libcmt.lib