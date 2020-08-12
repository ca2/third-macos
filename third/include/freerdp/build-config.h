#ifndef FREERDP_BUILD_CONFIG_H
#define FREERDP_BUILD_CONFIG_H

#define FREERDP_DATA_PATH "$HOME/application/rdp/data"
#define FREERDP_KEYMAP_PATH "$HOME/application/rdp/keymap"
#define FREERDP_PLUGIN_PATH "$HOME/application/rdp/plugin"

#define FREERDP_INSTALL_PREFIX "$HOME/application/rdp"

#define FREERDP_LIBRARY_PATH "$HOME/application/rdp/library"

#define FREERDP_ADDIN_PATH "$HOME/application/rdp/addin"

#ifdef _WIN32
#define FREERDP_SHARED_LIBRARY_SUFFIX ".dll"
#define FREERDP_SHARED_LIBRARY_PREFIX  ""
#elif defined(__APPLE__)
#define FREERDP_SHARED_LIBRARY_SUFFIX ".dylib"
#define FREERDP_SHARED_LIBRARY_PREFIX  "lib"
#else
#define FREERDP_SHARED_LIBRARY_SUFFIX ".so"
#define FREERDP_SHARED_LIBRARY_PREFIX  "lib"
#endif

#define FREERDP_VENDOR_STRING "ca2"
#define FREERDP_PRODUCT_STRING "rdp"

#define FREERDP_PROXY_PLUGINDIR "$HOME/application/rdp/proxy_plugin"

#endif /* FREERDP_BUILD_CONFIG_H */
