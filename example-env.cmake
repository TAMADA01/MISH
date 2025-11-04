#Заменить пути на свои
set(CMAKE_PREFIX_PATH "C:/local/msvc2017_64/lib/cmake" CACHE INTERNAL "" FORCE)
set(CMAKE_INSTALL_PREFIX "C:/MISH/components/installedlibs" CACHE INTERNAL "" FORCE)
set(BOOST_ROOT "C:/local/boost_1_84_0")
set(BASE_INSTALLED_DIR "C:/MISH/components/installedlibs")

#Скорее всего не трогать
set (Boost_NO_SYSTEM_PATHS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_STATIC_RUNTIME OFF)
set (BOOST_ALL_DYN_LINK OFF)

#set(CMAKE_AUTOMOC ON)
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
