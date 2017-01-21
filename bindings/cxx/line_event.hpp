/*
 * C++ bindings for libgpiod.
 *
 * Copyright (C) 2017 Bartosz Golaszewski <bartekgola@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 */

#ifndef __GPIOD_CXX_LINE_EVENT_HPP__
#define __GPIOD_CXX_LINE_EVENT_HPP__

namespace gpiod {

class line_event
{
public:

	line_event(void) throw();

	line_event(unsigned int sec, unsigned int nsec,
		   bool rising_edge) throw();

	line_event(const line_event& other) throw();

	unsigned int sec(void) const throw();

	unsigned int nsec(void) const throw();

	bool rising_edge(void) const throw();

private:

	unsigned int _M_sec;
	unsigned int _M_nsec;
	bool _M_rising_edge;
};

} /* namespace gpiod */

#endif /* __GPIOD_CXX_LINE_EVENT_HPP__ */
