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

#ifndef GET_ALL_CHILDREN_HPP
#define GET_ALL_CHILDREN_HPP

#include <string>
#include <iterator>
#include <xmim_api.h>

namespace lim_tslib_interface {

  /* Returns a list of the names of all the contracts available from the LIM */
  template<typename T>
  void getAllChildren(const XmimClientHandle& handle, T cont, const char* relname) {

    int num_relnames;
    XmimString* relnames;

    if(XmimGetRelChildren(handle, const_cast<char*>(relname), &num_relnames, &relnames) != XMIM_SUCCESS) {
      XmimPrintError(const_cast<char*>("XmimGetRelChildren"));
      return;
    }

    for(int i = 0; i < num_relnames; i++) {
      *cont++ = std::string(relnames[i]);
    }
  }
} // namespace lim_tslib_interface

#endif // GET_ALL_CHILDREN_HPP
