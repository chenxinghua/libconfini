## Process this file with automake to produce Makefile.in

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src

dist_doc_DATA = \
	COPYING \
	AUTHORS \
	ChangeLog \
	INSTALL \
	NEWS \
	README \
	docs/manual.html

man_MANS = docs/man/man3/confini.h.3 \
	docs/man/man3/IniDispatch.3 \
	docs/man/man3/IniFormat.3 \
	docs/man/man3/IniStatistics.3 \
	docs/man/man3/libconfini.3

examplesdir = $(docdir)/examples
examples_DATA = \
	examples/run_example.sh

examplesinifilesdir = $(examplesdir)/ini_files
examplesinifiles_DATA = \
	examples/ini_files/ambiguous.conf \
	examples/ini_files/bad_ini.conf \
	examples/ini_files/example.conf \
	examples/ini_files/hash_table.conf \
	examples/ini_files/typed_ini.conf

examplesotherdir = $(examplesdir)/miscellanea
examplesother_DATA = \
	examples/miscellanea/disambiguate.c \
        examples/miscellanea/dispatch_everything.c \
        examples/miscellanea/glib_hash_table.c \
	examples/miscellanea/print_format.c \
	examples/miscellanea/typed_ini.c

examplestopicsdir = $(examplesdir)/topics
examplestopics_DATA = \
	examples/topics/ini_array_break.c \
	examples/topics/ini_array_collapse.c \
	examples/topics/ini_array_release.c \
	examples/topics/ini_array_shift.c \
	examples/topics/ini_global_set_implicit_value.c \
	examples/topics/ini_string_match_si.c \
	examples/topics/ini_string_parse.c \
	examples/topics/load_ini_file.c \
	examples/topics/load_ini_path.c

# Make doc script executable
install-data-hook:
	chmod +x $(DESTDIR)$(examplesdir)/run_example.sh

# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(docdir)

