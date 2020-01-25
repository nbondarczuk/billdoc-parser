CC = g++
OPTIONS = -g
TARGETPARSER = billdocparser
TARGETTXTGEN = billdoctxtgen
INCLUDE = -I./include/rapidxml \
	-I./include \
	-I./include/xml_item \
	-I./include/xml_document \
	-I./include/utl \
	-I./include/txt_document \
	-I./include/txt_invoice

$(TARGETTXTGEN):
	$(CC) $(INCLUDE) $(OPTIONS) -o $(TARGETTXTGEN) $(TARGETTXTGEN).cpp

$(TARGETPARSER):
	$(CC) $(INCLUDE) $(OPTIONS) -o $(TARGETPARSER) $(TARGETPARSER).cpp

all: $(TARGETPARSER) $(TARGETTXTGEN)

clang-format:
	# LLVM, Google, Chromium, Mozilla, WebKit
	clang-format -assume-filename=config/.clang-format-config\
	-style="{BasedOnStyle: Google, IndentWidth: 2}" -i \
	*.cpp ./include/*.hpp ./include/*/*.hpp

run-test: $(TARGETTXTGEN)
	billdoctxtgen test/2877963/*.xml

clean:
	rm -f $(TARGETPARSER) $(TARGETTXTGEN) *~ ./include/*~ ./include/*/*~ core.*

tar:
	tar -cvf $(HOME)/billdoc.tar .
	gzip $(HOME)/billdoc.tar
