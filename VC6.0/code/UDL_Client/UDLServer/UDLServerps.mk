
UDLServerps.dll: dlldata.obj UDLServer_p.obj UDLServer_i.obj
	link /dll /out:UDLServerps.dll /def:UDLServerps.def /entry:DllMain dlldata.obj UDLServer_p.obj UDLServer_i.obj \
		mtxih.lib mtx.lib mtxguid.lib \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
		ole32.lib advapi32.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		/MD \
		$<

clean:
	@del UDLServerps.dll
	@del UDLServerps.lib
	@del UDLServerps.exp
	@del dlldata.obj
	@del UDLServer_p.obj
	@del UDLServer_i.obj
