#ifndef TEA_OBJECT_H
#define TEA_OBJECT_H

#include <stdio.h>

#include "tea_common.h"
#include "vm/tea_chunk.h"
#include "util/tea_table.h"
#include "vm/tea_value.h"
#include "util/tea_array.h"

#define OBJECT_TYPE(value) (AS_OBJECT(value)->type)

#define IS_FILE(value) is_object_type(value, OBJ_FILE)
#define IS_MODULE(value) is_object_type(value, OBJ_MODULE)
#define IS_LIST(value) is_object_type(value, OBJ_LIST)
#define IS_MAP(value) is_object_type(value, OBJ_MAP)
#define IS_BOUND_METHOD(value) is_object_type(value, OBJ_BOUND_METHOD)
#define IS_CLASS(value) is_object_type(value, OBJ_CLASS)
#define IS_CLOSURE(value) is_object_type(value, OBJ_CLOSURE)
#define IS_FUNCTION(value) is_object_type(value, OBJ_FUNCTION)
#define IS_INSTANCE(value) is_object_type(value, OBJ_INSTANCE)
#define IS_NATIVE(value) is_object_type(value, OBJ_NATIVE)
#define IS_STRING(value) is_object_type(value, OBJ_STRING)

#define AS_FILE(value) ((TeaObjectFile*)AS_OBJECT(value))
#define AS_MODULE(value) ((TeaObjectModule*)AS_OBJECT(value))
#define AS_LIST(value) ((TeaObjectList*)AS_OBJECT(value))
#define AS_MAP(value) ((TeaObjectMap*)AS_OBJECT(value))
#define AS_BOUND_METHOD(value) ((TeaObjectBoundMethod*)AS_OBJECT(value))
#define AS_CLASS(value) ((TeaObjectClass*)AS_OBJECT(value))
#define AS_CLOSURE(value) ((TeaObjectClosure*)AS_OBJECT(value))
#define AS_FUNCTION(value) ((TeaObjectFunction*)AS_OBJECT(value))
#define AS_INSTANCE(value) ((TeaObjectInstance*)AS_OBJECT(value))
#define AS_NATIVE(value) \
    (((TeaObjectNative*)AS_OBJECT(value))->function)
#define AS_STRING(value) ((TeaObjectString*)AS_OBJECT(value))
#define AS_CSTRING(value) (((TeaObjectString*)AS_OBJECT(value))->chars)

typedef enum
{
    OBJ_FILE,
    OBJ_MODULE,
    OBJ_LIST,
    OBJ_MAP,
    OBJ_BOUND_METHOD,
    OBJ_CLASS,
    OBJ_CLOSURE,
    OBJ_FUNCTION,
    OBJ_INSTANCE,
    OBJ_NATIVE,
    OBJ_STRING,
    OBJ_UPVALUE
} TeaObjectType;

struct TeaObject
{
    TeaObjectType type;
    bool is_marked;
    struct TeaObject* next;
};

struct TeaObjectFile
{
    TeaObject obj;
    FILE* file;
    char* path;
    char* type;
};

typedef struct
{
    TeaObject obj;
    TeaObjectString* name;
    TeaObjectString* path;
    TeaTable values;
} TeaObjectModule;

typedef struct
{
    TeaObject obj;
    int arity;
    int upvalue_count;
    TeaChunk chunk;
    TeaObjectString* name;
    TeaObjectModule* module;
} TeaObjectFunction;

typedef TeaValue (*TeaNativeFunction)(int arg_count, TeaValue* args);

typedef struct
{
    TeaObject obj;
    TeaNativeFunction function;
} TeaObjectNative;

struct TeaObjectString
{
    TeaObject obj;
    int length;
    char* chars;
    uint32_t hash;
};

typedef struct
{
    TeaObject obj;
    TeaValueArray items;
} TeaObjectList;

typedef struct
{
    TeaObject obj;
    TeaTable items;
} TeaObjectMap;

typedef struct TeaObjectUpvalue
{
    TeaObject obj;
    TeaValue* location;
    TeaValue closed;
    struct TeaObjectUpvalue* next;
} TeaObjectUpvalue;

typedef struct
{
    TeaObject obj;
    TeaObjectFunction* function;
    TeaObjectUpvalue** upvalues;
    int upvalue_count;
} TeaObjectClosure;

typedef struct TeaObjectClass
{
    TeaObject obj;
    TeaObjectString* name;
    TeaValue initializer;
    TeaTable methods;
} TeaObjectClass;

typedef struct
{
    TeaObject obj;
    TeaObjectClass* klass;
    TeaTable fields;
} TeaObjectInstance;

typedef struct
{
    TeaObject obj;
    TeaValue receiver;
    TeaObjectClosure* method;
} TeaObjectBoundMethod;

TeaObjectFile* tea_new_file();

TeaObjectModule* tea_new_module(TeaObjectString* name);

TeaObjectList* tea_new_list();

TeaObjectMap* tea_new_map();

TeaObjectBoundMethod* tea_new_bound_method(TeaValue receiver, TeaObjectClosure* method);
TeaObjectClass* tea_new_class(TeaObjectString* name);
TeaObjectClosure* tea_new_closure(TeaObjectFunction* function);
TeaObjectFunction* tea_new_function();
TeaObjectInstance* tea_new_instance(TeaObjectClass* klass);
TeaObjectNative* tea_new_native(TeaNativeFunction function);

TeaObjectString* tea_take_string(char* chars, int length);
TeaObjectString* tea_copy_string(const char* chars, int length);

TeaObjectUpvalue* tea_new_upvalue(TeaValue* slot);

char* tea_object_tostring(TeaValue value);

void tea_print_object(TeaValue value);

bool tea_objects_equal(TeaValue a, TeaValue b);

const char* tea_object_type(TeaValue a);

static inline bool is_object_type(TeaValue value, TeaObjectType type)
{
    return IS_OBJECT(value) && AS_OBJECT(value)->type == type;
}

#endif