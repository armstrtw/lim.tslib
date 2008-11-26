///////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008  Whit Armstrong                                    //
//                                                                       //
// This program is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by  //
// the Free Software Foundation, either version 3 of the License, or     //
// (at your option) any later version.                                   //
//                                                                       //
// This program is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of        //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         //
// GNU General Public License for more details.                          //
//                                                                       //
// You should have received a copy of the GNU General Public License     //
// along with this program.  If not, see <http://www.gnu.org/licenses/>. //
///////////////////////////////////////////////////////////////////////////

#ifndef HAS_ROWS_HPP
#define HAS_ROWS_HPP

#include <string>
#include <iterator>
#include <xmim_api.h>

namespace lim_tslib_interface {

  template<typename T, typename U>
  void hasRows(const XmimClientHandle& handle, T cont, U beg, U end, const XmimUnits units) {
    XmimReturnCode xmimReply;
    XmimDate fromDate;
    XmimDate toDate;
    const char* colnames = "close";
    const int ncols = 1;

    while(beg != end) {
      xmimReply = XmimGetDataRange(handle,
				   const_cast<char*>(beg->c_str()),
				   ncols,
				   const_cast<char**>(&colnames),
				   units,
				   &fromDate,
				   &toDate);
      if(xmimReply == XMIM_ERROR) {
	XmimPrintError(const_cast<char*>("XmimGetDataRange"));
	*cont = false;
      } else {
	if(fromDate.year == 0 || fromDate.month == 0 || fromDate.day == 0) {
	  *cont = false;
	} else {
	  *cont = true;
	}
      }
      ++beg; ++cont;
    }
  }
} // namespace lim_tslib_interface

#endif // HAS_ROWS_HPP

