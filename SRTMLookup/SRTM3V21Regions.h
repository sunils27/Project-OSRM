/*
    open source routing machine
    Copyright (C) Dennis Luxen, others 2010

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU AFFERO General Public License as published by
the Free Software Foundation; either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
or see http://www.gnu.org/licenses/agpl.txt.
 */


#ifndef SRTM3V21REGIONS_H_
#define SRTM3V21REGIONS_H_

#include <vector>
#include <string>

struct RegionLookup {
	struct Region {
		Region(short _left, short _right, short _up, short _down, const char * _name) :
			left(_left), right(_right), up(_up), down(_down), name(_name) {}
		short left; short right;
		short up; short down;
		std::string name;
	};
	RegionLookup() {
		srtmRegions.push_back(Region( -11,  180,  61,  35, "Eurasia")); //EUR1
		srtmRegions.push_back(Region(  60,  180,  35, -10, "Eurasia")); //EUR2
		srtmRegions.push_back(Region(  95,  106, -10, -14, "Eurasia")); //EUR3
		srtmRegions.push_back(Region(-180, -170,  61,  51, "Eurasia")); //EUR4
		srtmRegions.push_back(Region( -14,  -14,  58,  58, "Eurasia")); //EUR5
		srtmRegions.push_back(Region(-180, -139,   8, -12, "Eurasia")); //EUR6

		srtmRegions.push_back(Region( 112,  160, -10, -45, "Australia")); //AUS1
		srtmRegions.push_back(Region( 160,  180, -10, -25, "Australia")); //AUS2
		srtmRegions.push_back(Region(-180, -100, -10, -28, "Australia")); //AUS3

		srtmRegions.push_back(Region(-180, -154,  30,  15, "Islands")); //ISL1
		srtmRegions.push_back(Region( 165,  180, -25, -54, "Islands")); //ISL2
		srtmRegions.push_back(Region( -38,   84, -35, -56, "Islands")); //ISL3
		srtmRegions.push_back(Region( -30,   12,   5, -22, "Islands")); //ISL4
		srtmRegions.push_back(Region(  64,   65, -19, -19, "Islands")); //ISL5
		srtmRegions.push_back(Region( 155,  165, -54, -56, "Islands")); //ISL6
		srtmRegions.push_back(Region(-180, -175, -30, -45, "Islands")); //ISL7

		srtmRegions.push_back(Region( -25,   60,  35,  -5, "Africa")); //AFR1
		srtmRegions.push_back(Region(  10,   60,  -5, -35, "Africa")); //AFR2
		srtmRegions.push_back(Region( -33,  -24,  40,  35, "Africa")); //AFR3

		srtmRegions.push_back(Region(-170,  -40,  61,  30, "North_America")); //NA1
		srtmRegions.push_back(Region(-120,  -60,  30,  15, "North_America")); //NA2
		srtmRegions.push_back(Region(-109, -109,  11,  11, "North_America")); //NA3

		srtmRegions.push_back(Region( -95,  -38,  15, -56, "South_America")); //SA1
		srtmRegions.push_back(Region( -38,  -30,   0, -20, "South_America")); //SA2
}

	std::string Find(short latFraction, short lonFraction) const {
		BOOST_FOREACH(Region region, srtmRegions) {
			if(region.up <= latFraction && region.down >= latFraction && region.left <= lonFraction && region.right >= lonFraction)
				return region.name;
		}
		return "notFound";
	}

	std::vector<Region> srtmRegions;
};


#endif /* SRTM3V21REGIONS_H_ */
