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

clean:
	rm -f $(TARGETPARSER) $(TARGETTXTGEN) *~ ./include/*~ ./include/*/*~ core.*

tar:
	tar -cvf $(HOME)/billdoc.tar .
	gzip $(HOME)/billdoc.tar
