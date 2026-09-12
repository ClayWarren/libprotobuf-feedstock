#include "sample.pb.h"
#include <google/protobuf/util/json_util.h>
#include <iostream>
#include <string>
int main() {
    arm64test::Sample value;
    value.set_name("native-arm64");
    value.add_values(-17); value.add_values(9007199254740993LL);
    std::string wire;
    if (!value.SerializeToString(&wire)) return 1;
    arm64test::Sample decoded;
    if (!decoded.ParseFromString(wire) || decoded.name() != value.name() ||
        decoded.values_size() != 2 || decoded.values(0) != -17 || decoded.values(1) != 9007199254740993LL) return 2;
    std::string json;
    if (!google::protobuf::util::MessageToJsonString(value, &json).ok()) return 3;
    arm64test::Sample from_json;
    if (!google::protobuf::util::JsonStringToMessage(json, &from_json).ok() || from_json.SerializeAsString() != wire) return 4;
    std::cout << "Installed protoc generation, binary and JSON roundtrips passed\n";
}
