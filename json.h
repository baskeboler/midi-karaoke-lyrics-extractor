#if !defined(JSON_H)
#define JSON_H
#include <jansson.h>
#include <memory>
#include <string>

using std::shared_ptr, std::make_shared, std::string;

class Json {
protected:
  json_t *internal_json;
  // virtual json_t *get_internal_json() = 0;

public:
  shared_ptr<Json> get(const string &key);
  void set(const string &key, shared_ptr<Json> value);
  virtual ~Json() {
    if (internal_json != nullptr) {
      json_delete(internal_json);
    }
  }
} ;

template <typename T> 
class JsonLiteral: public Json {
  T value;
  

  // JsonLiteral(const T );

};

typedef JsonLiteral<std::string> JsonString;
typedef JsonLiteral<int> JsonInt;
typedef JsonLiteral<double> JsonDouble;
typedef JsonLiteral<bool> JsonBoolean;


class JsonObject : public Json {

protected:
  // json_t *get_internal_json() override { return internal_json; }

public:
  JsonObject() { internal_json = json_object(); }
};

class JsonArray: public Json {
public:
  JsonArray() {
    internal_json = json_array();
  }

  Json& operator[](std::size_t n ) {
    json_t *ret_internal = json_array_get(internal_json , n);

    if (json_is_array(ret_internal)) {
      //
    } else if (json_is_boolean(ret_internal)) {
      //
    } else if (json_is_integer(ret_internal)) {
      //
    } else if (json_is_null(ret_internal)) {
      //
    } else if (json_is_number(ret_internal)) {
      //
    } else if (json_is_object(ret_internal)) {
      //
    } else if (json_is_real(ret_internal)) {
      //
    } else if (json_is_string(ret_internal)) {
      //
    } else if (json_is_array(ret_internal)) {
      //
    } 
  }
};
#endif // JSON_H
