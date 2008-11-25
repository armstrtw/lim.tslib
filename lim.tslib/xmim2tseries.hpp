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

#ifndef XMIM2TSERIES_HPP
#define XMIM2TSERIES_HPP

#include <xmim_api.h>
#include <tslib/tseries.hpp>

namespace lim_tslib_interface {
  using namespace tslib;

  template<class TDATE,
           class TDATA,
           class TSDIM,
           template<typename,typename,typename> class TSDATABACKEND,
           template<typename> class DatePolicy,
           class LIMTYPE>
  const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>  xmim2tseries(const int num_records,
									  const int num_columns,
									  const LIMTYPE* values,
									  const XmimDateTime *dates, 
									  const std::vector<std::string>& colnames)
           {

             unsigned int r_index, lim_index;

             // allocate new answer
             TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> ans(num_records, num_columns);

             // set colnames
             ans.setColnames(colnames);
  
             TDATA* ans_data = ans.getData();  
             TDATE* ans_dates = ans.getDates();  

             for(int i = 0; i < num_records; i++) {
               ans_dates[i] = DatePolicy<TDATE>::toDate(dates[i].year,
                                                        dates[i].month,
                                                        dates[i].day,
                                                        dates[i].hour,
                                                        dates[i].minute,
                                                        dates[i].second,
                                                        dates[i].millisecond);

               // loop through columns
               for(int j = 0; j < num_columns; j++) {
                 lim_index = i*num_columns+j; // lim is column minor
                 r_index = i+num_records*j;   // R is column major
                 ans_data[r_index] = std::isnan(values[lim_index]) ? numeric_traits<TDATA>::NA() : static_cast<TDATA>(values[lim_index]);
               }
             }
             return ans;
           }
} // namespace lim_tslib_interface

#endif // XMIM2TSERIES_HPP
