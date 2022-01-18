//============================================================================
/// \file
/// \ingroup    g_unittests
/// \brief      Test accessing the generated version information.
/// \copyright  GNU General Public License (GPL) Version 3
//============================================================================

#include "app-lib/VersionInfo.h"
#include "Helpers.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

/// \test VersionInfo::getVersion() returns a non-empty string
TEST(VersionInfo,getVersionIsNotEmpty) {
    QString version = VersionInfo::getVersion();
    cout << "[          ] Version: " << version.toStdString() << endl;

    ASSERT_FALSE( version.isEmpty() );
}

/// \test VersionInfo::getVersion() returns a printable string
TEST(VersionInfo,getVersionIsPrintable) {
    QString version = VersionInfo::getVersion();

    ASSERT_TRUE( Helpers::isPrintable(version) );
}

/// \test VersionInfo::getBuildTag() returns a non-empty string
TEST(VersionInfo,getBuildTagIsNotEmpty) {
    QString buildTag = VersionInfo::getBuildTag();

    ASSERT_FALSE( buildTag.isEmpty() );
}

/// \test VersionInfo::getBuildTag() returns a printable string
TEST(VersionInfo,getBuildTagIsPrintable) {
    QString buildTag = VersionInfo::getBuildTag();

    ASSERT_TRUE( Helpers::isPrintable(buildTag) );
}
