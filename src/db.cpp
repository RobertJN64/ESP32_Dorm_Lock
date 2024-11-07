#include <Preferences.h>
#include <ArduinoJson.h>

StaticJsonDocument<65536> ids_json;
String ids_json_str;
Preferences key_store;

void init() {
  key_store.begin("dorm_key");
  ids_json_str = key_store.getString("dorm_key", "[]");
  Serial.print("Loaded key list: ");
  Serial.println(ids_json_str);
  key_store.end();
}

void write_keys() {
  key_store.begin("dorm_key");
  key_store.getString("dorm_key", ids_json_str);
  Serial.print("Wrote key list: ");
  Serial.println(ids_json_str);
  key_store.end();
}

void add_id(String key) {
  DeserializationError error = deserializeJson(ids_json, ids_json_str);
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  ids_json.add(key);

  serializeJson(ids_json, ids_json_str);
  write_keys();
}

void rm_id(String key) {
  DeserializationError error = deserializeJson(ids_json, ids_json_str);
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  for (int i = 0; i < ids_json.size(); i++) {
    if (ids_json[i] == key) {
      Serial.print("Found key at item ");
      Serial.print(i);
      Serial.print(". Removing...");
      ids_json.remove(i);
    }
  }

  serializeJson(ids_json, ids_json_str);
  write_keys();
}

bool check_id(String key) {
  DeserializationError error = deserializeJson(ids_json, ids_json_str);
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  for (int i = 0; i < ids_json.size(); i++) {
    if (ids_json[i] == key) {
      Serial.print("Found key at item ");
      Serial.print(i);
      return true;
    }
  }
  return false;
}
