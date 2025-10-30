ROOTDIR := ../
PYTHON := python3

HALLPY_SOURCEDIR := $(ROOTDIR)/hall-py
HALLPY_BUILDDIR := $(ROOTDIR)/hall-py/object

hallpy: hallpy-builddir
	# TODO: We are all miserable here.
	touch $(HALLPY_SOURCEDIR)/hall.pyx
	cd $(HALLPY_SOURCEDIR) && $(PYTHON) $(HALLPY_SOURCEDIR)/hall.py \
	build_ext --inplace --verbose

hallpy-builddir: 
	mkdir -p $(HALLPY_BUILDDIR)
