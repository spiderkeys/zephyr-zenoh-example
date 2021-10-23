if(NOT CONFIG_ZENOH_PICO)
  return()
endif()

set(ZENOH_DIR ${ZEPHYR_CURRENT_MODULE_DIR})

set( ZENOH_SOURCES 
  ${ZENOH_DIR}/src/collections/bytes.c
  ${ZENOH_DIR}/src/collections/intmap.c
  ${ZENOH_DIR}/src/collections/list.c
  ${ZENOH_DIR}/src/collections/mvar.c
  ${ZENOH_DIR}/src/collections/string.c
  ${ZENOH_DIR}/src/collections/vec.c

  ${ZENOH_DIR}/src/system/common.c
  ${ZENOH_DIR}/src/system/zephyr/network.c
  ${ZENOH_DIR}/src/system/zephyr/system.c

  ${ZENOH_DIR}/src/zenoh/api.c

  ${ZENOH_DIR}/src/zenoh/link/manager.c
  ${ZENOH_DIR}/src/zenoh/link/tcp.c
  ${ZENOH_DIR}/src/zenoh/link/udp.c

  ${ZENOH_DIR}/src/zenoh/protocol/codec.c
  ${ZENOH_DIR}/src/zenoh/protocol/iobuf.c
  ${ZENOH_DIR}/src/zenoh/protocol/msgcodec.c
  ${ZENOH_DIR}/src/zenoh/protocol/property.c
  ${ZENOH_DIR}/src/zenoh/protocol/rname.c
  ${ZENOH_DIR}/src/zenoh/protocol/utils.c

  ${ZENOH_DIR}/src/zenoh/session/query.c
  ${ZENOH_DIR}/src/zenoh/session/queryable.c
  ${ZENOH_DIR}/src/zenoh/session/resource.c
  ${ZENOH_DIR}/src/zenoh/session/rx.c
  ${ZENOH_DIR}/src/zenoh/session/scout.c
  ${ZENOH_DIR}/src/zenoh/session/subscription.c
  ${ZENOH_DIR}/src/zenoh/session/tx.c
  ${ZENOH_DIR}/src/zenoh/session/utils.c

  ${ZENOH_DIR}/src/zenoh/transport/rx.c
  ${ZENOH_DIR}/src/zenoh/transport/link/rx.c
  ${ZENOH_DIR}/src/zenoh/transport/link/tx.c
  ${ZENOH_DIR}/src/zenoh/transport/link/task/lease.c
  ${ZENOH_DIR}/src/zenoh/transport/link/task/read.c  
)

# Library target
zephyr_interface_library_named( zenoh-pico )
target_include_directories( zenoh-pico INTERFACE ${ZENOH_DIR}/include)
target_compile_definitions( zenoh-pico INTERFACE ZENOH_ZEPHYR=1 )
target_link_libraries( zenoh-pico INTERFACE posix_subsys )

zephyr_library()
zephyr_library_sources( ${ZENOH_SOURCES} )
zephyr_library_link_libraries( zenoh-pico )