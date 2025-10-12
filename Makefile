# ACLIPROJ := src/arduino-simple
ACLIPROJ := src/arduino

ACLIFLAGS := --config-dir $(ACLIPROJ)
BOARDDEV := /dev/ttyACM0
FQBN := arduino:avr:uno

HOSTSRC := src/host
OBJDIR := objects

CC := gcc
CFLAGS := -O2 -std=c99 -Wall -Wextra --pedantic
LDFLAGS := -lm

no-target:
	@echo "No target given!"

compile:
	arduino-cli compile --fqbn $(FQBN) $(ACLIPROJ) $(ACLIFLAGS)


flash:
	arduino-cli upload --port $(BOARDDEV) --fqbn $(FQBN) $(ACLIPROJ) $(ACLIFLAGS)


monitor: 
	arduino-cli monitor --port $(BOARDDEV) $(ACLIFLAGS)


host: objdir
	$(CC) $(HOSTSRC)/*.c -o $(OBJDIR)/host


objdir:
	mkdir -p $(OBJDIR)
	
install-libs:
	arduino-cli core install arduino:avr $(ACLIFLAGS)
