/*
** tea_list.h
** List handling
*/

#ifndef _TEA_LIST_H
#define _TEA_LIST_H

#include "tea_obj.h"

TEA_FUNC GClist* tea_list_new(tea_State* T);
TEA_FUNC void tea_list_add(tea_State* T, GClist* list, TValue* value);

#endif