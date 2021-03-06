#include "pch.h"
#include "JSON.h"
#include "JSONException.h"

using namespace std;

JSON::JSON() {
    root = KeyValue();
};

JSON::JSON(Array array) {   
    root = array;
}

JSON::JSON(std::initializer_list<Value> initializer_list) {
    root = initializer_list;
}

JSON::JSON(initializer_list<std::pair<const std::string, Value>> initializer_map) {
    root = initializer_map;
}


JSON::JSON(const JSON& json) {
    visit([this](Object const& arg) {
        if (holds_alternative<KeyValue>(arg)) {
            auto v_map = get<KeyValue>(arg);
            this->root = v_map;
        }
        else if (holds_alternative<Array>(arg)) {
            auto v_array = get<Array>(arg);
            this->root = v_array;
        }
        else {
            throw JSONException("Invalid argument");
        }
        }, json.root);
}

bool JSON::isEmpty() {
    return visit([](Object const& arg) -> bool {
        if (holds_alternative<KeyValue>(arg)) {
            auto v_map = get<KeyValue>(arg);
            return v_map.empty();
        }
        else if (holds_alternative<Array>(arg)) {
            auto v_array = get<Array>(arg);
            return v_array.empty();
        }
        else {
            throw JSONException("Invalid argument");
        }
        }, root);
}

bool JSON::isArray() {
    return holds_alternative<Array>(root);
}

void JSON::addValue(const string& key, Value value) {
    if (holds_alternative<KeyValue>(root)) {
        auto v_map = get<KeyValue>(root);
        v_map[key] = value;
        root = v_map;
    }
    else {
        throw JSONException("Failed to add KeyValue to Array");
    }
}

void JSON::addValue(const Value& value) {
    if (holds_alternative<Array>(root)) {
        auto v_array = get<Array>(root);
        v_array.push_back(value);
        root = v_array;
    }
    else {
        throw JSONException("Failed to add value to KeyValue");
    }
}

void JSON::editValue(const std::string& forKey, const Value& newValue) {
    if (holds_alternative<KeyValue>(root)) {
        auto v_map = get<KeyValue>(root);
        if (v_map.find(forKey) != v_map.end()) {
            v_map[forKey] = newValue;
            root = v_map;
        }
        else {
            throw JSONException("No value for key");
        }
    }
    else {
        throw JSONException("Failed to edit KeyValue in Array");
    }
}

void JSON::editValue(int atIndex, const Value& newValue) {
    if (holds_alternative<Array>(root)) {
        auto v_array = get<Array>(root);
        if (atIndex < 0 || atIndex >= v_array.size())
            throw JSONException("Invalid index");
        v_array[atIndex] = newValue;
        root = v_array;
    }
    else {
        throw JSONException("Failed to edit value in KeyValue");
    }
}

void JSON::removeValue(const std::string& forKey) {
    if (holds_alternative<KeyValue>(root)) {
        auto v_map = get<KeyValue>(root);
        if (v_map.find(forKey) != v_map.end()) {
            auto it = v_map.find(forKey);
            v_map.erase(it);
            root = v_map;
        }
        else {
            throw JSONException("No value for key");
        }
    }
    else {
        throw JSONException("Failed to remove KeyValue in Array");
    }
}

void JSON::removeValue(int atIndex) {
    if (holds_alternative<Array>(root)) {
        auto v_array = get<Array>(root);
        if (atIndex < 0 || atIndex >= v_array.size()) throw JSONException("Invalid index");
        v_array.erase(v_array.begin() + atIndex);
        root = v_array;
    }
    else {
        throw JSONException("Failed to remove value in KeyValue");
    }
}

string JSON::toString() const {
    return visit([this](Object&& arg) -> string {
        if (holds_alternative<KeyValue>(arg)) {
            auto v_map = get<KeyValue>(arg);
            return "{" + this->dictToString(v_map) + "}";
        }
        else if (holds_alternative<Array>(arg)) {
            auto v_array = get<Array>(arg);
            return "[" + this->arrayToString(v_array) + "]";
        }
        }, root);
}

string JSON::dictToString(const KeyValue& map) const {
    string rez = "";
    int i = map.size();
    for (const auto& [key, value] : map) {
        rez += " \"" + key + "\" : " + valueToString(value);
        rez += i != 1 ? ", " : " ";
        --i;
    }
    return rez;
}

