/*
 * C++ bindings for libgpiod.
 *
 * Copyright (C) 2017 Bartosz Golaszewski <bartekgola@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 */

#include "line.hpp"
#include "error.hpp"

#include <stdexcept>

namespace gpiod {

line::line(::gpiod_line *line, gpiod::chip *chip) throw()
	: _M_line(line),
	  _M_chip(chip)
{

}

unsigned int line::offset(void) throw()
{
	return gpiod_line_offset(this->_M_line);
}

const char * line::name(void) throw()
{
	return gpiod_line_name(this->_M_line);
}

const char * line::consumer(void) throw()
{
	return gpiod_line_consumer(this->_M_line);
}

bool line::input(void) throw()
{
	return gpiod_line_direction(this->_M_line) == GPIOD_DIRECTION_INPUT;
}

bool line::output(void) throw()
{
	return gpiod_line_direction(this->_M_line) == GPIOD_DIRECTION_OUTPUT;
}

bool line::active_low(void) throw()
{
	bool state = gpiod_line_active_state(this->_M_line);

	return state == GPIOD_ACTIVE_STATE_LOW;
}

bool line::used_by_kernel(void) throw()
{
	return gpiod_line_is_used_by_kernel(this->_M_line);
}

bool line::open_drain(void) throw()
{
	return gpiod_line_is_open_drain(this->_M_line);
}

bool line::open_source(void) throw()
{
	return gpiod_line_is_open_source(this->_M_line);
}

void line::update(void)
{
	int status;

	status = gpiod_line_update(this->_M_line);
	if (status < 0)
		throw_from_gpiod_errno();
}

bool line::needs_update(void) throw()
{
	return gpiod_line_needs_update(this->_M_line);
}

void line::request(int direction, const std::string& consumer,
		   int default_val, bool active_low, int flags)
{
	::gpiod_line_request_config config;
	int status;

	config.consumer = consumer.c_str();
	config.direction = direction;
	config.active_state = active_low ? GPIOD_ACTIVE_STATE_LOW
					 : GPIOD_ACTIVE_STATE_HIGH;

	if (flags & FLAG_OPEN_DRAIN)
		config.flags = GPIOD_REQUEST_OPEN_DRAIN;
	if (flags & FLAG_OPEN_SOURCE)
		config.flags = GPIOD_REQUEST_OPEN_SOURCE;

	status = gpiod_line_request(this->_M_line, &config, default_val);
	if (status < 0)
		throw_from_gpiod_errno();
}

void line::request_input(const std::string& consumer,
			 bool active_low, int flags)
{
	this->request(GPIOD_DIRECTION_INPUT, consumer, 0, active_low, flags);
}

void line::request_output(const std::string& consumer,
			  int default_val, bool active_low, int flags)
{
	this->request(GPIOD_DIRECTION_OUTPUT, consumer,
		      default_val, active_low, flags);
}

int line::get_value(void)
{
	int val;

	val = gpiod_line_get_value(this->_M_line);
	if (val < 0)
		throw_from_gpiod_errno();

	return val;
}

void line::set_value(int val)
{
	int status;

	status = gpiod_line_set_value(this->_M_line, val);
	if (status < 0)
		throw_from_gpiod_errno();
}

void line::request_event(int event_type, const std::string& consumer,
			 bool active_low, int flags)
{
	::gpiod_line_evreq_config config;
	int status;

	config.consumer = consumer.c_str();
	config.event_type = event_type;
	config.active_state = active_low ? GPIOD_ACTIVE_STATE_LOW
					 : GPIOD_ACTIVE_STATE_HIGH;

	if (flags & FLAG_OPEN_DRAIN)
		config.line_flags = GPIOD_REQUEST_OPEN_DRAIN;
	if (flags & FLAG_OPEN_SOURCE)
		config.line_flags = GPIOD_REQUEST_OPEN_SOURCE;

	status = gpiod_line_event_request(this->_M_line, &config);
	if (status < 0)
		throw_from_gpiod_errno();
}

void line::request_event_rising(const std::string& consumer,
				bool active_low, int flags)
{
	this->request_event(GPIOD_EVENT_RISING_EDGE,
			    consumer, active_low, flags);
}

void line::request_event_falling(const std::string& consumer,
				 bool active_low, int flags)
{
	this->request_event(GPIOD_EVENT_FALLING_EDGE,
			    consumer, active_low, flags);
}

void line::request_event_both(const std::string& consumer,
			      bool active_low, int flags)
{
	this->request_event(GPIOD_EVENT_BOTH_EDGES,
			    consumer, active_low, flags);
}

bool line::event_wait(unsigned int sec, unsigned int nsec)
{
	::timespec ts;
	int status;

	ts.tv_sec = sec;
	ts.tv_nsec = nsec;

	status = gpiod_line_event_wait(this->_M_line, &ts);
	if (status < 0)
		throw_from_gpiod_errno();

	return status > 0;
}

void line::event_read(gpiod::line_event& ev)
{
	::gpiod_line_event event;
	int status;

	status = gpiod_line_event_read(this->_M_line, &event);
	if (status < 0)
		throw_from_gpiod_errno();

	ev = line_event(event.ts.tv_sec, event.ts.tv_nsec,
			event.event_type == GPIOD_EVENT_RISING_EDGE ? true
								    : false);
}

void line::throw_from_gpiod_errno(void)
{
	throw gpiod::error(::gpiod_errno());
}

} /* namespace gpiod */
