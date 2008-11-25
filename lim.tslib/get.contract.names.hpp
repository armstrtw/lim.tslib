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

#ifndef GET_CONTRACT_NAMES_HPP
#define GET_CONTRACT_NAMES_HPP

#include <string>
#include <iterator>
#include <set>
#include <vector>

#include <xmim_api.h>
#include <lim.tslib/get.all.children.hpp>
#include <lim.tslib/get.relation.types.hpp>
#include <lim.tslib/has.rows.hpp>

namespace lim_tslib_interface {

  /* Returns a list of the names of all the contracts available from the LIM */
  template<typename T>
  void getContractNames(const XmimClientHandle& handle, T cont, const char* relname, const XmimUnits units, const int bars) {    
    std::set<std::string> tickers;
    std::vector<bool> has_rows;
    std::vector<XmimRelType> relTypes;

    // read in all children
    getAllChildren(handle, std::inserter(tickers,tickers.begin()), relname);

    // find rel types
    getRelationTypes(handle, std::inserter(relTypes,relTypes.begin()), tickers.begin(), tickers.end());

    // see if there is actual data in the relation
    hasRows(handle, std::inserter(has_rows,has_rows.begin()), tickers.begin(), tickers.end(), units);

    // drop out continuous contracts and such
    // only accept actual futures contracts
    std::vector<XmimRelType>::iterator relTypes_iter = relTypes.begin();
    std::vector<bool>::iterator has_rows_iter = has_rows.begin();

    for(std::set<std::string>::iterator it = tickers.begin(); it != tickers.end(); it++) {
      if(*relTypes_iter++ == XMIM_REL_FUTURES_CONTRACT && *has_rows_iter++) {
	*cont++ = *it;
      }
    }
  }

} // namespace lim_tslib_interface

#endif // GET_CONTRACT_NAMES_HPP
