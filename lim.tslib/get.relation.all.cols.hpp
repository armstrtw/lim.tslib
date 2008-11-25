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

#ifndef GET_RELATION_ALL_COLS_HPP
#define GET_RELATION_ALL_COLS_HPP


#include <vector>
#include <string>
#include <xmim_api.h>
#include <tslib/tseries.hpp>
#include <lim.tslib/xmim2tseries.hpp>

namespace lim_tslib_interface {
  using namespace tslib;

  template<class TDATE,
           class TDATA,
           class TSDIM,
           template<typename,typename,typename> class TSDATABACKEND,
           template<typename> class DatePolicy>
  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> getRelationAllCols(const XmimClientHandle& handle,
                                                                               const char* relname,
                                                                               const XmimUnits units,
                                                                               const int numUnits)
	   {
	     int numColumns = 0;
	     int numRecords = 0;
	     char** colNames = NULL;
	     double* values = NULL;
	     XmimDateTime* dates = NULL;
	     XmimReturnCode retCode;
	     XmimDate fromDate; fromDate.year = 1900; fromDate.month = 1; fromDate.day = 1;
	     XmimDate toDate; toDate.year = 2100; toDate.month = 12; toDate.day = 31;
	     XmimTime fromTime; fromTime.hour = 0; fromTime.minute = 0; fromTime.second = 0; fromTime.millisecond = 0;
	     XmimTime toTime; toTime.hour = 0; toTime.minute = 0; toTime.second = 0; toTime.millisecond = 0;

	     XmimGetRelColumns(handle, const_cast<char*>(relname), &numColumns, &colNames);
	     retCode = XmimGetRecordsDouble(handle, 1, const_cast<char**>(&relname),  numColumns, colNames, fromDate, toDate, fromTime, toTime, numUnits, units, XMIM_FILL_NAN, XMIM_FILL_NAN, XMIM_SKIP_ALL_NAN, 0, XMIM_LIMIT_BY_RECORDS, &numRecords, &dates, &values);

	     // return empty tseries if we encounter an error
	     if(retCode!=XMIM_SUCCESS) {
	       XmimPrintError(const_cast<char*>("XmimVaGetRecords"));
	       return TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>();
	     }
    
	     std::vector<std::string> colNamesVec; for(int i = 0; i < numColumns; i++) colNamesVec.push_back(colNames[i]);
	     return xmim2tseries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>(numRecords, numColumns, values, dates, colNamesVec);
	   }

} // namespace lim_tslib_interface

#endif // GET_RELATION_ALL_COLS_HPP
