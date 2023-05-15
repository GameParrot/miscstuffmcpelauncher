#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/mman.h>
#include <string>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void (*mcpelauncher_preinithook)(const char*sym, void*val, void **orig);
const char* (*_ZNK4Json5Value9asCStringEv)(void *t);
void (*mcpelauncher_log)(int level, const char* tag, const char* text);

void*_ZNK11AppPlatform16isNetworkAllowedEv;
void*__ZNK11AppPlatform16isNetworkAllowedEv;
std::string zeqaNa = "";
std::string zeqaEu = "";
std::string zeqaAs = "";
std::string zeqaAu = "";


const char* getHostIp(const char *host) {
    hostent * record = gethostbyname(host);
	if(record == NULL)
	{
        return "NXDOMAIN";
	}
	in_addr * address = (in_addr * )record->h_addr;
	return inet_ntoa(* address);
}

extern "C" void __attribute__ ((visibility ("default"))) mod_preinit() {
    auto h = dlopen("libmcpelauncher_mod.so", 0);
    zeqaNa = getHostIp("na.zeqa.net");
    zeqaEu = getHostIp("eu.zeqa.net");
    zeqaAs = getHostIp("as.zeqa.net");
    zeqaAu = getHostIp("au.zeqa.net");
    mcpelauncher_preinithook = (decltype(mcpelauncher_preinithook)) dlsym(h, "mcpelauncher_preinithook");
    mcpelauncher_log = (decltype(mcpelauncher_log)) dlsym(h, "mcpelauncher_log");

        mcpelauncher_preinithook("_ZNK4Json5Value9asCStringEv", (void*)+[](void *t) -> const char* {
        const char* ttt = _ZNK4Json5Value9asCStringEv(t);
        if (strstr(ttt, "hivebedrock.network:19132")) { // if (strstr(ttt, "localhost:29132")) {
            mcpelauncher_log(0, "ServerConnection", "The Hive");
        } else if (strstr(ttt, "cubecraft.net:19132")) {
            mcpelauncher_log(0, "ServerConnection", "Cubecraft Games");
        } else if (strstr(ttt, "play.inpvp.net:19132")) {
            mcpelauncher_log(0, "ServerConnection", "Mineville");
        } else if (strstr(ttt, "mco.lbsg.net:19132")) {
            mcpelauncher_log(0, "ServerConnection", "Lifeboat Network");
        } else if (strstr(ttt, "mco.mineplex.com:19132")) {
            mcpelauncher_log(0, "ServerConnection", "Mineplex");
        } else if (strstr(ttt, "play.galaxite.net:19132")) {
            mcpelauncher_log(0, "ServerConnection", "Galaxite");
        } else if (strstr(ttt, "play.pixelparadise.gg:19132")) {
            mcpelauncher_log(0, "ServerConnection", "Pixel Paradise");
        } else if (strstr(ttt, "zeqa.net:19132")) {
            mcpelauncher_log(0, "ServerConnection", "Zeqa");
        } else if (strstr(ttt, "zeqa.net:1000")) {
            mcpelauncher_log(0, "ServerConnection", "Zeqa");
        } else if (strstr(ttt, (zeqaNa + ":1000").c_str())) {
            mcpelauncher_log(0, "ServerConnection", "Zeqa");
        } else if (strstr(ttt, (zeqaEu + ":1000").c_str())) {
            mcpelauncher_log(0, "ServerConnection", "Zeqa");
        } else if (strstr(ttt, (zeqaAs + ":1000").c_str())) {
            mcpelauncher_log(0, "ServerConnection", "Zeqa");
        } else if (strstr(ttt, (zeqaAu + ":1000").c_str())) {
            mcpelauncher_log(0, "ServerConnection", "Zeqa");
        } else if (strstr(ttt, "play.nethergames.org:19132")) {
            mcpelauncher_log(0, "ServerConnection", "NetherGames");
        }
        
        return ttt;
    }, (void**)&_ZNK4Json5Value9asCStringEv);

    __ZNK11AppPlatform16isNetworkAllowedEv = (void*)+[](void*** t) -> bool {
        auto mc = dlopen("libminecraftpe.so", 0);
        
        auto appPlat = (void**)dlsym(mc, "_ZTV11AppPlatform");
        auto raw = &appPlat[2];
        auto othervt = *t;
        auto _ZN11AppPlatform19setKeepScreenOnFlagEb = (void**)dlsym(mc, "_ZN11AppPlatform19setKeepScreenOnFlagEb");

        
        for(int i = 0; raw[i] && raw[i] != (void*)0xffffffffffffffe8; i++) {
            if(raw[i] == _ZN11AppPlatform19setKeepScreenOnFlagEb) {
                othervt[i] = (void*) +[](void*t, bool on) {
                    mcpelauncher_log(0, "MainActivity", (on ? "setKeepScreenOnFlag: 1" : "setKeepScreenOnFlag: 0"));
                };
            }
            if(othervt[i] == __ZNK11AppPlatform16isNetworkAllowedEv) {
                othervt[i] = _ZNK11AppPlatform16isNetworkAllowedEv;
            }
        }
        
        dlclose(mc);
        return true;
    };
    mcpelauncher_preinithook("_ZNK11AppPlatform16isNetworkAllowedEv", __ZNK11AppPlatform16isNetworkAllowedEv, &_ZNK11AppPlatform16isNetworkAllowedEv);
    dlclose(h);
}

extern "C" __attribute__ ((visibility ("default"))) void mod_init() {
}
