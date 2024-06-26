## Indique qu'elle version de cmake minimale est utilisée.
cmake_minimum_required (VERSION 3.16.3)

## Specifie le nom du projet et le langage de programmation du projet
project(Lab3 CXX)

## Force le standard 
set(CMAKE_CXX_STANDARD 17)

## Indique les options de compilations pour le projet
## -pg : donne la possibilité de faire du profiling
## -Wall : affiche les warnings
set(CMAKE_CXX_FLAGS "-Wall")

## Définir la localisation des entêtes.
## include_directories sera propager à l'ensemble du projet
include_directories(${CMAKE_SOURCE_DIR}/include)

## Parcours les sous répertoires contenant les définitions (.cxx)
## On commence par créer une bibliothèque
add_subdirectory(src)

## On créée les tests pour la bibliothèque.
## Ces tests sont unitaires ou fonctionnels
# GoogleTest requires at least C++11

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.8.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(test)
add_subdirectory(demo)
