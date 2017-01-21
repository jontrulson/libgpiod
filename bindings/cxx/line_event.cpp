/*
 * C++ bindings for libgpiod.
 *
 * Copyright (C) 2017 Bartosz Golaszewski <bartekgola@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 */

#include "line_event.hpp"

namespace gpiod {

line_event::line_event(void) throw()
	: _M_sec(0),
	  _M_nsec(0),
	  _M_rising_edge(false)
{

}

line_event::line_event(unsigned int sec, unsigned int nsec,
		       bool rising_edge) throw()
	: _M_sec(sec),
	  _M_nsec(nsec),
	  _M_rising_edge(rising_edge)
{

}

unsigned int line_event::sec(void) const throw()
{
	return this->_M_sec;
}

unsigned int line_event::nsec(void) const throw()
{
	return this->_M_nsec;
}

bool line_event::rising_edge(void) const throw()
{
	return this->_M_rising_edge;
}

} /* namespace gpiod */
