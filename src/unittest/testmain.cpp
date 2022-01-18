//============================================================================
/// \file
/// \ingroup    g_unittests
/// \brief      The googlemock / googletest main file.
/// \details    As you may have guessed already, it contains the
///             unit test main() function and nothing else.
/// \copyright  GNU General Public License (GPL) Version 3
//============================================================================

#include <gmock/gmock.h>

/// The unit test main() function.
/// Not much to do here, just init Google Mock (which also inits Google Test)
/// giving it `argc` / `argv`, and then run the tests.
int main(int argc, char **argv) {
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
