SRC_DIR=./core/
DST_DIR=./core/


server:
	protoc -I=$(SRC_DIR) --cpp_out=$(DST_DIR) $(SRC_DIR)/drone.proto

client:
	protoc -I=$(SRC_DIR) --go_out=$(DST_DIR) $(SRC_DIR)/drone.proto
