#include <stdio.h>

#include <pspkernel.h>
#include <systemctrl_se.h>
#include <systemctrl.h>
#include <pspsysmem_kernel.h>

#define MAKE_CALL(a, f)	_sw(0x08000000 | (((u32)(f) >> 2) & 0x03FFFFFF), a);

/*----------------------------------------------------------------------------*/

PSP_MODULE_INFO("BatteryPatch", PSP_MODULE_KERNEL, 0, 2 );

int module_start( SceSize arglen, void *argp );
int module_stop( void );
int main_thread( SceSize arglen, void *argp );

void ClearCaches(void)
{
	sceKernelDcacheWritebackAll();
	sceKernelIcacheClearAll();
}

int WriteBatteryInfo(int volt){
	int ret = 0;
	if(volt >= 4150){//
		ret = 100;
	} else if(volt >= 4100){
		ret = 96;
	} else if(volt >= 4050){
		ret = 93;
	} else if(volt >= 4000){//
		ret = 90;
	} else if(volt >= 3950){
		ret = 81;
	} else if(volt >= 3900){
		ret = 73;
	} else if(volt >= 3850){
		ret = 66;
	} else if(volt >= 3800){//
		ret = 60;
	} else if(volt >= 3750){
		ret = 43;
	} else if(volt >= 3700){//
		ret = 30;
	} else if(volt >= 3650){
		ret = 20;
	} else if(volt >= 3600){//
		ret = 12;
	} else if(volt >= 3550){
		ret = 7;
	} else if(volt >= 3500){//
		ret = 4;
	} else if(volt >= 3450){
		ret = 3;
	} else if(volt >= 3400){//
		ret = 2;
	} else if(volt >= 3350){
		ret = 1;
	} else if(volt >= 3300){//
	}
	return ret;
}

int main_thread( SceSize arglen, void *argp ){
	
	while( sceKernelFindModuleByName("sceKernelLibrary") == NULL ){
		sceKernelDelayThread(1000);
	}
	if(sceKernelGetModel() == 4){
		SceModule2 *mod = sceKernelFindModuleByName("scePower_Service");
		u32 text_addr = mod->text_addr;
		u32 text_end = mod->text_addr + mod->text_size;
		for(; text_addr < text_end; text_addr += 4){
			if(_lw(text_addr) == 0x1880001C){
				MAKE_CALL(text_addr, WriteBatteryInfo);
				ClearCaches();
			}
		}
	}
	return sceKernelExitDeleteThread( 0 );
}

/*----------------------------------------------------------------------------*/

int module_start( SceSize arglen, void *argp ){
	SceUID thid = sceKernelCreateThread( "main", main_thread, 20, 0x1000, 0, NULL);
	if(thid)sceKernelStartThread(thid, arglen, argp);
	return 0;
}

int module_stop( void ){
	return 0;
}
