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

#include "FileDownload.h"

#include <fstream>
#include <iostream>

bool FileDownload::download(std::string & URL, std::string & outFile) {
    try {
        boost::asio::io_service io_service;
        URLSplitter::URLDetails details;
        URLSplitter::Run(URL, details);

        // Get a list of endpoints corresponding to the server name.
        boost::asio::ip::tcp::resolver resolver(io_service);
        boost::asio::ip::tcp::resolver::query query(details.host, details.protocol);
        boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        // Try each endpoint until we successfully establish a connection.
        boost::asio::ip::tcp::socket socket(io_service);
        socket.connect(*endpoint_iterator);

        // Form the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        boost::asio::streambuf request;
        std::ostream request_stream(&request);
//        std::cout << "Requesting: " << details.path << details.file << std::endl;
        request_stream << "GET " << details.path << details.file << " HTTP/1.0\r\n";
        request_stream << "Host: " << details.host << "\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";

        // Send the request.
        boost::asio::write(socket, request);

        // Read the response status line. The response streambuf will automatically
        // grow to accommodate the entire line. The growth may be limited by passing
        // a maximum size to the streambuf constructor.
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        // Check that response is OK.
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
            std::cout << "Invalid response\n";
            return 1;
        }

        if (status_code != 200) {
            std::cout << "Response returned with status code " << status_code << "\n";
            return 1;
        }
        // Read the response headers, which are terminated by a blank line.
        boost::asio::read_until(socket, response, "\r\n\r\n");

//        std::cout << "done" << std::endl;

        // Process the response headers.
        std::string header;
        while (std::getline(response_stream, header) && header != "\r") {
        	//Skip through headers.
//            std::cout << header << "\n";
        }
//        std::cout << "\n";

        // Read until EOF, writing data to output as we go.
        boost::system::error_code error;
        while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error)) {
        	// Read until EOF
        }
        if (error != boost::asio::error::eof)
            throw boost::system::system_error(error);
        unsigned responseLength = response.size();
        char * tmpData = new char[responseLength];
        response.sgetn(tmpData, responseLength);
        std::ofstream outStream(outFile.c_str(), std::ios::binary);
        outStream.write(tmpData, responseLength);
        outStream.close();
        delete tmpData;
//        std::cout << "left in buffer are " << response.size() << " bytes" << std::endl;
    }
    catch (std::exception& e) {
    	std::cerr << "exception occured while downloading: " << e.what() << std::endl;
    	std::cerr << "Please report this at http://project-osrm.org if issue persists" << std::endl;
        return false;
    }

    return true;
}
