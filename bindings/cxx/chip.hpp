/*
 * C++ bindings for libgpiod.
 *
 * Copyright (C) 2017 Bartosz Golaszewski <bartekgola@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 */

#ifndef __GPIOD_CXX_CHIP_HPP__
#define __GPIOD_CXX_CHIP_HPP__

#include "gpiodcxx-internal.hpp"

#include "line.hpp"
#include "error.hpp"

#include <string>
#include <vector>

namespace gpiod {

class chip
{
public:

	chip(void);

	chip(const std::string& device);

	~chip(void) throw();

	void open(const std::string& device);

	void close(void) throw();

	const char * name(void) throw();

	const char * label(void) throw();

	unsigned int num_lines(void) throw();

	bool is_open(void) const throw();

	gpiod::line * get_line(unsigned int offset);

	gpiod::line * operator[](unsigned int offset);

private:

	static void throw_from_gpiod_errno(void);

	::gpiod_chip *_M_chip;
	std::vector<gpiod::line *> _M_lines;
};

} /* namespace gpiod */

#endif /* __GPIOD_CXX_CHIP_HPP__ */
