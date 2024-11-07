#ifndef DB_H
#define DB_H

#include <Arduino.h>

void init();
void add_id(String);
void rm_id(String);
bool check_id(String);

#endif
