DIRS = $(wildcard [01]* Demo)

all: $(DIRS)

$(DIRS):
	-@cd $@ && make clean && make

.PHONY: $(DIRS)
