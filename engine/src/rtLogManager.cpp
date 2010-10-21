/*
Copyright (c) 2010 Alexander Novitsky                                             

Permission is hereby granted, free of charge, to any person obtaining a copy  
of this software and associated documentation files (the "Software"), to deal 
in the Software without restriction, including without limitation the rights  
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     
copies of the Software, and to permit persons to whom the Software is         
furnished to do so, subject to the following conditions:                      

The above copyright notice and this permission notice shall be included in    
all copies or substantial portions of the Software.                           

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN     
THE SOFTWARE.
*/

#include "rtCommonIncludes.h"
#include "rtLogManager.h"

URegisterSingleton(LogManager)

namespace rt
{
	LogManager::LogManager()
	{
		boost::gregorian::date localDate(boost::gregorian::day_clock::local_day());

		mFileStream.open("./logs/game.log.html");

		boost::posix_time::time_facet* facet = new boost::posix_time::time_facet("%H:%M:%S.%f");
		mFileStream.imbue(std::locale(mFileStream.getloc(), facet));

		mFileStream	<< "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">"
					<< "<html>"
					<< "<head>"
					<< "<meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\" />"
					<< "<title>ReTech Engine Log</title>"
					<< "<style type=\"text/css\" title=\"currentStyle\">"
					<< "@import \"./ext/css/demo_page.css\";"
					<< "@import \"./ext/css/demo_table_jui.css\";"
					<< "@import \"./ext/css/sunny/jquery-ui-1.8.5.custom.css\";"
					<< "</style>"
					<< "<script type=\"text/javascript\" language=\"javascript\" src=\"./ext/js/jquery.js\"></script>"
					<< "<script type=\"text/javascript\" language=\"javascript\" src=\"./ext/js/jquery.dataTables.min.js\"></script>"
					<< "<script type=\"text/javascript\" charset=\"utf-8\">"
					<< "$(document).ready(function() {"
					<< "$('#example').dataTable({\"bJQueryUI\": true,\"bAutoWidth\": true,\"sPaginationType\": \"full_numbers\"})"
					<< "} );"
					<< "</script>"
					<< "</head>"
					<< "<body id=\"dt_example\">"
					<< "<div id=\"container\">"
					<< "<div class=\"full_width big\">"
					<< "ReTech Engine Log (" << localDate << ")"
					<< "</div>"
					<< "<div id=\"demo\">"
					<< "<table cellpadding=\"0\" cellspacing=\"0\" border=\"0\" class=\"display\" id=\"example\">"
					<< "<thead>"
					<< "<tr>"
					<< "<th>Time</th>"
					<< "<th>Type</th>"
					<< "<th>Description</th>"
					<< "<th>Location</th>"
					<< "</tr>"
					<< "</thead>"
 					<< "<tbody>";
	}

	LogManager::~LogManager()
	{
		mFileStream << "</tbody>"
					<< "</table>"
					<< "</div>"
					<< "</body>"
					<< "</html>";

		if(mFileStream.is_open())
		{
			mFileStream.close();
		}
	}

	void LogManager::Critical( const std::string& iMessage, const std::string& iLocation/* = "Unknown"*/ )
	{
		

		if(mFileStream.is_open())
		{
			mFileStream << "<tr class=\"critical\"><td class=\"center\">" << boost::posix_time::microsec_clock::local_time().time_of_day() << "</td><td class=\"center\">Critical</td><td>" << iMessage <<"</td><td>" << iLocation << "</td></tr>";
		}
	}

	void LogManager::Error( const std::string& iMessage, const std::string& iLocation/* = "Unknown"*/ )
	{
		if(mFileStream.is_open())
		{
			mFileStream << "<tr class=\"error\"><td class=\"center\">" << boost::posix_time::microsec_clock::local_time().time_of_day() << "</td><td class=\"center\">Error</td><td>" << iMessage <<"</td><td>" << iLocation << "</td></tr>";
		}
	}

	void LogManager::Warning( const std::string& iMessage, const std::string& iLocation/* = "Unknown"*/ )
	{
		if(mFileStream.is_open())
		{
			mFileStream << "<tr class=\"warning\"><td class=\"center\">" << boost::posix_time::microsec_clock::local_time().time_of_day() << "</td><td class=\"center\">Warning</td><td>" << iMessage <<"</td><td>" << iLocation << "</td></tr>";
		}
	}

	void LogManager::Notice( const std::string& iMessage, const std::string& iLocation/* = "Unknown"*/ )
	{
		if(mFileStream.is_open())
		{
			mFileStream << "<tr class=\"notice\"><td class=\"center\">" << boost::posix_time::microsec_clock::local_time().time_of_day() << "</td><td class=\"center\">Notice</td><td>" << iMessage << "</td><td>" << iLocation << "</td></tr>";
		}
	}
}