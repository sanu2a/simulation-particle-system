# Créer un executable à partir de fichiers sources

enable_testing()



# Fait le lien avec la bibliothèque créée précedemment
# Les entêtes sont automatiquement détectés.
add_executable(TestUnit TestUniverUnit.cpp TestCelluleUnit.cpp TestParticuleUnit.cpp TestVecteurUnit.cpp)
add_executable(interactionstime interaction_perf.cpp)
add_executable(collections collections.cpp)
target_link_libraries(TestUnit  gtest_main)
include(GoogleTest)
gtest_discover_tests(TestUnit)