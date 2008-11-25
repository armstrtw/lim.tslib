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

#ifndef GET_RELATION_TYPES_HPP
#define GET_RELATION_TYPES_HPP

#include <string>
#include <iterator>
#include <xmim_api.h>

namespace lim_tslib_interface {

  template<typename T, typename U>
  void getRelationTypes(const XmimClientHandle& handle, T cont, U beg, U end) {
    XmimRelType reltype;

    while(beg != end) {
      if(XmimGetRelType (handle, const_cast<char*>(beg->c_str()), &reltype) != XMIM_SUCCESS) {
	XmimPrintError(const_cast<char*>("XmimGetRelType"));
	*cont++ = XMIM_REL_INVALID;
      } else {
	*cont++ = reltype;
      }
      ++beg;
    }
  }
} // namespace lim_tslib_interface

#endif // GET_RELATION_TYPES_HPP
