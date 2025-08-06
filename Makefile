CC=gcc
CFLAGS=-std=c2x -pedantic -g -Wall -Werror
SO=so
STATIC=static
OBJ=obj
SRC=src
SOURCES=$(notdir $(wildcard $(SRC)/*.c))
OBJS=$(patsubst %.c,$(OBJ)/%.o,$(SOURCES))

TEST=test
TEST_BIN=bin
TEST_OBJ=test_obj
TEST_SOURCES=$(notdir $(wildcard $(TEST)/*.c))
TEST_OBJS=$(patsubst %.c,$(TEST_OBJ)/%.o,$(TEST_SOURCES))
TEST_BINS=$(patsubst %.c,$(TEST_BIN)/%,$(TEST_SOURCES))

run: $(SO)/libds.so $(STATIC)/libds.a

test: run test_started_msg $(TEST_BINS) test_completed_msg

$(TEST_BIN)/%: $(TEST_OBJ)/%.o
	@$(CC) $(CFLAGS) -o $@ $^ -L./$(SO) -lds
	@touch $(TEST)/$(notdir $(patsubst %.o,%.c,$^))
	@LD_LIBRARY_PATH=$(SO) ./$@

	@echo "-----------------------------------------"
	@echo "Test Completed: File: $(TEST)/$(notdir $(patsubst %.o,%.c,$^))"
	@echo "-----------------------------------------"

$(TEST_OBJ)/%.o: $(TEST)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $^

test_started_msg:
	@echo "#########################################"
	@echo " Test is running"
	@echo "#########################################"

test_completed_msg:
	@echo "#########################################"
	@echo " Test is completed"
	@echo "#########################################"

$(SO)/libds.so: $(OBJS)
	@$(CC) $(CFLAGS) -shared -o $@ $^

	@echo "#########################################"
	@echo " Shared Library Build Completed"
	@echo "#########################################"

$(STATIC)/libds.a: $(OBJS)
	@ar rcs $(STATIC)/libds.a $(OBJS)

	@echo "#########################################"
	@echo " Static Library Build Completed"
	@echo "#########################################"

$(OBJ)/%.o: $(SRC)/%.c
	@$(CC) $(CFLAGS) -fPIC -c -o $@ $^

clean:
	@-rm -rf $(OBJ)
	@-rm -rf $(SO)
	@-rm -rf $(STATIC)
	@-rm -rf $(TEST_OBJ)
	@-rm -rf $(TEST_BIN)
	@mkdir $(OBJ)
	@mkdir $(SO)
	@mkdir $(STATIC)
	@mkdir $(TEST_OBJ)
	@mkdir $(TEST_BIN)

	@echo "#########################################"
	@echo " Cleaning Done"
	@echo "#########################################"
