#include "pch.h"

TEST(addInt, Equals) {
    JSON json;
    json.addValue("1", 2);

    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(addBool, Equals) {
    JSON json;
    json.addValue("1", true);

    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(addString, Equals) {
    JSON json;
    json.addValue("1", "213123");

    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(addJSON, Equals) {
    JSON json;
    JSON child = JSON({ 1, 2 });
    json.addValue("1", child);

    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(addNull, Equals) {
    JSON json;
    json.addValue("1", nullptr);
    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(addArray, Equals) {
    JSON json = JSON({ 1, 2 });
    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(addKeyValueToArray, Equals) {
    std::string expected = "Failed to add KeyValue to Array";
    JSON json = JSON({ 1, 2 });
    try {
        json.addValue("1", "1");
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(addArrayValueToArray, Equals) {
    std::string expected = "Failed to add value to KeyValue";
    JSON json = JSON();
    try {
        json.addValue("1");
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(editInt, NotEquals) {
    std::string key = "1";
    JSON json1;
    json1.addValue(key, 2);
    JSON json2 = json1;
    json2.editValue(key, 102);

    EXPECT_NE(json1, json2);
}

TEST(editBool, NotEquals) {
    std::string key = "1";
    JSON json1;
    json1.addValue(key, true);
    JSON json2 = json1;
    json2.editValue(key, false);

    EXPECT_NE(json1, json2);
}

TEST(editString, NotEquals) {
    std::string key = "1";
    std::string value = "test";
    std::string newValue = "t";
    JSON json1;
    json1.addValue(key, value);
    JSON json2 = json1;
    json2.editValue(key, newValue);

    EXPECT_NE(json1, json2);
}

TEST(editToAnotherTypeKeyValue, NotEquals) {
    std::string key = "1";
    std::string value = "test";
    int newValue = 1;
    JSON json1;
    json1.addValue(key, value);
    JSON json2 = json1;
    json2.editValue(key, newValue);

    EXPECT_NE(json1, json2);
}

TEST(editJSON, NotEquals) {
    std::string key = "1";
    JSON json1;
    json1.addValue(key, JSON({ 1, 2 }));
    JSON json2 = json1;
    json2.editValue(key, JSON({ 2 }));

    EXPECT_NE(json1, json2);
}

TEST(editArray, NotEquals) {
    JSON json1 = JSON({ 1, 2 });
    JSON json2 = json1;
    json2.editValue(0, 1.53);

    EXPECT_NE(json1, json2);
}

TEST(editKeyValueToArray, Equals) {
    std::string expected = "Failed to edit KeyValue in Array";
    JSON json = JSON({ 1, 2 });
    try {
        json.editValue("123", "1");
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(editArrayValueToArray, Equals) {
    std::string expected = "Failed to edit value in KeyValue";
    JSON json = JSON();
    try {
        json.editValue(1, "1");
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(editArrayWithInvalidInxed, Equals) {
    std::string expected = "Invalid index";
    JSON json = JSON({ 1, 2 });
    try {
        json.editValue(4, "1");
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(editNonExistingValue, Equals) {
    std::string expected = "No value for key";
    JSON json = JSON();
    try {
        json.editValue("1", "1");
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(removeWithKey, Equals) {
    std::string key = "1";
    JSON json = { {key, 2} };
    json.removeValue(key);

    bool expected = true;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(removeFromEmptyWithIndex, Equals) {
    std::string expected = "Invalid index";
    JSON json = JSON({ 1 });
    try {
        json.removeValue(1);
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(removeFromEmptyWithKey, Equals) {
    std::string expected = "No value for key";
    JSON json;
    try {
        json.removeValue("1");
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(removeInArrayWithKey, Equals) {
    std::string expected = "Failed to remove KeyValue in Array";
    JSON json = JSON({ 1, 2 });
    try {
        json.removeValue("1");
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(removeInKeyValueWithIndex, Equals) {
    std::string expected = "Failed to remove value in KeyValue";
    JSON json;
    try {
        json.removeValue(1);
    }
    catch (JSONException& ex) {
        std::string actual = ex.what();
        EXPECT_EQ(expected, actual);
    }
}

TEST(removeWithIndex, Equals) {
    JSON json = { 2 };
    json.removeValue(0);

    bool expected = true;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(getInt, Equals) {
    JSON json;
    int value = 1;
    std::string key = "1";
    json.addValue(key, value);

    int expected = value;
    auto actual = json.getValue<int>(key);

    EXPECT_EQ(expected, actual);
}

TEST(getBool, Equals) {
    JSON json;
    bool value = true;
    std::string key = "1";
    json.addValue(key, value);

    bool expected = value;
    auto actual = json.getValue<bool>(key);

    EXPECT_EQ(expected, actual);
}

TEST(getString, Equals) {
    JSON json;
    std::string value = "test";
    std::string key = "1";
    json.addValue(key, value);

    std::string expected = value;
    auto actual = json.getValue<std::string>(key);

    EXPECT_EQ(expected, actual);
}

TEST(getJSON, Equals) {
    JSON json;
    JSON value = JSON({ 1, 2 });;
    std::string key = "1";
    json.addValue(key, value);

    JSON expected = value;
    auto actual = json.getValue<JSON>(key);

    EXPECT_EQ(expected, actual);
}

TEST(getNull, Equals) {
    JSON json;
    void* value = nullptr;
    std::string key = "1";
    json.addValue(key, value);

    void* expected = value;
    auto actual = json.getValue<void*>(key);

    EXPECT_EQ(expected, actual);
}

TEST(getArray, Equals) {
    Array array = { 1, 2 };
    JSON json = JSON(array);

    Array expected = array;
    auto actual = json.asArray();
    EXPECT_EQ(expected, actual);
}

TEST(getNonExists, Equals) {
    JSON json;
    std::string key = "1";
    auto expected = std::nullopt;
    auto actual = json.getValue<int>(key);
    EXPECT_EQ(expected, actual);
}

TEST(isEmpty, Equals) {
    JSON json;
    bool expected = true;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(isNotEmpty, Equals) {
    JSON json = { 1, 2 };
    bool expected = false;
    bool actual = json.isEmpty();
    EXPECT_EQ(expected, actual);
}

TEST(initializerList, Equals) {
    JSON json = { 1, 1.3 };

    bool expected = true;
    bool actual = json.isArray();
    EXPECT_EQ(expected, actual);
}

TEST(isJSON, Equals) {
    Array array = { 212, 22, 22 };
    JSON json = { {"12", 2}, { "2" , array} };

    bool expected = false;
    bool actual = json.isArray();
    EXPECT_EQ(expected, actual);
}

TEST(isJSONAndArray, Equals) {
    JSON childArray = { 212, 22, 22 };
    JSON json = { {"12", 2}, { "2" , childArray} };

    EXPECT_EQ(json.isArray(), false);
    EXPECT_EQ((*json.getValue<JSON>("2")).isArray(), true);
}

TEST(isNotArray, Equals) {
    JSON json;
    bool expected = false;
    bool actual = json.isArray();
    EXPECT_EQ(expected, actual);
}

TEST(copyJSON, Equals) {
    JSON json1 = JSON();
    JSON json2 = json1;

    EXPECT_EQ(json1, json2);
}

TEST(forEachNonEmpty, Equals) {
    JSON json = { 1, 2, std::string("21") };
    std::stringstream ss;

    for (const auto& value : json) {
        ss << value << std::endl;
    }

    auto expected = false;
    auto actual = ss.str().empty();
    EXPECT_EQ(expected, actual);
}

TEST(forEachEmpty, Equals) {
    JSON json = {};
    std::stringstream ss;

    for (const auto& value : json) {
        ss << value << std::endl;
    }

    auto expected = true;
    auto actual = ss.str().empty();
    EXPECT_EQ(expected, actual);
}

TEST(findIteratorSuccess, Equals) {
    JSON json = { 1, 2, std::string("21") };

    auto expected = 2;
    auto actual = *std::find(json.begin(), json.end(), expected);
    EXPECT_EQ(expected, actual);
}

TEST(findIteratorEnd, Equals) {
    JSON json = { 1, 2, std::string("21") };

    auto expected = json.end();
    auto actual = std::find(json.begin(), json.end(), 12);
    EXPECT_EQ(expected, actual);
}