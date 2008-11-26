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

#ifndef GET_ROLL_DATES_HPP
#define GET_ROLL_DATES_HPP

#include <string>
#include <xmim_api.h>

namespace lim_tslib_interface {

  template<typename T>
  void getRollDates(const XmimClientHandle& handle, T cont, const char* relname, const char* rollDay) {

    int numContracts, numPeriods;
    XmimDate *rollDates, *contracts;
    std::string contractName;

    if(XmimVaGetRolloverDates(XMIM_CLIENT_HANDLE, handle,
                              XMIM_RELATION, const_cast<char*>(relname),
                              XMIM_COLUMN_LIST, NULL,
                              XMIM_UNITS, 1, XMIM_DAYS,
                              XMIM_ROLLOVER_DAY, const_cast<char*>(rollDay),
                              XMIM_NUM_CONTRACTS, &numContracts,
                              XMIM_NUM_PERIODS, &numPeriods,
                              XMIM_ROLL_DATES, &rollDates,
                              XMIM_CONTRACTS, &contracts,
                              XMIM_END_ARGS)!=XMIM_SUCCESS) {

      XmimPrintError(const_cast<char*>("XmimVaGetRolloverDates"));
      return;
    }

    for(int i = 0; i < numPeriods; i++) {
      //*cont++ = contracts[i].year * 100 + contracts[i].month;
      *cont++ = rollDates[i];
    }
  }
} // namespace lim_tslib_interface

#endif // GET_ROLL_DATES_HPP
