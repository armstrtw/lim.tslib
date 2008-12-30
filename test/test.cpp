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

#include <iostream>
#include <vector>
#include <map>
#include <boost/test/unit_test.hpp>

#include <tslib/tseries.hpp>
#include <xmim_api.h>
#include <lim.tslib/lim.tslib.hpp>
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using boost::unit_test::test_suite;
using namespace tslib;

//LDL = long, double, long
//DDL = double, double, long
typedef TSeries<long,double,long,TSdataSingleThreaded,PosixDate> LDL_ts;
typedef TSeries<double,double,long,TSdataSingleThreaded,PosixDate> DDL_ts;

// global for all calls to use
static XmimClientHandle lim_handle;

const XmimClientHandle limConnect() {
  XmimClientHandle handle = 0;

  char* limServer = getenv("LIM_SERVER");
  char* limPort_char = getenv("LIM_PORT");

  if(limServer == NULL || limPort_char == NULL) {
    cerr << "please make sure LIM_SERVER and LIM_PORT are defined in your environment." << endl;
  } else {
    int limPort = atoi(limPort_char);
    if(XmimConnect(limServer, limPort, &handle)!= XMIM_SUCCESS) {
      cerr << "failed to connect to lim" << endl;
    }
  }
  return handle;
}

void test_get_relation() {
  const char* relname = "IBM";
  std::vector<std::string> colnames;
  colnames.push_back("close");
  const XmimUnits xmim_units = XMIM_DAYS;
  const int numUnits = 1;
  LDL_ts ans;

  ans = lim_tslib_interface::getRelation<long,double,long,TSdataSingleThreaded,PosixDate>(lim_handle,
											  relname,
											  colnames,
											  xmim_units,
											  numUnits);
  BOOST_CHECK( ans.nrow() > 0);
  BOOST_CHECK( ans.ncol() == 1);
}

void test_get_relation_all_cols() {
  const char* relname = "IBM";
  const XmimUnits xmim_units = XMIM_DAYS;
  const int numUnits = 1;
  LDL_ts ans;

  ans = lim_tslib_interface::getRelationAllCols<long,double,long,TSdataSingleThreaded,PosixDate>(lim_handle,
											  relname,
											  xmim_units,
											  numUnits);
  BOOST_CHECK( ans.nrow() > 0);
  //BOOST_CHECK( ans.ncol() == 1);
}

void test_get_relation_types() {
  std::vector<std::string> relnames;
  relnames.push_back("IBM");
  relnames.push_back("TY");
  std::vector<XmimRelType> ans;
  lim_tslib_interface::getRelationTypes(lim_handle,
					std::back_inserter(ans),
					relnames.begin(),
					relnames.end());

  BOOST_CHECK(ans.size() == relnames.size());
}

void test_get_perpetual_series() {
  const char* relname = "TY";
  std::vector<std::string> colnames;
  colnames.push_back("close");
  const char* rollDay = "open_interest crossover";
  const char* rollPolicy = "actual prices";
  const XmimUnits xmim_units = XMIM_DAYS;
  const int numUnits = 1;
  LDL_ts ans;

  ans = lim_tslib_interface::getPerpetualSeries<long,double,long,TSdataSingleThreaded,PosixDate>(lim_handle,
												 relname,
												 colnames,
												 rollDay,
												 rollPolicy,
												 xmim_units,
												 numUnits);
  BOOST_CHECK( ans.nrow() > 0);
  BOOST_CHECK( ans.ncol() == 1);
}


void test_get_futures_series() {
  const char* relname = "TY";
  const XmimUnits xmim_units = XMIM_DAYS;
  const int numUnits = 1;
  std::map< std::string, LDL_ts> ans;

  lim_tslib_interface::getFuturesSeries<long,double,long,TSdataSingleThreaded,PosixDate>(lim_handle,
											 ans,
											 relname,
											 xmim_units,
											 numUnits);

  for(std::map< std::string, LDL_ts>::iterator iter = ans.begin(); iter != ans.end(); iter++) {
    cout << iter->first << endl;
  }
}

void test_get_contract_names() {
  const char* relname = "LIF.I";
  const XmimUnits xmim_units = XMIM_DAYS;
  std::vector<std::string> ans;

  lim_tslib_interface::getContractNames(lim_handle,back_inserter(ans),relname,xmim_units);

  for(std::vector<std::string>::iterator it = ans.begin(); it != ans.end(); it++) {
    cout << *it << endl;
  }
}

void test_has_rows() {
  const XmimUnits xmim_units = XMIM_DAYS;
  std::vector<bool> ans;
  std::vector<std::string> tickers;

  tickers.push_back("LIF.I_1989M");
  tickers.push_back("LIF.I_1989U");
  tickers.push_back("LIF.I_1989Z");

  // see if there is actual data in the relation
  lim_tslib_interface::hasRows(lim_handle, std::inserter(ans,ans.begin()), tickers.begin(), tickers.end(), xmim_units);

  for(std::vector<bool>::iterator it = ans.begin(); it != ans.end(); it++) {
    cout << *it << endl;
  }

}

test_suite*
init_unit_test_suite( int argc, char* argv[] ) {
  test_suite* test= BOOST_TEST_SUITE("tslib test");

  lim_handle = limConnect();

  test->add( BOOST_TEST_CASE( &test_get_relation_types ) );
  test->add( BOOST_TEST_CASE( &test_get_relation ) );
  test->add( BOOST_TEST_CASE( &test_get_relation_all_cols ) );
  test->add( BOOST_TEST_CASE( &test_get_futures_series ) );
  test->add( BOOST_TEST_CASE( &test_get_contract_names ) );
  test->add( BOOST_TEST_CASE( &test_has_rows ) );

  return test;
}
