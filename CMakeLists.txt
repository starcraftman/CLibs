CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(ArgTable C)

FIND_PACKAGE(ZLIB)
FIND_PACKAGE(CURL)

SET(LIB_INCLUDES ${CMAKE_SOURCE_DIR}/libs/include)
SET(ARGTABLE_LIB ${CMAKE_SOURCE_DIR}/libs/lib/libargtable2.a)
SET(DEBUG_FLAGS "-ggdb -Wall -Wextra -Winline -Wfatal-errors -pedantic")
SET(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c11 -D_REENTRANT ${DEBUG_FLAGS}")
# Important note, libxml needs math & zlib libraries.
IF(UNIX)
    SET(LIBXML_LIB ${CMAKE_SOURCE_DIR}/libs/lib/libxml2.a m ${ZLIB_LIBRARIES})
ELSE(UNIX)
    SET(LIBXML_LIB ${CMAKE_SOURCE_DIR}/libs/lib/libxml2.a ${ZLIB_LIBRARIES})
ENDIF(UNIX)
SET(JSON_LIB ${CMAKE_SOURCE_DIR}/libs/lib/libjansson.a)

INCLUDE_DIRECTORIES(
    ${LIB_INCLUDES}
    ${CURL_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIRS}
)

ADD_SUBDIRECTORY(args)
ADD_SUBDIRECTORY(jansson)
ADD_SUBDIRECTORY(xmlParse)

ADD_EXECUTABLE(ArgTable ${TAB_SRCS})
TARGET_LINK_LIBRARIES(ArgTable ${ARGTABLE_LIB})

ADD_EXECUTABLE(ArgP ${ARGP_SRCS})

ADD_EXECUTABLE(XML_Parse1 ${XMLP1_SRCS})
TARGET_LINK_LIBRARIES(XML_Parse1 ${LIBXML_LIB})

ADD_EXECUTABLE(XML_Reader1 ${XMLR1_SRCS})
TARGET_LINK_LIBRARIES(XML_Reader1 ${LIBXML_LIB})

ADD_EXECUTABLE(JSON_1 ${JSON1_SRCS})
TARGET_LINK_LIBRARIES(JSON_1 ${JSON_LIB} ${CURL_LIBRARIES})
