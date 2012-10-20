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

#include "fileExtensions.h"

std::string FileExtensions::extension(const boost::filesystem::path& ph)
{
	std::string filename = ph.filename().c_str();
	long n = filename.find('.');
 	if (n != std::string::npos)
		return filename.substr(n);
 	else
 		return std::string();
}

std::string FileExtensions::basename(const boost::filesystem::path& ph)
{
  std::string string_type;
  std::string filename = ph.filename().c_str();
  long n = filename.find('.');
  return filename.substr(0, n);
}

boost::filesystem::path FileExtensions::change_extension( const boost::filesystem::path& ph, const std::string& new_extension )
{
	return ph.parent_path() / (FileExtensions::basename(ph) + new_extension);
}