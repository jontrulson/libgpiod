#
# Copyright (C) 2017 Bartosz Golaszewski <bartekgola@gmail.com>
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of version 2.1 of the GNU Lesser General Public License
# as published by the Free Software Foundation.
#

AM_CPPFLAGS = -I$(top_srcdir)/bindings/cxx/ -I$(top_srcdir)/include
AM_CPPFLAGS += -Wall -Wextra -g -L$(top_srcdir)/bindings/cxx/
AM_LDFLAGS = -lgpiodcxx
LDADD = -lgpiodcxx -L$(top_srcdir)/bindings/cxx/
DEPENDENCIES = libgpiodcxx.la

check_PROGRAMS = gpio_error

gpio_error_SOURCES = gpio_error.cpp