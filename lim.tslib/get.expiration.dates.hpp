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

#ifndef GET_EXPIRATION_DATES_HPP
#define GET_EXPIRATION_DATES_HPP

#include <string>
#include <xmim_api.h>

namespace lim_tslib_interface {

  template<typename T, typename U>
  void getExpirationDates(const XmimClientHandle& handle, T cont, U beg, U end) {
    XmimDate ex_date;

    while(beg != end) {
      ex_date.year = 0; ex_date.month = 0; ex_date.day = 0;

      if(XmimVaGetRelation(XMIM_CLIENT_HANDLE, handle,
                           XMIM_RELATION, const_cast<char*>(beg->c_str()),
                           XMIM_EXPIRATION_DATE, &ex_date,
                           XMIM_END_ARGS) != XMIM_SUCCESS) {
        XmimPrintError(const_cast<char*>("XmimVaGetRelation"));
      } else {
        *cont = ex_date;
      }
      ++cont; ++beg;
    }
  }
} // namespace lim_tslib_interface

#endif // GET_EXPIRATION_DATES_HPP
