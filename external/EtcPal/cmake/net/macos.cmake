# macOS networking compilation support for EtcPal

set(ETCPAL_NET_ADDITIONAL_SOURCES
  ${ETCPAL_ROOT}/include/os/macos/etcpal/os_inet.h
  ${ETCPAL_ROOT}/include/os/macos/etcpal/os_socket.h

  ${ETCPAL_ROOT}/src/os/macos/etcpal/os_error.h
  ${ETCPAL_ROOT}/src/os/macos/etcpal/os_error.c
  ${ETCPAL_ROOT}/src/os/macos/etcpal/os_inet.c
  ${ETCPAL_ROOT}/src/os/macos/etcpal/os_netint.c
  ${ETCPAL_ROOT}/src/os/macos/etcpal/os_socket.c
)
set(ETCPAL_NET_INCLUDE_DIR ${ETCPAL_ROOT}/include/os/macos)
