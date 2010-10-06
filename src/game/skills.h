/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * roboHockey
 * Copyright (C) Albert Cervin 2010 <albert@nat0.se>
 * 
 * roboHockey is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * roboHockey is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SKILLS_H_
#define _SKILLS_H_


class Skills
{
	public:

		Skills(unsigned int _skating, unsigned int _shooting,
		       unsigned int _tackling, unsigned int _faceOff) :
		skating(_skating), shooting(_shooting), tackling(_tackling),
		faceOff(_faceOff) {}

		unsigned int getSkating() { return skating; }
		unsigned int getShooting() { return shooting; }
		unsigned int getTackling() { return tackling; }
		unsigned int getFaceOff() { return faceOff; }
			
	private:
		unsigned int skating, shooting, tackling, faceOff;
		
};

#endif // _SKILLS_H_