string JSON::arrayToString(const Array& array) const {
    string rez = "";
    int i = array.size();
    for (const auto& value : array) {
        rez += valueToString(value);
        rez += i != 1 ? ", " : "";
        --i;
    }
    return rez;
}

string JSON::valueToString(const Value& value) {
    return visit([](Value&& arg) -> string {
        if (holds_alternative<void*>(arg)) {
            return "null";
        }
        else if (holds_alternative<bool>(arg)) {
            auto v_bool = get<bool>(arg);
            return v_bool ? "true" : "false";
        }
        else if (holds_alternative<int>(arg)) {
            auto v_int = get<int>(arg);
            return to_string(v_int);
        }
        else if (holds_alternative<double>(arg)) {
            auto v_double = get<double>(arg);
            string str = to_string(v_double);
            str.erase(str.find_last_not_of('0') + 1, std::string::npos);
            return str;
        }
        else if (holds_alternative<string>(arg)) {
            auto v_string = get<string>(arg);
            return "\"" + v_string + "\"";
        }
        else if (holds_alternative<JSON>(arg)) {
            auto v_json = get<JSON>(arg);
            return v_json.toString();
        }
        }, value);
}

std::ostream& operator<<(std::ostream& out, const JSON& j) {
    out << j.toString();
    return out;
}

std::ostream& operator<<(std::ostream& out, const Value& v) {
    out << JSON::valueToString(v);
    return out;
}

bool operator==(const JSON& l, const JSON& r) {
    if (l.root.index() != r.root.index()) return false;
    return visit([r](JSON::Object&& arg) -> bool {
        if (holds_alternative<KeyValue>(arg)) {
            auto v_map_l = get<KeyValue>(arg);
            auto v_map_r = get<KeyValue>(r.root);
            return v_map_l == v_map_r;
        }
        else if (holds_alternative<Array>(arg)) {
            auto v_array_l = get<Array>(arg);
            auto v_array_r = get<Array>(r.root);
            return v_array_l == v_array_r;
        }
        }, l.root);
}

bool operator!=(const JSON& l, const JSON& r) {
    return !(l == r);
}

bool operator==(const Value& l, const Value& r) {
    if (l.index() != r.index()) return false;
    return visit([r](Value&& arg) -> bool {
        if (holds_alternative<void*>(arg)) {
            return true;
        }
        else if (holds_alternative<bool>(arg)) {
            auto v_bool_l = get<bool>(arg);
            auto v_bool_r = get<bool>(r);
            return v_bool_l == v_bool_r;
        }
        else if (holds_alternative<int>(arg)) {
            auto v_int_l = get<int>(arg);
            auto v_int_r = get<int>(r);
            return v_int_l == v_int_r;
        }
        else if (holds_alternative<double>(arg)) {
            auto v_double_l = get<double>(arg);
            auto v_double_r = get<double>(r);
            return v_double_l == v_double_r;
        }
        else if (holds_alternative<string>(arg)) {
            auto v_string_l = get<string>(arg);
            auto v_string_r = get<string>(r);
            return v_string_l == v_string_r;
        }
        else if (holds_alternative<JSON>(arg)) {
            auto v_json_l = get<JSON>(arg);
            auto v_json_r = get<JSON>(r);
            return v_json_l == v_json_r;
        }
        }, l);
}

bool operator!=(const Value& l, const Value& r) {
    return !(l == r);
}

std::optional<Array> JSON::asArray() {
    if (std::holds_alternative<Array>(root)) {
        return std::get<Array>(root);
    }
    else {
        return std::nullopt;
    }
}

JSON::JSONIterator JSON::begin() {
    if (std::holds_alternative<Array>(root)) {
        return JSONIterator(std::get<Array>(root).begin());
    }
    else {
        return JSONIterator(std::get<KeyValue>(root).begin());
    }
}

JSON::JSONIterator JSON::end() {
    if (std::holds_alternative<Array>(root)) {
        return JSONIterator(std::get<Array>(root).end());
    }
    else {
        return JSONIterator(std::get<KeyValue>(root).end());
    }
}