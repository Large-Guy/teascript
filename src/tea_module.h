#ifndef TEA_MODULE_H
#define TEA_MODULE_H

#include "tea_vm.h"

typedef TeaValue (*TeaNativeModule)(TeaVM* vm);

typedef struct
{
    char* name;
    int length;
    TeaNativeModule module;
} TeaNativeModules;

#define TEA_MATH_MODULE "math"
TeaValue tea_import_math(TeaVM* vm);

#define TEA_TIME_MODULE "time"
TeaValue tea_import_time(TeaVM* vm);

#define TEA_DATE_MODULE "date"
TeaValue tea_import_date(TeaVM* vm);

#define TEA_JSON_MODULE "json"
//TeaValue tea_import_json(TeaVM* vm);

#define TEA_CSV_MODULE "csv"
//TeaValue tea_import_csv(TeaVM* vm);

#define TEA_LOG_MODULE "log"
//TeaValue tea_import_log(TeaVM* vm);

#define TEA_PALETTE_MODULE "palette"
//TeaValue tea_import_palette(TeaVM* vm);

#define TEA_HTTP_MODULE "http"
//TeaValue tea_import_http(TeaVM* vm);

#define TEA_SOCKET_MODULE "socket"
//TeaValue tea_import_socket(TeaVM* vm);

#define TEA_PROCESS_MODULE "process"
//TeaValue tea_import_process(TeaVM* vm);

#define TEA_HASH_MODULE "hash"
//TeaValue tea_import_hash(TeaVM* vm);

#define TEA_WEB_MODULE "web"
//TeaValue tea_import_web(TeaVM* vm);

#define TEA_OS_MODULE "os"
TeaValue tea_import_os(TeaVM* vm);

#define TEA_PATH_MODULE "path"
//TeaValue tea_import_path(TeaVM* vm);

#define TEA_SYS_MODULE "sys"
TeaValue tea_import_sys(TeaVM* vm);

#define TEA_RANDOM_MODULE "random"
TeaValue tea_import_random(TeaVM* vm);

TeaValue tea_import_native_module(TeaVM* vm, int index);
int tea_find_native_module(char* name, int length);

#endif