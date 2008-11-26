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

#ifndef GET_PERPETUAL_SERIES_HPP
#define GET_PERPETUAL_SERIES_HPP


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
  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> getPerpetualSeries(const XmimClientHandle& handle,
                                                                               const char* relname,
                                                                               const std::vector<std::string>& colnames,
                                                                               const char* rollDay,
                                                                               const char* rollPolicy,
                                                                               const XmimUnits units,
                                                                               const int numUnits)
	   {
	     int num_columns = colnames.size();
	     int num_records = 0;
	     float* values = NULL;
	     XmimDateTime* dates = NULL;
	     XmimReturnCode retCode;
	     XmimDate from_date;

	     from_date.year  = 1900;
	     from_date.month = 1;
	     from_date.day   = 1;

	     // return empty tseries if no colnames supplied
	     if(!num_columns) {
	       return TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>();
	     }

	     XmimString* xmim_columns = new XmimString[num_columns];
	     int i = 0;
	     for(std::vector<std::string>::const_iterator it = colnames.begin(); it != colnames.end(); it++, i++) {
	       xmim_columns[i] = strdup(it->c_str());
	     }

	     retCode = XmimVaGetRecordsRollover(XMIM_CLIENT_HANDLE, handle,
						XMIM_RELATION, const_cast<char*>(relname),
						XMIM_COLUMN_ARRAY, num_columns, xmim_columns,
						XMIM_FROM_DATE, from_date,
						XMIM_UNITS, numUnits, units,
						XMIM_ROLLOVER_DAY, rollDay,
						XMIM_ROLLOVER_POLICY, rollPolicy,
						XMIM_NUM_RECORDS, &num_records,
						XMIM_DATE_TIMES, &dates,
						XMIM_VALUES, &values,
						XMIM_FILL_OPTION, XMIM_FILL_NAN, XMIM_FILL_NAN, XMIM_SKIP_ALL_NAN,
						XMIM_END_ARGS);

	     // free our colnames array
	     for(i = 0; i < num_columns; i++)
	       free(xmim_columns[i]);
	     delete []xmim_columns;

	     // return empty tseries if we encounter an error
	     if(retCode!=XMIM_SUCCESS) {
	       XmimPrintError(const_cast<char*>("XmimVaGetRecords"));
	       return TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>();
	     }

	     return xmim2tseries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>(num_records, num_columns, values, dates, colnames);
	   }
} // namespace lim_tslib_interface

#endif // GET_PERPETUAL_SERIES_HPP
