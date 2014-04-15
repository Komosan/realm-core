/*************************************************************************
 *
 * TIGHTDB CONFIDENTIAL
 * __________________
 *
 *  [2011] - [2012] TightDB Inc
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of TightDB Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to TightDB Incorporated
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from TightDB Incorporated.
 *
 **************************************************************************/
#ifndef TIGHTDB_TEST_UTIL_TEST_PATH_HPP
#define TIGHTDB_TEST_UTIL_TEST_PATH_HPP

#include <string>

#include <tightdb/util/features.h>

#include "unit_test.hpp"

#define TEST_PATH_HELPER(class_name, var_name, suffix) \
    class_name var_name(tightdb::test_util::get_test_path(test_details, "." #var_name "." suffix))

#define TEST_PATH(var_name) \
    TEST_PATH_HELPER(tightdb::test_util::TestPathGuard, var_name, "test");

#define GROUP_TEST_PATH(var_name) \
    TEST_PATH_HELPER(tightdb::test_util::TestPathGuard, var_name, "tightdb");

#define SHARED_GROUP_TEST_PATH(var_name) \
    TEST_PATH_HELPER(tightdb::test_util::SharedGroupTestPathGuard, var_name, "tightdb");

namespace tightdb {
namespace test_util {

/// Disable removal of test files. If called, the call must complete
/// before any TestPathGuard object is created.
void keep_test_files();

std::string get_test_path(const unit_test::TestDetails&, const char* suffix);

class PlatformConfig {
public:
    static PlatformConfig* Instance();
    std::string get_path();
    void set_path(std::string);
    std::string get_resource_path();
    void set_resource_path(std::string);
private:
    PlatformConfig(){};
    PlatformConfig(PlatformConfig const&){}; // Private copy constructor
    PlatformConfig& operator=(PlatformConfig const&); // Private assignment operator
    static PlatformConfig* instance;
    std::string test_path;
    std::string test_resource_path;
};

/// Constructor and destructor removes file if it exists.
class TestPathGuard {
public:
    TestPathGuard(const std::string& path);
    ~TestPathGuard() TIGHTDB_NOEXCEPT;
    operator std::string() const
    {
        return m_path;
    }
    const char* c_str() const
    {
        return m_path.c_str();
    }
protected:
    std::string m_path;
};

class SharedGroupTestPathGuard: public TestPathGuard {
public:
    SharedGroupTestPathGuard(const std::string& path);
    std::string get_lock_path() const
    {
        return m_path + ".lock";
    }
};

} // namespace test_util
} // namespace tightdb

#endif // TIGHTDB_TEST_UTIL_TEST_PATH_HPP