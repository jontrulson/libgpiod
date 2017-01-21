/*
 * C++ bindings for libgpiod.
 *
 * Copyright (C) 2017 Bartosz Golaszewski <bartekgola@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 */

#include "chip.hpp"

#include <stdexcept>

namespace gpiod {

chip::chip(void)
	: _M_chip(0),
	  _M_lines(0)
{

}

chip::chip(const std::string& device)
	: _M_chip(0),
	  _M_lines(0)
{
	this->open(device);
}

chip::~chip(void) throw()
{
	this->close();
}

void chip::open(const std::string& device)
{
	if (this->_M_chip)
		throw std::logic_error("chip already open");

	this->_M_chip = ::gpiod_chip_open_lookup(device.c_str());
	if (!this->_M_chip)
		throw_from_gpiod_errno();

	this->_M_lines.resize(this->num_lines(), 0);
}

void chip::close(void) throw()
{
	gpiod::line *line;

	for (std::vector<gpiod::line *>::iterator it = this->_M_lines.begin();
	     it != this->_M_lines.end(); it++) {
		line = *it;

		if (line)
			delete line;
	}

	if (this->_M_chip)
		::gpiod_chip_close(this->_M_chip);
}

const char * chip::name(void) throw()
{
	return gpiod_chip_name(this->_M_chip);
}

const char * chip::label(void) throw()
{
	return gpiod_chip_label(this->_M_chip);
}

unsigned int chip::num_lines(void) throw()
{
	return gpiod_chip_num_lines(this->_M_chip);
}

bool chip::is_open(void) const throw()
{
	return this->_M_chip != 0;
}

gpiod::line * chip::get_line(unsigned int offset)
{
	gpiod::line *line;
	::gpiod_line *line_internal;

	line = this->_M_lines[offset];

	if (line) {
		if (line->needs_update())
			line->update();
	} else {
		line_internal = ::gpiod_chip_get_line(this->_M_chip, offset);
		if (!line_internal)
			throw_from_gpiod_errno();

		line = new gpiod::line(line_internal, this);
		this->_M_lines[offset] = line;
	}

	return line;
}

gpiod::line * chip::operator[](unsigned int offset)
{
	return this->get_line(offset);
}

void chip::throw_from_gpiod_errno(void)
{
	throw gpiod::error(::gpiod_errno());
}

} /* namespace gpiod */
